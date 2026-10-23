#!/usr/bin/env python3
"""The opt-in ``.debug`` DIE-order normaliser: re-emit our chunk in retail's DIE order.

The set-equal gate (:mod:`toolchain.debug_set`) *recognises* the class where our compiler
emits the same DIEs in a different order and retail's chunk is kept in the image.  This
module is the stronger step the class admits: **rewrite** our chunk into retail's sequence
and accept it only when the rewritten bytes are retail's, byte for byte.

Why it is the same claim as the gate's, and not a new one: the DIE *set* is already measured
equal (the gate), so the correspondence between our DIEs and retail's is measured, not
guessed.  What this module adds is that emission order alone accounts for the difference --
it is a proof about the *compiler's output order*, never about the C source.

What it does, in order:

1. parse both chunks into DWARF 1 DIE trees (:func:`debug_set.parse`);
2. match DIEs one-to-one at every level of the tree, by a structural signature --
   ``(tag, attributes with references normalised to their target's description -- recursed
   through array subscripts -- sorted child signatures)``, so identical structures are
   paired in emission order and a different set refuses (:mod:`toolchain.debug_set`'s
   signature, made recursive);
3. lay out our DIE records in retail's sibling order, recursively (a lexical block reorders
   its own children, not the top level only), keeping the trailing terminator of every
   child chain that still has records -- a chain whose records were all dropped as extras
   is gone with them;
4. recompute every ``AT_sibling`` from the new layout (its target is the laid-out end of
   that record's subtree, so a dropped child chain contributes no terminator), and rewrite
   every intra-chunk offset reference through the source-to-new offset map;
5. re-emit, and let the caller compare the result with retail's bytes.  A difference is a
   refusal, not a warning: no tolerance, no partial.

**Which attributes this dialect carries as intra-chunk offsets** -- enumerated from the whole
of retail's ``.debug`` (``orig/SLUS_211.74``, 118,116 DIEs), not assumed:

===================================  ======  ==========================================
attribute                            form    how it is handled
===================================  ======  ==========================================
``0x0012`` AT_sibling                2       recomputed from the new layout
``0x0072`` AT_user_def_type          2       18797 occurrences; remapped
``0x0142`` (MW attribute 0x14)       2       7 occurrences; remapped
``0x00a3`` AT_subscr_data            3       element type / index type refs, by DWARF 1
                                              subscript grammar; remapped
``0x0083`` AT_mod_u_d_type           3       trailing user-defined reference; remapped
``0x2303`` (MW attribute 0x230)      3       1782 occurrences, each a block of 4-byte
                                              references; every word is remapped
every other block form               3, 4    untouched: no occurrence in the section holds
                                              an intra-chunk DIE offset (the 0x23 blocks'
                                              coincidental hits are addresses, not refs)
===================================  ======  ==========================================

A reference whose value lies inside the chunk but names no DIE refuses (a broken reference
must not produce a plausible wrong chunk).  A reference outside the chunk is another
section's (``.text`` addresses, ``.line`` offsets) and is left alone.

This step does **not** run unless the caller asks for it (``compile.py
--normalise-debug``): it is a measurement, and the gate's own default -- recognise the
class, keep retail's bytes -- stays the promotion path.
"""

from __future__ import annotations

import re
import struct

from toolchain import debug_set

AT_SIBLING = debug_set.AT_SIBLING          # 0x0012, recomputed positionally
AT_SUBSCR_DATA = debug_set.AT_SUBSCR_DATA  # 0x00a3
AT_MOD_U_D_TYPE = debug_set.AT_MOD_U_D_TYPE  # 0x0083
#: The MW attribute measured as a bare 4-byte reference in every one of its 1782
#: occurrences across retail's ``.debug``.
AT_2303 = 0x2303

_ANON_NAME = re.compile(r"@anon\d+$")

_U16 = struct.Struct("<H").unpack_from
_U32 = struct.Struct("<I").unpack_from
_P32 = struct.Struct("<I").pack_into


class Refusal(ValueError):
    """The chunk cannot be normalised: a set difference or a broken reference.

    A refusal is the honest verdict -- a chunk this module cannot rewrite into retail's
    order is not a chunk whose reordering has been proved, and emitting anything would be
    a guess.
    """


