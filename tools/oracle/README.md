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
