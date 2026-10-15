"""Compile-unit map -> the debug chunk manifest, `config/usam2/debug_chunks.json`.

The manifest carries the two DWARF sections as byte ranges that a splitter can
turn into one `databin` each: `.debug` splits once per translation unit (the 57
contiguous runs of CU records that share a `file`) and `.line` splits once per
function CU (the 423 statement-list extents).  Both tilings must be exact --
start at 0, abut, and end on the real section length.  A gap or an overlap
means the manifest is wrong, so this module raises instead of repairing it
(Review Focus 4); offsets resolve through `chunk_for`, which raises
`emit_cus.NoCompileUnit` outside every chunk of the requested section.
"""
import bisect, json, pathlib, sys

import emit_cus
from emit_cus import NoCompileUnit

DEBUG = ".debug"
LINE = ".line"
SECTIONS = (DEBUG, LINE)
DEBUG_SIZE = 657815     # .debug length in orig/SLUS_207.11 (see emit_cus)
LINE_SIZE = 140704      # .line length in orig/SLUS_207.11


def _records(path):
    return json.loads(pathlib.Path(path).read_text())


def _check_record_tiling(cus, size):
    """The CU map must tile `.debug` byte-for-byte, or the chunks would lie."""
    end = 0
    for cu in cus:
        if cu["offset"] != end or cu["size"] <= 0:
            raise NoCompileUnit(
                f"CU {cu['index']} ({cu['file']}) covers "
                f"0x{cu['offset']:x}+{cu['size']}, not a {end:#x} start: "
                f"the .debug tiling has a gap or an overlap")
        end = cu["offset"] + cu["size"]
    if not cus or end != size:
        raise NoCompileUnit(
            f"the compile-unit map tiles {end} bytes of .debug, "
            f"not the {size} in the ELF")


def _debug_chunks(cus, size):
    """One chunk per translation unit: the span of that TU's CU records."""
    _check_record_tiling(cus, size)
    runs, seen = [], set()
    for cu in cus:
        if not runs or runs[-1][0]["file"] != cu["file"]:
            if cu["file"] in seen:
                raise NoCompileUnit(
                    f"translation unit {cu['file']} is split in .debug at "
                    f"0x{cu['offset']:x}: chunks must be contiguous runs")
            seen.add(cu["file"])
            runs.append([])
        runs[-1].append(cu)
    return [dict(section=DEBUG,
                 offset=run[0]["offset"],
                 size=run[-1]["offset"] + run[-1]["size"] - run[0]["offset"],
                 tunits=[cu["index"] for cu in run])
            for run in runs]


def _line_chunks(cus, size):
    """One chunk per function CU: its `stmt_list` extent in `.line`."""
    pairs = [(cu["stmt_list"], cu["index"]) for cu in cus
             if cu["kind"] == "function"]
    if any(stmt is None for stmt, _ in pairs):
        raise NoCompileUnit("a function CU has no .line statement list")
    offsets = [stmt for stmt, _ in pairs]
    if len(set(offsets)) != len(offsets):
        raise NoCompileUnit(f".line offsets repeat: {len(offsets)} function CUs "
                            f"but {len(set(offsets))} distinct statement lists")

    chunks = [dict(section=LINE, offset=stmt, size=None, tunits=[index])
              for stmt, index in sorted(pairs)]
    if not chunks or chunks[0]["offset"] != 0:
        raise NoCompileUnit("the .line chunks do not start at .line+0x0")
    if chunks[-1]["offset"] >= size:
        raise NoCompileUnit(
            f"statement list {chunks[-1]['offset']} lies at or past the "
            f"{size}-byte .line section: no room for a chunk")

    # Distinct offsets in ascending order make each chunk end exactly where the
    # next begins; the last closes on the section, so every .line byte belongs
    # to exactly one function CU instead of falling into a gap.
    for chunk, nxt in zip(chunks, chunks[1:]):
        chunk["size"] = nxt["offset"] - chunk["offset"]
    chunks[-1]["size"] = size - chunks[-1]["offset"]
    return chunks


def build(cus_path, line_size=LINE_SIZE, debug_size=DEBUG_SIZE):
    """The manifest: 57 `.debug` chunks then 423 `.line` chunks, each tiling."""
    cus = _records(cus_path)
    return _debug_chunks(cus, debug_size) + _line_chunks(cus, line_size)


def chunk_for(chunks, section, offset):
    """The chunk covering `offset` bytes into `section`.

    A negative, past-the-end, or otherwise uncovered offset -- or a section the
    manifest does not carry -- belongs to no chunk; that is a hard error so a
    missing chunk surfaces instead of being skipped.
    """
    if section not in SECTIONS:
        raise NoCompileUnit(f"the manifest carries no {section} section")
    part = [c for c in chunks if c["section"] == section]
    i = bisect.bisect_right([c["offset"] for c in part], offset) - 1
    if i >= 0 and offset < part[i]["offset"] + part[i]["size"]:
        return part[i]
    raise NoCompileUnit(f"no {section} chunk covers {section}+0x{offset:x}")


def render(chunks):
    return json.dumps(chunks, indent=2) + "\n"


def write(path, chunks):
    pathlib.Path(path).write_text(render(chunks))


if __name__ == "__main__":
    cus_path = sys.argv[1] if len(sys.argv) > 1 else "config/usam2/cus.json"
    out = sys.argv[2] if len(sys.argv) > 2 else "config/usam2/debug_chunks.json"
    chunks = build(cus_path)
    write(out, chunks)
    counts = {s: sum(1 for c in chunks if c["section"] == s) for s in SECTIONS}
    print(f"{counts[DEBUG]} .debug chunks, {counts[LINE]} .line chunks "
          f"from {cus_path} -> {out}")
