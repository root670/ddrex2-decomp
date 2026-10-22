# ddrex-decomp — DDR Extreme 2 (US) preview matching decompilation

A **matching decompilation** of the *DDR Extreme 2 (US)* preview for the PlayStation 2, retail ELF
`SLUS_211.74`, sha256 `ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd`
(copied to the gitignored `orig/SLUS_211.74`).

**One target is registered, in one place**: [`config/targets.py`](config/targets.py) holds its retail
ELF and G1 pin, its disc image and G3 pin, its config directory, its *measured* geometry and the
compiler/flag pair each promoted unit was measured against.  Every tool reads that descriptor and
`--target <name>` selects it (default: the registered target, so a bare `./ddr build` means the binary
above); no other file spells a target name or a retail path.  Adding a target is a `Target(...)` plus
one line in the registry there.

The binary and its disc image are **not in the tree** — retail files are never committed, so you
supply both (below) — but the *measurement* of that binary is: `config/ddrex2p/` holds its generated
config, its pins and its compile-unit and debug-chunk maps, and the descriptor holds the segment
list, the chunked sections' lengths and the boot ELF's offset in the image.  Every verb that needs a
file you have not supplied stops with the name of the file it is missing instead of guessing.

"Matching" means the reconstruction is *proved*, not judged: the built ELF must be byte-identical to
the retail one, debug sections and all, and writing it back into the retail disc image must reproduce
that image byte for byte.  The build is byte-identical **before a single line of C is written** —
everything not yet reconstructed is assembled from the retail bytes themselves, and a generated
layout pins every function and datum at its retail address, so a mistake is attributable to the one
unit being edited.

| milestone | what it closed on | document |
|---|---|---|
| M1–M2 (removed target) | the skeleton and the first promoted unit of the previous target: oracle, splat config, pinned link, ISO layer, and one unit matching on `.text` + `.debug` + `.line` | records were removed with that target |
| M2 (this target) | the first promoted unit on `ddrex2p`: `sys_scf.c` matching on `.text` + `.debug` + `.line`, and the compiler pair it was measured with | [`docs/milestones/ddrex2p-m2.md`](docs/milestones/ddrex2p-m2.md) |
| library sourcing (this target) | which SDK archive revision reproduces each library, byte-wise, names only | [`docs/milestones/m3-library-sourcing.md`](docs/milestones/m3-library-sourcing.md) |

The retarget is specified in [`docs/superpowers/specs/2026-10-16-ddrex2-preview-retarget-design.md`](docs/superpowers/specs/2026-10-16-ddrex2-preview-retarget-design.md)
and planned in [`docs/superpowers/plans/2026-10-16-ddrex2-preview-retarget.md`](docs/superpowers/plans/2026-10-16-ddrex2-preview-retarget.md)
(the earlier skeleton plan kept it historical record); the working contract — the rules, the loop, and
why each rule exists — is [`AGENTS.md`](AGENTS.md).  Read that one before editing anything.

## Progress

<!-- status:start -->

**Overall: 47 / 249 translation units promoted (18.9%); 236 / 4,463 functions reconstructed (5.29%); 51,408 / 1,631,596 code bytes reconstructed (3.15%).**

Green means a unit is **promoted** — this is not a draft count.  It has a source at its manifest path, a `tu_builds` row recording the compiler and flags it was measured with, and a green `./ddr verify --tu` verdict: its `.text` span, its `.debug` chunk and its `.line` chunks are retail's bytes.  Amber is **partial** — a draft named like the unit exists on some branch, or a source exists without a `tu_builds` row (or its verdict is not green).  Grey is **untouched**.

**Code bytes are function sizes declared by the splits** (`nonmatching <fn>, 0xNN`), so debug information and data are excluded; a promoted unit contributes its pinned `.text` size (each function's span rounded to MWCC's 16-byte function alignment).  Split code no compile unit claims is `(library)` when the symbol has a name and `(unattributed)` when it is still `func_*`.

Regenerate both this table and [`docs/status.svg`](docs/status.svg) with `python3 tools/units/status.py --target ddrex2p`; `python3 tools/units/status.py --check` fails when either is stale.  The heatmap has one cell per translation unit, grouped by module; hover a cell for its path, code bytes and state.

