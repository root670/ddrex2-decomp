#!/usr/bin/env python3
"""C-mode headers: one per translation unit, and the named types they share.

Two things are being fixed here, and they are the same bug seen twice.  The headers
`dwarf1.py`'s own `header --cu` renders are *C++*: a use is spelled with a bare tag
(`_tag_SYS_SCF_WORK *pscf;`), which C cannot read, for two reasons worth remembering --

* Metrowerks labels every compile unit `LANG_CPLUSPLUS` even when the source is a `.c`
  file, and
* DWARF 1 resolves typedefs away (there are no typedef DIEs to render), so a type has no
  name but the tag the compiler happened to give it.

-- and the definitions are *duplicated*: DWARF 1 gives each unit a declaration unit holding
that unit's types, so `_tag_cFilepackData` arrives 17 times and `oni_mode` 15.

So a use is `struct <tag> *` / `union <tag> *` / `enum <tag>`, every *named* type is defined
once under `include/types/<tag>.h` (aggregated by `include/types.h`, with its offsets, the
DIE each definition came from, the units that declare it and a digest of its layout), and a
unit's own header includes the ones it uses and keeps its globals, its prototypes and their
retail address and line ranges.

Anonymous types are the measured exception, and the reason the tags are shaped the way they
are.  DWARF names them `@anon0..24`; that numbering is *per unit*, so `@anon0` in `les.c` and
`@anon0` in `onimode.c` are different types wearing one synthetic name (25 names, 21 of them
with more than one layout).  `@` is not a legal C identifier either.  So an anonymous type
keeps its own unit: a use becomes `anon_<N>_<unit>`, and the definition is emitted in that
unit's header and nowhere else -- as a **typedef of an unnamed aggregate**, because that is
the only spelling the compiler records as `@anonN`: `struct anon_0_109 { ... };` would put the
invented tag in the DIE, while `typedef struct { ... } anon_0_109;` leaves the aggregate
unnamed (DWARF 1 has no typedef DIE, so the alias never reaches the debug information).

A *named* type whose members hold an anonymous layout cannot spell that member out inline, and
cannot name one unit's tag either: the same layout is reachable from a named type's shared
header *and* from the unit's own anonymous types, and two declarations of it are two DIEs
where retail's block has one.  Measured on `shop_info.c`: retail's CU carries one `@anon0`
(`short x, y, w, h`, 8 bytes) referenced by both `_CWS_WIN_W.def` and `anon_1_129.shop_rect`,
and the inline spelling plus the unit's own typedef emitted two -- 181 DIEs / 0x18C7 bytes
against retail's 176 / 0x1805.  So the **layout is the key**: every anonymous aggregate
reachable from a named type's canonical definition is registered under the digest of its
structural signature, `types/anon_<digest>.h` defines it once as a typedef of an unnamed
aggregate, and both the named type's member and any unit's own anonymous type of that layout
name the alias.  The digest is the structural proof that the two declarations are the same
type (size, kind, member names, offsets, bit fields, member types), and the alias never
reaches the DWARF, so the compiler still records `@anonN`.

`include/**` is committed and generated: `./ddr oracle` regenerates it, and
`tests/oracle/test_emit_headers.py` checks every header compiles as C under the *original*
compiler (`tools/toolchain/compile.py --syntax-only`, which is `mwccps2 -lang c`).

No promoted unit includes one of these yet.  A unit that does gets different debug bytes: its
own declarations are what put its statements on the lines retail has them on, so replacing
them with an `#include` moves the unit's `.line` table (and, with it, `.debug`).  Reproducing
retail's own include graph is a generator problem, and a promoted unit keeps its hand-written
declarations until that is solved.
"""
import collections, hashlib, pathlib, re, sys, weakref

import dwarf1
import emit_cus
from demangle import cdecl as declare
from dwarf1 import (AGGREGATES, AT_bit_offset, AT_bit_size, AT_byte_size, AT_high_pc,
                    AT_low_pc, AT_name, Die, TAG_enumeration_type, TAG_global_variable,
                    TAG_inheritance, TAG_local_variable, TAG_member, TAG_subroutine,
                    TAG_unspecified_parameters, VOID, basename, innermost, loc_str,
                    member_offset)

#: The shared tree, under the output root: one file per named type.
TYPES_DIR = "types"
#: The file that includes every named type.
INDEX = "types.h"
#: The generated tree's own note about itself.
README_NAME = "README.md"

#: Fundamental types whose DWARF name is not a C spelling this compiler takes.
#:
#: `0xa510` is the EE's 128-bit integer.  The vendored reader's `FT` table calls it
#: `u_long128`, which is the *SDK typedef's* name (`eetypes.h`) and not something
#: `mwccps2 -lang c` knows: it rejects the name until that header is included.  The keyword
#: it does take is `__int128`, and the vendor's `u_` says which sign.  Measured: this and the
#: plain C names are the only fundamental types the image the oracle reads uses; a `bool`,
#: `label` or
#: `complex` would fail the C gate loudly rather than silently, which is where it would get
#: its mapping.
FUNDAMENTAL = {0xa510: "unsigned __int128"}

CACHE = {}

#: `dwarf()`'s path -> repo root, for prose that names the ELF it was generated from.
REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]

#: `{Dwarf: {TU: [anonymous DIE, ...]}}`: the per-ELF anonymous-type index (see `unit_types`).
_OWNED = weakref.WeakKeyDictionary()


class NoSuchUnit(LookupError):
    """No translation unit (or included source file) matches the string."""


class LayoutDisagreement(Exception):
    """Two translation units declare one named type differently.

    The definition is picked once and shared, so a disagreement is not something to settle
    by preference: it means the name does not identify one type, and picking either layout
    would silently decide which one a unit compiles against.
    """


class NotSpellable(Exception):
    """The evidence names something C cannot spell, and the loss would be silent.

    A base class, a `Class::member` name, an anonymous type only another unit can define: C
    has no syntax for these, so the emitter stops rather than emitting a header that means
    something the DWARF did not say.
    """


def dwarf(elf_path):
    """The parsed ELF, cached: the CLI renders 156 headers from one parse."""
    key = str(elf_path)
    if key not in CACHE:
        CACHE[key] = dwarf1.Dwarf(key)
    return CACHE[key]


def header_for(relpath):
    """`src/sys/sys_scf.c` -> `src/sys/sys_scf.h`."""
    return re.sub(r"\.[^./]+$", "", relpath) + ".h"


def anonymous(die):
    """DWARF's name for a type it has no name for: absent, or `@anonN`."""
    return not die.name or die.name.startswith("@")


