#!/usr/bin/env python3
"""The two objects ``ddr diff`` compares: retail's bytes for one symbol, and ours.

``./ddr verify --tu <tu>`` gates a whole translation unit on three parts, so iterating on
*one* function needs a per-function number.  ``objdiff-cli`` gives one, but only if the two
sides it is handed can be paired, and the split cannot be the target side of that pairing:
splat writes a ``jal`` to a name the object does not define, so the split's call renders as
``jal sceScfGetDateNotation`` (an unresolved symbol, *address zero*) while our object's call
carries the resolved retail address -- and objdiff counts the two as a mismatched operand.
The score for a byte-identical function lands at ~99.2%, for a reason that has nothing to do
with the code: the depression is an artefact of how a split spells a relocation.

So the target side is built from the *retail image* instead:

    retail(symbol, address, size, elf)  ->  build/diff/<symbol>.o

a relocatable object whose ``.text`` is exactly the bytes ``orig/<elf>`` holds at
``[address, address + size)`` -- read through the ELF's program headers, so a byte in the
loadable segment is copied verbatim -- with the symbol named exactly ``symbol`` (STT_FUNC,
size ``size``) so objdiff pairs it against the object under edit.  No relocations: our
compiled objects are fully placed (``compile.py`` resolves every address through the
oracle's manifests), so both sides then compare *addresses*, and a resolved call matches a
resolved call.  And no ``.NON_MATCHING`` alias: an object carrying one has every symbol of
that name ignored by objdiff (``objdiff-core/src/arch/mips.rs``: on the base side the alias
also ignores the plain name), which is precisely the "score it never computed" the verb used
to print.

The base side is the object under edit:

* a promoted unit -- the ``cc`` edge's object, read out of ``build.ninja``, unchanged;
* an unpromoted unit -- ``split(symbol, split_object)``, the same bytes splat's ``as``
  produced for that function, emitted the same way (plain name, no alias).  This is the one
  place a *derived* stand-in is needed: the split object itself is not scorable, so
  ``ddr diff`` on a unit with no C would print no comparison at all.  What is compared is
  then retail's bytes against the split's own bytes -- an honest number (the split's
  unresolved calls show up as their own mismatched instructions) and, because the verb
  prints both sides with their provenance, never mistakable for a C object.

The same construction serves a whole *unit*: ``objdiff-cli report generate`` measures a unit
against one target object, and a promoted unit's target object must be the unit's retail
bytes under the unit's own function names -- one object, not one per split.  ``unit(...)``
below builds it: ``.text`` is the retail region the promotion fills (``split_extent``), and
every function is a ``STT_FUNC`` symbol at its retail offset in that region.  A report over
that object and the promoted unit's ``cc`` object then counts code the way the gates count
it: a byte-identical function is 32/32 matched, not 99.2%.  An unpromoted unit keeps the
split object as its target -- retail's bytes as splat spelled them, which is all there is to
compare -- with a ``null`` base, so its bytes count as un-matched rather than as a score.

Where the objects live: the build's generated output directory.  ``build/diff/**`` is
gitignored, is named by no ninja edge, appears in no ``ld`` script, and is not part of the
file's tail, so neither the link nor G1 -- which compares ``out/<elf>`` with the retail ELF
-- can see it.  ``tests/diff/test_basis.py`` asserts exactly that about the generated graph.
"""

from __future__ import annotations

import pathlib
import struct
import sys

HERE = pathlib.Path(__file__).resolve().parent
REPO_ROOT = HERE.parents[1]
for extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT)):
    # `python3 tools/diff/basis.py`-style runs and `ddr`, which imports this by package name.
    if extra not in sys.path:
        sys.path.insert(0, extra)

import elf  # noqa: E402  the vendored 32-bit little-endian MIPS reader


class Unusable(Exception):
    """The bytes of a symbol cannot be emitted as an object (the caller reports it)."""


#: Where the emitted objects go: the build's generated output tree.  Not ``asm/**`` (splat's
#: splits, which G1's link is built from) and not ``out/**`` (the built image), because an
#: object derived from the retail image must never be able to enter either.
DIRECTORY = REPO_ROOT / "build" / "diff"

# The ELF this file writes: 32-bit little-endian ET_REL for the PS2's EE.
ET_REL, EM_MIPS = 1, 8
SHT_PROGBITS, SHT_SYMTAB, SHT_STRTAB = 1, 2, 3
SHF_ALLOC, SHF_EXECINSTR = 0x2, 0x4
STB_LOCAL, STB_GLOBAL = 0, 1
STT_FUNC, STT_SECTION = 2, 3
EHDR_SIZE, SHDR_SIZE, SYM_SIZE = 52, 40, 16