class Reordered:
    """The normalised chunk and what happened while rewriting it."""

    __slots__ = ("chunk", "dies", "moved", "references", "reference_changes", "dropped",
                 "name_changes", "adopted_attributes", "sibling_changes", "sibling_targets")

    def __init__(self, chunk, dies, moved, references, reference_changes=(),
                 dropped=(), name_changes=(), adopted_attributes=(), sibling_changes=(),
                 sibling_targets=()):
        self.chunk = chunk          # the rewritten bytes, at the same ``base``
        self.dies = dies            # DIEs emitted
        self.moved = moved          # DIEs whose new offset is not their old one
        self.references = references  # intra-chunk references rewritten
        #: ``(old, new, die_description, attribute)`` for every reference rewritten.
        self.reference_changes = tuple(reference_changes)
        #: ``(die, span_length)`` for every extra DIE dropped (with its whole subtree).
        self.dropped = tuple(dropped)
        #: ``(old_name, new_name, die_description)`` for every adopted ``@anonN`` name.
        self.name_changes = tuple(name_changes)
        #: ``(die_description, attribute)`` for every attribute retail has and ours lacks.
        self.adopted_attributes = tuple(adopted_attributes)
        #: ``(old, new, die_description)`` for every surviving ``AT_sibling`` recomputed.
        self.sibling_changes = tuple(sibling_changes)
        #: ``{new offset: sibling target}`` for every emitted record that carries one.
        self.sibling_targets = dict(sibling_targets)


def _describe(die, base):
    return debug_set._describe(die, base)


def _fields(record):
    """Every attribute of one DIE record, with the position of its value.

    Yields ``(code, form, at, size)``: ``at`` is the offset of the value inside ``record``
    (the 2-byte attribute code has already been skipped), and ``size`` is the value's width
    for the fixed-width forms or the payload length for a block.  The record is the way the
    compiler wrote it, so the walk is the same one :func:`debug_set.parse` makes.
    """
    p = 6                                   # 4-byte length, 2-byte tag
    n = len(record)
    while p < n:
        code = _U16(record, p)[0]
        p += 2
        form = code & 0x0F
        if form in (1, 2, 6):
            yield code, form, p, 4
            p += 4
        elif form == 5:
            yield code, form, p, 2
            p += 2
        elif form == 8:
            stop = record.index(b"\0", p)
            yield code, form, p, stop - p
            p = stop + 1
        elif form in (3, 4):
            width = 2 if form == 3 else 4
            size = _U16(record, p)[0] if form == 3 else _U32(record, p)[0]
            yield code, form, p + width, size
            p += width + size
        elif form == 7:
            yield code, form, p, 8
            p += 8
        else:
            raise Refusal(f"attribute 0x{code:04X} has unknown form {form}")


def _subscript_refs(payload):
    """The positions of the references inside an ``AT_subscr_data`` block.

    DWARF 1's subscript data is a sequence of entries, each a format byte followed by the
    index type and the bound; the element type is a *form 2 attribute* inside the block, and
    a user-defined index type is a bare 4-byte reference.  Both name DIEs and both move with
    the layout.
    """
    refs = []
    p = 0
    while p < len(payload):
        fmt = payload[p]
        p += 1
        if fmt == 8:                                  # FMT_ET: the element type attribute
            if p + 2 > len(payload):
                raise Refusal("a subscript block ends inside its element type")
            code = _U16(payload, p)[0]
            form = code & 0x0F
            if form in (1, 2, 6):
                if form == 2:
                    refs.append(p + 2)
                p += 2 + 4
            elif form == 5:
                p += 2 + 2
            elif form == 3:
                # A form-3 element type is a block: modifier flags, then a 4-byte DIE
                # reference.  The array of a user-defined type is written this way, and
                # that reference moves with the anonymous order like a form-2 one does.
                if p + 4 > len(payload):
                    raise Refusal("a subscript block ends inside its element type")
                size = _U16(payload, p + 2)[0]
                if p + 4 + size > len(payload):
                    raise Refusal("a subscript block ends inside its element type")
                if size >= 4:
                    refs.append(p + size)
                p += 4 + size
            else:
                p = len(payload)
            break
        if fmt & 4:                                   # user-defined index type
            if p + 4 > len(payload):
                raise Refusal("a subscript block ends inside its index type")
            refs.append(p)
            p += 4
        else:
            p += 2
        for expression in (fmt & 2, fmt & 1):
            if expression:
                if p + 2 > len(payload):
                    raise Refusal("a subscript block ends inside a bound")
                p += 2 + _U16(payload, p)[0]
            else:
                p += 4
    return refs


