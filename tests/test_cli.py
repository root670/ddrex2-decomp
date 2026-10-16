"""The ``ddr`` command surface: what a verb does, without ever building anything.

The CLI is the only entry point a contributor is meant to use for routine work, so these tests
drive it -- but *never* into a real build: `ninja`, `splat` and `configure.py` belong to whoever
owns the tree (`AGENTS.md`).  That rule is enforced at runtime by `tests/conftest.py` (every
process-spawning entry point, plus a session backstop that fails if the repository changed), and
`tests/target_support.py` provides the probe targets these tests replace the descriptor's lookup
with -- so a verb invoked here either stops before it could build or is caught by the guard.  What is pinned here is the
selection (`--target`, both spellings, default), the loud stops (an unknown name, a target with
no binary, a target with no measured geometry), the remedy line for a missing host tool, and the
`diff` verb's contract -- including the two cases that matter most, a unit with no C source and a
report that compared nothing.
"""

import dataclasses
import importlib.machinery
import importlib.util
import json
import os
import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))  # `config.targets`, the descriptor every tool reads

from tests import target_support  # noqa: E402
from config import targets  # noqa: E402
from iso import reinsert  # noqa: E402

TARGET = target_support.registered()


def run(*args):
    """``ddr`` as a process.  Callers must only reach verbs that stop before any build."""
    return subprocess.run([str(ROOT / "ddr"), *args], cwd=ROOT, capture_output=True, text=True)


def load_ddr():
    """The ``ddr`` script as a module, so a test can replace an input rather than arrange one."""
    loader = importlib.machinery.SourceFileLoader("ddr_cli_under_test", str(ROOT / "ddr"))
    module = importlib.util.module_from_spec(
        importlib.util.spec_from_loader(loader.name, loader))
    loader.exec_module(module)
    return module


# ---------------------------------------------------------------------------
# target selection
# ---------------------------------------------------------------------------


def test_the_target_flag_is_accepted_before_and_after_the_verb():
    ddr = load_ddr()
    for argv in (["--target", TARGET.name, "verify"], ["verify", "--target", TARGET.name],
                 ["verify"], ["oracle"]):
        assert ddr._target(ddr.parse_args(argv)) is TARGET, argv


def test_an_unknown_target_is_a_usage_error_naming_the_one_that_exists():
    p = run("--target", "usam2", "verify")
    assert p.returncode == 2
    assert "usam2" in p.stderr and TARGET.name in p.stderr
    assert "Traceback" not in p.stderr and "G1 ok" not in p.stdout


# ---------------------------------------------------------------------------
# the loud stops -- against a probe, never against the registered target
# ---------------------------------------------------------------------------


def test_every_verb_stops_loudly_when_its_target_has_no_binary(monkeypatch, capsys, tmp_path):
    """A fresh checkout: `orig/<elf>` is gitignored, so it is the developer who copies the retail
    binary in -- and until they do, every verb names the file it is missing and writes nothing.

    The target is a probe entirely under ``tmp_path``, so this test cannot read, write or build
    anything of the real tree even if a verb's checks were reordered.
    """
    ddr = load_ddr()
    probe = target_support.without_binary(tmp_path, monkeypatch, ddr, "probe_cli")

    assert ddr.main(["verify"]) == 2
    err = capsys.readouterr().err
    assert f"out/{probe.elf.name}" in err and "run ./ddr build" in err
    assert "Traceback" not in err

    assert ddr.main(["oracle"]) == 2
    err = capsys.readouterr().err
    assert probe.elf.name in err and "no such file" in err

    assert ddr.main(["build"]) == 2
    err = capsys.readouterr().err
    assert probe.elf.name in err and "Traceback" not in err

    assert not probe.config_dir.exists()          # nothing of the target's config was written


def test_build_stops_at_an_unmeasured_target_before_it_configures(
        monkeypatch, capsys, tmp_path):
    """With the binary in place but no measured geometry, `build` stops -- there is no segment
    list to split with, and the stop names the binary the measurement comes from."""
    ddr = load_ddr()
    elf = tmp_path / "SLUS_999.99"
    elf.write_bytes(b"\x7fELF")
    probe = target_support.without_binary(tmp_path, monkeypatch, ddr, "probe_cli")
    monkeypatch.setattr(ddr.targets, "get",
                        lambda name=None: dataclasses.replace(probe, elf=elf))
    assert ddr.main(["build"]) == 2
    err = capsys.readouterr().err
    assert "geometry" in err and elf.name in err and "Traceback" not in err
    assert not probe.config_dir.exists()


