# flag sweep report — are the three codegen divergences flags or a missing revision?

Tree: `<checkout>` (main checkout), 2026-10-19.
Builds: all five installed — `2.4-001213`, `3.0-011126`, `3.0.1-020123`, `3.0.3-020716`, `3.0b38-030307`.
Probes: `drafts/flagsweep/static_order.c`, `coalesce.c`, `fold_index.c`, `fold_ptr.c`.
Harness: `drafts/flagsweep/sweep.py` (64 flag families × 5 builds × 4 probes; regenerates the tables).
Accepted-pragma list: `drafts/flagsweep/accepted_pragmas.txt`.

## Answer

**None of the three decisions requires a compiler revision we do not have.**

* The **static tag** is a *source-shape* property, not a flag or a build signature. Retail's
  three statics are initialized; initialized file-scope statics are `local_variable` in **all
  five builds under all 64 flag families** (304/304 cells), in retail's order.
* The **coalescing choice** is a *build/flags* property. `3.0.1-020123` and `3.0.3-020716`
  produce retail's `bgez; nop; move; subu` block at the baseline `-O3` and at
  `-O3 -opt full`; `3.0-011126` does so only with `-O2`/`schedule off`; `3.0b38` with
  `-opt full`/`-O2`/`schedule off`. 122/304 cells are retail-like.
* The **pointer fold** is a *build* property. Only `3.0b38-030307`'s optimizer folds an index
  form into a walking pointer without adding a local: 10/304 cells, all `-opt full` variants.
  On the real `p_anime.c` index draft it gives `play_anime_step_inst` 0x41C (retail exact),
  18 locals (retail exact), and the `addu s8,s8,stride` pointer update. The other four builds
  never fold index→pointer under any tested family or accepted pragma.

The one residual string-level fact is that `3.0b38` writes
`MW MIPS C Compiler (3.0.0)` in `.comment`, where retail writes `(2.4.1.01)`. That is not a
codegen decision and the comment string is already known not to track the installed 3.0
builds (they report Version 3.0 but write the 2.4.1.01 string). The codegen signature is
b38's; the comment is the only mismatch.

## 1. Option inventory

### 1.1 Documented surface (`-help all`, identical in the five except where noted)

Options that can plausibly move code or DWARF:

| family | accepted values (as the compiler validates them) |
|---|---|
| optimization level | `-O0`, `-O1`, `-O2`, `-O3`, `-O4`; `-Os`, `-Op` (UNIX spellings; `-O+0..4,p,s` is documented but `-O+` itself is rejected) |
| `-opt` | `off`, `on`, `all`, `full`, `level=0..4`, `[no]intrinsics`, `display`, `dump`. **`-opt speed` and `-opt space` are rejected** despite the help text; `full` is what reports "optimize for speed" in `-opt display`. |
| inlining | `-inline on`/`smart`, `none`/`off`, `auto`, `noauto`, `all`, `deferred`, `level=0..8`; b38 adds `[no]bottomup` |
| debug | `-g` (= `-sym full,elf`), `-sym off`, `on`, `full`, `full,elf` |
| data/frame | `-sdatathreshold N`, `-farcall on|off`, `-fp off|single` |
| front end | `-lang c|c++|ec++`; b38 adds `c99`; `-char signed|unsigned`, `-enum min|int` |
| b38 only | `-flag pragma` (same as `#pragma`), `-for_scoping on|off` |

### 1.2 Accepted but undocumented

* `-lmwstmw` (no argument) — the only codegen-ish hidden flag found by probing candidate
  names. It changed **none** of the three probes on any build.
* Rejected despite being common MWCC spellings: `-ipa`, `-proc`, `-schedule`, `-pool`,
  `-frame`, `-model`, `-G`, `-mips3`, `-mr5900`, `-O+…`.

### 1.3 Pragmas — the compiler's own legality answer

`-w pragmas` reports `illegal #pragma` for an unknown name, so the accepted set can be
measured rather than guessed. `3.0-011126` accepts 26 codegen pragmas:

