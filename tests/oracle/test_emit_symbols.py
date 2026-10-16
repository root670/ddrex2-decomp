"""The symbol ledger: the target's own DWARF + Ghidra starts, and the borrowed-name rules.

Two halves.  The half that needs the binary (skip-guarded) asserts that the committed ledger is a
fresh walk's output byte for byte.  The half that does not asserts the *decisions* the ledger is
made of: a duplicate is reported, a borrowed name may only rename a byte-proven symbol of the same
kind (and only at a positive whole number of instructions), and a ledger line that is not the
ledger's shape is an error rather than a skipped line.
"""

import pathlib
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
    # The same call `ddr oracle` makes: the geometry decides which records are outside every
    # declared segment (the zero-fill overlay reservations), and those go to `unplaced`.
    placed, _unplaced = emit_symbols.final(records_, TARGET.geometry_required())
    assert borrowed == 0                                     # no ledger for this target yet
    assert emit_symbols.render(placed) == TARGET.symbols.read_text()
