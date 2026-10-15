# M1 — the skeleton: a byte-identical build with zero C written

M1's exit gate is the design's G1 and G3 with **no C source in the tree at all**: everything
the retail ELF contains is either split assembly assembled back byte for byte, or a databin
copied out of the retail file.  The milestone closed on two commits:

| commit | what it closed |
|---|---|
| `952541e` *build: pinned link reproduces the retail ELF byte for byte (M1)* | `./ddr build` produces `out/SLUS_207.11`; G1 green |
| `449023e` *iso: reinsert the built ELF and verify the rebuilt image hash* | `./ddr verify --iso` reproduces the disc image; G3 green |

"Zero C written" is checkable, not recalled: `git ls-tree -r 952541e --name-only | grep -c '^src/'`
is **0**.  The image digest below is unchanged by the later promotion of `sys_scf.c` (M2) — a
promoted unit's bytes *are* retail's bytes, which is what its verdict proves — so the same two
numbers are what `./ddr verify` and `./ddr verify --iso` print today.

## The observed digests

```
$ ./ddr build
…
[4100/4100] g1 out/SLUS_207.11
ok: out/SLUS_207.11 is a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc
real    1m10.170s

$ ./ddr verify --tu sys_scf --iso
G1 ok: out/SLUS_207.11 is a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc
src/sys/sys_scf.c: text ok (VA 0x0021C410-0x0021C450, 64 bytes)
src/sys/sys_scf.c: debug chunk ok (1 chunk(s), 646 bytes)
src/sys/sys_scf.c: line chunk ok (2 chunk(s), 96 bytes)
G3: splicing out/SLUS_207.11 into /Volumes/My Passport/PS2 Games/DDRMAX2 Dance Dance Revolution (USA).iso -> out/rebuilt.iso
G3 ok: out/rebuilt.iso is b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8 (1244823552 bytes, matches /Volumes/My Passport/PS2 Games/DDRMAX2 Dance Dance Revolution (USA).iso)
```

| artifact | size | sha256 |
|---|---|---|
| `out/SLUS_207.11` (the built ELF) | 2,512,980 B | `a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc` |
| `out/rebuilt.iso` (the image with that ELF written at `0x92000`) | 1,244,823,552 B | `b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8` |

Both records are in `config/usam2/checksums.txt`, and both gates check their *reference* against
its record before comparing (`./ddr verify` refuses a retail binary that is not the pinned file;
`--iso` refuses an image whose name matches a pin and whose digest does not) — the pin is the
criterion, not the agreement of the pair.

## What the build actually did

`./ddr build` is `python3 configure.py --config usam2` followed by `ninja`, and the graph is
4,102 edges:

```
$ python3 configure.py --config usam2
configure: 4092 splits, 3603 code splits at 0x100000, 487 tail databins, 15 link aliases, build.ninja written
```

* 3,603 code splits (`asm/nonmatchings/main/*.s`) assemble with `mips-linux-gnu-as`, each
  pinned at its retail address by the generated `build/SLUS_207.11.ld`.  Two of the 489
  splits under `asm/data/` are linked as well — `elf_header` (the file's first `0x80` bytes)
  and the bss marker — and the other 487 are splat's databin splits, assembled for the
  `objects` target only: the tail's bytes are not linked at all.
* the file's non-loadable tail — 799,188 bytes of `.debug`, `.line`, `.comment`, section
  headers and padding — is concatenated from splat's own `build/assets/*.databin.bin`
  (487 of them, in manifest order), because `ld`/`objcopy` write only the sections a program
  header loads.
* `g1` is an edge with no output, so the gate runs on **every** build, not only when a file
  changed: `ninja` proves the image, `ninja objects` stops at the objects.

So the tools M1's build ran were `splat 0.50.1` (the split), the host binutils (assemble,
link, objcopy) and `ninja` — no C compiler at all.  The CodeWarrior builds were fetched and
verified in the same milestone (their driver `compile.py` and the `cc` rule arrive with M2).

## The toolchain, as observed

From `toolchain/PROVENANCE.txt`, which `tools/toolchain/fetch.py` and
`tools/toolchain/check_deps.py` write as they verify each artifact before it is extracted or
run:

| tool | version | verified by |
|---|---|---|
| splat | `splat 0.50.1` (spimdisasm 1.42.4), module `splat` | `python3 -m pip install --user 'splat64[mips]'` |
| `mips-linux-gnu-as` | GNU assembler 2.47.20260726 | `brew install mips-linux-gnu-binutils` |
| `mips-linux-gnu-ld` | GNU ld 2.47.20260726 | `brew install mips-linux-gnu-binutils` |
| `mips-linux-gnu-objcopy` | GNU objcopy 2.47.20260726 | `brew install mips-linux-gnu-binutils` |
| ninja | 1.13.2 | `brew install ninja` |
| objdiff-cli | 3.8.2 (`objdiff-cli-macos-arm64`) | release download, digested on use |
| `mwccps2` | 2.4-001213 (required), 3.0-011126 (the build M2 measured) | fetched from the decomp.me compiler releases, archive and members digested before extraction |
| wibo | 1.2.0 (Darwin x86_64) | fetched, digest pinned and re-checked before every execution |

The host-tool section of `PROVENANCE.txt` was observed on this machine at
`2026-10-15T07:08:38Z`.  Each compiler entry instead carries the time *that* fetch verified it
(`13:16:33Z` for `2.4-001213` and `3.0-011126` in the run that produced this file) and is rewritten
whenever the archive is re-fetched: the versions are what travel, the times are the record of a
check.  None of it is in the repository — `toolchain/` is gitignored and re-fetched, and these
records are the only thing that does.

## Reproducing it

```bash
brew install mips-linux-gnu-binutils ninja
python3 -m pip install --user 'splat64[mips]' pytest
python3 tools/toolchain/fetch.py 2.4-001213 3.0-011126
python3 tools/toolchain/check_deps.py          # records what it observed in toolchain/PROVENANCE.txt
# orig/SLUS_207.11 and the disc image come from your own copy of the game
./ddr oracle                                   # deterministic: reproduces what is committed
./ddr build                                    # configure + ninja: G1 at the end of the build
./ddr verify                                   # G1 again, on its own
./ddr verify --iso                             # G3, with the retail image mounted (bare --iso)
python3 -m pytest -q                           # the suite; ~9 minutes
```

`./ddr oracle` is idempotent — a fresh run reproduces every committed artifact under
`config/usam2/` and `include/src/**` byte for byte
(`tests/test_cli.py::test_oracle_regenerates_the_committed_artifacts_byte_for_byte`), which is
what makes "the manifests are the evidence" a statement about the binary rather than about
when someone last ran the tool.

## What M1 did not do

* **No C.** `src/` did not exist at `952541e`; M2 is the first promoted unit.
* **No library work.** The ~2,670 functions outside the DWARF-described range stay split
  assembly; identifying them is M4's problem, and it costs source, never byte-identity.
* **No behavioural gate.** G1/G3 are byte gates; booting the rebuilt image in PCSX2 is a smoke
  test, not evidence, and nothing in this repository claims otherwise.
* **No CI yet.** The three workflows under `.github/workflows/` landed with the operating
  contract (Task 13); until then the evidence above is a local run of the same commands.
