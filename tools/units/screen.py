#!/usr/bin/env python3
"""screen.py -- rank unpromoted translation units by expected matching ease.

``docs/unit-work.md`` says to pick a unit by *shape*, not by size, and names the shape
that has actually cost time:

* few functions, scalar code, no VU0 (``.vutext`` has its own blocker);
* no EE 128-bit GPR operations -- MWCC PS2 has no 128-bit operators, so a unit whose split
  carries ``pxor``/``pand``/``paddw``/... is unwritable in C (the 128-bit blocker class);
* no fixed absolute address outside the declared segments (a split whose memory access is a
  ``lui``+offset pair at an address no segment declares, which no C constant can reproduce);
* calls absent or already named in ``config/ddrex2p/borrowed_symbols.txt``;
* plenty of DWARF line records, because ``.line`` punishes guesswork hardest;
* little ``.text`` in absolute terms, and no single enormous function, because a unit is
  replicated instruction by instruction however few functions it declares.

Promoted units (a ``src/`` source *and* a ``tu_builds`` row) are not candidates and are
dropped from every printed row.  Risks that only change ``.debug`` -- the ``mes_*`` table and
array-DIE order, unreferenced file-scope tables -- are warnings, not blockers: under
``--adopt-retail-meta`` a byte-identical ``.text`` lets the pipeline drop our extra records,
adopt retail's DIE order and locations, and substitute retail's ``.line``.  A *missing* record
retail has is still refused, which is why an unreferenced array DIE stays a blocker.

It also refuses a unit whose split disassembly names a branch/call/address target the promotion
path cannot resolve.  That is the link's symbol set, not one ledger (``compile.py``,
``Manifests``): a split label the ld script places, a ``symbol_addrs.txt`` record, a ``-T``
assignment this layout holds an address for, or the one ``unplaced_symbols.txt`` reason
``compile.py`` reads as address 0.  What is left is two different refusals: a record outside
every declared segment -- an overlay window, ``NetRouterMain`` stored through
``%hi(D_008062B0)``, deferred by design -- and a name with no record anywhere.  The screen sees
the same operand text splat wrote, so the check costs one pass over the splits it already reads
and no compiler.

The units that failed for shape reasons -- ``el_mes.c``/the ``mes_*`` siblings,
``AM/s573/doll/vu0.c``, ``sys_demo.c``, ``lang.c`` and ``eyetoy/eye_filter.c`` (ranked #1 before
this signal existed) -- are the screen's acceptance test: a class it cannot see is reported as
unseen rather than silently scored.

Everything is measured from the repository, never compiled:

* ``config/ddrex2p/cus.json`` -- the unit list, function counts and source paths;
* ``orig/SLUS_211.74``'s DWARF via ``tools/oracle/dwarf1.py`` -- types, globals, line tables;
* ``asm/nonmatchings/main/*.s`` -- calls, address operands, VU0/FPU/128-bit-GPR instructions;
* ``config/ddrex2p/symbol_addrs.txt``, ``borrowed_symbols.txt`` and ``unplaced_symbols.txt``
  -- the oracle's ledgers, and ``undefined_{syms,funcs}_auto.txt`` with the generated ld script
  -- the other half of the link's symbol set (``load_link_placement``).

Usage::

    python3 tools/units/screen.py                 # ranked candidates
    python3 tools/units/screen.py --all           # also the blocked units, with reasons
    python3 tools/units/screen.py --json          # machine-readable rows
    python3 tools/units/screen.py --markdown      # the table recorded in docs/milestones/

Exit codes: 0 a ranking was produced, 2 an input is missing or unreadable.

Costs, measured on this tree: DWARF parse ~0.5 s, reference graph ~0.4 s, the split listing ~1 s;
the whole screen ~2.4 s and no compiler, linker or build graph is touched.
"""

from __future__ import annotations

import argparse
import collections
import json
import os
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from dwarf1 import (AT_high_pc, AT_low_pc, AT_mod_u_d_type, AT_subscr_data,  # noqa: E402
                    AT_user_def_type, Dwarf, TAG_array_type, TAG_global_variable,
                    TAG_local_variable)
from demangle import cdecl  # noqa: E402

#: A file-scope array at least this large is the ``mes_*`` shape in ``docs/unit-work.md``.
LARGE_TABLE_BYTES = 256

#: More than this many file-scope array variables means the compiler's array-DIE order differs
#: (``lang.c`` has nine); one or two are ordinary data.  Debug-only since ``--adopt-retail-meta``.
ARRAY_ORDER_TABLES = 2

#: Size weights, in score points per KiB.  ``TOTAL_TEXT_WEIGHT`` charges the whole unit, so a
#: wide unit does not hide; ``LARGEST_TEXT_WEIGHT`` charges only the part of the largest
#: function above the free allowance.  One enormous function was previously ranked as easy
#: because the old score counted *functions*, not bytes.
TOTAL_TEXT_WEIGHT = 0.5
LARGEST_TEXT_WEIGHT = 3.0
LARGEST_TEXT_FREE_KIB = 1.0

#: Direct control-flow targets.  ``jalr`` is indirect and carries no name the screen can
#: resolve; computed targets have the same limitation.
_CALL_RE = re.compile(r"\bjal\s+([A-Za-z_.$][\w.$]*)")
_CONTROL_RE = re.compile(
    r"\b(jal|j|b|beq|bne|beqz|bnez|bgez|blez|bgtz|bltz|bgezal|bltzal|bc1f|bc1t|bc1fl|bc1tl)\s+(.+)$")
_ADDRESS_RE = re.compile(r"%(hi|lo|gp_rel|call16|got)\(([^)]+)\)")
_ENCODED_ADDR_RE = re.compile(r"^(?:func|D)_([0-9A-Fa-f]{8})$")

#: VU0 macro-mode operations.  The retail ELF is stripped of section names, so ``.vutext``
#: membership is inferred from the unit's own split: inline VU0 asm is the blocker, and it is
#: always present in such a function.
_VU0_RE = re.compile(r"\b(lqc2|sqc2|qmtc2|qmfc2|cfc2|ctc2|vmove|vadd|vsub|vmul|vmad|"
                     r"vmax|vmini|vabs|vdiv|vsqrt|vrsqrt|vwaitq|vnop|vcallms|vcall)\b")

