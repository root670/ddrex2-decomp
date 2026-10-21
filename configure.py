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
from toolchain import compile as cc  # noqa: E402  the one derivation of a unit's placement

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
ALIGN_FILTER = r"""sed -E '/^[[:space:]]*\.align[[:space:]]/d'"""
AS_RULE = ("cpp -Iinclude $in -o - | " + ALIGN_FILTER
           + " | mips-linux-gnu-as -Iasm/include --no-pad-sections "
             "-EL -march=5900 -mabi=eabi -o $out")

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
# splat symbol file
# ---------------------------------------------------------------------------

SYMBOL_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<address>0x[0-9A-Fa-f]+);\s*//\s*(?P<attrs>.*)$")
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


def split_sources() -> dict:
    """Every generated split's text, keyed by its repo-relative path.

    splat's output is read once: the link needs each code split's address and every
    split's labels and symbol references, and reading 4,092 files twice is silly.
    """
    sources = {}
    for path in sorted((REPO_ROOT / "asm").rglob("*.s")):
        sources[path.relative_to(REPO_ROOT).as_posix()] = path.read_text()
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


def data_placements(target=None):
    """The target's address-driven data ledger (see `toolchain.compile.data_placements`)."""
    try:
        return cc.data_placements(target or TARGET)
    except cc.Unusable as exc:
        raise ConfigError(str(exc)) from exc


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
    return pieces, removed


def plan_data(sources, code, geometry, placements, replacements):
    """Emit the per-region pieces a data placement's split no longer supplies.

    ``replacements`` maps a split path to the pieces that replace it, in address order.  The
    returned ``(pieces, pads, aliases)`` are the files to assemble and the labels to keep
    defined; the caller adds the compiled datum's own object section at the same addresses.
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
        split_end = rows[index + 1][0] if index + 1 < len(rows) else geometry.loadable_end
        begin, end = record["address"], record["address"] + record["extent"]
        if not (split_address <= begin < end <= split_end):
            raise ConfigError(
                f"{record['name']} spans 0x{begin:X}..0x{end:X}, which crosses the split "
                f"{split} (0x{split_address:X}..0x{split_end:X}); a placement must be inside "
                f"one split")
        per_split.setdefault(split, []).append((begin, end))
        if record["extent"] > record["size"]:
            pads.append((begin + record["size"], record["name"]))
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
    for address, name in pads:
        path = REPO_ROOT / "build" / "generated" / "data" / f"{name}.pad.s"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("\t.text\n\t.space\t%d\n" % pad_size(placements, name),
                        newline="\n")
        relative = path.relative_to(REPO_ROOT).as_posix()
        pad_pieces.append((address, relative))
    return pieces, pad_pieces, aliases


def rows_of(split, rows):
    """The retail address a split starts at."""
    for address, name in rows:
        if name == split:
            return address
    raise ConfigError(f"{split} is not a code split; a data placement names it")


def pad_size(placements, name):
    for record in placements:
        if record["name"] == name:
            return record["extent"] - record["size"]
    raise ConfigError(f"no placement record for {name}")


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

    ``.text`` comes from the object (the pinned ``ld`` script places it where the unit's
    splits used to be), while ``.debug``/``.line`` are dumped out of the same object by the
    ``objsec`` edges and substituted for the retail databins of the chunks the unit owns.
    The split objects stay in the graph: they are objdiff's target side (M1's own bytes),
    and ``ddr diff`` still needs them.
    """

    __slots__ = ("file", "address", "flags", "object", "debug_payload", "line_payload",
                 "debug_databin", "line_databins", "splits")

    def __init__(self, file, address, flags, object_path, debug_payload, line_payload,
                 debug_databin, line_databins, splits):
        self.file = file                  # "src/sys/sys_scf.c"
        self.address = address            # the unit's first function's retail address
        self.flags = flags                # the cc rule's `flags` variable
        self.object = object_path         # repo-relative path of the cc edge's output
        self.debug_payload = debug_payload
        self.line_payload = line_payload
        self.debug_databin = debug_databin        # the databin it replaces
        self.line_databins = line_databins        # the run of databins it replaces
        self.splits = splits              # the split paths the ld script must not list


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
    """Refuse a ``tu_builds`` source that still carries ``#line``, before anything is written.

    A promoted source is the evidence for the bytes the image carries, so a directive -- which
    renumbers what a reader sees -- is not something the build may quietly rewrite away.  This
    runs first in :func:`configure`, while ``build.ninja`` is still the previous file: a source
    that was promoted with directives left in it stops the run instead of producing a graph
    that hides the problem.  ``compile.py`` refuses the same source at the ``cc`` edge, so even
    a stale graph cannot build it.

    ``root`` is the tree the ``tu_builds`` paths are relative to; it is a parameter only so a
    test can point the same rule at a synthetic tree.
    """
    target = target or TARGET
    root = pathlib.Path(root) if root is not None else REPO_ROOT
    for file in sorted(target.build_table()):
        path = root / file
        if not path.is_file():
            continue        # a missing source is promotions()' error, and it names it there
        try:
            cc.refuse_line_directives(file, path.read_bytes().decode("latin-1"))
        except cc.Unusable as exc:
            raise ConfigError(str(exc)) from exc


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
    segment = target.geometry_required().code_segment
    for file, (version, flags, state) in sorted(builds.items()):
        tu = manifests.tu_named(file)
        command = f"--compiler {version} {flags}"
        if state is True:
            command += " --normalise-debug"
        elif state == "adopt":
            command += " --adopt-retail-meta"
        out.append(Promotion(
            file, tu.address, command,
            f"build/{file}.o", f"build/{file}.o.debug", f"build/{file}.o.line",
            f".debug_{manifests.debug_chunk_index(tu):03d}",
            [f".line_{index:03d}" for index in manifests.line_chunk_indices(tu)],
            {f"asm/nonmatchings/{segment}/{function.name}.s"
             for function in tu.functions}))
    return sorted(out, key=lambda promotion: promotion.address)


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
    order still *is* the layout.

    ``replacements`` carries a split whose bytes a data placement owns: ``{split: [(address,
    piece path)]}``, the split's remaining text as per-region pieces in address order.
    ``data`` is ``[(address, object, section)]`` for the compiled datum placed at its retail
    address, and ``pads`` ``[(address, piece path)]`` for the zero fill retail shows to the
    recorded extent.  Every entry is listed by address, so the script still *is* the layout.
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
    promoted = {name for promotion in promotions for name in promotion.splits}
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
    listed += [(promotion.address, promotion.object, ".text") for promotion in promotions]
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


