# Easy units on `ddrex2p`, ranked by shape

Generated with:

```bash
python3 tools/units/screen.py --markdown --top 20
python3 tools/units/screen.py --all --top 60   # the blocked rows, with reasons
```

The rule this implements is `docs/unit-work.md`'s "Pick a unit by shape, not by size": few
functions, scalar code, no VU0, no EE 128-bit GPR operations, no large/unreferenced file-scope
tables, no fixed absolute address above the declared segments, calls that already have names, and
plenty of DWARF line records.  Five units failed on exactly those shapes and cost 5½ hours
between them, so the screen's first job is to make those classes visible before anyone writes C.
It reads `config/ddrex2p/cus.json`,
`orig/SLUS_211.74`'s DWARF, `config/ddrex2p/symbol_addrs.txt`, `borrowed_symbols.txt`,
`unplaced_symbols.txt` and the splits under `asm/nonmatchings/main/`; it never compiles or links
anything.

**Second revision: a name is not a placeable name.**  The first ranking treated a call as fine
when its target merely *carried a name*, and ranked `network/net_sys/net_sys_connect.c` second
on a call to `NetRouterMain` — named, in `unplaced_symbols.txt` only, an overlay function no
layout places.  `compile.py` resolves a relocation against the unit's own functions or against
`symbol_addrs.txt` (plus the one `unplaced_symbols.txt` reason it reads as address 0); anything
else fails at `cc`, before any comparison.  The screen now scans every split's branch, call and
`%hi`/`%lo` operand against those ledgers and blocks on any target it cannot place.  That is
`unresolvable-callees`, the class `docs/unit-work.md`'s blocker table now records; the two
sub-cases are the **overlay boundary** (outside every declared segment; deferred by design) and
the **lookup gap** (a split the link places but `symbol_addrs.txt` lacks; a lookup bug).

**Third revision: `scalar` meant "no VU0", and that was not enough.**  The screen ranked
`eyetoy/eye_filter.c` #1 on the shape rule, and the unit turned out to be **unwritable in C at
all**: its `negaposi` is an EE 128-bit GPR xor (`pxor $4,$4,$7` / `pxor $3,$3,$7` over values
moved with `lq`/`sq`), and MWCC PS2 has **no 128-bit operators** — all five installed builds
reject `^ & | + - * ~ ^=` on `u_long128` with `Error: illegal data size`, for parameters,
locals, globals and dereferences alike.  `docs/unit-work.md`'s blocker table now records the
class and the compiler's own error text.  The screen reads each split for the 128-bit
*operations* and blocks on any (`128-bit-gpr`); the ranking below was regenerated with it.

The matching set is not "every `p…` mnemonic": `lq`, `sq` and `pcpyld` are what **legal**
`u_long128` C compiles to (assignment, and constant materialisation), and `eye_filter.c` proves
it in the tree — its neighbour `sepia` is expressible in C and contains `pcpyld` and `sq`.
Matching those would block every unit that merely moves 128-bit values.  `pref` is a prefetch
hint, and `lqc2`/`sqc2`/`qmtc2`/`qmfc2` stay the VU0 signal's.

**Fourth revision: the lookup gap was a bug in the reader, not a class.**  `compile.py` used to
resolve a relocation against `symbol_addrs.txt` alone, so a callee whose split the ld script
*does* place — `func_001C43E8`, called from `net_grf.c` — was refused while the link resolved it
happily.  `compile.py`'s `Manifests` now reads the link's whole symbol set: the split globals
under `asm/nonmatchings/<segment>` (bound to the address of the instruction after each label),
the `-T` files' assignments where this layout holds their address, and the ledger.  The screen
mirrors that in `load_link_placement`, and **53 units came out of the blocked list** on the
re-run — measured, not assumed.  What stays blocked is the **overlay boundary**: 141 targets
over 19 units whose address lies outside every declared segment (`net_sys_connect`'s
`NetRouterMain` is the first).  A name in *none* of the three sources is now its own refusal
(`no record anywhere`) and no unit in this tree has one.