`optimization_level`, `opt_common_subs`, `opt_propagation`, `opt_strength_reduction`,
`opt_strength_reduction_strict`, `opt_loop_invariants`, `opt_dead_code`,
`opt_dead_assignments`, `opt_lifetimes`, `opt_pointer_analysis`,
`opt_pointer_analysis_mode`, `opt_unroll_loops`, `opt_unroll_count`,
`opt_unroll_instr_count`, `opt_vectorize_loops`, `schedule`, `peephole`, `pool_strings`,
`global_optimizer`, `optimize_for_size`, `always_inline`, `auto_inline`, `dont_inline`,
`inline_bottom_up`, `inline_intrinsics`, `force_active` (plus `push`/`pop`).

`3.0b38` accepts those and ~60 more internal `opt_*` toggles — including
`opt_docrossconversionofinductionreference`, `opt_markcounterloops`,
`opt_markvariablecounterloops`, `opt_reverseloops`, `opt_rotateloops`,
`opt_moveinvariantsinaddressexpr`, `opt_unrollpostloop`, `opt_scalarize`, etc. The full list
is `drafts/flagsweep/accepted_pragmas.txt`; every one was tested on the fold probe.
Rejected in all builds: `opt_register_alloc`, `opt_peephole`, `opt_scheduling`,
`opt_schedule_instructions`, `opt_branch`, `opt_ptr_conversion`, `pool`, `scheduling`,
`frame`, `lmwstmw` (as a pragma).

`-pragma "NAME value"` is the command-line equivalent and was verified to take effect
(`optimization_level 0` changes the instruction count; `schedule off` changes scheduling).

### 1.4 `DW_AT_producer` and `.comment`

| source | `DW_AT_producer` | `.comment` |
|---|---|---|
| retail `p_anime.c`, `com_scrollbar.c` CUs | `MW MIPS C Compiler` | `MW MIPS C Compiler (2.4.1.01)\0PlayStation2\0` (whole section, 43 B) |
| `2.4-001213` object | `MW MIPS C Compiler` | `MW MIPS C Compiler (2.4.1.01)` |
| `3.0-011126` object | `MW MIPS C Compiler` | `MW MIPS C Compiler (2.4.1.01)` |
| `3.0.1-020123` object | `MW MIPS C Compiler` | `MW MIPS C Compiler (2.4.1.01)` |
| `3.0.3-020716` object | `MW MIPS C Compiler` | `MW MIPS C Compiler (2.4.1.01)` |
| `3.0b38-030307` object | `MW MIPS C Compiler` | `MW MIPS C Compiler (3.0.0)` |

`DW_AT_producer` is identical everywhere and cannot discriminate. `.comment` excludes b38
only if the retail `(2.4.1.01)` string is taken as authoritative; the 3.0 builds already show
that string and Version 3.0 disagree inside the same binary.

## 2. Discriminator 1 — file-scope static tag

Retail's `p_anime.c` declaration CU (0x17825) holds, in this order:

```
local_variable  anime_id_tbl
local_variable  hold_release
local_variable  pre_hold_flag
global_variable g_game_w
global_variable paw_p
global_variable play_anime_w
```

The static data themselves explain why: `anime_id_tbl` at 0x2D0B60 contains non-zero bytes
(`000000000100000004000000...`), i.e. it was **initialized** in the source;
`hold_release`/`pre_hold_flag` are zero but sit in the zero-initialized small-data section.
An initialized file-scope static is tagged `local_variable`, and initialized globals keep
declaration order.

The documented probe (`static int s_one; static int s_two[4]; int g_one;`) has *uninitialized*
statics. Re-measured: uninitialized statics are `local_variable` only while nothing references
them; once a function references one it becomes `global_variable`; initialized statics stay
`local_variable` even when referenced. The original measurement therefore tested a different
construct than retail's.

Probe `static_order.c` is retail's six objects with initializers and the references retail's
code has. Against the six-DIE retail sequence above:

| build | flag families tested | exact match |
|---|---:|---:|
| 2.4-001213 | 60 | 60/60 |
| 3.0-011126 | 60 | 60/60 |
| 3.0.1-020123 | 60 | 60/60 |
| 3.0.3-020716 | 60 | 60/60 |
| 3.0b38-030307 | 64 | 64/64 |

