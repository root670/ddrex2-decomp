# M3 — the promotion loop at scale: Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the C path usable for a normal translation unit — headers that compile as C and are centralized, a per-function diff that measures the function you are actually editing, a compiler/flag sample wider than two functions — then promote a calibrated batch of TUs and identify which library archives the game linked.

**Architecture:** M1 and M2 are done: the build reproduces the retail ELF and disc image byte-for-byte, and one TU (`sys_scf.c`) is promoted with its code *and* debug bytes matching. M3 removes the three things that block doing that a hundred times, then does it: headers become C-mode and shared (`include/types/`), `ddr diff` gets a basis built from retail bytes for the specific functions under work, the compiler pair stops resting on a two-function sample, and the library region's SDK release gets identified by byte-matching (which is what makes it "pinned objects" rather than "3,180 unknown functions").

**Tech Stack:** the existing pipeline — `tools/oracle/*` (vendored CodeWarrior DWARF 1 reader + emitters), `configure.py` + ninja + splat, `mwccps2` under wibo, `tools/verify/{g1,g2}.py`, `tools/iso/reinsert.py`, `ddr`, pytest.

**Spec:** `docs/superpowers/specs/2026-10-14-ddrmax2-us-decomp-design.md` (binding authority). Carry-forward input: `docs/milestones/m3-carry-forward.md`.

## Global Constraints

- Gates stay absolute and pinned: G1 `out/SLUS_207.11` sha256 `a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc`; G3 the retail image `b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8`; both check their reference against `config/usam2/checksums.txt` before comparing.
- Promotion rule: a TU counts as promoted only when its `.text` **and** its `.debug`/`.line` bytes match retail (`./ddr verify --tu <name>`).
- Names come from evidence. DWARF gives 423 functions across 57 TUs, 1,586 locals, 577 parameters, 123 named aggregates (member names and offsets), 639 globals/statics — with one measured exception: `@anon0..24` are per-TU numbering, so the same synthetic name means different types in different TUs (21 of 123 names differ by layout, all of them anonymous). Nothing is invented without recorded provenance.
- Statements land on the retail line numbers the oracle reports (`tools/oracle/dwarf1.py lines <VA> --table`).
- **Borrow before reversing.** For the library region, exhaust the public decomp corpora first — names, sizes, and any published C or assembly from `recvx-decomp`, `god-hand-decomp` and whatever else publishes PS2 symbol tables or SDK analysis — because that analysis has likely already been done, once, by someone. Reverse a library function ourselves only after recording which corpora were checked and why none of them explains it.
- **Renaming must not move a gate.** Borrowed names enter the ledger (`config/usam2/symbol_addrs.txt`) and the generated artifacts; if a rename moves G1, the names stay out of the linked image and live in a side ledger instead. Measure it with `./ddr verify`; do not assume either way.
- Compiler pair: `mwccps2` build `3.0-011126 -c -lang c -O3 -g` — measured, and treated as *provisional until Task 3 widens the sample*.
- Never hand-edit `asm/**`, the generated `config/usam2/splat.yaml`, `cus.json`, `debug_chunks.json`, or the generated headers; regenerate with `./ddr oracle`.
- Retail binaries, disc images and toolchains are never committed; `orig/`, `disc/`, `build/`, `out/`, `asm/`, `toolchain/` stay gitignored. Tool code is Python 3 standard library only; tests via `python3 -m pytest` (~6 minutes, one run per task).

## Review Focus

1. A generated header that does not compile as **C** (`mwccps2 -lang c`), or a header whose type spellings cannot be reused — the loop's first requirement (Task 1).
2. A named type defined in more than one header, or a per-TU anonymous type promoted to a shared one, silently changing which layout a TU compiles against (Task 1).
3. `ddr diff` reporting a number objdiff never computed — its earlier failure mode — instead of a real comparison for the function under edit (Task 2).
4. A `TU_BUILDS` entry baked in from a two-function sample that a wider run would overturn, with no record of which TUs were measured (Task 3).
5. A library function reversed from scratch without the corpora having been checked first — borrow-before-reversing is a constraint, not a preference (Task 5).
6. A library archive matched on *name* or *size* alone, presented as identified (Task 5).