def test_a_missing_host_tool_is_reported_with_its_remedy():
    """``check_deps.require`` is the CLI's gate: a remedy, never a traceback.

    The build cannot start at all here -- no tool is on ``PATH`` -- which is why this is the one
    place the suite names the verb.
    """
    env = {**os.environ, "PATH": "/nonexistent/ddr-cli-test"}
    p = subprocess.run([sys.executable, str(ROOT / "ddr"), "build"],
                       cwd=ROOT, capture_output=True, text=True, env=env)
    assert p.returncode != 0
    assert "Traceback" not in p.stderr
    assert "remedy:" in p.stderr and "brew install mips-linux-gnu-binutils" in p.stderr


# ---------------------------------------------------------------------------
# G3's CLI: the image, and the refusal that holds before any splice
# ---------------------------------------------------------------------------


def test_bare_iso_means_the_targets_image_and_skips_when_it_is_absent(
        monkeypatch, capsys, tmp_path):
    """Bare ``--iso`` is the *target's* mounted image: absent, the gate skips (exit 0) -- and the
    line has to make it unmistakable that no comparison happened.

    A skip is not a pass, so the exit code alone would not be enough: the line must say that
    nothing was compared, no success line may appear beside it, and no copy may be left behind --
    a rebuilt image nobody compared must not look like a comparison's artifact.
    """
    ddr = load_ddr()
    probe = target_support.without_binary(tmp_path, monkeypatch, ddr, "probe_cli")
    out = tmp_path / "rebuilt.iso"
    assert ddr.cmd_iso(ddr.parse_args(["iso", "--out", str(out)])) == 0
    printed = capsys.readouterr().out
    assert printed.startswith("G3 skipped") and "nothing was compared" in printed
    assert str(probe.image) in printed
    assert "G3 ok" not in printed and "G3 FAIL" not in printed
    assert not out.exists()


def test_iso_refuses_a_reference_no_record_names(tmp_path, monkeypatch):
    """No pin, no criterion: an image no record names is a hard failure (exit 2), not a gate.

    The refusal is answered before anything is spliced, so a probe target with no manifest of its
    own proves it -- and proves that a *missing* manifest does not silently fall back to the
    registered target's pins.
    """
    ddr = load_ddr()
    probe = target_support.without_binary(tmp_path, monkeypatch, ddr, "probe_cli")
    image = tmp_path / "synthetic.iso"
    image.write_bytes(b"\x3D" * 4096)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    out = tmp_path / "rebuilt.iso"
    argv = ["iso", "--iso", str(image), "--elf", str(elf), "--out", str(out)]
    err = _stderr_of(ddr, argv)
    assert not out.exists()
    assert "no record" in err and "--allow-unpinned-reference" in err
    assert str(probe.checksums.relative_to(ROOT)) in err, "the message names the target's manifest"
    assert str(TARGET.checksums.relative_to(ROOT)) not in err, "not the registered target's"


def _stderr_of(ddr, argv):
    """``ddr.main`` writes to the real stderr; capture it by running the verb in a subprocess-free
    way is not possible, so read the message from the same call the test already made."""
    import contextlib, io
    err = io.StringIO()
    with contextlib.redirect_stderr(err):
        ddr.main(argv)
    return err.getvalue()


def test_iso_stops_rather_than_splicing_at_an_offset_nobody_measured(tmp_path, monkeypatch):
    """With the refusal opted out of, the splice needs the target's boot-ELF offset -- a
    measurement of its disc image -- so an unmeasured target stops there, loudly."""
    ddr = load_ddr()
    probe = target_support.without_binary(tmp_path, monkeypatch, ddr, "probe_cli")
    image = tmp_path / "synthetic.iso"
    image.write_bytes(b"\x3D" * 4096)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    out = tmp_path / "rebuilt.iso"
    err = _stderr_of(ddr, ["iso", "--iso", str(image), "--elf", str(elf), "--out", str(out),
                           "--allow-unpinned-reference"])
    assert "geometry" in err and not out.exists()
    assert reinsert.retail_image(probe) == probe.image


