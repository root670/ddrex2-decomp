# Retarget to the DDR Extreme 2 (US) preview: Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Move the decompilation from DDRMAX2 (US) to the DDR Extreme 2 (US) preview template (`SLUS_211.74`), which ships Metrowerks DWARF 1 for 249 translation units and 2,676 functions — then reverse its **game code** to C, byte-exactly.

**Architecture:** The pipeline is already generic (`tools/oracle/*` parses any Metrowerks DWARF 1 ELF — it read this binary unchanged; `configure.py` + splat + ninja + `mwccps2` under wibo build it; `ddr` verifies it). What is *not* generic is the target binding: `SLUS_207.11` appears 19× in `configure.py` and 7× in `ddr`, and `usam2` is bound into the oracle emitters, the verifiers, the ISO tool and the tests (~26 touchpoints). This plan introduces one target descriptor, generates a second config from the new binary, re-proves the gates, and then works the game code.

**Spec:** `docs/superpowers/specs/2026-10-16-ddrex2-preview-retarget-design.md` (binding). Library survey and measurements: `docs/milestones/m3-library-sourcing.md`.

**Non-negotiable scope (user decisions):** the **game code** (DWARF-backed TUs) is what gets reversed to C. The **SDK/runtime library subset is identified, never reversed** — names with provenance, then pinned or left as split assembly. Overlay blobs (`DATA00–09.BIN`, 860 functions) and the DWARF-less engine are deferred behind the game TUs. **DDRMAX2 (US) is no longer a target** (user decision, 2026-10-16): its config, generated headers, promoted TU, gates and milestone records were removed, so the descriptor carries one registered target and there is no second-target regression coverage — what survives from that work is target-independent: the oracle, the build pipeline, the SDK archive corpus and the matching method in `tools/sdk/`, the corpora clones, and the SDK research recorded in `docs/milestones/m3-library-sourcing.md`.

## Target facts

| | value |
|---|---|
| template ELF | `SLUS_211.74`, 7,725,036 B → copy to `orig/SLUS_211.74` (gitignored) |
| G1 pin | sha256 `ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd` |
| disc image | *Dance Dance Revolution Extreme 2 (May 10, 2005 prototype)*, `<your copy>/PS2 - Dance Dance Revolution Extreme 2 PS2 Preview Code 6-22-05.iso` |
| G3 pin | sha256 `70a9056657665e978c7de9fc223cb753956902416418993176438316f6cd652b`, 1,838,940,160 B, plain 2048-byte ISO |
| layout | one `PT_LOAD` at `0x100000`, 1,958,272 B, plus zero-filled overlay reservations at `0x7f0000`, `0xe4d380`, `0x1884000` |
| DWARF | 118,116 DIEs, 2,925 CUs, 249 TUs, 2,676 functions (1,816 in the template, 799,900 B); `.debug` 4,789,110 B, `.line` 976,198 B |
| compiler ident | `MW MIPS C Compiler (2.4.1.01)` — same string family as the old target, which was nevertheless reproduced by build `3.0-011126` |
| library stamps | `libgraph/libdma/libipu/libkernl/libscf/libvu0/libcdvd 3000`, `libmc/libpad 3020`, `netcnfif 3020`, `libeyety 1300` |

## Global Constraints

