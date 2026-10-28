# DDRMAX2 US — Oracle, Toolchain and Byte-Identical Skeleton Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make `ninja` produce a byte-identical `out/SLUS_207.11` and a byte-identical rebuilt disc image with **zero C written**, then promote the first translation unit (`src/sys/sys_scf.c`, two functions) and prove its code and debug bytes match.

**Architecture:** Pin-and-match. A vendored CodeWarrior DWARF 1 reader turns the retail ELF into a symbol file, per-CU debug-chunk map and per-TU headers; splat splits the single loadable region into per-function and per-object pieces; every section's load address equals its retail file offset, so assembling and linking the splits, extracting the loadable half with `objcopy -O binary`, and appending the non-loadable tail from databin segments reproduces the retail file byte for byte (R29). C compiled by `mwccps2` (under wibo) then replaces those splits one translation unit at a time.

**Tech Stack:** Python 3 (stdlib only in the oracle, pytest for tests), splat + spimdisasm, Ninja, `mips-linux-gnu` binutils (Homebrew), `mwccps2`/`mwldps2` from the decomp.me compiler archives run through wibo + Rosetta 2, `objdiff-cli`, GNU `ld` + `objcopy`.

**Spec:** `docs/superpowers/specs/2026-10-14-ddrmax2-us-decomp-design.md`

## Global Constraints

- Target: `orig/SLUS_207.11`, size 2,512,980, sha256 `a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc`, `e_flags 0x20924000`, loadable region `0x00100000`/size 1,713,792 at file offset `0x80`, `.debug` 657,815 B at `0x1a2740`, `.line` 140,704 B at `0x2430e0`, `.comment` 43 B at `0x265680`, `.reginfo` 24 B at `0x2656ac`, `.shstrtab` 58 B at `0x1a2700`.
- Retail image: sha256 `b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8`, 1,244,823,552 B, 2048-byte sectors, ELF at byte offset `0x92000`.
- **G1** is the gate: `out/SLUS_207.11` sha256 equals the retail sha256, whole file, debug sections included. **G3** is the gate: rebuilt image sha256 equals the retail image sha256. **G2** is the diagnostic that names the first differing TU when G1 fails.
- DWARF facts that must hold after the oracle runs: 480 compile units (57 translation units + 423 functions), 818 aggregate DIEs / 123 distinct names, 1,586 locals, 577 parameters, 639 globals/statics, `0 sibling/length problems`.
- Never commit retail binaries, disc images or toolchains: `orig/`, `disc/`, `toolchain/`, `build/`, `out/`, `asm/` stay gitignored.
- Names are never invented: DWARF names where present, otherwise `func_<ADDR>`/`lbl_<ADDR>`/`D_<ADDR>`, with provenance recorded in the symbol file.
- Statements land on the original line numbers the oracle reports for that address.
- Host is macOS arm64; no Docker; the Windows compiler runs through wibo under Rosetta 2.
- Repo licence MIT; every borrowed artifact gets a `THIRD_PARTY_NOTICES.md` entry with licence and a pinned hash.
- Oracle code is Python 3 **stdlib only**; all tests run with `python3 -m pytest`.

## Review Focus

1. A promoted TU whose `.line` chunk drifts must surface as a *named TU* with the first differing byte, never a bare whole-file mismatch (Task 11).
2. `orig/SLUS_207.11` missing, truncated or a different version must fail loudly with the expected hash, never build something plausible (Tasks 9, 11).
3. A partial or corrupted compiler download must be rejected by hash before use (Task 5).
4. A compile unit absent from `cus.json` must fail loudly rather than be skipped silently (Tasks 3, 4).
5. Duplicate function names across translation units must be attributed explicitly, never silently dropped or renamed (Task 2).

## File Structure

| path | responsibility |
|---|---|
| `tools/oracle/dwarf1.py`, `demangle.py`, `elf.py` | vendored CodeWarrior DWARF 1 reader (unmodified) |
| `tools/oracle/emit_symbols.py` | DWARF + Ghidra function list → `config/usam2/symbol_addrs.txt` |
| `tools/oracle/emit_cus.py` | `.debug` walk → `config/usam2/cus.json` (480 records) |
| `tools/oracle/emit_headers.py` | per-TU C skeletons → `include/<tu>.h` |
| `tools/oracle/emit_chunks.py` | `cus.json` → `config/usam2/debug_chunks.json` + chunk manifest |
| `tools/toolchain/fetch.py` | download and hash-verify compilers + wibo into `toolchain/` |
| `tools/toolchain/probe.py` | run `mwccps2` under wibo on a probe C file, assert object shape |
| `tools/toolchain/check_deps.py` | verify `mips-linux-gnu-*`, `objdiff-cli`, `ninja`, `splat` |
| `tools/iso/reinsert.py` | write the built ELF into a copy of the retail image at `0x92000` |
| `tools/verify/g1.py`, `tools/verify/g2.py` | whole-file hash comparison; TU/chunk divergence localiser |
| `config/usam2/splat.yaml` | splat config: segments, subsegments, section order |
| `config/usam2/symbol_addrs.txt` | generated symbol file (splat syntax, provenance comments) |
| `config/usam2/cus.json`, `debug_chunks.json`, `checksums.txt` | generated oracle artifacts |
| `configure.py` | runs splat, emits `build.ninja` |
| `ddr` | project CLI: `oracle`, `build`, `verify`, `diff`, `iso` |
| `src/sys/sys_scf.c` | first promoted translation unit |
| `inline_asm.h` | `INCLUDE_ASM` / `INCLUDE_DATA` macro with `SKIP_ASM` guard |
| `tests/` | pytest suites, one directory per tool area |
| `AGENTS.md`, `docs/milestones/m2-sys-scf.md`, `.github/workflows/*.yml` | contract, evidence, CI |

---

### Task 1: Vendor and characterise the DWARF 1 oracle

**Files:**
- Create: `tools/oracle/dwarf1.py`, `tools/oracle/demangle.py`, `tools/oracle/elf.py`, `tools/oracle/README.md`
- Create: `tests/oracle/test_conformance.py`, `tests/oracle/__init__.py`
- Create: `THIRD_PARTY_NOTICES.md`
- Create: `orig/usam2.elf.txt` (copy of the vendor dump, gitignored)