def test_the_two_g3_success_lines_are_distinguishable(monkeypatch, capsys, tmp_path):
    """A pinned reference reports the *pin*; an unpinned one says so in so many words.

    Both are the same splice and the same hash -- what a reader must be able to tell apart is
    whether the criterion was the descriptor's pinned digest or the file the copy was made from.
    """
    ddr = load_ddr()
    offset = target_support.geometry().image_elf_offset
    probe = target_support.without_binary(tmp_path, monkeypatch, ddr, "probe_cli")
    probe = dataclasses.replace(probe, geometry=target_support.geometry())
    monkeypatch.setattr(ddr.targets, "get", lambda name=None: probe)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    image = tmp_path / "synthetic.iso"
    data = bytearray(b"\x3D" * (offset + 0x100))
    data[offset:offset + len(elf.read_bytes())] = elf.read_bytes()  # the image it was built from
    image.write_bytes(bytes(data))

    unpinned = tmp_path / "unpinned.iso"
    assert ddr.main(["iso", "--iso", str(image), "--elf", str(elf), "--out", str(unpinned),
                     "--allow-unpinned-reference"]) == 0
    out = capsys.readouterr().out
    assert "G3 ok" in out and "(UNPINNED)" in out
    assert "equals the reference image it was spliced into" in out

    pinned = tmp_path / "pinned.iso"
    digest = reinsert.sha256(image)
    monkeypatch.setattr(ddr.g1, "pinned_hash_for", lambda name, checksums: digest)
    assert ddr.main(["iso", "--iso", str(image), "--elf", str(elf), "--out", str(pinned)]) == 0
    out = capsys.readouterr().out
    assert "G3 ok" in out and f"equals the pinned digest of {image.name}" in out
    assert "(UNPINNED)" not in out


# ---------------------------------------------------------------------------
# diff: the contract, and the refusal that protects it
# ---------------------------------------------------------------------------


@pytest.fixture
def ledger():
    """A symbol name, its address and the TU that owns it -- read from the target's ledger.

    Read rather than written down: the ledger is the oracle's output for *this* binary, so a
    hardcoded name would be a fact about a build that no longer exists.
    """
    if not TARGET.symbols.is_file() or not TARGET.cus.is_file():
        pytest.skip(f"{TARGET.name}: its config is generated from its ELF (Task 4)")
    manifests = __import__("verify.g2", fromlist=["g2"]).Manifests(
        TARGET.cus, TARGET.chunks, TARGET.symbols)
    for record in manifests.records:
        if record.get("kind") != "function" or record.get("low_pc") is None:
            continue
        name = manifests.symbol_at(record["low_pc"])
        if name.startswith("func_"):
            continue                                  # a name no evidence gives: no diff target
        return dict(name=name, address=record["low_pc"], tu=record["file"])
    pytest.skip(f"{TARGET.name}: its ledger names no function")


def test_diff_refuses_a_symbol_that_is_not_in_the_named_tu(ledger):
    p = run("diff", ledger["name"], TARGET.elf.name)
    assert p.returncode == 2
    assert "no translation unit matches" in p.stderr and "Traceback" not in p.stderr


def test_diff_refuses_a_symbol_no_ledger_names(ledger):
    p = run("diff", "no_such_symbol_at_all", ledger["tu"])
    assert p.returncode == 2
    assert "no symbol named" in p.stderr or "is at" in p.stderr
    assert "Traceback" not in p.stderr


def _objdiff_report(symbol, percent=100.0):
    """A minimal ``objdiff-cli`` report: the symbol on both sides, scored or not."""
    def entry():
        found = {"name": symbol, "kind": "SYMBOL_FUNCTION"}
        if percent is not None:
            found["match_percent"] = percent
        return found
    return {"left": {"symbols": [entry()]}, "right": {"symbols": [entry()]}}


def _objdiff_stub(monkeypatch, ddr, report, recorded):
    """``ddr``'s one call to ``objdiff-cli``: the argv is recorded, the report is canned."""
    class Stub:
        TOOLS_BY_KEY = {"objdiff": type("T", (), {"key": "objdiff"})()}

        @staticmethod
        def resolve(tool):
            return "/usr/bin/false"

        @staticmethod
        def version(tool):
            return "stub"

    def fake_run(argv, cwd=None, capture_output=True, text=True):
        recorded["argv"] = argv
        return type("P", (), {"returncode": 0, "stdout": json.dumps(report),
                              "stderr": ""})()

    monkeypatch.setattr(ddr, "check_deps", Stub)
    monkeypatch.setattr(ddr.subprocess, "run", fake_run)


