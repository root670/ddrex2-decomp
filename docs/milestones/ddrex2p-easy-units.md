# Easy units on `ddrex2p`, ranked by shape

Generated with:

```bash
python3 tools/units/screen.py --markdown --top 20
python3 tools/units/screen.py --all --top 60   # the blocked rows, with reasons
```

The rule this implements is `docs/unit-work.md`'s "Pick a unit by shape, not by size": few
functions, scalar code, no VU0, no EE 128-bit GPR operations, no fixed absolute address above the declared
segments, calls that already have names, plenty of DWARF line records, and little absolute
`.text` (no single enormous function).  The large/unreferenced-table classes are now warnings:
`--adopt-retail-meta` handles `.debug`-only differences once `.text` is byte-identical.  Five units failed on exactly those shapes and cost 5½ hours
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

**Sixth revision: promotion-aware, `.debug`-only risks demoted, size scored.**  Three changes
follow the adoption pipeline (`compile.py --adopt-retail-meta`).  First, a unit is **excluded**
from every row -- candidates, `--all` and `--json` -- when it has both a committed `src/<unit>`
source and a `tu_builds` row.  Five are in that state: `sys/sys_scf.c`, `network/net_grf.c`,
`AM/s573/play/p_anime.c`, `CS/lang.c` and `CS/dancemaster/dmm_chara.c`.  A source without a row
is a half-landed promotion and stays listed with a `source-unbuilt` warning; a row without a
source cannot build and is not promoted either.

Second, the array/table shape classes moved from blockers to warnings.  Adoption requires
`.text` to be byte-identical, then proves retail's `.debug` and `.line` chunk: it normalises
retail's DIE order, adopts retail's `AT_location` values and `.line`, drops *our* extra DIEs and
adopts attributes retail carries.  So `large-tables`, `unreferenced-tables` and
`array-die-order` no longer say a unit is unpromotable -- they say its `.debug` will need
adoption.  `unreferenced-arrays` stays a blocker: those are DIEs *retail has and we do not*, and
adoption refuses to fabricate a missing record.  The `.text`-shaped blockers are unchanged:
VU0, 128-bit GPR operations, out-of-segment fixed addresses, unresolvable callees (the overlay
boundary included), overlay units and missing splits.

Third, size is now scored.  A unit is replicated instruction by instruction, so counting
functions alone ranked one 4 KiB function as easier than three small ones.  The screen reads
each split's `nonmatching` line for its byte size (falling back to one instruction line = 4
bytes when splat printed no size, and to the DWARF function extent if the block name does not
match) and records the unit's total `.text` and its largest function.  The score terms are
exactly `-0.5` per KiB of total `.text` and `-3.0` per KiB of the largest function above a free
1 KiB; both are printed in every row, and the `.text`/largest columns are below.

Of 249 translation units, **5 are promoted** and excluded outright, **105 are unblocked
candidates**, and **139 are blocked** (the categories overlap): 67 overlay units have no retail
split in this target, 66 have missing splits (mostly the same overlays), 38 carry a fixed
absolute address above the declared segments, 19 carry a call/branch target outside every
declared segment, 16 carry unreferenced array DIEs, 10 are data-only, 3 carry VU0, 1 carries EE
128-bit GPR operations and 1 is a library object.  The demoted table classes are now warnings on
candidates too: 120 units carry `array-die-order`, 71 `unreferenced-tables` and 57
`large-tables`, and none of them blocks.

## Ranking

Scores are a tie-break among unblocked units, not a probability.  `score = 100 - 6·(functions-1)
- 25·unresolvable targets - 2·placeholder calls - 1·named calls - 0.5·borrowed calls -
3·FPU functions - 0.02·array DIEs - 0.5·(total .text KiB) - 3.0·max(0, largest function KiB -
1) + min(10, line records per function)`, with a +2 bonus at 20 statements.  The unresolvable
term is a courtesy for the printed order, not the mechanism: such a unit is `blocked` and never
reaches the candidate list.  The array term is a tie-break; the demoted table warnings do not
enter the score.  Every term is printed in the last column, so a reader can disagree with the
weights without losing the evidence.  The size columns are the split's `nonmatching` bytes:
`-0.5/KiB` charges the unit's whole `.text`, and `-3.0/KiB` charges only the largest function's
bytes above 1 KiB.