**Interfaces:**
- Consumes: nothing.
- Produces: `dwarf1.py` importable from `tools/oracle` (`from dwarf1 import Dwarf, Elf`), CLI `python3 tools/oracle/dwarf1.py {stats,cus,fn,type,globals,lines,header,check,dump} <elf> …`; `dwarf1.main()` unchanged.

- [ ] **Step 1: Write the failing test**

```python
# tests/oracle/test_conformance.py
import subprocess, sys, pathlib
ROOT = pathlib.Path(__file__).resolve().parents[2]
CLI = ROOT / "tools/oracle/dwarf1.py"
ELF = ROOT / "orig/SLUS_207.11"

def run(cmd, *args):
    return subprocess.run([sys.executable, str(CLI), cmd, str(ELF), *args],
                          capture_output=True, text=True, check=True).stdout

def test_dwarf_counts_match_retail():
    out = run("stats")
    assert "compile units 480 (423 with code)" in out
    assert "translation units 57" in out
    assert "functions 423 (with code 423)" in out
    assert "818 (123 distinct names)" in out
    assert "unique globals/statics 639" in out

def test_tree_is_self_consistent():
    assert "0 sibling/length problems" in run("check")

def test_known_function_bounds_and_lines():
    assert "sysInitScf" in run("fn", "sysInitScf")
    assert "0x0021c420" in run("lines", "0x21c420")
```

- [ ] **Step 2: Run test to verify it fails**

Run: `python3 -m pytest tests/oracle/test_conformance.py -v`
Expected: FAIL — `can't open file .../tools/oracle/dwarf1.py`.

- [ ] **Step 3: Vendor the three files and pin their hashes**

```bash
mkdir -p tools/oracle tests/oracle
for f in dwarf1.py demangle.py elf.py; do
  curl -sL -o "tools/oracle/$f" "https://raw.githubusercontent.com/Toyz/piney_apples/main/tools/$f"
done
shasum -a 256 tools/oracle/*.py
```

Record the three hashes verbatim in `THIRD_PARTY_NOTICES.md` under `piney_apples (MIT OR Apache-2.0)`, noting they were fetched on 2026-10-14 and are unmodified.

- [ ] **Step 4: Copy the vendor dump for cross-checking**

```bash
cp "<your copy>/DDRMAX2 US.elf.txt" orig/usam2.elf.txt
```

- [ ] **Step 5: Run the tests and confirm they pass**

Run: `python3 -m pytest tests/oracle/ -v`
Expected: 3 passed.

- [ ] **Step 6: Cross-check against the vendor's own dump**

```python
# tests/oracle/test_vendor_dump.py
import re, pathlib, subprocess, sys, pytest
ROOT = pathlib.Path(__file__).resolve().parents[2]
DUMP = ROOT / "orig/usam2.elf.txt"

def test_dump_and_reader_agree_on_functions():
    if not DUMP.exists():
        pytest.skip("vendor dump not staged")
    text = DUMP.read_text(encoding="latin1")
    dump_low_pcs = set(re.findall(r"AT_low_pc\(([0-9a-f]{8})\)", text))
    reader = subprocess.run([sys.executable, str(ROOT / "tools/oracle/dwarf1.py"),
                             "cus", str(ROOT / "orig/SLUS_207.11")],
                            capture_output=True, text=True, check=True).stdout
    assert len(reader.splitlines()) >= 423          # one line per compile unit
    assert len(dump_low_pcs) >= 423                 # the vendor's own parse agrees
```

- [ ] **Step 7: Commit**

```bash
git add tools/oracle THIRD_PARTY_NOTICES.md tests/oracle
git commit -m "oracle: vendor and characterise the CodeWarrior DWARF 1 reader"
```

---

### Task 2: Symbol file from DWARF plus the Ghidra function list

**Files:**
- Create: `tools/oracle/emit_symbols.py`
- Create: `tests/oracle/test_emit_symbols.py`
- Create (generated): `config/usam2/symbol_addrs.txt`

**Interfaces:**
- Consumes: `tools/oracle/dwarf1.py`; `/list_functions` from the Ghidra MCP HTTP API at `127.0.0.1:8089`.
- Produces: `emit_symbols.build(elf_path, ghidra_json_path=None) -> list[dict]` with keys `name`, `address`, `size`, `kind`, `provenance`; `emit_symbols.write(path, records)`; splat syntax one per line: `name = 0xADDR; // type:func size:0xSIZE // provenance: dwarf`.

- [ ] **Step 1: Write the failing test**

```python
# tests/oracle/test_emit_symbols.py
import pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_symbols

def test_dwarf_functions_keep_their_names():
    recs = emit_symbols.build(ROOT / "orig/SLUS_207.11")
    by_addr = {r["address"]: r for r in recs}
    assert by_addr[0x0021C420]["name"] == "sysInitScf"
    assert by_addr[0x0021C420]["size"] == 0x30
    assert by_addr[0x0021C420]["provenance"] == "dwarf"

def test_counts_are_reported_by_the_reader():
    recs = emit_symbols.build(ROOT / "orig/SLUS_207.11")
    funcs = [r for r in recs if r["provenance"] == "dwarf" and r["kind"] == "func"]
    objs = [r for r in recs if r["provenance"] == "dwarf" and r["kind"] == "obj"]
    assert len(funcs) == 423
    assert len(objs) == 639          # if the reader reports another count, fix this constant

def test_duplicate_names_are_reported_not_dropped():
    recs = emit_symbols.build(ROOT / "orig/SLUS_207.11")
    dupes = emit_symbols.duplicates(recs)
    assert dupes == [], f"duplicate names must be resolved explicitly, got {dupes}"
```

- [ ] **Step 2: Run test to verify it fails**

Run: `python3 -m pytest tests/oracle/test_emit_symbols.py -v`
Expected: FAIL — `No module named 'emit_symbols'`.

- [ ] **Step 3: Implement the emitter**

```python
# tools/oracle/emit_symbols.py
"""DWARF names + Ghidra function starts -> splat symbol_addrs.txt."""
import json, pathlib, sys
from dwarf1 import Dwarf, Elf

def build(elf_path, ghidra_json_path=None):
    import dwarf1
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
        names = {r["address"] for r in out}
        for f in json.loads(pathlib.Path(ghidra_json_path).read_text())["functions"]:
            a = int(f["address"], 16)
            if a in names:
                continue
            out.append(dict(name=f"func_{a:08X}", address=a, size=0, kind="func",
                            provenance="ghidra"))
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
            fh.write(f'{r["name"]} = 0x{r["address"]:08X}; '
                     f'// type:{r["kind"]} size:0x{r["size"]:X} provenance:{r["provenance"]}\n')

if __name__ == "__main__":
    elf = sys.argv[1]
    gh = sys.argv[2] if len(sys.argv) > 2 else None
    recs = build(elf, gh)
    write(sys.argv[3] if len(sys.argv) > 3 else "config/usam2/symbol_addrs.txt", recs)
    print(f"{len(recs)} symbols; {len(duplicates(recs))} duplicates")
```

