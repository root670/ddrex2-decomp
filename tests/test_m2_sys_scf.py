# tests/test_m2_sys_scf.py
import pathlib, subprocess, sys
ROOT = pathlib.Path(__file__).resolve().parents[1]

def test_sys_scf_is_compiled_not_assembled():
    assert (ROOT / "src/sys/sys_scf.c").exists()
    src = (ROOT / "src/sys/sys_scf.c").read_text()
    assert "INCLUDE_ASM" not in src

def test_promoted_tu_keeps_the_binary_identical():
    subprocess.run([str(ROOT / "ddr"), "build"], cwd=ROOT, check=True)
    p = subprocess.run([str(ROOT / "ddr"), "verify"], cwd=ROOT, capture_output=True, text=True)
    assert p.returncode == 0 and "G1 ok" in p.stdout

def test_sys_scf_debug_chunk_matches_retail():
    p = subprocess.run([str(ROOT / "ddr"), "verify", "--tu", "sys_scf.c"],
                       cwd=ROOT, capture_output=True, text=True)
    assert p.returncode == 0 and "debug chunk ok" in p.stdout
