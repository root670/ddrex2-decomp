"""The ``ddr`` command surface: what a verb does, without ever building anything.

The CLI is the only entry point a contributor is meant to use for routine work, so these tests
drive it -- but *never* into a real build: `ninja`, `splat` and `configure.py` belong to whoever
owns the tree (`AGENTS.md`), and `tests/target_support.py` explains the rule and provides the
probe targets these tests replace the descriptor's lookup with.  What is pinned here is the
selection (`--target`, both spellings, default), the loud stops (an unknown name, a target with
no binary, a target with no measured geometry), the remedy line for a missing host tool, and the
`diff` verb's contract -- including the case that matters most, a unit with no C source.
"""

import dataclasses
import importlib.machinery
import importlib.util
import os
import pathlib
import re
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


def test_no_test_reaches_for_the_build_machines():
    """The rule, checked: no test shells out to ninja, splat or configure.py.

    One build at a time belongs to the agent that owns the tree; a test that ran one would race
    that agent, every other test and its own assertions.  Verbs are driven in process against
    probes instead (`tests/target_support.py`), and the machines are proved by the owner.
    """
    machines = re.compile(r'"ninja"|\bninja\b|"splat"|configure\.py')
    offenders = {}
    for path in sorted((ROOT / "tests").rglob("*.py")):
        for number, line in enumerate(path.read_text().splitlines(), start=1):
            if "subprocess" in line and machines.search(line):
                offenders.setdefault(path.relative_to(ROOT).as_posix(), []).append(number)
    assert not offenders, f"a test shells out to the build machines: {offenders}"


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
    line has to make it unmistakable that no comparison happened."""
    ddr = load_ddr()
    probe = target_support.without_binary(tmp_path, monkeypatch, ddr, "probe_cli")
    assert ddr.cmd_iso(ddr.parse_args(["iso"])) == 0
    out = capsys.readouterr().out
    assert out.startswith("G3 skipped") and "nothing was compared" in out
    assert str(probe.image) in out


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


def test_diff_refuses_a_unit_with_no_c_source(ledger):
    """A unit with no C source has nothing to measure (finding 10).

    objdiff would otherwise be handed the retail split as *both* sides, take the split's own
    ``.NON_MATCHING`` name as the base counterpart and print a score it never computed -- which
    reads as "the split does not match retail" when the split *is* retail's bytes.
    """
    ddr = load_ddr()
    args = ddr.parse_args(["diff", ledger["name"], ledger["tu"]])
    if not ddr.GRAPH.is_file():
        pytest.skip("no build graph: the base object is read out of it (Task 5)")
    assert ddr._promoted_object(ddr.g2.Manifests(TARGET.cus, TARGET.chunks,
                                                TARGET.symbols).tu_named(ledger["tu"])) is None
    assert ddr.cmd_diff(args) == 2, "a unit with no C object must be refused"


def test_diff_hands_objdiff_the_two_objects_it_was_given(ledger, tmp_path, monkeypatch, capsys):
    """``diff`` is a thin wrapper: the argv it hands ``objdiff-cli`` is the contract.

    Both object paths are replaced (the split object belongs to the build, and the base object to
    the unit's C source), so what is under test is the wiring: the symbol, the two sides, and the
    report of what was compared.
    """
    ddr = load_ddr()
    target_object, base_object = tmp_path / "split.s.o", tmp_path / "unit.o"
    for path in (target_object, base_object):
        path.write_bytes(b"\x7fELF")
    monkeypatch.setattr(ddr, "_split_object", lambda symbol, target: target_object)
    recorded = {}

    class Stub:
        TOOLS_BY_KEY = {"objdiff": type("T", (), {"key": "objdiff"})()}

        @staticmethod
        def resolve(tool):
            return "/usr/bin/false"

        @staticmethod
        def version(tool):
            return "stub"

    def fake_run(argv, cwd=None):
        recorded["argv"] = argv
        return type("P", (), {"returncode": 0})()

    monkeypatch.setattr(ddr, "check_deps", Stub)
    monkeypatch.setattr(ddr.subprocess, "run", fake_run)
    args = ddr.parse_args(["diff", ledger["name"], ledger["tu"], "--base", str(base_object)])
    assert ddr.cmd_diff(args) == 0
    argv = recorded["argv"]
    assert argv[1] == "diff" and ledger["name"] in argv
    assert argv[argv.index("-1") + 1] == str(target_object)
    assert argv[argv.index("-2") + 1] == str(base_object)
    err = capsys.readouterr().err
    assert ledger["tu"] in err and ledger["name"] in err