def _block_references(code, payload):
    """The positions of the references inside a block attribute, or ``None``.

    ``None`` means the attribute carries none this dialect has ever been measured to hold:
    untouched is then the honest treatment, because guessing at offsets inside a location
    expression would corrupt every unit that carries one.
    """
    if code == AT_SUBSCR_DATA:
        return _subscript_refs(payload)
    if code == AT_MOD_U_D_TYPE and len(payload) >= 4:
        return [len(payload) - 4]
    if code == AT_2303 and len(payload) >= 4 and len(payload) % 4 == 0:
        return list(range(0, len(payload), 4))
    return None


def _profiles(chunk, dies, base, key, ignore=None):
    """``offset -> tuple of (code, key of the referring DIE)`` for in-chunk references.

    Two records with the same signature are still told apart by *who points at them*: two
    ``[3]`` arrays of the same element type, or two subroutine types with the same
    parameters, are distinct DIEs, and each is named by a different record.  The profile is
    the incoming edge list with the source's *key* (order-invariant) in place of its offset,
    so the same structure produces the same profile in both chunks.

    ``AT_sibling`` is not a reference and is excluded: it is an absolute position, and the
    two chunks being compared put the same record at different positions.  ``ignore`` drops
    the attributes the pairing signature drops as well, so a value being adopted from retail
    cannot make a profile one-sided.
    """
    by_offset = {die.offset: die for die in dies}
    profiles = {}
    for die in dies:
        record = chunk[die.offset - base:die.offset - base + die.length]
        for code, form, at, size in _fields(record):
            if code == AT_SIBLING or (ignore is not None and ignore(die, code)):
                continue
            if form == 2:
                values = [_U32(record, at)[0]]
            elif form in (3, 4) and size:
                payload = record[at:at + size]
                positions = _block_references(code, payload)
                values = ([_U32(payload, position)[0] for position in positions]
                          if positions else [])
            else:
                values = []
            for value in values:
                if value in by_offset:
                    profiles.setdefault(value, []).append((code, repr(key(die))))
    return {offset: tuple(sorted(edges)) for offset, edges in profiles.items()}


def _signature_key(by_offset, ignore=None):
    """An order-invariant key for one DIE and its subtree; ``by_offset`` is its own map."""
    memo = {}

    def key(die):
        got = memo.get(die.offset)
        if got is None:
            local = debug_set._local_signature(die, by_offset, ignore)
            children = tuple(sorted(repr(key(child)) for child in die.children))
            got = (local, children)
            memo[die.offset] = got
        return got

    return key


def _shallow_key(by_offset, ignore=None):
    """A DIE's own signature, without its children: the key that locates a difference."""
    memo = {}

    def key(die):
        got = memo.get(die.offset)
        if got is None:
            got = debug_set._local_signature(die, by_offset, ignore)
            memo[die.offset] = got
        return got

    return key


def _mismatch(ours, theirs, our_shallow, retail_shallow, base, where):
    """The deepest difference between two sibling lists, for the refusal message.

    The pairing here is by *shallow* signature, so it is only how the message finds its DIE:
    a sibling list whose deep signatures differ but whose shallow ones pair is descended
    into, and the level that actually differs is the one reported.
    """
    if len(ours) != len(theirs):
        return f"{where} holds {len(ours)} DIEs against retail's {len(theirs)}"
    buckets = {}
    for die in ours:
        buckets.setdefault(our_shallow(die), []).append(die)
    paired = []
    for die in theirs:
        bucket = buckets.get(retail_shallow(die))
        if not bucket:
            return (f"the DIE set differs: {_describe(die, base)} has no counterpart in the "
                    f"emitted chunk")
        paired.append((bucket.pop(0), die))
    leftover = next((dies[0] for dies in buckets.values() if dies), None)
    if leftover is not None:
        return (f"the DIE set differs: {_describe(leftover, base)} has no counterpart in "
                f"retail")
    for our_die, retail_die in paired:
        deeper = _mismatch(our_die.children, retail_die.children, our_shallow,
                           retail_shallow, base,
                           f"the children of {_describe(retail_die, base)}")
        if deeper:
            return deeper
    return ""


