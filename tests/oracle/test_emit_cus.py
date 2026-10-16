import json, pathlib, pytest, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
sys.path.insert(0, str(ROOT))  # `config.targets`
import emit_cus
from config import targets

def test_cu_map_is_complete_and_contiguous():
    cus = emit_cus.build(ROOT / "orig/SLUS_207.11")
    assert len(cus) == 480
    assert sum(1 for c in cus if c["kind"] == "tu") == 57
    assert sum(1 for c in cus if c["kind"] == "function") == 423
    assert cus[0]["offset"] == 0
    for a, b in zip(cus, cus[1:]):
        assert a["offset"] + a["size"] == b["offset"]
    assert cus[-1]["offset"] + cus[-1]["size"] == 657815      # .debug size

def test_unknown_offset_raises():
    cus = emit_cus.build(ROOT / "orig/SLUS_207.11")
    import pytest
    with pytest.raises(emit_cus.NoCompileUnit):
        emit_cus.owner_of(cus, 657815 + 5)

def test_owner_of_samples_the_debug_range():
    cus = emit_cus.build(ROOT / "orig/SLUS_207.11")
    # Four offsets -- the CU map's first byte, a byte inside the first record, its last byte,
    # and the section's last byte -- not every byte: the tiling itself is the sibling test's
    # (`test_cu_map_is_complete_and_contiguous`).
    for off in (0, 234, 235, 657814):
        c = emit_cus.owner_of(cus, off)
        assert c["offset"] <= off < c["offset"] + c["size"], off

@pytest.mark.parametrize("name", targets.names())
def test_committed_map_matches_a_fresh_run(tmp_path, name):
    """For every target: the committed CU map is what a fresh run of its own ELF produces.

    Parameterised rather than duplicated, and it skips -- visibly -- for a target whose
    binary and manifests have not been placed yet (``ddrex2p``'s arrive in Task 4), so the
    retarget inherits this check the moment its config lands instead of needing a new test.
    """
    target = targets.get(name)
    if not target.elf.is_file() or not target.cus.is_file():
        pytest.skip(f"{name}: {target.elf.name} and its config are generated in Task 4")
    cus = emit_cus.build(target.elf)
    emit_cus.write(tmp_path / "cus.json", cus)
    assert (tmp_path / "cus.json").read_bytes() == target.cus.read_bytes()
    assert cus[-1]["offset"] + cus[-1]["size"] == \
        target.geometry_required().debug_size, "the map must tile the measured .debug"

def test_every_record_identifies_a_translation_unit():
    cus = emit_cus.build(ROOT / "orig/SLUS_207.11")
    # `file` groups the 480 records into exactly the 57 translation units,
    # each of which is contiguous in .debug (Task 4's chunking premise).
    runs = []
    for c in cus:
        assert c["file"].startswith("src/"), c["file"]
        if not runs or runs[-1]["file"] != c["file"]:
            runs.append(c)
    assert len(runs) == 57 == len({c["file"] for c in cus})
    assert all(r["kind"] == "tu" for r in runs)
    # every function CU carries the .line statement-list offset
    assert all(c["stmt_list"] is not None
               for c in cus if c["kind"] == "function")

