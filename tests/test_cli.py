"""The ``ddr`` command surface: what a verb does for the registered target.

The CLI is the only entry point a contributor (or an agent) is meant to use for routine work, so
these tests drive it as a *process* -- the way the plan's tasks and the CI workflows do.  The
target registry holds one target whose config is generated (retarget Task 4), so the behaviour
that matters here is the *loud stop* at every input the target does not have yet: a retail binary
a clone does not carry (`orig/` is gitignored), the built image a build has not produced, a
geometry nobody has measured.  None of them quietly works on anything else.  The target-flag
plumbing is covered without a run at all, and the hermetic gates (the ISO splice and the oracle's
determinism) are exercised on synthetic files so there is no dependency on the retail binary.
"""

import collections
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


def test_every_verb_stops_loudly_while_the_targets_binary_is_not_placed(
        monkeypatch, capsys, tmp_path):
    """The state every fresh checkout is in: `orig/<elf>` is gitignored, so it is the developer
    who copies the retail binary in -- and until they do, each verb names the file or the build
    it is missing, returns 2, and writes nothing.

    The descriptor is replaced rather than the files: the *target* is what says where its binary
    is, and `config/<name>/` stays the real one so a verb that did write would be caught here.
    """
    ddr = load_ddr()
    real = ddr.targets.get()
    absent = tmp_path / "not-placed.elf"
    monkeypatch.setattr(ddr.targets, "get",
                        lambda name=None: dataclasses.replace(real, elf=absent))
    before = {path: path.read_bytes() for path in (TARGET.cus, TARGET.chunks, TARGET.symbols)}

    built = f"out/{absent.name}"
    assert ddr.main(["verify"]) == 2
    err = capsys.readouterr().err
    assert built in err and "run ./ddr build" in err and "Traceback" not in err

    assert ddr.main(["oracle"]) == 2
    err = capsys.readouterr().err
    assert str(absent) in err and "no such file" in err

    assert ddr.main(["--target", TARGET.name, "build"]) == 2
    err = capsys.readouterr().err
    assert str(absent) in err and "Traceback" not in err

    # ... and nothing of the target's config was written by any of them.
    for path, content in before.items():
        assert path.read_bytes() == content, path


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


def test_iso_stops_rather_than_splicing_at_an_offset_nobody_measured(
        monkeypatch, capsys, tmp_path):
    """With the refusal opted out of, the splice needs the target's boot-ELF offset -- which is
    a measurement of its disc image.  An *unmeasured* target stops there, loudly, instead of
    writing a copy that no gate could defend."""
    ddr = load_ddr()
    real = ddr.targets.get()
    monkeypatch.setattr(ddr.targets, "get",
                        lambda name=None: dataclasses.replace(real, geometry=None))
    image = tmp_path / "synthetic.iso"
    image.write_bytes(b"\x3D" * 4096)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    out = tmp_path / "rebuilt.iso"
    status = ddr.main(["iso", "--iso", str(image), "--elf", str(elf), "--out", str(out),
                       "--allow-unpinned-reference"])
    captured = capsys.readouterr()
    assert status == 2
    assert "G3 ok" not in captured.out and "geometry" in captured.err
    assert not out.exists()