**Fifth revision: an address with no name is not a constant.**  Every signal above looks up
*names* in a split's operands, and `net_game_help.c`'s eight operands carry none: retail's
`0x01029FE4`, `0x0102FACC` and `0x0102FE00-14` sit above every declared segment, written
`lui $1,(0x1030000 >> 16)` + `lw $3,-0x601C($1)` — the assembler's `lw rt, sym` expansion, `$1`
being `at`, one pair per access — so there was nothing to look up and nothing was flagged.  A C
*constant* is not that form: it compiles to `lui`+`ori` in an allocated register, which is why
`NetGameHelpDisp` came out 4 bytes short of retail's with 155 of 172 words different while
`.debug` and `.line` were *exact* in size and wrong only in values.  The screen now reads each
split's `lui`/`ori`/`addiu` chains and their memory bases (including a branch's delay slot, where
four splits in this tree keep their only such access) and blocks any load or store whose
effective address is above `bss_end` (`absolute-addresses`).  Measured at `ce7a75b`: **21 of the
57 candidates left the list**, 218 splits over 38 units carry the flag, and the ranking below is
the regenerated one.  The class it must *not* match is measured too: the `addu`-indexed spelling
of the same band is byte-identical to the assembler's large-displacement expansion
(`lui at,1; addu at,ptr,at; lw rt,-0x62E0(at)` is `ptr + 0x9D20`, a struct field), which C
reproduces — matching it would have blocked 9 more units that are writable.

Of 249 translation units, **2 are promoted** (`sys/sys_scf.c` and `network/net_grf.c`), **36 are
unblocked candidates**, and 211 are blocked (the categories below overlap): 67 overlay units have
no retail split in this target, 1 is a library object, 19 carry a target outside every declared
segment, 38 carry a fixed absolute address above the declared segments, 1 carries EE 128-bit GPR
operations, and the remainder carry one of the other shape classes.

## Ranking

Scores are a tie-break among unblocked units, not a probability.  `score = 100 - 6·(functions-1)
- 25·unresolvable targets - calls/name penalties - FPU tax - 0.02·array DIEs +
min(10, line records per function)`, with a +2 bonus at 20 statements.  The unresolvable term is
a courtesy for the printed order, not the mechanism: such a unit is `blocked` and never reaches
the candidate list.  Every term is printed in the last column, so a reader can disagree with the
weights without losing the evidence.

