"""DWARF names + Ghidra function starts -> splat symbol_addrs.txt."""
import collections, json, pathlib, sys

import dwarf1
from dwarf1 import Dwarf


def _resolve_duplicate_names(records):
    """Two records may claim one name (file statics repeated across TUs).

    Keep the record with the lowest address under the bare DWARF spelling;
    suffix the rest `_<n>` in address order and stash the DWARF spelling on
    the record so the emitted comment still names it.  A record is never
    dropped, only renamed.
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


def build(elf_path, ghidra_json_path=None):
    dw = Dwarf(str(elf_path))
    out = []
    for tu in dw.tus:
        for f in tu.functions():
            lo = f.attrs[dwarf1.AT_low_pc]
            hi = f.attrs[dwarf1.AT_high_pc]
            out.append(dict(name=f.name, address=lo, size=hi - lo, kind="func",
                            provenance="dwarf"))
    for (qn, addr, home, _), _g in dw.globals(None).items():
        out.append(dict(name=qn, address=addr, size=0, kind="obj", provenance="dwarf"))
    if ghidra_json_path:
        known = {r["address"] for r in out}
        for f in json.loads(pathlib.Path(ghidra_json_path).read_text())["functions"]:
            a = int(f["address"], 16)
            if a in known:
                continue
            out.append(dict(name=f"func_{a:08X}", address=a, size=0, kind="func",
                            provenance="ghidra"))
    _resolve_duplicate_names(out)
    out.sort(key=lambda r: (r["kind"], r["address"]))
    return out


def duplicates(records):
    seen, dupes = set(), []
    for r in records:
        if r["name"] in seen:
            dupes.append(r["name"])
        seen.add(r["name"])
    return sorted(set(dupes))


def write(path, records):
    with open(path, "w") as fh:
        for r in records:
            line = (f'{r["name"]} = 0x{r["address"]:08X}; '
                    f'// type:{r["kind"]} size:0x{r["size"]:X} '
                    f'provenance:{r["provenance"]}')
            if r.get("dwarf_name"):
                line += f' dwarf_name:{r["dwarf_name"]}'
            fh.write(line + "\n")


if __name__ == "__main__":
    elf = sys.argv[1]
    gh = sys.argv[2] if len(sys.argv) > 2 else None
    recs = build(elf, gh)
    write(sys.argv[3] if len(sys.argv) > 3 else "config/usam2/symbol_addrs.txt", recs)
    print(f"{len(recs)} symbols; {len(duplicates(recs))} duplicates")
