# Library revisions: the DDR Extreme 2 (US) preview template

`SLUS_211.74`, sha256 `ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd`, one
loadable segment at `0x100000`, 1,958,272 B. This is plan Task 2's record: the SDK revisions the
prototype links, confirmed byte-wise per library, names only. **No matching C was written for any
library function, and no SDK bytes enter this repository** -- the archives stay where they were
unpacked and only the verdict is committed.

## Method

- **The stamps.** The binary's own `__ps2_libinfo__` objects name eleven libraries, at VAs
  `0x2A0100`-`0x2B8BA8`: the eleven in `tools/sdk/revisions.py:STAMPS`. A stamp names a *release*, not
  a file, and the 2005 media is a later release than some of them -- so every stamp is confirmed
  against bytes, never trusted.
- **The corpus.** Every `ar` archive under every package tree on this machine --
  `revisions.py:ARCHIVE_ROOTS`, 292 archives and 44,425 functions, from tlib
  2.5.0-2.5.5, SCE Tool-Libs 2.4.2, PS2 Runtime Library 2.0, EE 1.00.03 and the July-2005 devkit
  (runtime library 3.0.3) with its GNU trees. A first version of this scan pointed at library
  *directories* and silently missed `ee/gcc/lib` (four `libgcc.a` and the toolchain archives), the
  Demo Disc SDK's three libraries and `ee001003_1`'s `gcc/lib`; the roots are package trees now, so
  "every archive on disk" is a fact rather than an intention. Deliberately out, with reasons: SCE-RT
  (`scert` is the *PSP* runtime), `tlib_251` (ships no archive), `cw303j` and the toolchain 2.0 image
  (never unpacked). Nothing else on this machine holds an EE archive.
- **Function slots.** The image is cut into functions by the bytes alone: a function ends with
  `jr ra` and its delay slot, and the next one starts at the next non-zero word (the link's
  alignment padding is zeros). Every offset where a whole archive object reappears is added as a
  boundary. The rule is validated against this binary's own DWARF every run: it finds
  **1,763 of the 1,816 named functions (97.1 %)**, and what it misses are
  functions that do not end in `jr ra`. A rule error can only *split* a slot, which makes a function
  unmatchable -- a floor on the count, never two functions merged into one match.
- **The match.** An archive object fits a slot when its **whole body** equals the slot's
  instructions after relocation masking (`sdk.match`: `j`/`jal` targets and I-type immediates are
  link addresses and carry no code) *and* the rest of the slot is padding. One changed instruction
  is a different revision; a body that does not fit the slot is a different function and is never
  reported as identity.
- **The floor.** A body shorter than 48 B is not evidence -- the kernel's 16-byte `Copy` and `setup`
  recur throughout the image -- so the counts use a 48-byte floor.
- **The control.** The same measurement against the same image with its instruction words shuffled
  finds **0** matches, so a 48-byte whole-body hit is not chance.
- **Whole objects.** `whole objects` counts the members of the chosen archive whose entire `.text`
  reappears in the image: the strictest form of the answer, and what a link can pin without
  touching the object.

## Per library: the eleven stamps the binary carries

| library | stamp | chosen archive | functions | bytes | byte-exact | whole objects | verdict |
|---|---|---|---|---|---|---|---|
| libgraph | `PsIIlibgraph3000` | `devkit152` `libgraph.a` | 19 | 6,208 | 2 | 15/29 | stamp and bytes agree |
| libdma | `PsIIlibdma3000` | `devkit152` `libdma.a` | 16 | 1,724 | 1 | 1/2 | stamp and bytes agree |
| libvu0 | `PsIIlibvu03000` | `devkit152` `libvu0.a` | 18 | 2,208 | 9 | 1/1 | stamp and bytes agree |
| libipu | `PsIIlibipu3000` | `devkit152` `libipu.a` | 10 | 2,280 | 1 | 2/2 | stamp and bytes agree |
| libkernl | `PsIIlibkernl3000` | `devkit152` `libkernl.a` | 247 | 51,104 | 25 | 24/26 | stamp and bytes agree |
| libpad | `PsIIlibpad3020` | `devkit152` `libpad.a` | 38 | 6,328 | 0 | 1/1 | stamp and bytes agree |
| libcdvd | `PsIIlibcdvd3000` | `devkit152` `libcdvd.a` | 39 | 9,848 | 0 | 14/29 | stamp and bytes agree |
| libmc | `PsIIlibmc3020` | `devkit152` `libmc.a` | 27 | 6,272 | 0 | 0/2 | **stamp absent** — the closest revision reproduces 27 |
| libscf | `PsIIlibscf3000` | `devkit152` `libscf.a` | 16 | 1,588 | 0 | 1/1 | stamp and bytes agree |
| libeyetoy | `PsIIlibeyety1300` | `devkit152` `libeyetoy.a` | 1 | 48 | 1 | 0/1 | **stamp absent** — the closest revision reproduces 1 |
| netcnfif | `PsIInetcnfif3020` | `devkit152` `netcnfif.a` | 41 | 5,432 | 0 | 3/6 | stamp and bytes agree |