def objdiff_json(code, promotions, geometry=None) -> str:
    """The objdiff project: one unit per linked code object, target against the C that exists.

    objdiff compares a unit's ``base_path`` with its ``target_path``.  The target side here
    is the function's split object -- retail's own bytes, which G1 proves -- and the base side
    is the object the link actually places for it: the promoted unit's C object where the
    function has been rewritten, and ``null`` where it has not, which objdiff counts as
    un-matched.  One unit per *linked* object, because that is the set the image is built
    from: a project that listed only what is already in C would report a skeleton with zero C
    written as matched, which is the opposite of what a progress report is for.  Data is not
    part of this graph -- it stays pinned retail bytes by design -- so neither are the data
    databins.
    """
    geometry = _geometry(geometry=geometry)
    base_of = {split: promotion.object
               for promotion in promotions for split in promotion.splits}
    units = [{"name": f"{geometry.code_segment}/{pathlib.Path(name).stem}",
              "target_path": object_path(REPO_ROOT / name).relative_to(REPO_ROOT).as_posix(),
              "base_path": base_of.get(name),
              "scratch": {},
              "metadata": {}}
             for _, name in code]
    units.sort(key=lambda unit: unit["name"])
    return json.dumps({"$schema": OBJDIFF_SCHEMA, "custom_make": "ninja",
                       "build_target": True, "build_base": True,
                       "min_version": "2.0.0", "units": units}, indent=2) + "\n"


