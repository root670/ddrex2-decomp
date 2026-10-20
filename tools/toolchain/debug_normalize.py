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
   ``(tag, attributes with references normalised to their target's shallow description,
   sorted child signatures)``, so identical structures are paired in emission order and a
   different set refuses (:mod:`toolchain.debug_set`'s signature, made recursive);
3. lay out our DIE records in retail's sibling order, recursively (a lexical block reorders
   its own children, not the top level only), keeping each chain's trailing bytes verbatim;
4. recompute every ``AT_sibling`` from the new layout, and rewrite every intra-chunk offset
   reference through the source-to-new offset map;
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

import struct

from toolchain import debug_set

AT_SIBLING = debug_set.AT_SIBLING          # 0x0012, recomputed positionally
AT_SUBSCR_DATA = debug_set.AT_SUBSCR_DATA  # 0x00a3
AT_MOD_U_D_TYPE = debug_set.AT_MOD_U_D_TYPE  # 0x0083
#: The MW attribute measured as a bare 4-byte reference in every one of its 1782
#: occurrences across retail's ``.debug``.
AT_2303 = 0x2303

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

    __slots__ = ("chunk", "dies", "moved", "references")

    def __init__(self, chunk, dies, moved, references):
        self.chunk = chunk          # the rewritten bytes, at the same ``base``
        self.dies = dies            # DIEs emitted
        self.moved = moved          # DIEs whose new offset is not their old one
        self.references = references  # intra-chunk references rewritten


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


def _pair(ours, theirs, our_key, retail_key, base, where, locator=None):
    """Pair two sibling lists one-to-one; refuse on any set difference.

    Identical signatures are paired in emission order -- the only pairing they admit, and
    the same convention the gate's permutation count uses.  ``locator`` turns a refusal into
    the *deepest* difference (see :func:`_mismatch`) instead of naming the container.
    """
    if len(ours) != len(theirs):
        raise Refusal((locator() if locator else "")
                      or f"{where} holds {len(ours)} DIEs against retail's {len(theirs)}")
    buckets = {}
    for die in ours:
        buckets.setdefault(our_key(die), []).append(die)
    pairs = []
    for die in theirs:
        bucket = buckets.get(retail_key(die))
        if not bucket:
            raise Refusal(
                (locator() if locator else "")
                or f"the DIE set differs: {_describe(die, base)} has no counterpart in the "
                   f"emitted chunk")
        pairs.append((bucket.pop(0), die))
    leftover = next((dies[0] for dies in buckets.values() if dies), None)
    if leftover is not None:
        raise Refusal((locator() if locator else "")
                      or f"the DIE set differs: {_describe(leftover, base)} has no "
                         f"counterpart in retail")
    return pairs


def normalise(emitted: bytes, retail: bytes, base: int = 0, ignore=None) -> Reordered:
    """Rewrite ``emitted`` into ``retail``'s DIE order, at the same ``base`` in ``.debug``.

    The result carries retail's DIE *sequence*; whether it is retail's *bytes* is the
    caller's comparison, and a difference must be a refusal there.  Raises :class:`Refusal`
    when the chunk cannot be rewritten at all: a different DIE set, a chunk that is not a
    contiguous DIE sequence, an unknown attribute form, or a reference that lies inside the
    chunk but names no DIE.

    ``ignore`` names attributes whose value is excluded from the pairing signature.  The
    metadata-adoption step passes ``AT_location`` for locals: the location is being adopted
    from retail, so it must not stop the two records from pairing.
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
    roots = [die for die in ours if die.parent is None]
    retail_roots = [die for die in theirs if die.parent is None]

    def locator(ours_level, theirs_level, where):
        """The deepest difference in this level, for the refusal :func:`_pair` raises."""
        return lambda: _mismatch(ours_level, theirs_level, our_shallow, retail_shallow,
                                 base, where)

    new_at, new_end, children_of = {}, {}, {}

    def plan(pairs):
        for our_die, retail_die in pairs:
            where = f"the children of {_describe(retail_die, base)}"
            children_of[our_die.offset] = _pair(
                our_die.children, retail_die.children, our_key, retail_key, base, where,
                locator=locator(our_die.children, retail_die.children, where))
            new_at[our_die.offset] = cursor[0]
            cursor[0] += our_die.length
            plan(children_of[our_die.offset])
            if our_die.children:
                start, stop = residues[our_die.offset]
                cursor[0] += stop - start
            new_end[our_die.offset] = cursor[0]

    cursor = [base]
    root_pairs = _pair(roots, retail_roots, our_key, retail_key, base, "the chunk",
                       locator=locator(roots, retail_roots, "the chunk"))
    plan(root_pairs)
    # Anything after the last top-level DIE (a chain terminator, in a chunk that carries
    # one) is not part of any record; it is copied verbatim, and the caller's byte compare
    # is what catches a difference there.
    tail = subtree_end(roots[-1]) if roots else base
    if not (base <= tail <= end):
        raise Refusal(f"the emitted chunk's last DIE ends at 0x{tail:X}, past the chunk")

    rewritten = []

    def reference(value, die, code):
        """The new value of one intra-chunk reference, or ``None`` to leave it alone."""
        if not (base <= value < end):
            return None                     # another section's offset, not this chunk's
        moved = new_at.get(value)
        if moved is None:
            raise Refusal(f"{_describe(die, base)}: reference 0x{value:08X} (attribute "
                          f"0x{code:04X}) names no DIE in the chunk")
        if moved != value:
            rewritten.append((value, moved))
        return moved

    def record(die):
        span = emitted[die.offset - base:die.offset - base + die.length]
        out = bytearray(span)
        for code, form, at, size in _fields(out):
            if code == AT_SIBLING:
                _P32(out, at, new_end[die.offset])
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
    if len(chunk) != len(emitted):
        raise Refusal(f"the rewritten chunk is 0x{len(chunk):X} bytes against the emitted "
                      f"0x{len(emitted):X}; the DIE records were not reordered freely")
    moved = sum(1 for die in ours if new_at[die.offset] != die.offset)
    return Reordered(chunk, len(ours), moved, len(rewritten))
