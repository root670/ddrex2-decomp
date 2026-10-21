"""The opt-in ``.debug`` DIE-order normaliser: reorder, remap, prove byte-identity.

The normaliser's contract has two halves, and each test here pins one of them: a chunk that
is retail's DIE *set* in another order is rewritten into retail's bytes, and a chunk that is
not -- a different set, a different size, a reference that names no DIE -- refuses rather
than emit a plausible wrong chunk.  The last two tests drive the ``compile.py`` seam: the
step is opt-in, it prints what it normalised, and a rewritten chunk that is not
byte-identical is a refusal.

The chunks are synthetic, built with the DWARF 1 encoder :mod:`tests.toolchain.test_debug_set`
already uses, so the tests need no compiler: what is under test is the reordering and the
offset arithmetic, not the compiler's output.  The real net_grf chunk proof lives in
``reports/debug-normalize-report.md``.
"""

import pathlib
import struct
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import compile as cc  # noqa: E402
from toolchain import debug_normalize as dn  # noqa: E402
from tests.toolchain.test_debug_set import Die, _attribute, _encoded_length  # noqa: E402

AT_SIBLING = 0x0012
AT_LOCATION = 0x0023
AT_NAME = 0x0038
AT_FUND_TYPE = 0x0055
AT_USER_DEF_TYPE = 0x0072
AT_SUBSCR_DATA = 0x00A3
AT_MOD_U_D_TYPE = 0x0083
AT_BYTE_SIZE = 0x00B6
AT_LOW_PC = 0x0111
AT_HIGH_PC = 0x0121


class Lazy:
    """A block attribute whose payload is built *after* the offsets are known.

    A block that carries a DIE reference has to name the target's final offset, and the
    offset is only known once every record's length is; ``__len__`` is the fixed payload
    length, so the layout pass and the encode pass agree.
    """

    def __init__(self, length, render):
        self._length = length
        self._render = render

    def __len__(self):
        return self._length

    def render(self):
        return self._render()


def _record_size(die):
    """The bytes one DIE's own record occupies: length, tag, attributes, ``AT_sibling``."""
    return 6 + sum(_encoded_length(code, value) for code, value in die.attrs) + 6


def _subtree_length(die):
    """The bytes this DIE's record, its descendants and its chain terminator occupy.

    This is the Metrowerks shape retail's chunks have: every DIE carries an ``AT_sibling``
    equal to its subtree's end, a DIE with children is followed by a four-byte null that
    terminates the chain, and a parent's ``AT_sibling`` includes that null.
    """
    total = _record_size(die)
    if die.children:
        total += sum(_subtree_length(child) for child in die.children) + 4
    return total


def build(root):
    """Encode one DIE tree as a chunk; a form-2 value may be the target ``Die`` itself."""
    cursor = [0]

    def assign(die):
        die.offset = cursor[0]
        cursor[0] += _record_size(die)
        for child in die.children:
            assign(child)
        if die.children:
            cursor[0] += 4               # the chain terminator, inside this DIE's subtree

    assign(root)

    def value(one):
        if isinstance(one, Die):
            return one.offset
        if isinstance(one, Lazy):
            return one.render()
        return one

    def encode(die):
        body = struct.pack("<H", die.tag)
        for code, one in die.attrs:
            body += _attribute(code, value(one))
        body += _attribute(AT_SIBLING, die.offset + _subtree_length(die))
        record = struct.pack("<I", len(body) + 4) + body
        children = b"".join(encode(child) for child in die.children)
        return record + (children + b"\x00\x00\x00\x00" if die.children else b"")

    return encode(root)