| rank | unit | score | functions | line records | why expected easy |
|---:|---|---:|---:|---:|---|
| 1 | `AM/s573/doll/dexport.c` | 98.7 | 2 | 31 | 2 functions; 31 line records (15.5/function); calls: 0 borrowed, 3 named, 0 internal; 115 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 2 function(s) in cus.json |
| 2 | `CS/dancemaster/dmm_chara.c` | 97.4 | 1 | 32 | 1 function; 32 line records (32.0/function); calls: 0 borrowed, 9 named, 0 internal; 80 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 1 function(s) in cus.json |
| 3 | `common/com_scrollbar.c` | 95.0 | 1 | 80 | 1 function; 80 line records (80.0/function); calls: 0 borrowed, 0 named, 0 internal; no array/table risk; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1 FPU function(s); declared 1 function(s) in cus.json |
| 4 | `common/co_cursor.c` | 94.5 | 2 | 99 | 2 functions; 99 line records (49.5/function); calls: 1 borrowed, 0 named, 0 internal; no array/table risk; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1 FPU function(s); declared 2 function(s) in cus.json |
| 5 | `network/mio/md5.c` | 89.9 | 4 | 484 | 4 functions; 484 line records (121.0/function); calls: 0 borrowed, 0 named, 4 internal; 6 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 4 function(s) in cus.json |
| 6 | `common/com_keyboard.c` | 82.8 | 3 | 207 | 3 functions; 207 line records (69.0/function); calls: 0 borrowed, 0 named, 0 internal; 11 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1 FPU function(s); declared 3 function(s) in cus.json |
| 7 | `AM/s573/doll/model1.c` | 77.3 | 5 | 126 | 5 functions; 126 line records (25.2/function); calls: 0 borrowed, 3 named, 4 internal; 37 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1 FPU function(s); declared 5 function(s) in cus.json |
| 8 | `CS/opening/openinglogo.c` | 76.9 | 4 | 64 | 4 functions; 64 line records (16.0/function); calls: 0 borrowed, 0 named, 0 internal; 4 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1 FPU function(s); declared 4 function(s) in cus.json |
| 9 | `AM/s573/play/p_anime.c` | 73.2 | 5 | 239 | 5 functions; 239 line records (47.8/function); calls: 0 borrowed, 14 named, 0 internal; 39 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 5 function(s) in cus.json |
| 10 | `CS/dancemaster/dmm_mess.c` | 70.0 | 3 | 88 | 3 functions; 88 line records (29.3/function); calls: 0 borrowed, 10 named, 1 internal; 49 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1 FPU function(s); declared 3 function(s) in cus.json |
| 11 | `CS/shop/shop_main.c` | 66.0 | 6 | 53 | 6 functions; 53 line records (8.8/function); calls: 0 borrowed, 6 named, 0 internal; 41 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 6 function(s) in cus.json |
| 12 | `CS/shop/shop_list.c` | 65.2 | 7 | 233 | 7 functions; 233 line records (33.3/function); calls: 0 borrowed, 3 named, 6 internal; 88 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 7 function(s) in cus.json |
| 13 | `common/cws/cws_wins.c` | 64.8 | 7 | 133 | 7 functions; 133 line records (19.0/function); calls: 0 borrowed, 7 named, 0 internal; 12 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 7 function(s) in cus.json |
| 14 | `CS/shop/shop_info.c` | 63.8 | 4 | 113 | 4 functions; 113 line records (28.2/function); calls: 0 borrowed, 16 named, 2 internal; 9 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 4 function(s) in cus.json |
| 15 | `AM/s573/doll/matrix.c` | 63.6 | 5 | 41 | 5 functions; 41 line records (8.2/function); calls: 3 borrowed, 0 named, 0 internal; 4 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 5 FPU function(s); declared 5 function(s) in cus.json |
| 16 | `CS/dancemaster/dmm_mc.c` | 55.9 | 5 | 100 | 5 functions; 100 line records (20.0/function); calls: 0 borrowed, 5 named, 0 internal; 153 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 5 function(s) in cus.json |
| 17 | `AM/s573/doll/ps1lib.c` | 50.4 | 8 | 129 | 8 functions; 129 line records (16.1/function); calls: 9 borrowed, 0 named, 0 internal; 4 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 5 FPU function(s); declared 8 function(s) in cus.json |
| 18 | `CS/edit/ed_ssq_func.c` | 44.9 | 11 | 140 | 11 functions; 140 line records (12.7/function); calls: 0 borrowed, 0 named, 3 internal; 5 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1 FPU function(s); declared 11 function(s) in cus.json |
| 19 | `CS/shop/shop_select.c` | 43.8 | 5 | 295 | 5 functions; 295 line records (59.0/function); calls: 0 borrowed, 76 named, 4 internal; 9 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; scalar; declared 5 function(s) in cus.json |
| 20 | `AM/s573/doll/motion2.c` | 42.3 | 8 | 346 | 8 functions; 346 line records (43.2/function); calls: 3 borrowed, 20 named, 32 internal; 12 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 2 FPU function(s); declared 8 function(s) in cus.json |

Two of the three units the link fix freed first are still ranks 1–3 (`AM/s573/doll/dexport.c`,
blocked on `func_001BED10`, and `CS/dancemaster/dmm_chara.c`, `func_00128600`/`func_0012CD70`);
the third, `network/net_grf.c`, was promoted at `8d9a7bd` and left the list, which is why the
table above has 20 rows from a 36-unit candidate list.  `eyetoy/eye_filter.c` — the 128-bit
unit — is not here; it is the row the 128-bit block keeps out.  Neither is
`network/net_game/net_game_help.c`, which the fifth revision blocks on its eight unnamed
addresses; the row moved from rank 6 to the blocked list with its reason printed under `--all`.

`calls: 0 borrowed, 12 named, ...` means every call target already carries a `symbol_addrs`
record, so no name has to be imported mid-unit.  Distinct unresolvable targets are not a
scoring term a reader has to weigh: a unit with any is blocked and printed under `--all` with
the target's name, its address, and which of the two refusals it is.

### The top three, in one line each

* `AM/s573/doll/dexport.c` — two functions, three already-named calls, 31 statement lines, no
  file-scope table; the unit UnitC measured to 96.2% on `ps2dancerInitHide` and blocked on one
  `nop` and a name the ledger did not carry, now rank 1.
* `CS/dancemaster/dmm_chara.c` — one function, nine named calls, 32 statement lines: the
  shortest function list in the ranking, and the unit whose two absent targets
  (`func_00128600`, `func_0012CD70`) were the fourth callee finding; it moved up one place when
  `net_grf.c` was promoted.
* `common/com_scrollbar.c` — one function, 80 line records (80.0 per function, the densest line
  table in the top three), **no calls at all** and no array/table risk; its only tax is the one
  FPU function.

