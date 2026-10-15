# tests/oracle/test_emit_chunks.py
import json, pathlib, pytest, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_chunks

def test_chunks_tile_both_sections_exactly():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    for section, size in ((".debug", 657815), (".line", 140704)):
        part = [c for c in chunks if c["section"] == section]
        assert part[0]["offset"] == 0
        assert sum(c["size"] for c in part) == size
        for a, b in zip(part, part[1:]):
            assert a["offset"] + a["size"] == b["offset"]

def test_offsets_outside_any_chunk_raise():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.chunk_for(chunks, ".debug", 10**9)


def test_one_debug_chunk_per_translation_unit_and_one_line_chunk_per_function():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    cus = json.loads((ROOT / "config/usam2/cus.json").read_text())
    debug = [c for c in chunks if c["section"] == ".debug"]
    line = [c for c in chunks if c["section"] == ".line"]
    assert 57 == len(debug) == len({c["file"] for c in cus})
    assert 423 == len(line) == sum(1 for c in cus if c["kind"] == "function")
    assert all(c["size"] > 0 for c in chunks)
    assert {c["section"] for c in chunks} == {".debug", ".line"}


def test_every_cu_belongs_to_exactly_one_debug_chunk():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    cus = json.loads((ROOT / "config/usam2/cus.json").read_text())
    debug = [c for c in chunks if c["section"] == ".debug"]
    assert sorted(i for c in debug for i in c["tunits"]) == list(range(len(cus)))
    for c in debug:
        # a .debug chunk is the span of the records it names, and one TU
        first, last = cus[c["tunits"][0]], cus[c["tunits"][-1]]
        assert c["offset"] == first["offset"]
        assert c["offset"] + c["size"] == last["offset"] + last["size"]
        assert {cus[i]["file"] for i in c["tunits"]} == {first["file"]}
        assert c["tunits"] == list(range(c["tunits"][0], c["tunits"][-1] + 1))


def test_line_chunks_name_one_function_cu_each():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    cus = json.loads((ROOT / "config/usam2/cus.json").read_text())
    line = [c for c in chunks if c["section"] == ".line"]
    assert sorted(i for c in line for i in c["tunits"]) == \
        [c["index"] for c in cus if c["kind"] == "function"]
    for c in line:
        assert len(c["tunits"]) == 1
        assert cus[c["tunits"][0]]["stmt_list"] == c["offset"]


def test_out_of_range_offsets_raise_in_both_sections():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    for section, size in ((".debug", 657815), (".line", 140704)):
        for off in (-1, size, size + 5, 10**9):
            with pytest.raises(emit_chunks.NoCompileUnit):
                emit_chunks.chunk_for(chunks, section, off)


def test_chunk_lookup_agrees_with_emit_cus_and_its_error_type():
    import emit_cus
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    cus = json.loads((ROOT / "config/usam2/cus.json").read_text())
    assert emit_chunks.NoCompileUnit is emit_cus.NoCompileUnit
    for off in (0, 234, 235, 657814):
        chunk = emit_chunks.chunk_for(chunks, ".debug", off)
        owner = emit_cus.owner_of(cus, off)
        assert chunk["offset"] <= off < chunk["offset"] + chunk["size"]
        assert owner["index"] in chunk["tunits"]
        assert cus[chunk["tunits"][0]]["offset"] <= owner["offset"]
        assert cus[chunk["tunits"][-1]]["offset"] >= owner["offset"]
    for off in (0, 37, 140435, 140436, 140703):
        chunk = emit_chunks.chunk_for(chunks, ".line", off)
        assert chunk["offset"] <= off < chunk["offset"] + chunk["size"]

    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.chunk_for(chunks, ".comment", 0)


def test_committed_manifest_matches_a_fresh_run(tmp_path):
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    emit_chunks.write(tmp_path / "debug_chunks.json", chunks)
    assert (tmp_path / "debug_chunks.json").read_bytes() == \
        (ROOT / "config/usam2/debug_chunks.json").read_bytes()


def _map(cus, tmp_path, name="cus.json"):
    path = tmp_path / name
    path.write_text(json.dumps(cus))
    return path


def test_a_broken_map_fails_loudly_instead_of_being_repaired(tmp_path):
    cus = json.loads((ROOT / "config/usam2/cus.json").read_text())

    gapped = [dict(c) for c in cus]                 # a hole in .debug
    gapped[3]["offset"] += 1
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(_map(gapped, tmp_path, "gapped.json"))

    truncated = [dict(c) for c in cus[:-1]]         # .debug runs short
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(_map(truncated, tmp_path, "truncated.json"))

    split = [dict(c) for c in cus]                  # one TU in two runs
    split[-1]["file"] = split[0]["file"]
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(_map(split, tmp_path, "split.json"))

    repeated = [dict(c) for c in cus]               # two CUs on one stmt_list
    repeated[9]["stmt_list"] = repeated[8]["stmt_list"]
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(_map(repeated, tmp_path, "repeated.json"))

    past_end = [dict(c) for c in cus]               # .line cannot close
    past_end[9]["stmt_list"] = 140704
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.build(_map(past_end, tmp_path, "past_end.json"))
