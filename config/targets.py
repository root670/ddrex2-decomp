"""The target descriptor: every fact that differs between decompilation targets.

One decompilation target is one row of facts: the retail binary and its G1 pin, the disc image
and its G3 pin, the config directory its manifests live in, the measured geometry that turns a
file offset into a virtual address (and back), and the compiler/flag pair each promoted unit was
measured against.  This module is the only place those are written down; every tool -- the CLI,
``configure.py``, the oracle emitters, both gates, the ISO tool and the compiler driver -- reads
them from here, so retargeting is adding a descriptor rather than editing a dozen files.

    from config import targets
    target = targets.get()                   # the default target
    target = targets.get("ddrex2p")          # ... or one by name
    target.elf, target.elf_sha256            # the retail ELF and the digest G1 pins
    target.image, target.image_sha256        # the disc image and the digest G3 pins
    target.config_dir                        # config/ddrex2p
    target.cus, target.symbols               # the manifests inside it

**One registry, named targets.**  :class:`Registry` is the set of targets this tree can build
for, each addressed by name; :data:`TARGETS` is the one the tools use.  Adding a target is a
:class:`Target` and a line in that registry -- there is no other place that has to learn about
it, and no tool spells a target name or a retail path of its own.  ``--target <name>`` selects
one on every command; the default is the registry's, and a name nothing defines is a loud usage
error rather than a silent fallback to the default (a typo must not configure the wrong game).

**A missing field fails loudly.**  Every field is validated on construction -- an empty pin, a
nameless binary, a config directory that is not ``config/<name>`` -- because a descriptor that
quietly defaults is a gate that quietly passes.

**Geometry is measured, never assumed.**  :class:`Geometry` is the segment list and the file
geometry the build, both gates and the ISO tool read; it is *absent* for a target whose retail
ELF nobody has measured yet, and :meth:`Target.geometry_required` then raises rather than handing
back another target's numbers.  The current target's is measured from its own binary when it is
placed and split, which is what ``orig/<elf>`` plus a generated ``config/<name>/`` are for; until
then every tool stops at that message instead of producing a plausible image of the wrong game.
"""

from __future__ import annotations

import dataclasses
import pathlib
import re

#: The repository root: every path in a descriptor is spelled from here, so a descriptor is
#: readable in a diff without the reader resolving relative paths in their head.
REPO_ROOT = pathlib.Path(__file__).resolve().parents[1]

_SHA256 = re.compile(r"[0-9a-f]{64}")
_NAME = re.compile(r"[a-z0-9_]+")


class UnknownTarget(LookupError):
    """A target name no descriptor in the registry defines."""


class NotMeasured(RuntimeError):
    """The target's geometry has not been measured from its own retail ELF yet."""


@dataclasses.dataclass(frozen=True)
class Geometry:
    """The measured shape of one retail ELF and of the disc image that carries it.

    The numbers are measurements of a specific file, so every one of them is a field: the
    loadable segment's file and virtual addresses, the zero-filled tail above it, the
    sections that follow the loadable image (``trailing``) with the two chunked ones' lengths,
    and where the boot ELF sits in the disc image.  The derived values -- the code size, the
    bss base and size -- are properties, so a measurement cannot disagree with itself.

    ``trailing`` is ``((name, file offset, size), ...)`` in file order: the whole segment list
    after the loadable image, padding included or not (``configure.py`` fills the gaps with
    ``pad_*`` databins of its own).  The last entry ends at the file's end, and the debug and
    line sizes are the ``.debug``/``.line`` entries' sizes -- both checked at construction.
    """

    elf_size: int
    loadable_rom: int
    loadable_end: int
    loadable_vram: int
    bss_end: int
    trailing: tuple
    debug_size: int
    line_size: int
    image_elf_offset: int
    code_segment: str = "main"

    def __post_init__(self):
        for field in ("elf_size", "loadable_end", "loadable_vram", "bss_end", "debug_size",
                      "line_size", "image_elf_offset"):
            value = getattr(self, field)
            if not isinstance(value, int) or value <= 0:
                raise ValueError(f"geometry {field} is {value!r}: it must be a positive "
                                 f"integer, measured from the retail ELF")
        if not isinstance(self.loadable_rom, int) or self.loadable_rom < 0:
            raise ValueError(f"geometry loadable_rom is {self.loadable_rom!r}: the loadable "
                             f"image starts at a file offset, zero at the earliest")
        if not (self.loadable_rom < self.loadable_end < self.elf_size):
            raise ValueError(
                f"geometry says the loadable image is 0x{self.loadable_rom:X}.."
                f"0x{self.loadable_end:X} of a 0x{self.elf_size:X}-byte file: it must lie "
                f"inside the file")
        if self.bss_end <= self.bss_vram:
            raise ValueError(
                f"geometry says bss ends at 0x{self.bss_end:X}, below its base "
                f"0x{self.bss_vram:X}: the zero-filled tail must sit above the file-loaded "
                f"image")
        if not isinstance(self.code_segment, str) or not self.code_segment:
            raise ValueError("geometry code_segment is empty: it names the yaml's `c` "
                             "segment, which the splits live under")
        if not self.trailing:
            raise ValueError("geometry trailing is empty: the file's sections after the "
                             "loadable image are part of the measurement")
        names, previous_end = set(), self.loadable_end
        for entry in self.trailing:
            if not (isinstance(entry, tuple) and len(entry) == 3
                    and isinstance(entry[0], str) and entry[0]
                    and isinstance(entry[1], int) and isinstance(entry[2], int)):
                raise ValueError(f"geometry trailing entry {entry!r} is not "
                                 f"(name, file offset, size)")
            name, offset, size = entry
            if name in names:
                raise ValueError(f"geometry trailing names {name!r} twice")
            if size <= 0 or offset < previous_end:
                raise ValueError(
                    f"geometry trailing {name!r} is at 0x{offset:X}+0x{size:X}, which is not "
                    f"after the 0x{previous_end:X} the previous section ends at: the "
                    f"trailing sections must be in file order and must not overlap")
            names.add(name)
            previous_end = offset + size
        if previous_end != self.elf_size:
            raise ValueError(
                f"geometry trailing sections end at 0x{previous_end:X}, not at the file's "
                f"0x{self.elf_size:X} bytes: the measurement does not cover the file")
        for section, size in (("debug", self.debug_size), ("line", self.line_size)):
            if section not in names:
                raise ValueError(f"geometry trailing names no {section!r} section")
            if self.trailing_of(section)[1] != size:
                raise ValueError(
                    f"geometry {section}_size is {size}, but the .{section} section in "
                    f"trailing is {self.trailing_of(section)[1]} bytes: one measurement, "
                    f"two numbers")

    @property
    def code_size(self) -> int:
        """The loadable image's byte length: the code region the link asserts."""
        return self.loadable_end - self.loadable_rom

    @property
    def bss_vram(self) -> int:
        """Where the zero-filled tail starts, as a virtual address."""
        return self.loadable_end + self.loadable_vram - self.loadable_rom

    @property
    def bss_size(self) -> int:
        """How many zero-filled bytes the segment's memsz reaches above its base."""
        return self.bss_end - self.bss_vram

    @property
    def sections(self) -> tuple:
        """``((".debug", offset, size), (".line", offset, size))``: the chunked sections.

        The chunk manifests' offsets are relative to these, so this is the one place the two
        views of the file are joined.
        """
        return tuple((f".{name}", *self.trailing_of(name)) for name in ("debug", "line"))

    def trailing_of(self, name: str) -> tuple:
        """``(file offset, size)`` of the trailing section ``name``."""
        for entry_name, offset, size in self.trailing:
            if entry_name == name:
                return offset, size
        raise KeyError(name)

    def address_of(self, file_offset: int) -> int:
        """The virtual address a byte of the loadable image has."""
        return self.loadable_vram + file_offset - self.loadable_rom

    def offset_of(self, address: int) -> int:
        """The file offset of a loadable-image virtual address (the inverse of `address_of`)."""
        return self.loadable_rom + address - self.loadable_vram


