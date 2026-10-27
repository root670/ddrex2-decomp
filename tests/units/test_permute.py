"""The permuter driver's refusals and its tool contract, none of which needs the tool.

``units.permute`` imports decomp-permuter lazily, so everything here runs in a checkout
that has never fetched it: the unit gate, the scratch naming, and the one line a missing
tool gets instead of a traceback.  The search itself is exercised in
``test_permute_adapter.py`` (contract) and by hand on a promoted unit.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import fetch  # noqa: E402
from units import permute  # noqa: E402


def test_a_unit_with_no_measured_pair_is_refused(capsys):
    """The permuter is for residues, not for code nobody has measured a pair for."""
    status = permute.main(["src/not/a/unit.c", "--seconds", "0"])
    assert status == 2
    message = capsys.readouterr().err
    assert "tu_builds" in message
    assert "promoted" in message


def test_the_scratch_directory_is_named_for_the_unit_and_function():
    assert permute.slug("src/network/net_window/net_win_user.c", "NetWin_User") == \
        "net_win_user-NetWin_User"


def test_a_missing_tool_names_the_command_that_installs_it(tmp_path, monkeypatch):
    """Absent, the tool is one actionable line -- never an ImportError from the tree."""
    monkeypatch.setattr(fetch, "TOOLCHAIN_ROOT", tmp_path)
    with pytest.raises(permute.MissingTool) as excinfo:
        permute._load_permuter()
    assert fetch.PERMUTER_REMEDY in str(excinfo.value)


def test_the_pin_is_the_one_the_installer_verifies():
    """The driver reads the tree the fetch pins; the two names cannot drift apart."""
    assert fetch.permuter_dir().name == fetch.PERMUTER_VERSION
    assert fetch.PERMUTER_PINNED["tree"][1] > 0
    assert fetch.PERMUTER_REMEDY == f"python3 tools/toolchain/fetch.py {fetch.PERMUTER_NAME}"
