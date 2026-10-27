#!/usr/bin/env python3
"""Score one candidate source for a promoted unit, the way the gate scores it.

The permuter's contract is "a candidate source in, a number out": lower is better and
``0`` means the function *is* retail's.  This module is that contract for this tree, and
it deliberately answers with the gate's own evidence instead of a disassembly diff:

* the compiler build and the flags are the unit's recorded pair (``Target.build_pair``),
  never ``fetch.REQUIRED`` -- a pair measured for one unit says nothing about another;
* the compile is ``compile.py``'s (``probe.compile``, ``MWObject``, ``relocate`` and
  :func:`toolchain.compile.placed_text`), so relocations are applied and the bodies are
  laid at retail's addresses exactly as the ``cc`` edge does it;
* the expected words are read from the split splat generated for the function, and
  cross-checked against the pinned retail image, so a stale split cannot score silently;
* the score is the number of 32-bit words that differ, over the target function's span; a
  target body of another length is ranked by its size gap first (search only, below).

A candidate the gate cannot use -- mwcc rejects it, a datum it defines stops being
retail's, or a body *other than the target* is not retail's length -- is
:data:`PENALTY_INF`, the permuter's own word for "unscoreable".  The *search* needs one
exception: when the target body itself is not retail's length it still gets a finite rank
(:func:`rank`: bytes of size mismatch first, differing words second), so a size-blocked
unit can be searched.  The gate is untouched -- ``compile.py`` still refuses such a unit,
and ``0`` still means retail's words *and* retail's length.

Usage::

    python3 tools/units/permute_adapter.py src/network/net_window/net_win_user.c \\
        --function CwsWinCreate [--candidate file.c] [--json]

Prints one integer on stdout (the score) and the measurement on stderr.
"""

from __future__ import annotations

import argparse
import contextlib
import io
import json
import pathlib
import re
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from config import targets  # noqa: E402
from toolchain import compile as cc, fetch, probe  # noqa: E402

#: The permuter's word for a candidate that cannot be scored (its own ``PENALTY_INF``):
#: a compile the compiler refused, or a placement the build would refuse.
PENALTY_INF = 10 ** 9

#: What one byte of body-size mismatch costs in the search's rank.  The rank is
#: ``abs(len - retail) * SIZE_WEIGHT + differing words``, so any candidate of retail's
#: length beats any candidate that is not.  ``SIZE_WEIGHT`` is one more than the largest
#: word count a body can have: ``.text`` is 4 MiB, i.e. at most ``2**20`` words, so a
#: same-size candidate's worst rank (all words differ) stays below ``2**21`` and
#: therefore below one byte of mismatch.  The gate never sees this number: it refuses a
#: body of the wrong length (:func:`toolchain.compile.placed_text`), and only
#: :func:`rank` -- the *search* -- tolerates one.
SIZE_WEIGHT = 1 << 21