#: EE 128-bit GPR ("quadword") *operations*.  This is ``docs/unit-work.md``'s 128-bit blocker
#: class: MWCC PS2 has no 128-bit operators, so **no C expression emits one of these** -- only
#: inline asm does, and that is a probe rather than a promotion.  Measured with the retail
#: compilers: ``^ & | + - * ~ ^=`` on ``u_long128`` is rejected by all five installed builds
#: with ``Error: illegal data size``, for parameters, locals, globals and dereferences alike.
#:
#: Deliberately absent, and the reason this signal is not just "starts with p":
#:
#: * ``lq``, ``sq`` and ``pcpyld`` are what *legal* ``u_long128`` C compiles to (assignment
#:   and constant materialisation).  ``eyetoy/eye_filter.c`` proves it in the tree: its
#:   neighbour ``sepia`` is expressible in C and contains ``pcpyld`` and ``sq``.
#: * ``pref`` is a prefetch hint, not a 128-bit operation.
#: * ``lqc2``/``sqc2``/``qmtc2``/``qmfc2`` are the VU0 signal's, not this one's.
_GPR128_RE = re.compile(
    r"\b(pxor|pand|por|pnor|"
    r"paddb|paddh|paddw|paddsb|paddsh|paddsw|paddub|padduh|padduw|"
    r"psubb|psubh|psubw|psubsb|psubsh|psubsw|psubub|psubuh|psubuw|"
    r"pcgtb|pcgth|pcgtw|pceqb|pceqh|pceqw|pmaxh|pmaxw|pminh|pminw|pabsh|pabsw|"
    r"psllh|psllw|psllvw|psrlh|psrlw|psrlvw|psrah|psraw|psravw|"
    r"ppacb|ppacw|ppach|pextlb|pextlh|pextlw|pextub|pextuh|pextuw|"
    r"pexch|pexcw|pexeh|pexew|pcpyh|pcpyud|prot3w|pinth|pinteh|plzcw|"
    r"pmulth|pmultw|pmultuw|phmadh|phmsbh|pmaddh|pmaddw|pmadduw|pmsubh|pmsubw|"
    r"pmfhl|pmfhi|pmflo|pmthi|pmtlo|qfsrv)\b")

#: FPU work is not wrong, but "scalar code" in the selection rule means you are less likely to
#: fight the scheduler over a vector/FPU expression shape.
_FPU_RE = re.compile(r"\b(lwc1|swc1|ldc1|sdc1|madd\.s|msub\.s|add\.s|sub\.s|mul\.s|div\.s|"
                     r"cvt\.s|cvt\.w|mov\.s|neg\.s|abs\.s|sqrt\.s)\b")

#: A fixed absolute address: ``lui`` of the high half, then the low half carried by the access
#: itself (``lui $1,(0x1030000 >> 16)`` + ``lw $3,-0x601C($1)``) or materialised into the same
#: register (``lui``+``ori``/``addiu``, which is what a *C constant* compiles to).
#:
#: Splat prints a numeric operand here exactly when the address has no name: a named one is
#: written ``%hi(symbol)``/``%lo(symbol)``, and that is the callee signal's business.  So a
#: numeric ``lui`` whose address lies outside every declared segment is a reference no ledger
#: can spell, and the two spellings differ in bytes: retail's ``lui``+offset is a relocation
#: pair (the assembler's ``$1``/``at``, one per access), while a C constant pools its high half
#: in an allocated register and pairs it with ``ori`` -- measured on ``net_game_help.c``'s
#: ``NetGameHelpDisp``, 155 of 172 words different for that reason alone.
_LUI_RE = re.compile(r"^lui\s+(\$\d+),\s*\(?(0x[0-9A-Fa-f]+)")
_IMM_RE = re.compile(r"^-?(?:0x[0-9A-Fa-f]+|\d+)$")
_MEMORY_RE = re.compile(r"^(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$(\d+)\)$")

#: Memory operations, split by which operand is written, so a load that reuses its own base
#: does not leave a stale constant behind.
_LOADS = frozenset({"lb", "lbu", "lh", "lhu", "lw", "lwu", "ld", "lwl", "lwr", "ll",
                    "lwc1", "lwc2", "ldc1", "lq"})
_STORES = frozenset({"sb", "sh", "sw", "sd", "swl", "swr", "sc", "swc1", "swc2", "sdc1",
                     "sq"})

#: A branch, jump or call ends the straight-line run the constants are tracked over: the
#: instruction after it belongs to another path (`dmm_sys_fade.s` reloads a *pointer* whose
#: register held a float constant in the previous block), and ``at``/`$1` is only live for the
#: pair that follows its ``lui``.
_FLOW_RE = re.compile(r"^(?:j|jal|jalr|jr|b|bal|beq|bne|beqz|bnez|bgez|bgezal|bgezall|bgtz|"
                      r"bgtzl|blez|blezl|bltz|bltzal|bltzall|bbit|bc1f|bc1fl|bc1t|bc1tl)$")

#: Caller-saved registers, clobbered by any call.
_CALLER_SAVED = tuple(f"${i}" for i in list(range(1, 16)) + [24, 25])

_SYMBOL_RE = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+)")

#: A bare assignment in a linker script: splat's ``undefined_{syms,funcs}_auto.txt`` and the
#: aliases ``configure.py`` writes into the ld script.  The link's other symbol source, and
#: the same line ``compile.py``'s ``LINK_ASSIGN`` reads.
_LINK_ASSIGN_RE = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+);")

#: Splat's block header, with the size when it printed one: ``nonmatching func_0011CEF0, 0xA8``.
#: A size-less block (data blobs and a handful of early splits) is measured one instruction at
#: a time instead; the instruction line is ``/* 1D0F0 0011CEF0 F0FFBD27 */  addiu ...``.
_NONMATCHING_RE = re.compile(r"^nonmatching\s+(\S+)(?:\s*,\s*(0x[0-9A-Fa-f]+))?\s*$")
_INSN_LINE_RE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s*\*/")
_BLOCK_END_RE = re.compile(r"^(?:endlabel|enddlabel)\b")

try:  # the registry is part of this tree; a tree without it is a loud failure elsewhere
    from config.targets import TARGETS as _TARGETS  # noqa: E402
except ImportError:  # pragma: no cover
    _TARGETS = None


# --------------------------------------------------------------------------- inputs


def load_symbol_addrs(path: pathlib.Path) -> tuple[dict[str, int], dict[int, str]]:
    """``name -> address`` and ``address -> name`` from a splat symbol file."""
    by_name: dict[str, int] = {}
    by_addr: dict[int, str] = {}
    for line in path.read_text().splitlines():
        m = _SYMBOL_RE.match(line)
        if not m:
            continue
        name, addr = m.group(1), int(m.group(2), 16)
        by_name[name] = addr
        by_addr.setdefault(addr, name)
    return by_name, by_addr


def load_unplaced(path: pathlib.Path) -> tuple[dict[str, dict], dict[int, str]]:
    """Load names the oracle found outside the target's declared segments.

    ``compile.py`` intentionally does not put these records in its address map: an overlay
    address is real, but this target has no placement for it.  Keeping the address-to-name
    index lets the screen recognize splat's ``D_XXXXXXXX`` spelling of a function pointer.
    """
    by_name: dict[str, dict] = {}
    by_addr: dict[int, str] = {}
    for line in path.read_text().splitlines():
        match = _SYMBOL_RE.match(line)
        if match is None:
            continue
        comment = line.split("//", 1)[1] if "//" in line else ""
        reason_match = re.search(r"\breason:(.*?)(?:\s+dwarf_name:|$)", comment)
        reason = reason_match.group(1).strip() if reason_match else ""
        name, address = match.group(1), int(match.group(2), 16)
        by_name[name] = {"address": address, "reason": reason}
        by_addr.setdefault(address, name)
    return by_name, by_addr


