"""The generated line inventory: shape, policy, ``--check``, and the reformatted control.

The inventory exists so a promotion may reformat its source without losing the evidence:
``.line`` is reconstructed from retail's split linetable, ``.text`` byte equality is the proof,
and the linked ELF is the checksum that matters.  These tests pin the three things the record
has to get right --

* a synthetic set's rows: the retail shape (bytes, tables, records, digest), the emitted record
  count, and the row differences / shape mismatch the note explains;
* ``--check``: a current file passes, a stale one fails, and the CLI writes only when asked;
* the control: an existing promoted unit whose committed source is reformatted still compiles
  to retail's ``.text``, adopts retail's ``.line``, and is recorded as a layout that no longer
  corresponds.  That one needs the retail ELF and the pinned compiler, so it skips without them.

Nothing here runs a build machine; the control compiles one unit through ``compile.place`` with
its object kept under ``tmp_path``.
"""

from __future__ import annotations

import pathlib
import struct
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))

from units import line_inventory as li  # noqa: E402


def table(base: int, rows: list) -> bytes:
    """One DWARF 1 statement table: ``(length, base)`` then ``(line, position, delta)`` rows."""
    body = b"".join(struct.pack("<IHI", line, position, delta)
                    for line, position, delta in rows)
    return struct.pack("<II", 8 + len(body), base) + body


RETAIL = table(0x1000, [(12, 0, 0), (13, 0, 4)]) + table(0x2000, [(20, 0, 0)])
SAME = RETAIL
MOVED = table(0x1000, [(40, 0, 0), (41, 0, 4)]) + table(0x2000, [(48, 0, 0)])
SHORTER = table(0x1000, [(12, 0, 0)])


class FakeTarget:
    name = "synthetic"
    elf_sha256 = "ef31c90f" + "0" * 56 + "c02cd"


# ---------------------------------------------------------------------------
# one row
# ---------------------------------------------------------------------------


def test_a_reproduced_layout_records_the_retail_shape():
    row = li.record("src/sys/example.c", "000-001", RETAIL, SAME)

    assert (row.size, row.tables, row.records) == (len(RETAIL), 2, 3)
    assert row.emitted == 3
    assert row.differ == 0
    assert row.digest == li._digest(RETAIL)
    assert row.note == ("layout reproduces retail's table; adoption supplied .debug "
                        "metadata only")


def test_a_reformatted_layout_is_recorded_as_no_longer_corresponding():
    row = li.record("src/sys/example.c", "000-001", RETAIL, MOVED)

    assert row.emitted == 3
    assert row.differ == 3
    assert "no longer corresponds" in row.note
    assert "3 of 3 row(s) differ" in row.note


def test_a_different_table_shape_has_no_row_for_row_answer():
    row = li.record("src/sys/example.c", "000-001", RETAIL, SHORTER)

    assert row.emitted == 1
    assert row.differ is None
    assert "emitted 1 record(s), retail 3" in row.note
    assert "retail's chunk is adopted" in row.note


def test_a_layout_that_no_longer_corresponds_is_described_not_refused():
    """The inventory is descriptive: a moved table is recorded, not raised on."""
    moved = li.record("src/sys/example.c", "000", RETAIL, MOVED)
    shorter = li.record("src/sys/example.c", "000", RETAIL, SHORTER)

    assert moved.differ == 3 and "row(s) differ" in moved.note
    assert shorter.differ is None and "no longer corresponds" in shorter.note


def test_the_chunk_label_names_contiguous_split_linetables_once():
    assert li._chunk_label([]) == "-"
    assert li._chunk_label([5]) == "005"
    assert li._chunk_label([5, 6, 7]) == "005-007"
    assert li._chunk_label([5, 7, 8, 12]) == "005,007-008,012"


# ---------------------------------------------------------------------------
# the document and --check, on a synthetic set
# ---------------------------------------------------------------------------


def synthetic_rows():
    return [
        li.record("src/sys/example.c", "000-001", RETAIL, MOVED),
        li.record("src/CS/other.c", "002", RETAIL, SAME),
    ]


