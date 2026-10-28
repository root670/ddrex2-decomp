#!/usr/bin/env python3
"""configure.py -- split a target's retail ELF with splat and write the ninja build graph.

Usage::

    python3 configure.py --target <name>             # every split, plus the link edges
    python3 configure.py --target <name> --objects   # object graph only (CI objdiff job)

The target is *named*, never assumed.  ``config/targets.py`` owns the retail binary's path and
its G1 pin, the disc image, the config directory, the measured geometry (the loadable segment
in file and virtual addresses, the sections after it, the two chunked sections' lengths and
where the boot ELF sits in the image) and the compiler/flag pair each promoted unit was
measured against; this script reads all of it from there, so a second target is a second
descriptor rather than a second copy of this file.

The retail binary is read, never written: this script consumes the target's ELF and the
oracle's manifests (``cus.json``, ``debug_chunks.json``, ``symbol_addrs.txt``) and writes

* ``config/<target>/splat.yaml``             -- the whole segment list, refined per debug chunk
* ``config/<target>/splat_symbol_addrs.txt`` -- ``symbol_addrs.txt`` in the syntax splat accepts
* ``build/<elf>.ld``                         -- the pinned link: every byte of the file at its
                                                own file offset (see :func:`pinned_ld_script`)
* ``config/<target>/undefined_{funcs,syms}_auto.txt``, ``asm/**``, ``build/**`` and
  ``build.ninja``

via ``python3 -m splat split``.  Every byte of the file is covered by exactly one segment
(the section header table and all inter-section padding included), so the split is a
faithful partition of the retail image rather than a text-only sketch of it.

The image itself is assembled in two halves, because the retail ELF only *loads* the first
one: ``ld`` pins the loadable image (ELF header, code, bss) at its retail addresses and
``objcopy -O binary`` turns it into the file's first ``loadable_end`` bytes, while the file's
tail -- ``.shstrtab``, ``.debug``, ``.line``, ``.comment``, ``.reginfo`` and the section header
table, none of which the retail ELF loads -- is assembled from splat's databin assets in
manifest order.  ``objcopy`` cannot emit a non-loadable section, and a ``mwccps2`` link
drops ``.debug``/``.line`` outright (R18), so the tail is file content, not linker output.

Exit codes: 0 ok, 1 a build step failed, 2 the configuration or a manifest is unusable.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import pathlib
import re
import subprocess
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parent
if str(REPO_ROOT / "tools") not in sys.path:  # run as `python3 configure.py` too
    sys.path.insert(0, str(REPO_ROOT / "tools"))
if str(REPO_ROOT) not in sys.path:  # `config.targets`, the descriptor every tool reads
    sys.path.insert(0, str(REPO_ROOT))

from config import targets  # noqa: E402  the one place a target's facts are written down
from diff import basis  # noqa: E402  retail's own bytes as an object objdiff can pair
from toolchain import compile as cc  # noqa: E402  the one derivation of a unit's placement
from toolchain.retail import Retail  # noqa: E402  the file a unit's retail bytes are in

SPLAT = [sys.executable, "-m", "splat", "split"]
# objdiff's config schema, named so an editor can check the emitted project.
OBJDIFF_SCHEMA = ("https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json")

# The default target -- the one the tree is configured for when no ``--target`` names another.
# Nothing in this file spells a target name or a retail path: the numbers live in the
# descriptor, and every function here takes the geometry it works on as an argument, so
# ``--target`` is the only thing that decides which file is split and where its sections sit.
# The geometry is resolved *lazily* (`_geometry` below): a target nobody has measured yet must
# not make this module unimportable -- it must stop the one function that would have used a
# number nobody measured, which is what `Target.geometry_required` does.
TARGET = targets.get(targets.DEFAULT)
CHUNKED = ("debug", "line")  # refined into one databin per debug_chunks.json entry


def _geometry(target=None, geometry=None):
    """The geometry a function works with: the argument, or the target's own measurement."""
    if geometry is not None:
        return geometry
    return (target or TARGET).geometry_required()


def _display(path) -> str:
    """A path as the yaml, a ninja edge and a reader spell it: repo-relative, POSIX."""
    path = pathlib.Path(path)
    try:
        return path.relative_to(REPO_ROOT).as_posix()
    except ValueError:
        return str(path)


def _config_path(target, name) -> str:
    """A generated file inside ``target``'s config dir, spelled from the repo root."""
    return _display(target.config_dir / pathlib.Path(name).name)


# A split's instruction comments carry both views of the same byte: `/* <file offset>
# <virtual address> <bytes> */`.  The address is what the link needs (splat does not put
# it in the split's path) and the file offset is the invariant that ties it back to the
# loadable segment, so a split placed at the wrong address is caught here, not by G1.
SPLIT_COMMENT = re.compile(r"/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/")
LABEL_DEF = re.compile(r"^\s*(?:glabel|dlabel|alabel|jlabel)\s+(\S+)\s*$", re.M)
# Names splat derives from an address always end in that address; the prefix says what it
# is (`.L` local label, `D_` data, `func_` code, `jtbl_` jump table).
ALIAS_ADDRESS = re.compile(r"^(?:\.L|D_|lbl_|jtbl_|func_)([0-9A-F]{5,8})$")
ALIAS_TOKEN = re.compile(r"(?<![\w$.])((?:\.L|D_|lbl_|jtbl_|func_)[0-9A-F]{5,8})(?![\w.])")
IDENTIFIER = re.compile(r"[A-Za-z_.][A-Za-z0-9_.]*")

YAML_HEADER = """\
# Generated by configure.py --target {target} -- do not edit by hand.
#
# The segment list partitions {elf} byte for byte: the ELF header, every
# section, the section header table and all inter-section padding have a home.  The
# .debug and .line sections are cut into one databin per debug_chunks.json entry so a
# single translation unit's debug bytes can be diffed (and later matched) in isolation.
"""

NINJA_HEADER = """\
# Generated by configure.py --target {target} -- do not edit by hand.
#
# `ninja splits` materialises the splat output, `ninja objects` assembles every split.
# Bare `ninja` builds and gates {built}: `ld` pins the loadable image to its
# retail addresses, `bin` objcopies it, `cat` assembles the file's non-loadable tail from
# splat's databins and joins the two halves, and `g1` compares the result with
# {elf} (R5).
"""

# `as` needs -Iasm/include for the `.include "macro.inc"` that splat writes into every
# data split: GNU as resolves `.include` against the working directory and -I only, never
# against the including file, and the generated macros must not land in a tracked dir.
# --no-pad-sections keeps a split's .text exactly as long as the function: gas otherwise
# pads every section out to its 16-byte alignment, which would inflate the linked image.
# The `.align` lines are dropped for the same reason, from the *stream*, never from a
# split: splat emits them for alignment that is true in absolute VA terms, so in an
# object that starts at the function's own address (VA 0x26CC4C, say) they insert four
# zero bytes that the retail bytes already carry explicitly -- the splits' `.word` /
# `.short` / `.byte` stream is a byte-exact 1,713,792-byte partition on its own, and
# 19 splits (one per VA that is 4 mod 8) assemble 4 bytes too long while they survive.
# The interpreter every emitted edge runs its driver with.  ``sys.executable``, never the POSIX
# name ``python3``: ninja starts an edge with ``CreateProcess`` on Windows -- no shell -- where
# the interpreter is ``python.exe`` and need not be on PATH at all, so the graph spells the
# interpreter that configured *this* checkout.  Emitted once, as ninja's own ``python``
# variable, and referenced quoted because ``sys.executable`` may live under ``C:\Program Files``.
PYTHON = sys.executable

# The `as` rule's program.  It used to be a shell pipeline -- ``cpp -Iinclude $in -o - | sed -E
# '.../d' | mips-linux-gnu-as ...`` -- and ninja's Windows port has neither of those filters nor
# even a ``|`` to join them with.  ``as_split.py`` drops the same ``.align`` lines and runs the
# same ``as`` invocation itself, and the object bytes are unchanged: ``tests/test_configure.py``
# compares the two rules split by split.  The program is text of this graph's own, so it is an
# implicit input of every `as` edge (`AS_PROGRAM` below, beside ``GENERATOR``).
AS_PROGRAM = "tools/toolchain/as_split.py"
AS_RULE = f'"$python" {AS_PROGRAM} $in -o $out'

# ``objcopy --dump-section <section>=<out> <in> <copy>`` needs a *named* output file: a lone
# input is an in-place edit, and the two objsec edges run concurrently against the same object
# (the comment on the rule has the observation).  The copy itself is not wanted, so it goes to
# the null device -- and that is ``os.devnull``, ``/dev/null`` on POSIX and ``nul`` on Windows,
# because ``cmd`` cannot spell the POSIX one.  One Python process, no shell features, and the
# exit status objcopy returned.
OBJSEC_PY = ("import os, subprocess, sys; sys.exit(subprocess.call(["
             "'mips-linux-gnu-objcopy', '--dump-section', "
             "sys.argv[1] + '=' + sys.argv[2], sys.argv[3], os.devnull]))")

# ``cat $in > $out`` in one process: ``>`` means the same thing in ``sh`` and ``cmd``, but
# ``cat`` is not a program on Windows.  Unbuffered read/write, inputs in the order ninja gives.
CAT_PY = ("import sys; open(sys.argv[1], 'wb').write("
          "b''.join(open(path, 'rb').read() for path in sys.argv[2:]))")

# The graph has to depend on the code that generates it (R35a).  Every command line below
# is text from this file, and the `cc` rule's *program* is `tools/toolchain/compile.py` --
# whose own bytes decide the object's bytes, because the staged source path's length is
# baked into the DWARF.  Ninja does not hash command lines, so without these inputs editing
# either file leaves the objects it produced in place, silently: the machinery runs once,
# proves itself, and then never again.  They are declared as *implicit* inputs (`|`), which
# ninja keeps out of `$in` (verified on the pinned ninja 1.13.2), so no rule command changes
# and an edge is dirtied exactly when one of these files is touched.
GENERATOR = "configure.py"
COMPILER_DRIVER = "tools/toolchain/compile.py"
#: What every generated edge must declare: the file whose text spells it out.
GENERATED_BY = (GENERATOR,)
#: ... and what the compile edges add: the program that computes the object's content.
COMPILE_EDGE_INPUTS = (COMPILER_DRIVER, GENERATOR)


class ConfigError(Exception):
    """Unusable configuration or manifest: reported on stderr, exit 2, nothing written."""


# ---------------------------------------------------------------------------
# Manifests
# ---------------------------------------------------------------------------


def load_json(path: pathlib.Path, label: str):
    if not path.is_file():
        raise ConfigError(f"{label} not found: {path}")
    try:
        return json.loads(path.read_text())
    except json.JSONDecodeError as exc:
        raise ConfigError(f"{label} is not valid JSON: {path}: {exc}") from exc


