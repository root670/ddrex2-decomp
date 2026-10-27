# Third-party notices

## piney_apples (MIT OR Apache-2.0)

Source repository: <https://github.com/Toyz/piney_apples>

Fetched on **2026-10-14** from `https://raw.githubusercontent.com/Toyz/piney_apples/main/tools/<file>`
(branch `main`) into `tools/oracle/`. The files are **unmodified**: no edits, no
reformatting, no whitespace changes.

| Vendored file               | Upstream file | sha256                                                             |
| --------------------------- | ------------- | ------------------------------------------------------------------ |
| `tools/oracle/dwarf1.py`    | `dwarf1.py`   | `96bef9a47e5d4394463c84ec32fbcfcc801e8a71002c8dcf1b16ead5ebcaaecf` |
| `tools/oracle/demangle.py`  | `demangle.py` | `217e1752aed72c0ecb6f9e089f6f2cee3d2445e61233f9e7124d3dc6c53addb5` |
| `tools/oracle/elf.py`       | `elf.py`      | `88010dbec13b7e7727deb3f82fc66a9ac5610d915ddb3c9247751bc0df942a32` |

MD5 (for cross-checking against other copies): `dwarf1.py`
`aeedf767b25afb9dd751f4ec3e0505f2`, `demangle.py`
`2600ab92acb9f7038af8e4596afd3fe0`, `elf.py` `6825b0c8e1016b40f2de188f5eef48fb`.

Licence: dual-licensed **MIT OR Apache-2.0** (upstream offers either at the
user's option); this repository uses it under the MIT terms. The upstream
licence text is not copied here because the vendored files carry no
per-file headers; see the repository above for `LICENSE-MIT` / `LICENSE-APACHE`.

`tools/oracle/README.md` records the same source, licence, fetch date, hashes
and unmodified statement.

## m2c (GPL-3.0-only) — fetched, **not** vendored

Source repository: <https://github.com/matt-kempster/m2c>

Pinned commit: `c632946b8cfbe8fce442b522dba92dfa72f1f317` (2026-10-22,
"Don't crash decompiling functions declared as data"). Fetched on **2026-10-27** from
`https://codeload.github.com/matt-kempster/m2c/tar.gz/c632946b8cfbe8fce442b522dba92dfa72f1f317`
by `tools/toolchain/fetch.py m2c` into `toolchain/m2c/<commit>/` — a gitignored tree, like the
compilers, so **no m2c file is committed to this repository**. `tools/units/m2c_draft.py` runs it
as a subprocess; nothing here imports it.

| Pin | Value |
| --- | --- |
| archive sha256 | `b95b6eabd4c879292b896120cbf8e2bb8aed9700cd83d45e964f145f99be47e2` (713,313 bytes) |
| tree sha256 | `54a4a71f5aa3d0f1b9d5cef82b0fba4c485cf167793acd4154569ed3cb1ee7b4` (1,519 files) |

The tree digest is sha256 over `"<file sha256>  <relpath>\n"` for every regular file, sorted by
relpath; it is recomputed before the tree is published and again by `installed_m2c()` before the
drafter runs, so the bytes in use are the pinned ones rather than a plausible checkout.

Licence: **GPL-3.0-only** upstream (`LICENSE`, GPL v3). It is used here as a fetch-on-demand
development tool, not linked or redistributed; GPL code is deliberately not vendored into this
tree. The assignment's premise that m2c is MIT is wrong — pinning by content and keeping it out
of the repository is what makes that safe.

m2c vendors its own fork of **pycparser** as `m2c_pycparser/` (BSD-3-Clause, upstream commit
`b5c6024ff01346b194e43435af71a210b1e8e2ae`); it is part of the pinned tree above. Nothing else is
needed to run the drafter: m2c's only declared dependency is `graphviz ~= 0.20.1`, which **only**
`--visualize` uses, and `m2c_draft.py` never passes it.

## decomp-permuter (MIT) — fetched, **not** vendored

Source repository: <https://github.com/simonlindholm/decomp-permuter>

Pinned commit: `8556c81d80d1c1af98a858c8f4dc951357f29139` (2026-10-06, "Add a pass to
reverse if/else blocks").  The project publishes no tag or release, so the commit is the version.
Fetched on **2026-10-27** from
`https://codeload.github.com/simonlindholm/decomp-permuter/tar.gz/8556c81d80d1c1af98a858c8f4dc951357f29139`
by `tools/toolchain/fetch.py decomp-permuter` into `toolchain/decomp-permuter/<commit>/` — a
gitignored tree, like the compilers, so **no permuter file is committed to this repository**.
`tools/units/permute.py` imports it as a library, after `installed_permuter()` has re-verified the
tree digest.

| Pin | Value |
| --- | --- |
| archive sha256 | `57cfb45141a2f97ce27e74c1882aab162ff203c2f4688b4617fc2ec3a6ca9907` (2,870,176 bytes) |
| tree sha256 | `7a073645521e41b202cf59c8b6150daf8f627cd63b5d2b6f84486b48ac39ae89` (255 files) |

The tree digest is sha256 over `"<file sha256>  <relpath>\n"` for every regular file, sorted by
relpath, the same scheme m2c uses; it is recomputed before the tree is published and again by
`installed_permuter()` before the driver imports it.

Licence: **MIT** (`LICENSE`). It vendors its own fork of **pycparser** as `perm_pycparser/`
(BSD-3-Clause), part of the pinned tree above. Its only dependency that is not vendored is `toml`
(a host package: `python3 -m pip install toml`), as `tools/units/permute.py` says when it is
missing.
