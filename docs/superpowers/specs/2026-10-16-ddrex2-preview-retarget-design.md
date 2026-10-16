# Retarget to DDR Extreme 2 (US) preview — design

Status: proposed, awaiting review. Supersedes the *target* of
`docs/superpowers/specs/2026-10-14-ddrmax2-us-decomp-design.md`; everything that spec says about how the
pipeline works still holds.

## Intent

Decompile the **DDR Extreme 2 (US) preview** template instead of DDRMAX2 (US), because it ships Metrowerks
DWARF 1 for **249 translation units and 2,676 functions (1,816 inside the template, 799,900 B)** against
our current target's 57 TUs and 423 functions. It is a dev-era build that kept `-g` throughout, so four
times as much of the binary arrives with names, signatures, types, source file names and line tables —
less guessing, more lookup.

**Decisions taken by the user:** switch targets; template (main ELF) first, the overlay blobs later.

**Success is unchanged in kind:** a byte-identical rebuild of the template ELF (G1), a rebuilt prototype
disc image (G3), per-TU localisation (G2), and promoted translation units whose `.text` *and*
`.debug`/`.line` bytes match retail — with progress counted in promoted TUs.

## Target facts (measured)

| | DDRMAX2 (US), current | Extreme 2 preview, new |
|---|---|---|
| binary | `orig/SLUS_207.11`, 2,512,980 B | `SLUS_211.74`, **7,725,036 B** |
| sha256 (G1 pin) | `a7596e8a…a8cc` | **`ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd`** |
| disc image | `DDRMAX2 (USA).iso` | *DDR Extreme 2 (May 10, 2005 prototype)* image |
| image sha256 (G3 pin) | `b8519c91…3ec8` | **`70a9056657665e978c7de9fc223cb753956902416418993176438316f6cd652b`** (1,838,940,160 B, plain 2048-byte ISO) |
| loadable image | one section, 1,713,792 B | one section, **1,958,272 B** |
| debug sections | `.debug` 657,815 B, `.line` 140,704 B | `.debug` **4,789,110 B**, `.line` 976,198 B |
| DWARF | 16,125 DIEs / 480 CUs / 57 TUs / 423 functions | **118,116 DIEs / 2,925 CUs / 249 TUs / 2,676 functions** (251 source paths) |
| functions (proxy) | ~3,603 | ~3,601, of which 1,816 in the template |
| compiler ident | `MW MIPS C Compiler (2.4.1.01)` | same family — *build* not yet pinned |
| overlays | none | 860 functions at `0x7f0000`/`0xe4d380`/`0x1884000`, loaded from `DATA00–09.BIN` |

`SLUS_211.74` has one real `PT_LOAD` (`0x100000`, 1,958,272 B) plus zero-filled reservations for the
overlays — the same shape our current target presents, so the link structure and the split do not change
in kind.

## What carries over unchanged

- **The oracle.** `tools/oracle/*` parses this binary already: it produced the 2,925 CU / 118,116 DIE
  numbers above with no code change.
- **The build architecture.** `configure.py` + ninja + splat, `mwccps2` under wibo, gates G1/G2/G3, the
  `ddr` CLI, the per-TU verification, and the SDD plan/review workflow.
- **The loop.** `ddr diff` / `ddr verify --tu` and the promotion rule (code *and* debug bytes).
- **The library findings.** The tlib 2.5.x identification, the masked-comparison method and the archive
  corpus all transfer; the preview links the same SDK family.

## What must change

1. **Target parameterisation.** `SLUS_207.11` appears 19× in `configure.py`, 7× in `ddr`, and `usam2` is
   bound into `tools/oracle/emit_*`, `tools/verify/*`, `tools/iso/reinsert.py` and the tests — ~26
   touchpoints. Introduce one target descriptor and a `--target` selector; `config/usam2/` stays on disk
   untouched as reference (and as the regression target for the existing suites).
2. **A new config directory** (`config/ddrex2p/`, name open to change): retail ELF path + G1 pin, image
   path + G3 pin, `splat.yaml`, `symbol_addrs.txt`, `cus.json`, `debug_chunks.json`, library and section
   layout.
3. **The split.** Regenerate from the new binary: ~2,906 `jal` targets, ~3,601 units. Overlay addresses
   (outside every segment) are excluded by construction — 860 functions stay out of scope by decision.
