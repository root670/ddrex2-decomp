#!/usr/bin/env python3
"""select_build.py -- which compiler build and flag set reproduce a unit's retail bytes.

Measured, never assumed.  For one translation unit this compiles the source once per
(compiler build, flag set) candidate and compares the three parts the promotion rule cares
about against the retail image: the unit's ``.text`` span, its ``.debug`` chunk and its
``.line`` chunks.  The first pair whose three parts all match is the pair to build with; the
table printed here is the evidence for the choice recorded in ``docs/milestones/`` and
pasted into ``configure.py``'s per-unit build table.

The compiler builds are the ones ``tools/toolchain/fetch.py`` has already installed (a
missing alternative is named and skipped rather than downloaded), and the flag sets are the
axes the plan names: ``-O1..-O4`` under ``-lang c``, with and without ``-g``, with
``-sdatathreshold 0`` as an extra axis.  ``-g`` is not optional for a *promoted* unit -- its
``.debug``/``.line`` bytes are half of the promotion rule -- but the sets without it are
measured too, because "the code alone matches" is worth knowing.

Usage::

    python3 tools/toolchain/select_build.py --tu sys_scf.c

Exit codes: 0 a pair was found (printed), 1 no candidate reproduces the unit, 2 the unit or
a manifest is unusable.
"""

from __future__ import annotations

import argparse
import pathlib
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT / "tools" / "oracle"),
               str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from toolchain import check_deps, compile as cc, fetch  # noqa: E402

#: The compiler builds to try.  3.0b38 leads because every row in ``tu_builds`` records it,
#: so ``--first`` returns the build the tree itself uses; the fetched order follows.  (The
#: fetcher's ``REQUIRED`` is 2.4, which nothing here promotes against.)
PREFERRED = "3.0b38-030307"
CANDIDATES = tuple(dict.fromkeys((PREFERRED, fetch.REQUIRED, *fetch.CANDIDATES)))

#: The flag axes, in the plan's order: the four optimization levels under ``-lang c`` and
#: ``-g``, then the same levels with ``-sdatathreshold 0`` (which implies ``-model
#: absolute``), then the two levels without ``-g``.
LANG = ("-lang", "c")
LEVELS = ("-O2", "-O1", "-O3", "-O4")


#: MWCC's whole-program optimizer.  Every promoted unit's row records it, and the plain levels
#: do not schedule the same way, so a sweep without it reports "no installed compiler
#: reproduces" for units a committed row already reproduces.
OPT_FULL = ("-opt", "full")


def flag_sets() -> list[tuple[str, ...]]:
    """The flag sets to measure, each a whole ``mwccps2`` command line's flags.

    The full-optimizer forms come first because they are the ones this tree's rows use.
    """
    sets = [("-c", *LANG, level, *OPT_FULL, "-g") for level in ("-O3", "-O2")]
    sets += [("-c", *LANG, level, *OPT_FULL, "-sdatathreshold", "0", "-g")
             for level in ("-O3", "-O2")]
    sets += [("-c", *LANG, level, "-g") for level in LEVELS]
    sets += [("-c", *LANG, level, "-sdatathreshold", "0", "-g")
             for level in ("-O2", "-O3")]
    sets += [("-c", *LANG, level) for level in ("-O2", "-O3")]
    return sets


def installed(candidates=CANDIDATES, root=fetch.TOOLCHAIN_ROOT) -> tuple[list[str], list[str]]:
    """``(installed, missing)`` compiler builds: nothing here touches the network."""
    here = [version for version in candidates if (root / f"mwcps2-{version}").is_dir()]
    return here, [version for version in candidates if version not in here]


def measure(tu: cc.Tu, version: str, flags, manifests, root=fetch.TOOLCHAIN_ROOT):
    """Compile ``tu`` with one candidate and compare its three parts with retail.

    The placement adopts retail's metadata, exactly as every promoted unit's ``cc`` edge
    does: ``.text`` byte equality is the promotion proof, and ``.debug``/``.line`` are
    reconstructed from retail's inventory.  Measuring before adoption made this sweep
    useless for the whole current tree -- a unit whose ``.line`` is adopted failed
    condition 1 for *every* candidate, including the pair its own row records, so it
    reported "no installed compiler reproduces" for units that are green.
    """
    compiler_dir = fetch.compiler(version, root=root)
    wibo = fetch.wibo(root=root)
    try:
        placed = cc.place(tu, manifests, compiler_dir, wibo, flags, adopt=True)
    except Exception as exc:  # a candidate that cannot even be placed is a no
        message = " ".join(str(exc).split())[:110]
        return {part: (False, message) for part in ("text", "debug", "line")}
    return cc.compare(tu, placed)


def choose(name, manifests=None, compilers=None, sets=None, report=print, first=False):
    """The first ``(version, flags)`` whose text, debug and line all match retail.

    Every candidate is measured -- the printed table is the evidence for the choice -- and
    ``first`` stops at the first match, which is all the build needs.
    """
    manifests = manifests or cc.Manifests()
    tu = manifests.tu_named(name)
    compilers = list(compilers) if compilers else installed()[0]
    sets = list(sets) if sets else flag_sets()
    if not compilers:
        raise cc.Unusable(
            "no compiler build is installed under toolchain/; run tools/toolchain/fetch.py")
    found = None
    for version in compilers:
        for flags in sets:
            outcome = measure(tu, version, flags, manifests)
            line = " ".join(f"{part} {'ok' if outcome[part][0] else 'no'}"
                            for part in ("text", "debug", "line"))
            report(f"{version:14} {' '.join(flags):38} {line}")
            if all(outcome[part][0] for part in ("text", "debug", "line")):
                if found is None:
                    found = (version, flags)
                if first:
                    return found[0], list(found[1])
    if found is None:
        return None, None
    return found[0], list(found[1])


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(prog="select_build.py", description=__doc__.splitlines()[0])
    parser.add_argument("--tu", required=True,
                        help="the translation unit to select for (repo-relative, e.g. "
                             "src/<dir>/<unit>.c)")
    parser.add_argument("--all", action="store_true",
                        help="measure every candidate, not just up to the first match")
    parser.add_argument("--first", action="store_true", default=False,
                        help="stop at the first match (the default measures everything)")
    args = parser.parse_args(argv)
    try:
        check_deps.require()
        manifests = cc.Manifests()
        tu = manifests.tu_named(args.tu)
    except (cc.Unusable, check_deps.MissingDependency) as exc:
        print(f"select_build.py: error: {exc}", file=sys.stderr)
        return 2
    here, missing = installed()
    if missing:
        print(f"select: not installed, skipped: {', '.join(missing)}")
    found, sets = choose(args.tu, manifests, here, None, first=args.first and not args.all)
    if found is None:
        print(f"select: no installed compiler reproduces {tu.file}; the source or the "
              f"flag axes still have a gap", file=sys.stderr)
        return 1
    print(f"select: {tu.file}: --compiler {found} {' '.join(sets)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