def check_manifests(cus, chunks) -> None:
    """The chunk grouper keys off the TU file name, so a mis-grouped manifest is silent.

    There are exactly as many ``.debug`` chunks as ``cus.json`` has ``kind:tu`` records,
    each one starting at the TU it belongs to (a chunk that starts anywhere else means
    two TUs were merged, or a function stolen from its TU), and their ``tunits`` must
    cover every record exactly once.  Every ``.line`` chunk names the one record whose
    statement list it holds.  A bad manifest is reported, never repaired.
    """
    tus = [i for i, record in enumerate(cus) if record.get("kind") == "tu"]
    debug = [c for c in chunks if c.get("section") == ".debug"]
    if len(debug) != len(tus):
        raise ConfigError(
            f"debug_chunks.json has {len(debug)} .debug chunks but cus.json has "
            f"{len(tus)} kind:tu records; regenerate both from the same oracle run")
    for index, chunk in enumerate(debug):
        tunits = chunk.get("tunits") or []
        first = tunits[0] if tunits else None
        if first != tus[index] or cus[first].get("kind") != "tu":
            raise ConfigError(
                f"debug_chunks.json .debug chunk {index} starts at cus.json index "
                f"{first}, not at kind:tu record {tus[index]}; adjacent same-named TUs "
                f"would be merged silently")
    covered = sorted(t for chunk in debug for t in chunk["tunits"])
    if covered != list(range(len(cus))):
        raise ConfigError(
            "debug_chunks.json .debug chunks do not cover every cus.json record exactly "
            "once; the chunk grouper dropped or duplicated records")
    for index, chunk in enumerate(c for c in chunks if c.get("section") == ".line"):
        tunits = chunk.get("tunits") or []
        first = tunits[0] if tunits else None
        if not isinstance(first, int) or not (0 <= first < len(cus)) \
                or cus[first].get("stmt_list") is None:
            raise ConfigError(
                f"debug_chunks.json .line chunk {index} starts at cus.json index "
                f"{first}, which is not a record with a statement list")


def check_chunk_tiling(chunks, section: str, offset: int, size: int, geometry=None) -> None:
    """The chunks of one section must tile it exactly, or databins would not cover it."""
    geometry = _geometry(geometry=geometry)
    mine = sorted((c for c in chunks if c.get("section") == section),
                  key=lambda c: c["offset"])
    if not mine:
        raise ConfigError(f"debug_chunks.json has no {section} chunks")
    cursor = 0
    for chunk in mine:
        if chunk["offset"] != cursor:
            raise ConfigError(
                f"debug_chunks.json {section} chunks do not tile the section: expected "
                f"0x{cursor:X}, found 0x{chunk['offset']:X}")
        cursor += chunk["size"]
    if cursor != size:
        raise ConfigError(
            f"debug_chunks.json {section} chunks cover 0x{cursor:X} bytes, but the "
            f"section is 0x{size:X} bytes")
    if offset + size > geometry.elf_size:
        raise ConfigError(f"section {section} runs past the end of the ELF")


# ---------------------------------------------------------------------------
# splat.yaml
# ---------------------------------------------------------------------------


def databin_segments(chunks, geometry=None):
    """Every non-code segment, in file order: ``(name, file offset, size)``.

    The yaml's segment list, the pinned link's tail edge and the tail's byte order all
    read this one list, so a byte can never be covered twice by one of them or left out
    by another.  ``elf_header`` comes first (file offset 0); everything after it starts
    where the loadable image ends and runs to the end of the file.
    """
    geometry = _geometry(geometry=geometry)
    segments = [("elf_header", 0, geometry.loadable_rom)]
    cursor = geometry.loadable_end
    previous = geometry.code_segment
    for name, offset, size in geometry.trailing:
        if offset > cursor:
            segments.append((f"pad_{previous}", cursor, offset - cursor))
        if name in CHUNKED:
            for index, chunk in enumerate(
                    sorted((c for c in chunks if c["section"] == f".{name}"),
                           key=lambda c: c["offset"])):
                segments.append((f".{name}_{index:03d}",
                                 offset + chunk["offset"], chunk["size"]))
        else:
            segments.append((name, offset, size))
        cursor = offset + size
        previous = name
    return segments


def splat_yaml(chunks, target=None, geometry=None) -> str:
    target = target or TARGET
    geometry = geometry or target.geometry_required()
    elf = target.elf.name
    lines = [YAML_HEADER.format(target=target.name, elf=f"orig/{elf}")]
    lines.append("options:\n")
    lines.append(f"  basename: {elf}\n")
    lines.append("  base_path: ../..\n")
    lines.append(f"  target_path: orig/{elf}\n")
    lines.append("  platform: ps2\n")
    lines.append("  compiler: EEGCC\n")
    lines.append("  asm_path: asm\n")
    # The generated INCLUDE_ASM TU is a build artefact: it lives under build/ so that
    # `src/` keeps meaning "hand-written C for a promoted translation unit".
    lines.append("  src_path: build/src\n")
    lines.append("  build_path: build\n")
    lines.append("  asset_path: build/assets\n")
    lines.append(f"  ld_script_path: {_display(target.ld_script)}\n")
    lines.append("  ld_rom_start: 0\n")
    lines.append('  section_order: [".text", ".rodata", ".data", ".bss"]\n')
    lines.append('  auto_link_sections: [".rodata", ".data", ".bss"]\n')
    lines.append("  subalign: 1\n")
    lines.append("  create_c_files: true\n")
    # Dropped trailing nops would still have to come from somewhere: the splits are the
    # link input, so every byte of every function stays in its split.
    lines.append("  detect_redundant_function_end: false\n")
    # `-mabi=eabi` (which the retail ELF's e_flags demand) renumbers $t0..$t3 to
    # registers 12-15 and knows no $t4..$t7, so an o32-spelled split would encode the
    # wrong registers.  Numeric names assemble the same under either ABI (R21).
    lines.append("  named_regs_for_c_funcs: false\n")
    lines.append("  create_undefined_funcs_auto: true\n")
    lines.append(f"  undefined_funcs_auto_path: {_config_path(target, target.undefined_funcs)}\n")
    lines.append("  create_undefined_syms_auto: true\n")
    lines.append(f"  undefined_syms_auto_path: {_config_path(target, target.undefined_syms)}\n")
    lines.append(f"  symbol_addrs_path: {_config_path(target, target.splat_symbols)}\n")
    lines.append("  generate_asm_macros_files: true\n")
    lines.append("  generated_asm_macros_directory: asm/include\n")
    # The splits must assemble to the retail bytes, so the assembler is told not to
    # touch $at and not to fill delay slots itself; splat already encodes every nop.
    lines.append("  asm_inc_header: \".include \\\"macro.inc\\\"\\n.set noat\\n.set noreorder\\n\"\n")
    # splat writes C-segment splits with the R5900 special registers spelled bare
    # (`ACC`, `Q`, `I`); GNU as names them `$ACC`, `$Q`, `$I`.  The aliases live in the
    # generated macro.inc, so no split is ever edited by hand (R21).
    lines.append("  generated_macro_inc_content: |\n")
    for alias in ("ACC", "Q", "I"):
        lines.append(f"    .set {alias}, ${alias}\n")

    lines.append("segments:\n")
    segments = databin_segments(chunks, geometry)
    lines.append(f"  - [0x{segments[0][1]:X}, databin, {segments[0][0]}]\n")
    lines.append(f"  - name: {geometry.code_segment}\n")
    lines.append("    type: code\n")
    lines.append(f"    start: 0x{geometry.loadable_rom:X}\n")
    lines.append(f"    vram: 0x{geometry.loadable_vram:X}\n")
    lines.append("    subsegments:\n")
    # One `c` subsegment covers the whole loadable image: the retail ELF keeps text,
    # rodata and data in a single PT_LOAD section, so there is no section boundary to
    # copy -- per-function splits come from the symbol file instead.
    lines.append(f"      - [0x{geometry.loadable_rom:X}, c, {geometry.code_segment}]\n")
    for name, offset, _ in segments[1:]:
        lines.append(f"      - [0x{offset:X}, databin, {name}]\n")
    # The loadable PT_LOAD's memsz reaches past the file-loaded end: everything above it is
    # zero-fill at run time, and the compiler's globals and the DWARF objects live there.
    # Without this segment splat cannot place them, and the splits that name them (g_game_w
    # in 131 of them) reference symbols nothing defines.
    lines.append("  - name: bss\n")
    lines.append("    type: bss\n")
    lines.append(f"    vram: 0x{geometry.bss_vram:X}\n")
    lines.append(f"    bss_size: 0x{geometry.bss_size:X}\n")
    lines.append(f"  - [0x{geometry.elf_size:X}]\n")
    return "".join(lines)


# ---------------------------------------------------------------------------
# overlay splits: one splat run per blob, keyed by module name
# ---------------------------------------------------------------------------

OVERLAY_YAML_HEADER = """\
# Generated by configure.py --target {target} -- do not edit by hand.
#
# One overlay blob's splat run.  The module is named, never addressed: seven of this
# target's ten modules load at 0x7F0000, so an address does not name a blob.  The bytes are
# the ones the pinned disc image carries at 0x{image_offset:X}.
#
# Only the code is split.  The blob's 0x40-byte header and its data section are not: an
# overlay unit's splits are what its promoted object replaces, and the header and data are
# never rewritten (the image keeps retail's bytes).
"""


def overlay_splat_yaml(overlay, target=None) -> str:
    """The yaml for one overlay module's splat run: its code window, cut out of its blob.

    The segment starts at the blob's own header (``OVERLAY_HEADER`` bytes) and its vram at the
    window's base, so splat's split comments carry the *absolute* virtual addresses the DWARF
    records -- which is what ``compile.split_extent`` matches a unit's functions against.  The
    options that shape a split are the main run's, because a split is the text that run would
    write for the same bytes.
    """
    target = target or TARGET
    lines = [OVERLAY_YAML_HEADER.format(target=target.name,
                                        image_offset=overlay.image_offset)]
    lines.append("options:\n")
    lines.append(f"  basename: {overlay.name}\n")
    lines.append("  base_path: ../../..\n")
    lines.append(f"  target_path: {_display(target.overlay_blob(overlay.name))}\n")
    lines.append("  platform: ps2\n")
    lines.append("  compiler: EEGCC\n")
    lines.append("  asm_path: asm\n")
    lines.append(f"  src_path: {_display(target.overlay_workdir(overlay.name) / 'src')}\n")
    lines.append(f"  build_path: {_display(target.overlay_workdir(overlay.name) / 'splat')}\n")
    lines.append(f"  asset_path: {_display(target.overlay_workdir(overlay.name) / 'assets')}\n")
    # splat writes a linker script of its own for every run; this one is never linked (the
    # pinned script `overlay_link_script` writes is), so it is kept beside the run's output.
    lines.append(f"  ld_script_path: "
                 f"{_display(target.overlay_workdir(overlay.name) / 'splat.ld')}\n")
    lines.append("  ld_rom_start: 0\n")
    lines.append('  section_order: [".text"]\n')
    lines.append('  auto_link_sections: []\n')
    lines.append("  subalign: 1\n")
    # The C file is what makes splat emit the asm splits at all (`is_new_c_file`), and it
    # never overwrites an existing one; `run_overlay_splat` removes it first, so a run always
    # rewrites every split.  `do_c_func_detection` is off for the same reason: reading names
    # out of a stale artifact would silently suppress a split.
    lines.append("  create_c_files: true\n")
    lines.append("  do_c_func_detection: false\n")
    lines.append("  detect_redundant_function_end: false\n")
    lines.append("  named_regs_for_c_funcs: false\n")
    # The undefined ledger belongs to the main link; an overlay run resolves nothing, so it
    # must not write those files.
    lines.append("  create_undefined_funcs_auto: false\n")
    lines.append("  create_undefined_syms_auto: false\n")
    lines.append(f"  symbol_addrs_path: "
                 f"{_display(target.overlay_workdir(overlay.name) / 'symbol_addrs.txt')}\n")
    # `asm/include/macro.inc` is the main run's; a split includes it, and the overlay run
    # must not rewrite it.
    lines.append("  generate_asm_macros_files: false\n")
    lines.append("  asm_inc_header: \".include \\\"macro.inc\\\"\\n.set noat\\n.set noreorder\\n\"\n")
    lines.append("segments:\n")
    lines.append(f"  - name: {overlay.name}\n")
    lines.append("    type: code\n")
    # The segment *is* the code: it starts at the blob's first code byte (the 0x40-byte
    # header is not split) and loads at that byte's address, so every split's comment carries
    # the absolute VA the DWARF records.
    lines.append(f"    start: 0x{targets.OVERLAY_HEADER:X}\n")
    lines.append(f"    vram: 0x{overlay.code_vram:X}\n")
    lines.append("    subsegments:\n")
    lines.append(f"      - [0x{targets.OVERLAY_HEADER:X}, c, {overlay.name}]\n")
    lines.append(f"  - [0x{overlay.filesize:X}]\n")
    return "".join(lines)


