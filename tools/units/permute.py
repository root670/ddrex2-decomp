#!/usr/bin/env python3
"""permute.py -- search a promoted unit's C for the words retail has.

The residue this exists for is a *register or schedule* one: the unit is promoted, its
functions are retail's length, and a few words differ because the compiler coloured a
web differently or moved an instruction.  A body of the wrong length is still
*searchable* -- the adapter ranks it by size difference first and differing words second
-- but it is never a match: the gate refuses such a unit, and only ``0`` is success.
A run whose best candidate is the wrong length says so (``N bytes short``/``long``).

The search is decomp-permuter's (``simonlindholm/decomp-permuter``, MIT), fetched and
pinned by :mod:`toolchain.fetch`; the *scoring* is this tree's gate
(:mod:`units.permute_adapter`): the unit's recorded compiler/flags compile each
candidate, and the candidate's words for the target function are compared with those of
the split.  The permuter's own objdump heuristics are not used, so ``0`` means what
``./ddr verify --tu`` means.

A run never touches ``src/``: the base source is copied into
``drafts/permute/<unit>-<function>/`` and the best candidate is written there as
``best-<score>.c``.  That file is a *diff to read* (the permuter pretty-prints through
its C parser), not a file to commit; the unit's ``.line`` is adopted, so the statement
lines of a candidate are not retail's.

Usage::

    python3 tools/units/permute.py src/sys/sys_scf.c
    python3 tools/units/permute.py net_win_user --function NetWin_User --seconds 300
    python3 tools/units/permute.py src/... --seed 1 --function F --profile

Exit status: 0 when a candidate with score 0 was found, 1 when the search ran and did
not converge, 2 when the unit cannot be permuted (no ``tu_builds`` row, no function).
"""

from __future__ import annotations

import argparse
import pathlib
import shutil
import subprocess
import sys
import time

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from config import targets  # noqa: E402
from toolchain import compile as cc, fetch  # noqa: E402
from units import permute_adapter as adapter  # noqa: E402

#: Where the scratch copies live: inside the repository (so a best candidate is next to
#: the unit it belongs to and `git status` shows it until it is committed or cleaned),
#: gitignored, and never `src/`.
SCRATCH_ROOT = REPO_ROOT / "drafts" / "permute"

#: decomp-permuter's own default keep-probability: continue randomising the previous
#: candidate this often instead of starting again from the base source.
KEEP_PROB = 0.6

#: The permuter's compiler-type section of ``default_weights.toml`` this tree's compiler
#: is closest to (Metrowerks mwccps2 is the ``mwcc`` weighting).
COMPILER_TYPE = "mwcc"


class MissingTool(Exception):
    """The permuter is not installed, or one of its Python dependencies is missing."""


#: The host preprocessors tried in order.  pycparser does not preprocess, and a promoted
#: unit starts with its generated header, so the base the permuter parses is the
#: preprocessed spelling.  ``-P`` is what keeps line markers out, which the parser refuses.
PREPROCESSORS = ("clang", "cpp", "gcc")


def preprocess(source: pathlib.Path, target) -> str:
    """The unit with its ``#include``s resolved, as the permuter's parser needs it.

    The words are unaffected: :func:`--score-only` measures the *committed* source and
    a preprocessed copy with the same score, because ``compile.py`` resolves the same
    headers with the same ``-I`` flags.  What preprocessing changes is only what the
    permuter's C parser sees.
    """
    command = next((name for name in PREPROCESSORS if shutil.which(name)), None)
    if command is None:
        raise MissingTool(
            f"no host preprocessor ({', '.join(PREPROCESSORS)}) on PATH: the permuter "
            f"parses preprocessed C, and a promoted unit starts with a #include")
    result = subprocess.run([command, "-E", "-P", *cc.include_flags(target), str(source)],
                            capture_output=True, text=True)
    if result.returncode != 0:
        raise MissingTool(f"{command} could not preprocess {source}: "
                          f"{result.stderr.strip()}")
    return result.stdout