The first unit that did promote (`sys_scf.c`) scores **97.5** on the same formula (2
functions, 4 line records per function, one borrowed call), which is the calibration the
weights were set against: the top candidates are the units whose measured shape is at least
as clean as the one that worked.

## Validation: the callee failures, before and after the link fix

The previous ranking's #2, #3, #4 and #5 all scored on calls the promotion path "could not
resolve".  That section's table is kept as the record of what the screen was *supposed* to
catch, but the class split in two, and only one half was real:

| previous rank | unit | new flags | reason printed by the screen | known fact |
|---:|---|---|---|---|
| 2 | `network/net_sys/net_sys_connect.c` | `unresolvable-callees` | `D_008062B0` (NetRouterMain) at `0x8062B0`: outside every declared segment (overlay boundary) | `NetRouterMain` is in `unplaced_symbols.txt` only; the pointer is materialised with `%hi`/`%lo`, not a `jal` |
| 3 | `AM/s573/doll/dexport.c` | *(none)* | — | `func_001BED10` has a split, and the ld script places that split: the refusal was the reader's |
| 4 | `network/net_grf.c` | *(none)* | — | `func_001C43E8` likewise; this unit's refusal is what `c2dd80e` was written to fix |
| 5 | `CS/dancemaster/dmm_chara.c` | *(none)* | — | `func_00128600`, `func_0012CD70`: the same lookup gap |
| 1 | `eyetoy/eye_filter.c` | `128-bit-gpr` | `1 function(s) use EE 128-bit GPR operations (pxor) ...` | unblocked then; blocked now, on the 128-bit class, not on a name |

The same split shows up on `CS/edit_lib/el_mes.c`: its one call names `func_00192F30`, a
split-only name, so the `unresolvable-callees` reason is gone and only the `large-tables`
reason remains.

### The link fix's payoff, measured

After `compile.py` grew the link's symbol set (`c2dd80e`) and the screen mirrored it in
`load_link_placement`, the re-run moved:

| | before | after | Δ |
|---|---:|---:|---:|
| unblocked candidates | 5 | **58** | +53 |
| blocked units | 243 | **190** | −53 |
| units flagged `unresolvable-callees` | 142 | **19** | −123 |
| flagged targets: in-segment lookup gaps | 1,146 | **0** | −1,146 |
| flagged targets: outside every declared segment | 141 | **141** | 0 |

**53 units came out of the blocked list and none went in**, exactly the 1,146 in-segment
lookup-gap targets and nothing else; the 141 overlay-boundary targets over 19 units are
untouched, which is the half the parent starves by design until the overlay milestone models
those segments.  A third bucket exists and is empty: a name in no split, no ledger and no `-T`
file (`no record anywhere`) would be a genuine finding, and no unit in this tree has one.

## Validation: the four earlier shape failures

The 128-bit class is the fifth, and has its own section below because it moved a candidate;
these four were the state before it.

The screen is only useful if it also sees the classes that cost the 4½ hours.  It does:

| unit | flags | reason printed by the screen | matches the recorded failure |
|---|---|---|---|
| `sys/sys_demo.c` | `unreferenced-arrays` | `2 array DIE(s) nothing references: unsigned char *[6] @0x2FE, unsigned char [256] @0x5FD` | exactly the two DIEs and offsets recorded in `1accb6e`; 75 B shortfall |
| `CS/lang.c` | `unreferenced-tables`, `array-die-order` | `8 file-scope table(s) no function references ...; 9 array tables / 9 array DIEs: array-DIE order is compiler-table order, not declaration order` | `e1a9748`'s two independent `.debug` mismatches: variable order and the nine array DIEs |
| `CS/edit_lib/el_mes.c` | `large-tables`, `unresolvable-callees` | `1 large file-scope table(s) (the mes_* debug-order class): el_message_str_e (716 B)`; `func_00192F30 ... no symbol_addrs record` | the `mes_*` table class plus the unnamed helper in `unit-a-report.md` |
| `AM/s573/doll/vu0.c` | `vu0` | `3 function(s) use VU0 macro-mode operations (the .vutext blocker, inferred; section names are stripped)` | the VU0 unit; its splits open with `lqc2`/`ctc2`/`vmulax` |

