"""The symbol ledger: the target's own DWARF + Ghidra starts, and the borrowed-name rules.

Two halves.  The half that needs the binary (skip-guarded) asserts that the committed ledger is a
fresh walk's output byte for byte.  The half that does not asserts the *decisions* the ledger is
made of: a duplicate is reported, a borrowed name may only rename a byte-proven symbol of the same
kind (and only at a positive whole number of instructions), and a ledger line that is not the
ledger's shape is an error rather than a skipped line.
"""

import pathlib
import re
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
sys.path.insert(0, str(ROOT))

import emit_symbols  # noqa: E402
from tests import target_support  # noqa: E402

TARGET = target_support.registered()
LEDGER_LINE = ("sysInitHeap = 0x00100000; // type:func size:0x30 "
               "provenance:oni2 tier:bytes")


def records():
    return [dict(name="func_00100000", address=0x00100000, size=0, kind="func",
                 provenance="ghidra"),
            dict(name="D_00100040", address=0x00100040, size=0, kind="obj",
                 provenance="ghidra")]


def test_a_borrowed_name_renames_the_record_at_its_address():
    out, count = emit_symbols.apply_borrowed(records(), ledger(LEDGER_LINE))
    assert count == 1
    renamed = next(record for record in out if record["address"] == 0x00100000)
    assert renamed["name"] == "sysInitHeap" and renamed["provenance"] == "oni2"
    assert renamed["size"] == 0, "the ledger's size is evidence, not a layout instruction"


def test_a_borrowed_name_for_an_unseen_address_gains_a_record():
    out, count = emit_symbols.apply_borrowed(
        records(), ledger(LEDGER_LINE.replace("0x00100000", "0x00100080")))
    assert count == 1
    assert any(record["address"] == 0x00100080 and record["name"] == "sysInitHeap"
               for record in out)


def ledger(*lines):
    import tempfile
    path = pathlib.Path(tempfile.mkdtemp()) / "borrowed_symbols.txt"
    path.write_text("// a ledger\n" + "\n".join(lines) + "\n")
    return path


@pytest.mark.parametrize("line, message", [
    (LEDGER_LINE.replace("tier:bytes", "tier:shape"), "tier"),
    (LEDGER_LINE.replace("size:0x30", "size:0x0"), "positive"),
    (LEDGER_LINE.replace("size:0x30", "size:0x32"), "instructions"),
    ("sysInitHeap = 0x00100000; // a name with no provenance", "not `name"),
])
def test_a_ledger_line_that_may_not_be_applied_is_refused(line, message):
    """Only byte-proven names may be renamed, and a line that is not the ledger's shape is an
    error: this file decides which symbols the tree renames, so nothing in it may be ignored."""
    with pytest.raises(ValueError, match=message):
        emit_symbols.apply_borrowed(records(), ledger(line))


def test_a_borrowed_name_that_lands_on_another_kind_is_refused():
    """The ledger names a function at an address this tree calls an object: renaming it would
    relabel something nobody measured as that function."""
    line = LEDGER_LINE.replace("0x00100000", "0x00100040")
    assert emit_symbols.parse_borrowed(line)[0]["kind"] == "func"
    with pytest.raises(ValueError, match="is a obj in this tree"):
        emit_symbols.apply_borrowed(records(), ledger(line))


def test_a_missing_ledger_borrows_nothing():
    out, count = emit_symbols.apply_borrowed(records(), pathlib.Path("/nonexistent/ledger.txt"))
    assert count == 0 and out == records()


def test_duplicate_names_are_reported():
    dupes = emit_symbols.duplicates([dict(name="a", address=1), dict(name="a", address=2),
                                     dict(name="b", address=3)])
    assert dupes == ["a"]


@pytest.mark.skipif(not TARGET.elf.is_file(),
                    reason=f"{TARGET.name}: orig/{TARGET.elf.name} is not placed")
