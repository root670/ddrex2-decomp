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
unit's header and nowhere else.  A *named* type whose layout contains one spells that member
out inline instead -- the layout digest, checked across every unit that declares the type, is
what makes that faithful -- because a per-unit tag must not leak into a shared header.

`include/**` is committed and generated: `./ddr oracle` regenerates it, and
`tests/oracle/test_emit_headers.py` checks every header compiles as C under the *original*
compiler (`tools/toolchain/compile.py --syntax-only`, which is `mwccps2 -lang c`).

No promoted unit includes one of these yet.  A unit that does gets different debug bytes: its
own declaration is what puts its statements on the lines retail has them on, so removing it
moves the unit's `.line` table (measured on `sys_scf.c`: the same `.text`, 240 -> 237 bytes
of `.debug`, and a `.line` payload with different rows).  Reproducing retail's own includes is
a generator problem, and `src/sys/sys_scf.c` keeps its hand-written declarations for now.
"""
import collections, hashlib, pathlib, re, sys

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
#: plain C names are the only fundamental types orig/SLUS_207.11 uses; a `bool`, `label` or
#: `complex` would fail the C gate loudly rather than silently, which is where it would get
#: its mapping.
FUNDAMENTAL = {0xa510: "unsigned __int128"}

CACHE = {}


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


def _core_to(tree, core):
    """`tree` with its innermost type replaced by `core` (through pointers and arrays)."""
    kind = tree[0]
    if kind in ("ptr", "ref"):
        return (kind, _core_to(tree[1], core))
    if kind in ("cv", "array", "memptr"):
        return (kind, tree[1], _core_to(tree[2], core))
    return core


def _gap(indent, start, end, align):
    """Bytes no member covers, in the vendored renderer's own words.

    DWARF has no alignment attributes (`sceVu0FVECTOR` and friends are 16-byte aligned
    typedefs), so a gap that rounding up to 16 explains is only probably padding.  There is
    no vtable-pointer case: these are C translation units, and none of them has one.
    """
    up = lambda n: (start + n - 1) // n * n
    if up(align) == end:
        why = "padding"
    elif up(16) == end:
        why = "padding if 16-byte aligned, else a member DWARF omits"
    else:
        why = "not in DWARF (a member CodeWarrior did not describe)"
    return f"{indent}/* 0x{start:03x} */ // 0x{end - start:x} bytes {why}"


def _enum_lines(die, tag, indent):
    """`enum <tag> { A = 1, ... };` from CodeWarrior's own item blob.

    The vendored reader renders enums out of `0x00f3`/`0x00f4`, the vendor's attribute
    holding the items as an integer of `byte_size` bytes followed by a NUL-terminated name.
    Nothing in this image is an enum, so this path is untriggered; it is here because the
    renderer has to spell every aggregate DWARF can hand it.
    """
    blob = die.attrs.get(0x00f4) or die.attrs.get(0x00f3) or b""
    width = die.attrs.get(AT_byte_size, 4)
    lines = [f"{indent}enum {tag} {{   // size 0x{width:x}"]
    pos = 0
    while pos + width <= len(blob):
        value = int.from_bytes(blob[pos:pos + width], "little", signed=True)
        end = blob.index(b"\0", pos + width)
        lines.append(f"{indent}    {blob[pos + width:end].decode('latin-1')} = {value},")
        pos = end + 1
    lines.append(f"{indent}}};")
    return lines


def definition(dw, die, tag, tagger, inline_anonymous=False, indent=""):
    """A C definition of one aggregate, as lines.

    The layout is the vendored renderer's: member offsets in hex, a member's size or its bit
    range, and the bytes no member covers described in words -- so a reader comparing these
    headers with `dwarf1.py type` sees the same numbers in the same places.

    An anonymous member is `inline_anonymous`'s business: a shared header spells it out,
    because a per-unit tag cannot travel; a unit's own header names it instead, so that
    every use of one type inside that unit stays the same type.
    """
    if die.tag == TAG_enumeration_type:
        return _enum_lines(die, tag or die.name or "", indent)
    kind = _kind(dw, die)
    size = die.attrs.get(AT_byte_size, 0)
    lines = [f"{indent}{kind}{' ' + tag if tag else ''} {{   // size 0x{size:x}"]
    ind = indent + "    "
    cursor = 0
    members = 0
    for child in die.children:
        if child.tag == TAG_inheritance:
            raise NotSpellable(
                f"{die.name or hex(die.off)}: C has no base classes, so the inheritance "
                f"'{child.attrs.get(AT_name, '')}' records would be lost silently")
        if child.tag != TAG_member:
            continue
        members += 1
        offset = member_offset(child)
        tree = dw.type_of(child) or VOID
        size_of = dw.sizeof(tree)
        if offset is not None and offset > cursor and kind != "union":
            lines.append(_gap(ind, cursor, offset, dw.align_of(tree)))
        core = innermost(tree)
        nested = core[2] if len(core) > 2 and isinstance(core[2], Die) else None
        if inline_anonymous and nested is not None and nested.tag in AGGREGATES \
                and anonymous(nested):
            # `struct { ... } hc_work[8];` is the only spelling a shared header has.
            inline = definition(dw, nested, None, tagger,
                                inline_anonymous=inline_anonymous, indent=ind)
            tail = declare(_core_to(tree, ("base", "", None)), child.name or "").strip()
            inline[-1] = inline[-1].replace("};", f"}} {tail};")
            inline[0] = (f"{ind}/* 0x{offset if offset is not None else 0:03x} */ "
                         + inline[0].lstrip())
            lines.extend(inline)
        else:
            text = decl(dw, tree, child.name or "", tagger)
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
    if not members:
        lines.append(f"{ind}// no data members")
    elif kind != "union" and size > cursor:
        lines.append(_gap(ind, cursor, size, dw.align_of(("base", "", die))))
    lines.append(f"{indent}}};")
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


def _shared_tagger(dw):
    """A named type's spelling for a shared header -- and a refusal, not a guess.

    An anonymous type reaching a shared header means the caller should have spelled it out
    inline (`definition(..., inline_anonymous=True)`); a tag here would be one unit's, and
    the header is every unit's.
    """
    def specifier(die):
        if anonymous(die):
            raise NotSpellable(
                f"{_where(die)} ({_declared_by(die)}): a shared header names the anonymous "
                f"type {die.name!r}, which belongs to one unit and cannot travel")
        return f"{_kind(dw, die)} {die.name}"
    return specifier


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
        """`struct <tag>` for a use: this unit's tag, or the shared name."""
        return f"{_kind(self.dw, die)} {self.tag(die) if anonymous(die) else die.name}"

    def owns(self, die):
        """Whether this unit declared `die` (its anonymous types, and no other unit's)."""
        return die.cu is not None and self.dw.tu_of.get(die.cu.off) is self.tu

    def definitions(self):
        """This unit's anonymous types as `[(tag, DIE)]`, dependencies first.

        A member held by value needs its type complete before it, and one type held by value
        inside itself is not something C can express, so the order is a plain dependency
        walk.  Collisions are checked on the way: one tag over two layouts would be exactly
        the silent mix-up `anon_<N>_<unit>` exists to prevent.
        """
        own = collections.OrderedDict()
        for die in sorted(self.dw.dies.values(), key=lambda d: d.off):
            if die.tag in AGGREGATES and anonymous(die) and self.owns(die):
                tag = self.tag(die)
                first = own.setdefault(tag, die)
                if first is not die and \
                        _signature(self.dw, first) != _signature(self.dw, die):
                    raise LayoutDisagreement(
                        f"{tag}: {_where(first)} and {_where(die)} are both this unit's "
                        f"anonymous types and want the same tag")
        order, done = [], set()

        def visit(die):
            if die.off in done:
                return
            done.add(die.off)
            for dependency in _by_value(self.dw, die):
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