def load_link_placement(target=None) -> tuple[set[str], set[int]]:
    """Names and addresses the *generated link* resolves besides ``symbol_addrs.txt``.

    ``compile.py`` resolves a relocation against the link's own symbol set, not one ledger:
    the split objects its ld script lists (whose global labels are the split file names, read
    as ``split_names``) and its ``-T`` files' assignments -- ``undefined_{syms,funcs}_auto.txt``
    and the aliases ``configure.py`` writes into the ld script.  A ``-T`` assignment counts
    only where this layout holds its address, inside the declared segments; a target nobody
    has measured has no segments and so places none of them.  Reading the same three files
    under the same rule is what keeps the screen's verdict equal to the compiler's; before
    this, 1,146 in-segment split labels were reported as a ledger lookup gap that the
    promotion path had already stopped having.
    """
    target = _TARGETS.get() if target is None and _TARGETS is not None else target
    names: set[str] = set()
    addrs: set[int] = set()
    geometry = getattr(target, "geometry", None)
    if geometry is None:
        return names, addrs
    lo, hi = geometry.loadable_vram, geometry.bss_end
    paths = []
    for attr in ("undefined_syms", "undefined_funcs", "ld_script"):
        path = getattr(target, attr, None)
        if path is not None and pathlib.Path(path).is_file():
            paths.append(pathlib.Path(path))
    for path in paths:
        for line in path.read_text().splitlines():
            match = _LINK_ASSIGN_RE.match(line.strip())
            if match is None:
                continue
            address = int(match.group(2), 16)
            if lo <= address < hi:
                names.add(match.group(1))
                addrs.add(address)
    return names, addrs


def load_borrowed(path: pathlib.Path) -> tuple[set[str], set[int]]:
    """The byte-proven borrowed names, as names and as addresses."""
    names: set[str] = set()
    addrs: set[int] = set()
    for line in path.read_text().splitlines():
        m = _SYMBOL_RE.match(line)
        if m:
            names.add(m.group(1))
            addrs.add(int(m.group(2), 16))
    return names, addrs


def source_path(source: str) -> str:
    """Normalize a path in either form the inputs use.

    DWARF names are ``C:\\work2\\usaex2\\src\\CS\\lang.c`` and ``cus.json`` paths are
    ``src/CS/lang.c``; both become ``CS/lang.c``.  Anything not under ``src/`` is returned
    unchanged so a manifest oddity cannot silently join two different units.
    """
    posix = source.replace("\\", "/")
    if "/src/" in posix:
        return posix.split("/src/", 1)[1]
    if posix.startswith("src/"):
        return posix[len("src/"):]
    # Library objects (``C:\work2\ktps2\cd\libstr3.c``) are recorded by base name in cus.json.
    return posix.rsplit("/", 1)[-1]


def promotion_sources(tu_builds) -> set[str]:
    """``tu_builds`` entries as ``source_path``-relative keys (``sys/sys_scf.c``).

    The registry records ``src/sys/sys_scf.c``; the DWARF and ``cus.json`` use the same path
    without its leading ``src/``.  Normalising here keeps one spelling for the membership test.
    """
    sources = set()
    for entry in tu_builds or ():
        source = pathlib.PurePosixPath(str(entry[0]).replace("\\", "/"))
        if source.parts[:1] == ("src",):
            source = pathlib.PurePosixPath(*source.parts[1:])
        sources.add(str(source))
    return sources


def is_promoted(rel: str, tu_builds, root: pathlib.Path = REPO_ROOT) -> bool:
    """A promoted TU has both a committed ``src/`` source and a ``tu_builds`` row.

    Neither alone is a promotion: a source with no build row is a half-landed unit (warned
    about, not excluded), and a row with no source cannot be built.  Requiring both is the
    cutover rule the pipeline's own gates use.
    """
    return (root / "src" / rel).exists() and rel in promotion_sources(tu_builds)


def split_text_sizes(text: str) -> dict[str, int]:
    """Bytes of each ``nonmatching`` block in one split, keyed by block name.

    The size is the number splat printed on the block's ``nonmatching`` line; only when it is
    absent does the fallback count four bytes per instruction line in that block.  A split can
    carry data blocks after its function (``func_00106328.s`` ends with ``D_001063D0``), so the
    blocks are kept separate rather than summed.
    """
    blocks: list[dict] = []
    current: dict | None = None
    for line in text.splitlines():
        stripped = line.strip()
        match = _NONMATCHING_RE.match(stripped)
        if match:
            current = {"name": match.group(1),
                       "size": int(match.group(2), 16) if match.group(2) else None,
                       "instructions": 0}
            blocks.append(current)
            continue
        if current is not None and current["size"] is None and _INSN_LINE_RE.search(line):
            current["instructions"] += 1
        if _BLOCK_END_RE.match(stripped):
            current = None
    return {b["name"]: b["size"] if b["size"] is not None else b["instructions"] * 4
            for b in blocks}


def load_units(cus_path: pathlib.Path) -> "collections.OrderedDict[str, dict]":
    """The unit list from ``cus.json``: source path -> declared function count.

    ``cus.json`` is the repository's own count ("counts and paths come from
    ``config/ddrex2p/cus.json``" in ``docs/unit-work.md``).  The DWARF is used for names and
    bytes; this keeps the screen honest about which units exist even if the two disagree.
    """
    units: "collections.OrderedDict[str, dict]" = collections.OrderedDict()
    for entry in json.loads(cus_path.read_text()):
        if entry.get("kind") != "tu" or not entry.get("file"):
            continue
        rel = source_path(entry["file"])
        units.setdefault(rel, {"file": rel, "functions": 0})
    for entry in json.loads(cus_path.read_text()):
        if entry.get("kind") == "function" and entry.get("file"):
            rel = source_path(entry["file"])
            units.setdefault(rel, {"file": rel, "functions": 0})
            units[rel]["functions"] += 1
    return units


# --------------------------------------------------------------- DWARF type references


def build_reference_graph(dies) -> tuple[dict[int, set[int]], set[int]]:
    """Type-reference edges between DIEs, and the roots a *non-array* DIE references.

    The blocked class is "an array type nothing in the CU references", so reachability is the
    right question: an inner array of a two-dimensional array is referenced only by its parent
    array, and that is normal, while ``sys_demo.c``'s two arrays are referenced by nothing at
    all.  ``AT_sibling`` is deliberately ignored -- it is the DIE chain, and the milestone
    records that sys_demo's missing arrays are named only by siblings.  ``subscr_data`` is a
    byte block that can carry a user-defined element type at an unaligned offset, hence the
    4-byte window scan.
    """
    valid = set(dies)
    edges: dict[int, set[int]] = {}
    roots: set[int] = set()
    for die in dies.values():
        targets = edges.setdefault(die.off, set())
        for code, value in die.attrs.items():
            ref = None
            if code == AT_user_def_type and isinstance(value, int):
                ref = value
            elif code == AT_mod_u_d_type and isinstance(value, bytes) and len(value) >= 4:
                # Modifiers are the leading bytes; the DIE reference is the last four.
                ref = int.from_bytes(value[-4:], "little")
            if ref is not None and ref in valid:
                targets.add(ref)
                if die.tag != TAG_array_type:
                    roots.add(ref)
            elif code == AT_subscr_data and isinstance(value, bytes):
                for i in range(len(value) - 3):
                    ref = int.from_bytes(value[i:i + 4], "little")
                    if ref in valid:
                        targets.add(ref)
    return edges, roots