`stamp and bytes agree` means the chosen archive carries the stamp *and* is the best byte-wise
match on disk. `stamp absent` means nothing on disk carries the stamp, so the closest revision is
reported instead and the residue is unexplained. Note that `functions` counts only the objects that
reappear: an archive that reproduces 247 functions may still have members that retail does not
contain at all, and nothing on disk separates "not linked" from "not this revision" without the
split (plan Task 4).

## What each choice was measured against

| library | revisions on disk | the next best archives |
|---|---|---|
| libgraph | `PsIIlibgraph2000`, `PsIIlibgraph2400`, `PsIIlibgraph2500`, `PsIIlibgraph3000` | `tlib_250` 19f/6,208B; `toolibs242` 16f/4,376B; `rlib20` 14f/3,816B |
| libdma | `PsIIlibdma2000`, `PsIIlibdma2400`, `PsIIlibdma2500`, `PsIIlibdma3000` | `tlib_250` 16f/1,724B; `rlib20` 3f/328B; `toolibs242` 3f/328B |
| libvu0 | `PsIIlibvu03000` | `tlib_250` 18f/2,208B; `toolibs242` 18f/2,208B; `rlib20` 17f/2,148B |
| libipu | `PsIIlibipu2000`, `PsIIlibipu2400`, `PsIIlibipu2500`, `PsIIlibipu3000` | `tlib_250` 4f/1,236B; `toolibs242` 4f/1,236B; `rlib20` 1f/104B |
| libkernl | `PsIIlibkernl2000`, `PsIIlibkernl2420`, `PsIIlibkernl2500`, `PsIIlibkernl2520`, `PsIIlibkernl2530`, `PsIIlibkernl2540`, `PsIIlibkernl2550`, `PsIIlibkernl3000` | `tlib_250` 129f/19,792B; `tlib_252` 129f/19,792B; `tlib_253` 129f/19,792B |
| libpad | `PsIIlibpad2000`, `PsIIlibpad2410`, `PsIIlibpad2500`, `PsIIlibpad3020` | `tlib_250` 21f/2,912B; `toolibs242` 21f/2,912B; `rlib20` 14f/1,592B |
| libcdvd | `PsIIlibcdvd2000`, `PsIIlibcdvd2420`, `PsIIlibcdvd2500`, `PsIIlibcdvd2520`, `PsIIlibcdvd2530`, `PsIIlibcdvd3000` | `tlib_250` 19f/3,908B; `tlib_252` 19f/3,908B; `tlib_253` 19f/3,908B |
| libmc | `PsIIlibmc2000`, `PsIIlibmc2400`, `PsIIlibmc2500`, `PsIIlibmc2530`, `PsIIlibmc2540`, `PsIIlibmc3030` | `rlib20` 1f/52B; `tlib_250` 1f/52B; `tlib_253` 1f/52B |
| libscf | `PsIIlibscf2000`, `PsIIlibscf2400`, `PsIIlibscf2500`, `PsIIlibscf3000` | `tlib_250` 15f/1,476B; `toolibs242` 15f/1,476B; `rlib20` 4f/284B |
| libeyetoy | `PsIIlibeyety1400` | — |
| netcnfif | `PsIInetcnfif2500`, `PsIInetcnfif2530`, `PsIInetcnfif3020` | — |

Where the bytes are the only evidence, they agree with the stamp. `libkernl` reproduces 247
functions against 129 for the 2.5.x archives, `libcdvd` 39 against 19, `libpad` 38 against 21,
`libscf` 16 / 1,588 B against 15 / 1,476 B, and `libipu` 10 against 4: in each case the revision the
stamp names reproduces strictly more, so the bytes choose it without help.

