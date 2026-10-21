#!/usr/bin/env python3
"""line_reflow.py -- turn a source's ``#line N`` directives into a directive-free file.

A ``#line N`` directive makes the line *after* it number ``N``, which is how a
reconstruction can carry a header comment, an ``#include``, a type block or a ``#define``
between two statements without forty blank lines standing in for them (``docs/unit-work.md``
records the two rules that come with it).  This tool removes the dependence on the
directive in one of two modes.

**Strict (the default).**  Each directive is replaced by the blank lines that put the line
after it on physical line ``N``, so every compiled line number is the same before and after
by construction.  The rewrite refuses, without writing anything, when that cannot be
faithful:

* **a directive that moves backwards.**  ``#line N`` on physical line ``L`` whose ``N`` is
  at or before the line the rewritten file has already reached: padding only adds lines, so
  the next line can never sit there.  The refusal names ``L`` and ``N``.
* **a gap a wall of padding would fill.**  More than :data:`MAX_PADDING` blank lines for one
  directive is refused with the count and a recommendation to use ``--normalise``; a
  directive carrying 1,000 lines of type closure is not a layout, it is a hole.
* **a directive carrying a file name** that is not the unit's own path.  Changing
  ``__FILE__`` would change what the compiler records; the accepted spellings are the unit's
  DWARF name (``TU.name``) and its repository path (``TU.file``), or whatever
  ``--unit-path`` names.
* **a ``#line`` spelling this tool does not parse** -- macros, continuations, junk.

For a translation unit with a recorded pair in ``tu_builds`` the strict rewrite is accepted
only when compiling the source before and after through the promotion placement machinery
with that pair gives byte-identical ``.text``, ``.debug`` and ``.line``.  The build does
**not** run this rewrite: a promoted source that still carries a directive is refused by
``toolchain.compile.refuse_line_directives`` (and by ``configure.py`` before it writes
``build.ninja``), and the refusal names this tool with ``--normalise`` as the remedy.  So a
promotion cannot silently compile a layout the committed file does not spell.

**Normalising (``--normalise``).**  The directives are stripped and the file keeps its own,
natural layout -- no padding standing in for lines nobody can know.  Two lines the
directives number alike (a repeated target, or a backward target the compiler does not
move) are joined onto one physical line, so the normalised file records the same statement
groups instead of one row per line; lines separated by anything but directives are left
alone.  The guarantee changes with the mode:

* ``.text`` must still be byte-identical; a rewrite that moves it refuses.
* ``.line`` is *allowed* to diverge.  The tool reports how many ``.line`` rows would differ
  from retail's, because ``--adopt-retail-meta`` takes retail's statement table whole and
  ``.text`` byte-identity is that step's precondition.  The unit must therefore be one the
  adoption step can place (its ``tu_builds`` row is ``"adopt"``, or it already reproduces
  ``.line`` strictly).

Usage::

    python3 tools/toolchain/line_reflow.py src/<dir>/<tu>.c          # strict, in place
    python3 tools/toolchain/line_reflow.py --normalise src/<dir>/<tu>.c
    python3 tools/toolchain/line_reflow.py --check src/<dir>/<tu>.c  # check, write nothing
    python3 tools/toolchain/line_reflow.py --unit-path AM/x/y.c other.c

Exit codes: 0 the file was rewritten (or needed nothing, or ``--check`` found it sound),
1 the rewrite refused (backwards, too large a gap, a foreign file name, an unparsable
directive, or a compiled part that may not move), 2 a configuration problem (no source,
unknown target, no recorded pair, ``--no-verify`` on a promotion unit).
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

#: The most blank lines a single strict-mode directive may stand in for.  A screenful is
#: enough to park a few declarations; past that the directive is compressing a block (a
#: unit's whole type closure, in the measured case), and padding is pretending to be that
#: block.  ``--normalise`` exists for exactly this case, so the refusal recommends it.
MAX_PADDING = 40


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


def _ends_in_line_comment(line: str) -> bool:
    """Whether ``line`` ends inside a ``//`` comment (comments and strings respected)."""
    index, quote, in_block = 0, None, False
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
            quote, index = char, index + 1
            continue
        if line.startswith("/*", index):
            in_block, index = True, index + 2
            continue
        if line.startswith("//", index):
            return True
        index += 1
    return False


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