def reachable_offsets(edges: dict[int, set[int]], roots: set[int]) -> set[int]:
    """Every DIE offset reachable from a root, following array element-type edges."""
    reach = set(roots)
    stack = list(roots)
    while stack:
        for nxt in edges.get(stack.pop(), ()):
            if nxt not in reach:
                reach.add(nxt)
                stack.append(nxt)
    return reach


def type_text(dwarf: Dwarf, die) -> str:
    """A short C spelling for a type DIE, for the ranking's reasons."""
    tree = dwarf.array_type(die) if die.tag == TAG_array_type else dwarf.type_of(die)
    if not tree:
        return "?"
    try:
        return cdecl(tree)
    except ValueError:
        return "?"


# --------------------------------------------------------------------------- calls


def classify_calls(text: str, *, unit_functions: set[str], unit_lo: int | None,
                   unit_hi: int | None, by_name: dict[str, int], by_addr: dict[int, str],
                   borrowed_names: set[str], borrowed_addrs: set[int],
                   split_names: set[str]) -> dict[str, int]:
    """Classify every ``jal`` in one split.

    * ``internal`` -- a call to a function in this unit (its name and address are DWARF's);
    * ``borrowed`` -- resolved by ``borrowed_symbols.txt`` (the selection rule's happy case);
    * ``named`` -- any other name a symbol file already carries;
    * ``placeholder`` -- ``func_XXXXXXXX`` with a split but no symbol record: writable, but the
      C would need a name imported mid-unit (``el_mes.c``'s helper was this shape);
    * ``unknown`` -- no record and no split, so there is nothing to call.
    """
    counts = collections.Counter()
    for name in _CALL_RE.findall(text):
        addr = by_name.get(name)
        if name in unit_functions:
            counts["internal"] += 1
        elif addr is not None and unit_lo is not None and unit_lo <= addr < unit_hi:
            counts["internal"] += 1
        elif name in borrowed_names or (addr in borrowed_addrs):
            counts["borrowed"] += 1
        elif name in by_name or (addr is not None and name == by_addr.get(addr)):
            counts["named"] += 1
        elif name in split_names:
            counts["placeholder"] += 1
        else:
            counts["unknown"] += 1
    return dict(counts)


def _asm_line(line: str) -> str:
    """Drop splat's address comment before looking at instruction operands."""
    return re.sub(r"/\*.*?\*/", "", line)


def _reference_tokens(text: str):
    """Yield ``(kind, token)`` for relocatable control/address operands.

    Address pairs are included because a function pointer such as ``NetRouterMain`` is emitted
    as ``%hi(D_XXXXXXXX)``/``%lo(D_XXXXXXXX)`` rather than a ``jal``.  ``jalr`` and computed
    branches intentionally yield nothing: their target is not present in the split text.
    """
    for raw in text.splitlines():
        line = _asm_line(raw)
        for _kind, token in _ADDRESS_RE.findall(line):
            token = re.sub(r"\s*[+-]\s*0x[0-9A-Fa-f]+$", "", token).strip()
            yield "address", token
        match = _CONTROL_RE.search(line)
        if match is None:
            continue
        operands = match.group(2).split(",")
        yield "control", operands[-1].strip()


def find_unresolvable_references(text: str, *, unit_functions: set[str],
                                 unit_lo: int | None, unit_hi: int | None,
                                 by_name: dict[str, int], borrowed_names: set[str],
                                 split_names: set[str], unplaced: dict[str, dict],
                                 unplaced_by_addr: dict[int, str],
                                 link_names: set[str] | None = None) -> list[dict]:
    """Find named relocations that ``compile.py`` cannot resolve without compiling.

    A name resolves when the *link* resolves it: a split label the ld script places, a ledger
    record, a ``-T`` assignment this layout holds an address for (``link_names``, see
    ``load_link_placement``), or a borrowed name.  Only two things are left, and they are
    different refusals.  An unplaced record outside every declared segment is an overlay
    window this milestone does not model -- deferred by design.  A name in none of those sets
    has no record anywhere, and ``compile.py`` says so in those words.

    Unknown data-only operands are deliberately not treated as callees.  The one useful
    exception is an encoded address whose oracle record says it is an unplaced function (the
    ``D_008062B0`` spelling of ``NetRouterMain``).  This keeps the signal conservative while
    still catching function pointers visible in the split.
    """
    found: list[dict] = []
    seen: set[tuple[str, str]] = set()
    link_names = link_names or frozenset()
    for kind, token in _reference_tokens(text):
        if token.startswith(".L") or token in unit_functions:
            continue
        if token in by_name or token in borrowed_names:
            continue
        if token in split_names or token in link_names:
            continue
        record = unplaced.get(token)
        mapped_name = token
        address = None
        if record is not None:
            address = record["address"]
        else:
            encoded = _ENCODED_ADDR_RE.fullmatch(token)
            if encoded:
                address = int(encoded.group(1), 16)
                if (unit_lo is not None and unit_hi is not None
                        and unit_lo <= address < unit_hi):
                    continue
                mapped_name = unplaced_by_addr.get(address, token)
                record = unplaced.get(mapped_name)
        if record is not None:
            # ``compile.py`` substitutes address 0 for the one unplaced reason that retail's
            # DWARF itself gives no location; every other unplaced record is a real address
            # this layout does not model and is refused.
            if record["reason"].startswith("no AT_location"):
                continue
            key = (kind, token)
            if key not in seen:
                seen.add(key)
                found.append({"kind": kind, "target": token, "callee": mapped_name,
                              "address": address,
                              "reason": (f"{record['reason']} (overlay boundary: the target "
                                         "has no placement in this layout)")})
            continue
        # A func_XXXXXXXX in an address pair is still a code target, while an unknown D_
        # operand is an unnamed view of data the screen cannot classify from assembly.
        is_code_target = kind == "control" or token.startswith("func_")
        if not is_code_target:
            continue
        key = (kind, token)
        if key in seen:
            continue
        seen.add(key)
        reason = ("code target with no record anywhere: not a split label the link places, "
                  "not in symbol_addrs.txt, not in the link's -T files, and not in "
                  "unplaced_symbols.txt")
        found.append({"kind": kind, "target": token, "callee": token,
                      "address": address, "reason": reason})
    return found