- [ ] **Step 4: Export the Ghidra function list**

```bash
mkdir -p config/usam2 toolchain
curl -s "http://127.0.0.1:8089/list_functions?limit=10000" -o config/usam2/ghidra_functions.json
python3 -c "import json;d=json.load(open('config/usam2/ghidra_functions.json'));print(len(d['functions']),'functions')"
```

Expected: `3161 functions` (the current Ghidra program must be `SLUS_207.11`; verify with `curl -s http://127.0.0.1:8089/check_connection`).

- [ ] **Step 5: Generate and inspect the symbol file**

```bash
python3 tools/oracle/emit_symbols.py orig/SLUS_207.11 config/usam2/ghidra_functions.json config/usam2/symbol_addrs.txt
grep -c "provenance:dwarf" config/usam2/symbol_addrs.txt
grep -c "provenance:ghidra" config/usam2/symbol_addrs.txt
grep "sysInitScf" config/usam2/symbol_addrs.txt
```

Expected: 1,062 DWARF records (423 functions + 639 globals/statics) and 2,738 `provenance:ghidra` placeholders — the Ghidra function list is 3,161 and only the 423 DWARF *functions* overlap it, so every other Ghidra entry gets a placeholder — plus `sysInitScf = 0x0021C420; // type:func size:0x30 provenance:dwarf`. Object records with no address (27 unplaced statics) are written to `config/usam2/unplaced_symbols.txt` instead, so no symbol ever sits at address `0x0` and nothing is dropped.

- [ ] **Step 6: Run the tests and commit**

Run: `python3 -m pytest tests/oracle/test_emit_symbols.py -v` → 3 passed.

```bash
git add tools/oracle/emit_symbols.py tests/oracle/test_emit_symbols.py config/usam2/symbol_addrs.txt
git commit -m "oracle: emit splat symbol file from DWARF plus Ghidra function starts"
```

---

### Task 3: CU map and per-TU headers

**Files:**
- Create: `tools/oracle/emit_cus.py`, `tools/oracle/emit_headers.py`
- Create: `tests/oracle/test_emit_cus.py`, `tests/oracle/test_emit_headers.py`
- Create (generated): `config/usam2/cus.json`, `include/**/*.h`

**Interfaces:**
- Consumes: `dwarf1.Dwarf`.
- Produces: `cus.json` = JSON list of 480 records `{index, kind: "tu"|"function", offset, size, name, file, low_pc, high_pc}`; `include/<relpath>.h` per TU with prototypes, aggregates and globals.

- [ ] **Step 1: Write the failing tests**

```python
# tests/oracle/test_emit_cus.py
import json, pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_cus

def test_cu_map_is_complete_and_contiguous():
    cus = emit_cus.build(ROOT / "orig/SLUS_207.11")
    assert len(cus) == 480
    assert sum(1 for c in cus if c["kind"] == "tu") == 57
    assert sum(1 for c in cus if c["kind"] == "function") == 423
    assert cus[0]["offset"] == 0
    for a, b in zip(cus, cus[1:]):
        assert a["offset"] + a["size"] == b["offset"]
    assert cus[-1]["offset"] + cus[-1]["size"] == 657815      # .debug size

def test_unknown_offset_raises():
    cus = emit_cus.build(ROOT / "orig/SLUS_207.11")
    import pytest
    with pytest.raises(emit_cus.NoCompileUnit):
        emit_cus.owner_of(cus, 657815 + 5)
```

```python
# tests/oracle/test_emit_headers.py
import pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_headers

def test_sys_scf_header_has_types_globals_and_prototypes():
    text = emit_headers.render(ROOT / "orig/SLUS_207.11", "sys_scf.c")
    assert "struct _tag_SYS_SCF_WORK" in text
    assert "int date_notation;" in text
    assert "_tag_SYS_SCF_WORK *pscf;" in text
    assert "void sysInitScf(_tag_SYS_SCF_WORK *p);" in text
    assert "0x0021C410-0x0021C41C" in text
```

- [ ] **Step 2: Run tests to verify they fail**

Run: `python3 -m pytest tests/oracle/test_emit_cus.py tests/oracle/test_emit_headers.py -v`
Expected: FAIL — modules not found.

- [ ] **Step 3: Implement `emit_cus.py`**

Walk `.debug` using `Dwarf`'s compile units in file order; each record's `size` is the byte distance to the next unit; `owner_of(cus, off)` bisects and raises `NoCompileUnit` when the offset falls outside every unit (this is Review Focus 4 — a missing CU must not be skipped).

```python
class NoCompileUnit(LookupError):
    pass

def build(elf_path):
    import dwarf1
    dw = Dwarf(str(elf_path))
    units = []
    for tu in dw.tus:
        for cu in tu.cus:
            units.append(dict(offset=cu.off,
                              kind="tu" if cu is tu.decl else "function",
                              name=cu.name,
                              low_pc=cu.attrs.get(dwarf1.AT_low_pc),
                              high_pc=cu.attrs.get(dwarf1.AT_high_pc)))
    units.sort(key=lambda u: u["offset"])
    for i, u in enumerate(units):
        u["index"] = i
        u["size"] = ((units[i + 1]["offset"] - u["offset"]) if i + 1 < len(units)
                     else len(dw.buf) - u["offset"])
    return units

def owner_of(cus, offset):
    for c in cus:
        if c["offset"] <= offset < c["offset"] + c["size"]:
            return c
    raise NoCompileUnit(f"no compile unit covers .debug+0x{offset:x}")
```

- [ ] **Step 4: Implement `emit_headers.py`** using `dwarf1.py header --cu` output, writing `include/<relpath>.h` for all 57 TUs, plus `include/README.md` stating these files are generated and hand edits go elsewhere.

- [ ] **Step 5: Generate and verify**

```bash
python3 tools/oracle/emit_cus.py orig/SLUS_207.11 config/usam2/cus.json
python3 tools/oracle/emit_headers.py orig/SLUS_207.11 include
python3 -m pytest tests/oracle/ -v
```