def _display(path):
    """A path as a reader types it: repo-relative when it is inside the repo."""
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def unit_types(dw):
    """`{TU: [anonymous DIE, ...]}` -- every unit's anonymous types, from one scan.

    A unit's own anonymous aggregates are what its header defines, and asking `.debug` for
    them once per unit is `O(units x DIEs)`: 57 units over 16,125 DIEs is 919,125 entries
    today, and the retarget has 249 units.  The index is built once per parsed ELF, in
    `.debug` order, which is the order the dependency walk and the emitted definitions use.
    """
    index = _OWNED.get(dw)
    if index is None:
        index = collections.defaultdict(list)
        for die in sorted(dw.dies.values(), key=lambda d: d.off):
            if die.tag in AGGREGATES and anonymous(die) and die.cu is not None:
                owner = dw.tu_of.get(die.cu.off)
                if owner is not None:
                    index[owner].append(die)
        _OWNED[dw] = index
    return index


def _kind(dw, die):
    """The C keyword a definition of this aggregate needs."""
    if die.tag == TAG_enumeration_type:
        return "enum"
    return "union" if dw.is_union(die) else "struct"


def _where(die):
    """`DIE 0x7e6ab` -- the exact record a definition came from."""
    return f"DIE 0x{die.off:x}"


def _declared_by(die):
    """`dcamera.c (DIE 0x7e6ab)`: the source file the record sits in, and the record."""
    return f"{basename(die.cu.name) if die.cu else '?'} ({_where(die)})"


def _guard(*parts):
    """An include guard's name: one per header, legal C, and stable for a given tag."""
    return re.sub(r"[^A-Za-z0-9_]+", "_", "_".join(parts))


# ---------------------------------------------------------------------------
# rendering a type, in C
# ---------------------------------------------------------------------------


def _c_tree(dw, tree, tagger):
    """`tree` with every aggregate leaf spelled the way C needs one spelled.

    The vendored reader's `cdecl` renders a type tree verbatim, which for an aggregate is
    C++ (`t[1]` is the bare tag).  `tagger` decides what C should say instead: `struct
    <tag>` for a named type, the unit's own `anon_<N>_<unit>` for one of its anonymous ones,
    or a constant when the spelling is a signature rather than code.
    """
    kind = tree[0]
    if kind == "base":
        ref = tree[2] if len(tree) > 2 else None
        if isinstance(ref, Die) and ref.tag in AGGREGATES:
            return ("base", tagger(ref), ref)
        if isinstance(ref, int) and ref in FUNDAMENTAL:
            return ("base", FUNDAMENTAL[ref], ref)
        return tree
    if kind in ("ptr", "ref"):
        return (kind, _c_tree(dw, tree[1], tagger))
    if kind in ("cv", "array", "memptr"):
        return (kind, tree[1], _c_tree(dw, tree[2], tagger))
    if kind == "func":
        return ("func", None if tree[1] is None else _c_tree(dw, tree[1], tagger),
                [_c_tree(dw, p, tagger) for p in tree[2]], tree[3])
    return tree


def decl(dw, tree, inner, tagger):
    """`struct <tag> *p` -- a C declaration of `inner`, with `tagger` naming the aggregates."""
    return declare(_c_tree(dw, tree, tagger), inner)


def _gap(indent, start, end):
    """Bytes no member covers that C's own alignment explains, as a comment.

    Only reached once `definition` has established the gap is explained -- by the next
    member's own alignment or by the alignment an emitted `__attribute__((aligned(N)))`
    states -- because a gap the evidence does not explain is spelled as a member
    (`_omitted_member`), never left as a comment that cannot move anything.  The number and
    the wording are the vendored renderer's, so a reader comparing a generated header with
    `dwarf1.py type` sees the same line.  There is no vtable-pointer case: these are C
    translation units, and none of them has one.
    """
    return f"{indent}/* 0x{start:03x} */ // 0x{end - start:x} bytes padding"


#: The alignments a definition may state, in the order the emitter tries them.
#:
#: 16 comes first because the tree already spells it and retail's DWARF cannot tell it from a
#: narrower claim: `fp_style.c`'s `anon_5_73` (DIE 0x1254e3, members end 0x1c, size 0x20,
#: natural 4) is reproduced by 8 and 16 alike, and the promoted units were measured with 16.
#: 32 and 64 are what retail's wider aggregates need: `_NETWORK_W`'s members end at 0x76DC
#: and its `AT_byte_size` is 0x7700, which only 64 reaches; `_mio_message` jumps 0x24..0x40
#: and ends 0x45A..0x480; `_ddrnet` 0x36D8..0x3700 and 0x2B599..0x2B5C0; `_tag_cNetCnf`
#: 0x50..0x80 and 0xE04..0xE40.  Every one of those four is a multiple of 0x40 bytes long.
#: 8 is the last resort -- a gap no 16-byte alignment reaches -- because the narrower claim is
#: all the evidence supports.
ALIGNMENTS = (16, 32, 64, 8)


def _rounded(start, natural):
    """`start` rounded up to a multiple of `natural`."""
    return (start + natural - 1) // natural * natural


def _stated_alignment(start, offset, natural, size):
    """The alignment a member has to state to sit where retail put it, or `None`.

    DWARF records a member's offset, not its alignment, so a gap is ambiguous: it is either
    padding for an aligned member or a member DWARF omits.  Measured on `fp_qmenu.c`:
    `float cam_p[4]` declares alignment 4, but retail puts it at 0x60 after `float timer`
    ends at 0x54, and the type is 0x90 bytes -- a multiple of 16 whose tail rounds 0x88 up to
    0x90 exactly the same way.  The offset and the size together therefore state an
    alignment the declaration does not, and the spelling that carries it is
    `__attribute__((aligned(N)))`.

    N is searched over :data:`ALIGNMENTS` because 16 is not the widest alignment the pinned
    compiler honours or retail's image uses: `_NETWORK_W` (DIE 0x77470) records `byte_size`
    0x7700 with its last member ending at 0x76DC, and only 64 rounds one onto the other.
    Only a candidate that reproduces the recorded offset is returned, and only when the
    aggregate's own size is a multiple of it, so the attribute cannot move a later member or
    change the recorded size; otherwise the gap is still unexplained and `_omitted_member`
    spells it rather than the header claiming an alignment the evidence does not support.
    `_tail_alignment` below asks the same question about the bytes after the last member.
    """
    if offset <= start or _rounded(start, natural) == offset:
        return None
    for align in ALIGNMENTS:
        if _rounded(start, align) == offset and size % align == 0:
            return align
    return None


def _padded_by_alignment(start, end, natural):
    """Whether C's own padding from `start` reaches exactly `end`.

    The *next* member gives a gap its alignment: if rounding `start` up to that member's
    natural alignment lands on its recorded offset, the compiler places it there unaided and
    the gap is padding.  When it does not -- and no stated alignment covers it either -- the
    bytes have to be spelled, because a comment cannot move the member after them (see
    `_omitted_member`).
    """
    return natural > 0 and _rounded(start, natural) == end


