import pathlib, re, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_symbols

GHIDRA = ROOT / "config/usam2/ghidra_functions.json"
SPLAT = ROOT / "config/usam2/symbol_addrs.txt"
ORPHAN = ROOT / "config/usam2/unplaced_symbols.txt"
LINE = re.compile(r'\S+ = 0x[0-9A-F]{8}; // type:(?:func|obj) size:0x[0-9A-F]+ '
                  r'provenance:(?:dwarf|ghidra)(?: dwarf_name:\S+)?$')

def _final():
    return emit_symbols.final(emit_symbols.build(ROOT / "orig/SLUS_207.11", GHIDRA))

def test_dwarf_functions_keep_their_names():
    placed, _ = _final()
    by_addr = {r["address"]: r for r in placed}
    assert by_addr[0x0021C420]["name"] == "sysInitScf"
    assert by_addr[0x0021C420]["size"] == 0x30
    assert by_addr[0x0021C420]["provenance"] == "dwarf"

def test_counts_are_reported_by_the_reader():
    placed, _ = _final()
    funcs = [r for r in placed if r["provenance"] == "dwarf" and r["kind"] == "func"]
    objs = [r for r in placed if r["provenance"] == "dwarf" and r["kind"] == "obj"]
    ghidra = [r for r in placed if r["provenance"] == "ghidra"]
    assert len(funcs) == 423
    assert len(objs) == 612
    assert len(ghidra) == 2738
    assert len(placed) == 3773

def test_no_symbol_is_placed_at_zero_and_no_address_is_shared():
    placed, _ = _final()
    assert [r["name"] for r in placed if r["address"] == 0] == []
    assert len({r["address"] for r in placed}) == len(placed)

def test_unplaced_objects_are_kept_in_their_own_file():
    placed, unplaced = _final()
    assert len(unplaced) == 27
    assert {r["kind"] for r in unplaced} == {"obj"}
    assert {r["provenance"] for r in unplaced} == {"dwarf"}
    assert {r["address"] for r in unplaced} == {0}
    # nothing is dropped: the objects split across both files still total 639
    assert len([r for r in placed + unplaced if r["kind"] == "obj"]) == 639

def test_duplicate_names_are_reported_not_dropped():
    placed, unplaced = _final()
    assert emit_symbols.duplicates(placed) == []
    assert emit_symbols.duplicates(unplaced) == []
    assert len(placed) + len(unplaced) == 3800     # renaming never drops a record

def test_files_carry_splat_syntax_and_the_unplaced_reason(tmp_path):
    placed, unplaced = _final()
    text = (tmp_path / "splat.txt")
    orphan = (tmp_path / "orphan.txt")
    emit_symbols.write(text, placed)
    emit_symbols.write_unplaced(orphan, unplaced)
    lines = text.read_text().splitlines()
    assert len(lines) == 3773
    assert all(LINE.match(l) for l in lines)
    assert "= 0x00000000;" not in text.read_text()
    assert text.read_text().count("provenance:ghidra") == 2738
    assert "sysInitScf = 0x0021C420; // type:func size:0x30 provenance:dwarf" in text.read_text()
    orphans = orphan.read_text().splitlines()
    assert len(orphans) == 27
    assert all(l.endswith("reason:no AT_location address")
               or " reason:no AT_location address dwarf_name:" in l for l in orphans)

def test_committed_files_match_a_fresh_run(tmp_path):
    placed, unplaced = _final()
    emit_symbols.write(tmp_path / "splat.txt", placed)
    emit_symbols.write_unplaced(tmp_path / "orphan.txt", unplaced)
    assert (tmp_path / "splat.txt").read_bytes() == SPLAT.read_bytes()
    assert (tmp_path / "orphan.txt").read_bytes() == ORPHAN.read_bytes()
