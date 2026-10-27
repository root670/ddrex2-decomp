"""DWARF names + Ghidra function starts -> a target's splat symbol_addrs.txt.

Two kinds of record cannot be placed, and both are written to the target's
``unplaced_symbols.txt`` with the reason that kept them out of the split: an object whose
DWARF location carries no address, and -- the one a retarget meets -- a record whose address
lies outside every segment the target's geometry declares (this target's overlay
reservations).  Neither is dropped; see :data:`OUTSIDE_REASON`.
"""
import collections, json, pathlib, re, sys

import dwarf1
from dwarf1 import Dwarf

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[2]))  # `config.targets`
from config import targets

DEFAULT = targets.get(targets.DEFAULT)
UNPLACED_REASON = "no AT_location address"
#: The second reason a record cannot be placed, and the one a *retarget* finds: an address
#: outside every segment the yaml declares.  This target's eleven zero-fill overlay
#: reservations (p_filesz 0, VAs 0x7F0000, 0xE4D380, 0x1884000) hold 1,009 of the DWARF's
#: records, and `Geometry` carries one bss extent, so no subsegment claims them.  They are
#: excluded here and reported, in the same file the no-address ones go to, rather than
#: linked at an invented address or dropped.
OUTSIDE_REASON = "outside every declared segment"


def build(elf_path, ghidra_json_path=None):
    """Every symbol record, undeduplicated and unsorted.

    DWARF functions (`lo = AT_low_pc`, `size = AT_high_pc - lo`), DWARF
    globals/statics (`size = 0`) and every Ghidra function start the DWARF
    does not already name (`func_<ADDR>`).  Objects whose DWARF location
    carries no address are kept with `address = 0`; `final` routes them to
    the unplaced file, as are the records a target's segment list cannot hold (`final`,
    which needs the geometry to know where those segments are).
    """
    dw = Dwarf(str(elf_path))
    out = []
    for tu in dw.tus:
        home = targets.overlay_stem(tu.overlay)
        for f in tu.functions():
            lo = f.attrs[dwarf1.AT_low_pc]
            hi = f.attrs[dwarf1.AT_high_pc]
            record = dict(name=f.name, address=lo, size=hi - lo, kind="func",
                          provenance="dwarf")
            if home != "main":
                record["overlay"] = home
            out.append(record)
    for (qn, addr, home, _), _g in dw.globals(None).items():
        record = dict(name=qn, address=addr or 0, size=0, kind="obj", provenance="dwarf")
        module = targets.overlay_stem(home)
        if module != "main" and addr:
            # Only an *addressed* record in an overlay gets the module: the name disambiguates
            # the 64 addresses several modules share, and a record with no address at all
            # (addressed by `AT_location` never) has nothing for it to disambiguate.
            record["overlay"] = module
        out.append(record)
    if ghidra_json_path:
        known = {r["address"] for r in out}
        for f in json.loads(pathlib.Path(ghidra_json_path).read_text())["functions"]:
            a = int(f["address"], 16)
            if a in known:
                continue
            out.append(dict(name=f"func_{a:08X}", address=a, size=0, kind="func",
                            provenance="ghidra"))
    return out


def partition(records):
    """Objects with no real address come out first, before any renaming."""
    placed, unplaced = [], []
    for r in records:
        if r["kind"] == "obj" and not r["address"]:
            r["reason"] = UNPLACED_REASON
            unplaced.append(r)
        else:
            placed.append(r)
    return placed, unplaced


def declared_range(geometry):
    """``(low, high)`` of the address space ``configure.py``'s segment list declares.

    The yaml declares one file-backed ``c`` segment (VAs ``loadable_vram`` up to
    ``address_of(loadable_end)``) and one ``bss`` segment from there to ``bss_end``; those
    two are contiguous by construction, because ``bss_vram`` *is*
    ``address_of(loadable_end)``.  So the declared space is one half-open range, and
    anything the binary reserves at run time outside it -- the zero-fill overlay
    reservations -- has no segment to be placed in.
    """
    return geometry.loadable_vram, geometry.bss_end


