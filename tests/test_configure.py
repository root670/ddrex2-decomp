"""``configure.py`` writes the *named* target's config from the *named* target's geometry.

The full run needs the target's retail ELF (gitignored, supplied by its owner) and a generated
config, so these tests drive the pieces that decide the artifacts -- the manifest checks, the
segment list, the yaml, the linker script and the ninja graph -- with a synthetic but
self-consistent geometry and a probe target.  What they assert is the retarget's whole point: the
memory of target-specific numbers lives in the descriptor, and every generated artifact is a
function of the target it was given, not of a constant in the tool.
"""

import dataclasses
import json
import pathlib
import re
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

import configure  # noqa: E402
from config import targets  # noqa: E402

TARGET = targets.get()

DEBUG_SIZE = 0x400
LINE_SIZE = 0x100


def geometry():
    """A small, self-consistent measurement: what a target's ELF has to add up to."""
    return targets.Geometry(
        elf_size=0x2000, loadable_rom=0x80, loadable_end=0x1000, loadable_vram=0x00100000,
        bss_end=0x00110000,
        trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, DEBUG_SIZE),
                  ("line", 0x1410, LINE_SIZE), ("section_headers", 0x1510, 0x2000 - 0x1510)),
        debug_size=DEBUG_SIZE, line_size=LINE_SIZE, image_elf_offset=0x92000)


def probe(**overrides):
    """A second target, described only through the descriptor's public fields."""
    fields = dict(name="probe", config_dir=ROOT / "config" / "probe",
                  elf=ROOT / "orig" / "PROBE",
                  elf_sha256="ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd",
                  image=pathlib.Path("/tmp/probe.iso"),
                  image_sha256="70a9056657665e978c7de9fc223cb753956902416418993176438316f6cd652b",
                  geometry=geometry())
    fields.update(overrides)
    return targets.Target(**fields)


def cus():
    """A two-record CU map: one translation unit and one function inside it."""
    return [
        dict(index=0, kind="tu", offset=0, size=0x200, name="probe.c",
             file="src/probe.c", low_pc=None, high_pc=None, stmt_list=None),
        dict(index=1, kind="function", offset=0x200, size=DEBUG_SIZE - 0x200, name="probe_fn",
             file="src/probe.c", low_pc=0x100000, high_pc=0x100010, stmt_list=0),
    ]


def chunks(cus_records=None):
    """The manifest for `cus()`: one `.debug` chunk per TU, one `.line` chunk per function."""
    records = cus_records if cus_records is not None else cus()
    tunits = [record["index"] for record in records]
    line_owner = next(record["index"] for record in records if record["kind"] == "function")
    return [dict(section=".debug", offset=0, size=DEBUG_SIZE, tunits=tunits),
            dict(section=".line", offset=0, size=LINE_SIZE, tunits=[line_owner])]


# ---------------------------------------------------------------------------
# the manifests: a bad one is reported, never repaired
# ---------------------------------------------------------------------------


def test_check_manifests_accepts_a_well_formed_pair():
    configure.check_manifests(cus(), chunks())


def test_a_manifest_that_does_not_cover_every_record_is_refused():
    records = cus()
    chunks_ = chunks(records)
    chunks_[0]["tunits"] = [1]                       # no longer starts at its TU
    with pytest.raises(configure.ConfigError, match="chunk"):
        configure.check_manifests(records, chunks_)
    chunks_ = chunks(records)
    chunks_.append(dict(section=".debug", offset=DEBUG_SIZE, size=0, tunits=[1]))
    with pytest.raises(configure.ConfigError):        # two .debug chunks, one TU
        configure.check_manifests(records, chunks_)


def test_the_chunk_tiling_is_checked_against_the_targets_own_section_lengths():
    geo = geometry()
    configure.check_chunk_tiling(chunks(), ".debug", 0x1010, geo.debug_size, geo)
    gapped = chunks()
    gapped[0]["size"] -= 4
    with pytest.raises(configure.ConfigError, match="0x400"):
        configure.check_chunk_tiling(gapped, ".debug", 0x1010, geo.debug_size, geo)


def test_databin_segments_cover_the_targets_file_in_order():
    geo = geometry()
    segments = configure.databin_segments(chunks(), geo)
    assert segments[0] == ("elf_header", 0, geo.loadable_rom)
    assert [name for name, _, _ in segments] ==         ["elf_header", "shstrtab", ".debug_000", ".line_000", "section_headers"]
    # The loadable image is the code segment, so the databins after `elf_header` run from
    # `loadable_end` to the end of the file -- together with the code they are the whole file.
    assert segments[1][1] == geo.loadable_end
    assert geo.loadable_end + sum(size for _, _, size in segments[1:]) == geo.elf_size
    offsets = [offset for _, offset, _ in segments]
    assert offsets == sorted(offsets)