def subscript(upper_bound, element):
    """One DWARF 1 subscript entry with its element type: a fundamental type, or a DIE.

    The entries are retail's own shape (``com_scrollbar``'s arrays read
    ``('index-ft', 10), ('bound', 0), ('bound', 21), ('et', 0x55, 1)``): a format byte, the
    index type, a lower and an upper bound, then the element type as a *form 2 attribute*
    naming a DIE -- which is the reference that moves with the arrays.
    """
    fixed = 1 + 2 + 4 + 4 + 1 + 2

    def render():
        payload = (struct.pack("<B", 0) + struct.pack("<H", 0x000A)
                   + struct.pack("<I", 0) + struct.pack("<I", upper_bound)
                   + struct.pack("<B", 8))
        if isinstance(element, Die):
            return payload + struct.pack("<H", AT_USER_DEF_TYPE) + struct.pack(
                "<I", element.offset)
        return payload + struct.pack("<H", AT_FUND_TYPE) + struct.pack("<H", element)

    # ``FMT_ET`` (0x08) then an attribute code: form 2 is 4 bytes of reference, form 5 is a
    # 2-byte fundamental type.  Both passes see the same length.
    return Lazy(fixed + (4 if isinstance(element, Die) else 2), render)


def subscript_mod_u_d(upper_bound, element):
    """A subscript entry whose element type is a form-3 modifier block.

    ``AT_mod_u_d_type`` (0x0083) has form 3, so its value is a block: the modifier flags,
    then a 4-byte DIE reference.  The compiler writes an array of a user-defined type this
    way; the reference moves with the DIE order exactly as the form-2 one above does, and
    the flags stay put.
    """
    fixed = 1 + 2 + 4 + 4 + 1 + 2
    block = 1 + 4                        # one flags byte, one DIE reference

    def render():
        payload = (struct.pack("<B", 0) + struct.pack("<H", 0x000A)
                   + struct.pack("<I", 0) + struct.pack("<I", upper_bound)
                   + struct.pack("<B", 8))
        target = element.offset if isinstance(element, Die) else element
        element_block = struct.pack("<B", 0) + struct.pack("<I", target)
        return (payload + struct.pack("<HH", AT_MOD_U_D_TYPE, len(element_block))
                + element_block)

    return Lazy(fixed + 2 + block, render)


def mod_u_d_types(ours, form3=True, ref=None):
    """One array of a user-defined type, and the struct it holds.

    ``ours`` puts the array before the aggregate, retail puts the aggregate first, so the
    element reference inside ``AT_subscr_data`` names a DIE that moved.  ``ref`` replaces
    the reference with a raw word, for the guard that refuses one naming no DIE.
    """
    aggregate = Die(0x0013, [(AT_NAME, "@anon0"), (AT_BYTE_SIZE, 12)],
                    [member("x", 0)])
    element = subscript_mod_u_d(2, aggregate if ref is None else ref)
    if not form3:
        element = subscript(2, aggregate if ref is None else ref)
    array = Die(0x0001, [(AT_SUBSCR_DATA, element)])
    table = Die(0x000C, [(AT_NAME, "table"), (AT_USER_DEF_TYPE, array)])
    order = [array, aggregate] if ours else [aggregate, array]
    return Die(0x0011, [(AT_NAME, "net_win_any.c")], [table] + order)


def mixed_types(ours):
    """A form-2 array and a form-3 array of the same aggregate, so both paths run at once."""
    aggregate = Die(0x0013, [(AT_NAME, "@anon0"), (AT_BYTE_SIZE, 12)],
                    [member("x", 0)])
    form2 = Die(0x0001, [(AT_SUBSCR_DATA, subscript(2, aggregate))])
    form3 = Die(0x0001, [(AT_SUBSCR_DATA, subscript_mod_u_d(2, aggregate))])
    table = Die(0x000C, [(AT_NAME, "table"), (AT_USER_DEF_TYPE, form3)])
    order = [form2, form3, aggregate] if ours else [aggregate, form2, form3]
    return Die(0x0011, [(AT_NAME, "net_win_any.c")], [table] + order)


def member(name, offset, fund_type=7):
    return Die(0x000D, [(AT_NAME, name), (AT_FUND_TYPE, fund_type),
                        (AT_LOCATION, bytes([0x6B, 0x04, offset, 0, 0, 0, 0x07]))])


def _location(literal):
    """An eight-byte location block whose second word is ``literal``.

    A location is an expression or an address: arbitrary bytes that can *contain* a word
    equal to an offset in the chunk.  That word must survive the reordering verbatim, which
    is what :func:`test_a_location_blocks_bytes_are_never_mistaken_for_a_reference` pins.
    """
    return bytes(4) + struct.pack("<I", literal)


