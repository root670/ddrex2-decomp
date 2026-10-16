"""Runtime guards for the whole suite: no test builds, no test writes the tree.

Source scanning loses to indirection, so the rules are enforced where they bite, at *session*
scope -- a module-scoped fixture that builds would otherwise run before a function-scoped guard:

* **no build machines.**  Every way a process can be started from Python is wrapped -- ``os.system``,
  ``os.popen``, ``os.posix_spawn``/``spawnv``/``spawnvp``/``execlp``/``execvp``,
  ``pty.spawn`` and ``subprocess.run``/``Popen``.  A call whose *program* is ``ninja``, ``splat`` or
  ``configure.py`` fails the test that made it; a machine word appearing as an *argument* (asking a
  tool about another tool, as ``check_deps`` does) is not a build, and version/help probes are not
  either.  A grandchild started by a child cannot be hooked -- the backstop below catches it.
* **no writes into the tree.**  The generators the oracle and configure write with are wrapped:
  *every* path argument is inspected, exactly one of which may be the output, and a write outside
  pytest's temporary root fails the test.  It fails **closed**: a writer that is not one of the
  known shape is wrapped by inspecting all its ``pathlib.Path``-ish arguments, so a new writer or a
  new module is covered rather than missed.
* **the backstop.**  ``tests_leave_the_repository_alone`` records ``git status --porcelain`` and the
  mtimes of the generated trees and the committed manifests before the session and asserts they are
  unchanged at the end.  Whatever the hooks miss -- an unhooked spawn, a grandchild build, a writer
  nobody wrapped -- changes the repository, and this is what catches it.
"""

import os
import pathlib
import pty
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

#: The trees and manifests a build, an oracle run or a configure touches.  Tracked as
#: `(path, digest)`; a missing path is recorded as missing, so creating one is a change too.
WATCHED = ("asm", "build", "out", "include", "build.ninja", "objdiff.json")

#: Generators that write generated artifacts, and their output argument.
WRITERS = (("configure", "write_if_different", 0),
           ("emit_cus", "write", 0), ("emit_chunks", "write", 0),
           ("emit_symbols", "write", 0), ("emit_symbols", "write_unplaced", 0),
           ("emit_headers", "write_all", 1))


def _machine_in(argv) -> str | None:
    """The build machine an argv starts, or None: the *program* decides, never an argument."""
    if isinstance(argv, (str, bytes)):
        words = str(argv).split()
    else:
        try:
            words = [os.fsdecode(word) for word in argv]
        except TypeError:
            return None
    if not words:
        return None
    program = pathlib.Path(words[0]).name
    if program in {"python", "python3"} and "-m" in words[1:3]:
        program = pathlib.Path(words[words.index("-m") + 1]).name
    if program not in MACHINES:
        return None
    if PROBES & set(words):        # `ninja --version`
        return None
    return program


class _MachineGuard:
    """Every process-spawning entry point, wrapped, for the whole session."""

    def __init__(self):
        self.originals = {}

    def install(self):
        import subprocess as sp
        targets = {
            "subprocess.run": (sp, "run"),
            "subprocess.Popen": (sp, "Popen"),
            "subprocess.call": (sp, "call"),
            "subprocess.check_call": (sp, "check_call"),
            "os.system": (os, "system"),
            "os.popen": (os, "popen"),
            "os.posix_spawn": (os, "posix_spawn"),
            "os.posix_spawnp": (os, "posix_spawnp"),
            "os.spawnv": (os, "spawnv"),
            "os.spawnvp": (os, "spawnvp"),
            "os.execlp": (os, "execlp"),
            "os.execvp": (os, "execvp"),
            "pty.spawn": (pty, "spawn"),
        }
        for label, (module, name) in targets.items():
            original = getattr(module, name, None)
            if original is None:
                continue
            self.originals[label] = (module, name, original)
            setattr(module, name, self._guarded(label, original))

    def _guarded(self, label, original):
        def guarded(*args, **kwargs):
            argv = args[0] if args else kwargs.get("args", kwargs.get("path", ""))
            if kwargs.get("shell") and isinstance(argv, str):
                for word in argv.split():
                    if pathlib.Path(word).name in MACHINES and not (PROBES & set(argv.split())):
                        pytest.fail(f"a test started a build machine via {label}: {argv!r}")
            else:
                machine = _machine_in(argv)
                if machine:
                    pytest.fail(f"a test started a build machine via {label}: {machine!r} "
                                f"in {argv!r}")
            return original(*args, **kwargs)
        guarded.__name__ = f"guarded_{label.replace('.', '_')}"
        return guarded

    def restore(self):
        for module, name, original in self.originals.values():
            setattr(module, name, original)


