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

def test_sys_scf_debug_and_line_bytes_come_from_the_compiler():
    """Both payloads are the compiler's, not retail's databin wearing the same name.

    A byte-equality verdict cannot tell the two apart: retail's own databin *is* retail.
    So the graph itself is asserted -- the `cc` object, one `objsec` payload per section, and
    that payload in place of the chunk's databin on the tail edge.  `.debug` alone would be
    half the rule: the `.line` payload is what pins the statement numbers, so the same anchor
    is asserted for it (R35b) -- a promotion that quietly fell back to retail's `.line`
    databin would still print "line chunk ok".
    """
    graph = (ROOT / "build.ninja").read_text()
    edge = next(line for line in graph.splitlines()
                if line.startswith("build build/SLUS_207.11.tail: cat "))
    # The edge also declares the code that generates it (`|`, R35a): the tail is the
    # explicit part, which is what the `cat` command is handed.
    tail = edge.split(": cat ", 1)[1].split("|", 1)[0].split()
    for section, databin in ((".debug", ".debug_000"), (".line", ".line_000")):
        payload = f"build/src/sys/sys_scf.c.o{section}"
        assert f"build {payload}: objsec build/src/sys/sys_scf.c.o" in graph
        assert payload in tail
        assert f"build/assets/{databin}.databin.bin" not in tail


def test_staging_paths_are_unique_per_unit():
    """Two units that share a basename and a retail-name length must not share a stage.

    The staged path's guest spelling has to be exactly as long as retail's for the DWARF
    name replacement to work, so the directory is padded to length; it is the digest that
    tells two such units apart.
    """
    sys.path.insert(0, str(ROOT / "tools"))
    from toolchain import compile as cc

    def unit(file, name):
        function = cc.Function("f", 0x1000, 4, 0, 0, 0, 0, 1)
        return cc.Tu(file, name, [0, 1], 0, 0, 0, 0, [function])

    here = unit("src/sys/foo.c", "C:\\work\\usam2\\src\\sys\\foo.c")
    there = unit("src/mov/foo.c", "C:\\work\\usam2\\src\\mov\\foo.c")
    assert len(here.name) == len(there.name)          # the collision the digest breaks
    assert here.source.name == there.source.name == "foo.c"
    assert cc.staged_path(here) != cc.staged_path(there)
    for tu in (here, there):
        assert len(cc.recorded_name(cc.staged_path(tu))) == len(tu.name)