def ninja_text(splits, databins, objects_only: bool, promotions=(), target=None,
               geometry=None, pieces=(), pads=(), data_sources=(), data_compiler=None) -> str:
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
        f"  command = python3 tools/toolchain/compile.py --target {target.name} "
        "$in $out $flags\n",
        "  description = cc $in\n",
        "\n",
        # One section out of the object the compiler produced: the promoted unit's own
        # `.debug`/`.line` bytes, which the tail edge substitutes for retail's databins.
        # The explicit `/dev/null` output matters: objcopy treats a lone input file as an
        # *in-place* edit, and the `.debug` and `.line` edges run concurrently against the
        # same object, so an in-place rewrite (truncate, then write the same bytes back)
        # has one edge reading the object while the other is mid-write -- observed as
        # `objcopy: [.debug]: file truncated` and a short payload.  Naming an output keeps
        # objcopy read-only on $in: the object keeps its dates and bytes, each dump lands
        # at `now`, and both edges stay incremental.
        "rule objsec\n",
        "  command = mips-linux-gnu-objcopy --dump-section $section=$out $in /dev/null\n",
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
        # objcopy writes only the sections a program header loads.
        "rule cat\n",
        "  command = cat $in > $out\n",
        "  description = cat $out\n",
        "\n",
        "rule g1\n",
        # The gate reads the target too: its retail binary, its checksums manifest and its
        # manifests are all the target's, and `$in` is the target's built image.
        f"  command = python3 tools/verify/g1.py --target {target.name} $in\n",
        "  description = g1 $in\n",
        "\n",
    ]
    objects = []
    for split in splits:
        rel = split.relative_to(REPO_ROOT).as_posix()
        obj = object_path(split).relative_to(REPO_ROOT).as_posix()
        lines.append(f"build {obj}: as {rel}{generated_by(*GENERATED_BY)}\n")
        objects.append(obj)
    # A data placement's split pieces are generated by configure itself, not splat; the as
    # rule assembles them exactly like a split, because a piece *is* a split's remaining text.
    for path in list(pieces) + [path for _, path in pads]:
        obj = piece_object(path)
        lines.append(f"build {obj}: as {path}{generated_by(*GENERATED_BY)}\n")
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
        for section, payload in ((".debug", promotion.debug_payload),
                                 (".line", promotion.line_payload)):
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
    lines.append(f"\ndefault {built} g1\n")
    return "".join(lines)


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------


def write_if_different(path: pathlib.Path, text: str) -> None:
    if path.is_file() and path.read_text() == text:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, newline="\n")


def configure(target: "targets.Target", cus_path=None, chunks_path=None,
              symbols_path=None, objects_only: bool = False) -> None:
    """Split ``target``'s retail ELF and write its graph, its linker script and its objdiff
    project.

    The geometry is resolved first and on purpose: a target whose segment list nobody has
    measured stops here, before anything is written, rather than producing a split of one
    file at another file's addresses.  The promoted sources are checked on the same principle
    and nearly as early: a ``tu_builds`` source still carrying a ``#line`` directive stops the
    run before ``splat`` runs and before ``build.ninja`` is written (see
    :func:`check_promoted_sources`), which is the only moment a reader can still see the file
    the build would hide.
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

    print(f"configure: splat split {_display(yaml_path)}")
    splat = [*SPLAT, _display(yaml_path)]
    proc = subprocess.run(splat, cwd=REPO_ROOT)
    if proc.returncode != 0:
        raise ConfigError(
            f"`{' '.join(splat)}` failed with exit {proc.returncode}; its output above "
            f"names the problem")

    splits = sorted((REPO_ROOT / "asm").rglob("*.s"))
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

    sources = split_sources()
    code = code_splits(sources, geometry)
    promoted = promotions(target=target)
    aliases = link_aliases(
        sources, target.splat_symbols,
        [target.undefined_syms, target.undefined_funcs])
    placements = data_placements(target)
    replacements = {}
    pieces, pads, moved = plan_data(sources, code, geometry, placements, replacements)
    aliases = sorted(dict.fromkeys(aliases + moved), key=lambda item: (item[1], item[0]))
    built_from = {promotion.file: promotion.object for promotion in promoted}
    data = [(record["address"], built_from.get(record["source"], f"build/{record['source']}.o"),
             ".data") for record in placements]
    data_sources = sorted({record["source"] for record in placements} - set(built_from))
    versions = {version for version, _flags, _state in target.build_table().values()}
    data_compiler = (versions.pop() if len(versions) == 1 else cc.fetch.REQUIRED)
    write_if_different(target.ld_script,
                       pinned_ld_script(code, aliases, promoted, target, geometry,
                                        replacements=replacements, data=data, pads=pads))

    ninja = ninja_text(splits, databins, objects_only, promoted, target, geometry,
                       pieces=pieces, pads=pads, data_sources=data_sources,
                       data_compiler=data_compiler)
    write_if_different(REPO_ROOT / "build.ninja", ninja)
    write_if_different(REPO_ROOT / "objdiff.json",
                       objdiff_json(code, promoted, geometry))
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
