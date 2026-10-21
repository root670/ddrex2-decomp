#!/usr/bin/env python3
"""The one ``.debug`` deviation a promotion may carry: the anonymous-type DIE order.

Retail's Metrowerks DWARF 1 records anonymous aggregates as ``@anonN``, and ``N`` is the
compiler's emission counter.  The numbering depends on the whole translation unit's
declaration walk -- swapping two ``#include`` lines permutes it -- and retail's own order is
not a C declaration order, so a header cannot reproduce it for every unit
(``docs/unit-work.md``, "anonymous-type DIE order in a promoted unit").

The promotion gate therefore accepts a unit whose emitted debug chunk is **set-equal** to
retail's: the same chunk length, the same DIE count, and the same multiset of DIEs compared
structurally, with only ``@anonN`` normalised.  This module is that comparison and nothing
else -- the caller owns the ``.text``/``.line`` condition and the decision to place retail's
chunk in the image.

A DIE's signature is ``(tag, parent-shape, attributes)``:

* strings have ``@anonN`` replaced by ``@anon``;
* reference-valued attributes (form 2) are replaced by a shallow description of their
  target -- tag, normalised name, byte size, fundamental type -- so a permuted index does
  not move the reference out of the set;
* ``AT_sibling`` is dropped, because it is a positional offset and the class under test
  moves positions;
* the parent's shape (tag, normalised name, size, and its direct children's brief
  descriptions) keeps a member attached to its container.

The DIE's own record length is deliberately *not* in the signature: ``@anon3`` and
``@anon10`` are different name lengths, and a permutation that swaps them is the class this
gate accepts.  What condition 2 pins instead is the whole chunk's byte length and its DIE
count, both of which a permutation preserves.
"""

from __future__ import annotations

import collections
import re
import struct

AT_SIBLING = 0x0012
AT_NAME = 0x0038
AT_BYTE_SIZE = 0x00B6
AT_FUND_TYPE = 0x0055
AT_LOCATION = 0x0023
AT_SUBSCR_DATA = 0x00A3
AT_MOD_U_D_TYPE = 0x0083
#: The MW attribute measured as a block of 4-byte DIE references (one per element).
AT_2303 = 0x2303

TAG = {
    0x0001: "array_type", 0x0002: "class_type", 0x0003: "entry_point",
    0x0004: "enumeration_type", 0x0005: "formal_parameter", 0x0006: "global_subroutine",
    0x0007: "global_variable", 0x000A: "label", 0x000B: "lexical_block",
    0x000C: "local_variable", 0x000D: "member", 0x000F: "pointer_type",
    0x0010: "reference_type", 0x0011: "compile_unit", 0x0012: "string_type",
    0x0013: "structure_type", 0x0014: "subroutine", 0x0015: "subroutine_type",
    0x0016: "typedef", 0x0017: "union_type", 0x0018: "unspecified_parameters",
    0x0019: "variant", 0x001A: "common_block", 0x001B: "common_inclusion",
    0x001C: "inheritance", 0x001D: "inlined_subroutine", 0x001E: "module",
    0x001F: "ptr_to_member_type", 0x0020: "set_type", 0x0021: "subrange_type",
    0x0022: "with_stmt", 0x4080: "MW_overlay",
}

_ANON = re.compile(r"@anon\d+")
_U16 = struct.Struct("<H").unpack_from
_U32 = struct.Struct("<I").unpack_from
_U64 = struct.Struct("<Q").unpack_from


class Unparseable(ValueError):
    """The bytes are not a DWARF 1 DIE sequence this gate can compare."""


class Die:
    __slots__ = ("offset", "length", "tag", "attrs", "parent", "children")

    def __init__(self, offset, length, tag, attrs):
        self.offset = offset          # absolute .debug offset (chunk base + local)
        self.length = length
        self.tag = tag
        self.attrs = attrs
        self.parent = None
        self.children = []

    @property
    def name(self):
        return self.attrs.get(AT_NAME)


#: The conditions the caller reports.  Condition 1 (``.text``/``.line`` byte-equal) is not
#: this module's: it has no DIE to name.
LABEL = {
    1: ".text and .line byte-equal",
    2: ".debug length and DIE count",
    3: ".debug DIE multiset",
    4: "unparseable .debug chunk",
}


def _u16(buf, at):
    return _U16(buf, at)[0]


def _u32(buf, at):
    return _U32(buf, at)[0]