def _load_permuter():
    """Import the pinned permuter, or say exactly what to run instead."""
    try:
        root = fetch.installed_permuter()
    except fetch.MissingTool as exc:
        raise MissingTool(str(exc)) from exc
    path = str(root)
    if path not in sys.path:
        sys.path.insert(0, path)
    try:
        from src.helpers import get_default_randomization_weights
        from src.permuter import EvalError, Permuter
    except ModuleNotFoundError as exc:
        raise MissingTool(
            f"{root} needs the `{exc.name}` Python package (decomp-permuter's one "
            f"dependency that is not vendored); install it with "
            f"`python3 -m pip install {exc.name}`") from exc
    return Permuter, EvalError, get_default_randomization_weights


def slug(unit: str, function: str) -> str:
    """The scratch directory name: the unit's stem and the function, both readable."""
    return f"{pathlib.Path(unit).stem}-{function}"


def score_source(source: pathlib.Path, *, function=None, target=None) -> int:
    """The adapter's contract, as a function: a candidate source in, a number out."""
    candidate = adapter.Candidate(str(source), function, target)
    return candidate.score_file(source)


def size_warning(candidate: adapter.Candidate, source: bytes) -> str | None:
    """The line a wrong-length best candidate earns, or ``None`` when it is retail's size.

    A finite score from a body of the wrong length is not progress towards a promotion:
    the gate refuses that body, so the size is the next thing to fix, before any word
    residue the search also reported.
    """
    gap = candidate.size_gap(source)
    if not gap:
        return None
    return (f"best candidate is {abs(gap)} bytes "
            f"{'short' if gap > 0 else 'long'}; fix the size before expecting 0")


def search(candidate: adapter.Candidate, *, seconds: float, seed: int | None,
           scratch: pathlib.Path, keep_prob: float = KEEP_PROB,
           log=print) -> tuple[int, pathlib.Path | None]:
    """Run the permuter's search over ``candidate`` until the deadline or a zero.

    The permuter generates candidates (its randomizer, its keep-probability, its
    source-hash cache); every candidate it generates is compiled and scored by the
    adapter, so the number it reports is the gate's.  Returns the best score and the
    file it was written to (``None`` when nothing beat the base).
    """
    Permuter, EvalError, weights_for = _load_permuter()
    base_path = scratch / "base.c"
    if not base_path.is_file():
        base_path.write_text(preprocess(candidate.tu.source, candidate.target),
                             encoding="latin-1")
    base_source = base_path.read_text(encoding="latin-1")
    weights = weights_for(COMPILER_TYPE)

    permuter = Permuter(
        str(scratch),
        candidate.function.name,
        adapter.CandidateCompiler(candidate),
        adapter.WordScorer(candidate),
        str(scratch / "base.c"),
        base_source,
        randomization_weights=weights,
        force_seed=None,
        force_rng_seed=seed,
        keep_prob=keep_prob,
        need_profiler=False,
        need_all_sources=False,
        show_errors=False,
        best_only=False,
        better_only=False,
        score_threshold=None,
        debug_mode=False,
        speed=100,
    )
    log(f"base score = {permuter.base_score} "
        f"({len(candidate.expected) // 4} words in {candidate.function.name})")

    best_score = permuter.base_score
    best_path = None
    if best_score == 0:
        return 0, None

    deadline = time.monotonic() + seconds
    seeds = permuter.seed_iterator()
    tried = 0
    while time.monotonic() < deadline:
        try:
            seed_value = next(seeds)
        except StopIteration:
            break
        result = permuter.try_eval_candidate(seed_value)
        if isinstance(result, EvalError):
            continue
        tried += 1
        if result.source is not None and result.score < best_score:
            best_score = result.score
            best_path = scratch / f"best-{best_score}.c"
            best_path.write_text(result.source)
            log(f"score {best_score} after {tried} candidate(s): "
                f"{best_path.relative_to(REPO_ROOT)}")
        permuter.record_result(result)
        if best_score == 0:
            break
    log(f"evaluated {tried} candidate(s) in {seconds:.0f}s")
    # One extra measurement, only when the run did not converge: a finite score is not a
    # promotion if the best candidate's body is not retail's size, and that has to be
    # said out loud or the number reads as a word residue.
    warning = size_warning(candidate, (best_path or base_path).read_bytes())
    if warning:
        log(warning)
    return best_score, best_path


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="permute.py",
        description="Search a promoted unit's C for retail's words (decomp-permuter).")
    parser.add_argument("unit", help="the unit: src/... .c, or its stem")
    parser.add_argument("--function", default=None,
                        help="the function to permute (default: the unit's only function)")
    parser.add_argument("--seconds", type=float, default=60.0,
                        help="how long to search (default: 60)")
    parser.add_argument("--seed", type=int, default=None,
                        help="the randomizer's seed (default: fresh randomness)")
    parser.add_argument("--target", default=None,
                        help=f"the target to read (default: {targets.DEFAULT})")
    parser.add_argument("--scratch", default=None,
                        help=f"the scratch directory (default: "
                             f"{SCRATCH_ROOT.relative_to(REPO_ROOT)}/<unit>-<function>)")
    parser.add_argument("--keep-prob", type=float, default=KEEP_PROB,
                        help=f"probability of continuing from the previous candidate "
                             f"(default: {KEEP_PROB})")
    parser.add_argument("--score-only", action="store_true",
                        help="score the unit's committed source and exit")
    return parser