def object_bytes(text: bytes, symbol: str, size: int | None = None, flags: int = 0) -> bytes:
    """A relocatable object whose ``.text`` is ``text``, under the name ``symbol``.

    Three sections beyond ``.text`` itself (``.symtab``, ``.strtab``, ``.shstrtab``) and one
    symbol beyond the ``.text`` section symbol: no ``.data``, no ``.debug``/``.line``, no
    relocations, and no ``.NON_MATCHING`` alias -- everything a reader of the diff would
    otherwise have to be told about.  ``size`` is the symbol's own size and must be the
    length of ``text``: the object holds one function and nothing else, so a size that
    disagreed with the bytes would describe a different function.
    """
    if size is None:
        size = len(text)
    if size != len(text):
        raise Unusable(f"{symbol}: a {size}-byte symbol cannot be {len(text)} bytes of .text")
    return object_with_symbols(text, [(symbol, 0, size)], flags)


def object_with_symbols(text: bytes, symbols, flags: int = 0) -> bytes:
    """The same object, with one ``STT_FUNC`` symbol per ``(name, offset, size)`` in it.

    ``offset`` is into ``.text``, so the symbols are exactly where their bytes are.  The
    table is written in offset order (ties broken by name) so the object is a function of the
    facts alone: two runs write the same bytes, and a symbol table that reordered itself
    between runs would make every diff of the emitted objects noise.
    """
    if not text:
        raise Unusable("an object with no .text cannot carry a function")
    rows = []
    seen = set()
    for name, offset, size in symbols:
        if not name or "\0" in name:
            raise Unusable(f"{name!r} is not a symbol name an object can carry")
        if name in seen:
            raise Unusable(f"{name}: a symbol table cannot carry the name twice")
        if not isinstance(size, int) or size <= 0:
            raise Unusable(f"{name}: a symbol of size {size!r} has no bytes to diff")
        if not 0 <= offset or offset + size > len(text):
            raise Unusable(f"{name}: {size} bytes at offset {offset} run past the "
                           f"{len(text)}-byte .text")
        seen.add(name)
        rows.append((offset, name, size))
    if not rows:
        raise Unusable("an object whose symbol table is empty is not a comparison")
    rows.sort()

    shstr = b"\0"
    shstr_offsets = {}
    for name in (".text", ".symtab", ".strtab", ".shstrtab"):
        shstr_offsets[name] = len(shstr)
        shstr += name.encode() + b"\0"
    # Every symbol name at its own offset in .strtab, which starts with the empty string.
    strtab = b"\0"
    name_offsets = {}
    for _offset, name, _size in rows:
        name_offsets[name] = len(strtab)
        strtab += name.encode() + b"\0"

    # .text's own section symbol, then the functions: the local half of the table is the one
    # entry an assembler emits, and `sh_info` below is where the globals start.
    symtab = b"\0" * SYM_SIZE                                        # the null symbol
    symtab += struct.pack("<IIIBBH", 0, 0, 0, (STB_LOCAL << 4) | STT_SECTION, 0, 1)
    for offset, name, size in rows:
        symtab += struct.pack("<IIIBBH", name_offsets[name], offset, size,
                              (STB_GLOBAL << 4) | STT_FUNC, 0, 1)

    # (name, type, flags, align, entsize, data, link, info) -- section indexes are the
    # position in this list, one-based.
    sections = [(".text", SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR, 16, 0, text, 0, 0),
                (".symtab", SHT_SYMTAB, 0, 4, SYM_SIZE, symtab, 3, 2),
                (".strtab", SHT_STRTAB, 0, 1, 0, strtab, 0, 0),
                (".shstrtab", SHT_STRTAB, 0, 1, 0, shstr, 0, 0)]

    body = bytearray()
    headers = []
    for (name, kind, sect_flags, align, entsize, data, link, info) in sections:
        while (EHDR_SIZE + len(body)) % align:
            body += b"\0"
        offset = EHDR_SIZE + len(body)
        headers.append((shstr_offsets[name], kind, sect_flags, 0, offset, len(data), link,
                        info, align, entsize))
        body += data
    while (EHDR_SIZE + len(body)) % 4:
        body += b"\0"
    shoff = EHDR_SIZE + len(body)
    body += struct.pack("<10I", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    for header in headers:
        body += struct.pack("<10I", *header)

    header = (b"\x7fELF\x01\x01\x01" + b"\0" * 9
              + struct.pack("<HHIIIIIHHHHHH", ET_REL, EM_MIPS, 1, 0, 0, shoff, flags,
                            EHDR_SIZE, 0, 0, SHDR_SIZE, len(headers) + 1, len(headers)))
    return header + bytes(body)


def _write(path: pathlib.Path, data: bytes) -> pathlib.Path:
    """``data`` at ``path``, creating the directory; the object is rewritten in place."""
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return path


def retail(symbol: str, address: int, size: int, elf_path, directory=None) -> pathlib.Path:
    """The object whose ``.text`` is ``symbol``'s bytes in the retail image.

    ``address`` and ``size`` come from the target's own ledger/DWARF (the caller resolves
    them); the bytes come from ``elf_path``'s program headers, verbatim.  The object's
    ``e_flags`` are the image's own: the bytes are the image's, so the machine and ABI a
    diff tool reads off them should be the image's too (``as`` additionally sets the
    no-reorder bit on a split, and that changes no verdict -- measured against objdiff-cli
    3.8.2 both values score a byte-identical function at 100%).
    """
    image = elf.Elf(elf_path)
    text = image.read(address, size)
    if len(text) != size:
        raise Unusable(f"{symbol}: 0x{address:08X} is {len(text)} bytes into the image, not "
                       f"the {size} bytes the ledger sizes it at")
    return _write(_path(symbol, directory),
                  object_bytes(text, symbol, size, flags=image.flags))


def unit(functions, elf_path, start: int, end: int, name: str,
         directory=None) -> pathlib.Path:
    """The target object for a whole *unit*: every function's retail bytes, one object.

    ``functions`` is ``[(symbol, address, size)]`` -- the unit's manifest: where retail put
    each function and how long it is.  ``[start, end)`` is the retail region the promotion
    fills (``compile.split_extent``: the unit's splits up to the next one, padding included),
    and the object's ``.text`` is that region byte for byte, read through the image's program
    headers.  Each function is a ``STT_FUNC`` symbol at ``address - start``, so the object
    places the same bytes at the same offsets retail did, and objdiff pairs it by name
    against the ``cc`` object that compiles the unit.

    This is the one object ``objdiff-cli report generate`` needs per promoted unit: its
    target.  Handing it the splits instead is what made a byte-identical function score
    99.2% (a split's ``jal`` names an unresolved symbol -- address zero -- while our object's
    carries the retail address).

    ``name`` is the unit's key as the report spells it (``main/sys_scf``); it becomes the
    object's path (``build/diff/main/sys_scf.unit.o``), which is what ``objdiff.json`` names.
    """
    image = elf.Elf(elf_path)
    if end <= start:
        raise Unusable(f"{name}: the unit's retail region is empty "
                       f"(0x{start:08X}..0x{end:08X}), so it has no bytes to compare")
    text = image.read(start, end - start)
    if len(text) != end - start:
        raise Unusable(f"{name}: 0x{start:08X}..0x{end:08X} is {len(text)} bytes into the "
                       f"image, not the {end - start} the split extent measures")
    rows = []
    for symbol, address, size in functions:
        if address < start or address + size > end:
            raise Unusable(f"{symbol}: 0x{address:08X}+0x{size:X} is outside the unit's "
                           f"retail region 0x{start:08X}..0x{end:08X}")
        rows.append((symbol, address - start, size))
    if not rows:
        raise Unusable(f"{name}: a unit with no functions has no target object")
    return _write(unit_path(name, directory), object_with_symbols(text, rows,
                                                                flags=image.flags))


def unit_path(name: str, directory=None) -> pathlib.Path:
    """Where ``unit`` writes ``name``'s target object: ``build/diff/<name>.unit.o``."""
    return _path(name, directory, suffix=".unit")


def split(symbol: str, split_object, directory=None) -> pathlib.Path:
    """Our build's own bytes for ``symbol``, out of its split object, under the plain name.

    The same bytes ``as`` wrote (the split's ``.text`` at the symbol's own offset) with the
    one thing removed that makes the split unscorable: its ``<symbol>.NON_MATCHING`` alias.
    Its relocations are not carried either -- they are what the split spells an unresolved
    call with, and a diff of retail's bytes against ours must compare *bytes*.
    """
    image = elf.Elf(split_object)
    found = next((s for s in image.symbols if s.name == symbol and s.type == STT_FUNC), None)
    if found is None or found.shndx == 0:
        raise Unusable(f"{split_object}: the split defines no function {symbol!r}")
    section = image.sections[found.shndx]
    if section.type != SHT_PROGBITS:
        raise Unusable(f"{symbol}: the split's symbol is not in a section of bytes")
    start = section.offset + found.value
    text = image.data[start:start + found.size]
    if len(text) != found.size or not found.size:
        raise Unusable(f"{symbol}: the split's {found.size}-byte symbol runs past its section")
    return _write(_path(symbol, directory, suffix=".split"), object_bytes(text, symbol,
                                                                         found.size,
                                                                         flags=image.flags))


def scored(report: dict, symbol: str) -> bool:
    """Whether ``report`` holds a match percentage for ``symbol`` on *both* sides.

    ``objdiff-cli``'s JSON always lists the symbols it read, and a symbol it did not pair
    carries no ``match_percent`` at all.  A percentage on one side only, or on neither, is
    the old failure mode wearing a new hat: the verb must refuse to print a number it did
    not measure (a base object that does not define the symbol is the case that produces it).
    """
    for side in ("left", "right"):
        found = next((s for s in (report.get(side) or {}).get("symbols") or []
                      if s.get("name") == symbol), None)
        if found is None or found.get("match_percent") is None:
            return False
    return True


def _path(symbol: str, directory, suffix: str = "") -> pathlib.Path:
    """Where one symbol's emitted object lives, inside the build's generated outputs."""
    return pathlib.Path(directory or DIRECTORY) / f"{symbol}{suffix}.o"
