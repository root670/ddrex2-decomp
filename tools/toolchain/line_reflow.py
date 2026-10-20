#!/usr/bin/env python3
"""line_reflow.py -- turn a source's ``#line N`` directives into physical line numbers.

A ``#line N`` directive makes the line *after* it number ``N``, which is how a
reconstruction can carry a header comment, an ``#include``, a type block or a ``#define``
between two statements without forty blank lines standing in for them (``docs/unit-work.md``
records the two rules that come with it).  This tool removes the dependence on the
directive: it rewrites each one so the line that followed it sits at physical line ``N``,
replacing the directive with blank lines and copying every other byte -- indentation,
comments, blank lines -- unchanged.  The compiled line numbers are the same before and
after by construction; :func:`verify` is what proves it.

The rewrite refuses, without writing anything, when it cannot be faithful:

* **a directive that moves backwards.**  ``#line N`` on physical line ``L`` whose ``N`` is
  at or before the line the rewritten file has already reached: padding only adds lines, so
  the next line can never sit there.  The refusal names ``L`` and ``N``.
* **a directive carrying a file name** that is not the unit's own path.  Changing
  ``__FILE__`` would change what the compiler records; the accepted spellings are the unit's
  DWARF name (``TU.name``) and its repository path (``TU.file``), or whatever
  ``--unit-path`` names.
* **a ``#line`` spelling this tool does not parse** -- macros, continuations, junk.  It
  refuses rather than guess at a byte-preserving rewrite.

For a translation unit with a recorded pair in ``tu_builds`` the rewrite is accepted only
when compiling the source before and after through the promotion path
(:func:`toolchain.compile.place`) with that pair gives byte-identical ``.text``, ``.debug``
and ``.line``.  The check is the acceptance criterion, and the same condition runs inside
``compile.py`` whenever a promoted source still carries a directive, so a promotion cannot
silently compile a layout the rewrite would have changed.

Usage::

    python3 tools/toolchain/line_reflow.py src/<dir>/<tu>.c          # rewrite in place
    python3 tools/toolchain/line_reflow.py --check src/<dir>/<tu>.c  # check, write nothing
    python3 tools/toolchain/line_reflow.py --unit-path AM/x/y.c other.c

Exit codes: 0 the file was rewritten (or needed nothing, or ``--check`` found it sound),
1 the rewrite refused (backwards, a foreign file name, an unparsable directive, or a
compiled part that differs), 2 a configuration problem (no source, unknown target, no
recorded pair, ``--no-verify`` on a promotion unit).
"""

from __future__ import annotations

import argparse
import pathlib
import re
import shlex
import sys
import tempfile
from typing import NamedTuple

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

#: The directive the tool understands: ``#line N`` with optional whitespace, and optionally
#: one double-quoted file name.  A trailing ``//`` or ``/* ... */`` comment is kept out of
#: the numbers; every other spelling is refused rather than reinterpreted.
_DIRECTIVE = re.compile(
    r'^[ \t]*#[ \t]*line[ \t]+(?P<number>[0-9]+)'
    r'(?:[ \t]+"(?P<filename>[^"\n]*)")?'
    r'[ \t]*(?://.*|/\*.*\*/[ \t]*)?\r?$')
#: A line that *looks* like the directive, whether or not :data:`_DIRECTIVE` accepts it.
_LIKE_DIRECTIVE = re.compile(r"^[ \t]*#[ \t]*line\b", re.MULTILINE)


class Directive(NamedTuple):
    """One directive as the source spells it."""

    physical: int            # 1-based line the directive occupies
    target: int              # the number it gives the next line
    filename: str | None     # the optional file name it carries


class Refused(Exception):
    """The rewrite cannot be faithful; ``line`` is the source line to name in the message."""

    def __init__(self, line: int | None, reason: str):
        self.line = line
        super().__init__(f"line {line}: {reason}" if line is not None else reason)


def _advance(line: str, in_block: bool) -> bool:
    """Whether a block comment is open after ``line`` (comments and strings respected)."""
    index, quote = 0, None
    while index < len(line):
        char = line[index]
        if in_block:
            if line.startswith("*/", index):
                in_block, index = False, index + 2
                continue
            index += 1
            continue
        if quote is not None:
            if char == "\\":
                index += 2
                continue
            if char == quote:
                quote = None
            index += 1
            continue
        if char in "\"'":
            quote = char
            index += 1
            continue
        if line.startswith("/*", index):
            in_block, index = True, index + 2
            continue
        if line.startswith("//", index):
            break
        index += 1
    return in_block


def _content(raw: str) -> str:
    """A line without its terminator, so the pattern sees the line's own text."""
    if raw.endswith("\n"):
        raw = raw[:-1]
    if raw.endswith("\r"):
        raw = raw[:-1]
    return raw