| rank | unit | score | functions | .text bytes | largest fn | line records | why expected easy |
|---:|---|---:|---:|---:|---|---:|---|
| 1 | `CS/edit_lib/el_mes.c` | 106.0 | 1 | 56 | 56 | 8 | 1 function; 8 line records (8.0/function); calls: 0 borrowed, 0 named, 0 internal; 1 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 56 B .text, largest el_get_message_str 56 B; scalar; declared 1 function(s) in cus.json |
| 2 | `network/net_dnas/net_dnas_mes_e.c` | 103.5 | 2 | 424 | 368 | 40 | 2 functions; 40 line records (20.0/function); calls: 0 borrowed, 0 named, 0 internal; 12 array DIE(s), 10 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 424 B .text, largest ndmesMakeDNASErrorMessage 368 B; scalar; declared 2 function(s) in cus.json |
| 3 | `network/mio/blowfish.c` | 99.5 | 3 | 816 | 456 | 82 | 3 functions; 82 line records (27.3/function); calls: 0 borrowed, 0 named, 2 internal; 6 array DIE(s), 2 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 816 B .text, largest Blowfish_Init 456 B; scalar; declared 3 function(s) in cus.json |
| 4 | `sound/vxdecode/decode.c` | 98.7 | 3 | 1244 | 1188 | 145 | 3 functions; 145 line records (48.3/function); no calls; 9 array DIE(s), 9 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1244 B .text, largest decodeVAG 1188 B; scalar; declared 3 function(s) in cus.json |
| 5 | `AM/s573/doll/dexport.c` | 98.5 | 2 | 456 | 344 | 31 | 2 functions; 31 line records (15.5/function); calls: 0 borrowed, 3 named, 0 internal; 115 array DIE(s), 0 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 456 B .text, largest ps2dancerGetDollList 344 B; scalar; declared 2 function(s) in cus.json |
| 6 | `CS/bk_load.c` | 96.9 | 2 | 116 | 64 | 14 | 2 functions; 14 line records (7.0/function); calls: 0 borrowed, 0 named, 0 internal; 1 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 116 B .text, largest sysSetMusicBk 64 B; scalar; declared 2 function(s) in cus.json |
| 7 | `music_all.c` | 95.8 | 3 | 296 | 152 | 24 | 3 functions; 24 line records (8.0/function); calls: 0 borrowed, 0 named, 0 internal; 1 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 296 B .text, largest GetMusicData_by_base_name 152 B; scalar; declared 3 function(s) in cus.json |
| 8 | `CS/train/tra_str.c` | 95.5 | 3 | 464 | 324 | 35 | 3 functions; 35 line records (11.7/function); calls: 0 borrowed, 1 named, 0 internal; 15 array DIE(s), 14 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 464 B .text, largest Tr_bar_digit_disp 324 B; 1 FPU function(s); declared 3 function(s) in cus.json |
| 9 | `common/co_cursor.c` | 93.8 | 2 | 1140 | 1084 | 99 | 2 functions; 99 line records (49.5/function); calls: 1 borrowed, 0 named, 0 internal; no array/table risk; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1140 B .text, largest co_cursor01_disp 1084 B; 1 FPU function(s); declared 2 function(s) in cus.json |
| 10 | `network/net_auth/net_auth_errmes_e.c` | 93.4 | 3 | 672 | 248 | 87 | 3 functions; 87 line records (29.0/function); calls: 0 borrowed, 0 named, 0 internal; 12 array DIE(s), 9 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 672 B .text, largest namesMakeAuthMessage 248 B; scalar; declared 3 function(s) in cus.json |
| 11 | `common/com_scrollbar.c` | 93.4 | 1 | 1344 | 1344 | 80 | 1 function; 80 line records (80.0/function); calls: 0 borrowed, 0 named, 0 internal; no array/table risk; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1344 B .text, largest ComScrollBarDisp 1344 B; 1 FPU function(s); declared 1 function(s) in cus.json |
| 12 | `network/net_cnf/net_cnf_mes_e.c` | 90.1 | 3 | 80 | 56 | 8 | 3 functions; 8 line records (2.7/function); no calls; 26 array DIE(s), 26 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 80 B .text, largest ncmesGetMessageTable 56 B; scalar; declared 3 function(s) in cus.json |
| 13 | `network/net_auth/net_auth_mes_e.c` | 89.8 | 3 | 80 | 56 | 8 | 3 functions; 8 line records (2.7/function); no calls; 39 array DIE(s), 39 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 80 B .text, largest namesGetMessageTable 56 B; scalar; declared 3 function(s) in cus.json |
| 14 | `network/net_window/net_win_infoboard.c` | 84.5 | 4 | 196 | 104 | 15 | 4 functions; 15 line records (3.8/function); calls: 0 borrowed, 1 named, 0 internal; 9 array DIE(s), 4 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 196 B .text, largest NetWin_Infoboard 104 B; scalar; declared 4 function(s) in cus.json |
| 15 | `network/net_window/net_win_any.c` | 83.6 | 5 | 500 | 144 | 45 | 5 functions; 45 line records (9.0/function); calls: 0 borrowed, 3 named, 0 internal; 8 array DIE(s), 3 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 500 B .text, largest NetWin_AnyInit 144 B; scalar; declared 5 function(s) in cus.json |
| 16 | `CS/ani_load.c` | 81.6 | 4 | 224 | 104 | 22 | 4 functions; 22 line records (5.5/function); calls: 0 borrowed, 1 named, 0 internal; 39 array DIE(s), 2 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 224 B .text, largest sysReadAnimeWait2 104 B; scalar; declared 4 function(s) in cus.json |
| 17 | `common/co_button.c` | 79.3 | 2 | 1152 | 576 | 142 | 2 functions; 142 line records (71.0/function); calls: 0 borrowed, 0 named, 0 internal; 8 array DIE(s), 2 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1152 B .text, largest co_button_explain_disp 576 B; 2 FPU function(s); declared 2 function(s) in cus.json |
| 18 | `common/com_keyboard.c` | 78.2 | 3 | 2640 | 2136 | 207 | 3 functions; 207 line records (69.0/function); calls: 0 borrowed, 0 named, 0 internal; 11 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 2640 B .text, largest ComKeyBoardDisp 2136 B; 1 FPU function(s); declared 3 function(s) in cus.json |
| 19 | `network/net_window/net_win_listbk.c` | 77.7 | 5 | 1668 | 1472 | 114 | 5 functions; 114 line records (22.8/function); calls: 0 borrowed, 1 named, 0 internal; 11 array DIE(s), 4 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 1668 B .text, largest CwsWin_ListbkDisp 1472 B; 1 FPU function(s); declared 5 function(s) in cus.json |
| 20 | `network/mio/md5.c` | 77.6 | 4 | 5128 | 4376 | 484 | 4 functions; 484 line records (121.0/function); calls: 0 borrowed, 0 named, 4 internal; 6 array DIE(s), 1 file-scope table(s), all referenced; no VU0; no 128-bit GPR ops; no fixed absolute addresses; 5128 B .text, largest MD5Transform 4376 B; scalar; declared 4 function(s) in cus.json |

