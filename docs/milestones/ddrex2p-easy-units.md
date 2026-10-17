# Easy units on `ddrex2p`, ranked by shape

Generated with:

```bash
python3 tools/units/screen.py --markdown --top 20
```

The rule this implements is `docs/unit-work.md`'s "Pick a unit by shape, not by size": few
functions, scalar code, no VU0, no large/unreferenced file-scope tables, calls that already
have names, and plenty of DWARF line records.  Four units failed on exactly those shapes and
cost 4½ hours between them, so the screen's first job is to make those classes visible before
anyone writes C.  It reads `config/ddrex2p/cus.json`, `orig/SLUS_211.74`'s DWARF,
`config/ddrex2p/symbol_addrs.txt`, `config/ddrex2p/borrowed_symbols.txt` and the splits under
`asm/nonmatchings/main/`; it never compiles or links anything.

Of 249 translation units, 1 is promoted (`sys/sys_scf.c`), 62 are unblocked candidates, and
186 are blocked (67 overlay units have no retail split in this target, 1 is a library object,
and the rest carry at least one of the blocker classes below).

## Ranking

Scores are a tie-break among unblocked units, not a probability.  `score = 100 - 6·(functions-1)
- calls/name penalties - FPU tax - 0.02·array DIEs + min(10, line records per function)`, with
a +2 bonus at 20 statements.  Every term is printed in the last column, so a reader can
disagree with the weights without losing the evidence.

