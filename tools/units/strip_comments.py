#!/usr/bin/env python3
"""strip_comments.py -- remove a promoted source's comments without moving a byte.

A promoted unit's ``.line`` chunk pins every statement to retail's line number, so a
comment cannot be *deleted*: deleting it would move every statement below it.  This tool
therefore blanks comment text lexically -- every removed character becomes a space, every
``\\n`` and ``\\r`` survives -- which keeps the physical line numbers, the indentation and
the token stream exactly where they were.  A line that held only a comment comes out as a
line of spaces followed by its newline: a blank line, never a shorter file.  Because the
token stream is unchanged the object *should* be unchanged, and the tool does not assume it:
a source that names a configured promotion unit is compiled before and after through the
promotion path and is written only when ``.text``, ``.debug`` and ``.line`` are byte-identical.

There is no exception: every comment is blanked, including the leading header block and a
note marked with ``/*!`` or ``//!``.  A promoted source carries no comments at all.  The tool
enforces that rather than trusting the strip: :func:`require_no_comments` fails when a source
still holds one, ``--check`` fails while the file on disk is not clean, and the write path
refuses to write a result that carries one.

The lexer respects ``"..."`` strings, ``'...'`` character literals and backslash escapes, so
a ``//`` or ``/*`` inside a string is code and is left alone.  It refuses rather than guesses
when the file's comment structure is not well formed:

* an unterminated ``/*`` comment, a stray ``*/`` outside a comment, an unterminated string or
  character literal;
* a line that ends in a backslash continuation -- C splices such a line before tokenising,
  so a "comment" can swallow the line after it and blanking it would change the program
  text the compiler sees.

``--collapse`` is the tidy step that follows the strip.  It strips first, so the comments
are already gone, and then deliberately *moves* lines: runs of blank lines (including the
blank lines a stripped header and stripped notes became) become one, trailing whitespace
goes, a blank line directly after an opening ``{`` or before a closing ``}`` is dropped
-- those were line-number placeholders and carry nothing once ``.line`` is adopted -- and
every block-opening brace is joined to the line of its statement (a brace alone on the
next line, ``if (x)\\n{``, and a brace that opens a block inline, ``do\\n{ x = 1;``).  The
brace pass refuses a site it cannot read: a brace after a declaration or a closed block,
an aggregate-initializer row, and a block whose first statement is itself a declaration
are left on their own lines and reported.  Stray brace-padding is refused only
for a file that is not a promoted unit: a promoted source's blank line directly inside a
brace is line evidence (retail's own statement position), so ``--check`` passes it, while a
comment still fails there as everywhere.  Because the tidy
**moves statement lines**, acceptance is stricter than the strip's: ``.text`` must be
byte-identical, and ``.debug``/``.line`` must be *retail's* -- the adoption step proves the
chunk byte for byte and substitutes retail's ``.line``.

Usage::

    python3 tools/units/strip_comments.py src/sys/sys_scf.c
    python3 tools/units/strip_comments.py --check src/sys/sys_scf.c
    python3 tools/units/strip_comments.py --collapse src/sys/sys_scf.c

For a file that is not a configured promotion unit there is nothing to compile; such a file
is handled only with ``--no-verify`` (a layout-only edit) and the tool says so.  Exit codes:
0 stripped/tidied (or nothing to do), 1 refused, 2 unusable invocation or input.
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



class Comment(NamedTuple):
    """One comment token as the source spells it."""

    start: int          # offset of the opener
    end: int            # offset just past the closer (past the line feed for ``//``)
    kind: str           # "line" or "block"


class Refused(Exception):
    """The rewrite cannot be faithful; ``line`` is the source line to name in the message."""

    def __init__(self, line: int | None, reason: str):
        self.line = line
        self.reason = reason
        super().__init__(f"line {line}: {reason}" if line is not None else reason)


def _line_of(text: str, offset: int) -> int:
    return text.count("\n", 0, offset) + 1


def _check_splices(text: str) -> None:
    """Refuse a physical line that ends in a backslash continuation.

    C removes ``\\`` + newline before it tokenises, so the next physical line is part of
    this one.  Treating the pair as two lines would blank a comment and leave text the
    compiler sees *outside* it (or the reverse), so the file is refused rather than
    reinterpreted.
    """
    lines = text.split("\n")
    for number, line in enumerate(lines, 1):
        if line.endswith("\r"):
            line = line[:-1]
        # A backslash on the file's last line has no line feed to splice; it is a stray
        # character, not a continuation.
        if line.endswith("\\") and number < len(lines):
            raise Refused(number, "a trailing backslash continues onto the next line; "
                                  "splicing runs before comments are recognised, so the "
                                  "comment structure cannot be stripped faithfully")


def scan(text: str) -> tuple:
    """Every comment in ``text``, in order.

    Raises :class:`Refused` for malformed comments or literals.
    """
    found: list[dict] = []
    length = len(text)
    index = 0
    while index < length:
        char = text[index]
        if char in ('"', "'"):
            quote = char
            start = index
            index += 1
            while index < length:
                if text[index] == "\\":
                    index += 2
                    continue
                if text[index] == quote:
                    index += 1
                    break
                if text[index] == "\n":
                    raise Refused(_line_of(text, start),
                                  "unterminated string literal" if quote == '"'
                                  else "unterminated character literal")
                index += 1
            else:
                raise Refused(_line_of(text, start),
                              "unterminated string literal" if quote == '"'
                              else "unterminated character literal")
            continue
        if char == "/" and index + 1 < length and text[index + 1] == "/":
            start = index
            newline = text.find("\n", index)
            end = length if newline < 0 else newline
            found.append({"start": start, "end": end, "kind": "line"})
            index = end
            continue
        if char == "/" and index + 1 < length and text[index + 1] == "*":
            start = index
            close = text.find("*/", index + 2)
            if close < 0:
                raise Refused(_line_of(text, start), "unterminated /* comment")
            end = close + 2
            found.append({"start": start, "end": end, "kind": "block"})
            index = end
            continue
        if char == "*" and index + 1 < length and text[index + 1] == "/":
            raise Refused(_line_of(text, index), "*/ outside a comment")
        index += 1

    return tuple(Comment(item["start"], item["end"], item["kind"]) for item in found)


def require_no_comments(text: str, what: str = "source") -> None:
    """Raise :class:`Refused` unless ``text`` contains no comment at all.

    This is the enforcement behind "a promoted source carries no comments": it is run on
    the bytes the tool is about to write and under ``--check`` on the file as committed, so
    a kept header, a ``/*!`` note or a strip that silently missed one is a failure, not a
    style question.
    """
    comments = scan(text)
    if not comments:
        return
    first = comments[0]
    raise Refused(
        _line_of(text, first.start),
        f"the {what} still carries {len(comments)} comment(s); a promoted source carries "
        f"none -- run the strip without --check to blank them")


def _brace_edge_blanks(lines) -> tuple:
    """The 1-based numbers of blank lines sitting directly inside a brace.

    A blank line immediately after a line ending in ``{`` or immediately before a line
    starting with ``}`` is a possible line-number placeholder: for a promoted unit it holds
    retail's statement position, so ``--check`` passes it and the tidy keeps it; for any
    other file it carries nothing, so the tidy drops it and the gate refuses it.
    """
    found = []
    for index, line in enumerate(lines):
        if line.strip():
            continue
        previous = lines[index - 1] if index else None
        following = lines[index + 1] if index + 1 < len(lines) else None
        after_open = previous is not None and previous.rstrip().endswith("{")
        before_close = following is not None and following.lstrip().startswith("}")
        if after_open or before_close:
            found.append(index + 1)
    return tuple(found)


def brace_blanks_are_evidence(unit) -> bool:
    """Whether a blank line inside a brace is line evidence: only for a promoted unit.

    A promoted unit's ``.line`` chunk pins its statements to retail's line numbers, so a
    blank line directly inside a brace is the placeholder that holds the number, not
    padding.  ``None`` -- a file that is not a promotion unit -- has no such evidence, so it
    is held to the tidy layout.
    """
    return unit is not None


def require_no_brace_padding(text: str, what: str = "source") -> None:
    """Raise :class:`Refused` if a blank line sits directly inside a brace.

    This keeps a file that is not a promoted unit from looking accidental: a function or
    nested block opens and immediately reads its first statement, and its last statement is
    immediately followed by the closing brace.

    A promoted unit is not held to this: its blank is retail's statement position, so
    ``--check`` asks :func:`brace_blanks_are_evidence` before it fails.
    """
    found = _brace_edge_blanks(text.splitlines())
    if not found:
        return
    raise Refused(
        found[0],
        f"the {what} has a blank line directly inside a brace (line {found[0]}); no blank "
        f"line belongs immediately after an opening brace or before a closing one -- run "
        f"--collapse to drop it")


def strip(text: str) -> str:
    """``text`` with every comment blanked, header and ``/*!`` notes included.

    Removed characters become spaces; newlines (and carriage returns) are kept, so the
    file has the same number of lines and every statement keeps its line number.  The
    non-comment bytes are copied verbatim.
    """
    _check_splices(text)
    comments = scan(text)
    output = list(text)
    for comment in comments:
        for offset in range(comment.start, comment.end):
            if output[offset] not in "\r\n":
                output[offset] = " "
    stripped = "".join(output)
    if stripped.count("\n") != text.count("\n"):
        raise Refused(None, "internal error: stripping changed the line count")
    return stripped


class Attached(NamedTuple):
    """The brace-attach result: the text, the joins made, and the sites left alone.

    ``skipped`` holds ``(line, reason)`` for every block brace the pass deliberately did
    not join: a brace after a declaration or a closed block, an aggregate initializer row,
    or a block whose first statement is itself a declaration (moving that statement would
    move the declaration's recorded line).
    """

    text: str
    joined: int
    skipped: tuple


#: The first token of a declaration, which the attach pass must not pull onto a brace line.
_DECLARATION = re.compile(
    r"^(?:typedef|extern|static|const|volatile|register|auto|unsigned|signed|"
    r"int|char|short|long|float|double|void|struct|union|enum)\b")

#: ``TYPE name`` / ``TYPE *name`` / ``TYPE name[N]`` followed by ``=`` or ``;`` -- a
#: declaration spelled with a typedef name rather than a keyword (``anon_0_114 *p;``).
_TYPED_DECLARATION = re.compile(
    r"^[A-Za-z_]\w*\s+\**[A-Za-z_]\w*\s*(?:\[[^\]]*\])?\s*(?:=|;)")


def _block_statement_header(line: str) -> bool:
    """Whether ``line`` is the statement a following block brace belongs to.

    The accepted shapes are a control header ending in ``)`` (``for``/``while``/``if``/
    ``else if``/``switch``), the bare ``do``/``else`` keywords, and a function signature
    -- which is a declarator ending in ``)`` too.  A line ending in ``;`` is a declaration
    or a finished statement and keeps its line; so does a preprocessor directive and a
    line ending in ``{`` or ``,`` (an aggregate initializer).
    """
    stripped = line.strip()
    if not stripped or stripped.startswith("#"):
        return False
    if stripped.endswith(";"):
        return False
    if stripped in ("do", "else") or stripped.endswith(" else"):
        return True
    if stripped.endswith(")") and not stripped.startswith((")", ",")):
        return True
    return False


def _carries_declaration(statement: str) -> bool:
    """Whether ``statement`` is a declaration, which keeps the line the evidence gave it."""
    return bool(_DECLARATION.match(statement) or _TYPED_DECLARATION.match(statement))


def _skip_reason(previous: str | None) -> str:
    """Why the brace on the next line cannot be attached to ``previous``."""
    if previous is None:
        return "the brace is the file's first line; there is no statement to attach it to"
    stripped = previous.strip()
    if not stripped:
        return "the line before it is blank; a blank separates the statement from its brace"
    if stripped.startswith("#"):
        return "it follows a preprocessor directive"
    if stripped.endswith(",") or stripped.endswith("{"):
        return ("it opens an aggregate initializer, not a block; the initializer rows keep "
                "their own lines")
    if stripped.endswith(";"):
        return ("it follows a declaration that must keep its line; a bare block after a "
                "declaration is not that declaration's body")
    if stripped.endswith("}"):
        return "it follows a closed block; there is no statement to attach it to"
    return (f"the line before it ({stripped[:40]!r}) is not a control statement or a "
            f"function signature")


def attach_braces(text: str) -> Attached:
    """Join every block-opening brace to the line of its statement.

    A brace alone on a line (``if (x)\\n{``), and a brace that opens a block and carries
    its first statement or control statement inline (``do\\n{ Xl = ...;``, ``for (i...)\\n
    { for (j...``), moves up to the statement it belongs to: ``if (x) {``, ``do { Xl =
    ...;``.  A ``} else {`` already reads that way and is left alone.

    The pass refuses a site rather than guessing: a brace after a declaration (``int a;
    \\n{``), after a closed block, after a preprocessor directive, a blank line between the
    statement and its brace, an aggregate-initializer row (``{ .x = 0, ... }``), and a
    block whose first statement is a declaration.  Those are reported in ``skipped`` with
    the line the source spells them on.  Attaching never changes the token stream, but it
    deletes lines, so the caller's acceptance is the tidy's: adoption, ``.text``
    byte-identical, ``.debug``/``.line`` retail's.
    """
    if not text:
        return Attached(text, 0, ())
    newline = "\r\n" if "\r\n" in text else "\n"
    output: list[str] = []
    joined = 0
    skipped: list[tuple[int, str]] = []
    for number, line in enumerate(text.split(newline), 1):
        match = re.fullmatch(r"\{(?:\s+(.*))?", line.strip())
        if match is None:
            output.append(line)
            continue
        remainder = (match.group(1) or "").strip()
        previous = output[-1] if output else None
        if previous is None or not _block_statement_header(previous):
            skipped.append((number, _skip_reason(previous)))
            output.append(line)
            continue
        if remainder and _carries_declaration(remainder):
            skipped.append((number, "the block's first statement is a declaration "
                                    f"({remainder[:40]!r}) and keeps its line"))
            output.append(line)
            continue
        tail = f" {remainder}" if remainder else ""
        output[-1] = previous.rstrip() + " {" + tail
        joined += 1
    return Attached(newline.join(output), joined, tuple(skipped))


def tidy(text: str) -> Attached:
    """``text`` stripped and tidied: no comment, one blank line at most, no trailing space.

    Unlike :func:`strip`, this step **deletes lines** and therefore moves every statement
    below a deleted one.  That is the point -- the promotion gate's ``.line`` half is then
    supplied by retail-metadata adoption, which every promoted unit goes through.

    The comments go first (every one, header and notes included), so the leading header
    block no longer needs its own rule: it becomes blank lines and the blank-run collapse
    drops them.  Runs of blank lines collapse to one, with leading blank lines dropped and
    the file ending in exactly one newline.  Trailing spaces and tabs are removed from
    every line (a line that was only spaces therefore becomes blank and joins the run).
    A blank line directly after an opening ``{`` or before a closing ``}`` is dropped
    (:func:`_brace_edge_blanks`): those were ``#line`` placeholders and carry nothing once
    ``.line`` is adopted.  Finally :func:`attach_braces` joins every block-opening brace to
    its statement and reports the sites it refused to join.
    """
    if not text:
        return Attached(text, 0, ())
    _check_splices(text)
    text = strip(text)
    newline = "\r\n" if "\r\n" in text else "\n"

    output: list[str] = []
    for line in text.split(newline):
        line = line.rstrip(" \t\r\f\v")
        if not line:
            if not output or output[-1] == "":
                continue
            output.append("")
        else:
            output.append(line)
    while output and output[-1] == "":
        output.pop()
    edge = set(_brace_edge_blanks(output))
    if edge:
        output = [line for number, line in enumerate(output, 1) if number not in edge]
    return attach_braces(newline.join(output) + newline)


def collapse(text: str) -> str:
    """The text half of :func:`tidy`; the brace-attach result is discarded."""
    return tidy(text).text


def record_counts(placed) -> tuple:
    """``((function, emitted .line record count), ...)`` from a placement.

    A DWARF 1 statement record is 10 bytes (``line, column, address delta`` plus a
    terminator), so each function's emitted ``.line`` block size divides by ten.  This is
    the measure the tidy must preserve: the layout encoded *which statements share a
    line*, and a rewrite that separates or joins two statements changes the count.
    """
    return tuple((label, emitted // 10)
                 for label, chunk, emitted, _pinned in placed.sizes if chunk == ".line")


def compare_grouping(before, after, what: str = "tidied") -> None:
    """Require the edit to leave every function's ``.line`` record count equal."""
    counts = record_counts(before)
    current = dict(record_counts(after))
    changed = [(label, count, current.get(label)) for label, count in counts
               if current.get(label) != count]
    if not changed:
        return
    detail = "; ".join(f"{label} {was} -> {now}"
                       for label, was, now in changed)
    raise Refused(
        None,
        f"the {what} source changes which statements share a line: {detail} record(s) "
        f"before and after; the directive grouping did not survive, refusing to write it")


def compare(before, after, what: str = "stripped") -> None:
    """Require the three promotion parts to be byte-identical, or raise :class:`Refused`."""
    from toolchain import compile as cc

    for part in ("text", "debug", "line"):
        left, right = getattr(before, part), getattr(after, part)
        if left == right:
            continue
        at = cc._first_difference(left, right)
        raise Refused(
            None,
            f"the {what} source does not compile to the same {part}: "
            f"0x{len(left):X} bytes against 0x{len(right):X}, first difference at "
            f"0x{at:X}; refusing to write it")


def verify(tu, original: bytes, rewritten: bytes, target, *, tidy: bool = False,
           joins: int = 0):
    """Compile both spellings under the unit's recorded pair and compare the three parts.

    ``tu`` is the :class:`toolchain.compile.Tu`, ``target`` the configured target whose
    ``tu_builds`` row supplies the pair.  A different length or byte raises
    :class:`Refused` and the caller writes nothing.  Returns the before/after placements
    for their sizes.

    ``tidy`` is :func:`tidy`'s acceptance, which is stricter because the tidy moves lines:
    ``.text`` must be byte-identical, and the resulting ``.debug`` and ``.line`` must both
    be **retail's** bytes -- which the adoption step proves and substitutes rather than the
    tool assuming it.

    ``joins`` is how many block braces :func:`attach_braces` joined.  Blank-run collapse
    and header shrink must move line *numbers* only, so their result is held to
    :func:`compare_grouping`; a brace join deliberately shares one line between statements
    and therefore changes the emitted ``.line`` record count, which adoption then replaces
    wholesale, so the grouping check would refuse a faithful rewrite.

    ``rewritten`` is also held to :func:`require_no_comments`: a rewrite that still carries
    a comment (a kept header, a ``/*!`` note) is refused before anything is compiled.
    """
    from toolchain import compile as cc
    from toolchain import fetch

    require_no_comments(rewritten.decode("latin-1"), "rewritten source")
    pair = target.build_pair(tu.file)
    if pair is None:
        raise Refused(None, f"{tu.file} has no recorded compiler pair in tu_builds; measure "
                            f"it with tools/toolchain/select_build.py before stripping it")
    compiler, flags = pair
    manifests = cc.Manifests(target)
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    command = shlex.split(flags)
    normalise = False
    adopt = True
    with tempfile.TemporaryDirectory(prefix="strip-comments-") as scratch:
        try:
            before = cc._place_source(tu, manifests, compiler_dir, wibo, command, original,
                                      pathlib.Path(scratch) / "before.mw.o", normalise, adopt)
        except cc.Unusable as exc:
            raise Refused(None, f"the source as committed does not verify under its "
                                f"recorded pair ({exc}); nothing was written")
        try:
            after = cc._place_source(tu, manifests, compiler_dir, wibo, command, rewritten,
                                     pathlib.Path(scratch) / "after.mw.o", normalise, adopt)
        except cc.Unusable as exc:
            raise Refused(None, f"the edited source does not verify under its recorded "
                                f"pair ({exc}); refusing to write it")
    compare(before, after, "tidied" if tidy else "stripped")
    if tidy:
        # The layout encoded which statements share a line.  Blank-run collapse and header
        # shrink must move line *numbers* only: every function's record count stays equal,
        # which is what proves no two statements were joined or separated.  A brace join
        # is the one deliberate exception -- it puts two statements on one line, the
        # emitted .line count drops, and adoption supplies retail's chunk whole.
        if not joins:
            compare_grouping(before, after)
        # The tidy's claim is stronger than "unchanged": the three parts it leaves are
        # retail's.  Adoption returns retail's chunk and line, and this states the
        # acceptance in the tool's own terms.
        want = cc.retail_bytes(tu, target.elf, text_size=len(after.text))
        for part in ("text", "debug", "line"):
            got, expected = getattr(after, part), want[part]
            if got == expected:
                continue
            at = cc._first_difference(got, expected)
            raise Refused(
                None,
                f"the tidied source's {part} is not retail's: 0x{len(got):X} bytes against "
                f"0x{len(expected):X}, first difference at 0x{at:X}; refusing to write it")
    return before, after


def _display(path) -> str:
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _report_attached(display: str, attached: "Attached") -> None:
    """Print the brace-attach tally and every site the pass refused to join."""
    print(f"strip_comments.py: {display}: {attached.joined} block-opening brace(s) attached")
    for line, reason in attached.skipped:
        print(f"strip_comments.py: {display}: line {line}: brace not attached -- {reason}")


def _promoted_source(source: pathlib.Path, target):
    """The ``tu_builds`` key for ``source``, or None when it is not a promoted unit.

    ``--check`` asks this one question, so it reads ``tu_builds`` rather than building the
    target's manifests.  The key is the repo-relative path, which is the row's ``file``
    spelling and the same name :func:`_unit` resolves the compiled unit from.
    """
    try:
        relative = source.resolve().relative_to(REPO_ROOT).as_posix()
    except ValueError:
        return None
    return relative if target.build_pair(relative) is not None else None


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
    parser = argparse.ArgumentParser(prog="strip_comments.py",
                                     description=__doc__.splitlines()[0])
    parser.add_argument("source", help="the C file whose comments to strip")
    parser.add_argument("--target", default=None,
                        help="the target whose manifests and tu_builds name the unit "
                             "(default: this tree's configured target)")
    parser.add_argument("--check", action="store_true",
                        help="write nothing and fail if the file still carries a comment or, "
                             "unless it is a promoted source (whose blank lines inside a "
                             "brace are the line numbers themselves), a blank line directly "
                             "inside a brace (the gate that keeps a promoted source clean)")
    parser.add_argument("--collapse", action="store_true",
                        help="strip every comment, then tidy the layout: drop the blank "
                             "lines the header and notes leave, one blank line at most, no "
                             "trailing whitespace, and every block-opening brace joined to "
                             "the line of its statement; moves statement lines, which "
                             "--adopt-retail-meta covers")
    parser.add_argument("--no-verify", action="store_true",
                        help="layout-only edit for a file that is not a promotion unit; "
                             "refused for a unit that has a recorded pair")
    return parser


def main(argv=None) -> int:
    from config import targets

    args = _parser().parse_args(argv)
    source = pathlib.Path(args.source).expanduser()
    try:
        target = targets.get(args.target) if args.target else targets.get(targets.DEFAULT)
    except targets.UnknownTarget as exc:
        print(f"strip_comments.py: error: {exc}", file=sys.stderr)
        return 2
    if not source.is_file():
        print(f"strip_comments.py: error: {source} does not exist", file=sys.stderr)
        return 2
    original = source.read_bytes()
    text = original.decode("latin-1")       # one byte <-> one character: exact round trip

    attached = None
    if args.collapse:
        try:
            attached = tidy(text)
        except Refused as exc:
            print(f"strip_comments.py: {_display(source)}: {exc}", file=sys.stderr)
            return 1
        rewritten = attached.text
    else:
        try:
            rewritten = strip(text)
        except Refused as exc:
            print(f"strip_comments.py: {_display(source)}: {exc}", file=sys.stderr)
            return 1

    # The contract this tool exists to enforce: a promoted source carries no comment.  In
    # --check the file on disk is the thing being checked (nothing is written), so a
    # comment still in it fails; otherwise the bytes about to be written are held to it.
    try:
        if args.check:
            require_no_comments(text, _display(source))
        else:
            require_no_comments(rewritten, "rewritten source")
    except Refused as exc:
        print(f"strip_comments.py: {_display(source)}: {exc}", file=sys.stderr)
        return 1

    if args.check:
        # A comment is never evidence, but a blank line inside a brace is for a promoted
        # unit: its ``.line`` chunk pins the statements to retail's line numbers, so the
        # blank holds one of them.  Any other file has no such evidence, so it is held to
        # the tidy layout.
        unit = _promoted_source(source, target)
        if not brace_blanks_are_evidence(unit):
            try:
                require_no_brace_padding(text, _display(source))
            except Refused as exc:
                print(f"strip_comments.py: {_display(source)}: {exc}", file=sys.stderr)
                return 1

    if rewritten == text:
        if args.check:
            print(f"strip_comments.py: {_display(source)}: --check: no comments remain; "
                  f"nothing written")
            return 0
        print(f"strip_comments.py: {_display(source)}: nothing to "
              f"{'tidy' if args.collapse else 'strip'}; nothing to do")
        if attached is not None:
            _report_attached(_display(source), attached)
        return 0

    tu = _unit(source, target)
    if tu is None:
        if not args.no_verify:
            print(f"strip_comments.py: {_display(source)}: not a configured promotion unit, "
                  f"so nothing can be compiled before and after; refusing (--no-verify is a "
                  f"layout-only edit)", file=sys.stderr)
            return 2
        print(f"strip_comments.py: {_display(source)}: no recorded pair for this file; "
              f"layout check only, nothing was compiled")
    elif args.no_verify:
        print(f"strip_comments.py: {_display(source)}: this is a promotion unit; its "
              f"{'tidy' if args.collapse else 'strip'} must be compiled before and after "
              f"through the promotion path, so --no-verify is refused", file=sys.stderr)
        return 2
    else:
        try:
            before, after = verify(tu, original, rewritten.encode("latin-1"), target,
                                   tidy=args.collapse,
                                   joins=attached.joined if attached else 0)
        except Refused as exc:
            print(f"strip_comments.py: {_display(source)}: {exc}", file=sys.stderr)
            return 1
        compiler, flags = target.build_pair(tu.file)
        if args.collapse:
            comments = scan(text)
            print(f"strip_comments.py: {_display(source)}: tidied: "
                  f"{len(comments)} comment(s) blanked; line count "
                  f"{text.count(chr(10))} -> {rewritten.count(chr(10))}; "
                  f".text 0x{len(after.text):X} byte-identical, .debug "
                  f"0x{len(after.debug):X} and .line 0x{len(after.line):X} retail's "
                  f"under {compiler} {flags}")
            del before
        else:
            removed = sum(1 for before, after in zip(text, rewritten) if before != after
                          and before not in "\r\n")
            comments = scan(text)
            touched = len({_line_of(text, offset)
                           for comment in comments
                           for offset in range(comment.start, comment.end)
                           if text[offset] not in "\r\n"})
            print(f"strip_comments.py: {_display(source)}: blanked {len(comments)} comment(s) "
                  f"({removed} character(s)) on {touched} line(s); line count "
                  f"{text.count(chr(10))} -> "
                  f"{rewritten.count(chr(10))}; "
                  f".text 0x{len(before.text):X}, .debug 0x{len(before.debug):X}, "
                  f".line 0x{len(before.line):X} bytes under {compiler} {flags} -- "
                  f"byte-identical")
            del after

    if args.check:
        print(f"strip_comments.py: {_display(source)}: --check: no comments remain; "
              f"nothing written")
        return 0
    if attached is not None:
        _report_attached(_display(source), attached)
    source.write_bytes(rewritten.encode("latin-1"))
    print(f"strip_comments.py: {_display(source)}: written")
    return 0


if __name__ == "__main__":
    sys.exit(main())