def _omitted_member(indent, start, end):
    """A member covering bytes neither the members nor any stated alignment explain.

    The fallback of `_stated_alignment` and `_tail_alignment`: when no alignment reproduces
    the gap, DWARF's own facts -- the following member's offset, or the aggregate's
    `byte_size` -- still say the bytes are there, and a comment cannot move a member nor grow
    a type.  So the bytes are spelled as a member of their own.  The pinned image has no
    such gap left (every one is rounding to 8, 16, 32 or 64), so this is the safety net: a
    gap the evidence does not explain is stated, never silently dropped.

    The name is synthetic, because DWARF has none: `pad_<offset>` is unique within its
    aggregate and cannot name a retail member.  `unsigned char` is the element type that
    cannot round the following member up -- the gap ends on the offset retail recorded -- and,
    being an array, the member states the byte count the DIE's `byte_size` implies.  The
    member itself is not in the DIE, so a promoted unit's `.debug` carries one extra record
    where retail has none; adoption drops it, as it does for `net_sys_logout.c`'s hand-written
    `unsigned char tail[0x24]`.
    """
    n = end - start
    text = f"unsigned char pad_{start:x}[0x{n:x}];"
    return (f"{indent}/* 0x{start:03x} */ {text}".ljust(len(indent) + 48)
            + f"  // 0x{n:x} bytes no alignment or member explains")


#: The alignments an aggregate's tail can state, smallest first.  Eight is where a type of
#: 4-byte members first gains a padded tail (`fp_style.c`'s `anon_5_73`: 0x1c -> 0x20), 16 is
#: the SDK's vector alignment, and 64 is measured on `_NETWORK_W` (members end 0x76dc, size
#: 0x7700, and only 64 rounds one to the other).  Nothing in this image needs more.
TAIL_ALIGNMENTS = (8, 16, 32, 64)


def _tail_alignment(cursor, size, natural):
    """The alignment an aggregate's own size states beyond its members, or `None`.

    The member rule above reads a gap *between* members; this reads the gap *after* the last
    one.  DWARF records the aggregate's size, so a size that rounds the cursor up states an
    alignment the members do not: measured on `fp_style.c`, DIE 0x1254e3 (`@anon5`,
    `anon_5_73` in `include/src/CS/freeplay/fp_style.h`) ends its members at 0x1c, DWARF says
    0x20, and retail's item stride is 0x20 (`addiu $3,$3,0x20`) -- an unstated tail makes the
    emitted typedef 0x1c bytes, so `((anon_5_73 *)w)[i].step` strides 0x1c and every body that
    indexes it misses.  `natural` is the alignment the members already give the type: when
    rounding the cursor up by *that* lands on the size, the members explain the tail and there
    is nothing to state.

    The spelling is the one 3.0b38 honours, measured: the attribute goes **immediately after
    the closing brace**, before the typedef's name (`} __attribute__((aligned(16))) tag;`), and
    the same attribute after the name (`typedef struct {...} tag __attribute__((aligned(16)));`)
    is silently ignored -- `p[1].step` stayed at 0x34 and `sizeof` at 0x1c.  A named type gets
    the identical placement, `struct tag {...} __attribute__((aligned(16)));` (measured: stride
    0x38, `sizeof` 0x20); 64 is measured the same way on `_NETWORK_W` (members end 0x76DC,
    `sizeof` 0x7700 with the attribute, 0x76DC without).

    The alignment is not always 16, so the search takes the *smallest* of `TAIL_ALIGNMENTS`
    that rounds the cursor up to exactly the recorded size.  A smaller claim is the one DWARF
    supports, and a use that needs more states it on the member the offset demands
    (`_stated_alignment`).  When no alignment reproduces the size, the tail is not alignment
    padding at all: `None` leaves the caller to spell the bytes (`_omitted_member`) instead of
    inventing the next power of two.
    """
    if size <= cursor:
        return None
    up = lambda n: (cursor + n - 1) // n * n
    if up(natural) == size:
        return None                     # the members' own alignment explains the size
    for align in TAIL_ALIGNMENTS:
        if align > natural and up(align) == size:
            return align
    return None




def _enum_lines(die, tag, indent, typedef=False):
    """`enum <tag> { A = 1, ... };` from CodeWarrior's own item blob.

    The vendored reader renders enums out of `0x00f3`/`0x00f4`, the vendor's attribute
    holding the items as an integer of `byte_size` bytes followed by a NUL-terminated name.

    `typedef` spells an enumeration one word can name: `typedef enum { ... } <tag>;`.  It is
    not cosmetic.  A tag reaches the debug information -- `enum anon_x v;` records the
    enumeration DIE's name as `anon_x`, while `typedef enum { ... } anon_x;` records `@enum`,
    which is what retail has (measured with the pinned compiler: the tagged spelling's DIE
    name is the tag, the typedef's is `@enum`).
    """
    blob = die.attrs.get(0x00f4) or die.attrs.get(0x00f3) or b""
    width = die.attrs.get(AT_byte_size, 4)
    head = (f"{indent}typedef enum {{" if typedef else f"{indent}enum {tag} {{")
    lines = [f"{head}   // size 0x{width:x}"]
    pos = 0
    while pos + width <= len(blob):
        value = int.from_bytes(blob[pos:pos + width], "little", signed=True)
        end = blob.index(b"\0", pos + width)
        lines.append(f"{indent}    {blob[pos + width:end].decode('latin-1')} = {value},")
        pos = end + 1
    lines.append(f"{indent}}}{f' {tag};' if typedef else '};'}")
    return lines