**Verdict: source shape, not flags and not revision.** 304/304 cells. Adding initializers is a
C-level fix, not a compiler-revision boundary.

## 3. Discriminator 2 — the surviving second `subu`

Retail's `ComScrollBarDisp` block at 0x2484AC:

```
2484ac  bgez  v0, 2484b8
2484b0  nop
2484b4  move  v0, zero
2484b8  subu  v1, a3, a1      <- the subtraction survives
2484bc  slt   at, v1, v0
2484c0  beqz  at, 2484d0
2484c4  nop
2484c8  move  v0, v1
2484cc  nop
```

Probe `coalesce.c` is the else path alone. Classification: `retail_like` = the `subu` after a
`nop`+`move`; `coalesced` = the `subu` folded into the `bgez` delay slot.

| build | baseline `-O3` | `-O3 -opt full` | `-O2` | `schedule off` | retail-like cells |
|---|---|---|---:|---:|---:|
| 2.4-001213 | coalesced | coalesced | other | other | 0/60 |
| 3.0-011126 | coalesced | coalesced | **retail_like** | **retail_like** | 6/60 |
| 3.0.1-020123 | **retail_like** | **retail_like** | **retail_like** | **retail_like** | 50/60 |
| 3.0.3-020716 | **retail_like** | **retail_like** | **retail_like** | **retail_like** | 50/60 |
| 3.0b38-030307 | coalesced | **retail_like** | **retail_like** | **retail_like** | 16/64 |

`3.0.1`/`3.0.3` match at the same `-O3 -opt full` string the unit already uses for `p_anime`;
their only failures are the no-optimizer families (`-O0`, `-O1`, `-Os`, `-Op`, `-opt off`) and
the two pragmas that switch off the allocator assumptions (`peephole off`, `global_optimizer
off`). The chosen unit pair `3.0-011126 -O3 -opt full` is precisely the one that coalesces.

**Verdict: build/flags we have, not a revision.** The "mwcc coalesces them" statement is true
of `3.0-011126` and `2.4`, not of `3.0.1`/`3.0.3` (or b38 under `-opt full`).

The full-function register *permutation* is a separate fact: the 320-cell full-function sweep
(64 families × 5 builds) found **0** cells whose saved-register map equals retail's. b38's
`-O3 -opt full` reproduces retail's size (0x540) and the block above, but still assigns
`scrbw` to `s5` where retail uses `s1`. That residue is not moved by any documented flag,
scheduling/peephole/lifetime pragma, or optimization level.

## 4. Discriminator 3 — index IV folds to a walking pointer without a 19th local

Retail's large functions materialise `&g_game_w` once and advance it at the loop bottom
(`addu $22,$22,$4`, `$4 = 0x5428C`), with constant member offsets from the pointer.

Probe `fold_index.c` is the index source form (no pointer local); `fold_ptr.c` is the pointer
form (adds `gw`). Classification: `pointer_iv` = the symbol base is loaded before the loop and
the same register is advanced by `addu R,R,stride`; `index_iv` = base re-materialised inside the
loop, or a separate index added to it.

| build | index form → pointer IV | index locals | pointer form → pointer IV | pointer locals |
|---|---:|---:|---:|---:|
| 2.4-001213 | 0/60 | 2 | 0/60 (index) | 3 |
| 3.0-011126 | 0/60 | 2 | 60/60 | 3 |
| 3.0.1-020123 | 0/60 | 2 | 60/60 | 3 |
| 3.0.3-020716 | 0/60 | 2 | 60/60 | 3 |
| 3.0b38-030307 | **10/64** (all `-opt full` variants) | 2 | 64/64 | 3 |

On the *real* index-form draft (`.git/agents/unit-k/drafts/p_anime.c`) at
`-O3 -opt full -g`:

| build | `play_anime_step_inst` | `play_anime_step` | step_inst locals |
|---|---:|---:|---:|
| retail | 0x41C | 0x4A4 | 18 |
| 2.4-001213 | 0x410 | 0x48C | — |
| 3.0-011126 | 0x424 | 0x4AC | 18 |
| 3.0.1-020123 | 0x424 | 0x4AC | 18 |
| 3.0.3-020716 | 0x424 | 0x4AC | 18 |
| **3.0b38-030307** | **0x41C** | **0x49C** | **18** |