---

### Task 1: C-mode, centralized type headers

**Files:**
- Modify: `tools/oracle/emit_headers.py` (rendering + layout)
- Modify: `tests/oracle/test_emit_headers.py`
- Regenerate (committed): `include/**`, and new `include/types/*.h` + `include/types.h`
- Modify: `AGENTS.md` (the header convention), `tools/oracle/README.md`

**Interfaces:**
- Consumes: `Dwarf` from `tools/oracle/dwarf1.py`; the retail bytes for verification.
- Produces: `emit_headers.render_types(dwarf) -> dict[str, str]` (canonical named types), `emit_headers.render(elf_path, cu_substring) -> str` (unchanged signature, now C-mode and including the canonical types), `emit_headers.write_all(elf_path, out_dir) -> list[Path]` writing `include/types/<tag>.h`, `include/types.h` and one header per TU.

- [ ] **Step 1: Write the failing tests**

```python
# tests/oracle/test_emit_headers.py (additions)
import pathlib, subprocess, sys, collections, re
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_headers

def test_uses_are_c_not_cpp():
    text = emit_headers.render(ROOT / "orig/SLUS_207.11", "sys_scf.c")
    assert "struct _tag_SYS_SCF_WORK *pscf;" in text            # C spelling
    assert re.search(r"^_tag_SYS_SCF_WORK \*pscf;", text, re.M) is None

def test_every_header_compiles_as_c(tmp_path):
    for h in sorted((ROOT / "include").rglob("*.h")):
        tu = tmp_path / "probe.c"
        tu.write_text(f'#include "{h.relative_to(ROOT / "include")}"\nint main(void) {{ return 0; }}\n')
        r = subprocess.run([sys.executable, str(ROOT / "tools/toolchain/compile.py"),
                            "--syntax-only", "--include", str(ROOT / "include"), str(tu)],
                           capture_output=True, text=True)
        assert r.returncode == 0, f"{h}: {r.stderr[:400]}"

def test_named_types_are_defined_once():
    defs = collections.defaultdict(set)
    for h in (ROOT / "include").rglob("*.h"):
        for m in re.finditer(r"^(?:struct|union)\s+(\w+)\s*\{", h.read_text(), re.M):
            defs[m.group(1)].add(h.relative_to(ROOT / "include"))
    shared = {k: v for k, v in defs.items() if not k.startswith("anon") and len(v) > 1}
    assert shared == {}, f"named types defined in more than one header: {shared}"

def test_anonymous_types_stay_per_tu():
    a = emit_headers.render(ROOT / "orig/SLUS_207.11", "les.c")
    assert "anon" in a            # the per-TU synthetic tag is local to this header
```

- [ ] **Step 2: Run to verify they fail**

Run: `python3 -m pytest tests/oracle/test_emit_headers.py -v`
Expected: FAIL — `struct _tag_SYS_SCF_WORK *pscf;` is absent (the header emits the bare tag), and the compile probe has no `--syntax-only` mode yet.

- [ ] **Step 3: Add the C-mode compile seam**

`tools/toolchain/compile.py` gains `--syntax-only` plus `--include DIR`: it compiles the given file with `-c -lang c -O3 -g` under wibo and returns the compiler's exit status without producing an object, so a header can be checked by the *original compiler* rather than a host C compiler.

- [ ] **Step 4: Render C-mode types and centralize them**

- Uses become `struct <tag> *` / `union <tag> *` (typedefs do not exist in DWARF 1, so nothing is lost).
- Anonymous types get a per-TU synthetic tag derived from the `@anonN` name (`anon_<N>_<tu-index>`), emitted **only** in that TU's header, with a provenance comment; they are never centralized because the same synthetic name means different types in different TUs.
- Named types move to `include/types/<tag>.h` (definition + provenance: the offsets, the DIE offset, the TUs that declare it, and the layout signature); `include/types.h` includes them all; a per-TU header emits only `#include` lines, its globals, and its prototypes (with the retail line ranges kept as comments).
- Emit a canonical layout per named type. If two TUs disagree on a named type's layout, fail loudly naming the type and the differing members rather than picking one — the measurement says they agree today, so a disagreement is news.

