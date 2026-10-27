"""The permuter adapter: the gate's score for one candidate, and its contract.

Two halves, and only the first one needs the toolchain:

* the *contract* is "a candidate source in, a number out", ``0`` meaning the target
  function's words are retail's.  :class:`permute_adapter.WordScorer` is the permuter's
  scorer with the gate behind it, and the tests below drive it with a fake artifact --
  no compiler, no retail ELF -- to pin the contract itself: a candidate whose words
  are the expected ones scores zero, and is ranked first among its neighbours.
* the *measurement* compiles the committed unit and a one-word variation of it through
  the promotion path and requires ``0`` and a nonzero count.  That test skips when the
  retail ELF or the recorded compiler is not in this checkout, like the other compile
  tests, and it skips for the same reason the driver does: a candidate that cannot be
  placed is ``PENALTY_INF``, not a number.

The driver (:mod:`units.permute`) is not imported here: it imports decomp-permuter,
which this suite must not need.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from units import permute_adapter as pa  # noqa: E402

UNIT = "src/network/net_window/net_win_user.c"
FUNCTION = "NetWin_User"


def _words(text: str) -> bytes:
    """Four little-endian words from a readable pattern."""
    return b"".join(bytes([at, at + 1, at + 2, at + 3]) for at in range(0, len(text) * 4, 4))


class FakeCandidate:
    """The one thing ``WordScorer`` asks of a candidate: its expected words."""

    def __init__(self, words: bytes):
        self.expected = words


def _score(scorer, words: bytes) -> int:
    import tempfile

    with tempfile.NamedTemporaryFile(suffix=".words", delete=False) as handle:
        handle.write(words)
        path = handle.name
    try:
        return scorer.score(path)[0]
    finally:
        pathlib.Path(path).unlink()


def test_the_scorer_ranks_the_known_words_first(tmp_path):
    """A fake scorer, a known good candidate, and its neighbours: the known one wins."""
    expected = _words("abcd")
    scorer = pa.WordScorer(FakeCandidate(expected))

    assert _score(scorer, expected) == 0
    renamed = bytearray(expected)
    renamed[4] = 0xFF                     # one word of four differs
    assert _score(scorer, bytes(renamed)) == 1
    # The same bytes under another name are the same candidate: the score is a function
    # of the words, never of the file it arrived in.
    assert _score(scorer, expected) == 0
    assert _score(scorer, expected) < _score(scorer, bytes(renamed))


def test_an_artifact_that_is_not_a_candidate_is_unscoreable():
    """A failed compile has no artifact, and its words are never compared."""
    scorer = pa.WordScorer(FakeCandidate(_words("abcd")))
    assert scorer.score(None) == (pa.PENALTY_INF, "")
    assert scorer.PENALTY_INF == pa.PENALTY_INF


def test_the_body_splice_replaces_one_function():
    """A candidate carries a body, never the unit: the unit's other bodies are the file's."""
    base = (
        "struct S { int step[2]; };\n"
        "void other(struct S *s) { s->step[0] = 1; }\n"
        "int NetWin_User(struct S *s) {\n"
        "    return s->step[0];\n"
        "}\n"
    )
    start, end = pa.body_span(base, "NetWin_User")
    assert base[start:end] == "{\n    return s->step[0];\n}"
    # A prototype and a call are not definitions, and braces in literals are not bodies.
    tricky = 'int NetWin_User(struct S *s);\nvoid f(void) { char *p = "}"; }\n' + base
    start, end = pa.body_span(tricky, "NetWin_User")
    assert tricky[start:end] == "{\n    return s->step[0];\n}"


def _candidate():
    """The promoted unit's candidate, or a skip reason (retail ELF or toolchain absent)."""
    if not (ROOT / "orig" / "SLUS_211.74").is_file():
        pytest.skip("no retail ELF in this checkout: nothing to place the unit against")
    try:
        return pa.Candidate(UNIT, FUNCTION)
    except Exception as exc:                     # a checkout without the pinned toolchain
        pytest.skip(f"recorded compiler unavailable: {exc}")


def test_the_committed_source_scores_zero_and_a_variation_does_not(tmp_path):
    """The adapter's contract, measured through the promotion path it reuses."""
    candidate = _candidate()
    shipped = candidate.tu.source.read_bytes()
    assert candidate.score(shipped) == 0

    start, end = pa.body_span(shipped.decode("latin-1"), FUNCTION)
    body = bytearray(shipped[start:end])
    changed = body.replace(b"step[0]", b"step[1]", 1)
    assert changed != body, "the fixture must contain the word the test swaps"
    varied = shipped[:start] + changed + shipped[end:]
    assert candidate.score(varied) > 0
    assert candidate.score(shipped) < candidate.score(varied)
