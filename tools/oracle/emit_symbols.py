"""DWARF names + Ghidra function starts -> splat symbol_addrs.txt."""
import collections, json, pathlib, sys

import dwarf1
from dwarf1 import Dwarf

UNPLACED_REASON = "no AT_location address"


def build(elf_path, ghidra_json_path=None):
    """Every symbol record, undeduplicated and unsorted.

    DWARF functions (`lo = AT_low_pc`, `size = AT_high_pc - lo`), DWARF
    globals/statics (`size = 0`) and every Ghidra function start the DWARF
    does not already name (`func_<ADDR>`).  Objects whose DWARF location
    carries no address are kept with `address = 0`; `final` routes them to
    the unplaced file.
    """
    dw = Dwarf(str(elf_path))
    out = []
    for tu in dw.tus:
        for f in tu.functions():
            lo = f.attrs[dwarf1.AT_low_pc]
            hi = f.attrs[dwarf1.AT_high_pc]
            out.append(dict(name=f.name, address=lo, size=hi - lo, kind="func",
                            provenance="dwarf"))
    for (qn, addr, home, _), _g in dw.globals(None).items():
        out.append(dict(name=qn, address=addr or 0, size=0, kind="obj",
                        provenance="dwarf"))
    if ghidra_json_path:
        known = {r["address"] for r in out}
        for f in json.loads(pathlib.Path(ghidra_json_path).read_text())["functions"]:
            a = int(f["address"], 16)
            if a in known:
                continue
            out.append(dict(name=f"func_{a:08X}", address=a, size=0, kind="func",
                            provenance="ghidra"))
    return out


def partition(records):
    """Objects with no real address come out first, before any renaming."""
    placed, unplaced = [], []
    for r in records:
        if r["kind"] == "obj" and not r["address"]:
            unplaced.append(r)
        else:
            placed.append(r)
    return placed, unplaced


def resolve_names(records):
    """Two records may claim one name (statics repeated across TUs, R12).

    The lowest-address record keeps the bare DWARF spelling; the rest, in
    address order, get `_<n>`, skipping any suffix taken by another record's
    name, and carry `dwarf_name` so the comment still names them.  Records
    are renamed, never dropped.
    """
    taken = {r["name"] for r in records}
    groups = collections.defaultdict(list)
    for r in records:
        groups[r["name"]].append(r)
    for name, rs in groups.items():
        if len(rs) == 1:
            continue
        rs.sort(key=lambda r: r["address"])          # address order, stable
        n = 1
        for r in rs[1:]:
            while f"{name}_{n}" in taken:
                n += 1
            taken.add(f"{name}_{n}")
            if r["provenance"] == "dwarf":
                r["dwarf_name"] = name
            r["name"] = f"{name}_{n}"
            n += 1
    return records


def final(records):
    """`(placed, unplaced)`, each collision-resolved; placed address-sorted."""
    placed, unplaced = partition(records)
    resolve_names(placed)
    resolve_names(unplaced)
    placed.sort(key=lambda r: (r["kind"], r["address"]))
    return placed, unplaced


def duplicates(records):
    seen, dupes = set(), []
    for r in records:
        if r["name"] in seen:
            dupes.append(r["name"])
        seen.add(r["name"])
    return sorted(set(dupes))


def _located(r):
    line = (f'{r["name"]} = 0x{r["address"]:08X}; '
            f'// type:{r["kind"]} size:0x{r["size"]:X} '
            f'provenance:{r["provenance"]}')
    if r.get("dwarf_name"):
        line += f' dwarf_name:{r["dwarf_name"]}'
    return line


def _orphan(r):
    line = (f'{r["name"]} = 0x{r["address"]:08X}; '
            f'// type:{r["kind"]} provenance:{r["provenance"]} '
            f'reason:{UNPLACED_REASON}')
    if r.get("dwarf_name"):
        line += f' dwarf_name:{r["dwarf_name"]}'
    return line


def render(records):
    return "".join(_located(r) + "\n" for r in records)


def render_unplaced(records):
    return "".join(_orphan(r) + "\n" for r in records)


def write(path, records):
    with open(path, "w") as fh:
        fh.write(render(records))


def write_unplaced(path, records):
    with open(path, "w") as fh:
        fh.write(render_unplaced(records))


if __name__ == "__main__":
    elf = sys.argv[1]
    gh = sys.argv[2] if len(sys.argv) > 2 else None
    placed, unplaced = final(build(elf, gh))
    out = pathlib.Path(sys.argv[3] if len(sys.argv) > 3
                       else "config/usam2/symbol_addrs.txt")
    orphan = pathlib.Path(sys.argv[4]) if len(sys.argv) > 4 \
        else out.with_name("unplaced_symbols.txt")
    write(out, placed)
    write_unplaced(orphan, unplaced)
    print(f"{len(placed)} placed ({len(duplicates(placed))} dupes); "
          f"{len(unplaced)} unplaced ({len(duplicates(unplaced))} dupes)")
