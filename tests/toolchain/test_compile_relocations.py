"""`compile.py`'s relocations and the symbol sets it resolves them against.

Three couplings in `tools/toolchain/compile.py` are string- and shape-level rather than
type-level, so they are pinned here rather than trusted:

* the two reasons the oracle withholds a record are read apart: "no AT_location address"
  is the only one whose value is 0 and can be placed, while "outside every declared
  segment" (an overlay reservation this layout does not model) is a refusal by design and
  is reported as one.  Both spellings are the *oracle's* own words
  (`emit_symbols.UNPLACED_REASON`, `emit_symbols.OUTSIDE_REASON`).
* a relocation resolves against the symbols the *link* knows -- the ledger, and the global
  labels of the split objects the generated ld script lists (a `func_001C43E8` has a split
  but no DWARF record, and the old ledger-only lookup refused it falsely) -- and the two
  refusal messages are distinct: an overlay address says where it lives, an unknown name
  says it has no record at all.
* a `lui`/`addiu` address pair relocates as `symbol + addend`, where the addend is the
  pair's own two halves -- `(hi << 16) + signed16(lo)` -- so a field at a constant offset
  (a non-zero high half) reads exactly like a bare symbol.  A `lui` with no `%lo` partner is
  refused with the block's name, not approximated.
"""
import json
import pathlib
import re
import struct
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))       # `toolchain.compile`
sys.path.insert(0, str(ROOT / "tools" / "oracle"))   # `emit_symbols`, the reason's owner
sys.path.insert(0, str(ROOT))                 # `config.targets`

from toolchain import compile as cc  # noqa: E402
import emit_symbols  # noqa: E402


class Symbol:
    """What `relocate` reads off a relocation's last field: its name."""

    def __init__(self, name):
        self.name = name


def config_dir(tmp_path, placed=(), unplaced=(), splits=(), data=(), placements=()):
    """A synthetic config: only the files a `Manifests` reads have to exist.

    `splits` are `(name, text)` under the code segment's split directory -- the objects the
    generated ld script lists, whose global labels are the link's own symbol set.  They are
    written under `tmp_path` on purpose: `Manifests` is given `root=tmp_path`, so a test can
    never see (or depend on) the repository's generated `asm/`.  `data` are the same, under
    `asm/data`: the data splits the link places (`g_game_w` lives in `bss.bss.s`).
    `placements` are the target's own `data_placements.txt` lines.
    """
    (tmp_path / "cus.json").write_text(json.dumps([]))
    (tmp_path / "debug_chunks.json").write_text(json.dumps([]))
    (tmp_path / "symbol_addrs.txt").write_text("".join(placed))
    (tmp_path / "unplaced_symbols.txt").write_text("".join(unplaced))
    (tmp_path / "data_placements.txt").write_text("".join(placements))
    for name, text in splits:
        path = tmp_path / "asm" / "nonmatchings" / "main" / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    for name, text in data:
        path = tmp_path / "asm" / "data" / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    return tmp_path


def manifests(tmp_path, **kwargs):
    directory = config_dir(tmp_path, **kwargs)
    target = types.SimpleNamespace(config_dir=directory,
                                  symbols=directory / "symbol_addrs.txt")
    return cc.Manifests(target, root=tmp_path)


def split(function, text):
    """A generated split's text: the label macro, then splat's per-instruction comments."""
    return f'.include "macro.inc"\nnonmatching {function}, 0x8\n\nglabel {function}\n' + text


# -- the reason string, pinned to its owner ---------------------------------------------


def test_the_no_address_reason_is_the_oracles_own_word():
    assert cc.UNPLACED_NO_ADDRESS == emit_symbols.UNPLACED_REASON
    assert cc.UNPLACED_NO_ADDRESS != emit_symbols.OUTSIDE_REASON
    # The rendered record, not only the constant: a reworded writer would keep the constant
    # and still break the read (plan, "assertions on fields can miss a broken rendering").
    rendered = emit_symbols._orphan(dict(name="mesLanguageOK", address=0, kind="obj",
                                         size=0x18, provenance="dwarf"))
    assert f"reason:{cc.UNPLACED_NO_ADDRESS}" in rendered


def test_only_the_no_address_reason_is_read_as_address_zero(tmp_path):
    m = manifests(tmp_path, unplaced=[
        "mesLanguageOK = 0x00000000; // type:obj provenance:dwarf reason:no AT_location address\n",
        "OVERLAY_THING = 0x007F0080; // type:obj provenance:dwarf "
        "reason:outside every declared segment\n",
        "mesLanguageCANCEL = 0x00000000; // type:obj provenance:dwarf "
        "reason:no AT_location address dwarf_name:renamed\n",
    ])
    assert m.symbols["mesLanguageOK"] == (0, {"provenance": "unplaced"})
    assert m.symbols["mesLanguageCANCEL"] == (0, {"provenance": "unplaced"})
    # An object outside every declared segment has a real address this layout does not
    # model: substituting 0 for it would be a guess about the overlay windows.
    assert "OVERLAY_THING" not in m.symbols


