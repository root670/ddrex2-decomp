import pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_headers

def test_sys_scf_header_has_types_globals_and_prototypes():
    text = emit_headers.render(ROOT / "orig/SLUS_207.11", "sys_scf.c")
    assert "struct _tag_SYS_SCF_WORK" in text
    assert "int date_notation;" in text
    assert "_tag_SYS_SCF_WORK *pscf;" in text
    assert "void sysInitScf(_tag_SYS_SCF_WORK *p);" in text
    assert "0x0021C410-0x0021C41C" in text

def test_every_translation_unit_gets_one_header(tmp_path):
    written = emit_headers.write_all(ROOT / "orig/SLUS_207.11", tmp_path)
    committed = sorted(p for p in (ROOT / "include").rglob("*.h"))
    assert len(written) == 57 == len(committed)
    assert {p.relative_to(tmp_path) for p in written} == \
        {p.relative_to(ROOT / "include") for p in committed}
    assert (tmp_path / "README.md").exists()

def test_committed_headers_match_a_fresh_run(tmp_path):
    emit_headers.write_all(ROOT / "orig/SLUS_207.11", tmp_path)
    fresh = sorted(p for p in tmp_path.rglob("*") if p.is_file())
    for path in fresh:
        assert path.read_bytes() == (ROOT / "include" /
                                     path.relative_to(tmp_path)).read_bytes(), path