# ---------------------------------------------------------------------------
# the generated artifacts name the target they were generated for
# ---------------------------------------------------------------------------


def test_the_yaml_names_the_target_and_its_paths():
    target = probe()
    yaml_text = configure.splat_yaml(chunks(), target)
    assert f"target {target.name}" in yaml_text
    assert f"  basename: {target.elf.name}\n" in yaml_text
    assert f"  target_path: orig/{target.elf.name}\n" in yaml_text
    assert f"  ld_script_path: build/{target.elf.name}.ld\n" in yaml_text
    assert f"  symbol_addrs_path: config/{target.name}/splat_symbol_addrs.txt\n" in yaml_text
    assert f"  start: 0x{target.geometry.loadable_rom:X}\n" in yaml_text
    assert f"  vram: 0x{target.geometry.bss_vram:X}\n" in yaml_text


def test_the_linker_script_pins_the_targets_geometry():
    target = probe()
    geo = target.geometry
    script = configure.pinned_ld_script([], [], [], target, geo)
    assert f"orig/{target.elf.name}" in script
    assert f".{geo.code_segment} 0x{geo.loadable_vram:X} : AT(0x{geo.loadable_rom:X})" in script
    assert f"SIZEOF(.{geo.code_segment}) == 0x{geo.code_size:X}" in script
    assert f".bss 0x{geo.bss_vram:X} (NOLOAD)" in script
    assert f"SIZEOF(.bss) == 0x{geo.bss_size:X}" in script


def test_the_ninja_graph_names_the_target_on_every_edge_that_reads_it():
    """The compiler, the linker and the gate each read a target's files: the graph says which."""
    target = probe()
    geo = target.geometry
    databins = configure.databin_segments(chunks(), geo)
    ninja = configure.ninja_text([], databins, False, [], target, geo)
    assert f"python3 tools/toolchain/compile.py --target {target.name}" in ninja
    assert f"python3 tools/verify/g1.py --target {target.name}" in ninja
    assert f"-T config/{target.name}/undefined_syms_auto.txt" in ninja
    assert f"-T config/{target.name}/undefined_funcs_auto.txt" in ninja
    assert f"build out/{target.elf.name}.elf: ld build/{target.elf.name}.ld" in ninja
    assert f"build out/{target.elf.name}: cat" in ninja
    assert f"build g1: g1 out/{target.elf.name} | orig/{target.elf.name}" in ninja


# ---------------------------------------------------------------------------
# the target has to be real before anything is written
# ---------------------------------------------------------------------------


def test_configure_refuses_a_target_whose_geometry_is_unmeasured(tmp_path, capsys, monkeypatch):
    """A target nobody has measured: the config is generated from the binary, so neither the
    segment list nor the pipeline can be guessed -- and nothing is written on the way out."""
    unmeasured = dataclasses.replace(targets.get(), geometry=None)
    monkeypatch.setattr(configure.targets, "get", lambda name=None: unmeasured)
    yaml_path = unmeasured.config_dir / "splat.yaml"
    before = yaml_path.read_bytes() if yaml_path.exists() else None
    status = configure.main(["--target", targets.DEFAULT])
    err = capsys.readouterr().err
    assert status == 2
    assert "geometry" in err and targets.DEFAULT in err and "Traceback" not in err
    assert (yaml_path.read_bytes() if yaml_path.exists() else None) == before


def test_an_unknown_target_is_a_configuration_error_not_a_traceback(capsys):
    status = configure.main(["--target", "usam2"])
    err = capsys.readouterr().err
    assert status == 2
    assert "usam2" in err and targets.DEFAULT in err and "Traceback" not in err


# ---------------------------------------------------------------------------
# the helpers every generated artefact is made of
# ---------------------------------------------------------------------------


def test_splat_symbols_rewrites_attributes_the_way_splat_reads_them():
    """splat reads `key:value` as an attribute and rejects unknown ones, so provenance becomes
    `key=value`, and a zero size is dropped (it suppresses function detection outright)."""
    text = ("probe_one = 0x00100000; // type:func size:0x10 provenance:ghidra dwarf_name:x\n"
            "probe_obj = 0x00100040; // type:obj size:0x0 provenance:ghidra\n")
    out = configure.splat_symbols(text)
    assert "probe_one = 0x00100000; // type:func size:0x10 provenance=ghidra dwarf_name=x" in out
    assert "probe_obj = 0x00100040; // type:label provenance=ghidra" in out
    assert "size:0x0" not in out and "provenance:ghidra" not in out
    with pytest.raises(configure.ConfigError, match="symbol_addrs.txt line 1"):
        configure.splat_symbols("not a symbol line\n")


