import pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_symbols

def test_dwarf_functions_keep_their_names():
    recs = emit_symbols.build(ROOT / "orig/SLUS_207.11")
    by_addr = {r["address"]: r for r in recs}
    assert by_addr[0x0021C420]["name"] == "sysInitScf"
    assert by_addr[0x0021C420]["size"] == 0x30
    assert by_addr[0x0021C420]["provenance"] == "dwarf"

def test_counts_are_reported_by_the_reader():
    recs = emit_symbols.build(ROOT / "orig/SLUS_207.11")
    funcs = [r for r in recs if r["provenance"] == "dwarf" and r["kind"] == "func"]
    objs = [r for r in recs if r["provenance"] == "dwarf" and r["kind"] == "obj"]
    assert len(funcs) == 423
    assert len(objs) == 639          # if the reader reports another count, fix this constant

def test_duplicate_names_are_reported_not_dropped():
    recs = emit_symbols.build(ROOT / "orig/SLUS_207.11")
    dupes = emit_symbols.duplicates(recs)
    assert dupes == [], f"duplicate names must be resolved explicitly, got {dupes}"