def _type_header(dw, name, canonical, dies):
    """One named type: its definition, and where it came from."""
    g = _guard("DDR", TYPES_DIR, name, "H")
    signature = _signature(dw, canonical)
    spelling = f"{_kind(dw, canonical)} {name}"
    # A type does not include itself, however many copies of it DWARF holds.
    mentions = [d for d in _members(dw, canonical, deep=True) if d.name != name]
    nested_anonymous = any(anonymous(d) for d in mentions)
    dependencies = sorted({d.name for d in mentions if not anonymous(d)})
    forward = sorted({f"{_kind(dw, d)} {d.name};" for d in mentions
                      if not anonymous(d) and d.tag != TAG_enumeration_type})
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
    if nested_anonymous:
        lines += [" *",
                  " * A member this type holds anonymously is spelled out below, because it",
                  " * has no name that could travel: `@anonN` is per-unit numbering.  The",
                  " * layout digest above is compared across every declaration, which is what",
                  " * makes spelling it out here faithful."]
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
    if dependencies:
        lines.append("")
    lines += definition(dw, canonical, name, _shared_tagger(dw), inline_anonymous=True)
    lines += ["", f"#endif /* {g} */"]
    return "\n".join(lines) + "\n"


def _index_text(names):
    """`include/types.h`: every named type, for a reader or for a source that wants them all."""
    g = _guard("DDR", "TYPES", "H")
    return "\n".join(
        ["/* Every named type the oracle recovered from orig/SLUS_207.11, one definition each.",
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
              " * included from include/types/.  `@anonN` is this unit's own numbering, so it",
              " * is named here (`anon_<N>_<unit>`) and nowhere else.",
              " */",
              f"#ifndef {g}",
              f"#define {g}"]
    if named:
        lines.append("")
        lines += [f'#include "{TYPES_DIR}/{name}.h"' for name in sorted(named)]
    if definitions:
        lines += ["", f"/* anonymous types ({len(definitions)}) */"]
        for tag, die in definitions:
            lines += ["",
                      f"/* {tag} -- {die.name}, 0x{die.attrs.get(AT_byte_size, 0):x} "
                      f"bytes, {_declared_by(die)} */"]
            lines += definition(dw, die, tag, unit.specifier)
        lines.append("")

    globals_, references = [], []
    for die in variables:
        tree = dw.type_of(die) or VOID
        location = die.attrs.get(dwarf1.AT_location)
        where = loc_str(location) if location else "?"
        if where == "@0x00000000":
            where = "not allocated"
        if tree[0] == "func":
            references.append(f"{decl(dw, tree, _name(dw, die), unit.specifier)};".ljust(64)
                              + f" /* {where} */")
        else:
            storage = "static " if die.tag == TAG_local_variable else ""
            size = dw.sizeof(tree)
            globals_.append(f"{storage}{decl(dw, tree, _name(dw, die), unit.specifier)};"
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
                lines.append(f"{prototype(dw, function, unit.specifier)};".ljust(64)
                             + f" /* {_range(dw, function)} */")
    lines += ["", f"#endif /* {g} */"]
    return "\n".join(lines) + "\n"


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
    """`{tag: text}` -- the canonical definition of every named type, for the shared tree."""
    groups = named_types(dw)
    return {name: _uppercase(_type_header(dw, name,
                                          _canonical(dw, name, groups[name]),
                                          groups[name]))
            for name in sorted(groups)}


def render(elf_path, cu_substring):
    """The C header for the translation unit whose source path contains `cu_substring`."""
    dw = dwarf(elf_path)
    return _uppercase(_unit_header(dw, _unit(dw, cu_substring)))


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

    The tree is `include/types/<tag>.h` (one named type each), `include/types.h` (all of
    them) and `include/README.md`, plus one header per translation unit under
    `include/src/`.  The return value is the unit headers -- what `./ddr oracle` counts and
    what a caller working unit by unit wants; the shared tree is written alongside them.
    """
    dw = dwarf(elf_path)
    outdir = pathlib.Path(outdir)
    types = render_types(dw)
    types_dir = outdir / TYPES_DIR
    types_dir.mkdir(parents=True, exist_ok=True)
    for name in sorted(types):
        (types_dir / f"{name}.h").write_text(types[name])
    (outdir / INDEX).write_text(_index_text(types))
    (outdir / README_NAME).write_text(README)
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


README = """# include/

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
"""


if __name__ == "__main__":
    elf = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else "include"
    units = write_all(elf, out)
    print(f"{len(units)} translation-unit headers written -> {out}")
