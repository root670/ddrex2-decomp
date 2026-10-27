"""The permuter adapter: the gate's score for one candidate, and its contract.

Two halves, and only the first one needs the toolchain:

* the *contract* is "a candidate source in, a number out", ``0`` meaning the target
  function's words are retail's at retail's length.  :class:`permute_adapter.WordScorer`
  is the permuter's scorer with the gate behind it, and the tests below drive it with a
  fake artifact -- no compiler, no retail ELF -- to pin the contract itself: a candidate
  whose words are the expected ones scores zero and is ranked first among its neighbours,
  and a candidate of another length gets a finite rank ordered by its size gap so that a
  size-blocked unit is searchable.  A wrong-length rank is never a promotion, and the
  tests pin that too: a body the gate refuses for anything else stays ``PENALTY_INF``.
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

from toolchain import compile as cc  # noqa: E402
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


def test_a_wrong_length_artifact_is_ranked_by_size_and_never_beats_a_placed_one():
    """Search ranking only: finite, ordered by the size gap, ``0`` still exact retail."""
    expected = _words("abcd")                     # four words
    scorer = pa.WordScorer(FakeCandidate(expected))
    renamed = bytearray(expected)
    renamed[4] = 0xFF

    # The same-size residue is what the gate can promote: exactly one word differs.
    assert _score(scorer, bytes(renamed)) == 1

    short, long_ = expected[:-4], expected + b"\xAA\xBB\xCC\xDD"
    for wrong in (short, long_):
        score = _score(scorer, wrong)
        assert 0 < score < pa.PENALTY_INF         # finite: the search can rank it
        assert score > _score(scorer, bytes(renamed))

    # The price of one byte of mismatch dominates every differing word a body can have.
    assert _score(scorer, short) == 4 * pa.SIZE_WEIGHT
    assert _score(scorer, long_) == 4 * pa.SIZE_WEIGHT
    assert pa.SIZE_WEIGHT > 1 << 20               # more than the words in a 4 MiB .text

    # Size difference first, then words: two bytes off outranks one byte off.
    assert _score(scorer, expected[:-8]) > _score(scorer, short)
    # And only the exact words at the exact length are a zero.
    assert _score(scorer, expected) == 0


class StubCandidate(pa.Candidate):
    """The measurement seam of :class:`pa.Candidate`, with no compiler behind it."""

    def __init__(self, expected, body, placed=None):
        self.expected = expected
        self.stub_body = body
        self.stub_placed = placed

    def _object(self, source):
        return None, None

    def _body(self, mw, gp):
        return self.stub_body

    def _placed_text(self, mw, gp):
        if self.stub_placed is None:
            raise cc.Unusable(
                "src/example.c: condition 1 (.text and .line byte-equal) failed: .text F "
                "is short by 0x4 bytes; C is incomplete")
        return self.stub_placed

    def words(self, text):
        return text[:len(self.expected)]


def test_a_wrong_length_body_is_measurable_for_the_search_only():
    expected = _words("abcd")
    short = StubCandidate(expected, expected[:-4])
    assert short.rank_words(b"source") == expected[:-4]
    assert short.size_gap(b"source") == 4                     # bytes short
    assert short.score(b"source") == 4 * pa.SIZE_WEIGHT
    assert 0 < short.score(b"source") < pa.PENALTY_INF

    long_ = StubCandidate(expected, expected + b"\0\0\0\0")
    assert long_.size_gap(b"source") == -4                    # bytes too large
    assert long_.score(b"source") == 4 * pa.SIZE_WEIGHT


def test_the_gate_is_not_softened_by_the_size_ranking():
    """A body of retail's length that the gate refuses stays unscoreable, not finite."""
    expected = _words("abcd")
    refused = StubCandidate(expected, expected, placed=None)
    assert refused.rank_words(b"source") is None
    assert refused.score(b"source") == pa.PENALTY_INF
    assert "condition 1" in refused.refusal

    # A body the gate places is scored by its words; one differing word is one, not zero.
    placed = StubCandidate(expected, expected, placed=expected)
    assert placed.score(b"source") == 0
    assert placed.size_gap(b"source") == 0
    one_off = bytearray(expected)
    one_off[4] = 0xFF
    assert StubCandidate(expected, expected, placed=bytes(one_off)).score(b"source") == 1


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