def test_the_placed_ledger_wins_over_an_unplaced_record_of_the_same_name(tmp_path):
    m = manifests(
        tmp_path,
        placed=["mesLanguage = 0x002B33C0; // type:obj size:0x18 provenance:dwarf\n"],
        unplaced=["mesLanguage = 0x00000000; // type:obj provenance:dwarf "
                  "reason:no AT_location address\n"])
    assert m.symbols["mesLanguage"] == (0x2B33C0, {"type": "obj", "size": "0x18",
                                                   "provenance": "dwarf"})


# -- the link's symbol set, which is what a relocation resolves against ------------------


def test_the_outside_reason_is_the_oracles_own_word():
    """The overlay reason is pinned to its owner, like the no-address one."""
    assert cc.UNPLACED_OUTSIDE == emit_symbols.OUTSIDE_REASON
    assert cc.UNPLACED_OUTSIDE != cc.UNPLACED_NO_ADDRESS


def test_a_split_label_the_link_places_resolves(tmp_path):
    """`func_001C43E8`: the ld script places its split object, so the link resolves it.

    It has no record in either ledger -- the oracle's DWARF never named it -- which is
    exactly the case the old lookup refused, falsely.
    """
    m = manifests(tmp_path, splits=[("func_001C43E8.s", split(
        "func_001C43E8",
        "    /* C45E8 001C43E8 90FFBD27 */  addiu      $29, $29, -0x70\n"
        "    /* C4634 001C4634 0800E003 */  jr         $31\n"))])
    assert m.address_of("func_001C43E8") == 0x001C43E8
    assert "func_001C43E8" not in m.symbols        # the oracle's ledger never names it
    assert m.placed["func_001C43E8"] == 0x001C43E8


def test_a_label_binds_to_the_instruction_that_follows_it(tmp_path):
    """A mid-split entry point resolves to its own address, not the split's."""
    m = manifests(tmp_path, splits=[("two.s", split(
        "first",
        "    /* 0 00100000 00000000 */  nop\n"
        "alabel second\n"
        "    /* 4 00100004 00000000 */  nop\n"))])
    assert m.address_of("first") == 0x100000
    assert m.address_of("second") == 0x100004


def test_the_ledger_name_wins_over_a_split_label_at_the_same_address(tmp_path):
    m = manifests(tmp_path,
                  placed=["mesLanguage = 0x002B33C0; // type:obj provenance:dwarf\n"],
                  splits=[("D_002B33C0.s", split(
                      "D_002B33C0", "    /* 0 002B33C0 00000000 */  nop\n"))])
    assert m.address_of("D_002B33C0") == 0x2B33C0
    assert m.by_address[0x2B33C0] == "mesLanguage"


def test_a_name_outside_every_declared_segment_is_refused_by_design(tmp_path):
    """`NetRouterMain` is an overlay function: it has an address, but no place here."""
    m = manifests(tmp_path, unplaced=[
        "NetRouterMain = 0x008062B0; // type:func provenance:dwarf "
        "reason:outside every declared segment\n"])
    assert "NetRouterMain" not in m.symbols        # not address 0, and not the ledger
    assert "NetRouterMain" not in m.placed
    with pytest.raises(cc.Unusable) as refusal:
        m.address_of("NetRouterMain")
    assert "outside every declared segment" in str(refusal.value)
    assert "0x008062B0" in str(refusal.value)      # the refusal names where it really lives


def test_a_name_with_no_record_at_all_is_refused_differently(tmp_path):
    """The two refusals have to be tellable apart by a reader, not both look like a bug."""
    m = manifests(tmp_path, unplaced=[
        "NetRouterMain = 0x008062B0; // type:func provenance:dwarf "
        "reason:outside every declared segment\n"])
    with pytest.raises(cc.Unusable) as outside:
        m.address_of("NetRouterMain")
    with pytest.raises(cc.Unusable) as absent:
        m.address_of("neverHeardOfIt")
    assert "outside every declared segment" in str(outside.value)
    assert "outside every declared segment" not in str(absent.value)
    assert "neverHeardOfIt" in str(absent.value)


