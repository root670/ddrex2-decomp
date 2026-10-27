"""``units.slots``: the map is read off code the tests spell, not off a compiler.

The parsing, the attribution and the diff naming are pure functions over words and
``Local`` records, so they are pinned here with synthetic splits and hand-encoded
instructions.  The one measurement (a promoted unit end to end) skips when this checkout
has no toolchain or no generated split tree -- it is the only test that needs them.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from units import slots  # noqa: E402


# -- a tiny encoder, so a body can be spelled without a compiler -------------------------


def addiu(rt, rs, imm):
    return (0x09 << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def store(opcode, rt, offset, base=29):
    return (opcode << 26) | (base << 21) | (rt << 16) | (offset & 0xFFFF)


def load(opcode, rt, offset, base=29):
    return store(opcode, rt, offset, base)


def swc1(ft, offset, base=29):
    return store(0x39, ft, offset, base)


def jr(rs=31):
    return (rs << 21) | 0x08


SD, SQ, LW, LD, LQ = 0x3F, 0x1F, 0x23, 0x37, 0x1E


def prologue(frame, saved, body=()):
    """``addiu $sp``, the stores ``[(mnemonic, register, offset)]``, then ``body``."""
    words = [addiu(29, 29, -frame)]
    for kind, register, offset in saved:
        words.append({("sd"): store(SD, register, offset),
                      ("sq"): store(SQ, register, offset),
                      ("swc1"): swc1(register, offset)}[kind])
    return words + list(body)


# -- the split: words in memory order, trimmed to the extent -----------------------------


SPLIT = """\
.include "macro.inc"
.set noat
.set noreorder
.align 3
nonmatching demo, 0x10

glabel demo
    /* 1000 2000 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 1004 2004 0000BFDF */  ld         $31, 0x0($29)
    /* 1008 2008 0800E003 */  jr         $31
    /* 100C 200C 1000BD27 */   addiu     $29, $29, 0x10
endlabel demo
    /* 1010 2010 00000000 */  nop