@dataclasses.dataclass(frozen=True)
class Target:
    """One decompilation target: the binary, the image, their pins, and where its config is.

    ``geometry`` is that target's measured file/disc layout, or None until somebody measures it
    (:meth:`geometry_required`).  ``tu_builds`` is
    ``((source, compiler build, flags), ...)``: the compiler/flag pair
    ``tools/toolchain/select_build.py`` *measured* as reproducing a promoted unit's retail
    ``.text`` bytes.  Promotion is always adoption: ``.text`` byte equality is the proof,
    and ``compile.py --adopt-retail-meta`` reconstructs ``.line``/``.debug`` from retail's
    inventory, accepting only when the whole ``.debug`` chunk is retail's bytes.  It is per
    target because a pair measured against one retail binary says nothing about another, so a
    new target starts with an empty table and ``configure.py`` refuses to promote a source
    nobody has measured for *it*.

    ``include_dirs`` is the repo-relative search path the C units are compiled with, in
    order: where the oracle writes the generated headers this target's sources include.  It
    is a fact of the target because the headers are rendered from *its* DWARF; the driver
    that hands them to the compiler spells the paths, so nothing else has to know them.
    """

    name: str
    config_dir: pathlib.Path
    elf: pathlib.Path
    elf_sha256: str
    image: pathlib.Path
    image_sha256: str
    geometry: "Geometry | None" = None
    tu_builds: tuple = ()
    include_dirs: tuple = ("include",)

    def __post_init__(self):
        if not isinstance(self.name, str) or not _NAME.fullmatch(self.name):
            raise ValueError(f"target name {self.name!r} is not a lowercase identifier: it "
                             f"names both this descriptor and config/<name>/")
        for field in ("config_dir", "elf", "image"):
            object.__setattr__(self, field, pathlib.Path(getattr(self, field)))
        expected = REPO_ROOT / "config" / self.name
        if self.config_dir != expected:
            raise ValueError(
                f"target {self.name}: config_dir is {self.config_dir}, but a target's config "
                f"lives in config/<name>/ ({expected}): a descriptor pointing at another "
                f"target's config is a retarget that has half landed")
        for field, label in (("elf", "retail ELF"), ("image", "disc image")):
            if not getattr(self, field).name:
                raise ValueError(f"target {self.name}: {field} names no {label}")
        for field, label in (("elf_sha256", "G1"), ("image_sha256", "G3")):
            value = getattr(self, field)
            if not isinstance(value, str) or not _SHA256.fullmatch(value):
                raise ValueError(
                    f"target {self.name}: {field} is {value!r}, not a sha256 digest: the "
                    f"{label} pin is what makes the gate a gate")
        if self.geometry is not None and not isinstance(self.geometry, Geometry):
            raise ValueError(f"target {self.name}: geometry is {self.geometry!r}, not a "
                             f"Geometry (or None, for a target nobody has measured yet)")
        seen = set()
        for entry in self.tu_builds:
            if not (isinstance(entry, tuple) and len(entry) == 3
                    and all(isinstance(part, str) and part for part in entry)):
                raise ValueError(
                    f"target {self.name}: tu_builds entry {entry!r} is not "
                    f"(source, compiler build, flags): promotion is always adoption "
                    f"(--adopt-retail-meta, `.text` byte equality is the proof), so a row "
                    f"has three elements -- drop the state from a four-element row")
            if entry[0] in seen:
                raise ValueError(f"target {self.name}: tu_builds names {entry[0]!r} twice")
            seen.add(entry[0])
        object.__setattr__(self, "tu_builds", tuple(self.tu_builds))
        for entry in self.include_dirs:
            if not (isinstance(entry, str) and entry
                    and not pathlib.PurePosixPath(entry).is_absolute()):
                raise ValueError(
                    f"target {self.name}: include_dirs entry {entry!r} is not a repo-relative "
                    f"directory: a target's include path is spelled from the repository root, "
                    f"so the descriptors of two checkouts of the same tree name the same "
                    f"headers")

    # -- paths, all inside the target's own config dir -----------------------

    @property
    def checksums(self) -> pathlib.Path:
        """The gate manifest: ``<sha256>  <path>`` per binary and image this target pins."""
        return self.config_dir / "checksums.txt"

    @property
    def cus(self) -> pathlib.Path:
        """The oracle's compile-unit map."""
        return self.config_dir / "cus.json"

    @property
    def chunks(self) -> pathlib.Path:
        """The oracle's debug chunk manifest."""
        return self.config_dir / "debug_chunks.json"

    @property
    def symbols(self) -> pathlib.Path:
        """The oracle's symbol ledger."""
        return self.config_dir / "symbol_addrs.txt"

    @property
    def ghidra(self) -> pathlib.Path:
        """The target's Ghidra function list, if it has one."""
        return self.config_dir / "ghidra_functions.json"

    @property
    def borrowed(self) -> pathlib.Path:
        """The borrowed library-name ledger the oracle merges into the symbol ledger."""
        return self.config_dir / "borrowed_symbols.txt"

    @property
    def unplaced(self) -> pathlib.Path:
        """Symbols the oracle found but could not place."""
        return self.config_dir / "unplaced_symbols.txt"

    @property
    def splat_symbols(self) -> pathlib.Path:
        """``symbols`` in the syntax splat parses (generated, gitignored)."""
        return self.config_dir / "splat_symbol_addrs.txt"

    @property
    def undefined_funcs(self) -> pathlib.Path:
        """splat's own undefined-function file (generated, gitignored)."""
        return self.config_dir / "undefined_funcs_auto.txt"

    @property
    def undefined_syms(self) -> pathlib.Path:
        """splat's own undefined-symbol file (generated, gitignored)."""
        return self.config_dir / "undefined_syms_auto.txt"

    @property
    def built(self) -> pathlib.Path:
        """The linked image under ``out/``: the target's own ELF name, never a fixed one."""
        return REPO_ROOT / "out" / self.elf.name

    @property
    def ld_script(self) -> pathlib.Path:
        """The pinned linker script ``configure.py`` generates for this target."""
        return REPO_ROOT / "build" / f"{self.elf.name}.ld"

    # -- the include search path, spelled from the repository root -----------

    @property
    def include_paths(self) -> tuple:
        """The directories the C units include from: ``include_dirs``, repo-relative no more.

        The descriptor stores them repo-relative so a diff reads them the way a reader types
        them (see ``include_dirs``); every caller wants a path, so the join happens here and
        once.
        """
        return tuple(REPO_ROOT / entry for entry in self.include_dirs)

    def geometry_required(self) -> Geometry:
        """The measured geometry, or a loud stop naming what has to be measured."""
        if self.geometry is None:
            raise NotMeasured(
                f"target {self.name} ({self.elf.name}) has no measured geometry yet: its "
                f"segment list, file layout and disc-image offset are measured from "
                f"{_display(self.elf)} once that binary is placed and split (the retarget "
                f"plan's Tasks 4-6 generate its config), and until then this target cannot "
                f"be configured -- another target's numbers would produce a plausible wrong "
                f"image")
        return self.geometry

    def build_pair(self, source: str):
        """``(compiler build, flags)`` measured for ``source``, or None."""
        for file, version, flags in self.tu_builds:
            if file == source:
                return version, flags
        return None

    def build_table(self) -> dict:
        """``tu_builds`` as ``{source: (compiler build, flags)}``, for ``configure.py``."""
        return {file: (version, flags) for file, version, flags in self.tu_builds}