def test_two_names_that_differ_only_in_case_get_distinct_split_paths():
    """splat names a split file after its symbol, and one filesystem cannot hold both spellings.

    Measured on this target: `Tr_load_seq_th` (0x0027FC90, 0x68 B) and `tr_load_seq_th`
    (0x0027FD00, 0x1F0 B) are two functions whose names differ only in case, so splat wrote
    one split and the second write replaced it -- the link then came up 0x70 bytes short of
    the retail image's 1,958,272.  The `filename:` attribute disambiguates the *path* (splat
    splits an attribute on its colon); the symbol name, and so the label inside the split,
    stays the DWARF's own.
    """
    text = ("Tr_load_seq_th = 0x0027FC90; // type:func size:0x68 provenance:dwarf\n"
            "tr_load_seq_th = 0x0027FD00; // type:func size:0x1F0 provenance:dwarf\n"
            "beside_them = 0x0027FEF0; // type:func size:0x10 provenance:dwarf\n")
    out = configure.splat_symbols(text)
    assert "filename:Tr_load_seq_th_0027FC90" in out
    assert "filename:tr_load_seq_th_0027FD00" in out
    assert "filename:" not in [line for line in out.splitlines()
                              if line.startswith("beside_them")][0], \
        "a name nobody shares keeps its own path"
    assert "Tr_load_seq_th = 0x0027FC90;" in out, "the symbol name is evidence: unchanged"
    assert configure.case_collisions([("a", "0x1"), ("A", "0x2"), ("b", "0x3")]) == {"a", "A"}


SOURCES = {
    "asm/nonmatchings/main/a.s": "glabel a\n/* 0 00100000 00000000 */\n.L00100010\nnamed\n",
    "asm/nonmatchings/main/b.s": "glabel b\n/* 0 00100010 00000000 */\n.L00100010\nD_00100020\n",
}


def test_link_aliases_defines_only_the_names_nothing_defines(tmp_path):
    """A cross-split reference to a local label, an undefined `D_` name, and a named symbol some
    split mentions: each encodes its own address, so each becomes a linker-script assignment --
    and a name splat already resolved is left to splat."""
    symbols = tmp_path / "symbol_addrs.txt"
    symbols.write_text("named = 0x00100030;  // type:func\n")
    assert dict(configure.link_aliases(SOURCES, symbols, [])) == {
        ".L00100010": 0x00100010, "D_00100020": 0x00100020, "named": 0x00100030}
    auto = tmp_path / "undefined_funcs_auto.txt"
    auto.write_text("D_00100020 = 0x00100020;\n")
    assert dict(configure.link_aliases(SOURCES, symbols, [auto])) == {
        ".L00100010": 0x00100010, "named": 0x00100030}


def test_tail_inputs_substitutes_a_promotions_payloads_by_name():
    import types
    databins = [("elf_header", 0, 0x80), ("shstrtab", 0x1000, 0x10),
                (".debug_000", 0x1010, 0x400), (".line_000", 0x1410, 0x100)]
    promotion = types.SimpleNamespace(debug_payload="build/x.o.debug",
                                      debug_databin=".debug_000",
                                      line_payload="build/x.o.line",
                                      line_databins=[".line_000"])
    assert configure.tail_inputs(databins, [promotion]) == [
        "build/assets/shstrtab.databin.bin", "build/x.o.debug", "build/x.o.line"]
    assert configure.tail_inputs(databins, []) == [
        f"build/assets/{name}.databin.bin" for name in ("shstrtab", ".debug_000", ".line_000")]


def test_objdiff_json_lists_every_linked_object_under_the_targets_segment():
    target = probe()
    code = [(target.geometry.loadable_vram, "asm/nonmatchings/main/a.s")]
    project = json.loads(configure.objdiff_json(code, [], target.geometry))
    assert project["custom_make"] == "ninja" and project["min_version"]
    unit = project["units"][0]
    assert unit["name"] == f"{target.geometry.code_segment}/a"
    assert unit["target_path"].endswith("a.s.o") and unit["base_path"] is None


def test_write_if_different_leaves_an_identical_file_alone(tmp_path):
    path = tmp_path / "generated"
    configure.write_if_different(path, "one\n")
    stamp = path.stat().st_mtime_ns
    configure.write_if_different(path, "one\n")
    assert path.read_text() == "one\n" and path.stat().st_mtime_ns == stamp
    configure.write_if_different(path, "two\n")
    assert path.read_text() == "two\n"


def test_the_object_graph_stops_before_the_link():
    """`--objects` is the objdiff job's target: objects only, no link, no gate, no image."""
    target = probe()
    ninja = configure.ninja_text([], configure.databin_segments(chunks(), target.geometry),
                                 True, [], target, target.geometry)
    assert "default objects" in ninja
    assert "build g1:" not in ninja and "build out/" not in ninja
    assert "rule ld" in ninja                      # the rule exists; no edge uses it