def overlay_symbols_text(target, overlay) -> str:
    """The module's own ``symbol_addrs``, in the syntax splat parses.

    The oracle withholds an overlay record from the placed ledger -- seven modules share one
    base, so an address alone would name the wrong module's function -- and writes it to
    ``unplaced_symbols.txt`` with the module it belongs to.  That file is the only place a
    module's names exist, so it is what this reads.  Only the code window is kept: the run
    splits the code, and splat refuses a symbol no segment contains.
    """
    records = []
    text = target.unplaced.read_text() if target.unplaced.is_file() else ""
    for line in text.splitlines():
        match = SYMBOL_LINE.match(line.strip())
        if match is None:
            continue
        attrs = match["attrs"]
        module = OVERLAY_ATTR.search(attrs)
        if module is None or module.group(1) != overlay.name:
            continue
        address = int(match["address"], 16)
        if not overlay.code_vram <= address < overlay.code_end_vram:
            continue
        kind = "func" if "type:func" in attrs else "label"
        size = re.search(r"\bsize:(0x[0-9A-Fa-f]+)", attrs)
        trailer = f" // type:{kind}"
        if size is not None and int(size.group(1), 16):
            trailer += f" size:{size.group(1)}"
        records.append((address, match["name"], trailer))
    records.sort()
    return (f"// Generated by configure.py from {_display(target.unplaced)} -- do not edit.\n"
            f"// The records that name overlay {overlay.name}, at the virtual addresses they "
            f"load at.\n"
            + "".join(f"{name} = 0x{address:08X};{trailer}\n"
                      for address, name, trailer in records))


def overlay_blob(target, overlay) -> bytes:
    """The module's bytes as the pinned disc image carries them, header included."""
    with Retail(target).opened() as retail:
        return retail.code(overlay.vaddr, overlay.filesize, overlay)


def overlay_modules(promotions, geometry) -> list:
    """The overlays that have a promoted unit, in the geometry's own order.

    A module with no promotion has nothing to link, so no splat run is spent on it.
    """
    wanted = {promotion.module for promotion in promotions if promotion.is_overlay}
    return [overlay for overlay in geometry.overlays if overlay.name in wanted]


def run_overlay_splat(overlay, target) -> None:
    """Cut the blob out of the image, write the run's inputs, and split the module.

    Everything splat reads is generated under ``build/overlays/<name>/`` and the splits land
    under ``asm/nonmatchings/<name>/`` -- the directory ``compile.split_extent`` looks for,
    keyed by the module's name.
    """
    directory = target.overlay_workdir(overlay.name)
    directory.mkdir(parents=True, exist_ok=True)
    blob = target.overlay_blob(overlay.name)
    write_bytes_if_different(blob, overlay_blob(target, overlay))
    write_if_different(directory / "symbol_addrs.txt", overlay_symbols_text(target, overlay))
    yaml_path = directory / "splat.yaml"
    write_if_different(yaml_path, overlay_splat_yaml(overlay, target))
    # splat emits a module's asm splits only when it creates the C file for the run, and it
    # never overwrites one that exists: dropping the artifact makes the run a full rewrite.
    # splat writes `src/<module>.c`, not `src/<module>/<module>.c`: the nested path made the
    # removal a no-op, so a second run in a tree kept the stale C and produced no splits.
    generated_c = directory / "src" / f"{overlay.name}.c"
    if generated_c.exists():
        generated_c.unlink()
    print(f"configure: splat split {_display(yaml_path)}")
    splat = [*SPLAT, _display(yaml_path)]
    proc = subprocess.run(splat, cwd=REPO_ROOT)
    if proc.returncode != 0:
        raise ConfigError(
            f"`{' '.join(splat)}` failed with exit {proc.returncode}; its output above "
            f"names the problem")
    splits = sorted((REPO_ROOT / "asm" / "nonmatchings" / overlay.name).glob("*.s"))
    if not splits:
        raise ConfigError(f"splat produced no splits under "
                          f"asm/nonmatchings/{overlay.name}/")


# ---------------------------------------------------------------------------
# splat symbol file
# ---------------------------------------------------------------------------

SYMBOL_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<address>0x[0-9A-Fa-f]+);\s*//\s*(?P<attrs>.*)$")
#: ``unplaced_symbols.txt``'s module field: the only place an overlay record names its blob.
OVERLAY_ATTR = re.compile(r"\boverlay:(\S+)")
# splat's own undefined_*.txt are linker scripts: a bare assignment, no comment.
SYMBOL_ASSIGN = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+);")
# splat 0.50.1 knows exactly these symbol types; the oracle's `obj` means "a named
# address with no known size here", which is splat's `label`.
SPLAT_TYPES = {"func": "func", "obj": "label"}


def case_collisions(records) -> set:
    """The symbol names whose split *paths* one case-insensitive filesystem cannot tell apart.

    splat names a split file after its symbol (``Symbol.filename``), and this checkout is
    macOS: two symbols whose names differ only in case write to one path, the second write
    replaces the first, and the bytes the replaced split owned are in no split at all.  This
    target has exactly one such pair -- ``Tr_load_seq_th`` (0x0027FC90, 0x68 B) and
    ``tr_load_seq_th`` (0x0027FD00, 0x1F0 B) -- and the link came up 0x70 bytes short of the
    retail image's 1,958,272 because of it, which is how it was found.  Both halves of a
    collision are returned, so neither of the two is the arbitrary winner.
    """
    spellings = {}
    for name, _address in records:
        spellings.setdefault(name.lower(), set()).add(name)
    return {name for group in spellings.values() if len(group) > 1 for name in group}