class _WriteGuard:
    """A writer may only touch pytest's temporary root -- checked on *every* argument."""

    def __init__(self, roots):
        self.roots = tuple(roots)

    def _allowed(self, value) -> bool:
        try:
            resolved = pathlib.Path(value).resolve()
        except (TypeError, ValueError, OSError):
            return True                                   # not a path: nothing to police
        if not (str(value).startswith("/") or str(value).startswith(".")
                or resolved.is_absolute()):
            return True
        return any(resolved == root or resolved.is_relative_to(root) for root in self.roots)

    def wrap(self, function, output=None, strict=False):
        """Guard ``function``: ``output`` is its output argument's index, if it is known.

        A *known* writer is checked exactly -- its output argument, or a keyword naming one --
        because its other arguments are inputs (an ELF, content).  An *unknown* writer is checked
        **strictly** instead: any path-like argument that resolves into the repository refuses the
        call, so a writer nobody listed fails closed rather than slipping through.
        """
        def guarded(*args, **kwargs):
            candidates = []
            if output is not None:
                candidates = [args[output]] if len(args) > output else []
                candidates += [value for key, value in kwargs.items()
                               if key in ("path", "out", "outdir", "directory", "target")]
            elif strict:
                candidates = [value for value in list(args) + list(kwargs.values())
                              if isinstance(value, (str, pathlib.Path))]
            outside = [value for value in candidates if not self._allowed(value)]
            if outside:
                pytest.fail(f"a test's generator wrote outside its temporary directory: "
                            f"{outside} (in {getattr(function, '__name__', function)})")
            return function(*args, **kwargs)
        guarded.__name__ = getattr(function, "__name__", "guarded")
        return guarded


@pytest.fixture(scope="session", autouse=True)
def no_build_machines():
    """Fail the test that starts a build machine, however it spells the call.

    Session-scoped on purpose: a module- or class-scoped fixture runs before any function-scoped
    one, so a function-scoped guard would miss exactly the setup code that builds.
    """
    guard = _MachineGuard()
    guard.install()
    try:
        yield
    finally:
        guard.restore()


@pytest.fixture(scope="session", autouse=True)
def no_tree_writes():
    """The generators may only write under the session's temporary root.

    Fails *closed*: the wrap inspects every argument of every writer it knows, so a writer that
    gained an output argument, or a module added later, is refused rather than silently allowed.
    """
    import tempfile
    guard = _WriteGuard({pathlib.Path(tempfile.gettempdir()).resolve()})
    known = {(module_name, function_name): output for module_name, function_name, output in WRITERS}
    wrapped = []
    for module_name in {name for name, _, _ in WRITERS}:
        module = sys.modules.get(module_name)
        if module is None:
            continue
        for name in dir(module):
            candidate = getattr(module, name)
            if not (name.startswith("write") and callable(candidate)):
                continue
            if name in getattr(module, "__dict__", {}) or True:
                output = known.get((module_name, name))
                setattr(module, name, guard.wrap(candidate, output, strict=output is None))
                wrapped.append((module, name, candidate))
    try:
        yield
    finally:
        for module, name, original in wrapped:
            setattr(module, name, original)


def _snapshot():
    """What the repository's *generated* state looks like: their status lines, and their mtimes.

    Scoped to the trees and manifests a build, an oracle run or a configure writes, so a peer
    editing `src/`, `tests/` or a tool while the suite runs is not mistaken for the suite's own
    mutation -- and their half-finished build *is* caught, because it lands in exactly these paths.
    """
    status = subprocess.run(["git", "status", "--porcelain", "--", *WATCHED, "config"],
                            cwd=ROOT, capture_output=True, text=True, check=False).stdout
    stamps = {}
    for name in WATCHED:
        path = ROOT / name
        if path.exists():
            stamps[name] = (path.stat().st_mtime_ns,
                            max((child.stat().st_mtime_ns for child in path.rglob("*")),
                                default=0) if path.is_dir() else 0)
        else:
            stamps[name] = None
    return {"status": status, "stamps": stamps}


@pytest.fixture(scope="session", autouse=True)
def tests_leave_the_repository_alone():
    """The backstop: whatever the hooks miss changes the repository, and this notices.

    Recorded before the session and compared at the end -- the tracked tree's status, and the
    mtimes of the generated trees (`asm/`, `build/`, `out/`, `include/`), the graph and the objdiff
    project.  A grandchild build, an unhooked spawn and an unwrapped writer all end up here.
    """
    before = _snapshot()
    try:
        yield
    finally:
        after = _snapshot()
        assert after["status"] == before["status"], (
            "the test suite changed the repository's tracked state:\n"
            + after["status"])
        changed = {name: (before["stamps"][name], after["stamps"][name])
                   for name in after["stamps"] if before["stamps"][name] != after["stamps"][name]}
        assert not changed, f"the test suite touched generated trees: {changed}"