def outside_segments(records, geometry):
    """``(placeable, outside)``: which records the segment list can hold at all.

    A record outside :func:`declared_range` cannot be placed by any subsegment, and splat
    refuses even the records it *can* place when two symbols share an address no segment
    claims ("Duplicate symbol detected!").  The geometry *records* the overlay windows, but
    the yaml declares no segment for them (their bytes are the disc image's blobs), so this
    is the exclusion that keeps them out of the split -- measured per record, never a
    hand-written list.
    """
    low, high = declared_range(geometry)
    placeable, outside = [], []
    for r in records:
        (placeable if isinstance(r["address"], int) and low <= r["address"] < high
         else outside).append(r)
    return placeable, outside


def final(records, geometry=None):
    """``(placed, unplaced)``, each collision-resolved; placed address-sorted.

    ``geometry`` is the target's measured segment list, and it defaults to the registered
    target's -- the binary ``ddr oracle`` walks.  It is what says which addresses the split
    can hold at all: without it (or with a target's own, from ``ddr``) a ledger would hand
    splat records no segment claims, which is the state this target's overlays produce.
    """
    placed, unplaced = partition(records)
    if geometry is None:
        geometry = DEFAULT.geometry_required()
    placed, outside = outside_segments(placed, geometry)
    for r in outside:
        r["reason"] = OUTSIDE_REASON
    unplaced.extend(outside)
    resolve_names(placed)
    resolve_names(unplaced)
    placed.sort(key=lambda r: (r["kind"], r["address"]))
    return placed, unplaced


def resolve_names(records):
    """Two records may claim one name (statics repeated across TUs, R12).

    The lowest-address record keeps the bare DWARF spelling; the rest, in
    address order, get `_<n>`, skipping any suffix taken by another record's
    name, and carry `dwarf_name` so the comment still names them.  Records
    are renamed, never dropped.
    """
    taken = {r["name"] for r in records}
    groups = collections.defaultdict(list)
    for r in records:
        groups[r["name"]].append(r)
    for name, rs in groups.items():
        if len(rs) == 1:
            continue
        rs.sort(key=lambda r: r["address"])          # address order, stable
        n = 1
        for r in rs[1:]:
            while f"{name}_{n}" in taken:
                n += 1
            taken.add(f"{name}_{n}")
            if r["provenance"] == "dwarf":
                r["dwarf_name"] = name
            r["name"] = f"{name}_{n}"
            n += 1
    return records


def duplicates(records):
    seen, dupes = set(), []
    for r in records:
        if r["name"] in seen:
            dupes.append(r["name"])
        seen.add(r["name"])
    return sorted(set(dupes))


# ---------------------------------------------------------------------------
# borrowed library names
# ---------------------------------------------------------------------------

# The target's borrowed-name ledger, written by `tools/sdk/borrow.py`: one line per name a
# corpus published for a library function, validated against that function's split bounds before
# it was written.  Its `size:` is that validated number -- the split's own bound, because that is
# what the validation compared against.  It is deliberately *not* forwarded into the symbol
# ledger's `size:`: splat uses that attribute to lay the split out, and a non-zero size
# re-segments the bytes around the function (measured: the split stops carrying an address
# comment and the link fails), so the split keeps detecting the bounds itself -- the bounds this
# ledger checked -- and the number stays here as evidence.  The path is the *target's*: a target
# with no ledger yet (a retarget) borrows nothing, and `apply_borrowed` says so by returning the
# records unchanged.
BORROWED = targets.get(targets.DEFAULT).borrowed
BORROWED_LINE = re.compile(
    r"^(?P<name>[A-Za-z_]\w*) = 0x(?P<address>[0-9A-F]{8}); // type:(?P<kind>func|obj) "
    r"size:0x(?P<size>[0-9A-F]+) provenance:(?P<provenance>\S+) tier:(?P<tier>\S+)")


def parse_borrowed(text):
    """Every record of a borrowed-name ledger, in file order.

    A line that is not a comment and not exactly the ledger's shape is an error: this file
    decides which symbols this tree renames, so a line that does not parse must not be
    skipped quietly.
    """
    out = []
    for number, line in enumerate(text.splitlines(), start=1):
        if not line.strip() or line.lstrip().startswith("//"):
            continue
        match = BORROWED_LINE.match(line.strip())
        if match is None:
            raise ValueError(f"borrowed_symbols.txt line {number} is not "
                             f"`name = 0xADDR; // type:func size:0xSIZE provenance:SRC "
                             f"tier:bytes`: {line.strip()}")
        out.append(dict(name=match["name"], address=int(match["address"], 16),
                        kind=match["kind"], size=int(match["size"], 16),
                        provenance=match["provenance"], tier=match["tier"]))
    return out


