"""The set-equal ``.debug`` gate: the anonymous-type DIE-order class only.

The gate exists because retail's ``@anonN`` numbering is a property of the original
declaration walk, not of the header a reconstruction can write.  These tests pin the line
between that class and wrong C: a permutation of the anonymous indices is accepted; a
different DIE set, a different length, or a ``.text``/``.line`` byte difference refuses.
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
from toolchain import debug_set  # noqa: E402

AT_SIBLING = 0x0012
AT_LOCATION = 0x0023
AT_NAME = 0x0038
AT_FUND_TYPE = 0x0055
AT_BYTE_SIZE = 0x00B6


# -- a minimal DWARF 1 encoder, so the comparison is tested without a compiler ------------


class Die:
    def __init__(self, tag, attrs=(), children=()):
        self.tag = tag
        self.attrs = list(attrs)
        self.children = list(children)
        self.offset = 0

    def end(self):
        return self.offset + 6 + _attrs_size(self) + sum(child.end() for child in self.children)


def _encoded_length(code, value):
    form = code & 0x0F
    if form in (1, 2, 6):
        return 2 + 4
    if form == 5:
        return 2 + 2
    if form == 8:
        return 2 + len(value.encode("latin-1")) + 1
    if form in (3, 4):
        return 2 + (2 if form == 3 else 4) + len(value)
    if form == 7:
        return 2 + 8
    raise AssertionError(f"unsupported form {form}")


def _attrs_size(die):
    total = sum(_encoded_length(code, value) for code, value in die.attrs)
    if die.children:
        total += _encoded_length(AT_SIBLING, 0)   # the parent's sibling pointer
    return total


def _attribute(code, value):
    form = code & 0x0F
    if form in (1, 2, 6):
        return struct.pack("<HI", code, value)
    if form == 5:
        return struct.pack("<HH", code, value)
    if form == 8:
        return struct.pack("<H", code) + value.encode("latin-1") + b"\0"
    if form == 3:
        return struct.pack("<HH", code, len(value)) + value
    if form == 4:
        return struct.pack("<HI", code, len(value)) + value
    if form == 7:
        return struct.pack("<HQ", code, value)
    raise AssertionError(f"unsupported form {form}")


def chunk(root):
    """Encode one top-level DIE and its children as a ``.debug`` chunk."""
    cursor = [0]

    def assign(die):
        die.offset = cursor[0]
        cursor[0] += 6 + _attrs_size(die)
        for child in die.children:
            assign(child)

    assign(root)

    def encode(die):
        body = struct.pack("<H", die.tag)
        for code, value in die.attrs:
            body += _attribute(code, value)
        if die.children:
            body += _attribute(AT_SIBLING, die.end())
        # This parser (like Metrowerks' records) counts the four length bytes: the DIE
        # ends at ``offset + length`` and its attributes start at ``offset + 6``.
        payload = struct.pack("<I", len(body) + 4) + body
        return payload + b"".join(encode(child) for child in die.children)

    return encode(root)


def unit(*types):
    """A compile unit holding aggregate declarations, retail's types-block shape."""
    return Die(0x0011, [(AT_NAME, "unit.c")], types)


def structure(name, size, members):
    return Die(0x0013, [(AT_NAME, name), (AT_BYTE_SIZE, size)],
               [Die(0x000D, [(AT_NAME, member), (AT_LOCATION, bytes([offset])),
                             (AT_FUND_TYPE, 0x0007)])
                for member, offset in members])


def two_anonymous(second_name="@anon1"):
    return unit(structure("@anon0", 12, [("x", 0), ("y", 4)]),
                structure(second_name, 4, [("n", 0)]))


# -- condition 2: length and DIE count ----------------------------------------------------


def test_a_permuted_anonymous_index_is_the_accepted_class():
    retail = chunk(two_anonymous())
    emitted = chunk(two_anonymous(second_name="@anon1"))
    swapped = chunk(unit(structure("@anon1", 12, [("x", 0), ("y", 4)]),
                         structure("@anon0", 4, [("n", 0)])))

    assert len(swapped) == len(retail)
    outcome = debug_set.classify(swapped, retail)

    assert outcome.ok
    assert outcome.condition == 0
    assert outcome.die_count == 6          # CU + two structs + two members + one member
    assert outcome.anonymous == 2
    assert outcome.permuted == 2
    assert emitted == retail               # the control: no permutation, no deviation


def test_a_length_difference_refuses_and_names_the_first_offending_die():
    retail = chunk(two_anonymous())
    emitted = chunk(unit(structure("@anon10", 12, [("x", 0), ("y", 4)]),
                         structure("@anon1", 4, [("n", 0)])))

    assert len(emitted) == len(retail) + 1
    outcome = debug_set.classify(emitted, retail)

    assert not outcome.ok
    assert outcome.condition == 2
    assert "0x" in outcome.detail and "retail's" in outcome.detail
    assert "structure_type '@anon10'" in outcome.detail


def test_a_missing_die_refuses_and_names_it():
    retail = chunk(two_anonymous())
    emitted = chunk(unit(structure("@anon0", 12, [("x", 0), ("y", 4)])))

    outcome = debug_set.classify(emitted, retail)

    assert not outcome.ok
    assert outcome.condition == 2
    assert "structure_type '@anon1'" in outcome.detail
    assert "(retail's)" in outcome.detail