def test_the_oracle_runs_for_a_target_with_no_ghidra_function_list(
        monkeypatch, capsys, tmp_path):
    """A Ghidra function list is an *optional* input: it names the function starts the DWARF
    does not cover, and a target whose DWARF is complete has none.

    The registered target is such a target, so the oracle must pass *no* Ghidra path rather than
    the path of a file that is not there -- the first `oracle` run on this target stopped on
    exactly that.  The four artifact families are stubbed, so this is the CLI's own wiring: what
    a target's absence of a Ghidra list resolves to.
    """
    ddr = load_ddr()
    real = ddr.targets.get()
    assert ddr._ghidra(real) is None                  # the premise: this target has no list
    placed = tmp_path / "retail.elf"
    placed.write_bytes(b"\x7fELF")
    monkeypatch.setattr(ddr.targets, "get",
                        lambda name=None: dataclasses.replace(real, elf=placed))
    seen = {}

    def build(elf_path, ghidra_json_path=None):
        seen["elf"], seen["ghidra"] = elf_path, ghidra_json_path
        return []

    monkeypatch.setattr(ddr.emit_cus, "build", lambda path: [])
    monkeypatch.setattr(ddr.emit_cus, "write", lambda path, cus: None)
    monkeypatch.setattr(ddr.emit_chunks, "build", lambda path, line, debug: [])
    monkeypatch.setattr(ddr.emit_chunks, "write", lambda path, chunks: None)
    monkeypatch.setattr(ddr.emit_symbols, "build", build)
    monkeypatch.setattr(ddr.emit_symbols, "write", lambda path, records: None)
    monkeypatch.setattr(ddr.emit_symbols, "write_unplaced", lambda path, records: None)
    monkeypatch.setattr(ddr.emit_headers, "write_all", lambda path, dest: [])

    assert ddr.main(["oracle"]) == 0
    out, err = capsys.readouterr()
    assert seen == {"elf": placed, "ghidra": None}
    assert "no Ghidra function list" in out and not err


def test_the_generated_config_is_the_measurement_of_the_targets_binary():
    """`config/<target>/` is the oracle's output for the retail ELF, and these are the DWARF
    facts the plan records for this binary: 2,925 compile units -- 249 translation units and
    2,676 functions -- and `sys_scf.c`'s two functions at 0x1B3D30 (12 bytes) and 0x1B3D40
    (48 bytes).

    The artifacts are committed (the oracle is deterministic), so this asserts the config a
    reader gets rather than one a run just produced; a drift from the binary is the finding.
    """
    cus = json.loads(TARGET.cus.read_text())
    kinds = collections.Counter(record["kind"] for record in cus)
    assert kinds == {"tu": 249, "function": 2676}, kinds
    assert len({record["file"] for record in cus if record["kind"] == "tu"}) == 249

    scf = [record for record in cus
           if record["file"] == "src/sys/sys_scf.c" and record["kind"] == "function"]
    assert [(record["low_pc"], record["high_pc"] - record["low_pc"]) for record in scf] \
        == [(0x1B3D30, 12), (0x1B3D40, 48)]

    chunks = json.loads(TARGET.chunks.read_text())
    # One `.debug` chunk per translation unit, one `.line` chunk per function -- and both have
    # to tile their section exactly, which is the same measurement the descriptor carries: the
    # manifests and the geometry cannot disagree about how long the sections are.
    sections = collections.Counter(chunk["section"] for chunk in chunks)
    assert sections == {".debug": 249, ".line": 2676}, sections
    geometry = TARGET.geometry_required()
    assert sum(record["size"] for record in cus) == geometry.debug_size
    for section, size in ((".debug", geometry.debug_size), (".line", geometry.line_size)):
        mine = [chunk for chunk in chunks if chunk["section"] == section]
        assert sum(chunk["size"] for chunk in mine) == size, section
        assert [chunk["offset"] for chunk in sorted(mine, key=lambda c: c["offset"])] \
            == sorted(chunk["offset"] for chunk in mine)
    assert TARGET.symbols.is_file() and TARGET.unplaced.is_file()


def test_oracle_reproduces_the_committed_artifacts_when_the_target_has_a_binary():
    """The oracle is deterministic: a fresh run reproduces what is committed (or staged).

    The *input* is the developer's own retail binary (`orig/` is gitignored), so a checkout
    without one skips this *visibly* rather than asserting against nothing; the artifacts it
    would rewrite are the committed ones this test reads first.
    """
    if not TARGET.elf.is_file():
        pytest.skip(f"{TARGET.name}: {TARGET.elf.name} is the developer's own copy "
                    f"(retail binaries are never committed)")
    watched = [path for path in TARGET.config_dir.glob("*.json")]
    watched += [TARGET.symbols, TARGET.unplaced]
    watched += [path for path in (ROOT / "include").rglob("*") if path.is_file()]
    before = {path: path.read_bytes() for path in watched if path.is_file()}
    p = run("oracle")
    assert p.returncode == 0, p.stdout + p.stderr
    assert {path: path.read_bytes() for path in before} == before
