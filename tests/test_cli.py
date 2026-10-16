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

Two of them cover the finding that a gate can pass by comparing the *wrong pair*: ``verify``
must check ``orig/SLUS_207.11`` against its record in ``checksums.txt`` before G1 compares it
with the build, and the ISO gate must check its reference image against that manifest's
record before comparing the rebuild with it.  Both are pinned here as digests, because a
gate whose expectation is "whatever it was handed" is no gate at all -- and a reference *no*
record names is refused outright (exit 2): the synthetic fixtures opt in with
``--allow-unpinned-reference``, which makes the reference file itself the criterion and says
so on the success line.
"""

import hashlib
import importlib.machinery
import importlib.util
import os
import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from iso import reinsert  # noqa: E402  (path set up above, as the brief specifies)
from verify import g1, g2  # noqa: E402

RETAIL = ROOT / "orig/SLUS_207.11"
BUILT = ROOT / "out/SLUS_207.11"
# The manifest's two records, as the plan and the spec pin them.
PINNED_ELF = "a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc"
PINNED_IMAGE = "b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8"
# The retail geometry: the one loadable section starts at file offset 0x80, VA 0x100000,
# so `sysInitScf` (VA 0x21C420, size 0x30) is at file 0x11C4A0 and its third word -- the one
# the brief flips -- at 0x11C4A4.
TEXT_OFFSET = 0x80 + (0x21C424 - 0x100000)
SYS_SCF = "src/sys/sys_scf.c"
IMAGE = pathlib.Path(
    "/Volumes/My Passport/PS2 Games/DDRMAX2 Dance Dance Revolution (USA).iso")


def run(*args):
    return subprocess.run([str(ROOT / "ddr"), *args], cwd=ROOT, capture_output=True, text=True)


def load_ddr():
    """The ``ddr`` script as a module, for the two cases the process boundary cannot reach.

    ``ddr`` has no ``.py`` suffix, so it is loaded by path; executing it imports what the CLI
    imports and defines ``cmd_iso``/``parse_args`` without running them (``main`` is guarded).
    Needed where the test must *replace* an input the CLI reads (a mount, a pin) rather than
    arrange one on disk.
    """
    loader = importlib.machinery.SourceFileLoader("ddr_cli_under_test", str(ROOT / "ddr"))
    module = importlib.util.module_from_spec(
        importlib.util.spec_from_loader(loader.name, loader))
    loader.exec_module(module)
    return module


def corrupted_copy(path, offset, out):
    """``path`` with the byte at ``offset`` flipped, written to ``out``."""
    data = bytearray(path.read_bytes())
    data[offset] ^= 0xFF
    out.write_bytes(bytes(data))
    return out


def synthetic_image(tmp_path, elf, name="synthetic.iso"):
    """A stand-in disc image: a pattern, with ``elf`` spliced in at the real offset.

    G3 is a ``write`` into a copy plus a hash, so a 3 MB pattern tests the same code path
    as the 1.24 GB image -- without reading, writing or hashing the retail disc.  ``name``
    matters when the pin is what is under test: the manifest resolves a pin by file name.
    """
    size = reinsert.ELF_OFFSET + len(elf) + 0x1000
    data = bytearray((index * 7 + 11) & 0xFF for index in range(size))
    data[reinsert.ELF_OFFSET:reinsert.ELF_OFFSET + len(elf)] = elf
    image = tmp_path / name
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


def test_the_checksums_file_pins_both_binaries():
    """One manifest, two records: the built image (first) and the retail disc image."""
    assert g1.pinned_hash() == PINNED_ELF
    assert g1.pinned_hash_for(IMAGE.name) == PINNED_IMAGE
    assert g1.pinned_hash_for("no-such-image.iso") is None


def test_verify_refuses_a_retail_binary_that_is_not_the_pinned_one(tmp_path):
    """A self-consistent pair is not a green G1: the pin is checked before the comparison.

    The reviewer's counterexample, in effect: a 100-byte-short retail binary with
    ``out/SLUS_207.11`` built from it compares "ok" against each other, and G1's own CLI
    still fails it on the pin.  ``--retail`` keeps the irreplaceable ``orig/`` out of the
    test; only the rebuildable, gitignored ``out/`` is mutated, and restored in ``finally``.
    """
    saved = BUILT.read_bytes()
    try:
        short = saved[:-100]
        impostor = tmp_path / "SLUS_207.11"
        impostor.write_bytes(short)
        BUILT.write_bytes(short)  # the pair agrees with itself...
        p = run("verify", "--retail", str(impostor))
        assert p.returncode != 0
        assert "G1 ok" not in p.stdout
        assert PINNED_ELF in p.stdout and hashlib.sha256(short).hexdigest() in p.stdout
    finally:
        BUILT.write_bytes(saved)


def test_verify_still_compares_against_a_retail_binary_it_was_given():
    """``--retail`` is the same gate on another file: this one *is* the pinned binary."""
    p = run("verify", "--retail", str(RETAIL))
    assert p.returncode == 0 and "G1 ok" in p.stdout


def test_iso_refuses_a_reference_image_that_is_not_the_pinned_one(tmp_path):
    """The disc image is pinned too, by name: a stub wearing its name is not the disc."""
    image = synthetic_image(tmp_path, BUILT.read_bytes(), name=IMAGE.name)
    out = tmp_path / "rebuilt.iso"
    p = run("iso", "--iso", str(image), "--out", str(out))
    assert p.returncode == 1
    assert PINNED_IMAGE in p.stdout and reinsert.sha256(image) in p.stdout
    assert not out.exists()  # the reference is checked before anything is written


def test_iso_refuses_a_reference_no_record_names(tmp_path):
    """No pin, no criterion: comparing the rebuild with the reference is comparing the copy
    with itself, so an image no record names is a hard failure (exit 2), not a green gate.

    Even a *self-consistent* unpinned image -- one that already holds the built ELF, so the
    splice would change nothing and the hashes would agree -- is refused: that agreement is
    exactly the shape that would let a renamed or tampered image pass.
    """
    # The image already holds the built ELF, so the splice would change nothing and the two
    # hashes would agree -- the self-comparison that must never count as a green gate.
    image = synthetic_image(tmp_path, BUILT.read_bytes())
    out = tmp_path / "rebuilt.iso"
    p = run("iso", "--iso", str(image), "--out", str(out))
    assert p.returncode == 2
    assert "G3 ok" not in p.stdout
    assert "no record" in p.stderr and "--allow-unpinned-reference" in p.stderr
    assert not out.exists()


def test_an_unpinned_and_corrupted_image_never_passes(tmp_path):
    """The reviewer's counterexample: an image no pin names, whose bytes are not the disc's.

    ``--allow-unpinned-reference`` makes the file itself the criterion; the file's own ELF
    region is corrupted, so splicing the built ELF into it changes it and the hash fails.
    Without the opt-out it never reaches the hash: exit 2, and no ``G3 ok`` either way.
    """
    image = synthetic_image(tmp_path, BUILT.read_bytes())
    corrupt = corrupted_copy(image, reinsert.ELF_OFFSET + 0x40,
                             tmp_path / "renamed-corrupt.iso")
    out = tmp_path / "rebuilt.iso"
    refused = run("iso", "--iso", str(corrupt), "--out", str(out))
    assert refused.returncode == 2 and "G3 ok" not in refused.stdout
    assert "--allow-unpinned-reference" in refused.stderr and not out.exists()
    measured = run("iso", "--iso", str(corrupt), "--out", str(out),
                   "--allow-unpinned-reference")
    assert measured.returncode == 1
    assert "G3 ok" not in measured.stdout and "G3 FAIL" in measured.stdout
    assert reinsert.sha256(corrupt) in measured.stdout  # the criterion it measured against


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
    # Target = the split object (retail's own bytes, M1's shape); base = the promoted unit's
    # C object, which is what the image is built from once `src/sys/sys_scf.c` exists (M2).
    assert argv[argv.index("-1") + 1].endswith("sysInitScf.s.o")
    assert argv[argv.index("-2") + 1].endswith("src/sys/sys_scf.c.o")
    assert "sys_scf.c" in p.stderr  # the TU it validated the symbol against


def test_diff_rejects_a_symbol_that_is_not_in_the_named_tu():
    p = run("diff", "sysInitScf", "les_sel_lv")
    assert p.returncode == 2
    assert "sysInitScf" in p.stderr and SYS_SCF in p.stderr


def test_diff_refuses_a_unit_with_no_c_source():
    """A unit with no C source has nothing to measure (finding 10).

    objdiff would otherwise be handed the retail split as *both* sides, take the split's own
    ``.NON_MATCHING`` name as the base counterpart and print a score it never computed --
    which reads as "the split does not match retail" when the split *is* retail's bytes.
    """
    p = run("diff", "draw_cur", "les_sel_lv")
    assert p.returncode == 2
    assert p.stdout == ""                       # objdiff was never run
    assert "no C source" in p.stderr and "--base" in p.stderr
    assert "Traceback" not in p.stderr


def test_bare_iso_with_no_mounted_image_says_nothing_was_compared(monkeypatch, capsys,
                                                                  tmp_path):
    """Bare ``--iso`` is the mounted retail image: absent, the gate skips (exit 0) -- and the
    line has to make it unmistakable that no comparison happened."""
    ddr = load_ddr()
    monkeypatch.setattr(ddr.reinsert, "RETAIL_IMAGE", tmp_path / "absent.iso")
    assert ddr.cmd_iso(ddr.parse_args(["iso"])) == 0
    out = capsys.readouterr().out
    assert out.startswith("G3 skipped") and "nothing was compared" in out


def test_the_success_line_names_the_pinned_digest_when_the_reference_is_pinned(
        monkeypatch, capsys, tmp_path):
    """The two success lines are distinguishable: a pinned reference reports the *pin*."""
    ddr = load_ddr()
    image = synthetic_image(tmp_path, BUILT.read_bytes(), name="pinned-by-this-test.iso")
    monkeypatch.setattr(ddr.g1, "pinned_hash_for", lambda name: reinsert.sha256(image))
    args = ddr.parse_args(["iso", "--iso", str(image), "--out", str(tmp_path / "out.iso")])
    assert ddr.cmd_iso(args) == 0, capsys.readouterr()
    out = capsys.readouterr().out
    assert "G3 ok" in out and f"equals the pinned digest of {image.name}" in out
    assert "(UNPINNED)" not in out


def test_iso_reproduces_the_image_it_is_given(tmp_path):
    """G3 through ``verify --iso``: the rebuilt copy is the image, hash for hash.

    The synthetic image is not the disc, so the gate needs the explicit opt-out -- and the
    success line has to say so: the criterion is the reference *it was spliced into*, not a
    pinned digest, and a reader must be able to tell those two apart.
    """
    image = synthetic_image(tmp_path, BUILT.read_bytes())
    out = tmp_path / "rebuilt.iso"
    p = run("verify", "--iso", str(image), "--out", str(out),
            "--allow-unpinned-reference")
    assert p.returncode == 0, p.stdout + p.stderr
    assert "G1 ok" in p.stdout and "G3 ok" in p.stdout
    assert "equals the reference image it was spliced into" in p.stdout
    assert "(UNPINNED)" in p.stdout
    assert out.read_bytes() == image.read_bytes()


def test_iso_names_the_first_byte_that_diverges(tmp_path):
    elf = BUILT.read_bytes()
    image = synthetic_image(tmp_path, elf)
    stamp = corrupted_copy(BUILT, 0, tmp_path / "stamp.elf")
    p = run("iso", "--iso", str(image), "--elf", str(stamp),
            "--out", str(tmp_path / "rebuilt.iso"), "--allow-unpinned-reference")
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
