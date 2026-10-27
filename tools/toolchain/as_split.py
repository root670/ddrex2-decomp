#!/usr/bin/env python3
"""as_split.py -- the ninja ``as`` rule: assemble one splat split for the pinned layout.

The rule used to be a shell pipeline::

    cpp -Iinclude $in -o - | sed -E '/^[[:space:]]*\\.align[[:space:]]/d' | \\
        mips-linux-gnu-as -Iasm/include --no-pad-sections -EL -march=5900 -mabi=eabi -o $out

Three of those four programs do not exist on Windows, where ninja starts an edge with
``CreateProcess`` -- no shell, so neither ``cpp`` nor ``sed`` nor even a ``|`` is available --
and neither of the two filters was doing anything the split needs: no split in this tree
carries a preprocessor directive (``cpp``'s whole contribution is the ``# 1 "file"`` marker
comments gas reads as comments), and the one ``sed`` rule drops the ``.align`` lines gas would
otherwise pad to.  So this program applies that one filter and runs ``as`` itself: one command
line, no shell features, the same object bytes -- ``tests/test_configure.py`` pins the
equivalence against the old pipeline, split by split.

``.align`` is dropped on purpose and from the *stream*, never from a split: splat emits it for
alignment that is true in absolute VA terms, so in an object that starts at a function's own
address it inserts zero bytes the retail bytes already carry explicitly -- ``configure.py``'s
note above ``AS_RULE`` has the measurement (19 splits assemble 4 bytes too long while their
``.align`` lines survive).
"""

from __future__ import annotations

import argparse
import pathlib
import re
import subprocess
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]

#: The assembler invocation the pinned layout needs; identical to the old rule's.
AS = ("mips-linux-gnu-as", "-Iasm/include", "--no-pad-sections", "-EL", "-march=5900",
      "-mabi=eabi")

#: ``sed -E '/^[[:space:]]*\.align[[:space:]]/d'``, on bytes: a line whose first non-space word
#: is ``.align`` is dropped, and nothing else is touched.  ``[[:space:]]`` and ``\\s`` agree on
#: the classes gas splits use (space, tab, form feed, vertical tab, CR, LF).
ALIGN = re.compile(rb"^[ \t\r\n\f\v]*\.align[ \t\r\n\f\v]")

#: A line only a preprocessor could honour.  No split in this tree has one; if one ever appears,
#: gas would read it as a comment and assemble the split short, so it is refused instead.
DIRECTIVE = re.compile(rb"^[ \t\r\n\f\v]*#")


class AssemblyError(Exception):
    """The split could not be assembled; the message names the file and the reason."""


def filtered(text: bytes) -> bytes:
    """``text`` without its ``.align`` lines, byte for byte what the old ``sed`` passed on."""
    return b"".join(line for line in text.splitlines(keepends=True)
                    if not ALIGN.match(line))


def assemble(split, out) -> None:
    """Assemble ``split`` into ``out`` with the pinned ``as`` flags, as the ninja edge does."""
    # The edge spells paths repo-relative (ninja runs in the repo root); `as` is given the
    # same spelling, so both are read from here rather than from the caller's directory.
    source = pathlib.Path(split)
    if not source.is_absolute():
        source = REPO_ROOT / source
    try:
        text = source.read_bytes()
    except OSError as exc:
        raise AssemblyError(f"{split}: {exc}") from exc
    for number, line in enumerate(text.splitlines(), start=1):
        if DIRECTIVE.match(line):
            raise AssemblyError(
                f"{split}:{number}: a preprocessor directive ({line.strip()[:40]!r}); this "
                f"rule runs no preprocessor, so the split cannot be assembled here")
    # `as` reads stdin when it is given no input file, which is how the old pipeline fed it:
    # the filtered text arrives the same way, with stdout/stderr left to ninja.
    proc = subprocess.run([*AS, "-o", str(out)], cwd=REPO_ROOT, input=filtered(text))
    if proc.returncode != 0:
        raise AssemblyError(f"{split}: mips-linux-gnu-as exited {proc.returncode}")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("split", help="the split to assemble")
    parser.add_argument("-o", "--object", required=True, dest="object",
                        help="the object to write")
    args = parser.parse_args(argv)
    try:
        assemble(args.split, args.object)
    except AssemblyError as exc:
        print(f"as_split.py: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