The `mes_*` siblings are caught too: `CS/cmes_e.c`, `cmes_j.c`, `cmes_js.c` and `cmes_js2.c`
are `data-only` with 84/83/73/73 `unreferenced-tables`; `net_auth_mes_e.c`,
`net_cnf_mes_e.c`, `net_router_mes_e.c`, `net_dnas_mes_e.c` and `workout_message.c` carry the
table/array-order flags.

## Validation: the 128-bit class

The previous #1 was the unit that made this signal necessary, so it is also its acceptance
test.  Measured on the tree as it stood then (commit `1e9c192`, before the link fix of
`c2dd80e` reached the ranking), the change moved exactly **one** unit and touched nothing else:

| | before | after |
|---|---:|---:|
| unblocked candidates | 6 | **5** |
| blocked units | 242 | **243** |
| units flagged `128-bit-gpr` | 0 | **1** |

| unit | before | after | reason printed by the screen |
|---|---|---|---|
| `eyetoy/eye_filter.c` | rank 1, score 106.0, unblocked | `blocked`, `128-bit-gpr` | `1 function(s) use EE 128-bit GPR operations (pxor): MWCC has no 128-bit operators, so no C expression produces them (the 128-bit blocker class; inline asm is the only route, and that is a probe rather than a promotion)` |

Every other candidate kept its score and its `good` reasons apart from the new `no 128-bit GPR
ops` term — the evidence that the signal did not leak into units that merely move 128-bit
values: `sepia`, in the blocked unit itself, compiles from C and contains `pcpyld` and `sq`.
Across 4,491 splits in 249 units, exactly one unit matches the operation set.  On the merged
tree below, the flag costs `eye_filter.c` its place in the candidate list while the link fix
frees 53 other units around it.

## Validation: the out-of-segment address class

The finding is UnitF's (`unit-f-report.md`), and the acceptance test is the six units of the
ranking the finding was made against (`78ae234`: `eyetoy/eye_filter.c` #1, `net_game_help.c` #2,
`p_anime.c` #3, `net_inter.c` #4, `ps1lib.c` #5, `motion2.c` #6).  Measured on the regenerated
screen, the two units that carry the class are caught, the four that do not are untouched:

| unit | then | flag now | detail |
|---|---|---|---|
| `network/net_game/net_game_help.c` | rank 2 | `absolute-addresses` | 8 addresses in the `0x01029FD0`/`0x0102FFCC` bands, from **2 of 2** functions: `0x01030000 (NetGameHelpDisp: lw $3,-0x601C($1) -> 0x01029FE4)` — the eight fields UnitF measured |
| `network/net_inter.c` | rank 4 | `absolute-addresses` | 1 address (`0x01029FDC`), from **7 of 7** functions |
| `eyetoy/eye_filter.c` | rank 1 | *(none)* | carries only `128-bit-gpr`, the class that already blocked it; no address flag |
| `AM/s573/play/p_anime.c` | rank 3 | *(none)* | `flags=[]`, still a candidate — the unit UnitF handed on as clear of the class |
| `AM/s573/doll/ps1lib.c` | rank 5 | *(none)* | `flags=[]`, still a candidate |
| `AM/s573/doll/motion2.c` | rank 6 | *(none)* | `flags=[]`, still a candidate |

The re-run's full effect, at `ce7a75b` (where `net_grf.c` had just been promoted, so the
starting list is 57 rather than the 58 of the ranking the finding quotes):

| | before | after |
|---|---:|---:|
| unblocked candidates | 57 | **36** |
| blocked units | 190 | **211** |
| units flagged `absolute-addresses` | 0 | **38** |
| splits flagged (of 4,491 in 249 units) | 0 | **218** |
| distinct addresses reported | 0 | **207** |

**21 units left the candidate list and none entered it** — measured as a set difference against
the same tree with the previous `screen.py`, which is the same 21 at the 58-candidate ranking
(58 → 37).  The flag does not disturb the scores of the units that stay: every row keeps its
`score` and gains one `good` clause (`no fixed absolute addresses`), so the only ordering change
is the shrink itself.  The units it moves are exactly the 21 whose only flag is this one —
eleven `net_game_*` units (`help`, `challenge`, `data`, `list`, `logout`, `main`, `match`,
`opt`, `prac`, `prg`, `rc`), six `net_sys_*` units (`info`, `logout`, `main`, `menu`, `new`,
`rule`), `net_inter.c`, `net_read_data.c`, `CS/bk_disp/bk_disp_sub.c` and
`common/co_movie.c`.  The other 17 rows the flag lands on were blocked already
(`net_prg.c`, `net_main.c`, the five `net_win_per*` units, `net_game_vs.c`/`vs_win.c`/
`window.c`/`menu.c`, `net_sys_lobby.c`/`user.c`/`top.c`, `net_type.c`, `net.c`,
`title_demo.c`), which is why the candidate list shrinks by 21 and not by 38.

