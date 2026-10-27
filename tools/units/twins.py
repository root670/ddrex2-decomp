#!/usr/bin/env python3
r"""twins.py -- identical-body splits: one source shape serves every member.

Ask this **before writing a body** (``docs/unit-work.md`` rule 18).  Two splits with the same
instruction words need the same source, so a body whose twin already sits in a *promoted*
unit is a copy, not a reconstruction: read that source's shape, verify it against the split,
and do not retype it.

The signature is every four-byte word a split prints, in order -- the word column of each
``/* offset address word */`` comment (a trailing data block's words included)::

    re.findall(r"/\\* [0-9A-F]+ [0-9A-F]+ ([0-9A-F]{8}) \\*/", text)

Two splits with equal tuples are twins.  The group is *whole-split* identity only: a body
that merely looks similar is not a twin, and a twin in a unit measured against a different
compiler pair still needs its own measurement -- equal words say the shape is the same, not
that a recorded build reproduces it.

A twin counts as **promoted** when its function belongs to a translation unit whose ``src/``
source is committed and whose ``tu_builds`` row exists.  That is the cutover rule
:func:`units.screen.is_promoted` applies, and it is the whole unit's ``.text`` being retail's
that makes the twin's body already written down.

Usage::

    python3 tools/units/twins.py --tu src/CS/train/tra_menu.c   # this unit's bodies
    python3 tools/units/twins.py --all                          # every group in the tree
    python3 tools/units/twins.py --all --limit 0                 # ... all of them
    python3 tools/units/twins.py --tu shop_list.c --target ddrex2p

Input is the build's own generated split tree (``asm/nonmatchings/main/*.s``) plus the
target's manifests; the retail ELF, a compiler and the build graph are never touched.  A tree
without the splits says so and names the command that generates them (``./ddr build``).

Exit codes: 0 a report was produced, 2 the unit does not resolve, its functions are outside
this split tree, or the splits are absent.
"""

from __future__ import annotations

import argparse
import collections
import dataclasses
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from units import screen  # noqa: E402
from toolchain import compile as cc  # noqa: E402

#: The split tree the build generates: one ``<function>.s`` per body.
SPLITS = pathlib.PurePosixPath("asm/nonmatchings/main")
#: The word column of a split line: file offset, virtual address, four bytes.
_WORD = re.compile(r"/\* [0-9A-F]+ [0-9A-F]+ ([0-9A-F]{8}) \*/")
#: Rows the default report prints, so a unit with many functions still fits ~40 lines.
LIMIT = 34
#: What generates a missing split tree; every "absent" message names it.
BUILD = "./ddr build"


class Missing(RuntimeError):
    """An input the report needs is absent; the message names how to make it."""


@dataclasses.dataclass(frozen=True)
class Body:
    """One function's split: its word count and the other members of its group.

    ``words`` is ``None`` when the unit names the function but the split tree has no file for
    it, which is a ``./ddr build`` shortfall, not an empty body.  ``twins`` is sorted, so the
    copy source and every rendered line are deterministic.
    """

    name: str
    words: int | None
    twins: tuple


# ---------------------------------------------------------------------------
# measurement
# ---------------------------------------------------------------------------


def split_path(name: str, splits=SPLITS) -> str:
    """The repo-relative split a function's body is read from, in the unit's own tree."""
    return f"{splits}/{name}.s"


def signature(text: str) -> tuple:
    """Every four-byte word one split prints, in order -- its body's identity."""
    return tuple(_WORD.findall(text))


def split_directory(manifests, unit: str) -> pathlib.PurePosixPath:
    """Where ``unit``'s splits are: the code segment's tree, or its overlay module's.

    A main-image unit's bodies are under ``asm/nonmatchings/<code segment>``; an overlay
    unit's are under ``asm/nonmatchings/<module>``, because that module's own splat run is
    the only thing that writes them.
    """
    for chunk in manifests.chunks:
        if chunk.get("section") != ".debug":
            continue
        tunits = chunk.get("tunits") or ()
        if not tunits or manifests.cus[tunits[0]]["file"] != unit:
            continue
        module = manifests.cus[tunits[0]].get("overlay") or "main"
        return pathlib.PurePosixPath("asm/nonmatchings") / module
    return SPLITS