def parse(chunk: bytes, base: int = 0) -> list:
    """The DIE sequence of a chunk that lives at ``base`` in ``.debug``.

    ``base`` matters because reference and sibling attributes are absolute section offsets:
    a chunk sliced out of the section still carries them, so a sibling has to be compared
    after subtracting the chunk's base.
    """
    n = len(chunk)
    dies = []
    stack = [(None, n)]
    off = 0
    while off < n:
        while len(stack) > 1 and off >= stack[-1][1]:
            stack.pop()
        if n - off < 4:
            raise Unparseable(f"{n - off} trailing bytes at +0x{off:X}")
        length = _u32(chunk, off)
        if length < 8:                       # null entry: ends a sibling chain
            off += max(length, 4)
            continue
        end = off + length
        if end > n:
            raise Unparseable(f"DIE at +0x{off:X} runs past the chunk")
        attrs = {}
        die = Die(base + off, length, _u16(chunk, off + 4), attrs)
        p = off + 6
        while p < end:
            if p + 2 > end:
                raise Unparseable(f"DIE at +0x{off:X} has a truncated attribute code")
            code = _u16(chunk, p)
            p += 2
            form = code & 0x0F
            if form in (1, 2, 6):
                if p + 4 > end:
                    raise Unparseable(f"DIE at +0x{off:X} has a truncated attribute")
                value = _u32(chunk, p)
                p += 4
            elif form == 8:
                try:
                    stop = chunk.index(b"\0", p, end)
                except ValueError:
                    raise Unparseable(f"DIE at +0x{off:X} has an unterminated string")
                value = chunk[p:stop].decode("latin-1")
                p = stop + 1
            elif form == 5:
                if p + 2 > end:
                    raise Unparseable(f"DIE at +0x{off:X} has a truncated attribute")
                value = _u16(chunk, p)
                p += 2
            elif form in (3, 4):
                width = 2 if form == 3 else 4
                if p + width > end:
                    raise Unparseable(f"DIE at +0x{off:X} has a truncated block")
                size = _u16(chunk, p) if form == 3 else _u32(chunk, p)
                p += width
                if p + size > end:
                    raise Unparseable(f"DIE at +0x{off:X} has a truncated block")
                value = chunk[p:p + size]
                p += size
            elif form == 7:
                if p + 8 > end:
                    raise Unparseable(f"DIE at +0x{off:X} has a truncated attribute")
                value = _U64(chunk, p)[0]
                p += 8
            else:
                raise Unparseable(f"DIE at +0x{off:X}: attribute 0x{code:04X} has "
                                  f"unknown form {form}")
            attrs[code] = value
        if p != end:
            raise Unparseable(f"DIE at +0x{off:X} ends at +0x{p:X}, length says +0x{end:X}")
        die.parent = stack[-1][0]
        if die.parent is not None:
            die.parent.children.append(die)
        dies.append(die)
        sibling = attrs.get(AT_SIBLING)
        if sibling is not None:
            local = sibling - base
            if local > end:
                stack.append((die, min(local, n)))
        off = end
    return dies


def _normalise(value):
    return _ANON.sub("@anon", value) if isinstance(value, str) else value


def _brief(die):
    """A cheap identity for a parent: tag, normalised name, size, and direct children.

    The children are a **sorted** multiset, not a sequence: the compile unit's child order
    is exactly what the anonymous-index class permutes, while a member's position is
    already carried by its ``AT_location`` offset.
    """
    children = tuple(sorted(
        ((child.tag, _normalise(child.name),
          child.attrs.get(AT_BYTE_SIZE), child.attrs.get(AT_FUND_TYPE),
          child.attrs.get(AT_LOCATION)) for child in die.children),
        key=repr))
    return (die.tag, _normalise(die.name), die.attrs.get(AT_BYTE_SIZE),
            die.attrs.get(AT_FUND_TYPE), die.attrs.get(AT_LOCATION), children)


def _target_key(value, by_offset):
    target = by_offset.get(value)
    if target is None:
        return ("outside", value)
    return ("die", target.tag, _normalise(target.name), target.attrs.get(AT_BYTE_SIZE),
            target.attrs.get(AT_FUND_TYPE))


def _form_value(block, p, form):
    """Read one encoded attribute value from a block; ``p`` is past the attribute code."""
    if form in (1, 2, 6):
        return _U32(block, p)[0], p + 4
    if form == 5:
        return _U16(block, p)[0], p + 2
    if form == 8:
        stop = block.index(b"\0", p)
        return block[p:stop].decode("latin-1"), stop + 1
    if form == 3:
        size = _U16(block, p)[0]
        return block[p + 2:p + 2 + size], p + 2 + size
    if form == 4:
        size = _U32(block, p)[0]
        return block[p + 4:p + 4 + size], p + 4 + size
    if form == 7:
        return _U64(block, p)[0], p + 8
    raise ValueError(f"form {form}")


