# Two of the four data-only candidates are overlay data: not placeable in this target

`CS/lesson/kn_lmsg.c` and `CS/dancemaster/dmm_subject.c` are data-only units whose one
allocated datum lives in an overlay blob, not in the image the target builds.  The two that
are placeable -- `sound/vxdecode/get4bit.c` and `sound/vxdecode/dectbl.c` -- are promoted
(see their commits and `tu_builds` rows).

## What the DWARF says

    $ python3 tools/oracle/dwarf1.py header orig/SLUS_211.74 --cu kn_lmsg
    * MW MIPS C Compiler, overlay les_rel4cd.prg; 0 functions
    unsigned char *kn_less_msg[307];   /* @0x007fa180 size 0x4cc */

    $ python3 tools/oracle/dwarf1.py header orig/SLUS_211.74 --cu dmm_subject
    * MW MIPS C Compiler, overlay dmm_rel4cd.prg; 0 functions
    struct @anon2 dmm_subject_w[200];  /* @0x00806220 size 0x7080 */

`dwarf1.py globals` attributes both: `kn_less_msg` to `les_rel4cd.prg` (the overlay's code
ends at `0x007FA0B0`, so the datum is the first thing after it) and `dmm_subject_w` to
`dmm_rel4cd.prg`.

## Why no ledger row can name them

`orig/SLUS_211.74` has one file-backed `PT_LOAD` (`0x00100000`..`0x002DE180`) and eleven
zero-fill reservations for the overlay blobs (`filesz 0`, the first at `0x7F0000`).  So
`elf.Elf.read` returns zeros for both addresses by design (`tools/oracle/elf.py`: a VA in a
`filesz 0` segment reads as `.bss`), and the bytes an initialiser would have to reproduce are
in the disc image's overlay file, which no tool in this tree extracts (the target's geometry
records the overlays as *not represented*; see the comment on `Geometry` in
`config/targets.py`).

`splat` produces no split above the file-backed image either, so `configure.plan_data` refuses
the placement before the compiler is reached.  Measured, one row added at a time and then
removed:

    $ echo 'kn_less_msg = 0x007FA180; // size:0x4CC extent:0x4D0 source:src/CS/lesson/kn_lmsg.c' >> config/ddrex2p/data_placements.txt
    $ python3 configure.py --target ddrex2p
    configure.py: error: kn_less_msg spans 0x7FA180..0x7FA650, which crosses the split
    asm/nonmatchings/main/func_002DDDB8.s (0x2DDDB8..0x2DE180); a placement must be inside one
    split

    $ echo 'dmm_subject_w = 0x00806220; // size:0x7080 extent:0x7080 source:src/CS/dancemaster/dmm_subject.c' >> config/ddrex2p/data_placements.txt
    $ python3 configure.py --target ddrex2p
    configure.py: error: dmm_subject_w spans 0x806220..0x80D2A0, which crosses the split
    asm/nonmatchings/main/func_002DDDB8.s (0x2DDDB8..0x2DE180); a placement must be inside one
    split

`compile.Manifests._tu` has the same precondition from the other side: a unit with no functions
is a `Tu` only when a placement row names its source, so neither unit can even be compiled as
C by the build (`no data placement names it`), let alone verified.

## What would unblock them

A ledger that can name an overlay address (an overlay-aware split or a second image to compare
against) plus the bytes: the initialisers cannot be written from anything in `orig/`, and
inventing them is exactly the placeholder a data placement exists to prevent.  This is the
milestone's recorded overlay boundary (`config/targets.py`, the `Geometry` comment: "The
overlays are out of this milestone's scope anyway (the spec defers DATA00-09.BIN)"), reached
from the data side rather than the code side.