class Registry:
    """The targets this tree can build for, by name, with one of them as the default.

    It is data, not code: :meth:`add` is the whole of "support another target", and no tool
    needs to know which names exist.  The default is a name, and :meth:`get` with no name (or
    with the default's) returns that target -- so a tool that never sees ``--target`` works on
    the target this tree is configured for, while a name nothing defines raises
    :class:`UnknownTarget` instead of quietly doing the same thing.
    """

    def __init__(self, *targets: Target, default: str | None = None):
        self._targets: dict = {}
        for target in targets:
            self.add(target)
        if not self._targets:
            raise ValueError("a registry needs at least one target")
        if default is None:
            default = next(iter(self._targets))
        if default not in self._targets:
            raise ValueError(f"the registry's default {default!r} is not one of its targets: "
                             + ", ".join(self.names()))
        self._default = default

    @property
    def default(self) -> str:
        """The name every tool uses when no ``--target`` is given."""
        return self._default

    def add(self, target: Target) -> Target:
        """Register ``target``; returns it, so the registry line reads as one expression."""
        if not isinstance(target, Target):
            raise TypeError(f"{target!r} is not a Target: a registry holds descriptors")
        if target.name in self._targets:
            raise ValueError(
                f"a target named {target.name!r} is already registered: two descriptors for "
                f"one name would make every path ambiguous")
        self._targets[target.name] = target
        return target

    def names(self) -> tuple:
        """Every registered target's name, in registration order."""
        return tuple(self._targets)

    def get(self, name: str | None = None) -> Target:
        """The target ``name``, or the default one when no name is given."""
        if name is None or name == "":
            name = self._default
        try:
            return self._targets[name]
        except KeyError:
            raise UnknownTarget(
                f"no target named {name!r}: this tree knows " + ", ".join(self.names())) \
                from None


def _display(path) -> str:
    """A path as a reader types it: repo-relative when it is inside the repo."""
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


# ---------------------------------------------------------------------------
# the targets
# ---------------------------------------------------------------------------

