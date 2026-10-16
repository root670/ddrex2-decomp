#!/usr/bin/env python3
"""G3 -- reinsert the built ELF into a copy of the retail image, and verify the copy.

The disc's boot ELF lives at a fixed byte offset in the image -- LBA 894146 = ``0x6D261000``
for the prototype image this tree is built for, and each target's own offset is a measurement
of its own image, carried in its descriptor -- and nothing else in the image depends on its
bytes: so reinsertion is one ``write`` into a copy, and the gate is the copy's sha256 against
the retail image's -- a file of over a gigabyte that is therefore read in 1 MiB blocks here,
never slurped whole (R30).  Assets (``DATA/FILEDATA.BIN``,
``SOUND``, ``IRX/``) are never touched: they are not rebuildable, and matching does not
require it.

The image, its pin and the offset are the target's, so this module takes the target rather
than naming a game: ``retail_image(target)`` and ``elf_offset(target)`` are what `ddr iso`
resolves a bare ``--iso`` through, and the module-level names are the default target's.

Geometry: each target's image is a plain ISO9660 image with 2048-byte sectors (the prototype
image is), so an "offset" is an image byte offset and a sector is 2048 bytes (the ELF's own
offset lands 0x6D261000 = 894146 * 2048, on a sector boundary, and its 7,725,036 bytes leave
the last 20 bytes of that extent untouched -- the splice writes the ELF and nothing else).
R31: the two other layouts the sibling-build ladder needs
are documented, not half-supported, here -- MODE2/2352 (DDRMAX JP; each 2352-byte sector
carries user data at byte 24, so a user-data offset maps as ``24 + 2048 * n + k``) and
MODE2/2448 with a 96-byte subchannel appended (Party Collection).  Neither changes this
module's contract; both would add a geometry translation in front of ``build``'s seek, and
the ladder's own gate would verify it.
"""

import hashlib
import os
import pathlib
import shutil
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
if str(REPO_ROOT) not in sys.path:  # `config.targets`, the descriptor every tool reads
    sys.path.insert(0, str(REPO_ROOT))
from config import targets  # noqa: E402

#: The default target, whose files the names below describe.  A target names its own image --
#: and its own offset within it -- in the descriptor, so every function here takes the target
#: it works on: nothing about the *disc* is a property of this tool.
TARGET = targets.get(targets.DEFAULT)

# The retail image on its read-only mount.  Named here because it is the reference a
# mismatched copy is diagnosed against, not because this module ever writes to it.
RETAIL_IMAGE = TARGET.image

# The build under gate, and the image the gate writes: out/ is gitignored, and the copy is
# 1.84 GB, so it must never land in a temporary directory (R30).
BUILT_ELF = TARGET.built
REBUILT_IMAGE = REPO_ROOT / "out" / "rebuilt.iso"


def elf_offset(target=None) -> int:
    """Where ``target``'s built ELF sits in its disc image, from the target's own geometry.

    Resolved when asked for, never at import: the offset is a measurement of that target's
    image (the boot ELF's LBA), so a target whose geometry nobody has measured raises
    :class:`targets.NotMeasured` here instead of splicing a build at another disc's offset.
    """
    return (target or TARGET).geometry_required().image_elf_offset


def retail_image(target=None) -> pathlib.Path:
    """The mounted retail image for ``target`` -- the file a bare ``--iso`` means.

    The image is the target's, not a constant: a bare ``--iso`` must mean the image of the
    target being built, or the gate would compare a rebuild of one game against another game's
    bytes.
    """
    return (target or TARGET).image


BLOCK = 1 << 20


def sha256(path) -> str:
    """Digest of a file, read in blocks: this image must never be loaded whole."""
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for block in iter(lambda: handle.read(BLOCK), b""):
            digest.update(block)
    return digest.hexdigest()


def read(path, offset, length) -> bytes:
    """``length`` bytes at ``offset``: the probe that shows what an image holds where."""
    with open(path, "rb") as handle:
        handle.seek(offset)
        return handle.read(length)


def first_difference(lhs, rhs):
    """``(offset, note)`` of the first byte that differs, or ``(None, "")`` if equal.

    ``note`` is empty unless the two files run out at different lengths -- the shape a
    truncated or over-long image has.
    """
    left_size, right_size = os.path.getsize(lhs), os.path.getsize(rhs)
    with open(lhs, "rb") as left, open(rhs, "rb") as right:
        offset = 0
        while True:
            one, other = left.read(BLOCK), right.read(BLOCK)
            if one != other:
                for index, (a, b) in enumerate(zip(one, other)):
                    if a != b:
                        return offset + index, ""
                if left_size < right_size:
                    note = (f" (the copy ends there: {left_size} bytes against "
                            f"{right_size})")
                else:
                    note = (f" (the copy runs past the image: {left_size} bytes against "
                            f"{right_size})")
                return offset + min(len(one), len(other)), note
            if not one:
                return None, ""
            offset += len(one)


def build(image_path, elf_path, out_path, offset=None) -> None:
    """Write a copy of ``image_path`` with ``elf_path`` spliced in at ``offset``.

    ``offset`` is the target's measured boot-ELF offset by default (``elf_offset()``), and an
    explicit one for a caller working on another layout -- a test fixture, say.  It is resolved
    here rather than as a default argument so that an unmeasured target stops with
    :class:`targets.NotMeasured` at the call instead of at import.

    The copy is byte-identical to the image everywhere else, and exactly as long, which is
    what lets G3 be a single hash.  An ELF that does not fit, or a request to splice the
    image into itself, raises rather than writing: the retail image is the only copy of
    the disc, and a grown image would pass no gate.
    """
    image_path = pathlib.Path(image_path)
    elf_path = pathlib.Path(elf_path)
    out_path = pathlib.Path(out_path)
    offset = elf_offset() if offset is None else offset
    elf_size = elf_path.stat().st_size
    image_size = image_path.stat().st_size
    if offset < 0 or offset + elf_size > image_size:
        raise ValueError(
            f"the {elf_size}-byte ELF does not fit at 0x{offset:X} in the "
            f"{image_size}-byte image {image_path}")
    if out_path.resolve() == image_path.resolve():
        raise ValueError(f"refusing to splice the image into itself: {out_path}")
    out_path.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(image_path, out_path)
    with open(elf_path, "rb") as elf, open(out_path, "r+b") as copy:
        copy.seek(offset)
        shutil.copyfileobj(elf, copy, BLOCK)


def verify(path, expected_sha256, reference=None) -> str:
    """``"ok"``, or the mismatch message: both hashes, and where the copy diverges.

    ``reference`` -- the image the copy was built from, the retail image by default -- is
    read only on the failure path, to turn "the hash is wrong" into a byte a reader can go
    look at.  A missing reference costs that diagnosis, never the verdict.
    """
    actual = sha256(path)
    if actual == expected_sha256:
        return "ok"
    message = f"sha256 mismatch: {path} has {actual}, expected {expected_sha256}"
    reference = RETAIL_IMAGE if reference is None else reference
    if not pathlib.Path(reference).exists():
        return f"{message} (no reference image to name a difference against)"
    offset, note = first_difference(path, reference)
    if offset is None:
        return f"{message} (the bytes of {path} now agree with {reference})"
    return f"{message} (first difference against {reference} at 0x{offset:X}{note})"
