"""The ``ddr`` command surface: the oracle, the build, both gates and the localisation.

The CLI is the only entry point a contributor (or an agent) is meant to use for routine
work, so these tests drive it as a *process* -- the way the plan's tasks and the CI
workflows do -- rather than importing its functions.  Two of them are the brief's, verbatim
and load-bearing: the green direction (``ddr build`` then ``ddr verify`` prints ``G1 ok``)
and the failing direction (one byte flipped inside ``sysInitScf`` must be reported as
``src/sys/sys_scf.c`` / ``sysInitScf`` -- the G2 role, built on G1's localisation per R32).

Everything else here is cheap and hermetic: the per-TU verdict Task 12 asserts, the two
pieces of the ``g2`` mapping the CLI's message is made of, the dependency-remedy report, the
``objdiff-cli`` wiring (against a stub on ``PATH``), and the ISO verb against a small
synthetic image instead of the 1.24 GB retail one (tests/iso owns the real G3 evidence).
"""

import os
import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from iso import reinsert  # noqa: E402  (path set up above, as the brief specifies)
from verify import g2  # noqa: E402

RETAIL = ROOT / "orig/SLUS_207.11"
BUILT = ROOT / "out/SLUS_207.11"
# The retail geometry: the one loadable section starts at file offset 0x80, VA 0x100000,
# so `sysInitScf` (VA 0x21C420, size 0x30) is at file 0x11C4A0 and its third word -- the one
# the brief flips -- at 0x11C4A4.
TEXT_OFFSET = 0x80 + (0x21C424 - 0x100000)
SYS_SCF = "src/sys/sys_scf.c"
IMAGE = pathlib.Path(
    "/Volumes/My Passport/PS2 Games/DDRMAX2 Dance Dance Revolution (USA).iso")


def run(*args):
    return subprocess.run([str(ROOT / "ddr"), *args], cwd=ROOT, capture_output=True, text=True)


def corrupted_copy(path, offset, out):
    """``path`` with the byte at ``offset`` flipped, written to ``out``."""
    data = bytearray(path.read_bytes())
    data[offset] ^= 0xFF
    out.write_bytes(bytes(data))
    return out


def synthetic_image(tmp_path, elf):
    """A stand-in disc image: a pattern, with ``elf`` spliced in at the real offset.

    G3 is a ``write`` into a copy plus a hash, so a 3 MB pattern tests the same code path
    as the 1.24 GB image -- without reading, writing or hashing the retail disc.
    """
    size = reinsert.ELF_OFFSET + len(elf) + 0x1000
    data = bytearray((index * 7 + 11) & 0xFF for index in range(size))
    data[reinsert.ELF_OFFSET:reinsert.ELF_OFFSET + len(elf)] = elf
    image = tmp_path / "synthetic.iso"
    image.write_bytes(bytes(data))
    return image


def test_verify_reports_ok_when_built_matches():
    assert run("build").returncode == 0
    p = run("verify")
    assert p.returncode == 0 and "G1 ok" in p.stdout


def test_verify_names_the_offending_tu(tmp_path):
    bad = ROOT / "out/SLUS_207.11"
    saved = bad.read_bytes()
    try:
        # VA 0x21C424 is inside .text, which starts at file offset 0x80 for VA 0x100000
        off = 0x80 + (0x21C424 - 0x100000)
        b = bytearray(saved); b[off] ^= 0xFF; bad.write_bytes(bytes(b))
        p = run("verify")
        assert p.returncode != 0
        assert "sys_scf.c" in p.stdout and "sysInitScf" in p.stdout
    finally:
        bad.write_bytes(saved)


def test_the_per_tu_verdict_covers_text_and_both_chunks():
    """Task 12's contract: ``--tu`` is a filter over G1's localisation, and it is green."""
    p = run("verify", "--tu", "sys_scf.c")
    assert p.returncode == 0, p.stdout + p.stderr
    assert "G1 ok" in p.stdout
    assert f"{SYS_SCF}: text ok" in p.stdout
    assert f"{SYS_SCF}: debug chunk ok" in p.stdout
    assert f"{SYS_SCF}: line chunk ok" in p.stdout


def test_the_per_tu_verdict_fails_on_a_flipped_text_byte(tmp_path):
    saved = BUILT.read_bytes()
    try:
        BUILT.write_bytes(corrupted_copy(RETAIL, TEXT_OFFSET, tmp_path / "bad").read_bytes())
        p = run("verify", "--tu", "sys_scf")
        assert p.returncode != 0
        assert f"{SYS_SCF}: text FAIL" in p.stdout
        assert "sysInitScf" in p.stdout  # the failing byte's own function, from g2
    finally:
        BUILT.write_bytes(saved)


def test_verify_rejects_an_unknown_tu_name():
    """A usage error is exit 2, answered before G1 runs, and never a traceback."""
    p = run("verify", "--tu", "nosuch_tu")
    assert p.returncode == 2
    assert "G1 ok" not in p.stdout
    assert "Traceback" not in p.stderr and "nosuch_tu" in p.stderr