def test_a_data_split_label_the_link_places_resolves(tmp_path):
    """`g_game_w`: no split of code defines it and the ld script assigns it nowhere.

    The link resolves it from the *data* split ``asm/data/bss.bss.s`` -- ``dlabel
    g_game_w`` over ``/* 00607A70 */ .space 0x4`` -- which is one of the objects the ld
    script lists.  That half of the link's symbol set is what a promoted unit's `%hi`/`%lo`
    against an object resolves through, so it has to be read here too.
    """
    m = manifests(tmp_path, data=[("bss.bss.s", (
        '.include "macro.inc"\n\n.section .bss, "wa"\n\n'
        "nonmatching g_game_w, 0x4\n\ndlabel g_game_w\n"
        "    /* 00607A70 */ .space 0x04\n"))])
    assert m.address_of("g_game_w") == 0x607A70
    assert m.placed["g_game_w"] == 0x607A70
    assert "g_game_w" not in m.symbols          # the ledger is not where this came from


def test_a_databin_label_without_an_address_is_not_invented(tmp_path):
    """`dlabel __comment_databin` has no address comment; the link places it by `cat` only."""
    m = manifests(tmp_path, data=[("comment.s", (
        '.include "macro.inc"\n\n.section .comment\n\n'
        'dlabel __comment_databin\n.incbin "build/assets/comment.databin.bin"\n'
        "enddlabel __comment_databin\n"))])
    assert "__comment_databin" not in m.placed
    with pytest.raises(cc.Unusable) as refusal:
        m.address_of("__comment_databin")
    assert "no record at all" in str(refusal.value)


def test_the_ledger_address_relocates_even_when_the_name_is_also_unplaced(tmp_path):
    """`g_game_w`'s pair: the ledger says where it is, so a `lui`/`addiu` pair is not zero.

    The oracle lists an object with no `AT_location` in `unplaced_symbols.txt`, and the value
    a placement reproduces for *that record* is 0.  When the same name has an address in
    `symbol_addrs.txt`, the ledger is the link's answer and the unplaced record must not win:
    filling 0 would turn an otherwise byte-equal function's `lui s8,0x60` into `lui s8,0x0`.
    """
    m = manifests(
        tmp_path,
        placed=["g_game_w = 0x00607A70; // type:obj provenance:dwarf\n"],
        unplaced=["g_game_w = 0x00000000; // type:obj provenance:dwarf "
                  "reason:no AT_location address\n"])
    data = struct.pack("<II", 0x3C1E0000, 0x27DE0000)     # lui s8,0 ; addiu s8,s8,0
    relocs = [(0, cc.R_MIPS_HI16, Symbol("g_game_w")),
              (4, cc.R_MIPS_LO16, Symbol("g_game_w"))]
    out = cc.relocate(data, relocs, lambda symbol: m.address_of(symbol.name),
                      "play_anime_step_inst.text", 0)
    assert struct.unpack_from("<I", out, 0)[0] == 0x3C1E0060     # lui s8,0x60
    assert struct.unpack_from("<I", out, 4)[0] == 0x27DE7A70     # addiu s8,s8,0x7a70


def test_a_relocation_to_a_name_with_no_record_still_refuses(tmp_path):
    """The widening is only to names the link itself resolves: an unknown one stays a gap."""
    m = manifests(tmp_path, data=[("bss.bss.s", (
        "dlabel g_game_w\n    /* 00607A70 */ .space 0x04\n"))])
    data = struct.pack("<II", 0x3C1E0000, 0x27DE0000)
    relocs = [(0, cc.R_MIPS_HI16, Symbol("neverHeardOfIt")),
              (4, cc.R_MIPS_LO16, Symbol("neverHeardOfIt"))]
    with pytest.raises(cc.Unusable) as refusal:
        cc.relocate(data, relocs, lambda symbol: m.address_of(symbol.name),
                    "somebody.text", 0)
    assert "neverHeardOfIt" in str(refusal.value)
    assert "no record at all" in str(refusal.value)


# -- the placement ledger's names -------------------------------------------------------


def test_a_literal_pool_slot_is_a_datum_the_ledger_can_place(tmp_path):
    """`@40`: Metrowerks numbers a literal the source never named.

    The object relocates against that number (the ``.debug`` record's ``AT_location``, the
    ``lui``/``%lo`` pair), so it is a datum at a retail address like any other: the ledger
    spells it and the relocation resolves instead of refusing the unit.
    """
    m = manifests(tmp_path, placements=[
        "@40 = 0x002D6D88; // size:0x5 extent:0x8 "
        "source:src/network/net_window/net_win_listdtl2.c\n"])
    assert m.address_of("@40") == 0x2D6D88
    assert m.placed["@40"] == 0x2D6D88
    assert m.by_address[0x2D6D88] == "@40"


