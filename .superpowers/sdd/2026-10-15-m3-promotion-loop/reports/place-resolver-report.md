# place-resolver report — the link's symbols, the compare path, and `g_game_w`

Tree: main checkout `<checkout>`, from master `8dd8845`.
Unit draft measured: `.git/agents/unit-k` at `c7b6ef0` (branch `wt-unit-k`); `play_anime_step_inst`
is byte-identical in the draft from `0414860` through `c7b6ef0`.
Command: `python3 -m tools.toolchain.compile src/AM/s573/play/p_anime.c <out> --compare
--compiler 3.0b38-030307 -c -lang c -O3 -opt full -g` (the pair the unit report names; the CLI
does not read `tu_builds`).

## 1. The site, reproduced

`play_anime_step_inst`, VA `0x001C5B40`, `.text` size `0x41C`:
`.text` offset `0x10` (VA `0x001C5B50`) is an `R_MIPS_HI16` to `g_game_w`, and `0x18` (VA
`0x001C5B58`) its paired `R_MIPS_LO16`; a second pair sits at `0x250`/`0x258`.

**The placement path resolves all four.** `place()`'s `relocate` writes, and retail's image
holds, exactly:

| offset | placed | retail | symbol |
|---|---|---|---|
| `0x010` | `60001e3c` (`lui s8,0x60`) | `60001e3c` | `R_MIPS_HI16 g_game_w` |
| `0x018` | `707ade27` (`addiu s8,s8,0x7a70`) | `707ade27` | `R_MIPS_LO16 g_game_w` |
| `0x250` | `6000023c` | `6000023c` | `R_MIPS_HI16 g_game_w` |
| `0x258` | `707a4224` | `707a4224` | `R_MIPS_LO16 g_game_w` |

`Manifests.symbols['g_game_w'] == (0x00607A70, {type:obj, provenance:dwarf})`, from
`config/ddrex2p/symbol_addrs.txt:3418`, and `address_of('g_game_w') == 0x607A70`. So the
zero comes from **nowhere in the placement path**: `lui s8,0x0` is objdiff's view of the raw
`.mw.o`, whose relocation fields are zeros by construction (`ddr diff --base <raw .mw.o>`:
`lui s8, 0x0` vs retail `lui s8, 0x60`). `place()`'s output is the typed, resolved object.

## 2. What the link does

* `build/SLUS_211.74.ld` has **no** `g_game_w = …` line and neither does
  `config/ddrex2p/undefined_{syms,funcs}_auto.txt`.
* The link's map does define it: `build/SLUS_211.74.map:65480` — `0x00607a70 g_game_w` inside
  `.bss` (`0x002de180`), under `build/asm/data/bss.bss.s.o(.bss)` (map line 64738).
* The source is `asm/data/bss.bss.s:3012-3015`:
  `nonmatching g_game_w, 0x4` / `dlabel g_game_w` / `/* 00607A70 */ .space 0x04`.
  `mips-linux-gnu-nm build/asm/data/bss.bss.s.o` → `003298f0 B g_game_w` (relocated by the ld).
* At the site itself the pin's `lui 0x60` is the **split's literal instruction**
  (`asm/nonmatchings/main/play_anime_step_inst.s:12`, `/* C5D50 001C5B50 60001E3C */`), because
  the unit is unpromoted and no relocation is linked. The symbol is nonetheless link-resolved
  from the data split, so a promoted object's `%hi`/`%lo` would resolve too.

The decisive comparison: the ld's symbol table and `place`'s lookup **agree** (`0x00607A70`).
The premise that the compare path withholds this symbol is not reproducible.

## 3. The real divergence, and the change

The link's symbol set has two split halves; `Manifests` read only one. `_split_symbols` globbed
`asm/nonmatchings/<segment>/*.s` (code) and never `asm/data/*.s` (data), even though the ld
script lists both. Data labels bind the same way — a `dlabel` and splat's address comment —
but the comment has one number (`/* 00607A70 */`) rather than a code split's three
(`/* C5D50 001C5B50 60001E3C */`). A name that only the data split defines (a `.L002DE184`, or
`g_game_w` if the ledger did not carry it) was refused as "no record at all" although the link
resolves it.

`tools/toolchain/compile.py`:
* `DATA_ADDRESS = /\*\s+([0-9A-Fa-f]+)\s+\*/` — the data split's address comment.
* `_split_symbols` scans `asm/nonmatchings/<segment>/*.s` with `SPLIT_ADDRESS` and
  `asm/data/*.s` with `DATA_ADDRESS`. `setdefault` ordering is unchanged, so
  `symbol_addrs.txt` still wins (`address_of` checks `symbols` first).
* Databin `dlabel`s with no address comment (`__comment_databin`) are skipped, not invented.

Measured on ddrex2p: 1,284 data labels; 1,121 already in the ledger; 163 new (all `.L…`), no
address disagrees with the map, no collision with an existing `placed`/`symbols` entry.

## 4. The specific guard the ticket asked for

`Manifests` already let a ledger address override an `unplaced_symbols.txt` record of the same
name. The new test drives that through `relocate`, not just `address_of`:
`test_the_ledger_address_relocates_even_when_the_name_is_also_unplaced` asserts the emitted
words are `3C1E0060` / `27DE7A70`, never `3C1E0000` / `27DE0000`. The negative,
`test_a_relocation_to_a_name_with_no_record_still_refuses`, asserts the old "no record at all"
refusal at a relocation site. Also added: `test_a_data_split_label_the_link_places_resolves`
(the `bss.bss.s` shape) and `test_a_databin_label_without_an_address_is_not_invented`.

## 5. `play_anime_step_inst` does not verify `.text` — and why

Resolving every relocation is not enough: the draft still differs in **code**, not addresses.
After relocation, 71 of its 263 words differ. Seven of those sit at relocation offsets inside a
shifted region (the instruction at that offset is a different one); the remaining 64 are plain
code — registers and constants:

* first difference `+0x1D0`: ours `5b002312`, retail `5d002312` (register allocation);
* `+0x264`: ours `07000524` (`addiu a1,zero,7`), retail `07000624` (`addiu a2,zero,7`);
* `+0x2B0`: two instructions deleted (`slt at,zero,s1` / `beqz at,0x340`), one inserted;
* `+0x2F0`: `bne v1,v0,0x340` replaced.

The `97.14%` in the unit report is objdiff's fuzzy score of the **raw** object (`ddr diff
--base /tmp/pa.mw.o` → `match_percent 97.13688`), not word equality; it counts operand
mismatches partially. So the acceptance item "`step_inst` `.text` ok" is not met, and cannot be
by a resolver change — the source still needs UnitK's remaining register/control-flow work.
What *is* proven is that no `.text` refusal at `0x10`/`0x18`/`0x250`/`0x258` is attributable to
symbol resolution.

## 6. Guards

| check | result |
|---|---|
| `python3 -m pytest -q` | **321 passed** (after the change; 318+3 earlier failures were the temp source + a concurrent build) |
| `./ddr verify --tu sys_scf` | text ok / debug chunk ok / line chunk ok |
| `./ddr verify --tu net_grf` | text ok / debug chunk ok / line chunk ok |
| `python3 configure.py --target ddrex2p` | 7425 splits, 4491 code splits, 17 link aliases, `build.ninja written` |
| `ninja` | `ok: out/SLUS_211.74 is ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd` |

Commit: `f63395b` — `compile: resolve against the link's data splits, not only its code splits`.
