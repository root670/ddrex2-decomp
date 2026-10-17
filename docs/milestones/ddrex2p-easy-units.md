# Easy units on `ddrex2p`, ranked by shape

Generated with:

```bash
python3 tools/units/screen.py --markdown --top 20
python3 tools/units/screen.py --all --top 60   # the blocked rows, with reasons
```

The rule this implements is `docs/unit-work.md`'s "Pick a unit by shape, not by size": few
functions, scalar code, no VU0, no large/unreferenced file-scope tables, calls that already
have names, and plenty of DWARF line records.  Four units failed on exactly those shapes and
cost 4½ hours between them, so the screen's first job is to make those classes visible before
anyone writes C.  It reads `config/ddrex2p/cus.json`, `orig/SLUS_211.74`'s DWARF,
`config/ddrex2p/symbol_addrs.txt`, `borrowed_symbols.txt`, `unplaced_symbols.txt` and the
splits under `asm/nonmatchings/main/`; it never compiles or links anything.

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

Of 249 translation units, 1 is promoted (`sys/sys_scf.c`), **6 are unblocked candidates**, and
242 are blocked (the categories below overlap): 67 overlay units have no retail split in this
target, 1 is a library object, 142 carry at least one unresolvable target, and the remainder
carry one of the shape classes.

## Ranking

Scores are a tie-break among unblocked units, not a probability.  `score = 100 - 6·(functions-1)
- 25·unresolvable targets - calls/name penalties - FPU tax - 0.02·array DIEs +
min(10, line records per function)`, with a +2 bonus at 20 statements.  The unresolvable term is
a courtesy for the printed order, not the mechanism: such a unit is `blocked` and never reaches
the candidate list.  Every term is printed in the last column, so a reader can disagree with the
weights without losing the evidence.

| rank | unit | score | functions | line records | why expected easy |
|---:|---|---:|---:|---:|---|
| 1 | `eyetoy/eye_filter.c` | 106.0 | 2 | 44 | 2 functions; 44 line records (22.0/function); no calls; no array/table risk; no VU0; scalar; declared 2 function(s) in cus.json |
| 2 | `network/net_game/net_game_help.c` | 94.0 | 2 | 47 | 2 functions; 47 line records (23.5/function); calls: 0 borrowed, 12 named, 0 internal; no array/table risk; no VU0; scalar; declared 2 function(s) in cus.json |
| 3 | `AM/s573/play/p_anime.c` | 73.2 | 5 | 239 | 5 functions; 239 line records (47.8/function); calls: 0 borrowed, 14 named, 0 internal; 39 array DIE(s), 1 file-scope table(s), all referenced; no VU0; scalar; declared 5 function(s) in cus.json |
| 4 | `network/net_inter.c` | 61.9 | 7 | 42 | 7 functions; 42 line records (6.0/function); calls: 0 borrowed, 10 named, 0 internal; 5 array DIE(s), 0 file-scope table(s), all referenced; no VU0; scalar; declared 7 function(s) in cus.json |
| 5 | `AM/s573/doll/ps1lib.c` | 50.4 | 8 | 129 | 8 functions; 129 line records (16.1/function); calls: 9 borrowed, 0 named, 0 internal; 4 array DIE(s), 0 file-scope table(s), all referenced; no VU0; 5 FPU function(s); declared 8 function(s) in cus.json |
| 6 | `AM/s573/doll/motion2.c` | 42.3 | 8 | 346 | 8 functions; 346 line records (43.2/function); calls: 3 borrowed, 20 named, 32 internal; 12 array DIE(s), 0 file-scope table(s), all referenced; no VU0; 2 FPU function(s); declared 8 function(s) in cus.json |

`calls: 0 borrowed, 12 named, ...` means every call target already carries a `symbol_addrs`
record, so no name has to be imported mid-unit.  Distinct unresolvable targets are not a
scoring term a reader has to weigh: a unit with any is blocked and printed under `--all` with
the target's name, its address, and which ledger gap it is.