def read_splits(directory=None) -> dict:
    """``{split name: words}`` for every ``*.s`` in ``directory``, in name order.

    Reading the tree is the whole cost (measured: 4,491 splits, ~1.5 s); nothing else here
    opens a file.  A missing directory is :class:`Missing`, naming ``./ddr build``.
    """
    directory = pathlib.Path(REPO_ROOT / SPLITS if directory is None else directory)
    if not directory.is_dir():
        raise Missing(f"{_display(directory)} is absent; run {BUILD} to generate the splits")
    return {path.stem: signature(path.read_text()) for path in sorted(directory.glob("*.s"))}


def groups(signatures: dict) -> dict:
    """``{words: (member, ...)}`` for every signature two or more splits share.

    Members are sorted; a split that prints no words is not a body and is not grouped.
    """
    members = collections.defaultdict(list)
    for name, words in signatures.items():
        if words:
            members[words].append(name)
    return {words: tuple(sorted(names)) for words, names in members.items() if len(names) > 1}


def twins_of(name: str, signatures: dict, index: dict) -> tuple:
    """The other members of ``name``'s group, sorted -- nothing for a body with no twin."""
    words = signatures.get(name)
    if not words:
        return ()
    return tuple(member for member in index.get(words, ()) if member != name)


def bodies(names, signatures: dict, index: dict) -> list:
    """A :class:`Body` per function, in the order ``names`` gives (the unit's address order)."""
    return [Body(name,
                 len(signatures[name]) if name in signatures else None,
                 twins_of(name, signatures, index))
            for name in names]


def unit_functions(manifests) -> tuple:
    """``(function -> unit, unit -> functions, unit -> declared function count)``.

    Read from the same manifests the build places: each ``.debug`` chunk names its translation
    unit and the function records that follow it, and ``by_address`` names a record's
    ``low_pc``.  An *overlay* address is not in ``by_address`` -- the oracle withholds those
    records, because seven modules are alternatives at one base -- so the name comes from the
    same place the build's does: ``unplaced_symbols.txt``'s ``(module, address)`` records,
    with the module the unit's own DWARF overlay name gives.  A function nothing names is
    still counted, so a report can say how many it could not list.
    """
    by_name: dict = {}
    by_unit: dict = {}
    declared: dict = collections.Counter()
    for chunk in manifests.chunks:
        if chunk.get("section") != ".debug":
            continue
        tunits = chunk.get("tunits") or ()
        if not tunits:
            continue
        unit = manifests.cus[tunits[0]]["file"]
        overlay = manifests.cus[tunits[0]].get("overlay") or "main"
        for number in tunits[1:]:
            declared[unit] += 1
            low_pc = manifests.cus[number].get("low_pc")
            name = manifests.by_address.get(low_pc)
            if name is None and overlay != "main":
                name = manifests.overlay_symbols.get((overlay, low_pc))
            if name is None:
                continue
            by_name.setdefault(name, unit)
            by_unit.setdefault(unit, []).append(name)
    return (by_name, {unit: tuple(found) for unit, found in by_unit.items()},
            dict(declared))


def unit_file(manifests, name: str) -> str:
    """The translation unit ``name`` spells -- the rules ``ddr verify --tu`` uses.

    ``name`` is a repo path, a path tail or a file name; nothing or several matches is the
    same refusal the build gives, so a typo cannot report another unit's bodies.
    """
    matched = sorted(
        (index, record["file"]) for index, record in enumerate(manifests.cus)
        if record.get("kind") == "tu"
        and (record["file"] == name
             or record["file"].endswith("/" + name)
             or pathlib.PurePosixPath(record["file"]).name in (name, f"{name}.c")))
    if not matched:
        raise cc.Unusable(f"no translation unit matches {name!r}")
    if len(matched) > 1:
        raise cc.Unusable(f"{name!r} matches {len(matched)} translation units: "
                          + ", ".join(file for _, file in matched))
    return matched[0][1]


