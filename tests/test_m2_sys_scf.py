"""M2 on the retargeted tree: ``src/sys/sys_scf.c`` is compiled, and its bytes are the compiler's.

The promotion rule is byte equality on three parts (``.text``, ``.debug``, ``.line``), and the
verdict comes from ``./ddr verify --tu sys_scf.c`` -- a build, which this suite never runs
(`tests/conftest.py`, `tests/target_support.py`).  What is pinned here is what a byte-equality
verdict cannot tell apart on its own: retail's own databin *is* retail, so a promotion that
quietly fell back to it would still print "debug chunk ok".  So the graph is asserted -- the
``cc`` object, one ``objsec`` payload per section, and those payloads in place of the chunks'
databins on the tail edge -- together with the two facts the graph rests on: the source keeps
retail's statement *grouping* (its layout is tidied, so the row adopts retail's ``.line``
chunk whole and the physical numbers are free), and the target's descriptor records a
*measured* compiler pair for it (what ``configure.py`` refuses to promote without).
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))

import configure  # noqa: E402
from config import targets  # noqa: E402
from tests import target_support  # noqa: E402

TARGET = target_support.registered()
SOURCE = "src/sys/sys_scf.c"

#: Retail's statement lines and what sits on each, from this build's own line tables
#: (``dwarf1.py lines orig/SLUS_211.74 0x001B3D30 --table`` and ``… 0x001B3D40 --table``):
#: ``sysInitScf`` (0x001B3D40, 48 B) has statements on 24, 29, 35 and 43, and
#: ``sysGetDateNotation`` (0x001B3D30, 12 B) on 50 and 51.  Line 24 is both the opening brace
#: and the line the prologue is attributed to; 43 and 51 are the closing braces that own the
#: epilogues.  The unit's layout is tidied and its row records ``adopt``, so the numbers are
#: provenance for the *grouping* the test pins, not the physical lines the file uses.
RETAIL_LINES = {
    24: "void sysInitScf(struct _tag_SYS_SCF_WORK *p) {",
    29: "pscf = p; pscf->date_notation = sceScfGetDateNotation(p);",
    35: "pscf->language = 1;",
    43: "}",
    49: "int sysGetDateNotation(void) {",
    50: "return pscf->date_notation;",
    51: "}",
}


def source_lines() -> list:
    text = (ROOT / SOURCE).read_text()
    assert "INCLUDE_ASM" not in text, f"{SOURCE} is assembly, not the promoted unit"
    return text.splitlines()


def graph() -> str:
    """The generated ninja graph, or a skip: it is a build's output, not a source."""
    path = ROOT / "build.ninja"
    if not path.is_file():
        pytest.skip("build.ninja is absent: nothing has been configured in this checkout")
    return path.read_text()


def test_the_unit_keeps_retails_statement_grouping():
    """Every statement retail's DWARF records is present, once, in retail's order.

    The tidy moves the physical lines, so the ``.line`` half of the rule is satisfied by
    adopting retail's chunk -- and what the source must then keep is the grouping (which
    statements share a line), which is what the record-count check in the tidy tool proves.
    A missing, duplicated or reordered statement would still change that count.
    """
    lines = [line.strip() for line in source_lines()]
    index = 0
    for number, statement in RETAIL_LINES.items():
        while index < len(lines) and lines[index] != statement:
            index += 1
        assert index < len(lines), (
            f"{SOURCE}: {statement!r} (retail line {number}) is missing or out of order")
        index += 1
    pair = TARGET.build_pair(SOURCE)
    assert pair is not None and pair[2] == "adopt", (
        f"{SOURCE}: a moved statement line needs retail-metadata adoption recorded in "
        f"tu_builds")


def test_the_descriptor_records_a_measured_compiler_for_the_unit():
    """A unit with a source but no measured pair is a configuration error, so the pair is the
    unit's other half: it must name this source, and `select_build.py` is what filled it."""
    assert TARGET.build_pair(SOURCE) is not None, (
        f"{TARGET.name} lists no compiler for {SOURCE}: run "
        f"python3 tools/toolchain/select_build.py --tu {SOURCE} and record the pair")


@pytest.mark.parametrize("section", (".debug", ".line"))
def test_the_payload_in_the_image_is_the_compilers(section):
    """``.debug`` and ``.line`` reach the tail as the ``cc`` object's own payload.

    ``.debug`` alone would be half the rule: the ``.line`` payload is what pins the statement
    numbers, so the same anchor is asserted for it (R35b) -- a promotion that quietly fell
    back to retail's ``.line`` databin would still print "line chunk ok".
    """
    text = graph()
    promotion = next((p for p in configure.promotions(target=TARGET) if p.file == SOURCE), None)
    assert promotion is not None, f"{SOURCE} is not in {TARGET.name}'s promotions"
    payload = f"build/{SOURCE}.o{section}"
    assert f"build {payload}: objsec build/{SOURCE}.o" in text
    tail_name = f"build build/{TARGET.elf.name}.tail: cat "
    edge = next(line for line in text.splitlines() if line.startswith(tail_name))
    tail = edge.split(": cat ", 1)[1].split("|", 1)[0].split()
    assert payload in tail
    # Every databin the unit owns, not just the first: the unit's functions have one `.debug`
    # chunk between them but a `.line` chunk each, so a fallback on any but the first would
    # otherwise go unnoticed while the payload assertion above stayed green.
    chunks = ([promotion.debug_databin] if section == ".debug" else promotion.line_databins)
    assert chunks, f"{SOURCE}: no {section} chunk was pinned for the unit"
    for chunk in chunks:
        assert f"build/assets/{chunk}.databin.bin" not in tail, (
            f"the tail still assembles retail's own {chunk} for {SOURCE}")