Where bytes cannot separate two releases that ship the same objects, the stamp does it. `libgraph`,
`libdma` and `libvu0` tie instruction for instruction with their 2.5.x counterparts (19/6,208,
16/1,724 and 18/2,208 on both sides) -- which is exactly why the stamp is recorded next to the bytes
rather than instead of them.

## Explained, as numbers

| quantity | value |
|---|---|
| function slots the bytes alone find (>= 48 B) | 3,536 |
| bytes those slots span | 1,939,192 |
| slots a whole-body identical archive object explains | 557 |
| bytes those objects explain | 123,784 |
| …as a share of the image | 6.32 % |
| …of which byte-exact, immediates and all | 10,344 B |
| …in the eleven stamped libraries (union) | 378 slots / 80,732 B |
| head matches rejected: the object does not fit the slot | 471 |
| slots nothing on disk explains | 2,979 / 1,814,152 B |
| control: whole-body matches with the image's instructions shuffled | 0 |
| …below the game's first DWARF function (`0x1B3D30`) | 724,732 B in 1,633 slots |
| …of that, what an archive explains | 462 slots / 109,024 B (15.04 %) |
| …and what nothing explains | 614,700 B |

Read the coverage two ways. Against the whole image, the archives on this machine explain
**6.32 %** of it. Against the region a reader would call the library region they explain
**15.0 %**: the 724,732 B below the game's first DWARF function (`0x1B3D30`)
hold 462 slots an archive reproduces (109,024 B), about three times the
whole-image rate, and that is where the SDK's objects sit.

The eleven stamped libraries, counted over the whole image, account for **378 slots /
80,732 B**; restricted to the same region below `0x1B3D30` they are
**348 slots / 76,380 B**. Both numbers are the *union* over each stamp's
chosen archive, so a slot two libraries share is counted once.

The rest the numbers also name: 1,814,152 B (92.6 %) has no whole-body
identical object anywhere in the corpus -- game code the DWARF backs and game code it does not, the
newlib/GNU runtime whose revision no stamp pins, library code from the one revision that is not on
disk as an archive, and the data section. The old target's survey measured its own SDK subset at 757
functions / 86,944 B; this template's is the same order of magnitude, larger because the title links
more of the SDK.

## The longest unexplained stretches

| addresses | bytes |
|---|---|
| `0x2A16E8`–`0x2DE180` | 248,472 |
| `0x2923B0`–`0x2A044C` | 57,500 |
| `0x1E9630`–`0x1F6280` | 52,304 |
| `0x1D4E10`–`0x1DF698` | 43,144 |
| `0x249770`–`0x253EB0` | 42,816 |
| `0x135470`–`0x13F950` | 42,208 |
| `0x13F970`–`0x149490` | 39,712 |
| `0x187C70`–`0x191420` | 38,832 |

These 8 stretches are 564,988 B, 31 % of everything no archive explains. Nothing in them
is reproduced by any archive on disk: the DWARF names no code between `0x100000` and `0x1B3D30` at
all (736 KB of the image), the newlib/GNU runtime matches only in part, and the topmost stretch,
`0x2A16E8`-`0x2DE180`, is the data and read-only-data tail where the library banners and the game's
strings sit rather than code.

## Code the bytes name that carries no stamp in this binary

The stamp list is a **lower bound**. `__ps2_libinfo__` is one member of each archive, and the linker
only pulls that member in when something references it -- so a library can be linked with no stamp
in the image at all. These archives reproduce code the binary carries no stamp for. Packages are
listed together where the same source appears more than once (hard- and soft-float twins of the GNU
runtime usually produce identical counts; where they do not (the two `libgcc.a` builds) both rows are
shown).