def main(argv=None) -> int:
    args = _parser().parse_args(argv)
    try:
        candidate = adapter.Candidate(args.unit, args.function, args.target)
    except adapter.NotPromoted as exc:
        print(f"permute.py: {exc}", file=sys.stderr)
        return 2
    except adapter.NoSuchFunction as exc:
        print(f"permute.py: {exc}", file=sys.stderr)
        return 2
    except (FileNotFoundError, ValueError) as exc:
        print(f"permute.py: {exc}", file=sys.stderr)
        return 1

    print(f"unit: {candidate.unit} [{candidate.target.name}]")
    print(f"function: {candidate.function.name} "
          f"({len(candidate.expected) // 4} words, {candidate.function.size:#x} bytes)")
    print(f"pair: {candidate.compiler_version} {' '.join(candidate.flags)}")

    if args.score_only:
        score = candidate.score_file(candidate.tu.source)
        print(score)
        if score:
            warning = size_warning(candidate, candidate.tu.source.read_bytes())
            if warning:
                print(warning, file=sys.stderr)
        return 0

    scratch = pathlib.Path(args.scratch) if args.scratch else \
        SCRATCH_ROOT / slug(candidate.unit, candidate.function.name)
    scratch.mkdir(parents=True, exist_ok=True)
    base = scratch / "base.c"
    if not base.is_file():
        base.write_text(preprocess(candidate.tu.source, candidate.target),
                        encoding="latin-1")
    print(f"scratch: {scratch}")

    try:
        best, path = search(candidate, seconds=args.seconds, seed=args.seed,
                            scratch=scratch, keep_prob=args.keep_prob,
                            log=lambda line: print(line, flush=True))
    except MissingTool as exc:
        print(f"permute.py: {exc}", file=sys.stderr)
        return 1

    if best == 0:
        print(f"score 0: {candidate.function.name} is placed"
              + (f" ({path})" if path else " (the committed source already matches)"))
        return 0
    if path is not None:
        print(f"best: {path} (score {best})"
              f"\napply it by hand: the permuter's output is pretty-printed, and its "
              f"lines are not retail's")
    else:
        print(f"best: the base source ({scratch / 'base.c'}, score {best}); "
              f"no candidate improved on it")
    return 1


if __name__ == "__main__":
    sys.exit(main())