Expected: 480 CUs written, 57 headers emitted, all tests pass.

- [ ] **Step 6: Commit**

```bash
git add tools/oracle/emit_cus.py tools/oracle/emit_headers.py tests/oracle config/usam2/cus.json include
git commit -m "oracle: emit compile-unit map and per-TU headers"
```

---

### Task 4: Debug chunk manifest

**Files:**
- Create: `tools/oracle/emit_chunks.py`, `tests/oracle/test_emit_chunks.py`
- Create (generated): `config/usam2/debug_chunks.json`

**Interfaces:**
- Consumes: `config/usam2/cus.json`.
- Produces: `debug_chunks.json` = list of `{section: ".debug"|".line", offset, size, tunits: [indices]}` where each chunk is one TU's contiguous range; `emit_chunks.chunk_for(chunks, section, offset)` raising `NoCompileUnit`.

- [ ] **Step 1: Write the failing test**

```python
# tests/oracle/test_emit_chunks.py
import json, pathlib, pytest, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_chunks

def test_chunks_tile_both_sections_exactly():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    for section, size in ((".debug", 657815), (".line", 140704)):
        part = [c for c in chunks if c["section"] == section]
        assert part[0]["offset"] == 0
        assert sum(c["size"] for c in part) == size
        for a, b in zip(part, part[1:]):
            assert a["offset"] + a["size"] == b["offset"]

def test_offsets_outside_any_chunk_raise():
    chunks = emit_chunks.build(ROOT / "config/usam2/cus.json")
    with pytest.raises(emit_chunks.NoCompileUnit):
        emit_chunks.chunk_for(chunks, ".debug", 10**9)
```

- [ ] **Step 2: Run test to verify it fails** — `python3 -m pytest tests/oracle/test_emit_chunks.py -v` → FAIL (module missing).

- [ ] **Step 3: Implement `emit_chunks.py`**

Group the 480 CU records by `file` (one chunk per TU, taken from the first and last CU of that file in `.debug`), and derive `.line` chunks from each function CU's `stmt_list` extent; assert both tilings are exact and raise on overlap or gap rather than repairing them.

- [ ] **Step 4: Generate and verify**

```bash
python3 tools/oracle/emit_chunks.py config/usam2/cus.json config/usam2/debug_chunks.json
python3 -m pytest tests/oracle/test_emit_chunks.py -v
```

Expected: 57 `.debug` chunks + 423 `.line` chunks, both exact tilings, test passes.

- [ ] **Step 5: Commit**

```bash
git add tools/oracle/emit_chunks.py tests/oracle/test_emit_chunks.py config/usam2/debug_chunks.json
git commit -m "oracle: emit per-TU debug chunk manifest"
```

---

### Task 5: Fetch the toolchain with hash verification

**Files:**
- Create: `tools/toolchain/fetch.py`, `tests/toolchain/test_fetch.py`, `tests/toolchain/__init__.py`
- Create (generated, gitignored): `toolchain/mwcps2-2.4-001213/*`, `toolchain/wibo`

**Interfaces:**
- Consumes: network.
- Produces: `fetch.compiler(version, root=..., override_url=None) -> pathlib.Path` (directory containing `mwccps2.exe`, `mwldps2.exe`, `asm_r5900_elf.exe`, `LMGR326B.DLL`); `fetch.wibo() -> pathlib.Path`; `fetch.CANDIDATES` listing `2.4-001213`, `3.0-011126`, `3.0.1-020123`, `3.0b38-030307`, `3.0.3-020716`.

- [ ] **Step 1: Write the failing test**

```python
# tests/toolchain/test_fetch.py
import hashlib, pathlib, pytest, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch

MWCCPS2_SHA256 = "98d3fb6fc362c6b28208e1cc05ff25e32b7c78ffca0c3114cde5392a67c06294"

def test_compiler_archive_has_expected_members(tmp_path):
    d = fetch.compiler("2.4-001213", root=tmp_path)
    assert (d / "mwccps2.exe").stat().st_size == 1379328
    assert (d / "mwldps2.exe").exists() and (d / "asm_r5900_elf.exe").exists()

def test_compiler_binary_hash_is_pinned(tmp_path):
    d = fetch.compiler("2.4-001213", root=tmp_path)
    assert hashlib.sha256((d / "mwccps2.exe").read_bytes()).hexdigest() == MWCCPS2_SHA256

def test_corrupt_archive_is_rejected(tmp_path):
    bad = tmp_path / "mwcps2-2.4-001213.tar.gz"
    bad.write_bytes(b"not a tarball")
    with pytest.raises(fetch.HashMismatch):
        fetch.compiler("2.4-001213", root=tmp_path, override_url=f"file://{bad}")
```

- [ ] **Step 2: Run test to verify it fails** — `python3 -m pytest tests/toolchain/test_fetch.py -v` → FAIL (module missing).

- [ ] **Step 3: Implement `fetch.py`**

```python
BASE = "https://github.com/decompme/compilers/releases/download/compilers"
ARTIFACTS = {
    "2.4-001213":   "mwcps2-2.4-001213.tar.gz",
    "3.0-011126":   "mwcps2-3.0-011126.tar.gz",
    "3.0.1-020123": "mwcps2-3.0.1-020123.tar.gz",
    "3.0b38-030307": "mwcps2-3.0b38-030307.tar.gz",
    "3.0.3-020716": "mwcps2-3.0.3-020716.tar.gz",
}
WIBO_URL = "https://github.com/decompals/wibo/releases/latest/download/wibo-macos"
```

Download to `toolchain/.downloads/`, verify the tarball's member hashes against `PINNED` (Review Focus 3: verify before use, never after), extract with `tarfile`, and for wibo prefer the already-built patched binary at `~/ac-decomp/.cache/wibo/*/wibo` when the download fails, recording which path was used in `toolchain/PROVENANCE.txt`.

- [ ] **Step 4: Run the fetch and the tests**

```bash
python3 tools/toolchain/fetch.py 2.4-001213
python3 -m pytest tests/toolchain/test_fetch.py -v
```

Expected: archive fetched, hashes verified, 3 passed.

- [ ] **Step 5: Commit**

```bash
git add tools/toolchain/fetch.py tests/toolchain
git commit -m "toolchain: fetch and hash-verify mwccps2 candidates and wibo"
```

---