**The one false positive this signal had is recorded, because it was measured and removed.**
An earlier draft also matched the `addu`-indexed spelling of the same band (`lui $1,(0x1030000
>> 16)`; `addu $1, $2, $1`; `lh $3,-0x6350($1)`) and blocked 9 more units — `fft/fft_disp.c`
and `CS/shop/shop_obj.c` (both candidates with no other flag) plus `AM/s573/doll/dinit.c`,
`CS/freeplay/fp_chara.c`, `fp_msel.c`, `fp_msel_obj.c`, `fp_res.c`, `CS/dancemaster/dmm_func.c`
and `AM/s573/play/onimode.c`.  Inspecting them showed the shape is ambiguous against the
assembler's large-displacement expansion: `lui at,1; addu at,ptr,at; lw rt,-0x62E0(at)` is
`ptr + 0x9D20`, an ordinary struct field that C reproduces byte for byte, and the constants those
units use (`0x10000`/`0x20000`/`0x30000`/`0xB0000`/`0xE0000`) sit *below* `loadable_vram`, where
as absolute addresses nothing in the game's link would be.  The narrower match kept the 21 that
are unambiguous and dropped the 9 that are not.  The three splits that use the band this way
(`NetPadCon`, `NetReadDataGetStr`, `NetGamePrgGetWinLoseDraw`) are named under "what the signal
cannot see" below rather than blocked on a guess.

## What the signal cannot see

* **A 128-bit value assembled from the expressible subset.**  `lq`, `sq` and `pcpyld` are
  deliberately not matched, so a unit that only moves 128-bit values looks clean — see the
  block above for why matching them would be worse.  The signal sees the *operations*, not the
  data flow: a unit whose stored value needs an operation the compiler lacks is only caught if
  the operation itself appears.
* **Whether the unit has a CU at all.**  The signal is per DWARF translation unit, and 84 of
  the 85 splits in this tree that carry these opcodes belong to functions the DWARF does not
  describe (engine and overlay code, already blocked as `overlay`/`missing-dwarf`).  The
  attribution gap is structural: an opcode in a split with no function DIE cannot be charged to
  a unit, so the flag would be silent if such a unit ever became a candidate.
* **Opcodes outside the list.**  The set is the EE `p…`/`qfsrv` operation families, cross-checked
  against every split in this disc (the 40 mnemonics actually present are all matched except the
  three excluded ones).  An operation that appears in no split here and is missing from the list
  would slip; the reverse error is the cheap one, as above.
* **Indirect calls and computed targets.**  `jalr $3` and `jr $3` name no symbol, so a unit whose
  only foreign dependency is a call through a register — a function pointer loaded out of a data
  table, a `switch` jump table rendered as `jr` — looks clean.  `NetRouterMain` was caught only
  because its *address* was materialised with `%hi`/`%lo` in the same function; the identical
  dependency through `lw $3, %lo(tbl)($1); jalr $3` would not be flagged.
* **Data-only dependencies.**  An unknown `D_XXXXXXXX` operand that has no unplaced function
  record is deliberately ignored: it is usually an unnamed view of a symbol the ledger *does*
  have (`D_006B2F58` is inside `g_game_w`, which is recorded at `0x00607A70`).  A unit whose only
  unresolved relocation is such a datum is ranked as unblocked and can still fail at `cc`; the
  split text does not say whether the C would reference it through its named parent.
* **The link's symbol set, only as far as `compile.py` reads it.**  The screen mirrors
  `Manifests` — the split labels, the `-T` assignments this layout holds an address for, the
  ledgers — instead of running `ld`.  If the ld script grows a construct the two readers
  disagree on, the screen is wrong in the pessimistic direction and a placeable unit stays
  blocked until somebody looks.  The overlay half is a refusal by design, not a blind spot:
  this layout holds no address for those windows, so no reader can place them.
* **Reachability.**  The signal flags a target's *presence* in the split, not whether the C has
  to emit the relocation.  Dead retail code behind an unconditional return still blocks.