def splat_symbols(text: str, target=None) -> str:
    """Rewrite the oracle's symbol file into the syntax splat parses.

    Three measurements drive this.  splat reads every `key:value` in the trailing comment
    as an attribute and rejects unknown ones (`provenance:ghidra` is read as a boolean),
    so the oracle's provenance fields are rewritten colon-free; a function symbol
    carrying `size:0x0` suppresses spimdisasm's function detection outright, so zero
    sizes are dropped while the DWARF sizes that are known are kept; and a name two
    symbols share up to case gets a `filename:`, because splat derives each split's path
    from its symbol and one filesystem cannot hold both spellings (see
    :func:`case_collisions`).  Only the path is disambiguated -- the symbol name, and so
    the label inside the split, stays the DWARF's own.
    """
    target = target or TARGET
    records = []
    for number, line in enumerate(text.splitlines(), start=1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        match = SYMBOL_LINE.match(line.strip())
        if match is None:
            raise ConfigError(
                f"symbol_addrs.txt line {number} is not `name = 0xADDR; // attrs`: {line}")
        records.append((match["name"], match["address"], match["attrs"]))
    colliding = case_collisions([(name, address) for name, address, _ in records])
    out = [f"// Generated by configure.py from {_display(target.symbols)} -- do not edit.",
           "// splat 0.50.1 syntax: unknown attributes are booleans, so provenance and",
           "// dwarf_name carry `=` instead of `:`, and zero sizes are omitted."]
    for name, address, attr_text in records:
        attrs = []
        for attr in attr_text.split():
            key, _, value = attr.partition(":")
            if not _:
                continue
            if key == "type":
                attrs.append(f"type:{SPLAT_TYPES.get(value, value)}")
            elif key == "size":
                if int(value, 16) != 0:
                    attrs.append(attr)
            else:
                attrs.append(f"{key}={value}")
        if name in colliding:
            # The address is what makes the two paths distinct, spelled as splat does for
            # the symbols it names itself (`func_00100000`).
            attrs.append(f"filename:{name}_{address[2:]}")
        out.append(f"{name} = {address};" + (f" // {' '.join(attrs)}" if attrs else ""))
    return "\n".join(out) + "\n"


# ---------------------------------------------------------------------------
# the pinned link
# ---------------------------------------------------------------------------


def split_sources(skip=()) -> dict:
    """Every generated split's text, keyed by its repo-relative path.

    splat's output is read once: the link needs each code split's address and every
    split's labels and symbol references, and reading 4,092 files twice is silly.

    ``skip`` names segments whose splits are *not* the main image's -- an overlay module's
    run writes into ``asm/nonmatchings/<module>/``, and those addresses belong to a blob's
    window, so the main link's aliases and data pieces must never see them.
    """
    prefixes = tuple(f"asm/nonmatchings/{name}/" for name in skip)
    sources = {}
    for path in sorted((REPO_ROOT / "asm").rglob("*.s")):
        relative = path.relative_to(REPO_ROOT).as_posix()
        if prefixes and relative.startswith(prefixes):
            continue
        sources[relative] = path.read_text()
    if not sources:
        raise ConfigError("splat produced no splits under asm/")
    return sources


def code_splits(sources, geometry=None):
    """``[(retail address, split path)]`` for the code splits, in address order.

    The address comes from the split's own first instruction comment and is checked
    against the loadable segment's geometry (file offset ``loadable_rom + VA -
    loadable_vram``) -- the same invariant :func:`splat_yaml` writes into the yaml.
    Nothing else in the build knows where a split belongs, so a split that cannot be
    placed is an error here rather than a silent hole in the image.
    """
    geometry = _geometry(geometry=geometry)
    prefix = f"asm/nonmatchings/{geometry.code_segment}/"
    rows = []
    for name, text in sources.items():
        if not name.startswith(prefix):
            continue
        match = SPLIT_COMMENT.search(text)
        if match is None:
            raise ConfigError(f"{name} carries no address comment; splat's split format "
                              f"is not the one this linker script expects")
        file_offset, address = int(match.group(1), 16), int(match.group(2), 16)
        expected = geometry.offset_of(address)
        if file_offset != expected:
            raise ConfigError(
                f"{name} says VA 0x{address:X} is at file offset 0x{file_offset:X}, but "
                f"the loadable segment puts it at 0x{expected:X}")
        rows.append((address, name))
    if not rows:
        raise ConfigError(f"splat produced no code splits under {prefix}")
    rows.sort()
    if rows[0][0] != geometry.loadable_vram:
        raise ConfigError(f"the first code split is at 0x{rows[0][0]:X}, not the segment's "
                          f"start 0x{geometry.loadable_vram:X}")
    if len(set(a for a, _ in rows)) != len(rows):
        raise ConfigError("two splits claim the same address; the link order is ambiguous")
    return rows


#: A split line that defines a label (the macro splat emits: `dlabel`/`alabel`/...).
SPLIT_LABEL_LINE = re.compile(r"^\s*(?:glabel|alabel|ehlabel|jlabel|dlabel)\s+(\S+)")
#: The line that closes a label's extent; it computes ``. - NAME`` and so needs NAME local.
SPLIT_END_LABEL_LINE = re.compile(r"^\s*end(?:d|g|a|eh|j)label\s+(\S+)")


def data_placements(target=None):
    """The target's address-driven data ledger (see `toolchain.compile.data_placements`)."""
    try:
        return cc.data_placements(target or TARGET)
    except cc.Unusable as exc:
        raise ConfigError(str(exc)) from exc


def placement_inputs(placements, built_from):
    """``[(address, object, section)]``: the link inputs a placement ledger asks for.

    A promoted unit is one object whose placed data symbols each own a section
    (``compile.data_section``), so the section is named per record: selecting ``.data`` would
    drag every other placed datum of the same unit along with it.  A data-only unit is
    compiled raw and has exactly the one ``.data`` section its single datum occupies.
    """
    return [(record["address"],
             built_from.get(record["source"], f"build/{record['source']}.o"),
             cc.data_section(record["name"]) if record["source"] in built_from else ".data")
            for record in placements]


def placements_by_module(placements, promotions, geometry):
    """Partition the data ledger by the link that owns each record.

    A record is linked wherever its *bytes* are, and the geometry says where that is: an
    address in the file-backed image is main's, an address in an overlay window is that
    module's.  The two links are not interchangeable -- the main script asserts ``.main`` to
    the file-backed image's exact size, and the overlay reservation in it is zero-fill, so an
    overlay datum listed there has nowhere to go (and a main datum listed in a module's link
    would be placed at a negative offset into a blob that does not hold it).

    The ``source`` resolves *which* module when several windows share one base (seven of this
    target's ten load at 0x7F0000): the promoted unit's own module has to be one of the
    windows that holds the address.  A record in no window and in no loadable image is
    refused, and so is one whose source is an overlay unit of a module whose window does not
    contain it.

    Note that "source is an overlay unit" does not by itself mean "belongs to the module":
    `opt_doll.c`'s and `infodoll.c`'s `crect` are initialised data in the *main* image
    (0x002DDEE8, 0x002DDE60) and the main link places them today; the address is what
    decides, because the address is where retail's bytes are.

    Returns ``(main, {module: [(promotion, record), ...]})``.  Every module-owned record is
    checked against the window it now has to fit: inside the module's data (not its code),
    and its whole retail extent -- the bytes plus the zero fill retail shows after them --
    inside the blob's initialised data.  Extents of one module must not overlap, which is
    the ledger's own invariant for the main image too.
    """
    module_of = {promotion.file: promotion for promotion in promotions}
    main, owned = [], {}
    for record in placements:
        begin, end = record["address"], record["address"] + record["extent"]
        promotion = module_of.get(record["source"])
        windows = geometry.overlays_at(begin)
        if not windows:
            if not (geometry.loadable_vram <= begin and end <= geometry.bss_vram):
                raise ConfigError(
                    f"{record['name']} ({record['source']}) spans 0x{begin:X}..0x{end:X}, "
                    f"which is neither in the loadable image "
                    f"(0x{geometry.loadable_vram:X}..0x{geometry.bss_vram:X}) nor in any "
                    f"overlay window this target's geometry records: nothing holds its bytes")
            main.append(record)
            continue
        overlay = next((window for window in windows
                        if promotion is not None and window.name == promotion.module), None)
        if overlay is None:
            names = ", ".join(window.name for window in windows)
            where = (f"{promotion.file}'s module is {promotion.module}"
                     if promotion is not None and promotion.is_overlay
                     else "its source is no promoted unit of an overlay module")
            raise ConfigError(
                f"{record['name']} ({record['source']}) is at 0x{begin:X}, inside overlay "
                f"{names}, but {where}: the address names the blob the datum's bytes are in, "
                f"and only that module's link can place them")
        data_end = overlay.vaddr + overlay.filesize
        if begin < overlay.data_vram:
            raise ConfigError(
                f"{record['name']} ({record['source']}) is at 0x{begin:X}, inside "
                f"{overlay.name}'s code (0x{overlay.code_vram:X}..0x{overlay.data_vram:X}); a "
                f"datum has to lie in the module's data, which is where its bytes are")
        if end > data_end:
            raise ConfigError(
                f"{record['name']} ({record['source']}) spans 0x{begin:X}..0x{end:X}, past "
                f"{overlay.name}'s data end 0x{data_end:X}: the module's link can only place "
                f"bytes the blob holds")
        owned.setdefault(overlay.name, []).append((promotion, record))
    for module, records in owned.items():
        records.sort(key=lambda item: item[1]["address"])
        for (_, before), (_, after) in zip(records, records[1:]):
            if before["address"] + before["extent"] > after["address"]:
                raise ConfigError(
                    f"{module}: {before['name']} at 0x{before['address']:X} claims "
                    f"{before['extent']:#x} bytes and overlaps {after['name']} at "
                    f"0x{after['address']:X}; two placements cannot own one address")
    return main, owned


def cut_split(name, text, start, cuts):
    """Split one split's assembler text around the byte ranges a placement owns.

    Returns ``([(piece address, text)], [(removed label, address)])``.  The cut happens on
    word boundaries, which is where splat writes every data line; a continuation piece gets
    the original preamble (`.include`/`.set`/`.align`) again, and every label inside a cut
    is reported so the linker script can keep defining it as an absolute symbol.  A cut that
    does not land on an emitted word is refused rather than approximated.
    """
    lines = text.splitlines(keepends=True)
    entries = []                 # [(address, [lines])] -- the lines since the previous word
    pending = []
    for line in lines:
        match = SPLIT_COMMENT.search(line)
        if match is None:
            pending.append(line)
            continue
        entries.append((int(match.group(2), 16), pending + [line]))
        pending = []
    if pending:
        entries.append((None, pending))
    first_label = next((i for i, line in enumerate(lines) if SPLIT_LABEL_LINE.match(line)),
                       None)
    if first_label is None:
        raise ConfigError(f"{name}: a data placement cuts a split with no label to keep")
    preamble = [line for line in lines[:first_label]
                if not line.lstrip().startswith("nonmatching")]
    starts = {address for address, _ in entries if address is not None}
    for begin, end in cuts:
        for edge in (begin, end):
            if edge not in starts:
                raise ConfigError(
                    f"{name}: the data placement boundary 0x{edge:X} is not a word the split "
                    f"emits; the cut would move bytes")
    ranges, cursor = [], start
    for begin, end in cuts:
        ranges.append((cursor, begin))
        cursor = end
    ranges.append((cursor, None))
    pieces, removed = [], []
    for piece_start, piece_end in ranges:
        if piece_end is not None and piece_end <= piece_start:
            # Two placements that touch leave no bytes between them; an empty piece would
            # claim the same address as the second placement and make the link order
            # ambiguous.
            continue
        body = list(preamble) if piece_start != start else []
        for address, lineset in entries:
            if address is None:
                continue
            if address < piece_start or (piece_end is not None and address >= piece_end):
                continue
            body += lineset
        pieces.append((piece_start, "".join(body)))
    for begin, end in cuts:
        for address, lineset in entries:
            if address is None or not (begin <= address < end):
                continue
            for line in lineset:
                match = SPLIT_LABEL_LINE.match(line)
                if match:
                    removed.append((match.group(1), address))
    # A label whose extent straddles a cut has its ``dlabel`` in one piece and its
    # ``enddlabel`` in another, where ``. - NAME`` no longer evaluates (NAME is absolute
    # there), so the piece does not assemble.  Drop any end line whose label this piece does
    # not define; the label itself is still defined absolutely by the linker script.
    trimmed = []
    for address, body in pieces:
        lines_of = body.splitlines(keepends=True)
        defined = {match.group(1) for match in map(SPLIT_LABEL_LINE.match, lines_of)
                   if match is not None}
        trimmed.append((address, "".join(
            line for line in lines_of
            if not _ends_label_outside(line, defined))))
    return trimmed, removed


def _ends_label_outside(line, defined):
    """True for an ``enddlabel NAME`` line whose NAME this piece does not define."""
    match = SPLIT_END_LABEL_LINE.match(line)
    return match is not None and match.group(1) not in defined


def plan_data(sources, code, geometry, placements, replacements):
    """Emit the per-region pieces a data placement's split no longer supplies.

    ``replacements`` maps a split path to the pieces that replace it, in address order.  The
    returned ``(pieces, pads, aliases)`` are the files to assemble and the labels to keep
    defined; the caller adds the compiled datum's own object section at the same addresses.
    A pad piece is named from its datum *and* its ``source``: a literal-pool index is numbered
    per object, so two units of alike shape both place ``@40`` and their pads are two pieces.
    """
    rows = sorted(code)
    per_split = {}
    pads, aliases = [], []
    for record in placements:
        owners = [i for i, (address, _) in enumerate(rows) if address <= record["address"]]
        if not owners:
            raise ConfigError(f"{record['name']} at 0x{record['address']:X} precedes every "
                              f"split; no split carries it")
        index = owners[-1]
        split_address, split = rows[index]
        # The last split ends at ``bss_vram``, not ``loadable_end``: split addresses are VAs,
        # and the loadable end is a *file* offset (the tail databins sit between them), so the
        # old bound made the final code split unable to accept any placement.
        split_end = rows[index + 1][0] if index + 1 < len(rows) else geometry.bss_vram
        begin, end = record["address"], record["address"] + record["extent"]
        if not (split_address <= begin < end <= split_end):
            raise ConfigError(
                f"{record['name']} spans 0x{begin:X}..0x{end:X}, which crosses the split "
                f"{split} (0x{split_address:X}..0x{split_end:X}); a placement must be inside "
                f"one split")
        per_split.setdefault(split, []).append((begin, end))
        if record["extent"] > record["size"]:
            pads.append((begin + record["size"], record["name"], record["source"],
                         record["extent"] - record["size"]))
    pieces = []
    for split, cuts in per_split.items():
        cuts.sort()
        stem = pathlib.Path(split).relative_to("asm").with_suffix("")
        split_pieces, removed = cut_split(split, sources[split], rows_of(split, rows), cuts)
        replacements[split] = []
        for number, (address, text) in enumerate(split_pieces):
            path = REPO_ROOT / "build" / "generated" / stem.parent / \
                   f"{stem.name}.part{number}.s"
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, newline="\n")
            relative = path.relative_to(REPO_ROOT).as_posix()
            replacements[split].append((address, relative))
            pieces.append(relative)
        aliases += removed
    pad_pieces = []
    for address, name, source, size in pads:
        # The piece is named from the datum *and* the source it belongs to: a literal-pool
        # index is numbered per object, so two units of alike shape can both place `@40` at
        # their own address.  One name for both would be two ninja rules writing one file.
        token = cc.data_section(name).rsplit(".", 1)[-1] + "_" + \
            hashlib.sha1(source.encode()).hexdigest()[:8]
        path = REPO_ROOT / "build" / "generated" / "data" / f"{token}.pad.s"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("\t.text\n\t.space\t%d\n" % size, newline="\n")
        relative = path.relative_to(REPO_ROOT).as_posix()
        pad_pieces.append((address, relative))
    return pieces, pad_pieces, aliases