def definition(dw, die, tag, tagger, indent="", typedef=False):
    """A C definition of one aggregate, as lines.

    The layout is the vendored renderer's: member offsets in hex, a member's size or its bit
    range, and the bytes no member covers described in words -- so a reader comparing these
    headers with `dwarf1.py type` sees the same numbers in the same places.

    Describing a gap is not enough to reproduce it: C places the next member by its own
    alignment and closes the aggregate on its widest member's, so a gap that alignment
    explains needs the comment alone, one that a stated alignment reproduces gets
    `__attribute__((aligned(N)))` (`_stated_alignment`, `_tail_alignment`), and one no
    alignment explains is spelled as a member of its own (`_omitted_member`) -- the header
    must reach the recorded offsets and `byte_size`, and a comment does neither.

    `tagger` names every aggregate the members mention.  An anonymous one is named by the
    shared typedef that defines it (`anon_<layout digest>`), never spelled out here: two
    declarations of the same layout would be two DIEs in a unit that uses both, where
    retail's CU carries one.  A named one is `struct <tag>`.

    `typedef` is how a header names a type MWCC's DWARF has no name for.  A `struct <tag>`
    would put the invented tag in the DIE; `typedef struct { ... } <tag>;` leaves the
    aggregate itself unnamed, which is the spelling the compiler records as `@anonN` --
    DWARF 1 has no typedef DIE, so the alias is invisible to the debug information.
    """
    if die.tag == TAG_enumeration_type:
        return _enum_lines(die, tag or die.name or "", indent, typedef=typedef)
    kind = _kind(dw, die)
    size = die.attrs.get(AT_byte_size, 0)
    head = f"{indent}{kind}{' ' + tag if tag else ''} {{   // size 0x{size:x}"
    if typedef:
        head = f"{indent}typedef {kind} {{   // size 0x{size:x}"
    lines = [head]
    ind = indent + "    "
    cursor = 0
    members = 0
    tail_align = dw.align_of(("base", "", die))
    for child in die.children:
        if child.tag not in (TAG_member, TAG_inheritance):
            continue
        if child.tag == TAG_inheritance:
            raise NotSpellable(
                f"{die.name or hex(die.off)}: C has no base classes, so the inheritance "
                f"'{child.attrs.get(AT_name, '')}' records would be lost silently")
        members += 1
        offset = member_offset(child)
        tree = dw.type_of(child) or VOID
        size_of = dw.sizeof(tree)
        align = dw.align_of(tree)
        stated = None if offset is None or kind == "union" else _stated_alignment(
            cursor, offset, align, size)
        if offset is not None and offset > cursor and kind != "union":
            if stated is None and not _padded_by_alignment(cursor, offset, align):
                lines.append(_omitted_member(ind, cursor, offset))
            else:
                lines.append(_gap(ind, cursor, offset))
        text = decl(dw, tree, child.name or "", tagger)
        if stated:
            text += f" __attribute__((aligned({stated})))"
            tail_align = max(tail_align, stated)
        if AT_bit_size in child.attrs:
            bit = child.attrs.get(AT_bit_offset, 0)
            width = child.attrs[AT_bit_size]
            text += f" : {width}"
            note = f"bits {bit}..{bit + width - 1}"
        else:
            note = f"0x{size_of:x}" if size_of is not None else "?"
        lines.append(f"{ind}/* 0x{offset if offset is not None else 0:03x} */ "
                     f"{text};".ljust(len(ind) + 48) + f"  // {note}")
        if offset is not None and size_of is not None:
            cursor = max(cursor, offset + size_of)
    tail = None
    if not members:
        lines.append(f"{ind}// no data members")
    elif size > cursor:
        tail = _tail_alignment(cursor, size, tail_align)
        if kind != "union":
            if tail or _padded_by_alignment(cursor, size, tail_align):
                lines.append(_gap(ind, cursor, size))
            else:
                lines.append(_omitted_member(ind, cursor, size))
    stated = f" __attribute__((aligned({tail})))" if tail else ""
    lines.append(f"{indent}}}{stated}{' ' + tag if typedef and tag else ''};")
    if typedef and not tag:
        raise NotSpellable(f"DIE 0x{die.off:x}: a typedef needs the name the C will use")
    return lines


# ---------------------------------------------------------------------------
# the layout a definition is picked from
# ---------------------------------------------------------------------------


def _signature(dw, die):
    """What DWARF recorded about one aggregate: its size, its kind, its members.

    A member's type is part of it, and an anonymous member contributes its own structure
    rather than its `@anonN` name -- that name is per-unit numbering, so it is not evidence;
    what is inside it is.  Two units whose copies of a named type disagree *inside* a nested
    anonymous type are disagreeing about that named type, and this has to say so.
    """
    members = []
    for child in die.children:
        if child.tag != TAG_member:
            continue
        tree = dw.type_of(child) or VOID
        core = innermost(tree)
        nested = core[2] if len(core) > 2 and isinstance(core[2], Die) else None
        if nested is not None and nested.tag in AGGREGATES and anonymous(nested):
            spelling = ("anonymous", _signature(dw, nested), _signature_spelling(dw, tree))
        else:
            spelling = _signature_spelling(dw, tree)
        members.append((child.name, member_offset(child), child.attrs.get(AT_bit_offset),
                        child.attrs.get(AT_bit_size), spelling))
    return (die.attrs.get(AT_byte_size), _kind(dw, die), tuple(members))


def _signature_spelling(dw, tree):
    """A member's type, spelled stably: an anonymous aggregate is `struct ANON`."""
    text = decl(dw, tree, "", lambda d: f"{_kind(dw, d)} "
                                        f"{'ANON' if anonymous(d) else d.name}")
    return re.sub(r"@anon\d+", "@anon", text)


def _digest(signature):
    """A short digest of a layout: how a reader tells two apart, and compares two runs."""
    return hashlib.sha256(repr(signature).encode()).hexdigest()[:12]


def _disagreement(dw, name, first, second):
    """The line a shared definition cannot be picked over: the type, then the member."""
    one, two = _signature(dw, first), _signature(dw, second)
    if one[0] != two[0]:
        return (f"{name}: declared 0x{one[0]:x} bytes in {_where(first)} but 0x{two[0]:x} "
                f"in {_where(second)}")
    if one[1] != two[1]:
        return f"{name}: a {one[1]} in {_where(first)} but a {two[1]} in {_where(second)}"
    for member in one[2]:
        other = next((m for m in two[2] if m[0] == member[0]), None)
        if other != member:
            return (f"{name}: member '{member[0]}' is at "
                    f"0x{member[1] if member[1] is not None else 0:03x} as '{member[4]}' in "
                    f"{_where(first)}, but at "
                    f"0x{other[1] if other and other[1] is not None else 0:03x} as "
                    f"'{other[4] if other else 'absent'}' in {_where(second)}")
    return (f"{name}: {_where(first)} and {_where(second)} disagree about its members "
            f"({len(one[2])} against {len(two[2])})")


def _canonical(dw, name, dies):
    """The one DIE that speaks for `name`, or a :class:`LayoutDisagreement`."""
    signature = _signature(dw, dies[0])
    for other in dies[1:]:
        if _signature(dw, other) != signature:
            raise LayoutDisagreement(_disagreement(dw, name, dies[0], other))
    return dies[0]


def named_types(dw):
    """`{name: [DIE, ...]}` -- every named aggregate, by the name DWARF gives it."""
    groups = collections.defaultdict(list)
    for die in dw.dies.values():
        if die.tag in AGGREGATES and not anonymous(die):
            groups[die.name].append(die)
    return {name: sorted(dies, key=lambda d: d.off) for name, dies in groups.items()}


# ---------------------------------------------------------------------------
# the anonymous layouts, shared
# ---------------------------------------------------------------------------

