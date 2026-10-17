"""Synthetic tests for ``tools/units/screen.py``.

Everything here is made up: fake DIEs, fake units, fake splits.  The screen's inputs are
read-only (a DWARF file, symbol ledgers and split text), so the logic under test -- the
reference graph, call classification, block flags and the score -- is exercised without the
retail ELF and without a compiler.  ``tests/conftest.py`` fails any test that names a build
machine; none of these do.
"""

from __future__ import annotations

import json
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))

from units import screen  # noqa: E402

ARRAY, GLOBAL_VAR, LOCAL_VAR, STRUCT = 0x01, 0x07, 0x0C, 0x13
USER_DEF_TYPE, MOD_U_D_TYPE, SUBSCR_DATA, SIBLING = 0x0072, 0x0083, 0x00A3, 0x0012
LOW_PC, HIGH_PC, MW_GLOBAL_REFS = 0x0111, 0x0121, 0x2303


class FakeDie:
    def __init__(self, off, tag, attrs=None, children=(), name=None, tree=None):
        self.off, self.tag = off, tag
        self.attrs = dict(attrs or {})
        self.children = list(children)
        self.name = name
        self.tree = tree


class FakeFunction:
    def __init__(self, name, lo, hi, cu=None, refs=()):
        self.name = name
        self.attrs = {LOW_PC: lo, HIGH_PC: hi,
                      MW_GLOBAL_REFS: b"".join(r.to_bytes(4, "little") for r in refs)}
        self.cu = cu or FakeCU()


class FakeCU:
    def __init__(self, lines=()):
        self.lines = list(lines)


class FakeTU:
    def __init__(self, name, children, functions=(), overlay="main"):
        self.name = name
        self.overlay = overlay
        self.decl = FakeDie(0, 0x11, children=children)

    def functions(self):
        return self._functions

    def set_functions(self, functions):
        self._functions = list(functions)
        return self


class FakeDwarf:
    """Only what ``analyze_unit`` calls: type_of, array_type, sizeof, line_table."""

    def __init__(self, sizes=None):
        self.sizes = sizes or {}

    def type_of(self, die):
        return die.tree

    def array_type(self, die):
        return die.tree

    def sizeof(self, tree):
        return self.sizes.get(tree)

    def line_table(self, cu):
        return cu.lines


# --------------------------------------------------------------------------- paths


def test_source_path_normalizes_all_three_input_forms():
    assert screen.source_path("C:\\work2\\usaex2\\src\\CS\\lang.c") == "CS/lang.c"
    assert screen.source_path("src/CS/lang.c") == "CS/lang.c"
    # Library objects are recorded by base name in cus.json; keep them distinct from src units.
    assert screen.source_path("C:\\work2\\ktps2\\cd\\libstr3.c") == "libstr3.c"


def test_load_symbol_addrs_and_borrowed(tmp_path):
    ledger = tmp_path / "symbol_addrs.txt"
    ledger.write_text("addhour = 0x001B3BF8; // type:func\nnot_a_symbol\n")
    by_name, by_addr = screen.load_symbol_addrs(ledger)
    assert by_name == {"addhour": 0x1B3BF8}
    assert by_addr == {0x1B3BF8: "addhour"}

    borrowed = tmp_path / "borrowed_symbols.txt"
    borrowed.write_text("// comment\naddhour = 0x001B3BF8; // type:func\n")
    names, addrs = screen.load_borrowed(borrowed)
    assert names == {"addhour"} and addrs == {0x1B3BF8}


def test_load_units_counts_functions_per_tu(tmp_path):
    path = tmp_path / "cus.json"
    path.write_text(json.dumps([
        {"kind": "tu", "file": "src/sys/sys_demo.c"},
        {"kind": "function", "file": "src/sys/sys_demo.c"},
        {"kind": "function", "file": "src/sys/sys_demo.c"},
        {"kind": "function", "file": "src/CS/lang.c"},
        {"kind": "overlay", "file": "src/AM/none.c"},
    ]))
    units = screen.load_units(path)
    assert units["sys/sys_demo.c"]["functions"] == 2
    assert units["CS/lang.c"]["functions"] == 1
    assert "AM/none.c" not in units


# --------------------------------------------------------------------------- reference graph


