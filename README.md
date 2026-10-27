# DDR Extreme 2 (US) preview — matching decompilation

A **matching decompilation** of the *Dance Dance Revolution Extreme 2 (US)* preview for the
PlayStation 2: `SLUS_211.74`, 7,725,036 bytes, sha256
`ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd`.

"Matching" is literal. The C compiles with the retail compiler and links into an ELF **byte-identical
to retail's** — code, debug sections, line tables, headers — and splicing that ELF back into the disc
image reproduces the image byte for byte. A unit counts only when its `.text`, `.debug` chunk and
`.line` chunks all match.

**No copyrighted assets are included.** This repository ships no game data, no retail code and no
disassembly of retail code. You supply the retail ELF and the disc image; they belong in the
gitignored `orig/` and `disc/`, are never committed and never redistributed. What is committed is
*measurement* — addresses, sizes, digests, generated headers — plus the C we wrote. The compiler is
proprietary: `tools/toolchain/fetch.py` downloads and hash-verifies it into the gitignored
`toolchain/`. See [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md).

![Translation-unit heatmap — one square per unit, green means promoted](docs/status.svg)

## Progress

<!-- status:start -->

**Overall: 76 / 249 translation units promoted (30.5%); 421 / 4,463 functions reconstructed (9.43%); 106,160 / 1,631,596 code bytes reconstructed (6.51%).**

Green means a unit is **promoted** — this is not a draft count.  It has a source at its manifest path, a `tu_builds` row recording the compiler and flags it was measured with, and a green `./ddr verify --tu` verdict: its `.text` span, its `.debug` chunk and its `.line` chunks are retail's bytes.  Amber is **partial** — a draft named like the unit exists on some branch, or a source exists without a `tu_builds` row (or its verdict is not green).  Grey is **untouched**.

**Code bytes are function sizes declared by the splits** (`nonmatching <fn>, 0xNN`), so debug information and data are excluded; a promoted unit contributes its pinned `.text` size (each function's span rounded to MWCC's 16-byte function alignment).  Split code no compile unit claims is `(library)` when the symbol has a name and `(unattributed)` when it is still `func_*`.

Regenerate both this table and [`docs/status.svg`](docs/status.svg) with `python3 tools/units/status.py --target ddrex2p`; `python3 tools/units/status.py --check` fails when either is stale.  The heatmap has one cell per translation unit, grouped by module; hover a cell for its path, code bytes and state.

| module | units | promoted units | functions | reconstructed functions | code bytes | reconstructed bytes | units % | functions % | bytes % |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| `AM` | 18 | 8 | 182 | 44 | 67,808 | 9,424 | 44.4% | 24.18% | 13.90% |
| `common` | 15 | 8 | 147 | 62 | 44,708 | 18,624 | 53.3% | 42.18% | 41.66% |
| `CS` | 118 | 22 | 814 | 116 | 433,844 | 34,096 | 18.6% | 14.25% | 7.86% |
| `eyetoy` | 3 | 0 | 30 | 0 | 13,300 | 0 | 0.0% | 0.00% | 0.00% |
| `fft` | 1 | 0 | 9 | 0 | 12,084 | 0 | 0.0% | 0.00% | 0.00% |
| `gs` | 2 | 1 | 18 | 15 | 3,172 | 2,416 | 50.0% | 83.33% | 76.17% |
| `network` | 82 | 31 | 542 | 174 | 208,732 | 39,936 | 37.8% | 32.10% | 19.13% |
| `sound` | 4 | 3 | 20 | 3 | 7,520 | 1,264 | 75.0% | 15.00% | 16.81% |
| `sys` | 2 | 2 | 4 | 4 | 80 | 96 | 100.0% | 100.00% | 120.00% |
| `(root)` | 3 | 1 | 43 | 3 | 7,232 | 304 | 33.3% | 6.98% | 4.20% |
| `(external)` | 1 | 0 | 7 | 0 | 1,420 | 0 | 0.0% | 0.00% | 0.00% |
| `(library)` | 0 | 0 | 439 | 0 | 117,800 | 0 | 0.0% | 0.00% | 0.00% |
| `(unattributed)` | 0 | 0 | 2,208 | 0 | 713,896 | 0 | 0.0% | 0.00% | 0.00% |
| **total** | **249** | **76** | **4,463** | **421** | **1,631,596** | **106,160** | **30.5%** | **9.43%** | **6.51%** |

Legend: green = promoted (G2 green); amber = partial (draft or source, unproven); grey = untouched.

<!-- status:end -->

## Quick start