def rows_of(split, rows):
    """The retail address a split starts at."""
    for address, name in rows:
        if name == split:
            return address
    raise ConfigError(f"{split} is not a code split; a data placement names it")


def symbol_table(path) -> dict:
    """``name -> address`` from a splat symbol file (ours or splat's own auto files).

    splat's ``undefined_{syms,funcs}_auto.txt`` are bare ``name = 0xADDR;`` assignments
    (they are read by ld as a linker script), while ``symbol_addrs.txt`` carries a
    provenance comment, so this matches the assignment only.
    """
    table = {}
    for line in pathlib.Path(path).read_text().splitlines():
        match = SYMBOL_ASSIGN.match(line.strip())
        if match is not None:
            table[match.group(1)] = int(match.group(2), 16)
    return table


def link_aliases(sources, symbols_path, auto_paths):
    """``[(name, address)]`` of the names some split references and nothing defines.

    This is the one data-modelling gap M1 has left: the loadable image is a single ``c``
    segment with no rodata/data subsegments, so a split that reads a byte another split
    owns can name it differently from the owner's label -- ``D_0027EB50`` where the owner
    wrote ``D_0027EB52``, or ``.L00140378`` where the branch target's owner is the next
    split.  Every such name encodes its own address, so a linker-script assignment is
    unambiguous; G1, not inspection, is what proves the address is the retail one.

    Three cases, all measured, and the set is closed by construction:

    * ``.L`` names, which gas keeps *local to the object that defines them*: a cross-split
      reference to one stays undefined however the owner spells it, so any ``.L`` name two
      splits mention gets a definition (a ``.L`` name that only its owner mentions needs
      none -- gas resolves it internally).
    * names no split defines as a global label (``glabel``/``dlabel``/...);
    * symbols whose name is not address-shaped (``finger_pos_tbl``): those resolve through
      the oracle's symbol file, and only if a split mentions the name.

    Names splat already resolved into ``undefined_{syms,funcs}_auto.txt`` are left to it.
    """
    labels, owners, tokens = set(), {}, set()
    for name, text in sources.items():
        labels |= set(LABEL_DEF.findall(text))
        for token in ALIAS_TOKEN.findall(text):
            tokens.add(token)
            owners.setdefault(token, set()).add(name)
    symbols = symbol_table(symbols_path)
    resolved = set()
    for path in auto_paths:
        resolved |= set(symbol_table(path))

    aliases = {}
    for token in tokens:
        if token in resolved:
            continue
        if token.startswith(".L"):
            if len(owners[token]) > 1:
                aliases[token] = int(ALIAS_ADDRESS.match(token).group(1), 16)
        elif token not in labels:
            aliases[token] = int(ALIAS_ADDRESS.match(token).group(1), 16)
    identifiers = set(IDENTIFIER.findall("\n".join(sources.values())))
    for name, address in symbols.items():
        if name in identifiers and name not in labels and name not in resolved \
                and name not in aliases:
            aliases[name] = address
    return sorted(aliases.items(), key=lambda item: (item[1], item[0]))


# ---------------------------------------------------------------------------
# promoted translation units
# ---------------------------------------------------------------------------

#: How a promoted unit is built, per target: the key is the unit's source file exactly as
#: ``cus.json`` spells it (the retail tree's own path); the value is the compiler build and the
#: flag string ``tools/toolchain/select_build.py`` measured as reproducing its retail ``.text``,
#: ``.debug`` and ``.line`` bytes.  The table is the *target's* (``config/targets.py``): a pair
#: measured against one retail binary says nothing about another, so it is never inherited.
#: ``src/`` and the target's table must agree -- a source nobody has measured for *this* target,
#: or a table entry whose source is gone, is a configuration error rather than a silently
#: unchanged image.


class Promotion:
    """A unit built from C: its object, its payloads, and what it replaces in the image.

    A unit with code contributes ``.text`` from its object (the pinned ``ld`` script places
    it where the unit's splits used to be); a data-only unit has no code at all, so its
    object is placed by the data ledger instead and its empty ``.text`` is never listed.
    ``.debug``/``.line`` are dumped out of the object by the ``objsec`` edges and
    substituted for the retail databins of the chunks the unit owns; a data-only unit owns
    one ``.debug`` chunk and no ``.line`` chunk.  The split objects stay assembled: ``ddr
    diff`` reads one to stand in for a function that has no C, and an unpromoted unit's
    split is still its objdiff target.  A promoted unit's objdiff target is the object
    :func:`unit_targets` derives from the retail image, not the split -- a split's symbolic
    ``jal`` makes a byte-identical function score ~99.2% (see :mod:`diff.basis`).

    ``module`` is the unit's own answer to *where its code loads* -- ``main`` for the
    file-backed image, an overlay's stem for a blob -- because that decides which link places
    the object: the pinned main script (asserted to the file-backed image's exact size) or
    the module's own overlay link.
    """

    __slots__ = ("file", "address", "flags", "object", "debug_payload", "line_payload",
                 "debug_databin", "line_databins", "splits", "code", "module")

    def __init__(self, file, address, flags, object_path, debug_payload, line_payload,
                 debug_databin, line_databins, splits, code=True, module="main"):
        self.file = file                  # "src/sys/sys_scf.c"
        self.address = address            # the unit's first function's address, or -- a
                                          # data-only unit -- its first placed datum's
        self.flags = flags                # the cc rule's `flags` variable
        self.object = object_path         # repo-relative path of the cc edge's output
        self.debug_payload = debug_payload
        self.line_payload = line_payload
        self.debug_databin = debug_databin        # the databin it replaces
        self.line_databins = line_databins        # the run of databins it replaces
        self.splits = splits              # the split paths the ld script must not list
        self.code = code                  # whether the object carries the unit's .text
        self.module = module              # "main", or the overlay whose link places it

    @property
    def is_overlay(self) -> bool:
        """Whether the blob's link, not the main image's, places this object."""
        return self.module != "main"


def promotions(manifests=None, target=None) -> list:
    """Every promoted unit, in address order, with the layout the oracle pinned for it.

    ``cc`` reports an unusable manifest or an unplaceable unit as :class:`cc.Unusable`; a
    configuration failure the CLI names and exits 2 on, so it is translated here rather
    than escaping as a traceback.
    """
    try:
        return _promotions(manifests, target)
    except cc.Unusable as exc:
        raise ConfigError(str(exc)) from exc


def check_promoted_sources(target=None, root=None) -> None:
    """Refuse a ``tu_builds`` source the source-form rules forbid, before anything is written.

    Two rules live here, and both are about the file a reader sees rather than the bytes the
    compiler is handed:

    * no ``#line`` directive -- a directive renumbers what a reader sees, and the rewrite that
      removes it can move ``.line`` rows, so it is a promotion step the build never performs;
    * no cast literal -- ``AGENTS.md`` rule 3: a datum with no DWARF name is reached through a
      symbol, or through one file-scope ``#define D_<ADDR>``, never by ``(struct _T *)0x...``
      at the use site (:mod:`units.address_casts`).

    This runs first in :func:`configure`, while ``build.ninja`` is still the previous file: a
    source that breaks a rule stops the run instead of producing a graph that hides the
    problem.  ``compile.py`` refuses the same source at the ``cc`` edge, so even a stale graph
    cannot build it.  Each refusal names the file, the count and the remedy.

    ``root`` is the tree the ``tu_builds`` paths are relative to; it is a parameter only so a
    test can point the same rule at a synthetic tree.
    """
    target = target or TARGET
    root = pathlib.Path(root) if root is not None else REPO_ROOT
    for file in sorted(target.build_table()):
        path = root / file
        if not path.is_file():
            continue        # a missing source is promotions()' error, and it names it there
        text = path.read_bytes().decode("latin-1")
        try:
            cc.refuse_line_directives(file, text)
            cc.refuse_cast_literals(file, text)
        except cc.Unusable as exc:
            raise ConfigError(str(exc)) from exc


def promotion_command(version: str, flags: str) -> str:
    """The ``compile.py`` arguments for one measured pair.

    Every promoted unit is adopted: ``--adopt-retail-meta`` reconstructs ``.line``/``.debug``
    from retail's inventory and proves the whole ``.debug`` chunk is retail's bytes, with
    ``.text`` byte equality as the precondition.  There is no other promotion step to name.
    """
    return f"--compiler {version} {flags} --adopt-retail-meta"


def _promotions(manifests=None, target=None) -> list:
    target = target or TARGET
    manifests = manifests or cc.Manifests(target)
    builds = target.build_table()
    present = {file for file in manifests.tu_files() if (REPO_ROOT / file).is_file()}
    if present - set(builds):
        raise ConfigError(
            f"these translation units have a source under src/ but no build measured for "
            f"target {target.name}: " + ", ".join(sorted(present - set(builds)))
            + "; run python3 tools/toolchain/select_build.py --tu <file> and record the "
              "pair in that target's descriptor")
    if set(builds) - present:
        raise ConfigError(
            f"target {target.name} lists promoted units with no source under src/: "
            + ", ".join(sorted(set(builds) - present)))
    out = []
    for file, (version, flags) in sorted(builds.items()):
        tu = manifests.tu_named(file)
        command = promotion_command(version, flags)
        out.append(Promotion(
            file, tu.address, command,
            f"build/{file}.o", f"build/{file}.o.debug", f"build/{file}.o.line",
            f".debug_{manifests.debug_chunk_index(tu):03d}",
            [f".line_{index:03d}" for index in manifests.line_chunk_indices(tu)],
            # The unit's splits are its *own* module's run: an overlay unit's are under
            # `asm/nonmatchings/<overlay>/`, which only that module's splat run writes.
            {f"asm/nonmatchings/{tu.split_directory}/{function.name}.s"
             for function in tu.functions},
            code=bool(tu.functions), module=tu.overlay))
    return sorted(out, key=lambda promotion: (promotion.address, promotion.file))


def tail_inputs(databins, promotions) -> list:
    """The file's tail in file order: splat's databins, with a promoted unit's own
    ``.debug``/``.line`` payload substituted for the databins of the chunks it owns.

    Substitution is by *name*, so the tail's length in bytes is whatever the compiler
    wrote: a payload that is not the pinned size shifts every later byte and G1 localises
    it -- which is the honest failure, not a silently padded chunk.
    """
    runs = {}
    for promotion in promotions:
        for payload, names in ((promotion.debug_payload, [promotion.debug_databin]),
                               (promotion.line_payload, promotion.line_databins)):
            for name in names:
                runs[name] = (names[0], payload)
    out = []
    for name, _, _ in databins[1:]:
        first, payload = runs.get(name, (None, None))
        if first is None:
            out.append(f"build/assets/{name}.databin.bin")
        elif name == first:
            out.append(payload)
    return out


