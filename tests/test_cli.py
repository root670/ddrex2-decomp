"""The ``ddr`` command surface: what a verb does for the registered target.

The CLI is the only entry point a contributor (or an agent) is meant to use for routine work, so
these tests drive it as a *process* -- the way the plan's tasks and the CI workflows do.  With the
target registry holding one target whose config is not generated yet, the behaviour that matters
here is the *loud stop*: every verb names the target's own file (or its unmeasured geometry) and
returns 2, and none of them quietly works on anything else.  The target-flag plumbing is covered
without a run at all, and the two hermetic gates (the ISO splice and the oracle's determinism) are
exercised on synthetic files so there is no dependency on the retail binary.
"""

import dataclasses
import importlib.machinery
import importlib.util
import os
import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))  # `config.targets`, the descriptor every tool reads

from config import targets  # noqa: E402

TARGET = targets.get()


def run(*args):
    return subprocess.run([str(ROOT / "ddr"), *args], cwd=ROOT, capture_output=True, text=True)


def load_ddr():
    """The ``ddr`` script as a module, for the cases the process boundary cannot reach.

    ``ddr`` has no ``.py`` suffix, so it is loaded by path; executing it imports what the CLI
    imports and defines the verbs without running them (``main`` is guarded).  Needed where the
    test must *replace* an input the CLI reads (a mount, a target's image).
    """
    loader = importlib.machinery.SourceFileLoader("ddr_cli_under_test", str(ROOT / "ddr"))
    module = importlib.util.module_from_spec(
        importlib.util.spec_from_loader(loader.name, loader))
    loader.exec_module(module)
    return module


def test_the_target_flag_is_accepted_before_and_after_the_verb():
    """``--target`` is one selection with two spellings, and its default is the registry's."""
    ddr = load_ddr()
    for argv in (["--target", TARGET.name, "verify"], ["verify", "--target", TARGET.name],
                 ["verify"], ["oracle"]):
        assert ddr._target(ddr.parse_args(argv)) is TARGET, argv


def test_an_unknown_target_is_a_usage_error_naming_the_one_that_exists():
    p = run("--target", "usam2", "verify")
    assert p.returncode == 2
    assert "usam2" in p.stderr and TARGET.name in p.stderr
    assert "Traceback" not in p.stderr and "G1 ok" not in p.stdout


def test_every_verb_stops_loudly_while_the_target_has_no_config():
    """The state the tree is in between "target registered" and "config generated".

    Each verb names the file or the measurement it is missing, returns 2, and writes nothing:
    in particular neither gate may report a verdict about a build that does not exist.
    """
    built = str(TARGET.built.relative_to(ROOT))
    elf = str(TARGET.elf.relative_to(ROOT))
    verify = run("verify")
    assert verify.returncode == 2
    assert built in verify.stderr and "G1 ok" not in verify.stdout
    assert "Traceback" not in verify.stderr

    oracle = run("oracle")
    assert oracle.returncode == 2
    assert elf in oracle.stderr and "no such file" in oracle.stderr

    build = run("build")
    assert build.returncode == 2
    assert elf in build.stderr and "Traceback" not in build.stderr

    configure = run("--target", TARGET.name, "build")
    assert configure.returncode == 2
    # ... and nothing of the target's config was written by any of them.
    for path in (TARGET.checksums, TARGET.cus, TARGET.chunks, TARGET.symbols):
        assert not path.exists(), path


def test_a_missing_host_tool_is_reported_with_its_remedy():
    """``check_deps.require`` is the CLI's gate: a remedy, never a traceback."""
    env = {**os.environ, "PATH": "/nonexistent/ddr-cli-test"}
    p = subprocess.run([sys.executable, str(ROOT / "ddr"), "build"],
                       cwd=ROOT, capture_output=True, text=True, env=env)
    assert p.returncode != 0
    assert "Traceback" not in p.stderr
    assert "remedy:" in p.stderr and "brew install mips-linux-gnu-binutils" in p.stderr


def test_bare_iso_means_the_targets_image_and_skips_when_it_is_absent(
        monkeypatch, capsys, tmp_path):
    """Bare ``--iso`` is the *target's* mounted image: absent, the gate skips (exit 0) -- and the
    line has to make it unmistakable that no comparison happened.

    The target is replaced rather than a module constant, because the image a bare ``--iso``
    means is the descriptor's (`Target.image`).
    """
    ddr = load_ddr()
    absent = tmp_path / "absent.iso"
    real = ddr.targets.get
    monkeypatch.setattr(ddr.targets, "get",
                        lambda name=None: dataclasses.replace(real(name), image=absent))
    assert ddr.cmd_iso(ddr.parse_args(["iso"])) == 0
    out = capsys.readouterr().out
    assert out.startswith("G3 skipped") and "nothing was compared" in out


def test_iso_refuses_a_reference_no_record_names(tmp_path):
    """No pin, no criterion: an image no record names is a hard failure (exit 2), not a gate.

    The refusal is answered before anything is spliced, so it holds in the target's current
    state -- no built image, no checksums manifest, no measured offset.
    """
    image = tmp_path / "synthetic.iso"
    image.write_bytes(b"\x3D" * 4096)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    out = tmp_path / "rebuilt.iso"
    p = run("iso", "--iso", str(image), "--elf", str(elf), "--out", str(out))
    assert p.returncode == 2
    assert "G3 ok" not in p.stdout
    assert "no record" in p.stderr and "--allow-unpinned-reference" in p.stderr
    assert not out.exists()


def test_iso_stops_rather_than_splicing_at_an_offset_nobody_measured(tmp_path):
    """With the refusal opted out of, the splice needs the target's boot-ELF offset -- which is
    a measurement of its disc image.  An unmeasured target stops there, loudly, instead of
    writing a copy that no gate could defend."""
    image = tmp_path / "synthetic.iso"
    image.write_bytes(b"\x3D" * 4096)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    out = tmp_path / "rebuilt.iso"
    p = run("iso", "--iso", str(image), "--elf", str(elf), "--out", str(out),
            "--allow-unpinned-reference")
    assert p.returncode == 2
    assert "G3 ok" not in p.stdout and "geometry" in p.stderr
    assert not out.exists()


def test_oracle_reproduces_the_committed_artifacts_when_the_target_has_a_binary():
    """The oracle is deterministic: a fresh run reproduces what is committed (or staged).

    The target's binary and config are placed by the retarget plan's Task 4, so this runs then;
    until it does, the check is skipped *visibly* rather than asserted against nothing.
    """
    if not TARGET.elf.is_file() or not TARGET.cus.is_file():
        pytest.skip(f"{TARGET.name}: {TARGET.elf.name} and its config are generated in Task 4")
    watched = [path for path in TARGET.config_dir.glob("*.json")]
    watched += [TARGET.symbols, TARGET.unplaced]
    watched += [path for path in (ROOT / "include").rglob("*") if path.is_file()]
    before = {path: path.read_bytes() for path in watched if path.is_file()}
    p = run("oracle")
    assert p.returncode == 0, p.stdout + p.stderr
    assert {path: path.read_bytes() for path in before} == before