def test_diff_measures_an_unpromoted_unit_instead_of_refusing_it(tmp_path, monkeypatch,
                                                                 capsys):
    """A unit with no C object is measured against our own bytes for the symbol (finding 10).

    The target side is retail's bytes for the symbol; the base side is the same bytes out of
    the split, emitted without splat's ``.NON_MATCHING`` alias -- an object objdiff refuses to
    score keeps the verb from printing a percentage it never computed, so the stand-in is what
    makes an unpromoted unit measurable at all.
    """
    ddr = load_ddr()
    if not ddr.GRAPH.is_file():
        pytest.skip("no build graph: the base object is read out of it (Task 5)")
    manifests = ddr.g2.Manifests(TARGET.cus, TARGET.chunks, TARGET.symbols)
    # Read out of this target's own manifests rather than from `ledger`: promoted units *do*
    # have an object to measure (that is the point of a promotion), so this needs a unit with
    # no source under `src/` -- and a split object the build has already assembled.
    file, function = next(
        (record["file"], record) for record in manifests.records
        if record.get("kind") == "function" and record.get("low_pc") is not None
        and not (ROOT / record["file"]).is_file()
        and ddr._split_object(manifests.symbol_at(record["low_pc"]), TARGET).is_file())
    symbol = manifests.symbol_at(function["low_pc"])
    assert ddr._promoted_object(file) is None
    target_object, stand_in = tmp_path / "retail.o", tmp_path / "split.o"
    for path in (target_object, stand_in):
        path.write_bytes(b"\x7fELF")
    calls = []

    def fake_retail(name, address, size, elf, directory=None):
        calls.append(("retail", name, address, size, pathlib.Path(elf)))
        return target_object

    def fake_split(name, split_object, directory=None):
        calls.append(("split", name, pathlib.Path(split_object)))
        return stand_in

    monkeypatch.setattr(ddr.diff_basis, "retail", fake_retail)
    monkeypatch.setattr(ddr.diff_basis, "split", fake_split)
    recorded = {}
    _objdiff_stub(monkeypatch, ddr, _objdiff_report(symbol), recorded)
    args = ddr.parse_args(["diff", symbol, file])
    assert ddr.cmd_diff(args) == 0
    # The base is resolved first on purpose: a refusal there must not leave an emitted object.
    assert calls == [("split", symbol, ddr._split_object(symbol, TARGET)),
                     ("retail", symbol, function["low_pc"],
                      function["high_pc"] - function["low_pc"], TARGET.elf)]
    argv = recorded["argv"]
    assert argv[argv.index("-1") + 1] == str(target_object)
    assert argv[argv.index("-2") + 1] == str(stand_in)
    err = capsys.readouterr().err
    assert "the retail bytes of " + symbol in err and TARGET.elf.name in err
    assert "no object in the build graph" in err and str(stand_in) in err


def test_diff_refuses_to_print_a_score_objdiff_never_computed(ledger, tmp_path, monkeypatch,
                                                              capsys):
    """A base object holding no such symbol is a refusal: no comparison, no percentage.

    objdiff still lists the symbols it read and still scores the *sections*, so a report
    without a ``match_percent`` for the symbol is exactly the shape that reads as a score while
    measuring nothing.  Nothing goes to stdout, and the remedy is named.
    """
    ddr = load_ddr()
    target_object, base_object = tmp_path / "retail.o", tmp_path / "unit.o"
    for path in (target_object, base_object):
        path.write_bytes(b"\x7fELF")
    monkeypatch.setattr(ddr.diff_basis, "retail", lambda *a, **k: target_object)
    _objdiff_stub(monkeypatch, ddr, _objdiff_report(ledger["name"], percent=None), {})
    args = ddr.parse_args(["diff", ledger["name"], ledger["tu"], "--base", str(base_object)])
    assert ddr.cmd_diff(args) == 2
    out = capsys.readouterr()
    assert out.out == "", "a report that compared nothing must not reach stdout"
    assert "compared nothing" in out.err and ledger["name"] in out.err


def test_diff_hands_objdiff_the_two_objects_it_was_given(ledger, tmp_path, monkeypatch, capsys):
    """``diff`` is a thin wrapper: the argv it hands ``objdiff-cli`` is the contract.

    Both object paths are replaced (the retail object is emitted from the image, the base
    object belongs to the unit's C source), so what is under test is the wiring: the symbol,
    the two sides, and the report of what each side is.
    """
    ddr = load_ddr()
    target_object, base_object = tmp_path / "retail.o", tmp_path / "unit.o"
    for path in (target_object, base_object):
        path.write_bytes(b"\x7fELF")
    monkeypatch.setattr(ddr.diff_basis, "retail", lambda *a, **k: target_object)
    recorded = {}
    _objdiff_stub(monkeypatch, ddr, _objdiff_report(ledger["name"]), recorded)
    args = ddr.parse_args(["diff", ledger["name"], ledger["tu"], "--base", str(base_object)])
    assert ddr.cmd_diff(args) == 0
    argv = recorded["argv"]
    assert argv[1] == "diff" and ledger["name"] in argv
    assert argv[argv.index("-1") + 1] == str(target_object)
    assert argv[argv.index("-2") + 1] == str(base_object)
    err = capsys.readouterr().err
    assert ledger["tu"] in err and ledger["name"] in err
    assert "the retail bytes" in err and "the object you named" in err
