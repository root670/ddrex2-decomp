#!/usr/bin/env python3
"""nopline measure -- run the control and one variant per candidate, and diff them.

The control is `drafts/nopline/control.c`: retail's `ps2dancerInitHide` shape with nothing
on line 103.  It reproduces retail's shortfall exactly -- `.text` 0x6C and the records
98,100,101,102,104,105, where retail has 0x70 and one more record, for line 103, whose whole
code is the pad `nop` at 0x4C (VA 0x1CF1FC).

Each candidate is injected on line 103, either *inside* the `if` body (after its store, before
the closing brace) or *after* the `if` (before the loop increment) -- the two places retail's
pad could sit.  For each the table prints the `.text` size, whether the word array gained a
`nop` at 0x4C with everything after it shifted, and the line-record delta against the control.

    python3 drafts/nopline/measure.py

Read-only w.r.t. the repo: objects go to temp dirs.
"""

from __future__ import annotations

import pathlib
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

import elf  # noqa: E402
from toolchain import fetch, probe  # noqa: E402

FLAGS = ("-c", "-lang", "c", "-O3", "-g")
BUILD = "3.0-011126"
HERE = pathlib.Path(__file__).resolve().parent

HEAD = """\
struct nopline_savedata {
    unsigned char pad[0x40];
    unsigned char HideFlag[0x100];
};
extern struct nopline_savedata SaveData;
int get_chara_hide(int chara);
"""

INIT_HIDE = """\
#line 98
void ps2dancerInitHide(void) { int i;
#line 99

#line 100
    i = 0;
    do {
#line 101
        if (get_chara_hide(i)) {
#line 102
            SaveData.HideFlag[(i + 0x46) >> 5] |= 1 << ((i + 0x46) & 0x1F);
#line 103
@CANDIDATE@
        }
#line 104
        i++;
    } while (i < 0x2D);
#line 105
}
"""

#: (name, where, candidate text).  ``where`` is "in" (inside the `if` body, after its store)
#: or "after" (between the `if` and the loop increment).
CANDIDATES = [
    ("none", "in", ""),
    ("empty-stmt", "in", "            ;"),
    ("brace-block", "in", "            { }"),
    ("self-assign", "in", "            i = i;"),
    ("void-cast", "in", "            (void)i;"),
    ("label-only", "in", "        nop103: ;"),
    ("label-alone", "in", "        nop103:"),
    ("goto-next", "in", "            goto nop103;\n        nop103: ;"),
    ("goto-fwd-label", "in", "            goto nop103;\n            ;\n        nop103: ;"),
    ("goto-back", "in", "            goto nop103;\n        nop103: ;"),
    ("empty-if-true", "in", "            if (i >= 0) ;"),
    ("empty-if-var", "in", "            if (i) { }"),
    ("empty-else", "in", "            if (i) { } else { }"),
    ("if-else-empty-else", "in", "            if (get_chara_hide(i) == 0) {} else {}"),
    ("empty-switch", "in", "            switch (i) { case 0: break; }"),
    ("empty-switch-default", "in", "            switch (i) { default: ; }"),
    ("do-while-0", "in", "            do { } while (0);"),
    ("discarded-call", "in", "            get_chara_hide(i);"),
    ("decl-103", "in", "            int k;"),
    ("decl-init-103", "in", "            int k = 0;"),
    ("asm-nop", "in", "            __asm__ (\"nop\");"),
    ("asm-nop-block", "in", "            asm (\"nop\");"),
    ("empty-stmt-after", "after", ""),
    ("label-only-after", "after", "    nop103: ;"),
    ("label-alone-after", "after", "    nop103:"),
    ("goto-next-after", "after", "        goto nop103;\n    nop103: ;"),
    ("empty-if-true-after", "after", "        if (i >= 0) ;"),
    ("empty-else-after", "after", "        if (i) { } else { }"),
    ("do-while-0-after", "after", "        do { } while (0);"),
    ("asm-nop-after", "after", "        __asm__ (\"nop\");"),
    ("decl-after", "after", "        int k;"),
]