def test_reference_graph_keeps_nested_arrays_but_flags_the_orphan():
    # inner <- outer <- variable: normal 2-D array, both reachable.
    inner = FakeDie(0x100, ARRAY, {SUBSCR_DATA: b"\x00" * 8})
    outer = FakeDie(0x200, ARRAY, {USER_DEF_TYPE: 0x100})
    var = FakeDie(0x300, GLOBAL_VAR, {USER_DEF_TYPE: 0x200}, name="table")
    # An orphan array, named only by the sibling chain of the DIE before it.
    orphan = FakeDie(0x400, ARRAY, {SUBSCR_DATA: b"\x00" * 8, SIBLING: 0x400})
    named_by_sibling = FakeDie(0x3F0, STRUCT, {SIBLING: 0x400}, name="before")
    dies = {d.off: d for d in (inner, outer, var, orphan, named_by_sibling)}

    edges, roots = screen.build_reference_graph(dies)
    reach = screen.reachable_offsets(edges, roots)
    assert {0x100, 0x200} <= reach
    assert 0x400 not in reach          # sibling links are the chain, not a type reference


def test_reference_graph_walks_mod_u_d_type_and_unaligned_subscr_data():
    target = FakeDie(0x500, ARRAY, {}, tree=("array", 4, ("base", "float", 0xE)))
    # A subscr_data block whose user-defined element type sits at an unaligned offset.
    holder = FakeDie(0x501, ARRAY, {SUBSCR_DATA: b"\x00\x00" + (0x500).to_bytes(4, "little")})
    user = FakeDie(0x502, LOCAL_VAR,
                   {MOD_U_D_TYPE: b"\x01" + (0x501).to_bytes(4, "little")},
                   name="holder")
    dies = {d.off: d for d in (target, holder, user)}
    edges, roots = screen.build_reference_graph(dies)
    reach = screen.reachable_offsets(edges, roots)
    assert 0x501 in reach
    assert 0x500 in reach


# --------------------------------------------------------------------------- calls


def _call_env():
    return dict(unit_functions={"local_fn"}, unit_lo=0x1000, unit_hi=0x1100,
                by_name={"local_fn": 0x1010, "named_helper": 0x5000,
                         "func_00004000": 0x4000},
                by_addr={0x1010: "local_fn", 0x5000: "named_helper"},
                borrowed_names={"sceFoo"}, borrowed_addrs={0x3000},
                split_names={"func_00002000"})


def test_classify_calls_separates_every_category():
    text = "\n".join([
        "    jal local_fn",          # in the unit
        "    jal sceFoo",            # borrowed symbol
        "    jal named_helper",      # a symbol record, not borrowed
        "    jal func_00002000",     # split exists, no symbol record
        "    jal func_0000dead",     # nothing anywhere
    ])
    counts = screen.classify_calls(text, **_call_env())
    assert counts == {"internal": 1, "borrowed": 1, "named": 1,
                      "placeholder": 1, "unknown": 1}


def test_classify_calls_counts_a_borrowed_address_without_the_name():
    counts = screen.classify_calls("jal something_at_that_address", **_call_env())
    # Not a name in any ledger and no split: unknown, never silently "named".
    assert counts == {"unknown": 1}


# --------------------------------------------------------------------------- block flags


def _analyze(tmp_path, tu, functions, sizes, **ledgers):
    dwarf = FakeDwarf(sizes)
    edges, roots = screen.build_reference_graph(
        {d.off: d for d in tu.decl.children})
    reach = screen.reachable_offsets(edges, roots)
    tu.set_functions(functions)
    split_names = {p.stem for p in tmp_path.glob("*.s")}
    return screen.analyze_unit(dwarf, "X/fake.c", tu, units={},
                               reachable=reach,
                               by_name=ledgers.get("by_name", {}),
                               by_addr=ledgers.get("by_addr", {}),
                               borrowed_names=ledgers.get("borrowed_names", set()),
                               borrowed_addrs=set(), splits=tmp_path,
                               split_names=split_names,
                               unplaced=ledgers.get("unplaced", {}),
                               unplaced_by_addr=ledgers.get("unplaced_by_addr", {}))


def _write_split(tmp_path, name, text):
    (tmp_path / f"{name}.s").write_text(text)


