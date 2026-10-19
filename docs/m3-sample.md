# M3 sample: every TU with C, five builds, two flag strings

Date: 2026-10-19. Tree: `<checkout>` (main checkout, `ea6f92e`).
Target: `ddrex2p`. This is the measurement the M3 promotion loop was missing: every source
that has C was compiled through the promotion path, under all five installed compiler builds
and both recorded flag strings, and the day's per-unit throughput was reduced to one table.

**Result in one line.** The game's build is uniform: `3.0-011126 -c -lang c -O3 -opt full -g`
reproduces both units whose C is believed correct (`sys_scf`, `net_grf`) byte-for-byte on
`.text`, `.debug` and `.line`, with no per-file exception. `3.0b38-030307` is excluded by
`net_grf`'s `.debug`, which is set-equal there, not byte-equal. The gate's set-equal policy
still admits a wider set of *draft* passes — `3.0b38-030307 -O3 -opt full -g` is the only
pair common to all three gate-passing units, and `lang.c` passes only there — but those are
evidence about unfinished C, not about the shipped build. §3 keeps the three counts separate.

## Method

* **Sources.** `src/**/*.c` (2 files, both promoted) plus every `drafts/**/*.c` on branches
  `wt-unit-c`, `-d`, `-f`, `-g2`, `-j`, `-k`, `-k2`, `-l`, `-m`. The branches carry 57 C entries
  (31 distinct paths, 33 distinct draft blobs); with the two `src` units the sample covers 35
  distinct blobs, and 20 of the 31 draft paths are reduced probes, not translation units. §1 accounts for all of them.
* **The promotion path.** Every cell is `tools/toolchain/compile.py`'s own `place()` and
  `compare()` — the functions behind `python3 -m tools.toolchain.compile … --compare`. They
  compile with `mwccps2` under wibo, relocate every function into the pinned layout (the
  resolver scans the data splits), rename the staged source path to retail's, and compare the
  unit's `.text`, `.debug` and `.line` with the retail image. For a cell that `place()` refuses,
the word counts were still measured by the same `MWObject` + `relocate` steps `place()` uses,
so a refusal has a text number rather than a guess. Draft sources were materialized
  under `build/sample/<variant>/<retail-basename>` and their `Tu.file` was pointed at that
  path, because the CLI's `tu_named` accepts retail paths only; this changes the staging
  directory but not the compiler, flags, relocation or comparison. The two promoted units were
  also run through the literal CLI as anchors (`sys_scf.c` and `net_grf.c`; the latter's
  `3.0b38-030307 -O3 -g` run prints `text ok`, `debug ok`, `line ok`, with the set-equal
  `.debug` boundary line on stderr).
* **Builds (all five installed):** `2.4-001213`, `3.0-011126`, `3.0.1-020123`,
  `3.0.3-020716`, `3.0b38-030307`.
* **Flag strings (the two recorded):** `-c -lang c -O3 -g` and
  `-c -lang c -O3 -opt full -g`. The compile driver also passes the target's own `-I include`
  (from `Target.include_paths`); it cannot change codegen and is required by the
  header-including drafts.
