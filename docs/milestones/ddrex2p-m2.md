# M2 on the retargeted tree -- the first promoted unit: `src/sys/sys_scf.c`

M2's exit gate is the promotion rule: a translation unit counts as promoted only when its
**code**, its **debug bytes** and its **line bytes** match retail.  `sys_scf.c` is the first
unit on `ddrex2p`, and all three match:

```
$ ./ddr --target ddrex2p verify --tu sys_scf.c
G1 ok: out/SLUS_211.74 is ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd
src/sys/sys_scf.c: text ok (VA 0x001B3D30-0x001B3D70, 64 bytes)
src/sys/sys_scf.c: debug chunk ok (1 chunk(s), 652 bytes)
src/sys/sys_scf.c: line chunk ok (2 chunk(s), 116 bytes)
```

The unit's two functions, from this build's DWARF (`tools/oracle/dwarf1.py fn orig/SLUS_211.74
<name>`): `sysGetDateNotation` at `0x001B3D30`, 0x0C bytes, lines 50-51; `sysInitScf` at
`0x001B3D40`, 0x30 bytes, lines 24-43.  `0x001B3D30` is also this image's lowest game-code PC,
which is what makes the unit the first one below the library region *and* the boundary
`tools/sdk/revisions.py` uses.

## The compiler build and flag set

Measured, not assumed (`python3 tools/toolchain/select_build.py --tu sys_scf.c`, five installed
builds, every flag axis):

```
2.4-001213     -c -lang c -O2 -g                      text no  debug no  line no
2.4-001213     -c -lang c -O1 -g                      text no  debug no  line no
2.4-001213     -c -lang c -O3 -g                      text no  debug ok  line ok
2.4-001213     -c -lang c -O4 -g                      text no  debug ok  line ok
2.4-001213     -c -lang c -O2 -sdatathreshold 0 -g    text no  debug no  line no
2.4-001213     -c -lang c -O3 -sdatathreshold 0 -g    text no  debug no  line no
2.4-001213     -c -lang c -O2                         text no  debug no  line no
2.4-001213     -c -lang c -O3                         text no  debug no  line no
3.0-011126     -c -lang c -O2 -g                      text no  debug no  line no
3.0-011126     -c -lang c -O1 -g                      text no  debug no  line no
3.0-011126     -c -lang c -O3 -g                      text ok  debug ok  line ok
3.0-011126     -c -lang c -O4 -g                      text ok  debug ok  line ok
3.0-011126     -c -lang c -O2 -sdatathreshold 0 -g    text no  debug no  line no
3.0-011126     -c -lang c -O3 -sdatathreshold 0 -g    text no  debug no  line no
3.0-011126     -c -lang c -O2                         text no  debug no  line no
3.0-011126     -c -lang c -O3                         text no  debug no  line no
3.0.1-020123   -c -lang c -O3 -g                      text ok  debug ok  line ok
3.0.1-020123   -c -lang c -O4 -g                      text ok  debug ok  line ok      (`-O2`, `-O1`,
3.0.3-020716   -c -lang c -O3 -g                      text ok  debug ok  line ok       the
3.0.3-020716   -c -lang c -O4 -g                      text ok  debug ok  line ok       `-sdatathreshold`
3.0b38-030307  -c -lang c -O3 -g                      text ok  debug ok  line ok       and no-`-g` sets:
3.0b38-030307  -c -lang c -O4 -g                      text ok  debug ok  line ok       no/no/no, as above)
```

(The elided rows are the same eight flag sets for the three remaining builds; the full 40-row
table is the command's own output.  `config/targets.py`'s `tu_builds` holds the pair the build
uses.)

What it settles, and what it does not:

* **`-O3`-or-`-O4` and `-g`, as on the previous target.**  Below `-O3` the delay slots are not
  filled; without `-g` there are no `.debug`/`.line` bytes at all; `-sdatathreshold 0` implies
  `-model absolute`, so `pscf` would be addressed with `lui`/`lw` instead of `-0x3C68($gp)` and
  even the code stops matching.
