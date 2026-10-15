# ddrex-decomp — DDRMAX2 (US) matching decompilation

A **matching decompilation** of *DDRMAX2: Dance Dance Revolution* (USA) for the PlayStation 2,
retail ELF `SLUS_207.11` — 2,512,980 bytes, sha256
`a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc`.

"Matching" means the reconstruction is *proved*, not judged: the built ELF must be byte-identical to
the retail one, debug sections and all, and writing it back into the retail disc image must reproduce
that image byte for byte.  The build is byte-identical **before a single line of C is written** —
everything not yet reconstructed is assembled from the retail bytes themselves, and a generated
layout pins every function and datum at its retail address, so a mistake is attributable to the one
unit being edited.

| milestone | what it closed on | document |
|---|---|---|
| M1 — oracle, splat config, pinned link, ISO layer | `./ddr build` reproduces `out/SLUS_207.11`; `./ddr verify --iso` reproduces the disc image; **zero C written** | [`docs/milestones/m1-skeleton.md`](docs/milestones/m1-skeleton.md) |
| M2 — the first promoted translation unit | `src/sys/sys_scf.c`: its `.text`, its `.debug` chunk and its `.line` chunks all match retail | [`docs/milestones/m2-sys-scf.md`](docs/milestones/m2-sys-scf.md) |

The design is in [`docs/superpowers/specs/2026-10-14-ddrmax2-us-decomp-design.md`](docs/superpowers/specs/2026-10-14-ddrmax2-us-decomp-design.md),
the plan that built this skeleton in
[`docs/superpowers/plans/2026-10-14-ddrmax2-us-oracle-toolchain-skeleton.md`](docs/superpowers/plans/2026-10-14-ddrmax2-us-oracle-toolchain-skeleton.md),
and the working contract — the rules, the loop, and why each rule exists — is
[`AGENTS.md`](AGENTS.md).  Read that one before editing anything.

## The gates

Every claim about this repository is one of three machine-checkable digests.  Each gate checks its
*reference* against the digest pinned in `config/usam2/checksums.txt` **before** comparing, so a
corrupted or wrong-version input fails loudly instead of being compared with a build.

| gate | command | what it proves |
|---|---|---|
| **G1** binary | `./ddr verify` | `out/SLUS_207.11` sha256 == the retail ELF's — the whole file, `.debug`/`.line`/`.comment`/headers included |
| **G2** per-TU | `./ddr verify --tu sys_scf` | for a promoted unit: its `.text` span, its `.debug` chunk and its `.line` chunks against retail, naming the first divergence — this is the **promotion rule**: code *and* debug bytes |
| **G3** disc | `./ddr verify --iso` | splicing the built ELF into a copy of the retail image at byte offset `0x92000` (LBA 292) reproduces the image's sha256 |

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

* `orig/SLUS_207.11` — the retail ELF, extracted from your own copy of the disc.
* `disc/DDRMAX2 Dance Dance Revolution (USA).iso` — the retail image, for G3.  A 1.24 GB copy of the
  ELF inside it; if you mount the image at the path recorded in `tools/iso/reinsert.py` you can use
  bare `./ddr verify --iso` and let the tool find it.

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
python3 -m pytest -q              # the suite: real splat, real assembler, real compiler, ~9 min
```

`./ddr build` takes about a minute from scratch (4,102 ninja edges, 4,092 of them splits) and less
when only the unit you edited changed.  `./ddr diff <symbol> <tu>` shows objdiff's instruction-level
view of one function; G1 and the per-TU verdicts are the arbiters (see the caveat at the end of
`docs/milestones/m2-sys-scf.md`).

## How it works

```
orig/SLUS_207.11 ──► ./ddr oracle ──► config/usam2/{cus,debug_chunks,symbol_addrs}.json/txt
                                      include/src/**        (one header per translation unit)
config/usam2/**   ──► configure.py ──► asm/** (splat splits), build/SLUS_207.11.ld,
                                      build.ninja, objdiff.json
asm/**, src/**    ──► ninja ─────────► build/** objects ──► ld ──► objcopy ──► cat ──► out/SLUS_207.11 ──► G1
                                                                        out/rebuilt.iso ──► G3
```

* `tools/oracle/**` — the vendored DWARF 1 reader plus the emitters that turn the retail ELF's own
  debug information into the manifests and headers.  Names and line numbers come from the target, not
  from a guess.
* `configure.py` — splits the ELF with splat and writes the ninja graph, the linker script that pins
  every address, and the objdiff project the CI reports from.
* `tools/toolchain/compile.py` — the `cc` rule's program: it runs `mwccps2` under wibo, reads the
  Metrowerks object with the oracle's own reader, and places the `.text`, `.debug` and `.line` bytes
  the compiler wrote (mainline binutils cannot read those objects, and `mwldps2` does not keep the
  debug sections — R23).
* `.github/workflows/` — `build` (toolchain, configure, ninja, G1), `objects` (the objdiff object
  graph) and `progress` (the objdiff report); all three run on macOS runners and fetch the retail ELF
  from a URL kept in a repository secret, because the repository never contains it.

## Licence and provenance

The vendored oracle code (`tools/oracle/**`) is third-party MIT/Apache-2.0 and is listed, with its
upstream hashes, in [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md).  The retail binary, the disc
image and the CodeWarrior toolchain belong to their owners and are never redistributed here; the
repository holds only the artifacts of *this* build and the code that produces them.