* **`.vutext` membership directly.**  This retail ELF's section headers are stripped (the only
  named sections are `.debug`, `.line`, `.comment`, `.reginfo` and the string tables), so
  "lands in `.vutext`" is inferred from VU0 macro-mode instructions in the unit's split.
* **A right-length, wrong-bytes `.debug` block.**  The screen predicts blockers from shape; it
  cannot compare DIE bytes without compiling.
* **Shape conflicts.**  A unit needing two mutually exclusive C shapes has no signature in the
  DWARF; it is discovered only by trying both.
* **Inline/macro provenance and statement *content*.**  Line records are counted per function;
  whether the original statements can be recovered from them is not modelled.
* **The exact array-DIE order.**  The screen flags the class when a unit carries ≥2 file-scope
  array tables, but it cannot say whether a given unit's compiler table will happen to agree.
* **Data-only units in the overlays.**  All 67 overlay units already carry `overlay`/`no retail
  split`; the screen deliberately does not pretend to rank them.
* **The `addu`-indexed spelling of the band.**  Three splits reach the band only as
  `lui $1,(0x1030000 >> 16)` + `addu $1, $idx, $1` + a load (`NetPadCon`,
  `NetReadDataGetStr`, `NetGamePrgGetWinLoseDraw`).  That shape is not separable from the
  assembler's large-displacement expansion over a register, which C reproduces, so those units
  read as unblocked instead of being guessed at; telling the two apart needs the unit's own C.
* **An address passed rather than dereferenced.**  `NetGameChallengeMain` materialises
  `0x0102FFD0` into `$4` (`lui $2,(0x102FFD0 >> 16)`; `ori $4,$2,0xFFD0`) and passes it to a
  call, never using it as a base — the same unmatchable class for the C, and not reported (that
  unit is caught anyway, by the delay-slot store at `0x0102FFCC`).
* **Addresses below `loadable_vram`.**  Deliberately unmatched: that is where the displacement
  expansion lives, and nothing below the image was measured as a memory base in this tree.

### What a false positive costs

The signal is deliberately biased toward blocking, because the two errors are not symmetric.  A
false negative costs an agent its whole box (the unit never reaches a comparison, as happened
four times in a row).  A false positive costs one line in `--all`: the unit sinks to the same
blocked list as the overlay, VU0 and `mes_*` classes, with the target's name and address
printed, so a reader can overrule it in seconds.  The one false positive this signal ever had
(the transient lookup gap above) is gone with the fix that closed it: the screen now reads the
same three sources `compile.py` does, and the 19 units still flagged are all the overlay
boundary, which is a refusal by design rather than an error.

For the 128-bit signal the bias runs the other way on purpose, and the false positive has a
named shape.  Matching `lq`/`sq`/`pcpyld` would have blocked **every** unit that moves a
`u_long128` value — starting with `sepia`, the C-writable half of the very unit the class was
found on — so those three are excluded and the cost is a false *negative*: a unit that only
assigns 128-bit values is ranked as clean.  What is matched is the operation set, and a false
positive there means an opcode that MWCC can in fact emit from C; the screen has no way to
prove the negative without compiling, so the list is evidence-driven (the compiler probes in
`docs/unit-work.md`) and printed per row with the opcodes it matched, which is what a reader
needs to overrule it.  Measured today the class has no false positive at all: across 4,491
splits in 249 units, exactly one unit matches, and it is the unit that cannot be written.

## What I would add next if this proves too coarse

1. **A dependency closure, not a block**: resolve each `func_` callee to the unit that owns it,
   so a wave can pick a closure of units together rather than flags failing on names.  The
   lookup-gap case is the first instance of this paying off.
2. **Per-function screening**: the unit score hides a unit with one easy function and one
   pathological one.
3. **A DIE-shape model**: capture, per TU, the types block's DIE tag sequence and compare it to
   what the candidate C would produce once compiled.
4. **Statement-gap histogram**: line records per function plus the largest line gap, because a
   large gap is where an inline hides.
5. **Indirect-target recovery**: read the `%hi`/`%lo` pair that feeds a `jalr` register when it
   is in the same basic block, so the `NetRouterMain` case is caught structurally rather than
   only because splat happened to render the pointer itself.
6. **Make the thresholds measured rather than chosen** (`LARGE_TABLE_BYTES = 256`,
   `ARRAY_ORDER_TABLES = 2`, the 25-point unresolvable term): once a few screened units are
   promoted, fit the weights against observed time-to-green.
