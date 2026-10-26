# Unit work — how a translation unit gets promoted on `ddrex2p`

Reference for anyone (human or agent) writing matching C for this target. The loop below is the
one that actually produced `src/sys/sys_scf.c` and `src/sys/sys_demo.c`; every command in it exists
and is exercised by the suite.

Two external documents are worth reading alongside this one, for different reasons:

- `zeldaret/tww`'s `docs/decompiling.md` — the fullest unit-work workflow anyone has written down.
  Its central lesson is platform-independent: **inline and macro usage is invisible in the
  disassembly but changes codegen**, so a semantically correct function can still fail to match.
- `LucasPicoli/god-hand-decomp`'s `docs/ps2_mips_cheatsheet.md` — EE register/ABI table, delay
  slots, `nop` padding at TU boundaries, and a per-TU compiler table like our `tu_builds`.

We differ from both in one important way: **our target ships full Metrowerks DWARF**, so names,
structs, frames and statement lines are given rather than inferred. Work with them; they are the
reason this loop is cheap.

## What "promoted" means

A translation unit counts as promoted only when `./ddr --target ddrex2p verify --tu <tu>` reports
**all three** parts ok:

| part | what must match |
|---|---|
| `.text` | the compiled instructions, byte for byte — **this is the promotion proof** |
| `.debug` | the debug chunk for that unit, reconstructed from retail's inventory under `--adopt-retail-meta` (types, member order, visibility) |
| `.line` | the statement→address line table. It is a structural hint and a localiser (`tools/units/line_map.py`), never a gate; the chunk is reconstructed from retail's inventory at promotion, so a reformatted source is allowed (see "`.line`: corroboration and a localiser, never a gate") |

**Promotion is always adoption.** Every `tu_builds` row is `(source, compiler build, flags)`;
`configure.py` puts `--adopt-retail-meta` on each promoted unit's `cc` edge, which proves
`.text` byte-identical, reconstructs `.debug` from retail's inventory and substitutes retail's
`.line` chunk. What the source must then preserve is *which statements share a line*, not the
physical number (see "Tidying a promoted source").

### A unit with no code: data-only promotion

A translation unit can own initialised data and no function at all. The first one is
`AM/s573/play/oni_list.c`: two types and `oni_course course_list[39]` (0x28D4 bytes at VA
0x002AFD40), one declaration CU, no function CU. It is promoted like any other unit, with an
empty `.text`; the proof moves to the datum and the chunk.

- **The datum is the proof.** `data_placements.txt` names it, and `cc` relocates and compares
  the object's bytes with retail at that address before the link places it. The row's `extent`
  is the retail span to the next datum; the zero fill inside it is a pad piece, so G1 still
  compares every byte.