def _pair(ours, theirs, our_key, retail_key, base, where, locator=None,
          drop_extra=False, our_shallow=None, retail_shallow=None,
          our_profiles=None, retail_profiles=None):
    """Pair two sibling lists one-to-one; refuse on a missing record, allow extra ones.

    Identical signatures are paired by the references into them (:func:`_profiles`), and
    where even those do not tell them apart, in emission order -- the only pairing they then
    admit, and the same convention the gate's permutation count uses.  ``locator`` turns a
    refusal into the *deepest* difference (see :func:`_mismatch`) instead of naming the
    container.

    With ``drop_extra`` a DIE on *our* side that retail does not have is returned as a
    leftover instead of refusing: the adoption step drops it and proves the bytes.  A DIE
    retail has and we do not is still a refusal -- fabricating a record would be invention,
    not adoption.  A parent whose only difference is an extra child cannot match by the
    recursive key, so a second pass matches the remaining records by their *shallow* key;
    the caller's byte compare is what proves the pairing.
    """
    if len(ours) != len(theirs) and not drop_extra:
        raise Refusal((locator() if locator else "")
                      or f"{where} holds {len(ours)} DIEs against retail's {len(theirs)}")

    matched = {}
    buckets = {}
    for die in ours:
        buckets.setdefault(our_key(die), []).append(die)
    # A key group with more than one record admits more than one pairing.  Retail emits
    # structurally identical arrays and subroutine types as distinct DIEs -- ``[3]`` of the
    # same element, the same signature -- and only the record that points at one of them
    # tells them apart.  The profiles are that fact made explicit.
    ambiguous = {key for key, bucket in buckets.items() if len(bucket) > 1}
    groups = {}
    for die in theirs:
        groups.setdefault(retail_key(die), []).append(die)
    for key, group in groups.items():
        bucket = buckets.get(key)
        if bucket is None:
            continue
        if (key in ambiguous and our_profiles is not None
                and retail_profiles is not None):
            remaining = list(bucket)
            for die in group:
                profile = retail_profiles.get(die.offset)
                if not profile:
                    continue
                pick = next((candidate for candidate in remaining
                             if our_profiles.get(candidate.offset) == profile), None)
                if pick is not None:
                    matched[die.offset] = pick
                    remaining.remove(pick)
            for die in group:
                if die.offset in matched:
                    continue
                if remaining:
                    matched[die.offset] = remaining.pop(0)
        else:
            remaining = bucket
            for die in group:
                if remaining:
                    matched[die.offset] = remaining.pop(0)
        buckets[key] = remaining
    unmatched = [die for die in theirs if die.offset not in matched]

    if drop_extra and unmatched:
        shallow = our_shallow or our_key
        retail_shallow = retail_shallow or retail_key
        leftover = [die for bucket in buckets.values() for die in bucket]
        leftover.sort(key=lambda die: die.offset)
        shallow_buckets = {}
        for die in leftover:
            shallow_buckets.setdefault(shallow(die), []).append(die)
        for die in list(unmatched):
            bucket = shallow_buckets.get(retail_shallow(die))
            if bucket:
                matched[die.offset] = bucket.pop(0)
                unmatched.remove(die)
        buckets = shallow_buckets

    if unmatched:
        die = unmatched[0]
        raise Refusal(
            (locator() if locator else "")
            or f"the DIE set differs: {_describe(die, base)} has no counterpart in the "
               f"emitted chunk")
    pairs = [(matched[die.offset], die) for die in theirs]
    dropped = sorted((die for bucket in buckets.values() for die in bucket),
                     key=lambda die: die.offset)
    if dropped and not drop_extra:
        raise Refusal((locator() if locator else "")
                      or f"the DIE set differs: {_describe(dropped[0], base)} has no "
                         f"counterpart in retail")
    return pairs, dropped


def _raw_attributes(record):
    """``[(code, raw_bytes)]`` for one record, in the order the compiler wrote them."""
    out = []
    at = 6
    end = len(record)
    while at < end:
        start = at
        code = _U16(record, at)[0]
        at += 2
        form = code & 0x0F
        if form in (1, 2, 6):
            at += 4
        elif form == 5:
            at += 2
        elif form == 8:
            at = record.index(b"\0", at) + 1
        elif form in (3, 4):
            width = 2 if form == 3 else 4
            size = _U16(record, at)[0] if form == 3 else _U32(record, at)[0]
            at += width + size
        elif form == 7:
            at += 8
        else:
            raise Refusal(f"attribute 0x{code:04X} has unknown form {form}")
        out.append((code, record[start:at]))
    return out


def _encode_attribute(code, payload):
    """One DWARF 1 attribute, encoded the way the compiler writes it."""
    if len(payload) <= 0xFFFF:
        return struct.pack("<HH", code, len(payload)) + payload
    return (struct.pack("<H", (code & ~0x0F) | 4) + struct.pack("<I", len(payload))
            + payload)