- [ ] **Step 5: Regenerate and verify**

```bash
./ddr oracle
python3 -m pytest tests/oracle -q
./ddr build && ./ddr verify            # G1 must stay green: headers cannot change emitted bytes
./ddr verify --tu sys_scf.c
```

Expected: 57 per-TU headers + `include/types/*.h` + `include/types.h`; `G1 ok`; all three `sys_scf.c` verdicts ok; the named-type set still 123 with each defined once.

- [ ] **Step 6: Commit**

```bash
git add tools/oracle/emit_headers.py tools/toolchain/compile.py tests/oracle include AGENTS.md
git commit -m "oracle: emit C-mode headers and centralize named types"
```

---

### Task 2: A `ddr diff` basis for the functions under edit

**Files:**
- Modify: `tools/verify/g2.py` (target-object construction), `ddr` (`diff` verb)
- Modify: `tools/toolchain/compile.py` (per-function object extraction, if not already exposed)
- Create: `tests/verify/test_g2_target_object.py`, extend `tests/test_cli.py`
- Modify: `configure.py` (emit the target object as a ninja edge so `diff` never builds implicitly)

**Interfaces:**
- Consumes: `config/usam2/symbol_addrs.txt`, `cus.json`, the retail ELF.
- Produces: `g2.target_object(symbol) -> pathlib.Path`, a relocatable object whose `.text` is the retail bytes for that function (and only those bytes) under the symbol's own name, with the `.NON_MATCHING` alias removed so objdiff pairs the two sides.

- [ ] **Step 1: Write the failing tests**

```python
# tests/verify/test_g2_target_object.py
import pathlib, subprocess, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from verify import g2

def test_target_object_holds_retail_bytes_for_one_function():
    obj = g2.target_object("sysInitScf")
    text = g2.section_bytes(obj, ".text")
    retail = (ROOT / "orig/SLUS_207.11").read_bytes()[0x80 + (0x0021C420 - 0x100000):]
    assert text == retail[:len(text)] == retail[:0x30]

def test_diff_for_an_unpromoted_function_measures_something():
    r = subprocess.run([str(ROOT / "ddr"), "diff", "draw_cur", "les_sel_lv"],
                       cwd=ROOT, capture_output=True, text=True)
    assert r.returncode in (0, 1)          # a real verdict, not a refusal
    assert "match_percent" in r.stdout
    assert "unpromoted" not in r.stderr.lower()
```

- [ ] **Step 2: Run to verify they fail** — `python3 -m pytest tests/verify/test_g2_target_object.py -v` → FAIL (`g2.target_object` absent; `ddr diff` still exits 2 for an unpromoted unit).

- [ ] **Step 3: Build the target object from retail bytes**

For a requested symbol: take its address and size from the oracle's symbol file, copy the bytes from `orig/SLUS_207.11`, and emit a minimal MIPS relocatable object (`.text` with those bytes under the symbol's name, `.reginfo`/`.mips.abiflags` as GNU `as` produces them) at `build/target/<symbol>.o`. Assembly path: a generated `.s` with `.word` lines plus a `glabel`-style symbol, assembled by the existing `as` rule — no new toolchain.

- [ ] **Step 4: Wire the verb**

- `ddr diff <symbol> <tu>`: target = `g2.target_object(symbol)`; base = the promoted object when the TU has C, else the split object — and for an unpromoted TU the verdict now reads as a comparison of retail bytes against the split, which *is* the honest number.
- Drop the exit-2 refusal for unpromoted units; keep `--base` as the override.
- Print one line naming what was compared (`target: retail bytes for <symbol>; base: <path>`), so no score can be misread.

- [ ] **Step 5: Verify both directions**

