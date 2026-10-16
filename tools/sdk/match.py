"""Instruction comparison between a borrowed corpus's bytes and our retail bytes.

A corpus publishes an image built by the same compiler but linked at a different base, and
(for a different SDK generation) from a different revision of the SDK source.  The
immediates that carry addresses -- ``lui``/``addiu`` pairs, ``ori`` masks, ``jal`` targets --
therefore differ between the two links even when the *code* is the same function.
``compare`` reports both the byte-exact answer and the answer after those immediates are
masked, so a caller can tell "the same instructions" from "the same bytes".

The masking rule is the one measured on this tree (the Oni 2 dev build recipe: 8.8 % of our
library functions of >= 48 bytes, 153 distinct names recovered):

    op = word >> 26
    op in (2, 3)  -> keep only the opcode      the 26-bit jump target is an address
    op != 0       -> keep opcode, rs, rt       the 16-bit immediate is an address or offset
    op == 0       -> the whole word            R-type: every field is the instruction

R-type words are never masked; masking them would make every register-register operation
read as "the same instruction".
"""

from __future__ import annotations

import struct

WORD = 4


def words(blob: bytes) -> list[int]:
    """Little-endian instruction words; a partial word is a usage error."""
    if len(blob) % WORD:
        raise ValueError(
            f"{len(blob)} bytes is not a whole number of 4-byte instructions")
    return list(struct.unpack(f"<{len(blob) // WORD}I", blob))


def mask(word: int) -> int:
    """``word`` with the fields that carry a link address zeroed (see the module docstring)."""
    op = word >> 26
    if op in (2, 3):                 # j, jal: the low 26 bits are an absolute target
        return word & 0xFC000000
    if op:                           # I-type: the low 16 bits are an immediate or offset
        return word & 0xFFFF0000
    return word                      # R-type: every field is part of the instruction


def compare(object_bytes: bytes, retail_bytes: bytes) -> dict:
    """Compare a corpus object's bytes against our bytes for the same function.

    Returns ``{"identical", "differing_words", "first_difference"}`` plus the two facts a
    validation record wants next to them:

    * ``identical`` -- same number of words and every word equal *after masking*.  This is
      the answer "the same instructions", which is the strongest a differently-linked
      corpus can give.
    * ``exact`` -- every byte equal.  ``identical and not exact`` is exactly the case
      "the same code at a different address".
    * ``differing_words`` -- words that differ even after masking, plus (when the inputs are
      of different lengths) the words one side does not have, so a size mismatch is never
      reported as identical.
    * ``first_difference`` -- the index of the first word that differs after masking; when
      one input is a prefix of the other, the first index the shorter input does not have;
      ``None`` when identical.
    * ``masked_words`` -- how many words were equal only after masking: the relocation
      evidence, and zero for two links of the same code at the same address.
    """
    left, right = words(object_bytes), words(retail_bytes)
    common = min(len(left), len(right))
    masked = 0
    differing = 0
    first = None
    for index in range(common):
        if left[index] == right[index]:
            continue
        if mask(left[index]) == mask(right[index]):
            masked += 1
            continue
        differing += 1
        if first is None:
            first = index
    if len(left) != len(right):
        differing += abs(len(left) - len(right))
        if first is None:
            first = common
    return {
        "identical": differing == 0,
        "exact": len(left) == len(right) and differing == 0 and masked == 0,
        "differing_words": differing,
        "first_difference": first,
        "masked_words": masked,
    }
