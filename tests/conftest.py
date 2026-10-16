"""Runtime guards for the whole suite: no test builds, and no test writes the tree.

Source scanning loses to indirection (a multi-line ``subprocess.run(``, a helper, ``os.system``),
so the rule is enforced where it actually bites:

* **no build machines.**  ``subprocess.run``/``Popen``/``os.system`` are wrapped, and an argv that
  names ``ninja``, ``splat`` or ``configure.py`` fails the test that made the call.  One agent owns
  the build at a time (`AGENTS.md`); a test that started one would race that agent, every other test
  and its own assertions.  Verbs are driven in process against probe targets
  (`tests/target_support.py`) instead, and the machines are proved by whoever owns the tree.
* **no writes into the tree.**  The oracle's writers and ``configure.write_if_different`` are
  wrapped: writing outside pytest's temporary root fails the test.  That is the mutation a source
  scan could never catch -- ``ddr.main(["oracle"])`` against a *measured* target regenerates the
  committed manifests without spawning anything.

Both are autouse, so a new test inherits them without asking.  A test may opt out only by taking
``allow_build_machines``/``allow_tree_writes``, which exist so that an intentional exception is
visible in the diff rather than hidden in the guard.
"""

import os
import pathlib
import subprocess
import sys
import tempfile

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

#: The programs that turn this repository's sources into its artifacts.
MACHINES = {"ninja", "ninja-build", "configure.py", "splat", "splat64"}


#: Asking a tool what version it is is not building anything (`check_deps` does exactly that).
PROBES = {"--version", "-version", "-V", "--help", "-h"}


def _named_machine(argv) -> str | None:
    if isinstance(argv, (str, bytes)):
        argv = [argv]
    try:
        words = [os.fsdecode(word) for word in argv]
    except TypeError:
        return None
    if PROBES & set(words):
        return None
    for word in words:
        if pathlib.Path(word).name in MACHINES:
            return word
        if word == "splat" and "splat" in words:          # `python3 -m splat split`
            return "splat"
    return None


@pytest.fixture(autouse=True)
def no_build_machines(monkeypatch, request):
    """Fail the test if it starts a build machine, however it spells the call."""
    if "allow_build_machines" in request.fixturenames:
        return
    real_run, real_popen = subprocess.run, subprocess.Popen
    real_system = os.system

    def guarded_run(argv, *args, **kwargs):
        machine = _named_machine(argv)
        if machine:
            pytest.fail(f"a test started a build machine: {machine!r} in {argv!r}")
        return real_run(argv, *args, **kwargs)

    def guarded_popen(argv, *args, **kwargs):
        machine = _named_machine(argv)
        if machine:
            pytest.fail(f"a test started a build machine: {machine!r} in {argv!r}")
        return real_popen(argv, *args, **kwargs)

    def guarded_system(command):
        machine = _named_machine(str(command).split())
        if machine:
            pytest.fail(f"a test started a build machine: {machine!r} in {command!r}")
        return real_system(command)

    monkeypatch.setattr(subprocess, "run", guarded_run)
    monkeypatch.setattr(subprocess, "Popen", guarded_popen)
    monkeypatch.setattr(os, "system", guarded_system)


@pytest.fixture(autouse=True)
def no_tree_writes(monkeypatch, tmp_path, request):
    """Fail the test if a *generator* writes outside pytest's temporary root.

    Only the generators are wrapped: a test that writes its own scratch file, or a toolchain test
    that records versions under `toolchain/`, is not what this protects against.
    """
    if "allow_tree_writes" in request.fixturenames:
        return
    guard = _WriteGuard(tmp_path)

    for name in ("configure", "emit_cus", "emit_chunks", "emit_symbols", "emit_headers"):
        module = sys.modules.get(name)
        if module is None:
            continue
        for function in ("write", "write_unplaced", "write_all", "write_if_different"):
            if hasattr(module, function):
                monkeypatch.setattr(module, function, guard.wrap(getattr(module, function)))


class _WriteGuard:
    """Everything the guarded writers touch must land under ``tmp_path``."""

    def __init__(self, tmp_path):
        self.roots = {pathlib.Path(tmp_path).resolve(),
                      pathlib.Path(tempfile.gettempdir()).resolve()}

    def wrap(self, function):
        def guarded(path, *args, **kwargs):
            resolved = pathlib.Path(path).resolve()
            if not any(resolved.is_relative_to(root) for root in self.roots):
                pytest.fail(f"a test's generator wrote into the tree: {path!r} "
                            f"(only pytest's temporary directory is allowed)")
            return function(path, *args, **kwargs)
        guarded.__name__ = getattr(function, "__name__", "guarded")
        return guarded