def test_render_is_deterministic_and_carries_the_policy():
    first = li.render(synthetic_rows(), FakeTarget())
    second = li.render(synthetic_rows(), FakeTarget())

    assert first == second
    assert "iteration gate, not a promotion gate" in first
    assert "| `src/sys/example.c` | 000-001 | 0x2E | 2 | 3 |" in first
    assert "| `src/CS/other.c` | 002 | 0x2E | 2 | 3 |" in first
    assert "| unit | split line chunks | bytes |" in first
    assert "| unit | state |" not in first
    assert "python3 tools/units/line_inventory.py --check" in first


def test_cli_writes_once_then_check_passes_and_a_stale_file_fails(tmp_path, monkeypatch):
    monkeypatch.setattr(li, "resolve_target", lambda name=None: FakeTarget())
    monkeypatch.setattr(li, "collect", lambda target, verbose=False: synthetic_rows())
    out = tmp_path / "line-inventory.md"

    assert li.main(["--output", str(out)]) == 0
    written = out.read_text()
    assert li.main(["--output", str(out)]) == 0
    assert out.read_text() == written, "a current file is not rewritten with other bytes"
    assert li.main(["--output", str(out), "--check"]) == 0

    out.write_text(written.replace("0x2E", "0x2B"))
    assert li.main(["--output", str(out), "--check"]) == 1


def test_check_reports_a_missing_file_as_stale(tmp_path, monkeypatch):
    monkeypatch.setattr(li, "resolve_target", lambda name=None: FakeTarget())
    monkeypatch.setattr(li, "collect", lambda target, verbose=False: synthetic_rows())
    out = tmp_path / "missing.md"

    assert li.main(["--output", str(out), "--check"]) == 1
    assert not out.is_file(), "--check writes nothing"


# ---------------------------------------------------------------------------
# the control: a reformatted promoted unit still verifies
# ---------------------------------------------------------------------------

CONTROL = "src/sys/sys_scf.c"


def _control_unit():
    """The control unit, its manifests and the toolchain, or a skip reason."""
    from config import targets
    from toolchain import compile as cc, fetch

    if not (ROOT / "orig" / "SLUS_211.74").is_file():
        pytest.skip("no retail ELF in this checkout: nothing to place the unit against")
    if not (ROOT / CONTROL).is_file():
        pytest.skip(f"{CONTROL} is absent from this checkout")
    target = targets.get(targets.DEFAULT)
    manifests = cc.Manifests(target)
    tu = manifests.tu_named(CONTROL)
    pair = target.build_pair(CONTROL)
    assert pair is not None, "the control must stay a recorded promotion"
    compiler, flags = pair
    try:
        compiler_dir = fetch.compiler(compiler)
        wibo = fetch.wibo()
    except Exception as exc:                     # a checkout without the pinned toolchain
        pytest.skip(f"recorded compiler unavailable: {exc}")
    import shlex
    return tu, manifests, compiler_dir, wibo, shlex.split(flags)


def test_a_reformatted_promoted_unit_still_compiles_to_retail(tmp_path):
    """Reformatting moves every line; `.text` is still retail's and `.line` is adopted."""
    from toolchain import compile as cc

    tu, manifests, compiler_dir, wibo, flags = _control_unit()
    original = tu.source.read_text()
    # A leading note and two-space indentation of every non-blank line: no statement changes,
    # every physical line does.  This is the freedom the policy claims.
    reformatted = "/* reformatted control */\n\n" + "\n".join(
        ("  " + line) if line.strip() else line for line in original.splitlines()) + "\n"
    assert len(reformatted.splitlines()) > len(original.splitlines())

    placed = cc.place(tu, manifests, compiler_dir, wibo, flags,
                      keep=tmp_path / "control.mw.o", adopt=True,
                      source_text=reformatted.encode("latin-1"))
    retail = cc.retail_bytes(tu, manifests.target.elf)

    assert placed.text == retail["text"], "reformatting moved .text"
    assert placed.debug == retail["debug"], ".debug is not retail's after adoption"
    assert placed.line == retail["line"], "the adopted .line is not retail's chunk"
    assert placed.emitted_line != retail["line"], (
        "the reformat was supposed to move the emitted table; choose another control")
    assert all(ok for ok, _detail in cc.compare(tu, placed).values())

    row = li.record(tu.file, li._chunk_label(manifests.line_chunk_indices(tu)),
                    retail["line"], placed.emitted_line)
    assert row.emitted > 0
    assert "no longer corresponds" in row.note