| rank | unit | score | functions | line records | why expected easy |
|---:|---|---:|---:|---:|---|
| 1 | `eyetoy/eye_filter.c` | 106.0 | 2 | 44 | 2 functions; 44 line records (22.0/function); no calls; no array/table risk; no VU0; scalar; declared 2 function(s) in cus.json |
| 2 | `network/net_sys/net_sys_connect.c` | 101.1 | 2 | 18 | 2 functions; 18 line records (9.0/function); calls: 0 borrowed, 1 named, 0 placeholder, 0 internal; 45 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 2 function(s) in cus.json |
| 3 | `AM/s573/doll/dexport.c` | 98.7 | 2 | 31 | 2 functions; 31 line records (15.5/function); calls: 0 borrowed, 3 named, 1 placeholder, 0 internal; 115 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 2 function(s) in cus.json |
| 4 | `network/net_grf.c` | 98.0 | 2 | 12 | 2 functions; 12 line records (6.0/function); calls: 0 borrowed, 0 named, 1 placeholder, 0 internal; 2 array DIE(s), 1 file-scope table(s), all referenced; no VU0; scalar; declared 2 function(s) in cus.json |
| 5 | `CS/dancemaster/dmm_chara.c` | 97.4 | 1 | 32 | 1 function; 32 line records (32.0/function); calls: 0 borrowed, 9 named, 2 placeholder, 0 internal; 80 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 1 function(s) in cus.json |
| 6 | `common/com_scrollbar.c` | 95.0 | 1 | 80 | 1 function; 80 line records (80.0/function); calls: 0 borrowed, 0 named, 7 placeholder, 0 internal; no array/table risk; no VU0; 1 FPU function(s); declared 1 function(s) in cus.json |
| 7 | `common/co_cursor.c` | 94.5 | 2 | 99 | 2 functions; 99 line records (49.5/function); calls: 1 borrowed, 0 named, 4 placeholder, 0 internal; no array/table risk; no VU0; 1 FPU function(s); declared 2 function(s) in cus.json |
| 8 | `network/net_game/net_game_help.c` | 94.0 | 2 | 47 | 2 functions; 47 line records (23.5/function); calls: 0 borrowed, 12 named, 0 placeholder, 0 internal; no array/table risk; no VU0; scalar; declared 2 function(s) in cus.json |
| 9 | `network/mio/md5.c` | 89.9 | 4 | 484 | 4 functions; 484 line records (121.0/function); calls: 0 borrowed, 0 named, 2 placeholder, 4 internal; 6 array DIE(s), 1 file-scope table(s), all referenced; no VU0; scalar; declared 4 function(s) in cus.json |
| 10 | `network/net_sys/net_sys_main.c` | 85.3 | 2 | 68 | 2 functions; 68 line records (34.0/function); calls: 0 borrowed, 13 named, 3 placeholder, 0 internal; 83 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 2 function(s) in cus.json |
| 11 | `common/com_keyboard.c` | 82.8 | 3 | 207 | 3 functions; 207 line records (69.0/function); calls: 0 borrowed, 0 named, 7 placeholder, 0 internal; 11 array DIE(s), 1 file-scope table(s), all referenced; no VU0; 1 FPU function(s); declared 3 function(s) in cus.json |
| 12 | `AM/s573/doll/model1.c` | 77.3 | 5 | 126 | 5 functions; 126 line records (25.2/function); calls: 0 borrowed, 3 named, 2 placeholder, 4 internal; 37 array DIE(s), 1 file-scope table(s), all referenced; no VU0; 1 FPU function(s); declared 5 function(s) in cus.json |
| 13 | `CS/opening/openinglogo.c` | 76.9 | 4 | 64 | 4 functions; 64 line records (16.0/function); calls: 0 borrowed, 0 named, 7 placeholder, 0 internal; 4 array DIE(s), 1 file-scope table(s), all referenced; no VU0; 1 FPU function(s); declared 4 function(s) in cus.json |
| 14 | `AM/s573/play/p_anime.c` | 73.2 | 5 | 239 | 5 functions; 239 line records (47.8/function); calls: 0 borrowed, 14 named, 0 placeholder, 0 internal; 39 array DIE(s), 1 file-scope table(s), all referenced; no VU0; scalar; declared 5 function(s) in cus.json |
| 15 | `network/net_game/net_game_challenge.c` | 70.3 | 3 | 138 | 3 functions; 138 line records (46.0/function); calls: 0 borrowed, 18 named, 5 placeholder, 1 internal; 83 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 3 function(s) in cus.json |
| 16 | `CS/dancemaster/dmm_mess.c` | 70.0 | 3 | 88 | 3 functions; 88 line records (29.3/function); calls: 0 borrowed, 10 named, 8 placeholder, 1 internal; 49 array DIE(s), 0 file-scope table(s), all referenced; no VU0; 1 FPU function(s); declared 3 function(s) in cus.json |
| 17 | `CS/shop/shop_main.c` | 66.0 | 6 | 53 | 6 functions; 53 line records (8.8/function); calls: 0 borrowed, 6 named, 4 placeholder, 0 internal; 41 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 6 function(s) in cus.json |
| 18 | `CS/shop/shop_list.c` | 65.2 | 7 | 233 | 7 functions; 233 line records (33.3/function); calls: 0 borrowed, 3 named, 3 placeholder, 6 internal; 88 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 7 function(s) in cus.json |
| 19 | `common/cws/cws_wins.c` | 64.8 | 7 | 133 | 7 functions; 133 line records (19.0/function); calls: 0 borrowed, 7 named, 2 placeholder, 0 internal; 12 array DIE(s), 1 file-scope table(s), all referenced; no VU0; scalar; declared 7 function(s) in cus.json |
| 20 | `network/net_sys/net_sys_logout.c` | 64.1 | 3 | 73 | 3 functions; 73 line records (24.3/function); calls: 0 borrowed, 19 named, 8 placeholder, 0 internal; 45 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 3 function(s) in cus.json |

`calls: 0 borrowed, 1 named, ...` means the call targets already carry a symbol record, so no
name has to be imported mid-unit.  `placeholder` count is call sites to a split-only
`func_XXXXXXXX` name: writable, but the C has to name a callee the ledger does not.  It is a
warning, not a block, because the name may arrive with the callee's own unit.

### The top three, in one line each

* `eyetoy/eye_filter.c` — two functions, **no calls at all**, no array or file-scope-table
  shape, 44 statement lines: the closest thing to `sys_scf.c`'s shape in the tree.
* `network/net_sys/net_sys_connect.c` — two functions, one already-named call, 18 statement
  lines; its 45 array DIEs are all struct-member types referenced by the CU, not tables.
* `AM/s573/doll/dexport.c` — two functions, 31 lines, three named calls and one placeholder;
  its 115 array DIEs are all referenced (no unreferenced DIE and no file-scope table).

The first unit that did promote (`sys_scf.c`) scores **97.5** on the same formula (2
functions, 4 line records per function, one borrowed call), which is the calibration the
weights were set against: the top candidates are the units whose measured shape is at least
as clean as the one that worked.

## Validation against the four known failures

The screen is only useful if it sees the classes that actually cost the 4½ hours.  It does:

