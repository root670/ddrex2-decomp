"""``match.compare``: instruction comparison that survives a different link.

A borrowed corpus publishes an image built by the same compiler but linked at a different
base (and, for a different SDK generation, a different revision of the SDK source).  The
immediates that carry addresses — ``lui``/``addiu`` pairs, ``ori`` masks, ``jal`` targets —
therefore differ between the corpus and retail even when the *code* is the same function.
``compare`` reports both the byte-exact answer and the answer after those immediates are
masked, so a caller can tell "the same instructions" from "the same bytes".

The masking rule is the one measured on this tree (Main's Oni 2 dev-build recipe, which
recovered 153 names at 8.8 % over the library region):

    op = word >> 26
    op in (2, 3)  -> keep only the opcode      (the 26-bit jump target is an address)
    op != 0       -> keep opcode, rs, rt       (the 16-bit immediate is an address/offset)
    op == 0       -> the whole word            (R-type: every field is the instruction)

so R-type words are never masked — otherwise every register-register operation would read
as "the same instruction".
"""
import pathlib, sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from sdk import match  # noqa: E402

RETAIL = ROOT / "orig" / "SLUS_207.11"
# ``sysInitScf`` -- the promoted TU's first function, 0x30 bytes of retail code.
SYS_INIT_SCF_VA = 0x0021C420


def retail_bytes(va, size):
    """The retail bytes of ``[va, va + size)``: file offset ``0x80 + va - 0x100000``."""
    return RETAIL.read_bytes()[0x80 + (va - 0x100000):0x80 + (va - 0x100000) + size]


def words(*values):
    return b"".join(value.to_bytes(4, "little") for value in values)


def test_identity_for_retail_bytes_at_their_own_address():
    """The baseline: retail against itself is identical, with nothing masked."""
    if not RETAIL.is_file():
        import pytest
        pytest.skip("retail binary not available")
    blob = retail_bytes(SYS_INIT_SCF_VA, 0x30)
    result = match.compare(blob, blob)
    assert result["identical"] is True
    assert result["exact"] is True
    assert result["differing_words"] == 0
    assert result["first_difference"] is None
    assert result["masked_words"] == 0


def test_the_same_bytes_shifted_by_four_are_not_identical():
    """A four-byte shift misaligns every word: the first word already differs."""
    if not RETAIL.is_file():
        import pytest
        pytest.skip("retail binary not available")
    blob = retail_bytes(SYS_INIT_SCF_VA, 0x40)
    shifted = blob[4:]
    result = match.compare(shifted, blob[:len(shifted)])
    assert result["identical"] is False
    assert result["first_difference"] == 0
    assert result["differing_words"] >= 1


def test_the_first_differing_word_is_the_word_that_changed():
    """One changed R-type word in the middle: its index is the first difference."""
    nop = 0x00000000
    body = [0x27BDFFF0, nop, 0x00000021]      # addiu $sp,$sp,-16; nop; addu $0,$0,$0
    changed = list(body)
    changed[1] = 0x00000025                   # or $0,$0,$1 -- R-type, cannot be masked
    result = match.compare(words(*changed), words(*body))
    assert result["identical"] is False
    assert result["first_difference"] == 1
    assert result["differing_words"] == 1


def test_a_relocated_immediate_is_masked():
    """``lui``/``addiu`` immediates carry a link address: they are not a difference."""
    ours = words(0x27BDFFF0, 0x3C020021, 0x2442C410, 0xAC820000)
    theirs = words(0x27BDFFF0, 0x3C02004A, 0x2442A0C0, 0xAC820000)
    result = match.compare(theirs, ours)
    assert result["identical"] is True
    assert result["exact"] is False
    assert result["differing_words"] == 0
    assert result["first_difference"] is None
    assert result["masked_words"] == 2


def test_a_jump_target_is_masked():
    """``jal`` encodes an absolute address in 26 bits; the opcode is what survives."""
    ours = words(0x0C000000 | (0x0021C420 >> 2), 0x00000000)
    theirs = words(0x0C000000 | (0x004A0008 >> 2), 0x00000000)
    result = match.compare(theirs, ours)
    assert result["identical"] is True
    assert result["exact"] is False
    assert result["masked_words"] == 1


def test_an_r_type_instruction_is_never_masked():
    """Masking R-type words would erase the instruction itself."""
    result = match.compare(words(0x00000021), words(0x00000023))
    assert result["identical"] is False
    assert result["first_difference"] == 0
    assert result["differing_words"] == 1


def test_a_size_mismatch_is_never_identical():
    """A shorter object is a mismatch, and the report says where the words run out."""
    blob = words(0x27BDFFF0, 0x3C020021)
    result = match.compare(blob[:4], blob)
    assert result["identical"] is False
    assert result["first_difference"] == 1
    assert result["differing_words"] == 1


def test_a_length_that_is_not_a_whole_number_of_instructions_is_refused():
    import pytest
    with pytest.raises(ValueError):
        match.compare(b"\x00\x00\x00", b"\x00\x00\x00\x00")
