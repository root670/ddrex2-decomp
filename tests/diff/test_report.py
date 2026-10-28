"""The report's arithmetic: code is measured, data is never a fabricated 100%.

objdiff-cli derives every percentage from a numerator and a denominator and prints 100% when
the denominator is empty, so a unit with no data target reads as "100% data".  These tests pin
the three behaviours the report relies on:

* a data measure whose denominator is empty is *removed*, never printed as 100%;
* a data measure with a real denominator is left exactly as objdiff computed it;
* a claim of matched data with no denominator is refused rather than arithmetically blessed.

The last test runs the real ``objdiff-cli`` over a synthetic unit -- one matched function and
one that differs -- because that pairing (``basis.unit`` target, compiled object as the base)
is the one the report is generated from.
"""

import json
import pathlib
import shutil
import struct
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))              # `diff.report`, `diff.basis`
sys.path.insert(0, str(ROOT / "tools" / "oracle"))   # the vendored ELF reader
sys.path.insert(0, str(ROOT))

import elf  # noqa: E402
from diff import basis, report  # noqa: E402

BASE = 0x100000
FILE_OFFSET = 0x100
#: 48 bytes of image: three 16-byte functions, so a report can match some and not all.
CODE = bytes(range(48))
NOP = b"\0\0\0\0"


def image_bytes(payload=CODE, base=BASE, file_offset=FILE_OFFSET) -> bytes:
    """A miniature retail image: ``ET_EXEC`` for the EE, one ``PT_LOAD``, no sections."""
    header = (b"\x7fELF\x01\x01\x01" + b"\0" * 9
              + struct.pack("<HHIIIIIHHHHHH", 2, 8, 1, base, 52, 0, 0x20924000,
                            52, 32, 1, 40, 0, 0))
    phdr = struct.pack("<8I", 1, file_offset, base, base, len(payload), len(payload), 5, 4)
    return header + phdr + b"\0" * (file_offset - 52 - 32) + payload


@pytest.fixture
def retail(tmp_path):
    path = tmp_path / "SLUS_000.00"
    path.write_bytes(image_bytes())
    return path


# ---------------------------------------------------------------------------
# the pruning rule, without objdiff in the loop
# ---------------------------------------------------------------------------


def test_an_empty_data_denominator_is_removed_not_printed_as_100():
    """The defect: 0/0 is 100% in objdiff's arithmetic, and that is not a measurement."""
    measures = {"total_code": "60", "matched_code": "60", "matched_code_percent": 100.0,
                "total_functions": 2, "matched_functions": 2,
                "matched_functions_percent": 100.0,
                "matched_data_percent": 100.0, "complete_data_percent": 100.0}
    pruned = report.pruned(measures)
    assert "matched_data_percent" not in pruned
    assert "complete_data_percent" not in pruned
    assert pruned["matched_code_percent"] == 100.0      # the code claim is untouched
    assert measures["matched_data_percent"] == 100.0    # and the input was not mutated


def test_zero_byte_counts_leave_no_trace_either():
    pruned = report.pruned({"matched_data_percent": 100.0, "total_data": "0",
                            "matched_data": "0", "complete_data": "0"})
    assert pruned == {}


def test_a_measured_data_denominator_is_left_exactly_as_objdiff_computed_it():
    measures = {"total_data": "16", "matched_data": "8", "matched_data_percent": 50.0,
                "complete_data": "8", "complete_data_percent": 50.0}
    assert report.pruned(measures) == measures


def test_matched_data_with_no_denominator_is_refused():
    """A ratio with an empty denominator is undefined: pruning must not bless the claim."""
    with pytest.raises(ValueError):
        report.pruned({"matched_data": "4", "matched_data_percent": 100.0})
    with pytest.raises(ValueError):
        report.pruned({"complete_data": "4"})


def test_prune_visits_the_report_its_units_and_its_categories():
    fabricated = {"matched_code": "60", "matched_data_percent": 100.0,
                  "complete_data_percent": 100.0}
    document = {"measures": dict(fabricated),
                "units": [{"name": "a", "measures": dict(fabricated)},
                          {"name": "b", "measures": {"matched_data_percent": 100.0}}],
                "categories": [{"id": "c", "measures": dict(fabricated)}]}
    pruned, removed = report.prune(document)
    assert removed == 4
    assert "matched_data_percent" not in pruned["measures"]
    assert all("matched_data_percent" not in unit["measures"] for unit in pruned["units"])
    assert "matched_data_percent" not in pruned["categories"][0]["measures"]
    assert document["measures"]["matched_data_percent"] == 100.0   # deep copy


