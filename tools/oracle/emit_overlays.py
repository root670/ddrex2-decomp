#!/usr/bin/env python3
"""ELF program headers + the pinned image's ``DATA*.BIN`` blobs -> the target's ``overlays.txt``.

The retail binary reserves ten overlay windows (one ``PT_LOAD`` each, ``p_filesz == 0``, all at
``p_offset == loadable_end``) and the ten blobs are in the disc image, one per window.  Two
files say where they are, and neither alone is the measurement:

* the **ELF** says *where each window loads* and *how big it is* (``p_vaddr``, ``p_memsz``), and
  nothing about where its bytes are;
* the **image** says *where each blob's bytes are* (its ISO9660 extent) and, in the blob's own
  0x40-byte ``MWo3`` header, *what it is* -- the module name, the window base, the code length,
  the data length, the bss length, and ``vaddr + filesize``.

They are joined by the header's own arithmetic, which this program checks on every blob::

    0x40 + code_end + data_size == filesize
    filesize + bss == p_memsz                 (the reservation is the blob plus its bss)
    (vaddr, p_memsz) appears exactly once among the reservations

That last line is the reason this is a *derivation* and not a table: a blob is paired with its
window by ``(vaddr, memsz)``, and the pairing has to be a bijection.  Two windows of one size,
or two blobs claiming one window, is a named error -- never resolved by taking the first match,
because a wrong pairing would put a module's code at another module's addresses.

``config/<target>/overlays.txt`` is the artifact this writes; ``config.targets.load_overlays``
reads it back into ``Geometry.overlays``, so the build, the gates and the compiler driver all
consume the same measurement.

Usage::

    python3 tools/oracle/emit_overlays.py [--target NAME] [--elf PATH] [--image PATH] [--out PATH]

The image is 1.8 GB, so it is read at an offset and never slurped; a missing image or ELF is a
stop naming the file, not an empty ledger.
"""

from __future__ import annotations

import argparse
import hashlib
import pathlib
import struct
import sys