LD_HEADER = """\
/* Generated by configure.py --target {target} -- do not edit by hand.
 *
 * The pinned link: every byte of {elf} at the address it sits at in the
 * retail file.  ld places an output section's LMA (AT) at its file offset and objcopy -O
 * binary writes sections out at their LMAs, so `.elf_header` covers file 0..0x{rom:X} and
 * `.{segment}` covers 0x{rom:X}..0x{end:X} with no gap between them and no filler anywhere.
 *
 * `.{segment}` is the whole loadable image: every code split listed in address order, with
 * SUBALIGN(1) so gas's per-object 16-byte .text alignment cannot pad one split away from
 * the next.  Their virtual addresses are the retail ones, so `jal` and `%hi`/`%lo`
 * resolve to the addresses the retail instructions encode.  `.bss` is NOLOAD at
 * 0x{bss:X}: the DWARF objects above the file-loaded end need their retail addresses,
 * and no byte of them reaches the file.
 *
 * The file's tail (`.shstrtab`, `.debug`, `.line`, `.comment`, `.reginfo` and the section
 * header table) is not loaded by the retail ELF and so is not linked here at all: it is
 * assembled from splat's databins by the ninja `cat` edges (see configure.py).
 */
"""


def pinned_ld_script(code, aliases, promotions=(), target=None, geometry=None,
                     replacements=None, data=(), pads=()) -> str:
    """The linker script that pins the loadable image to the retail file's addresses.

    A promoted unit contributes one object where its splits used to be, at the address its
    first function sits at; every other split is listed exactly as before, so the object
    order still *is* the layout.  A data-only unit has no code to contribute, so its object
    is not listed here: its datum reaches the link through ``data``.

    ``replacements`` carries a split whose bytes a data placement owns: ``{split: [(address,
    piece path)]}``, the split's remaining text as per-region pieces in address order.
    ``data`` is ``[(address, object, section)]`` for the compiled datum placed at its retail
    address, and ``pads`` ``[(address, piece path)]`` for the zero fill retail shows to the
    recorded extent.  Every entry is listed by address, so the script still *is* the layout.

    Every placement here is a *main-image* one: a datum a promoted unit of an overlay module
    defines belongs to that module's own link (`overlay_link_script`), and `configure` hands
    this script only the ledger's main half (`placements_by_module`).  `.main` is asserted to
    the file-backed image's exact size, so an overlay datum listed here has nowhere to go.
    """
    replacements = replacements or {}
    data = list(data)
    pads = list(pads)
    target = target or TARGET
    geometry = geometry or target.geometry_required()
    lines = [LD_HEADER.format(target=target.name, elf=f"orig/{target.elf.name}",
                              rom=geometry.loadable_rom, end=geometry.loadable_end,
                              segment=geometry.code_segment, bss=geometry.bss_vram)]
    if aliases:
        lines.append("/* Names some splits reference and no split defines; each one's\n"
                     " * name encodes the retail address it must resolve to. */\n")
        for name, address in aliases:
            lines.append(f"{name} = 0x{address:X};\n")
        lines.append("\n")
    lines.append("SECTIONS\n{\n")
    lines.append("  .elf_header 0x0 : AT(0x0) SUBALIGN(1)\n  {\n"
                 "    build/asm/data/elf_header.s.o(.data)\n  }\n")
    # GNU ld 2.47 accepts ASSERT only without a trailing semicolon.
    lines.append(f"  ASSERT(SIZEOF(.elf_header) == 0x{geometry.loadable_rom:X}, "
                 f"\"elf_header is not the retail ELF header\")\n\n")
    lines.append(f"  .{geometry.code_segment} 0x{geometry.loadable_vram:X} : "
                 f"AT(0x{geometry.loadable_rom:X}) SUBALIGN(1)\n  {{\n")
    promoted = {name for promotion in promotions if not promotion.is_overlay
                for name in promotion.splits}
    listed = []
    for address, name in code:
        if name in promoted:
            continue
        if name in replacements:
            listed += [(piece_address, piece_object(piece), ".text")
                       for piece_address, piece in replacements[name]]
        else:
            listed.append((address,
                           object_path(REPO_ROOT / name).relative_to(REPO_ROOT).as_posix(),
                           ".text"))
    # An overlay unit's object is placed by its module's own link (`overlay_link_script`).
    # `.main` is asserted to the file-backed image's exact size, so an overlay address has
    # nowhere to go here -- and the file's bytes must stay retail's.
    listed += [(promotion.address, promotion.object, ".text") for promotion in promotions
               if promotion.code and not promotion.is_overlay]
    listed += [(address, name, section) for address, name, section in data]
    listed += [(address, piece_object(piece), ".text") for address, piece in pads]
    listed.sort()
    if len({address for address, _, _ in listed}) != len(listed):
        raise ConfigError("two inputs claim the same address; the link order is ambiguous")
    for _, name, section in listed:
        lines.append(f"    {name}({section})\n")
    lines.append("  }\n")
    lines.append(f"  ASSERT(SIZEOF(.{geometry.code_segment}) == 0x{geometry.code_size:X}, "
                 f"\"the code splits are not the retail {geometry.code_size:,} bytes\")\n\n")
    lines.append(f"  .bss 0x{geometry.bss_vram:X} (NOLOAD) : SUBALIGN(1)\n  {{\n"
                 f"    build/asm/data/bss.bss.s.o(.bss)\n  }}\n")
    lines.append(f"  ASSERT(SIZEOF(.bss) == 0x{geometry.bss_size:X}, "
                 f"\"the bss split is not the retail {geometry.bss_size:,} bytes\")\n\n")
    lines.append("  /DISCARD/ : { *(*) }\n}\n")
    return "".join(lines)


OVERLAY_LD_HEADER = """\
/* Generated by configure.py --target {target} -- do not edit by hand.
 *
 * One overlay blob's link: every promoted unit of module {module}, in address order, each
 * pinned to the virtual address its code sits at inside the window
 * 0x{vaddr:08X}..0x{end:08X} (code ends at 0x{code_end:08X}), and each asserted to fill
 * exactly the extent of the splits it replaces.  The same units' placed data follows, at the
 * addresses the data ledger records -- a datum a module's own object defines belongs to this
 * link, not to the main image's, whose zero-fill reservation maps no bytes there.
 *
 * This link is NOT the image.  The blob's bytes live in the disc image at 0x{image_offset:X}
 * (the DATA*.BIN the module loads from), the build never rewrites them, and out/{elf} is
 * assembled only from the retail ELF's own two halves -- so nothing placed here can move a
 * byte G1 compares.  What it is for: a promoted object is *linked*, at the address the
 * module loads at, inside a window whose bounds the link itself checks; and its bytes are
 * what `verify --tu` reads as the built side of an overlay unit's .text.
 */
"""


def overlay_section(promotion) -> str:
    """The output section one promoted unit gets in its module's link.

    Named from the unit's file stem: a section is what the script selects, so the name has to
    be unique inside the module.  Two promoted sources of one module sharing a stem would be
    two sections of one name, so that is refused where the script is written.
    """
    return f"ovl_{promotion.module}_{pathlib.PurePosixPath(promotion.file).stem}"


def overlay_data_section(promotion, record) -> str:
    """The output section one placed *datum* gets in its module's link.

    Named from the unit's own section (:func:`overlay_section`) and the datum: a
    literal-pool index is numbered per object, so two sources of one module can each place
    ``@53`` at their own address, and selecting the object's section by name alone would make
    the two one wildcard.  The name in the *object* is :func:`compile.data_section`'s; this is
    the output section the script gives it.
    """
    return (f"{overlay_section(promotion)}_data_"
            f"{cc.data_section(record['name']).removeprefix('.datum.')}")


def overlay_link_script(overlay, placements, target=None, data=()) -> str:
    """The linker script that places one module's promoted objects inside its window.

    ``placements`` is ``[(promotion, (start, end))]`` -- the address the unit's first function
    sits at and the end of the splits it replaces, both from ``compile.split_extent``, so the
    extent asserted here is the retail one and not a number this script invents.  Each
    section's LMA is its offset in the blob, which is where the image keeps those bytes.

    ``data`` is ``[(promotion, record)]`` for the ledger records the module *owns* -- a
    datum whose ``source`` is one of its promoted units (see :func:`placements_by_module`).
    Each is placed at the retail address the record names, in a section of its own, asserted
    to be the record's compiled length and bounded by the window's data end: a datum at
    0x008011F0 belongs to the blob's data, which the main image's zero-fill reservation
    cannot place and the module's own link can.
    """
    target = target or TARGET
    lines = [OVERLAY_LD_HEADER.format(
        target=target.name, module=overlay.name, vaddr=overlay.vaddr, end=overlay.end,
        code_end=overlay.code_end_vram, image_offset=overlay.image_offset,
        elf=target.elf.name)]
    lines.append("SECTIONS\n{\n")
    names = set()
    for promotion, (start, end) in placements:
        section = overlay_section(promotion)
        if section in names:
            raise ConfigError(
                f"two promoted units of overlay {overlay.name} would share the link section "
                f".{section}: " + ", ".join(
                    other.file for other, _ in placements
                    if overlay_section(other) == section))
        names.add(section)
        lines.append(f"  .{section} 0x{start:08X} : AT(0x{start - overlay.vaddr:08X}) "
                     f"SUBALIGN(1)\n  {{\n    {promotion.object}(.text)\n  }}\n")
        lines.append(f"  ASSERT(SIZEOF(.{section}) == 0x{end - start:X}, "
                     f"\"{promotion.file} does not fill the {end - start:#x} bytes of splits "
                     f"it replaces\")\n")
        lines.append(f"  ASSERT(ADDR(.{section}) + SIZEOF(.{section}) <= "
                     f"0x{overlay.code_end_vram:X}, \"{promotion.file} runs past "
                     f"{overlay.name}'s code end\")\n")
    data_end = overlay.vaddr + overlay.filesize
    for promotion, record in data:
        section = overlay_data_section(promotion, record)
        if section in names:
            raise ConfigError(
                f"two data placements of overlay {overlay.name} would share the link "
                f"section .{section}: " + ", ".join(
                    f"{other.file}'s {other_record['name']}"
                    for other, other_record in data
                    if overlay_data_section(other, other_record) == section))
        names.add(section)
        start = record["address"]
        lines.append(f"  .{section} 0x{start:08X} : AT(0x{start - overlay.vaddr:08X}) "
                     f"SUBALIGN(1)\n  {{\n    {promotion.object}"
                     f"({cc.data_section(record['name'])})\n  }}\n")
        lines.append(f"  ASSERT(SIZEOF(.{section}) == 0x{record['size']:X}, "
                     f"\"{promotion.file}'s {record['name']} is not the "
                     f"{record['size']:#x} bytes the ledger places\")\n")
        # The extent is the retail span the datum owns -- its bytes plus the zero fill
        # retail shows before the next datum -- so it is what the window has to hold, not
        # the compiled length alone.
        lines.append(f"  ASSERT(ADDR(.{section}) + 0x{record['extent']:X} <= "
                     f"0x{data_end:08X}, \"{promotion.file}'s {record['name']} runs past "
                     f"{overlay.name}'s data end\")\n")
    lines.append("  /DISCARD/ : { *(*) }\n}\n")
    return "".join(lines)