def test_the_yaml_asks_splat_for_a_byte_exact_split():
    """The settings the G1-proven split depends on: no input alignment, numeric registers,
    no dropped function tails, and the R5900 register aliases in the generated macro."""
    text = configure.splat_yaml(chunks(), probe())
    assert "  subalign: 1\n" in text
    assert "  named_regs_for_c_funcs: false\n" in text
    assert "  detect_redundant_function_end: false\n" in text
    assert "macro.inc" in text and "set noat" in text and "set noreorder" in text
    for alias in ("ACC", "Q", "I"):
        assert f"    .set {alias}, ${alias}\n" in text


def test_the_linker_script_lists_its_inputs_in_address_order():
    target = probe()
    code = [(0x100010, "asm/nonmatchings/main/b.s"), (0x100000, "asm/nonmatchings/main/a.s")]
    script = configure.pinned_ld_script(code, [], [], target, target.geometry)
    listed = re.findall(r"^\s+(\S+)\(\.text\)$", script, re.M)
    assert listed == ["build/asm/nonmatchings/main/a.s.o",
                      "build/asm/nonmatchings/main/b.s.o"]
    ambiguous = [(0x100000, "asm/nonmatchings/main/a.s"),
                 (0x100000, "asm/nonmatchings/main/b.s")]
    with pytest.raises(configure.ConfigError, match="ambiguous"):
        configure.pinned_ld_script(ambiguous, [], [], target, target.geometry)


def test_code_splits_reads_each_splits_own_address_comment():
    geo = geometry()
    good = {"asm/nonmatchings/main/a.s": "/* 80 00100000 00000000 */\nglabel a\n"}
    assert configure.code_splits(good, geo) == [(0x100000, "asm/nonmatchings/main/a.s")]
    with pytest.raises(configure.ConfigError, match="file offset"):
        configure.code_splits(
            {"asm/nonmatchings/main/a.s": "/* 84 00100000 00000000 */\n"}, geo)
    with pytest.raises(configure.ConfigError, match="no address comment"):
        configure.code_splits({"asm/nonmatchings/main/a.s": "glabel a\n"}, geo)
    with pytest.raises(configure.ConfigError, match="no code splits"):
        configure.code_splits({}, geo)


def test_promotions_refuses_a_table_entry_whose_source_is_gone():
    """A `tu_builds` pair whose source no longer exists is a configuration error, not a silently
    unchanged image (the same rule in the other direction is what keeps a promoted unit honest)."""
    unbuilt = probe(tu_builds=(("src/nothing.c", "3.0-011126", "-c -g"),))
    manifests = type("M", (), {"tu_files": lambda self: {"src/nothing.c"}})()
    with pytest.raises(configure.ConfigError, match="no source under src/"):
        configure.promotions(manifests, unbuilt)


def test_the_registered_targets_promotions_agree_with_its_sources():
    """Whatever the target lists is exactly what `src/` provides -- today, nothing."""
    if not TARGET.cus.is_file():
        pytest.skip(f"{TARGET.name}: its config is generated in Task 4")
    promoted = configure.promotions(target=TARGET)
    present = {path.relative_to(ROOT).as_posix() for path in (ROOT / "src").rglob("*.c")}
    assert {promotion.file for promotion in promoted} == present


def test_load_json_stops_on_a_missing_or_broken_manifest(tmp_path):
    """A manifest that is not there, or is not JSON, is a configuration error naming the file --
    reported before anything is written, never repaired and never defaulted."""
    missing = tmp_path / "cus.json"
    with pytest.raises(configure.ConfigError, match="cus.json not found"):
        configure.load_json(missing, "cus.json")
    broken = tmp_path / "debug_chunks.json"
    broken.write_text("{not json")
    with pytest.raises(configure.ConfigError, match="not valid JSON"):
        configure.load_json(broken, "debug_chunks.json")
    good = tmp_path / "cus.json"
    good.write_text('[{"index": 0, "kind": "tu"}]\n')
    assert configure.load_json(good, "cus.json") == [{"index": 0, "kind": "tu"}]


def test_a_configuration_that_cannot_be_placed_writes_nothing(monkeypatch, capsys):
    """`configure()` reads its manifests *before* it writes anything: a missing one leaves the
    target's config and the graph untouched (the generator never half-lands)."""
    target = targets.get()
    before = {path: path.read_text() for path in (target.splat_symbols, target.undefined_syms)
              if path.is_file()}
    status = configure.main(["--target", target.name, "--cus", "/nonexistent/cus.json"])
    err = capsys.readouterr().err
    assert status == 2 and "cus.json not found" in err and "Traceback" not in err
    assert {path: path.read_text() for path in before} == before