def test_two_units_naming_one_literal_slot_resolve_to_their_own_record(tmp_path):
    """One name, two objects: `@40` is numbered per object, not shared between units.

    Measured on `net_win_listdtl2.c` and `net_win_listdtl3.c`: alike-shaped units, so both
    objects number their pool from `@40`, but retail has a separate slot for each unit's
    literal.  The ledger carries both records, the first stays the default (a unit with no
    records of its own can only be reading another unit's datum), and
    :meth:`Manifests.prefer_source` lets the unit being compiled see its own address.
    """
    m = manifests(tmp_path, placements=[
        "@40 = 0x002D6D88; // size:0x5 extent:0x8 "
        "source:src/network/net_window/net_win_listdtl2.c\n",
        "@40 = 0x002D6DA8; // size:0x5 extent:0x8 "
        "source:src/network/net_window/net_win_listdtl3.c\n",
    ])
    # The ledger's first record, unchanged: the old behaviour, and what a unit without a
    # record of its own still gets.
    assert m.address_of("@40") == 0x2D6D88
    m.prefer_source("src/network/net_window/net_win_listdtl3.c")
    assert m.address_of("@40") == 0x2D6DA8
    assert m.placed["@40"] == 0x2D6DA8
    assert m.by_address[0x2D6DA8] == "@40"
    # ...and the other unit still sees its own.
    m.prefer_source("src/network/net_window/net_win_listdtl2.c")
    assert m.address_of("@40") == 0x2D6D88
    # A unit with no records of its own changes nothing.
    m.prefer_source("src/somewhere/else.c")
    assert m.address_of("@40") == 0x2D6D88


def test_prefer_source_leaves_every_other_name_alone(tmp_path):
    """The preference is per record, not a wipe: shared data still resolves as before."""
    m = manifests(tmp_path, placements=[
        "@40 = 0x002D6D88; // size:0x5 extent:0x8 "
        "source:src/network/net_window/net_win_listdtl2.c\n",
        "g_game_w = 0x002E0000; // size:0x4 extent:0x4 "
        "source:data/bk_load_data.c\n",
    ])
    m.prefer_source("src/network/net_window/net_win_listdtl3.c")
    assert m.address_of("@40") == 0x2D6D88
    assert m.address_of("g_game_w") == 0x2E0000


def test_a_placement_name_that_is_neither_an_identifier_nor_a_slot_is_refused(tmp_path):
    """The ledger's name grammar is closed: a misspelled pool slot is a bad line, not a gap."""
    with pytest.raises(cc.Unusable) as refusal:
        manifests(tmp_path, placements=[
            "@pool = 0x002D6D88; // size:0x5 extent:0x8 source:src/x.c\n"])
    assert "data_placements.txt" in str(refusal.value)
    assert "@pool" in str(refusal.value)


def test_each_placed_datum_leaves_the_object_in_its_own_section():
    """A unit may place several data symbols; the ld script selects a section by name."""
    text = cc.assembly(0, [], b"", b"", data=[
        ("@40", b"%05d\0", (), lambda symbol: 0),
        ("@41", b"%08d\0", (), lambda symbol: 0),
        ("xxxx_bk_tm2_tbl", b"\x00\x00\x00\x00", (), lambda symbol: 0),
    ])
    assert re.findall(r"^\t\.section ([^,]+),", text, re.M) == [
        ".datum._4040", ".datum._4041", ".datum.xxxx_5fbk_5ftm2_5ftbl"]
    assert "0x64353025" in text and "0x64383025" in text


def test_the_section_encoding_cannot_collide():
    """A C identifier that spells the escape is still a different section from the slot."""
    assert cc.data_section("@40") == ".datum._4040"
    assert cc.data_section("_4040") == ".datum._5f4040"


#: The range the synthetic tests measure: the split bases above sit inside it, the overlay
#: window (`0x008062B0`) does not.
SEGMENTS = types.SimpleNamespace(loadable_vram=0x100000, bss_end=0x723700)


def link_manifests(tmp_path, syms=(), funcs=(), aliases=()):
    """A `Manifests` whose target carries the link's `-T` inputs as well."""
    directory = config_dir(tmp_path)
    (directory / "undefined_syms_auto.txt").write_text("".join(syms))
    (directory / "undefined_funcs_auto.txt").write_text("".join(funcs))
    (directory / "SLUS_211.74.ld").write_text("".join(aliases))
    target = types.SimpleNamespace(
        config_dir=directory, symbols=directory / "symbol_addrs.txt",
        undefined_syms=directory / "undefined_syms_auto.txt",
        undefined_funcs=directory / "undefined_funcs_auto.txt",
        ld_script=directory / "SLUS_211.74.ld", geometry=SEGMENTS)
    return cc.Manifests(target, root=tmp_path)