# ---------------------------------------------------------------------------
# build.ninja
# ---------------------------------------------------------------------------


def object_path(split: pathlib.Path) -> pathlib.Path:
    """Mirror splat's own object naming (``path_to_object_path``), so its linker script
    and this graph agree: the .s path under the build dir, with ``.o`` appended."""
    return REPO_ROOT / "build" / split.relative_to(REPO_ROOT).with_name(
        split.name + ".o")


def piece_object(path) -> str:
    """The object a generated piece assembles to (the piece path plus ``.o``)."""
    path = pathlib.Path(path)
    return path.with_name(path.name + ".o").as_posix()


def generated_by(*inputs) -> str:
    """The ninja ``|`` clause declaring the files whose text or bytes produce an edge."""
    return " | " + " ".join(inputs)


def unit_name(promotion, geometry=None) -> str:
    """The report's name for a promoted unit: its segment and its source file's stem.

    One name per *linked object* -- ``main/sys_scf`` -- because that is what the promoted
    unit is on both sides: its ``cc`` object (base) against one object of retail's own bytes
    for the same unit (target).  The split-per-function naming it replaces was a property of
    splat's output, not of the unit.
    """
    geometry = _geometry(geometry=geometry)
    return f"{geometry.code_segment}/{pathlib.Path(promotion.file).stem}"


def unit_targets(promoted, manifests, target, geometry=None) -> dict:
    """Write every promoted main-image unit's objdiff target object; ``{file: path}``.

    The object is retail's own bytes for the unit (:func:`diff.basis.unit`), named after the
    unit's functions -- the target side ``objdiff-cli report generate`` must be handed for a
    promoted unit.  Handing it the splits is what made a byte-identical function score
    ~99.2%: a split's ``jal`` names a symbol the object does not define, so objdiff reads it
    as address zero while the ``cc`` object carries the retail address, and counts the two as
    a mismatched operand.  A unit whose code is in an overlay gets no object here: its bytes
    are not in the file-backed image (they are a blob's), and no overlay unit is a report
    unit.

    The objects live in ``build/diff/`` (see :mod:`diff.basis`), are written at configure
    time, and are never an input to the link or to a gate.
    """
    geometry = _geometry(target=target, geometry=geometry)
    written = {}
    for promotion in promoted:
        if promotion.is_overlay or not promotion.code:
            continue
        tu = manifests.tu_named(promotion.file)
        start, end = cc.split_extent(tu, manifests)
        try:
            path = basis.unit([(function.name, function.address, function.size)
                               for function in tu.functions],
                              target.elf, start, end, unit_name(promotion, geometry))
        except basis.Unusable as exc:
            raise ConfigError(str(exc)) from exc
        written[promotion.file] = _display(path)
    return written


def objdiff_json(code, promotions, geometry=None, targets=None) -> str:
    """The objdiff project: one unit per linked object, target against the object we build.

    objdiff compares a unit's ``base_path`` with its ``target_path``.  A promoted main-image
    unit is one unit and one pair: its ``cc`` object is the base, and the target is the
    object :func:`unit_targets` derives from the retail image -- every function of the unit,
    at its retail offset, under its retail name.  That pairing measures the code the gates
    measure: a function the compiler reproduced is byte-for-byte equal, so the report counts
    it, instead of scoring it ~99.2% over a split's symbolic ``jal``.  ``targets`` is what
    :func:`unit_targets` returned; a promoted unit it did not write is a configuration error,
    not a silently missing function.

    Every other code split keeps its own unit and its split object as the target, with a
    ``null`` base: there is no C for it yet, so its bytes have to count as un-matched.  (The
    diff *verb* stands the split's own bytes in for a base when it compares one function; a
    progress report must not score a unit against itself.)  A project that listed only what
    is already in C would report a skeleton with zero C written as matched, which is the
    opposite of what a progress report is for.  Data is not part of this graph -- it stays
    pinned retail bytes by design -- so neither are the data databins.
    """
    geometry = _geometry(geometry=geometry)
    targets = targets or {}
    promoted_splits = {split for promotion in promotions
                       if not promotion.is_overlay and promotion.code
                       for split in promotion.splits}
    units = [{"name": f"{geometry.code_segment}/{pathlib.Path(name).stem}",
              "target_path": object_path(REPO_ROOT / name).relative_to(REPO_ROOT).as_posix(),
              "base_path": None,
              "scratch": {},
              "metadata": {}}
             for _, name in code if name not in promoted_splits]
    for promotion in promotions:
        if promotion.is_overlay or not promotion.code:
            continue
        target = targets.get(promotion.file)
        if target is None:
            raise ConfigError(
                f"{promotion.file}: a promoted unit has no target object; the report would "
                f"count none of its code.  unit_targets() writes one per promoted unit")
        units.append({"name": unit_name(promotion, geometry),
                      "target_path": target,
                      "base_path": promotion.object,
                      "scratch": {},
                      "metadata": {}})
    units.sort(key=lambda unit: unit["name"])
    names = [unit["name"] for unit in units]
    if len(set(names)) != len(names):
        repeated = sorted({name for name in names if names.count(name) > 1})
        raise ConfigError("two objdiff units share a name: " + ", ".join(repeated)
                          + "; a report keys units by name")
    return json.dumps({"$schema": OBJDIFF_SCHEMA, "custom_make": "ninja",
                       "build_target": True, "build_base": True,
                       "min_version": "2.0.0", "units": units}, indent=2) + "\n"


def ninja_text(splits, databins, objects_only: bool, promotions=(), target=None,
               geometry=None, pieces=(), pads=(), data_sources=(), data_compiler=None,
               overlay_links=()) -> str:
    target = target or TARGET
    geometry = geometry or target.geometry_required()
    elf = target.elf.name
    built = _display(target.built)
    lines = [NINJA_HEADER.format(target=target.name, built=built,
                                 elf=f"orig/{elf}"), "\n"]
    lines += [
        # ninja rule blocks accept only its own keywords, so the variables the specified
        # command lines interpolate are declared at the top level (and may be overridden
        # per edge, which is how Task 12 will pick a compiler flag set per TU).
        f"python = {PYTHON}\n",
        f"mapfile = build/{elf}.map\n",
        "\n",
        "rule as\n",
        f"  command = {AS_RULE}\n",
        "  description = as $in\n",
        "\n",
        "rule cc\n",
        # The target is a *flag* of the driver, not part of its input list: which config's
        # manifests place the unit -- and which retail binary its DWARF is compared with --
        # is exactly what `--target` decides, and ninja has to say it on every edge.
        f'  command = "$python" tools/toolchain/compile.py --target {target.name} '
        '$in $out $flags\n',
        "  description = cc $in\n",
        "\n",
        # One section out of the object the compiler produced: the promoted unit's own
        # `.debug`/`.line` bytes, which the tail edge substitutes for retail's databins.
        # The named sink is what keeps objcopy read-only on $in -- it treats a lone input as
        # an *in-place* edit, and the `.debug` and `.line` edges run concurrently against the
        # same object, so an in-place rewrite (truncate, then write the same bytes back) has
        # one edge reading the object while the other is mid-write -- observed as
        # `objcopy: [.debug]: file truncated` and a short payload.  The sink is the null
        # device, spelled by `os.devnull` because `cmd /c` has no `/dev/null` (see OBJSEC_PY).
        "rule objsec\n",
        f'  command = "$python" -c "{OBJSEC_PY}" $section $out $in\n',
        "  description = objsec $section $out\n",
        "\n",
        "rule ld\n",
        f"  command = mips-linux-gnu-ld -EL -T {_display(target.undefined_syms)} "
        f"-T {_display(target.undefined_funcs)} -Map $mapfile -T $in -o $out\n",
        "  description = ld $out\n",
        "\n",
        "rule bin\n",
        "  command = mips-linux-gnu-objcopy $in $out -O binary\n",
        "  description = bin $out\n",
        "\n",
        # The file's non-loadable tail has no symbols to link, so it is concatenated in
        # manifest order instead -- the one shape `ld`/`objcopy` cannot produce, because
        # objcopy writes only the sections a program header loads.  The rule keeps its name
        # (`cat`, and three tests identify the tail edge by it); only its command is Python,
        # because `cat` is not a program on Windows (see CAT_PY).
        "rule cat\n",
        f'  command = "$python" -c "{CAT_PY}" $out $in\n',
        "  description = cat $out\n",
        "\n",
        "rule g1\n",
        # The gate reads the target too: its retail binary, its checksums manifest and its
        # manifests are all the target's, and `$in` is the target's built image.
        f'  command = "$python" tools/verify/g1.py --target {target.name} $in\n',
        "  description = g1 $in\n",
        "\n",
    ]
    objects = []
    for split in splits:
        rel = split.relative_to(REPO_ROOT).as_posix()
        obj = object_path(split).relative_to(REPO_ROOT).as_posix()
        lines.append(f"build {obj}: as {rel}"
                     f"{generated_by(GENERATOR, AS_PROGRAM)}\n")
        objects.append(obj)
    # A data placement's split pieces are generated by configure itself, not splat; the as
    # rule assembles them exactly like a split, because a piece *is* a split's remaining text.
    for path in list(pieces) + [path for _, path in pads]:
        obj = piece_object(path)
        lines.append(f"build {obj}: as {path}"
                     f"{generated_by(GENERATOR, AS_PROGRAM)}\n")
        objects.append(obj)
    for source in data_sources:
        # `--data`: compile a data-only source raw (no `-g`, so it contributes no DWARF) and
        # verify each of its placements against retail.  The link places the section itself.
        lines.append(f"build build/{source}.o: cc {source}"
                     f"{generated_by(*COMPILE_EDGE_INPUTS)}\n")
        lines.append(f"  flags = --data --compiler {data_compiler} "
                     f"-c -lang c -O3 -opt full\n")
        objects.append(f"build/{source}.o")
    for promotion in promotions:
        lines.append(f"build {promotion.object}: cc {promotion.file}"
                     f"{generated_by(*COMPILE_EDGE_INPUTS)}\n")
        lines.append(f"  flags = {promotion.flags}\n")
        # A unit with no `.line` chunk (a data-only unit has no code, so no statement
        # table) has nothing to substitute and the object carries no `.line` section; an
        # `objcopy --dump-section` edge would then fail on a section that is not there.
        sections = [(".debug", promotion.debug_payload)]
        if promotion.line_databins:
            sections.append((".line", promotion.line_payload))
        for section, payload in sections:
            lines.append(f"build {payload}: objsec {promotion.object}"
                         f"{generated_by(*COMPILE_EDGE_INPUTS)}\n")
            lines.append(f"  section = {section}\n")
        objects.append(promotion.object)
    lines.append("\n")
    lines.append("build splits: phony "
                 + " ".join(s.relative_to(REPO_ROOT).as_posix() for s in splits) + "\n")
    lines.append("build objects: phony " + " ".join(objects) + "\n")
    lines.append("\n")
    if objects_only:
        lines.append("default objects\n")
        return "".join(lines)
    # One link per overlay module with a promoted unit.  It is a *second* link, in its own
    # script, into its own ELF: the blob's bytes are the disc image's and the file G1
    # compares is assembled from the retail ELF's two halves, so a promoted overlay object
    # being linked at its retail VA cannot move a byte of it.
    overlay_elfs = []
    if overlay_links:
        lines.append("rule ldovl\n")
        lines.append("  command = mips-linux-gnu-ld -EL -T $script -o $out $in\n")
        lines.append("  description = ld $out\n")
        lines.append("\n")
        for module, script, objects_of_module in overlay_links:
            elf_path = _display(target.overlay_elf(module))
            # The descriptor is an implicit input too: a promoted row added anywhere bumps
            # config/targets.py's mtime, and without this dependency the module ELF stays
            # older than it, which the staleness check then reports as stale evidence.
            lines.append(f"build {elf_path}: ldovl " + " ".join(objects_of_module)
                         + f" | {_display(script)} {GENERATOR} "
                           f"{_display(REPO_ROOT / 'config' / 'targets.py')}\n")
            lines.append(f"  script = {_display(script)}\n")
            overlay_elfs.append(elf_path)
        lines.append("\n")
    # elf_header is part of the loadable image (it is the file's first
    # `loadable_rom` bytes), so the tail is every databin after it, in file order -- with a
    # promoted unit's own `.debug`/`.line` payload in place of the databins of the chunks it
    # owns.
    tail = tail_inputs(databins, promotions)
    lines.append(f"build out/{elf}.elf: ld {_display(target.ld_script)}"
                 f"{generated_by(*GENERATED_BY)} || objects\n")
    lines.append(f"build build/{elf}.loadable: bin out/{elf}.elf"
                 f"{generated_by(*GENERATED_BY)}\n")
    lines.append(f"build build/{elf}.tail: cat " + " ".join(tail)
                 + f"{generated_by(*GENERATED_BY)}\n")
    lines.append(f"build {built}: cat build/{elf}.loadable "
                 f"build/{elf}.tail" + generated_by(*GENERATED_BY) + "\n")
    lines.append("\n")
    # The gate is an edge of its own with no output file, so ninja runs it on every
    # build: `ninja` proves the image, `ninja objects` still stops at the objects.
    lines.append(f"build g1: g1 {built} | orig/{elf}\n")
    lines.append(f"\ndefault {built} " + " ".join(overlay_elfs + ["g1"]) + "\n")
    return "".join(lines)


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------