| module | units | promoted units | functions | reconstructed functions | code bytes | reconstructed bytes | units % | functions % | bytes % |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| `AM` | 18 | 5 | 182 | 34 | 67,808 | 6,560 | 27.8% | 18.68% | 9.67% |
| `common` | 15 | 3 | 147 | 11 | 44,708 | 4,208 | 20.0% | 7.48% | 9.41% |
| `CS` | 118 | 16 | 814 | 62 | 433,844 | 20,608 | 13.6% | 7.62% | 4.75% |
| `eyetoy` | 3 | 0 | 30 | 0 | 13,300 | 0 | 0.0% | 0.00% | 0.00% |
| `fft` | 1 | 0 | 9 | 0 | 12,084 | 0 | 0.0% | 0.00% | 0.00% |
| `gs` | 2 | 0 | 18 | 0 | 3,172 | 0 | 0.0% | 0.00% | 0.00% |
| `network` | 82 | 20 | 542 | 121 | 208,732 | 18,400 | 24.4% | 22.32% | 8.82% |
| `sound` | 4 | 1 | 20 | 3 | 7,520 | 1,264 | 25.0% | 15.00% | 16.81% |
| `sys` | 2 | 1 | 4 | 2 | 80 | 64 | 50.0% | 50.00% | 80.00% |
| `(root)` | 3 | 1 | 43 | 3 | 7,232 | 304 | 33.3% | 6.98% | 4.20% |
| `(external)` | 1 | 0 | 7 | 0 | 1,420 | 0 | 0.0% | 0.00% | 0.00% |
| `(library)` | 0 | 0 | 439 | 0 | 117,800 | 0 | 0.0% | 0.00% | 0.00% |
| `(unattributed)` | 0 | 0 | 2,208 | 0 | 713,896 | 0 | 0.0% | 0.00% | 0.00% |
| **total** | **249** | **47** | **4,463** | **236** | **1,631,596** | **51,408** | **18.9%** | **5.29%** | **3.15%** |

Legend: green = promoted (G2 green); amber = partial (draft or source, unproven); grey = untouched.

<!-- status:end -->

## The gates

Every claim about this repository is one of three machine-checkable digests.  Each gate checks its
*reference* against the digest pinned in the target's `config/<target>/checksums.txt` **before**
comparing, so a corrupted or wrong-version input fails loudly instead of being compared with a
build — and a reference *no* record names is refused outright (exit 2) rather than compared with
itself, unless `--allow-unpinned-reference` says so in so many words on the success line.  A
target's inputs are its own: `./ddr --target ddrex2p verify` reads that target's binary and pin, and a
target whose binary has not been placed yet is a loud stop rather than a fallback to another one.

| gate | command | what it proves |
|---|---|---|
| **G1** binary | `./ddr verify` | the built image `out/<elf>` sha256 == the retail ELF's — the whole file, `.debug`/`.line`/`.comment`/headers included |
| **G2** per-TU | `./ddr verify --tu sys_scf` | for a promoted unit: its `.text` span, its `.debug` chunk and its `.line` chunks against retail, naming the first divergence — this is the **promotion rule**: code *and* debug bytes |
| **G3** disc | `./ddr verify --iso` | splicing the built ELF into a copy of the target's retail image, at the offset its descriptor measured, reproduces that image's sha256 |

A red gate is never worked around; on a red G1 the tool names the translation unit, the function,
the compile unit and the chunk that own the first divergent byte, and that is where the fix goes.

## Building it