"""


def test_split_words_are_little_endian_and_trimmed_to_the_extent():
    words = slots.split_words(SPLIT)
    assert words == [addiu(29, 29, -0x10), load(LD, 31, 0x0), jr(31),
                     addiu(29, 29, 0x10)]


def test_split_words_accepts_the_assembler_pseudo_spellings():
    text = ('nonmatching demo, 0x8\n'
            '    /* 1000 2000 F0FFBD27 */  addiu $29, $29, -0x10\n'
            '    /* 1004 2004 03002014 */  bnez  $2, .L1\n')
    # bnez is bne with $zero: the split's spelling is a pseudo-instruction, the word is not
    words = slots.split_words(text)
    assert slots.measure.decode(words[1]).mnemonic == "bne"


def test_split_words_refuses_a_comment_that_contradicts_the_word():
    text = SPLIT.replace("ld         $31", "lq         $31")
    with pytest.raises(slots.Missing) as error:
        slots.split_words(text)
    assert "the comment says lq" in str(error.value)


def test_split_words_of_an_empty_file_is_empty():
    assert slots.split_words(".set noat\n") == []


# -- the anatomy: frame, saved order, slots ---------------------------------------------


BODY = prologue(0x250, [("sd", 31, 0x90), ("sq", 30, 0x80), ("sq", 22, 0x60)],
                body=[swc1(21, 0x4), addiu(4, 29, 0x1A0), load(LW, 2, 0xB0),
                      jr(31), addiu(29, 29, 0x250)])


def test_frame_comes_from_the_stack_adjustment_signed():
    assert slots.anatomy("demo", BODY).frame == 0x250


def test_saved_gpr_and_fp_are_separate_and_keep_store_order():
    body = slots.anatomy("demo", BODY)
    assert [(entry.register, entry.offset) for entry in body.saved_gpr] == [
        ("$ra", 0x90), ("$fp", 0x80), ("$s6", 0x60)]
    assert [(entry.register, entry.offset) for entry in body.saved_fp] == [("$f21", 0x4)]
    # `sq $30` saves the GPR $fp; a frame register whose number is also an FP number is
    # decided by the mnemonic, never by the number's range.
    assert body.saved_fp[0].floating


def test_frame_register_saved_with_sq_is_not_a_floating_point_register():
    body = slots.anatomy("demo", prologue(0x20, [("sq", 30, 0x0)]))
    assert [entry.register for entry in body.saved_gpr] == ["$fp"]


def test_epilogue_is_read_backwards_into_prologue_order():
    words = prologue(0x20, [("sd", 31, 0x10), ("sq", 16, 0x0)],
                     body=[jr(31), addiu(29, 29, 0x20)])
    body = slots.anatomy("demo", words)
    assert [(entry.register, entry.offset) for entry in body.restored] == [
        ("$ra", 0x10), ("$s0", 0x0)]


def test_a_slot_address_and_a_slot_value_are_told_apart():
    body = slots.anatomy("demo", BODY)
    address = body.slot(0x1A0)
    assert (address.kind, address.registers) == ("address", ("$a0",))
    value = body.slot(0xB0)
    assert (value.kind, value.registers) == ("value", ("$v0",))


def test_a_saved_offset_is_a_saved_slot_not_a_value_slot():
    body = slots.anatomy("demo", BODY)
    assert body.slot(0x90).kind == "saved"
    assert body.slot(0x90).registers == ("$ra",)


# -- attribution: this side's own DWARF, nothing inferred --------------------------------

SYMBOLS = slots.Symbols([
    slots.Local("sp", 0x1A0, 0x24, (("flg", 0x20, 4), ("w", 0xC, 4))),
    slots.Local("def_y", 0xB0, 4, ()),
])


def test_attribution_names_a_local_its_member_and_an_offset_inside_it():
    assert SYMBOLS.name(0x1A0) == ("sp", 0x24)
    assert SYMBOLS.name(0x1C0, address=True) == ("&sp.flg", 4)
    assert SYMBOLS.name(0x1AC, address=True) == ("&sp.w", 4)
    assert SYMBOLS.name(0x1A4) == ("sp+0x4", 0x24)
    assert SYMBOLS.name(0x1C4) == (None, None)   # past the struct's own 0x24 bytes


def test_an_unknown_offset_is_unattributed_rather_than_guessed():
    assert SYMBOLS.name(0x220) == (None, None)
    assert SYMBOLS.label(0x220) == "0x220 (unattributed)"
    assert SYMBOLS.label(0xB0) == "def_y (0x4)"


# -- the diff: exchanges named the way a human reads a prologue --------------------------

RETAIL_SYMBOLS = slots.Symbols([slots.Local("sp", 0x1A0, 0x24,
                                            (("flg", 0x20, 4), ("w", 0xC, 4)))])
OURS_SYMBOLS = slots.Symbols([slots.Local("sp", 0x1A0, 0x24,
                                          (("flg", 0x20, 4), ("w", 0xC, 4))),
                              slots.Local("def_y", 0xB0, 4, ())])


def _exchange(retail_codes, ours_codes):
    retail = slots.anatomy("demo", prologue(0x250, [], body=retail_codes))
    ours = slots.anatomy("demo", prologue(0x250, [], body=ours_codes))
    return slots.diff_lines(retail, ours, RETAIL_SYMBOLS, OURS_SYMBOLS)


def test_the_exchange_is_named_with_both_registers():
    # retail materialises &sp.flg into $s4 and &sp.w into $s6; ours the other way round
    lines = _exchange([addiu(20, 29, 0x1C0), addiu(22, 29, 0x1AC)],
                      [addiu(22, 29, 0x1C0), addiu(20, 29, 0x1AC)])
    assert "  retail &sp.flg -> s4, ours -> s6" in lines
    assert "  retail &sp.w -> s6, ours -> s4" in lines


def test_an_exchange_is_not_reported_when_the_registers_agree():
    lines = _exchange([addiu(20, 29, 0x1C0)], [addiu(20, 29, 0x1C0)])
    assert lines == []


def test_a_slot_move_is_named_by_its_accesses_not_by_its_offset():
    # retail keeps def_y's slot at 0xA0, ours at 0xB0; the accesses are the same multiset
    retail = [load(LW, 2, 0xA0), store(0x2B, 2, 0xA0), load(LW, 22, 0xA0)]
    ours = [load(LW, 2, 0xB0), store(0x2B, 2, 0xB0), load(LW, 22, 0xB0)]
    lines = _exchange(retail, ours)
    assert "  retail 0xA0 (unattributed) -> ours 0xB0 (def_y, 0x4 bytes)  " \
           "[3 matching accesses]" in lines


def test_two_moved_slots_are_called_an_exchange():
    retail = [load(LW, 2, 0xA0), load(LW, 3, 0xB0)]
    ours = [load(LW, 2, 0xB0), load(LW, 3, 0xA0)]
    lines = _exchange(retail, ours)
    assert "  the two slots are exchanged: retail 0xA0 <-> ours 0xB0" in lines


def test_an_ambiguous_access_signature_is_not_paired():
    # two slots on each side share one signature: neither pairing is evidence
    retail = [load(LW, 2, 0xA0), load(LW, 2, 0xB0)]
    ours = [load(LW, 2, 0xA0), load(LW, 2, 0xB8)]
    assert slots._slot_moves(slots.anatomy("demo", retail),
                             slots.anatomy("demo", ours)) == []


def test_the_frame_and_saved_set_are_reported_when_they_differ():
    retail = slots.anatomy("demo", prologue(0x250, [("sd", 31, 0x90)]))
    ours = slots.anatomy("demo", prologue(0x240, [("sd", 31, 0x90), ("sq", 16, 0x0)]))
    lines = slots.diff_lines(retail, ours, slots.Symbols(), slots.Symbols(), raw=0)
    assert "  frame: retail 0x250, ours 0x240 (-0x10)" in lines
    assert "  saved set: ours only $s0; retail only -" in lines


# -- --search: enumerated orders, and the rule that keeps an artefact out ----------------

SOURCE = """\
int demo(void) {
    int alpha;
    int beta;
    struct huge sp;
    int gamma;
    alpha = 1;
    return alpha + beta;
}
"""


def test_declaration_lines_finds_only_whole_line_declarations_of_the_named_locals():
    found = slots.declaration_lines(SOURCE, ("alpha", "sp"))
    assert [(line, name) for line, name in found] == [(1, "alpha"), (3, "sp")]


def test_permuted_swaps_the_declarations_and_leaves_the_rest_alone():
    text = slots.permuted(SOURCE, ("sp", "beta", "alpha"))
    assert "    struct huge sp;" in text.splitlines()[1]
    lines = text.splitlines()
    assert lines[0] == "int demo(void) {"
    assert lines[-1] == "}"


def test_orders_is_a_fixed_enumeration_rotations_then_transpositions():
    assert slots.orders(("a", "b", "c")) == [
        ("a", "b", "c"), ("b", "c", "a"), ("c", "a", "b"),
        ("b", "a", "c"), ("c", "b", "a"), ("a", "c", "b")]


def test_orders_is_bounded_and_deterministic():
    names = tuple(f"v{i}" for i in range(slots.MAX_LOCALS))
    first = slots.orders(names)
    assert first == slots.orders(names)
    assert len(first) <= slots.MAX_CANDIDATES


def test_a_candidate_must_lower_the_unmasked_count_to_count_as_an_improvement():
    assert slots.improves(300, 336)
    assert not slots.improves(336, 336)
    assert not slots.improves(340, 336)


# -- one measurement, for a checkout that has the compiler and the split tree -----------

PROMOTED = ("sys_scf", "sysGetDateNotation")


def _measured_available():
    from config import targets

    target = targets.get()
    return (bool(slots.split_path(PROMOTED[1]).is_file())
            and (ROOT / "orig" / "SLUS_211.74").is_file()
            and (ROOT / "toolchain").exists())


@pytest.mark.skipif(not _measured_available(),
                    reason="needs the compiled toolchain and the generated split tree")
def test_a_promoted_unit_maps_end_to_end(capsys):
    assert slots.main([PROMOTED[0], PROMOTED[1]]) == 0
    out = capsys.readouterr().out
    assert out.startswith(f"{PROMOTED[0]} {PROMOTED[1]}\n")
    assert "retail:" in out and "ours:" in out
    assert "\ndiff\n" in out