def net_grf_types(ours):
    """net_grf's types CU in one of the two measured orders.

    ``ours`` is the ``3.0b38-030307`` order: the two ``char`` arrays and the array of struct
    come before the aggregates, where retail puts the aggregates first.  The local's type
    reference and the array-of-struct's element reference both move with them.
    """
    aggregate = Die(0x0013, [(AT_NAME, "@anon0"), (AT_BYTE_SIZE, 12)],
                    [member("x", 0), member("y", 4)])
    union = Die(0x0017, [(AT_NAME, "@anon1"), (AT_BYTE_SIZE, 4)],
                [member("id", 0, fund_type=8)])
    array22 = Die(0x0001, [(AT_SUBSCR_DATA, subscript(21, 1))])
    array1024 = Die(0x0001, [(AT_SUBSCR_DATA, subscript(1023, 1))])
    array_of_struct = Die(0x0001, [(AT_SUBSCR_DATA, subscript(2, aggregate))])
    dancer = Die(0x000C, [(AT_NAME, "dancer_num"), (AT_USER_DEF_TYPE, array22)])
    if ours:
        order = [array22, array1024, array_of_struct, aggregate, union]
    else:
        order = [aggregate, union, array22, array1024, array_of_struct]
    return Die(0x0011, [(AT_NAME, "net_grf.c")], [dancer] + order)


def function_cu(ours, location=0x20):
    """A function CU whose lexical block's locals are the ``3.0`` family's reversed order."""
    array22 = Die(0x0001, [(AT_SUBSCR_DATA, subscript(21, 1))])
    ret = Die(0x000C, [(AT_NAME, "r"), (AT_FUND_TYPE, 8), (AT_LOCATION, _location(location))])
    tmp = Die(0x000C, [(AT_NAME, "tmp"), (AT_USER_DEF_TYPE, array22),
                       (AT_LOCATION, _location(0x40))])
    ap = Die(0x000C, [(AT_NAME, "ap"), (AT_FUND_TYPE, 8),
                      (AT_LOCATION, _location(0x2B8C20))])
    block = Die(0x000B, [(AT_LOW_PC, 0x001EBD40), (AT_HIGH_PC, 0x001EBDE8)],
                [ap, tmp, ret] if ours else [ret, tmp, ap])
    body = Die(0x0006, [(AT_NAME, "peerPrintf"), (AT_LOW_PC, 0x001EBD40),
                        (AT_HIGH_PC, 0x001EBDE8)], [block])
    return Die(0x0011, [(AT_NAME, "net_grf.c")], [body])


def _ref_position(chunk_bytes, name, code):
    """Where the value of ``code`` sits inside the DIE called ``name``, in ``chunk_bytes``."""
    from toolchain import debug_set

    for die in debug_set.parse(chunk_bytes, 0):
        if die.name == name:
            for field_code, _form, at, _size in dn._fields(
                    chunk_bytes[die.offset:die.offset + die.length]):
                if field_code == code:
                    return die.offset + at
            raise AssertionError(f"{name} has no attribute 0x{code:04X}")
    raise AssertionError(f"no DIE called {name}")


# -- the rewrite: order, nesting, and the references that move with them -------------------


def test_a_types_block_is_rewritten_into_retails_order_byte_for_byte():
    retail = build(net_grf_types(ours=False))
    emitted = build(net_grf_types(ours=True))

    assert len(emitted) == len(retail)
    assert emitted != retail
    result = dn.normalise(emitted, retail)

    assert result.chunk == retail
    assert result.dies == 10        # CU, local, 2 aggregates, 3 members, 3 arrays, 1 member
    assert result.moved > 0
    # The local's type reference and the array-of-struct's element reference both moved.
    assert result.references >= 2


def test_a_lexical_blocks_children_are_reordered_too():
    retail = build(function_cu(ours=False))
    emitted = build(function_cu(ours=True))

    assert len(emitted) == len(retail)
    assert emitted != retail
    result = dn.normalise(emitted, retail)

    assert result.chunk == retail
    # The top level is a single CU and it does not move: the only thing that can have moved
    # is the block's own child list, whose ``AT_sibling`` chain is what the offsets recompute.
    assert result.moved >= 1