**Prerequisites** (macOS; the compiler runs under [wibo](https://github.com/decompals/wibo), which
is fetched for you):

```bash
brew install mips-linux-gnu-binutils ninja
python3 -m pip install --user 'splat64[mips]' pytest
curl -sL -o ~/.local/bin/objdiff-cli \
  https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-macos-arm64 \
  && chmod +x ~/.local/bin/objdiff-cli
```

`python3 tools/toolchain/check_deps.py` verifies all of them and records the versions it observed in
`toolchain/PROVENANCE.txt`; a missing tool is reported with the exact command that provides it.

**The retail files are yours to supply** — they are never committed (see `THIRD_PARTY_NOTICES.md`
and `AGENTS.md` rule 5):

* `orig/SLUS_211.74` — the retail ELF (7,725,036 bytes), copied out of your own copy of the preview
  image.  Its measured geometry and its generated config are committed (`config/targets.py`,
  `config/ddrex2p/`), and `./ddr oracle` regenerates the config from the copy you place here.
* the *DDR Extreme 2 (May 10, 2005 prototype)* image — the G3 reference.  Both paths, and the two
  sha256 digests they are pinned by, are recorded in `config/targets.py` (the image is the one the
  plan pinned: `70a90566…6cd652b`).  Mount it at the recorded path and bare `./ddr --target ddrex2p
  verify --iso` finds it; an absent image skips (exit 0) with an explicit "nothing was compared".

**The compiler** is proprietary and is fetched, hash-verified and extracted into the gitignored
`toolchain/`:

```bash
python3 tools/toolchain/fetch.py 2.4-001213 3.0-011126
```

`2.4-001213` is the required build (the retail `.comment` names the 2.4.1.01 *linker* family);
`3.0-011126` is the build the first promoted unit was measured against, so a full build needs both.

**Then:**

```bash
./ddr build                       # configure.py + ninja: split, assemble, link, tail, G1
./ddr verify                      # G1
./ddr verify --tu sys_scf         # the promotion rule for one unit
./ddr verify --iso                # G3 (skips cleanly when the image is not mounted)
python3 -m pytest -q              # the suite: real splat, real assembler, real compiler (~16 s today)
```

Any of those takes `--target <name>` (default: the registered target), before or after the
verb: `./ddr --target ddrex2p verify` is the same gate on the same files as `./ddr verify`.

`./ddr build` takes about a minute from scratch (4,102 ninja edges, 4,092 of them splits) and less
when only the unit you edited changed.  `./ddr diff <symbol> <tu>` shows objdiff's instruction-level
view of one function: the target side is the *retail bytes* of that symbol (emitted into
`build/diff/`, which no link edge reads), the base side is the object under edit -- the unit's C
object, or for a unit with no C the split's own bytes without splat's `.NON_MATCHING` alias, which
objdiff would otherwise refuse to score.  Both sides are printed with what they are, and a
percentage is printed only when objdiff really compared the symbol; G1 and the per-TU verdicts are
the arbiters (see the caveat at the end of `docs/milestones/ddrex2p-m2.md`).

## How it works

```
orig/<target ELF> ──► ./ddr oracle ──► config/<target>/{cus,debug_chunks,symbol_addrs}.json/txt
                                      include/src/**        (one header per translation unit)
config/<target>/** ──► configure.py ─► asm/** (splat splits), build/<elf>.ld,
                                      build.ninja, objdiff.json
asm/**, src/**     ──► ninja ────────► build/** objects ──► ld ──► objcopy ──► cat ──► out/<elf> ──► G1
                                                                        out/rebuilt.iso ──► G3
```

Every path above is the one `config/targets.py` gives the target `--target` names; with another
target the same pipeline splits `orig/<its ELF>` into `config/<name>/**` and gates
`out/<its ELF>`.  `asm/**`, `build/**`, `out/**` and `include/**` are single generated trees, so one
target is configured at a time (another target's config and pins stay on disk untouched).

* `config/targets.py` — the target descriptor: the ELF and its G1 pin, the disc image and its G3 pin,
  the config directory, the measured geometry (loadable segment, trailing sections, chunk sizes,
  disc-image offset) and the per-unit compiler/flag pairs.  Adding a target is adding a descriptor.
* `tools/oracle/**` — the vendored DWARF 1 reader plus the emitters that turn the retail ELF's own
  debug information into the manifests and headers.  Names and line numbers come from the target, not
  from a guess.
* `configure.py` — splits the target's ELF with splat and writes the ninja graph, the linker script
  that pins every address, and the objdiff project the CI reports from.
* `tools/toolchain/compile.py` — the `cc` rule's program: it runs `mwccps2` under wibo, reads the
  Metrowerks object with the oracle's own reader, and places the `.text`, `.debug` and `.line` bytes
  the compiler wrote (mainline binutils cannot read those objects, and `mwldps2` does not keep the
  debug sections — R23).
* `.github/workflows/` — `build` (toolchain, configure, ninja, G1), `objects` (the objdiff object
  graph) and `progress` (the objdiff report); all three run on macOS runners and fetch the retail ELF
  from a URL kept in a repository secret, because the repository never contains it.  The progress
  report is objdiff's own object-level arithmetic, **not** the gates' verdict: its
  `matched_data_percent: 100.0` is a percentage over splat's target object (this build reconstructs
  no data at all), and its `matched_code` reads 0.0007% for a tree whose linked `sys_scf` bytes *are*
  retail's — `./ddr verify --tu` is what proves a unit (`AGENTS.md` rules 6 and 9).

## Licence and provenance

The vendored oracle code (`tools/oracle/**`) is third-party MIT/Apache-2.0 and is listed, with its
upstream hashes, in [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md).  The retail binary, the disc
image and the CodeWarrior toolchain belong to their owners and are never redistributed here; the
repository holds only the artifacts of *this* build and the code that produces them.