- Gates pinned per target: G1 the rebuilt template ELF is byte-identical; G2 a promoted TU's `.text` **and** `.debug`/`.line` bytes match; G3 the rebuilt disc image is byte-identical. Each checks its pin in its own config.
- **Library code is never reversed to C.** Names only, with provenance; then pin or leave as split assembly.
- Statements land on the retail line numbers the DWARF reports (`tools/oracle/dwarf1.py lines <VA> --table`).
- Never hand-edit `asm/**` or generated config (`splat.yaml`, `cus.json`, `debug_chunks.json`, `objdiff.json`, generated headers); regenerate with `./ddr oracle`.
- Retail binaries, disc images and toolchains are never committed. Tool code is Python 3 standard library only. `python3 -m pytest` for tests (the full suite is minutes; run focused tests while iterating).
- Concurrent-agent rule: each task owns its files; when two tasks would touch one file (e.g. `configure.py`), they serialize. **And only one agent runs a build at a time.** `./ddr build`, `./ddr oracle` and the full suite all rewrite `asm/**`, `build/**` and the generated config, so two agents running them in this checkout corrupt each other — observed three times today: a link failure with an undefined `D_00293A58` from a concurrently regenerated split, `symbol_addrs.txt` reverted twice mid-task, and `ddr`'s hunks nearly lost to a `git checkout -- ddr`. Serialize builds, and hand-edited names go in `borrowed_symbols.txt` (which the oracle merges), never in the generated file.
- **A shrinking name set needs a clean rebuild.** Removing borrowed names left `asm/**` splits referring to symbols nothing defined and the link failed until `rm -rf asm build out`; the generated tree is not pruned when the ledger shrinks. Fixing the generator to prune the split files it owns is a task, not a workaround to remember.
- **Staging is shared too.** In one checkout `git commit --amend` picks up whatever another agent has staged — an amend today swept in another task's `revisions.py`, its tests and `config/ddrex2p/*`. Always commit with an explicit path list, and never `--amend` here.
- **One record per VA, and nothing outside the declared segments.** splat's duplicate check is parser-level and fires at symbol load, *before* the split: 73 duplicated VAs in the generated ledger stopped `configure.py` and `ddr build` outright (88 extra records — 76 in the overlay window plus 12 `obj` repeats **inside bss**, which are not overlay material at all). So the generator must hand splat exactly one record per VA inside the declared segments and withhold everything else into `unplaced_symbols.txt` with its reason. **No reservation-segment model is needed** — extending `Geometry` for the eleven overlay reservations would not have unblocked it, since the check fires for in-bss repeats too.
- **Yields are relative to the ledger.** A borrowed name is a function start, so the ledger's own contents move the split's bounds; any alignment yield or chance control is relative to the current ledger, not an absolute property of the binary.
- **A green suite in a shared worktree proves nothing about a commit.** In this checkout a suite run reported 204 passed while calling a two-argument `emit_symbols.final` that existed only in another agent's *uncommitted* edit — the committed tool took one argument. Verify claims at the commit (an AST cross-check of committed tests against committed tools is enough to catch signature drift), not against whatever is in the tree at the time.

## Review Focus

1. A retarget that silently keeps an old pin — the two targets' pins must differ and be asserted to differ.
2. Library code acquiring hand-written C, or a library rename losing its provenance.
3. A compiler pin taken from the ident string instead of from measured bytes.
4. G1/G3 "passing" through a skip path (a missing image printing a skip and returning 0) rather than a real comparison.

---

## Phase 1 — identification (do this first, per the user's ordering)

### Task 1: Pin the compiler for this build, by measurement

