# DDR Extreme 2 (US) preview

![Translation-unit heatmap](docs/status.svg)

A matching decompilation of *Dance Dance Revolution Extreme 2 (US)* for the PlayStation 2.

This repository does **not** contain any game assets, retail code or disassembly. An existing copy of the game is required.

Supported version: `SLUS_211.74`, sha256 `ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd`.

## Requirements

Python 3.11+, ninja, a MIPS binutils, `splat` and `objdiff-cli`. `python3 tools/toolchain/check_deps.py` names anything missing. wibo is fetched automatically on macOS and Linux.

### macOS

```sh
brew install mips-linux-gnu-binutils ninja
python3 -m pip install --user 'splat64[mips]' pytest
curl -sL -o ~/.local/bin/objdiff-cli \
  https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-macos-arm64
chmod +x ~/.local/bin/objdiff-cli
```

### Linux (x86_64)

```sh
sudo apt install build-essential ninja-build binutils-mips-linux-gnu
python3 -m pip install --user 'splat64[mips]' pytest
curl -sL -o ~/.local/bin/objdiff-cli \
  https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-linux-x86_64
chmod +x ~/.local/bin/objdiff-cli
```

### Windows (x86_64)

Native tooling: WSL and msys2 are not needed, and the CodeWarrior tools are Windows binaries, so nothing is emulated.

```bat
winget install Python.Python.3.12 Ninja-build.Ninja
python -m pip install --user splat64[mips] pytest
```

Put `objdiff-cli-windows-x86_64.exe` from the same release on `%PATH%`. Call the driver as `python ddr <verb>`.

## Building

```sh
python3 tools/toolchain/fetch.py 2.4-001213 3.0-011126
cp /path/to/your/SLUS_211.74 orig/
./ddr build
./ddr verify
```

The compilers are fetched and hash-verified into the gitignored `toolchain/`. The disc image is needed only for G3: place it at its path in `config/targets.py` and run `./ddr verify --iso`.

## Verifying

| gate | command | proves |
|---|---|---|
| G1 | `./ddr verify` | the built ELF's sha256 equals the retail ELF's |
| G2 | `./ddr verify --tu <unit>` | that unit's `.text`, `.debug` chunk and `.line` chunks equal retail's |
| G3 | `./ddr verify --iso` | splicing the built ELF into the image reproduces the image |

A red gate is never worked around: the tool names the unit, function and chunk that own the first divergent byte.

## Progress

<!-- status:start -->

**77/249 (30.9%) units · 424/4,463 (9.5%) functions · 104,696/1,631,596 (6.4%) code bytes reconstructed** — green = promoted, amber = partial, grey = untouched; `tools/units/status.py` counts only what `./ddr verify --tu` confirms.

| module | units | functions | reconstructed bytes |
|---|---:|---:|---:|
| `AM` | 8/18 (44.4%) | 44/182 (24.2%) | 9,172/67,808 (13.5%) |
| `common` | 8/15 (53.3%) | 62/147 (42.2%) | 18,320/44,708 (41.0%) |
| `CS` | 23/118 (19.5%) | 119/814 (14.6%) | 34,544/433,844 (8.0%) |
| `gs` | 1/2 (50.0%) | 15/18 (83.3%) | 2,332/3,172 (73.5%) |
| `network` | 31/82 (37.8%) | 174/542 (32.1%) | 38,708/208,732 (18.5%) |
| `sound` | 3/4 (75.0%) | 3/20 (15.0%) | 1,244/7,520 (16.5%) |
| `sys` | 2/2 (100.0%) | 4/4 (100.0%) | 80/80 (100.0%) |
| `(root)` | 1/3 (33.3%) | 3/43 (7.0%) | 296/7,232 (4.1%) |

<!-- status:end -->

## Everyday commands

```sh
./ddr build                     # configure + ninja: split, assemble, compile, link, G1
./ddr verify --tu sys_scf       # G1 plus that unit's promotion verdict
./ddr diff sysInitScf sys_scf   # retail's bytes for one symbol against our object
python3 -m pytest -q tests      # the suite runs the real tools, not stubs
```

Unit work: `tools/units/line_map.py`, `twins.py`, `measure.py`, `m2c_draft.py`, `slots.py`, `permute.py`.

## Docs

- [`AGENTS.md`](AGENTS.md) — the operating contract: the rules, the loop, why each exists.
- [`docs/unit-work.md`](docs/unit-work.md) — how a unit is promoted, and the measured codegen rules.
- [`docs/`](docs) — the design, the milestones, and the evidence each milestone closed on.

## Credits

- [splat](https://github.com/ethteck/splat), [wibo](https://github.com/decompals/wibo), [objdiff](https://github.com/encounter/objdiff), [m2c](https://github.com/matt-kempster/m2c), [decomp-permuter](https://github.com/simonlindholm/decomp-permuter), and the [dtk-template](https://github.com/encounter/dtk-template) layout.