#: `{Dwarf: {layout digest: representative DIE}}`: the shared anonymous-type index.
_SHARED = weakref.WeakKeyDictionary()

#: The prefix of a shared anonymous type's C alias.  The digest makes it stable; `@` is not
#: a legal C identifier, and a per-unit `anon_<N>_<unit>` name cannot appear in a shared
#: header, so a name has to be invented -- and it never reaches the DWARF, because the
#: aggregate the alias names is still unnamed.
ANON_PREFIX = "anon_"


def shared_name(digest):
    """The alias one anonymous layout is known by, everywhere it is used."""
    return f"{ANON_PREFIX}{digest}"


def shared_anonymous(dw):
    """`{layout digest: [DIE, ...]}` -- every anonymous layout a shared header defines.

    The defect this fixes is measured, not inferred: retail's CU for `shop_info.c` carries
    **one** `@anon0` DIE (8 bytes, `short x, y, w, h`), referenced by both
    `_CWS_WIN_W.def` and `anon_1_129.shop_rect` (DIE 0x23C9FD, refs 0x23DBFA and 0x23D289).
    A named type's header that spells the member out inline, plus a unit header that
    typedefs its own copy, declares *two* aggregates of that layout -- two DIEs where
    retail's block has one, 5 DIEs and 0x97 bytes too many (181/0x18C7 against 176/0x1805).

    So the layout is the key, not the unit or an offset: every anonymous aggregate reachable
    from a named type's canonical definition is registered under the digest of its
    structural signature, and its header defines it once as a typedef of an *unnamed*
    aggregate.  A named type's member and a unit's own anonymous type both name that alias,
    which keeps one DIE -- and the digest is the structural proof that the two layouts are
    the same, since the signature covers size, kind, member names, offsets, bit fields and
    the members' own types.
    """
    index = _SHARED.get(dw)
    if index is None:
        index = {}
        groups = named_types(dw)
        for name in sorted(groups):
            canonical = _canonical(dw, name, groups[name])
            for mention in _members(dw, canonical, deep=True):
                if not anonymous(mention):
                    continue
                bucket = index.setdefault(_digest(_signature(dw, mention)), [])
                if all(known.off != mention.off for known in bucket):
                    bucket.append(mention)
        for dies in index.values():
            dies.sort(key=lambda d: d.off)
        _SHARED[dw] = index
    return index


def _tagger(dw):
    """Every aggregate a member mentions, spelled the way a shared header spells it.

    A named type is `struct <tag>`; an anonymous one is the alias of its layout's shared
    definition, and a layout that was not registered is a refusal rather than an inline
    spelling: spelling it out here is what put a second DIE in retail's block.
    """
    def specifier(die):
        if not anonymous(die):
            return f"{_kind(dw, die)} {die.name}"
        digest = _digest(_signature(dw, die))
        if digest not in shared_anonymous(dw):
            raise NotSpellable(
                f"{_where(die)} ({_declared_by(die)}): the anonymous type {die.name!r} is "
                f"not reachable from a named type, so no shared header defines it")
        return shared_name(digest)
    return specifier


def _member_spellings(dw, die):
    """`(named, anonymous)` -- the aggregates this definition's own members name.

    Named ones belong in the include list and the forward declarations, anonymous ones in
    the include list as the shared header that defines them.  Nested anonymous aggregates
    are *that* header's members, so they are not this one's dependency.
    """
    named, anon = [], []
    for mention in _members(dw, die):
        if mention is die or mention.off == die.off:
            continue
        (anon if anonymous(mention) else named).append(mention)
    return named, anon


# ---------------------------------------------------------------------------
# one unit's own anonymous types
# ---------------------------------------------------------------------------


class Unit:
    """One translation unit, and the anonymous types that belong to it.

    `@anon0` is the numbering of the unit that declares it, so a use has to name the unit:
    `anon_<N>_<unit index>`.  The index is the unit's place in the retail DWARF's own order,
    which makes the tag as stable as the ELF it came from.
    """

    def __init__(self, dw, tu):
        self.dw = dw
        self.tu = tu
        self.index = dw.tus.index(tu)

    def tag(self, die):
        number = die.name[5:] if (die.name or "").startswith("@anon") else ""
        stem = number if number.isdigit() else f"x{die.off:x}"
        return f"anon_{stem}_{self.index}"

    def specifier(self, die):
        """A use of this unit's own anonymous type: the alias its header typedefs.

        Not `struct <tag>`: the unit header declares the type as a `typedef` of an
        *unnamed* aggregate, which is the only spelling MWCC records as `@anonN` (DWARF 1
        has no typedef DIE, so the alias itself never reaches the debug information).  A
        named type still needs its keyword, because the shared header defines a tag.

        An anonymous enumeration is a typedef too, for the same reason a shared one is: a tag
        reaches the debug information (`enum anon_x v;` records the enumeration DIE's name as
        `anon_x`), while `typedef enum { ... } anon_x;` records `@enum` -- what retail has.
        """
        if anonymous(die):
            return self.tag(die)
        return f"{_kind(self.dw, die)} {die.name}"

    def owns(self, die):
        """Whether this unit declared `die` (its anonymous types, and no other unit's)."""
        return die.cu is not None and self.dw.tu_of.get(die.cu.off) is self.tu

    def definitions(self):
        """This unit's anonymous types as `[(tag, DIE)]`, dependencies first.

        The order matters twice.  A member held by value needs its type complete before it,
        and one type held by value inside itself is not something C can express.  And a use
        is an *alias* (`anon_<N>_<unit>` is a typedef of an aggregate that has no name), so
        a member that only points at another of these types still needs that alias declared
        first -- C wants the name, not the complete type.  Collisions are checked on the way:
        one tag over two layouts would be exactly the silent mix-up `anon_<N>_<unit>` exists
        to prevent.
        """
        own = collections.OrderedDict()
        for die in unit_types(self.dw).get(self.tu, []):
            tag = self.tag(die)
            first = own.setdefault(tag, die)
            if first is not die and _signature(self.dw, first) != _signature(self.dw, die):
                raise LayoutDisagreement(
                    f"{tag}: {_where(first)} and {_where(die)} are both this unit's "
                    f"anonymous types and want the same tag")
        order, done = [], set()

        def visit(die):
            if die.off in done:
                return
            done.add(die.off)
            for dependency in _members(self.dw, die, deep=True):
                if dependency.off not in done and self.owns(dependency) \
                        and anonymous(dependency):
                    visit(dependency)
            order.append(die)

        for die in own.values():
            visit(die)
        return [(self.tag(die), die) for die in order]