### What moved

Eight of the new top ten were blocked by exactly the demoted `.debug` classes before this
revision: `el_mes.c`, `net_dnas_mes_e.c`, `bk_load.c`, `music_all.c` (large or unreferenced
tables), `blowfish.c`, `decode.c`, `net_auth_errmes_e.c` and `tra_str.c` (array-DIE order).
The other two, `dexport.c` and `co_cursor.c`, were already candidates and moved 1→5 and 4→9 as
the entrants and the size term displaced them.

| old rank | unit | now | cause |
|---:|---|---|---|
| 1 | `AM/s573/doll/dexport.c` | 5 (98.5) | entrants; `-0.2` size |
| 2 | `CS/dancemaster/dmm_chara.c` | **excluded** | promoted (`tu_builds` row) |
| 3 | `common/com_scrollbar.c` | 11 (93.4) | entrants; `-1.6` size |
| 4 | `common/co_cursor.c` | 9 (93.8) | entrants; `-0.6` size |
| 5 | `network/mio/md5.c` | 20 (77.6) | entrants; `-12.4` size (4,376 B function) |
| 6 | `common/com_keyboard.c` | 18 (78.2) | entrants; `-4.6` size (2,136 B function) |
| 7 | `AM/s573/doll/model1.c` | 21 (76.7) | entrants; size |
| 8 | `CS/opening/openinglogo.c` | 22 (76.6) | entrants; size |
| 9 | `AM/s573/play/p_anime.c` | **excluded** | promoted (`tu_builds` row) |
| 10 | `CS/dancemaster/dmm_mess.c` | 27 (69.4) | entrants; size |
| 11–20 | (all ten remaining) | 30, 34, 33, 36, 35, 43, 49, 54, 55, 57 | entrants; size |

`network/mio/md5.c` is the size signal's clearest case: it has four functions and, before this
revision, ranked 5th (89.9); its `MD5Transform` is 4,376 B, so the two size terms cost it 12.4
points and it falls to 20th.  `common/com_keyboard.c` pays 4.6 points for its 2,136 B display
function.  The units that did *not* grow keep their old score minus only their size term:
`dexport.c`'s 456 B costs 0.2 points, `co_cursor.c`'s 1,140 B costs 0.6.

## Blocked rows (`--all`, regenerated)

`python3 tools/units/screen.py --all --top 60` prints all 139 blocked rows with every reason.
The classes (overlapping) are: `overlay` 67, `missing-splits` 66, `absolute-addresses` 38,
`unresolvable-callees` 19, `unreferenced-arrays` 16, `data-only` 10, `vu0` 3, `128-bit-gpr` 1,
`library` 1.  The highest-scoring blocked rows are:

| unit | flags |
|---|---|
| `eyetoy/eye_filter.c` | `128-bit-gpr` |
| `AM/s573/play/oni_list.c` | `data-only`, `large-tables`, `unreferenced-tables` |
| `CS/dancemaster/dmm_subject.c` | `overlay`, `data-only`, `large-tables`, `unreferenced-tables` |
| `CS/lesson/kn_lmsg.c` | `overlay`, `data-only`, table warnings |
| `sound/vxdecode/get4bit.c` | `data-only`, table warnings |
| `network/usa_client/ddrex2_usa_id.c` | `overlay`, `missing-splits` |
| `sound/vxdecode/dectbl.c` | `data-only`, table warnings |
| `AM/s573/doll/vu0.c` | `vu0` |
| `gs/gs_vu0.c` | `vu0` |
| `CS/bk_disp/bk_mv_list.c` | `data-only`, table warnings |
| `CS/cmes_js2.c`, `CS/cmes_js.c`, `CS/cmes_j.c`, `CS/cmes_e.c` | `data-only`, table warnings |
| `CS/option/opt_doll.c` | `overlay`, `missing-splits` |
| `CS/edit/ed_calc.c`, `sys/sys_demo.c` | `unreferenced-arrays` |
| `CS/option/opt_lang.c` | `overlay`, `missing-splits` |
| `network/net_game/net_game_help.c` | `absolute-addresses` |
| `CS/option/opt_adjust.c` | `overlay`, `missing-splits` |

Note what is *not* on this list any more: `CS/edit_lib/el_mes.c` and the `net_*_mes_e.c`
units, whose table warnings were the old blocker.  Their `.text` shape is what the ranking now
measures.

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
split-only name, so the `unresolvable-callees` reason is gone -- and since the sixth revision
its single large table is a `.debug` warning, not a blocker, which is why it leads the current
ranking.

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
| `sys/sys_demo.c` | `unreferenced-arrays` | `2 array DIE(s) nothing references: unsigned char *[6] @0x2FE, unsigned char [256] @0x5FD -- ... adoption can only drop our extra records, not fabricate a missing one` | exactly the two DIEs and offsets recorded in `1accb6e`; 75 B shortfall; still a blocker, because retail has records we do not |
| `CS/lang.c` | **excluded** | promoted: the source and a `tu_builds` row both exist | `e1a9748`'s two independent `.debug` mismatches: variable order and the nine array DIEs; adoption now supplies retail's DIE order |
| `CS/edit_lib/el_mes.c` | `large-tables` (warning) | `1 large file-scope table(s) (the mes_* debug-order class): el_message_str_e (716 B) -- .debug-only ...` | the `mes_*` table class; the unnamed helper in `unit-a-report.md` now resolves through the link, and the table is adoption's work, not the C's |
| `AM/s573/doll/vu0.c` | `vu0` | `3 function(s) use VU0 macro-mode operations (the .vutext blocker, inferred; section names are stripped)` | the VU0 unit; its splits open with `lqc2`/`ctc2`/`vmulax` |

The `mes_*` siblings are still caught: `CS/cmes_e.c`, `cmes_j.c`, `cmes_js.c` and `cmes_js2.c`
are `data-only` with 84/83/73/73 table warnings.  `net_auth_mes_e.c`, `net_cnf_mes_e.c` and
`net_dnas_mes_e.c` are now **candidates** -- their table/array-order flags are warnings -- while
`net_router_mes_e.c` and `workout_message.c` remain blocked by `overlay`/`missing-splits`,
which is a `.text` placement fact rather than a metadata one.

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
  Since the sixth revision this is a warning rather than a blocker: adoption normalises the
  order when `.text` is byte-identical.
* **The shape of a large function, only its size.**  `largest fn` reads the split's
  `nonmatching` bytes; two functions of the same size can be very different work (a flat
  memcpy loop against a branch-heavy state machine).  The score charges bytes, not basic
  blocks, and a split without a size falls back to instruction count or the DWARF extent.
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
blocked list as the overlay and VU0 classes, with the target's name and address printed, so a
reader can overrule it in seconds.  The demoted `mes_*` classes are no longer on that list:
they print under `risk:` and cost at most a named `.debug` adoption step.  The one false positive this signal ever had
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
5. **Size per function, not only the maximum**: a statement-gap and branch-count histogram
   would tell a 2 KiB straight-line function from a 2 KiB state machine; the current term
   charges both alike.
6. **Indirect-target recovery**: read the `%hi`/`%lo` pair that feeds a `jalr` register when it
   is in the same basic block, so the `NetRouterMain` case is caught structurally rather than
   only because splat happened to render the pointer itself.
7. **Make the thresholds measured rather than chosen** (`LARGE_TABLE_BYTES = 256`,
   `ARRAY_ORDER_TABLES = 2`, the 25-point unresolvable term): once a few screened units are
   promoted, fit the weights against observed time-to-green.