```bash
./ddr diff sysInitScf sys_scf     # promoted: expect a high match with a resolved call graph
./ddr diff draw_cur les_sel_lv    # unpromoted: expect a real score, not 0.0% with an empty diff
ninja -n | head                    # the target object is a graph edge, so nothing builds implicitly
python3 -m pytest tests/test_cli.py tests/verify -q
```

- [ ] **Step 6: Commit** — `git commit -m "verify: diff the retail bytes for the function under edit (M3)"`

---

### Task 3: Widen the compiler and flag sample

**Files:**
- Modify: `tools/toolchain/select_build.py` (batch mode), `configure.py` (`TU_BUILDS`)
- Create: `docs/milestones/m3-compiler-sample.md`
- Modify: `tests/toolchain/test_select_build.py` (or create it)

**Interfaces:**
- Produces: `select_build.sample(tu_names) -> list[dict]` returning per-TU `{tu, version, flags, parts: {text, debug, line}}`; a `--sample N` flag that picks the N smallest unpromoted TUs from the oracle's records.

- [ ] **Step 1: Write the failing test** — a batch run over three named TUs returns one verdict per TU, each with all three parts, and a TU no candidate matches is reported as unmatched rather than silently skipped.
- [ ] **Step 2: Run to verify it fails.**
- [ ] **Step 3: Implement batch mode** — iterate candidates × flag axes over the N smallest unpromoted TUs by DWARF size; write `docs/milestones/m3-compiler-sample.md` with the table (per TU: which builds and flag sets matched all three parts) and the resulting `TU_BUILDS` entries.
- [ ] **Step 4: Run over a dozen TUs**

```bash
python3 tools/toolchain/select_build.py --sample 12
# expect: a per-TU verdict; if more than one (version, flags) pair survives across all twelve,
# record the tie and prefer the lowest build that also writes the retail `.comment` ident
```

- [ ] **Step 5: Commit** — `git commit -m "toolchain: pin the compiler and flags by a twelve-TU sample (M3)"`

---

### Task 4: Promote the first calibrated batch of TUs

**Files:**
- Create: `src/<tu>.c` for each promoted TU, `docs/milestones/m3-batch-one.md`
- Modify: `tests/test_m3_batch.py` (per-TU gates), `configure.py` only if a rule needs it

**Interfaces:** consumes everything above; produces promoted TUs whose `./ddr verify --tu <name>` is green.

- [ ] **Step 1: Pick the batch** — the smallest unpromoted TUs by total DWARF function size, from `config/usam2/cus.json`; expect the data-only and one-function units first (`kn_lmsg.c`, `cmes_e.c`, `sys_demo.c`, `music_all.c`, …).
- [ ] **Step 2: For each TU, work the loop** — read `tools/oracle/dwarf1.py fn/lines`, the split's disassembly, and the generated header; write the C with statements on the retail lines; `./ddr diff <symbol> <tu>`; `./ddr verify --tu <tu>`.
- [ ] **Step 3: Record throughput honestly** — in `docs/milestones/m3-batch-one.md`: per TU, its function count, byte count, wall-clock, how many iterations the diff needed, and anything the loop lacked.
- [ ] **Step 4: Gate and commit** — `./ddr build && ./ddr verify && python3 -m pytest -q`; one commit per TU (or one per small group), message `m3: promote <tu>`.

---

### Task 5: Borrow the corpora's work first, then identify the SDK release

**Files:**
- Create: `tools/sdk/borrow.py`, `tools/sdk/inventory.py`, `tools/sdk/match.py`, `tests/sdk/*`
- Create (committed): `config/usam2/library-names.md` — one row per borrowed name: the corpus, what it publishes (names only? names with sizes? C? assembly?), how it was validated against our bytes, and where the name landed in the library symbol ledger (`config/usam2/symbol_addrs.txt` for placed names, `unplaced_symbols.txt` for what stays unnamed)
- Create (committed): `config/usam2/sdk-candidates.md` — candidate releases, provenance, and the verdict per candidate
- Modify: `AGENTS.md` (library rule: borrowed names carry provenance, bytes stay pinned)

