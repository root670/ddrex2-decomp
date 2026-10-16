# Library sourcing survey (M3 evidence base)

Survey of what public decompilation projects actually publish for the PS2 SDK libraries, and what it
is usable for. Measured against this repo's binaries, 2026-10-15. Feeds plan Task 5 (`borrow.py`,
`library-names.md`). Nothing here is a claim about our own reverse engineering: it is a catalogue of
*borrowable references*, with licences, so the borrow step can be done once and correctly.

## The size of the problem, measured

- `objdiff.json` has **3,603 units = 423 DWARF-named + 3,180 `main/func_*`**.
- **3,032 of the unnamed functions sit below VA `0x21C410`** — the lowest game-code PC (per
  `orig/usam2.elf.txt`) — inside a **1,164,296-byte region, 68 % of the loadable image**.
- Only **148** unnamed functions are inside the game region proper.

So the library region is the dominant unknown, and it is exactly where other projects' work is
borrowable in principle.

## What each source publishes

| Source | Publishes | Licence | Names / sizes | Bytes (asm) | Source | Objects |
|---|---|---|---|---|---|---|
| `AshfordFamily/recvx-decomp` | `config/symbol_addrs.txt`: **~1,038 named SDK functions with explicit `size:0x…`** (VA `0x1000C0`–`0x12B060`; game code starts at line 1067), incl. `visibility:local` statics (`memclr`, `_sceRpcGetPacket`, `_loopRotMatrixZ`); a complete **object-member map** of the SDK archives with address ranges (`sce/ee/lib/libgraph/graph001` … `sce/ee/gcc/ee/lib/libgcc/fp-bit`, library span 176,096 B); the linked `-l` list (`gcc graph dma dev pkt pad vu0 kernl c mc cdvd m ssyn sdr mpeg ipu`); an SDK 2.0.0 / 3.0.3 switch | MIT | names **and sizes** | no | no | no |
| `LucasPicoli/god-hand-decomp` | ~6,917 functions + 40,215 data symbols with SDK names (`sceGsResetGraph`, `sceDmaPutEnv`, `scePadPortOpen`, `_pad_intr_hdr`, `sceSifInitRpc`, …); per-TU compiler map | MIT | names only (`// type:func`, no sizes) | no | their own C | no |
| `TheOnlyZac/sly1` (Sly Cooper, 2002) | library names **labelled by original SDK source path** — e.g. `// /usr/local/sce/ee/gcc/src/newlib/libm/math/wf_fmod.c` → `fmodf = 0x2058a0`, plus `// libdma.c`, `// ../eecdvd.c`, `// libpad.c`, `// filestub.c`; `sceSifInitRpc`/`BindRpc`/`CallRpc`, `sceCdSync`, `scePadInit`, `sceMcInit`, `sceGsResetPath`, `memclr`; several historical symbol files | CC0-1.0 | names only | no | no | no |
| `g-guthrie/mvc2-ps2-decomp` | `build-inputs/mvc2-ps2-build-inputs.tar.gz` (9.4 MB) = **their retail ELF image + MWCCPS2 3.0.3 and 3.0-011126 + Wibo 1.2.0 + SHA-256 manifest**; `config/functions.csv` 5,657 rows `name,address,size,end,classification,confidence`; `matches.csv`/`data_matches.csv` per-byte evidence | **none declared** (all rights reserved) | their own names only (no `sce*`/`Gs*`) | their ELF, not ours | no | no |
| `ps2dev/ps2sdk` | C reimplementations + headers + doxygen (`ee/kernel`, `ee/dma`, `ee/graph`, `ee/rpc/{pad,cdvd,…}`, `ee/libgs`, `ee/math3d`, …) | AFL-2.0 | names **and semantics/types** | no (different compiler, independent implementation) | yes | their own builds |
| Ghidra `ghidra-emotionengine-reloaded` | `r5900_LE_patterns.xml`: 138 `<funcstart label=…>` SDK signatures (67 matched this binary) | Apache-2.0 | names (signature-based) | no | no | no |

