# M2 -- the first promoted translation unit: `src/sys/sys_scf.c`

M2's exit gate is the spec's promotion rule: a translation unit counts as promoted only when
its **code** *and* its **debug bytes** match retail.  `sys_scf.c` (2 functions, 0x40 bytes of
`.text`, 646 bytes of `.debug`, 96 bytes of `.line`) is the first one, and all three match:

```
$ ./ddr verify --tu sys_scf.c
G1 ok: out/SLUS_207.11 is a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc
src/sys/sys_scf.c: text ok (VA 0x0021C410-0x0021C450, 64 bytes)
src/sys/sys_scf.c: debug chunk ok (1 chunk(s), 646 bytes)
src/sys/sys_scf.c: line chunk ok (2 chunk(s), 96 bytes)
```

## The compiler build and flag set

Measured, not assumed:

```
$ python3 tools/toolchain/select_build.py --tu sys_scf.c
2.4-001213     -c -lang c -O2 -g                      text no debug no line no
2.4-001213     -c -lang c -O1 -g                      text no debug no line no
2.4-001213     -c -lang c -O3 -g                      text no debug ok line ok
2.4-001213     -c -lang c -O4 -g                      text no debug ok line ok
2.4-001213     -c -lang c -O2 -sdatathreshold 0 -g    text no debug no line no
2.4-001213     -c -lang c -O3 -sdatathreshold 0 -g    text no debug no line no
2.4-001213     -c -lang c -O2                         text no debug no line no
2.4-001213     -c -lang c -O3                         text no debug no line no
3.0-011126     -c -lang c -O1 -g                      text no debug no line no
3.0-011126     -c -lang c -O3 -g                      text ok debug ok line ok
3.0-011126     -c -lang c -O4 -g                      text ok debug ok line ok
3.0-011126     -c -lang c -O2 -sdatathreshold 0 -g    text no debug no line no
3.0.1-020123   -c -lang c -O3 -g                      text ok debug ok line ok
3.0b38-030307  -c -lang c -O3 -g                      text ok debug ok line ok
3.0.3-020716   -c -lang c -O3 -g                      text ok debug ok line ok
select: src/sys/sys_scf.c: --compiler 3.0-011126 -c -lang c -O3 -g
```

(`select_build.py` prints every candidate; the table above is that output, with the flag sets
that cannot matter for the third line elided.  `configure.py`'s `TU_BUILDS` holds the pair it
picks.)  Three things it settles:

* **`-O3` (or `-O4`), not `-O2`.**  Instruction scheduling first appears at optimizer level
  3, and retail's delay slots are filled (`sw $4,pscf` inside the first `jal`'s slot, the
  first callee's store inside the second `jal`'s).  At `-O2` the same source emits `nop`
  slots and 0x3C bytes of `.text` for `sysInitScf` where retail has 0x30.
* **`-g` is not optional**: it is where `.debug`/`.line` come from, and the promotion rule
  needs them (the sets without it are measured too, and they fail).
* **`-sdatathreshold 0` is wrong here**: it implies `-model absolute`, so `pscf` would be
  addressed with `lui`/`lw` instead of `-0x5A78($gp)`, and even the code stops matching.
* **The 2.4 build cannot match the code.**  `2.4-001213` reproduces the `.debug` and `.line`
  bytes at `-O3`/`-O4`, but it saves `ra` with `sq`/`lq` (128-bit) where retail uses
  `sd`/`ld` (64-bit): `.text` differs in two instructions of `sysInitScf` whatever the flag.
  Every installed 3.0 build emits retail's `sd`/`ld` and matches all three parts.  The
  compiler ident in the retail `.comment` ("MW MIPS C Compiler (2.4.1.01)") is not an
  argument against a 3.0 compiler: `.comment` is a *tail databin* (retail's own bytes, see
  `configure.py`'s `TRAILING`), and the DWARF `producer` both builds write is the
  version-less `'MW MIPS C Compiler'`.

## How a promoted unit reaches the image

`tools/toolchain/compile.py` is the ninja `cc` rule's program.  It runs `mwccps2` (under
wibo), reads the Metrowerks object with the oracle's own ELF reader, and places what it wrote
under the pinned layout, because mainline binutils cannot read a `mwccps2` object at all and
`mwldps2` -- which can -- does not keep `.debug`/`.line` for a link without debug flags
(R23):

