"""`compile.py`'s include path: the target's generated headers, on the compiler's search path.

`place()` stages the source under ``/tmp`` and runs MWCC with its own *installation* directory
as the working directory, so a quoted ``#include`` of a generated header -- the way a unit
whose type closure is larger than its own header declares its types -- resolves nowhere unless
the driver passes the target's include path.  Nothing here runs the compiler: the derivation is
a function of the descriptor, so what is pinned is that the flags **follow** the descriptor
(never a spelling of the driver's own) and that a search path which cannot exist is refused
rather than skipped.
"""

import dataclasses
import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
for extra in (str(ROOT), str(ROOT / "tools"), str(ROOT / "tools" / "oracle")):
    if extra not in sys.path:
        sys.path.insert(0, extra)

from config import targets  # noqa: E402
from toolchain import compile as cc  # noqa: E402


def test_the_flags_follow_the_descriptors_search_path_in_order():
    """The directories are the descriptor's, spelled in its order -- two are two flags."""
    target = dataclasses.replace(targets.get(), include_dirs=("include", "src"))
    assert cc.include_flags(target) == [f"-I{ROOT / 'include'}", f"-I{ROOT / 'src'}"]
    assert cc.include_flags(targets.get()) == [f"-I{ROOT / 'include'}"]


def test_an_include_directory_that_is_not_there_is_a_configuration_error():
    """A missing search path is reported, never skipped: a silent skip is a compile that
    fails later for a reason that names the source instead of the configuration."""
    target = dataclasses.replace(targets.get(), include_dirs=("include", "no_such_headers"))
    with pytest.raises(cc.Unusable) as exc:
        cc.include_flags(target)
    assert "no_such_headers" in str(exc.value)