def _instruction(raw: str) -> tuple[str, list[str]] | None:
    """``(opcode, operands)`` for one split line, or ``None`` for anything else.

    Splat writes one instruction per line as ``/* <rom> <va> <word> */  op  operands``; the
    address comment is dropped, directives (``.align``, ``.L…:``) are the caller's business.
    """
    line = _asm_line(raw).strip()
    if not line:
        return None
    match = re.match(r"^([a-z][a-z0-9._]*)\s*(.*)$", line)
    if match is None:
        return None
    operands = [operand.strip() for operand in match.group(2).split(",")] if match.group(2) else []
    return match.group(1), operands


def _immediate(token: str) -> int | None:
    """The value of a signed MIPS immediate operand, ``0x…`` or decimal."""
    token = token.strip()
    sign = -1 if token.startswith("-") else 1
    body = token.lstrip("+-")
    try:
        value = int(body, 16) if body.startswith("0x") else int(body)
    except ValueError:
        return None
    return sign * value


def fixed_absolute_addresses(text: str, top: int) -> list[dict]:
    """Fixed absolute addresses above ``top`` that one split uses as memory bases.

    The signal ``docs/unit-work.md`` records as the out-of-segment address class, measured on
    ``network/net_game/net_game_help.c``: retail's eight fields at ``0x01029FE4``,
    ``0x0102FACC`` and ``0x0102FE00-14`` sit above every declared segment, so the oracle can
    give them no name (``borrowed_symbols.txt`` is functions-only, and an out-of-segment
    unplaced record is refused rather than resolved to 0), and a C *constant* cannot stand in
    for retail's relocation -- ``lui``+``ori``/``addiu`` against ``lui``+offset.

    What is matched, in the disassembly splat writes:

    * ``lui $r, (0xVVVVVVVV >> 16)`` -- a numeric high half, which is also how splat spells a
      ``lui`` of a plain immediate; ``%hi(name)`` is not matched, because that has a name;
    * optionally chained into the same register by ``ori $r, $r, L`` (``base | L``) or
      ``addiu $r, $r, L`` (``base + sign_extend(L)``), the C-constant spelling;
    * then a load (``lb/lbu/lh/lhu/lw/lwu/ld/lwl/lwr/ll/lwc1/lwc2/ldc1/lq``) or a store
      (``sb/sh/sw/sd/swl/swr/sc/swc1/swc2/sdc1/sq``) of the form ``op $x, S($r)`` whose
      effective address ``base + S`` is still above ``top`` (the declared top, ``bss_end``).
      The access is required to be *straight-line* — the tracked constants are dropped at every
      label, branch, jump and call, and past a branch's delay slot — because the point of the
      signal is the base value itself, and a register reused in a later block
      (`dmm_sys_fade.s` loads a pointer through a register that held a float constant three
      blocks earlier) is not evidence about this one.  The delay slot itself *is* included: it
      runs with the constants the branch saw, and four splits in this tree (`NetGameOptInit2`,
      `NetGameOptPortSetInit`, `NetGameChallengeMain`, `NetInterErrGetStatus`) touch the band
      only there.

    Deliberately **not** matched, each with its measurement:

    * ``addu $1, $x, $1`` between the ``lui`` and the access.  That shape is the assembler's
      expansion of a *displacement* over a register -- ``lui at,1; addu at,ptr,at;
      lw rt,-0x62E0(at)`` is ``ptr + 0x9D20``, a struct field, not an address -- and the same
      bytes are also what an ``at``-based symbol-plus-index access looks like, so the two are
      not separable from the split.  Measured: 5 such constants below the image (`1`/`2`/`3`/
      `0xB`/`0xE` << 16) across 9 units, every one of them C-writable, plus 3 splits that use
      the band this way (`NetPadCon`, `NetReadDataGetStr`, `NetGamePrgGetWinLoseDraw`).
    * addresses *below* the declared base.  Nothing below ``loadable_vram`` was measured as a
      memory base in this tree (`lui $r, 0`/`0x10000` are the displacement expansion above, or
      counters), so only the "above every declared segment" half is reported; the other half
      would be a guess about addresses in the first megabyte.
    """
    const: dict[str, int | None] = {}
    found: dict[int, dict] = {}
    delay: dict[str, int | None] | None = None

    def forget() -> None:
        """Drop every tracked value: another path into the code, or another function."""
        const.clear()

    def record(register: str, offset: int, opcode: str, operand: str) -> None:
        base = const.get(register)
        if base is None:
            return
        address = (base + offset) & 0xFFFFFFFF
        if address > top and address not in found:
            found[address] = {"address": address, "base": base, "opcode": opcode,
                              "offset": offset, "operand": operand}

    for raw in text.splitlines():
        stripped = raw.strip()
        if stripped.startswith("."):
            forget()  # a directive, or a ``.L…:`` label: another path into this code
            delay = None
            continue
        parsed = _instruction(raw)
        if parsed is None:
            forget()  # unparsable: never pair a constant across it
            delay = None
            continue
        # The instruction right after a branch, jump or call is its delay slot: it still runs
        # with the constants the branch saw, and nothing after it does (``NetGameOptInit2``'s
        # only access is the ``sb`` in ``jal``'s delay slot).  Splat writes the delay slot on
        # its own line, indented, *after* the branch.
        in_delay_slot = delay is not None
        if in_delay_slot:
            const, delay = delay, None
        opcode, operands = parsed
        if opcode in ("glabel", "endlabel", "nonmatching", "alabel"):
            forget()
            continue
        if opcode == "lui" and len(operands) == 2:
            match = _LUI_RE.match(_asm_line(raw).strip())
            const[operands[0]] = int(match.group(2), 16) if match else None
            continue
        if opcode in ("ori", "or", "addiu", "addi", "daddiu") and len(operands) == 3:
            dest, source, imm = operands
            base = const.get(source)
            value = _immediate(imm) if _IMM_RE.match(imm) else None
            if base is None or value is None:
                const[dest] = None
            elif opcode in ("ori", "or"):
                const[dest] = (base | value) & 0xFFFFFFFF
            else:
                half = value - 0x10000 if value >= 0x8000 else value
                const[dest] = (base + half) & 0xFFFFFFFF
            continue
        if opcode in _LOADS or opcode in _STORES:
            if len(operands) >= 2:
                memory = _MEMORY_RE.match(operands[1])
                if memory is not None:
                    offset = _immediate(memory.group(1))
                    if offset is not None:
                        record("$" + memory.group(2), offset, opcode, _asm_line(raw).strip())
            if opcode in _LOADS and operands:
                const[operands[0]] = None
            continue
        if _FLOW_RE.match(opcode):
            delay = dict(const)  # what the delay slot, if any, still sees
            forget()
            if opcode == "jal":
                const.update({name: None for name in _CALLER_SAVED})
            continue
        if operands:
            const[operands[0]] = None
        if in_delay_slot:
            forget()  # past the delay slot the path is the branch's, not this run's
    return [found[address] for address in sorted(found)]


