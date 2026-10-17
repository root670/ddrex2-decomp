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
compile.py: error: src/sys/sys_demo.c: the unit's types .debug is short by 0x4B bytes;
  C is incomplete (cannot pad .debug)
compile.py: error: src/CS/lang.c: mesGetLanguage01 .line is short by 0x1E bytes;
  C is incomplete (cannot pad .line)
```

So the old `the code splits are not the retail N bytes` is now the *backstop* for a real
configuration error, not the first thing a short unit produces.

Inside that, the whole-image gates stay green by construction and are the safety net:
`./ddr --target ddrex2p verify` (G1, the template ELF is `ef31c90f…c02cd`) and
`./ddr --target ddrex2p iso` (G3, the rebuilt disc image is `70a90566…652b`). Undecompiled code is
the split's own bytes, so the image links byte-identically no matter how little is written.

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
| `.debug` a few bytes *short* of the pinned layout | missing parameter or local DIEs — declare the parameters the DWARF records (`dwarf1.py fn`), even unused; measured once as the discriminator that proved a unit's shape. The build refuses it (`the unit's types .debug is short by 0xN bytes; C is incomplete`) rather than padding it |
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
- No test may reach a build machine — `tests/conftest.py` fails any test whose argv names `ninja`,
  `splat` or `configure.py`, and a session backstop fails a run that changes the repository.
- Verify suite claims **at the commit** (`git archive <sha> | tar -x -C /tmp/…` and run there); this
  checkout is shared and has already produced one green build against uncommitted code.

## Known blocker classes and two failure modes worth knowing

Measured while finishing two hard units in 28 minutes and 78 compile-and-compare cycles between them:
the cost was the unknowns, not the loop.

Two failure modes the table above does not cover:

- **A `.debug` block of the right length but the wrong bytes.** Every size message stays silent; only a
  byte comparison sees it, and `ninja`'s `g1` edge is what catches it. Do not conclude a unit is sound
  because the build printed no warning.
- **A `.line` record that a conditional expression cannot produce.** The original used a *branch*: two
  one-line `if`s reproduced retail's seven statement records exactly, where a `? :` — even split
  across lines — never produced records 119 and 122.

Blocked classes, each with a mechanism rather than a label. A unit that fails this way is a **finding**,
not a puzzle: record it and take another unit.

| class | mechanism |
|---|---|
| **unreferenced array DIEs** | the types block is short of DIEs describing an array type *nothing in the CU references* (`unsigned char *[6]`, `unsigned char[256]`); fifteen constructs and all five compiler builds left the block unchanged, so no C shape produces them |
| **unreferenced aggregate DIEs** (solved once) | *which* construct emits a type's DIEs, and where: a file-scope **object** of the type emits them but leaves its own variable DIE behind (+0x23) and relocations no ledger places; an `extern` declaration emits neither; an unused **`static` function** whose body touches the type emits them and nothing else — but only for a *member* access through a pointer or a by-value parameter/return, never for a copy or `sizeof`. The emission **order** is fixed by where that function sits relative to the file-scope variable and the unit's functions: between the variable and the first function the block came out byte-equal to retail's, after the variable but past the functions the aggregate pair came out reversed, past both functions the array pair. Measured on 40 constructs in `network/net_grf.c` (`reports/net-grf-debug-report.md`) |
| **`mes_*` units** | `.global_variable` DIE ordering differs for large unreferenced file-scope tables, referenced statics come out reversed, and the residue is array-DIE order, which no declaration order controls |
| **VU0 units** (`.vutext`) | MWCC sinks the epilogue, so the last inline-asm statement takes the `jr` delay slot where retail fills it from the operation that follows |
| **shape conflicts** | a unit needing two mutually exclusive C shapes: the reconstruction that fixed `.line` scheduled six words differently and left `.text` short, so both could not be had. Record the conflict; never pick a winner and call it promoted |
| **unresolvable callees** | a call target the promotion path cannot relocate, failing at `cc` *before* any comparison. The ledger is now the **link's own symbol set**, not one file: the split globals under `asm/nonmatchings/<segment>` (bound to the address of the instruction after each label), the `-T` files' assignments where this layout holds their address, and `symbol_addrs.txt`. Two things survive that, and they must not be confused with a lookup gap: the **overlay boundary** — an address outside every declared segment, an overlay window this milestone does not model, deferred by design — and a name with **no record at all** in any of the three. `net_sys_connect` is the first (`NetRouterMain`, stored through `%hi(D_008062B0)` rather than called, undefined in the link); the split-only callees that blocked four candidates (`func_001C43E8` in `net_grf.c`, `func_001BED10` in `dexport.c`, `func_00128600`/`func_0012CD70` in `dmm_chara.c`) were never a class: `compile.py` was reading one ledger while the link resolved the split objects its ld script lists, and fixing that took **53 units out of the screen's blocked list** while the four overlay units stayed in it. |
| **128-bit GPR operations** | the unit's split carries an EE 128-bit GPR **operation** (`pxor`, `pand`, `paddw`, …), and MWCC PS2 has **no 128-bit operators**, so no C expression emits one. Measured with the retail compilers under wibo (`-c -lang c -O3 -g`, and `-lang c++`): `a ^ b`, `a & b`, `a \| b`, `a + b`, `a - b`, `a * b`, `~a`, `a ^= b` on `u_long128`/`unsigned __int128` are rejected by **all five installed builds** with `Error: illegal data size` — for parameters, locals, globals and pointer dereferences alike — and `u_long128 a;` without a typedef fails the same way. What 128-bit C *does* give is assignment (`lq`/`sq`) and constant materialisation (`lui`/`ori`/`dsll32`/`or`/`pcpyld`), which is exactly how retail builds `Cr`, `Cb` and `ex`. The only construct that produced a `pxor` was MWCC's inline-asm extension (`asm { pxor a, a, ex }`) — assembly, not C, so it is a probe rather than a promotion. Found on `eyetoy/eye_filter.c`, whose `negaposi` is `pxor $4,$4,$7`/`pxor $3,$3,$7` over `lq`/`sq` values, while its neighbour `sepia` in the same unit uses only the expressible subset. The screen flags it as `128-bit-gpr` and must **not** match `lq`/`sq`/`pcpyld` (`sepia` is the in-tree proof that legal C emits them) nor `pref` (a prefetch hint). |

**Caveat — a `#include`d unit's `.debug` depends on the spelling of the include path.** With the derived `-I<repo>/include` in place, a unit that actually `#include`s a header gets type `.debug` bytes that shift with the *length* of the spelling used, while `.text` stays identical (measured: same-length spellings match, +2 characters differ; the `-I` itself is byte-neutral on a unit that does not include). So a header-including unit can fail the section compare for a reason that has nothing to do with its C. The spelling the retail build used is recorded in the split's own DWARF (`DW_AT_comp_dir` and the included-file paths), so the durable derivation is "the spelling the original object records", not "whatever path the repository happens to have".

**What the loop lacks:** a way to ask *which C construct* emits a given missing DIE. That is manual
probing today and it is where most of a hard unit's cycles go. Everything else the loop needs exists.