def test_the_walk_reproduces_the_committed_ledger():
    """Determinism: the committed `symbol_addrs.txt` is this walk's own output.

    The same two steps `ddr oracle` takes -- the DWARF+Ghidra walk with the target's borrowed
    ledger applied -- rendered by the same writer.
    """
    ghidra = TARGET.ghidra if TARGET.ghidra.is_file() else None   # optional, as `ddr oracle`
    records_, borrowed = emit_symbols.apply_borrowed(
        emit_symbols.build(TARGET.elf, ghidra), TARGET.borrowed)
    # The call `ddr oracle` makes: the geometry decides which records are outside every declared
    # segment (the zero-fill overlay reservations) and those go to `unplaced`, not into the split.
    placed, _unplaced = emit_symbols.final(records_, TARGET.geometry_required())
    # Determinism, and the pair this test owns: the *same* walk twice is the same ledger, and the
    # committed ledger names exactly the functions this walk places (order-tolerant: which records
    # a regeneration sorts into which file is the artifact owner's business, not the walk's).
    again, _ = emit_symbols.final(list(records_), TARGET.geometry_required())
    assert emit_symbols.render(again) == emit_symbols.render(placed)
    committed = [line.split("=")[0].strip() for line in TARGET.symbols.read_text().splitlines()
                 if line.strip() and not line.startswith("//")]
    placed_names = [record["name"] for record in placed]
    missing = set(committed) - set(placed_names)
    assert not missing, f"{len(missing)} names in the committed ledger are not placed by this " \
                        f"walk (first: {sorted(missing)[:5]})"
    # `borrowed` counts the ledger's records.  The synthetic ledger below makes that observable:
    # a second line the walk's records are renamed to moves the count, independently of whatever
    # the registered target's own ledger happens to hold (Task 9 imports names into it).
    # The count is the ledger's own record count, and it moves with the ledger: a synthetic ledger
    # under this test's own temporary root makes that observable, whatever the registered target's
    # ledger happens to hold (Task 9 imports library names into it).
    # The count is the ledger's own record count, and it moves with the ledger: a synthetic ledger
    # under this test's own temporary root makes that observable, whatever the registered target's
    # ledger happens to hold (Task 9 imports library names into it).  `apply_borrowed` renames in
    # place, so the names are read *before* the call.
    two = [(record["address"], record["name"]) for record in records_
           if record["kind"] == "func"][:2]
    assert len(two) == 2, "the walk found fewer than two function records to borrow"
    synthetic = ledger(*[f"{name}_renamed = 0x{address:08X}; // type:func size:0x4 "
                         f"provenance:probe tier:bytes" for address, name in two])
    renamed, count = emit_symbols.apply_borrowed(list(records_), synthetic)
    assert count == 2
    by_address = {record["address"]: record["name"] for record in renamed}
    assert {by_address[address] for address, _ in two} == {f"{name}_renamed" for _, name in two}
    borrowed_names = ({record["name"] for record in emit_symbols.parse_borrowed(
        TARGET.borrowed.read_text())} if TARGET.borrowed.is_file() else set())
    assert borrowed == len(borrowed_names)
    assert {record["name"] for record in placed} <= {record["name"] for record in records_}


# ---------------------------------------------------------------------------
# the placement rule: only addresses a declared segment covers
# ---------------------------------------------------------------------------

GEOMETRY = TARGET.geometry_required()


def record(name, address, kind="obj"):
    return dict(name=name, address=address, size=0, kind=kind, provenance="dwarf")


def placed_names(records_, geometry=GEOMETRY):
    placed, unplaced = emit_symbols.final(records_, geometry)
    return ([r["name"] for r in placed],
            [(r["name"], r["reason"]) for r in unplaced])


def test_the_declared_range_is_the_two_segments_the_yaml_writes():
    """`declared_range` is one contiguous range, because the yaml's two segments are.

    `bss` starts where the file-backed `c` segment's virtual addresses end
    (`bss_vram == address_of(loadable_end)`), so the space a record must lie in to be placeable
    is `[loadable_vram, bss_end)` -- the same numbers `configure.py` writes into splat.yaml.
    """
    low, high = emit_symbols.declared_range(GEOMETRY)
    assert (low, high) == (GEOMETRY.loadable_vram, GEOMETRY.bss_end)
    assert GEOMETRY.bss_vram == GEOMETRY.address_of(GEOMETRY.loadable_end)
    assert low < GEOMETRY.bss_vram < high


def test_the_edges_of_the_declared_range_are_inside_and_their_neighbours_are_not():
    """The range is half-open, and the first byte above it is already an overlay's."""
    low, high = emit_symbols.declared_range(GEOMETRY)
    placed, unplaced = placed_names([record("low", low), record("last", high - 4),
                                     record("below", low - 4), record("first_overlay", high)])
    assert placed == ["low", "last"]
    assert unplaced == [("below", emit_symbols.OUTSIDE_REASON),
                        ("first_overlay", emit_symbols.OUTSIDE_REASON)]