def source_for(where: str, candidate: str) -> str:
    if where == "in":
        body = HEAD + INIT_HIDE.replace("@CANDIDATE@", candidate)
        return body
    # "after": the candidate replaces the `if` block's own closing brace position
    tail = """\
#line 98
void ps2dancerInitHide(void) { int i;
#line 99

#line 100
    i = 0;
    do {
#line 101
        if (get_chara_hide(i)) {
#line 102
            SaveData.HideFlag[(i + 0x46) >> 5] |= 1 << ((i + 0x46) & 0x1F);
#line 103
        }
@CANDIDATE@
#line 104
        i++;
    } while (i < 0x2D);
#line 105
}
""".replace("@CANDIDATE@", candidate)
    return HEAD + tail


def decode_line(data: bytes, off: int, size: int):
    """[(address, line)] from a Metrowerks DWARF 1 `.line` section at `off`."""
    import struct

    length, base = struct.unpack_from("<II", data, off)
    end = min(off + length, off + size)
    rows = []
    for p in range(off + 8, end, 10):
        line, _pos, delta = struct.unpack_from("<IHI", data, p)
        rows.append((base + delta, line))
    return rows


def measure(source_text: str, name: str) -> dict:
    tmp = pathlib.Path(tempfile.mkdtemp(prefix="nopline-"))
    src = tmp / f"{name}.c"
    src.write_text(source_text)
    obj = tmp / f"{name}.o"
    probe.compile(src, obj, fetch.compiler(BUILD), fetch.wibo(), list(FLAGS))
    e = elf.Elf(obj)
    data = e.data
    funcs = {}
    text_indexes = [i for i, s in enumerate(e.sections)
                    if s.name == ".text" or s.name.startswith(".text")]
    by_index = {i: e.sections[i] for i in text_indexes}
    for sym in e.symbols:
        if sym.shndx in by_index and sym.name and sym.type == 2:
            sec = by_index[sym.shndx]
            body = bytes(data[sec.offset + sym.value:sec.offset + sym.value + sym.size])
            funcs[sym.name] = {"bytes": body,
                               "words": [body[i:i + 4].hex() for i in range(0, len(body), 4)],
                               "rows": []}
    for s in e.sections:
        if s.name == ".line":
            rows = decode_line(data, s.offset, s.size)
            if len(funcs) == 1:
                next(iter(funcs.values()))["rows"] = rows
            else:
                # several functions: attach by address range of the records
                for f in funcs.values():
                    if rows and 0 <= rows[0][0] < len(f["bytes"]):
                        f["rows"] = rows
    return {"name": name, "funcs": funcs, "source": src}


def summarise(control: dict, variant: dict) -> str:
    c = next(iter(control["funcs"].values()))
    v = next(iter(variant["funcs"].values()))
    cw, vw = c["words"], v["words"]
    delta = (len(vw) - len(cw)) * 4
    first = next((i for i in range(min(len(cw), len(vw))) if cw[i] != vw[i]), None)
    extra_nop = None
    if len(vw) == len(cw) + 1:
        # is vw a nop inserted at some index with the rest shifted?
        for i in range(len(vw)):
            if vw[i] == "00000000" and vw[:i] + vw[i + 1:] == cw:
                extra_nop = i * 4
                break
    cr = [ln for _a, ln in c["rows"] if ln]
    vr = [ln for _a, ln in v["rows"] if ln]
    missing = [ln for ln in vr if ln not in cr]
    addr_of = {ln: a for a, ln in v["rows"] if ln}
    note = ""
    if extra_nop is not None:
        note = f"nop at 0x{extra_nop:X} (rest shifted)"
    return (f"| {variant['name']:<22} | 0x{len(vw) * 4:X} "
            f"| {delta:+#x} | {first if first is None else hex(first * 4)} "
            f"| {note or '-'} | records={len(vr)} "
            f"{'+' + ','.join(str(m) for m in missing) if missing else ''} "
            f"{('(103@0x%X)' % addr_of[103]) if 103 in addr_of else ''} |")


def main() -> int:
    control = measure(source_for("in", ""), "control")
    c = next(iter(control["funcs"].values()))
    print(f"control: .text 0x{len(c['bytes']):X}, records " +
          " ".join(f"{ln}@0x{a:X}" for a, ln in c["rows"]))
    print("| candidate | .text | delta | first diff | insert | line |")
    print("|---|---|---|---|---|---|")
    for name, where, cand in CANDIDATES:
        if name == "none":
            continue
        try:
            v = measure(source_for(where, cand), name if where == "in" else name + "@after")
        except Exception as exc:  # a rejected construct is a result too
            print(f"| {name:<22} | COMPILE FAILED: {exc} |")
            continue
        print(summarise(control, v))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
