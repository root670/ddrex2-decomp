#!/usr/bin/env python3
"""Adopt retail's ``.line`` chunk and ``AT_location`` values, then prove the bytes.

This is the opt-in step for the class a ``.text``-exact unit leaves behind: the compiled
code is retail's, but the debug metadata around it is not.  Retail's statement table may
place the same instructions on different lines, and a local may sit in a different register
than the one retail's DIE names.  The step adopts the metadata **from retail**, and accepts
only when the result is retail's ``.debug`` chunk byte for byte:

1. ``.text`` must already be byte-identical.  That is the caller's precondition
   (:func:`toolchain.compile.debug_promotion`), enforced before this module is reached: no
   amount of metadata adoption can make different instructions the same ones.
2. ``.line`` is retail's chunk, whole.  The step reports how many rows differ (and in which
   sub-table) before it is replaced; it never pads or edits individual rows.
3. ``.debug`` is first put into retail's DIE order with :mod:`toolchain.debug_normalize`,
   with ``AT_location`` excluded from the pairing signature: two records whose only
   difference is the register a local was assigned are the same record.  On that ordering
   the step adopts, for every record that otherwise matches retail's:
     * ``AT_location`` on a local variable (the register/stack slot retail's compiler used);
     * ``AT_name`` on an anonymous aggregate (``@anonN`` is a synthesized index, and
       adopting retail's assignment is what the index permutation means);
     * the value of an intra-chunk reference (``AT_user_def_type``, ``AT_mod_u_d_type``,
       ``AT_subscr_data``'s element/index types, and the ``0x2303`` reference lists) when
       the reference it replaces names a structurally identical DIE.  Duplicate DIEs are
       interchangeable; the adopted value is retail's choice among them.
   Every other byte must already be retail's.  A difference in anything else refuses and
   names the DIE and attribute -- there is no tolerance and no partial adoption.
4. The adopted chunk is compared with retail's.  A difference is a :class:`Refused`, never
   a warning and never a plausible-looking result.

The report :class:`Adopted` carries every value that changed, which is what the caller
prints and what a ``tu_builds`` comment quotes.  It is part of the acceptance, not an
optional trace.
"""

from __future__ import annotations

import re
import struct

from toolchain import debug_normalize, debug_set

AT_LOCATION = debug_set.AT_LOCATION
AT_NAME = debug_set.AT_NAME
TAG_LOCAL_VARIABLE = 0x000C
#: The attributes measured to carry intra-chunk DIE references (see debug_normalize).
REFERENCE_CODES = (0x0072, 0x0083, debug_set.AT_SUBSCR_DATA, debug_set.AT_2303)

_ANON = re.compile(r"@anon\d+$")
_U16 = struct.Struct("<H").unpack_from
_U32 = struct.Struct("<I").unpack_from
_P32 = struct.Struct("<I").pack_into

GPR = ("zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3",
       "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
       "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra")


class Refused(ValueError):
    """The unit's metadata cannot be adopted: the result would not be retail's bytes."""


class Changed:
    """One adopted ``AT_location`` or anonymous name."""

    __slots__ = ("where", "name", "before", "after")

    def __init__(self, where, name, before, after):
        self.where = where      # the function that owns the local ("" for a type name)
        self.name = name        # the local's name, or the anonymous DIE's old name
        self.before = before    # rendered location / adopted-away name
        self.after = after      # retail's location / retail's name

    def __str__(self):
        if not self.where:
            return f"{self.name} -> {self.after}"
        return f"{self.name} (in {self.where}): {self.before} -> {self.after}"


class Adopted:
    """Retail's metadata, and what had to change to make it ours."""

    __slots__ = ("chunk", "line", "line_rows", "line_tables", "line_total",
                 "line_changed", "first_line_row", "line_note", "locations", "anon_names",
                 "references", "reference_changes", "dropped", "adopted_attributes",
                 "dies")

    def __init__(self, chunk, line, line_rows, line_tables, line_total, line_changed,
                 first_line_row, locations, anon_names, references, dies,
                 line_note=None, reference_changes=(), dropped=(),
                 adopted_attributes=()):
        self.chunk = chunk              # retail's .debug chunk, byte-equal to the proof
        self.line = line                # retail's .line chunk, adopted whole
        self.line_rows = line_rows      # [(table, row, before, after)] byte-different rows
        self.line_tables = line_tables  # sub-tables compared
        self.line_total = line_total    # rows in the adopted chunk
        self.line_changed = line_changed  # rows whose statement line moved, aligned
        self.first_line_row = first_line_row  # (table, row, offset, ours, retail) or None
        self.line_note = line_note      # why the emitted table is not row-comparable, or None
        self.locations = locations      # [Changed], one per adopted AT_location
        self.anon_names = anon_names    # [Changed], one per adopted @anonN name
        self.references = references    # intra-chunk reference words rewritten
        #: ``(old, new, die_offset, attribute)`` for every reference rewritten.
        self.reference_changes = tuple(reference_changes)
        #: ``(die, span_length)`` for every extra DIE dropped (with its whole subtree).
        self.dropped = tuple(dropped)
        #: ``(die_description, attribute)`` for every attribute retail has and ours lacks.
        self.adopted_attributes = tuple(adopted_attributes)
        self.dies = dies                # DIEs in the adopted chunk