def test_a_chunk_already_in_retails_order_is_unchanged():
    retail = build(net_grf_types(ours=False))

    result = dn.normalise(retail, retail)

    assert result.chunk == retail
    assert result.moved == 0
    assert result.references == 0


def test_a_location_blocks_bytes_are_never_mistaken_for_a_reference():
    # A location block is arbitrary bytes, and here its second word is exactly the offset of
    # the ``r`` local in *our* chunk -- an in-chunk DIE offset, aligned, that a scan for
    # "looks like an offset" would rewrite.  ``r`` is the block's *first* child in retail and
    # its last in ours, so that rewrite is visibly wrong: the block must be copied verbatim.
    from toolchain import debug_set

    probe = debug_set.parse(build(function_cu(ours=True)), 0)
    literal = next(die.offset for die in probe if die.name == "r")
    retail = build(function_cu(ours=False, location=literal))
    emitted = build(function_cu(ours=True, location=literal))

    result = dn.normalise(emitted, retail)

    assert result.chunk == retail
    assert result.moved >= 1         # the block's children did move
    assert struct.pack("<I", literal) in emitted


def test_a_form_3_element_reference_pairs_and_is_rewritten():
    # The array's element type is a modifier block whose 4-byte reference names the
    # aggregate; the two chunks differ only in where that aggregate sits.  Comparing the
    # block's bytes would see two different arrays; resolving the reference pairs them.
    retail = build(mod_u_d_types(ours=False))
    emitted = build(mod_u_d_types(ours=True))

    assert len(emitted) == len(retail)
    assert emitted != retail
    result = dn.normalise(emitted, retail)

    assert result.chunk == retail
    assert result.references >= 2       # the local's type and the embedded element ref


def test_form_2_and_form_3_element_references_rewrite_together():
    # One chunk carries both encodings, each naming the same aggregate.  The form-2 case is
    # unchanged by the form-3 handling, and both references move with the aggregate.
    retail = build(mixed_types(ours=False))
    emitted = build(mixed_types(ours=True))

    assert len(emitted) == len(retail)
    assert emitted != retail
    result = dn.normalise(emitted, retail)

    assert result.chunk == retail
    assert result.references >= 3       # the local's type and both element refs


def test_a_form_3_element_reference_to_a_different_shape_refuses():
    # The reference resolves, but to a structure whose size is not retail's: normalising
    # the reference must not paper over an element type that genuinely differs.
    retail = build(mod_u_d_types(ours=False))
    ours = mod_u_d_types(ours=True)
    ours.children[2].attrs[1] = (AT_BYTE_SIZE, 16)    # @anon0 is a different type

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(build(ours), retail)

    assert "no counterpart" in str(excinfo.value)
    # The array's key now carries its element's shape, so the array -- and the local that
    # names it -- are what differ; the refusal is unchanged.
    assert "local_variable 'table'" in str(excinfo.value)


def nested_arrays(bounds, holder_bound=0x10000, outer_bound=2, element=1):
    """One CU of ``[outer_bound][bound]`` chains, in the given order, plus a local naming one.

    The chains are retail's shape: the outer array's ``AT_subscr_data`` names the inner
    array by a form-2 DIE reference, so the only thing that separates ``[3][65536]`` from
    ``[3][45568]`` is the key's recursion into the inner array's own bound.  Every chain
    has the same tag, no name and no byte size -- a shallow key cannot tell them apart.
    """
    chains = []
    for bound in bounds:
        inner = Die(0x0001, [(AT_SUBSCR_DATA, subscript(bound, element))])
        outer = Die(0x0001, [(AT_SUBSCR_DATA, subscript(outer_bound, inner))])
        chains.append((bound, outer, inner))
    holder = Die(0x000C, [(AT_NAME, "m"),
                          (AT_USER_DEF_TYPE,
                           next((outer for bound, outer, _inner in chains
                                 if bound == holder_bound), chains[0][1]))])
    return Die(0x0011, [(AT_NAME, "doll.c")],
               [holder] + [die for _bound, outer, inner in chains
                           for die in (outer, inner)])