## Corrections to earlier assumptions

- `god-hand-decomp` publishes **no SDK headers** (`include/sce/` contains only `.gitkeep`) and **no
  sizes**.
- `recvx-decomp` does **not** publish the SDK-object disassembly its `compile_config.json` names —
  `build/` and the SDK tree are gitignored; only the *map* is committed.

## Consequences

1. **Names route (cheap, immediate).** recvx gives names *with sizes* — a size match against our
   function bounds is a real validation, not a guess. sly1's names carry the **original SDK source
   path**, which is the best available evidence for attributing a library function to a header.
   god-hand adds breadth (later SDK generation — tag it as such). ps2sdk gives types and semantics
   for whatever is named. The in-binary assert strings and the 138-entry Ghidra pattern DB (67 hits)
   stay in the mix.
2. **Bytes route (the SDK media).** **No project publishes SDK library objects or library
   disassembly**, so byte-identity for our library region can only come from the SDK itself — which
   is why Task 5's media step is the only route to objects. mvc2's bundled ELF is the single public
   byte-usable artifact, but it is *their* game's image, so its value to us is a **compiler/flag
   cross-check for Task 3**, not our library bytes — and it carries **no licence**, so nothing from it
   may be copied into this repo.
3. **Validation rule for every borrowed name:** size must match our function's bounds, and where the
   source publishes bytes or a digest, the bytes must match after masking relocated immediates. A name
   that fails either check is recorded as unvalidated and does **not** enter the ledger.
4. **Gates are measured, not assumed.** Borrowed names enter `config/usam2/symbol_addrs.txt` and the
   generated artifacts; renaming must not move G1 (`./ddr verify`). If it does, the names stay out of
   the linked image and live in a side ledger.

## Local sources (on the user's media, not published by any project)

These outrank the published corpora: a single artifact carries names **and** sizes **and** bytes, so a
match is validated rather than suggested.

### Oni 2 dev build — `abc/oni2dev_ps2.iso` (Dec 2002)

An unreleased game's dev build (Oni 2; the `SCPS_123.45` serial is a dev placeholder). Plain 2048-byte
ISO9660 — `hdiutil` refuses it, `7z` reads it. Contents: `SYSTEM.CNF` (`BOOT2 = cdrom0:\SCPS_123.45;1`),
the Sony IOP module set (`IOPRP255.IMG`, `PADMAN`, `LIBSD`, `MCMAN`, `SIO2MAN`, `USBD`, …),
`BANKS.DAT` / `RB.DAT` / `STREAMS.DAT`, and:

- **`SCPS_123.45` is an unstripped MIPS-III ELF**: `.symtab` = 15,788 symbols, **10,615 FUNCs and every
  one carries a size**, plus a 2.5 MB `.mdebug` whose CU names are the Sony EE runtime sources
  (`libpad.c libdma.c libmc.c libmtap.c libipu.c ../eecdvd.c graphdev.c glue.c cache.c intr.c thread.c
  sifcmd.c sifrpc.c filestub.c eeloadfile.c iopreset.c klib.s`).
- Version stamps: `PsIIlibpad 2500`, `PsIIlibgraph 2500`, `PsIIlibmtap 2500`, `IOPRP255` — one IOP
  revision from our game's `IOPRP254`.

Measured against our 3,032 unnamed functions below `0x21C410`:

| comparison | result |
|---|---|
| exact 24-byte prefix | 59 (2.5 %) — a floor: any `jal`/`lui` immediate breaks it |
| masked 12-word (relocation-bearing immediates zeroed) | **192 of 2,180 (8.8 %)**, **97 size-exact**, **153 distinct names** |

Names recovered are the target class: `sceGsResetGraph`, `sceGsResetPath`, `checkModelVersion`,
`sceGsSetDefDispEnv`, `sceGsSetDefDrawEnv`, `sceGsSetDefClear`, `sceGsSyncV`, `WaitDma`, `memclr`,
`sceDmaReset`, `sceDmaPutEnv`, `sceDmaSend`, `sceDmaPause`, `sceIpuSync`, `sceIpuRestartDMA`,
`sceIpuInit`, `VSync`, `_sceSDC`, `SyncDCache`, `_printf`, `kprintf`, `kputchar`, `ftoi`, `sceSifInitCmd`.