#: One per-instruction comment in a splat split: ``/* <file offset> <address> <word> */``,
#: the word printed in the order the bytes have in the image (little-endian).
SPLIT_WORD = re.compile(r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s+\*/")


def body_span(text: str, name: str) -> tuple[int, int]:
    """The ``{ ... }`` span of ``name``'s definition in ``text``.

    Scans the C the way a reader does -- strings, character literals and comments are
    skipped -- so a brace inside a literal is not mistaken for the body.  The *body* is
    what a candidate replaces: its signature and the unit's other functions stay the
    committed source's, which is what lets a permuter output (a function and the
    declarations it needs) be compiled as this unit.
    """
    pattern = re.compile(r"\b" + re.escape(name) + r"\s*\(")
    at = 0
    while True:
        match = pattern.search(text, at)
        if match is None:
            raise ValueError(f"no definition of {name} in the candidate source")
        at = match.end()
        depth, index = 1, at
        while index < len(text) and depth:
            char = text[index]
            if char == "(":
                depth += 1
            elif char == ")":
                depth -= 1
            index += 1
        while index < len(text) and text[index] in " \t\r\n":
            index += 1
        if index >= len(text) or text[index] != "{":
            continue   # a prototype or a call: keep looking
        start, depth = index, 0
        while index < len(text):
            char = text[index]
            if char in "\"'":
                quote = char
                index += 1
                while index < len(text) and text[index] != quote:
                    index += 2 if text[index] == "\\" else 1
            elif text.startswith("//", index):
                index = text.find("\n", index)
                if index < 0:
                    break
            elif text.startswith("/*", index):
                index = text.find("*/", index + 2)
                if index < 0:
                    break
                index += 1
            elif char == "{":
                depth += 1
            elif char == "}":
                depth -= 1
                if depth == 0:
                    return start, index + 1
            index += 1
        raise ValueError(f"unbalanced braces after {name}")


class NotPromoted(Exception):
    """The unit has no measured pair in the target's ``tu_builds``."""


class NoSuchFunction(Exception):
    """The unit declares no function with that name."""


def split_words(tu: cc.Tu, function: cc.Function, target) -> bytes:
    """The instruction words splat's split carries for ``function``.

    The split is what the build links when the unit is not promoted, and it is generated
    from the same retail image G1 pins, so its words are retail's instructions byte for
    byte.  The address on every row is checked against the record: a split whose first
    word is not the function's address is a stale generated tree, and the remedy is a
    configure, not a guess.
    """
    geometry = target.geometry_required()
    directory = pathlib.Path(target.config_dir).parent.parent / "asm" / "nonmatchings"
    path = directory / geometry.code_segment / f"{function.name}.s"
    if not path.is_file():
        raise FileNotFoundError(
            f"{path} is missing: the split for {function.name} has to be generated before "
            f"a candidate can be scored against it (./ddr build)")
    words = bytearray()
    for match in SPLIT_WORD.finditer(path.read_text()):
        address, word = int(match.group(1), 16), match.group(2)
        if not words and address != function.address:
            raise ValueError(
                f"{path}: the split starts at 0x{address:08X}, retail starts "
                f"{function.name} at 0x{function.address:08X}: regenerate the tree "
                f"(./ddr build)")
        words += bytes.fromhex(word)
    if len(words) < function.size:
        raise ValueError(
            f"{path}: {len(words):#x} bytes of instructions, but {function.name} is "
            f"{function.size:#x} bytes in retail; regenerate the tree (./ddr build)")
    # Splat's split runs to the next split, which can carry padding past the function's
    # DWARF `high_pc` (the same trailing run `_split_extent` measures); the function's
    # words are its first `size` bytes.
    return bytes(words[:function.size])


def rank(words: bytes, expected: bytes) -> int:
    """The search's rank: bytes of size mismatch first, differing words second.

    ``0`` still means exactly ``expected`` -- same length, same words.  A candidate of
    another length is finite and strictly worse than any of retail's length (see
    :data:`SIZE_WEIGHT`), so the merest size improvement is a step the search can see.
    This is a *search* ordering, never a promotion: the gate refuses a body of the wrong
    length (:func:`toolchain.compile.placed_text`).
    """
    gap = abs(len(words) - len(expected)) * SIZE_WEIGHT
    span = min(len(words), len(expected))
    diffs = sum(1 for at in range(0, span - 3, 4)
                if words[at:at + 4] != expected[at:at + 4])
    return gap + diffs


class Candidate:
    """One unit, one function, and everything a candidate source is judged with.

    Built once per search: the manifests, the recorded pair and the retail words are
    read here, and every :meth:`score` call is one compile plus one comparison.
    """

    def __init__(self, unit, function=None, target=None, scratch=None):
        self.target = targets.get(target)
        source = _unit_file(unit, self.target)
        pair = self.target.build_pair(source)
        if pair is None:
            raise NotPromoted(
                f"{source} has no measured pair in {self.target.name}'s tu_builds: there "
                f"is nothing to permute until it is promoted (the permuter is for "
                f"register/schedule residues, not for unfinished code)")
        self.unit = source
        self.compiler_version, flags = pair
        self.flags = flags.split()
        self.manifests = cc.Manifests(self.target)
        self.tu = self.manifests.tu_named(source)
        self.function = self._pick(function)
        self.expected = split_words(self.tu, self.function, self.target)
        self._check_split_against_retail()
        self.compiler_dir = fetch.compiler(self.compiler_version)
        self.wibo = fetch.wibo()
        self.scratch = pathlib.Path(scratch or tempfile.mkdtemp(prefix="ddr-permute-"))
        self.scratch.mkdir(parents=True, exist_ok=True)
        self.staged = cc.staged_path(self.tu)
        self.object = self.scratch / "candidate.mw.o"

    # -- setup ------------------------------------------------------------

    def _pick(self, name):
        if name is None:
            if len(self.tu.functions) != 1:
                names = ", ".join(f.name for f in self.tu.functions)
                raise NoSuchFunction(
                    f"{self.unit} declares {len(self.tu.functions)} functions "
                    f"({names}); name the one to permute with --function")
            return self.tu.functions[0]
        function = self.tu.function_named(name)
        if function is None:
            names = ", ".join(f.name for f in self.tu.functions)
            raise NoSuchFunction(
                f"{self.unit} declares no function {name!r}; it has {names}")
        return function

    def _check_split_against_retail(self):
        """Refuse a split that disagrees with the pinned image: the score would be a lie."""
        offset = self.function.address - self.tu.address
        retail = cc.retail_bytes(self.tu, self.target.elf)["text"]
        retail = retail[offset:offset + len(self.expected)]
        if retail != self.expected:
            first = next((i for i, (a, b) in enumerate(zip(retail, self.expected))
                          if a != b), min(len(retail), len(self.expected)))
            raise ValueError(
                f"{self.unit}: the split's words for {self.function.name} disagree with "
                f"{self.target.elf.name} at +0x{first:X}: the generated tree is stale "
                f"(./ddr build)")

    # -- the measurement --------------------------------------------------

    def commit(self, source: bytes) -> bytes:
        """``source``'s spelling of the target function, on the committed unit.

        A permutation changes one function's body; every other body, the declarations and
        the data are the committed source's, so the candidate is compiled as *this unit*
        (:meth:`placed`), and a body is the only thing the score can attribute to it.
        """
        text = source.decode("latin-1")
        try:
            start, end = body_span(text, self.function.name)
        except ValueError:
            return source      # not a spelling we can splice: score it as it is
        self.manifests.prefer_source(self.tu.file)
        base = self.tu.source.read_text(encoding="latin-1")
        base_start, base_end = body_span(base, self.function.name)
        return (base[:base_start] + text[start:end] + base[base_end:]).encode("latin-1")

    def _object(self, source: bytes):
        """Compile ``source`` as this unit; return the object and retail's ``$gp``."""
        self.staged.parent.mkdir(parents=True, exist_ok=True)
        self.staged.write_bytes(self.commit(source))
        recorded = cc.recorded_name(self.staged)
        if len(recorded) != len(self.tu.name):
            raise cc.Unusable(f"staging {self.staged} spells {len(recorded)} bytes, "
                              f"retail {len(self.tu.name)}")
        probe.compile(self.staged, self.object, self.compiler_dir, self.wibo,
                      [*self.flags, *cc.include_flags(self.target)])
        mw = cc.MWObject(self.object, self.manifests)
        gp = cc.gp_value(self.target.elf)
        self.manifests.prefer_source(self.tu.file)
        return mw, gp

    def placed(self, source: bytes) -> bytes:
        """The unit's ``.text`` with ``source`` compiled through the recorded pair."""
        mw, gp = self._object(source)
        return self._placed_text(mw, gp)

    def _placed_text(self, mw, gp) -> bytes:
        """The gate's placement: data verified, every body retail's length."""
        with contextlib.redirect_stdout(io.StringIO()), \
                contextlib.redirect_stderr(io.StringIO()):
            cc.verify_data(mw, self.manifests, self.tu.file, self.target)
        groups = mw.groups(self.tu)
        text, _labels, _sizes, _retail = cc.placed_text(self.tu, mw, self.manifests,
                                                        gp, groups)
        return text

    def _body(self, mw, gp) -> bytes:
        """The target body's relocated instructions, whatever its length.

        The gate refuses a body that is not the function's retail size; this is the same
        compile and the same relocation *without* that refusal, so a size-blocked unit
        can be ranked.  It is never a promotion: :func:`rank` scores it.
        """
        groups = mw.groups(self.tu)
        section = groups[self.function.name][0]
        return cc.relocate(mw.data(section), mw.relocs.get(section, ()),
                           lambda symbol: mw.resolve(self.tu, symbol),
                           f"{self.function.name}.text", gp)

    def words(self, text: bytes) -> bytes:
        """The target function's words as they came out of the compile."""
        offset = self.function.address - self.tu.address
        return text[offset:offset + len(self.expected)]

    def rank_words(self, source: bytes) -> bytes | None:
        """The target body's words for the search, or ``None`` when it is unscoreable.

        One compile, then the gate's order: the body is relocated, and a body of another
        length is the *one* refusal the search tolerates (:func:`rank` orders it).  A
        body of retail's length is put through the gate proper -- data checked, every
        body placed -- and any refusal there still means ``None``.  ``compile.py`` gets
        no softer question: :func:`toolchain.compile.placed_text` still refuses a unit
        whose body length is wrong, so this can rank such a unit but never promote it.
        """
        errors = (cc.Unusable, probe.ProbeError, FileNotFoundError, ValueError, KeyError)
        self.refusal = None
        try:
            mw, gp = self._object(source)
            body = self._body(mw, gp)
        except errors as exc:
            self.refusal = str(exc)
            return None
        if len(body) != len(self.expected):
            return body
        try:
            return self.words(self._placed_text(mw, gp))
        except errors as exc:
            self.refusal = str(exc)
            return None

    def size_gap(self, source: bytes) -> int | None:
        """Bytes ``source``'s target body is short of retail's (negative: too large)."""
        words = self.rank_words(source)
        return None if words is None else len(self.expected) - len(words)

    def score(self, source: bytes) -> int:
        """The search's rank; ``0`` means retail's words at retail's length."""
        words = self.rank_words(source)
        return PENALTY_INF if words is None else rank(words, self.expected)

    def score_file(self, path) -> int:
        return self.score(pathlib.Path(path).read_bytes())

    # -- the permuter's two objects ---------------------------------------

    def scorer(self):
        """The permuter's ``Scorer`` contract: an artifact path in, a score out."""
        return WordScorer(self)


class WordScorer:
    """The permuter's scorer, with the gate behind it.

    The permuter asks a scorer for ``(score, dump)`` over an artifact its compiler
    produced; here the artifact holds the candidate's words for the target function, so
    the comparison is the split's words against the object's -- nothing is disassembled
    and no instruction heuristic is involved.  An artifact of another length is ranked,
    not rejected: :func:`rank` makes the size gap come first.  ``hash`` is the words
    themselves, which is what the permuter deduplicates candidates by.
    """

    PENALTY_INF = PENALTY_INF

    def __init__(self, candidate: Candidate):
        self.candidate = candidate

    def score(self, artifact) -> tuple[int, str]:
        if not artifact:
            return PENALTY_INF, ""
        try:
            words = pathlib.Path(artifact).read_bytes()
        except OSError:
            return PENALTY_INF, ""
        expected = self.candidate.expected
        return rank(words, expected), words.hex()


def compiler_for(candidate: Candidate):
    """The permuter's ``Compiler`` contract: candidate source text in, artifact out.

    The artifact is not a relocatable object: it is the target function's instruction
    words, written by the compile this module already owns.  ``None`` is the permuter's
    "cannot compile" -- a rejected source, or a placement the build would refuse for any
    reason *but* the target body's length: a wrong-length body is measurable
    (:meth:`Candidate.rank_words`) so the search can rank it.
    """
    return CandidateCompiler(candidate)


class CandidateCompiler:
    """Compile one candidate, once, and hand the permuter its words."""

    def __init__(self, candidate: Candidate):
        self.candidate = candidate
        self._serial = 0

    def compile(self, source, *, show_errors=False):
        words = self.candidate.rank_words(source.encode())
        if words is None:
            if show_errors:
                print(f"permute: candidate refused: "
                      f"{self.candidate.refusal or 'unplaceable'}", file=sys.stderr)
            return None
        self._serial += 1
        artifact = self.candidate.scratch / f"candidate-{self._serial}.words"
        artifact.write_bytes(words)
        return str(artifact)


def _unit_file(unit: str, target) -> str:
    """``sys_scf``, ``sys_scf.c`` and ``src/sys/sys_scf.c`` name the same unit."""
    unit = str(unit).replace("\\", "/")
    for entry in target.build_table():
        if entry == unit or entry.endswith("/" + unit) or pathlib.Path(entry).stem == unit:
            return entry
    return unit


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="permute_adapter.py",
        description="Score one candidate source for a promoted unit (0 == retail's words).")
    parser.add_argument("unit", help="the unit: src/... .c, or its stem")
    parser.add_argument("--function", default=None,
                        help="the function to score (default: the unit's only function)")
    parser.add_argument("--candidate", default=None,
                        help="the source to score (default: the unit's own source)")
    parser.add_argument("--target", default=None,
                        help=f"the target whose pair and image are used (default: "
                             f"{targets.DEFAULT})")
    parser.add_argument("--json", action="store_true", help="also report the measurement")
    return parser


def main(argv=None) -> int:
    args = _parser().parse_args(argv)
    try:
        candidate = Candidate(args.unit, args.function, args.target)
    except (NotPromoted, NoSuchFunction) as exc:
        print(f"permute_adapter.py: {exc}", file=sys.stderr)
        return 2
    except (FileNotFoundError, ValueError) as exc:
        print(f"permute_adapter.py: {exc}", file=sys.stderr)
        return 1
    path = pathlib.Path(args.candidate) if args.candidate else candidate.tu.source
    score = candidate.score_file(path)
    if args.json:
        print(json.dumps({
            "unit": candidate.unit,
            "function": candidate.function.name,
            "candidate": str(path),
            "compiler": candidate.compiler_version,
            "flags": " ".join(candidate.flags),
            "words": len(candidate.expected) // 4,
            "score": score,
        }))
    else:
        print(score)
    return 0


if __name__ == "__main__":
    sys.exit(main())