# ---------------------------------------------------------------------------
# .line
# ---------------------------------------------------------------------------


def _line_tables(chunk: bytes) -> list:
    """``[(offset, base, [(line, position, address delta), ...]), ...]`` for one chunk.

    Retail's chunk is a run of DWARF 1 statement-list tables, each introduced by its
    ``(length, base address)`` header; the function CUs' tables are concatenated.  A chunk
    that does not parse exactly to its end refuses: an adopted table the step cannot read
    is not a table whose rows it may replace.
    """
    tables, offset = [], 0
    while offset < len(chunk):
        if offset + 8 > len(chunk):
            raise Refused(f".line +0x{offset:X}: a table header runs past the chunk")
        length, base = struct.unpack_from("<II", chunk, offset)
        if length < 8 or offset + length > len(chunk):
            raise Refused(f".line +0x{offset:X}: table length 0x{length:X} does not fit "
                          f"the 0x{len(chunk):X}-byte chunk")
        rows = []
        at = offset + 8
        while at < offset + length:
            if at + 10 > offset + length:
                raise Refused(f".line +0x{at:X}: a table entry runs past its table")
            rows.append(struct.unpack_from("<IHI", chunk, at))
            at += 10
        tables.append((offset, base, rows))
        offset += length
    return tables


def line_changes(emitted: bytes, retail: bytes):
    """``(changes, table count, row count)``: rows where the statement table is not retail's."""
    ours = _line_tables(emitted)
    theirs = _line_tables(retail)
    if len(ours) != len(theirs):
        raise Refused(f".line holds {len(ours)} statement table(s) against retail's "
                      f"{len(theirs)}; the tables are not comparable one-for-one")
    changes = []
    for index, ((_, base_a, rows_a), (_, base_b, rows_b)) in enumerate(zip(ours, theirs)):
        if len(rows_a) != len(rows_b):
            raise Refused(f".line table {index} holds {len(rows_a)} rows against retail's "
                          f"{len(rows_b)}")
        for row, (one, other) in enumerate(zip(rows_a, rows_b)):
            if one != other:
                changes.append((index, row, (base_a, one), (base_b, other)))
    return changes, len(ours), sum(len(rows) for _offset, _base, rows in ours)


def line_number_changes(emitted: bytes, retail: bytes):
    """``(count, first)``: the statement lines that moved, aligned per sub-table.

    A statement table can shift as a whole (the same lines against later addresses) or lose
    and gain rows; a row-by-row byte comparison then reports the whole tail as changed.
    Aligning the *line numbers* per table names the records whose statement line actually
    moved: a row on our side that is not matched equal is one changed row.  ``first`` is
    ``(table, row, offset, ours, retail)``, where ``offset`` is the row's byte position in
    the chunk, or ``None``.
    """
    import difflib

    ours = _line_tables(emitted)
    theirs = _line_tables(retail)
    count, first = 0, None
    for index, ((offset, _base, rows_a), (_offset_b, _base_b, rows_b)) in enumerate(
            zip(ours, theirs)):
        left = [row[0] for row in rows_a]
        right = [row[0] for row in rows_b]
        matcher = difflib.SequenceMatcher(None, left, right, autojunk=False)
        for tag, i, j, k, _l in matcher.get_opcodes():
            if tag not in ("replace", "delete"):
                continue
            count += j - i
            if first is None:
                first = (index, i, offset + 8 + 10 * i, left[i],
                         right[k] if k < len(right) else None)
    return count, first


# ---------------------------------------------------------------------------
# AT_location rendering
# ---------------------------------------------------------------------------