4. **The compiler pin, re-measured.** The ident is the same family, but the build that reproduces *these*
   bytes must be found with `select_build` over sampled TUs, not assumed from the ident.
5. **Gates re-pinned and re-proved.** G1/G2/G3 must pass on the new target before any C is written; a
   config that references a missing image or binary skips with an explicit "nothing was compared" line
   (existing behaviour, reused rather than reinvented).
6. **Docs and tests**: a milestone document per phase, and suites parameterised by target so neither
   target loses coverage.

## Data flow (shape unchanged)

```
retail ELF + disc image
   → tools/oracle: symbols, CU map, per-TU headers, debug-chunk manifest
   → configure.py + splat: the split (asm/**) and the object graph
   → ninja: mwccps2 under wibo → objects → link → G1 (byte-identical ELF)
   → tools/iso/reinsert.py → G3 (byte-identical disc image)
per TU: DWARF facts (fn/lines) → C on the retail line numbers → ddr diff → ddr verify --tu (G2)
```

## Milestones

- **M1 (skeleton):** target descriptor, new config, split, G1 green, G3 green. No C.
- **M2 (first TU):** one small TU promoted with code *and* debug identity. The DDRMAX2 US `sys_scf.c` work
  is the starting point, but **not a copy**: the source has drifted (the preview's `sysInitScf` contains
  `li a0,1` where DDRMAX2's calls a function, so the two are not byte-identical), and it is a small port
  rather than a straight port.
- **M3 (the loop at scale):** C-mode centralised headers (the existing Task 1, now four times more
  valuable), a `ddr diff` basis for the unit under edit (Task 2), a wider compiler/flag sample (Task 3),
  then a calibrated batch of promotions (Task 4).
- **M4 (library identification, no C):** name the SDK subset with provenance (measured already: 9 of the 11
  stamps this build needs, 1,163 functions matched byte-wise), pin the members that are byte-identical and
  leave the rest as split assembly. Library code is never reversed to C. The overlay blobs and the
  DWARF-less engine follow as their own milestones, behind the game TUs.

## Scope boundaries

- **In — the game code:** the DWARF-backed translation units, reversed to C and promoted (2,676 functions
  across 249 TUs, 1,816 of them inside the template), together with the build, the gates and the loop that
  verify them. This is where the effort goes.
- **In — identification only, no C:** the SDK/runtime library subset. It is **named** from the archives and
  corpora with recorded provenance, and then either pinned as the compiled object or left as split
  assembly. **No matching C is written for library functions** (user decision, 2026-10-16): the objects
  exist, so hand-written C would be more work for a worse result, and matching C is the right tool only
  where the object is unavailable.
- **Out (own milestone):** `DATA00–09.BIN` overlays (860 functions), `FILEDATA.BIN` and `SD.BIN` assets,
  the IOP side.
- **Deferred behind the game TUs:** the DWARF-less engine code. No archive names it and no debug info
  describes it, so it neither blocks nor precedes the game TUs; it stays as split assembly until someone
  chooses to reverse it.
- **Out (unchanged):** generating `.comment` from the compiler object, MODE2/2352 and MODE2/2448
  geometries (this target is a plain 2048-byte image).

## Risks

- **The compiler pin may not transfer.** Measure it first; everything downstream depends on it.
- **A prototype is not a retail release.** The reconstruction is of a May-2005 preview build; the gates
  make the claim checkable (byte-exact), and the asset layout may differ from retail.
- **Scale.** 249 TUs of generated headers make the C-mode/centralisation work load-bearing rather than a
  convenience.
- **Overlay temptation.** 860 named functions sit just outside the template; taking them on early would
  multiply gate setup before any C is written, so they wait.

## Test strategy

- Port the existing suites to be target-parameterised; run them against both targets (the old one keeps
  its pins, so this is regression coverage, not duplication).
- New: a completeness test for the target descriptor (ELF, image, config files present, hashes equal to
  the pins) and a test that the two targets' pins differ (so a retarget cannot silently keep an old pin).
- The end-to-end proof stays behavioural: `ddr verify` for G1/G3 and `ddr verify --tu` for G2 on the new
  target, exercised on a freshly built tree.