def score_unit(*, functions: int, statements: int, calls: dict, fp_functions: int,
               arrays: int, unresolvable: int = 0, text_bytes: int = 0,
               largest_function_bytes: int = 0) -> float:
    """Expected-ease score: few functions dominates, then size, then calls and line records.

    It is a tie-break among unblocked units, not a claim of certainty; every term is printed
    beside the unit as a reason.  The line-record term is a reward, not a gate: a unit with
    many statements gives ``.line`` evidence to follow, which is why the selection rule asks
    for it.

    The size terms are what stop a one-function unit from ranking as easy when that function
    is enormous: ``-0.5`` per KiB of the unit's whole ``.text``, and ``-3.0`` per KiB of the
    largest function above a free 1 KiB.  Both are measured from the split's ``nonmatching``
    line, so they are the bytes to be replicated, not the declared function count.
    """
    lines_per_function = (statements / functions) if functions else 0.0
    score = 100.0
    score -= 6.0 * max(0, functions - 1)
    score -= 25.0 * min(unresolvable, 8)
    score -= 2.0 * min(calls.get("placeholder", 0), 12)
    score -= 1.0 * min(calls.get("named", 0), 20)
    score -= 0.5 * min(calls.get("borrowed", 0), 20)
    score -= 3.0 * fp_functions
    score -= 0.02 * arrays
    score -= TOTAL_TEXT_WEIGHT * (text_bytes / 1024.0)
    score -= LARGEST_TEXT_WEIGHT * max(
        0.0, largest_function_bytes / 1024.0 - LARGEST_TEXT_FREE_KIB)
    score += min(10.0, lines_per_function)
    if statements >= 20:
        score += 2.0
    return score


# --------------------------------------------------------------------------- one unit