def promoted_units(tu_builds, root=REPO_ROOT) -> frozenset:
    """The units whose source is committed **and** whose ``tu_builds`` row exists.

    One convention, :func:`units.screen.is_promoted`: neither half alone is a promotion, so a
    half-landed unit never lends its shape as if it were verified.
    """
    root = pathlib.Path(root)
    return frozenset(
        source
        for source in (str(entry[0]).replace("\\", "/") for entry in tu_builds or ())
        if screen.is_promoted(screen.source_path(source), tu_builds, root))


# ---------------------------------------------------------------------------
# rendering
# ---------------------------------------------------------------------------


def _display(path) -> str:
    """The repo-relative spelling of ``path`` when it is inside the tree."""
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _count(number: int, noun: str) -> str:
    return f"{number} {noun}" if number == 1 else f"{number} {noun}s"


def note(body: Body, unit_of: dict, promoted, splits=SPLITS) -> str:
    """One body's twin line: what it shares, who is promoted, and the split to copy from.

    ``unit_of`` maps a function to the unit that owns it and ``promoted`` holds the units
    whose source is committed with a ``tu_builds`` row -- so a twin is promoted when its
    *unit* is, which is the only thing that makes its body already written down.
    """
    if body.words is None:
        return f"split absent — run {BUILD}"
    if not body.twins:
        return "no twin"
    known = [twin for twin in body.twins if unit_of.get(twin) in promoted]
    if not known:
        return (f"{_count(len(body.twins), 'twin candidate')}, none promoted - "
                f"one source shape serves all — copy {split_path(body.twins[0], splits)}")
    shown = known[:3]
    names = ", ".join(f"{twin} ({unit_of[twin]})" for twin in shown)
    if len(known) > len(shown):
        names += f", +{len(known) - len(shown)} more"
    return (f"{_count(len(body.twins), 'twin')}, {len(known)} promoted: {names} — "
            f"copy {split_path(shown[0], splits)}")


def render_unit(unit: str, found, unit_of: dict, promoted, *, target: str = "?", limit: int = LIMIT,
                note_text: str | None = None, splits=SPLITS) -> str:
    """One line per body of ``unit``: its word count, its twins, the split to copy from."""
    lines = [
        f"{unit} — identical-body twins ({target})",
        "words: every four-byte word the body's split prints, in order; twins share all "
        "of them.",
        "copy: the split whose body is already written in a promoted source, when one exists.",
    ]
    if note_text:
        lines.append(f"note: {note_text}")
    lines.append("")
    width = max([len("body")] + [len(body.name) for body in found])
    lines.append(f"  {'body':<{width}}  {'words':>5}  twins")
    shown = found[:limit] if limit > 0 else found
    for body in shown:
        words = "-" if body.words is None else str(body.words)
        lines.append(f"  {body.name:<{width}}  {words:>5}  "
                     f"{note(body, unit_of, promoted, splits)}")
    if len(shown) < len(found):
        lines.append(f"  … {len(found) - len(shown)} more bodies (--limit 0 prints all)")
    return "\n".join(lines) + "\n"