def _array_dies(chunk_bytes):
    """``(outer, inner, by_offset)``: the array DIEs, split by what their element is."""
    from toolchain import debug_set

    dies = debug_set.parse(chunk_bytes, 0)
    by_offset = {die.offset: die for die in dies}
    outer, inner = [], []
    for die in dies:
        if die.tag != 0x0001:
            continue
        element = debug_set._subscript_key(die.attrs[AT_SUBSCR_DATA], by_offset)[1][-1][2]
        (outer if isinstance(element, tuple) else inner).append(die)
    return outer, inner, by_offset


def test_arrays_differing_only_in_a_nested_bound_do_not_pair():
    from toolchain import debug_set

    low_outer, _low_inner, low_by_offset = _array_dies(build(nested_arrays([0x10000])))
    high_outer, _high_inner, high_by_offset = _array_dies(build(nested_arrays([0xB200])))

    # The shallow key's whole input is equal -- tag, absent name, absent byte size -- which
    # is what used to make these two arrays interchangeable.
    assert ((low_outer[0].tag, low_outer[0].name, low_outer[0].attrs.get(AT_BYTE_SIZE))
            == (high_outer[0].tag, high_outer[0].name,
                high_outer[0].attrs.get(AT_BYTE_SIZE)))

    assert (debug_set._target_key(low_outer[0].offset, low_by_offset)
            != debug_set._target_key(high_outer[0].offset, high_by_offset))
    assert (dn._shallow_key(low_by_offset)(low_outer[0])
            != dn._shallow_key(high_by_offset)(high_outer[0]))


def test_identical_nested_arrays_pair_at_any_offset():
    from toolchain import debug_set

    outer, inner, by_offset = _array_dies(build(nested_arrays([0x10000, 0x10000])))

    assert len(outer) == 2 and len(inner) == 2
    assert outer[0].offset != outer[1].offset
    assert (debug_set._target_key(outer[0].offset, by_offset)
            == debug_set._target_key(outer[1].offset, by_offset))
    assert dn._shallow_key(by_offset)(outer[0]) == dn._shallow_key(by_offset)(outer[1])


def test_a_reordered_chain_of_nested_arrays_pairs_by_its_nested_bound():
    # All three chains have the same shallow key, and only their inner bounds separate
    # them: a shallow pairing would land each bound in another chain's slot and the
    # rewritten chunk would not be retail's.
    retail = build(nested_arrays([0x10000, 0xB200, 0x15300]))
    emitted = build(nested_arrays([0xB200, 0x15300, 0x10000]))

    assert len(emitted) == len(retail)
    assert emitted != retail
    result = dn.normalise(emitted, retail)

    assert result.chunk == retail
    assert result.references >= 3       # the local's type and two element references


def test_a_genuine_array_shape_difference_still_refuses():
    retail = build(nested_arrays([0x10000]))
    ours = build(nested_arrays([0x10000], outer_bound=3))

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(ours, retail)

    assert "no counterpart" in str(excinfo.value)


def test_a_form_3_element_reference_that_names_no_die_refuses():
    # Both chunks carry the same broken element reference -- an in-chunk word that names no
    # DIE -- so the set comparison passes it and only the normaliser's guard refuses.
    from toolchain import debug_set

    retail = build(mod_u_d_types(ours=False, ref=1))
    emitted = build(mod_u_d_types(ours=True, ref=1))
    assert debug_set.classify(emitted, retail).ok

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(emitted, retail)

    assert "names no DIE in the chunk" in str(excinfo.value)
    assert "0x00000001" in str(excinfo.value)


# -- refusals: a different set, a different size, a reference that names nothing ------------


def test_an_extra_member_refuses_and_names_the_container():
    retail = build(net_grf_types(ours=False))
    ours = net_grf_types(ours=True)
    ours.children[4].children.append(member("z", 8))     # the struct gains a member

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(build(ours), retail)

    assert "holds 3 DIEs against retail's 2" in str(excinfo.value)
    assert "structure_type" in str(excinfo.value)


def test_a_missing_die_refuses():
    retail = build(net_grf_types(ours=False))
    ours = net_grf_types(ours=True)
    del ours.children[5]                                  # the union is gone

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(build(ours), retail)

    assert "holds 5 DIEs against retail's 6" in str(excinfo.value)