def _subscript_key(block, by_offset):
    """``AT_subscr_data`` as a structure, with its element type's reference normalised.

    The array's element type and a user-defined index type are encoded *inside the block*,
    so comparing the block's bytes verbatim would reject the anonymous-order class: the
    reference names a DIE whose ``@anonN`` offset moved.
    """
    parts = []
    p = 0
    while p < len(block):
        fmt = block[p]
        p += 1
        if fmt == 8:                                  # FMT_ET: element type attribute
            code = _U16(block, p)[0]
            form = code & 0x0F
            value, p = _form_value(block, p + 2, form)
            if form == 2:
                value = _target_key(value, by_offset)
            elif form == 3 and isinstance(value, bytes) and len(value) >= 4:
                # An array of a user-defined type encodes its element as a modifier
                # block: flags, then a 4-byte DIE reference.  The reference names a DIE
                # that moved with the anonymous order, so the raw block is not the
                # element type's identity.
                value = ("mod_u_d", value[:-4],
                         _target_key(_U32(value, len(value) - 4)[0], by_offset))
            parts.append(("et", code, value))
            break
        if fmt & 4:                                   # user-defined index type
            parts.append(("index-ref", _target_key(_U32(block, p)[0], by_offset)))
            p += 4
        else:                                         # fundamental index type
            parts.append(("index-ft", _U16(block, p)[0]))
            p += 2
        for expr in (fmt & 2, fmt & 1):
            if expr:
                size = _U16(block, p)[0]
                parts.append(("bound-expr", block[p + 2:p + 2 + size]))
                p += 2 + size
            else:
                parts.append(("bound", _U32(block, p)[0]))
                p += 4
    return ("subscript", tuple(parts))


def _local_signature(die, by_offset, ignore=None):
    """The DIE's own tag and attributes, without its parent's shape.

    ``ignore`` is a predicate ``(die, code) -> bool`` naming attribute values that are not
    part of the identity being compared.  The metadata-adoption step ignores ``AT_location``
    on locals only: two objects assign the same local to different registers, and the step
    proves the rest of the record is retail's before it adopts the location.  A member's
    ``AT_location`` is an offset, never ignored.
    """
    attrs = []
    for code, value in sorted(die.attrs.items()):
        if code == AT_SIBLING or (ignore is not None and ignore(die, code)):
            continue
        if isinstance(value, str):
            value = _normalise(value)
        if (code & 0x0F) == 2:
            value = _target_key(value, by_offset)
        elif code == AT_SUBSCR_DATA and isinstance(value, bytes):
            try:
                value = _subscript_key(value, by_offset)
            except (ValueError, IndexError, struct.error):
                pass                                  # raw bytes: a refusal, not a crash
        elif code == AT_MOD_U_D_TYPE and isinstance(value, bytes) and len(value) >= 4:
            # Modifier flags, then a user-defined type reference whose DIE moved with the
            # anonymous index.
            value = ("mod_u_d", value[:-4],
                     _target_key(_U32(value, len(value) - 4)[0], by_offset))
        elif (code == AT_2303 and isinstance(value, bytes) and len(value) >= 4
              and len(value) % 4 == 0):
            # A list of DIE references: each word names an object that moved with the DIE
            # order, so the raw bytes are not the attribute's identity.
            value = ("refs", tuple(_target_key(_U32(value, at)[0], by_offset)
                                   for at in range(0, len(value), 4)))
        attrs.append((code, value))
    return (die.tag, tuple(attrs))


def _signature(die, by_offset):
    parent = die.parent
    parent_key = _brief(parent) if parent is not None else None
    return (die.tag, parent_key, _local_signature(die, by_offset)[1])


def _describe(die, base):
    tag = TAG.get(die.tag, f"tag 0x{die.tag:02X}")
    name = die.name
    return f"+0x{die.offset - base:X} {tag}" + (f" {name!r}" if name else "")


def _first_positional_difference(emitted, retail, by_emitted, by_retail, base):
    """The first DIE, in emission order, whose shallow shape is not retail's at that index."""
    for index, die in enumerate(emitted):
        if index >= len(retail):
            return die, "emitted"
        left = (die.tag, die.length, tuple((c, _normalise(v) if isinstance(v, str) else v)
                                           for c, v in sorted(die.attrs.items())
                                           if c != AT_SIBLING))
        other = retail[index]
        right = (other.tag, other.length,
                 tuple((c, _normalise(v) if isinstance(v, str) else v)
                       for c, v in sorted(other.attrs.items()) if c != AT_SIBLING))
        if left != right:
            return die, "emitted"
    if len(retail) > len(emitted):
        return retail[len(emitted)], "retail"
    return None, None