- **No `.line` chunk exists** (there are no statements), so `configure.py` writes no `.line`
  payload edge -- the object carries no `.line` section to dump. `.debug` is still one chunk
  (the declaration CU's types) and must come out retail's, as always.
- **The object is not listed in the ld script.** A unit with no code has no `.text` to place;
  its datum reaches the link through the placement ledger alone. Its `Promotion.address` (the
  sort key) is its first datum's address.
- **`verify --tu` reports** `text ok (the translation unit declares no code)`,
  `debug chunk ok` and `line chunk ok (nothing to compare in line)`.

A unit whose DWARF declares no function *and* which no `data_placements.txt` row names is
refused by `compile.Manifests._tu`: there is nothing to place.

### `.line`: corroboration and a localiser, never a gate

Line numbers are **recovery evidence**, never part of the promotion proof. Before writing code,
read the map -- `python3 tools/units/line_map.py --tu <tu>` -- for retail's statement shape per
function: the span, the lines carrying more than one statement, the lines carrying none, and
where the braces are. Use it as a structural hint. A gap is a blank line, a comment, a
declaration with no code, or a statement that produced nothing; an unexpectedly large gap is
where an inline hides. Chase `.text` first. A byte-equal function whose lines then match is
corroboration, and where they do not, the moved row localises the guess. A `.line` difference
never blocks a promotion, because:

- the **promotion proof** is `.text` byte equality, with `.debug` under the conditions below;
- the `.line` chunk the image carries is **reconstructed from retail's inventory** -- the unit's
  split linetable -- rather than from the source's physical layout: `--adopt-retail-meta`
  substitutes it (along with the metadata the unit needed) for every promoted unit;
- a promoted source may therefore be **reformatted freely** (comments stripped, blank runs
  collapsed, declarations grouped) without moving the image by a byte;
- the checksum that matters is the **linked ELF's** (`G1`, `ef31c90f…c02cd`). `verify --tu` is
  necessary but not sufficient, for the staleness reason below.

The evidence survives in `docs/line-inventory.md`, generated by
`python3 tools/units/line_inventory.py` (and checked by `--check` exactly like the status report).
For every promoted unit it records the split linetable's byte size, table count, record count and
a sha256 prefix, plus the record count our own committed layout emits and how many rows differ,
measured through the unit's own `tu_builds` pair with `--adopt-retail-meta`. The inventory is
descriptive: it says whether the committed layout still reproduces retail's table or no longer
corresponds to it, and retail's chunk is what the image carries either way.

**A per-unit green is necessary but not sufficient.** Observed twice: `verify --tu` reported all
three parts ok for units whose `.debug`/`.line` payload was *smaller* than the pinned layout, and the
link then refused with `the code splits are not the retail N bytes`. So build the image before
believing a promotion — `ninja` runs `g1` as its last edge, and that edge is what promotes a unit.
And `ddr verify` on its own can report `G1 ok` against a **stale** `out/SLUS_211.74` left behind by a
failed build, so treat freshness as part of the check.

**What "the extent it replaces" means, and what the build now says about it.** A promotion is placed
where its *splits* were, and a splat split runs from its symbol's address to the **next** symbol's
address — so the last split of a unit usually covers bytes past the unit's last function. That
overhang is retail's `nop` padding, and `tools/toolchain/compile.py` measures the extent from the
split files themselves, fills the overhang from retail, and prints what it filled:

```
compile: src/sys/sys_demo.c: filled .text trailing nop padding from retail (0x8 bytes)
```

It fills **only** `nop` — in the overhang and in the inter-function gaps alike. Anything else is
content this unit has not written, and is refused by name, chunk and byte shortfall, saying the C is
incomplete rather than that the link is broken. `.debug` and `.line` are never padded at all:

```
compile.py: error: src/sys/sys_demo.c: condition 2 (.debug length and DIE count) failed:
  the unit's types .debug is short by 0x4B bytes; C is incomplete (cannot pad .debug)
compile.py: error: src/CS/lang.c: mesGetLanguage01 .line is short by 0x1E bytes;
  C is incomplete (cannot pad .line)
```

So the old `the code splits are not the retail N bytes` is now the *backstop* for a real
configuration error, not the first thing a short unit produces.

Inside that, the whole-image gates stay green by construction and are the safety net:
`./ddr --target ddrex2p verify` (G1, the template ELF is `ef31c90f…c02cd`) and
`./ddr --target ddrex2p iso` (G3, the rebuilt disc image is `70a90566…652b`). Undecompiled code is
the split's own bytes, so the image links byte-identically no matter how little is written.

### The one recorded `.debug` deviation

A unit whose **only** `.debug` deviation is the anonymous-type DIE order may be promoted.  The
gate applies four conditions in order: (1) `.text` and `.line` are **byte-equal**, never relaxed;
(2) the emitted `.debug` chunk is exactly retail's length and holds retail's DIE count;
(3) the two chunks are identical as **multisets of DIEs compared structurally** — tag, size,
member names/offsets/kinds, variable and parameter attributes — with only the synthesized
`@anonN` names normalised; (4) anything else refuses, naming the failed condition and the first
offending DIE (a missing or extra DIE, a changed member, a different tag, a different length).
On acceptance the gate prints an explicit boundary line, keeps retail's `.debug` chunk in the
image (so G1 remains the pin), and the measured permutation is recorded as a comment on the
unit's `tu_builds` row and as a line in this section.  No unit has been accepted this way yet.

### The `--normalise-debug` step, and exactly what it proves

A second step stops *recognising* the permutation and *rewrites* it:
`tools/toolchain/debug_normalize.py`, reached through `compile.py --normalise-debug`
(off by default, so the gate's own "keep retail's bytes" treatment stays the promotion path).
No promoted unit puts it on its `cc` edge: the adoption step applies the same normaliser
internally where a chunk needs it, and every `tu_builds` row is adopted.

It parses both chunks into DWARF 1 DIE trees, pairs DIEs one-to-one at every level by
structural signature (tag, attributes with references normalised to their target's shallow
description, sorted child signatures), lays our records out in retail's sibling order --
**recursively**, so a lexical block reorders its own children and not only the top level --
recomputes every `AT_sibling` from the new layout, and rewrites every intra-chunk offset
reference.  Records whose signature is identical (retail emits structurally identical arrays
and subroutine types as distinct DIEs) are paired by the attribute code and signature of the
record that references each one, and only when even that does not tell them apart, in
emission order: pairing twins by position alone rewrites a local to its neighbour's array
(`net_win_menu.c`'s two `[3]` board arrays are that case).  Which attributes carry a
reference is enumerated from retail's whole `.debug` (118,116
DIEs) rather than assumed: `0x0012` `AT_sibling` (recomputed positionally), `0x0072`
`AT_user_def_type` (18,797 occurrences), `0x0142` (7), `AT_subscr_data`'s element and index
types, `AT_mod_u_d_type`'s trailing reference, and the MW block `0x2303` (a bare reference in
all 1,782 of its occurrences).  A reference inside the chunk that names no DIE refuses, and a
rewritten chunk that is not retail's byte for byte refuses -- there is no tolerance and no
partial result.

**What it proves, and what it does not.** It proves the two objects differ in *emission order
only*: the same DIEs, types, members and references, reordered.  It makes no new claim about
the C source -- a source that reproduces retail's bytes under one build and only the byte-set
under another is exactly the case where this step applies.  It prints that it normalised,
with the counts the unit's record quotes, and the `--compare` line marks the part
`[normalised: our DIE order re-emitted as retail's]`.

Measured on `net_grf.c`, `3.0b38-030307 -c -lang c -O3 -opt full -g`: the emitted
`0x638`-byte chunk differs from retail's in **702** bytes, first at `+0x5D` (the
`AT_user_def_type` of `dancer_num`, `0x00084F7F` against retail's `0x000852B2`); after
normalisation 31 of its 41 DIEs have moved, 8 references are rewritten, and the chunk is
retail's **byte for byte** (0 differing bytes).  That normalisation now happens inside
`--adopt-retail-meta`, which every promoted unit goes through; `sys_scf.c`'s `652`-byte chunk
is byte-equal outright, so the normaliser is inert there.  `3.0-011126 -c -lang c -O3 -opt
full -g` reproduces both units byte for byte without the normaliser.

### Adopting retail's metadata: `--adopt-retail-meta`

`tools/toolchain/debug_adopt.py`, reached through `compile.py --adopt-retail-meta`
(off by default at the tool level, mutually exclusive with `--normalise-debug`, and on every
promoted unit's `cc` edge), is for the unit whose **instructions are already retail's** and
whose debug metadata is not.  It adopts, and proves the result is retail's chunk byte for
byte:

| what is adopted | precondition | what the report names |
|---|---|---|
| retail's `.line` chunk, whole | `.text` is **byte-identical to retail's**; otherwise the step refuses loudly, before touching `.line` (`.text` differs, first byte at `+0xN`) | how many `.line` rows changed, and in how many statement tables; or that the emitted table is not row-for-row comparable (a normalised layout can emit a different number of records) and is therefore adopted whole |
| `AT_location` values in `.debug` | the local's record is otherwise retail's (the DIE set is matched one-to-one; the location is excluded from the pairing signature) | every local by name and owning function, with the values: `n (in play_anime_step_inst): scratch -> $a2` |
| anonymous `@anonN` names, and reference words between structurally identical DIEs | the referenced DIE is structurally identical to retail's -- duplicates are interchangeable, so retail's choice among them is adopted | every name (`@anon1 -> @anon0`) and every rewritten reference (old -> new, attribute, owning DIE) |
| one of **our** `.debug` records that retail does not have | `.text` is byte-identical, and the record's whole subtree has no retail counterpart; the record is dropped, its references are remapped, and the remaining bytes must equal retail's | every dropped DIE: tag, name, chunk offset and span (`dropped extra DIE +0x64C6 local_variable 'dmm_t' (0x21 bytes; no counterpart in retail)`) |
| every surviving record's `AT_sibling` word | the drops are final, so the record's subtree end is the laid-out position; a child chain whose records were all dropped contributes no terminator either | every recomputed word: `recomputed AT_sibling 0x00059F48 -> 0x00059EFF (in +0x3C5B compile_unit …)` |
| an attribute retail carries on a paired DIE while ours lacks it (measured: the `0x2303` access-reference list) | the attribute is a list of 4-byte references, and every target has a paired DIE | the attribute and its owning DIE (`adopted attribute 0x2303 on …`) |
| an entry of one of **our** `0x2303` access-reference lists that names a dropped *global declaration* (the `extern D_<addr>` of a DWARF-less data object, which retail has no DIE for) | the dropped target is a `global_variable`/`global_subroutine` with no identical surviving twin, and at least one other entry remains; the entry, the list's length word and the record's length word go, every later offset follows, and the chunk must still equal retail's | the dropped declaration (`dropped extra DIE … global_variable 'D_006B2F58'`) |

**The distinction is explicit:** extra records on our side may be **dropped**; a record
retail has and we do not must **refuse** -- fabricating a DIE would be invention, not
adoption.  `_pair` only returns leftovers for our side, and the refusal names the missing
retail DIE (`no counterpart in the emitted chunk`, or `a missing record is not fabricated`
when the chunk is shorter).

**A drop moves positional words.**  `AT_sibling` is not a reference: it names the laid-out
end of the record's subtree, so a drop invalidates it even though every reference word stays
put.  After the layout is final every surviving record that carries the word is recomputed
to its laid-out end, and a child chain whose records were all dropped takes its four-byte
terminator with it (the end-of-subtree arithmetic counts a terminator only for a chain that
still has records).  `info_data.c` is the measured shape: the two locals in
`get_table_no_by_infotxt_num` (`0x49` bytes) empty their lexical block's chain, and the
block's, the function's and the CU's words each moved four bytes past retail's before the
recompute.

Then the **whole `.debug` chunk must equal retail's**.  Anything else refuses, naming the
DIE and attribute; there is no partial adoption.  The `.line` substitution is the reason the
step exists: `condition 1`'s `.line` half is relaxed *only* here, and `.text`'s half is not
relaxed at all.

Measured on `p_anime.c` under `3.0b38-030307 -c -lang c -O3 -opt full -g`.  With its
original `#line` layout the report named 10 statement lines that moved (first at
`.line+0x45A`: ours 115, retail 114; 35 of 244 rows byte-different in 5 tables).  The
promoted source is now normalised (see the `#line` reflow section), so the emitted table
carries 4 more records than retail's (`play_anime_step_inst` +1, `play_anime_step` +3) and is
not row-for-row comparable: the report says so and retail's chunk is adopted whole.  Either
way the `0x4273`-byte `.debug` chunk differed in `n`'s location in both large functions --
the emitted value is MW's `scratch` (`DW_OP_reg2`), retail's is `$a2` (`DW_OP_reg6`) -- and
adoption takes retail's `.line`, both `n` locations, 4 anonymous names and 15 reference
words, leaving the chunk retail's byte for byte (414 DIEs).  `verify --tu` reports all three
parts ok and G1 is `ef31c90f…c02cd`.

Measured on `dmm_chara.c` under the same pair: `.text` and `.line` are byte-equal
(`0x1D0` / `0x152`), but `.debug` is `0x16A` against retail's `0x151` -- the block-scoped
temporary that forces retail's register split adds one local record (`dmm_t`,
`local_variable` at `+0x64C6`, `0x21` bytes), and the function DIE lacks retail's `0x2303`
access-reference list.  Adoption drops `dmm_t` (the 33-byte span and the 8-byte adopted
attribute explain the block's 25-byte difference), adopts `0x2303`, 24 anonymous names and
142 reference words; `.debug` becomes retail's `0x64DA` bytes / 666 DIEs, `verify --tu` is
ok on all three parts, and G1 stays `ef31c90f…c02cd`.  A *missing* record is still the
refusal case: adoption never fabricates a DIE retail has and we do not.

## The loop

1. **Pick a unit by shape, not by size.** Small turned out to mean hard: the three smallest candidates
   were a `mes_*` unit (blocked on `.debug` DIE ordering), a VU0 unit (blocked on the epilogue sinking
   into the last inline-asm delay slot), and one whose `.text` needs an in-extent `nop` with an exacting
   scratch-variable shape — 4½ hours of agent time between them, nothing promoted, while the first unit
   that *did* promote took 15 minutes. Choose instead:

   - few functions, **scalar** code, and **no VU0** (`.vutext` has its own section and its own blocker);
   - **no large unreferenced file-scope tables** (the `mes_*` blocker class);
   - calls either absent or already named in `config/ddrex2p/borrowed_symbols.txt`, so no library name
     has to be imported mid-unit;
   - plenty of DWARF line records, because the statement map is richest there and a moved row
     localises guesswork fastest.

   **Time-box it: about thirty minutes.** If it is not green by then, commit it as WIP with what you
   learned and take the next one. A unit that resists is a finding; three hours on one is a lost
   afternoon, and the shape list above exists so the next person avoids the class rather than the unit.
   Counts and paths come from `config/ddrex2p/cus.json`.

2. **Gather the evidence** (do not guess any of it):

   ```bash
   python3 tools/oracle/dwarf1.py fn  orig/SLUS_211.74 <symbol>       # signature, frame, saved regs, globals
   python3 tools/oracle/dwarf1.py lines orig/SLUS_211.74 <VA> --table # the retail statement line numbers
   cat include/src/<dir>/<tu>.h                                       # structs, globals, prototypes, line ranges
   cat asm/nonmatchings/main/<symbol>.s                               # the disassembly to reverse
   ```

3. **Read the line map before writing code — it is retail's statement structure.** One command
   prints, per function, the retail VA range, word count, line span, and the lines that carry
   more than one statement or none at all:

   ```bash
   python3 tools/units/line_map.py --tu <tu>          # --raw every row; --json for tooling
   ```

   The shape says where a `switch` dispatch, a chained assignment, or an inline you have not
   written sits, before the compiler says anything. A `.line` mismatch is corroboration or a
   localiser, never a gate: chase `.text` first.

4. **Write the C on retail's line numbers.** The line numbers are evidence, not a suggestion. If the
   generated header spells a tag bare (`_tag_X`, C++ syntax), write `struct _tag_X` in the C; if a
   gap between two statements is large, the original had lines you have not reproduced yet — often an
   inline, sometimes a declaration — and the map will show the hole until they are accounted for.

5. **Iterate with the diff, not with the gate.** The gate compiles the whole unit; the diff scores one
   function against **retail's bytes**:

   ```bash
   ./ddr --target ddrex2p diff <symbol> <tu>
   ```

   It prints what it compared (target = the retail bytes of the symbol, base = your C object, or the
   split's own bytes when the unit has no C). A 100.0% on an unpromoted function is normal and is the
   signal to move on.

6. **Gate the unit**, then commit it alone:

   ```bash
   ./ddr --target ddrex2p verify --tu <tu>
   git add <explicit paths> && git commit -m "ddrex2p: promote <tu>"
   ```

   A promoted source carries **no `#line` directive**, and the build is what enforces it:
   `configure.py` refuses a `tu_builds` source that still has one *before* it writes
   `build.ninja`, and `compile.py` (the `cc` edge) refuses the same unit before the compiler
   runs.  Both name the file, the count and the remedy.  Run
   `python3 tools/toolchain/line_reflow.py <src> --normalise` before committing and commit the
   rewritten file: the tool strips the directives, proves `.text` byte-identical, and reports
   the `.line` rows that adoption takes from retail (see "The `#line` reflow step").  There is
   no silent path: a directive-laden source can neither be configured nor built, and its
   staged copy is never rewritten behind the committed file's back.

   Promoted C is committed with **no comments at all**.  Run
   `python3 tools/units/strip_comments.py <src>` (it recompiles before and after under the
   unit's `tu_builds` pair and writes only when `.text`, `.debug` and `.line` are identical),
   then gate the stripped file with `verify --tu` and commit it.  Every comment is blanked --
   the header block and `/*!`/`//!` notes included; a note worth keeping belongs in this
   document, not in the source.  `strip_comments.py --check <src>` is the gate that enforces
   it, and it fails while the file still carries a comment (see "Stripping comments from a
   promoted source").

   Then tidy the layout:
   `python3 tools/units/strip_comments.py --collapse <src>`.  It strips the comments and
   collapses blank-line runs to one, strips trailing whitespace and drops the lines the header
   and notes left behind.  Because
   that **moves statement lines**, retail's `.line` chunk is what the image carries -- every
   promoted unit's `cc` edge runs `--adopt-retail-meta` -- and the row comment should say the
   layout is tidied and `.line` adopted.  The tool compiles the committed and
   tidied spellings through the promotion path and requires each function's `.line` record count
   to be equal (the directive grouping must survive), then accepts only when `.text` is
   byte-identical and `.debug`/`.line` are retail's after adoption.  Gate with `verify --tu`,
   rebuild with `configure.py` + `ninja`, and check the G1 pin (see "Tidying a promoted
   source").

   Finally refresh the persisted record: `python3 tools/units/line_inventory.py` rewrites
   `docs/line-inventory.md` with the unit's split-linetable size, tables, records and digest,
   and the row count and differences its emitted table produced.  `--check` is the staleness
   gate.  The file covers every promoted unit, so it is a shared document: the controller
   updates it with the `tu_builds` row rather than each unit agent committing its own copy.

7. **Record the compiler.** Measure the pair that reproduces this unit with
   `tools/toolchain/select_build.py --tu <tu>` and add it to `tu_builds` in `config/targets.py`.
   `configure.py` refuses to promote a source nobody has measured.  Record
   `("src/<path>.c", "<build>", "<flags>")` -- the row is exactly the measured pair, and
   `--adopt-retail-meta` goes on its `cc` edge: `.text` byte-identical is the proof and
   retail's inventory supplies `.line`/`.debug`.  The row comment quotes the measurement.  As of the last
   batch: four builds (`3.0-011126`, `3.0.1-020123`, `3.0.3-020716`, `3.0b38-030307`) reproduce a
   unit byte-for-byte at `-c -lang c -O3 -g`; `.comment` separates them as *provenance*
   (`3.0b38-030307` writes `(3.0.0)` where retail has `(2.4.1.01)`), and **only `.text` can
   separate them as reproduction** — `.debug`'s producer string is version-less.  The pair
   recorded today is `3.0b38-030307 -c -lang c -O3 -opt full -g`, and every row is adopted
   (its `.line` comes from retail's inventory): b38 takes the promoted units'
   `.text`/`.line` byte-exactly, `sys_scf.c`'s `.debug` is byte-equal outright, and `net_grf.c`'s
   chunk -- the same DIE set in b38's order -- is normalised to retail's DIE order and is
   byte-identical (see "The `--normalise-debug` step" above).  Neither `.comment` nor the chunk's
   order reaches the image, so the pair is a reproduction recipe, not a claim about which build
   the game shipped.  A unit that contradicts the recorded pair is a finding worth reporting
   loudly.

   **The flag string is half of the pair, and one unit has already contradicted it.** `p_anime.c`
   (`AM/s573/play/p_anime.c`, candidate #12) needs `-c -lang c -O3 -opt full -g`: its two large
   functions reach 78.15% and 88.76% of retail's words with `-opt full` and only 69.97% and 67.19%
   without it, and the difference is mechanical — **`-opt full` is what turns a `pid`-indexed address
   into a walking induction variable**. At `-O3` mwcc emits `mult` for `pid * 0x5428C` once per
   iteration, no `sp+0xA0` slot for the `paw_p->db[pid]` index, and a frame 0x30 bytes smaller; with
   `-opt full` it emits retail's `addu base, base, <size>` increment at the loop bottom and the 0xD0
   frame. All five installed builds behave identically under `-O3` and identically under
   `-O3 -opt full`, so this is a *flag* fact, not a *build* fact, and it is invisible on a unit with
   no indexed address inside a loop — which is why `sys_scf.c`'s recorded pair could not show it.
   Per-unit flags exist for exactly this; `tu_builds` carries the whole string.

   **A second trap, measured the same day: the `--compare` invocation ignores `tu_builds`.**
   `python3 -m tools.toolchain.compile <src> <out> --compare` takes its compiler from its own
   `--compiler` default (`fetch.REQUIRED`, 2.4-001213) and its flags from the command line, not from
   the target descriptor — only `ninja`'s `cc` edge uses the recorded pair.  On `p_anime.c` that made
   the unit look `2 bytes short` (and a first attempt, without `-opt full`, `0x10 short`) from nothing
   but the wrong compiler: the 2.4 build saves the frame with `sq`/`lq` where retail has `sd`/`ld`, so
   the "shortfall" was the frame's instruction shape.  To compare a unit by hand, pass the pair in
   full: `--compiler 3.0-011126 -c -lang c -O3 -opt full -g`.

## What the diff's failure modes mean

The diff reports *shape*, and each shape points at a different cause. Read it as a diagnosis, not a
score:

| what you see | what it usually means |
|---|---|
| registers swapped, instructions reordered, an instruction duplicated | expression or macro/inline shape — try the original's macro or inline, not a logic change |
| a spurious `jal` argument mismatch (`jal sceScfGetDateNotation` vs `jal func_001B3840`) | a *naming* difference, not a code difference — the split cases by address, retail by name |
| `.line` mismatch only | statements on the wrong source lines: a missing declaration, an inline, or re-wrapped expressions |
| `.debug` mismatch only | types, member order, bitfield spelling or visibility differ from what the compiler recorded |
| `.text` correct size but wrong bytes | wrong expression form, wrong flag, or wrong helper |
| `.text` different size | the source structure differs (extra call, missing call, different control flow) |
| `.debug` a few bytes *short* of the pinned layout | missing parameter or local DIEs — declare the parameters the DWARF records (`dwarf1.py fn`), even unused; measured once as the discriminator that proved a unit's shape. The build refuses it (`condition 2 (.debug length and DIE count) failed: the unit's types .debug is short by 0xN bytes; C is incomplete`) rather than padding it |
| `.line` short of the pinned layout | a statement the original had has no counterpart, or an inline is unwritten. Refused the same way (`<fn> .line is short by 0xN bytes; C is incomplete`) — one 10-byte record per statement, so the shortfall says how many are missing |
| the build fills `.text` padding and says so (`filled .text trailing nop padding from retail (0xN bytes)`) | the unit's last split ran past its last function and retail's bytes there are `nop` — normal, and now handled |
| the link refuses with `the code splits are not the retail N bytes` | a real layout error: a split that is in no object, a symbol at two addresses, a split order that is not the address order. A *short unit* no longer reaches it |

When a function resists matching after the logic is right, check the line table for skipped lines
before assuming a mistake: that is where an inline hides.

## What is given, and what we invent

Given (do not re-invent): function names, signatures, frames, saved registers; 8,152 local names,
3,930 parameter names, 1,043 globals; 292 named aggregates with member names and offsets; 13,756
array types; the statement lines. Library names arrive from the archives with byte evidence, into
`config/ddrex2p/borrowed_symbols.txt` — hand-written, byte tier only, merged into the generated
`symbol_addrs.txt` by the oracle; run-tier *proposals* live in `library-names.md` and must never
enter the build artifact.

Invented, with provenance recorded — because DWARF does not carry it:

- **typedef spellings** (zero typedef DIEs; types are structural only),
- **enum members** (17 enumeration types, no enumerators),
- **anonymous aggregate tags** (`anon_<N>_<unit>`, per unit, since the same synthetic name means
  different types in different units),
- **descriptive names** for the DWARF-less engine code, which has no names at all.

The rule to follow is tww's, and it is a good one: **no names are better than incorrect names.**

## Data with no DWARF name: `D_<addr>`, never a raw address

**Precedence: a DWARF name first, `D_<addr>` only when no debug object covers the address.**
"Covers" includes a *member* of a DWARF-named global: `D_006B2F58` is `g_game_w.last_data_addr`
(`g_game_w` is at `0x607A70`, size `0xACDC4`; `0x6B2F58 - 0x607A70 = 0xAB4E8`), so it is spelled
that way, never as an `extern ... D_006B2F58[]`.  `python3 tools/units/dwarf_audit.py [--all]`
lists, for every `D_<8hex>` name and raw hex constant in a promoted source, the member expression
the debug information gives its address (or `none`); run it before reaching for a `D_` name.
Measured on `bk_disp.c`: `D_006B47F0` -> `g_game_w.bk_ef_kind` is byte-identical in `.text`,
`.debug` and `.line`.  `D_006B2F58` -> `g_game_w.last_data_addr` (cast to `unsigned int` where
passed to an integer parameter) also gives identical `.text`, but the compiler's `@N` label for
the unit's string literal moves (`@87` -> `@91`, any spelling of a store through that member), so
the unit's key in `data_placements.txt` moves with it; the retail address is unchanged.

A promoted source **never** reaches a data object by a hard-coded address
(`*(unsigned int *)0x006B2F58`, `(struct x *)0x00824450`).  The name of an object comes from
DWARF; where retail's debug information has none, the name is splat's address-derived
`D_<8 hex digits>` (`D_006B2F58 = 0x6B2F58;` in `config/ddrex2p/undefined_syms_auto.txt`) --
exactly as an unnamed function keeps `func_<8 hex digits>` (AGENTS.md rule 3: names are never
invented).  A function reached through a pointer takes the function's name (the DWARF name if
`symbol_addrs.txt` has one, `CwsWinOpen` for `0x00207360`; `func_XXXXXXXX` otherwise), never a
cast address.

**The spelling is an incomplete-array extern, subscripted:**

```c
extern unsigned int D_006B2F58[];
extern int D_006B47F0[];
...
size = SdFFTInit(D_006B2F58[0]);
D_006B2F58[0] += size;
```

Measured against `bk_disp.c`: a plain `extern unsigned int D_006B2F58;` is small data to this
compiler and is addressed `$gp`-relative, which `compile.py` refuses when the address is out of
`$gp`'s reach (and `-sdatathreshold 0` on the row moves other functions of the unit); the
incomplete-array form is never small data, so it gives the `lui`/`lw` absolute addressing retail
has.  The element type is the type the access reads; a pointer object is
`extern struct _CWS_WIN_W *D_00824450[];` read as `D_00824450[0]`.

The extern puts a global-declaration DIE in our `.debug` that retail does not have, and the
function's `0x2303` access list names it.  `--adopt-retail-meta` drops the DIE and the list entry
(see the table above); the whole chunk must still equal retail's.  **Trust `./ddr build`, not
`./ddr verify --tu`, for this**: the per-unit verdict can report ok while the full build refuses
in adoption.

Only a *name that exists* can be used.  A data address with no `D_<addr>` entry (an initialiser
value such as `pOpening = (struct _tag_cOpening *)0x006D33A0` in a file-scope definition, whose
bytes are not linked -- rule 9) has nothing to name; leave it and list it in the unit's report.

An address used as an *integer constant* cannot be named at all: `ps2dancerPdataLoadInit((void *)0x01874000)`
in `fp_doll_init` compiles to `lui; ori` in retail, while any symbol reference gives `lui; addiu`
(measured with `extern char D_01874000[];`), so that one raw constant stays.  It is a value, not
a data access; do not loosen adoption's `.text` equality for it.

The overlay window (`D_00824450` and its neighbours, outside every declared segment) is named
the same way: `compile.py` resolves a `D_<8 hex>` outside the segments as its own address, and
`shop_select.c`, `shop_info.c`, `dmm_mess.c` and `fp_qmenu.c` use `extern struct _CWS_WIN_W
*D_0082445x[];`.  Two measured rules for those:

* A function whose only reference to the object is the `extern` makes the compiler record a
  global-declaration DIE and a `0x2303` entry; adoption drops both, and drops the whole `0x2303`
  attribute when every entry is such a declaration and retail's record has none.
* A local initialised straight from the extern (`winp = D_00824450[0];`) loses its
  `local_variable` DIE under this compiler, which adoption refuses ("children of ... lexical_block
  holds 0 DIEs against retail's 1").  Spelling the initialiser with a cast to the local's own
  type (`winp = (struct _CWS_WIN_W *)D_00824450[0];`) keeps the DIE (`dmm_mess.c`).

One listed exception remains: `src/common/cws/multi_window.c` keeps `#define D_00824450
(*(struct _MULTI_WIN_W *)0x824450)` and `#define D_00824470 ((char *)0x824470)`.  Retail indexes
the window array with a variable (`pwin[win_num]`) and folds the address's low half into the load
(`lui; addu; lw %lo`).  MWCC folds a *constant* address that way, but a symbol indexed by a
register is always `lui; addiu; addu; lw 0` -- measured for an incomplete array, a sized array, a
struct, a defined (non-extern) object, and a cast-and-add spelling, each one word too large per
access (`MultiWindowSetCautionMark` is 0x8 bytes over).  No spelling of the symbol reproduces
retail, so the raw constant stays and is the only way that unit matches.

## An initialiser is the recoverable truth, never a `{ 0 }` placeholder

A file-scope object's initialiser is written out from retail's bytes whenever they give it, because
the promoted source is the only place that evidence lives and rule 9 makes it free: `compile.py`
links only the object's `.text`, so the compiled `.data`/`.rodata` never reach the image and cannot
move a gate. Measured on `tra_str.c` (13 pointer tables plus `tr_str_tbl`, 40 pooled literals):
`.text` came out byte-identical, the placed `.debug` and `.line` chunks were byte-identical, and
the only raw-`.debug` change was the documented DIE-order class (same length, same 50 DIEs, absorbed
by `--adopt-retail-meta`). The initialiser must still be *recovered*, not guessed: retail's databin
pinpoints every entry (`tr_str_play[0]` points at `0x002D7390`, `tr_str_ck_menu[1]` at `BACK`, not
`CHECK`), and a wrong literal is invisible to `.text`/`.debug`/`.line` and only surfaces when the
data itself is compared against the databin. Keep the initialiser even where only `{ 0 }` is known:
a static's *having* one is what makes MWCC tag it `.local_variable` (see the blocker table), so the
placeholder's presence is load-bearing even though its contents are not.

## Comment style

**Three source-form rules cover a promoted file, and each has a mechanism that enforces it:**
no comments and no blank line directly inside a brace (`tools/units/strip_comments.py
--check`), and no `#line` directive (`configure.py` before it writes `build.ninja`, and
`compile.py` at the `cc` edge, both naming the count and the remedy).  They exist because the
source is evidence: a comment is an essay in the wrong place, a brace-padding blank is a style
choice pretending to be layout, and a directive means the file a reader sees is not the file
the compiler numbered.  The brace rule bends for a promoted source: its `.line` chunk pins
the statements to retail's line numbers, so a blank line inside a brace *is* the line retail
gives the statement after it, and `--check` passes it; a file with no `tu_builds` row has no
such evidence, so there the blank is padding and fails.

**A committed promoted file carries no comments at all.**  The C is evidence, not an essay,
and the evidence lives beside it, not in it:

- **No top-level header comment.**  A committed promoted file starts with its first declaration
  or `#include`; the source path the DWARF records, the pair, and the measurements live in the
  `tu_builds` row comment and this document.
- **No inline comments either.**  A note about a magic constant, an unusual expression shape
  or a gap the evidence forces belongs in this document, in `docs/milestones/*.md`, or in
  `config/<target>/library-names.md`.
- **No markers.**  `/*!` and `//!` are blanked like any other comment: there is no opt-out.
  `tools/units/strip_comments.py` blanks every comment, and
  `tools/units/strip_comments.py --check <src>` fails while the file still carries one (see
  "Stripping comments from a promoted source").

**One mechanical exception, and it is a real one:** the `.line` gate pins *statement* lines to retail's
own line numbers, so the number of lines before the first statement and between statements is fixed by
evidence, not by taste. Where that forces space, use **blank lines** — a comment thick enough to fill a
twenty-line gap is padding pretending to be documentation. While a unit is being recovered the
statement lines must not move; what fills the space between them is your choice. At promotion
retail's `.line` is substituted, so the *grouping* is what must survive (see "Tidying a
promoted source") and the physical numbers are free.

**A `#line N` directive is a drafting aid, and a commit never takes that form.** A directive
makes the line that *follows* it number `N`, so a draft can carry an `#include`, a type block
or a `#define` between two statements without forty empty lines standing in for them.
Measured on a draft of UnitC's `AM/s573/doll/dexport.c`, whose statements are at lines 61–105
while its type closure is 1,111 lines over 28 headers — the generated headers are the only way
to declare `SaveData` (0x1FF50 B) and `g_game_w` (0xACDC4) without moving the statements, and
the emitted `.line` numbers stayed retail's.  While it is a draft, three rules come with it:

- the directive numbers the *next* line, so the statement after it must be the one retail puts
  on `N`; put it immediately before that statement, not before a block of declarations;
- **`#line` numbers must stay monotonic inside a function.**  MWCC attributes a loop's
  preheader — the IV initialisations, a hoisted symbol, the peeled head statement — to the
  *highest* line number it has seen so far, not to the `for`.  With declarations parked on
  lines 383–401 and the `for` on 386, every head-statement record vanished and the preheader
  took line 401; compressing the declarations onto lines ≤ 385 and putting the `for` on 386
  took `play_anime_step_inst` from 94 line records to **103, retail's count exactly**.  `#line N`
  may be repeated to park several declaration lines on one number.
- **a `for` loop's increment and test carry the line of the body's closing brace**, not the
  `for`'s own line.  Measured on a probe: `for (n = 0; n < 4; n++) { … }` with the `}` on line 9
  records the `n++` and the test on line 9.  So when the line a `#line` must reach is a loop's,
  it is the brace's line that has to be right, and both of UnitC's candidate units are only
  explicable with that rule.

**A promoted source carries none.**  `configure.py` refuses a `tu_builds` source that still
has a directive before it writes `build.ninja`, and `compile.py` refuses the same unit at the
`cc` edge; both print the file, the count and the remedy
(`python3 tools/toolchain/line_reflow.py <file> --normalise`), never a silent rewrite of a
scratch copy.  The rules above are the ones the *rewrite* has to satisfy: the strict mode puts
the statement back on the physical line the directive named, so a draft that broke them does not
reflow strictly, and the normalising mode (`.line` adopted from retail) is the way out.

### The `#line` reflow step (part of promotion)

`tools/toolchain/line_reflow.py` removes a promoted source's `#line` directives in one of two
modes.  Both copy every non-directive byte unchanged; they differ in what they do to the line
layout, and therefore in what they guarantee.

**Strict (the default)** replaces each `#line N` with the blank lines that put the line after it
on physical line `N`, so every compiled line number survives by construction:

```bash
python3 tools/toolchain/line_reflow.py src/<dir>/<tu>.c          # rewrite in place
python3 tools/toolchain/line_reflow.py --check src/<dir>/<tu>.c  # same check, write nothing
```

It refuses, with a non-zero exit and a message naming the physical line, when the layout cannot be
expressed:

- **a directive that moves backwards** — `#line N` where the rewritten file has already reached
  line `N` or beyond.  Padding only adds lines, so the next line cannot sit there.
- **a gap larger than a screenful** — more than `MAX_PADDING` (40) blank lines for one directive.
  The refusal quotes the count and recommends `--normalise`: a directive standing in for a
  thousand-line type closure is a hole, and padding it is pretending to know what was there.
- **a directive carrying a file name that is not the unit's own** — the accepted spellings are
  the unit's DWARF name (`cus.json`'s `name`, e.g. `C:\work2\usaex2\src\sys\sys_scf.c`), its
  repository path (`src/sys/sys_scf.c`), or what `--unit-path` names.
- **a `#line` spelling it does not parse** (a macro, a continuation).

For a unit with a recorded pair in `tu_builds`, the strict rewrite is accepted only after the
source is compiled **before and after** through the promotion path with that pair and `.text`,
`.debug` and `.line` come out **byte-identical**; any difference refuses and the file is left
untouched.

**The build does not run this rewrite.**  A `tu_builds` source that still carries a directive is
refused, with a non-zero exit, by `configure.py` (before it writes `build.ninja`) and by
`compile.py` (before the compiler runs) alike:

```
src/<dir>/<tu>.c: 89 #line directive(s); a promoted source carries none: run
python3 tools/toolchain/line_reflow.py src/<dir>/<tu>.c --normalise
```

So a directive cannot reach a commit and be silently normalised at build time: the file a reader
sees is the file the compiler saw, or the unit does not build.  The rewrite is a step *before*
promotion, and this tool is the remedy the refusal names.

**Normalising (`--normalise`)** strips the directives and keeps the file's own, natural layout —
no padding standing in for comment blocks or blank lines nobody can know.  The guarantee changes:

- **`.text` must stay byte-identical**; if the rewrite moves even one instruction the tool refuses
  and writes nothing.
- **`.line` is allowed to diverge.**  The tool reports it: either *N of M rows differ* (when the
  emitted table is still row-for-row comparable) or *the emitted `.line` is not row-for-row
  comparable, +N records* (a changed layout can emit a different number of statement records).
  Either way `--adopt-retail-meta` takes retail's `.line` chunk **whole**, and `.text` byte-identity
  is that step's precondition.  The adoption step's row report degrades to an explicit
  `not row-for-row comparable … retail's chunk is adopted whole` line rather than refusing a source
  whose code is retail's.

Use it for a promoted unit whose directives exist to compress layout (the `dexport.c` class):
strict padding would be a wall of blanks, and every promoted unit is adopted, so retail's
statement table is what the image carries.

**Measured 2026-10-20, `src/AM/s573/play/p_anime.c`** (`3.0b38-030307 -c -lang c -O3 -opt full
-g`): 189 directives, 454 lines before and 265 after, zero left.  The normalised source
compiles to `.text` 0x950 bytes byte-identical to retail's; its emitted `.line` gains 4 records
(`play_anime_step_inst` +1, `play_anime_step` +3), so the table is adopted whole.  Before and after
compile through `_place_source` to identical `.text` (0x950), `.debug` (0x4273) and `.line` (0x9B0).
The strict/backwards refusal is exercised by `src/CS/dancemaster/dmm_chara.c`'s draft (`line 80:
#line 33 moves backwards…`); the strict compile check by `tests/toolchain/test_line_reflow.py`,
which recompiles `sys_scf.c` with a no-op directive inserted and requires the three parts identical
before and after, and the normalising check by the same file's normalise case (`.text` identical,
the diverging rows counted).  The build's refusal of a directive -- count, file and remedy -- is
`tests/toolchain/test_compile_directives.py` for the `cc` edge and `tests/test_configure.py` for
`configure.py`, which asserts the graph on disk is untouched when the refusal fires.

### Stripping comments from a promoted source (part of promotion)

`tools/units/strip_comments.py` blanks a promoted file's comments lexically.  It **replaces
the removed characters with spaces and keeps every newline**, so the file has the same number
of physical lines, every statement keeps the line number the `.line` gate pins, and indentation
that sat before a comment is still indentation.  A line that held only a comment becomes a line
of spaces followed by its newline -- a blank line, never a deleted one.  That is the whole
reason the step cannot delete text: `.line` pins *statement addresses to line numbers*, so
removing one line from above a statement would move the statement and fail promotion.  The
strip therefore never deletes or collapses anything; a line that held only a comment becomes a
line of spaces, and the *tidy* step below is what removes those lines -- deliberately, with
adoption as its acceptance.

The strip is lexical, not textual: `"..."` strings, `'...'` character literals and backslash
escapes are respected, so a `//` or `/*` inside a string is code.  It refuses, writing nothing,
on a malformed file -- an unterminated `/*` comment, a stray `*/`, an unterminated string or
character literal -- and on a line ending in a backslash continuation, because C splices such a
line before it tokenises and the comment structure the tool would strip is not the one the
compiler sees.

**Every comment is blanked -- there is no exception.**  The leading header block, an inline
note and a `!`-marked comment (`/*! ... */` or `//! ...`) all go: a promoted source carries
no comments at all, and a note worth keeping belongs in this document, in
`docs/milestones/*.md` or in `config/<target>/library-names.md`.  The tool does not rely on
its own blanking to hold that line: `require_no_comments` raises when a source still holds a
comment, `--check` fails while the file on disk is not clean, and the write path refuses to
write a result that carries one.

**Acceptance.** For a configured promotion unit the tool gets the pair from that unit's
`tu_builds` row and compiles the file **before and after** through the promotion path; it
writes only when `.text`, `.debug` and `.line` are byte-identical, and refuses (leaving the file
untouched) on any difference.  A unit with no recorded pair is refused rather than stripped
unchecked.  A file that is not a promotion unit has nothing to compile and is edited only with
`--no-verify`, with an explicit "nothing was compiled" line.  `--check` writes nothing and
**fails while the file still carries a comment** -- never evidence -- or, for a file with no
`tu_builds` row, a blank line directly inside a brace, where the blank would be padding (for a
promoted source the blank *is* the statement's line, see the tidy rule below): it is the gate
that keeps a promoted source clean, not a dry run.

```bash
python3 tools/units/strip_comments.py src/sys/sys_scf.c          # strip + verify + write
python3 tools/units/strip_comments.py --check src/sys/sys_scf.c  # fail unless already clean
```

**Measured 2026-10-20, the five promoted units.**  `src/sys/sys_scf.c` had three `/*!` notes
(the store/call packing, the `language = 1` constant, the epilogue that owns the closing brace);
all three were blanked, and the tidy then dropped their lines (33 -> 20, and 18 after the
brace rule below).  `src/network/net_grf.c` had two `/*!` notes (the unused helper that carries
the aggregate DIEs, and the `__builtin_next_arg` expression); both were blanked (58 -> 50).
`src/AM/s573/play/p_anime.c` (247 lines), `src/CS/lang.c` (20) and
`src/CS/dancemaster/dmm_chara.c` (69) were already comment-free, so the tool reported nothing
to do.  Compiled before and after under `3.0b38-030307 -c -lang c -O3 -opt full -g`: `sys_scf`
`.text` 0x40, `.debug` 0x28C, `.line` 0x74; `net_grf` 0xC0 / 0x638 / 0x9C -- `.text`
byte-identical, `.debug`/`.line` retail's after adoption.  The tool's tests are in
`tests/units/test_strip_comments.py`: line and block comments, strings/char literals, line-count
preservation, the header and `!` marker being blanked, the no-comment gate, the refusals, a
changed object part, and the real before/after compile (skipped when the retail ELF or the
recorded compiler is absent).

### Tidying a promoted source (part of promotion, after the strip)

`python3 tools/units/strip_comments.py --collapse <src>` is the layout step.  It differs from
the strip in exactly one way: it **deletes lines**, on purpose.

- **Runs of blank lines collapse to one**, anywhere -- between functions, between blocks and
  between statements inside a block -- and leading blank lines go; the file ends in one
  newline.
- **Trailing whitespace is removed from every line.**  A line that held only a blanked comment
  is therefore whitespace-only, becomes blank, and joins the run beside it.
- **No blank line directly inside a brace.**  A blank immediately after an opening `{` or
  immediately before a closing `}` is dropped, for functions and nested blocks alike; the same
  goes for `if (...) {`, `} else {` and a multi-line struct initialiser.  One blank line
  *between* statements inside a block stays.  For a promoted source those inner blanks can be
  line evidence (retail's statement position), so `--check` passes them; a file with no
  `tu_builds` row has no such evidence and the check fails while one is present.  The tidy
  itself drops them, which is why a unit whose layout deliberately keeps them is never
  `--collapse`d.
- **Comments are gone before the layout is considered.**  The tidy runs the strip first, so
  the leading header block and every `/*!`/`//!` note become blank lines and are dropped by
  the rules above -- there is no separate header rule and no surviving marker.  A promoted
  file starts with its first declaration or `#include`; its measurements live in the
  `tu_builds` row comment and the unit report, not in the source.

**What the line shift costs.**  Collapsing a blank line above a statement moves that
statement, so the emitted `.line` is no longer retail's -- which is fine, because every
promoted unit's `cc` edge runs `--adopt-retail-meta` and retail's `.line` chunk is what the
image carries.  The tidy is therefore applied after the strip, and the row comment records that
the layout is tidied and `.line` adopted; changing the compiler or the flags is never part
of it.

**The grouping check.**  The old `#line` layout encoded *which statements share a line*, and
adoption cannot recover a grouping the source has lost -- it only replaces the table.  So
before accepting, the tool compiles the committed and the tidied spelling of the unit through
the promotion path and requires each function's **emitted** `.line` record count to be equal.
The count comes from the per-function block sizes `_fill` reports, which are measured before
adoption replaces the table with retail's.  A record is 10 bytes, so the count is the block size divided by
ten; a difference means a rewrite joined or separated two statements and is refused by name and
by count (`f 7 -> 8`).  The same measure is how a `#line` layout was shown to be droppable: the
directive and reflowed spellings of `p_anime.c` both emit 244 records in 5 tables
(104 + 2 + 123 + 12 + 3), `dmm_chara.c` 33 in one, and the tidied sources keep those exact
counts.

**Acceptance.**  Stricter than the strip's, because `.line` is no longer ours: `.text` must be
byte-identical, and the resulting `.debug` and `.line` must be **retail's bytes** -- the
adoption step proves the chunk byte for byte and substitutes the line table, and the tool
re-checks both against `retail_bytes` before writing.  A unit with no recorded pair, a
non-unit without `--no-verify`, or a `#line`-carrying file is refused exactly as for the strip;
`--check` writes nothing and fails if the file still carries a comment or, for a file with no
`tu_builds` row, a blank line directly inside a brace (for a promoted source the blank is the
line, so it passes).

```bash
python3 tools/units/strip_comments.py --collapse src/sys/sys_scf.c          # tidy + verify + write
python3 tools/units/strip_comments.py --collapse --check src/sys/sys_scf.c  # fail unless clean
```

**Measured 2026-10-20, all five promoted units** under `3.0b38-030307 -c -lang c -O3 -opt full
-g`.  The comment strip (above) took `sys_scf.c` 33 -> 20 with its three notes, and the brace
rule took it 20 -> 18; `net_grf.c` 58 -> 50 with its two notes.  `p_anime.c` (247 lines),
`lang.c` (20) and `dmm_chara.c` (69) were already comment-free and tidy, so the tool reported
nothing to do.  Every unit's `.text` is byte-identical (0x40 / 0xC0 / 0x950 / 0x50 / 0x1D0),
`.debug` and `.line` are retail's after adoption (0x28C / 0x74, 0x638 / 0x9C, 0x4273 / 0x9B0,
0x43E / 0x4E, 0x64DA / 0x152), and the record counts are unchanged -- every row is adopted,
with the row comment saying the layout was tidied and `.line` adopted.  G1 is
`ef31c90f…c02cd`.  Tests: blank-run collapse, trailing whitespace, header removal, the
brace-edge blank, idempotence, the grouping refusal, a
moved `.text`, and the real before/after compile with per-function counts.

## House rules that keep the gates honest

- Gates are pins, not opinions: `config/ddrex2p/checksums.txt` holds both, and a gate that lacks its
  input **skips with an explicit "nothing was compared" line** — never a silent pass. Note that a
  skip and a pass share exit code 0; read the line.
- Never hand-edit generated files (`asm/**`, `include/**`, `config/ddrex2p/splat*.yaml`,
  `symbol_addrs.txt`, `unplaced_symbols.txt`, `objdiff.json`); regenerate with
  `./ddr --target ddrex2p oracle`. Hand-written names go in `borrowed_symbols.txt`.
- One record per VA inside the declared segments: splat's duplicate check fires at symbol load,
  *before* it splits, so a duplicated address stops the build outright.
- Commit with explicit paths and never `--amend`; parallel writers get their own `git worktree`
  (seed `orig/` and `toolchain/` by symlink, regenerate the generated trees per worktree).
- **Subagent worktrees live at `.git/agents/<name>`** — a `git worktree` inside the repository's
  own `.git`, never in the home directory.  `git worktree list` then finds every one of them, and
  the branch name and the directory travel together; a home-directory worktree is outside the
  repository's cleanup and disappears from the roster.  Merge back by cherry-picking into the main
  checkout, never by rewriting the worktree's history.  An agent leaves its worktree in place;
  after integrating a unit, run `python3 tools/units/worktree_prune.py` — it keeps the worktree
  until its source is merged, then archives its diff and removes it.
- No test may reach a build machine — `tests/conftest.py` fails any test whose argv names `ninja`,
  `splat` or `configure.py`, and a session backstop fails a run that changes the repository.
- Verify suite claims **at the commit** (`git archive <sha> | tar -x -C /tmp/…` and run there); this
  checkout is shared and has already produced one green build against uncommitted code.

## Register colouring rules (measured)

Controlled experiments under `3.0b38-030307 -c -lang c -O3 -opt full -g`, one factor at a time;
the probe sources and drivers are `drafts/regalloc/rules/` (`cc.py` compiles + disassembles one
file, `cmpfn.py <file> <fn>` prints the register substitution ours -> retail's split asm,
`climb.py` hill-climbs declaration order against it, `gen1..gen8.py` are the experiments below).
All callee-saved results read the register a value lives in from the instruction that uses it.

| # | finding | evidence |
|---|---|---|
| 1 | **Inert factors**: number of uses (0..4 inside the loop, 1..4 after a call, loop depth of the uses), where the last use is (after call 1/2/3), initialise-at-declaration vs later, type, statement order. For webs that are *the same kind* (declared variables live across the same calls) none of these moves a register. | `gen1`, `gen5`, `gen6`, `gen2` (init True/False identical) |
| 2 | **Declared webs are coloured in declaration order, first declared -> highest `sN`** (3 values: `s2,s1,s0` for any permutation of declaration order). | `gen2`, `gen6` (21 cells), `gen3` |
| 3 | **A compiler-made strength-reduced pointer whose base is a global, a constant or an address expression is coloured after every declared web**, so it takes the lowest register left (`s0` in 60/60 declaration permutations of `shop_bind_nm`), and a later loop's SR temp is coloured before that loop's re-split `i` (`ofs2=s2, i2=s0`). No declaration order can move it. | `gen1` (ptr=s0 in all 10 cells), `sb_perm2`, `sb_search` |
| 4 | **An SR pointer whose base is a declared, non-constant pointer `p` that dies at the loop is coloured as `p`** (it inherits `p`'s declaration slot). `p,w,i` declared in that order gives `ptr=s2, w=s1, i=s0` -- the exact retail shape of `shop_bind_nm`; `w,p,i` gives `ptr=s1`. So when retail's SR pointer outranks a declared value, look for a declared pointer (or struct base) the pointer is derived from, and put that declaration where the pointer's colour belongs. | `gen7` (6 permutations, all as stated) |
| 5 | **This does not survive constant propagation**: with `tbl = (unsigned int *)0xA7D350;` the SR pointer is initialised from the folded constant, not from `tbl`, and stays `s0` in all 720 declaration permutations (`sb_search2`). The explicit-pointer spelling (`ofs = *tbl++`) does colour `tbl` first (`ptr=s2,work=s1,i=s0`, retail's colours) but loses retail's loop shape: the preheader is emitted inline (`ori s2` in the delay slot of the entry `b`) and the unit is 4 words short, because the compiler-made pointer is what places `lui/ori` in the out-of-line preheader after the function body. So both halves of `shop_bind_nm` are reachable, never together by declarations alone. | `sb_explicit_ptr.c`, `sb_search2.py` |
| 6 | **A web used heavily in a *later* loop outranks earlier-loop webs regardless of declaration order** (w read in loop 2 -> `w=s2` for all six declaration orders; its competitors then follow rule 2 among themselves). A variable used in two loops is split into two webs and the second is coloured after the SR temps (rule 3). | `gen3` (`loop2`, `loop2b`), `gen4` |
| 7 | **Short scalar copies of struct fields do not follow rule 2.** In `CwsWin_ListbkDisp` the `wx/wy/ww/wh` and `loop_cut` declarations can be permuted freely (120 orders) without moving the `loop_cut`/`wy` pair (`s0`/`s1`), nor does moving `loop_cut = 0;` before or after the field loads. The set is retail's; only that pair is swapped. | `cmpfn.py` + permutation loop on `net_win_listbk.c` |
| 8 | At nine or more live values the n<=5 rule above generalises as the existing "register assignment is declaration order" row (first six reversed into `s5..s0`, 7th..9th `s6..s8`); retail's `ListbkDisp` set (`dr=s3 dg=s5 db=s7 da=fp dz=s6 objw=s4`) is not a monotone function of its DWARF declaration order, so at that size treat the DWARF order as evidence, not as the declaration order to write. | `CwsWin_ListbkDisp` DWARF vs ours |

**How to use them.** (a) Read retail's colouring off the DWARF (`dwarf1.py fn`) *and* the asm; a
value with no DIE is a compiler temp. (b) If retail has an SR pointer or CSE temp in a *high*
register, the C needs a declared value for the compiler to derive it from (rule 4) -- a constant
base will not do (rule 5). (c) If two declared values are swapped, permute their declarations
first (rule 2); if permuting the pair changes nothing (rule 7), the pair is not decided by
declaration order and the cause is the web structure (rule 6), not the spelling.
`cmpfn.py <file> <fn>` is the quickest way to tell: it reports the substitution table
(`{('s0','s1'): 7, ('s1','s0'): 10}` is a clean pairwise swap).

**Not fixed by these rules (parked, with what was learned):** `shop_bind_nm` (rule 5),
`CwsWin_ListbkDisp` (rule 7), `down_load_anime`, `back_anime_step`, `freeze_eff_disp`
(not examined: no probe applies yet).

### 9. A member access may belong to a POINTER, not to the struct

When one of our bodies puts an address in `$1`/`at` where retail reuses `$2`, suspect the base,
not the allocator. Retail's `lw $2,-0x4508($28); lw $2,0x4C($2)` is a **pointer deref**; a
static struct's member compiles to `lui at; lw $2,0x4C(at)`. Measured on
`network/net_play/net_play_main.c`: the DWARF declares `static struct _tag_cNetPlay _pNetPlay`
(0x5C at 0x71F020) *and* `_tag_cNetPlay *pNetPlay` (0x002DDBE8); gp is 0x2E20F0, so
`gp-0x4508` is exactly `pNetPlay`, and `_pNetPlay` is never referenced in the TU. Rewriting every
access through `pNetPlay` made eleven bodies register-exact at once and took the twelfth from
`+0x18` to `+0x4`. Probe: `static struct S *p` gives `lw v0,0(gp); jr ra; lw v0,76(v0)`, while
`static struct S obj` gives `lui at,0; jr ra; lw v0,76(at)`. So read `tools/oracle/dwarf1.py
globals ELF --grep <name>` before believing a header's struct-versus-pointer spelling, and check
which of the two addresses the gp-relative load actually reaches.

### 10. Free-list state, not kind: SR pointer versus declared counter

`drafts/regalloc/rules/tempord.py` (non-unrolling trip count; a constant 3 unrolls eight ways)
shows the SR pointer always takes the earlier temp register and the declared counter a later one —
in every expression shape and every lever — so **rule 3 is a callee-saved statement only**. It is
not a kind rule either: `ps2dancerLoadInit`'s loop 2 gives the pointer `v1`/counter `t1` while its
loop 3, four instructions later, gives the counter `t1`/pointer `t2`. The pair's order is per-loop
free-list state; adding or removing *any* value rotates the allocation by one register, so a
residue of this kind is reached by rotating, never by permuting declarations.

### 11. A loop bound's spelling decides the branch temp

`for (i = 0; i <= 0x1C; i++)` with the increment as its own statement emits
`slti $1,i,0x1D` + `bnez $1`; writing the same bound as `i < 0x1D` emits `slti $v1`
instead. Measured on `shop_bind_nm`: its loop 1 must stay `i < 0x4C` (because
`<= 0x4B` gives `slti $at`), while loop 2 needs `<= 0x1C`, and the `<=` form took the
body from nine differing words to a single swapped register pair; the `.line` rows
agree the increments are separate statements (lines 363/371). So when a residue is
`slti $1` against `slti $v1`, change the bound's spelling before touching the allocator.

### 12. A compare against a 32-bit immediate keeps its constant in a register — unless the bound is written `>`

`if (z >= 0xFF00)` compiles to `slt v0,v1,v0`, keeping the constant in an allocated
register; `if (z > 0xFEFF)` canonicalises to `slt at,v0,at`, with the constant in `at` —
retail's shape in `ComKeyBoardDisp` (probe: `drafts/com_keyboard/probe/p1.c`..`p4.c`, only
the `>` spelling matches). Same unit, same idea one type down:
`(int)g_sys_w.s_counter % 32 - 16` needs the `int` cast to get the signed-modulo fixup
(`bgez` / `addi -0x20`), because `s_counter` is `unsigned int`.

### 13. A debug-only shortfall that adoption cannot repair

Adoption can drop records our object emits and retail's does not; it can never add one.
`AM/s573/doll/vu0.c` is the case: its three bodies are handwritten VU0 macro-mode and are
byte-equal as `asm { }` blocks (108/108 words, `.set noreorder` inside the block so the
compiler's epilogue lands after it — `$Lab:` labels are rejected, plain `Lab:` works), but
retail's CU carries `formal_parameter` DIEs for parameters its code never reads (`m0` of
`a_make` and `rgb_make`), and MWCC 3.0b38 records such a DIE **only when the parameter
reaches emitted code** — 27 dead C spellings, five builds and eight flag sets all agree.
Naming the parameter inside the asm does emit the DIE, but it substitutes the parameter's
home register into an instruction retail encodes with a different one, so `.text` breaks.
The chunk is short by exactly the unused parameters' DIEs (18 records, 0x262 bytes). This is
a *compiler DWARF-emission* difference, not a C shape: record it and do not fabricate.

### 14. Designated initialisers are accepted; mixing forms is not

`.field = x` compiles under the pinned pair, **including on bitfields** (`unsigned a : 4`
may be named), so a struct table can be written sparsely — `src/music_all.c`'s
`.link_num = 0,` style — and omitted members still zero-fill. What b38 rejects is mixing
inside one brace: `{ .a = 1, 2, 3 }` is an "expression syntax error". Two traps that cost a
wrong conclusion once: `compile.py --syntax-only` mis-parses a trailing `-c -lang c …` flag
string and will report a *promoted* unit as broken (it "fails" `music_all.c`), so probe
through `drafts/regalloc/rules/cc.py` instead; and a rejected *mixed* initialiser is not
evidence that designation is unsupported.

### 15. A unit's generated prototypes are shorter than the real parameter lists

MWCC writes a `formal_parameter` DIE only for a parameter that reaches emitted code (the
`vu0.c` mechanism), so `include/src/…h` under-declares any signature with unused arguments —
and the *used* ones therefore sit in later registers than the prototype implies. Measured on
`AM/s573/doll/model2.c`: `drawLcore` really takes 8 arguments (`rp=a1`, `r=t0`, `g=t1`,
`b=t2`, `prmask=t3`) while the header shows 4, and `drawGT3`'s `cull`/`prmask` arrive on the
stack, so it has 8 register formals before them. Two consequences: a header include is
unusable for such a unit (the short prototype is "redeclared" against the definition), so it
declares its own types inline like `model1.c`; and the missing formals can be declared
freely, because unreached parameters emit no DIE and the `.debug` inventory still matches.

## Known blocker classes and three failure modes worth knowing

Measured while finishing two hard units in 28 minutes and 78 compile-and-compare cycles between them:
the cost was the unknowns, not the loop.

Three failure modes the table above does not cover:

- **A `.debug` block of the right length but the wrong bytes.** Every size message stays silent; only a
  byte comparison sees it, and `ninja`'s `g1` edge is what catches it. Do not conclude a unit is sound
  because the build printed no warning.
- **A `.line` record that a conditional expression cannot produce.** The original used a *branch*: two
  one-line `if`s reproduced retail's seven statement records exactly, where a `? :` — even split
  across lines — never produced records 119 and 122.
- **A `.line` chunk of the right length with a record at the wrong address.** The record *count* and every
  line *number* can match while one record's offset does not, and only the byte compare sees it — the same
  blindness as the `.debug` bullet above, one section over. Measured on `ps2dancerInitHide`: with the pad
  `nop` of the next-but-one entry restored, `.line` was retail's 0x58 bytes and all seven line numbers were
  retail's, but line 105's record pointed at the loop's `slt` (+0x54) where retail's points at the epilogue
  (+0x60). The fix is source re-lining, not code: the `do` statement's closing brace and `while` clause need
  their own `#line 104` marker, like every other statement in the reconstruction. So "short by 0xA" is a
  *size* reading only; a `.line` verdict has to be read as bytes.

Blocked classes, each with a mechanism rather than a label. A unit that fails this way is a **finding**,
not a puzzle: record it and take another unit.

| class | mechanism |
|---|---|
| **anonymous-type DIE order in a promoted unit** | a unit whose types `.debug` contains anonymous aggregates gets its per-object chunk compared byte-for-byte, and the compiler's `@anonN` index assignment cannot be reproduced by the header. Measured: the block has the right length and the same aggregates, structurally identical (tag, size, member names, offsets, kinds) to retail's, but the indices are permuted. The assignment follows the *declaration* order in controlled cases (six standalone aliases declared `a`..`f` get `@anon0`..`@anon5`; reversed, reversed), a container's *inline* anonymous members are emitted after it in member order, and aliases nested by value keep their own position -- but it also depends on the whole TU's content: the promoted `src/network/net_grf.c` declares `grf_coord` before `grf_element` and its object emits `grf_element` `@anon0` then `grf_coord` `@anon1` (retail's order), while the *same typedef block* alone compiles the other way round. Swapping two `#include` lines in a unit header permutes all 25 indices of `dmm_chara.c` without changing the block's length. Retail's own emitted order is not a declaration order: `dmm_chara.c`'s `@anon7` (`work`, 15740 B) has by-value member types on **both sides** of it (7 before, 10 after) with other containers' declarations (`play_mode`, `play_hist`, `g_game_w`, …) interleaved between the followers, and a named type cannot be declared inside a struct body -- so a container's by-value member type would have to be declared *after* its container, which no C declaration order expresses. Tell this class from wrong C by comparing the two chunks as a **set** of DIEs, not by position: same length, same DIE count, pairwise-identical structures and only the anonymous indices moved = this boundary; any difference in the set (type, member, size, statement or parameter DIE) = the C is wrong. `.text` and `.line` stay verifiable and `.debug` is not part of the linked image, but the promotion path refuses the chunk first (`does not fit the pinned chunk`), so the gate is stricter than the image: such a unit would link byte-identically while its per-object debug chunk differs. |
| **unreferenced array DIEs** | the types block is short of DIEs describing an array type *nothing in the CU references* (`unsigned char *[6]`, `unsigned char[256]`); fifteen constructs and all five compiler builds left the block unchanged, so no C shape produces them |
| **unreferenced aggregate DIEs** (solved once) | *which* construct emits a type's DIEs, and where: a file-scope **object** of the type emits them but leaves its own variable DIE behind (+0x23) and relocations no ledger places; an `extern` declaration emits neither; an unused **`static` function** whose body touches the type emits them and nothing else — but only for a *member* access through a pointer or a by-value parameter/return, never for a copy or `sizeof`. The emission **order** is fixed by where that function sits relative to the file-scope variable and the unit's functions: between the variable and the first function the block came out byte-equal to retail's, after the variable but past the functions the aggregate pair came out reversed, past both functions the array pair. Measured on 40 constructs in `network/net_grf.c` (`reports/net-grf-debug-report.md`) |
| **`mes_*` units** | `.global_variable` DIE ordering differs for large unreferenced file-scope tables, referenced statics come out reversed, and the residue is array-DIE order, which no declaration order controls |
| **VU0 units** (`.vutext`) | MWCC sinks the epilogue, so the last inline-asm statement takes the `jr` delay slot where retail fills it from the operation that follows |
| **shape conflicts** | a unit needing two mutually exclusive C shapes: the reconstruction that fixed `.line` scheduled six words differently and left `.text` short, so both could not be had. Record the conflict; never pick a winner and call it promoted |
| **unresolvable callees** | a call target the promotion path cannot relocate, failing at `cc` *before* any comparison. The ledger is now the **link's own symbol set**, not one file: the split globals under `asm/nonmatchings/<segment>` (bound to the address of the instruction after each label), the `-T` files' assignments where this layout holds their address, and `symbol_addrs.txt`. Two things survive that, and they must not be confused with a lookup gap: the **overlay boundary** — an address outside every declared segment, an overlay window this milestone does not model, deferred by design — and a name with **no record at all** in any of the three. `net_sys_connect` is the first (`NetRouterMain`, stored through `%hi(D_008062B0)` rather than called, undefined in the link); the split-only callees that blocked four candidates (`func_001C43E8` in `net_grf.c`, `func_001BED10` in `dexport.c`, `func_00128600`/`func_0012CD70` in `dmm_chara.c`) were never a class: `compile.py` was reading one ledger while the link resolved the split objects its ld script lists, and fixing that took **53 units out of the screen's blocked list** while the four overlay units stayed in it. |
| **128-bit GPR operations** | the unit's split carries an EE 128-bit GPR **operation** (`pxor`, `pand`, `paddw`, …), and MWCC PS2 has **no 128-bit operators**, so no C expression emits one. Measured with the retail compilers under wibo (`-c -lang c -O3 -g`, and `-lang c++`): `a ^ b`, `a & b`, `a \| b`, `a + b`, `a - b`, `a * b`, `~a`, `a ^= b` on `u_long128`/`unsigned __int128` are rejected by **all five installed builds** with `Error: illegal data size` — for parameters, locals, globals and pointer dereferences alike — and `u_long128 a;` without a typedef fails the same way. What 128-bit C *does* give is assignment (`lq`/`sq`) and constant materialisation (`lui`/`ori`/`dsll32`/`or`/`pcpyld`), which is exactly how retail builds `Cr`, `Cb` and `ex`. The only construct that produced a `pxor` was MWCC's inline-asm extension (`asm { pxor a, a, ex }`) — assembly, not C, so it is a probe rather than a promotion. Found on `eyetoy/eye_filter.c`, whose `negaposi` is `pxor $4,$4,$7`/`pxor $3,$3,$7` over `lq`/`sq` values, while its neighbour `sepia` in the same unit uses only the expressible subset. The screen flags it as `128-bit-gpr` and must **not** match `lq`/`sq`/`pcpyld` (`sepia` is the in-tree proof that legal C emits them) nor `pref` (a prefetch hint). |
| **out-of-segment fixed addresses** | the unit's split accesses a fixed absolute address above every declared segment, and the bytes say retail's operand was a *symbol*, not a constant: `lui $1,(0x1030000 >> 16)` + `lw $3,-0x601C($1)` is the assembler's `lw rt, sym` expansion (`$1` is `at`, one pair per access), where a C constant compiles to `lui`+`ori` in an allocated register — measured on `network/net_game/net_game_help.c`, whose `NetGameHelpDisp` is 155 of 172 words different and 4 bytes short for that reason alone, with `.debug`/`.line` DIEs *exact* and only their values differing. The address cannot be named: `borrowed_symbols.txt` validates every line against a split's bounds (functions only), an out-of-segment `unplaced_symbols.txt` record is refused rather than resolved to 0 (`compile.py`'s `Manifests`), and no record in any of the four ledgers is above `bss_end` except the overlay ones. Measured on this tree: 207 distinct addresses in the `0x01029FD0..0x0102FFCC` band plus `0x00A7D350`/`0x00F4D380` and the scratchpad `0x10002000`/`0x10010000`, from 218 splits over 38 units — 21 of the 57 candidates at `ce7a75b` leave the list on it. It is **not** a segment missing from `config/ddrex2p/`: the band has no ROM offset (0x01029FE4 → file 0xF2A1E4 past the file's 0x75DFEC bytes), no `PT_LOAD` window covers it (the ELF's memsz-only windows are 0x7F0000, 0x1884000, 0xE4D380 — the overlay slots the oracle already records), and the DWARF names nothing in `0x00A00000..0x01100000`, so nothing in this repository places it. The screen flags it as `absolute-addresses`; it does not match the `addu`-indexed spelling of the same band (3 splits), which is byte-identical to the assembler's large-displacement expansion over a register. |
| **a statement whose whole code is a pad `nop`** | retail's `.line` carries a record whose entire code is one `nop` *inside* a function's extent, and retail's `.text` is 4 bytes longer for it (`ps2dancerInitHide`: record 103 at +0x4C, 0x70 against 0x6C, every other instruction identical, `beqz` displacement 0x0D against 0x0C). Only **inline assembly** on that line inside the enclosing body produces the record *with* the bytes — `__asm__ ("nop");`, `asm ("nop");`, `__asm__ volatile ("nop");`, `asm { nop }` each give +0x4 and the one record. About thirty C candidates give neither: bare `;`, `{ }`, `{ ; }`, `i = i;`, `i += 0;`, `(void)i;`, `if (0) ;`, `else if (0) ;`, `continue;`, `if (i >= 0) ;`, `if (i) { }`, `if (i) { } else { }`, `else ;`, `else { l: ; }`, an empty `switch` case/default, `do { } while (0);`, `while (0) ;`, `for (;;) break;`, `i ? 0 : 0;`, `(void)(i, 0);`, `__asm__ ("");` (nothing at all), and `int k;` (rejected — the dialect is C89, a declaration cannot sit mid-block). A lone label, a `goto` to the label that follows, and a conditional branch to the next statement instead **delete** a record with no byte change, and **no construct yields the record without code**: a record's address always carries an instruction, which is exactly what `C is incomplete (cannot pad .line)` reports. Consequence: a unit whose retail build pads a statement is **not promotable from C** — the same boundary as the 128-bit `pxor`. Assembly is a probe, not a promotion, because the goal is readable C; but the route is *known*, not lost: on the `dexport.c` draft `__asm__ ("nop")` at line 103 plus the re-lining of the failure mode below reproduced retail's `.text` byte-for-byte (modulo two relocation sites) and `.line` record-for-record. Probes: `drafts/nopline/` on `wt-unit-n`; the full construct table is in `.superpowers/sdd/2026-10-15-m3-promotion-loop/reports/nop-line-report.md` |
| **a file-scope `static`'s DWARF tag** | all five installed builds tag a **file-scope `static`** as `.global_variable`, while retail's CU records the same object as `.local_variable`, in declaration order (`p_anime.c`: `anime_id_tbl`, `hold_release`, `pre_hold_flag`).  A *block-scope* static does come out `.local_variable`, but in the **function's** own CU inside a `lexical_block`, which is not where retail's file-scope objects sit.  Measured on a minimal TU (`static int s_one; static int s_two[4]; int g_one;`) at `-O3` and `-O3 -opt full`; no source shape moves it, so a unit blocked here is evidence for the compiler-revision hypothesis below rather than a C bug. |
| **a `+0x10` overrun from a `for` loop's entry guard** | a `for` loop emits an entry guard (`b <bottom>` in the preheader) that retail's loops in `p_anime.c` do not have.  Rewriting the loop as `do … while` removes the guard, but it also **changes the unit's size** — measured: it grew `play_anime_step_inst` by `0x28` — so the loop form is not the fix for a `+0x10` overrun; look elsewhere. |
| **hypothesis — a compiler revision outside the five installed** | **Not a finding.**  Two units failed to reproduce a decision across the five installed builds under two flag strings (`-O3` and `-O3 -opt full`) and a set of source variants: `p_anime.c` needs a file-scope static recorded `.local_variable`, and that **is source-movable**: a tentative definition is `global_variable` in every build, while an *initialised* one (`= { 0 }`) is `local_variable` in declaration order — measured again on `co_button.c`, `blowfish.c`, `bk_load.c` and `music_all.c`, so the tag follows the initialiser rather than a compiler revision; `com_scrollbar.c` needs a register-allocation permutation that no variant reproduces, while the callee-saved *set* is retail's (`u/scrbw`, `y1/x1/z0/y0`, `v/z1/w`) and only the *numbers* move — the same permutation in every build.  What is established is "no source form tried, under those two flag strings, reproduces the decision", not "the revision is unobtainable": MWCC's option space (allocation, scheduling, inlining, pooling, `lmw/stmw`, per-file pragmas) has not been swept.  **The test is a flag sweep on minimal discriminators**, which owns the final wording.  `.comment` cannot narrow it: four of the five write retail's `MW MIPS C Compiler (2.4.1.01)` string.  Whatever the sweep finds, tell this class from wrong C by the set comparison: `p_anime.c`'s DIE set differs only in the static's tag and the permuted `@anonN` indices (353 of 361 DIEs common), and `com_scrollbar.c`'s emitted instruction sequence and local-DIE order are retail's while only the register colouring moves. |
| **register-save line records** | a missing `.line` record is not always a pad. In `ps2dancerGetDollList` retail's extra record is `61@0x28`, and 0x1CF248 holds `sw s1,0x10(sp)` — a **register save in the prologue** — while the function's two real `nop`s (0x1CF2E4, 0x1CF34C) carry **no** record at all (retail's records run 74@0xB0 → 75@0xCC across +0xC4, and 82@0x130 follows +0x12C), i.e. ordinary unrecorded alignment padding. So that shortfall is a statement/line-attribution gap in the prologue: do not conflate the two classes and do not probe for a `nop` in it |
| **compiler boundary — callee-saved colouring** | the source is right and the compiler is the residue. Retail colours the nine values live across this unit's calls `u=s0, scrbw=s1, y1=s2, x1=s3, z0=s4, y0=s5, v=s6, z1=s7, w=s8`; the same source under **all five installed builds** colours them as a permutation of that set (the set is invariant, the numbers are not), and 190 compile-and-compare cycles over statement order, declaration placement, expression form, `-O` levels, `-opt` families and pragmas never produce retail's assignment. **Under the game's pair** (`3.0-011126 -c -lang c -O3 -opt full -g`; `3.0.1`/`3.0.3` agree) the same source is 0x18 short of `.text` (0x528 vs 0x540), 0x28 short of `.line` (0x30a vs 0x332 — 77 of 81 records, 33 of them at retail's exact (line, address)), `.debug` at the pinned 0x955 length but with its local-DIE order **retail's exact reverse** — and that order is unreachable by declaration order: the 3.0 family emits local DIEs **inner-block-first with each block reversed**, so declaring the blocks' locals reversed (both the then-block's and the else's, and again with the else's pair moved to function scope) only permutes the groups inside that fixed block order (`bar_y,bar_h | bar_y,bar_h,sa,dw_h | info,sp2` and `bar_y,bar_h,sa,dw_h | info,sp2,bar_h,bar_y`), Declaring **all four then-locals at function scope**, in retail's DIE order reversed, is the one form that gets the function-level group right: the group comes out `info, sp2, bar_y, bar_h, sa, dw_h` — retail's exact sequence — but the else pair must stay nested (retail's DWARF carries **two** `bar_y`/`bar_h` pairs, `[$a0]` and `[$a1]`, so the source had two scopes), and a nested group is emitted **first**, giving `bar_h, bar_y, info, sp2, bar_y, bar_h, sa, dw_h` (`.text` 0x528, `.line` 0x30a, 84.80% words, registers unchanged). So under the game's pair no legal declaration order reaches retail's order, while the same source under `3.0b38-030307` reproduces it exactly. **Verified at the byte level, not through a transformed copy**: this CU's `.debug` chunk (section offset 0x20abd9, 0x955 bytes) is **byte-identical** between `orig/SLUS_211.74` and the split databin (`build/assets/.debug_120.databin.bin`), and `net_grf`'s chunk 45 (1592 bytes) is identical too as the control — splat does not reorder DIEs, so the ordering observation is in the retail object itself. **This bounds the uniform-pair proof**: neither `sys_scf` nor `net_grf` carries block-scoped locals in its `.debug`, so their strict byte-equality proves the build and the flags but cannot discriminate the local-DIE emission order; `com_scrollbar` is the first unit that can, and on it the game's pair emits inner-group-first-reversed while retail's object carries outer-first-forward. An **inverted guard** (`if (!(scrbw->flag & 1)) { <else body> } else { <then body> }`, the statements re-numbered with `#line` so their values stay retail's) does not fix the order: the DIE sequence becomes `dw_h, sa, bar_h, bar_y, bar_h, bar_y, info, sp2` — the function-level group is still emitted last — while `.text` drops to 0x520, `.line` to 0x22e and word equality to 31.16%, because the bodies swap places in the instruction stream and the line records are address-ordered. So the order is a property of the block emission, not of the guard's polarity; the build stays `3.0-011126` and what differs for this unit is **our source's block structure** — the function-level declarations must precede the code, which is exactly why their group comes out last. never retail's outer-first forward order; the nine registers stay `u→temp, …` in both (84.75% / 84.80%, 0x528 both), and **84.84%** word equality, the nine coloured `u→temp, v=s8, w=s1, h=s0, x1=s2, y1=s3, z0=s6, z1=s4, y0=s7` (plain `-O3` gives 84.80% with `w/z0/y0` at `s7/s1/s6`). The closest cell, `3.0b38-030307` at the same flags — **not** the game's build — reaches all three pinned sizes and 81 of 81 `.line` records, 78 of them byte-identical (94.55%) but still permutes the numbering; there the residue is one knob: `#pragma opt_propagation off` reproduces the assignment **exactly** and costs 0x18 bytes, because the propagation pass is both what CSEs the three bar blocks and what proves `sa == 0` in the else path, after which the allocator coalesces `bar_h`/`dw_h`. Pragmas are function-granular, ignored inside a nested block, and illegal between `}` and `else`, so the two knobs cannot be split. Re-run under the game's pair: propagation off costs 0x04 (0x544) with all four `subu`s surviving (both of the then-block's, and the else-path clamp) but the bar blocks lose their CSEs (spans +4/+3/−1/−2/−2/−1/−3/+3) and the numbering still differs (`u→temp`, …); the five subtrahend spellings (`bar_h - sa`, `bar_h + -sa`, `-sa + bar_h`, and both paths with each) and the declaration-order variants leave 0x528 and that assignment untouched. Measured on `common/com_scrollbar.c`; the full argument is in its unit report. **The declaration-order rule below cannot reach it**: the nine coloured values are **not declarations** — eight are MWCC's address temporaries for `sp2`'s members and one is the parameter — so no source-visible order selects them (the rule itself is **register assignment is declaration order, not statement order**). Read backwards, retail's assignment implies the order `y0, z0, x1, y1, scrbw, u, v, z1, w`, and none of the three source-visible orders is that one: members `x0, y0, x1, y1, z0, z1, w, h, u, v`, definitions `flg, u, v, w, h, x0, y0, z0, x1, y1, z1`, materialisation `u, v, w, y0, z0, x1, y1, z1`. Direct test — reversed then-block declarations plus block A's uses reordered `y0, z0, x1, y1` — leaves the assignment unchanged in **both** cells: `u=s3, v=s4, w=s8, x1=s0, y1=s6, z0=s1, z1=s7, y0=s2` with the sizes still `0x540`/`0x955`/`0x332` (94.55%) under `3.0b38-030307 -O3 -opt full`, and `u→temp, v=s8, w=s1, h=s0, x1=s2, y1=s3, z0=s6, z1=s4, y0=s7` with 0x528/0x30a (84.84%) under the game's pair. The rule's regime does **not** explain it: call-straddling locals were measured separately and obey the **same** declaration-order rule at n=9 (twelve random declaration-order × side-of-the-call pairs, plus every side partition at canonical order; the `s4↔s0` swap is reachable for every partition tried — see `drafts/regalloc/stagger.py`). The exclusion is that these nine are **not declarations**: eight are address temporaries and one is a parameter, so no declaration order selects them. |
| **register assignment is declaration order, not statement order** | Measured with `drafts/regalloc/probe.py` under `3.0b38-030307 -c -lang c -O3 -opt full -g`, on N=2..9 locals that all cross a call and are each identifiable by their constant: the register is fixed by **declaration order alone** — the K-th declared value gets `s(n-K)` for n≤5, the first six reversed into `s5..s0` and the 7th/8th/9th `s6/s7/s8` in declaration order for n≥7 (n=6 is a boundary: the sixth takes `s5`). Statement order, initialisation at declaration vs later, first-use order, call position and the local's type are **inert** (all measured). Any target is reachable on that shape: the `s4↔s0` swap of a 9-value set and a fully arbitrary 9-permutation were each realised by one declaration order (`(0,5,2,3,4,1,6,7,8)` for the swap), and the `a`-class scan counter's `a1↔a2` too. Retail's local DIEs are emitted in declaration order and carry `DW_OP_regN`, so `.debug` and `.text` are one decision seen twice and retail's DWARF reads out the order to use. **The limit is liveness subsets, not staggered definitions.** Declaration order alone decides in every side partition: nine locals with two calls, each given one live definition on either side and read on the far side, gave the same `A = reverse(D[:6]) + D[6:]` for all eight partitions tried (`S = ∅`, `{0}`, `{0,1}`, `{0..4}`, `{0,2,4,6,8}`, `{4}`, `{4,5,6}`, all nine), for twelve random (declaration order × partition) pairs, and with the within-side definition orders reversed; the `s4↔s0` swap was reached by `D=(0,5,2,3,4,1,6,7,8)` in every partition compiled. The only deviation is the n=5 small-set rotation `A = reverse(D[:r]) + reverse(D[r:])`, `r = p` if `p < \|S\|` else `p-1`, where `p` is the longest declared prefix defined before the first call (120/120 verified). What the rule does **not** cover is a **value set whose liveness membership changes across regions** — values that come and go between calls rather than a fixed set all live across them: retail's `play_anime_step` does not satisfy the formula for its DIE order (`counter` takes `s7` although third declared among the saved ones), and it is not in the staggered regime. Report: `.superpowers/sdd/2026-10-15-m3-promotion-loop/reports/regalloc-report.md`. |

### The two compiler boundaries, and why only one is promotable

Two classes now end at the compiler rather than at the C, and they are **not** equivalent:

* **anonymous-DIE ordering** changes only `.debug`, which is never linked. A unit in that class is
  **promotable under the set-equal gate with the deviation recorded** — the rebuilt image is still
  byte-identical.
* **callee-saved colouring** changes `.text`, because register numbers are encoded in the instructions,
  so no recorded-deviation policy can accept it: the rebuilt image would differ. Such a unit **stays
  unpromoted no matter how correct its source**, and that is the honest outcome.

The mechanism sentence for the second, which is what a future reader needs: **retail has propagation-on
code with propagation-off colouring** — the CSEs that give the pinned instruction count and the free-list
order that gives the pinned register numbers come from the same pass in every build we have. What would
close it is therefore not a C shape but a compiler that lets the propagation pass and the allocator's
first-fit/free-list decision be configured separately: a build we do not have, or a pragma granularity
the compiler does not offer. The alternatives are ruled out by measurement, not assumption — five
subtrahend spellings (`bar_h - sa`, `bar_h + -sa`, `-sa + bar_h`, and both paths with each) leave the
permutation untouched; the DWARF records **two distinct `bar_h` DIEs** (`[$a0]` then-branch, `[$a1]`
else-branch), so `bar_h` cannot be extended across the else path to break the coalescing; and the `.line`
pin fixes every statement in the then-block, so the liveness cannot be moved either.

**Caveat — the two things that move type `.debug` bytes, in the order they matter.** First, and this is what actually blocks units: a generated header that *names* an anonymous aggregate puts that name into the DIE, where retail's build has MWCC's `@anonN`, so the type block is long by exactly the invented names' worth. Fixed in the generator: an unnamed aggregate is emitted as `typedef struct { … } alias;`, because DWARF 1 has no typedef DIE and the alias keeps the compiler's own name. Measured: `dmm_chara.c` 0x67A0 → **0x6389, retail's pin exactly**, and `dexport.c` 0x6CFE → **0x692C**, the same defect and not the path length. Second, a smaller effect, now only worth knowing: for a unit that `#include`s a header, the type `.debug` bytes also shift with the *length* of the include path's spelling, while `.text` is identical (same-length spellings match, +2 characters differ; the `-I` itself is byte-neutral on a unit that does not include). The spelling the retail build used is recorded in the split's own DWARF (`DW_AT_comp_dir` and the included-file paths), so derive it from there rather than from whatever path the repository happens to have — but do not chase this before checking the naming defect above, which is 0x3D2 of the 0x3D2 seen on `dexport`.

**What the loop lacks:** a way to ask *which C construct* emits a given missing DIE. That is manual
probing today and it is where most of a hard unit's cycles go. Everything else the loop needs exists.

## Worker lessons: parallel unit runs (read before starting a unit)

Measured over the parallel batches that promoted `dexport`, `md5`, `com_scrollbar`,
`net_auth_errmes_e`, `net_win_base`, `shop_main`, `net_win_user`, `net_dnas_mes_e`, `ed_ssq_func`
and `ed_edit_disp`.  Each item cost somebody an hour once.

**Acceptance**

1. **The only proof is `./ddr build` exiting 0 and writing a fresh `out/SLUS_211.74`, then
   `./ddr verify`.**  `./ddr verify` prints `G1 ok` against a stale `out/` after a failed build,
   and `./ddr verify --tu <unit>` can say all three parts ok while the full build fails (it
   compiles the unit alone).  Quote the build's exit code in your report.
2. **Rebase onto current `master` before the final check and re-run it.**  Other units land
   placements and `tu_builds` rows while you work; a green result on an old base is not green.
3. **`config/ddrex2p/data_placements.txt` and `tu_builds` in `config/targets.py` are append
   hotspots.**  On a conflict keep both sides, then `grep -n '^<<<<<<<\|^=======$\|^>>>>>>>'`
   both files and confirm there are no markers.  On macOS write `sed -i ''`, not `sed -i`.
4. **Report byte differences per function, never sizes.**  A function can be the right size and
   mostly wrong; relocation words (`jal`, `lui`/`addiu` of symbols) differ in an unlinked object
   and are not real differences.
5. **Park honestly.**  If a unit does not match after about 45 minutes, commit the draft under
   `drafts/` (not `src/`, no `tu_builds` row, so the tree still builds) and report which
   function, which words, and what you tried.

**Compiler and layout**

6. **Functions go in retail address order.**  The compiler emits in source order; writing them
   top-down by name usually reverses the unit.
7. **Declaration order is register assignment.**  When two callee-saved registers are swapped,
   permute declarations before changing logic; a block-local scratch variable (`mx = a + b;
   dx = mx + c;`) fixes swapped `addu` operands, and adoption drops the extra local DIE.
   A *new global* DIE is not dropped (see 13).
8. **Constant and compare shapes matter:** `x > 0xFEFF` against `x >= 0xFF00` changes which
   register holds the constant; `(a != 0)` forces a materialised flag; a sign-extend from a
   byte is `(int)((unsigned int)x << 24) >> 24`; a ternary clamp (`sa = sa > 0 ? sa : 0`) can
   fix a whole callee-saved numbering.
9. **`-sdatathreshold`:** try the default, `0` and `4` before settling on a row.  A literal
   or global under the threshold goes to `.sdata` and is addressed `$gp`-relative, which
   changes both the instructions and the register choice.  The recorded pair is half of the
   measurement.
10. **Static inline helpers** (`Decode`/`Encode`, a table `find`) leave no DIE of their own, so
    they are free tools for reproducing an inline retail had.
11. **A DIE retail has and the code does not need** (an unused `@anon0` type) can be emitted by
    a trailing `static void probe(T *p) { p->m = 1; }`; adoption drops the probe's own DIE.

**Data and names**

12. **Compiler-numbered literal names (`@134`) are per object, not global.**  Two units can
    both own an `@1`.  Put a unit's own addresses in `config/ddrex2p/unit_symbols.txt`
    (`@N = 0xADDR; // source:FILE`, also for a file-scope static whose bare name another unit
    owns, e.g. `step0`).  An 8-byte-or-shorter literal shared with other code may need padding
    (`"(%+d)\0\0\0"`) so it leaves `.sdata`; strings are not linked, so the padding changes no
    image byte.
13. **Never reference data by a hard-coded address.**  A name comes from the debug info; with
    no debug symbol, use splat's address-derived `D_<8 hex digits>` (they are in
    `config/ddrex2p/undefined_syms_auto.txt`), the same way unnamed functions keep
    `func_XXXXXXXX` (AGENTS.md rule 3).  Do not write `*(unsigned int *)0x006B2F58`.  A
    function pointer by address becomes the function's name.  (The mechanism that makes this
    build for a symbol with no DWARF is being added; until it lands, list any raw address you
    could not convert in your report instead of inventing a name.)
14. **A `.debug` reference to a global DIE retail does not have** fails adoption
    ("points at a DIE dropped as an extra record").  Prefer inline string literals over
    declaring an extern for them.

**Workspace**

15. **Work only in your own worktree** (`.git/agents/<name>` on branch `wt-<name>`, with
    `orig` and `toolchain` symlinked to the main checkout).  The controller cherry-picks
    commits onto `master` one at a time and rebuilds after each; do not touch the main checkout.

16. **Disk: every worktree carries a full `build/` + `out/` (about 90 MB to 180 MB each, 50+ worktrees
    is ~10 GB) and a full disk makes every shell command fail with ENOSPC.**  When you finish or
    park a unit, commit first, then `rm -rf build out .ninja_log .ninja_deps` in your worktree
    (they regenerate with `./ddr build`).  Never delete a worktree or its branch: parked drafts
    live on the branch.  Keep scratch scripts in your scratchpad or `drafts/`, not in a shared
    `/tmp` name another worker may overwrite.