#: The target this tree is built for: the *DDR Extreme 2 (US)* preview template
#: (``SLUS_211.74``), whose DWARF covers 249 translation units.  ``orig/SLUS_211.74`` is
#: gitignored like every retail binary; ``config/ddrex2p/`` holds its manifests and pins.
#:
#: Its ``geometry`` is a measurement of that binary -- read out of its headers with
#: ``tools/oracle/elf.py`` and confirmed byte-for-byte against the image it is booted from
#: (every number below is annotated with where it comes from).  ``tu_builds`` records one
#: uniform pair for both units whose C is believed correct (``sys_scf.c`` and ``net_grf.c``),
#: measured 2026-10-19 through the promotion path over all five installed builds × both
#: recorded flag strings: ``3.0-011126 -c -lang c -O3 -opt full -g`` reproduces both byte for
#: byte on ``.text``/``.debug``/``.line`` (0x40/652/116 and 0xc0/1592/156 bytes).  ``-opt
#: full`` is not a per-file exception: it is compatible with the code that already matched,
#: so one compiler and one flag set explain every believed-correct unit.  The pair recorded
#: now is ``3.0b38-030307 -c -lang c -O3 -opt full -g``, with the ``.debug`` DIE-order
#: normaliser that adoption applies for ``net_grf``: b38 takes both units'
#: ``.text``/``.line`` byte-exactly, ``sys_scf``'s ``.debug`` is byte-equal outright (the
#: normaliser is inert), and ``net_grf``'s chunk -- the same DIE set in b38's order -- is
#: rewritten into retail's DIE order and comes out byte-identical (41 DIEs, 31 moved, 8
#: references rewritten).  All five promoted units' layouts are now tidied, which moves
#: their statement lines, so promotion is always adoption and ``--adopt-retail-meta``
#: supplies retail's ``.line`` (and applies the normaliser itself where a chunk needs it).
#: b38 writes ``(3.0.0)`` in ``.comment`` where retail writes ``(2.4.1.01)``; that string and
#: the chunk order never reach the image (whose ``.comment`` and chunks are retail's), so the
#: pair is a reproduction recipe, not a claim that b38 is the original compiler.
#: ``2.4-001213`` is ruled out by its frame instructions (``sq``/``lq`` where retail has
#: ``sd``/``ld``) and by ``net_grf``'s short ``.line``.
#: A pair measured against one retail binary says nothing about another, so this table starts
#: empty on a new target and ``configure.py`` refuses to promote a source nobody has measured.
#: A guessed *geometry* would be a split of one game at another game's addresses;
#: ``geometry_required()`` is what refuses to guess, and `tests/test_targets.py` pins both
#: halves of that behaviour.
DDREX2P = Target(
    name="ddrex2p",
    config_dir=REPO_ROOT / "config" / "ddrex2p",
    elf=REPO_ROOT / "orig" / "SLUS_211.74",
    elf_sha256="ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd",
    image=pathlib.Path(
        "$HOME/Downloads/Dance Dance Revolution Extreme 2 (May 10, 2005 "
        "prototype)/PS2 - Dance Dance Revolution Extreme 2 PS2 Preview Code 6-22-05.iso"),
    image_sha256="70a9056657665e978c7de9fc223cb753956902416418993176438316f6cd652b",
    # Measured from `orig/SLUS_211.74` (sha256 ef31c90f…c02cd, 7,725,036 B) and from the
    # pinned image it was copied out of: the ELF header, the program headers and the section
    # header table, plus that image's own bytes (the boot ELF sits at LBA 894146, and the
    # image's 7,725,036 bytes there are the ELF byte for byte, so a rebuilt ELF spliced back
    # in at that offset is the whole of G3).
    #
    # `bss_end` is the file-backed PT_LOAD's `vaddr + memsz` (0x100000 + 0x623700): the
    # zero-filled tail that segment claims.  It is *not* the highest address any PT_LOAD
    # claims -- the binary also reserves eleven disjoint zero-fill regions for the overlay
    # blobs (`0x7F0000`, `0xE4D380`, `0x1884000`, `filesz` 0, together reaching 0x1995E00) --
    # because one bss extent spanning 0x723700..0x1995E00 would claim the unmapped gaps
    # between those reservations as addressable, and `Geometry` has no way to express several
    # disjoint zero-fill regions.  The overlays are out of this milestone's scope anyway (the
    # spec defers DATA00-09.BIN), so this is recorded as *not represented* rather than
    # guessed; see the Task 4 report.
    geometry=Geometry(
        elf_size=0x75DFEC,          # .reginfo ends at 0x75DCCC, then 20 * 40 B section headers
        loadable_rom=0x200,         # PT_LOAD 0's p_offset
        loadable_end=0x1DE380,      # 0x200 + p_filesz 0x1DE180: the whole file-backed image
        loadable_vram=0x100000,     # PT_LOAD 0's p_vaddr
        bss_end=0x723700,           # PT_LOAD 0's p_vaddr + p_memsz
        trailing=(                  # the sections after the loadable image, in file order
            ("shstrtab", 0x1DE380, 0x3A),
            ("debug", 0x1DE3C0, 0x491376),
            ("line", 0x66F740, 0xEE546),
            ("comment", 0x75DC86, 0x2B),
            ("reginfo", 0x75DCB4, 0x18),
            ("section_headers", 0x75DCCC, 0x320),
        ),
        debug_size=0x491376,        # .debug (4,789,110 B, matching the spec's table)
        line_size=0xEE546,          # .line (976,198 B)
        image_elf_offset=0x6D261000,  # LBA 894146 in the pinned image
    ),
    # (source, compiler build, flags): measured, never inherited -- see the note above.
    # Promotion is always adoption: `.text` byte equality is the proof, and
    # `--adopt-retail-meta` reconstructs `.line`/`.debug` from retail's inventory.
    #
    # A unit accepted under the anonymous-type DIE-order boundary (`docs/unit-work.md`,
    # "The one recorded `.debug` deviation") must say so in a comment on its row, quoting
    # the line `compile.py` prints: `.debug set-equal, not byte-equal (anonymous-type DIE
    # order: N of M @anonN indices permuted)`.  The gate re-measures the chunks on every
    # build, and the comment is the record that a human made the promotion decision.  No
    # unit is accepted this way yet.
    #
    # The row's comment quotes the adoption report -- the number of `.line` rows changed, or
    # that the emitted table is not row-for-row comparable and is adopted whole, and every
    # adopted `local: before -> after` -- because the report is what says *what* was
    # adopted; the step itself refuses unless the whole `.debug` chunk comes out retail's
    # bytes.
    #
    # Measured 2026-10-19 through the promotion path (`place()` + `compare()`), all five
    # installed builds x both recorded flag strings: `sys_scf.c` and `net_grf.c` are both
    # byte-equal on `.text`, `.debug` and `.line` under `3.0-011126 -c -lang c -O3 -opt
    # full -g` (and under `3.0.1-020123`/`3.0.3-020716` x both flag strings); that pair
    # reproduces both without the normaliser.  The pair recorded now is `3.0b38-030307 -c
    # -lang c -O3 -opt full -g`: `.text`/`.line` byte-equal for both (0x40/116 and
    # 0xc0/156 bytes), `sys_scf`'s `.debug` byte-equal (652 bytes, normaliser inert), and
    # `net_grf`'s 1592-byte chunk normalised from b38's DIE order into retail's (41 DIEs,
    # 31 moved, 8 references rewritten) and byte-identical.
    #
    # `p_anime.c` measured 2026-10-20 under `3.0b38-030307 -c -lang c -O3 -opt full -g`:
    # all five bodies word-exact (0x950 bytes), and `.debug` the same 0x4273 bytes / 414
    # DIEs.  Before the source's `#line` layout was normalised, the report named 10
    # statement lines that moved (first at `.line+0x45A`: 115 -> 114; 35 of 244 rows
    # byte-different); after normalisation the emitted `.line` carries 4 more records than
    # retail's and the tables are not row-comparable, so retail's chunk is adopted whole.
    # `--adopt-retail-meta` also adopts `n`'s location in both large functions -- the
    # emitted `AT_location` is MW's `scratch` (DW_OP_reg2), retail's is `$a2`
    # (DW_OP_reg6) -- plus 4 anonymous names and 15 reference words between structurally
    # identical DIEs; the chunk then equals retail's byte for byte.
    #
    # `dmm_chara.c` measured 2026-10-20 under the same pair: `.text` and `.line` are
    # byte-equal (0x1D0 / 0x152).  `.debug` is 0x16A against retail's 0x151 because the
    # block-scoped temp adds one local record (`dmm_t`, local_variable at +0x64C6, 0x21
    # bytes) and the function DIE lacks retail's 0x2303 access-reference list.  Adoption
    # drops the extra record, adopts the missing 0x2303 attribute, 24 anonymous names and
    # 142 reference words; `.debug` becomes retail's 0x64DA bytes / 666 DIEs.  A *missing*
    # record would refuse -- fabricating a DIE retail has is invention, not adoption.
    tu_builds=(
        # The layout is tidied (blank runs collapsed to one, header dropped), so its
        # statement lines moved and `.line` is adopted.  Under this pair `.text` is
        # retail's 0x40 bytes and `.debug` its 0x28C bytes outright; adoption has
        # only `.line` to substitute.
        # .text 0x540 word-exact; .debug retail's 0x955 / 63 DIEs after adoption (anon names and
        # references rewritten); .line adopted whole (81 records).  Operand order is
        # (h - 4) * c_now, y + 2 + bar_y [+ bar_h]; `z > 0xFEFF`; and the dw_h clamp is
        # `sa = (sa > 0) ? sa : 0; dw_h = bar_h - sa;`, which keeps the register split.
        ("src/common/com_scrollbar.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        ("src/sys/sys_scf.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # Layout tidied, so `.line` is adopted.  Adoption applies the DIE-order normaliser
        # internally (41 DIEs, 31 moved, 8 references) and proves the chunk retail's 0x638
        # bytes.
        ("src/network/net_grf.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # Layout tidied; `.line` adopted.  The emitted table keeps retail's 244
        # records in its 5 tables (104 + 2 + 123 + 12 + 3), so the grouping the old
        # `#line` layout encoded survived the tidy.
        ("src/AM/s573/play/p_anime.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # Layout tidied; `.line` adopted (33 records in one table, retail's).
        ("src/CS/dancemaster/dmm_chara.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # Layout tidied; `.line` adopted (7 records, retail's).
        ("src/CS/lang.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # Layout tidied; `.line` adopted (9 rows, 0x62 table); `.debug` byte-equal outright.
        ("src/CS/edit_lib/el_mes.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x860 of eleven bodies word-exact; .debug retail's 0x148B / 112 DIEs; .line adopted.
        # The header walks keep `size = header->size` and the found pointer assigned inside the loop.
        ("src/CS/edit/ed_ssq_func.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xB70 of four bodies word-exact; .debug/.line adopted.  Needs
        # -sdatathreshold 4 (5-byte literals stay out of .sdata, edw stays gp-relative); the
        # two literals are placed; disp reuses dx as the 38.0f operand (rx + dx - 3.0f).
        ("src/CS/edit/ed_edit_disp.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 4"),
        # .text 0xB00 of eleven bodies word-exact; .debug/.line adopted; three data placements
        # (next_tab, the title literal, the switch table).  menu_icon_set is a static inline.
        ("src/CS/edit/ed_menu.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x350 with all three bodies word-exact; adoption supplies temp's AT_location
        # ($t1 -> $t7 / $t6) and 8 reference words.  ORIG_P/ORIG_S must be initialised
        # file-scope statics: only then does this build tag them local_variable.
        ("src/network/mio/blowfish.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x141C of four bodies word-exact; .debug retail's 0x82D / 42 DIEs after
        # adoption; .line adopted whole.  Encode/Decode/MD5_memset are `static inline`
        # helpers (no DIE of their own); MD5_memset((char *)x, 0, sizeof(x)) after the
        # state adds is the 21-word tail and the 0x10 of frame.  MD5_memcpy is a call.
        ("src/network/mio/md5.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x80, both bodies word-exact; .debug retail's 0x2C9 / 13 DIEs outright;
        # .line adopted (2 tables / 16 rows, sizes and offsets already retail's).
        ("src/CS/bk_load.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x130, three bodies word-exact; .line (27 rows) and the TU-level DIE order
        # adopted; .debug retail's after adoption.  tblMusicData must be initialised.
        ("src/music_all.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x1E0, three bodies word-exact; .line adopted after the tidy (35 of 38 rows);
        # .debug retail's 0x8B8 / 50 DIEs after 25 reference words (array-type order).
        ("src/CS/train/tra_str.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x4F0, all three bodies word-exact; .line adopted (emitted 143 records,
        # adopted 148); .debug retail's 0x846 / 50 DIEs after 34 ref words and d5's location.
        ("src/sound/vxdecode/decode.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x58, three bodies word-exact; .line grouping already retail's (11 records,
        # 3 tables; 8 numbers moved); .debug 0xB90 / 64 DIEs after 26 ref words and
        # warning0/warning1 locations.
        ("src/network/net_cnf/net_cnf_mes_e.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x58, three bodies word-exact; .line adopted (11 records / 3 tables, 8 numbers
        # moved); .debug 0xFC9 / 90 DIEs after AUTH_RUN/AUTH_OK locations and 68 ref words.
        ("src/network/net_auth/net_auth_mes_e.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        ("src/network/net_dnas/net_dnas_mes_e.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x480 (0x43C + 0x38), both bodies word-exact.  The five corner values live in
        # a static inline helper, so they never reach DWARF; .line adopted whole (37 vs 93 rows);
        # .debug 0xC62 / 80 DIEs after 3 type-reference words.
        ("src/common/co_cursor.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xE0, four bodies word-exact; .line adopted (19 records, 15 rows moved);
        # .debug retail's 0x125E / 125 DIEs after 31 reference words (0x72, 0x83, 0xA3).
        ("src/network/net_window/net_win_infoboard.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x208 (520 bytes), all five bodies word-exact.  .debug is retail's 0x1435
        # bytes / 134 DIEs byte for byte after adoption, including the form-3
        # AT_subscr_data element references (3 rewritten); .line (5 chunks, 540 bytes) and
        # AT_location adopted under --adopt-retail-meta.
        ("src/network/net_window/net_win_any.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xF0, four bodies word-exact; .line exact before the tidy and adopted after;
        # .debug 0x3A7B / 368 DIEs set-equal (5 of 6 anon indices), adopted after 4 ref words.
        # Needs the `_pairs` fix (ddde799): the flag field sits at a non-zero offset.
        ("src/CS/ani_load.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x480, both bodies word-exact; .line exact before the tidy, adopted after (144
        # records, 142 rows); .debug retail's 0xD78 / 87 DIEs after 16 reference words.
        ("src/common/co_button.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x480 (0x474 + 0xC nop padding), all five bodies word-exact.  .line adopted
        # whole (emitted 141 records, adopted 131: table 1 holds 20 rows against retail's
        # 13); 20 anonymous names and 75 reference words adopted.  .debug is retail's
        # 0x2E67 bytes / 321 DIEs byte for byte after the normaliser moved 266 records: the
        # array types are keyed by their subscript data, so [3][65536], [3][45568] and
        # [3][86784] pair by nested bound instead of cyclically.
        ("src/AM/s573/doll/model1.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x2B0, four bodies word-exact; .line byte-equal before the tidy, adopted after
        # (68 records, 4 tables); .debug retail's 0x10D9 / 108 DIEs after 2 anon names and 18
        # refs.  Two .bss statics keep {0} (above 0x2DE180) and are why both are local_variable.
        ("src/CS/opening/openinglogo.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xE50, eight bodies word-exact; .line byte-equal outright (8 tables, 26/16/
        # 9/7/8/15/15/218 records); .debug retail's 0x234E / 242 DIEs after adoption.
        # Function order must be retail's DIE order; a dead `int i = 0;` creates i's vreg
        # first and fixes the spill slots without touching .text.  The error string is the
        # pooled literal @33 at 0x2D3CE0, not an extern (a global_variable DIE costs too).
        ("src/common/cws/cws_obj.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x1300, 17 bodies word-exact; .debug retail's 0x21FC / 211 DIEs and .line adopted.
        # Needs the two jump tables (@179, @317) and the error string (@500) placed.  Chained
        # stores run v then s (`v.x = s.x = x`); CwsWinCreate returns from inside its loop.
        ("src/common/cws/cws_win.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x970, 15 bodies word-exact; .debug and .line adopted.  `-inline deferred` gives
        # retail's reversed emission order, `level=8` folds gs3dSetRenderMatrix into the unit
        # matrix setter.  dist3d is `asm {}` in a C function under `.set noreorder` (10 words).
        ("src/gs/gs_3d.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -inline auto,level=8,deferred"),
        # .text 0x2A8, three bodies word-exact; .line and .debug adopted.  Nine statics (seven
        # tables in the 0x2BF2C8 band, three one-string tables in sdata) need placements.
        ("src/network/net_auth/net_auth_errmes_e.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x810, six bodies word-exact; .debug retail's 0x8111 / 835 DIEs byte-equal
        # after adoption; .line adopted whole (161 records vs retail's 154).  Needs @87
        # ("eye stat %d"), which sits in the last code split.  ti_cnt needs `= 0` to stay a
        # local_variable; address literals must be casts, since an extern declaration costs
        # a global_variable DIE plus an array_type.  `(x & 0x20) ? 1 : 0` for sltu.
        ("src/CS/bk_disp/bk_disp.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x11E8, ten bodies word-exact; .line 0x100E and .debug 0x2A91 / 265 DIEs
        # adopted byte-equal.  Needs @420 and seven statics.  BoardDisp assigns dx/dy/dz
        # inside BOTH arms of the master_link branch -- that duplicated tail is retail's;
        # its plate guard is `ptex_obj > 1` (slti $1).  LineDisp shares one block for
        # cases 0 and 1; `nm_page == 0 ? i : i + 5` puts the index in the delay slot.
        ("src/network/net_window/net_win_rccssel.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xDE0 (0x24C + 0x2D4 + 0x300 + 0x5AC), four bodies word-exact; .line adopted
        # (2782 bytes); .debug retail's 0x6052 / 635 DIEs after adoption.  pad_type is one
        # 62-instruction line whose `= 1` test and `? -1 : 0` arm are load-bearing; init's
        # `if (code == -1) return;` must be a return, not a block (also fixes code's
        # AT_location); the `switch (step_s)` lists case 3 before case 2.
        ("src/CS/train/tra_msel.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x1D8 in a 0x1E0 extent, eleven bodies word-exact; .line adopted whole;
        # .debug retail's 0x13ED / 112 DIEs after adoption (63 sibling words, 45 refs).
        # Twenty statics are placed (65 rows incl. 45 @N strings); six are unallocated in
        # retail (DW_AT_location 0) and stay bare declarations.  chara_data_name/mot_data_name
        # point into bk_tm2_records at 0x98+8i and 0x58+8i.
        ("src/AM/s573/doll/ddata.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x758 in a 0x760 extent, six bodies word-exact; .debug retail's 0x5E9D / 623
        # DIEs after adoption (one array_type dropped, 199 sibling/reference rewrites);
        # .line 0x5C6 adopted whole.  Never -sdatathreshold 0 here: it turns every gp access
        # into lui/lw.  cam_p needs 16-byte alignment, which the header emitter now states.
        ("src/CS/freeplay/fp_qmenu.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        ("src/CS/freeplay/fp_eyetoy.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xBB0, eleven bodies word-exact; .debug retail's 0x998A byte-equal after
        # adoption, .line adopted.  The unit declares its own anonymous types: every float[4]
        # member is the one shared FVEC4 node (and [3][4] / [2][4] are arrays of it), cam_p
        # needs 16-byte alignment in both gs3d and the doll work, and the local data tables
        # (@N) are the init templates for set_pos / fpanel_update / disp.
        ("src/CS/freeplay/fp_doll.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x238, nine bodies word-exact; .debug retail's 0x419B / 413 DIEs after
        # adoption, which drops get_table_no_by_infotxt_num's two locals (retail's CU has
        # none) and recomputes 392 AT_sibling words.  The dancer table needs
        # (int)(num - 202); the bounds compares are sizeof(tbl)/sizeof(tbl[0]) for sltiu.
        ("src/CS/info_data.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xEB4, five bodies word-exact; .debug retail's 0x1FE8 / 211 DIEs byte-equal
        # after adoption (9 anon names, 37 refs, rtv_sel's location); .line 0xBE0 adopted
        # (309 records vs retail's 300).  Needs -sdatathreshold 0 and five placements.
        # The two dy frame tests are spelled asymmetrically: `< -0x3B ? 4 : 0x14` but
        # `>= 0x3C ? 4 : 0x14`; the dy branch's set_frame must be if/else (a ternary drops
        # its local DIE).  ctrl's dispatch is `if (dx == 0 && dy == 0) … else …`.
        ("src/CS/shop/shop_select.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x560, four bodies word-exact.  case 0 binds shop_get_work() through an int
        # cast rather than a declared temp (a temp adds a third local DIE); disp regained
        # retail's sixth local ofsx.  Needs the @31 jump table.
        ("src/CS/shop/shop_info.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x260, six bodies word-exact; .debug retail's 0x46BF byte-equal after adoption,
        # .line 0x27E adopted.  step0 is dmm_main.c's name too: the oracle numbers this one
        # step0_1, so config/ddrex2p/unit_symbols.txt gives it 0x002DE560 for this source.
        # The 0x2303 ref order forces `step0 = 0` before the sb pair, inside a block local.
        ("src/CS/shop/shop_main.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x350, both bodies word-exact; .line byte-equal pre-tidy (56+20 rows) and
        # adopted after; .debug retail's 0x78DD / 785 DIEs (24 of 25 anon indices permuted).
        # 0x6B2F58 is g_game_w.last_data_addr, a member access, not a literal.
        ("src/CS/shop/shop_init.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x358 in a 0x360 extent, eight bodies word-exact; .line 0x252 adopted
        # (53 records, 38 of 53 rows differ); .debug retail's 0x1B6D / 173 DIEs after 39
        # reference words.  Needs -sdatathreshold 0 and ten placements.  SetPoint is two
        # separate identical "%04d" blocks, not a shared fall-through.
        ("src/network/net_window/net_win_dhead.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x398 in a 0x3A0 extent, eight bodies word-exact; .line 0x270 adopted
        # (the type include and an unreferenced-aggregate helper add two lines retail lacks);
        # .debug retail's 0x1B80 / 173 DIEs after adoption.  Needs -sdatathreshold 0 and
        # twelve placements.  Retail carries a whole unreferenced _nsv_player_list_file.
        ("src/network/net_window/net_win_dpoint.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x928 in a 0x930 extent, eight bodies word-exact; .line 0x5FE adopted whole
        # (148 records against retail's 147); .debug retail's 0x2804 / 253 DIEs byte-equal
        # after adoption.  Needs -sdatathreshold 0 and fifteen placements.  Main's second
        # dispatch level tests entry_flag, and the dancer cell stride is (num % 8) * 42.
        ("src/network/net_window/net_win_suser.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x920 in a 0x928 extent, six bodies word-exact; .line 0x5D0 adopted; .debug retail's
        # 0x28E0 / 269 DIEs byte-equal after adoption.  Needs -sdatathreshold 0 and thirteen
        # placements.  BoardDisp's else arm needs scratch `mx = m.x + w.x; dx = mx + o.x` (x, y, z;
        # the extra locals are dropped by adoption, and they shift the pool numbers to @148..@150, @194).
        ("src/network/net_window/net_win_user.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x458 in a 0x460 extent, ten bodies word-exact; .line 0x406 adopted whole
        # (91 records against retail's 95); .debug retail's 0x1C7A / 177 DIEs byte-equal
        # after adoption.  Needs -sdatathreshold 0 and twelve placements.  CwsObjMove
        # returns int: a char prototype adds dsll32/dsra32 to Main's != 0 test.
        ("src/network/net_window/net_win_rcname.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x470 in a 0x470 extent, seven bodies word-exact; .line 0x3BC adopted
        # (83 of 90 rows moved by statement line); .debug retail's 0x1BC4 / 175 DIEs byte
        # for byte after adoption.  Main's dispatch source case order is 2,3,1 -- that is
        # what makes MWCC emit retail's compare chain 1,3,2 with blocks 2,3,1,default.
        # .text 0x490 in a 0x490 extent, six bodies word-exact; .line and .debug (0x19DA / 173
        # DIEs) adopted, layout tidied.  Needs -sdatathreshold 0 and six placements.  BoardDisp's
        # else arm needs a scratch `mx = m.x + w.x; dx = mx + o.x` (the extra locals are dropped
        # by adoption); without it the final add operands come out swapped.
        ("src/network/net_window/net_win_base.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        ("src/network/net_window/net_win_listsel.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x460 in a 0x460 extent, eight bodies word-exact; .line 0x31A and .debug
        # 0x1A12 / 162 DIEs adopted (.debug byte-equal).  Needs -sdatathreshold 0 and twelve
        # placements.  Local names are forced by the DIE comparison: winw, and rtn in Slby.
        ("src/network/net_window/net_win_slby.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x198 in a 0x1A0 extent, nine bodies word-exact; .debug retail's 0x1988 /
        # 168 DIEs byte-equal after adoption.  The layout emits all 42 .line records on
        # retail's lines; 1 row differs in position, so retail's .line 0x1EC is adopted.
        # Needs -sdatathreshold 0.  Its three statics verify but cannot be placed until
        # plan_data keeps a dlabel/enddlabel pair together (D_002BF02A spans the cut).
        ("src/network/net_window/net_win_bar.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x3B8 in a 0x3C0 extent, eight bodies word-exact; .text AND .line
        # byte-equal outright, so --normalise-debug alone makes .debug retail's 0x1817 /
        # 152 DIEs.  Needs -sdatathreshold 0 and six static placements.  `_point` is a
        # vararg in the "%06d"/"%08d" cases, which puts it in $a3 at entry.
        ("src/network/net_window/net_win_infosel.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x778, six bodies word-exact; .text AND .line byte-equal outright, so
        # --normalise-debug alone makes .debug retail's 0x1969 / 161 DIEs.  No
        # placements; the setters hold retail's emission-free lines with a trailing `return;`.
        ("src/network/net_window/net_win_item.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0xC30 in a 0xC34 extent, seven bodies word-exact; .line 0x998 and .debug
        # 0x4DFC / 496 DIEs adopted.  Needs the @13 jump-table placement (0x002D6860).
        # Adopted whole: retail blanks eight lines before each closing brace.
        ("src/CS/shop/shop_list.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x770, seven bodies word-exact; .line 0x5B0 byte-equal outright, so
        # --normalise-debug alone makes .debug retail's 0x179F / 153 DIEs.  Blank lines
        # are retail's statement positions; never --collapse, and brace-adjacent blanks stay.
        ("src/common/cws/cws_wins.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x6E8, eight bodies word-exact; .line 0x59A and .debug 0xDAA / 77 DIEs
        # adopted (six colouring intermediates, GsInitCoordinate2's `i` and a duplicate
        # array_type dropped, with the reference retargeted to the surviving twin).
        ("src/AM/s573/doll/ps1lib.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x300, five bodies word-exact; .text, .line 0x1F4 and .debug 0x6D4 / 33 DIEs
        # are retail's outright.  The Create bodies need their matrix
        # prototypes spelled through a typedef: five `float (*)[4]` declarators emit five
        # array_type DIEs (0x90 over).  Line-bearing layout; never --collapse.
        ("src/AM/s573/doll/matrix.c", "3.0b38-030307", "-c -lang c -O3 -g"),
        # .text 0x7A0, five bodies word-exact; .line 0x348 byte-equal (blank-line padding,
        # no directives); .debug retail's 0x18DB / 160 DIEs via --normalise-debug.  Needs
        # the five @40..@44 placements; per-source preference resolves the shared names.
        ("src/network/net_window/net_win_listdtl3.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x2D0, six bodies word-exact; .text and .line byte-equal outright, so
        # --normalise-debug alone makes .debug retail's 0x16BD / 147 DIEs.  Needs the
        # @62 jump-table placement in data_placements.txt.  The two `[3]` array DIEs behind
        # netwinmenu_plate_board_off/_on are structurally identical; the normaliser pairs
        # them by the local that names each (2026-10-21), which is what makes the chunk
        # byte-identical instead of swapping the two references.
        ("src/network/net_window/net_win_menu.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x3B8 in a 0x3C0 extent, six bodies word-exact; .text AND .line byte-equal
        # outright, so --normalise-debug alone makes .debug retail's
        # 0x164D / 146 DIEs.  Layout keeps retail's blank gaps on purpose; never --collapse.
        ("src/network/net_window/net_win_watch.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x3F8 in a 0x400 extent, all seven bodies word-exact; .line adopted whole
        # (7 chunks; TabSetOff's ten straight-line masks alternate two lines); .debug retail's
        # 0x1E4B / 200 DIEs after 55 type refs and every AT_location.
        ("src/network/net_window/net_win_tab.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x4F0, three bodies word-exact; .line 91 records adopted (83 rows moved);
        # .debug retail's 0x46EF / 485 DIEs after 1 location, 21 names and 99 refs.
        ("src/CS/dancemaster/dmm_mess.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        # .text 0x3A0, five bodies word-exact; .line adopted whole (5 tables, 5 chunks), as
        # is .debug (retail's 0x12E7 / 136 DIEs).  `-sdatathreshold 0` keeps the "%05d" and
        # "%08d" literals in .data sections of their own instead of a shared 8-byte pool, so
        # each is placed at its retail slot (`@40`/`@41` in data_placements.txt).
        ("src/network/net_window/net_win_listdtl2.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g -sdatathreshold 0"),
        # .text 0x1D0 (two bodies word-exact), .line byte-equal; .debug set-equal (anonymous-
        # type DIE order), adopted.  The sort's outer counter is `i`, not `t` (`t` is the
        # swap temp), which also fixes the callee-saved colouring.
        ("src/AM/s573/doll/dexport.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g"),
        ("src/common/cws/multi_window.c", "3.0b38-030307",
         "-c -lang c -O3 -opt full -g")),
)

#: Every target this tree can build for.  Adding one is a `Target(...)` above and a mention
#: here -- and, if it should be the default, the ``default=`` name; nothing else changes.
TARGETS = Registry(DDREX2P, default="ddrex2p")

#: The name every tool uses when no ``--target`` names another: the target this tree is for.
DEFAULT = TARGETS.default


def names() -> tuple:
    """Every registered target's name, in registration order."""
    return TARGETS.names()


def get(name: str | None = None) -> Target:
    """The registered target ``name``, or the default one when no name is given.

    An unknown name raises :class:`UnknownTarget` naming the ones that exist: a typo must not
    silently configure the default target and produce a plausible image of another game.
    """
    return TARGETS.get(name)
