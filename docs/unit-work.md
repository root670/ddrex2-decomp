# Unit work — how a translation unit gets promoted on `ddrex2p`

Reference for anyone (human or agent) writing matching C for this target. The loop below is the
one that actually produced `src/sys/sys_scf.c` and `src/sys/sys_demo.c`; every command in it exists
and is exercised by the suite.

Two external documents are worth reading alongside this one, for different reasons:

- `zeldaret/tww`'s `docs/decompiling.md` — the fullest unit-work workflow anyone has written down.
  Its central lesson is platform-independent: **inline and macro usage is invisible in the
  disassembly but changes codegen**, so a semantically correct function can still fail to match.
- `LucasPicoli/god-hand-decomp`'s `docs/ps2_mips_cheatsheet.md` — EE register/ABI table, delay
  slots, `nop` padding at TU boundaries, and a per-TU compiler table like our `tu_builds`.

We differ from both in one important way: **our target ships full Metrowerks DWARF**, so names,
structs, frames and statement lines are given rather than inferred. Work with them; they are the
reason this loop is cheap.

## What "promoted" means

A translation unit counts as promoted only when `./ddr --target ddrex2p verify --tu <tu>` reports
**all three** parts ok:

| part | what must match |
|---|---|
| `.text` | the compiled instructions, byte for byte |
| `.debug` | the debug chunk the compiler emits for that unit — types, member order, visibility |
| `.line` | the statement→address line table, i.e. **your statements must sit on retail's line numbers** |

**A per-unit green is necessary but not sufficient.** Observed twice: `verify --tu` reported all
three parts ok for units whose `.debug`/`.line` payload was *smaller* than the pinned layout, and the
link then refused with `the code splits are not the retail N bytes`. So build the image before
believing a promotion — `ninja` runs `g1` as its last edge, and that edge is what promotes a unit.
And `ddr verify` on its own can report `G1 ok` against a **stale** `out/SLUS_211.74` left behind by a
failed build, so treat freshness as part of the check.

**What "the extent it replaces" means, and what the build now says about it.** A promotion is placed
where its *splits* were, and a splat split runs from its symbol's address to the **next** symbol's
address — so the last split of a unit usually covers bytes past the unit's last function. That
overhang is retail's `nop` padding, and `tools/toolchain/compile.py` measures the extent from the
split files themselves, fills the overhang from retail, and prints what it filled:

```
compile: src/sys/sys_demo.c: filled .text trailing nop padding from retail (0x8 bytes)
```

It fills **only** `nop` — in the overhang and in the inter-function gaps alike. Anything else is
content this unit has not written, and is refused by name, chunk and byte shortfall, saying the C is
incomplete rather than that the link is broken. `.debug` and `.line` are never padded at all:

```
compile.py: error: src/sys/sys_demo.c: condition 2 (.debug length and DIE count) failed:
  the unit's types .debug is short by 0x4B bytes; C is incomplete (cannot pad .debug)
compile.py: error: src/CS/lang.c: mesGetLanguage01 .line is short by 0x1E bytes;
  C is incomplete (cannot pad .line)
```

So the old `the code splits are not the retail N bytes` is now the *backstop* for a real
configuration error, not the first thing a short unit produces.

Inside that, the whole-image gates stay green by construction and are the safety net:
`./ddr --target ddrex2p verify` (G1, the template ELF is `ef31c90f…c02cd`) and
`./ddr --target ddrex2p iso` (G3, the rebuilt disc image is `70a90566…652b`). Undecompiled code is
the split's own bytes, so the image links byte-identically no matter how little is written.

### The one recorded `.debug` deviation

A unit whose **only** `.debug` deviation is the anonymous-type DIE order may be promoted.  The
gate applies four conditions in order: (1) `.text` and `.line` are **byte-equal**, never relaxed;
(2) the emitted `.debug` chunk is exactly retail's length and holds retail's DIE count;
(3) the two chunks are identical as **multisets of DIEs compared structurally** — tag, size,
member names/offsets/kinds, variable and parameter attributes — with only the synthesized
`@anonN` names normalised; (4) anything else refuses, naming the failed condition and the first
offending DIE (a missing or extra DIE, a changed member, a different tag, a different length).
On acceptance the gate prints an explicit boundary line, keeps retail's `.debug` chunk in the
image (so G1 remains the pin), and the measured permutation is recorded as a comment on the
unit's `tu_builds` row and as a line in this section.  No unit has been accepted this way yet.

## The loop

1. **Pick a unit by shape, not by size.** Small turned out to mean hard: the three smallest candidates
   were a `mes_*` unit (blocked on `.debug` DIE ordering), a VU0 unit (blocked on the epilogue sinking
   into the last inline-asm delay slot), and one whose `.text` needs an in-extent `nop` with an exacting
   scratch-variable shape — 4½ hours of agent time between them, nothing promoted, while the first unit
   that *did* promote took 15 minutes. Choose instead:

   - few functions, **scalar** code, and **no VU0** (`.vutext` has its own section and its own blocker);
   - **no large unreferenced file-scope tables** (the `mes_*` blocker class);
   - calls either absent or already named in `config/ddrex2p/borrowed_symbols.txt`, so no library name
     has to be imported mid-unit;
   - plenty of DWARF line records, because `.line` is the gate that punishes guesswork hardest.

   **Time-box it: about thirty minutes.** If it is not green by then, commit it as WIP with what you
   learned and take the next one. A unit that resists is a finding; three hours on one is a lost
   afternoon, and the shape list above exists so the next person avoids the class rather than the unit.
   Counts and paths come from `config/ddrex2p/cus.json`.