**Files:**
- Modify: `tools/toolchain/select_build.py` (accept `--target`/config dir), `configure.py` (the target's `TU_BUILDS`)
- Create: `docs/milestones/ddrex2p-compiler-sample.md`
- Modify: `tests/toolchain/test_select_build.py`

**Interfaces:** `select_build.sample(tu_names, builds) -> list[dict]` — per TU, per candidate build: the three verdicts (`.text`, `.debug`, `.line`) and the flags used.

- [ ] **Step 1: Write the failing test** — a batch run over three named TUs of the new target returns one verdict per (TU, build) pair, including builds that fail, and never silently drops a TU.
- [ ] **Step 2: Run to verify it fails.**
- [ ] **Step 3: Run the sample over every TU for which C exists** (it starts with `sys_scf.c` alone, and grows as promotions accumulate — the verdict is a running record, not a one-shot), across all five builds present (`2.4-001213`, `3.0-011126`, `3.0.1-020123`, `3.0.3-020716`, `3.0b38-030307`) and the flag axes already in use. A build can only be pinned against functions we can compile, so this task stays open across the milestone and closes when a sample of *unrelated* TUs agrees.
  Already measured on `sys_scf.c` (the sweep that motivated this task): with `-c -lang c -O3 -g` the object's function sizes are 12 B and 48 B, matching retail, while `-O2 -g` gives 16 B and 60 B and is therefore **ruled out**; `2.4-001213` reproduces the *old* target's `sys_scf.c` only 1/2 and is also **ruled out**; `3.0-011126`, `3.0.1-020123`, `3.0.3-020716` and `3.0b38-030307` each reproduce it 2/2, so the tie must be broken by a wider sample. Note the flags are per-TU in this project (`configure.py`'s `TU_BUILDS`), so the sample must vary them, not assume one set.
- [ ] **Step 4: Record the verdict** in `docs/milestones/ddrex2p-compiler-sample.md`: the winning (build, flags) per TU, the ties, and the counter-evidence. If more than one build survives the whole sample, prefer the one that also reproduces the retail `.comment` bytes and say so.
- [ ] **Step 5: Commit** — `ddrex2p: pin the compiler by measured sample, not by ident`

### Task 2: Confirm the library revisions byte-wise (names only)

**Files:**
- Create: `tools/sdk/revisions.py`, `tests/sdk/test_revisions.py`
- Create: `config/ddrex2p/library-revisions.md` (committed)

**Interfaces:** `revisions.match(region_bytes, archives) -> dict` — per library stamp: which archive set (if any) reproduces its members byte-for-byte under relocation masking (`j`/`jal` targets and I-type immediates zeroed, whole bodies compared); `revisions.verdicts() -> list[dict]`.

- [ ] **Step 1: Write the failing test** — a function copied byte-for-byte from a known archive member is reported as matched, one differing in a single instruction as unmatched, and a size mismatch is reported as such.
- [ ] **Step 2: Run to verify it fails.**
- [ ] **Step 3: Run the match** for the eleven stamps this build needs against every archive set on disk (`~/sdk-downloads`, `~/sdk-extract`: tlib 2.5.0–2.5.5, Tool-Libs 2.4.2, Runtime Library 2.0, EE 1.00.03, devkit 1.52 = tlib 3.0.3, SCE-RT).
- [ ] **Step 4: Record per library**: the stamp, the archive that matches, the count of whole-body-identical functions, and what is unexplained (`libmc 3020` vs our `3030`; EyeToy `1.3.0`). Names go into the ledger with provenance; **no C is written**.
- [ ] **Step 5: Commit** — `ddrex2p: library revisions matched byte-wise (names only, no C)`

---

## Phase 2 — the skeleton (M1: no C)

### Task 3: One target descriptor, and every tool reads it

**Files:**
- Create: `config/targets.py` (the descriptor: name, retail ELF path, G1 pin, image path, G3 pin, config dir)
- Modify: `configure.py`, `ddr`, `tools/oracle/emit_{symbols,cus,chunks,headers}.py`, `tools/verify/{g1,g2}.py`, `tools/iso/reinsert.py` — take the target instead of hardcoding `usam2`/`SLUS_207.11`
- Modify: the test suites, parameterised over targets

**Interfaces:** `targets.get(name) -> Target`; `Target.config_dir`, `.elf`, `.elf_sha256`, `.image`, `.image_sha256`; CLI `--target <name>` on `ddr` and `configure.py` (default keeps today's behaviour).

- [ ] **Step 1: Write the failing tests** — the descriptor resolves `ddrex2p` with its pins; a descriptor missing a required field fails loudly; the registry is generic enough that a second target is addable by configuration alone (test that property, not a second target's existence); nothing outside the descriptor hardcodes a target name or a retail path. (DDRMAX2 (US) was removed on 2026-10-16: `ddrex2p` is the only registered target and the default.)
- [ ] **Step 2: Run to verify they fail.**
- [ ] **Step 3: Implement the descriptor** and thread it through the ~26 touchpoints, with `ddrex2p` as the only registered target and the CLI default. No `usam2` literal or `SLUS_207.11` path survives outside the descriptor module.
- [ ] **Step 4: Verify the plumbing without building** — `python3 -m pytest -q` green with the usam2-only tests removed (`tests/test_m2_sys_scf.py` and the usam2-pinned hash/disc-path cases). Do **not** attempt `./ddr build` or `./ddr verify` for `ddrex2p`: its config does not exist until Task 4 generates it.
- [ ] **Step 5: Commit** — `retarget: one target descriptor, ddrex2p only`

### Task 4: Generate the new config from the new binary

**Files:**
- Create: `orig/SLUS_211.74` (gitignored copy), `config/ddrex2p/{checksums.txt,symbol_addrs.txt,splat_symbol_addrs.txt,cus.json,debug_chunks.json,splat.yaml}` (generated where the others are)
- Modify: `ddr` (oracle verb), tests that assert config completeness

- [ ] **Step 1: Place the retail binary** at `orig/SLUS_211.74` and pin both hashes in `config/ddrex2p/checksums.txt`.
- [ ] **Step 2: Run `./ddr --target ddrex2p oracle`** and verify the artifacts against the DWARF facts: 2,676 functions, 249 TUs, and the function addresses the oracle reports for `sys_scf.c` (`sysGetDateNotation` 12 B, `sysInitScf` 48 B).
- [ ] **Step 3: Commit** — `ddrex2p: the generated config, pinned to the prototype`

### Task 5: G1 — byte-identical rebuild of the template

**Files:** `configure.py` (segment list from the new binary), `tests/verify/test_g1.py` (parameterised)

- [ ] **Step 1: Split and link** — `./ddr --target ddrex2p oracle && python3 configure.py --target ddrex2p && ninja`.
- [ ] **Step 2: Prove G1** — `./ddr --target ddrex2p verify` reports the pinned hash `ef31c90f…c02cd` and passes; investigate any divergence as a build-configuration error, not a data problem.
- [ ] **Step 3: Commit** — `ddrex2p: G1 green on the prototype template`

### Task 6: G3 — byte-identical disc rebuild

**Files:** `tools/iso/reinsert.py` (already accepts `--iso`/`--out`), `tests/iso/test_reinsert.py` (parameterised)

- [ ] **Step 1: Prove G3** — splice the rebuilt ELF into the mounted prototype image and compare the hash to `70a90566…652b`. The image is a plain 2048-byte ISO, so no MODE2 ladder work applies.
- [ ] **Step 2: Confirm the skip path still refuses to claim a comparison** when the image is absent.
- [ ] **Step 3: Commit** — `ddrex2p: G3 green on the prototype image`

---

## Phase 3 — game code (M2, then the loop at scale)

### Task 7: First promoted TU on the new target

**Files:** `src/sys/sys_scf.c` (already written for the old target, same source exists here), `tests/test_m2_sys_scf.py` (parameterised), `docs/milestones/ddrex2p-m2.md`

- [ ] **Step 1: Promote `sys_scf.c`** — a small port, not a copy: the source drifted between builds (the preview's `sysInitScf` has `li a0,1` where DDRMAX2's calls a function; the two functions are *not* byte-identical), so the task is to reproduce the preview's bytes, adjusting the C where the source changed, and to get `./ddr --target ddrex2p verify --tu sys_scf.c` green on all three parts.
- [ ] **Step 2: Commit** — `ddrex2p: promote sys_scf.c (M2)`

### Task 8: The loop at scale

Port the M3 work already briefed, re-pointed at this target (four times the TUs make each item load-bearing):
- C-mode, centralised type headers across 249 TUs (the in-flight Task 1 work is target-generic);
- a `ddr diff` basis built from retail bytes for the unit under edit (in-flight Task 2 brief);
- a calibrated promotion batch, recorded in `docs/milestones/ddrex2p-batch-one.md` with throughput measured honestly.

Acceptance for the batch: each promoted TU green on `.text` + `.debug` + `.line`, G1 and G3 unmoved, and the batch's throughput written down rather than asserted.

---

## Phase 4 — library identification (no C)

### Task 9: Name the library subset and pin what matches

- Import the library names from `config/ddrex2p/library-revisions.md` and the corpora into `config/ddrex2p/symbol_addrs.txt` with provenance; pin the archive members that are byte-identical so the region links rather than reverses; leave the rest as split assembly.
- Never write matching C. Report the split as numbers: named, pinned, unexplained.
- Acceptance: G1/G3 unmoved by the renames, provenance recorded per name, and the unexplained remainder listed rather than summarised.

---

## Self-Review Notes

- **Coverage of the spec:** identification-first (Tasks 1–2), skeleton (3–6), game code (7–8), library naming without C (9). Overlays, assets, IOP and the DWARF-less engine are deliberately absent — they are the spec's out-of-scope list.
- **Sequencing:** Tasks 3–6 are one chain (descriptor → config → G1 → G3) because each depends on the previous; 1 and 2 are independent of the chain and can run in parallel with it; 7 needs 5; 8 needs 7.
- **Known risk carried forward:** if Task 1 cannot pin a build for *most* TUs, the skeleton still proceeds (G1 depends on the split and the link, not on per-TU compiler choice), but promotion throughput becomes the constraint — and that finding belongs in the milestone doc, not in a silent workaround.