def test_no_unit_with_an_empty_data_denominator_can_report_100_percent_data(tmp_path):
    """Over a whole report: every empty denominator ends with no data claim at all."""
    units = [{"name": f"main/unit{i}", "measures": {"total_code": "8", "matched_code": "8",
                                                    "matched_data_percent": 100.0,
                                                    "complete_data_percent": 100.0}}
             for i in range(5)]
    document = {"measures": {"total_code": "40", "matched_code": "40",
                             "matched_data_percent": 100.0},
                "units": units}
    path = tmp_path / "report.json"
    path.write_text(json.dumps(document))
    assert report.main([str(path)]) == 0
    written = json.loads(path.read_text())
    for holder in [written] + written["units"]:
        assert "matched_data_percent" not in holder["measures"]
        assert "complete_data_percent" not in holder["measures"]
    assert written["measures"]["matched_code"] == "40"


# ---------------------------------------------------------------------------
# the real tool over a synthetic unit
# ---------------------------------------------------------------------------


def test_a_report_counts_a_units_matched_and_unmatched_functions(tmp_path, retail):
    """A unit whose base has one matching and one differing body reports 16 of 32 bytes.

    The target is the object :func:`basis.unit` builds from the image; the base is the
    stand-in for a compiled object.  The first function's bytes are retail's, the second's
    last word is not, so the report must count exactly one of them -- and still print "100%
    data" on its raw output, which is what pruning removes.
    """
    objdiff = shutil.which("objdiff-cli")
    if objdiff is None:
        pytest.skip("objdiff-cli is not installed: the report's pairing needs it")
    functions = [("matched", BASE, 16), ("differing", BASE + 16, 16)]
    target = basis.unit(functions, retail, BASE, BASE + 32, "main/synthetic",
                        directory=tmp_path / "target")
    ours = bytes(range(16)) + NOP * 3 + struct.pack("<I", 0x0C000001)
    base = tmp_path / "base.o"
    base.write_bytes(basis.object_with_symbols(
        ours, [(name, address - BASE, size) for name, address, size in functions]))

    project = tmp_path / "project"
    project.mkdir()
    (project / "objdiff.json").write_text(json.dumps({
        "custom_make": None, "build_target": False, "build_base": False,
        "min_version": "2.0.0",
        "units": [{"name": "main/synthetic",
                   "target_path": str(target), "base_path": str(base),
                   "scratch": {}, "metadata": {}}]}))
    done = subprocess.run([objdiff, "report", "generate", "-p", str(project),
                           "-o", str(project / "report.json")],
                          capture_output=True, text=True)
    assert done.returncode == 0, done.stderr[-600:]
    raw = json.loads((project / "report.json").read_text())
    measures = raw["units"][0]["measures"]
    assert (measures["total_code"], measures["matched_code"]) == ("32", "16")
    assert (measures["total_functions"], measures["matched_functions"]) == (2, 1)
    assert measures["matched_functions_percent"] == 50.0
    assert measures["matched_data_percent"] == 100.0        # the fabrication, before pruning

    pruned, _removed = report.prune(raw)
    assert "matched_data_percent" not in pruned["units"][0]["measures"]
    assert "matched_data_percent" not in pruned["measures"]


def test_a_report_over_three_functions_counts_only_the_one_the_base_holds(tmp_path, retail):
    """A partially promoted unit: the report's denominator is still retail's whole unit."""
    objdiff = shutil.which("objdiff-cli")
    if objdiff is None:
        pytest.skip("objdiff-cli is not installed: the report's pairing needs it")
    functions = [("one", BASE, 16), ("two", BASE + 16, 16), ("three", BASE + 32, 16)]
    target = basis.unit(functions, retail, BASE, BASE + 48, "main/partial",
                        directory=tmp_path / "target")
    base = tmp_path / "base.o"
    base.write_bytes(basis.object_with_symbols(bytes(range(16)), [("one", 0, 16)]))
    project = tmp_path / "project"
    project.mkdir()
    (project / "objdiff.json").write_text(json.dumps({
        "custom_make": None, "build_target": False, "build_base": False,
        "min_version": "2.0.0",
        "units": [{"name": "main/partial", "target_path": str(target),
                   "base_path": str(base), "scratch": {}, "metadata": {}}]}))
    done = subprocess.run([objdiff, "report", "generate", "-p", str(project),
                           "-o", str(project / "report.json")],
                          capture_output=True, text=True)
    assert done.returncode == 0, done.stderr[-600:]
    measures = json.loads((project / "report.json").read_text())["units"][0]["measures"]
    assert (measures["total_code"], measures["matched_code"]) == ("48", "16")
    assert (measures["total_functions"], measures["matched_functions"]) == (3, 1)