### The top three, in one line each

* `eyetoy/eye_filter.c` — two functions, **no calls at all**, no array or file-scope-table
  shape, 44 statement lines: the closest thing to `sys_scf.c`'s shape in the tree.
* `network/net_game/net_game_help.c` — two functions, twelve already-named calls, 47 statement
  lines, no array or table shape; it took candidate #2's place once the callee signal moved
  `net_sys_connect` down.
* `AM/s573/play/p_anime.c` — five functions, 239 statement lines, fourteen named calls, one
  referenced file-scope table; more functions than the calibration unit, but every name it
  calls is placeable today.

The first unit that did promote (`sys_scf.c`) scores **97.5** on the same formula (2
functions, 4 line records per function, one borrowed call), which is the calibration the
weights were set against: the top candidates are the units whose measured shape is at least
as clean as the one that worked.

## Validation: the four callee failures

The previous ranking's #2, #3, #4 and #5 all scored on calls the promotion path cannot resolve.
The signal must see all four, and must leave #1 alone:

| previous rank | unit | new flags | reason printed by the screen | known fact |
|---:|---|---|---|---|
| 2 | `network/net_sys/net_sys_connect.c` | `unresolvable-callees` | `D_008062B0` (NetRouterMain) at `0x8062B0`: outside every declared segment (overlay boundary) | `NetRouterMain` is in `unplaced_symbols.txt` only; the pointer is materialised with `%hi`/`%lo`, not a `jal` |
| 3 | `AM/s573/doll/dexport.c` | `unresolvable-callees` | `func_001BED10` at `0x1BED10`: code target with a split but no `symbol_addrs` record (lookup gap) | call to a split-only `func_`; the first ranking called it a warning, not a block |
| 4 | `network/net_grf.c` | `unresolvable-callees` | `func_001C43E8` at `0x1C43E8`: code target with a split but no `symbol_addrs` record (lookup gap) | a callee in **no** ledger at all; blocked the unit before a comparison |
| 5 | `CS/dancemaster/dmm_chara.c` | `unresolvable-callees` | `func_00128600` at `0x128600`; `func_0012CD70` at `0x12CD70`: code targets with a split but no `symbol_addrs` record (lookup gap) | the two absent targets recorded for this unit |
| 1 | `eyetoy/eye_filter.c` | *(none)* | — | remains unblocked and is still rank 1 |

The same two-sub-case print shows up on `CS/edit_lib/el_mes.c`, which the first ranking carried
as a *warning* (`calls-without-record`): its one call names `func_00192F30`, a split-only name,
so the unit now carries `unresolvable-callees` beside its `large-tables` reason.  Neither the
warning nor a `placeholder` count survives; a name without an address is a block.

Across the tree the signal moves **68 candidates from unblocked to blocked** (the previous
recorded ranking listed 62 unblocked; the tree has since grown to 74 under the old rule, and the
new rule leaves 6).  Of the flagged targets, 141 are overlay-boundary addresses and 1,146 are
in-segment lookup gaps, spread over 142 units.

## Validation: the four shape failures

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

## What the signal cannot see

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
* **Whether a lookup gap is permanent.**  The in-segment sub-case is a ledger lookup gap that is
  being fixed, so those units unblock themselves as soon as `symbol_addrs.txt` gains the record —
  the screen reads the ledger at run time, but a ranking printed before that fix says `blocked`.
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

### What a false positive costs

The signal is deliberately biased toward blocking, because the two errors are not symmetric.  A
false negative costs an agent its whole box (the unit never reaches a comparison, as happened
four times in a row).  A false positive costs one line in `--all`: the unit sinks to the same
blocked list as the overlay, VU0 and `mes_*` classes, with the target's name and address
printed, so a reader can overrule it in seconds — and if the name really is placeable, the
`symbol_addrs` check passes and the flag disappears on the next run.  The one known false
positive today is the transient one above: a lookup gap that the ledger fix closes.

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