def _location_text(payload: bytes) -> str:
    """The short location text the oracle uses: ``scratch``, ``$a2``, ``@0x...``."""
    ops, at = [], 0
    while at < len(payload):
        op = payload[at]
        at += 1
        if op in (0x01, 0x02, 0x03, 0x04, 0x80) and at + 4 <= len(payload):
            ops.append((op, _U32(payload, at)[0]))
            at += 4
        else:
            ops.append((op, None))
    kinds = [op for op, _ in ops]
    if kinds[-1:] in ([0x82], [0x06]):
        kinds, ops = kinds[:-1], ops[:-1]
    if kinds == [0x01]:
        register = ops[0][1]
        if register == 2:
            return "scratch"                      # MW's placeholder, not $v0
        return f"${GPR[register]}" if register < 32 else f"$r{register}"
    if kinds == [0x80]:
        return f"$f{ops[0][1]}"
    if kinds == [0x03]:
        return f"@0x{ops[0][1]:08X}"
    if kinds == [0x02]:
        return f"{GPR[ops[0][1]] if ops[0][1] < 32 else ops[0][1]}+0x0"
    if kinds == [0x02, 0x04, 0x07]:
        return f"{GPR[ops[0][1]] if ops[0][1] < 32 else ops[0][1]}+0x{ops[1][1]:X}"
    if kinds == [0x01, 0x04, 0x07]:
        name = "scratch" if ops[0][1] == 2 else (
            f"${GPR[ops[0][1]]}" if ops[0][1] < 32 else f"$r{ops[0][1]}")
        return f"{name}+0x{ops[1][1]:X}"
    if kinds == [0x04, 0x07]:
        return f"+0x{ops[0][1]:X}"
    return payload.hex()


# ---------------------------------------------------------------------------
# .debug
# ---------------------------------------------------------------------------


def _fields(record: bytes, start: int = 0):
    """``(code, form, at, size)`` for every attribute of one DIE record.

    ``at`` is the value's offset inside ``record``; ``size`` is the payload width.  The walk
    is the compiler's own encoding (the same one :func:`debug_set.parse` makes).
    """
    at = start + 6                                # 4-byte length, 2-byte tag
    end = len(record)
    while at < end:
        if at + 2 > end:
            raise Refused("a DIE record ends inside an attribute code")
        code = _U16(record, at)[0]
        at += 2
        form = code & 0x0F
        if form in (1, 2, 6):
            yield code, form, at, 4
            at += 4
        elif form == 5:
            yield code, form, at, 2
            at += 2
        elif form == 8:
            stop = record.index(b"\0", at)
            yield code, form, at, stop - at
            at = stop + 1
        elif form in (3, 4):
            width = 2 if form == 3 else 4
            size = _U16(record, at)[0] if form == 3 else _U32(record, at)[0]
            yield code, form, at + width, size
            at += width + size
        elif form == 7:
            yield code, form, at, 8
            at += 8
        else:
            raise Refused(f"attribute 0x{code:04X} has unknown form {form}")


def _owner(die) -> str:
    """The function a local sits in, for the report."""
    node = die.parent
    while node is not None and node.parent is not None:
        if node.tag in (0x0006, 0x0014):
            return node.name or "?"
        node = node.parent
    return ""


def _key_tree(dies):
    """``{offset: shallow key}``: what a reference's target is, ignoring its children.

    Two DIEs with the same tag, name, size and attributes are interchangeable for a
    reference -- and after the pairing they are in retail's order, so retail's choice among
    identical records is the one adopted.  The final whole-chunk byte comparison is what
    proves no real difference was hidden.
    """
    by_offset = {die.offset: die for die in dies}
    key = debug_normalize._shallow_key(by_offset)
    return {die.offset: key(die) for die in dies}


