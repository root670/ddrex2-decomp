#!/usr/bin/env python3
"""Retail bytes for one target: the ELF's loadable image for main, the disc's blobs for overlays.

The retail ELF answers for exactly one region: the file-backed ``PT_LOAD`` at
``[loadable_vram, bss_vram)``.  Its other ten reservations are *zero-fill* -- their program
headers claim no bytes at all -- so ``Elf.read`` at an overlay address returns zeros, and a
comparison against those zeros says everything matches an empty buffer.  The overlay's bytes
are in the pinned disc image instead, in the ``DATA*.BIN`` blob that loads at that address.

This module is the one place that decides which of the two files to read, so every consumer --
``compile.placed_text``, ``compile.retail_bytes``, ``compile.compare`` and ``verify --tu``'s
text verdict -- asks the same question and gets the same answer:

* **main** (a unit whose overlay is ``main``): the ELF's file offset for the address, refusing
  an address the file-backed image does not map instead of returning ``.bss`` zeros;
* **overlay** (a unit whose DWARF ``DW_TAG_MW_overlay`` names a module): the image at
  ``overlay.image_offset + (VA - overlay.vaddr)`` -- the blob's own header is part of that
  image, so ``vaddr + 0x40`` is where its code starts.

``.debug`` and ``.line`` are never in the image: both sections are in the ELF, chunked by
``debug_chunks.json``, and they stay there (:meth:`Retail.section`).

Usage::

    from toolchain.retail import Retail

    retail = Retail(target)                  # the target's own ELF and image
    text = retail.text(tu, size=0x50)        # the unit's retail .text bytes
    chunk = retail.section(tu, ".debug")     # its .debug chunk bytes, from the ELF

The image is 1.8 GB, so it is read at an offset and never slurped; the handle is opened once
per :class:`Retail` and closed by :meth:`Retail.close` (or the context manager).  A missing
file is an :class:`OSError` naming it -- never an empty read that would compare as a match.
"""

from __future__ import annotations

import contextlib
import pathlib
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

import elf  # noqa: E402  the vendored 32-bit little-endian MIPS reader
from config import targets  # noqa: E402

DEFAULT_TARGET = targets.get(targets.DEFAULT)


class Retail:
    """One target's retail bytes, read from the file that actually holds them.

    ``elf_path``/``image_path`` exist for the tests and for a checkout whose image lives
    elsewhere; both default to the target's own paths.  Nothing is opened until it is asked
    for, so building a provider is free and a target whose image is missing only stops when an
    overlay unit's bytes are actually needed.
    """

    def __init__(self, target=None, elf_path=None, image_path=None):
        self.target = target if target is not None else DEFAULT_TARGET
        self.geometry = self.target.geometry_required()
        self.elf_path = pathlib.Path(elf_path if elf_path is not None else self.target.elf)
        self.image_path = pathlib.Path(image_path if image_path is not None
                                       else self.target.image)
        self._elf = None
        self._image = None

    # -- the two files -------------------------------------------------------

    def elf(self) -> elf.Elf:
        """The retail ELF, parsed once."""
        if self._elf is None:
            if not self.elf_path.is_file():
                raise FileNotFoundError(f"{self.elf_path}: no such retail ELF")
            self._elf = elf.Elf(str(self.elf_path))
        return self._elf

    def image(self):
        """The pinned disc image, opened once (never read whole)."""
        if self._image is None:
            if not self.image_path.is_file():
                raise FileNotFoundError(
                    f"{self.image_path}: no such disc image: the overlay blobs' retail bytes "
                    f"are in it, so an overlay unit cannot be compared without it")
            self._image = open(self.image_path, "rb")
        return self._image

    def close(self) -> None:
        if self._image is not None:
            self._image.close()
            self._image = None

    @contextlib.contextmanager
    def opened(self):
        """``with Retail(target) as retail:`` -- closes the image on the way out."""
        try:
            yield self
        finally:
            self.close()

    # -- which file a unit's bytes are in -------------------------------------

    def overlay_of(self, tu):
        """``tu``'s :class:`config.targets.Overlay`, or ``None`` for a main-image unit.

        ``tu.overlay`` is the unit's own answer -- the DWARF overlay name, kept as the module
        stem -- and this is the one place it becomes geometry.  A name the geometry does not
        record is a :class:`KeyError` naming it, never a fallback to main: main's addresses are
        a different image.
        """
        name = getattr(tu, "overlay", "main")
        return self.geometry.overlay_named(name)

    def text(self, tu, size=None) -> bytes:
        """The unit's retail ``.text``: ``tu.end - tu.address`` bytes unless ``size`` is given."""
        return self.code(tu.address, tu.end - tu.address if size is None else size,
                         self.overlay_of(tu))

    def code(self, address: int, size: int, overlay=None) -> bytes:
        """``size`` retail bytes at ``address``, from the image when it is an overlay address."""
        if overlay is not None:
            return self._blob(overlay, address, size)
        return self._loadable(address, size)

    def _loadable(self, address: int, size: int) -> bytes:
        """The file-backed image's bytes, refusing anything it does not map.

        ``Elf.read`` would answer zeros for the bss tail and for every overlay reservation
        (both are ``PT_LOAD``s with ``filesz == 0``), which is exactly the evidence that made
        a mismatch read as a match.  A read that leaves the file-backed image is refused here,
        with the geometry's own range in the message.
        """
        image = self.elf()
        offset = image.file_offset(address)
        high = self.geometry.bss_vram
        if offset is None:
            raise targets.OutsideLoadableImage(
                f"0x{address:08X} has no retail file offset: the file-backed image is "
                f"0x{self.geometry.loadable_vram:08X}..0x{high:08X} of {self.elf_path}")
        if address + size > high:
            raise targets.OutsideLoadableImage(
                f"0x{address:08X}+0x{size:X} runs past the file-backed image's end at "
                f"0x{high:08X}")
        data = image.data[offset:offset + size]
        if len(data) != size:
            raise ValueError(f"{self.elf_path} ends inside 0x{address:08X}+0x{size:X}")
        return data

    def _blob(self, overlay, address: int, size: int) -> bytes:
        """The blob's bytes: ``image_offset + (address - vaddr)``, bounded by the blob."""
        start = overlay.image_offset_of(address)
        if address + size > overlay.vaddr + overlay.filesize:
            raise targets.OutsideLoadableImage(
                f"overlay {overlay.name}: 0x{address:08X}+0x{size:X} runs past the blob's end "
                f"at 0x{overlay.vaddr + overlay.filesize:08X}")
        handle = self.image()
        handle.seek(start)
        data = handle.read(size)
        if len(data) != size:
            raise ValueError(f"{self.image_path} ends inside overlay {overlay.name}'s blob at "
                             f"0x{address:08X}+0x{size:X} (read 0x{len(data):X} bytes)")
        return data

    # -- the ELF's chunked sections ------------------------------------------

    def section(self, tu, section: str) -> bytes:
        """The unit's ``section`` chunk bytes, from the ELF (``.debug`` or ``.line``)."""
        image = self.elf()
        entry = next((s for s in image.sections if s.name == section), None)
        if entry is None:
            raise ValueError(f"{self.elf_path}: no {section} section")
        offset, size = ((tu.debug_offset, tu.debug_size) if section == ".debug"
                        else (tu.line_offset, tu.line_size))
        data = image.data[entry.offset + offset:entry.offset + offset + size]
        if len(data) != size:
            raise ValueError(f"{self.elf_path}: {section} ends inside the unit's chunk at "
                             f"0x{offset:X}+0x{size:X}")
        return data