* `.text` -- each function's bytes with the object's own relocations applied (`R_MIPS_32`
  against the pinned record offsets, `R_MIPS_26` against the callee's address,
  `R_MIPS_GPREL16` against `$gp`, which is read from the retail ELF's `.reginfo`), laid out
  at the retail addresses with the inter-function padding the pinned layout has, and
  labelled with the DWARF names.  The pinned `ld` script links this one object where the
  unit's splits used to be.
* `.debug` / `.line` -- the object's per-function DWARF records, relocated the same way and
  placed at the offsets `debug_chunks.json` pinned (the unit's chunk, each function's record,
  each statement list).  The `objsec` edges dump them out of the object
  (`objcopy --dump-section`) and the tail edge substitutes them for the retail databins of
  the chunks the unit owns -- so the promoted unit's debug bytes are the *compiler's*, not a
  copy of retail's, which is what makes the debug-chunk verdict mean anything.

Two properties are load-bearing and are checked, not assumed: a function's `.text` must be
exactly its pinned size (it has to fit its slot), and a debug/line block that does not fit its
pinned chunk is raised rather than allowed to reflow the file.  Everything else -- a payload
of the wrong size, a byte that differs -- is left to G1 and to the per-chunk verdicts, which
name the unit and the chunk.

### The one normalised field

The compiler records the *absolute* path of the source it is given, and wibo spells a host
path with the `Z:` drive; retail's CU name records the original build host's path
(`C:\work\usam2\src\sys\sys_scf.c`).  `compile.py` therefore compiles a staged copy of the
source at a path whose guest spelling is *exactly as long* as retail's (a directory under
`/tmp`, padded to length), then replaces that recorded name with retail's spelling.  The
substitution is asserted to be a same-length replacement: a different length would resize
every DIE that carries the name and the chunk would not fit.  Everything else in the payload
is the compiler's bytes.

## What this does not cover yet

* The unit declares its own types and globals.  `include/src/sys/sys_scf.h` spells the tag the
  way the DWARF record does (`_tag_SYS_SCF_WORK *`), which is C++ syntax, so a C unit writes
  `struct` in front of the same names instead of including it.  A unit that includes other
  headers will also record *those* paths in its DWARF, and the staging trick above covers the
  main source only.
* The staging path length is a function of retail's path spelling (`Z:` + host path must equal
  it), so a unit whose retail path is shorter than `/tmp` plus its own basename cannot be
  staged, and `compile.py` fails loudly rather than recording a name it cannot replace.
* `src/` and `configure.py`'s `TU_BUILDS` must agree: a source nobody has measured, or a
  listing whose source is gone, is a configuration error, never a silently unchanged image.

## Reproducing it

```bash
python3 tools/toolchain/select_build.py --tu sys_scf.c   # the compiler and flags, measured
./ddr build                                              # configure + ninja + G1
./ddr verify --tu sys_scf.c                              # text, debug chunk, line chunk
python3 -m pytest tests/test_m2_sys_scf.py -v
```

One caveat for the diff loop: `ddr diff sysInitScf sys_scf` compares the split (retail's own
bytes, with the `jal` targets left to the linker) against the promoted object (whose call
targets are already resolved), so objdiff scores the two `jal` instructions as different and
reports ~99% for a function whose linked bytes are retail's.  G1 and the per-chunk verdicts
are the arbiters; the instruction streams do agree, mnemonic for mnemonic.