| unit | flags | reason printed by the screen | matches the recorded failure |
|---|---|---|---|
| `sys/sys_demo.c` | `unreferenced-arrays` | `2 array DIE(s) nothing references: unsigned char *[6] @0x2FE, unsigned char [256] @0x5FD` | exactly the two DIEs and offsets recorded in `1accb6e`; 75 B shortfall |
| `CS/lang.c` | `unreferenced-tables`, `array-die-order` | `8 file-scope table(s) no function references ...; 9 array tables / 9 array DIEs: array-DIE order is compiler-table order, not declaration order` | `e1a9748`'s two independent `.debug` mismatches: variable order and the nine array DIEs |
| `CS/edit_lib/el_mes.c` | `large-tables`, `calls-without-record` (warning) | `1 large file-scope table(s) (the mes_* debug-order class): el_message_str_e (716 B)`; warning: its one call names `func_00192F30`, which has no `symbol_addrs` record | the `mes_*` table class plus the unnamed helper in `unit-a-report.md` |
| `AM/s573/doll/vu0.c` | `vu0` | `3 function(s) use VU0 macro-mode operations (the .vutext blocker, inferred; section names are stripped)` | the VU0 unit; its splits open with `lqc2`/`ctc2`/`vmulax` |

The `mes_*` siblings are caught too: `CS/cmes_e.c`, `cmes_j.c`, `cmes_js.c` and `cmes_js2.c`
are `data-only` with 84/83/73/73 `unreferenced-tables`; `net_auth_mes_e.c`,
`net_cnf_mes_e.c`, `net_router_mes_e.c`, `net_dnas_mes_e.c` and `workout_message.c` carry the
table/array-order flags.  `el_mes.c` is the one exception in that family: its single table
**is** referenced by its only function, so the screen flags it under the *large-table* half of
the class, not as an unreferenced table.  That distinction is real and is printed, not hidden.

### What the screen cannot see

* **`.vutext` membership directly.**  This retail ELF's section headers are stripped (the only
  named sections are `.debug`, `.line`, `.comment`, `.reginfo` and the string tables), so
  "lands in `.vutext`" is inferred from VU0 macro-mode instructions in the unit's split.  A
  unit with a `.vutext` payload but no VU instruction in its first-level split would be missed;
  none is known in this target.
* **A right-length, wrong-bytes `.debug` block.**  The screen predicts blockers from shape; it
  cannot compare DIE bytes without compiling.  That is the failure mode the docs call
  invisible to every size message, and only the build's byte comparison sees it.
* **Shape conflicts.**  A unit needing two mutually exclusive C shapes (the `net_win_infoboard`
  case) has no signature in the DWARF; it is discovered only by trying both.
* **Inline/macro provenance and statement *content*.**  Line records are counted per function;
  whether the original statements can be recovered from them is not modelled.
* **The exact array-DIE order.**  The screen flags the class when a unit carries ≥2 file-scope
  array tables, but it cannot say whether a given unit's compiler table will happen to agree.
* **Whether a split-only `func_` callee will be named by another unit's promotion.**  It is a
  warning, never a hard block, precisely because that resolution is external to this unit.
* **Data-only units in the overlays.**  All 67 overlay units already carry `overlay`/`no retail
  split`; the screen deliberately does not pretend to rank them.

## What I would add next if this proves too coarse

1. **A dependency column, not just a call count**: resolve each `func_` callee to the unit that
   owns it and mark "waiting on an unpromoted unit", so a wave can pick a closure of units
   together rather than flags failing on names.
2. **Per-function screening**: the unit score hides a unit with one easy function and one
   pathological one.  The same signals (line records, calls, VU/FPU, array use) are already
   per-function; rank `(unit, function)` pairs for a first conversion.
3. **A DIE-shape model**: capture, per TU, the types block's DIE tag sequence and compare it to
   what the candidate C would produce once compiled.  That would turn "right length, wrong
   bytes" from a post-compile discovery into a pre-write risk.
4. **Statement-gap histogram**: line records per function plus the largest line gap, because a
   large gap is where an inline hides and is the cheapest early warning for `.line` trouble.
5. **Make the thresholds measured rather than chosen** (`LARGE_TABLE_BYTES = 256`,
   `ARRAY_ORDER_TABLES = 2`): once a few screened units are promoted, fit the weights against
   observed time-to-green instead of the four failures alone.
