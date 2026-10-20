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

Two classes of comment survive, by policy:

* **the leading header block** -- the first comment at the top of the file (only whitespace
  before it).  For a ``//`` header, consecutive ``//`` lines are part of the block; a blank
  line ends it.  This is the file's provenance note; it is kept whole, marker or not.
* **a marked comment** -- one whose opener is immediately followed by ``!``, i.e. ``/*!``
  or ``//!``.  The marker is the author's decision that the note is load-bearing (a magic
  constant, a statement packing that must not be "fixed", an epilogue that owns no
  statement).  An unmarked comment is blanked; marking it is how a note is converted into
  a kept one.

The lexer respects ``"..."`` strings, ``'...'`` character literals and backslash escapes, so
a ``//`` or ``/*`` inside a string is code and is left alone.  It refuses rather than guesses
when the file's comment structure is not well formed:

* an unterminated ``/*`` comment, a stray ``*/`` outside a comment, an unterminated string or
  character literal;
* a line that ends in a backslash continuation -- C splices such a line before tokenising,
  so a "comment" can swallow the line after it and blanking it would change the program
  text the compiler sees.

Usage::

    python3 tools/units/strip_comments.py src/sys/sys_scf.c
    python3 tools/units/strip_comments.py --check src/sys/sys_scf.c

For a file that is not a configured promotion unit there is nothing to compile; such a file
is handled only with ``--no-verify`` (a layout-only edit) and the tool says so.  Exit codes:
0 stripped (or nothing to do), 1 refused, 2 unusable invocation or input.
"""

from __future__ import annotations

import argparse
import pathlib
import shlex
import sys
import tempfile
from typing import NamedTuple

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

#: The characters that make up a kept header's ``//`` continuation.  A blank line, code or
#: a block comment between two ``//`` lines ends the header block.
_LINE_GAP = ("\n", "\r\n")


class Comment(NamedTuple):
    """One comment token as the source spells it."""

    start: int          # offset of the opener
    end: int            # offset just past the closer (past the line feed for ``//``)
    kind: str           # "line" or "block"
    keep: bool          # the header block or a ``!``-marked note


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
    """Every comment in ``text``, in order, with the header block and markers marked.

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

    header_end = _header_end(text, found)
    comments = []
    for item in found:
        opener = text[item["start"]:item["start"] + 3]
        marker = opener.startswith("//!") or opener.startswith("/*!")
        in_header = header_end is not None and item["start"] < header_end
        comments.append(Comment(item["start"], item["end"], item["kind"],
                                keep=marker or in_header))
    return tuple(comments)


def _header_end(text: str, found: list) -> int | None:
    """The offset just past the leading header block, or None when the file has none."""
    if not found:
        return None
    index = 0
    while index < len(text) and text[index] in " \t\r\n":
        index += 1
    first = found[0]
    if first["start"] != index:
        return None
    if first["kind"] == "block":
        return first["end"]
    # A ``//`` header is the run of consecutive ``//`` lines that starts the file.
    end = first["end"]
    previous = first
    for item in found[1:]:
        if item["kind"] != "line":
            break
        if text[previous["end"]:item["start"]] not in _LINE_GAP:
            break
        end = item["end"]
        previous = item
    return end


def strip(text: str) -> str:
    """``text`` with every comment but the header and ``!``-marked notes blanked.

    Removed characters become spaces; newlines (and carriage returns) are kept, so the
    file has the same number of lines and every statement keeps its line number.  The
    non-comment bytes are copied verbatim.
    """
    _check_splices(text)
    comments = scan(text)
    output = list(text)
    for comment in comments:
        if comment.keep:
            continue
        for offset in range(comment.start, comment.end):
            if output[offset] not in "\r\n":
                output[offset] = " "
    stripped = "".join(output)
    if stripped.count("\n") != text.count("\n"):
        raise Refused(None, "internal error: stripping changed the line count")
    return stripped