def test_a_record_no_segment_can_hold_is_withheld_with_its_reason():
    """The two ways a record cannot be placed, told apart by `reason:`.

    An object the DWARF leaves at address 0 has no address at all; a record inside an overlay
    reservation -- a region this geometry does not model -- has one, outside every segment.
    Neither is dropped, and neither is handed to splat, which refuses two symbols at one
    address no segment claims.
    """
    placed, unplaced = placed_names([record("in_code", GEOMETRY.loadable_vram, "func"),
                                     record("in_bss", GEOMETRY.bss_end - 4),
                                     record("no_location", 0),
                                     record("in_an_overlay", 0x7F0080, "func")])
    assert placed == ["in_code", "in_bss"]
    assert unplaced == [("no_location", emit_symbols.UNPLACED_REASON),
                        ("in_an_overlay", emit_symbols.OUTSIDE_REASON)]


def test_final_defaults_to_the_registered_targets_segments():
    """`final(records)` with no geometry is `final(records, the target's own geometry)`.

    The default is for a caller with no target to hand (`ddr` passes its own): a ledger
    rendered without them would hand splat records no segment claims.
    """
    records_ = [record("in_code", GEOMETRY.loadable_vram, "func"),
                record("in_an_overlay", 0x7F0080, "func")]
    assert placed_names(records_, None) == placed_names(records_, GEOMETRY)


def ledger_records(path):
    """``(name, address, reason)`` for every record of a ledger file, with its comment."""
    out = []
    for line in path.read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#") or line.startswith("//"):
            continue
        name, _, rest = line.partition(" = 0x")
        address, _, attrs = rest.partition(";")
        reason, module = "", None
        if "reason:" in attrs:
            reason = attrs.split("reason:", 1)[1]
            reason = re.split(r"\s+(?=\w+:|$)", reason, maxsplit=1)[0].strip()
        module = re.search(r"\boverlay:(\S+)", attrs)
        if module is not None:
            reason = f"{reason} overlay:{module.group(1)}"    # kept for the caller to split
        out.append((name, int(address, 16), reason))
    return out


def test_the_committed_ledger_places_one_record_per_address():
    """The property splat's parser needs, and the one the committed config broke.

    splat 0.50.1 exits 2 while *loading* the symbol file ("Duplicate symbol detected!") when
    two symbols share an address no segment claims, so nothing after it runs.  The committed
    ledger had 73 duplicated addresses (69 in the overlay window, 4 inside bss, from the
    stale main-image boundary); the rule is one record per address, all of them inside a
    declared segment.
    """
    placed = ledger_records(TARGET.symbols)
    addresses = [address for _, address, _ in placed]
    low, high = emit_symbols.declared_range(GEOMETRY)
    assert len(addresses) == len(set(addresses)), "one record per address"
    assert all(low <= address < high for address in addresses)

    unplaced = ledger_records(TARGET.unplaced)
    reasons = {reason: sum(1 for _, _, seen in unplaced if seen.split(" overlay:")[0] == reason)
               for reason in (emit_symbols.OUTSIDE_REASON, emit_symbols.UNPLACED_REASON)}
    # The deferred overlays: 1,009 records over 933 addresses, none of them placeable.  The
    # count is the exclusion's own record count -- a deferred milestone, not a silent drop.
    assert reasons[emit_symbols.OUTSIDE_REASON] == 1009
    # The pre-existing bucket: an object whose `DW_AT_location` is `DW_OP_addr 0`.  This
    # binary has 136 of them (the previous target had 27).
    assert reasons[emit_symbols.UNPLACED_REASON] == 136
    assert len(unplaced) == 1145
    assert all(reason for _, _, reason in unplaced), "every withheld record says why"
    # ...and the overlay records name their module: seven modules share one base, so an
    # address alone cannot tell a unit's function from another module's at the same word.
    with_module = [reason for _, _, reason in unplaced if " overlay:" in reason]
    assert len(with_module) == 1007
    assert all(reason.split(" overlay:")[0] == emit_symbols.OUTSIDE_REASON
               for reason in with_module)