* **`2.4-001213` is ruled out on this unit too, and independently of the sample that first
  ruled it out.**  It reproduces `.debug` and `.line` at `-O3`/`-O4` and *not* `.text`: it saves
  `ra` with `sq`/`lq` (0x7F/0x7B-encoded) where retail has `sd`/`ld` (`0x0000BFFF` at 0x001B3D44
  and `0x0000BFDF` at 0x001B3D64), whatever the flags.
* **The tie is recorded, not resolved.**  Four builds -- `3.0-011126`, `3.0.1-020123`,
  `3.0.3-020716`, `3.0b38-030307` -- reproduce all three parts of this unit, so this unit does
  **not** discriminate among them.  The descriptor records the first match
  (`3.0-011126 -c -lang c -O3 -g`, the build the previous target's sample also chose), and the
  wider sample that can break the tie is Task 1's, which stays open until a sample of
  *unrelated* units agrees.

## The drift from the previous target's source

The same file exists in this repository's history for DDRMAX2 (US), and it cannot be reused
verbatim.  Three differences, each read off this build's own bytes:

* **One call, not two.**  DDRMAX2's `sysInitScf` called `sceScfGetDateNotation(p)` *and*
  `sceScfGetLanguage()`.  The preview calls the first and stores the constant `1` into
  `language` (`addiu $4, $0, 0x1`, 0x001B3D54) -- which is what a US-only preview would do:
  the language is not read, it is forced.
* **A different line table.**  The preview's statements are on lines 24, 29, 35 and 43 where
  DDRMAX2's were 24, 29, 32 and 34, and `sysGetDateNotation`'s are 50 and 51 where that build's
  were 41 and 42.  Line 35 owns the constant *and* both stores, while the first field's load
  keeps line 29 alone -- mwcc's scheduler reordered the two statement chains through one
  register, and the statement list records that.  The source is laid out so each statement
  lands on its retail line.
* **A callee with no DWARF name.**  `sysInitScf`'s only call is `jal 0x001B3840`, and this
  binary's DWARF names nothing there (the TU's DIEs are `pscf` and the two functions --
  `dwarf1.py globals` has no `sceScf*` record).  The name is borrowed from the corpus and
  byte-validated: `tools/sdk/revisions.py` places this image's `libscf` at
  `0x001B34C0-0x001B3CE8` (stamp `PsIIlibscf3000`, set `devkit152`), and
  `sdk.revisions.classify` reproduces the 0x64 bytes at `0x001B3840` from that set's
  `libscf.a` instruction for instruction (5 words masked, 0 differing): the function is
  `sceScfGetDateNotation`.  `config/ddrex2p/borrowed_symbols.txt` records it with that
  provenance; the split that holds its bytes keeps its own bounds (`nonmatching
  func_001B3840, 0x64`), so adding the name re-segments nothing.

## How the promoted unit reaches the image

`tools/toolchain/compile.py` (the ninja `cc` rule) compiles the source with the measured pair,
reads the Metrowerks object with the oracle's own ELF reader, and places it under the pinned
layout: `.text` relocated against the retail addresses, `$gp` read from the retail `.reginfo`,
and the object's `.debug`/`.line` blocks filled into the offsets `debug_chunks.json` pinned.
The `objsec` edges then dump those payloads and the tail edge substitutes them for the retail
databins of the chunks the unit owns, so the unit's debug bytes are the *compiler's* -- which is
what makes the debug-chunk and line-chunk verdicts mean anything.  `tests/test_m2_sys_scf.py`
pins the graph (both sections' payloads in the tail, retail's databins out of it), the retail
statement lines, and that the descriptor has a measured pair for the unit.

G1 is unmoved by the promotion: `out/SLUS_211.74` is still `ef31c90f…c02cd`.

## What this unit does and does not change about the compiler question

It eliminates `2.4-001213` for a *second* target by measurement, and it leaves four 3.0 builds
tied.  A tie of four on a 0x3C-byte unit is the expected shape: the builds differ in ways this
much code does not exercise.  The open question is therefore unchanged -- which 3.0 build
produced this binary -- and the answer needs the wider sample Task 1 is holding open, not a
choice made here.