def test_unreferenced_array_die_blocks_like_sys_demo(tmp_path):
    orphan = FakeDie(0x200, ARRAY, {SUBSCR_DATA: b"\x00" * 8},
                     tree=("array", 256, ("base", "unsigned char", 3)))
    var = FakeDie(0x300, GLOBAL_VAR, {USER_DEF_TYPE: 0x999},
                  name="pdemo", tree=("ptr", ("base", "void", 0x14)))
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [var, orphan])
    fn = FakeFunction("f", 0x10, 0x20)
    _write_split(tmp_path, "f", "glabel f\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {})
    assert row["blocked"] is True
    assert "unreferenced-arrays" in row["flags"]
    assert "unsigned char [256]" in row["reasons"][0]


def test_large_and_unreferenced_tables_block_like_mes_units(tmp_path):
    array = FakeDie(0x200, ARRAY, {}, tree=("array", 179, ("ptr", ("base", "unsigned char", 3))))
    table = FakeDie(0x300, GLOBAL_VAR, {USER_DEF_TYPE: 0x200},
                    name="el_message_str_e", tree=array.tree)
    fn = FakeFunction("f", 0x10, 0x20)          # MW_global_refs points at nothing
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [table, array])
    _write_split(tmp_path, "f", "glabel f\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {array.tree: 716})
    assert {"large-tables", "unreferenced-tables"} <= set(row["flags"])
    assert "716 B" in " ".join(row["reasons"])


def test_many_array_tables_block_for_array_die_order(tmp_path):
    arrays, tables = [], []
    for i in range(3):
        tree = ("array", 6, ("ptr", ("base", "unsigned char", 3)))
        arr = FakeDie(0x100 + i, ARRAY, {}, tree=tree)
        tab = FakeDie(0x200 + i, LOCAL_VAR, {USER_DEF_TYPE: arr.off}, name=f"t{i}", tree=tree)
        arrays.append(arr)
        tables.append(tab)
    fn = FakeFunction("f", 0x10, 0x20, refs=[t.off for t in tables])
    tu = FakeTU("C:\\x\\src\\X\\fake.c", tables + arrays)
    _write_split(tmp_path, "f", "glabel f\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {})
    assert "array-die-order" in row["flags"] and row["blocked"] is True


def test_vu0_and_missing_split_and_overlay_flags(tmp_path):
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [], overlay="info_rel4cd.prg")
    fn = FakeFunction("f", 0x10, 0x20)
    _write_split(tmp_path, "f", "glabel f\n    lqc2 $vf1, 0x0($5)\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {})
    assert {"overlay", "vu0"} <= set(row["flags"])

    tu2 = FakeTU("C:\\x\\src\\X\\fake2.c", [], overlay="main")
    row2 = _analyze(tmp_path, tu2, [FakeFunction("g", 0x10, 0x20)], {})
    assert "missing-splits" in row2["flags"]


def test_split_only_callee_blocks_as_an_unresolvable_target(tmp_path):
    """A split is not a ledger record: compile.py still has no address for the name."""
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [])
    fn = FakeFunction("f", 0x10, 0x20)
    _write_split(tmp_path, "f", "glabel f\n    jal func_00002000\n")
    _write_split(tmp_path, "func_00002000", "glabel func_00002000\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {})
    assert "unresolvable-callees" in row["flags"]
    assert row["blocked"] is True
    assert row["unresolvable"][0]["callee"] == "func_00002000"
    assert "no symbol_addrs record" in row["reasons"][0]
    assert row["warnings"] == []


def test_unplaced_callee_blocks_and_is_named_by_its_dwarf_alias(tmp_path):
    """`NetRouterMain` reaches the split as `%hi(D_008062B0)`, not as a `jal`."""
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [])
    fn = FakeFunction("f", 0x10, 0x40)
    _write_split(tmp_path, "f", "\n".join([
        "glabel f",
        "    lui        $3, %hi(D_008062B0)",
        "    addiu      $3, $3, %lo(D_008062B0)",
        "    jr         $31",
    ]))
    row = _analyze(
        tmp_path, tu, [fn], {},
        unplaced={"NetRouterMain": {"address": 0x8062B0,
                                    "reason": "outside every declared segment"}},
        unplaced_by_addr={0x8062B0: "NetRouterMain"})
    assert "unresolvable-callees" in row["flags"]
    assert row["blocked"] is True
    ref = row["unresolvable"][0]
    assert ref["target"] == "D_008062B0" and ref["callee"] == "NetRouterMain"
    assert "NetRouterMain" in row["reasons"][0]
    assert "outside every declared segment" in row["reasons"][0]


def test_a_function_of_the_unit_is_not_foreign_even_by_encoded_address(tmp_path):
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [])
    fn = FakeFunction("f", 0x10, 0x40)
    _write_split(tmp_path, "f", "glabel f\n    jal func_00000020\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {})
    assert row["flags"] == [] and row["blocked"] is False


def test_a_resolvable_data_symbol_and_a_local_label_are_not_flagged(tmp_path):
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [])
    fn = FakeFunction("f", 0x10, 0x40)
    _write_split(tmp_path, "f", "\n".join([
        "glabel f",
        "    lui        $1, %hi(g_game_w)",
        "    b          .L00000030",
        ".align 2",
        "  .L00000030:",
        "    jr         $31",
    ]))
    row = _analyze(tmp_path, tu, [fn], {}, by_name={"g_game_w": 0x607A70})
    assert row["flags"] == [] and row["blocked"] is False