def _by_value(dw, die):
    """The aggregates a definition needs *complete*: its members and bases held by value."""
    out = []
    for child in die.children:
        if child.tag not in (TAG_member, TAG_inheritance):
            continue
        tree = dw.type_of(child)
        while tree and tree[0] in ("cv", "array"):
            tree = tree[-1]
        if tree and tree[0] == "base" and len(tree) > 2 and isinstance(tree[2], Die) \
                and tree[2].tag in AGGREGATES:
            out.append(tree[2])
    return out


def _mentioned(tree, out):
    """Every aggregate a type tree names, through pointers and arrays too."""
    kind = tree[0]
    if kind == "base":
        ref = tree[2] if len(tree) > 2 else None
        if isinstance(ref, Die) and ref.tag in AGGREGATES:
            out.append(ref)
    elif kind == "func":
        if tree[1] is not None:
            _mentioned(tree[1], out)
        for param in tree[2]:
            _mentioned(param, out)
    elif kind in ("ptr", "ref", "cv", "array", "memptr"):
        _mentioned(tree[-1], out)
    return out


def _subtree(dw, die, out):
    """Every aggregate a declaration names: its own type, then its children's."""
    tree = dw.type_of(die)
    if tree:
        _mentioned(tree, out)
    for child in die.children:
        _subtree(dw, child, out)
    return out


def _members(dw, die, deep=False):
    """The aggregates the members of `die` name, however deeply.

    `deep` descends into the anonymous aggregates those members hold: a definition that
    spells one out inline needs *its* members' types too, and they are not in its type tree.
    """
    out = []
    for child in die.children:
        if child.tag in (TAG_member, TAG_inheritance):
            _mentioned(dw.type_of(child) or VOID, out)
    if deep:
        for mention in list(out):
            if anonymous(mention):
                out.extend(_members(dw, mention, deep=True))
    return out


# ---------------------------------------------------------------------------
# the headers
# ---------------------------------------------------------------------------


def _dependencies(dw, die, own_name=None):
    """The includes one definition's header needs: named types, then anonymous layouts.

    `(named, anonymous)` names, sorted; the anonymous ones are the shared headers that
    define the layout.  `own_name` -- the header's own type -- is never a dependency of
    itself, however many copies of it DWARF holds.
    """
    named, anon = _member_spellings(dw, die)
    names = sorted({d.name for d in named if d.name != own_name})
    layouts = sorted({shared_name(_digest(_signature(dw, d))) for d in anon})
    return names, layouts


def _forward(dw, die, own_name=None):
    """`struct _CWS_OBJ;` -- the named aggregates this definition points at."""
    named, _anon = _member_spellings(dw, die)
    return sorted({f"{_kind(dw, d)} {d.name};" for d in named
                   if d.name != own_name and d.tag != TAG_enumeration_type})


def _type_header(dw, name, canonical, dies):
    """One named type: its definition, and where it came from."""
    g = _guard("DDR", TYPES_DIR, name, "H")
    signature = _signature(dw, canonical)
    spelling = f"{_kind(dw, canonical)} {name}"
    dependencies, layouts = _dependencies(dw, canonical, own_name=name)
    forward = _forward(dw, canonical, own_name=name)
    declared = ", ".join(_declared_by(d) for d in dies)
    lines = [f"/* {spelling} -- {len(signature[2])} members, size 0x{signature[0]:x}, "
             f"layout {_digest(signature)}.",
             " *",
             f" * One definition, agreed by the {len(dies)} "
             f"{'unit' if len(dies) == 1 else 'units'} that "
             f"{'declares' if len(dies) == 1 else 'declare'} it: "
             f"{_declared_by(canonical)}.",
             " *",
             " * DWARF 1 resolves typedefs away, so the only spelling the evidence offers",
             f" * for a use is `{spelling} *`."]
    if layouts:
        lines += [" *",
                  " * An anonymous member is named, not spelled out here: its layout is",
                  " * defined once in the `types/anon_<digest>.h` header included below, as a",
                  " * typedef of an *unnamed* aggregate, so every use of that layout in a",
                  " * unit's block is one DIE -- retail's own block has one, and two",
                  " * declarations of it are 5 DIEs and 0x97 bytes of overrun."]
    lines += [" *",
              f" * declared by: {declared}",
              " */",
              f"#ifndef {g}",
              f"#define {g}",
              ""]
    lines += forward
    if forward:
        lines.append("")
    lines += [f'#include "{TYPES_DIR}/{dep}.h"' for dep in dependencies]
    lines += [f'#include "{TYPES_DIR}/{layout}.h"' for layout in layouts]
    if dependencies or layouts:
        lines.append("")
    lines += definition(dw, canonical, name, _tagger(dw))
    lines += ["", f"#endif /* {g} */"]
    return _uppercase("\n".join(lines) + "\n")


def _anon_header(dw, digest, dies):
    """One shared anonymous layout: a typedef of an unnamed aggregate, defined once.

    The aggregate stays unnamed -- `typedef struct { ... } anon_<digest>;`, never `struct
    anon_<digest> { ... };` -- because DWARF 1 has no typedef DIE: the alias never reaches
    the debug information, and the compiler records the type as `@anonN`, which is what
    retail's block has.  A tag of our own would put an invented name into the DIE.
    """
    die = dies[0]
    name = shared_name(digest)
    g = _guard("DDR", TYPES_DIR, name, "H")
    size = die.attrs.get(AT_byte_size, 0)
    kind = _kind(dw, die)
    dependencies, layouts = _dependencies(dw, die)
    forward = _forward(dw, die)
    declared = ", ".join(_declared_by(d) for d in dies)
    lines = [f"/* anonymous {kind} -- {len(_signature(dw, die)[2])} members, size "
             f"0x{size:x}, layout {digest}.",
             " *",
             " * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias",
             f" * `{name}` is the oracle's own, derived from the layout digest: every header",
             " * that uses the layout names the same typedef, and a unit's block then holds",
             " * one DIE for it -- retail's own has one.",
             " *",
             f" * {len(dies)} declarations share this layout, all structurally identical; the",
             " * definition comes from the first in `.debug` order.",
             " *",
             " * declared by: " + declared,
             " */",
             f"#ifndef {g}",
             f"#define {g}",
             ""]
    lines += forward
    if forward:
        lines.append("")
    lines += [f'#include "{TYPES_DIR}/{dep}.h"' for dep in dependencies]
    lines += [f'#include "{TYPES_DIR}/{layout}.h"' for layout in layouts]
    if dependencies or layouts:
        lines.append("")
    lines += definition(dw, die, name, _tagger(dw), typedef=True)
    lines += ["", f"#endif /* {g} */"]
    return _uppercase("\n".join(lines) + "\n")


