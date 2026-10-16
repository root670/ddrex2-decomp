"""`compile.py`'s relocations and the one unplaced record it may read as address 0.

Two couplings in `tools/toolchain/compile.py` are string- and shape-level rather than
type-level, so they are pinned here rather than trusted:

* the reason the placement treats as "retail gives this object no address" is the *oracle's*
  own word for it (`emit_symbols.UNPLACED_REASON`).  A rewording on either side would silently
  stop the substitution -- a unit would fail to place for a name the symbol file has no address
  for, or worse, address 0 would come from the *other* reason, whose objects have real
  addresses in the overlay reservations this layout does not model.
* a `lui`/`addiu` address pair relocates as `symbol + addend`, where the addend is the
  *instruction's* own sign-extended low half.  A pair split any other way is refused with the
  block's name, not approximated.
"""
import json
import pathlib
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


def config_dir(tmp_path, placed=(), unplaced=()):
    """A synthetic config: only the three files a `Manifests` reads have to exist."""
    (tmp_path / "cus.json").write_text(json.dumps([]))
    (tmp_path / "debug_chunks.json").write_text(json.dumps([]))
    (tmp_path / "symbol_addrs.txt").write_text("".join(placed))
    (tmp_path / "unplaced_symbols.txt").write_text("".join(unplaced))
    return tmp_path


def manifests(tmp_path, **kwargs):
    directory = config_dir(tmp_path, **kwargs)
    target = types.SimpleNamespace(config_dir=directory,
                                  symbols=directory / "symbol_addrs.txt")
    return cc.Manifests(target)


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


def test_a_high_half_that_already_carries_a_constant_is_refused_not_approximated():
    data = struct.pack("<II", 0x3C02002B, 0x24420000)     # a split this build cannot read
    relocs = [(0, cc.R_MIPS_HI16, Symbol("mesLanguage")),
              (4, cc.R_MIPS_LO16, Symbol("mesLanguage"))]
    with pytest.raises(cc.Unusable, match="mesGetLanguage01.text"):
        cc.relocate(data, relocs, lambda symbol: 0x2B33C0, "mesGetLanguage01.text", 0)


def test_a_lone_high_half_is_refused():
    data = struct.pack("<II", 0x3C020000, 0x00000000)
    with pytest.raises(cc.Unusable, match="lone high half"):
        cc.relocate(data, [(0, cc.R_MIPS_HI16, Symbol("mesLanguage"))],
                    lambda symbol: 0x2B33C0, "somebody.text", 0)