def apply_borrowed(records, ledger_path=None):
    """``(records, count)`` with the borrowed-name ledger applied.

    A borrowed name was validated against its function's split bounds -- and, where the
    corpus publishes the bytes, word for word after relocation masking -- before it entered
    the ledger, so this step renames rather than decides.  A record at an address the ledger
    names takes that name and its provenance; an address the ledger names that no record
    carries (spimdisasm detects starts Ghidra did not list) gains one.  The record keeps
    `size: 0` so the split still detects the bounds itself: the ledger's `size:` is the bound the
    validation compared our bytes against, and it must be a positive whole number of
    instructions, but forwarding it to splat re-segments the split (see the note above).  A
    borrowed name that another record already carries at a *different* address, or that lands on
    a different *kind* of symbol, is refused loudly: it would rename something nobody measured.
    """
    path = pathlib.Path(ledger_path) if ledger_path else BORROWED
    if not path.is_file():
        return records, 0
    borrowed = parse_borrowed(path.read_text())
    named = {r["address"] for r in borrowed}
    elsewhere = {r["name"]: r["address"] for r in records if r["address"] not in named}
    by_address = {r["address"]: r for r in records}
    for record in borrowed:
        if record["tier"] != "bytes":
            raise ValueError(
                f"{path}: {record['name']} (0x{record['address']:08X}) is tier "
                f"{record['tier']!r}: only byte-proven names may be renamed in the build, "
                f"because a symbol file line carries no tier")
        if not record["size"] or record["size"] % 4:
            raise ValueError(
                f"{path}: {record['name']} (0x{record['address']:08X}) carries size "
                f"0x{record['size']:X}: a borrowed name must have been validated against a "
                f"positive whole number of instructions")
        taken = elsewhere.get(record["name"])
        if taken is not None:
            raise ValueError(
                f"{path}: {record['name']} is already 0x{taken:08X}'s name, and the ledger "
                f"borrows it for 0x{record['address']:08X}")
        mine = by_address.get(record["address"])
        if mine is None:
            records.append(dict(name=record["name"], address=record["address"], size=0,
                                kind=record["kind"], provenance=record["provenance"]))
            continue
        if mine["kind"] != record["kind"]:
            raise ValueError(
                f"{path}: 0x{record['address']:08X} is a {mine['kind']} in this tree, and the "
                f"ledger names it as a {record['kind']}")
        mine["name"] = record["name"]
        mine["provenance"] = record["provenance"]
    return records, len(borrowed)


def _located(r):
    line = (f'{r["name"]} = 0x{r["address"]:08X}; '
            f'// type:{r["kind"]} size:0x{r["size"]:X} '
            f'provenance:{r["provenance"]}')
    if r.get("dwarf_name"):
        line += f' dwarf_name:{r["dwarf_name"]}'
    return line


def _orphan(r):
    line = (f'{r["name"]} = 0x{r["address"]:08X}; '
            f'// type:{r["kind"]} provenance:{r["provenance"]} '
            f'reason:{r.get("reason", UNPLACED_REASON)}')
    if r.get("overlay"):
        line += f' overlay:{r["overlay"]}'
    if r.get("dwarf_name"):
        line += f' dwarf_name:{r["dwarf_name"]}'
    return line


def render(records):
    return "".join(_located(r) + "\n" for r in records)


def render_unplaced(records):
    return "".join(_orphan(r) + "\n" for r in records)


def write(path, records):
    with open(path, "w") as fh:
        fh.write(render(records))


def write_unplaced(path, records):
    with open(path, "w") as fh:
        fh.write(render_unplaced(records))


if __name__ == "__main__":
    elf = sys.argv[1]
    gh = sys.argv[2] if len(sys.argv) > 2 else None
    placed, unplaced = final(build(elf, gh), DEFAULT.geometry_required())
    out = pathlib.Path(sys.argv[3] if len(sys.argv) > 3 else DEFAULT.symbols)
    orphan = pathlib.Path(sys.argv[4]) if len(sys.argv) > 4 \
        else out.with_name("unplaced_symbols.txt")
    write(out, placed)
    write_unplaced(orphan, unplaced)
    print(f"{len(placed)} placed ({len(duplicates(placed))} dupes); "
          f"{len(unplaced)} unplaced ({len(duplicates(unplaced))} dupes)")