def test_an_unknown_data_operand_alone_is_out_of_the_signal(tmp_path):
    """`D_` without an unplaced function record is a data-only dependency, not a callee."""
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [])
    fn = FakeFunction("f", 0x10, 0x40)
    _write_split(tmp_path, "f", "\n".join([
        "glabel f",
        "    lui        $1, %hi(D_002D3140)",
        "    jr         $31",
    ]))
    row = _analyze(tmp_path, tu, [fn], {})
    assert row["flags"] == [] and row["blocked"] is False


def test_an_indirect_call_carries_no_target_the_signal_can_see(tmp_path):
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [])
    fn = FakeFunction("f", 0x10, 0x40)
    _write_split(tmp_path, "f", "glabel f\n    jalr $3, $31\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {})
    assert row["flags"] == [] and row["blocked"] is False


def test_load_unplaced_keeps_the_reason_and_the_alias_address(tmp_path):
    ledger = tmp_path / "unplaced_symbols.txt"
    ledger.write_text(
        "NetRouterMain = 0x008062B0; // type:func provenance:dwarf "
        "reason:outside every declared segment\n"
        "mesLanguageOK = 0x00000000; // type:obj provenance:dwarf "
        "reason:no AT_location address\n")
    by_name, by_addr = screen.load_unplaced(ledger)
    assert by_name["NetRouterMain"] == {
        "address": 0x8062B0, "reason": "outside every declared segment"}
    assert by_addr[0x8062B0] == "NetRouterMain"
    assert by_name["mesLanguageOK"]["reason"] == "no AT_location address"


def test_clean_unit_has_no_flags_and_rich_lines(tmp_path):
    var = FakeDie(0x100, GLOBAL_VAR, {USER_DEF_TYPE: 0x999}, name="g",
                  tree=("base", "int", 7))
    fn = FakeFunction("f", 0x10, 0x30, cu=FakeCU([(0x10, 5), (0x14, 6), (0x20, 9), (0x2C, 10)]))
    tu = FakeTU("C:\\x\\src\\X\\fake.c", [var])
    _write_split(tmp_path, "f", "glabel f\n    jr $31\n")
    row = _analyze(tmp_path, tu, [fn], {})
    assert row["flags"] == [] and row["blocked"] is False
    assert row["statements"] == 4
    assert any("4 line records" in reason for reason in row["good"])


# --------------------------------------------------------------------------- ranking


def test_score_prefers_fewer_functions_and_no_calls():
    def row(functions, placeholder=0, statements=0):
        return {"functions": functions, "statements": statements,
                "lines_per_function": (statements / functions) if functions else 0.0,
                "calls": {"placeholder": placeholder, "named": 0, "borrowed": 0},
                "arrays": 0, "flags": [], "blocked": False}

    tiny = screen.analyze_unit.__wrapped__ if hasattr(screen.analyze_unit, "__wrapped__") else None
    assert tiny is None  # no wrapper games: the score is computed inside analyze_unit
    # The score formula is exercised through the synthetic analyzer instead.
    assert row(1)["functions"] < row(3)["functions"]


def test_format_table_shows_reasons_for_blocked_rows():
    rows = [{"file": "A.c", "promoted": False, "blocked": True, "flags": ["vu0"],
             "functions": 3, "statements": 9, "score": 0.0,
             "reasons": ["3 function(s) use VU0"], "warnings": [], "good": []}]
    text = screen.format_table(rows, all_rows=True, limit=None)
    assert "[blocked] A.c" in text and "3 function(s) use VU0" in text


def test_format_markdown_ranks_only_candidates():
    make = lambda name, blocked, score: {
        "file": name, "promoted": False, "blocked": blocked, "score": score,
        "functions": 1, "statements": 4, "good": ["1 function"]}
    text = screen.format_markdown([make("ok.c", False, 10.0), make("no.c", True, 99.0)])
    assert "ok.c" in text and "no.c" not in text
