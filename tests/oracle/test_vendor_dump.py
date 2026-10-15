import re, pathlib, subprocess, sys, pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
DUMP = ROOT / "orig/usam2.elf.txt"


def test_dump_and_reader_agree_on_functions():
    if not DUMP.exists():
        pytest.skip("vendor dump not staged")
    text = DUMP.read_text(encoding="latin1")
    dump_low_pcs = set(re.findall(r"AT_low_pc\(([0-9a-f]{8})\)", text))
    reader = subprocess.run([sys.executable, str(ROOT / "tools/oracle/dwarf1.py"),
                             "cus", str(ROOT / "orig/SLUS_207.11")],
                            capture_output=True, text=True, check=True).stdout
    assert len(reader.splitlines()) >= 423          # one line per compile unit
    assert len(dump_low_pcs) >= 423                 # the vendor's own parse agrees

    # stronger check: the reader reproduces exactly the set of low_pc values
    # the vendor's own dump prints (verified equal, 423 both sides)
    reader_low_pcs = set(re.findall(r"0x([0-9a-f]{8})-0x[0-9a-f]{8}", reader))
    assert len(reader_low_pcs) == len(dump_low_pcs)
    assert reader_low_pcs == dump_low_pcs