2. **Gather the evidence** (do not guess any of it):

   ```bash
   python3 tools/oracle/dwarf1.py fn  orig/SLUS_211.74 <symbol>       # signature, frame, saved regs, globals
   python3 tools/oracle/dwarf1.py lines orig/SLUS_211.74 <VA> --table # the retail statement line numbers
   cat include/src/<dir>/<tu>.h                                       # structs, globals, prototypes, line ranges
   cat asm/nonmatchings/main/<symbol>.s                               # the disassembly to reverse
   ```

3. **Write the C on retail's line numbers.** The line numbers are evidence, not a suggestion. If the
   generated header spells a tag bare (`_tag_X`, C++ syntax), write `struct _tag_X` in the C; if a
   gap between two statements is large, the original had lines you have not reproduced yet — often an
   inline, sometimes a declaration — and `.line` will fail until they are accounted for.

4. **Iterate with the diff, not with the gate.** The gate compiles the whole unit; the diff scores one
   function against **retail's bytes**:

   ```bash
   ./ddr --target ddrex2p diff <symbol> <tu>
   ```

   It prints what it compared (target = the retail bytes of the symbol, base = your C object, or the
   split's own bytes when the unit has no C). A 100.0% on an unpromoted function is normal and is the
   signal to move on.

5. **Gate the unit**, then commit it alone:

   ```bash
   ./ddr --target ddrex2p verify --tu <tu>
   git add <explicit paths> && git commit -m "ddrex2p: promote <tu>"
   ```

6. **Record the compiler.** Measure the pair that reproduces this unit with
   `tools/toolchain/select_build.py --tu <tu>` and add it to `tu_builds` in `config/targets.py`.
   `configure.py` refuses to promote a source nobody has measured. As of the last batch: four builds
   (`3.0-011126`, `3.0.1-020123`, `3.0.3-020716`, `3.0b38-030307`) reproduce a unit byte-for-byte at
   `-c -lang c -O3 -g`, `.comment` cuts that to three (`3.0b38-030307` writes `(3.0.0)` where retail
   has `(2.4.1.01)`), and **only `.text` can separate the rest** — `.debug`'s producer string is
   version-less. So a unit that contradicts the recorded pair is a finding worth reporting loudly.

   **The flag string is half of the pair, and one unit has already contradicted it.** `p_anime.c`
   (`AM/s573/play/p_anime.c`, candidate #12) needs `-c -lang c -O3 -opt full -g`: its two large
   functions reach 78.15% and 88.76% of retail's words with `-opt full` and only 69.97% and 67.19%
   without it, and the difference is mechanical — **`-opt full` is what turns a `pid`-indexed address
   into a walking induction variable**. At `-O3` mwcc emits `mult` for `pid * 0x5428C` once per
   iteration, no `sp+0xA0` slot for the `paw_p->db[pid]` index, and a frame 0x30 bytes smaller; with
   `-opt full` it emits retail's `addu base, base, <size>` increment at the loop bottom and the 0xD0
   frame. All five installed builds behave identically under `-O3` and identically under
   `-O3 -opt full`, so this is a *flag* fact, not a *build* fact, and it is invisible on a unit with
   no indexed address inside a loop — which is why `sys_scf.c`'s recorded pair could not show it.
   Per-unit flags exist for exactly this; `tu_builds` carries the whole string.

   **A second trap, measured the same day: the `--compare` invocation ignores `tu_builds`.**
   `python3 -m tools.toolchain.compile <src> <out> --compare` takes its compiler from its own
   `--compiler` default (`fetch.REQUIRED`, 2.4-001213) and its flags from the command line, not from
   the target descriptor — only `ninja`'s `cc` edge uses the recorded pair.  On `p_anime.c` that made
   the unit look `2 bytes short` (and a first attempt, without `-opt full`, `0x10 short`) from nothing
   but the wrong compiler: the 2.4 build saves the frame with `sq`/`lq` where retail has `sd`/`ld`, so
   the "shortfall" was the frame's instruction shape.  To compare a unit by hand, pass the pair in
   full: `--compiler 3.0-011126 -c -lang c -O3 -opt full -g`.

## What the diff's failure modes mean

The diff reports *shape*, and each shape points at a different cause. Read it as a diagnosis, not a
score:

| what you see | what it usually means |
|---|---|
| registers swapped, instructions reordered, an instruction duplicated | expression or macro/inline shape — try the original's macro or inline, not a logic change |
| a spurious `jal` argument mismatch (`jal sceScfGetDateNotation` vs `jal func_001B3840`) | a *naming* difference, not a code difference — the split cases by address, retail by name |
| `.line` mismatch only | statements on the wrong source lines: a missing declaration, an inline, or re-wrapped expressions |
| `.debug` mismatch only | types, member order, bitfield spelling or visibility differ from what the compiler recorded |
| `.text` correct size but wrong bytes | wrong expression form, wrong flag, or wrong helper |
| `.text` different size | the source structure differs (extra call, missing call, different control flow) |
| `.debug` a few bytes *short* of the pinned layout | missing parameter or local DIEs — declare the parameters the DWARF records (`dwarf1.py fn`), even unused; measured once as the discriminator that proved a unit's shape. The build refuses it (`condition 2 (.debug length and DIE count) failed: the unit's types .debug is short by 0xN bytes; C is incomplete`) rather than padding it |
| `.line` short of the pinned layout | a statement the original had has no counterpart, or an inline is unwritten. Refused the same way (`<fn> .line is short by 0xN bytes; C is incomplete`) — one 10-byte record per statement, so the shortfall says how many are missing |
| the build fills `.text` padding and says so (`filled .text trailing nop padding from retail (0xN bytes)`) | the unit's last split ran past its last function and retail's bytes there are `nop` — normal, and now handled |
| the link refuses with `the code splits are not the retail N bytes` | a real layout error: a split that is in no object, a symbol at two addresses, a split order that is not the address order. A *short unit* no longer reaches it |

When a function resists matching after the logic is right, check the line table for skipped lines
before assuming a mistake: that is where an inline hides.

## What is given, and what we invent

Given (do not re-invent): function names, signatures, frames, saved registers; 8,152 local names,
3,930 parameter names, 1,043 globals; 292 named aggregates with member names and offsets; 13,756
array types; the statement lines. Library names arrive from the archives with byte evidence, into
`config/ddrex2p/borrowed_symbols.txt` — hand-written, byte tier only, merged into the generated
`symbol_addrs.txt` by the oracle; run-tier *proposals* live in `library-names.md` and must never
enter the build artifact.

Invented, with provenance recorded — because DWARF does not carry it:

- **typedef spellings** (zero typedef DIEs; types are structural only),
- **enum members** (17 enumeration types, no enumerators),
- **anonymous aggregate tags** (`anon_<N>_<unit>`, per unit, since the same synthetic name means
  different types in different units),
- **descriptive names** for the DWARF-less engine code, which has no names at all.

The rule to follow is tww's, and it is a good one: **no names are better than incorrect names.**

## Comment style

The C is evidence, not an essay. Keep it to a short header and local notes:

- **A two-line header**: the source path the DWARF records, and that the unit was reconstructed from
  `orig/SLUS_211.74`'s DWARF and disassembly.
- **An inline comment only where the C is genuinely non-obvious** — a magic constant, an unusual
  expression shape, a gap the evidence forces.
- **No narrated reasoning.** Why the source drifted, what the disassembly showed, which names were
  invented, which gates accepted it — that belongs in this document, in `docs/milestones/*.md`, or in
  `config/<target>/library-names.md`. Anywhere a reader goes looking for rationale rather than code.

**One mechanical exception, and it is a real one:** the `.line` gate pins *statement* lines to retail's
own line numbers, so the number of lines before the first statement and between statements is fixed by
evidence, not by taste. Where that forces space, use **blank lines** — a comment thick enough to fill a
twenty-line gap is padding pretending to be documentation. The statement lines must not move; what
fills the space between them is your choice.

**A better answer than padding when the file must carry more than the statements.** A `#line N`
directive makes the line that *follows* it number `N`, so statements land on retail's line
numbers directly and the blank-line dance disappears: the file can hold a header comment, an
`#include`, a type block or a `#define` between two statements without forty empty lines
standing in for them.  Measured on UnitC's `AM/s573/doll/dexport.c`, whose statements are at
lines 61–105 while its type closure is 1,111 lines over 28 headers — the generated headers are
the only way to declare `SaveData` (0x1FF50 B) and `g_game_w` (0xACDC4) without moving the
statements, and the emitted `.line` numbers stayed retail's.  Two rules come with it:

- the directive numbers the *next* line, so the statement after it must be the one retail puts
  on `N`; put it immediately before that statement, not before a block of declarations;
- **`#line` numbers must stay monotonic inside a function.**  MWCC attributes a loop's
  preheader — the IV initialisations, a hoisted symbol, the peeled head statement — to the
  *highest* line number it has seen so far, not to the `for`.  With declarations parked on
  lines 383–401 and the `for` on 386, every head-statement record vanished and the preheader
  took line 401; compressing the declarations onto lines ≤ 385 and putting the `for` on 386
  took `play_anime_step_inst` from 94 line records to **103, retail's count exactly**.  `#line N`
  may be repeated to park several declaration lines on one number.
- **a `for` loop's increment and test carry the line of the body's closing brace**, not the
  `for`'s own line.  Measured on a probe: `for (n = 0; n < 4; n++) { … }` with the `}` on line 9
  records the `n++` and the test on line 9.  So when the line a `#line` must reach is a loop's,
  it is the brace's line that has to be right, and both of UnitC's candidate units are only
  explicable with that rule.

## House rules that keep the gates honest

- Gates are pins, not opinions: `config/ddrex2p/checksums.txt` holds both, and a gate that lacks its
  input **skips with an explicit "nothing was compared" line** — never a silent pass. Note that a
  skip and a pass share exit code 0; read the line.
- Never hand-edit generated files (`asm/**`, `include/**`, `config/ddrex2p/splat*.yaml`,
  `symbol_addrs.txt`, `unplaced_symbols.txt`, `objdiff.json`); regenerate with
  `./ddr --target ddrex2p oracle`. Hand-written names go in `borrowed_symbols.txt`.
- One record per VA inside the declared segments: splat's duplicate check fires at symbol load,
  *before* it splits, so a duplicated address stops the build outright.
- Commit with explicit paths and never `--amend`; parallel writers get their own `git worktree`
  (seed `orig/` and `toolchain/` by symlink, regenerate the generated trees per worktree).
- **Subagent worktrees live at `.git/agents/<name>`** — a `git worktree` inside the repository's
  own `.git`, never in the home directory.  `git worktree list` then finds every one of them, and
  the branch name and the directory travel together; a home-directory worktree is outside the
  repository's cleanup and disappears from the roster.  Merge back by cherry-picking into the main
  checkout, never by rewriting the worktree's history.
- No test may reach a build machine — `tests/conftest.py` fails any test whose argv names `ninja`,
  `splat` or `configure.py`, and a session backstop fails a run that changes the repository.
- Verify suite claims **at the commit** (`git archive <sha> | tar -x -C /tmp/…` and run there); this
  checkout is shared and has already produced one green build against uncommitted code.

## Known blocker classes and three failure modes worth knowing

Measured while finishing two hard units in 28 minutes and 78 compile-and-compare cycles between them:
the cost was the unknowns, not the loop.

Three failure modes the table above does not cover:

- **A `.debug` block of the right length but the wrong bytes.** Every size message stays silent; only a
  byte comparison sees it, and `ninja`'s `g1` edge is what catches it. Do not conclude a unit is sound
  because the build printed no warning.
- **A `.line` record that a conditional expression cannot produce.** The original used a *branch*: two
  one-line `if`s reproduced retail's seven statement records exactly, where a `? :` — even split
  across lines — never produced records 119 and 122.
- **A `.line` chunk of the right length with a record at the wrong address.** The record *count* and every
  line *number* can match while one record's offset does not, and only the byte compare sees it — the same
  blindness as the `.debug` bullet above, one section over. Measured on `ps2dancerInitHide`: with the pad
  `nop` of the next-but-one entry restored, `.line` was retail's 0x58 bytes and all seven line numbers were
  retail's, but line 105's record pointed at the loop's `slt` (+0x54) where retail's points at the epilogue
  (+0x60). The fix is source re-lining, not code: the `do` statement's closing brace and `while` clause need
  their own `#line 104` marker, like every other statement in the reconstruction. So "short by 0xA" is a
  *size* reading only; a `.line` verdict has to be read as bytes.

Blocked classes, each with a mechanism rather than a label. A unit that fails this way is a **finding**,
not a puzzle: record it and take another unit.

| class | mechanism |
|---|---|
| **anonymous-type DIE order in a promoted unit** | a unit whose types `.debug` contains anonymous aggregates gets its per-object chunk compared byte-for-byte, and the compiler's `@anonN` index assignment cannot be reproduced by the header. Measured: the block has the right length and the same aggregates, structurally identical (tag, size, member names, offsets, kinds) to retail's, but the indices are permuted. The assignment follows the *declaration* order in controlled cases (six standalone aliases declared `a`..`f` get `@anon0`..`@anon5`; reversed, reversed), a container's *inline* anonymous members are emitted after it in member order, and aliases nested by value keep their own position -- but it also depends on the whole TU's content: the promoted `src/network/net_grf.c` declares `grf_coord` before `grf_element` and its object emits `grf_element` `@anon0` then `grf_coord` `@anon1` (retail's order), while the *same typedef block* alone compiles the other way round. Swapping two `#include` lines in a unit header permutes all 25 indices of `dmm_chara.c` without changing the block's length. Retail's own emitted order is not a declaration order: `dmm_chara.c`'s `@anon7` (`work`, 15740 B) has by-value member types on **both sides** of it (7 before, 10 after) with other containers' declarations (`play_mode`, `play_hist`, `g_game_w`, …) interleaved between the followers, and a named type cannot be declared inside a struct body -- so a container's by-value member type would have to be declared *after* its container, which no C declaration order expresses. Tell this class from wrong C by comparing the two chunks as a **set** of DIEs, not by position: same length, same DIE count, pairwise-identical structures and only the anonymous indices moved = this boundary; any difference in the set (type, member, size, statement or parameter DIE) = the C is wrong. `.text` and `.line` stay verifiable and `.debug` is not part of the linked image, but the promotion path refuses the chunk first (`does not fit the pinned chunk`), so the gate is stricter than the image: such a unit would link byte-identically while its per-object debug chunk differs. |
| **unreferenced array DIEs** | the types block is short of DIEs describing an array type *nothing in the CU references* (`unsigned char *[6]`, `unsigned char[256]`); fifteen constructs and all five compiler builds left the block unchanged, so no C shape produces them |
| **unreferenced aggregate DIEs** (solved once) | *which* construct emits a type's DIEs, and where: a file-scope **object** of the type emits them but leaves its own variable DIE behind (+0x23) and relocations no ledger places; an `extern` declaration emits neither; an unused **`static` function** whose body touches the type emits them and nothing else — but only for a *member* access through a pointer or a by-value parameter/return, never for a copy or `sizeof`. The emission **order** is fixed by where that function sits relative to the file-scope variable and the unit's functions: between the variable and the first function the block came out byte-equal to retail's, after the variable but past the functions the aggregate pair came out reversed, past both functions the array pair. Measured on 40 constructs in `network/net_grf.c` (`reports/net-grf-debug-report.md`) |
| **`mes_*` units** | `.global_variable` DIE ordering differs for large unreferenced file-scope tables, referenced statics come out reversed, and the residue is array-DIE order, which no declaration order controls |
| **VU0 units** (`.vutext`) | MWCC sinks the epilogue, so the last inline-asm statement takes the `jr` delay slot where retail fills it from the operation that follows |
| **shape conflicts** | a unit needing two mutually exclusive C shapes: the reconstruction that fixed `.line` scheduled six words differently and left `.text` short, so both could not be had. Record the conflict; never pick a winner and call it promoted |
| **unresolvable callees** | a call target the promotion path cannot relocate, failing at `cc` *before* any comparison. The ledger is now the **link's own symbol set**, not one file: the split globals under `asm/nonmatchings/<segment>` (bound to the address of the instruction after each label), the `-T` files' assignments where this layout holds their address, and `symbol_addrs.txt`. Two things survive that, and they must not be confused with a lookup gap: the **overlay boundary** — an address outside every declared segment, an overlay window this milestone does not model, deferred by design — and a name with **no record at all** in any of the three. `net_sys_connect` is the first (`NetRouterMain`, stored through `%hi(D_008062B0)` rather than called, undefined in the link); the split-only callees that blocked four candidates (`func_001C43E8` in `net_grf.c`, `func_001BED10` in `dexport.c`, `func_00128600`/`func_0012CD70` in `dmm_chara.c`) were never a class: `compile.py` was reading one ledger while the link resolved the split objects its ld script lists, and fixing that took **53 units out of the screen's blocked list** while the four overlay units stayed in it. |
| **128-bit GPR operations** | the unit's split carries an EE 128-bit GPR **operation** (`pxor`, `pand`, `paddw`, …), and MWCC PS2 has **no 128-bit operators**, so no C expression emits one. Measured with the retail compilers under wibo (`-c -lang c -O3 -g`, and `-lang c++`): `a ^ b`, `a & b`, `a \| b`, `a + b`, `a - b`, `a * b`, `~a`, `a ^= b` on `u_long128`/`unsigned __int128` are rejected by **all five installed builds** with `Error: illegal data size` — for parameters, locals, globals and pointer dereferences alike — and `u_long128 a;` without a typedef fails the same way. What 128-bit C *does* give is assignment (`lq`/`sq`) and constant materialisation (`lui`/`ori`/`dsll32`/`or`/`pcpyld`), which is exactly how retail builds `Cr`, `Cb` and `ex`. The only construct that produced a `pxor` was MWCC's inline-asm extension (`asm { pxor a, a, ex }`) — assembly, not C, so it is a probe rather than a promotion. Found on `eyetoy/eye_filter.c`, whose `negaposi` is `pxor $4,$4,$7`/`pxor $3,$3,$7` over `lq`/`sq` values, while its neighbour `sepia` in the same unit uses only the expressible subset. The screen flags it as `128-bit-gpr` and must **not** match `lq`/`sq`/`pcpyld` (`sepia` is the in-tree proof that legal C emits them) nor `pref` (a prefetch hint). |
| **out-of-segment fixed addresses** | the unit's split accesses a fixed absolute address above every declared segment, and the bytes say retail's operand was a *symbol*, not a constant: `lui $1,(0x1030000 >> 16)` + `lw $3,-0x601C($1)` is the assembler's `lw rt, sym` expansion (`$1` is `at`, one pair per access), where a C constant compiles to `lui`+`ori` in an allocated register — measured on `network/net_game/net_game_help.c`, whose `NetGameHelpDisp` is 155 of 172 words different and 4 bytes short for that reason alone, with `.debug`/`.line` DIEs *exact* and only their values differing. The address cannot be named: `borrowed_symbols.txt` validates every line against a split's bounds (functions only), an out-of-segment `unplaced_symbols.txt` record is refused rather than resolved to 0 (`compile.py`'s `Manifests`), and no record in any of the four ledgers is above `bss_end` except the overlay ones. Measured on this tree: 207 distinct addresses in the `0x01029FD0..0x0102FFCC` band plus `0x00A7D350`/`0x00F4D380` and the scratchpad `0x10002000`/`0x10010000`, from 218 splits over 38 units — 21 of the 57 candidates at `ce7a75b` leave the list on it. It is **not** a segment missing from `config/ddrex2p/`: the band has no ROM offset (0x01029FE4 → file 0xF2A1E4 past the file's 0x75DFEC bytes), no `PT_LOAD` window covers it (the ELF's memsz-only windows are 0x7F0000, 0x1884000, 0xE4D380 — the overlay slots the oracle already records), and the DWARF names nothing in `0x00A00000..0x01100000`, so nothing in this repository places it. The screen flags it as `absolute-addresses`; it does not match the `addu`-indexed spelling of the same band (3 splits), which is byte-identical to the assembler's large-displacement expansion over a register. |
| **a statement whose whole code is a pad `nop`** | retail's `.line` carries a record whose entire code is one `nop` *inside* a function's extent, and retail's `.text` is 4 bytes longer for it (`ps2dancerInitHide`: record 103 at +0x4C, 0x70 against 0x6C, every other instruction identical, `beqz` displacement 0x0D against 0x0C). Only **inline assembly** on that line inside the enclosing body produces the record *with* the bytes — `__asm__ ("nop");`, `asm ("nop");`, `__asm__ volatile ("nop");`, `asm { nop }` each give +0x4 and the one record. About thirty C candidates give neither: bare `;`, `{ }`, `{ ; }`, `i = i;`, `i += 0;`, `(void)i;`, `if (0) ;`, `else if (0) ;`, `continue;`, `if (i >= 0) ;`, `if (i) { }`, `if (i) { } else { }`, `else ;`, `else { l: ; }`, an empty `switch` case/default, `do { } while (0);`, `while (0) ;`, `for (;;) break;`, `i ? 0 : 0;`, `(void)(i, 0);`, `__asm__ ("");` (nothing at all), and `int k;` (rejected — the dialect is C89, a declaration cannot sit mid-block). A lone label, a `goto` to the label that follows, and a conditional branch to the next statement instead **delete** a record with no byte change, and **no construct yields the record without code**: a record's address always carries an instruction, which is exactly what `C is incomplete (cannot pad .line)` reports. Consequence: a unit whose retail build pads a statement is **not promotable from C** — the same boundary as the 128-bit `pxor`. Assembly is a probe, not a promotion, because the goal is readable C; but the route is *known*, not lost: on the `dexport.c` draft `__asm__ ("nop")` at line 103 plus the re-lining of the failure mode below reproduced retail's `.text` byte-for-byte (modulo two relocation sites) and `.line` record-for-record. Probes: `drafts/nopline/` on `wt-unit-n`; the full construct table is in `.superpowers/sdd/2026-10-15-m3-promotion-loop/reports/nop-line-report.md` |
| **a file-scope `static`'s DWARF tag** | all five installed builds tag a **file-scope `static`** as `.global_variable`, while retail's CU records the same object as `.local_variable`, in declaration order (`p_anime.c`: `anime_id_tbl`, `hold_release`, `pre_hold_flag`).  A *block-scope* static does come out `.local_variable`, but in the **function's** own CU inside a `lexical_block`, which is not where retail's file-scope objects sit.  Measured on a minimal TU (`static int s_one; static int s_two[4]; int g_one;`) at `-O3` and `-O3 -opt full`; no source shape moves it, so a unit blocked here is evidence for the compiler-revision hypothesis below rather than a C bug. |
| **a `+0x10` overrun from a `for` loop's entry guard** | a `for` loop emits an entry guard (`b <bottom>` in the preheader) that retail's loops in `p_anime.c` do not have.  Rewriting the loop as `do … while` removes the guard, but it also **changes the unit's size** — measured: it grew `play_anime_step_inst` by `0x28` — so the loop form is not the fix for a `+0x10` overrun; look elsewhere. |
| **hypothesis — a compiler revision outside the five installed** | **Not a finding.**  Two units failed to reproduce a decision across the five installed builds under two flag strings (`-O3` and `-O3 -opt full`) and a set of source variants: `p_anime.c` needs a file-scope static tagged `.local_variable` in declaration order, where all five builds emit `.global_variable` in another order; `com_scrollbar.c` needs a register-allocation permutation that no variant reproduces, while the callee-saved *set* is retail's (`u/scrbw`, `y1/x1/z0/y0`, `v/z1/w`) and only the *numbers* move — the same permutation in every build.  What is established is "no source form tried, under those two flag strings, reproduces the decision", not "the revision is unobtainable": MWCC's option space (allocation, scheduling, inlining, pooling, `lmw/stmw`, per-file pragmas) has not been swept.  **The test is a flag sweep on minimal discriminators**, which owns the final wording.  `.comment` cannot narrow it: four of the five write retail's `MW MIPS C Compiler (2.4.1.01)` string.  Whatever the sweep finds, tell this class from wrong C by the set comparison: `p_anime.c`'s DIE set differs only in the static's tag and the permuted `@anonN` indices (353 of 361 DIEs common), and `com_scrollbar.c`'s emitted instruction sequence and local-DIE order are retail's while only the register colouring moves. |
| **register-save line records** | a missing `.line` record is not always a pad. In `ps2dancerGetDollList` retail's extra record is `61@0x28`, and 0x1CF248 holds `sw s1,0x10(sp)` — a **register save in the prologue** — while the function's two real `nop`s (0x1CF2E4, 0x1CF34C) carry **no** record at all (retail's records run 74@0xB0 → 75@0xCC across +0xC4, and 82@0x130 follows +0x12C), i.e. ordinary unrecorded alignment padding. So that shortfall is a statement/line-attribution gap in the prologue: do not conflate the two classes and do not probe for a `nop` in it |
| **compiler boundary — callee-saved colouring** | the source is right and the compiler is the residue. Retail colours the nine values live across this unit's calls `u=s0, scrbw=s1, y1=s2, x1=s3, z0=s4, y0=s5, v=s6, z1=s7, w=s8`; the same source under **all five installed builds** colours them as a permutation of that set (the set is invariant, the numbers are not), and 190 compile-and-compare cycles over statement order, declaration placement, expression form, `-O` levels, `-opt` families and pragmas never produce retail's assignment. **Under the game's pair** (`3.0-011126 -c -lang c -O3 -opt full -g`; `3.0.1`/`3.0.3` agree) the same source is 0x18 short of `.text` (0x528 vs 0x540), 0x28 short of `.line` (0x30a vs 0x332 — 77 of 81 records, 33 of them at retail's exact (line, address)), `.debug` at the pinned 0x955 length but with its local-DIE order **retail's exact reverse** — and that order is unreachable by declaration order: the 3.0 family emits local DIEs **inner-block-first with each block reversed**, so declaring the blocks' locals reversed (both the then-block's and the else's, and again with the else's pair moved to function scope) only permutes the groups inside that fixed block order (`bar_y,bar_h | bar_y,bar_h,sa,dw_h | info,sp2` and `bar_y,bar_h,sa,dw_h | info,sp2,bar_h,bar_y`), Declaring **all four then-locals at function scope**, in retail's DIE order reversed, is the one form that gets the function-level group right: the group comes out `info, sp2, bar_y, bar_h, sa, dw_h` — retail's exact sequence — but the else pair must stay nested (retail's DWARF carries **two** `bar_y`/`bar_h` pairs, `[$a0]` and `[$a1]`, so the source had two scopes), and a nested group is emitted **first**, giving `bar_h, bar_y, info, sp2, bar_y, bar_h, sa, dw_h` (`.text` 0x528, `.line` 0x30a, 84.80% words, registers unchanged). So under the game's pair no legal declaration order reaches retail's order, while the same source under `3.0b38-030307` reproduces it exactly. **This bounds the uniform-pair proof**: neither `sys_scf` nor `net_grf` carries block-scoped locals in its `.debug`, so their strict byte-equality proves the build and the flags but cannot discriminate the local-DIE emission order; `com_scrollbar` is the first unit that can, and on it the game's pair emits inner-group-first-reversed while retail's object carries outer-first-forward. An **inverted guard** (`if (!(scrbw->flag & 1)) { <else body> } else { <then body> }`, the statements re-numbered with `#line` so their values stay retail's) does not fix the order: the DIE sequence becomes `dw_h, sa, bar_h, bar_y, bar_h, bar_y, info, sp2` — the function-level group is still emitted last — while `.text` drops to 0x520, `.line` to 0x22e and word equality to 31.16%, because the bodies swap places in the instruction stream and the line records are address-ordered. So the order is a property of the block emission, not of the guard's polarity; the build stays `3.0-011126` and what differs for this unit is **our source's block structure** — the function-level declarations must precede the code, which is exactly why their group comes out last. never retail's outer-first forward order; the nine registers stay `u→temp, …` in both (84.75% / 84.80%, 0x528 both), and **84.84%** word equality, the nine coloured `u→temp, v=s8, w=s1, h=s0, x1=s2, y1=s3, z0=s6, z1=s4, y0=s7` (plain `-O3` gives 84.80% with `w/z0/y0` at `s7/s1/s6`). The closest cell, `3.0b38-030307` at the same flags — **not** the game's build — reaches all three pinned sizes and 81 of 81 `.line` records, 78 of them byte-identical (94.55%) but still permutes the numbering; there the residue is one knob: `#pragma opt_propagation off` reproduces the assignment **exactly** and costs 0x18 bytes, because the propagation pass is both what CSEs the three bar blocks and what proves `sa == 0` in the else path, after which the allocator coalesces `bar_h`/`dw_h`. Pragmas are function-granular, ignored inside a nested block, and illegal between `}` and `else`, so the two knobs cannot be split. Re-run under the game's pair: propagation off costs 0x04 (0x544) with all four `subu`s surviving (both of the then-block's, and the else-path clamp) but the bar blocks lose their CSEs (spans +4/+3/−1/−2/−2/−1/−3/+3) and the numbering still differs (`u→temp`, …); the five subtrahend spellings (`bar_h - sa`, `bar_h + -sa`, `-sa + bar_h`, and both paths with each) and the declaration-order variants leave 0x528 and that assignment untouched. Measured on `common/com_scrollbar.c`; the full argument is in its unit report. **The declaration-order rule below cannot reach it**: the nine coloured values are **not declarations** — eight are MWCC's address temporaries for `sp2`'s members and one is the parameter — so no source-visible order selects them (the rule itself is **register assignment is declaration order, not statement order**). Read backwards, retail's assignment implies the order `y0, z0, x1, y1, scrbw, u, v, z1, w`, and none of the three source-visible orders is that one: members `x0, y0, x1, y1, z0, z1, w, h, u, v`, definitions `flg, u, v, w, h, x0, y0, z0, x1, y1, z1`, materialisation `u, v, w, y0, z0, x1, y1, z1`. Direct test — reversed then-block declarations plus block A's uses reordered `y0, z0, x1, y1` — leaves the assignment unchanged in **both** cells: `u=s3, v=s4, w=s8, x1=s0, y1=s6, z0=s1, z1=s7, y0=s2` with the sizes still `0x540`/`0x955`/`0x332` (94.55%) under `3.0b38-030307 -O3 -opt full`, and `u→temp, v=s8, w=s1, h=s0, x1=s2, y1=s3, z0=s6, z1=s4, y0=s7` with 0x528/0x30a (84.84%) under the game's pair. The rule's regime does **not** explain it: call-straddling locals were measured separately and obey the **same** declaration-order rule at n=9 (twelve random declaration-order × side-of-the-call pairs, plus every side partition at canonical order; the `s4↔s0` swap is reachable for every partition tried — see `drafts/regalloc/stagger.py`). The exclusion is that these nine are **not declarations**: eight are address temporaries and one is a parameter, so no declaration order selects them. |
| **register assignment is declaration order, not statement order** | Measured with `drafts/regalloc/probe.py` under `3.0b38-030307 -c -lang c -O3 -opt full -g`, on N=2..9 locals that all cross a call and are each identifiable by their constant: the register is fixed by **declaration order alone** — the K-th declared value gets `s(n-K)` for n≤5, the first six reversed into `s5..s0` and the 7th/8th/9th `s6/s7/s8` in declaration order for n≥7 (n=6 is a boundary: the sixth takes `s5`). Statement order, initialisation at declaration vs later, first-use order, call position and the local's type are **inert** (all measured). Any target is reachable on that shape: the `s4↔s0` swap of a 9-value set and a fully arbitrary 9-permutation were each realised by one declaration order (`(0,5,2,3,4,1,6,7,8)` for the swap), and the `a`-class scan counter's `a1↔a2` too. Retail's local DIEs are emitted in declaration order and carry `DW_OP_regN`, so `.debug` and `.text` are one decision seen twice and retail's DWARF reads out the order to use. **The limit is liveness subsets, not staggered definitions.** Declaration order alone decides in every side partition: nine locals with two calls, each given one live definition on either side and read on the far side, gave the same `A = reverse(D[:6]) + D[6:]` for all eight partitions tried (`S = ∅`, `{0}`, `{0,1}`, `{0..4}`, `{0,2,4,6,8}`, `{4}`, `{4,5,6}`, all nine), for twelve random (declaration order × partition) pairs, and with the within-side definition orders reversed; the `s4↔s0` swap was reached by `D=(0,5,2,3,4,1,6,7,8)` in every partition compiled. The only deviation is the n=5 small-set rotation `A = reverse(D[:r]) + reverse(D[r:])`, `r = p` if `p < \|S\|` else `p-1`, where `p` is the longest declared prefix defined before the first call (120/120 verified). What the rule does **not** cover is a **value set whose liveness membership changes across regions** — values that come and go between calls rather than a fixed set all live across them: retail's `play_anime_step` does not satisfy the formula for its DIE order (`counter` takes `s7` although third declared among the saved ones), and it is not in the staggered regime. Report: `.superpowers/sdd/2026-10-15-m3-promotion-loop/reports/regalloc-report.md`. |

### The two compiler boundaries, and why only one is promotable

Two classes now end at the compiler rather than at the C, and they are **not** equivalent:

* **anonymous-DIE ordering** changes only `.debug`, which is never linked. A unit in that class is
  **promotable under the set-equal gate with the deviation recorded** — the rebuilt image is still
  byte-identical.
* **callee-saved colouring** changes `.text`, because register numbers are encoded in the instructions,
  so no recorded-deviation policy can accept it: the rebuilt image would differ. Such a unit **stays
  unpromoted no matter how correct its source**, and that is the honest outcome.

The mechanism sentence for the second, which is what a future reader needs: **retail has propagation-on
code with propagation-off colouring** — the CSEs that give the pinned instruction count and the free-list
order that gives the pinned register numbers come from the same pass in every build we have. What would
close it is therefore not a C shape but a compiler that lets the propagation pass and the allocator's
first-fit/free-list decision be configured separately: a build we do not have, or a pragma granularity
the compiler does not offer. The alternatives are ruled out by measurement, not assumption — five
subtrahend spellings (`bar_h - sa`, `bar_h + -sa`, `-sa + bar_h`, and both paths with each) leave the
permutation untouched; the DWARF records **two distinct `bar_h` DIEs** (`[$a0]` then-branch, `[$a1]`
else-branch), so `bar_h` cannot be extended across the else path to break the coalescing; and the `.line`
pin fixes every statement in the then-block, so the liveness cannot be moved either.

**Caveat — the two things that move type `.debug` bytes, in the order they matter.** First, and this is what actually blocks units: a generated header that *names* an anonymous aggregate puts that name into the DIE, where retail's build has MWCC's `@anonN`, so the type block is long by exactly the invented names' worth. Fixed in the generator: an unnamed aggregate is emitted as `typedef struct { … } alias;`, because DWARF 1 has no typedef DIE and the alias keeps the compiler's own name. Measured: `dmm_chara.c` 0x67A0 → **0x6389, retail's pin exactly**, and `dexport.c` 0x6CFE → **0x692C**, the same defect and not the path length. Second, a smaller effect, now only worth knowing: for a unit that `#include`s a header, the type `.debug` bytes also shift with the *length* of the include path's spelling, while `.text` is identical (same-length spellings match, +2 characters differ; the `-I` itself is byte-neutral on a unit that does not include). The spelling the retail build used is recorded in the split's own DWARF (`DW_AT_comp_dir` and the included-file paths), so derive it from there rather than from whatever path the repository happens to have — but do not chase this before checking the naming defect above, which is 0x3D2 of the 0x3D2 seen on `dexport`.

**What the loop lacks:** a way to ask *which C construct* emits a given missing DIE. That is manual
probing today and it is where most of a hard unit's cycles go. Everything else the loop needs exists.