def _lines(text: str) -> list[str]:
    """Split on ``\\n`` only, terminators kept.

    ``str.splitlines`` also breaks on control bytes that are ordinary data in a C file
    decoded as latin-1 (0x0B, 0x0C, 0x85, ...), which would both miscount physical lines
    and lose bytes.  This keeps the rewrite byte-preserving.
    """
    pieces = text.split("\n")
    lines = [piece + "\n" for piece in pieces[:-1]]
    if pieces[-1]:
        lines.append(pieces[-1])
    return lines


def scan(text: str) -> tuple[Directive, ...]:
    """Every ``#line`` directive in ``text``, in order.

    Directives inside a block comment are not directives; a line continued from the
    previous one is not a directive either.  A line that starts like a directive but does
    not parse raises :class:`Refused` -- an unparsed one would otherwise be copied through
    and leave the rewritten file's numbering wrong.
    """
    found = []
    in_block, continued = False, False
    for number, raw in enumerate(_lines(text), 1):
        body = _content(raw)
        if not in_block and not continued and _LIKE_DIRECTIVE.match(body):
            match = _DIRECTIVE.match(body)
            if match is None:
                raise Refused(number, f"cannot parse the #line directive {body.strip()!r}; "
                                      f"this tool only rewrites `#line N` and "
                                      f"`#line N \"file\"`")
            found.append(Directive(number, int(match["number"]), match["filename"]))
        continued = body.endswith("\\") and not in_block
        in_block = _advance(body, in_block)
    return tuple(found)


def has_directives(text: str) -> bool:
    """Whether ``text`` may contain a ``#line`` directive (a cheap, conservative test).

    A ``#line`` inside a block comment answers yes here and resolves to no directives in
    :func:`scan`; the point of the test is only to keep the promotion path from paying for a
    scan twice on every unit that has no directive at all.
    """
    return bool(_LIKE_DIRECTIVE.search(text))


def _path(path: str) -> str:
    return path.replace("\\", "/")


def _match_filename(filename: str, accepted) -> bool:
    """Whether ``filename`` names one of the unit's own paths."""
    spelled = _path(filename)
    for candidate in accepted:
        if candidate and spelled == _path(candidate):
            return True
    return False


def rewrite(text: str, unit_path: str | None = None,
            accept_paths=()) -> tuple[str, tuple[Directive, ...]]:
    """``text`` with every directive replaced by the lines that put its target in place.

    Returns the rewritten text and the directives that were rewritten (empty when there were
    none).  Raises :class:`Refused` when the layout cannot be expressed -- and then nothing
    has been produced, so a caller can leave its input untouched.
    """
    accepted = tuple(path for path in (unit_path, *accept_paths) if path)
    directives = scan(text)
    if not directives:
        return text, directives

    output = []
    position = 0                     # lines emitted so far
    for directive in directives:
        if directive.filename is not None:
            if not accepted:
                raise Refused(
                    directive.physical,
                    f'#line {directive.target} names {directive.filename!r}, but no unit '
                    f'path is known to compare it with; pass --unit-path')
            if not _match_filename(directive.filename, accepted):
                raise Refused(
                    directive.physical,
                    f'#line {directive.target} names {directive.filename!r}, which is not '
                    f'this unit ({", ".join(sorted(_path(path) for path in accepted))}); '
                    f'refusing to change the path the compiler records')

    lines = _lines(text)
    by_line = {directive.physical: directive for directive in directives}
    for number, raw in enumerate(lines, 1):
        directive = by_line.get(number)
        if directive is None:
            output.append(raw)
            position += 1
            continue
        padding = directive.target - position - 1
        if padding < 0:
            raise Refused(
                number,
                f"#line {directive.target} moves backwards: the rewritten file has already "
                f"reached line {position + 1}, so the next line cannot sit at "
                f"{directive.target}; physical layout cannot express it")
        ending = "\r\n" if raw.endswith("\r\n") else "\n"
        output.extend([ending] * padding)
        # A target equal to the line the directive already occupies collapses the directive
        # away (`padding == 0`); the next line then falls exactly on the target.
        position += padding
    return "".join(output), directives