### Task 6: Prove the compiler runs under wibo

**Files:**
- Create: `tools/toolchain/probe.py`, `tests/toolchain/test_probe.py`, `tests/toolchain/probe.c`
- Create (generated): `build/probe/probe.o`

**Interfaces:**
- Consumes: `fetch.compiler`, `fetch.wibo`.
- Produces: `probe.compile(src, obj, compiler_dir, wibo, flags) -> None`; `probe.inspect(obj) -> dict` with `sections`, `comment`, `debug_kind`, `text`.

- [ ] **Step 1: Write the failing test**

```python
# tests/toolchain/test_probe.py
import pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch, probe

def test_compiler_produces_metrowerks_object(tmp_path):
    d = fetch.compiler("2.4-001213")
    obj = tmp_path / "probe.o"
    probe.compile(ROOT / "tests/toolchain/probe.c", obj, d, fetch.wibo(),
                  ["-c", "-lang", "c", "-O2", "-g"])
    info = probe.inspect(obj)
    # A compile-only object carries the compiler string; `PlayStation2` is added by MWLD at link
    # time, so the retail 43-byte string is a post-link artifact (spec §2).
    assert info["comment"] == b"MW MIPS C Compiler (2.4.1.01)\x00"
    assert ".debug" in info["sections"] and ".line" in info["sections"]
    assert info["sections"][".debug"][0] == 0x70000005      # SHT_MIPS_DEBUG
    assert "sysInitScf" in info["text_symbols"]
```

```c
/* tests/toolchain/probe.c */
typedef struct { int date_notation; int language; } _tag_SYS_SCF_WORK;
_tag_SYS_SCF_WORK *pscf;
int sysGetDateNotation(void) { return pscf->date_notation; }
void sysInitScf(_tag_SYS_SCF_WORK *p) { pscf = p; p->date_notation = 0; }
```

- [ ] **Step 2: Run test to verify it fails** — FAIL (module missing).

- [ ] **Step 3: Implement `probe.py`**

Run `wibo <compiler_dir>/mwccps2.exe <flags> -o <obj> <src>` with `cwd=compiler_dir` (the FLEXlm licence lookup is directory-relative), capture stderr, and parse the object's sections and `.comment` with a small reader that shares `elf.py` from the oracle. If the compiler exits non-zero with a licence error, raise `NothingToBuild` naming the FLEXlm fallback.

- [ ] **Step 4: Run and verify**

```bash
python3 -m pytest tests/toolchain/test_probe.py -v
```

Expected: PASS. If it fails with a licence error, record that in `toolchain/PROVENANCE.txt` and switch to the community-patched binary from the Internet Archive item `metrowerks-ps2-compiler`; the plan's remaining tasks are unaffected.

- [ ] **Step 5: Commit**

```bash
git add tools/toolchain/probe.py tests/toolchain/probe.c tests/toolchain/test_probe.py
git commit -m "toolchain: prove mwccps2 runs under wibo and emits DWARF 1"
```

---

### Task 7: Host dependencies

**Files:**
- Create: `tools/toolchain/check_deps.py`, `tests/toolchain/test_check_deps.py`
- Create (generated, gitignored): `toolchain/PROVENANCE.txt`

**Interfaces:**
- Produces: `check_deps.require() -> dict` with keys `as`, `ld`, `objcopy`, `ninja`, `splat`, `objdiff` and their versions; raises `MissingDependency` naming the exact `brew install`/`pip install` command.

- [ ] **Step 1: Write the failing test**

```python
# tests/toolchain/test_check_deps.py
import pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import check_deps

def test_required_tools_are_present_and_usable():
    v = check_deps.require()
    assert v["as"].startswith("GNU assembler")
    assert v["splat"]
    assert check_deps.assembles_r5900()          # as accepts -march=5900 -EL
```

- [ ] **Step 2: Run test to verify it fails** — FAIL (module missing).

- [ ] **Step 3: Implement `check_deps.py`** with the exact remedies:

```
brew install mips-linux-gnu-binutils
python3 -m pip install --user 'splat64[mips]' pytest
# objdiff: fetch the darwin/arm64 asset from https://github.com/encounter/objdiff/releases
#          (verify `objdiff-cli --version`), else `cargo install objdiff-cli`
```

`assembles_r5900()` writes a three-word `.s` with `lui/addiu/jr $ra`, runs `mips-linux-gnu-as -EL -march=5900 -mabi=eabi` into a temp object, and returns True only if the object appears.

- [ ] **Step 4: Run the install commands, then the test**

```bash
brew install mips-linux-gnu-binutils
python3 -m pip install --user splat64 pytest
python3 -m pytest tests/toolchain/test_check_deps.py -v
```

Expected: PASS, and `toolchain/PROVENANCE.txt` records each tool's version.

- [ ] **Step 5: Commit**

```bash
git add tools/toolchain/check_deps.py tests/toolchain/test_check_deps.py
git commit -m "toolchain: verify host assembler, linker, ninja, splat and objdiff"
```

---

### Task 8: Splat config and configure.py

**Files:**
- Create: `config/usam2/splat.yaml`, `configure.py`, `inline_asm.h`, `tests/test_configure.py`
- Create (generated): `asm/**`, `build.ninja`, `config/usam2/undefined_{funcs,syms}_auto.txt`

**Interfaces:**
- Consumes: `config/usam2/symbol_addrs.txt`, `cus.json`, `debug_chunks.json`.
- Produces: `asm/nonmatchings/<seg>/<symbol>.s` per function; `inline_asm.h` providing `INCLUDE_ASM(folder, name)` → `.include` of the split, and a no-op under `SKIP_ASM`; `configure.main(["--config", "usam2", "--objects"]) -> int`.

- [ ] **Step 1: Write the failing test**

```python
# tests/test_configure.py
import pathlib, subprocess, sys
ROOT = pathlib.Path(__file__).resolve().parents[1]

def test_splat_splits_every_symbol():
    subprocess.run([sys.executable, "configure.py", "--config", "usam2"], cwd=ROOT, check=True)
    splits = list((ROOT / "asm").rglob("*.s"))
    assert len(splits) >= 3161
    assert (ROOT / "build.ninja").exists()

def test_debug_chunks_are_carried_as_data():
    yaml = (ROOT / "config/usam2/splat.yaml").read_text()
    assert "databin" in yaml and ".debug" in yaml and ".line" in yaml

def test_config_without_cus_json_fails_loudly(tmp_path):
    p = subprocess.run([sys.executable, "configure.py", "--config", "usam2",
                        "--cus", str(tmp_path / "missing.json")],
                       cwd=ROOT, capture_output=True, text=True)
    assert p.returncode != 0 and "cus.json" in p.stderr
```