Why only 8.8 %: the two builds link **different library revisions** (Dec 2002 versus our 2003 title), so
many functions genuinely differ. Names transfer far better than bytes, and every size-exact hit is
byte-validated.

**Also measured: `orig/SLUS_207.11`'s `.symtab` is empty — 0 symbols.** The retail ELF ships DWARF but no
symbol table, so (a) the 3,180 unnamed functions are genuinely unnamed in retail, and (b) a rename cannot
collide with a retail name; what G1 compares is an empty symtab. Still measure after a rename batch — it is
now expected-green rather than unknown.

### Extracted SDK archives — `~/sdk-extract/devkit152/ee/lib/` (110 `.a`)

Obtained by unpacking the July-2005 devkit update's Wise packages with **WiseUnpacker** (no Wine; the
alternatives all fail: `innoextract` is broken here, `7z` refuses Wise packages, `unshield`/`cabextract`
expect CAB). Later era than the game, so expect names and member order to transfer while bytes do not.

### Consequence

Borrowing now has three tiers, in order of strength: **local sibling bytes+names** (Oni 2 dev build),
**extracted SDK archive member symbol tables** (names + sizes + member order), then the **published
corpora** (names, sometimes sizes). Yield is recorded per source in `config/usam2/library-names.md`.

## tlib 2.5.x — the game's own release, obtained from `archive.org/download/ps2_sdks`

The item `ps2_sdks` holds the whole tlib 2.5 line plus toolchain and CodeWarrior packages. Downloaded
outside the repo to `~/sdk-downloads/`: **`tlib_250.tgz`** (12 MB — the full 2.5.0 runtime-library
release, 38 archives under `sce/ee/lib/`) and the patch drops `tlib_251/252/253/254/255.tgz`.

**Our game's version stamps, complete list** — only eight libraries carry one, and each names its own
patch level:

| our stamp | libraries | matching tlib |
|---|---|---|
| `…2500` | libgraph, libdma, libipu, libpad, libscf | **tlib 2.5.0** |
| `…2530` | libcdvd | tlib 2.5.3 |
| `…2540` | libkernl, libmc | tlib 2.5.4 |

`tlib_250` also ships the rest of the link list (`libdev libpkt libvu0 libssyn libsdr libmpeg libmtap`);
`libc`/`libm`/`libgcc` come from the GNU toolchain packages (`DTL-S13010`, `ee001003_1.tgz`).

**Measured: masked whole-body comparison against our 2,180 library functions that have a full body.**

| archive set | 48-byte prefix | same size | **whole body identical** |
|---|---|---|---|
| tlib 2.5.0 (38 archives, 1,885 funcs) | 308 | 5 | **162** |
| tlib 2.5.2 (2, 198) | 178 | 1 | 95 |
| tlib 2.5.3 (15, 760) | 205 | 1 | 108 |
| tlib 2.5.4 (2, 175) | 175 | 1 | 91 |
| tlib 2.5.5 (9, 1,614) | 148 | 1 | 78 |

The split by library is exactly what the stamps predict: 2.5.0 matches libgraph/libdma
(`sceGsResetGraph`, `sceGsResetPath`, `checkModelVersion`, `sceGsPutDrawEnv`, `WaitDma`), while
2.5.2–2.5.5 match libkernl (`VSync`, `DisableIntc`, `topThread`, `iSuspendThread`). So the game links
**2.5.0 with per-library patches**, and a "whole body identical" hit means the archive object can be
linked as-is and reproduce retail bytes — the library region stops being 3,032 unknowns and becomes
**named, pinned objects**. What remains is coverage accounting, not reversal.

## What this does and does not prove

- Proved: the exact release family, the per-library patch levels, whole-object identity for a growing
  subset, and that names come from Sony's own archives rather than inference.