| library | archive | packages | revision | functions | bytes | byte-exact |
|---|---|---|---|---|---|---|
| `libmpeg` | `libmpeg.a` | `devkit152` | `PsIIlibmpeg3000` | 84 | 28,712 | 21 |
| `libc` | `libc.a` | `devkit152`, `devkit152/soft` | — | 102 | 13,532 | 15 |
| `libg` | `libg.a` | `devkit152`, `devkit152/soft` | — | 102 | 13,532 | 15 |
| `libmpeg` | `libmpeg.a` | `tlib_250` | `PsIIlibmpeg2500` | 22 | 7,236 | 0 |
| `libmpeg` | `libmpeg.a` | `toolibs242` | `PsIIlibmpeg2420` | 18 | 5,676 | 0 |
| `libdev` | `libdev.a` | `devkit152` | — | 31 | 3,120 | 7 |
| `libdev` | `libdev.a` | `tlib_250`, `rlib20`, `toolibs242` | — | 27 | 2,268 | 5 |
| `libc` | `libc.a` | `ee001003_1`, `ee001003_1/soft` | — | 7 | 2,228 | 7 |
| `libg` | `libg.a` | `ee001003_1`, `ee001003_1/soft` | — | 7 | 2,228 | 7 |
| `libgcc` | `libgcc.a` | `devkit152/soft` | — | 15 | 1,940 | 1 |
| `libgcc` | `libgcc.a` | `devkit152` | — | 15 | 1,892 | 1 |
| `libtimer` | `libtimer.a` | `devkit152` | `PsIIlibtimer3000` | 12 | 1,688 | 0 |
| `libc` | `libc.a` | `toolibs242`, `toolibs242/soft` | — | 3 | 1,140 | 3 |
| `libg` | `libg.a` | `toolibs242`, `toolibs242/soft` | — | 3 | 1,140 | 3 |

`libmpeg` is the largest: 84 functions / 28,712 B reproduced by the 3.0.3 archive, 21 of them
byte-exact -- and the binary carries no `PsIIlibmpeg` string anywhere, which is why the stamp list
cannot be read as the linked-library list. Whatever the reason no
`__ps2_libinfo__` member was pulled in, the code is there and it is tlib 3.0.3's. `libdev`,
`libtimer`, `libsdr`, `libpad2`, `libmrpc` and the GNU runtime (`libc`, `libg`, `libm`, `libgcc`,
`libstdc++`, `libiberty`, `libidt`, from the devkit's `ee/gcc` trees) are the rest of the linked
runtime; they carry no stamp of their own in this build either. Nothing here is reversed to C -- these are names for a
ledger, and the pinned objects are the ones that match.

## Unexplained

**`libmc` needs `PsIIlibmc3020`; no *archive* on disk is 3020 -- but a 3.0.2 *link* is.** The 2005
media ships `PsIIlibmc3030` (built 2005-05-19) and every other package 2000/2400/2500/2530/2540, so
the release the prototype links cannot be linked from anything here: 3030 reproduces 27 functions /
6,272 B of the template and **none** of its two objects whole.

A correction to the first version of this record, which said "nothing on disk is 3020": the SCEE
YNCF Tool 1.1 of the *same* July-2005 devkit carries the stamp. `PsIIlibmc3020` sits at
`0x1443E0` in `~/sdk-extract/devkit152/SoftwareToolsSetup/MAINDIR/SCEE_Tools/YNCFTool/Cdburn/Slus_123.45` (and in `~/sdk-extract/devkit152/SoftwareToolsSetup/MAINDIR/SCEE_Tools/YNCFTool/Iso/SCEE_YNCF_Tool_1.1.iso`), so libmc 3.0.2 bytes **are** on this
machine. The limitation is what it can be used for: it is a **linked binary**, not an archive -- it
can validate a candidate's bytes for libmc 3.0.2, but there is no relocatable member to pin or to
link, which is the whole capability an archive gives.

Measured, so the lead is not overread: searching the template's `libmc` neighbourhood
(`0x1198E8`-`0x11EE8C`, the 84 slots within ±8 KiB of the functions 3030 does
reproduce) against that image finds 43 slots whole-body identical
(11,212 B) -- 41 of the 49 an archive already
explains, and only **2 of the 35** that no archive explains.
So the 3.0.2 link confirms the shared code and does **not** close the `libmc` gap: the template's
unexplained `libmc` code is not in it either.

**`libeyetoy` needs `PsIIlibeyety1300`; the only archive on disk is 1.4.0.** That archive explains a
single 48-byte function in the whole image (byte-exact, so the code is real), and nothing else: the
EyeToy revision the prototype links is not on disk, and the 1.4.0 objects are not it. No linked
binary carrying `PsIIlibeyety1300` was found either.

**The rest.** 2,979 slots / 1,814,152 B of the image
(92.6 %) have no whole-body identical archive object anywhere in the corpus. That is
not a statement that the code is unknown: it is game code (DWARF-backed and DWARF-less), GNU runtime
code whose revision is not pinned by any stamp, library code from the missing revision, and the data
section. Plan Task 9 names what matches and leaves the rest as split assembly -- the residue is
listed here as numbers rather than summarised away.