**Interfaces:**
- `borrow.corpora() -> list[dict]` — each public corpus with its licence, what it publishes, and its fetch/extract entry point.
- `borrow.validate(name, size, retail_bytes) -> dict` — how a borrowed name is *accepted*: its size must match ours, and where the corpus publishes byte-exact code or a digest, the bytes must match after relocation masking.
- `inventory.scan(root) -> list[dict]` — every `lib*.a`/`*.o` found under a mounted SDK or an extracted installer, with member names, sizes and digests.
- `match.compare(object_bytes, retail_bytes) -> dict` — normalised instruction comparison masking relocated immediates → `{identical, differing_words, first_difference}`.

- [ ] **Step 1: Write the failing tests** — `compare()` reports identity for retail bytes copied at their own address and the first differing word for the same bytes shifted by four; a size mismatch is reported as a mismatch, never as identity; `validate()` rejects a borrowed name whose size differs from ours.
- [ ] **Step 2: Run to verify they fail.**
- [ ] **Step 3: Catalogue and borrow from the public corpora** — the surveyed sources and their exact yields are in `docs/milestones/m3-library-sourcing.md`: recvx-decomp (~1,038 SDK functions **with sizes**, MIT), sly1 (names labelled by **original SDK source path**, CC0), god-hand-decomp (~6,917 names, no sizes, MIT, later SDK generation), ps2sdk (AFL-2.0 reimplementation → names and semantics only), the Ghidra pattern DB (138 signatures, 67 matched, Apache-2.0), mvc2-ps2-decomp (**no licence: copy nothing**; its value is a compiler/flag cross-check for Task 3). Record each source's licence, what it publishes and the extract command; import only names that validate (size matches our bounds; bytes match after relocation masking where published); record the yield per source in `library-names.md`. **This runs before any reversing of our own.**
- [ ] **Step 4: Get the SDK media into reach** — mount the drive holding `ps2sdk_july2005.iso`; extract the installers (this machine's `innoextract` is broken: `Symbol not found: …boost::program_options…`, and `7z` cannot list the InstallShield stubs — try `unshield`, or run the installer under wibo, or fall back to an archived release) and record which release produced which archives.
- [ ] **Step 5: Match candidates and record the verdict** — compare each candidate's archive members against the library region; a high byte-match rate identifies the era, a low one is evidence against it. Three tiers, strongest first (details and measurements in `docs/milestones/m3-library-sourcing.md`): (a) the **Oni 2 dev build** (`abc/oni2dev_ps2.iso` → unstripped ELF, 10,615 FUNC symbols with sizes; 8.8 % of our library functions already match it under relocation masking, 97 size-exact) — use it for names and for the byte-validated subset; (b) the **extracted SDK archives** in `~/sdk-extract/devkit152/ee/lib/` — align by size sequence and masked-opcode equality, remembering the linker preserves archive member order; (c) the published corpora from Step 3. If nothing matches for a function, say so plainly and leave it as split assembly.
- [ ] **Step 6: Reconsider only what is left** — for functions no corpus and no archive explains, decide with the user whether to reverse them or leave them as pinned bytes, and record the decision with its reason per function family.
- [ ] **Step 7: Commit** — `git commit -m "sdk: borrow the corpora's names first, then identify the library release (M3)"`

---

## Self-Review Notes

- **Spec coverage:** M3's spec line — "the loop at scale: workflow, docs, CI, progress reporting; N TUs promoted, all gates green per change" — is Tasks 1–4; the library workstream (spec's M4) is Task 5, kept in the same plan because the SDK question the user raised is what turns 3,180 unknown functions into pinned objects, and its first step (get the media into reach) is independent of promotion work.
- **Known-carry items deliberately left out of M3:** generating `.comment` from the compiler object (it stays a retail databin, so the `2.4-001213`-matches-the-ident-but-not-the-code inversion stays hypothetical), the MODE2/2352 and MODE2/2448 disc geometries (ladder work), and the public-corpus *source* question beyond names (customary: PS2SDK is a reimplementation and will not produce identical bytes).