HERE = pathlib.Path(__file__).resolve().parent
REPO_ROOT = HERE.parents[1]
for _extra in (str(HERE), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

import elf  # noqa: E402  the vendored 32-bit little-endian MIPS reader
from config import targets  # noqa: E402

DEFAULT = targets.get(targets.DEFAULT)

#: ISO9660's sector size, and the sector its primary volume descriptor sits in.
SECTOR = 2048
PVD_SECTOR = 16
#: The descriptor's own ``CD001`` marker (one byte in: the type byte comes first).
CD_MAGIC = b"CD001"

#: The blob header: ``MWo3``, the overlay id, then six 32-bit fields, then the module name.
MAGIC = b"MWo3"
OFF_IDENT = 0x04
OFF_VADDR = 0x08
OFF_CODE_END = 0x0C
OFF_DATA_SIZE = 0x10
OFF_BSS = 0x14
OFF_END = 0x18
OFF_NAME = 0x20
NAME_BYTES = 0x20


class OverlayMismatch(RuntimeError):
    """The two files disagree about an overlay: a named stop, never a guess."""


def read_at(handle, offset, length):
    """``length`` bytes of ``handle`` at ``offset``, refusing a short read."""
    handle.seek(offset)
    data = handle.read(length)
    if len(data) != length:
        raise OverlayMismatch(f"the image ends at 0x{offset + len(data):X}, inside the "
                              f"0x{offset:X}+0x{length:X} read")
    return data


def iso_root(handle):
    """``(offset, size)`` of the ISO9660 root directory, from the primary volume descriptor."""
    pvd = read_at(handle, PVD_SECTOR * SECTOR, SECTOR)
    if pvd[1:6] != CD_MAGIC:
        raise OverlayMismatch(
            f"sector {PVD_SECTOR} is not a volume descriptor ({pvd[1:6]!r}, not "
            f"{CD_MAGIC!r}): this image's filesystem is not the ISO9660 the disc's offsets "
            f"were measured from")
    if pvd[0] != 1:
        raise OverlayMismatch(f"sector {PVD_SECTOR} is volume descriptor type {pvd[0]}, not "
                              f"the primary (1)")
    record = pvd[156:156 + pvd[156]]
    extent = struct.unpack_from("<I", record, 2)[0]
    size = struct.unpack_from("<I", record, 10)[0]
    if not (extent and size):
        raise OverlayMismatch("the primary volume descriptor's root directory is empty")
    return extent * SECTOR, size


def directory_entries(handle, offset, size):
    """``[(name, extent offset, size, is_dir)]`` for one directory's records.

    Reads whole sectors, because a record never straddles one; the padding after the last
    record of a sector is a zero length byte, which is where the walk skips to the next sector.
    """
    data = read_at(handle, offset, (size + SECTOR - 1) // SECTOR * SECTOR)
    out, position = [], 0
    while position < size:
        length = data[position]
        if length == 0:
            position = (position // SECTOR + 1) * SECTOR
            continue
        record = data[position:position + length]
        if len(record) < 34:
            raise OverlayMismatch(f"directory record at 0x{offset + position:X} is "
                                  f"{len(record)} bytes, too short for a name")
        extent = struct.unpack_from("<I", record, 2)[0]
        length_bytes = struct.unpack_from("<I", record, 10)[0]
        flags = record[25]
        name = record[33:33 + record[32]].decode("latin-1")
        name = name.split(";", 1)[0]          # ISO9660's `NAME.EXT;1` version suffix
        if name not in ("\x00", "\x01"):
            out.append((name, extent * SECTOR, length_bytes, bool(flags & 0x02)))
        position += length
    return out


def iso_files(handle, limit=64):
    """``{NAME: (image offset, size)}`` for every file under the ISO9660 root.

    The root itself holds the boot files and the ``DATA`` directory; the blobs are one level
    down.  The walk is breadth-first and bounded (``limit`` directories), so a malformed image
    that claims to contain the whole disc as directories stops instead of looping.  Names are
    basenames: two different files called ``DATA03.BIN`` would make the ledger ambiguous, so
    that is refused rather than resolved.
    """
    files, seen = {}, set()
    root = iso_root(handle)
    queue = [(root, "the root")]
    seen.add(root[0])
    while queue:
        if len(seen) > limit:
            raise OverlayMismatch(f"the image's directory tree is deeper than {limit} "
                                  f"directories: this is not the disc layout the blobs were "
                                  f"measured in")
        (offset, size), label = queue.pop(0)
        for name, extent, length, is_dir in directory_entries(handle, offset, size):
            if is_dir:
                if extent in seen:
                    raise OverlayMismatch(f"directory {name} under {label} points back at "
                                          f"0x{extent:X}")
                seen.add(extent)
                queue.append(((extent, length), f"{label}/{name}"))
                continue
            if name in files:
                raise OverlayMismatch(f"two files named {name}: one at image 0x{files[name][0]:X} "
                                      f"and one at 0x{extent:X}; the ledger identifies a blob by "
                                      f"name, so it cannot be ambiguous")
            files[name] = (extent, length)
    if not files:
        raise OverlayMismatch("the image's filesystem names no files")
    return files


def blob_names(files):
    """The ``DATA*.BIN`` entries, in disc order -- the eleven blobs and nothing else."""
    names = sorted((name for name in files if name.startswith("DATA") and name.endswith(".BIN")),
                   key=lambda name: files[name][0])
    if not names:
        raise OverlayMismatch("the root directory carries no DATA*.BIN blobs")
    numbers = [int(name[4:-4]) for name in names if name[4:-4].isdigit()]
    if len(numbers) != len(names) or numbers != list(range(len(names))):
        raise OverlayMismatch(f"the blobs are not DATA00..DATA{len(names) - 1:02d}: {names}")
    return names


def read_blob(handle, name, offset, size):
    """One blob's measured row, from its own header -- every field checked against the others."""
    header = read_at(handle, offset, targets.OVERLAY_HEADER + NAME_BYTES)
    if header[0:4] != MAGIC:
        raise OverlayMismatch(f"{name} at image 0x{offset:X} starts with {header[0:4]!r}, not "
                              f"{MAGIC!r}: that is not an overlay blob")
    vaddr, code_end, data_size, bss, end = struct.unpack_from("<IIIII", header, OFF_VADDR)
    stem = header[OFF_NAME:OFF_NAME + NAME_BYTES].split(b"\x00")[0].decode("latin-1")
    if not stem.endswith(targets.OVERLAY_SUFFIX):
        raise OverlayMismatch(f"{name} names itself {stem!r}, which is not a module name "
                              f"ending in {targets.OVERLAY_SUFFIX!r}")
    module = targets.overlay_stem(stem)
    if not targets._OVERLAY_NAME.fullmatch(module):   # the geometry's own rule, one spelling
        raise OverlayMismatch(f"{name} names itself {stem!r}, which is not a module identifier")
    if targets.OVERLAY_HEADER + code_end + data_size != size:
        raise OverlayMismatch(
            f"{name} ({stem}): 0x{targets.OVERLAY_HEADER:X} header + 0x{code_end:X} code + "
            f"0x{data_size:X} data is "
            f"0x{targets.OVERLAY_HEADER + code_end + data_size:X}, but the ISO entry is "
            f"0x{size:X} bytes")
    if end != vaddr + size:
        raise OverlayMismatch(
            f"{name} ({stem}): its header says the blob ends at 0x{end:08X}, but "
            f"vaddr 0x{vaddr:08X} + filesize 0x{size:X} is 0x{vaddr + size:08X}")
    ident = struct.unpack_from("<I", header, OFF_IDENT)[0]
    # The digest of the blob's own bytes: a row can then be satisfied either by slicing the
    # image or by a pre-extracted pack, and both prove they are these bytes.
    digest = hashlib.sha256(read_at(handle, offset, size)).hexdigest()
    return dict(name=module, header_name=stem, ident=ident, vaddr=vaddr, filesize=size,
                code_end=code_end, data_size=data_size, bss=bss, image_offset=offset,
                sha256=digest)


def windows(elf_path):
    """The ELF's zero-fill reservations: ``[(vaddr, memsz)]`` of the ``PT_LOAD``s with no bytes.

    A reservation with ``memsz == 0`` claims nothing and holds no blob, so it is not a window.
    """
    image = elf.Elf(str(elf_path))
    out = [(segment.vaddr, segment.memsz) for segment in image.segments
           if segment.type == 1 and segment.filesz == 0 and segment.memsz > 0]
    if not out:
        raise OverlayMismatch(f"{elf_path}: no zero-fill PT_LOAD reservations, so the binary "
                              f"claims no overlay windows")
    return out


def pair(blobs, reservations):
    """Join the blobs to the reservations by ``(vaddr, memsz)``: a bijection, or a named stop.

    This is the measurement's load-bearing step.  A blob's header gives its ``vaddr`` and its
    ``filesize + bss``; the ELF gives each reservation's ``vaddr`` and ``memsz``.  Each blob
    must match exactly one reservation and each reservation exactly one blob -- the window
    sizes are unique for that reason.  Anything else names the two rows that disagree.
    """
    by_key = {}
    for vaddr, memsz in reservations:
        if (vaddr, memsz) in by_key:
            raise OverlayMismatch(
                f"the ELF reserves 0x{vaddr:08X}+0x{memsz:X} twice: the window size cannot "
                f"identify a blob, so the pairing is ambiguous")
        by_key[(vaddr, memsz)] = None
    for blob in blobs:
        key = (blob["vaddr"], blob["filesize"] + blob["bss"])
        if key not in by_key:
            raise OverlayMismatch(
                f"blob {blob['name']} loads at 0x{blob['vaddr']:08X} and needs "
                f"0x{blob['filesize'] + blob['bss']:X} bytes, but the ELF reserves no window "
                f"there/that size")
        if by_key[key] is not None:
            raise OverlayMismatch(
                f"blobs {by_key[key]} and {blob['name']} both claim the window at "
                f"0x{key[0]:08X}+0x{key[1]:X}")
        by_key[key] = blob["name"]
    unpaired = [key for key, name in by_key.items() if name is None]
    if unpaired:
        raise OverlayMismatch(
            "the ELF reserves windows no blob fills: "
            + ", ".join(f"0x{vaddr:08X}+0x{memsz:X}" for vaddr, memsz in unpaired))
    return sorted(blobs, key=lambda blob: blob["image_offset"])


def derive(elf_path, image_path):
    """The ten rows: read the ELF's reservations, the image's blobs, and pair them."""
    elf_path, image_path = pathlib.Path(elf_path), pathlib.Path(image_path)
    for path, what in ((elf_path, "retail ELF"), (image_path, "disc image")):
        if not path.is_file():
            raise OverlayMismatch(f"{path}: no such {what}: the overlay ledger is measured "
                                  f"from it, so it cannot be generated")
    reservations = windows(elf_path)
    with open(image_path, "rb") as handle:
        files = iso_files(handle)
        blobs = [read_blob(handle, name, *files[name]) for name in blob_names(files)]
    return pair(blobs, reservations)


def write_blobs(elf_path, image_path, directory):
    """Write every blob out of the image into ``directory`` as ``<module>.bin``.

    This is the pack ``configure.py`` accepts in place of the image: it holds *all* the blobs,
    not only the modules that happen to have a promoted unit today, so promoting the first
    unit of a new module never needs the 1.8 GB image again.  The bytes are the image's,
    verified against the rows' own digests by whatever consumes them.
    """
    directory = pathlib.Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    rows = derive(elf_path, image_path)
    written = []
    with open(image_path, "rb") as handle:
        for row in rows:
            data = read_at(handle, row["image_offset"], row["filesize"])
            if hashlib.sha256(data).hexdigest() != row["sha256"]:
                raise OverlayMismatch(
                    f"{row['name']}: the bytes at image 0x{row['image_offset']:X} are not the "
                    f"ones the row records")
            path = directory / f"{row['name']}.bin"
            path.write_bytes(data)
            written.append(path)
    return written


def render(rows):
    """The artifact's text: one row per blob, in disc order, six hex numbers and a digest."""
    width = max(len(blob["name"]) for blob in rows)
    lines = ["# Overlay blobs: measured from the retail ELF's zero-fill PT_LOAD reservations and "
             "the pinned image's", "# DATA*.BIN headers.  One row per blob: `name vaddr "
             "filesize code_end data_size bss image_offset sha256`.", "#",
             f"# {'name'.ljust(width)}  vaddr      filesize   code_end   data_size  bss        "
             f"image_offset       sha256"]
    for blob in rows:
        lines.append(f"{blob['name'].ljust(width)}  "
                     f"0x{blob['vaddr']:08X} 0x{blob['filesize']:08X} "
                     f"0x{blob['code_end']:08X} 0x{blob['data_size']:08X} "
                     f"0x{blob['bss']:08X} 0x{blob['image_offset']:08X} {blob['sha256']}")
    return "\n".join(lines) + "\n"


def write(path, rows):
    path = pathlib.Path(path)
    path.write_text(render(rows))


def parse_args(argv):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--target", default=None,
                        help="the target whose ELF, image and config directory to use")
    parser.add_argument("--elf", default=None, help="the retail ELF to measure (default: the "
                                                   "target's)")
    parser.add_argument("--image", default=None, help="the disc image to measure (default: the "
                                                     "target's)")
    parser.add_argument("--blobs", default=None, metavar="DIR",
                        help="also write every blob out of the image into DIR as "
                             "<module>.bin: the pack configure.py accepts instead of the image "
                             "(all ten, not only the modules with a promoted unit)")
    parser.add_argument("--out", default=None, help="where to write (default: the target's "
                                                    "overlays.txt)")
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(sys.argv[1:] if argv is None else argv)
    target = targets.get(args.target) if args.target else DEFAULT
    elf_path = pathlib.Path(args.elf) if args.elf else target.elf
    image_path = pathlib.Path(args.image) if args.image else target.image
    out = pathlib.Path(args.out) if args.out else target.overlays
    try:
        rows = derive(elf_path, image_path)
    except (OverlayMismatch, OSError, ValueError) as exc:
        print(f"emit_overlays: {exc}", file=sys.stderr)
        return 2
    # Round-trip through the reader the tools use: a row this program cannot read back is a
    # row no tool can, and the artifact is what they read.
    write(out, rows)
    try:
        loaded = targets.load_overlays(out)
    except (ValueError, OSError) as exc:
        print(f"emit_overlays: wrote {out}, which does not read back: {exc}", file=sys.stderr)
        return 2
    for overlay in loaded:
        print(f"{overlay.name}: 0x{overlay.vaddr:08X}+0x{overlay.memsz:X} "
              f"(code 0x{overlay.code_end:X}, data 0x{overlay.data_size:X}, "
              f"bss 0x{overlay.bss:X}) at image 0x{overlay.image_offset:08X}")
    if args.blobs:
        try:
            written = write_blobs(elf_path, image_path, args.blobs)
        except (OverlayMismatch, OSError, ValueError) as exc:
            print(f"emit_overlays: {exc}", file=sys.stderr)
            return 2
        print(f"{len(written)} blobs -> {args.blobs} (the pack configure.py accepts in place "
              f"of the image)")
    print(f"{len(loaded)} overlays -> {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
