# oni_list: the first data-only unit promoted on ddrex2p

`src/AM/s573/play/oni_list.c` owns initialised data and no code. Its DWARF declares one
declaration CU (cus.json record 50) with two types and one file-scope object and no function
CU at all:

| object | VA | size | extent |
|---|---|---|---|
| `struct oni_mode` | — | 0x00C | 20 per course |
| `struct oni_course` | — | 0x10C | |
| `oni_course course_list[39]` | 0x002AFD40 | 0x28D4 = 39 * 0x10C | 0x28E0 |

The bytes live in the main code segment (`splat.yaml`'s `- [0x200, c, main]`), inside
`asm/nonmatchings/main/func_002AC0A8.s` as the `alabel course_list` block at file 0x1AFF40
(VA 0x002AFD40).  The block runs to 0x002B2614 and is followed by 12 zero bytes before the
next datum (an SJIS string at 0x002B2620), hence extent 0x28E0.  No word is a relocation: the
table is pure immediates.

The 39 initialisers are decoded from retail's bytes.  The bitfields of `oni_mode` are written
positionally because this compiler refuses designated initialisers in C (`.freeze = 1` is
"illegal initialization").

Measured with the retail compiler (`3.0b38-030307 -c -lang c -O3 -opt full -g`):

* the datum: `course_list at 0x002AFD40 is the retail datum (0x28d4 bytes, 0 relocation(s),
  extent 0x28e0)`;
* the unit's `.debug` chunk: retail's 0x5BE bytes / 35 DIEs byte for byte under
  `--adopt-retail-meta` (nothing adopted: the chunk is already retail's);
* `.text` is 0 bytes and there are no `.line` chunks (no statements).

## What promotion needed

* `compile.Manifests._tu` now reads a declaration-only unit: with no function records it
  anchors the `Tu` at the first datum its source has in `data_placements.txt` and records
  `line_offset = line_size = 0`.  No code and no placement row is a refusal.
* `Tu.address` / `Tu.end` fall back to that anchor, so the sort key in
  `configure._promotions` and the empty `.text` span (`_split_extent`) are defined.  The span
  is anchored at `geometry.loadable_vram`, because retail's VA 0 is the ELF header and
  `Elf.read` refuses it even for a zero-byte read.
* `configure.Promotion.code` is false for such a unit: the pinned ld script does not list its
  object (there is no `.text` to place; the datum arrives through the ledger), and the graph
  writes no `.line` objsec edge (the object has no `.line` section).
* The `tu_builds` row is `("src/AM/s573/play/oni_list.c", "3.0b38-030307",
  "-c -lang c -O3 -opt full -g")` and the ledger row is
  `course_list = 0x002AFD40; // size:0x28D4 extent:0x28E0 source:src/AM/s573/play/oni_list.c`.

`./ddr verify --tu src/AM/s573/play/oni_list.c` reports

    text ok (the translation unit declares no code)
    debug chunk ok (1 chunk(s), 1470 bytes)
    line chunk ok (nothing to compare in line)

The tests that pin the wiring are in `tests/toolchain/test_compile_extent.py` (the empty
extent, the anchor, the refusal, `_tu`'s read of the ledger row) and `tests/test_configure.py`
(the data-only `Promotion`, no `.text` in the ld script, no `.line` edge in the graph).