def _index_text(names, elf):
    """`include/types.h`: every named type, for a reader or for a source that wants them all."""
    g = _guard("DDR", "TYPES", "H")
    return "\n".join(
        [f"/* Every named type the oracle recovered from {_display(elf)}, one definition each.",
         " *",
         " * Generated by tools/oracle/emit_headers.py; do not hand-edit.  Compile with the",
         " * include root on the search path:",
         " *   mwccps2 -c -lang c -O3 -g -Iinclude",
         " */",
         f"#ifndef {g}",
         f"#define {g}",
         ""]
        + [f'#include "{TYPES_DIR}/{name}.h"' for name in sorted(names)]
        + ["", f"#endif /* {g} */"]) + "\n"


def _supplied_anonymous(dw, named):
    """`{layout digest: shared alias}` -- the anonymous layouts a shared header defines.

    A named type's header no longer spells an anonymous member out where it sits: it names
    the shared typedef of that layout (`types/anon_<digest>.h`), so the header a unit
    includes already declares the layout.  A unit header that declared the same layout again
    would put a second DIE in the unit's debug block for one type -- retail's has one.  The
    walk follows the named types a shared header includes, since those name theirs too.
    """
    out, seen = {}, set()
    stack = list(named.values())
    while stack:
        die = stack.pop()
        if die.off in seen:
            continue
        seen.add(die.off)
        for mention in _members(dw, die, deep=True):
            if anonymous(mention):
                digest = _digest(_signature(dw, mention))
                if digest in shared_anonymous(dw):
                    out[digest] = shared_name(digest)
            else:
                stack.append(mention)
    return out


def _unit_header(dw, tu):
    """`include/src/<unit>.h`: what it includes, its own types, its globals, its functions."""
    unit = Unit(dw, tu)
    definitions = unit.definitions()
    known = {tag for tag, _ in definitions}
    functions = tu.functions()
    declarations = tu.decl.children if tu.decl else []
    variables = [d for d in declarations
                 if d.tag in (TAG_global_variable, TAG_local_variable)]

    named, used = collections.OrderedDict(), []

    def collect(mentions):
        for mention in mentions:
            if anonymous(mention):
                used.append(mention)
            else:
                named.setdefault(mention.name, mention)

    for die in variables + functions:
        collect(_subtree(dw, die, []))
    for _tag, die in definitions:
        collect(_members(dw, die))
    strangers = [d for d in used if unit.tag(d) not in known]
    if strangers:
        raise NotSpellable(
            f"{tu.name} uses the anonymous type {strangers[0].name!r} "
            f"({_declared_by(strangers[0])}), which its own header cannot name: an anonymous "
            f"type belongs to the unit that declares it, and this one is another unit's")

    # What this header has to declare, and what the shared headers already declare for it.
    # A supplied layout stays out (its shared typedef is one DIE in retail's block, and the
    # header the unit includes already defines it); anything else -- a root with no named
    # container -- is declared here, as a typedef of an *unnamed* aggregate so MWCC records
    # the `@anonN` name retail has.
    #
    # One DIE per layout, and no more: a unit that declares the *same* layout twice keeps the
    # second as its own typedef, because retail's block has two DIEs there (measured:
    # `fp_msel_obj.c` and `net.c` each declare one layout twice, and their CUs carry two).
    # Sharing both would drop a DIE.  The one that shares is the first in `.debug` order, so
    # the choice does not depend on the walk.
    supplied = _supplied_anonymous(dw, named)
    by_digest = collections.defaultdict(list)
    for _tag, die in definitions:
        if not anonymous(die):
            continue
        digest = _digest(_signature(dw, die))
        if digest in supplied:
            by_digest[digest].append(die)
    shared_off = {min(dies, key=lambda d: d.off).off: supplied[digest]
                  for digest, dies in by_digest.items()}

    def shared_alias(die):
        """The shared alias for this use, if a header this unit includes defines it."""
        return shared_off.get(die.off) if anonymous(die) else None

    keep, stack = set(), [die for _tag, die in definitions if shared_alias(die) is None]
    while stack:
        die = stack.pop()
        if die.off in keep:
            continue
        keep.add(die.off)
        stack.extend(d for d in _members(dw, die, deep=True)
                     if anonymous(d) and unit.owns(d) and shared_alias(d) is None)
    own = [(tag, die) for tag, die in definitions if die.off in keep]

    def specifier(die):
        """A use of an anonymous type: its shared alias, or this unit's own typedef."""
        alias = shared_alias(die)
        return alias if alias else unit.specifier(die)

    g = _guard("DDR", "UNIT", emit_cus.relpath(tu.name), "H")
    pcs = [(cu.attrs[AT_low_pc], cu.attrs[AT_high_pc]) for cu in tu.cus
           if AT_low_pc in cu.attrs]
    files = collections.Counter(f.cu.name for f in functions)
    lines = ["/*",
             f" * {tu.name}",
             f" * {tu.cus[0].attrs.get(dwarf1.AT_producer, '')}, overlay {tu.overlay}; "
             f"{len(functions)} functions"
             + (f", code 0x{min(p[0] for p in pcs):08x}-0x{max(p[1] for p in pcs):08x}"
                if pcs else "")]
    if len(files) > 1:
        lines.append(" * functions come from: "
                     + ", ".join(f"{basename(n)} ({c})" for n, c in files.items()))
    lines += [" * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex",
              " *",
              " * C mode: a use is `struct <tag> *`, and the named types this unit needs are",
              " * included from include/types/.  `@anonN` is this unit's own numbering, so an",
              " * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a",
              " * typedef of an *unnamed* aggregate, which is the spelling the compiler",
              " * records back as `@anonN`.  A layout the shared headers already define is",
              " * named by its own `anon_<digest>` alias instead, so the block holds one DIE",
              " * for it, as retail's does.",
              " */",
              f"#ifndef {g}",
              f"#define {g}"]
    if named:
        lines.append("")
        lines += [f'#include "{TYPES_DIR}/{name}.h"' for name in sorted(named)]
    if own:
        lines += ["", f"/* anonymous types ({len(own)}) */"]
        for tag, die in own:
            lines += ["",
                      f"/* {tag} -- {die.name}, 0x{die.attrs.get(AT_byte_size, 0):x} "
                      f"bytes, {_declared_by(die)} */"]
            lines += definition(dw, die, tag, specifier, typedef=True)
        lines.append("")

    globals_, references = [], []
    for die in variables:
        tree = dw.type_of(die) or VOID
        location = die.attrs.get(dwarf1.AT_location)
        where = loc_str(location) if location else "?"
        if where == "@0x00000000":
            where = "not allocated"
        if tree[0] == "func":
            references.append(f"{decl(dw, tree, _name(dw, die), specifier)};".ljust(64)
                              + f" /* {where} */")
        else:
            storage = "static " if die.tag == TAG_local_variable else ""
            size = dw.sizeof(tree)
            globals_.append(f"{storage}{decl(dw, tree, _name(dw, die), specifier)};"
                            .ljust(64) + f" /* {where}"
                            + (f" size 0x{size:x}" if size is not None else "") + " */")
    if globals_:
        lines += ["", f"/* variables ({len(globals_)}) */"]
        lines += list(dict.fromkeys(globals_))
    if references:
        lines += ["", f"/* functions referenced ({len(references)}) */"]
        lines += list(dict.fromkeys(references))
    if functions:
        lines += ["", f"/* functions defined ({len(functions)}) */"]
        by_file = collections.OrderedDict()
        for function in functions:
            by_file.setdefault(function.cu.name, []).append(function)
        for name, group in by_file.items():
            if len(by_file) > 1:
                lines += ["", f"/* {basename(name)} */"]
            for function in sorted(group, key=lambda f: f.attrs.get(AT_low_pc, 0)):
                lines.append(f"{prototype(dw, function, specifier)};".ljust(64)
                             + f" /* {_range(dw, function)} */")
    lines += ["", f"#endif /* {g} */"]
    return _uppercase("\n".join(lines) + "\n")