def test_localisation_names_the_function_and_its_translation_unit(tmp_path):
    """.text has no chunk manifest, so the offset becomes a VA and the VA picks the CU."""
    bad = corrupted_copy(RETAIL, TEXT_OFFSET, tmp_path / "bad")
    located = g2.localise(bad, RETAIL)
    assert located["section"] == ".text"
    assert located["offset"] == TEXT_OFFSET
    assert located["function"] == "sysInitScf"
    assert located["tu"] == SYS_SCF
    assert located["cu"] == 415  # the function CU's own .debug offset: 0x19F
    assert g2.localise(RETAIL, RETAIL) is None


def test_localisation_names_the_translation_unit_for_a_debug_byte(tmp_path):
    """The .debug half is g1's: a chunk byte belongs to the TU whose records it holds."""
    chunk = next(c for c in g2.Manifests().debug_chunks if c["offset"] == 0)
    bad = corrupted_copy(RETAIL, 0x1A2740 + chunk["offset"], tmp_path / "bad")
    located = g2.localise(bad, RETAIL)
    assert located["section"] == ".debug"
    assert located["tu"] == SYS_SCF
    assert located["function"] is None  # the byte is in the TU header, not a function


def test_a_missing_host_tool_is_reported_with_its_remedy():
    """``check_deps.require`` is the CLI's gate: a remedy, never a traceback."""
    env = {**os.environ, "PATH": "/nonexistent/ddr-cli-test"}
    p = subprocess.run([sys.executable, str(ROOT / "ddr"), "build"],
                       cwd=ROOT, capture_output=True, text=True, env=env)
    assert p.returncode != 0
    assert "Traceback" not in p.stderr
    assert "remedy:" in p.stderr and "brew install mips-linux-gnu-binutils" in p.stderr


def test_diff_reaches_objdiff_cli(tmp_path):
    """``diff`` is a thin wrapper: the argv it hands ``objdiff-cli`` is the contract."""
    stubdir = tmp_path / "bin"
    stubdir.mkdir()
    stub = stubdir / "objdiff-cli"
    stub.write_text('#!/bin/sh\nprintf \'%s\\n\' "$@" >> "$0.argv"\n'
                    'echo "objdiff-cli 0.0.0-stub"\n')
    stub.chmod(0o755)
    env = {**os.environ, "PATH": str(stubdir) + os.pathsep + os.environ["PATH"]}
    p = subprocess.run([str(ROOT / "ddr"), "diff", "sysInitScf", "sys_scf"],
                       cwd=ROOT, capture_output=True, text=True, env=env)
    assert p.returncode == 0, p.stdout + p.stderr
    argv = (stubdir / "objdiff-cli.argv").read_text().splitlines()
    assert "diff" in argv and "sysInitScf" in argv
    assert argv[argv.index("-1") + 1].endswith("sysInitScf.s.o")
    assert argv[argv.index("-2") + 1].endswith("sysInitScf.s.o")  # still assembled from asm
    assert "sys_scf.c" in p.stderr  # the TU it validated the symbol against


def test_diff_rejects_a_symbol_that_is_not_in_the_named_tu():
    p = run("diff", "sysInitScf", "les_sel_lv")
    assert p.returncode == 2
    assert "sysInitScf" in p.stderr and SYS_SCF in p.stderr


def test_iso_reproduces_the_image_it_is_given(tmp_path):
    """G3 through ``verify --iso``: the rebuilt copy is the image, hash for hash."""
    image = synthetic_image(tmp_path, BUILT.read_bytes())
    out = tmp_path / "rebuilt.iso"
    p = run("verify", "--iso", str(image), "--out", str(out))
    assert p.returncode == 0, p.stdout + p.stderr
    assert "G1 ok" in p.stdout and "G3 ok" in p.stdout
    assert out.read_bytes() == image.read_bytes()


def test_iso_names_the_first_byte_that_diverges(tmp_path):
    elf = BUILT.read_bytes()
    image = synthetic_image(tmp_path, elf)
    stamp = corrupted_copy(BUILT, 0, tmp_path / "stamp.elf")
    p = run("iso", "--iso", str(image), "--elf", str(stamp),
            "--out", str(tmp_path / "rebuilt.iso"))
    assert p.returncode != 0
    assert "G3 FAIL" in p.stdout and "0x92000" in p.stdout


def test_iso_reports_a_missing_image(tmp_path):
    p = run("iso", "--iso", str(tmp_path / "absent.iso"))
    assert p.returncode == 2
    assert "Traceback" not in p.stderr and "absent.iso" in p.stderr


def test_retail_image_hash_is_the_pinned_one():
    """The image ``ddr iso`` is pointed at here is the one the plan pinned."""
    if not IMAGE.exists():
        pytest.skip("retail image not available")
    assert reinsert.sha256(IMAGE) == (
        "b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8")


def test_oracle_regenerates_the_committed_artifacts_byte_for_byte():
    """The oracle is deterministic: a fresh run reproduces what is committed (or staged)."""
    targets = [path for path in (ROOT / "config/usam2").glob("*.json")]
    targets += [ROOT / "config/usam2/symbol_addrs.txt",
                ROOT / "config/usam2/unplaced_symbols.txt"]
    targets += [path for path in (ROOT / "include").rglob("*") if path.is_file()]
    before = {path: path.read_bytes() for path in targets}
    p = run("oracle")
    assert p.returncode == 0, p.stdout + p.stderr
    assert {path: path.read_bytes() for path in targets} == before
