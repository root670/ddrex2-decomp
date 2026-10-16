"""G2 -- the promotion rule: a unit's `.text` **and** its `.debug` **and** its `.line` bytes.

`verdicts` is what every promotion is judged by, so it is tested here on synthetic files: the
three parts are compared independently (G1 can be green while a chunk is not, and vice versa), a
divergence in each is reported as *that* part failing, and a name that matches no translation unit
is a usage error rather than an empty report.
"""

import json
import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))

from config import targets  # noqa: E402
from verify import g2  # noqa: E402

GEOMETRY = targets.Geometry(
    elf_size=0x2000, loadable_rom=0x80, loadable_end=0x1000, loadable_vram=0x00100000,
    bss_end=0x00110000,
    trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400), ("line", 0x1410, 0x100),
              ("section_headers", 0x1510, 0x2000 - 0x1510)),
    debug_size=0x400, line_size=0x100, image_elf_offset=0x92000)
TU = "src/probe.c"
FUNCTIONS = ((0x00100000, 0x00100010, "probe_one"), (0x00100010, 0x00100040, "probe_two"))


@pytest.fixture
def manifests(tmp_path):
    cus = [dict(index=0, kind="tu", offset=0, size=0x40, name="probe.c", file=TU,
                low_pc=None, high_pc=None, stmt_list=None)]
    chunks = [dict(section=".debug", offset=0, size=0x400, tunits=[0])]
    for index, (low, high, _) in enumerate(FUNCTIONS, start=1):
        cus.append(dict(index=index, kind="function", offset=0x40 * index, size=0x40,
                        name=f"probe_{index}", file=TU, low_pc=low, high_pc=high,
                        stmt_list=(index - 1) * 0x40))
        chunks[0]["tunits"].append(index)
        chunks.append(dict(section=".line", offset=(index - 1) * 0x40, size=0x40,
                           tunits=[index]))
    cus_path, chunks_path = tmp_path / "cus.json", tmp_path / "debug_chunks.json"
    symbols_path = tmp_path / "symbol_addrs.txt"
    cus_path.write_text(json.dumps(cus))
    chunks_path.write_text(json.dumps(chunks))
    symbols_path.write_text("".join(
        f"{name} = 0x{low:08X};  // type:func size:0x{high - low:X} provenance:dwarf\n"
        for low, high, name in FUNCTIONS))
    return cus_path, chunks_path, symbols_path


def target_image(tmp_path, name="built", flip=None):
    """A stand-in for both sides of the comparison; ``flip`` changes one byte of the copy."""
    path = tmp_path / name
    data = bytearray(b"\x3D" * GEOMETRY.elf_size)
    if flip is not None:
        data[flip] ^= 0xFF
    path.write_bytes(bytes(data))
    return path


def verdicts(tmp_path, manifests, flip=None):
    cus, chunks, symbols = manifests
    retail = target_image(tmp_path, "retail")
    built = target_image(tmp_path, "built", flip)
    return g2.verdicts(built, retail, TU, cus, chunks, symbols, GEOMETRY)


def test_a_unit_whose_bytes_all_match_is_promoted(tmp_path, manifests):
    tu, report = verdicts(tmp_path, manifests)
    assert tu == TU
    assert [verdict.what for verdict in report] == ["text", "debug chunk", "line chunk"]
    assert all(verdict.ok for verdict in report), report
    assert "VA 0x00100000-0x00100040" in report[0].detail


def test_a_code_byte_fails_the_text_part_and_names_its_function(tmp_path, manifests):
    offset = GEOMETRY.offset_of(0x00100014)          # inside `probe_two`, the second function
    _, report = verdicts(tmp_path, manifests, flip=offset)
    assert report[0].what == "text" and report[0].ok is False
    assert f"0x{offset:X}" in report[0].detail and "probe_two" in report[0].detail
    assert report[1].ok and report[2].ok, "the debug bytes are untouched and must stay green"


def test_a_debug_byte_fails_only_the_debug_part(tmp_path, manifests):
    _, report = verdicts(tmp_path, manifests, flip=0x1014)
    assert report[0].ok and report[1].ok is False and report[2].ok
    assert "0x1014" in report[1].detail and ".debug" in report[1].detail


def test_a_line_byte_fails_only_the_line_part(tmp_path, manifests):
    _, report = verdicts(tmp_path, manifests, flip=0x1414)
    assert report[0].ok and report[1].ok and report[2].ok is False
    assert "0x1414" in report[2].detail and ".line" in report[2].detail


def test_the_manifests_join_names_addresses_and_chunks(tmp_path, manifests):
    cus, chunks, symbols = manifests
    loaded = g2.Manifests(cus, chunks, symbols, GEOMETRY)
    assert loaded.tu_named("probe") == TU
    assert loaded.tu_named("probe.c") == TU
    assert loaded.tu_named(TU) == TU
    assert loaded.symbol_at(0x00100010) == "probe_two"
    # The ledger names function *starts*: an address inside one has no entry, and falls back to
    # the name its address gives it rather than to the function that contains it.
    assert loaded.symbol_at(0x00100011) == "func_00100011"
    owner = loaded.record_at_pc(0x00100020)
    assert owner["low_pc"] == 0x00100010 and owner["file"] == TU
    assert [chunk["offset"] for chunk in loaded.line_chunks_of(TU)] == [0, 0x40]
    assert [chunk["offset"] for chunk in loaded.debug_chunks_of(TU)] == [0]
    assert loaded.describe(0x84)["function"] == "probe_one"


def test_a_name_that_matches_no_unit_is_a_usage_error(tmp_path, manifests):
    cus, chunks, symbols = manifests
    loaded = g2.Manifests(cus, chunks, symbols, GEOMETRY)
    with pytest.raises(g2.UnknownUnit):
        loaded.tu_named("nosuch")
    with pytest.raises(g2.UnknownUnit):
        g2.verdicts(target_image(tmp_path), target_image(tmp_path, "retail"), "nosuch",
                    cus, chunks, symbols, GEOMETRY)