def directive_count(text: str) -> int:
    """How many lines of ``text`` look like a ``#line`` directive (a cheap, conservative count).

    A ``#line`` inside a block comment counts here and resolves to no directive in
    :func:`scan`; that is the right answer for the build's refusal, which is about what a
    reader of the committed file sees rather than about what the compiler would honour.  The
    count is what :class:`toolchain.compile.Unusable` reports, so the message says how many
    directives the remedy will strip.
    """
    return len(_LIKE_DIRECTIVE.findall(text))


def has_directives(text: str) -> bool:
    """Whether ``text`` may contain a ``#line`` directive (a cheap, conservative test).

    See :func:`directive_count`: this is the test the promotion path uses to refuse a source,
    and it answers yes to a directive a block comment hides rather than paying for a scan.
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


def _check_names(directives, accepted) -> None:
    """Refuse a directive whose file name is not one the unit may spell."""
    for directive in directives:
        if directive.filename is None:
            continue
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


def rewrite(text: str, unit_path: str | None = None,
            accept_paths=()) -> tuple[str, tuple[Directive, ...]]:
    """Strict mode: ``text`` with each directive's target put on a physical line.

    Returns the rewritten text and the directives that were rewritten (empty when there were
    none).  Raises :class:`Refused` when the layout cannot be expressed -- and then nothing
    has been produced, so a caller can leave its input untouched.
    """
    accepted = tuple(path for path in (unit_path, *accept_paths) if path)
    directives = scan(text)
    if not directives:
        return text, directives
    _check_names(directives, accepted)

    output = []
    position = 0                     # lines emitted so far
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
        if padding > MAX_PADDING:
            raise Refused(
                number,
                f"#line {directive.target} would need {padding} blank lines, more than the "
                f"{MAX_PADDING}-line bound for one gap; refusing to emit a wall of padding "
                f"-- run with --normalise to strip the directives instead (its .line rows "
                f"are then taken from retail by --adopt-retail-meta)")
        ending = "\r\n" if raw.endswith("\r\n") else "\n"
        output.extend([ending] * padding)
        # A target equal to the line the directive already occupies collapses the directive
        # away (`padding == 0`); the next line then falls exactly on the target.
        position += padding
    return "".join(output), directives


def strip(text: str, unit_path: str | None = None,
          accept_paths=()) -> tuple[str, tuple[Directive, ...]]:
    """Normalising mode: remove every directive line, keeping shared line numbers joined.

    The file keeps its natural layout, so the lines after a directive move to wherever the
    remaining text puts them.  Two lines that the directives number alike -- a repeated
    target, or a backward target the compiler does not move -- are joined with a single
    space instead: the directive layout recorded one line for the pair, and giving each its
    own physical line would add a statement row the directive layout never emitted.  Only
    lines separated by directives alone are joined; a blank line or other text between them
    is authoritative and stops the join.  A file name that is not the unit's own still
    refuses (stripping such a directive would change ``__FILE__``); the caller checks the
    consequences with :func:`verify_normalised`.
    """
    accepted = tuple(path for path in (unit_path, *accept_paths) if path)
    directives = scan(text)
    if not directives:
        return text, directives
    _check_names(directives, accepted)
    lines = _lines(text)
    by_line = {directive.physical: directive for directive in directives}
    numbers = {}
    number = 1
    for physical, raw in enumerate(lines, 1):
        directive = by_line.get(physical)
        if directive is not None:
            number = directive.target
            continue
        numbers[physical] = number
        number += 1
    joined = set()
    previous = None
    for physical in sorted(numbers):
        if not lines[physical - 1].strip():
            continue
        if previous is not None:
            between = range(previous + 1, physical)
            if (all(index in by_line for index in between)
                    and numbers[physical] <= numbers[previous]):
                joined.add(physical)
        previous = physical
    output = []
    for physical, raw in enumerate(lines, 1):
        if physical in by_line:
            continue
        if physical not in joined:
            output.append(raw)
            continue
        earlier = output[-1]
        head = _content(earlier)
        ending = earlier[len(head):]
        if _ends_in_line_comment(head) or head.rstrip().endswith("\\"):
            raise Refused(
                physical,
                "the two statements were recorded on one line, but the line before this "
                "one ends in a comment or a continuation; joining them would change what "
                "the comment covers, so the layout cannot be kept without the directive")
        body = _content(raw).lstrip()
        if body.startswith("#"):
            raise Refused(
                physical,
                "the two statements were recorded on one line, but this line is a "
                "preprocessor directive; joining them would not be C")
        output[-1] = f"{head} {body}{ending}"
    return "".join(output), directives


def verify(tu, original: bytes, rewritten: bytes, target):
    """Strict mode: compile both spellings and require identical ``.text/.debug/.line``.

    ``tu`` is the :class:`toolchain.compile.Tu`, ``target`` the configured target whose
    ``tu_builds`` row supplies the settled pair.  The comparison is the promotion's own
    three parts; a different length or byte raises :class:`Refused` and no file is written.
    Returns the pair of :class:`toolchain.compile.Placed` results for their sizes.
    """
    from toolchain import compile as cc
    from toolchain import fetch

    pair = _pair(tu, target)
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


def _pair(tu, target):
    pair = target.build_pair(tu.file)
    if pair is None:
        raise Refused(None, f"{tu.file} has no recorded compiler pair in tu_builds; measure "
                            f"it with tools/toolchain/select_build.py before rewriting it")
    return pair


def compare_normalised(before, after, retail_line: bytes):
    """The normalising mode's guarantee: ``.text`` identical, and the ``.line`` rows that differ.

    ``after`` is the placement of the rewritten source compiled with
    ``allow_line=True``: its ``emitted_line`` is what the normalised source produced, and
    ``retail_line`` is the statement table the adoption step would take.  Returns
    ``(changes, tables, rows, note)`` -- the differing statement rows, the number of
    statement tables compared, the row total, and a note when the emitted table is not
    row-for-row comparable with retail's (a normalised layout can emit a different number of
    records; adoption still takes retail's chunk whole).  Raises :class:`Refused` when
    ``.text`` moved.
    """
    from toolchain import debug_adopt

    if before.text != after.text:
        left, right = before.text, after.text
        at = next((index for index, (one, other) in enumerate(zip(left, right))
                   if one != other), min(len(left), len(right)))
        raise Refused(
            None,
            f"the normalised source moves .text: 0x{len(left):X} bytes against "
            f"0x{len(right):X}, first difference at 0x{at:X}; normalising may drop .line "
            f"rows but never an instruction, refusing to write it")
    # A normalised layout can emit a different number of statement records; the glued
    # chunk is then not parseable table-for-table, so the per-function block sizes are the
    # honest measure.  Either way adoption takes retail's chunk whole -- this is the report.
    sized = [(label, emitted, pinned) for label, chunk, emitted, pinned in after.sizes
             if chunk == ".line"]
    differing = [(emitted - pinned) // 10 for _label, emitted, pinned in sized
                 if emitted != pinned]
    if differing:
        extra = sum(differing)
        return [], len(sized), 0, (f"{extra} more record(s)" if extra > 0
                                   else f"{-extra} fewer record(s)")
    try:
        changes, tables, rows = debug_adopt.line_changes(after.emitted_line, retail_line)
    except debug_adopt.Refused as exc:
        return [], 0, 0, str(exc)
    return changes, tables, rows, None


def verify_normalised(tu, original: bytes, rewritten: bytes, target):
    """Normalising mode: ``.text`` must survive; ``.line`` may diverge and is counted.

    The source *before* the rewrite is compiled under its recorded state (a strictly
    reproducing unit must still reproduce it).  The written source is compiled with
    ``allow_line`` so its emitted statement table survives for the count: ``.text`` must
    still be retail's (condition 1), which is the adoption step's own precondition, but the
    rows are compared here rather than adopted.  Returns
    ``(before, after, changes, tables, rows, note)``.
    """
    from toolchain import compile as cc
    from toolchain import fetch

    compiler, flags, state = _pair(tu, target)
    manifests = cc.Manifests(target)
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    command = shlex.split(flags)
    normalise_debug = state is True
    adopt = state == "adopt"
    with tempfile.TemporaryDirectory(prefix="line-reflow-") as scratch:
        before = cc._place_source(tu, manifests, compiler_dir, wibo, command, original,
                                  pathlib.Path(scratch) / "before.mw.o", normalise_debug,
                                  adopt)
        after = cc._place_source(tu, manifests, compiler_dir, wibo, command, rewritten,
                                 pathlib.Path(scratch) / "after.mw.o", normalise_debug,
                                 adopt, allow_line=True)
    changes, tables, rows, note = compare_normalised(before, after,
                                                     cc.retail_bytes(tu)["line"])
    return before, after, changes, tables, rows, note


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
    parser.add_argument("--normalise", action="store_true",
                        help="strip the directives and keep the natural layout instead of "
                             "padding to their numbers, joining the lines a directive "
                             "numbered alike; .text must stay identical and the differing "
                             ".line rows are reported for --adopt-retail-meta")
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
        rewrite_text = strip if args.normalise else rewrite
        rewritten, directives = rewrite_text(text, accept_paths=accepted)
    except Refused as exc:
        print(f"line_reflow.py: {_display(source)}: {exc}", file=sys.stderr)
        return 1

    if not directives:
        print(f"line_reflow.py: {_display(source)}: no #line directives; nothing to do")
        return 0

    if tu is None:
        print(f"line_reflow.py: {_display(source)}: no recorded pair for this file; "
              f"layout check only, nothing was compiled")
    elif args.normalise:
        try:
            before, after, changes, tables, rows, note = verify_normalised(
                tu, original, rewritten.encode("latin-1"), target)
        except Refused as exc:
            print(f"line_reflow.py: {_display(source)}: {exc}", file=sys.stderr)
            return 1
        compiler, flags, _state = target.build_pair(tu.file)
        if note:
            detail = (f"the emitted .line is not row-for-row comparable with retail's "
                      f"({note}); retail's chunk is what --adopt-retail-meta takes whole")
        else:
            detail = (f"{len(changes)} of {rows} .line row(s) differ in {tables} statement "
                      f"table(s), and retail's table is what --adopt-retail-meta takes")
        print(f"line_reflow.py: {_display(source)}: {len(directives)} directive(s) stripped; "
              f".text {len(after.text):#x} bytes under {compiler} {flags} -- byte-identical; "
              f"{detail}")
    else:
        try:
            before, after = verify(tu, original, rewritten.encode("latin-1"), target)
        except Refused as exc:
            print(f"line_reflow.py: {_display(source)}: {exc}", file=sys.stderr)
            return 1
        compiler, flags, _state = target.build_pair(tu.file)
        print(f"line_reflow.py: {_display(source)}: {len(directives)} directive(s) reflowed; "
              f".text {len(after.text):#x}, .debug {len(after.debug):#x}, .line "
              f"{len(after.line):#x} bytes under {compiler} {flags} -- byte-identical")

    if args.check:
        print(f"line_reflow.py: {_display(source)}: {len(directives)} directive(s) would be "
              f"reflowed; --check wrote nothing")
        return 0
    source.write_bytes(rewritten.encode("latin-1"))
    if args.normalise:
        print(f"line_reflow.py: {_display(source)}: stripped {len(directives)} directive(s)")
    else:
        print(f"line_reflow.py: {_display(source)}: rewrote {len(directives)} directive(s) "
              f"into physical lines")
    return 0


if __name__ == "__main__":
    sys.exit(main())