def write_if_different(path: pathlib.Path, text: str) -> None:
    if path.is_file() and path.read_text() == text:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, newline="\n")


def write_bytes_if_different(path: pathlib.Path, data: bytes) -> None:
    """``write_if_different`` for bytes: a blob is not text, and is 100 KB of it."""
    if path.is_file() and path.read_bytes() == data:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)


def configure(target: "targets.Target", cus_path=None, chunks_path=None,
              symbols_path=None, objects_only: bool = False) -> None:
    """Split ``target``'s retail ELF and write its graph, its linker script and its objdiff
    project.

    The geometry is resolved first and on purpose: a target whose segment list nobody has
    measured stops here, before anything is written, rather than producing a split of one
    file at another file's addresses.  The promoted sources are checked on the same principle
    and nearly as early: a ``tu_builds`` source that still carries a ``#line`` directive, or
    that reaches a datum by a cast literal, stops the run before ``splat`` runs and before
    ``build.ninja`` is written (see :func:`check_promoted_sources`), which is the only moment a
    reader can still see the file the build would hide.
    """
    geometry = target.geometry_required()
    check_promoted_sources(target)
    config_dir = target.config_dir
    cus_path = pathlib.Path(cus_path) if cus_path else target.cus
    chunks_path = pathlib.Path(chunks_path) if chunks_path else target.chunks
    symbols_path = pathlib.Path(symbols_path) if symbols_path else target.symbols
    cus = load_json(cus_path, "cus.json")
    chunks = load_json(chunks_path, "debug_chunks.json")
    check_manifests(cus, chunks)
    for name, offset, size in geometry.trailing:
        if name in CHUNKED:
            check_chunk_tiling(chunks, f".{name}", offset, size, geometry)

    write_if_different(target.splat_symbols,
                       splat_symbols(symbols_path.read_text(), target))
    yaml_path = config_dir / "splat.yaml"
    write_if_different(yaml_path, splat_yaml(chunks, target, geometry))

    # splat emits a split only when it creates the C file for the run, and it never overwrites
    # one that exists: a stale artifact makes it write only the functions its deps file names,
    # and the link then refuses with "the code splits are not the retail ... bytes".
    for stale in sorted((REPO_ROOT / "build" / "src").glob("*.c")):
        stale.unlink()
    print(f"configure: splat split {_display(yaml_path)}")
    splat = [*SPLAT, _display(yaml_path)]
    proc = subprocess.run(splat, cwd=REPO_ROOT)
    if proc.returncode != 0:
        raise ConfigError(
            f"`{' '.join(splat)}` failed with exit {proc.returncode}; its output above "
            f"names the problem")

    # The main graph's splits are the main image's.  An overlay module's run writes under
    # `asm/nonmatchings/<module>/`, and those bodies are placed by that module's own link,
    # never assembled into the main image -- so they are not `as` edges and not objdiff units.
    overlay_prefixes = tuple(f"asm/nonmatchings/{overlay.name}/"
                             for overlay in geometry.overlays)
    splits = [path for path in sorted((REPO_ROOT / "asm").rglob("*.s"))
              if not path.relative_to(REPO_ROOT).as_posix().startswith(overlay_prefixes)]
    if not splits:
        raise ConfigError("splat produced no splits under asm/")

    databins = databin_segments(chunks, geometry)
    tail = databins[1:]
    covered = geometry.loadable_end + sum(size for _, _, size in tail)
    if covered != geometry.elf_size:
        raise ConfigError(
            f"the databin segments after elf_header cover "
            f"{covered - geometry.loadable_end} bytes, so the file's tail would be "
            f"0x{geometry.elf_size - covered:X} bytes short of 0x{geometry.elf_size:X}; "
            f"splat's assets and the manifest disagree")

    try:
        manifests = cc.Manifests(target)
    except cc.Unusable as exc:
        raise ConfigError(str(exc)) from exc
    promoted = promotions(manifests, target)
    overlays = overlay_modules(promoted, geometry)
    for overlay in overlays:
        run_overlay_splat(overlay, target)

    # The overlay runs' splits are a blob's, not the main image's: they are what
    # `compile.split_extent` reads for an overlay unit, and nothing else may see them.
    sources = split_sources(skip={overlay.name for overlay in overlays})
    code = code_splits(sources, geometry)
    target_objects = unit_targets(promoted, manifests, target, geometry)
    aliases = link_aliases(
        sources, target.splat_symbols,
        [target.undefined_syms, target.undefined_funcs])
    placements = data_placements(target)
    main_placements, module_placements = placements_by_module(placements, promoted, geometry)
    replacements = {}
    pieces, pads, moved = plan_data(sources, code, geometry, main_placements, replacements)
    aliases = sorted(dict.fromkeys(aliases + moved), key=lambda item: (item[1], item[0]))
    built_from = {promotion.file: promotion.object for promotion in promoted}
    data = placement_inputs(main_placements, built_from)
    data_sources = sorted({record["source"] for record in main_placements}
                          - set(built_from))
    versions = {version for version, _flags in target.build_table().values()}
    data_compiler = (versions.pop() if len(versions) == 1 else cc.fetch.REQUIRED)
    write_if_different(target.ld_script,
                       pinned_ld_script(code, aliases, promoted, target, geometry,
                                        replacements=replacements, data=data, pads=pads))
    overlay_links = []
    for overlay in overlays:
        units = [promotion for promotion in promoted
                 if promotion.module == overlay.name and promotion.code]
        placements_of = []
        for promotion in units:
            tu = manifests.tu_named(promotion.file)
            placements_of.append((promotion, cc.split_extent(tu, manifests)))
        records = module_placements.get(overlay.name, [])
        script = overlay_link_script(overlay, placements_of, target, data=records)
        write_if_different(target.overlay_ld_script(overlay.name), script)
        # ninja does not create an edge's output directory, and `ld` will not either.
        target.overlay_elf(overlay.name).parent.mkdir(parents=True, exist_ok=True)
        # Every object the script selects is a link input: one section of a promoted unit's
        # object is not an input the module named anywhere, and `ld` will not find it.
        objects_of_module = [promotion.object for promotion in units]
        for promotion, _record in records:
            if promotion.object not in objects_of_module:
                objects_of_module.append(promotion.object)
        overlay_links.append((overlay.name, target.overlay_ld_script(overlay.name),
                              objects_of_module))
        placed = ", ".join(f"{promotion.file} at 0x{start:08X}..0x{end:08X}"
                           for promotion, (start, end) in placements_of)
        datums = ", ".join(f"{record['name']} at 0x{record['address']:08X}"
                           for _promotion, record in records)
        print(f"configure: overlay {overlay.name}: " + placed
              + (f"; data {datums}" if datums else ""))

    ninja = ninja_text(splits, databins, objects_only, promoted, target, geometry,
                       pieces=pieces, pads=pads, data_sources=data_sources,
                       data_compiler=data_compiler, overlay_links=overlay_links)
    write_if_different(REPO_ROOT / "build.ninja", ninja)
    write_if_different(REPO_ROOT / "objdiff.json",
                       objdiff_json(code, promoted, geometry, target_objects))
    print(f"configure: target {target.name} ({target.elf.name}): {len(splits)} splits, "
          f"{len(code)} code splits at 0x{code[0][0]:X}, "
          f"{len(tail)} tail databins, {len(aliases)} link aliases, build.ninja written"
          + (" (objects only)" if objects_only else ""))
    if promoted:
        print("configure: built from C: "
              + ", ".join(f"{p.file} at 0x{p.address:08X} [{p.flags}]" for p in promoted))


def parse_args(argv):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--target", default=targets.DEFAULT,
                        help="the target to configure, by name (default: "
                             f"{targets.DEFAULT}; known: {', '.join(targets.names())})")
    parser.add_argument("--cus", type=pathlib.Path, default=None,
                        help="path to cus.json (default: the target's own)")
    parser.add_argument("--chunks", type=pathlib.Path, default=None,
                        help="path to debug_chunks.json (default: the target's own)")
    parser.add_argument("--symbols", type=pathlib.Path, default=None,
                        help="path to symbol_addrs.txt (default: the target's own)")
    parser.add_argument("--objects", action="store_true",
                        help="emit the object graph only (the objdiff CI job's target)")
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(sys.argv[1:] if argv is None else argv)
    try:
        target = targets.get(args.target)
        configure(target, args.cus, args.chunks, args.symbols, args.objects)
    except targets.UnknownTarget as exc:
        print(f"configure.py: error: {exc}", file=sys.stderr)
        return 2
    except targets.NotMeasured as exc:
        print(f"configure.py: error: {exc}", file=sys.stderr)
        return 2
    except ConfigError as exc:
        print(f"configure.py: error: {exc}", file=sys.stderr)
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