- [ ] **Step 2: Run test to verify it fails** — `python3 -m pytest tests/test_configure.py -v` → FAIL (`configure.py` missing).

- [ ] **Step 3: Write `config/usam2/splat.yaml`**

```yaml
options:
  basename: SLUS_207.11
  target_path: orig/SLUS_207.11
  platform: ps2
  compiler: EEGCC
  asm_path: asm
  src_path: src
  build_path: build
  ld_rom_start: 0
  section_order: [".text", ".rodata", ".data", ".bss"]
  auto_link_sections: [".rodata", ".data", ".bss"]
  subalign: 1                     # measured: 8 cannot place the 22 starts at VA % 8 == 4 (R26)
  create_undefined_funcs_auto: true
  undefined_funcs_auto_path: config/usam2/undefined_funcs_auto.txt
  create_undefined_syms_auto: true
  undefined_syms_auto_path: config/usam2/undefined_syms_auto.txt
  symbol_addrs_path: config/usam2/symbol_addrs.txt
segments:
  - [0x0, databin, elf_header]                 # ELF header + program headers + padding
  - name: main
    type: code
    start: 0x80
    vram: 0x100000
    subsegments:
      - [0x80, asm, main]                      # per-function splits come from symbol_addrs
      - [0x1a2700, databin, shstrtab]
      - [0x1a2740, databin, debug]             # refined per TU by debug_chunks.json
      - [0x2430e0, databin, line]
      - [0x265680, databin, comment]
      - [0x2656ac, databin, reginfo]
```

`configure.py` loads `cus.json`/`debug_chunks.json` (exiting non-zero with the file name in stderr when absent), refines the `debug`/`line` subsegments into one `databin` per chunk, runs `python3 -m splat split config/usam2/splat.yaml` as a subprocess, then writes `build.ninja` with the rules below, mirroring sly1:

```python
ninja.rule("as", command="cpp -Iinclude $in -o - | mips-linux-gnu-as -EL -march=5900 -mabi=eabi -o $out")
# NOTE (measured in Task 7): register naming is ABI-dependent. With -mabi=eabi, $t0..$t3 are r12..r15 and
# $t4..$t7 are unknown, so a split written with o32 names would encode the wrong registers. Assemble one
# split and require its bytes to equal the retail bytes for that function; if they differ, fix the ABI flag
# or the disassembler's register naming — never hand-edit a split.
ninja.rule("cc", command="python3 tools/toolchain/compile.py $in $out $flags")
ninja.rule("ld", command="mips-linux-gnu-ld -EL -T config/usam2/undefined_syms_auto.txt "
                         "-T config/usam2/undefined_funcs_auto.txt -Map $mapfile -T $in -o $out")
ninja.rule("bin", command="mips-linux-gnu-objcopy $in $out -O binary")   # loadable half only; the tail is appended (R29)
ninja.rule("g1", command="python3 tools/verify/g1.py $in")
```

- [ ] **Step 4: Write `inline_asm.h`**

```c
#pragma once
#ifdef SKIP_ASM
#define INCLUDE_ASM(folder, name)
#define INCLUDE_DATA(folder, name)
#else
#define INCLUDE_ASM(folder, name) __asm__( \
    ".section .text\n.set noat\n.set noreorder\n" \
    ".include \"asm/nonmatchings/" folder "/" #name ".s\"\n")
#define INCLUDE_DATA(folder, name) __asm__( \
    ".include \"asm/nonmatchings/" folder "/" #name ".s\"\n")
#endif
```

- [ ] **Step 5: Run splat and verify**

```bash
python3 configure.py --config usam2
ls asm/nonmatchings/main | wc -l
python3 -m pytest tests/test_configure.py -v
```

Expected: ≥3,161 splits, `build.ninja` written, 3 passed.

- [ ] **Step 6: Commit**

```bash
git add configure.py config/usam2/splat.yaml inline_asm.h tests/test_configure.py
git commit -m "build: splat config and ninja generation for the all-asm skeleton"
```

---

### Task 9: Pinned link to a byte-identical ELF (M1 gate)

**Files:**
- Create: `tools/verify/g1.py`, `tools/verify/__init__.py`, `tests/verify/test_g1.py`, `config/usam2/checksums.txt`
- Modify: `configure.py` (final link + `objcopy` + gate wiring)

**Interfaces:**
- Consumes: `build.ninja`, `asm/**`.
- Produces: `out/SLUS_207.11`; `g1.compare(built, retail) -> str` returning `"ok"` or `"sha256 mismatch: expected … got … at first difference 0x…"`.

- [ ] **Step 1: Write the failing test**

```python
# tests/verify/test_g1.py
import pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from verify import g1

RETAIL = ROOT / "orig/SLUS_207.11"
SHA = "a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc"

def test_retail_hash_is_pinned():
    assert g1.sha256(RETAIL) == SHA

def test_truncated_copy_is_rejected(tmp_path):
    bad = tmp_path / "SLUS_207.11"
    bad.write_bytes(RETAIL.read_bytes()[:1000])
    msg = g1.compare(bad, RETAIL)
    assert msg.startswith("sha256 mismatch") and "0x" in msg
```

- [ ] **Step 2: Run test to verify it fails** — FAIL (module missing).

- [ ] **Step 3: Implement `g1.py`**

Compute both hashes; on mismatch, report the first differing byte offset and, using `cus.json`, the owning CU, its TU and its function — this is the localisation that makes G2 a diagnostic rather than a separate gate.

- [ ] **Step 4: Add the final link rules and run the build**

```bash
python3 configure.py --config usam2
ninja -C . out/SLUS_207.11
```

Expected: `out/SLUS_207.11` is produced, and its sha256 equals `a7596e8a…5218aa8cc` — the milestone M1 gate, with zero C written.

- [ ] **Step 5: Write the checksum file from the verified run**

```bash
# the manifest holds two records; Task 11 appends the retail image's pin (do not overwrite)
printf '%s  out/SLUS_207.11\n' "$(shasum -a 256 out/SLUS_207.11 | cut -d' ' -f1)" > config/usam2/checksums.txt
printf '%s  disc/DDRMAX2 Dance Dance Revolution (USA).iso\n' \
  b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8 >> config/usam2/checksums.txt
```

