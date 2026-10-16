"""The generated headers: one C header per translation unit, from the target's own DWARF.

Re-pointed at the registered target.  Rendering the whole tree is what `ddr oracle` does; what is
tested here is the emitter's contract on one unit of *this* binary -- a header is produced, a name
that matches nothing is refused, and the committed tree and a fresh render agree for that unit --
so nothing depends on how many units the binary happens to have.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
sys.path.insert(0, str(ROOT))

import emit_headers  # noqa: E402
from tests import target_support  # noqa: E402

TARGET = target_support.registered()
pytestmark = pytest.mark.skipif(
    not TARGET.elf.is_file() or not TARGET.cus.is_file(),
    reason=f"{TARGET.name}: its ELF and config are generated in Task 4")


def a_unit():
    """One translation unit of this binary, taken from the committed CU map."""
    import json
    cus = json.loads(TARGET.cus.read_text())
    return next(record["file"] for record in cus
                if record.get("kind") == "tu" and record.get("file")).split("/")[-1]


def test_a_units_header_is_generated_from_its_own_evidence():
    unit = a_unit()
    text = emit_headers.render(TARGET.elf, unit)
    assert text.count("#ifndef") == 1 and "DDR_UNIT_" in text
    assert "#endif /* DDR_UNIT_" in text, "the header is guarded and closes its guard"
    assert unit in text, "the header names the unit it was generated from"


def test_an_unknown_unit_is_refused():
    with pytest.raises(emit_headers.NoSuchUnit):
        emit_headers.render(TARGET.elf, "no_such_unit_at_all.c")


def test_the_committed_header_matches_a_fresh_render(tmp_path):
    """The committed tree is the generator's output: the same unit renders the same bytes."""
    unit = a_unit()
    committed = ROOT / "include" / emit_headers.header_for(f"src/{unit}")
    if not committed.is_file():
        pytest.skip(f"include/{emit_headers.header_for(f'src/{unit}')} is not committed yet")
    assert emit_headers.render(TARGET.elf, unit) == committed.read_text()
