# Working in this repository

This is a **matching decompilation** of the *DDR Extreme 2 (US) preview*, PlayStation 2:
`SLUS_211.74`, **7,725,036 bytes, sha256
`ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd`**.  The goal is a C source tree
that, compiled with the retail compiler and linked with the pinned layout, reproduces the retail
artifacts **byte for byte** — not "looks right", not "runs the same".  The design is in
`docs/superpowers/specs/2026-10-16-ddrex2-preview-retarget-design.md`; the plan that built the
skeleton is `docs/superpowers/plans/2026-10-16-ddrex2-preview-retarget.md`, and the loop a unit goes
through is `docs/unit-work.md`.

**One target is registered, in one descriptor.**  `ddrex2p` (the *DDR Extreme 2 (US)* preview,
`SLUS_211.74`) is this tree's target; its binary is yours to place (retail files are never
committed), and its config and its measured segment list are committed (`config/ddrex2p/`,
`config/targets.py`).  Every verb whose input is not there stops naming it.  Adding
another target is a `Target(...)` plus one line in the registry there, and nothing else changes.
`config/targets.py` is the only place a target's facts are written down — its retail ELF and G1 pin, its disc image and G3 pin, its config directory, its
*measured* geometry (segment list, chunked-section lengths, disc-image offset) and the
compiler/flag pair each promoted unit was measured against.  Every tool reads them from there, so
retargeting is adding a descriptor rather than editing a dozen files.  The flag that selects one is
`--target <name>`, on `ddr` and on `configure.py`; the default is the registered target, which is why a bare
`./ddr build` still means this target.

The contract below is short because everything in this repository is *provable* by a command, and
every rule here exists because breaking it produces a tree that still builds, still passes, and is
still wrong.  Read it before your first edit.

## The loop

```bash
./ddr build                          # configure.py + ninja: the whole image, gates included
./ddr verify                          # G1: out/<elf> == the pinned retail ELF
./ddr verify --tu sys_scf            # ... plus the promotion rule for one unit
./ddr verify --iso                    # ... plus G3 on the mounted retail image (skipped if absent)
./ddr diff sysInitScf sys_scf         # objdiff-cli: retail's bytes for one symbol vs our object
python3 -m pytest -q                  # the suite (251 tests; ~94 s today)
```

`--target <name>` (default: the registered target) goes on any of them — before the verb
(`./ddr --target ddrex2p verify`) or after it (`./ddr verify --target ddrex2p`) -- and it decides which
binary, image, pin, config directory and geometry the verb reads.  Its other spelling is
`python3 configure.py --target <name>` (`./ddr build` runs exactly that for its target).