* **Words.** `words` is the sum of the retail function sizes / 4. It excludes the unit's
  trailing padding to the next split (4 B in `sys_scf`, 16 B in `net_grf`), which is why the
  CLI's text byte count is `0x40`/`0xc0` while the table's denominator is 15/44 words.
  `differing` counts retail-word positions whose compiled (relocated) word differs; a missing
  word counts as differing, extra compiled words are not counted (the denominator stays
  retail's).
* **Per-part verdicts:** `ok` = byte-equal to retail; `ok*` = gate-ok because the
  compiler-emitted `.debug` is set-equal under the recorded DIE boundary and `debug_promotion`
  keeps retail's chunk in the image (`.text` and `.line` are byte-equal); `size` = length
  matches retail but bytes differ; `±N` = length differs by N bytes; `–` = not reached (an
  earlier condition refused); `err` = no usable object (the compiler, the resolver, or the
  function lookup refused).

## 1. Inventory

### 1.1 Sampled source variants (15 variants, 11 distinct retail TUs)

| # | source | branch(es) | blob (git) | retail TU | functions | words | retail `.debug` | retail `.line` |
|---:|---|---|---|---|---:|---:|---:|---:|
| 1 | `src/sys/sys_scf.c` | master | `f648d202c470` | `sys_scf.c` | 2 | 15 | 0x28c | 0x074 |
| 2 | `src/network/net_grf.c` | master | `aa088436dc28` | `net_grf.c` | 2 | 44 | 0x638 | 0x09c |
| 3 | `drafts/com_scrollbar.c` | m | `bf98e9fed37a` | `com_scrollbar.c` | 1 | 336 | 0x955 | 0x332 |
| 4 | `drafts/dexport.c` | c | `00178b58fd83` | `dexport.c` | 2 | 114 | 0x6c39 | 0x15a |
| 5 | `drafts/dexport.c` | l | `9a28f1f1dc7d` | `dexport.c` | 2 | 114 | 0x6c39 | 0x15a |
| 6 | `drafts/dmm_chara.c` | j | `36b86aec6e15` | `dmm_chara.c` | 1 | 116 | 0x64da | 0x152 |
| 7 | `drafts/dmm_chara.c` | k, k2, master | `0b8c5f7d532b` | `dmm_chara.c` | 1 | 116 | 0x64da | 0x152 |
| 8 | `drafts/eye_filter.c` | c | `50c0f5977cbf` | `eye_filter.c` | 2 | 93 | 0x52c | 0x1dc |
| 9 | `drafts/lang.c` | c, d, f, g2, j, k, k2, l, m, master | `7941c6db30a5` | `lang.c` | 1 | 17 | 0x43e | 0x04e |
| 10 | `drafts/net_game_help.c` | f | `fa5f5cd2a5cf` | `net_game_help.c` | 2 | 179 | 0x2b1 | 0x1fa |
| 11 | `drafts/net_grf.c` | g2 | `331a7bbf7332` | `net_grf.c` | 2 | 44 | 0x638 | 0x09c |
| 12 | `drafts/net_sys_connect.c` | d | `1cb53991771a` | `net_sys_connect.c` | 2 | 52 | 0x3945 | 0x0d8 |
| 13 | `drafts/p_anime.c` | k, k2 | `47d2a26c9a5a` | `p_anime.c` | 5 | 588 | 0x4273 | 0x9b0 |
| 14 | `drafts/p_anime_walk.c` | k, k2 | `130baf731a17` | `p_anime.c` | 5 | 588 | 0x4273 | 0x9b0 |
| 15 | `drafts/sys_demo.c` | c, d, f, g2, j, k, k2, l, m, master | `fecdc9121919` | `sys_demo.c` | 2 | 5 | 0x65b | 0x042 |

`drafts/p_anime_walk.c` is a full-TU variant of the same retail TU; it was sampled under the
retail basename `p_anime.c` so the staging path has retail's length. `src/network/net_grf.c`
and `drafts/net_grf.c` are the promoted unit and its earlier WIP; both are sampled because the
question is what the source compiles to, not what is already committed under `src/`.

### 1.2 C that is not a TU (20 probe files, not sampled)

| group | files | branches | why excluded |
|---|---|---|---|
| `drafts/ctxred/` | `shape_localcopy.c`, `shape_ptrlocal.c`, `stage01_min.c` … `stage13_full.c` (15) | k, k2 | p_anime context-reduction ladder (40–150 lines against the TU's 454); a probe of the scan loop, not a translation unit |
| `drafts/flagsweep/` | `coalesce.c`, `fold_index.c`, `fold_ptr.c`, `static_order.c` (4) | k, k2, master | minimal flag/decision probes (16–60 lines); no retail TU has these names |
| `drafts/nopline/` | `control.c` (1) | k, k2, master | a `nop`/line-attribution probe |

These cannot be compiled through the promotion path: `compile.py` resolves a source to a
retail TU by name, and no `cus.json` record carries these names. They were used for the
mechanism findings in the flag-sweep and nop-line reports, and are outside this TU sample.
The 35 distinct blobs reduce to 15 sampled variants plus these 20 probes; the 57 branch
entries are duplicates of the 31 distinct paths across branches (and the master checkout
carries the same blobs for `dmm_chara.c`, `lang.c`, `sys_demo.c`, the four `flagsweep` files
and `nopline/control.c`).

## 2. Per-TU build/flag table

Each cell is `differing/words text/debug/line`. Read it across a row to compare builds for one
flag string, and down a TU's two rows to compare the flag string. `err` cells are explained in
§2.1; `–` means the gate refused before that part.

| TU source | flags | 2.4-001213 | 3.0-011126 | 3.0.1-020123 | 3.0.3-020716 | 3.0b38-030307 |
|---|---|---|---|---|---|---|
| `src/sys/sys_scf.c` | -O3 -g | 2/15 size/ok/ok | 0/15 ok/ok/ok | 0/15 ok/ok/ok | 0/15 ok/ok/ok | 0/15 ok/ok/ok |
| `src/sys/sys_scf.c` | -O3 -opt full -g | 2/15 size/ok/ok | 0/15 ok/ok/ok | 0/15 ok/ok/ok | 0/15 ok/ok/ok | 0/15 ok/ok/ok |
| `src/network/net_grf.c` | -O3 -g | 8/44 size/–/-0xA | 0/44 ok/ok/ok | 0/44 ok/ok/ok | 0/44 ok/ok/ok | 0/44 ok/ok*/ok |
| `src/network/net_grf.c` | -O3 -opt full -g | 8/44 size/–/-0xA | 0/44 ok/ok/ok | 0/44 ok/ok/ok | 0/44 ok/ok/ok | 0/44 ok/ok*/ok |
| `drafts/com_scrollbar.c` (m) | -O3 -g | 297/336 -16/–/– | 266/336 -24/–/– | 266/336 -24/–/– | 266/336 -24/–/– | 223/336 -24/–/– |
| `drafts/com_scrollbar.c` (m) | -O3 -opt full -g | 297/336 -16/–/– | 265/336 -24/–/– | 265/336 -24/–/– | 265/336 -24/–/– | 132/336 size/–/– |
| `drafts/dexport.c` (c) | -O3 -g | err | err | err | err | err |
| `drafts/dexport.c` (c) | -O3 -opt full -g | err | err | err | err | err |
| `drafts/dexport.c` (l) | -O3 -g | err | err | err | err | err |
| `drafts/dexport.c` (l) | -O3 -opt full -g | err | err | err | err | err |
| `drafts/dmm_chara.c` (j) | -O3 -g | err | err | err | err | err |
| `drafts/dmm_chara.c` (j) | -O3 -opt full -g | err | err | err | err | err |
| `drafts/dmm_chara.c` (k) | -O3 -g | 109/116 +8/–/– | 96/116 -12/–/– | 86/116 -8/–/– | 86/116 -8/–/– | 104/116 -12/–/– |
| `drafts/dmm_chara.c` (k) | -O3 -opt full -g | 109/116 +8/–/– | 96/116 -12/–/– | 86/116 -8/–/– | 86/116 -8/–/– | 89/116 +8/–/– |
| `drafts/eye_filter.c` (c) | -O3 -g | err | err | err | err | err |
| `drafts/eye_filter.c` (c) | -O3 -opt full -g | err | err | err | err | err |
| `drafts/lang.c` (all) | -O3 -g | 6/17 size/–/– | 14/17 -8/–/– | 13/17 -4/–/– | 13/17 -4/–/– | 13/17 -4/–/– |
| `drafts/lang.c` (all) | -O3 -opt full -g | 6/17 size/–/– | 14/17 -8/–/– | 13/17 -4/–/– | 13/17 -4/–/– | 0/17 ok/ok*/ok |
| `drafts/net_game_help.c` (f) | -O3 -g | 157/179 +24/–/– | 155/179 -4/–/– | 155/179 -4/–/– | 155/179 -4/–/– | 146/179 -24/–/– |
| `drafts/net_game_help.c` (f) | -O3 -opt full -g | 157/179 +24/–/– | 155/179 -4/–/– | 155/179 -4/–/– | 155/179 -4/–/– | 159/179 -8/–/– |
| `drafts/net_grf.c` (g2) | -O3 -g | 8/44 size/–/-0xA | 0/44 ok/-0x333/ok | 0/44 ok/-0x333/ok | 0/44 ok/-0x333/ok | 0/44 ok/-0x333/ok |
| `drafts/net_grf.c` (g2) | -O3 -opt full -g | 8/44 size/–/-0xA | 0/44 ok/-0x333/ok | 0/44 ok/-0x333/ok | 0/44 ok/-0x333/ok | 0/44 ok/-0x333/ok |
| `drafts/net_sys_connect.c` (d) | -O3 -g | err | err | err | err | err |
| `drafts/net_sys_connect.c` (d) | -O3 -opt full -g | err | err | err | err | err |
| `drafts/p_anime.c` (k) | -O3 -g | 544/588 -108/–/– | 538/588 -152/–/– | 534/588 -144/–/– | 534/588 -144/–/– | 534/588 -152/–/– |
| `drafts/p_anime.c` (k) | -O3 -opt full -g | 522/588 +12/–/– | 476/588 +40/–/– | 487/588 +48/–/– | 487/588 +48/–/– | 241/588 +24/–/– |
| `drafts/p_anime_walk.c` (k) | -O3 -g | 536/588 -120/–/– | 530/588 -152/–/– | 525/588 -144/–/– | 525/588 -144/–/– | 524/588 -168/–/– |
| `drafts/p_anime_walk.c` (k) | -O3 -opt full -g | 512/588 -16/–/– | 449/588 +16/–/– | 449/588 +16/–/– | 449/588 +16/–/– | 276/588 +16/–/– |
| `drafts/sys_demo.c` (all) | -O3 -g | 0/5 ok/–/size | 0/5 ok/–/size | 0/5 ok/–/size | 0/5 ok/–/size | 0/5 ok/–/size |
| `drafts/sys_demo.c` (all) | -O3 -opt full -g | 0/5 ok/–/size | 0/5 ok/–/size | 0/5 ok/–/size | 0/5 ok/–/size | 0/5 ok/–/size |

### 2.1 The cells that are `err`, and the refusals behind the others

**No usable object (all ten cells of the source):**

* `drafts/dexport.c` (both the `wt-unit-c` and `wt-unit-l` blobs). `mwccps2` exits 1 at line 61
  in both:
  `identifier 'ps2dancerGetDollList(struct *, int)' redeclared; was declared as:
  'void (struct *, int)'; now declared as: 'void (struct anon_1_26 *, int)'`.
  The generated header spells the parameter with the typedef `anon_1_26`; the draft spells
  `struct anon_1_26 *`, which declares a different incomplete struct tag. Dropping `struct`
  is the fix; the branch trees were not edited.
* `drafts/dmm_chara.c` (`wt-unit-j`). The header comment closes at line 35 and six stray `*`
  lines follow it; `mwccps2` reports `declaration syntax error` at lines 38–40. Behind that,
  the same typedef/tag conflict appears (`dmm_chara` declared `int`, then
  `void (struct *)`). The tip is syntactically broken, so the UnitJ report's measurements are
  of an earlier valid draft, not this blob.
* `drafts/eye_filter.c`. It compiles, but the object has **no definition of `negaposi`**: the
  draft is `sepia` in C plus the shape of `negaposi`, whose body needs the 128-bit GPR `pxor`
  no C expression can emit (UnitC's measured blocker). `place()` refuses before `.text`.
* `drafts/net_sys_connect.c`. It compiles, but relocation cannot resolve `NetRouterMain` at
  `0x008062B0`: the address is outside every declared segment (the overlay reservation), so
  `place()` refuses before `.text`.

**Refused after an object (the table's `size`/`±N`/`–` cells):**

* `com_scrollbar.c`: only `3.0b38-030307 -O3 -opt full -g` reaches the pinned text size
  (`0x540`); it then differs at byte `0x35`, 132 of 336 words. All other cells are 0x18 short (2.4 is `-0x10`). Reading 132/336 positionally is **not** the report's 94.55%: the
  report's score is the diff's register-canonicalised, aligned percentage; this column is
  raw positional words. The size-exact cell is the point.
* `dmm_chara.c` (k/k2): best is `3.0.1-020123`/`3.0.3-020716` at 86/116 words, 0x8 short;
  b38 is 89/116 and 0x8 too large. Nothing places.
* `lang.c`: `3.0b38-030307 -O3 -opt full -g` is the only cell that places (0/17 words,
  text/debug/line all byte-equal). 2.4 has the right text length but 6 words differ; the
  3.0/3.0.1/3.0.3 cells are 4–8 bytes short.
* `net_game_help.c`: by size progress the three 3.0.x builds are closest (155/179 words, 4
  bytes short); `3.0b38-030307 -O3 -g` has fewer positional differences (146/179) but is 24
  bytes short. Nothing places.
* `net_grf.c` (the WIP draft): 3.0/3.0.1/3.0.3/b38 take `.text` and `.line` byte-exact and
  then fail the types `.debug` block, `-0x333`; 2.4 has 8 words different and `peerPrintf
  .line` 0xA short. The promoted `src/network/net_grf.c` closed this with the unreferenced
  static function that emits the two array DIEs (commit `8d9a7bd`).
* `p_anime.c` (both tip variants): the two large functions do not reach retail's sizes.
  `p_anime_walk.c` is the better tip variant by function-size exactness: `play_anime_step_inst` `0x41c/0x41c`, three
  small functions exact, `play_anime_step` `0x4b4/0x4a4`; `p_anime.c` is `0x424` and `0x4b4`.
  The UnitK report's `0x4ac` (+0x8) is the `drafts/p_anime.c` at `c7b6ef0`; measured for this
  report, that blob gives exactly `0x4ac` and `0x41c`, while the branch tip's later commits
  moved both functions. The tip is what the table measures.
* `sys_demo.c`: `.text` is byte-exact on all ten cells; `.line` has the right length but its
  first differing byte is at `0x8`; `.debug` is not reached. The draft-finish report
  independently measured the types block at `0x45d` against retail's `0x4a8` (`-0x4b`).

The raw `differing` count is positional. A single inserted word shifts every later word, so a
function that is 8–16 bytes off (the p_anime and dmm_chara cases) reads much worse here than
its aligned `ddr diff` score. The verdict symbols (`ok`, `size`, `±N`) are the size facts and
are unaffected.

## 3. The tie

Two definitions are kept separate, because they answer different questions.

### 3.1 Gate pass, and the set-equal `.debug` boundary

A cell is **gate-passing** when `place()` accepts the unit and `compare()` reports `.text`,
`.debug` and `.line` all `ok`. That set includes cells where the compiler's emitted `.debug` is
only **set-equal**: `debug_promotion` then keeps retail's chunk in the image and prints the
boundary line. The emitted `.debug` is byte-equal only when that line is absent. This sample
does not re-litigate the policy; it records which passing cells use it (`ok*` in §2).

| TU source | gate-passing `(build, flags)` | emitted `.debug` |
|---|---|---|
| `src/sys/sys_scf.c` | `3.0-011126`, `3.0.1-020123`, `3.0.3-020716`, `3.0b38-030307` × {`-O3 -g`, `-O3 -opt full -g`} = 8 | byte-equal on all 8 |
| `src/network/net_grf.c` | the same four builds × both flag strings = 8 | byte-equal on `3.0`/`3.0.1`/`3.0.3` (6); `3.0b38` × both is set-equal (`ok*`) |
| `drafts/lang.c` | only `3.0b38-030307`, `-O3 -opt full -g` = 1 | set-equal (`ok*`) |
| the other 12 sources | none | — |

**Gate-passing intersection.** The only pair common to all three units is

```
3.0b38-030307 -c -lang c -O3 -opt full -g.
```

The largest set of TUs sharing a gate-passing pair is therefore **3** (`sys_scf`, `net_grf`,
`lang`), **3/15 = 20%** of the sample — not a majority. It is 3/3 of the gate-passing units and
3/10 of the units that compile far enough to measure. The tie among the four builds on
`sys_scf` and `net_grf` is closed by an *unrelated* unit, but only through the boundary:
`lang.c` passes under `3.0b38-030307` (with `ok*` `.debug`) and under none of the other builds;
its boundary line reports `0 of 0 @anonN indices permuted`, so the residual is recorded as
DIE order/spelling, not an anonymous-type permutation.

**Byte-equal intersection.** There is none. `sys_scf` and `net_grf` agree on
`3.0-011126`/`3.0.1-020123`/`3.0.3-020716` × both flag strings (6 pairs), but `lang.c` has no
byte-equal cell. Under the strict byte-equality reading, the largest agreeing set is therefore
**2 TUs, 6 pairs, 2/15 = 13.3%** — also not a majority. `sys_scf`/`net_grf` pass at `-O3 -g`
too, but `lang` needs `-opt full`; the flag half is pinned by `lang`'s boundary pass and by the
`p_anime`/`com_scrollbar` closest cells.

### 3.2 Relaxed best cell: what the data says about the build even where no unit reproduces

For the ten sources that produce a measurable object, define the best cell as the one with the
**fewest differing words**, taking ties as a set (this is the reports' quality axis; no tie is
broken artificially). `3.0b38-030307 -O3 -opt full -g` is in the best set for:

| source | best set, by fewest differing words | b38 + full? |
|---|---|---:|
| `sys_scf` | all four builds × both flags (0/15) | yes (tie) |
| `src/network/net_grf.c` | all four builds × both flags (0/44) | yes (tie) |
| `com_scrollbar.c` | `3.0b38-030307 -opt full` (132/336) | yes |
| `lang.c` | `3.0b38-030307 -opt full` (0/17) | yes |
| `net_grf.c` draft | all four builds × both flags (0/44) | yes (tie) |
| `p_anime.c` | `3.0b38-030307 -opt full` (241/588) | yes |
| `p_anime_walk.c` | `3.0b38-030307 -opt full` (276/588) | yes |
| `sys_demo.c` | all five builds × both flags (0/5; the line differs identically) | yes (tie) |
| `dmm_chara.c` (k/k2) | `3.0.1-020123` / `3.0.3-020716` × both flags (86/116) | no |
| `net_game_help.c` | `3.0b38-030307 -O3 -g` (146/179) | no |

That is **8 of 10 measurable sources (80%)**, and **8 of the 15 sampled (53.3%)** — a bare
majority of the sample. It is not an artefact of breaking ties toward b38: in every `yes (tie)`
row, b38+full has the same best score as the other cells. The two exceptions are real:
`dmm_chara` prefers the 3.0.1/3.0.3 pair by three words, and `net_game_help` prefers b38
without `-opt full`.

### 3.3 Answer

* **Is `3.0b38-030307` the default the data supports?** Under the gate's recorded set-equal
  `.debug` policy, yes: `3.0b38-030307 -c -lang c -O3 -opt full -g` is the only pair common to
  every gate-passing unit, the unique gate-passing cell for `lang.c`, and the unique closest
  cell (fewest differing words) for `com_scrollbar`, `p_anime.c` and `p_anime_walk.c`. Under a
  strict byte-equal `.debug` rule, **no**: `net_grf`'s b38 cells and `lang`'s only pass are
  `ok*`, so the supported builds are `3.0-011126`/`3.0.1-020123`/`3.0.3-020716`, and `lang`
  remains without a byte-equal cell. The distinction is the recorded DIE boundary, not a
  codegen difference. This is a statement about the gate's policy, not about the game: the
  uniform pair over the units whose C is believed correct is `3.0-011126 -O3 -opt full -g`,
  and b38 is excluded by `net_grf`'s `.debug`.
* **On which TUs do unrelated agreements pin it?** `sys_scf` and `net_grf` pin the build set
  `{3.0-011126, 3.0.1-020123, 3.0.3-020716}` on byte-equal `.debug`; `lang.c` selects
  `3.0b38-030307` + `-opt full` through the set-equal gate. `p_anime` and `com_scrollbar`
  independently select the same b38+full cell as their closest text match (not gate passes).
* **Is the agreeing set the majority?** Gate-passing: 3/15 = 20%, no. Byte-equal: 2/15 =
  13.3%, no. Relaxed best-cell: 8/15 = 53.3% (8/10 measurable), a bare majority. The three
  definitions are stated so the claim cannot be read as stronger than the evidence.
* One known non-codegen mismatch stays on the record: `3.0b38` writes
  `MW MIPS C Compiler (3.0.0)` in `.comment`, retail writes `(2.4.1.01)`. The flag sweep
  already established that `.comment` does not track the installed builds' codegen; it is not
  part of this tie.

### 3.4 Local-DIE emission order is a compiler property, not a module boundary

A function CU carries one `TAG_lexical_block` with nested scopes flattened into it, so scope
boundaries are not in the DWARF tree. They are recoverable from a repeated local name (the
same name cannot be declared twice in one scope) plus the line table (a function-scope local
used early must be declared before a later block). Classifying by whether the outer group
precedes the block groups:

| sample | retail order | `3.0-011126` | `3.0b38-030307` |
|---|---|---|---|
| `common/com_scrollbar.c` `ComScrollBarDisp` (8 locals, 2 blocks) | `info,sp2,bar_y,bar_h,sa,dw_h,bar_y,bar_h` — outer-first | reversed, inner group first | **retail exactly** |
| `common/cws/cws_str.c` `CwsStrDisp` (17 locals, 4 blocks) | outer prefix, then `size_w,size_h` ×4 | reverses the sequence | forward |
| game `AM/s573/doll/model2.c` `NormCulcG3U` (8, 1 block) | `normal_top,nnum,i,flg,nmp,v,nnum,i` — outer-first | inner group first | forward |
| game `CS/dancemaster/dmm_select.c` `dmm_disp_connect_sub` (23, 3 array pairs) | outer prefix, then the block pairs | reverses the sequence | forward |
| `network/net_grf.c` `peerPrintf` (one group, no block) | `r,tmp,ap` | `r,tmp,ap` for source `ap,tmp,r`; type block also matches | `r,tmp,ap` for source `r,tmp,ap`, but its type block still differs (§3.4.1) |

Inventory: **15 common TUs, 147 function CUs, 64 with locals, 268 local DIEs, 2 with a
repeated local name**, both outer-first. Game sources: **1,764 function CUs with locals, 44
with a repeated name**; 40 show the outer-first signature and 4 are name-indistinct pairs
(`i,i`, `ret,ret`, `p,sp,p`, …) that cannot order a group. A six-block probe emits `i,h,g,f,e,d,a` under
`3.0-011126` (whole declaration sequence reversed) and `a,d,e,f,g,h,i` under `3.0b38-030307`
(forward).

**Verdict:** the order difference **cuts across modules**; it tracks the compiler revision,
not `common/`. `sys_scf`/`net_grf` cannot discriminate: `sys_scf` has no local DIEs, and
`net_grf`'s single-group declaration order is unpinned — `ap,tmp,r` and `r,tmp,ap` give
byte-identical `.text` under both builds. Its 3.0 byte-equality is the draft's choice of
source order, and the b38 order that fixes its locals still differs in the type block
(§3.4.1). The module-boundary reading is refuted by any game unit with distinct block
groups in forward order; the two controls here are such units. It would be restored by a
game unit (or a common unit) whose retail DIE order puts a block group before the outer
group while matching `3.0-011126`'s `.text`/`.line`; none exists among the 46
repeated-name functions.

#### 3.4.1 `net_grf`'s first differing byte, decoded

`net_grf`'s pinned chunk is 1592 bytes at `.debug` 0x84F08. The b38 chunk is the same
length with the same 41 DIEs and the same type set; its first differing byte is chunk offset
**0x5D** (absolute 0x84F65), inside the DIE that starts at chunk 0x4F (0x84F57):

| property | value |
|---|---|
| owner DIE | `TAG_local_variable` `dancer_num`, length 0x28, sibling 0x84F7F |
| field at 0x5D | `AT_user_def_type` (code 0x0072), 4-byte `ref` |
| retail and `3.0-011126` | `0x000852B2` — the `array_type` at chunk 0x3AA (`char[22]`) |
| `3.0b38-030307` | `0x00084F7F` — the `array_type` at chunk 0x77 (`char[22]`) |

The array DIE is the same record in both chunks (same length 0x24, same subscript data); it
has moved. b38 emits the type block as `dancer_num`, `char[22]`, `char[1024]`, `struct
@anon0`, `union @anon1`; retail and 3.0 emit `dancer_num`, `struct @anon0`, `union
@anon1`, `char[22]`, `char[1024]`. The 4-byte field differs because its target DIE moved,
and every sibling/reference offset after it shifts with it. It is **not** an anonymous-type
name, a file/line stamp or a type size: chunk length, DIE count, tags and all type records
are identical.

Source reordering moves the order but does not close it. With the current declaration order
(`union`, `struct`, array, unused-static function) b38 differs in 702 bytes (3.0: 0). With
the function locals correctly declared `r,tmp,ap`, b38's types block still differs (636
bytes, first at 0x5D) while 3.0's differs only in the local order (68 bytes, first at
0x4DC). Among the legal permutations of the four top-level blocks (`U<S` is required because
the struct uses the union), b38's best is `U,A,S,F` at 171 differing bytes; 3.0 is byte-equal
on `U,S,A,F` and `U,A,S,F`. No permutation makes b38 emit the array types after the
aggregates. Deferring the array definition to the end changes the variable DIE's position
(first difference 0x53) and does not help.

**Consequence.** The retail object needs b38's forward local order (the 40/44 signature) and
the 3.0 family's type-block order (arrays last), and no installed build emits both. So the
`0x5D` difference is **not** a fixable header/source artefact; the game's compiler is a
revision none of the five is. `sys_scf` does not narrow this: both its CUs carry no local
DIEs at all (`sysGetDateNotation`, `sysInitScf` have parameters only), so its `.debug`
equality is necessary but cannot discriminate DIE order; the build question rests on this
byte and the 44 local-order discriminators together.

## 4. Throughput, as recorded by the unit reports

Promoted units first. Every number is copied from the named report; `not recorded` means the
report omits it, and no value was estimated or interpolated. `bytes targeted` is retail
`.text` bytes as the report states it.

| outcome | unit (attempt) | functions attempted | bytes targeted | wall-clock | diff iterations | compiler runs | source |
|---|---|---|---:|---:|---|---|---|
| **promoted** | `src/sys/sys_scf.c` | 2 | not recorded (manifest 0x3c) | 15 min | not recorded | not recorded | unit-screener ("the one unit that promoted in 15 minutes") |
| **promoted** | `src/network/net_grf.c` (UnitG) | 2 | 0xb0 (176) | ~100 min | ~25 compile-and-compare | not recorded separately | unit-g; promoted in `8d9a7bd` |
| not promoted | `eye_filter.c` (UnitC) | 2 | 0x174 (372) | ~50 min | 1 | ~14 probes | unit-c |
| not promoted | `dexport.c` (UnitC) | 2 | 0x1c8 (456) | ~70 min | 8 | ~30 probes | unit-c |
| not promoted | `dexport.c` (UnitL) | 2 | 0x1c8 (456) | ~95 min | 14 | ~45 runs | unit-l |
| not promoted | `net_game_help.c` (UnitF) | 2 | 0x2cc (716) | ~3 h 05 m | 2 | ~22 probes | unit-f |
| not promoted | `p_anime.c` (UnitF probe) | 2 of 5 | 0x18 (24) | ~20 min | 0 | 6 probes | unit-f |
| not promoted | `dmm_chara.c` (UnitJ) | 1 | 0x1d0 (464) | not recorded ("over the box") | 1 official | ~35 probes | unit-j |
| not promoted | `p_anime.c` (UnitK) | 5 | 0x930 (2352) | ~2 h 40 m | ~25 | ~70 probes | unit-k |
| not promoted | `com_scrollbar.c` (UnitM) | 1 | 0x540 (1344) | ~2 h | ≈190 compile-and-compare | not recorded separately | unit-m |
| not promoted | `net_sys_connect.c` (UnitD) | 2 | 0xd0 (208) | not recorded | 0 official; 1 manual | not recorded | unit-d |
| blocked | `vu0.c` (UnitB) | 3 | 444 (text only) | ~35 min | 0 `ddr diff` | ~25 `cc.compare` | unit-b |
| not promoted | `net_win_infoboard.c` (UnitA) | 4 | 0xc4 (196) | not recorded (UnitA total ≈3 h for 3 units) | 0 successful | not recorded | unit-a |
| not promoted | `el_mes.c` (UnitA) | 1 | 0x38 (56) | not recorded (same total) | 0 successful | not recorded | unit-a |

Recorded **unit totals** (not summed across units, because the missing wall-clocks above make a
day total uncomputable): UnitC — 4 functions, 0x374 bytes, ~2 h, 9 diff iterations, ~44 probes,
0 promoted. UnitF — 4 functions, 740 bytes, ~3 h 25 m, 2 diff iterations, ~28 probes, 0
promoted. UnitA — 0 promoted functions, 0 promoted bytes, ~3 h, 0 successful diff iterations.

**The screen reports are passes, not unit attempts.** They record no per-unit wall-clock,
diff iterations or compiler runs, so they have no rows in the table. Their recorded counts are:
unit-screener 1 promoted / 62 unblocked / 186 blocked of 249 units; screen-callee 1 / 6 / 242
(of 249); screen-128 after both fixes 1 promoted / 58 unblocked / 190 blocked; screen-rawdata
2 promoted / 36 candidates / 211 blocked. The counts differ because they are different tree
states, not alternative measurements of one state.

## 5. What the sample changes

1. **The compiler question is settled: one compiler and one flag set.** The game's build is a
   fact about the game, not a per-unit choice. Every unit whose C is believed correct
   (`sys_scf.c`, `net_grf.c`) is byte-equal on `.text`, `.debug` and `.line` under
   `3.0-011126 -c -lang c -O3 -opt full -g` — and under the sibling cells from
   `3.0.1-020123`/`3.0.3-020716` × both flag strings — so `tu_builds` records that uniform
   pair for both. `-opt full` is not a per-file exception: it is compatible with the code
   that already matched and is the uniform flag set. `3.0b38-030307 -O3 -opt full -g` is
   excluded by `net_grf`'s `.debug`: same length and DIE count (41), set-equal only, not
   byte-equal. Its wider gate-passing claim rests on `lang.c`, an unproven draft whose only
   pass is also `.debug` set-equal. Per-unit pairs remain a fallback for a unit no single
   pair can explain, not the organizing principle.
2. **Four branch-tip draft blobs are broken and cost compiles.** `dexport.c` on `wt-unit-c` and
   `wt-unit-l`, and `dmm_chara.c` on `wt-unit-j` and `wt-unit-k`, spell a typedef parameter as
   `struct <tag> *`; the compiler rejects the redeclaration. The UnitC/UnitL/UnitJ reports
   measured valid earlier drafts, so their throughput rows are not measurements of the tip.
   `dmm_chara.c` on `wt-unit-j` also has a broken comment (stray text after the first `*/`).
3. **UnitK's best table is not the tip.** The report's `0x41c`/`0x4ac` table reproduces on
   `drafts/p_anime.c` at `c7b6ef0`, not on the branch tip; the tip's `p_anime_walk.c` measures
   `0x41c`/`0x4b4` and its `p_anime.c` `0x424`/`0x4b4`. The wall-clock/probe counts still
   stand, but the per-function sizes in that report are historical.
4. **The gate is doing its job.** No source reports a false pass: every non-reproducing source
   is refused at text size, line bytes, types `.debug`, or relocation. The only sources whose
   `.text`, `.debug` and `.line` are all byte-equal to retail are the two promoted units and
   `drafts/lang.c` at `3.0b38-030307 -O3 -opt full -g`.

## 6. Process-list check

No row was appended to the loop in `docs/unit-work.md`: every blocker observed here is already
one of its recorded classes (128-bit GPR, `.debug` DIE ordering / unreferenced arrays, an
unplaced callee, callee-saved colouring, `.line` attribution). The two compile failures are
branch-tip source bugs (`struct` before a typedef, a stray comment), not a new blocker class.
The only new facts are the tie and the throughput consolidation, and they live in this
document rather than duplicating that list.

## 7. Reproducing

For a promoted source, the literal CLI is the measurement:

```bash
python3 -m tools.toolchain.compile src/network/net_grf.c /tmp/net_grf.o \
  --compiler 3.0b38-030307 -c -lang c -O3 -g --compare
python3 -m tools.toolchain.compile src/network/net_grf.c /tmp/net_grf.o \
  --compiler 3.0b38-030307 -c -lang c -O3 -opt full -g --compare
```

For a draft, materialize it at a repo path whose basename is the retail TU's basename (the
sample used `build/sample/<variant>/<name>`), point `Tu.file` at that path, and call
`toolchain.compile.place(tu, Manifests(target), fetch.compiler(build), fetch.wibo(), flags)`;
`place()` returns the relocated `.text`/`.debug`/`.line`, and `compare()` is the gate's
per-part answer. The full 150-cell sweep is reproducible with the two flag strings and the
five `--compiler` values above; every cell in §2 is one such call.