- Not yet proved: the complete per-library mapping including `libc`/`libm`/`libgcc`, and how many of the
  3,032 are covered once every archive set is in play. That is Task 6's job, with the covered/uncovered
  split reported as numbers rather than asserted.

---

## Correction: what the unnamed 1.16 MB actually is

The framing used earlier in this file and in the plan — "3,032 unnamed functions below `0x21C410` =
68 % of the loadable image = SDK library code" — is **wrong**, and the measurements say so.

- **Byte-anchored matching** of our `0x100000`–`0x21C410` region against **273 EE-side archives from every
  package obtained** (tlib 2.5.0 and patch drops 2.5.1–2.5.5, SCE Tool-Libs 2.4.2, PS2 Runtime Library
  2.0, EE 1.00.03, the July-2005 devkit's 3.0.x set) — **30,862 indexed functions** — identifies
  **757 functions / 86,944 bytes = 7.5 %**.
- That 87 KB *is* the SDK library span: sibling builds show the same size (the Oni 2 dev build's library
  region is `0x4a0000`–`0x4b4ddc`; recvx's committed object map gives 176,096 B). The libraries are fully
  explained — they are simply small.
- The remaining **~1.08 MB in 161 runs** (largest single run 114,672 B) contains: **no** CRI/ADX/Sofdec
  strings, **no** source-file strings and no `.c:line` asserts, newlib fragments (`bug in vfprintf: bad
  base`), Sony library banners (`libpad:`, `libdma: sync timeout`, `## internel error in libkernl.a!`) and
  Konami/Bemani strings.
- **Cross-build naming is weak here.** The DDRMAX2 JP build's DWARF covers only 197 functions spanning
  `0x216a70`–`0x238ee4` — its *own game* region, in a different link order. DDRMAX (US) covers 109,
  DDR Extreme (JP) 472, DDR Extreme E3 (US) 555. Matching all four sibling builds against our region names
  **49 functions / 3,880 B**, with names that are plainly *game* code: `ps2dancerReChoiceChara`,
  `ps2dancerSetCameraPos`, `ps2dancerBreakDataArea`, `Update_OptDoll`, `SetPreRead_Les`, `EdsBoxMain`,
  `animode_load_tex_init`, `get_mdt_name`.
- Every Konami build's `.comment` reads `MW MIPS C Compiler (2.4.1.01)` + `PlayStation2`.

**Conclusion: the region is ~87 KB of Sony/GCC library objects plus ~1.07 MB of game code that retail
shipped without DWARF.** The 3,180 functions are unnamed not because they are library code but because
**retail DWARF covers only 423 of 3,603 units (12 %)** — the engine, character/dancer renderer, lesson
loader and option UI were compiled without `-g`.

### Consequences

1. **Task 6 stays, with honest scope**: pin/name the SDK subset (757 functions from archives, plus
   whatever the published corpora add) and stop there. No archive will explain the rest.
2. **The bulk is ordinary decompilation**, done through the M3 promotion loop: reverse from the split
   assembly, and where no source exists name the function descriptively with recorded provenance.
3. The names recovered from siblings describe the code's shape — character rendering, lesson preload,
   option UI, oni-mode texture loading — which is useful context for that reversing.
4. `[INFERENCE]` Pinning (linking rather than reversing) is available only where whole bodies are
   identical: measured at 162–190 functions across archive sets under relocation masking.

## DDR Extreme 2 preview build (2005): the richest sibling DWARF, and why bytes still do not transfer

`/Volumes/Untitled 1/SLUS_211.74`, mounted from the user's *Dance Dance Revolution Extreme 2 (May 10,
2005 prototype)* image: a 7.7 MB ELF whose `.debug` is **4.8 MB** and `.line` 976 KB, `.comment`
`MW MIPS C Compiler (2.4.1.01)` + `PlayStation2`.

| quantity | value |
|---|---|
| DWARF | 118,116 DIEs, 2,925 CUs, 249 TUs, **2,676 functions** |
| named code | 1,221,292 B, spanning `0x1b3d30`–`0x806468` |
| source files | 249, in `src/{cs,network,am,common,sound,eyetoy,sys,gs}` + `music_all.c`, `olmain.c` |
| transfer to our unnamed region | **39 functions / 1,220 B (0.1 %)**, whole-body and relocation-masked |
| 16-byte prefix hits in the region | 1,352 offsets — similar code, not identical code |

Names that did land are shared-engine functions (`ps2dancerSetCameraPos`, `back_anime_set_inst_mode`,
`net_ave_end`, `fp_win_disp_obj`, `EyeRefGetPeerBitstreamAddr`, `get_mdt_name`).

**Verdict:** a richer sibling Debug build does not transfer as identity. Across all five sibling builds
measured (DDRMAX US, DDRMAX2 JP, DDR Extreme JP, DDR Extreme E3 US, DDR Extreme 2 preview) whole-body
transfer is **0.1–8.8 %**, while the SDK's *own* archives explain 100 % of the functions they contain
(757 in our region, 7.5 % of it). The sibling DWARF's value is **names, signatures and type layouts** for
the reversing work — the use M1 already made of the E3/Festival dumps — not identification.

### What this means for the ~1.08 MB

It is game code to be reversed through the promotion loop (plan Tasks 1–4), with the sibling and
prototype DWARF supplying engine vocabulary (`ps2dancer*`, `back_anime_*`, `Eds*`, `SetPreRead_*`,
`animode_load_tex_init`, `net_ave_end`, …) and type layouts. No further archive or sibling build is
expected to change that; the SDK subset is settled.

## Is there reversed SDK C to borrow as a first draft? (checked, 2026-10-16)

**No — and for the SDK subset it would not help.** Verified against the repositories' own file trees
(not sparse clones):

| project | `.c` files | library-shaped sources |
|---|---|---|
| `LucasPicoli/god-hand-decomp` | 2,782 | none — all `src/cod/` (Capcom engine + game) |
| `AshfordFamily/recvx-decomp` | 228 | **CRI middleware only**: `src/cri/ps2/cri_sdk.622/source/{adxt,dtx,psm,pcm_stm,ps2rna}/…` |
| `TheOnlyZac/sly1` | 167 | none (`src/P2`) |
| `g-guthrie/mvc2-ps2-decomp` | 6,030 | none (`src/data` = C arrays) |
| `ps2dev/ps2sdk` | SDK-sized | C **reimplementations** of the EE libraries (AFL-2.0) — clean-room, so not byte-matching |

The library-shaped C that does get published is third-party *middleware* (recvx's CRI — and this game has
none: zero `CRI`/`ADX`/`Sofdec` strings). Matching decompilations of console SDKs exist elsewhere
(`n64decomp/libreultra`; the PS1 PSY-Q reconstruction) but not for the PS2 EE runtime libraries.

**Why it would not help anyway:** for the SDK subset we already hold the exact objects — 9 of the 11
stamps the preview needs, and 1,163 functions matched byte-wise already. Reverse-engineering C to
reproduce a function whose compiled object we can link is strictly more work for a strictly worse result.
Matching C is the right tool only where the object is unavailable.

**Where external C is still worth harvesting**, in order of value:

1. **`ps2sdk` semantics for library functions our archives cannot match.** It states what the function
   does, and for small leaf functions a faithful implementation compiled with our compiler and flags may
   even reproduce the bytes. Cheap, decisive test: compile the candidate, compare, keep only exact
   matches — the same "propose, then measure" discipline as Task 7.
2. **Sibling game/engine C for idiom and structure** (god-hand's 2,782 files are the largest such
   corpus). Byte transfer is 0.1–8.8 %, so treat it as vocabulary, never as a match. No Bemani/Konami PS2
   decompilation project exists to borrow the shared engine from (checked: the search returns tooling
   only — `ps2dec`, `ps2dis`, `PS2Recomp`).
3. **The target's own DWARF** remains the best "draft" for its 249 TUs — signatures, types and line
   numbers, which no external C can supply.
