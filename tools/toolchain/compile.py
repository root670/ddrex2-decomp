#!/usr/bin/env python3
"""compile.py -- build one promoted translation unit with the retail compiler.

This is the program behind the ninja ``cc`` rule::

    build <out.o>: cc <src>     # flags = --compiler 3.0-011126 -c -lang c -O3 -g
      command = python3 tools/toolchain/compile.py $in $out $flags

``$in`` is the source alone: ``configure.py`` also declares this file -- and itself -- as the
edge's *implicit* inputs (``| ...``, R35a), so editing the driver invalidates the object it
produced without changing the command line.

It runs ``mwccps2`` (under wibo, through :mod:`toolchain.probe`) over a C source and turns
the Metrowerks object it writes into the one object the pinned build needs:

* ``.text`` -- the unit's functions, laid out and relocated at the virtual addresses the
  retail image has them at and labelled with their DWARF names, so the pinned ``ld`` script
  places the unit exactly where its splits used to be, and
* ``.debug`` / ``.line`` -- the unit's DWARF 1 payload, with the object's own ``.rel.debug``
  / ``.rel.line`` applied, so the ninja ``objsec`` edges can dump them and the file's tail
  can be assembled from the compiler's bytes instead of from the retail databins.

Why a translation rather than a link of the Metrowerks object (R23): mainline binutils
cannot read a ``mwccps2`` object at all, and ``mwldps2`` -- which can -- does not keep
``.debug``/``.line`` for a link without debug flags.  Every address a relocation needs is
already pinned -- the unit's own chunk in ``.debug``, each function's record and statement
list, the unit's address, ``$gp`` from the retail ELF's ``.reginfo``, and every other name
the pinned link itself resolves (the split objects its ld script lists and its ``-T`` files'
assignments) -- so the object's bytes can be placed directly under the pinned layout.
G1 and the unit's per-chunk verdicts are what prove the result; this program only has to be
honest about what it wrote.

Usage::

    python3 tools/toolchain/compile.py src/sys/sys_scf.c build/src/sys/sys_scf.c.o \\
        --compiler 3.0-011126 -c -lang c -O3 -g

``--syntax-only`` is the second thing this program is: the *compiler's* verdict on whether a
file is C, for the generated headers (`include/types/*.h`, `include/src/**`) that nothing
compiles yet:

    python3 tools/toolchain/compile.py --syntax-only --include include probe.c

``--normalise-debug`` is the opt-in third thing: on the set-equal DIE-order class it re-emits
*our* ``.debug`` chunk in retail's DIE sequence and accepts it only when the rewritten bytes
are retail's, byte for byte (:mod:`toolchain.debug_normalize`).  It is never silent -- it
prints what it normalised -- and it is off by default, because the gate's own treatment
(recognise the class, keep retail's bytes) stays the promotion path.

``--adopt-retail-meta`` is the fourth: for a unit whose ``.text`` is already retail's, it
adopts retail's ``.line`` chunk and the ``AT_location`` values of locals whose records
otherwise match, then accepts only when the whole ``.debug`` chunk is retail's bytes
(:mod:`toolchain.debug_adopt`).  ``.text`` differing is a refusal, printed loudly; every
adopted row and location is printed, with its before and after values.

MWCC has no parse-only mode -- ``-nocodegen`` skips the front end's own error reporting, so
it exits 0 on a file it cannot parse -- so the check runs the ordinary compile and throws
the object away.  What is left is the exit status and the compiler's own diagnostics.

A promoted source carries **no ``#line`` directive**, and this program is where the ``cc``
edge enforces it: :func:`refuse_line_directives` stops the build before the compiler runs,
naming the file, the count and the remedy
(``python3 tools/toolchain/line_reflow.py <file> --normalise``).  ``configure.py`` refuses the
same source even earlier, before it writes ``build.ninja``.  The rewrite is a promotion step,
never something the build does to a scratch copy the committed file does not show.

Exit codes: 0 the object was written (or ``--syntax-only`` accepted the file), 1 the compiler
or the assembler failed, 2 the source, a manifest, a host tool or a name the object needs is
not something this build can place.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import pathlib
import re
import shutil
import struct
import subprocess
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

import elf  # noqa: E402  the vendored 32-bit little-endian MIPS reader
from config import targets  # noqa: E402  the one place a target's facts are written down
from toolchain import (check_deps, debug_adopt, debug_normalize, debug_set, fetch,
                       line_reflow, probe)  # noqa: E402

#: The target a direct invocation works on when ``--target`` names none: the one the tree is
#: configured for.  The ninja graph always names the target it was generated for, so a build
#: never depends on this default; it is what `compile.py` and `select_build.py` do by hand.
DEFAULT_TARGET = targets.get(targets.DEFAULT)
RETAIL = DEFAULT_TARGET.elf
BUILD = REPO_ROOT / "build"

#: The ``mwccps2`` flags a direct invocation uses.  ``-O3`` is where the retail instruction
#: scheduling appears, ``-g`` is where its DWARF 1 comes from;
#: ``tools/toolchain/select_build.py`` measures the pair per unit and prints what the build
#: should pass.
DEFAULT_FLAGS = ("-c", "-lang", "c", "-O3", "-g")

#: The host assembler invocation, matching the splits' rule in ``configure.py``: no padding
#: (the pinned script places whole objects back to back with SUBALIGN(1)), EABI register
#: numbering, the R5900 ISA.
AS = ("mips-linux-gnu-as", "-Iasm/include", "--no-pad-sections", "-EL", "-march=5900",
      "-mabi=eabi")

#: The staging root.  The compiler records the *absolute* path of the file it is given,
#: canonicalised -- wibo resolves the host path, so a staged copy under macOS's ``/tmp``
#: is recorded under ``/private/tmp`` -- and spells the host root as the ``Z:`` drive.
#: Retail's CU name records the original build host's path, and a staged copy is put at a
#: path whose guest spelling is exactly as long as retail's, so that replacing the
#: recorded name cannot resize a DIE.  ``/tmp`` is the shortest root every host has (the
#: repo's own path is longer than the retail build's recorded one); it is resolved here because
#: the *real* path is the one that has to fit.
STAGING_ROOT = pathlib.Path("/tmp").resolve()

#: The oracle's own word for the one reason that still has an address to place: an object
#: whose DWARF `AT_location` carries none, which is 0 in retail's bytes (`emit_symbols.py`
#: writes the reason; `tests/toolchain/test_compile_relocations.py` pins this spelling to
#: it).  The other reason, "outside every declared segment", is *not* address 0 -- those
#: objects live in the overlay reservations this layout does not model.
UNPLACED_NO_ADDRESS = "no AT_location address"

#: The oracle's word for the other way a name misses the placed ledger: the record lives
#: outside every declared segment (one of this target's overlay reservations), so this
#: layout has no place to relocate it to and the promotion is refused *by design* until the
#: overlay milestone models those segments.  Kept distinct from `UNPLACED_NO_ADDRESS` so the
#: refusal can say which of the two it is instead of looking like a lookup that broke.
UNPLACED_OUTSIDE = "outside every declared segment"

R_MIPS_NONE, R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16 = 0, 2, 4, 5, 6, 7
RELOC_NAMES = {R_MIPS_32: "R_MIPS_32", R_MIPS_26: "R_MIPS_26",
               R_MIPS_HI16: "R_MIPS_HI16", R_MIPS_LO16: "R_MIPS_LO16",
               R_MIPS_GPREL16: "R_MIPS_GPREL16"}

SHT_REL = 9
STT_SECTION, STT_FUNC = 3, 2
SYMBOL_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<address>0x[0-9A-Fa-f]+);\s*//\s*(?P<attrs>.*)$")
#: The global labels a generated split defines (`asm/include/macro.inc`'s macros).  The one
#: label at an address is the same name the link knows, and `_split_symbols` binds each to the
#: address of the piece of data or instruction that follows it.
SPLIT_LABEL = re.compile(r"^\s*(?:glabel|alabel|ehlabel|jlabel|dlabel)\s+(\S+)", re.M)
#: A code split's per-instruction comment: splat prints the file offset, the address and the
#: encoded word, so the *second* number is the address.
SPLIT_ADDRESS = re.compile(
    r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]{8}\s+\*/")
#: A data split's per-object comment: splat prints the address alone (``/* 00607A70 */``)
#: before the ``.space`` that reserves the object.  That is the same address the ld gives the
#: label, because the data section is placed at its retail address.
DATA_ADDRESS = re.compile(r"/\*\s+([0-9A-Fa-f]+)\s+\*/")
#: A bare assignment in a linker script -- splat's ``undefined_{syms,funcs}_auto.txt`` and
#: the aliases ``configure.py`` writes into the ld script itself.  These are the link's other
#: symbol source, and the ones ``symbol_addrs.txt`` does not carry.
LINK_ASSIGN = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+);")
#: One address-driven data placement (``config/<target>/data_placements.txt``): the compiled
#: symbol, the retail address its bytes were matched to, the compiled length, the retail span
#: (including the zero fill retail shows), and which source defines it.
#:
#: The symbol is a C identifier, or Metrowerks' literal-pool name ``@N``: a literal the source
#: never named is numbered by the compiler, and that number is what the object's relocations
#: carry.  A pool slot is a datum like any other -- the address is the pool entry's, proved by
#: the same byte comparison -- so the ledger has to be able to spell one.
DATA_PLACEMENT = re.compile(
    r"^(?P<name>[A-Za-z_]\w*|@\d+)\s*=\s*0x(?P<address>[0-9A-Fa-f]+);\s*//\s*"
    r"size:0x(?P<size>[0-9A-Fa-f]+)\s+extent:0x(?P<extent>[0-9A-Fa-f]+)\s+"
    r"source:(?P<source>\S+)\s*$")


class Unusable(Exception):
    """The unit cannot be placed: a manifest, a name or the source itself is unusable."""


# ---------------------------------------------------------------------------
# the oracle's manifests, as the compiler needs them
# ---------------------------------------------------------------------------


class Function:
    """One function of a unit: where retail put it, and where its DWARF goes."""

    __slots__ = ("name", "address", "size", "debug_offset", "debug_size",
                 "line_offset", "line_size", "record")

    def __init__(self, name, address, size, debug_offset, debug_size, line_offset,
                 line_size, record):
        self.name = name
        self.address = address
        self.size = size
        self.debug_offset = debug_offset      # offset in the .debug section
        self.debug_size = debug_size
        self.line_offset = line_offset        # offset in the .line section
        self.line_size = line_size
        self.record = record                  # index into cus.json


class Tu:
    """One translation unit of the retail build, with its pinned placement."""

    __slots__ = ("file", "name", "records", "debug_offset", "debug_size",
                 "line_offset", "line_size", "functions")

    def __init__(self, file, name, records, debug_offset, debug_size, line_offset,
                 line_size, functions):
        self.file = file                  # repo-relative, e.g. "src/sys/sys_scf.c"
        self.name = name                  # the retail spelling, with its drive
        self.records = records            # cus.json indices, in .debug order
        self.debug_offset = debug_offset  # the unit's .debug chunk
        self.debug_size = debug_size
        self.line_offset = line_offset    # the unit's run of .line chunks
        self.line_size = line_size
        self.functions = functions        # in address order

    @property
    def source(self) -> pathlib.Path:
        return REPO_ROOT / self.file

    @property
    def address(self) -> int:
        return min(function.address for function in self.functions)

    @property
    def end(self) -> int:
        return max(function.address + function.size for function in self.functions)

    def function_named(self, name):
        return next((f for f in self.functions if f.name == name), None)


# ---------------------------------------------------------------------------
# address-driven data placement
# ---------------------------------------------------------------------------


def data_placements(target=None) -> list:
    """``[dict]`` from the target's ``data_placements.txt``: the derived data ledger.

    The file is checked in, not generated at build time: an address is evidence, and the one
    thing a build must never do is invent it.  ``configure.py`` reads the same file to cut the
    retail split and place the compiled object's section; :class:`Manifests` reads it so the
    unit's own DWARF relocations resolve to the same address.
    """
    target = target or DEFAULT_TARGET
    path = target.config_dir / "data_placements.txt"
    if not path.is_file():
        return []
    out = []
    for number, line in enumerate(path.read_text().splitlines(), start=1):
        text = line.strip()
        if not text or text.startswith("//"):
            continue
        match = DATA_PLACEMENT.match(text)
        if match is None:
            raise Unusable(
                f"{_display(path)} line {number} is not `name = 0xADDR; // size:0xS "
                f"extent:0xE source:FILE`: {text}")
        out.append(dict(name=match["name"], address=int(match["address"], 16),
                        size=int(match["size"], 16), extent=int(match["extent"], 16),
                        source=match["source"]))
    return out


class Manifests:
    """A target's manifests, plus the symbol set its generated link actually resolves.

    The target is a parameter, never a module-level convention: the ninja ``cc`` edge passes
    ``--target``, so a unit is placed against the manifests of the binary its object is
    linked into rather than against whichever config a default happens to name.

    Resolution follows the link, not one ledger.  The link's inputs are the split objects the
    ld script lists (``asm/nonmatchings/<segment>/*.s`` for code and ``asm/data/*.s`` for the
    data sections) and its ``-T`` files (``undefined_{syms,funcs}_auto.txt`` and the ld
    script's own aliases), so a name in any of them resolves here -- which is what makes a
    callee the oracle's DWARF never named, like `func_001C43E8`, placeable, and what makes an
    object like `g_game_w` (a ``dlabel`` in `asm/data/bss.bss.s`, assigned by no ``-T``
    line) resolve the way the link resolves it.  ``symbol_addrs.txt`` adds the oracle's own
    addresses, and a ``-T`` assignment only counts where this layout holds its address.

    A name that misses all of it is refused, and the refusal says which way: an address
    outside every declared segment (an overlay window this layout does not model) is a
    boundary deferred by design, while a name with no record at all is a gap.
    """

    def __init__(self, target=None, root=REPO_ROOT):
        self.target = target if target is not None else DEFAULT_TARGET
        self.root = pathlib.Path(root)
        self.dir = self.target.config_dir
        self.cus = self._json(self.dir / "cus.json")
        self.chunks = self._json(self.dir / "debug_chunks.json")
        self.symbols = {}
        self.placed = {}
        self.withheld = {}
        self.by_address = {}
        # An object the oracle could not place *because retail's own DWARF gives it no
        # address* still has a value a placement has to reproduce: 0, which is what retail's
        # `AT_location` holds for it.  Anything else it withheld is a refusal, not an address:
        # an object outside every declared segment lives in an overlay this layout does not
        # model, so it is kept aside with its reason for `address_of` to report.
        for name, address, attrs in self._unplaced():
            if attrs["reason"] == UNPLACED_NO_ADDRESS:
                self.symbols.setdefault(name, (address, {"provenance": "unplaced"}))
            else:
                self.withheld.setdefault(
                    name, (address, attrs["reason"], self.dir / "unplaced_symbols.txt"))
        for line in (self.dir / "symbol_addrs.txt").read_text().splitlines():
            match = SYMBOL_LINE.match(line.strip())
            if match is None:
                continue
            address = int(match["address"], 16)
            attrs = dict(attr.split(":", 1) for attr in match["attrs"].split() if ":" in attr)
            self.symbols[match["name"]] = (address, attrs)
            # An address-derived stand-in (`func_0021C410`) and the DWARF name share an
            # address; the DWARF name is the evidence, so it wins.
            known = self.by_address.get(address)
            if known is None or (attrs.get("provenance") == "dwarf"
                                 and self.symbols[known][1].get("provenance") != "dwarf"):
                self.by_address[address] = match["name"]
        # A data placement is the address a compiled datum was matched to.  It is the same
        # evidence the link places the object's section at, so the unit's DWARF relocations to
        # that datum resolve here instead of missing the ledger (`symbol_addrs.txt` is the
        # oracle's DWARF output and cannot carry a symbol retail never declared).
        #
        # The name is not unique across units: a Metrowerks literal-pool index (`@40`) is
        # numbered per object, so two units compiled from alike-shaped sources both emit
        # `@40`, at different retail slots.  Every record is kept -- `prefer_source` lets the
        # unit being compiled select its own -- and the ledger's first record stays the
        # default, which is what a unit with no records of its own can only be reading.
        self.placements = data_placements(self.target)
        for record in self.placements:
            self.placed.setdefault(record["name"], record["address"])
            self.by_address.setdefault(record["address"], record["name"])
        # The split objects the ld script places define their own global labels, and those are
        # in neither ledger: `func_001C43E8` has a split and no DWARF record, so the link
        # resolves it while the symbol file never mentions it.  Read last, so a ledger name
        # keeps its attrs, and `by_address` gains the name of a split no DWARF record covers.
        for name, address in self._split_symbols().items():
            self.placed.setdefault(name, address)
            self.by_address.setdefault(address, name)
        # The link's other inputs are its `-T` files.  They are only half a symbol set: an
        # assignment names an address, and this layout has to hold one.  `D_001158C0` (data a
        # split reads and nothing labels) is inside the declared segments, so it resolves;
        # `D_008062B0`, the overlay's generated stand-in, is outside every one of them, so it
        # is a refusal with that reason -- the same boundary `NetRouterMain` hits from the
        # oracle's ledger.  A target nobody has measured gets neither (see `_within_segments`).
        for name, address, source in self._link_assignments():
            if self._within_segments(address):
                self.placed.setdefault(name, address)
                self.by_address.setdefault(address, name)
            else:
                self.withheld.setdefault(name, (address, UNPLACED_OUTSIDE, source))

    def _link_assignments(self):
        """``[(name, address, path)]`` for the ``-T`` linker scripts' own assignments."""
        out = []
        for path in (getattr(self.target, "undefined_syms", None),
                     getattr(self.target, "undefined_funcs", None),
                     getattr(self.target, "ld_script", None)):
            if path is None or not pathlib.Path(path).is_file():
                continue
            for line in pathlib.Path(path).read_text().splitlines():
                match = LINK_ASSIGN.match(line.strip())
                if match is not None:
                    out.append((match.group(1), int(match.group(2), 16), path))
        return out

    def _within_segments(self, address) -> bool:
        """Whether ``address`` is one this layout places: inside the declared segments.

        A target nobody has measured has no segments to be inside, and its link is not
        generated either, so everything from the ``-T`` files is refused rather than placed.
        """
        geometry = getattr(self.target, "geometry", None)
        if geometry is None:
            return False
        return geometry.loadable_vram <= address < geometry.bss_end

    def _split_symbols(self):
        """``{label: address}`` for the global labels of the split objects the link places.

        The ld script lists ``build/asm/nonmatchings/<segment>/*.s.o`` and
        ``build/asm/data/*.s.o``; this reads the *sources* of those same objects, so a name
        resolves here exactly when the link resolves it.  Both kinds matter: a function's
        label is code, and an object's label is data -- `g_game_w` is placed by
        ``asm/data/bss.bss.s``'s ``dlabel`` and by no assignment in the ld script, which is
        why the data half cannot be left out of "the symbols the link knows".

        A label is bound to the address of the instruction or object that follows it --
        splat's per-instruction ``/* fileoffset address bytes */`` comment, or the per-object
        ``/* address */`` one before a data split's ``.space`` -- which is the same address
        `configure.py` checks against the segment geometry.
        """
        geometry = getattr(self.target, "geometry", None)
        segment = getattr(geometry, "code_segment", "main")
        directories = ((self.root / "asm" / "nonmatchings" / segment, SPLIT_ADDRESS),
                       (self.root / "asm" / "data", DATA_ADDRESS))
        out = {}
        for directory, pattern in directories:
            if not directory.is_dir():
                continue
            for path in sorted(directory.glob("*.s")):
                text = path.read_text()
                addresses = [(match.start(), int(match.group(1), 16))
                             for match in pattern.finditer(text)]
                if not addresses:
                    continue
                for label in SPLIT_LABEL.finditer(text):
                    # The label belongs to the instruction or object after it, so the first
                    # address comment past the label is its address (a label in the
                    # directives before any instruction -- every `glabel` -- gets the first
                    # instruction's; a databin `dlabel` has none and is skipped).
                    entry = next((address for position, address in addresses
                                  if position > label.start()), None)
                    if entry is not None:
                        out.setdefault(label.group(1), entry)
        return out

    def _unplaced(self):
        """``[(name, address, attrs)]`` for every record outside the placed ledger.

        The placed ledger wins over all of them (they are read first), so these can only ever
        *add* a name: one whose object exists in the unit's DWARF and nowhere in the image.
        """
        path = self.dir / "unplaced_symbols.txt"
        if not path.is_file():
            return []
        out = []
        for line in path.read_text().splitlines():
            match = SYMBOL_LINE.match(line.strip())
            if match is None:
                continue
            # The reason is prose and carries spaces ("no AT_location address"), so it is the
            # one field that cannot come out of the keyword split; `dwarf_name:` follows it
            # when the oracle had to rename a duplicate.
            tail = match["attrs"]
            if "reason:" not in tail:
                continue
            reason = tail.split("reason:", 1)[1].split(" dwarf_name:", 1)[0].strip()
            out.append((match["name"], int(match["address"], 16), {"reason": reason}))
        return out

    @staticmethod
    def _json(path) -> object:
        if not path.is_file():
            raise Unusable(f"{path.relative_to(REPO_ROOT)} is missing; run ./ddr oracle")
        return json.loads(path.read_text())

    def prefer_source(self, source: str) -> None:
        """Let ``source``'s own placement records win over another unit's of the same name.

        A record names the source that defines it, and the name alone cannot carry the
        identity of a datum: `@40` is whatever literal pool slot that *object* numbered
        first, so `net_win_listdtl2.c`'s `@40` ("%05d" at 0x002D6D88) and
        `net_win_listdtl3.c`'s (`"%05d"` at 0x002D6DA8) are two different slots wearing one
        name.  The ledger keeps both; this decides which one a same-named relocation means.

        Called with the unit's source path before its relocations are resolved.  Nothing is
        invented: both records are already derived from retail's bytes by :func:`verify_data`,
        so the choice is between measured addresses, not between a measurement and a guess.
        A unit with no records of its own changes nothing -- the ledger default stands.

        ``symbols`` also has to yield: `netwinslby_plate_board` is one unit's static at
        0x002C0780 and another's at 0x002BF710, and the split records the bare name for the
        first, so without this pop the object's ``AT_location`` and initialiser would bake
        the other unit's address.  The source's own measured record displaces the bare name.
        """
        for record in self.placements:
            if record["source"] == source:
                self.placed[record["name"]] = record["address"]
                self.symbols.pop(record["name"], None)
                self.by_address[record["address"]] = record["name"]

    def address_of(self, name) -> int:
        if name in self.symbols:
            return self.symbols[name][0]
        if name in self.placed:
            return self.placed[name]
        withheld = self.withheld.get(name)
        if withheld is not None:
            address, reason, source = withheld
            raise Unusable(
                f"the object references {name!r}, which is at 0x{address:08X}, {reason} "
                f"({_display(source)}); this layout has no place to relocate it to -- the "
                f"segments that hold it are the overlay milestone's -- so the unit cannot "
                f"be placed")
        raise Unusable(
            f"the object references {name!r}, which has no record at all: not among the "
            f"split labels the link places, not in {_display(self.target.symbols)}, not in "
            f"the link's -T files, and not in {self._unplaced_path()}; the unit cannot be "
            f"placed")

    def _unplaced_path(self):
        """The target's unplaced ledger, as a reader types it."""
        return _display(self.dir / "unplaced_symbols.txt")

    def tu_named(self, name: str) -> Tu:
        """The unit ``name`` spells -- a repo path, a path tail, or a file name.

        The rules are ``tools/verify/g2.py``'s, so the name ``ddr verify --tu`` accepts is
        the name this build accepts, and an ambiguous name is an error in both.
        """
        matched = sorted(
            (index, record["file"]) for index, record in enumerate(self.cus)
            if record.get("kind") == "tu"
            and (record["file"] == name
                 or record["file"].endswith("/" + name)
                 or pathlib.PurePosixPath(record["file"]).name in (name, f"{name}.c")))
        if not matched:
            raise Unusable(f"no translation unit matches {name!r}")
        if len(matched) > 1:
            raise Unusable(f"{name!r} matches {len(matched)} translation units: "
                           + ", ".join(file for _, file in matched))
        return self._tu(matched[0][0])

    def tu_files(self) -> set:
        """Every ``file`` a ``kind:tu`` record names -- no placement asked, no validation.

        Most units have records this build cannot place (a unit with no function at all, a
        unit whose records are not subprograms); they are still units the promotion check
        has to see, so the listing is what this returns rather than a placed :class:`Tu`.
        """
        return {record["file"] for record in self.cus if record.get("kind") == "tu"}

    def _tu(self, index: int) -> Tu:
        record = self.cus[index]
        chunk = next((c for c in self.chunks if c.get("section") == ".debug"
                      and c.get("tunits", [None])[0] == index), None)
        if chunk is None:
            raise Unusable(f"no .debug chunk starts at cus.json record {index}")
        records = list(chunk["tunits"])
        line_chunks = []
        functions = []
        for number in records[1:]:
            entry = self.cus[number]
            if entry.get("kind") != "function" or entry.get("low_pc") is None:
                raise Unusable(
                    f"{record['file']}: cus.json record {number} is "
                    f"{entry.get('kind')!r}, not a function this build can place")
            name = self.by_address.get(entry["low_pc"])
            if name is None:
                raise Unusable(f"{record['file']}: no symbol at 0x{entry['low_pc']:08X}")
            line = next((c for c in self.chunks if c.get("section") == ".line"
                         and c.get("tunits", [None])[0] == number), None)
            if line is None:
                raise Unusable(f"{record['file']}: no .line chunk for {name}")
            line_chunks.append((line["offset"], line["size"]))
            functions.append(Function(
                name, entry["low_pc"], entry["high_pc"] - entry["low_pc"],
                entry["offset"], entry["size"], line["offset"], line["size"], number))
        if not functions:
            raise Unusable(f"{record['file']} declares no functions")
        functions.sort(key=lambda f: f.address)
        if not _contiguous(line_chunks):
            raise Unusable(
                f"{record['file']}: the unit's .line chunks are not contiguous "
                f"({', '.join(f'0x{o:X}+0x{s:X}' for o, s in line_chunks)}); the file's tail "
                f"cannot be assembled from one payload")
        return Tu(record["file"], record["name"], records, chunk["offset"], chunk["size"],
                  min(offset for offset, _ in line_chunks),
                  sum(size for _, size in line_chunks), functions)

    def section_chunks(self, section: str):
        """A section's chunks in file order -- the order ``configure.py`` cuts databins."""
        return sorted((c for c in self.chunks if c.get("section") == section),
                      key=lambda c: c["offset"])

    def line_chunk_indices(self, tu: Tu):
        """The unit's ``.line`` chunks, by their position among the ``.line`` chunks.

        The position, not the manifest index: ``configure.py`` names a databin
        ``.line_<position>`` from the section's own file order, which is what the tail
        substitution has to match.
        """
        offsets = {f.line_offset for f in tu.functions}
        return [index for index, chunk in enumerate(self.section_chunks(".line"))
                if chunk["offset"] in offsets]

    def debug_chunk_index(self, tu: Tu) -> int:
        """The unit's ``.debug`` chunk, by its position among the ``.debug`` chunks."""
        return [c["offset"] for c in self.section_chunks(".debug")].index(tu.debug_offset)


def _contiguous(runs) -> bool:
    ordered = sorted(runs)
    return all(ordered[i][0] + ordered[i][1] == ordered[i + 1][0]
               for i in range(len(ordered) - 1))


def _split_extent(tu: Tu, manifests: Manifests, root=None) -> tuple[int, int]:
    """Return the address range occupied by the splits a promotion removes.

    Splat's function split includes the trailing bytes up to the next split, which can be
    padding outside the function's DWARF ``high_pc``.  The linker removes that whole run,
    so a promoted object has to fill it too.
    """
    root = manifests.root if root is None else root
    segment = manifests.target.geometry_required().code_segment
    directory = pathlib.Path(root) / "asm" / "nonmatchings" / segment
    if not directory.is_dir():
        raise Unusable(f"{tu.file}: {directory} is missing; run the oracle and "
                       "configure step first")
    rows = []
    for path in directory.glob("*.s"):
        match = SPLIT_ADDRESS.search(path.read_text())
        if match is None:
            raise Unusable(f"{path} carries no split address")
        rows.append((int(match.group(1), 16), path))
    rows.sort()
    addresses = [function.address for function in tu.functions]
    positions = []
    for address in addresses:
        position = next((i for i, (candidate, _) in enumerate(rows)
                         if candidate == address), None)
        if position is None:
            raise Unusable(f"{tu.file}: no code split at 0x{address:08X}")
        positions.append(position)
    first, last = min(positions), max(positions)
    if sorted(positions) != list(range(first, last + 1)):
        raise Unusable(f"{tu.file}: its function splits are not one contiguous run")
    end = rows[last + 1][0] if last + 1 < len(rows) else tu.end
    if end < tu.end:
        raise Unusable(f"{tu.file}: split extent ends at 0x{end:08X}, before its "
                       f"last function ends at 0x{tu.end:08X}")
    return tu.address, end


def _all_nops(data: bytes) -> bool:
    """Whether ``data`` is whole-word MIPS ``nop`` padding."""
    return len(data) % 4 == 0 and all(data[offset:offset + 4] == b"\0\0\0\0"
                                       for offset in range(0, len(data), 4))


def _uncovered(size: int, spans) -> list[tuple[int, int]]:
    """The ``[start, end)`` runs of ``size`` that no ``(offset, length)`` span covers."""
    runs = []
    cursor = 0
    for start, length in sorted(spans):
        if start > cursor:
            runs.append((cursor, start))
        cursor = max(cursor, start + length)
    if cursor < size:
        runs.append((cursor, size))
    return runs


def _require_nops(data: bytes, unit: str, chunk: str) -> None:
    """Refuse unless ``data`` is whole-word ``nop``: padding may be filled, content not."""
    if not _all_nops(data):
        raise Unusable(
            f"{unit}: {chunk} is short by 0x{len(data):X} bytes; C is incomplete "
            f"(retail's bytes there are content, not nop padding)")


def _fill_nop_tail(known: bytes, padding: bytes, unit: str, chunk: str) -> bytes:
    """``known`` extended with retail's ``padding`` -- only when that padding is ``nop``."""
    _require_nops(padding, unit, chunk)
    if padding:
        print(f"compile: {unit}: filled {chunk} trailing nop padding from retail "
              f"(0x{len(padding):X} bytes)", file=sys.stderr)
    return known + padding


def _text_extent(text: bytes, retail: bytes, spans, trailing: int, unit: str) -> bytes:
    """``text`` with every byte no function body covers taken from retail's own padding.

    ``spans`` are the ``(offset, length)`` runs the unit's function bodies occupy and
    ``trailing`` is where its last function ends: the run from there on is the *shortfall*
    the promotion has to fill, because the splits it displaces run to the next split's
    address, past that function.  A byte in an inter-function gap that retail does not
    leave ``nop`` is content this unit has not written, and is refused -- as is a shortfall
    whose remainder is anything but ``nop``.
    """
    for start, end in _uncovered(len(text), spans):
        gap = retail[start:end]
        if start == trailing:
            return _fill_nop_tail(text[:start], gap, unit, ".text")
        _require_nops(gap, unit, ".text")
    return text


# ---------------------------------------------------------------------------
# the Metrowerks object
# ---------------------------------------------------------------------------


class MWObject:
    """A compiled ``mwccps2`` object, read by section index.

    Metrowerks emits one group of sections per function (``.text``, ``.debug``, ``.line``,
    ``.mwcats``), so a section *name* is not unique: every lookup here goes through the
    symbol table, which is also how the linker told the groups apart.
    """

    def __init__(self, path, manifests=None):
        self.path = pathlib.Path(path)
        self.elf = elf.Elf(str(self.path))
        self.manifests = manifests
        self.relocs = {}      # target section index -> [(offset, type, symbol)]
        for section in self.elf.sections:
            if section.type != SHT_REL:
                continue
            for offset in range(section.offset, section.offset + section.size, 8):
                at, info = struct.unpack_from("<II", self.elf.data, offset)
                self.relocs.setdefault(section.info, []).append(
                    (at, info & 0xFF, self.elf.symbols[info >> 8]))

    def data(self, index) -> bytes:
        section = self.elf.sections[index]
        return self.elf.data[section.offset:section.offset + section.size]

    def section_named(self, name) -> int:
        """The first section called ``name`` -- the unit's own ``.debug``, for instance."""
        found = [i for i, s in enumerate(self.elf.sections) if s.name == name]
        if not found:
            raise Unusable(f"{self.path}: the object has no {name} section")
        return found[0]

    def _symbol(self, predicate, what: str):
        for symbol in self.elf.symbols:
            if predicate(symbol):
                return symbol
        raise Unusable(f"{self.path}: the object has no {what}")

    def section_of_symbol(self, name) -> int:
        return self._symbol(lambda s: s.name == name and s.type == STT_SECTION,
                            f"section symbol {name!r}").shndx

    def function_section(self, name) -> int:
        return self._symbol(lambda s: s.name == name and s.type == STT_FUNC,
                            f"definition of the function {name!r}").shndx

    def groups(self, tu: Tu):
        """``{function name: (text, debug, line)}`` -- one section group per function."""
        return {function.name: (self.function_section(function.name),
                               self.section_of_symbol(f".debug_{function.name}"),
                               self.section_of_symbol(f".line_{function.name}"))
                for function in tu.functions}

    def resolve(self, tu: Tu, symbol):
        """The pinned value of ``symbol`` in the layout this unit goes into.

        Four cases, all pinned: one of the unit's own section symbols (the offset of the
        block it carries: the unit's records, a function's DWARF record, or a statement
        list), a function of the unit (its retail address), a global label of a split the
        link places, and anything else -- which has to be a name the manifests give an
        address for, and is otherwise refused by :meth:`Manifests.address_of`.
        """
        pinned = self._section_offset(tu, symbol)
        if pinned is not None:
            return pinned
        function = tu.function_named(symbol.name)
        if function is not None:
            return function.address
        if self.manifests is None:
            raise Unusable("no manifests to resolve symbols with")
        return self.manifests.address_of(symbol.name)

    def _section_offset(self, tu: Tu, symbol):
        if symbol.type != STT_SECTION:
            return None
        name = symbol.name
        if name == ".debug":                       # the unit's own records start here
            return tu.debug_offset
        for function in tu.functions:
            if name == f".debug_{function.name}":
                return function.debug_offset
            if name == f".line_{function.name}":
                return function.line_offset
            if name == ".text" and symbol.shndx == self.function_section(function.name):
                return function.address
        return None


def _signed16(value: int) -> int:
    """A 16-bit immediate as the instruction means it: sign-extended."""
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def _lo_addend(data, offset: int) -> int:
    """The addend an instruction carries: what the compiler wrote in its low half."""
    return _signed16(struct.unpack_from("<I", data, offset)[0])


def _pairs(data, relocs, what: str):
    """``{hi offset: (lo offset, addend)}`` for the ``lui``/``addiu`` address pairs.

    A MIPS address over the small-data threshold is materialised by two instructions whose
    *addend* is split the same way: the compiler writes the high half in the ``lui`` and the
    low half in the ``%lo`` instruction, so the value to place is ``symbol + addend`` and the
    two immediates are its halves.  The addend is read off the pair, not guessed: the
    ``lui``'s immediate is ``addend >> 16`` and the ``%lo`` immediate is the sign-extended
    low half, so ``(hi << 16) + signed16(lo)`` is the addend exactly -- for a bare symbol
    (high half zero) and for a field at a constant offset (high half carrying it) alike.  A
    ``lui`` with no ``%lo`` for the same symbol raises, because a lone high half is not an
    address.
    """
    lo = [(offset, _lo_addend(data, offset), symbol.name)
          for offset, rtype, symbol in relocs if rtype == R_MIPS_LO16]
    pairs = {}
    for offset, rtype, symbol in relocs:
        if rtype != R_MIPS_HI16:
            continue
        partner = next((entry for entry in lo
                        if entry[2] == symbol.name and entry[0] > offset), None)
        if partner is None:
            raise Unusable(
                f"{what}: the address of {symbol.name} at 0x{offset:X} is loaded with a "
                f"`lui` whose `%lo` half is not in this section; a lone high half is not an "
                f"address")
        hi = struct.unpack_from("<I", data, offset)[0] & 0xFFFF
        pairs[offset] = ((hi << 16) + partner[1], partner[2])
    return pairs


def relocate(data: bytes, relocs, resolve, what: str, gp: int) -> bytes:
    """Apply a section's ``.rel`` entries to its bytes.

    The objects are ``SHT_REL``, so each entry's addend is the value already in the field:
    a whole word for ``R_MIPS_32`` (the compiler writes the record's own offset there and
    relocates against its section symbol), the target word for ``R_MIPS_26``, the
    sign-extended immediate for ``R_MIPS_GPREL16`` and for the ``%lo`` half of an address,
    and the *paired* ``%lo``'s immediate for that address's ``%hi`` half -- because the
    address is ``symbol + addend`` and the compiler writes one constant's two halves into
    the two instructions.  A pair whose constant offset is split any other way is refused
    rather than approximated (see :func:`_pairs`).
    """
    out = bytearray(data)
    pairs = _pairs(data, relocs, what)
    for offset, rtype, symbol in relocs:
        if rtype == R_MIPS_NONE:
            continue
        value = resolve(symbol)
        word = struct.unpack_from("<I", out, offset)[0]
        if rtype == R_MIPS_32:
            struct.pack_into("<I", out, offset, (value + word) & 0xFFFFFFFF)
        elif rtype == R_MIPS_26:
            target = value + ((word & 0x03FFFFFF) << 2)
            struct.pack_into("<I", out, offset,
                             (word & 0xFC000000) | ((target >> 2) & 0x03FFFFFF))
        elif rtype in (R_MIPS_HI16, R_MIPS_LO16):
            address = value + (pairs[offset][0] if rtype == R_MIPS_HI16
                               else _lo_addend(data, offset))
            half = (address + 0x8000) >> 16 if rtype == R_MIPS_HI16 else address
            struct.pack_into("<I", out, offset, (word & 0xFFFF0000) | (half & 0xFFFF))
        elif rtype == R_MIPS_GPREL16:
            addend = word & 0xFFFF
            if addend & 0x8000:
                addend -= 0x10000
            delta = value + addend - gp
            if not -0x8000 <= delta <= 0x7FFF:
                raise Unusable(
                    f"{what}: {symbol.name} is 0x{delta:X} from $gp (0x{gp:08X}), which the "
                    f"instruction cannot hold; retail's $gp does not fit this layout")
            struct.pack_into("<I", out, offset, (word & 0xFFFF0000) | (delta & 0xFFFF))
        else:
            raise Unusable(f"{what}: relocation {RELOC_NAMES.get(rtype, rtype)!r} at "
                           f"0x{offset:X} is not one this build applies")
    return bytes(out)


def gp_value(retail=RETAIL) -> int:
    """``$gp`` as the retail ELF's ``.reginfo`` records it -- the ABI's own number."""
    image = elf.Elf(str(retail))
    section = next((s for s in image.sections if s.name == ".reginfo"), None)
    if section is None or section.size < 24:
        raise Unusable(f"{retail}: no .reginfo section to read $gp from")
    return struct.unpack_from("<I", image.data, section.offset + 20)[0]


# ---------------------------------------------------------------------------
# staging: the source path the DWARF records
# ---------------------------------------------------------------------------


def staged_path(tu: Tu) -> pathlib.Path:
    """Where to compile ``tu``'s source so that the DWARF path has retail's length."""
    basename = tu.source.name
    pad = len(tu.name) - len("Z:") - 1 - len(basename) - len(str(STAGING_ROOT)) - 1
    if pad < 1:
        raise Unusable(
            f"{tu.file}: retail's path spelling is {len(tu.name)} bytes, too short to stage "
            f"{basename!r} under {STAGING_ROOT}; this unit's DWARF name cannot be "
            f"reproduced")
    stem = re.sub(r"\W", "_", basename)
    # The directory must stay exactly `pad` long, so a per-unit digest is mixed in: two
    # units that share a basename and a retail-name length (`src/sys/foo.c` and
    # `src/mov/foo.c`) would otherwise stage over each other, and ninja runs `cc` edges in
    # parallel -- one unit would compile the other's copy.
    tag = hashlib.sha1(tu.file.encode()).hexdigest()
    directory = tag[:pad] if pad <= len(tag) else (stem + "_" * pad)[:pad - len(tag)] + tag
    return STAGING_ROOT / directory / basename


def recorded_name(staged: pathlib.Path) -> bytes:
    """The source path as mwcc records it: wibo spells a host path as the ``Z:`` drive."""
    return ("Z:" + str(staged)).replace("/", "\\").encode()


def retail_name_in(payload: bytes, recorded: bytes, retail: bytes) -> bytes:
    """Replace the recorded source path with retail's spelling, or fail loudly."""
    if len(recorded) != len(retail):
        raise Unusable(
            f"the staged path spells {len(recorded)} bytes where retail's spells "
            f"{len(retail)}; a different-length name would resize the DWARF records")
    if recorded == retail:
        return payload
    if recorded not in payload:
        raise Unusable(f"the compiler did not record {recorded!r} in its DWARF")
    return payload.replace(recorded, retail)


# ---------------------------------------------------------------------------
# emitting the GNU object
# ---------------------------------------------------------------------------


def _words(data: bytes) -> list[str]:
    """``.word`` lines for the bytes, with a trailing partial word as ``.byte``."""
    lines = []
    for start in range(0, len(data), 16):
        chunk = data[start:start + 16]
        whole = len(chunk) - len(chunk) % 4
        line = ""
        if whole:
            line = "\t.word\t" + ", ".join(
                f"0x{struct.unpack_from('<I', chunk, at)[0]:08X}"
                for at in range(0, whole, 4))
        if whole != len(chunk):
            rest = "\t.byte\t" + ", ".join(f"0x{byte:02X}" for byte in chunk[whole:])
            line = f"{line}\n{rest}" if line else rest
        lines.append(line)
    return lines


def _data_words(body: bytes, relocs, resolve, what: str) -> list[str]:
    """``.word`` lines for one datum, keeping its relocations symbolic.

    Retailing's addresses are not baked into the source: an ``R_MIPS_32`` against a name the
    link defines (another placement's symbol) is emitted as ``name + addend``, so the linker
    does the arithmetic.  A relocation against a name this layout only knows by address is
    emitted as that address; any other relocation kind is refused rather than approximated.
    """
    by_offset = {}
    for offset, rtype, symbol in relocs:
        if rtype == R_MIPS_NONE:
            continue
        if rtype != R_MIPS_32:
            raise Unusable(f"{what}: relocation {RELOC_NAMES.get(rtype, rtype)!r} at "
                           f"0x{offset:X} is not one a placed datum carries")
        addend = struct.unpack_from("<I", body, offset)[0]
        if symbol.type != STT_SECTION and symbol.shndx == 0:
            text = symbol.name + (f" + {addend}" if addend else "")
        else:
            text = f"0x{(resolve(symbol) + addend) & 0xFFFFFFFF:08X}"
        by_offset[offset] = text
    lines = []
    for start in range(0, len(body), 16):
        chunk = body[start:start + 16]
        words = []
        for at in range(0, len(chunk) - len(chunk) % 4, 4):
            offset = start + at
            words.append(by_offset.get(offset)
                         or f"0x{struct.unpack_from('<I', chunk, at)[0]:08X}")
        line = "\t.word\t" + ", ".join(words)
        if len(chunk) % 4:
            line += "\n\t.byte\t" + ", ".join(f"0x{b:02X}" for b in chunk[len(chunk) - len(chunk) % 4:])
        lines.append(line)
    return lines


def data_section(name: str) -> str:
    """The section a placed datum ``name`` is emitted in: one per symbol, in one object.

    A placement is per symbol -- the link puts *this* datum at *this* address -- but a unit
    can define several placed data symbols (a literal pool contributes ``@40`` and ``@41``
    as two sections), and a linker script selects an input section by name alone.  So each
    datum leaves the emitted object in a section of its own, named from the symbol: ``.``
    for Metrowerks' ``@N`` spells neither a label nor a section any other way.

    The encoding is injective (every character outside ``[A-Za-z0-9]``, the underscore
    included, becomes ``_`` and two hex digits), so two symbols can never name one section.
    """
    encoded = []
    for character in name:
        if character.isascii() and character.isalnum():
            encoded.append(character)
        elif ord(character) < 0x100:
            encoded.append(f"_{ord(character):02x}")
        else:
            raise Unusable(f"{name!r} is not a name a placed datum can carry")
    return ".datum." + "".join(encoded)


def assembly(size: int, labels, debug: bytes, line: bytes, data=()) -> str:
    """The GNU assembler source for the placed split extent and the payloads.

    Each function's bytes follow its label, and the layout's own inter-function padding --
    the retail image aligns them, and the gap is zeros there -- is a ``.space`` between
    them.  The final ``.space`` fills any trailing split padding accepted by ``place``.

    Every placed datum gets its own section (:func:`data_section`): the linker places the
    section a ledger row names, so one datum per section is what makes a per-symbol address
    expressible at all -- a unit with two placed data symbols otherwise moves both whenever
    it places one.
    """
    out = ["\t.text"]
    cursor = 0
    for address, name, body in sorted(labels):
        if address > cursor:
            out.append(f"\t.space\t{address - cursor}")
        out += [f"\t.globl\t{name}", f"{name}:"]
        out += _words(body)
        cursor = address + len(body)
    if cursor < size:
        out.append(f"\t.space\t{size - cursor}")
    for name, payload in ((".debug", debug), (".line", line)):
        if payload:
            out.append(f'\t.section {name},"",@progbits')
            out += _words(payload)
    for name, body, relocs, resolve in data:
        out.append(f'\t.section {data_section(name)},"aw",@progbits')
        out += _data_words(body, relocs, resolve, f"{name}.data")
    return "\n".join(out) + "\n"


def assemble(source: str, out: pathlib.Path) -> None:
    """Assemble the placed unit with the host assembler the splits use."""
    out.parent.mkdir(parents=True, exist_ok=True)
    assembler = shutil.which(AS[0])
    if assembler is None:
        raise check_deps.MissingDependency(
            f"{AS[0]} is not on PATH; run python3 tools/toolchain/check_deps.py")
    result = subprocess.run([assembler, *AS[1:], "-o", str(out), "-"],
                            input=source, capture_output=True, text=True)
    if result.returncode != 0:
        raise Unusable(f"{AS[0]} failed:\n{result.stderr.strip()}")


# ---------------------------------------------------------------------------
# the whole step
# ---------------------------------------------------------------------------


class Placed:
    """What a promoted unit contributes to the pinned build."""

    __slots__ = ("text", "debug", "line", "labels", "sizes", "normalised", "adopted",
                 "emitted_line", "data")

    def __init__(self, text, debug, line, labels, sizes, normalised=False, adopted=False,
                 emitted_line=None, data=()):
        self.text = text        # the promoted run of code splits, including its tail padding
        self.debug = debug      # the unit's .debug chunk
        self.line = line        # the unit's run of .line chunks (retail's when adopted)
        self.labels = labels    # [(offset within .text, function name, bytes)]
        self.sizes = sizes      # [(function name, (block, emitted, pinned))]
        self.normalised = normalised  # the .debug chunk came out of the order normaliser
        self.adopted = adopted  # retail's .line and AT_location values were adopted
        self.emitted_line = line if emitted_line is None else emitted_line  # what we wrote
        self.data = data        # [(symbol, bytes, relocations, resolve)] placed per symbol


def _fill(mw: MWObject, tu: Tu, base: int, size: int, blocks, gp: int, section: str,
          rename=None, unit_file=None) -> tuple[bytes, list]:
    """A pinned span of ``.debug`` or ``.line``, filled from the object's own blocks.

    ``blocks`` is ``[(offset, pinned size, section index, label)]``, all of them offsets
    retail pinned, and ``rename`` is the ``(recorded, retail)`` source-path pair for the
    sections that carry one.  A block that does not fit its slot is raised: the file's tail
    would otherwise reflow silently and every later chunk would be a red herring.
    """
    out = bytearray(size)
    sizes = []
    for offset, pinned, index, label in blocks:
        body = relocate(mw.data(index), mw.relocs.get(index, ()),
                        lambda symbol: mw.resolve(tu, symbol), f"{label}.{section}", gp)
        if rename is not None:
            body = retail_name_in(body, *rename)
        sizes.append((label, section, len(body), pinned))
        at = offset - base
        owner = unit_file or tu.file
        if len(body) < pinned:
            shortfall = pinned - len(body)
            raise Unusable(
                f"{owner}: {label} {section} is short by 0x{shortfall:X} bytes; "
                f"C is incomplete (cannot pad {section})")
        if at < 0 or at + len(body) > size:
            raise Unusable(
                f"{owner}: {label} {section} is 0x{len(body):X} bytes where retail's is "
                f"0x{pinned:X}; it does not fit the pinned chunk at 0x{offset:X}")
        out[at:at + len(body)] = body
    return bytes(out), sizes


def _adopted_line(mw: MWObject, tu: Tu, blocks, gp: int) -> tuple[bytes, list]:
    """The emitted ``.line`` as the adoption report reads it: the blocks end to end.

    Under ``--adopt-retail-meta`` retail's chunk is what the image carries, so the emitted
    table is only the *measurement* of how many statement records the source produced.
    A compiler that sinks a record (MWCC folds ``d7 = nLow[*a0]`` into the next statement's
    line) leaves a block shorter than retail's, and a normalised layout can leave one
    longer; neither is an incomplete unit once ``.text`` is retail's.  The blocks are
    therefore concatenated in retail's function order instead of being padded into retail's
    pinned offsets: a pinned-length slot would need zero fill, and a zero-filled gap is not
    a parseable run of statement tables.

    ``blocks`` is the same ``[(offset, pinned size, section index, label)]`` :func:`_fill`
    takes; the offsets are not used, because the report compares row counts, not placement.
    """
    sizes = []
    bodies = []
    for _offset, pinned, index, label in blocks:
        body = relocate(mw.data(index), mw.relocs.get(index, ()),
                        lambda symbol: mw.resolve(tu, symbol), f"{label}.line", gp)
        sizes.append((label, ".line", len(body), pinned))
        bodies.append(body)
    return b"".join(bodies), sizes


def _retail_chunk(image, section: str, offset: int, size: int) -> bytes:
    """``size`` bytes of retail's ``section`` at the unit's pinned chunk ``offset``."""
    entry = next((s for s in image.sections if s.name == section), None)
    if entry is None:
        raise Unusable(f"{image.path}: no {section} section")
    return image.data[entry.offset + offset:entry.offset + offset + size]


def _first_difference(left: bytes, right: bytes) -> int:
    """The first byte index at which two byte strings differ (or the shorter length)."""
    for index, (one, other) in enumerate(zip(left, right)):
        if one != other:
            return index
    return min(len(left), len(right))


def debug_promotion(unit: str, *, text: bytes, line: bytes, debug: bytes,
                    retail_text: bytes, retail_line: bytes, retail_debug: bytes,
                    base: int = 0, block_mismatches=(), normalise: bool = False,
                    adopt: bool = False, allow_line: bool = False) -> bytes:
    """The four conditions, and the bytes the image should carry for this unit.

    Condition 1 (``.text`` and ``.line`` byte-equal) is checked here rather than in
    :func:`place`'s size checks because a same-size instruction difference is invisible to
    a length test, and this is the one path that would otherwise accept it.  Condition 2
    (retail's chunk length and DIE count) and condition 3 (the DIE multiset, with only
    ``@anonN`` normalised) are :mod:`toolchain.debug_set`'s.  Condition 4 is every other
    case: a missing or extra DIE, a changed member, a different tag, a different length --
    the refusal names the first offending DIE.

    On acceptance the retail chunk is returned, not the emitted one: the deviation is the
    compiler's ``@anonN`` assignment, and keeping retail's structurally-equal bytes in the
    image is what leaves G1 the pin.  The printed line names the boundary and the measured
    permutation, which is the record the unit's ``tu_builds`` comment quotes.

    ``normalise`` is the opt-in stronger step (:mod:`toolchain.debug_normalize`): rather than
    keeping retail's chunk, rewrite our own into retail's DIE order and accept it **only** if
    the result is retail's bytes.  It is off unless the caller asks for it, and on acceptance
    it prints that it normalised, with the counts the unit's record quotes.

    ``adopt`` is the other opt-in step (:mod:`toolchain.debug_adopt`), and it relaxes
    condition 1 for ``.line`` only: ``.text`` must still be byte-identical -- the callers
    that pass ``adopt`` print exactly that refusal -- and then retail's ``.line`` chunk and
    the ``AT_location`` values of locals whose records otherwise match are adopted.  The
    whole ``.debug`` chunk must come out retail's byte for byte, or the unit refuses.

    ``allow_line`` is the measurement seam for :mod:`toolchain.line_reflow`'s normalising
    mode: the ``.line`` half of condition 1 is skipped and the emitted chunk is returned
    unchanged, so a caller can count the rows that would differ from retail's without
    adopting anything.  ``.text`` is still required to be retail's.
    """
    if adopt:
        if normalise:
            raise Unusable(f"{unit}: --adopt-retail-meta and --normalise-debug are "
                           f"different claims; pass one")
        if text != retail_text:
            at = _first_difference(text, retail_text)
            raise Unusable(
                f"{unit}: refusing to adopt retail's metadata: condition 1 "
                f"({debug_set.LABEL[1]}) failed: .text is 0x{len(text):X} bytes against "
                f"retail's 0x{len(retail_text):X}, first differing byte at 0x{at:X}; "
                f"adoption needs retail's instructions, byte for byte")
        # A block that is longer than retail's is the extra-record case adoption drops; a
        # shorter one is missing records, which the step refuses when it pairs the DIEs.
        try:
            adopted = debug_adopt.adopt(debug, retail_debug, base, line, retail_line)
        except debug_adopt.Refused as exc:
            raise Unusable(f"{unit}: condition 6 (retail metadata adoption) failed: {exc}")
        if adopted.line != retail_line:
            raise Unusable(f"{unit}: condition 6 (retail metadata adoption) failed: the "
                           f"adopted .line is not retail's {len(retail_line):#x} bytes")
        counts = f"emitted {adopted.line_emitted} record(s), adopted {adopted.line_total}"
        if adopted.line_note:
            print(f"compile: {unit}: the emitted .line is not row-for-row comparable with "
                  f"retail's ({counts}: {adopted.line_note}); retail's chunk is adopted "
                  f"whole", file=sys.stderr)
        else:
            first = ""
            if adopted.first_line_row is not None:
                _table, _row, offset, before, after = adopted.first_line_row
                first = (f", first at .line+0x{offset:X}: {before}"
                         + (f" -> {after}" if after is not None else " (absent in retail)"))
            print(f"compile: {unit}: adopted retail's .line ({counts}; "
                  f"{adopted.line_changed} row(s) changed by statement line{first}; "
                  f"{len(adopted.line_rows)} of {adopted.line_total} rows byte-different "
                  f"in {adopted.line_tables} statement table(s))", file=sys.stderr)
        for change in adopted.locations:
            print(f"compile: {unit}: adopted AT_location {change}", file=sys.stderr)
        for change in adopted.anon_names:
            print(f"compile: {unit}: adopted anonymous name {change}", file=sys.stderr)
        for where, code in adopted.adopted_attributes:
            print(f"compile: {unit}: adopted attribute 0x{code:04X} on {where} "
                  f"(missing from the emitted record)", file=sys.stderr)
        for die, span in adopted.dropped:
            print(f"compile: {unit}: dropped extra DIE +0x{die.offset - base:X} "
                  f"{debug_set.TAG.get(die.tag, f'tag 0x{die.tag:02X}')}"
                  f"{f' {die.name!r}' if die.name else ''} (0x{span:X} bytes; no "
                  f"counterpart in retail)", file=sys.stderr)
        for old, new, where, code in adopted.reference_changes:
            print(f"compile: {unit}: rewrote reference 0x{old:08X} -> 0x{new:08X} "
                  f"(attribute 0x{code:04X} in {where})", file=sys.stderr)
        print(f"compile: {unit}: .debug is retail's 0x{len(retail_debug):X} bytes byte for "
              f"byte after adoption ({adopted.dies} DIEs)", file=sys.stderr)
        print(f"compile: {unit}: record in its tu_builds comment: .line and AT_location "
              f"adopted under --adopt-retail-meta, .debug byte-equal", file=sys.stderr)
        return adopted.chunk

    if text != retail_text:
        at = _first_difference(text, retail_text)
        raise Unusable(
            f"{unit}: condition 1 ({debug_set.LABEL[1]}) failed: .text is "
            f"0x{len(text):X} bytes against retail's 0x{len(retail_text):X}, first "
            f"differing byte at 0x{at:X}")
    if line != retail_line and not allow_line:
        at = _first_difference(line, retail_line)
        raise Unusable(
            f"{unit}: condition 1 ({debug_set.LABEL[1]}) failed: .line is "
            f"0x{len(line):X} bytes against retail's 0x{len(retail_line):X}, first "
            f"differing byte at 0x{at:X}")

    # A chunk that is already retail's needs no normalisation -- but the equality of one
    # part cannot stand in for the others: ``.text`` and ``.line`` above are checked first,
    # because the state this function stands for claims all three.  Only the ``adopt`` path
    # substitutes ``.line`` by design, and it returned above.
    if debug == retail_debug and not block_mismatches:
        return debug

    if block_mismatches:
        label, emitted, pinned, block = block_mismatches[0]
        detail = (f"{label} .debug is short by 0x{pinned - emitted:X} bytes"
                  if emitted < pinned else
                  f"{label} .debug is 0x{emitted - pinned:X} bytes too large")
        raise Unusable(f"{unit}: condition 2 ({debug_set.LABEL[2]}) failed: {detail}; "
                       f"C is incomplete (cannot pad .debug); "
                       f"{block.detail or 'the block differs'}")

    outcome = debug_set.classify(debug, retail_debug, base)
    if not outcome.ok:
        raise Unusable(f"{unit}: {outcome.message}")

    if normalise:
        try:
            result = debug_normalize.normalise(debug, retail_debug, base)
        except debug_normalize.Refusal as exc:
            raise Unusable(f"{unit}: condition 5 (.debug DIE-order normalisation) failed: "
                           f"{exc}")
        if result.chunk != retail_debug:
            at = _first_difference(result.chunk, retail_debug)
            raise Unusable(
                f"{unit}: condition 5 (.debug DIE-order normalisation) failed: the "
                f"normalised chunk is 0x{len(result.chunk):X} bytes against retail's "
                f"0x{len(retail_debug):X}, first differing byte at 0x{at:X}")
        print(f"compile: {unit}: .debug normalised to retail's DIE order "
              f"(0x{len(retail_debug):X} bytes, {result.dies} DIEs, {result.moved} moved, "
              f"{result.references} references rewritten) and byte-identical to retail",
              file=sys.stderr)
        print(f"compile: {unit}: record in its tu_builds comment: .debug DIE order "
              f"normalised under --normalise-debug, byte-equal", file=sys.stderr)
        return result.chunk

    print(f"compile: {unit}: .debug set-equal under the anonymous-type DIE-order boundary "
          f"(0x{len(retail_debug):X} bytes, {outcome.die_count} DIEs, "
          f"{outcome.permuted} of {outcome.anonymous} @anonN indices permuted); "
          f".text and .line are byte-equal, retail's .debug chunk is kept in the image",
          file=sys.stderr)
    print(f"compile: {unit}: record in its tu_builds comment: .debug set-equal, not "
          f"byte-equal (anonymous-type DIE order: {outcome.permuted} of "
          f"{outcome.anonymous} @anonN indices permuted)", file=sys.stderr)
    return retail_debug


def _fill_debug(mw: MWObject, tu: Tu, base: int, size: int, blocks, gp: int,
                rename=None, retail_chunk: bytes = b"") -> tuple[bytes, list, list]:
    """The unit's ``.debug`` candidate, assembled without refusing on length.

    Length is a condition :func:`debug_promotion` reports (with the offending DIE), not a
    reason to stop assembling here: a short block leaves a gap and a long one extends the
    candidate, and both are visible to the whole-chunk comparison.  Blocks are placed at
    the offsets retail pinned, which is what makes a DIE's position comparable.

    A block whose length is not retail's is returned as a mismatch too.  Without that, a
    short block whose missing bytes happened to be trailing nulls could leave the *chunk*
    the right length and the DIE count unchanged, and the whole-chunk comparison would
    accept a block that is not retail's.
    """
    bodies = []
    for offset, pinned, index, label in blocks:
        body = relocate(mw.data(index), mw.relocs.get(index, ()),
                        lambda symbol: mw.resolve(tu, symbol), f"{label}.debug", gp)
        if rename is not None:
            body = retail_name_in(body, *rename)
        bodies.append((offset - base, pinned, body, label))
    end = max([size] + [at + len(body) for at, _pinned, body, _label in bodies])
    out = bytearray(end)
    sizes, mismatches = [], []
    for at, pinned, body, label in bodies:
        out[at:at + len(body)] = body
        sizes.append((label, ".debug", len(body), pinned))
        if len(body) != pinned:
            retail_block = retail_chunk[at:at + pinned]
            mismatches.append((label, len(body), pinned,
                               debug_set.classify(body, retail_block, at + base)))
    return bytes(out), sizes, mismatches


def include_flags(target) -> list:
    """The ``-I`` flags that put ``target``'s generated headers on the compiler's search path.

    ``place`` stages the source under ``/tmp`` before compiling it, so the one directory MWCC
    searches for a quoted ``#include`` -- the source's own -- holds a scratch copy of the C
    and none of the headers, and ``probe._invoke`` runs the compiler with its *installation*
    directory as the working directory.  Without these flags a unit whose types live further
    up the type closure than its own header -- the generated headers under ``include/`` are
    the only way a unit with low statement numbers can declare types it cannot inline without
    moving its statements -- cannot compile at all:

        #include "src/AM/s573/doll/dexport.h"
        Error: the file 'src/AM/s573/doll/dexport.h' cannot be opened

    The directories come from the target descriptor
    (:attr:`config.targets.Target.include_paths`), never from a spelling of this driver's own,
    and each is passed absolute the way the source and the object already are: the compiler
    resolves a relative ``-I`` against its own working directory, which sits under the
    toolchain symlink and is therefore not a path this tree can name.

    ``-I`` cannot change codegen -- measured on this target: the compiler's ``.text`` is
    byte-identical with and without it -- so this is the one flag the recorded pair
    (``tu_builds``) does not have to carry.  (The generated headers' own *spelling* is not
    free for a unit that includes them: MWCC's DWARF records offsets that follow the length of
    the path a header was opened through, while the path itself never appears in the payload.)
    """
    flags = []
    for directory in target.include_paths:
        if not directory.is_dir():
            raise Unusable(
                f"{_display(directory)} is not a directory: the target's include path is "
                f"where the oracle writes the headers a unit includes, so it has to exist "
                f"before that unit can compile")
        flags.append(f"-I{directory}")
    return flags


#: What a promoted source that still carries a ``#line`` directive is told to run.  The
#: rewrite is a step *before* promotion, never something the build does behind the caller's
#: back: `place` used to reflow such a source in a staged copy, which meant a directive-laden
#: file could be committed and built while the file a reader sees was not the one compiled.
LINE_REMEDY = "python3 tools/toolchain/line_reflow.py {file} --normalise"


def refuse_line_directives(file: str, text: str) -> None:
    """Refuse a promoted source that still carries ``#line`` directives.

    A promoted source is the evidence for the bytes: the file says what the compiler saw.  A
    ``#line`` directive renumbers what a reader -- and ``git diff`` -- sees, and the rewrite
    that removes it can move ``.line`` rows (which only retail adoption may hide), so the
    build refuses rather than rewriting a scratch copy the caller never sees.  The message
    names the file, how many directives are there, and the one command that removes them.
    """
    count = line_reflow.directive_count(text)
    if not count:
        return
    raise Unusable(
        f"{file}: {count} #line directive(s); a promoted source carries none: run "
        + LINE_REMEDY.format(file=file))


def place(tu: Tu, manifests: Manifests, compiler_dir, wibo, flags, keep=None,
          normalise: bool = False, adopt: bool = False,
          source_text: bytes | None = None) -> Placed:
    """Compile ``tu`` and place it: the unit's bytes, as the pinned layout has them.

    ``source_text`` overrides the file's bytes (the reflow step's before/after check and
    :mod:`toolchain.line_reflow` use it); the staged path, and therefore the source name
    the compiler records, is the same either way.

    A source that carries ``#line`` directives is refused by
    :func:`refuse_line_directives`, before the compiler, the manifests or the toolchain are
    touched: the directive's removal is a promotion step (``line_reflow.py``), and the build
    must compile the bytes the committed file spells.
    """
    if source_text is None:
        if not tu.source.is_file():
            raise Unusable(f"{tu.source.relative_to(REPO_ROOT)} does not exist")
        source_text = tu.source.read_bytes()
    refuse_line_directives(tu.file, source_text.decode("latin-1"))
    return _place_source(tu, manifests, compiler_dir, wibo, flags, source_text, keep,
                         normalise, adopt)


def _place_source(tu: Tu, manifests: Manifests, compiler_dir, wibo, flags, source: bytes,
                  keep=None, normalise: bool = False, adopt: bool = False,
                  allow_line: bool = False) -> Placed:
    """Compile one spelling of the unit's source and place its bytes.

    :func:`place` owns the refusal of ``#line`` directives and the read of the file; this is
    the promotion itself, unchanged, and it is also what :mod:`toolchain.line_reflow` calls to
    compile the *before* spelling -- the one still carrying directives -- that its rewrite is
    checked against.
    """
    staged = staged_path(tu)
    staged.parent.mkdir(parents=True, exist_ok=True)
    staged.write_bytes(source)
    recorded = recorded_name(staged)
    if len(recorded) != len(tu.name):
        raise Unusable(f"staging {staged} spells {len(recorded)} bytes, retail "
                       f"{len(tu.name)}")

    obj = pathlib.Path(keep) if keep else BUILD / "cc" / (tu.file + ".mw.o")
    probe.compile(staged, obj, compiler_dir, wibo,
                  [*flags, *include_flags(manifests.target)])

    mw = MWObject(obj, manifests)
    gp = gp_value(manifests.target.elf)
    manifests.prefer_source(tu.file)
    placed_data = []
    for name, address, size, extent, relocs in verify_data(mw, manifests, tu.file,
                                                           manifests.target):
        body, section_relocs = _data_only_section(mw, name)
        placed_data.append((name, body, section_relocs,
                            lambda symbol: manifests.address_of(symbol.name)))
        print(f"compile: {tu.file}: {name} at 0x{address:08X} is the retail datum "
              f"({size:#x} bytes, {relocs} relocation(s), extent {extent:#x})",
              file=sys.stderr)
    groups = mw.groups(tu)

    text_start, text_end = _split_extent(tu, manifests)
    text_size = text_end - text_start
    text = bytearray(text_size)
    labels, sizes, body_spans = [], [], []
    for function in tu.functions:
        body = relocate(mw.data(groups[function.name][0]),
                        mw.relocs.get(groups[function.name][0], ()),
                        lambda symbol: mw.resolve(tu, symbol), f"{function.name}.text", gp)
        if len(body) != function.size:
            shortfall = function.size - len(body)
            detail = (f"short by 0x{shortfall:X} bytes" if shortfall > 0
                      else f"0x{-shortfall:X} bytes too large")
            raise Unusable(
                f"{tu.file}: condition 1 ({debug_set.LABEL[1]}) failed: .text "
                f"{function.name} is {detail}; C is incomplete")
        at = function.address - text_start
        text[at:at + len(body)] = body
        body_spans.append((at, len(body)))
        labels.append((at, function.name, body))
        sizes.append((function.name, ".text", len(body), function.size))

    retail = elf.Elf(str(manifests.target.elf))
    expected_text = retail.read(text_start, text_size)
    text = bytearray(_text_extent(bytes(text), expected_text, body_spans,
                                  tu.end - text_start, tu.file))

    types = manifests.cus[tu.records[0]]
    # `.line` first: condition 1 pairs it with `.text`, and the `.debug` policy needs both.
    # Under adoption the emitted table is only the report's measurement (retail's chunk is
    # placed), so a block that is not retail's length is measured rather than refused.
    line_blocks = [(f.line_offset, f.line_size, groups[f.name][2], f.name)
                   for f in tu.functions]
    if adopt:
        line, line_sizes = _adopted_line(mw, tu, line_blocks, gp)
    else:
        line, line_sizes = _fill(mw, tu, tu.line_offset, tu.line_size, line_blocks, gp,
                                 ".line", unit_file=tu.file)
    retail_debug = _retail_chunk(retail, ".debug", tu.debug_offset, tu.debug_size)
    retail_line = _retail_chunk(retail, ".line", tu.line_offset, tu.line_size)
    emitted_debug, debug_sizes, debug_mismatches = _fill_debug(
        mw, tu, tu.debug_offset, tu.debug_size,
        [(types["offset"], types["size"], mw.section_named(".debug"), "the unit's types")]
        + [(f.debug_offset, f.debug_size, groups[f.name][1], f.name) for f in tu.functions],
        gp, (recorded, tu.name.encode()), retail_chunk=retail_debug)
    debug = debug_promotion(
        tu.file, text=bytes(text), line=line, debug=emitted_debug, retail_text=expected_text,
        retail_line=retail_line, retail_debug=retail_debug, base=tu.debug_offset,
        block_mismatches=debug_mismatches, normalise=normalise, adopt=adopt,
        allow_line=allow_line)
    return Placed(bytes(text), debug, retail_line if adopt else line, labels,
                  sizes + debug_sizes + line_sizes,
                  normalised=normalise and emitted_debug != retail_debug,
                  adopted=adopt, emitted_line=line, data=placed_data)


def retail_bytes(tu: Tu, retail=RETAIL, text_size=None) -> dict:
    """The unit's bytes in the retail image: its replaced text extent and payloads."""
    image = elf.Elf(str(retail))
    text = image.read(tu.address, tu.end - tu.address if text_size is None else text_size)
    spans = {}
    for section, (base, size) in ((".debug", (tu.debug_offset, tu.debug_size)),
                                  (".line", (tu.line_offset, tu.line_size))):
        entry = next((s for s in image.sections if s.name == section), None)
        if entry is None:
            raise Unusable(f"{retail}: no {section} section")
        spans[section] = image.data[entry.offset + base:entry.offset + base + size]
    return {"text": text, "debug": spans[".debug"], "line": spans[".line"]}


def compare(tu: Tu, placed: Placed, retail=RETAIL) -> dict:
    """Per part: ``(ok, detail)`` -- what the gates would say, for the selection loop."""
    want = retail_bytes(tu, retail, text_size=len(placed.text))
    mine = {"text": placed.text, "debug": placed.debug, "line": placed.line}
    out = {}
    for part, expected in want.items():
        got = mine[part]
        if got == expected:
            out[part] = (True, f"{len(expected)} bytes")
        elif len(got) != len(expected):
            out[part] = (False, f"{len(got)} bytes, retail has {len(expected)}")
        else:
            at = next(i for i, (a, b) in enumerate(zip(got, expected)) if a != b)
            out[part] = (False, f"{len(got)} bytes, first difference at 0x{at:X}")
    return out




# ---------------------------------------------------------------------------
# entry point
# ---------------------------------------------------------------------------


def _display(path) -> str:
    """A path as a reader types it: repo-relative when it is inside the repo."""
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _data_only_section(mw: MWObject, name: str):
    """The section a data placement's symbol alone occupies, and its relocations.

    A placement is *per symbol*: the link places this section at the symbol's retail address,
    so the section must carry that symbol and nothing else (offset 0, whole extent).  A section
    with another datum in it would move that datum too, which is exactly the section-driven
    placement this path exists to avoid.
    """
    symbol = next((s for s in mw.elf.symbols if s.name == name and s.shndx != 0), None)
    if symbol is None:
        raise Unusable(f"{_display(mw.path)}: no definition of the data symbol {name!r}")
    index = symbol.shndx
    body = mw.data(index)
    others = [s.name for s in mw.elf.symbols
              if s.shndx == index and s.name not in (name, "")]
    if symbol.value != 0 or len(body) != symbol.size or others:
        raise Unusable(
            f"{_display(mw.path)}: {name} shares its section ({len(body):#x} bytes) with "
            f"{', '.join(others) or 'a non-zero offset'}; a data placement must own the "
            f"section it places")
    return body, mw.relocs.get(index, ())


def verify_data(mw: MWObject, manifests: Manifests, source: str, target=None) -> list:
    """Check every data placement ``source`` defines against the retail bytes it names.

    The object's bytes are relocated symbolically (its relocations are not patched with retail
    addresses in the file), then compared byte for byte with the retail image at the recorded
    address, and the zero fill retail shows to the recorded extent is required to be zero.
    This is the local proof; G1 remains the whole-image backstop.
    """
    target = target or manifests.target
    records = [r for r in data_placements(target) if r["source"] == source]
    if not records:
        return []
    image = elf.Elf(str(target.elf))
    gp = gp_value(target.elf)
    report = []
    for record in records:
        body, relocs = _data_only_section(mw, record["name"])
        if len(body) != record["size"]:
            raise Unusable(
                f"{source}: {record['name']} is {len(body):#x} bytes, the placement records "
                f"{record['size']:#x}; the placement ledger and the C disagree")
        placed = relocate(body, relocs,
                          lambda symbol: manifests.address_of(symbol.name),
                          f"{record['name']}.data", gp)
        retail = image.read(record["address"], record["size"])
        if placed != retail:
            at = _first_difference(placed, retail)
            raise Unusable(
                f"{source}: {record['name']} is not the retail datum at "
                f"0x{record['address']:08X}: first differing byte at +0x{at:X} "
                f"({placed[at]:#04x} against {retail[at]:#04x})")
        pad = record["extent"] - record["size"]
        fill = image.read(record["address"] + record["size"], pad)
        if any(fill):
            raise Unusable(
                f"{source}: the {pad:#x}-byte extent after {record['name']} is not zero in "
                f"retail; the placement must not claim another datum's bytes")
        report.append((record["name"], record["address"], record["size"], record["extent"],
                       len(relocs)))
    return report


def data_build(source, out, flags, compiler: str, target=None, manifests=None) -> list:
    """Compile a data-only source and verify its placements (the ``--data`` rule).

    Data-only sources carry no retail DWARF -- they are compiled without ``-g`` on purpose, so
    the unit whose data they define keeps retail's ``.debug`` chunk unchanged.  The object is
    written raw: the link places the section itself, it is not wrapped in a placed object.
    """
    target = target or DEFAULT_TARGET
    manifests = manifests if manifests is not None else Manifests(target)
    if not [r for r in data_placements(target) if r["source"] == source]:
        raise Unusable(f"{source}: no data placement record names it")
    probe.compile(source, out, fetch.compiler(compiler), fetch.wibo(),
                  [*flags, *include_flags(target)])
    return verify_data(MWObject(out, manifests), manifests, source, target)


def build(tu: Tu, out: pathlib.Path, flags, compiler: str, manifests=None,
          keep=None, target=None, normalise: bool = False,
          adopt: bool = False) -> Placed:
    """Everything the ``cc`` rule does: compile, place, and write ``out``."""
    target = target if target is not None else DEFAULT_TARGET
    manifests = manifests if manifests is not None else Manifests(target)
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    placed = place(tu, manifests, compiler_dir, wibo, flags, keep=keep,
                   normalise=normalise, adopt=adopt)
    assemble(assembly(len(placed.text), placed.labels, placed.debug, placed.line,
                      placed.data), out)
    return placed


def syntax_only(source, flags, compiler: str, includes=()) -> int:
    """Compile ``source`` with the retail compiler and throw the object away.

    Returns the compiler's exit status -- 0 it accepted the file, 1 it did not, with its own
    diagnostics on stderr -- which is the whole point: a generated header is checked by
    ``mwccps2 -lang c``, the compiler the units are measured against, not by a host ``cc``.
    ``includes`` are added with ``-I`` (MWCC wants the directory joined to the flag), and
    nothing survives the call, so the check cannot be mistaken for a build.
    """
    source = pathlib.Path(source).expanduser()
    if not source.is_file():
        raise Unusable(f"{source} does not exist")
    command = list(flags or DEFAULT_FLAGS)
    for directory in includes:
        directory = pathlib.Path(directory).expanduser().resolve()
        if not directory.is_dir():
            raise Unusable(f"{directory} is not a directory: --include wants one")
        command.append(f"-I{directory}")
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    with tempfile.TemporaryDirectory(prefix="cc-syntax-") as scratch:
        obj = pathlib.Path(scratch) / (source.stem + ".mw.o")
        try:
            probe.compile(source, obj, compiler_dir, wibo, command)
        except probe.CompilerFailed as exc:
            print(f"compile.py: {exc}", file=sys.stderr)
            return 1
    print(f"cc --syntax-only {_display(source)}: accepted as C")
    return 0


def _parser(with_out: bool) -> argparse.ArgumentParser:
    """The CLI.  Two shapes, because mwcc's flags carry bare values.

    ``--syntax-only`` checks one file and writes nothing, so its parser has one positional
    and not two: with an optional ``out``, ``-lang c``'s value would be taken for the object
    path and the flag would reach the compiler stripped of its argument.
    """
    parser = argparse.ArgumentParser(prog="compile.py", description=__doc__.splitlines()[0])
    parser.add_argument("source",
                        help="the C source: as configure.py names it (src/...), or any file "
                             "with --syntax-only")
    if with_out:
        parser.add_argument("out", type=pathlib.Path, help="the object to write")
    parser.add_argument("--syntax-only", action="store_true",
                        help="ask the compiler whether the source is C and write nothing")
    parser.add_argument("--data", action="store_true",
                        help="compile a data-only source to a raw object and verify each of "
                             "its data placements against retail (no DWARF, no placement "
                             "wrapper)")
    parser.add_argument("--include", action="append", default=[], metavar="DIR",
                        help="add DIR to the compiler's include search path (repeatable; "
                             "with --syntax-only)")
    parser.add_argument("--compiler", default=fetch.REQUIRED,
                        help=f"the mwccps2 build to use (default: {fetch.REQUIRED})")
    parser.add_argument("--target", default=targets.DEFAULT,
                        help="the target whose manifests place the unit and whose retail "
                             f"binary it is compared with (default: {targets.DEFAULT}; "
                             f"known: {', '.join(targets.names())})")
    parser.add_argument("--keep", type=pathlib.Path, default=None,
                        help="where to keep the Metrowerks object the compiler writes")
    parser.add_argument("--compare", action="store_true",
                        help="also report each part against the retail image")
    opt = parser.add_mutually_exclusive_group()
    opt.add_argument("--normalise-debug", action="store_true",
                     help="opt in to the .debug DIE-order normaliser: re-emit our chunk "
                          "in retail's DIE order and accept it only if the result is "
                          "byte-identical; without it the set-equal gate keeps retail's "
                          "chunk (never silent: the normalisation is printed)")
    opt.add_argument("--adopt-retail-meta", action="store_true",
                     help="opt in to retail metadata adoption: .text must be byte-equal, "
                          "then retail's .line chunk and the AT_location of locals whose "
                          "records otherwise match are adopted and the whole .debug chunk "
                          "must be retail's byte for byte; every adopted value is printed")
    return parser


def main(argv=None) -> int:
    argv = list(sys.argv[1:] if argv is None else argv)
    # Everything else is a flag for mwccps2 (`-c`, `-lang c`, `-O3`, `-g`, ...), which is
    # why the rule can pass `$flags` after the two paths without a separator.
    parser = _parser(with_out="--syntax-only" not in argv)
    args, flags = parser.parse_known_args(argv)
    try:
        target = targets.get(args.target)
        if args.syntax_only:
            return syntax_only(args.source, flags, args.compiler, args.include)
        if args.data:
            report = data_build(args.source, args.out, flags or DEFAULT_FLAGS,
                                args.compiler, target)
            for name, address, size, extent, relocs in report:
                print(f"cc {args.source}: {name} at 0x{address:08X} is the retail datum "
                      f"({size:#x} bytes, {relocs} relocation(s), extent {extent:#x})")
            return 0
        manifests = Manifests(target)
        tu = manifests.tu_named(args.source)
        placed = build(tu, args.out, flags or DEFAULT_FLAGS, args.compiler, manifests,
                       keep=args.keep, target=target, normalise=args.normalise_debug,
                       adopt=args.adopt_retail_meta)
        shown = _display(args.out)
        print(f"cc {tu.file} [{target.name}]: {len(placed.text):#x} bytes of .text, "
              f"{len(placed.debug):#x} of .debug, {len(placed.line):#x} of .line -> {shown}")
        if args.compare:
            for part, (ok, detail) in compare(tu, placed, target.elf).items():
                note = (" [normalised: our DIE order re-emitted as retail's]"
                        if part == "debug" and placed.normalised and ok else "")
                if placed.adopted and ok and part in ("debug", "line"):
                    note = " [adopted: retail's bytes]"
                print(f"cc {tu.file}: {part} {'ok' if ok else 'DIFFERS'} ({detail}){note}")
        return 0
    except targets.UnknownTarget as exc:
        print(f"compile.py: error: {exc}", file=sys.stderr)
        return 2
    except probe.ProbeError as exc:  # the compiler failed: the source, or the flags
        print(f"compile.py: error: {exc}", file=sys.stderr)
        return 1
    except (Unusable, fetch.FetchError, check_deps.MissingDependency) as exc:
        print(f"compile.py: error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
