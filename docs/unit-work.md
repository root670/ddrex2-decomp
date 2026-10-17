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

**A per-unit green is necessary but not sufficient.** Observed twice: `verify --tu` reported all three parts ok for units whose `.debug`/`.line` payload was *smaller* than the pinned layout, and the link then refused with `the code splits are not the retail N bytes`. So build the image before believing a promotion — `ninja` runs `g1` as its last edge, and that edge is what promotes a unit. And `ddr verify` on its own can report `G1 ok` against a **stale** `out/SLUS_211.74` left behind by a failed build, so treat freshness as part of the check.

Inside that, the whole-image gates stay green by construction and are the safety net:
`./ddr --target ddrex2p verify` (G1, the template ELF is `ef31c90f…c02cd`) and
`./ddr --target ddrex2p iso` (G3, the rebuilt disc image is `70a90566…652b`). Undecompiled code is
the split's own bytes, so the image links byte-identically no matter how little is written.

## The loop

1. **Pick a unit.** Start small, and prefer units whose calls are already named in
   `config/ddrex2p/borrowed_symbols.txt` — a unit with no calls needs no library name at all.
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
| `.debug` a few bytes *short* of the pinned layout | missing parameter or local DIEs — declare the parameters the DWARF records (`dwarf1.py fn`), even unused; measured once as the discriminator that proved a unit's shape |
| `.line` short of the pinned layout | a statement the original had has no counterpart, or an inline is unwritten |
| the link refuses with `the code splits are not the retail N bytes` | the unit's payload does not fill the extent it replaces — the strongest signal, and invisible to `verify --tu` |

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
