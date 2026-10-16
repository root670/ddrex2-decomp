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