def test_a_changed_size_refuses_as_a_set_difference():
    retail = build(net_grf_types(ours=False))
    ours = net_grf_types(ours=True)
    ours.children[4].attrs[1] = (AT_BYTE_SIZE, 16)        # @anon0 is a different type

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(build(ours), retail)

    assert "no counterpart" in str(excinfo.value)
    assert "@anon0" in str(excinfo.value)


def test_a_reference_that_names_no_die_refuses():
    # Both chunks carry the *same* broken reference -- a word inside the chunk that names no
    # DIE -- so the set comparison sees no difference at all (retail is as broken as we are)
    # and only the normaliser's own guard stands between that and a plausible wrong chunk.
    from toolchain import debug_set

    def broken(ours):
        chunk = bytearray(build(net_grf_types(ours)))
        at = _ref_position(bytes(chunk), "dancer_num", AT_USER_DEF_TYPE)
        struct.pack_into("<I", chunk, at, 1)              # in-chunk, and no DIE starts there
        return bytes(chunk)

    retail, emitted = broken(ours=False), broken(ours=True)
    assert debug_set.classify(emitted, retail).ok         # the set comparison passes it

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(emitted, retail)

    assert "names no DIE in the chunk" in str(excinfo.value)
    assert "0x00000001" in str(excinfo.value)


def test_a_chunk_that_is_not_a_contiguous_die_sequence_refuses():
    # A hole inside a child chain: four bytes that belong to no DIE.  The records still
    # parse -- a null entry is skipped -- so nothing else would notice, and the reordering
    # would silently drop the hole.  It has to refuse.
    from toolchain import debug_set

    emitted = build(net_grf_types(ours=True))
    second = debug_set.parse(emitted, 0)[2]
    holed = emitted[:second.offset] + b"\x00\x00\x00\x00" + emitted[second.offset:]

    with pytest.raises(dn.Refusal) as excinfo:
        dn.normalise(holed, holed)

    assert "not a contiguous DIE sequence" in str(excinfo.value)


# -- the compile.py seam: opt-in, printed, and byte-identical or nothing -------------------


def test_the_step_is_opt_in_and_prints_what_it_normalised(capsys):
    retail = build(net_grf_types(ours=False))
    emitted = build(net_grf_types(ours=True))

    placed = cc.debug_promotion("src/network/net_grf.c", text=b"code", line=b"line",
                               debug=emitted, retail_text=b"code", retail_line=b"line",
                               retail_debug=retail, normalise=True)

    assert placed == retail
    error = capsys.readouterr().err
    assert ".debug normalised to retail's DIE order" in error
    assert "byte-identical to retail" in error
    assert "tu_builds comment" in error


def test_without_the_flag_the_set_equal_boundary_still_keeps_retails_chunk(capsys):
    retail = build(net_grf_types(ours=False))
    emitted = build(net_grf_types(ours=True))

    placed = cc.debug_promotion("src/network/net_grf.c", text=b"code", line=b"line",
                               debug=emitted, retail_text=b"code", retail_line=b"line",
                               retail_debug=retail)

    assert placed == retail
    assert "anonymous-type DIE-order boundary" in capsys.readouterr().err


def test_a_normalised_chunk_that_is_not_byte_identical_refuses(capsys):
    # Both chunks carry a four-byte chain terminator, so their DIEs, lengths and sets are
    # retail's -- but ours ends with a byte retail's does not.  Nothing but the byte compare
    # can see that, which is exactly what the step has to refuse on.
    retail = build(net_grf_types(ours=False)) + b"\x00\x00\x00\x00"
    emitted = build(net_grf_types(ours=True)) + b"\x01\x00\x00\x00"

    with pytest.raises(cc.Unusable) as excinfo:
        cc.debug_promotion("src/network/net_grf.c", text=b"code", line=b"line",
                           debug=emitted, retail_text=b"code", retail_line=b"line",
                           retail_debug=retail, normalise=True)

    assert "condition 5 (.debug DIE-order normalisation) failed" in str(excinfo.value)
    assert "first differing byte at 0x" in str(excinfo.value)