b38's `step_inst` body contains the retail pointer update (`addu s8,s8,a0` with
`a0 = 0x5428C` at the loop bottom), and its local count is retail's 18 (retail's `step` has
19, and the draft has 19 there too — the unit report's "18" applies to `step_inst`). With the
small probe, `-opt full` unrolls the eight-iteration loop; adding `opt_unroll_loops off` gives
the single-element walk exactly:

```
10: lui    a3,0x0
14: addiu  a3,a3,0        ; &g_game_w
18: lui    v1,0x5
1c: ori    a1,v1,0x428c   ; stride
20: sw     t0,0(a3)       ; constant offset from the walker
...
34: bnez   v1,20
38: addu   a3,a3,a1       ; pointer += stride
```

No accepted pragma and no `-O2/-O3/-O4` variant enables this fold on the other four builds;
the ~90 b38-only `opt_*` pragmas change nothing on the non-b38 builds either.

**Verdict: a build we have (`3.0b38`) plus `-opt full`, not a missing revision.** The residual
is string-level: b38's `.comment` is `(3.0.0)`, retail's is `(2.4.1.01)`. If `.comment` is
authoritative, the retail compiler is a b38-optimizer build carrying the old comment string —
a revision between `3.0.3-020716` and `3.0b38` that is not installed. But the codegen decision
itself no longer needs an unknown revision: it is reachable with an installed binary.

## 5. Sweep size and what is still untested

* Main matrix: **64 flag families × 5 builds = 320 cells**, four probes per cell
  (~1,280 compiles); 304 cells per probe compiled (16 are the four b38-only options rejected
  by the other four builds).
* Extra pragma surface: ~90 b38-only accepted pragmas plus the 26 common ones, each on top of
  `-O3` and `-O3 -opt full` (~720 compiles), checking for an index→pointer change.
* Full `ComScrollBarDisp` register-map sweep: 64 families × 5 builds = 320 compiles.
* Retail `p_anime.c` index draft: five builds × the `-O3 -opt full` pair.

Not exhaustively tested, and why:

* **Pragma combinations.** Single-pragma additions were tested, not the 2^n cross product.
  No single accepted pragma changed the fold on a non-b38 build, and the fold is reproduced
  without any pragma on b38, so combinations are not needed for the positive result.
* **Function-local `#pragma` placement.** `-pragma` applies TU-wide; a `#pragma` inside a
  function could in principle scope an optimizer toggle to one loop. It cannot add an
  optimizer that the build lacks (none of the non-b38 builds folds under any global toggle),
  so this is only relevant to tuning b38, which already folds.
* **`-lmwstmw` combinations.** The bare flag is accepted and inert on all probes; it was not
  crossed with the rest of the matrix.
* **Builds other than the five.** None were available. The specific untested build class is
  "b38's optimizer with the 2.4.1.01 `.comment` string"; that is the only way to reconcile
  the codegen and the string.
* **`-D`/`-U`, include order, and per-unit source pragmas** were not swept; they change the
  front end's view, not the optimizer flags, and the probes are self-contained.

## Verdicts

| discriminator | reproduces with | is it flags? | is it a revision? |
|---|---|---|---|
| static tag | initialized statics, **all 5 builds × all 64 families** (304/304) | no | no — source shape |
| surviving second `subu` | `3.0.1`/`3.0.3` at `-O3` or `-O3 -opt full`; `3.0-011126` at `-O2`/`schedule off`; b38 at `-opt full` (122/304) | yes | no — installed build/flags |
| index→pointer fold, no 19th local | **`3.0b38-030307`, `-O3 -opt full`** (10/304; real draft: 0x41C and 18 locals) | yes (`-opt full`) | no for the codegen; b38's `.comment` is the one string mismatch |

The two-flag-string premise is what made "sixth revision" look necessary. With the optimizer
surface enumerated from the binaries, the static decision disappears as a compiler question,
the coalescing decision is a build selection, and the fold is an installed build's
`-opt full` behavior.