# -- condition 3: the DIE multiset --------------------------------------------------------


def test_a_different_die_set_refuses_even_at_the_same_length():
    retail = chunk(two_anonymous())
    emitted = chunk(unit(structure("@anon0", 12, [("x", 0), ("z", 4)]),
                         structure("@anon1", 4, [("n", 0)])))

    assert len(emitted) == len(retail)
    outcome = debug_set.classify(emitted, retail)

    assert not outcome.ok
    assert outcome.condition == 3
    assert "member 'z'" in outcome.detail
    assert "no counterpart" in outcome.detail


def test_a_different_tag_refuses():
    retail = chunk(two_anonymous())
    union = Die(0x0017, [(AT_NAME, "@anon0"), (AT_BYTE_SIZE, 12)],
                [Die(0x000D, [(AT_NAME, "x"), (AT_LOCATION, bytes([0])),
                              (AT_FUND_TYPE, 0x0007)]),
                 Die(0x000D, [(AT_NAME, "y"), (AT_LOCATION, bytes([4])),
                              (AT_FUND_TYPE, 0x0007)])])
    emitted = chunk(unit(union, structure("@anon1", 4, [("n", 0)])))

    assert len(emitted) == len(retail)
    outcome = debug_set.classify(emitted, retail)

    assert not outcome.ok
    assert outcome.condition == 3
    assert "union_type '@anon0'" in outcome.detail


def test_a_changed_member_type_refuses():
    retail = chunk(two_anonymous())
    emitted = chunk(unit(structure("@anon0", 12, [("x", 0), ("y", 4)]),
                         structure("@anon1", 4, [("n", 0)])))
    # Same names and length; the member's fundamental type moves int -> unsigned int.
    emitted = emitted.replace(struct.pack("<HH", AT_FUND_TYPE, 0x0007),
                              struct.pack("<HH", AT_FUND_TYPE, 0x0009), 1)

    outcome = debug_set.classify(emitted, retail)

    assert not outcome.ok
    assert outcome.condition == 3


def test_an_unparseable_chunk_refuses_as_condition_four():
    outcome = debug_set.classify(b"\x08\x00\x00\x00", chunk(two_anonymous()))

    assert not outcome.ok
    assert outcome.condition == 4


# -- condition 1: `.text` and `.line` are never relaxed ------------------------------------


def _retail_and_emitted():
    retail = chunk(two_anonymous())
    emitted = chunk(unit(structure("@anon1", 12, [("x", 0), ("y", 4)]),
                         structure("@anon0", 4, [("n", 0)])))
    return retail, emitted


def test_acceptance_keeps_retails_chunk_and_prints_the_boundary(capsys):
    retail, emitted = _retail_and_emitted()

    placed = cc.debug_promotion("src/example.c", text=b"code", line=b"line", debug=emitted,
                                retail_text=b"code", retail_line=b"line",
                                retail_debug=retail)

    assert placed == retail
    error = capsys.readouterr().err
    assert "anonymous-type DIE-order boundary" in error
    assert "2 of 2 @anonN indices permuted" in error
    assert "tu_builds comment" in error


class _MW:
    relocs = {}

    @staticmethod
    def data(_index):
        return b"\xAA\xBB"

    @staticmethod
    def resolve(_tu, _symbol):
        return 0


def test_a_block_length_difference_refuses_as_condition_two():
    candidate, _sizes, mismatches = cc._fill_debug(
        _MW(), object(), 0, 4, [(0, 4, 0, "the unit's types")], 0,
        retail_chunk=b"\0" * 4)

    assert mismatches
    with pytest.raises(cc.Unusable) as excinfo:
        cc.debug_promotion("src/example.c", text=b"", line=b"", debug=candidate,
                           retail_text=b"", retail_line=b"", retail_debug=b"\0" * 4,
                           block_mismatches=mismatches)

    assert "condition 2 (.debug length and DIE count)" in str(excinfo.value)
    assert "short by 0x2 bytes" in str(excinfo.value)
    assert "cannot pad .debug" in str(excinfo.value)


def test_a_text_byte_difference_refuses_as_condition_one():
    retail, emitted = _retail_and_emitted()

    with pytest.raises(cc.Unusable) as excinfo:
        cc.debug_promotion("src/example.c", text=b"code", line=b"line", debug=emitted,
                           retail_text=b"c0de", retail_line=b"line",
                           retail_debug=retail)

    assert "condition 1 (.text and .line byte-equal)" in str(excinfo.value)
    assert "first differing byte at 0x1" in str(excinfo.value)


def test_a_line_byte_difference_refuses_as_condition_one():
    retail, emitted = _retail_and_emitted()

    with pytest.raises(cc.Unusable) as excinfo:
        cc.debug_promotion("src/example.c", text=b"code", line=b"line", debug=emitted,
                           retail_text=b"code", retail_line=b"1ine",
                           retail_debug=retail)

    assert "condition 1 (.text and .line byte-equal)" in str(excinfo.value)
    assert ".line is 0x4 bytes" in str(excinfo.value)
