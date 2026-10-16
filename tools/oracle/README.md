# `tools/oracle` — CodeWarrior DWARF 1 reader

`dwarf1.py`, `demangle.py` and `elf.py` are **vendored, unmodified** from the
[piney_apples](https://github.com/Toyz/piney_apples) repository
(`https://raw.githubusercontent.com/Toyz/piney_apples/main/tools/<file>`,
branch `main`), fetched **2026-10-14**.

They are dual-licensed **MIT OR Apache-2.0**; this project uses them under the
MIT terms. See `THIRD_PARTY_NOTICES.md` for the pinned hashes and the
unmodified statement.

| File          | sha256                                                             |
| ------------- | ------------------------------------------------------------------ |
| `dwarf1.py`   | `96bef9a47e5d4394463c84ec32fbcfcc801e8a71002c8dcf1b16ead5ebcaaecf` |
| `demangle.py` | `217e1752aed72c0ecb6f9e089f6f2cee3d2445e61233f9e7124d3dc6c53addb5` |
| `elf.py`      | `88010dbec13b7e7727deb3f82fc66a9ac5610d915ddb3c9247751bc0df942a32` |

Standard library only (Python 3); nothing here is patched. Fixes that would
change behaviour belong upstream or in a wrapper in this repo, never in these
three files.

## Use

```
python3 tools/oracle/dwarf1.py stats   orig/SLUS_207.11
python3 tools/oracle/dwarf1.py cus     orig/SLUS_207.11 [--files | --tus]
python3 tools/oracle/dwarf1.py fn      orig/SLUS_207.11 sysInitScf
python3 tools/oracle/dwarf1.py lines   orig/SLUS_207.11 0x21c420
python3 tools/oracle/dwarf1.py check   orig/SLUS_207.11
```

`--help` lists the rest (`type`, `globals`, `header`, `dump`) and documents how
CodeWarrior uses DWARF 1. As a library:

```python
from dwarf1 import Dwarf, Elf            # sys.path must include tools/oracle
dw = Dwarf("orig/SLUS_207.11")
```

## Retail sanity check

`stats`/`check` against the retail ELF (`orig/SLUS_207.11`) print
`compile units 480 (423 with code)`, `translation units 57`,
`functions 423 (with code 423)`, `818 (123 distinct names)`,
`unique globals/statics 639` and `0 sibling/length problems`; these exact
strings are asserted by `tests/oracle/test_conformance.py`.
`tests/oracle/test_vendor_dump.py` additionally checks the reader's function
`low_pc` set equals the one printed by the vendor's own dump
(`orig/usam2.elf.txt`, a gitignored copy of the DWARF dump shipped with the
community debug-symbol package).

## The generated headers (`emit_headers.py`, ours, not vendored)

`emit_headers.py` is this repository's own renderer; it reads the tree with
the vendored `Dwarf` above and writes all of `include/**` (`./ddr oracle`):

| path | what it is |
|---|---|
| `include/types/<tag>.h` | one named type, defined exactly once: the members with their offsets, the DIE it came from, the units that declare it, and a digest of its layout |
| `include/types.h` | every named type |
| `include/src/<unit>.h` | a unit: the shared types it includes, its own anonymous types, its globals, and its prototypes with retail's address and line range |

It renders **C**, where the vendored `dwarf1.py header --cu` renders C++: there a
use is a bare tag (`_tag_SYS_SCF_WORK *pscf;`), which cannot compile as C —
CodeWarrior labels every compile unit `LANG_CPLUSPLUS` even for a `.c` file, and
DWARF 1 resolves typedefs away, so `struct <tag>` is the only spelling the
evidence offers.  A named type is therefore defined once and shared, and a unit's
header includes what it uses.  An anonymous type (`@anon0..24`) is DWARF's
per-unit numbering — the same name is a different type in a different unit — so it
stays in the unit that declares it as `anon_<N>_<unit>`, and two units that
declare one *named* type differently fail the oracle (`LayoutDisagreement`) naming
the type and the member that differs.

Every header is checked by the original compiler, not a host `cc`:

```
python3 tools/toolchain/compile.py --syntax-only --include include probe.c -c -lang c -O3 -g
```

`--syntax-only` is `mwccps2 -c -lang c -O3 -g` with the object thrown away — MWCC
has no parse-only mode (`-nocodegen` skips the front end's own error reporting, so
it exits 0 on a file it cannot parse).  No promoted unit includes a generated
header yet: an `#include` changes the unit's debug bytes, because the type DIEs
record a unit's own declaration is what puts its statements on retail's lines (measured on
`sys_scf.c`: the same `.text`, but 240 -> 237 bytes of `.debug` and a moved `.line`
table).