def analyze_unit(dwarf: Dwarf, rel: str, tu, *, units: dict, reachable: set[int],
                 by_name, by_addr, borrowed_names, borrowed_addrs, splits: pathlib.Path,
                 split_names: set[str], unplaced: dict | None = None,
                 unplaced_by_addr: dict[int, str] | None = None,
                 link_names: set[str] | None = None,
                 segments: tuple[int, int] | None = None,
                 tu_builds=()) -> dict:
    """Every signal for one unpromoted (or promoted) unit.  No I/O beyond its splits."""
    promoted = is_promoted(rel, tu_builds)
    source_without_build = (REPO_ROOT / "src" / rel).exists() and not promoted
    library = "/src/" not in tu.name.replace("\\", "/")
    functions = [f for f in tu.functions() if AT_low_pc in f.attrs]
    arrays = [c for c in tu.decl.children if c.tag == TAG_array_type]

    # Array DIEs that no variable, member, parameter or function references.  An array used
    # only as another array's element type does not count as referenced (mes_* chains).
    unreferenced_arrays = [c for c in arrays if c.off not in reachable]

    # File-scope tables: variables with an array type.  lang.c's nine statics are the shape
    # whose array-DIE order no declaration order controls.
    function_refs: set[int] = set()
    for f in functions:
        blob = f.attrs.get(0x2303, b"") if isinstance(f.attrs.get(0x2303), bytes) else b""
        for i in range(0, len(blob) - 3, 4):
            function_refs.add(int.from_bytes(blob[i:i + 4], "little"))

    tables, large_tables, unreferenced_tables = [], [], []
    for child in tu.decl.children:
        if child.tag not in (TAG_global_variable, TAG_local_variable) or not child.name:
            continue
        tree = dwarf.type_of(child)
        if not tree or tree[0] != "array":
            continue
        size = dwarf.sizeof(tree) or 0
        entry = {"name": child.name, "size": size, "referenced": child.off in function_refs}
        tables.append(entry)
        if size >= LARGE_TABLE_BYTES:
            large_tables.append(entry)
        if child.off not in function_refs:
            unreferenced_tables.append(entry)

    # Splits carry the calls and the instruction mix.
    line_counts: list[int] = []
    function_sizes: list[tuple[str, int]] = []
    vu_functions = 0
    fp_functions = 0
    quad_functions = 0
    quad_ops: "collections.Counter[str]" = collections.Counter()
    split_missing = 0
    calls = collections.Counter()
    unresolvable: list[dict] = []
    unresolved_seen: set[str] = set()
    addresses: list[dict] = []
    address_seen: set[int] = set()
    address_functions: set[str] = set()
    unit_functions = {f.name for f in functions if f.name}
    unit_lo = min((f.attrs[AT_low_pc] for f in functions), default=None)
    unit_hi = max((f.attrs[AT_high_pc] for f in functions), default=None)
    for f in functions:
        path = splits / f"{f.name}.s"
        if not path.exists():
            split_missing += 1
            continue
        text = path.read_text()
        lo, hi = f.attrs[AT_low_pc], f.attrs[AT_high_pc]
        sizes = split_text_sizes(text)
        size = sizes.get(f.name)
        # A split whose block header carries no name (or no size) falls back to the DWARF
        # function extent, which is the same bytes without trusting a block match.
        function_sizes.append((f.name, size if size is not None else hi - lo))
        if _VU0_RE.search(text):
            vu_functions += 1
        if _FPU_RE.search(text):
            fp_functions += 1
        quad = _GPR128_RE.findall(text)
        if quad:
            quad_functions += 1
            quad_ops.update(quad)
        if segments is not None:
            hits = fixed_absolute_addresses(text, segments[1])
            if hits:
                address_functions.add(f.name)
            for hit in hits:
                if hit["address"] in address_seen:
                    continue
                address_seen.add(hit["address"])
                addresses.append({**hit, "function": f.name})
        calls.update(classify_calls(text, unit_functions=unit_functions, unit_lo=unit_lo,
                                    unit_hi=unit_hi, by_name=by_name, by_addr=by_addr,
                                    borrowed_names=borrowed_names,
                                    borrowed_addrs=borrowed_addrs,
                                    split_names=split_names))
        for ref in find_unresolvable_references(
                text, unit_functions=unit_functions, unit_lo=unit_lo, unit_hi=unit_hi,
                by_name=by_name, borrowed_names=borrowed_names,
                split_names=split_names, unplaced=unplaced or {},
                unplaced_by_addr=unplaced_by_addr or {},
                link_names=link_names):
            if ref["target"] in unresolved_seen:
                continue
            unresolved_seen.add(ref["target"])
            unresolvable.append({**ref, "function": f.name})
        lo, hi = f.attrs[AT_low_pc], f.attrs[AT_high_pc]
        line_counts.append(sum(1 for addr, line in dwarf.line_table(f.cu)
                               if line and lo <= addr < hi))
    text_bytes = sum(size for _, size in function_sizes)
    largest_name, largest_bytes = max(function_sizes, key=lambda pair: pair[1],
                                      default=(None, 0))
    n = len(functions)
    statements = sum(line_counts)
    lines_per_function = (statements / n) if n else 0.0
    declared = units.get(rel, {"functions": n})["functions"]

    flags: list[str] = []
    reasons: list[str] = []
    warnings: list[str] = []

    if promoted:
        flags.append("promoted")
    if library:
        flags.append("library")
        reasons.append("library object (outside src/): its functions are linked, not reversed")
    if tu.overlay != "main":
        flags.append("overlay")
        reasons.append(f"overlay {tu.overlay}: no retail split in this target")
    if n == 0:
        flags.append("data-only")
        reasons.append("no functions: nothing to compile as C")
    if split_missing:
        flags.append("missing-splits")
        reasons.append(f"{split_missing} function split(s) missing")
    if vu_functions:
        flags.append("vu0")
        reasons.append(f"{vu_functions} function(s) use VU0 macro-mode operations "
                       "(the .vutext blocker, inferred; section names are stripped)")
    if quad_functions:
        flags.append("128-bit-gpr")
        shown_ops = ", ".join(sorted(quad_ops))
        reasons.append(f"{quad_functions} function(s) use EE 128-bit GPR operations "
                       f"({shown_ops}): MWCC has no 128-bit operators, so no C expression "
                       "produces them (the 128-bit blocker class; inline asm is the only "
                       "route, and that is a probe rather than a promotion)")
    if unreferenced_arrays:
        flags.append("unreferenced-arrays")
        shown = ", ".join(f"{type_text(dwarf, c)} @0x{c.off:X}"
                          for c in unreferenced_arrays[:3])
        warnings.append(f"{len(unreferenced_arrays)} array DIE(s) nothing references: {shown}"
                        " -- adoption can only drop our extra records, not fabricate a missing "
                        "one, so the DIE has to be emitted by an UNCALLED static that takes the "
                        "type (`static void *unused_decl(void) { return (void *)&name; }`), the "
                        "device that closed dmm_style and sys_demo.  .text is unaffected")
    if large_tables:
        flags.append("large-tables")
        shown = ", ".join(f"{t['name']} ({t['size']} B)" for t in large_tables[:3])
        warnings.append(f"{len(large_tables)} large file-scope table(s) (the mes_* "
                        f"debug-order class): {shown} -- .debug-only; adoption re-emits the "
                        "DIE order, drops our extra records and substitutes retail's .line "
                        "once .text is byte-identical")
    if unreferenced_tables:
        flags.append("unreferenced-tables")
        shown = ", ".join(t["name"] for t in unreferenced_tables[:3])
        warnings.append(f"{len(unreferenced_tables)} file-scope table(s) no function references "
                        f"(mes_* debug-order class): {shown} -- .debug-only under adoption")
    if len(tables) >= ARRAY_ORDER_TABLES and len(arrays) >= ARRAY_ORDER_TABLES:
        flags.append("array-die-order")
        warnings.append(f"{len(tables)} array tables / {len(arrays)} array DIEs: "
                        "array-DIE order is compiler-table order, not declaration order -- "
                        ".debug-only; adoption normalises retail's DIE order")
    if source_without_build:
        flags.append("source-unbuilt")
        warnings.append("src/ holds this unit's source but tu_builds has no row for it: not "
                        "promoted, and configure cannot build it")
    if unresolvable:
        flags.append("unresolvable-callees")
        shown = []
        for ref in unresolvable[:3]:
            where = f" at 0x{ref['address']:X}" if ref["address"] is not None else ""
            alias = (f" ({ref['callee']})" if ref["callee"] != ref["target"] else "")
            shown.append(f"{ref['target']}{alias}{where}: {ref['reason']}")
        reasons.append(f"{len(unresolvable)} branch/call target(s) the promotion path cannot "
                       f"resolve: " + "; ".join(shown))
    if addresses:
        flags.append("absolute-addresses")
        shown = []
        for hit in addresses[:3]:
            shown.append(f"0x{hit['base']:08X} ({hit['function']}: {hit['operand']} -> "
                         f"0x{hit['address']:08X})")
        span = ("above every declared segment" if segments is None
                else f"above the declared segments (top 0x{segments[1]:X})")
        warnings.append(f"{len(addresses)} fixed absolute address(es) {span}, used as a memory "
                       f"base by {len(address_functions)} of this unit's function(s): "
                       + "; ".join(shown) + " -- spell each as a file-scope `D_<ADDR>` macro "
                       "or a `unit_symbols.txt` extern (the incomplete-array form keeps it off "
                       "$gp); a literal C address compiles to lui+ori where retail's bytes are "
                       "a lui+offset relocation pair")

    # Blockers are the risks that change .text (or stop the unit compiling).  The array/table
    # classes are deliberately absent: they only differ in .debug, and --adopt-retail-meta
    # replaces retail's DIE order, locations and .line once .text is byte-identical.
    # ``absolute-addresses`` is measured advice, not a wall: an address outside every declared
    # segment is nameable by `unit_symbols.txt`, and net_game_help.c, net_sys_top.c and
    # net_sys_main.c all promoted that way.  Treating it as blocked kept promotable units out
    # of the dispatch list (net_sys_main sat at rank 56 behind it and promoted first try).
    blocked = any(flag in {"data-only", "overlay", "missing-splits", "vu0", "128-bit-gpr",
                           "library", "unresolvable-callees"} for flag in flags)

    score = score_unit(functions=n, statements=statements, calls=calls,
                       fp_functions=fp_functions, arrays=len(arrays),
                       unresolvable=len(unresolvable),
                       text_bytes=text_bytes, largest_function_bytes=largest_bytes)

    good = [
        f"{n} function{'s' if n != 1 else ''}",
        f"{statements} line record{'s' if statements != 1 else ''}"
        f" ({lines_per_function:.1f}/function)",
        (f"calls: {calls['borrowed']} borrowed, {calls['named']} named, "
         f"{calls['internal']} internal")
        if sum(calls.values()) else "no calls",
        "no array/table risk" if not arrays and not tables else
        f"{len(arrays)} array DIE(s), {len(tables)} file-scope table(s), all referenced",
        "no VU0" if not vu_functions else f"{vu_functions} VU0 function(s)",
        "no 128-bit GPR ops" if not quad_functions
        else f"{quad_functions} 128-bit GPR function(s)",
        "no fixed absolute addresses" if not addresses
        else f"{len(addresses)} fixed absolute address(es)",
        f"{text_bytes} B .text"
        + (f", largest {largest_name} {largest_bytes} B" if largest_name else ""),
        "scalar" if not fp_functions else f"{fp_functions} FPU function(s)",
        f"declared {declared} function(s) in cus.json",
    ]

    return {
        "file": rel,
        "overlay": tu.overlay,
        "promoted": promoted,
        "source_without_build": source_without_build,
        "declared_functions": declared,
        "functions": n,
        "statements": statements,
        "lines_per_function": round(lines_per_function, 2),
        "text_bytes": text_bytes,
        "largest_function": largest_name,
        "largest_function_bytes": largest_bytes,
        "arrays": len(arrays),
        "unreferenced_arrays": [
            {"offset": c.off, "type": type_text(dwarf, c)} for c in unreferenced_arrays],
        "tables": [{"name": t["name"], "size": t["size"], "referenced": t["referenced"]}
                   for t in tables],
        "large_tables": [t["name"] for t in large_tables],
        "unreferenced_tables": [t["name"] for t in unreferenced_tables],
        "vu_functions": vu_functions,
        "quad_functions": quad_functions,
        "quad_ops": sorted(quad_ops),
        "fp_functions": fp_functions,
        "split_missing": split_missing,
        "calls": dict(calls),
        "unresolvable": unresolvable,
        "addresses": addresses,
        "address_functions": len(address_functions),
        "flags": flags,
        "warnings": warnings,
        "blocked": blocked,
        "score": round(score, 2),
        "reasons": reasons,
        "good": good,
    }


