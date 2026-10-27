"""The staged source path: retail's DWARF name length, with and without a runner.

Retail's CU name is a build host's path (``C:\\work2\\usaex2\\src\\sys\\sys_scf.c``), and
``compile.py`` compiles each unit from a staged copy whose *recorded* spelling is exactly as
long, so replacing the name in the object cannot resize a DIE.  What the compiler records is
not the host path this driver wrote to, though: under wibo the guest sees the host root as the
``Z:`` drive, and a native Windows run records the host path itself.  Both spellings have to
fit retail's budget, so the padding directory is measured from the root's *recorded* spelling
rather than from a hardcoded ``Z:``.

Nothing here runs the compiler: the staging is a function of the unit's retail name and the
runner, so that is what is pinned.
"""

import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
for extra in (str(ROOT), str(ROOT / "tools"), str(ROOT / "tools" / "oracle")):
    if extra not in sys.path:
        sys.path.insert(0, extra)

from toolchain import compile as cc  # noqa: E402

#: A retail CU name as `cus.json` records it: a Windows host path, 33 bytes.
RETAIL_NAME = "C:\\work2\\usaex2\\src\\sys\\sys_scf.c"


def _tu(name: str = RETAIL_NAME) -> cc.Tu:
    """A unit with a data anchor and no functions: staging reads only ``file``/``name``."""
    return cc.Tu("src/sys/sys_scf.c", name, [], 0, 0, 0, 0, [], anchor=0x00100000)


def test_the_recorded_name_is_exactly_retails_length_under_wibo():
    tu = _tu()
    staged = cc.staged_path(tu, "/toolchain/wibo")
    recorded = cc.recorded_name(staged, "/toolchain/wibo")
    assert recorded.startswith(b"Z:\\")
    assert b"/" not in recorded
    assert len(recorded) == len(tu.name)


def test_a_native_run_records_the_host_path_and_never_invents_a_drive():
    """``wibo is None``: the compiler is handed the host path, so that is what it records."""
    tu = _tu()
    staged = cc.staged_path(tu, None)
    recorded = cc.recorded_name(staged, None)
    assert b"Z:" not in recorded
    assert b"/" not in recorded
    assert len(recorded) == len(tu.name)


def test_the_two_runners_stage_the_same_host_path_with_different_padding():
    """One staging path per unit -- only the length of the directory differs, by the prefix."""
    tu = _tu()
    runner = cc.staged_path(tu, "/toolchain/wibo")
    native = cc.staged_path(tu, None)
    assert runner.parent != native.parent
    assert runner.name == native.name == tu.source.name
    # The native spelling is shorter by the ``Z:`` the runner adds, so its directory is longer
    # by those two bytes: both recorded names are retail's length.
    assert len(native.parent.name) == len(runner.parent.name) + 2


def test_a_name_too_short_to_stage_is_refused():
    """Retail's spelling is the whole budget; one byte less and the unit cannot be staged.

    The name is short enough that even ``Z:/tmp`` -- the shortest root any host has -- leaves
    no room for the directory, so the refusal does not depend on this host's ``/tmp``.
    """
    too_short = "C:\\x\\sys_scf.c"
    try:
        cc.staged_path(_tu(too_short), "/toolchain/wibo")
    except cc.Unusable as refused:
        assert "cannot be reproduced" in str(refused)
    else:  # pragma: no cover - the assertion is the refusal
        raise AssertionError(f"{too_short} installed as a staging path")
