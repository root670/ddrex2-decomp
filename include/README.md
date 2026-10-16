# include/

Generated from `orig/SLUS_207.11` by `tools/oracle/emit_headers.py` (`./ddr oracle`).
Do not hand-edit anything here: a fresh run overwrites it.

| path | what it is |
|---|---|
| `types/<tag>.h` | one named type, defined exactly once: its members and offsets, the DIE it came from, the units that declare it, and a digest of its layout. |
| `types.h` | every named type, for a reader and for a source that wants them all. |
| `src/<unit>.h` | a translation unit: the shared types it uses, its own anonymous types, its globals, and its prototypes with retail's address and line range. |

These headers are **C**.  A use is `struct <tag> *`, never a bare tag: CodeWarrior labels
every compile unit `LANG_CPLUSPLUS` even for a `.c` file, and DWARF 1 resolves typedefs away,
so `struct <tag>` is the only spelling the evidence offers.

An anonymous type keeps its unit.  DWARF names them `@anon0..24`, and that numbering is
per-unit -- `@anon0` in `les.c` and `@anon0` in `onimode.c` are different types -- so a use
becomes `anon_<N>_<unit index>` and the definition is emitted in that unit's own header and
nowhere else.  A named type whose layout contains one spells that member out inline; the
layout digest, compared across every declaration, is what makes that faithful.

Check a header the way the compiler does, not with a host `cc`:

    python3 tools/toolchain/compile.py --syntax-only --include include <probe.c> -c -lang c -O3 -g

No promoted translation unit includes one of these yet: a unit's own declaration is what puts
its statements on the lines retail has them on, so an `#include` in its place moves the unit's
`.line` table (measured on `sys_scf.c`: the same `.text`, 240 -> 237 bytes of `.debug`).  So
reproducing retail's own include graph is a generator problem and not a missing include.
Hand-written reconstruction lives under `src/`.