def normalise(emitted: bytes, retail: bytes, base: int = 0, ignore=None,
              drop_extra: bool = False, adopt_missing=(), adopt_names: bool = False,
              redirect_dropped: bool = False, trim_dropped_refs=()) -> Reordered:
    """Rewrite ``emitted`` into ``retail``'s DIE order, at the same ``base`` in ``.debug``.

    The result carries retail's DIE *sequence*; whether it is retail's *bytes* is the
    caller's comparison, and a difference must be a refusal there.  Raises :class:`Refusal`
    when the chunk cannot be rewritten at all: a different DIE set, a chunk that is not a
    contiguous DIE sequence, an unknown attribute form, or a reference that lies inside the
    chunk but names no DIE.

    ``ignore`` names attributes whose value is excluded from the pairing signature.  The
    metadata-adoption step passes ``AT_location`` for locals: the location is being adopted
    from retail, so it must not stop the two records from pairing.

    ``drop_extra`` allows a DIE on *our* side to have no retail counterpart: it is dropped
    with its whole subtree and reported in :attr:`Reordered.dropped`.  A DIE retail has and
    we do not still refuses -- fabricating a record would be invention, not adoption.  Every
    surviving record's ``AT_sibling`` is then recomputed from the final layout and reported
    in :attr:`Reordered.sibling_changes`; :attr:`Reordered.sibling_targets` carries the
    target per laid-out offset, which is what the adoption step applies.

    ``adopt_missing`` names attributes retail carries on a paired DIE while ours does not
    (the adoption step passes ``AT_2303``, the access-reference list).  Each such attribute
    is copied from retail with its 4-byte references translated through the pairing to our
    DIE offsets; anything else missing is a refusal.

    ``adopt_names`` takes retail's ``@anonN`` name for a paired anonymous DIE.  The name is
    part of the record, so it is adopted *before* the layout -- a longer index moves every
    later record -- and reported in :attr:`Reordered.name_changes`.

    ``redirect_dropped`` lets a reference into a dropped record be retargeted at a *surviving
    record with the same full subtree key* -- the same structural interchangeability the
    pairing already relies on.  The compiler sometimes emits two identical type records where
    retail emitted one, and both are referenced; dropping either twin changes the reference
    word of whichever record named it, so the value is rewritten to the surviving twin and
    reported in :attr:`Reordered.reference_changes`.  A reference to a dropped record with no
    identical survivor still refuses, because there the reference's meaning would change.

    ``trim_dropped_refs`` names *list* attributes (the adoption step passes ``AT_2303``, the
    access-reference list) from which an entry is removed when it names a dropped extra
    *global declaration* (``global_variable`` / ``global_subroutine``) that has no identical
    twin.  The compiler records every extern a function touches, and retail has no DIE for a
    data object it never named; the entry has no meaning once its target is gone, so it is
    deleted and the list's length word, the record's length word and every later offset
    follow.  A list that would be left empty is removed whole when retail's paired record
    carries no such attribute at all; when retail's does carry one, or the target is any other
    dropped record, it still refuses.
    """
    try:
        ours = debug_set.parse(emitted, base)
        theirs = debug_set.parse(retail, base)
    except debug_set.Unparseable as exc:
        raise Refusal(str(exc))
    end = base + len(emitted)
    by_offset = {die.offset: die for die in ours}

    def subtree_end(die):
        sibling = die.attrs.get(AT_SIBLING)
        if sibling is not None:
            return sibling
        if die.children:
            raise Refusal(f"{_describe(die, base)} has children but no AT_sibling")
        return die.offset + die.length

    # The trailing bytes of each child chain (the compiler's 4-byte terminators), kept
    # verbatim, and the contiguity the reordering is only sound with.
    residues = {}
    for die in ours:
        if not die.children:
            continue
        cursor = die.children[0].offset
        for child in die.children:
            if child.offset != cursor:
                raise Refusal(f"the emitted chunk is not a contiguous DIE sequence at "
                              f"{_describe(child, base)}")
            cursor = subtree_end(child)
        stop = subtree_end(die)
        if stop < cursor or stop > end:
            raise Refusal(f"{_describe(die, base)} ends at 0x{stop:X}, past the chunk")
        residues[die.offset] = (cursor, stop)

    our_key = _signature_key(by_offset, ignore)
    theirs_by_offset = {die.offset: die for die in theirs}
    retail_key = _signature_key(theirs_by_offset, ignore)
    our_shallow = _shallow_key(by_offset, ignore)
    retail_shallow = _shallow_key(theirs_by_offset, ignore)
    our_profiles = _profiles(emitted, ours, base, our_key, ignore)
    retail_profiles = _profiles(retail, theirs, base, retail_key, ignore)
    roots = [die for die in ours if die.parent is None]
    retail_roots = [die for die in theirs if die.parent is None]

    def locator(ours_level, theirs_level, where):
        """The deepest difference in this level, for the refusal :func:`_pair` raises."""
        return lambda: _mismatch(ours_level, theirs_level, our_shallow, retail_shallow,
                                 base, where)

    # -- pairing: every level, one-to-one, extras on our side kept for dropping ---------
    children_of, retail_of, dropped = {}, {}, []
    retail_to_ours = {}
    redirect_of = {}                    # dropped DIE offset -> identical surviving twin

    def pair_level(our_level, retail_level, where):
        pairs, leftovers = _pair(our_level, retail_level, our_key, retail_key, base, where,
                                 locator=locator(our_level, retail_level, where),
                                 drop_extra=drop_extra, our_shallow=our_shallow,
                                 retail_shallow=retail_shallow,
                                 our_profiles=our_profiles,
                                 retail_profiles=retail_profiles)
        for die in leftovers:
            span = subtree_end(die) - die.offset
            dropped.append((die, span))
            if redirect_dropped:
                twin = next((candidate for candidate, _retail_die in pairs
                             if our_key(candidate) == our_key(die)), None)
                if twin is not None:
                    redirect_of[die.offset] = twin.offset
        return pairs

    def walk(pairs):
        for our_die, retail_die in pairs:
            retail_of[our_die.offset] = retail_die
            retail_to_ours[retail_die.offset] = our_die
            where = f"the children of {_describe(retail_die, base)}"
            children_of[our_die.offset] = pair_level(
                our_die.children, retail_die.children, where)
            walk(children_of[our_die.offset])

    root_pairs = pair_level(roots, retail_roots, "the chunk")
    walk(root_pairs)

    # -- anonymous names: retail's index, adopted before the layout ---------------------
    name_raw, name_delta, name_changes = {}, {}, []
    if adopt_names:
        for our_offset, retail_die in retail_of.items():
            our_die = by_offset[our_offset]
            if not (our_die.name and retail_die.name
                    and _ANON_NAME.match(our_die.name)
                    and _ANON_NAME.match(retail_die.name)
                    and our_die.name != retail_die.name):
                continue
            ours_record = emitted[our_die.offset - base:our_die.offset - base + our_die.length]
            theirs_record = retail[retail_die.offset - base:
                                   retail_die.offset - base + retail_die.length]
            ours_name = next(raw for code, raw in _raw_attributes(ours_record)
                             if code == debug_set.AT_NAME)
            theirs_name = next(raw for code, raw in _raw_attributes(theirs_record)
                               if code == debug_set.AT_NAME)
            name_raw[our_offset] = theirs_name
            name_delta[our_offset] = len(theirs_name) - len(ours_name)
            name_changes.append((our_die.name, retail_die.name, _describe(our_die, base)))

    # -- attributes retail carries and the paired record does not ------------------------
    extras = {}
    adopted_attributes = []
    for our_offset, retail_die in retail_of.items():
        our_die = by_offset[our_offset]
        missing = [(code, value) for code, value in retail_die.attrs.items()
                   if code not in our_die.attrs]
        if not missing:
            continue
        for code, value in sorted(missing):
            if code not in adopt_missing:
                raise Refusal(
                    f"{_describe(retail_die, base)} carries attribute 0x{code:04X} with no "
                    f"counterpart in the emitted record; only {len(adopt_missing)} named "
                    f"attribute kind(s) may be adopted, not this one")
            if not isinstance(value, bytes) or not value or len(value) % 4:
                raise Refusal(f"{_describe(retail_die, base)}: attribute 0x{code:04X} is "
                              f"not a list of 4-byte references")
            payload = bytearray(value)
            for position in range(0, len(payload), 4):
                target = _U32(payload, position)[0]
                counterpart = retail_to_ours.get(target)
                if counterpart is None:
                    raise Refusal(
                        f"{_describe(retail_die, base)}: attribute 0x{code:04X} names "
                        f"+0x{target - base:X}, which has no counterpart in the emitted "
                        f"chunk; a missing record is not adopted")
                _P32(payload, position, counterpart.offset)
            extras[(our_offset, code)] = _encode_attribute(code, bytes(payload))
            adopted_attributes.append((_describe(retail_die, base), code))

    # -- layout: our records in retail's order, plus the adopted attributes -------------
    new_at, new_end = {}, {}
    dropped_offsets = {die.offset for die, _span in dropped}

    # -- entries of a ``trim_dropped_refs`` list that name a dropped global declaration ---
    trimmed = {}                        # (our offset, code) -> payload positions removed
    for our_offset in retail_of:
        our_die = by_offset[our_offset]
        span = emitted[our_die.offset - base:our_die.offset - base + our_die.length]
        for code, form, at, size in _fields(span):
            if code not in trim_dropped_refs or form not in (3, 4) or not size:
                continue
            positions = _block_references(code, span[at:at + size]) or []
            gone = []
            for position in positions:
                value = _U32(span, at + position)[0]
                if (value in dropped_offsets and value not in redirect_of
                        and by_offset[value].tag in (0x0006, 0x0007)):
                    gone.append(position)
            if gone and len(gone) == len(positions):
                retail_span = retail[retail_of[our_offset].offset - base:
                                     retail_of[our_offset].offset - base
                                     + retail_of[our_offset].length]
                if code not in dict(_raw_attributes(retail_span)):
                    trimmed[(our_offset, code)] = "all"
                    continue
                raise Refusal(f"{_describe(our_die, base)}: attribute 0x{code:04X} names "
                              f"only dropped global declarations; an empty list is not "
                              f"retail's record")
            if gone:
                trimmed[(our_offset, code)] = gone
    trim_delta = {}
    for (our_offset, _code), gone in trimmed.items():
        if gone == "all":
            span = emitted[our_offset - base:our_offset - base
                           + by_offset[our_offset].length]
            whole = sum(len(raw) for field, raw in _raw_attributes(span) if field == _code)
            trim_delta[our_offset] = trim_delta.get(our_offset, 0) + whole
        else:
            trim_delta[our_offset] = trim_delta.get(our_offset, 0) + 4 * len(gone)

    def extra_length(offset):
        return sum(len(raw) for (owner, _code), raw in extras.items()
                   if owner == offset)

    def plan(pairs):
        for our_die, _retail_die in pairs:
            new_at[our_die.offset] = cursor[0]
            cursor[0] += (our_die.length + extra_length(our_die.offset)
                          + name_delta.get(our_die.offset, 0)
                          - trim_delta.get(our_die.offset, 0))
            children = children_of[our_die.offset]
            plan(children)
            # The four-byte terminator belongs to the *surviving* child chain.  A chain
            # whose records were all dropped as extras has no chain left to terminate, and
            # its bytes are not laid out -- so the end of its subtree is the record's own
            # end, exactly as ``emit`` writes it.
            if children:
                start, stop = residues[our_die.offset]
                cursor[0] += stop - start
            new_end[our_die.offset] = cursor[0]

    cursor = [base]
    plan(root_pairs)
    # Anything after the last top-level DIE (a chain terminator, in a chunk that carries
    # one) is not part of any record; it is copied verbatim, and the caller's byte compare
    # is what catches a difference there.
    tail = subtree_end(roots[-1]) if roots else base
    if not (base <= tail <= end):
        raise Refusal(f"the emitted chunk's last DIE ends at 0x{tail:X}, past the chunk")

    # AT_sibling is a positional word: once an extra record is dropped and the offsets are
    # final, the value the emitted record carries no longer names its subtree's end.  The
    # target is the layout's own end-of-subtree offset -- the arithmetic this encoder writes
    # the chunk with, which counts a child chain's terminator only when the chain still has
    # records.  A surviving record that carries the attribute but has no laid-out position
    # would be a guess, so it refuses.
    sibling_targets, sibling_changes = {}, []
    for our_die in by_offset.values():
        if AT_SIBLING not in our_die.attrs or our_die.offset in dropped_offsets:
            continue
        target = new_end.get(our_die.offset)
        if target is None:
            raise Refusal(f"{_describe(our_die, base)} carries AT_sibling but has no "
                          f"position in the laid-out chunk")
        sibling_targets[new_at[our_die.offset]] = target
        if our_die.attrs[AT_SIBLING] != target:
            sibling_changes.append((our_die.attrs[AT_SIBLING], target,
                                    _describe(our_die, base)))

    rewritten = []

    def reference(value, die, code):
        """The new value of one intra-chunk reference, or ``None`` to leave it alone."""
        if not (base <= value < end):
            return None                     # another section's offset, not this chunk's
        if value in dropped_offsets:
            twin = redirect_of.get(value)
            if twin is not None:
                moved = new_at[twin]
                rewritten.append((value, moved, _describe(die, base), code))
                return moved
            raise Refusal(f"{_describe(die, base)}: reference 0x{value:08X} (attribute "
                          f"0x{code:04X}) points at a DIE dropped as an extra record; "
                          f"retail carries no such target")
        moved = new_at.get(value)
        if moved is None:
            raise Refusal(f"{_describe(die, base)}: reference 0x{value:08X} (attribute "
                          f"0x{code:04X}) names no DIE in the chunk")
        if moved != value:
            rewritten.append((value, moved, _describe(die, base), code))
        return moved

    def _trim_lists(span, offset):
        """``span`` without the trimmed entries, its length words following."""
        out = bytearray(span)
        for (owner, code), gone in sorted(trimmed.items(), reverse=True):
            if owner != offset:
                continue
            for field, form, at, size in _fields(bytes(out)):
                if field != code:
                    continue
                if gone == "all":
                    width = 2 if form == 3 else 4
                    del out[at - width - 2:at + size]
                    break
                payload = out[at:at + size]
                for position in sorted(gone, reverse=True):
                    del payload[position:position + 4]
                width = 2 if form == 3 else 4
                struct.pack_into("<H" if form == 3 else "<I", out, at - width, len(payload))
                out[at:at + size] = payload
                break
        _P32(out, 0, len(out))
        return bytes(out)

    def record(die):
        span = emitted[die.offset - base:die.offset - base + die.length]
        if trim_delta.get(die.offset):
            span = _trim_lists(span, die.offset)
        extra = [(code, raw) for (owner, code), raw in extras.items()
                 if owner == die.offset]
        name = name_raw.get(die.offset)
        if extra or name is not None:
            ours_attrs = dict(_raw_attributes(span))
            if name is not None:
                ours_attrs[debug_set.AT_NAME] = name
            adopted = dict(extra)
            if extra:
                # Retail's attribute sequence is the compiler's emission order, not the
                # code order: rebuild in retail's order, keeping our bytes for every
                # attribute the two records share and the adopted bytes for the rest.
                retail_die = retail_of[die.offset]
                theirs = retail[retail_die.offset - base:
                                retail_die.offset - base + retail_die.length]
                order = [code for code, _raw in _raw_attributes(theirs)]
                stray = set(ours_attrs) - set(order)
                if stray:
                    raise Refusal(f"{_describe(die, base)}: the emitted record carries "
                                  f"attribute(s) retail's does not: "
                                  + ", ".join(f"0x{code:04X}" for code in sorted(stray)))
            else:
                order = [code for code, _raw in _raw_attributes(span)]
            rebuilt = bytearray(span[:6])
            for code in order:
                if code in ours_attrs:
                    rebuilt += ours_attrs[code]
                elif code in adopted:
                    rebuilt += adopted[code]
                else:
                    raise Refusal(f"{_describe(die, base)}: retail carries attribute "
                                  f"0x{code:04X} that adoption did not supply")
            _P32(rebuilt, 0, len(rebuilt))
            span = bytes(rebuilt)
        out = bytearray(span)
        for code, form, at, size in _fields(out):
            if code == AT_SIBLING:
                target = sibling_targets.get(new_at[die.offset])
                if target is None:
                    raise Refusal(f"{_describe(die, base)} carries AT_sibling but its "
                                  f"target is not determined by the laid-out chunk")
                _P32(out, at, target)
                continue
            if form == 2:
                value = _U32(out, at)[0]
                moved = reference(value, die, code)
                if moved is not None:
                    _P32(out, at, moved)
            elif form in (3, 4) and size:
                payload = out[at:at + size]
                positions = _block_references(code, payload)
                for position in positions if positions is not None else ():
                    value = _U32(payload, position)[0]
                    moved = reference(value, die, code)
                    if moved is not None:
                        _P32(payload, position, moved)
                out[at:at + size] = payload
        return bytes(out)

    def emit(pairs):
        out = bytearray()
        for our_die, _retail_die in pairs:
            out += record(our_die)
            children = children_of[our_die.offset]
            if children:
                out += emit(children)
                start, stop = residues[our_die.offset]
                out += emitted[start - base:stop - base]
        return bytes(out)

    chunk = emit(root_pairs) + emitted[tail - base:]
    if not drop_extra and not adopt_missing and len(chunk) != len(emitted):
        raise Refusal(f"the rewritten chunk is 0x{len(chunk):X} bytes against the emitted "
                      f"0x{len(emitted):X}; the DIE records were not reordered freely")
    moved = sum(1 for offset in new_at if new_at[offset] != offset)
    return Reordered(chunk, len(new_at), moved, len(rewritten), rewritten, dropped,
                     name_changes, adopted_attributes, sibling_changes, sibling_targets)