```sh
python3 tools/toolchain/check_deps.py                   # what is missing, and how to get it
python3 tools/toolchain/fetch.py 2.4-001213 3.0-011126  # compilers, hash-verified
cp /path/to/your/SLUS_211.74 orig/                      # you supply this
./ddr build && ./ddr verify                             # G1: byte-identical to retail
```

## Hosts

|host|support|compiler runs|
|---|---|---|
|macOS (arm64, x86_64)|tested|`wibo-macos`, fetched and digest-pinned|
|Linux (x86_64)|supported|`wibo-x86_64`, fetched and digest-pinned|
|Windows (x86_64)|supported, native|`mwccps2.exe` directly — no wibo, no WSL|

All three need Python 3.11+, `ninja`, a MIPS binutils (`ld`, `objcopy`, `as`), `splat` and optionally
`objdiff-cli` for `./ddr diff`. `python3 tools/toolchain/check_deps.py` names every missing tool with
the command that provides it.

**macOS**

```sh
brew install mips-linux-gnu-binutils ninja
python3 -m pip install --user 'splat64[mips]' pytest
curl -sL -o ~/.local/bin/objdiff-cli \
  https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-macos-arm64
chmod +x ~/.local/bin/objdiff-cli
```

**Linux (x86_64)**, Debian/Ubuntu names:

```sh
sudo apt install build-essential ninja-build python3 python3-pip binutils-mips-linux-gnu
python3 -m pip install --user 'splat64[mips]' pytest
curl -sL -o ~/.local/bin/objdiff-cli \
  https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-linux-x86_64
chmod +x ~/.local/bin/objdiff-cli
```

**Windows (x86_64)** — native tooling; WSL and msys2 are not needed:

```bat
winget install Python.Python.3.12 Ninja-build.Ninja
python -m pip install --user splat64[mips] pytest
:: objdiff-cli-windows-x86_64.exe from the same release page, on %PATH%
python ddr build
python ddr verify
```

`ddr` is a Python script, so on Windows call it as `python ddr <verb>`. The CodeWarrior tools are
Windows binaries, so nothing is emulated there.

## Supplying the retail files

* `orig/SLUS_211.74` — the retail ELF from your own copy of the preview. Its geometry and generated
  config are committed (`config/targets.py`, `config/ddrex2p/`); `./ddr oracle` regenerates the config
  from the copy you place.
* the disc image — the G3 reference. Its path and pinned sha256 live in `config/targets.py`; without
  it `./ddr verify --iso` skips with an explicit "nothing was compared".

## Gates

|gate|command|proves|
|---|---|---|
|G1|`./ddr verify`|the built ELF's sha256 equals the retail ELF's|
|G2|`./ddr verify --tu <unit>`|that unit's `.text`, `.debug` chunk and `.line` chunks equal retail's|
|G3|`./ddr verify --iso`|splicing the built ELF into the image reproduces the image|

A red gate is never worked around: the tool names the unit, function, compile unit and chunk that own
the first divergent byte, and that is where the fix goes.

## Everyday commands

```sh
./ddr build                     # configure.py + ninja: split, assemble, compile, link, G1
./ddr verify --tu sys_scf       # G1 + that unit's promotion verdict
./ddr diff sysInitScf sys_scf   # objdiff-cli: retail's bytes for one symbol against our object
python3 -m pytest -q tests      # the suite — it runs the real tools, not stubs
```

While reconstructing a unit: `tools/units/line_map.py` (retail's statement structure), `twins.py`
(bodies already written elsewhere), `measure.py` (per-body word diff), `m2c_draft.py` (first draft,
jump tables fed), `slots.py` (callee-saved and stack-slot map), `permute.py` (bounded search). The
rules behind them are [`docs/unit-work.md`](docs/unit-work.md).

## Where things live

`ddr` is the command surface (`oracle`, `build`, `verify`, `diff`, `iso`). `config/targets.py` is the
only place a target's facts are written down — retail ELF and pin, image and pin, config directory,
measured geometry, and the compiler/flag pair each promoted unit was measured against. `tools/oracle/`
is the DWARF 1 reader and the header/manifest emitters, `tools/toolchain/` the compiler plumbing.
`src/**` is the C we write; `include/**`, `asm/**`, `build.ninja` are generated and never hand-edited.

[`AGENTS.md`](AGENTS.md) is the operating contract — the rules, the loop, and why each exists;
[`docs/unit-work.md`](docs/unit-work.md) is the unit rulebook;
[`docs/superpowers/specs/`](docs/superpowers/specs) holds the design and
[`docs/milestones/`](docs/milestones) the evidence each milestone closed on.