def test_a_link_assignment_inside_the_segments_resolves(tmp_path):
    """`undefined_*_auto.txt` is a linker script: what it assigns, the link resolves.

    Splat writes one for every name no split defines (`D_001158C0` is data a split reads and
    nothing labels), and an ld script alias is the same kind of assignment.
    """
    m = link_manifests(tmp_path, syms=["D_001158C0 = 0x001158C0;\n"],
                       aliases=["option_icon_tex = 0x2C0460;\n"])
    assert m.address_of("D_001158C0") == 0x1158C0
    assert m.address_of("option_icon_tex") == 0x2C0460


def test_a_link_assignment_outside_the_segments_is_refused_not_resolved(tmp_path):
    """`D_008062B0` is assigned where nothing is placed: an overlay window, not an address."""
    m = link_manifests(tmp_path, syms=["D_008062B0 = 0x008062B0;\n"])
    assert "D_008062B0" not in m.placed
    with pytest.raises(cc.Unusable) as refusal:
        m.address_of("D_008062B0")
    assert "outside every declared segment" in str(refusal.value)
    assert "undefined_syms_auto.txt" in str(refusal.value)


# -- the lui/addiu address pair ----------------------------------------------------------


def test_a_lui_addiu_pair_places_symbol_plus_the_addend():
    """`0x2B8000` keeps its low half negative, so its high half has to carry."""
    data = struct.pack("<II", 0x3C020000, 0x24420000)     # lui v0,0 ; addiu v0,v0,0
    relocs = [(0, cc.R_MIPS_HI16, Symbol("mesLanguage")),
              (4, cc.R_MIPS_LO16, Symbol("mesLanguage"))]
    out = cc.relocate(data, relocs, lambda symbol: 0x2B8000, "mesGetLanguage01.text", 0)
    assert struct.unpack_from("<I", out, 0)[0] == 0x3C02002C     # lui v0,0x2C
    assert struct.unpack_from("<I", out, 4)[0] == 0x24428000     # addiu v0,v0,-0x8000


def test_the_addend_is_the_instructions_own_sign_extended_low_half():
    data = struct.pack("<II", 0x3C020000, 0x2442FFFC)     # lui v0,0 ; addiu v0,v0,-4
    relocs = [(0, cc.R_MIPS_HI16, Symbol("mesLanguage")),
              (4, cc.R_MIPS_LO16, Symbol("mesLanguage"))]
    out = cc.relocate(data, relocs, lambda symbol: 0x2B33C0, "mesGetLanguage01.text", 0)
    assert struct.unpack_from("<I", out, 0)[0] == 0x3C02002B
    assert struct.unpack_from("<I", out, 4)[0] == 0x244233BC     # 0x2B33C0 - 4


def test_a_high_half_that_carries_a_constant_offset_is_read_off_the_pair():
    """`g_game_w.anime2_load_flg`: `lui 0xB` / `sb 0xB516` is addend `0xAB516`, not a guess.

    A field at a non-zero offset is the ordinary case this pair encodes: the compiler writes
    the *addend*'s two halves into the two instructions, so `(hi << 16) + signed16(lo)` is
    the addend and the pair relocates as `g_game_w + 0xAB516` -- retail's `lui 0x6B` /
    `sb 0x2F86`, exactly what a zero-high-half pair against the field's own address would
    give.
    """
    data = struct.pack("<II", 0x3C01000B, 0xA024B516)     # lui at,0xB ; sb a0,0xB516(at)
    relocs = [(0, cc.R_MIPS_HI16, Symbol("g_game_w")),
              (4, cc.R_MIPS_LO16, Symbol("g_game_w"))]
    out = cc.relocate(data, relocs, lambda symbol: 0x607A70,
                      "SetBeginnerFlg2p.text", 0)
    assert struct.unpack_from("<I", out, 0)[0] == 0x3C01006B     # lui at,0x6B
    assert struct.unpack_from("<I", out, 4)[0] == 0xA0242F86     # sb a0,0x2F86(at)


def test_a_lone_high_half_is_refused():
    data = struct.pack("<II", 0x3C020000, 0x00000000)
    with pytest.raises(cc.Unusable, match="lone high half"):
        cc.relocate(data, [(0, cc.R_MIPS_HI16, Symbol("mesLanguage"))],
                    lambda symbol: 0x2B33C0, "somebody.text", 0)
