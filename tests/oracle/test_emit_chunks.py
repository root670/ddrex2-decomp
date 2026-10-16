"""The debug-chunk manifest: two tilings that must be exact, from a target's own measurements.

The manifest is the bridge between the oracle's CU map and the split, so both halves are checked
here on a synthetic map -- one `.debug` chunk per translation unit, one `.line` chunk per function,
each tiling its section byte for byte -- together with the failure modes (a gap, an overlap, a TU
split in two runs, a repeated statement list) that must be reported rather than repaired.  The
section lengths come from the target's geometry, which the CLI resolves; with none given they are
the default target's, which is exactly the state a target without a measured geometry cannot be in.
"""

import dataclasses
import json
import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
sys.path.insert(0, str(ROOT))  # `config.targets`

import emit_chunks  # noqa: E402
from config import targets  # noqa: E402

DEBUG_SIZE = 0x400
LINE_SIZE = 0x100


def records():
    """One translation unit, two functions: the smallest map that has both chunk kinds."""
    return [
        dict(index=0, kind="tu", offset=0, size=0x100, name="probe.c", file="src/probe.c",
             low_pc=None, high_pc=None, stmt_list=None),
        dict(index=1, kind="function", offset=0x100, size=0x180, name="one", file="src/probe.c",
             low_pc=0x100000, high_pc=0x100010, stmt_list=0),
        dict(index=2, kind="function", offset=0x280, size=DEBUG_SIZE - 0x280, name="two",
             file="src/probe.c", low_pc=0x100010, high_pc=0x100020, stmt_list=0x40),
    ]


def map_file(tmp_path, cus, name="cus.json"):
    path = tmp_path / name
    path.write_text(json.dumps(cus))
    return path


def build(tmp_path, cus=None):
    return emit_chunks.build(map_file(tmp_path, records() if cus is None else cus),
                             LINE_SIZE, DEBUG_SIZE)


def test_the_chunks_tile_both_sections_exactly(tmp_path):
    chunks = build(tmp_path)
    for section, size in ((".debug", DEBUG_SIZE), (".line", LINE_SIZE)):
        part = [c for c in chunks if c["section"] == section]
        assert part[0]["offset"] == 0
        assert sum(c["size"] for c in part) == size
        for a, b in zip(part, part[1:]):
            assert a["offset"] + a["size"] == b["offset"]


def test_one_debug_chunk_per_translation_unit_and_one_line_chunk_per_function(tmp_path):
    chunks = build(tmp_path)
    cus = records()
    debug = [c for c in chunks if c["section"] == ".debug"]
    line = [c for c in chunks if c["section"] == ".line"]
    assert len(debug) == len({c["file"] for c in cus}) == 1
    assert len(line) == sum(1 for c in cus if c["kind"] == "function") == 2
    assert all(c["size"] > 0 for c in chunks)
    assert {c["section"] for c in chunks} == {".debug", ".line"}


def test_every_cu_belongs_to_exactly_one_debug_chunk(tmp_path):
    chunks = build(tmp_path)
    debug = [c for c in chunks if c["section"] == ".debug"]
    assert sorted(i for c in debug for i in c["tunits"]) == list(range(len(records())))


def test_a_chunk_covers_the_bytes_it_names(tmp_path):
    chunks = build(tmp_path)
    cus = records()
    for chunk in chunks:
        for off in (chunk["offset"], chunk["offset"] + chunk["size"] - 1):
            found = emit_chunks.chunk_for(chunks, chunk["section"], off)
            assert found is chunk, (chunk, off)
    assert cus[chunks[0]["tunits"][0]]["offset"] == 0


def test_offsets_outside_any_chunk_raise(tmp_path):
    chunks = build(tmp_path)
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.chunk_for(chunks, ".debug", 10 ** 9)
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.chunk_for(chunks, ".comment", 0)


def test_a_broken_map_fails_loudly_instead_of_being_repaired(tmp_path):
    def broken(name, mutate):
        cus = [dict(record) for record in records()]
        mutate(cus)
        return map_file(tmp_path, cus, name)

    gapped = broken("gapped.json", lambda cus: cus[1].__setitem__("offset", 0x104))
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(gapped, LINE_SIZE, DEBUG_SIZE)

    truncated = broken("truncated.json", lambda cus: cus.pop())
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(truncated, LINE_SIZE, DEBUG_SIZE)

    split = broken("split.json", lambda cus: cus[1].__setitem__("file", "src/other.c"))
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(split, LINE_SIZE, DEBUG_SIZE)

    repeated = broken("repeated.json", lambda cus: cus[2].__setitem__("stmt_list", 0))
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(repeated, LINE_SIZE, DEBUG_SIZE)

    past_end = broken("past_end.json", lambda cus: cus[2].__setitem__("stmt_list", LINE_SIZE))
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(past_end, LINE_SIZE, DEBUG_SIZE)


def test_the_default_sizes_are_the_default_targets_measurement(monkeypatch):
    """With no sizes given, the manifest needs the target's own measurement -- and a target
    nobody has measured stops there rather than inheriting another target's numbers."""
    geometry = targets.get().geometry_required()
    assert emit_chunks.default_sizes() == (geometry.line_size, geometry.debug_size)
    monkeypatch.setattr(emit_chunks, "DEFAULT",
                        dataclasses.replace(targets.get(), geometry=None))
    with pytest.raises(targets.NotMeasured):
        emit_chunks.default_sizes()