def adopt(emitted: bytes, retail: bytes, base: int = 0, emitted_line: bytes = b"",
          retail_line: bytes = b"") -> Adopted:
    """Retail's metadata in our chunk, accepted only when the bytes are retail's."""
    # The report is best-effort: retail's chunk is adopted whole either way, and a source
    # whose layout was normalised (``#line`` directives stripped) can emit a different
    # number of statement records while its .text stays retail's.  A table that is not
    # row-for-row comparable is recorded in ``line_note`` instead of refusing the adoption.
    line_note = None
    try:
        line_diff, line_table_count, line_total = line_changes(emitted_line, retail_line) \
            if emitted_line or retail_line else ([], 0, 0)
        line_changed, first_line_row = line_number_changes(emitted_line, retail_line) \
            if emitted_line or retail_line else (0, None)
    except Refused as exc:
        line_note = str(exc)
        line_diff, line_table_count, line_total = [], 0, 0
        line_changed, first_line_row = 0, None

    if len(emitted) < len(retail):
        raise Refused(f".debug is 0x{len(emitted):X} bytes against retail's "
                      f"0x{len(retail):X}; retail carries records we do not, and a missing "
                      f"record is not fabricated")

    try:
        ordering = debug_normalize.normalise(
            emitted, retail, base,
            ignore=lambda die, code: (
                (code == AT_LOCATION and die.tag == TAG_LOCAL_VARIABLE)
                or code == debug_set.AT_2303),
            drop_extra=True, adopt_missing=(debug_set.AT_2303,), adopt_names=True)
    except debug_normalize.Refusal as exc:
        raise Refused(str(exc))

    out = bytearray(ordering.chunk)
    if len(out) != len(retail):
        raise Refused(f"the ordered chunk is 0x{len(out):X} bytes against retail's "
                      f"0x{len(retail):X}")

    try:
        ours = debug_set.parse(bytes(out), base)
        theirs = debug_set.parse(retail, base)
    except debug_set.Unparseable as exc:
        raise Refused(str(exc))
    if len(ours) != len(theirs):
        raise Refused(f"the ordered chunk holds {len(ours)} DIEs against retail's "
                      f"{len(theirs)}")
    for one, other in zip(ours, theirs):
        if one.offset != other.offset or one.tag != other.tag:
            raise Refused(f"the ordered chunk does not follow retail's DIE sequence at "
                          f"+0x{one.offset - base:X}: {debug_set.TAG.get(one.tag, '?')} "
                          f"against {debug_set.TAG.get(other.tag, '?')}")

    ours_keys, retail_keys = _key_tree(ours), _key_tree(theirs)
    locations = []
    anon_names = [Changed("", old, old, new)
                  for old, new, _where in ordering.name_changes]
    reference_changes = list(ordering.reference_changes)
    references = len(reference_changes)

    for die, ref_die in zip(ours, theirs):
        if die.length != ref_die.length:
            raise Refused(f"+0x{die.offset - base:X} {debug_set.TAG.get(die.tag, '?')} is "
                          f"0x{die.length:X} bytes against retail's "
                          f"0x{ref_die.length:X}")
        start = die.offset - base
        record = bytes(out[start:start + die.length])
        retail_record = retail[start:start + die.length]
        if record == retail_record:
            continue
        for code, form, at, size in list(_fields(record)):
            mine = record[at:at + size]
            other = retail_record[at:at + size]
            if mine == other:
                continue
            if code == AT_LOCATION and die.tag == TAG_LOCAL_VARIABLE:
                if len(mine) != len(other):
                    raise Refused(
                        f"{die.name} (in {_owner(die) or '?'}) has a "
                        f"0x{len(mine):X}-byte AT_location against retail's "
                        f"0x{len(other):X}; a location is adopted, not reshaped")
                out[start + at:start + at + size] = other
                locations.append(Changed(_owner(die), die.name or "?",
                                         _location_text(mine), _location_text(other)))
                continue
            if code == AT_NAME and len(mine) and len(other):
                old, new = mine.decode("latin-1"), other.decode("latin-1")
                if _ANON.match(old) and _ANON.match(new):
                    out[start + at:start + at + size] = other
                    anon_names.append(Changed("", old, old, new))
                    continue
            if code in REFERENCE_CODES and size:
                positions = ([0] if form == 2
                             else debug_normalize._block_references(code, mine))
                patched = bytearray(mine)
                repaired = 0
                for word in positions or ():
                    value = _U32(mine, word)[0]
                    target = _U32(other, word)[0]
                    if value == target:
                        continue
                    if ours_keys.get(value) != retail_keys.get(target):
                        raise Refused(
                            f"+0x{die.offset - base:X} {debug_set.TAG.get(die.tag, '?')} "
                            f"{die.name or ''}: attribute 0x{code:04X} names "
                            f"+0x{value - base:X} here and +0x{target - base:X} in retail, "
                            f"and the two DIEs are not structurally identical")
                    _P32(patched, word, target)
                    repaired += 1
                    reference_changes.append((value, target, debug_set._describe(die, base),
                                              code))
                if repaired:
                    out[start + at:start + at + size] = patched
                continue
            prefix = min(size, 16)
            raise Refused(
                f"+0x{die.offset - base:X} {debug_set.TAG.get(die.tag, '?')} "
                f"{die.name or ''}: attribute 0x{code:04X} is {mine[:prefix].hex()} here "
                f"and {other[:prefix].hex()} in retail; adoption covers .line, locals' "
                f"AT_location, the anonymous name and references, not this")

    if bytes(out) != retail:
        at = next(index for index, (one, other) in enumerate(zip(out, retail))
                  if one != other)
        raise Refused(f"the adopted chunk is not retail's: first difference at "
                      f"+0x{at:X} (0x{out[at]:02X} against 0x{retail[at]:02X})")

    return Adopted(retail, retail_line, line_diff, line_table_count, line_total,
                   line_changed, first_line_row, locations, anon_names,
                   len(reference_changes), len(ours), line_note,
                   reference_changes, ordering.dropped, ordering.adopted_attributes)
