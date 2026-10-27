"""`.debug` walk -> a target's compile-unit map, `cus.json`.

Every DWARF 1 compile unit in the retail `.debug` section becomes one record: the
translation-unit headers (the range-less CU that opens each TU) and the per-function CUs
nested after them.  Records tile `.debug` exactly: each record's `size` is the byte distance
to the next record's offset, and the last ends at the section length.  A CU missing from that
tiling is an error, not a gap to skip (Review Focus 4), so callers resolve offsets with
`owner_of`, which raises `NoCompileUnit` outside every record.

The ELF is a parameter (`build(elf_path)`) and the output path comes from the target's
descriptor, so nothing here is bound to one game's config directory.
"""
import bisect, json, pathlib, re, sys

import dwarf1
from dwarf1 import Dwarf

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[2]))  # `config.targets`
from config import targets

DEFAULT = targets.get(targets.DEFAULT)
DEBUG_SECTION = ".debug"


class NoCompileUnit(LookupError):
    """No compile-unit record covers the requested `.debug` offset."""


def relpath(name):
    """`<anything>/src/sys/sys_scf.c` -> `src/sys/sys_scf.c` (POSIX).

    The retail build's own drive and working directory (`C:\\work\\<tree>\\...`) are dropped:
    the tree-relative source path identifies a translation unit, and it is the same spelling
    the generated headers use under `include/`.
    """
    p = (name or "").replace("\\", "/")
    m = re.search(r"(?:^|/)src/", p)
    return p[m.start():].lstrip("/") if m else p.split("/")[-1]


def build(elf_path):
    """Every compile-unit record, in `.debug` offset order."""
    dw = Dwarf(str(elf_path))
    units = []
    for tu in dw.tus:
        for cu in tu.cus:
            units.append(dict(
                index=None,
                kind="tu" if cu is tu.decl else "function",
                offset=cu.off,
                size=None,
                name=cu.name,
                file=relpath(tu.name),
                # The module the unit loads in: `main`, or the stem of the DWARF
                # `DW_TAG_MW_overlay` name (`dmm_rel4cd`, whose blob names itself
                # `dmm_rel4cd.prg`).  This is the *only* evidence that separates the seven
                # modules that are alternatives at 0x7F0000 -- their addresses overlap, so
                # nothing downstream can recover it from a PC.  It decides a unit's split
                # directory and which disc blob its retail bytes come from.
                overlay=targets.overlay_stem(tu.overlay),
                low_pc=cu.attrs.get(dwarf1.AT_low_pc),
                high_pc=cu.attrs.get(dwarf1.AT_high_pc),
                stmt_list=cu.attrs.get(dwarf1.AT_stmt_list)))
    units.sort(key=lambda u: u["offset"])
    for i, u in enumerate(units):
        u["index"] = i
        u["size"] = ((units[i + 1]["offset"] - u["offset"]) if i + 1 < len(units)
                     else len(dw.buf) - u["offset"])
    return units


def owner_of(cus, offset):
    """The record covering `offset` bytes into `.debug`.

    `cus` must be sorted by offset, as `build` returns it.  A negative or
    past-the-end offset belongs to no compile unit; that is a hard error so a
    missing CU surfaces instead of being skipped.
    """
    i = bisect.bisect_right([c["offset"] for c in cus], offset) - 1
    if i >= 0 and offset < cus[i]["offset"] + cus[i]["size"]:
        return cus[i]
    raise NoCompileUnit(f"no compile unit covers .debug+0x{offset:x}")


def render(cus):
    return json.dumps(cus, indent=2) + "\n"


def write(path, cus):
    pathlib.Path(path).write_text(render(cus))


if __name__ == "__main__":
    elf = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else str(DEFAULT.cus)
    cus = build(elf)
    write(out, cus)
    tus = sum(1 for c in cus if c["kind"] == "tu")
    print(f"{len(cus)} CUs written ({tus} tus, {len(cus) - tus} functions) -> {out}")