- [ ] **Step 6: Commit**

```bash
git add tools/verify/g1.py tests/verify config/usam2/checksums.txt configure.py
git commit -m "build: pinned link reproduces the retail ELF byte for byte (M1)"
```

---

### Task 10: Rebuild the disc image (M1 gate, second half)

**Files:**
- Create: `tools/iso/reinsert.py`, `tests/iso/test_reinsert.py`, `tests/iso/__init__.py`

**Interfaces:**
- Consumes: `out/SLUS_207.11`, the retail image path from `--iso`.
- Produces: `reinsert.build(image_path, elf_path, out_path, offset=0x92000) -> None`; `reinsert.verify(out_path, expected_sha256) -> str`.

- [ ] **Step 1: Write the failing test**

```python
# tests/iso/test_reinsert.py
import hashlib, pathlib, sys, pytest
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from iso import reinsert

IMAGE = pathlib.Path("/Volumes/My Passport/PS2 Games/DDRMAX2 Dance Dance Revolution (USA).iso")
SHA = "b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8"

def test_elf_lands_at_the_right_offset():
    if not IMAGE.exists():
        pytest.skip("retail image not available")
    head = reinsert.read(IMAGE, 0x92000, 8)
    assert head[:4] == b"\x7fELF"

def test_reinsertion_reproduces_the_image(tmp_path):
    if not IMAGE.exists():
        pytest.skip("retail image not available")
    out = tmp_path / "rebuilt.iso"
    reinsert.build(IMAGE, ROOT / "out/SLUS_207.11", out)
    assert hashlib.sha256(out.read_bytes()).hexdigest() == SHA
```

- [ ] **Step 2: Run test to verify it fails** — FAIL (module missing).

- [ ] **Step 3: Implement `reinsert.py`** by seeking to `offset` in a copy of the image and writing the built ELF, leaving every other byte untouched; `verify` compares sha256 and reports the first differing offset when it fails.

- [ ] **Step 4: Run and verify**

```bash
python3 -m pytest tests/iso -v
```

Expected: PASS, or `skipped` when the image is absent — the milestone evidence comes from the run where it is present, recorded in `docs/milestones/`.

- [ ] **Step 5: Commit**

```bash
git add tools/iso tests/iso
git commit -m "iso: reinsert the built ELF and verify the rebuilt image hash"
```

---

### Task 11: The `ddr` CLI

**Files:**
- Create: `ddr`, `tests/test_cli.py`, `tools/verify/g2.py`

**Interfaces:**
- Consumes: everything above.
- Produces: `./ddr oracle` (regenerate symbol/CU/chunk/header artifacts), `./ddr build`, `./ddr verify [--tu NAME]` (G1, then G3 when `--iso` is given, localising a failure to TU/function via `g2.localise`), `./ddr diff <symbol> <tu>` (objdiff), `./ddr iso --iso PATH`.

- [ ] **Step 1: Write the failing test**

```python
# tests/test_cli.py
import pathlib, subprocess, sys
ROOT = pathlib.Path(__file__).resolve().parents[1]

def run(*args):
    return subprocess.run([str(ROOT / "ddr"), *args], cwd=ROOT, capture_output=True, text=True)

def test_verify_reports_ok_when_built_matches():
    assert run("build").returncode == 0
    p = run("verify")
    assert p.returncode == 0 and "G1 ok" in p.stdout

def test_verify_names_the_offending_tu(tmp_path):
    bad = ROOT / "out/SLUS_207.11"
    saved = bad.read_bytes()
    try:
        # VA 0x21C424 is inside .text, which starts at file offset 0x80 for VA 0x100000
        off = 0x80 + (0x21C424 - 0x100000)
        b = bytearray(saved); b[off] ^= 0xFF; bad.write_bytes(bytes(b))
        p = run("verify")
        assert p.returncode != 0
        assert "sys_scf.c" in p.stdout and "sysInitScf" in p.stdout
    finally:
        bad.write_bytes(saved)
```

- [ ] **Step 2: Run test to verify it fails** — FAIL (`ddr` missing).

- [ ] **Step 3: Implement `ddr` and `g2.py`**

`g2.localise(built, retail, cus_json, chunks_json) -> {section, offset, cu, tu, function}` maps the first differing offset through the chunk manifest; the CLI prints `G1 FAIL: first difference at 0x<off> in .text → sys_scf.c / sysInitScf (CU 0x19f)`. This is Review Focus 1.

- [ ] **Step 4: Run the tests and verify both directions**

```bash
python3 -m pytest tests/test_cli.py -v
```

Expected: both tests pass — green when identical, and a named TU when a single byte is flipped.

- [ ] **Step 5: Commit**

```bash
git add ddr tools/verify/g2.py tests/test_cli.py
git commit -m "cli: ddr build/verify/oracle/diff with per-TU failure localisation"
```

---

### Task 12: First promoted translation unit (`sys_scf.c`)

**Files:**
- Create: `src/sys/sys_scf.c`, `tools/toolchain/select_build.py`, `tests/test_m2_sys_scf.py`, `docs/milestones/m2-sys-scf.md`
- Modify: `configure.py` (per-TU rule choice: C when `src/<tu>.c` exists, else the split)

**Interfaces:**
- Consumes: `include/sys/sys_scf.h`, the compiler candidates, `ddr diff`.
- Produces: `select_build.choose(tu_bounds, retail_bytes, candidates) -> (version, flags)` returning the first candidate+flag set whose object reproduces the retail bytes for that TU.

- [ ] **Step 1: Write the failing test**

```python
# tests/test_m2_sys_scf.py
import pathlib, subprocess, sys
ROOT = pathlib.Path(__file__).resolve().parents[1]

def test_sys_scf_is_compiled_not_assembled():
    assert (ROOT / "src/sys/sys_scf.c").exists()
    src = (ROOT / "src/sys/sys_scf.c").read_text()
    assert "INCLUDE_ASM" not in src

def test_promoted_tu_keeps_the_binary_identical():
    subprocess.run([str(ROOT / "ddr"), "build"], cwd=ROOT, check=True)
    p = subprocess.run([str(ROOT / "ddr"), "verify"], cwd=ROOT, capture_output=True, text=True)
    assert p.returncode == 0 and "G1 ok" in p.stdout

def test_sys_scf_debug_chunk_matches_retail():
    p = subprocess.run([str(ROOT / "ddr"), "verify", "--tu", "sys_scf.c"],
                       cwd=ROOT, capture_output=True, text=True)
    assert p.returncode == 0 and "debug chunk ok" in p.stdout
```