def _name(dw, die):
    """The plain name of a global: a C header has no `Class::member` to spell."""
    qualified = dwarf1.Dwarf.qualname(dw, die)
    if "::" in qualified:
        raise NotSpellable(f"{die.name!r} at 0x{die.off:x} is a class member; a C header "
                           f"cannot spell `{qualified}`")
    return die.name or qualified


def _range(dw, function):
    """`0x0021C420-0x0021C450 lines 24-34` -- retail's bytes and retail's line numbers."""
    low, high = function.attrs.get(AT_low_pc, 0), function.attrs.get(AT_high_pc, 0)
    span = dw.line_range(function)
    return f"0x{low:08x}-0x{high:08x}" + (f" lines {span[0]}-{span[1]}" if span else "")


def prototype(dw, function, tagger):
    """`void f(struct T *p);` -- the vendored `prototype()`, spelled in C.

    The parameter list is the vendored reader's own (`params()`, which reconciles DWARF's
    partial list with the mangled name); only the spelling of the type trees is ours.
    """
    parts = []
    for die, tree in dw.params(function):
        if die is None:
            parts.append(decl(dw, tree, "", tagger) + " /* not in DWARF */")
            continue
        parts.append(decl(dw, tree, die.name or "", tagger))
    if any(c.tag == TAG_unspecified_parameters for c in function.children):
        parts.append("...")
    text = decl(dw, dw.type_of(function) or VOID,
                f"{_name(dw, function)}({', '.join(parts) or 'void'})", tagger)
    if function.tag == TAG_subroutine:
        text = "static " + text
    elif dw.lacks_this(function):
        text = "/*static?*/ " + text
    return text


_HEX = re.compile(r"0x([0-9a-fA-F]+)")


def _uppercase(text):
    """Hex offsets upper-cased, as every header under `include/` has spelled them."""
    return _HEX.sub(lambda m: "0x" + m.group(1).upper(), text)


def render_types(dw):
    """`({tag: text}, {layout digest: text})` -- the shared tree, named types and layouts.

    A named type's definition names its anonymous members by the layout's shared alias, so
    the anonymous layouts are headers of their own; both sets are returned because both are
    written, and the anonymous ones are named by digest (there is no DWARF name to use).
    """
    groups = named_types(dw)
    types = {name: _type_header(dw, name, _canonical(dw, name, groups[name]), groups[name])
             for name in sorted(groups)}
    anonymous = {digest: _anon_header(dw, digest, dies)
                 for digest, dies in sorted(shared_anonymous(dw).items())}
    return types, anonymous


def render(elf_path, cu_substring):
    """The C header for the translation unit whose source path contains `cu_substring`."""
    dw = dwarf(elf_path)
    return _unit_header(dw, _unit(dw, cu_substring))


def _unit(dw, needle):
    """The one translation unit a `dwarf1 header --cu`-style needle names."""
    want = (needle or "").lower()
    for match in (lambda t: (t.name or "").lower() == want,
                  lambda t: basename(t.name).lower() == want,
                  lambda t: want in (t.name or "").lower()):
        hits = [tu for tu in dw.tus if match(tu)]
        if len(hits) == 1:
            return hits[0]
        if hits:
            raise NoSuchUnit(f"{len(hits)} translation units match {needle!r}: "
                             + ", ".join(t.name for t in hits[:8]))
    raise NoSuchUnit(f"no translation unit matches {needle!r}")


def write_all(elf_path, outdir):
    """Write the whole generated tree; returns the translation-unit headers.

    The tree is `include/types/<tag>.h` (one named type each), `include/types/anon_<digest>.h`
    (one anonymous layout each, shared by every header that uses it), `include/types.h` (all
    the named types) and `include/README.md`, plus one header per translation unit under
    `include/src/`.  The return value is the unit headers -- what `./ddr oracle` counts and
    what a caller working unit by unit wants; the shared tree is written alongside them.

    Nothing is deleted: a file from a previous run -- another target's `types/<tag>.h`, a unit
    this ELF does not have -- stays until someone removes it.  That is on purpose (the set of
    tags is evidence, and silently deleting a header is how a stale one survives a target
    switch unnoticed); `tests/oracle/test_emit_headers.py` compares the committed tree with a
    fresh run, so a leftover file fails the suite instead.
    """
    dw = dwarf(elf_path)
    outdir = pathlib.Path(outdir)
    types, anonymous = render_types(dw)
    types_dir = outdir / TYPES_DIR
    types_dir.mkdir(parents=True, exist_ok=True)
    for name in sorted(types):
        (types_dir / f"{name}.h").write_text(types[name])
    for digest in sorted(anonymous):
        (types_dir / f"{shared_name(digest)}.h").write_text(anonymous[digest])
    (outdir / INDEX).write_text(_index_text(types, elf_path))
    (outdir / README_NAME).write_text(readme(elf_path))
    units = []
    seen = {}
    for tu in dw.tus:
        rel = emit_cus.relpath(tu.name)
        dest = outdir / header_for(rel)
        if dest in seen:
            raise NoSuchUnit(f"{tu.name} and {seen[dest]} both write {dest}")
        seen[dest] = tu.name
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text(_unit_header(dw, tu))
        units.append(dest)
    return units


def readme(elf):
    """`include/README.md`: what the tree is, and how to check it."""
    return f"""# include/

Generated from `{_display(elf)}` by `tools/oracle/emit_headers.py` (`./ddr oracle`).
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
"""


if __name__ == "__main__":
    elf = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else "include"
    units = write_all(elf, out)
    print(f"{len(units)} translation-unit headers written -> {out}")
