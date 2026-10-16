"""The host tools the build and the matching loop call by name must be present and usable.

Every test here is offline: :func:`check_deps.require` only *reports* what the machine
has, so a missing tool fails with the command that provides it rather than starting an
install behind the developer's back.
"""

import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import check_deps


def test_required_tools_are_present_and_usable():
    v = check_deps.require()
    assert v["as"].startswith("GNU assembler")
    assert v["splat"]
    assert check_deps.assembles_r5900()          # as accepts -march=5900 -EL


def test_every_tool_the_build_calls_is_reported_with_a_version():
    v = check_deps.require()
    assert sorted(v) == ["as", "ld", "ninja", "objcopy", "objdiff", "splat"]
    for key, version in v.items():
        assert version.strip(), f"{key} reported no version"


def test_the_r5900_flags_produce_a_little_endian_mips_object(tmp_path):
    """`-EL -march=5900 -mabi=eabi` must really assemble, not merely exit zero."""
    assert check_deps.assembles_r5900(tmp_path) is True
    assert (tmp_path / "r5900.s").read_text() == "lui $t0, 0x1234\naddiu $t1, $t0, 0x5678\njr $ra\n"
    blob = (tmp_path / "r5900.o").read_bytes()
    assert blob[:4] == b"\x7fELF"
    assert blob[5] == 1                                # EI_DATA: little-endian
    assert int.from_bytes(blob[18:20], "little") == 8  # EM_MIPS


def test_assembles_r5900_is_false_when_the_assembler_is_absent(monkeypatch):
    monkeypatch.setattr(check_deps, "which", lambda name: None)
    assert check_deps.assembles_r5900() is False


def test_a_missing_tool_names_the_command_that_provides_it(monkeypatch):
    real = check_deps.which
    monkeypatch.setattr(check_deps, "which", lambda name: None if name == "ninja" else real(name))
    with pytest.raises(check_deps.MissingDependency) as excinfo:
        check_deps.require()
    assert "ninja" in str(excinfo.value)
    assert "brew install ninja" in str(excinfo.value)


def test_a_missing_splat_names_the_pip_command(monkeypatch):
    """splat64 without its mips extras cannot satisfy `python3 -m splat`."""
    monkeypatch.setattr(check_deps, "find_spec", lambda name: None)
    with pytest.raises(check_deps.MissingDependency) as excinfo:
        check_deps.require()
    assert "python3 -m pip install --user 'splat64[mips]'" in str(excinfo.value)


def test_a_probe_that_hangs_is_a_missing_dependency_not_a_traceback(monkeypatch):
    """A tool that never answers `--version` is as absent as one that is not installed.

    `version` runs each probe under a 60-second timeout; a `TimeoutExpired` allowed to
    propagate would escape `ddr`'s `except MissingDependency` and print a traceback instead of
    the remedy (review finding 5, the shape `fetch._wibo_version` already uses).
    """
    def hang(argv, *args, **kwargs):
        raise subprocess.TimeoutExpired(argv, check_deps.TIMEOUT)

    monkeypatch.setattr(check_deps.subprocess, "run", hang)
    with pytest.raises(check_deps.MissingDependency) as excinfo:
        check_deps.version(check_deps.TOOLS_BY_KEY["ninja"])
    assert "ninja" in str(excinfo.value)
    assert "brew install ninja" in str(excinfo.value)


def test_the_r5900_probe_reports_a_hung_assembler_instead_of_raising(tmp_path, monkeypatch,
                                                                    capsys):
    """The same guard on the assembler probe: a hang is a failed check, not an exception."""
    def hang(argv, *args, **kwargs):
        raise subprocess.TimeoutExpired(argv, check_deps.TIMEOUT)

    monkeypatch.setattr(check_deps, "which", lambda name: "/usr/bin/true")
    monkeypatch.setattr(check_deps.subprocess, "run", hang)
    assert check_deps.assembles_r5900(tmp_path) is False
    assert "could not run the R5900 probe" in capsys.readouterr().err


def test_require_only_runs_the_tools_themselves(monkeypatch):
    """require() probes; it never installs (a spy over every command it runs)."""
    calls = []
    real_run = subprocess.run

    def spy(argv, *args, **kwargs):
        calls.append([str(a) for a in argv])
        return real_run(argv, *args, **kwargs)

    monkeypatch.setattr(check_deps.subprocess, "run", spy)
    check_deps.require()
    assert calls, "require() ran nothing at all"
    assert {pathlib.Path(argv[0]).name for argv in calls} <= {
        "mips-linux-gnu-as", "mips-linux-gnu-ld", "mips-linux-gnu-objcopy",
        "ninja", "objdiff-cli", "python3",
    }


def test_provenance_block_is_written_once_and_survives_refetch(tmp_path):
    from toolchain import fetch

    manifest = tmp_path / "PROVENANCE.txt"
    report = check_deps.record(path=manifest)
    first = manifest.read_text()
    assert report["as"].startswith("GNU assembler")
    assert "brew install mips-linux-gnu-binutils" in first
    assert "python3 -m pip install --user 'splat64[mips]'" in first
    assert "https://github.com/encounter/objdiff/releases" in first
    for version in report.values():
        assert version in first
    assert first.count(check_deps.HOST_TOOLS_BEGIN) == 1

    check_deps.record(path=manifest)                            # idempotent
    assert manifest.read_text().count(check_deps.HOST_TOOLS_BEGIN) == 1

    # fetch.py owns the file; a refetch must not drop the host section.
    fetch.write_provenance(state_file=tmp_path / "state.json", path=manifest)
    again = manifest.read_text()
    assert again.count(check_deps.HOST_TOOLS_BEGIN) == 1
    assert "brew install mips-linux-gnu-binutils" in again