def compare(before, after) -> None:
    """Require the three promotion parts to be byte-identical, or raise :class:`Refused`."""
    from toolchain import compile as cc

    for part in ("text", "debug", "line"):
        left, right = getattr(before, part), getattr(after, part)
        if left == right:
            continue
        at = cc._first_difference(left, right)
        raise Refused(
            None,
            f"the stripped source does not compile to the same {part}: "
            f"0x{len(left):X} bytes against 0x{len(right):X}, first difference at "
            f"0x{at:X}; refusing to write it")


def verify(tu, original: bytes, rewritten: bytes, target):
    """Compile both spellings under the unit's recorded pair and compare the three parts.

    ``tu`` is the :class:`toolchain.compile.Tu`, ``target`` the configured target whose
    ``tu_builds`` row supplies the pair.  A different length or byte raises
    :class:`Refused` and the caller writes nothing.  Returns the before/after placements
    for their sizes.
    """
    from toolchain import compile as cc
    from toolchain import fetch

    pair = target.build_pair(tu.file)
    if pair is None:
        raise Refused(None, f"{tu.file} has no recorded compiler pair in tu_builds; measure "
                            f"it with tools/toolchain/select_build.py before stripping it")
    compiler, flags, state = pair
    manifests = cc.Manifests(target)
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    command = shlex.split(flags)
    normalise = state is True
    adopt = state == "adopt"
    with tempfile.TemporaryDirectory(prefix="strip-comments-") as scratch:
        before = cc._place_source(tu, manifests, compiler_dir, wibo, command, original,
                                  pathlib.Path(scratch) / "before.mw.o", normalise, adopt)
        after = cc._place_source(tu, manifests, compiler_dir, wibo, command, rewritten,
                                 pathlib.Path(scratch) / "after.mw.o", normalise, adopt)
    compare(before, after)
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
    parser = argparse.ArgumentParser(prog="strip_comments.py",
                                     description=__doc__.splitlines()[0])
    parser.add_argument("source", help="the C file whose comments to strip")
    parser.add_argument("--target", default=None,
                        help="the target whose manifests and tu_builds name the unit "
                             "(default: this tree's configured target)")
    parser.add_argument("--check", action="store_true",
                        help="run the strip and its compile check, write nothing")
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

    try:
        stripped = strip(text)
    except Refused as exc:
        print(f"strip_comments.py: {_display(source)}: {exc}", file=sys.stderr)
        return 1

    if stripped == text:
        print(f"strip_comments.py: {_display(source)}: no comments to strip; nothing to do")
        return 0

    removed = sum(1 for before, after in zip(text, stripped) if before != after
                  and before not in "\r\n")
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
        print(f"strip_comments.py: {_display(source)}: this is a promotion unit; its strip "
              f"must be compiled before and after through the promotion path, so --no-verify "
              f"is refused", file=sys.stderr)
        return 2
    else:
        try:
            before, after = verify(tu, original, stripped.encode("latin-1"), target)
        except Refused as exc:
            print(f"strip_comments.py: {_display(source)}: {exc}", file=sys.stderr)
            return 1
        compiler, flags, _state = target.build_pair(tu.file)
        comments = scan(text)
        blanked = [comment for comment in comments if not comment.keep]
        touched = len({_line_of(text, offset)
                       for comment in blanked
                       for offset in range(comment.start, comment.end)
                       if text[offset] not in "\r\n"})
        print(f"strip_comments.py: {_display(source)}: blanked {len(blanked)} comment(s) "
              f"({removed} character(s)) on {touched} line(s); kept "
              f"{len(comments) - len(blanked)}; line count {text.count(chr(10))} -> "
              f"{stripped.count(chr(10))}; "
              f".text 0x{len(before.text):X}, .debug 0x{len(before.debug):X}, "
              f".line 0x{len(before.line):X} bytes under {compiler} {flags} -- byte-identical")
        del after

    if args.check:
        print(f"strip_comments.py: {_display(source)}: --check, nothing written")
        return 0
    source.write_bytes(stripped.encode("latin-1"))
    print(f"strip_comments.py: {_display(source)}: written")
    return 0


if __name__ == "__main__":
    sys.exit(main())