def render_all(index: dict, unit_of: dict, promoted, *, target: str = "?", limit: int = LIMIT) -> str:
    """The global groups, largest first: a worker picking a cheap unit reads this table."""
    ordered = sorted(index.items(), key=lambda item: (-len(item[1]), item[1][0]))
    total = sum(len(members) for _, members in ordered)
    lines = [
        f"identical-body groups under {SPLITS} ({target})",
        f"{len(ordered)} group(s) covering {total} split(s); a group is one source shape.",
        "promoted: a member whose unit's source is committed and whose tu_builds row exists.",
        "",
        f"  {'splits':>6}  {'words':>5}  {'promoted':>8}  members",
    ]
    shown = ordered[:limit] if limit > 0 else ordered
    for words, members in shown:
        names = ", ".join(members[:6])
        if len(members) > 6:
            names += f", +{len(members) - 6} more"
        known = [member for member in members if unit_of.get(member) in promoted]
        suffix = ""
        if known:
            suffix = f"  |  {known[0]} ({unit_of[known[0]]})"
            if len(known) > 1:
                suffix += f", +{len(known) - 1} more"
        lines.append(f"  {len(members):>6}  {len(words):>5}  {len(known):>8}  {names}{suffix}")
    if len(shown) < len(ordered):
        lines.append(f"  … {len(ordered) - len(shown)} more groups (--limit 0 prints all)")
    return "\n".join(lines) + "\n"


# ---------------------------------------------------------------------------
# entry point
# ---------------------------------------------------------------------------


def parse_args(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    what = parser.add_mutually_exclusive_group(required=True)
    what.add_argument("--tu", metavar="PATH",
                      help="the translation unit (repo path, path tail or file name)")
    what.add_argument("--all", action="store_true",
                      help="every identical-body group in the tree")
    parser.add_argument("--target", default=None,
                        help="the registered target (default: this tree's)")
    parser.add_argument("--limit", type=int, default=LIMIT, metavar="N",
                        help=f"rows to print (default {LIMIT}; 0 prints every row)")
    return parser.parse_args(argv)


def resolve_target(name=None):
    """The target ``--target`` names (a seam the tests use in place of the registry)."""
    from config import targets

    return targets.get(name)


def main(argv=None) -> int:
    args = parse_args(argv)
    from config import targets

    try:
        target = resolve_target(args.target)
        promoted = promoted_units(target.tu_builds)
        # `--all` is the main image's tree: an overlay module's bodies are alternatives to
        # it, not the same address space, so only `--tu` asks for a module's.
        if args.all:
            manifests, directory = None, SPLITS
        else:
            manifests = cc.Manifests(target)
            directory = split_directory(manifests, unit_file(manifests, args.tu))
        # The tree is read before the manifests: a missing one is a build shortfall, and that
        # is the answer a reader needs whether or not its config has been generated.
        signatures = read_splits(directory)
        index = groups(signatures)
        manifests = manifests or cc.Manifests(target)
        unit_of, by_unit, declared = unit_functions(manifests)
        if args.all:
            text = render_all(index, unit_of, promoted, target=target.name, limit=args.limit)
        else:
            unit = unit_file(manifests, args.tu)
            names = by_unit.get(unit, ())
            if not names:
                if declared.get(unit):
                    raise cc.Unusable(
                        f"{unit}: the manifests name none of its {declared[unit]} function(s) "
                        f"(nothing in {directory.as_posix()} names them)")
                text = (f"{unit}: declares no code — a data-only unit has no body to twin\n")
            else:
                found = bodies(names, signatures, index)
                if all(body.words is None for body in found):
                    raise Missing(f"{unit}: none of its splits exist under "
                                  f"{directory.as_posix()}; run {BUILD}")
                note_text = None
                if declared.get(unit, 0) > len(names):
                    note_text = (f"{declared[unit] - len(names)} function(s) of this unit "
                                 f"have no symbol in this layout and are not listed")
                text = render_unit(unit, found, unit_of, promoted, target=target.name,
                                   limit=args.limit, note_text=note_text, splits=directory)
    except targets.UnknownTarget as exc:
        print(f"twins: {exc}", file=sys.stderr)
        return 2
    except (cc.Unusable, Missing, OSError) as exc:
        print(f"twins: {exc}", file=sys.stderr)
        return 2

    sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
