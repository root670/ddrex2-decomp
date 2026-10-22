# include/

Generated from `orig/SLUS_211.74` by `tools/oracle/emit_headers.py` (`./ddr oracle`).
Do not hand-edit anything here: a fresh run overwrites it.

| path | what it is |
|---|---|
| `types/<tag>.h` | one named type, defined exactly once: its members and offsets, the DIE it came from, the units that declare it, and a digest of its layout. |
| `types/anon_<digest>.h` | one anonymous layout, defined exactly once as a typedef of an unnamed aggregate, for every header that holds it. |
| `types.h` | every named type, for a reader and for a source that wants them all. |
| `src/<unit>.h` | a translation unit: the shared types it uses, its own anonymous types, its globals, and its prototypes with retail's address and line range. |

These headers are **C**.  A use is `struct <tag> *`, never a bare tag: CodeWarrior labels
every compile unit `LANG_CPLUSPLUS` even for a `.c` file, and DWARF 1 resolves typedefs away,
so `struct <tag>` is the only spelling the evidence offers.

An anonymous type keeps its unit.  DWARF names them `@anon0..24`, and that numbering is
per-unit -- `@anon0` in `les.c` and `@anon0` in `onimode.c` are different types -- so a use
becomes `anon_<N>_<unit>` and the definition is emitted in that unit's own header and
nowhere else, as a typedef of an unnamed aggregate (the compiler records that back as
`@anonN`; a tag of our own would land in the DIE).

A layout a *named* type holds, though, is shared.  The same 8-byte rect is reached both
through `_CWS_WIN_W.def` and through a unit's own `@anon0`, and retail's CU carries **one**
DIE for it, referenced twice; spelling the member out inline while the unit typedefs its own
copy declared two, 5 DIEs and 0x97 bytes over retail's block.  So a layout reachable from a
named type's definition gets a header of its own, `types/anon_<digest>.h` -- a typedef of an
unnamed aggregate, so the alias never reaches the DWARF and the compiler still records
`@anonN` -- and every use of that layout, in a named type's member or in a unit's own
anonymous type, names that one alias.  The digest is the structural proof that the uses are
the same type: it covers size, kind, member names, offsets, bit fields and member types.

Check a header the way the compiler does, not with a host `cc`:

    python3 tools/toolchain/compile.py --syntax-only --include include <probe.c> -c -lang c -O3 -g

No promoted translation unit includes one of these yet: a unit's own declarations are what put
its statements on the lines retail has them on, so an `#include` in their place moves the
unit's `.line` table.  Reproducing retail's own include graph is a generator problem and not a
missing include.  Hand-written reconstruction lives under `src/`.

A run never deletes anything: point the oracle at another retail ELF and the previous target's
`types/*.h` and `src/*.h` stay on disk until they are removed.  That is deliberate — the set of
tags is evidence — and `tests/oracle/test_emit_headers.py` compares the committed tree against
a fresh run, so a stale file is a failure to clean up, not something to silence.
