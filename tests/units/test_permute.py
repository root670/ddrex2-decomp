"""The permuter driver's refusals, its tool contract, and its success condition.

``units.permute`` imports decomp-permuter lazily, so everything here runs in a checkout
that has never fetched it: the unit gate, the scratch naming, the one line a missing
tool gets instead of a traceback, and the rule that only a score of ``0`` is success --
a fake permuter returns a finite size-ranked score and the driver must not call it a
match.  The scoring contract itself is exercised in ``test_permute_adapter.py``.
"""

import pathlib
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import fetch  # noqa: E402
from units import permute  # noqa: E402
from units import permute_adapter as pa  # noqa: E402


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


class StubUnit:
    """The driver's view of a candidate: a name, a base source, and a size gap."""

    def __init__(self, gap=0):
        self.expected = b"\x00" * 0x38C
        self.tu = types.SimpleNamespace(source=pathlib.Path("src/example.c"))
        self.function = types.SimpleNamespace(name="F")
        self.target = None
        self.gap = gap

    def size_gap(self, source):
        return self.gap


class FakePermuter:
    """The one thing ``search`` uses from decomp-permuter: a base score and seeds."""

    score = 0

    def __init__(self, *args, **kwargs):
        self.base_score = self.score

    def seed_iterator(self):
        return iter(())

    def try_eval_candidate(self, seed):
        raise AssertionError("no seed was offered")

    def record_result(self, result):
        raise AssertionError("no candidate was evaluated")


def _fake_permuter(monkeypatch, score):
    class Scored(FakePermuter):
        pass

    Scored.score = score
    monkeypatch.setattr(permute, "_load_permuter",
                        lambda: (Scored, RuntimeError, lambda name: {}))
    monkeypatch.setattr(permute, "preprocess", lambda source, target: "void F(void) {}\n")


def test_a_finite_size_ranked_score_is_reported_and_is_not_success(tmp_path, monkeypatch):
    """The search may rank a wrong-length body, but only ``0`` is a match."""
    lines = []
    _fake_permuter(monkeypatch, 4 * pa.SIZE_WEIGHT)

    score, path = permute.search(StubUnit(gap=0x18), seconds=0, seed=1,
                                 scratch=tmp_path, log=lines.append)

    assert score == 4 * pa.SIZE_WEIGHT
    assert score != 0 and score < pa.PENALTY_INF
    assert path is None
    assert "best candidate is 24 bytes short; fix the size before expecting 0" in lines


def test_a_zero_base_is_success_and_no_search_happens(tmp_path, monkeypatch):
    _fake_permuter(monkeypatch, 0)

    assert permute.search(StubUnit(gap=0x18), seconds=5, seed=None, scratch=tmp_path,
                          log=lambda line: None) == (0, None)


def test_a_wrong_length_best_candidate_is_named_as_one():
    short = permute.size_warning(StubUnit(gap=4), b"")
    assert short == "best candidate is 4 bytes short; fix the size before expecting 0"
    long_ = permute.size_warning(StubUnit(gap=-8), b"")
    assert long_ == "best candidate is 8 bytes long; fix the size before expecting 0"
    # Retail's size: the score is a word residue, and nothing about size needs saying.
    assert permute.size_warning(StubUnit(gap=0), b"") is None
    # Unmeasurable: no claim either way.
    assert permute.size_warning(StubUnit(gap=None), b"") is None