- [ ] **Step 2: Run test to verify it fails**

Run: `python3 -m pytest tests/test_m2_sys_scf.py -v`
Expected: FAIL — `src/sys/sys_scf.c` missing.

- [ ] **Step 3: Write the source from the oracle's evidence**

> **Linker constraint (measured, plan ruling R23):** mainline GNU binutils cannot read `mwccps2` objects
> (`objcopy`: "Unable to recognise the architecture"; `ld`: "relocations in generic ELF"). The C-side link
> therefore uses `mwldps2 -m <entry>` or the `decompals/binutils-mips-ps2-decompals` fork; if MWLD drops
> `.debug`/`.line`, splice the object's sections under the pinned layout applying `.rel.debug`/`.rel.line`.
> The skeleton (Tasks 8–9) is unaffected: its inputs are GNU-assembled splits plus data blobs.

```c
/* src/sys/sys_scf.c — reconstructed from DWARF 1: lines 1-42 of the original file */
#include "sys/sys_scf.h"          /* generated: _tag_SYS_SCF_WORK, pscf, prototypes */

_tag_SYS_SCF_WORK *pscf;

int sysGetDateNotation(void) {
    return pscf->date_notation;                    /* retail line 41-42 */
}

void sysInitScf(_tag_SYS_SCF_WORK *p) {            /* retail lines 24-34 */
    pscf = p;
    p->date_notation = 0;
    /* statements must land on the retail line numbers: 24, 29, 32, 34 */
}
```

The generated header supplies `_tag_SYS_SCF_WORK` (`int date_notation;` at 0x0, `int language;` at 0x4), `pscf` and the prototypes with their line ranges; the body comes from the disassembly at `0x21c420`-`0x21c450`.

- [ ] **Step 4: Select the compiler build and flags**

```bash
python3 tools/toolchain/select_build.py --tu sys_scf.c
```

Expected: prints the first `(version, flags)` pair whose object reproduces the retail bytes for `0x21c420-0x21c450`; record the pair in `docs/milestones/m2-sys-scf.md`. Candidate flags to try in order: `-O2`, `-O1`, `-O3`, `-O4` × `-lang c` × `-g`, with `-sdatathreshold 0` as an extra axis.

- [ ] **Step 5: Iterate until the gates are green**

```bash
./ddr diff sysInitScf sys_scf        # objdiff until the instruction streams agree
ninja
./ddr verify --tu sys_scf.c
```

Expected: `G1 ok`, and `debug chunk ok` for `sys_scf.c` — the promotion rule of the spec, satisfied for the first time.

- [ ] **Step 6: Commit**

```bash
git add src/sys/sys_scf.c tools/toolchain/select_build.py tests/test_m2_sys_scf.py docs/milestones/m2-sys-scf.md
git commit -m "m2: promote sys_scf.c, code and debug chunk both matching retail"
```

---

### Task 13: Operating contract and CI

**Files:**
- Create: `AGENTS.md`, `.github/workflows/build.yml`, `.github/workflows/objects.yml`, `.github/workflows/progress.yml`, `docs/milestones/m1-skeleton.md`, `README.md`

**Interfaces:**
- Consumes: `ddr`, `configure.py`.
- Produces: the written contract new contributors and agents follow.

- [ ] **Step 1: Write `AGENTS.md`** stating: use `./ddr` for routine work; `./ddr build` then `./ddr verify` after every change; never hand-edit `asm/`, `config/usam2/cus.json`, `debug_chunks.json`, `symbol_addrs.txt` (regenerate with `./ddr oracle`); names are never invented; statements keep retail line numbers; retail binaries and toolchains never enter the repo; a TU is promoted only when its code and its debug chunk both match.

- [ ] **Step 2: Write the three workflows**

```yaml
# .github/workflows/build.yml
name: build
on: [push, pull_request]
jobs:
  skeleton:
    runs-on: macos-14
    steps:
      - uses: actions/checkout@v4
      - run: python3 -m pip install --user splat64 pytest
      - run: brew install mips-linux-gnu-binutils ninja
      - run: python3 tools/toolchain/fetch.py 2.4-001213
      - run: python3 configure.py --config usam2 && ninja
      - run: ./ddr verify            # skips G3 when the retail image is absent
```

`objects.yml` runs `configure.py --objects` and uploads the objdiff artefacts; `progress.yml` runs `objdiff-cli report generate` and uploads to decmp.dev. All three require the retail ELF, so they document that it must be supplied out of band (the repo never contains it).

- [ ] **Step 3: Record the milestone evidence**

Write `docs/milestones/m1-skeleton.md` with the observed hashes (`out/SLUS_207.11`, the rebuilt image), the tool versions from `toolchain/PROVENANCE.txt`, and the exact commands run — and `README.md` linking spec, plan and milestones.

- [ ] **Step 4: Run everything one last time**

```bash
./ddr oracle && python3 configure.py --config usam2 && ninja && ./ddr verify --iso "/Volumes/My Passport/PS2 Games/DDRMAX2 Dance Dance Revolution (USA).iso"
python3 -m pytest -q
```

Expected: `G1 ok`, `G3 ok`, full suite passing.

- [ ] **Step 5: Commit**

```bash
git add AGENTS.md .github docs/milestones README.md
git commit -m "docs: operating contract, CI and milestone evidence"
```

---

## Self-Review Notes

- **Spec coverage:** G1 (Task 9), G3 (Task 10), G2 localisation (Task 11), oracle and its four-way validation (Tasks 1–4), toolchain and its empirical build selection (Tasks 5–7, 12), splitting/pinned link (Tasks 8–9), ISO layer (Task 10), workflow and contract (Tasks 11–13). Deferred to their own plans, per the spec's milestones: M3 (loop at scale), M4 (library naming and SDK identification), M5 (100%). The overlay and sibling-build material in the spec is deliberately not a task here — it belongs to the ladder plan.
- **Open items carried into execution:** the per-TU layout skew in `_tag_cDDR7SaveData` (Task 3 emits per-TU headers, which is the shape that survives if the skew is real), compiler build selection (Task 12 owns it), `.line` strictness (Task 11 makes any drift nameable, Task 12 proves the first case).