# --------------------------------------------------------------------------- driver


def screen(elf: pathlib.Path, root: pathlib.Path = REPO_ROOT) -> list[dict]:
    """Analyze every unit.  Returns rows sorted easiest-first among unblocked units."""
    dwarf = Dwarf(str(elf))
    units = load_units(root / "config/ddrex2p/cus.json")
    by_name, by_addr = load_symbol_addrs(root / "config/ddrex2p/symbol_addrs.txt")
    borrowed_names, borrowed_addrs = load_borrowed(root / "config/ddrex2p/borrowed_symbols.txt")
    link_names, _link_addrs = load_link_placement()
    unplaced_path = root / "config/ddrex2p/unplaced_symbols.txt"
    unplaced, unplaced_by_addr = (load_unplaced(unplaced_path) if unplaced_path.is_file()
                                  else ({}, {}))
    edges, roots = build_reference_graph(dwarf.dies)
    reachable = reachable_offsets(edges, roots)
    splits = root / "asm/nonmatchings/main"
    split_names = {p.stem for p in splits.glob("*.s")} if splits.is_dir() else set()
    # The declared segments the address signal reads: the same measurement ``compile.py``'s
    # ``Manifests`` and the gates use, and the reason an out-of-segment record is refused.
    target = _TARGETS.get() if _TARGETS is not None else None
    geometry = getattr(target, "geometry", None)
    segments = (geometry.loadable_vram, geometry.bss_end) if geometry is not None else None
    tu_builds = getattr(target, "tu_builds", ())

    rows = []
    seen = set()
    for tu in dwarf.tus:
        if not tu.name:
            continue
        rel = source_path(tu.name)
        seen.add(rel)
        rows.append(analyze_unit(dwarf, rel, tu, units=units, reachable=reachable,
                                 by_name=by_name, by_addr=by_addr,
                                 borrowed_names=borrowed_names, borrowed_addrs=borrowed_addrs,
                                 splits=splits, split_names=split_names,
                                 unplaced=unplaced, unplaced_by_addr=unplaced_by_addr,
                                 link_names=link_names, segments=segments,
                                 tu_builds=tu_builds))
    # A cus.json unit with no DWARF TU is a manifest inconsistency; surface it, never average it.
    for rel, info in units.items():
        if rel not in seen and not is_promoted(rel, tu_builds):
            rows.append({"file": rel, "overlay": "?", "promoted": False,
                         "declared_functions": info["functions"], "functions": 0,
                         "statements": 0, "lines_per_function": 0.0, "arrays": 0,
                         "unreferenced_arrays": [], "tables": [], "large_tables": [],
                         "unreferenced_tables": [], "vu_functions": 0, "quad_functions": 0,
                         "quad_ops": [], "fp_functions": 0,
                         "split_missing": 0, "calls": {}, "unresolvable": [], "addresses": [], "address_functions": 0,
                         "flags": ["missing-dwarf"],
                         "blocked": True, "score": 0.0,
                         "reasons": ["cus.json names this unit but the DWARF has no TU for it"],
                         "good": []})

    # Promoted units have a src/ source and a tu_builds row; they are not candidates, and
    # excluding them here keeps every output (table, markdown, --json) consistent.
    rows = [row for row in rows if not row["promoted"]]

    # Blocked units follow the candidates so a reader can see what was excluded and why.
    rows.sort(key=lambda r: (r["blocked"], -r["score"], r["functions"], r["file"]))
    return rows


def format_table(rows: list[dict], *, all_rows: bool, limit: int | None) -> str:
    shown = [r for r in rows if not r["promoted"] and (all_rows or not r["blocked"])]
    if limit is not None:
        shown = shown[:limit]
    out = []
    for i, row in enumerate(shown, 1):
        if row["blocked"]:
            head = f"{i:2d}. [blocked] {row['file']}  flags={','.join(row['flags'])}"
        else:
            head = (f"{i:2d}. {row['file']}  score={row['score']:.1f} "
                    f"({row['functions']} fn, {row['statements']} lines)")
        out.append(head)
        for reason in row["reasons"]:
            out.append(f"      why blocked: {reason}")
        for warning in row.get("warnings", []):
            out.append(f"      risk: {warning}")
        if not row["blocked"]:
            out.append("      why easy: " + "; ".join(row["good"]))
    if not shown:
        out.append("(no units matched)")
    return "\n".join(out)


def format_markdown(rows: list[dict], limit: int = 20) -> str:
    candidates = [r for r in rows if not r["promoted"] and not r["blocked"]][:limit]
    lines = ["| rank | unit | score | functions | .text bytes | largest fn | line records | "
             "why expected easy |",
             "|---:|---|---:|---:|---:|---|---:|---|"]
    for i, row in enumerate(candidates, 1):
        why = "; ".join(row["good"])
        lines.append(f"| {i} | `{row['file']}` | {row['score']:.1f} | {row['functions']} | "
                     f"{row.get('text_bytes', 0)} | {row.get('largest_function_bytes', 0)} | "
                     f"{row['statements']} | {why} |")
    return "\n".join(lines)


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--elf", default=str(REPO_ROOT / "orig/SLUS_211.74"))
    parser.add_argument("--top", type=int, default=None, help="limit the printed rows")
    parser.add_argument("--all", action="store_true", help="include blocked units and reasons")
    parser.add_argument("--json", action="store_true", help="print rows as JSON")
    parser.add_argument("--markdown", action="store_true", help="print the ranking table")
    args = parser.parse_args(argv)

    elf = pathlib.Path(args.elf)
    for required in (elf, REPO_ROOT / "config/ddrex2p/cus.json",
                     REPO_ROOT / "config/ddrex2p/symbol_addrs.txt",
                     REPO_ROOT / "config/ddrex2p/borrowed_symbols.txt"):
        if not required.exists():
            print(f"screen.py: missing input: {required}", file=sys.stderr)
            return 2
    try:
        rows = screen(elf)
    except (OSError, ValueError) as exc:
        print(f"screen.py: {exc}", file=sys.stderr)
        return 2
    if args.json:
        print(json.dumps(rows, indent=1))
    elif args.markdown:
        print(format_markdown(rows, limit=args.top or 20))
    else:
        print(format_table(rows, all_rows=args.all, limit=args.top))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