`./ddr` is the project's whole command surface: `oracle`, `build`, `verify [--tu NAME] [--iso IMG]
[--retail FILE]`, `diff SYMBOL TU`, `iso --iso IMG`.  Nothing else is a supported entry point, and
`./ddr --help` is the authoritative list.  Exit codes: **0** green, **1** a gate or a TU verdict
failed (or a host tool is missing — you get the remedy, never a traceback), **2** a usage or
configuration problem.

**After every change: `./ddr build` then `./ddr verify`.**  A change is not done when the build
succeeds; it is done when the gate that covers it is green.  Changes to one unit are checked with
`./ddr verify --tu <name>` — `--tu` accepts `sys_scf`, `sys_scf.c` or `src/sys/sys_scf.c`.

## The rules

1. **A red gate is never worked around.**  Do not edit a pin (`config/<target>/checksums.txt`), do not
   point `--retail`/`--iso` at a different file to make a gate green, do not exclude a unit from the
   graph, do not special-case a chunk.  A failing gate is the *result*; fix the bytes it names.  On a
   red G1 the tool prints the translation unit, the function, the compile unit and the chunk that own
   the first divergent byte (G2 consumes G1's own localisation — do not re-derive the offset by
   hand).

2. **The generated tree is never hand-edited.**  `asm/**` (splat's splits),
   `config/<target>/splat.yaml`, `config/<target>/splat_symbol_addrs.txt`,
   `config/<target>/undefined_{syms,funcs}_auto.txt`, `build.ninja`, `build/<elf>.ld` and
   `objdiff.json` are all outputs of `configure.py`; `./ddr build` regenerates them.  The oracle's
   artifacts — `config/<target>/cus.json`, `config/<target>/debug_chunks.json`,
   `config/<target>/symbol_addrs.txt`, `config/<target>/unplaced_symbols.txt` and the generated header
   tree under `include/**` — are outputs of `./ddr oracle`, which is deterministic: a fresh run
   reproduces what is committed, byte for byte (`tests/test_cli.py::test_oracle_regenerates_the_committed_artifacts_byte_for_byte`).
   If one of those files is wrong, the fix belongs in the code that emits it, or in
   `config/<target>/ghidra_functions.json` (the oracle's one hand-curated *input*), never in its output.

3. **Names are never invented.**  A symbol's name comes from the retail debug information or from
   `config/<target>/ghidra_functions.json`; a function with no evidence keeps the name its address gives
   it (`func_00214080`).  Inventing a plausible name (`Player_Update`, `RenderScene`) puts a lie in
   the symbol table, in the headers, and in every objdiff verdict that follows.

4. **Statements keep their retail line numbers.**  The `.line` section is part of the artifact
   (`docs/milestones/ddrex2p-m2.md`), so a statement belongs on the line the evidence says it is on.
   Reflowing code to read better, or "tidying" a blank line, moves every statement number after it
   and shows up as a `.line` chunk that no longer matches — that is the build telling you the
   source's shape is part of the target, not a style preference.

   **A promoted source carries no comments, no blank line directly inside a brace, and no `#line`
   directive — and the build enforces all three.**  `tools/units/strip_comments.py --check` fails
   on the first two, with one exception that follows the paragraph above: a unit whose
   `tu_builds` row records `False` or `True` emits the source's own statement positions, so a
   blank line inside a brace is the line itself — `--check` reports it as evidence, and
   `--collapse` refuses until that row records `adopt`.  `configure.py` refuses a `tu_builds`
   source with a directive *before* it writes `build.ninja`, and `compile.py` refuses the same
   unit before the compiler runs.  Both
   name the file, the count and the remedy
   (`python3 tools/toolchain/line_reflow.py <file> --normalise`), so a directive-laden source can
   neither be configured nor built, and nothing rewrites a scratch copy the committed file does
   not show.

5. **Retail binaries, disc images and toolchains never enter the repository.**  `orig/`, `disc/` and
   `toolchain/` are gitignored and stay that way; the user supplies the ELF and the image, and the
   compiler archives are fetched by `tools/toolchain/fetch.py` and hash-verified before they are
   extracted or run.  Never `git add -f` any of them, never paste a byte range of either into a
   test, never commit a toolchain archive.  `THIRD_PARTY_NOTICES.md` records what *is* vendored
   (`tools/oracle/**`).

6. **A translation unit counts as promoted only when its code *and* its debug bytes match.**  The
   verdict is `./ddr verify --tu <name>`, which prints the unit's `.text` span, its `.debug` chunk
   and its `.line` chunks against retail.  Writing a source under `src/` that matches nothing is not
   promotion, and it is not silent either: a source with no measured pair in its target's
   `tu_builds`, or a `tu_builds` entry whose source is gone, is a configuration error (exit 2)
   rather than a silently unchanged image.  Every component of the verdict is load-bearing — the
   payloads on the tail edge are the *compiler's* bytes, not retail's databin under the same name,
   and `tests/test_m2_sys_scf.py` asserts exactly that, for `.debug` and for `.line`.

7. **Reproduce the measurement, don't guess it.**  Which compiler build and flags reproduce a unit is
   *measured*: `python3 tools/toolchain/select_build.py --tu <file>` prints every candidate with its
   verdict for text/debug/line, and the pair that wins is recorded next to the source it belongs to
   in the *target's* `tu_builds` (`config/targets.py`) — per target, because a pair measured against
   one retail binary says nothing about another.  The same holds for the geometry, which lives in the
   same descriptor: those numbers were read out of that target's retail ELF's own headers, not
   chosen.  A target whose geometry has not been measured yet cannot be configured at all —
   `geometry_required()` stops the tool and names it, rather than splitting one game's bytes at
   another game's addresses.

8. **`python3 -m pytest -q` is part of the loop, not a formality.**  A green suite is what makes the
   next change safe: the tests run the real tools (splat, the assembler, the linker, the compiler
   under wibo), not stubs.  The suite takes roughly nine minutes.

9. **A promoted unit contributes code and debug bytes — and nothing else.**  `compile.py` links
   only the object's `.text`; its `.debug`/`.line` payloads replace the retail databins of the
   chunks the unit owns, and the object's data sections are not linked at all.  So a unit's
   *globals* contribute no bytes: `pscf` in `src/sys/sys_scf.c` is the standing example — the
   image's `pscf` lives in the `.bss` split at `0x002A2A78` (NOLOAD: it has no file byte at all)
   because retail put it there, and the definition in the C source is simply not linked.
   Reconstructing a unit's *data* therefore needs a mechanism this build does not have yet; do
   not "fix" a mismatching datum by editing its definition, because nothing is reading it.
   The relocations `compile.py` applies are exactly `R_MIPS_32`, `R_MIPS_26` and
   `R_MIPS_GPREL16`; any other kind (a `R_MIPS_HI16`/`R_MIPS_LO16`-addressed access, say) raises
   `Unusable` and stops the build rather than being placed by guesswork.

10. **A generated header compiles as C, and a named type is defined once.**  A use is
    `struct <tag> *`, `union <tag> *` or `enum <tag>`, never a bare tag: CodeWarrior labels every
    compile unit `LANG_CPLUSPLUS` even for a `.c` file, and DWARF 1 resolves typedefs away, so
    `struct <tag>` is the only spelling the evidence offers.  `include/types/<tag>.h` holds the one
    definition of that type (with its offsets, the DIE it came from, the units that declare it and a
    digest of its layout), `include/types.h` includes them all, and `include/src/<unit>.h` is one
    unit: the shared types it includes, its own anonymous types, its globals and its prototypes.  An
    anonymous type (`@anon0..24` — DWARF's *per-unit* numbering, so the same name is a different
    type in a different unit) stays in the unit that declares it, as `anon_<N>_<unit>`; a named type
    whose layout contains one spells that member out inline, and a named type two units declare
    *differently* fails the oracle by name instead of picking a layout.  Check a header with the
    original compiler, never a host `cc`:
    `python3 tools/toolchain/compile.py --syntax-only --include include <probe.c> -c -lang c -O3 -g`.
    A promoted unit does **not** include one yet: adding an `#include` changes the unit's debug
    bytes — measured on `sys_scf.c`, the same `.text` but 240 -> 237 bytes of `.debug` and a moved
    `.line` table, because the unit's own declaration is what puts its statements on retail's lines
    — so reproducing retail's own include graph is a generator problem, not a missing include.

## Where things live

| path | what it is |
|---|---|
| `ddr` | the command surface: oracle, build, verify, diff, iso |
| `config/targets.py` | **the target descriptor**: each target's ELF + G1 pin, image + G3 pin, config dir, measured geometry and per-unit build pairs — the only place a target's facts are written down |
| `configure.py` | manifests → splat inputs → `build.ninja`, the `ld` script and `objdiff.json` (for the target `--target` names) |
| `tools/oracle/**` | the vendored DWARF 1 reader and the emitters that produce the manifests and headers |
| `tools/toolchain/**` | fetch/probe/verify the toolchain, and `compile.py`, the `cc` rule's program |
| `tools/verify/**`, `tools/iso/**` | G1/G2 and the disc-image splice, each read through its target |
| `tools/diff/**` | the two objects `ddr diff` compares: the retail bytes of the symbol under work, emitted under its own name into `build/diff/`, and the stand-in an unpromoted unit's split needs |
| `config/<target>/**` | the oracle's artifacts and `ghidra_functions.json`, plus the pinned digests (the registered target's config arrives in Tasks 4–6) |
| `include/types/**`, `include/types.h` | one named type each, defined once — generated |
| `include/src/**` | one header per translation unit, generated |
| `src/**` | the C being reconstructed — the only tree written by hand |
| `docs/` | the spec, the plan, and one document per closed milestone |

`AGENTS.md` (this file) is the operating contract; `README.md` is the front door;
`docs/milestones/*.md` records the evidence each milestone closed on.