class Outcome:
    """What the four-condition test concluded for one chunk.

    ``ok`` means conditions 2 and 3 passed; the caller still has to have established
    condition 1 (``.text``/``.line`` byte-equal) before accepting, and condition 4 is a
    refusal this object already carries.
    """

    __slots__ = ("ok", "condition", "detail", "die_count", "permuted", "anonymous")

    def __init__(self, ok, condition=0, detail="", die_count=0, permuted=0, anonymous=0):
        self.ok = ok
        self.condition = condition
        self.detail = detail
        self.die_count = die_count
        self.permuted = permuted
        self.anonymous = anonymous

    @property
    def label(self):
        return LABEL.get(self.condition, "unknown")

    @property
    def message(self):
        return f"condition {self.condition} ({self.label}) failed: {self.detail}"


def classify(emitted: bytes, retail: bytes, base: int = 0) -> Outcome:
    """Apply conditions 2 and 3 to a whole unit's ``.debug`` chunk.

    ``emitted`` and ``retail`` are both positioned at ``base`` in retail's ``.debug``, so
    their reference attributes name the same section offsets.
    """
    try:
        mine = parse(emitted, base)
        theirs = parse(retail, base)
    except Unparseable as exc:
        return Outcome(False, 4, str(exc))
    mine_by_offset = {die.offset: die for die in mine}
    retail_by_offset = {die.offset: die for die in theirs}

    if len(emitted) != len(retail):
        first, side = _first_positional_difference(mine, theirs, mine_by_offset,
                                                   retail_by_offset, base)
        detail = (f"the chunk is 0x{len(emitted):X} bytes against retail's "
                  f"0x{len(retail):X}")
        if first is not None:
            detail += (f"; first offending DIE is {_describe(first, base)}"
                       + (" (the emitted chunk)" if side == "emitted" else
                          " (retail's) "))
        return Outcome(False, 2, detail, die_count=len(mine))

    if len(mine) != len(theirs):
        first, side = _first_positional_difference(mine, theirs, mine_by_offset,
                                                   retail_by_offset, base)
        detail = (f"the chunk holds {len(mine)} DIEs against retail's {len(theirs)}")
        if first is not None:
            detail += (f"; first offending DIE is {_describe(first, base)}"
                       + (" (the emitted chunk)" if side == "emitted" else
                          " (retail's) "))
        return Outcome(False, 2, detail, die_count=len(mine))

    mine_counts = collections.Counter(_signature(die, mine_by_offset) for die in mine)
    retail_counts = collections.Counter(_signature(die, retail_by_offset) for die in theirs)

    if mine_counts != retail_counts:
        # Prefer a DIE whose own attributes are new: a member added to a container would
        # otherwise be reported as its first *sibling*, because every child's contextual
        # signature moved when the parent's child list did.
        mine_local = collections.Counter(_local_signature(die, mine_by_offset) for die in mine)
        retail_local = collections.Counter(
            _local_signature(die, retail_by_offset) for die in theirs)
        extra = next((die for die in mine
                      if mine_local[_local_signature(die, mine_by_offset)]
                      > retail_local[_local_signature(die, mine_by_offset)]), None)
        missing = next((die for die in theirs
                        if retail_local[_local_signature(die, retail_by_offset)]
                        > mine_local[_local_signature(die, retail_by_offset)]), None)
        if extra is None and missing is None:
            extra = next((die for die in mine
                          if mine_counts[_signature(die, mine_by_offset)]
                          > retail_counts[_signature(die, mine_by_offset)]), None)
            missing = next((die for die in theirs
                            if retail_counts[_signature(die, retail_by_offset)]
                            > mine_counts[_signature(die, retail_by_offset)]), None)
        first = min((die for die in (extra, missing) if die is not None),
                    key=lambda die: (die.offset, die is missing))
        side = "the emitted chunk" if first is extra else "retail's"
        return Outcome(False, 3,
                       f"the DIE set differs: {_describe(first, base)} has no counterpart "
                       f"in {'retail' if side == 'the emitted chunk' else 'the emitted chunk'}"
                       f" (first offending DIE is in {side})",
                       die_count=len(mine))

    # Conditions 2 and 3 hold.  Count the anonymous indices whose structure is unique in
    # both chunks and whose number moved -- the measurement the doc records.
    def anon_by_signature(dies, by_offset):
        out = collections.defaultdict(list)
        for die in dies:
            name = die.name
            if isinstance(name, str) and _ANON.fullmatch(name):
                out[_signature(die, by_offset)].append(name)
        return out

    mine_anon = anon_by_signature(mine, mine_by_offset)
    retail_anon = anon_by_signature(theirs, retail_by_offset)
    permuted = 0
    for key, names in retail_anon.items():
        emitted = mine_anon.get(key, ())
        # Structures with identical signatures are paired in emission order: that is the
        # only pairing their signatures admit, and it is what makes `@anonN -> @anonM`
        # countable rather than an unordered multiset.
        permuted += sum(1 for left, right in zip(names, emitted) if left != right)
    anonymous = sum(len(names) for names in retail_anon.values())
    return Outcome(True, die_count=len(mine), permuted=permuted, anonymous=anonymous)