def verify(tu, original: bytes, rewritten: bytes, target):
    """Compile both spellings through the promotion path and require identical bytes.

    ``tu`` is the :class:`toolchain.compile.Tu`, ``target`` the configured target whose
    ``tu_builds`` row supplies the settled pair.  The comparison is the promotion's own
    three parts; a different length or byte raises :class:`Refused` and no file is written.
    Returns the pair of :class:`toolchain.compile.Placed` results for their sizes.
    """
    from toolchain import compile as cc
    from toolchain import fetch

    pair = target.build_pair(tu.file)
    if pair is None:
        raise Refused(None, f"{tu.file} has no recorded compiler pair in tu_builds; measure "
                            f"it with tools/toolchain/select_build.py before rewriting it")
    compiler, flags, state = pair
    manifests = cc.Manifests(target)
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    command = shlex.split(flags)
    normalise = state is True
    adopt = state == "adopt"
    with tempfile.TemporaryDirectory(prefix="line-reflow-") as scratch:
        before = cc._place_source(tu, manifests, compiler_dir, wibo, command, original,
                                  pathlib.Path(scratch) / "before.mw.o", normalise, adopt)
        after = cc._place_source(tu, manifests, compiler_dir, wibo, command, rewritten,
                                 pathlib.Path(scratch) / "after.mw.o", normalise, adopt)
    for part in ("text", "debug", "line"):
        mine, theirs = getattr(before, part), getattr(after, part)
        if mine == theirs:
            continue
        at = cc._first_difference(mine, theirs)
        raise Refused(
            None,
            f"the rewritten source does not compile to the same {part}: "
            f"0x{len(mine):X} bytes against 0x{len(theirs):X}, first difference at "
            f"0x{at:X}; the rewrite is not semantics-preserving, refusing to write it")
    return before, after


def _display(path) -> str:
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _unit(source: pathlib.Path, target):
    """The configured translation unit ``source`` is, or None for any other file."""
    from toolchain import compile as cc

    try:
        relative = str(source.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return None
    manifests = cc.Manifests(target)
    try:
        tu = manifests.tu_named(relative)
    except cc.Unusable:
        return None
    return tu if (REPO_ROOT / tu.file).resolve() == source.resolve() else None


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(prog="line_reflow.py", description=__doc__.splitlines()[0])
    parser.add_argument("source", help="the C file to rewrite")
    parser.add_argument("--target", default=None,
                        help="the target whose manifests and tu_builds name the unit "
                             "(default: this tree's configured target)")
    parser.add_argument("--unit-path", action="append", default=[], metavar="PATH",
                        help="a path a #line file name may spell as the unit's own "
                             "(repeatable; added to the unit's own paths)")
    parser.add_argument("--check", action="store_true",
                        help="run the whole rewrite and its compile check, write nothing")
    parser.add_argument("--no-verify", action="store_true",
                        help="skip the compile comparison (only for a file that is not a "
                             "promoted unit)")
    return parser


def main(argv=None) -> int:
    from config import targets

    args = _parser().parse_args(argv)
    source = pathlib.Path(args.source).expanduser()
    try:
        target = targets.get(args.target) if args.target else targets.get(targets.DEFAULT)
    except targets.UnknownTarget as exc:
        print(f"line_reflow.py: error: {exc}", file=sys.stderr)
        return 2
    if not source.is_file():
        print(f"line_reflow.py: error: {source} does not exist", file=sys.stderr)
        return 2
    original = source.read_bytes()
    text = original.decode("latin-1")       # one byte <-> one character: exact round trip

    try:
        tu = _unit(source, target)
        if not args.check and args.no_verify and tu is not None:
            print(f"line_reflow.py: error: {_display(source)} is a promotion unit; its "
                  f"rewrite must be compiled before and after through the promotion path",
                  file=sys.stderr)
            return 2
        accepted = list(args.unit_path)
        if tu is not None:
            accepted = [tu.name, tu.file, *accepted]
        rewritten, directives = rewrite(text, accept_paths=accepted)
    except Refused as exc:
        print(f"line_reflow.py: {_display(source)}: {exc}", file=sys.stderr)
        return 1

    if not directives:
        print(f"line_reflow.py: {_display(source)}: no #line directives; nothing to do")
        return 0

    if tu is None:
        print(f"line_reflow.py: {_display(source)}: no recorded pair for this file; "
              f"layout check only, nothing was compiled")
    else:
        try:
            before, after = verify(tu, original, rewritten.encode("latin-1"), target)
        except Refused as exc:
            print(f"line_reflow.py: {_display(source)}: {exc}", file=sys.stderr)
            return 1
        compiler, flags, _normalise = target.build_pair(tu.file)
        print(f"line_reflow.py: {_display(source)}: {len(directives)} directive(s) reflowed; "
              f".text {len(after.text):#x}, .debug {len(after.debug):#x}, .line "
              f"{len(after.line):#x} bytes under {compiler} {flags} -- byte-identical")

    if args.check:
        print(f"line_reflow.py: {_display(source)}: {len(directives)} directive(s) would be "
              f"reflowed; --check wrote nothing")
        return 0
    source.write_bytes(rewritten.encode("latin-1"))
    print(f"line_reflow.py: {_display(source)}: rewrote {len(directives)} directive(s) into "
          f"physical lines")
    return 0


if __name__ == "__main__":
    sys.exit(main())
