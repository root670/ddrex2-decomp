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
import shutil
import struct
import subprocess
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

import configure  # noqa: E402
from config import targets  # noqa: E402

sys.path.insert(0, str(ROOT / "tools" / "oracle"))   # the reader the emitted object is checked with
import elf  # noqa: E402

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


def test_a_data_only_promotion_contributes_no_text_and_no_line_edge():
    """A declaration-only unit has no code for the ld script (its datum arrives through the
    ledger) and no ``.line`` section to dump: an ``objcopy --dump-section`` edge for one would
    fail on a section the object does not carry."""
    import types
    target = probe()
    data_only = types.SimpleNamespace(
        address=0x00100010, object="build/src/data.c.o", code=False, splits=set(),
        module="main", is_overlay=False,
        file="src/data.c", flags="--compiler 3.0 -g --adopt-retail-meta",
        debug_payload="build/src/data.c.o.debug",
        line_payload="build/src/data.c.o.line",
        debug_databin=".debug_000", line_databins=[])
    script = configure.pinned_ld_script([], [], [data_only], target, target.geometry)
    assert "build/src/data.c.o" not in script

    databins = configure.databin_segments(chunks(), target.geometry)
    ninja = configure.ninja_text([], databins, False, [data_only], target, target.geometry)
    assert "build build/src/data.c.o.debug: objsec build/src/data.c.o" in ninja
    assert "build/src/data.c.o.line" not in ninja


def test_the_ninja_graph_names_the_target_on_every_edge_that_reads_it():
    """The compiler, the linker and the gate each read a target's files: the graph says which."""
    target = probe()
    geo = target.geometry
    databins = configure.databin_segments(chunks(), geo)
    ninja = configure.ninja_text([], databins, False, [], target, geo)
    assert f'"$python" tools/toolchain/compile.py --target {target.name}' in ninja
    assert f'"$python" tools/verify/g1.py --target {target.name}' in ninja
    assert f"-T config/{target.name}/undefined_syms_auto.txt" in ninja
    assert f"-T config/{target.name}/undefined_funcs_auto.txt" in ninja
    assert f"build out/{target.elf.name}.elf: ld build/{target.elf.name}.ld" in ninja
    assert f"build out/{target.elf.name}: cat" in ninja
    assert f"build g1: g1 out/{target.elf.name} | orig/{target.elf.name}" in ninja


# ---------------------------------------------------------------------------
# The generated graph has to run where the build runs: `CreateProcess`, not `sh`
#
# Ninja starts an edge with `sh -c` on macOS/Linux and with `CreateProcessA` on Windows --
# no shell at all, so no `|`, no `>`, and none of `python3`, `cpp`, `sed` or `cat`.  A rule
# command may therefore only name the interpreter that configured this graph
# (`sys.executable`, spelled once as ninja's `python` variable), programs installed by name
# on every host, and `-c` one-liners.  Rule *names* stay (`cat` names the tail edge, and
# three tests identify it by that name); only the commands had to move.
# ---------------------------------------------------------------------------


def test_no_edge_command_needs_a_posix_shell():
    """Every command is the configured interpreter or a MIPS binutils program."""
    target = probe()
    ninja = configure.ninja_text([], [], False, [], target, target.geometry)
    commands = [line.split("=", 1)[1].strip()
                for line in ninja.splitlines() if line.startswith("  command = ")]
    assert len(commands) >= 6               # as, cc, objsec, ld, bin, cat, g1
    for command in commands:
        for posix_only in ("python3", "/dev/null", "cpp ", "sed ", "cat ", " | "):
            assert posix_only not in command, f"{posix_only!r} is POSIX-only: {command}"
        first = command.split()[0]
        assert first == '"$python"' or first.startswith("mips-linux-gnu-"), command
    assert f"python = {sys.executable}" in ninja


def test_the_as_rule_is_one_program_that_every_as_edge_depends_on():
    """The split filter and the assembler are one process, and its bytes dirty every edge."""
    target = probe()
    split = ROOT / "asm" / "nonmatchings" / "main" / "probe.s"
    ninja = configure.ninja_text([split], [], True, [], target, target.geometry)
    assert f'  command = "$python" {configure.AS_PROGRAM} $in -o $out\n' in ninja
    assert " | " not in configure.AS_RULE
    assert (f" | {configure.GENERATOR} {configure.AS_PROGRAM}\n") in ninja
    assert (ROOT / configure.AS_PROGRAM).is_file()


def test_the_emitted_one_liners_replace_the_shell_utilities_byte_for_byte(tmp_path):
    """`cat $in > $out` and the `/dev/null` sink, as the processes they now are."""
    pieces = [b"one\n", b"two\n", b"three"]
    paths = []
    for index, blob in enumerate(pieces):
        path = tmp_path / f"in{index}"
        path.write_bytes(blob)
        paths.append(str(path))
    out = tmp_path / "out"
    subprocess.run([sys.executable, "-c", configure.CAT_PY, str(out), *paths], check=True)
    assert out.read_bytes() == b"".join(pieces)

    # The objsec edge names the null device as its copy sink: the dump must be the section's
    # bytes and the object untouched (two of these edges run concurrently against it).
    source = tmp_path / "sec.s"
    source.write_text('\t.section .debug,"",@progbits\n\t.4byte 0x11223344\n\t.byte 0xAA\n')
    obj = tmp_path / "sec.o"
    subprocess.run(["mips-linux-gnu-as", "-EL", "-march=5900", "-mabi=eabi",
                    "-o", str(obj), str(source)], check=True)
    before = obj.read_bytes()
    dumped = tmp_path / "sec.bin"
    subprocess.run([sys.executable, "-c", configure.OBJSEC_PY, ".debug", str(dumped),
                    str(obj)], check=True)
    assert dumped.read_bytes() == b"\x44\x33\x22\x11\xaa"
    assert obj.read_bytes() == before


def test_the_as_rule_program_assembles_splits_byte_for_byte_like_the_old_pipeline(tmp_path):
    """The proof the `as` rule rests on, on a spread of splits (all 7,664 were compared).

    The old rule was ``cpp -Iinclude $in -o - | sed -E '<.align drop>' | as ...``; the new one
    is ``as_split.py``.  The two must produce identical objects: the filter is the only thing
    that changes, and `cpp`'s own contribution is marker comments gas reads as comments.
    """
    if shutil.which("cpp") is None or shutil.which("sed") is None:
        pytest.skip("the old pipeline's cpp/sed are not on this host")
    splits = sorted((ROOT / "asm").rglob("*.s"))
    if not splits:
        pytest.skip("no generated split tree (run ./ddr build)")
    sample = splits[::700] + [path for path in splits if path.parent.name == "data"][:1]
    for split in sample:
        rel = split.relative_to(ROOT).as_posix()
        reference = tmp_path / "reference.o"
        chain = (f"cpp -Iinclude {rel} -o - | "
                 f"sed -E '/^[[:space:]]*[.]align[[:space:]]/d' | "
                 f"mips-linux-gnu-as -Iasm/include --no-pad-sections -EL -march=5900 "
                 f"-mabi=eabi -o {reference}")
        subprocess.run(["sh", "-c", chain], cwd=ROOT, check=True)
        ours = tmp_path / "ours.o"
        subprocess.run([sys.executable, str(ROOT / configure.AS_PROGRAM), rel,
                        "-o", str(ours)], cwd=ROOT, check=True)
        assert reference.read_bytes() == ours.read_bytes(), rel


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


def probe_elf(tmp_path, flags=0x20924000):
    """A one-segment ELF: what ``basis.image_flags`` reads for an object built from a blob."""
    payload = bytes(range(32))
    image = (b"\x7fELF\x01\x01\x01" + b"\0" * 9
             + struct.pack("<HHIIIIIHHHHHH", 2, 8, 1, 0x00100000, 52, 0, flags,
                           52, 32, 1, 40, 0, 0))
    image += struct.pack("<8I", 1, 0x100, 0x00100000, 0x00100000, len(payload),
                         len(payload), 5, 4)
    image += b"\0" * (0x100 - 52 - 32) + payload
    elf_path = tmp_path / "PROBE.elf"
    elf_path.write_bytes(image)
    return elf_path


def promoted_unit(file="src/probe/unit.c", module="main", splits=("asm/nonmatchings/main/one.s",),
                  code=True):
    """A promoted unit as ``configure.promotions`` builds one, for the objdiff tests."""
    return configure.Promotion(file, 0x00100000, "--compiler 3.0b38-030307 -c -O3 -g",
                               f"build/{file}.o", f"build/{file}.o.debug",
                               f"build/{file}.o.line", ".debug_000", [".line_000"],
                               set(splits), code=code, module=module)


def test_objdiff_json_pairs_a_promoted_unit_with_one_retail_object():
    """The promoted unit is the report's unit: one target object, one ``cc`` object.

    The split-per-function units it replaces are gone (their bytes would be counted twice),
    and the target path is the object ``unit_targets`` derives from the retail image.
    """
    target = probe()
    promotion = promoted_unit()
    code = [(0x00100000, "asm/nonmatchings/main/one.s"),
            (0x00200000, "asm/nonmatchings/main/two.s")]
    project = json.loads(configure.objdiff_json(
        code, [promotion], target.geometry,
        {"src/probe/unit.c": "build/diff/main/unit.unit.o"}))
    units = {unit["name"]: unit for unit in project["units"]}
    assert set(units) == {"main/unit", "main/two"}
    assert units["main/unit"]["target_path"] == "build/diff/main/unit.unit.o"
    assert units["main/unit"]["base_path"] == "build/src/probe/unit.c.o"
    # The unpromoted split keeps its own object and a null base: its bytes are un-matched.
    assert units["main/two"]["target_path"] == "build/asm/nonmatchings/main/two.s.o"
    assert units["main/two"]["base_path"] is None


def test_objdiff_json_refuses_a_promoted_unit_with_no_target_object():
    """A promoted unit with no retail object would silently count none of its code."""
    target = probe()
    promotion = promoted_unit()
    with pytest.raises(configure.ConfigError):
        configure.objdiff_json([(0x00100000, "asm/nonmatchings/main/one.s")], [promotion],
                               target.geometry, {})


def test_objdiff_json_pairs_a_promoted_overlay_unit_with_its_blob_object():
    """A promoted overlay unit is a report unit too, under its module's name.

    Its bytes are a blob's, not the file-backed image's, so its target is the object
    ``unit_targets`` builds from that blob; naming it after the module is what keeps it apart
    from a main-image unit and from the six other blobs that load at its address.
    """
    target = probe()
    promotion = promoted_unit("src/probe/ov.c", module="probe_rel4cd",
                              splits=("asm/nonmatchings/probe_rel4cd/one.s",))
    code = [(0x00100000, "asm/nonmatchings/main/one.s")]
    project = json.loads(configure.objdiff_json(
        code, [promotion], target.geometry,
        {"src/probe/ov.c": "build/diff/probe_rel4cd/ov.unit.o"}))
    units = {unit["name"]: unit for unit in project["units"]}
    assert set(units) == {"main/one", "probe_rel4cd/ov"}
    assert units["probe_rel4cd/ov"]["target_path"] == "build/diff/probe_rel4cd/ov.unit.o"
    assert units["probe_rel4cd/ov"]["base_path"] == "build/src/probe/ov.c.o"
    # The main image's split is still its own unit with a null base.
    assert units["main/one"]["base_path"] is None


def test_an_overlay_module_named_like_the_report_segment_is_refused():
    """One name space: a module prefix equal to the main segment would merge two units."""
    geo = dataclasses.replace(geometry(), code_segment="probe")
    promotion = promoted_unit("src/probe/ov.c", module="probe",
                              splits=("asm/nonmatchings/probe/one.s",))
    assert promotion.is_overlay
    with pytest.raises(configure.ConfigError, match="probe"):
        configure.unit_name(promotion, geo)


def test_unit_targets_writes_one_object_per_promoted_main_unit(tmp_path, monkeypatch):
    """configure writes the object: retail's bytes for the unit, its functions named in it."""
    elf_path = probe_elf(tmp_path)
    functions = [types.SimpleNamespace(name="one", address=0x00100014, size=8),
                 types.SimpleNamespace(name="two", address=0x00100000, size=8)]
    manifests = types.SimpleNamespace(tu_named=lambda file: types.SimpleNamespace(
        functions=functions))
    monkeypatch.setattr(configure.cc, "split_extent", lambda tu, manifests: (0x00100000,
                                                                            0x00100020))
    monkeypatch.setattr(configure.basis, "DIRECTORY", tmp_path / "diff")
    units = [promoted_unit(),
             promoted_unit("src/probe/data.c", code=False)]
    written = configure.unit_targets(units, manifests, probe(elf=elf_path), geometry())
    assert written == {"src/probe/unit.c": str(tmp_path / "diff" / "main" / "unit.unit.o")}
    emitted = elf.Elf(written["src/probe/unit.c"])
    assert [(s.name, s.value, s.size) for s in emitted.symbols if s.name] == [
        ("two", 0, 8), ("one", 0x14, 8)]


def test_unit_targets_writes_an_overlay_units_object_from_its_blob(tmp_path, monkeypatch):
    """An overlay unit's target is its module blob's bytes at the window base, one read.

    Two units of one module share the blob read (it is the verified pack or the 1.9 GB image,
    so reading it per unit would be wasted work), and the object carries the region's bytes
    with the functions at their retail offsets and the retail ELF's ``e_flags`` -- the blob is
    not an ELF, so nothing there can be read off it.
    """
    geo = overlay_geometry()
    blob = b"\0" * 0x40 + bytes(range(0x100)) + b"\0" * 0xC0
    functions = [types.SimpleNamespace(name="one", address=0x00200040, size=8),
                 types.SimpleNamespace(name="two", address=0x00200050, size=8)]
    manifests = types.SimpleNamespace(tu_named=lambda file: types.SimpleNamespace(
        functions=functions))
    monkeypatch.setattr(configure.cc, "split_extent", lambda tu, manifests: (0x00200040,
                                                                            0x00200060))
    monkeypatch.setattr(configure.basis, "DIRECTORY", tmp_path / "diff")
    reads = []
    monkeypatch.setattr(configure, "overlay_blob",
                        lambda target, overlay: reads.append(overlay.name) or blob)
    units = [promoted_unit("src/probe/ov.c", module="probe_rel4cd"),
             promoted_unit("src/probe/ov2.c", module="probe_rel4cd")]
    written = configure.unit_targets(units, manifests, probe(elf=probe_elf(tmp_path)), geo)
    assert written == {
        "src/probe/ov.c": str(tmp_path / "diff" / "probe_rel4cd" / "ov.unit.o"),
        "src/probe/ov2.c": str(tmp_path / "diff" / "probe_rel4cd" / "ov2.unit.o")}
    assert reads == ["probe_rel4cd"]
    emitted = elf.Elf(written["src/probe/ov.c"])
    text = next(section for section in emitted.sections if section.name == ".text")
    assert text.size == 0x20 and emitted.data[text.offset:text.offset + 0x20] == blob[0x40:0x60]
    assert [(s.name, s.value, s.size) for s in emitted.symbols if s.name] == [
        ("one", 0, 8), ("two", 0x10, 8)]
    assert emitted.flags == 0x20924000


def test_unit_targets_refuses_an_overlay_unit_with_no_blob_or_image(tmp_path, monkeypatch):
    """No blob and no image means no target object: refused, never counted as 0%.

    ``configure.overlay_blob`` is the one place a module's bytes are proved (the pack's
    sha256 or the image's), and it already refuses loudly; the report must not swallow that
    into a unit with no target, which objdiff would score as nothing written.
    """
    geo = dataclasses.replace(overlay_geometry(),
                              overlays=(dataclasses.replace(OVERLAY, sha256="ab" * 32),))
    functions = [types.SimpleNamespace(name="one", address=0x00200040, size=8)]
    manifests = types.SimpleNamespace(tu_named=lambda file: types.SimpleNamespace(
        functions=functions))
    monkeypatch.setattr(configure.cc, "split_extent", lambda tu, manifests: (0x00200040,
                                                                            0x00200060))
    monkeypatch.setattr(configure.basis, "DIRECTORY", tmp_path / "diff")
    target = types.SimpleNamespace(overlays=geo.overlays,
                                   image=tmp_path / "absent.iso",
                                   overlay_blob=lambda name: tmp_path / "absent.bin")
    with pytest.raises(configure.ConfigError, match="probe_rel4cd: neither"):
        configure.unit_targets([promoted_unit("src/probe/ov.c", module="probe_rel4cd")],
                               manifests, target, geo)
    assert not (tmp_path / "diff").exists()


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


def test_a_promoted_units_datum_is_selected_by_its_own_section():
    """One placed datum per section: a unit with two would otherwise move both at once.

    A data-only source is compiled raw and keeps its single ``.data``; a promoted source is
    the emitted object whose every placed datum has a section of its own, named from the
    symbol (``compile.data_section``), so the linker script can place ``@40`` and ``@41`` at
    two different addresses out of one object.
    """
    placements = [
        dict(name="@40", address=0x2D6D88, size=5, extent=8,
             source="src/network/net_window/net_win_listdtl2.c"),
        dict(name="@41", address=0x2D6D90, size=5, extent=8,
             source="src/network/net_window/net_win_listdtl2.c"),
        dict(name="bk_tm2_records", address=0x2DA260, size=0xDE8, extent=0xDE8,
             source="data/bk_load_data.c"),
    ]
    promoted = {"src/network/net_window/net_win_listdtl2.c":
                "build/src/network/net_window/net_win_listdtl2.c.o"}
    assert configure.placement_inputs(placements, promoted) == [
        (0x2D6D88, "build/src/network/net_window/net_win_listdtl2.c.o", ".datum._4040"),
        (0x2D6D90, "build/src/network/net_window/net_win_listdtl2.c.o", ".datum._4041"),
        (0x2DA260, "build/data/bk_load_data.c.o", ".data"),
    ]


def data_split_text():
    """A data split with words at every edge the two `@40` placements cut on."""
    rows = [(0x002D6D80, "00000000"), (0x002D6D88, "25303564"),
            (0x002D6D8C, "00000000"), (0x002D6D90, "00000000"),
            (0x002D6DA8, "25303564"), (0x002D6DAC, "00000000"),
            (0x002D6DB0, "00000000"), (0x002D6DB8, "00000000")]
    lines = []
    for address, word in rows:
        if address in (0x002D6D80, 0x002D6D88, 0x002D6DA8):
            lines.append(f"dlabel D_{address:08X}\n")
            lines.append(f"nonmatching D_{address:08X}\n")
        lines.append(f"    /* 1 {address:08X} {word} */ .word 0x{word}\n")
    return "".join(lines)


def test_two_units_that_both_place_at_40_get_distinct_pad_pieces(tmp_path, monkeypatch):
    """One literal index, two units: each pad piece is its own file and its own size.

    `net_win_listdtl2.c`'s `@40` sits at 0x002D6D88 and `net_win_listdtl3.c`'s at
    0x002D6DA8 -- the same index because a pool is numbered per *object*, and the units are
    alike enough that both start at `@40`.  A pad named from the symbol alone is one ninja
    output claimed by two rules, which `ninja` refuses to load; and a size looked up by name
    would give the second unit the first unit's pad.
    """
    monkeypatch.setattr(configure, "REPO_ROOT", tmp_path)
    split = "asm/nonmatchings/main/data.s"
    sources = {split: data_split_text()}
    code = [(0x002D6D80, split), (0x002D6DC0, "asm/data/next.s")]
    placements = [
        dict(name="@40", address=0x2D6D88, size=5, extent=0x8, source="src/a.c"),
        dict(name="@40", address=0x2D6DA8, size=5, extent=0x10, source="src/b.c"),
    ]
    pieces, pads, aliases = configure.plan_data(sources, code, geometry(), placements, {})
    assert [address for address, _ in pads] == [0x2D6D8D, 0x2D6DAD]
    assert len({path for _, path in pads}) == 2, pads
    bodies = [pathlib.Path(tmp_path / path).read_text() for _, path in pads]
    assert [body.split()[-1] for body in bodies] == ["3", "11"], "each record's own extent"
    assert all("_4040_" in path for _, path in pads)


def test_one_unit_placing_at_40_still_yields_one_pad_piece(tmp_path, monkeypatch):
    """The preference is for collisions: a lone placement keeps one piece of its own size."""
    monkeypatch.setattr(configure, "REPO_ROOT", tmp_path)
    split = "asm/nonmatchings/main/data.s"
    placements = [dict(name="@40", address=0x2D6D88, size=5, extent=0x8, source="src/a.c")]
    pieces, pads, aliases = configure.plan_data(
        {split: data_split_text()}, [(0x002D6D80, split), (0x002D6DC0, "asm/data/next.s")],
        geometry(), placements, {})
    assert len(pads) == 1
    address, path = pads[0]
    assert address == 0x2D6D8D
    assert pathlib.Path(tmp_path / path).read_text().split()[-1] == "3"


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


def test_the_cc_edge_carries_adoption_for_every_unit():
    """Every promoted unit's `cc` edge carries `--adopt-retail-meta`, and nothing else.

    Promotion is always adoption: `.text` byte equality is the proof and retail's inventory
    supplies `.line`/`.debug`, so there is no per-row debug step to put on the edge.
    """
    if not TARGET.cus.is_file():
        pytest.skip(f"{TARGET.name}: its config is generated in Task 4")
    promoted = {promotion.file: promotion for promotion in configure.promotions(target=TARGET)}
    for file, _version, _flags in TARGET.tu_builds:
        flags = promoted[file].flags
        assert flags.endswith("--adopt-retail-meta"), flags
        assert "--normalise-debug" not in flags
    # net_grf's 1592-byte chunk is normalised inside the adoption step itself, not by a flag.
    assert promoted["src/network/net_grf.c"].flags.endswith("--adopt-retail-meta")


def test_a_measured_row_configures_an_adopting_unit():
    """A three-element row configures with `--adopt-retail-meta` on its `cc` edge.

    `.text` byte equality is the proof and retail's inventory supplies `.line`/`.debug`; the
    row carries only the compiler build and flags it was measured with.
    """
    tu = type("Tu", (), {"address": 0x100000,
                         "functions": (type("F", (), {"name": "f"})(),),
                         "overlay": "main", "split_directory": "main"})
    manifests = type("M", (), {
        "tu_files": lambda self: {"src/sys/sys_scf.c"},
        "tu_named": lambda self, name: tu,
        "debug_chunk_index": lambda self, unit: 0,
        "line_chunk_indices": lambda self, unit: [0],
    })()
    (promotion,) = configure.promotions(
        manifests, probe(tu_builds=(("src/sys/sys_scf.c", "3.0", "-g"),)))

    assert promotion.flags == "--compiler 3.0 -g --adopt-retail-meta"
    assert promotion.code is True
    assert promotion.splits == {"asm/nonmatchings/main/f.s"}


def test_a_data_only_row_carries_no_code_and_no_line_databins():
    """A unit whose DWARF declares no function is promotion too: its address is its first
    placed datum's, its object contributes no `.text`, and it owns a `.debug` chunk with no
    `.line` chunk beside it."""
    tu = type("Tu", (), {"address": 0x002AFD40, "functions": (), "overlay": "main",
                         "split_directory": "main"})
    manifests = type("M", (), {
        "tu_files": lambda self: {"src/AM/s573/play/oni_list.c"},
        "tu_named": lambda self, name: tu,
        "debug_chunk_index": lambda self, unit: 7,
        "line_chunk_indices": lambda self, unit: [],
    })()
    (promotion,) = configure.promotions(
        manifests, probe(tu_builds=(("src/AM/s573/play/oni_list.c", "3.0", "-g"),)))

    assert promotion.address == 0x002AFD40
    assert promotion.code is False
    assert promotion.splits == set()
    assert promotion.debug_databin == ".debug_007"
    assert promotion.line_databins == []
    assert promotion.flags == "--compiler 3.0 -g --adopt-retail-meta"


def test_a_four_element_row_is_refused_before_anything_is_configured():
    """The removed state ladder leaves a clear error, not a silently ignored element."""
    for stale in (("src/sys/sys_scf.c", "3.0", "-g", "adopt"),
                  ("src/sys/sys_scf.c", "3.0", "-g", True),
                  ("src/sys/sys_scf.c", "3.0", "-g", False)):
        with pytest.raises(ValueError) as excinfo:
            probe(tu_builds=(stale,))
        assert "three elements" in str(excinfo.value)
        assert "--adopt-retail-meta" in str(excinfo.value)


def test_a_promoted_source_with_directives_is_refused_and_a_clean_one_is_not(tmp_path):
    """The `#line` rule of a committed promoted source, checked against a synthetic tree.

    A directive renumbers what a reader sees, and the rewrite that removes it is a promotion
    step, so `configure.py` refuses to write a graph over one: the message names the file, the
    count and the remedy.  The same source without the directive is accepted.
    """
    source = tmp_path / "src" / "promoted.c"
    source.parent.mkdir()
    source.write_text("int f(void) {\n#line 20\n    return 0;\n#line 30\n}\n")
    target = probe(tu_builds=(("src/promoted.c", "3.0-011126", "-c -g"),))

    with pytest.raises(configure.ConfigError) as excinfo:
        configure.check_promoted_sources(target, root=tmp_path)

    message = str(excinfo.value)
    assert "src/promoted.c" in message
    assert "2 #line directive(s)" in message
    assert ("python3 tools/toolchain/line_reflow.py src/promoted.c --normalise"
            in message)

    source.write_text("int f(void) {\n    return 0;\n}\n")
    assert configure.check_promoted_sources(target, root=tmp_path) is None


def test_configure_refuses_the_directive_before_it_writes_the_graph(tmp_path, monkeypatch):
    """The check is first: a `#line` stops configure before `splat`, the manifests or a write.

    `cus_path` does not exist and the graph on disk says `untouched` -- if the gate ran after
    the writes, or after reading the manifests, one of those would be the first failure.
    """
    source = tmp_path / "src" / "promoted.c"
    source.parent.mkdir()
    source.write_text("#line 1\nint f(void) { return 0; }\n")
    target = probe(tu_builds=(("src/promoted.c", "3.0-011126", "-c -g"),))
    monkeypatch.setattr(configure, "REPO_ROOT", tmp_path)
    graph = tmp_path / "build.ninja"
    graph.write_text("untouched\n")

    with pytest.raises(configure.ConfigError, match=r"src/promoted\.c: 1 #line directive"):
        configure.configure(target, cus_path=tmp_path / "cus.json")

    assert graph.read_text() == "untouched\n"


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


# ---------------------------------------------------------------------------
# overlay blobs: one splat run per module, and a link of its own
# ---------------------------------------------------------------------------

#: A second window at the *same* base as a plausible sibling: seven of this target's modules
#: load at 0x7F0000, which is why a run (and its directory) is keyed by name, never address.
OVERLAY = targets.Overlay("probe_rel4cd", 0x00200000, 0x200, 0x100, 0xC0, 0x100, 0x1000)
SIBLING = targets.Overlay("other_rel4cd", 0x00200000, 0x100, 0x80, 0x40, 0x80, 0x2000)


def overlay_geometry():
    fields = dataclasses.asdict(geometry())
    return targets.Geometry(**{**fields, "overlays": (OVERLAY, SIBLING)})


def test_an_overlay_run_splits_its_blob_at_the_windows_code_addresses():
    """The run is the module's *code window*: it starts at the blob's first code byte, loads at
    that byte's address, and stops at the blob -- so every split comment carries the absolute
    VA the DWARF records, which is what `compile.split_extent` matches a unit's functions on.
    """
    text = configure.overlay_splat_yaml(OVERLAY, probe())
    assert f"  basename: {OVERLAY.name}\n" in text
    assert f"    start: 0x{targets.OVERLAY_HEADER:X}\n" in text
    assert f"    vram: 0x{OVERLAY.code_vram:X}\n" in text
    assert f"      - [0x{targets.OVERLAY_HEADER:X}, c, {OVERLAY.name}]\n" in text
    assert f"  - [0x{OVERLAY.filesize:X}]\n" in text
    # The main run's split-shaping options, because a split must be the text splat would write.
    assert "  subalign: 1\n" in text
    assert "  named_regs_for_c_funcs: false\n" in text
    assert "  detect_redundant_function_end: false\n" in text
    # ... and the files that belong to the main link are not this run's to write.
    assert "  create_undefined_funcs_auto: false\n" in text
    assert "  generate_asm_macros_files: false\n" in text
    assert f"{OVERLAY.name}/symbol_addrs.txt" in text
    assert "asm/nonmatchings" not in text, "asm_path is `asm`; splat appends the segment"
    # Two modules at one base are two runs with two sets of inputs.
    assert configure.overlay_splat_yaml(SIBLING, probe()) != text


def test_overlay_symbols_come_from_the_modules_own_records(tmp_path):
    """The oracle withholds an overlay record from the placed ledger; the module it names is
    the only thing that makes an address resolvable, so the run's symbol file is filtered by
    module *and* by the code window it splits."""
    unplaced = tmp_path / "unplaced_symbols.txt"
    unplaced.write_text(
        f"inside = 0x{OVERLAY.code_vram:08X}; // type:func provenance:dwarf "
        f"reason:outside every declared segment overlay:{OVERLAY.name}\n"
        f"data = 0x{OVERLAY.data_vram:08X}; // type:obj provenance:dwarf "
        f"reason:outside every declared segment overlay:{OVERLAY.name}\n"
        f"elsewhere = 0x{OVERLAY.code_vram:08X}; // type:func provenance:dwarf "
        f"reason:outside every declared segment overlay:{SIBLING.name}\n")
    text = configure.overlay_symbols_text(types.SimpleNamespace(unplaced=unplaced), OVERLAY)
    assert f"inside = 0x{OVERLAY.code_vram:08X}; // type:func" in text
    assert "elsewhere" not in text, "another module's record at the same address is not ours"
    assert "data = " not in text, "the run splits the code window, not the data section"
    # splat reads `key:value` attributes; the oracle's reason/provenance must not leak in.
    assert "reason" not in text and "provenance" not in text


def promotion(module, file, address):
    return configure.Promotion(file, address, "--compiler 3.0b38-030307 -c -O3 -g", 
                               f"build/{file}.o", f"build/{file}.o.debug",
                               f"build/{file}.o.line", ".debug_000", [".line_000"],
                               set(), module=module)


def test_an_overlay_link_places_a_unit_at_the_retail_address_inside_the_window():
    """The script pins the object at the unit's address, with the blob offset as its LMA, and
    asserts both the retail extent and the window's own end."""
    unit = promotion(OVERLAY.name, "src/probe/ov.c", 0x00200080)
    script = configure.overlay_link_script(OVERLAY, [(unit, (0x00200080, 0x002000C0))],
                                           probe())
    assert "  .ovl_probe_rel4cd_ov 0x00200080 : AT(0x00000080) SUBALIGN(1)\n" in script
    assert "    build/src/probe/ov.c.o(.text)\n" in script
    assert "SIZEOF(.ovl_probe_rel4cd_ov) == 0x40" in script
    assert f"<= 0x{OVERLAY.code_end_vram:X}" in script
    # It is not the image: nothing here is objcopied into out/, so no byte G1 compares moves.
    assert "NOT the image" in script


def test_two_units_of_one_module_get_two_sections(tmp_path):
    first = promotion(OVERLAY.name, "src/probe/a.c", 0x00200080)
    second = promotion(OVERLAY.name, "src/probe/b.c", 0x002000A0)
    script = configure.overlay_link_script(
        OVERLAY, [(first, (0x00200080, 0x002000A0)), (second, (0x002000A0, 0x002000C0))],
        probe())
    assert ".ovl_probe_rel4cd_a 0x00200080" in script
    assert ".ovl_probe_rel4cd_b 0x002000A0" in script


def datum(promotion_, name, address, size, extent):
    return dict(name=name, address=address, size=size, extent=extent,
                source=promotion_.file)


def test_an_overlay_link_places_a_datum_at_its_recorded_address():
    """A module-owned datum gets a section of its own -- selecting `.text` would not carry it,
    and selecting the object's `.data` would drag every other datum along -- at the retail
    address the ledger records, with its blob offset as the LMA, its compiled length asserted,
    and its whole retail extent bounded by the module's data end."""
    unit = promotion(OVERLAY.name, "src/probe/ov.c", 0x00200080)
    record = datum(unit, "@53", OVERLAY.data_vram + 0x10, 0x24, 0x30)
    script = configure.overlay_link_script(
        OVERLAY, [(unit, (0x00200080, 0x002000C0))], probe(), data=[(unit, record)])
    section = ".ovl_probe_rel4cd_ov_data__4053"
    assert (f"  {section} 0x00200150 : AT(0x00000150) SUBALIGN(1)\n  {{\n"
            f"    build/src/probe/ov.c.o(.datum._4053)\n  }}\n") in script
    assert f"ASSERT(SIZEOF({section}) == 0x24," in script
    # The *extent* is what the window has to hold, not the compiled length alone.
    assert (f"ASSERT(ADDR({section}) + 0x30 <= "
            f"0x{OVERLAY.vaddr + OVERLAY.filesize:08X},") in script
    # The unit's `.text` section still selects `.text` only: a datum is never dragged in by
    # another section's wildcard.
    assert "build/src/probe/ov.c.o(.text)\n" in script


def test_two_datum_records_get_two_sections_even_with_one_name():
    """A literal-pool index is numbered per object, so two units of one module can both place
    `@53`; the section name carries the unit as well as the datum."""
    first = promotion(OVERLAY.name, "src/probe/a.c", 0x00200080)
    second = promotion(OVERLAY.name, "src/probe/b.c", 0x002000A0)
    records = [(first, datum(first, "@53", OVERLAY.data_vram, 0x4, 0x4)),
               (second, datum(second, "@53", OVERLAY.data_vram + 0x4, 0x4, 0x4))]
    script = configure.overlay_link_script(OVERLAY, [], probe(), data=records)
    assert ".ovl_probe_rel4cd_a_data__4053 " in script
    assert ".ovl_probe_rel4cd_b_data__4053 " in script


def overlay_unit(module, file, address):
    return promotion(module, file, address)


def test_the_data_ledger_is_partitioned_by_the_file_that_holds_the_bytes():
    """The partition is the *address's* answer and, where several windows share a base, the
    source's: `@53` at 0x00200150 is inside both probe windows and belongs to the module its
    source is in; `crect` is an overlay unit's datum that retail placed in the main image, so
    it stays main's."""
    geo = overlay_geometry()
    unit = overlay_unit(OVERLAY.name, "src/probe/ov.c", 0x00200080)
    sibling = overlay_unit(SIBLING.name, "src/probe/other.c", 0x00200080)
    records = [datum(unit, "@53", 0x00200150, 0x24, 0x30),
               datum(unit, "crect", 0x00100100, 0x8, 0x8),
               dict(name="table", address=0x00100400, size=0x10, extent=0x10,
                    source="data/table.c")]
    main, owned = configure.placements_by_module(records, [unit, sibling], geo)
    assert [record["name"] for record in main] == ["crect", "table"]
    assert owned == {OVERLAY.name: [(unit, records[0])]}


def test_a_datum_in_a_window_its_source_does_not_load_in_is_refused():
    geo = overlay_geometry()
    main_unit = promotion("main", "src/probe/main.c", 0x00100000)
    record = dict(name="@53", address=0x00200150, size=0x24, extent=0x30,
                  source="src/probe/main.c")
    with pytest.raises(configure.ConfigError, match="only that module's link"):
        configure.placements_by_module([record], [main_unit], geo)


def test_a_datum_in_no_window_and_no_loadable_image_is_refused():
    geo = overlay_geometry()
    record = dict(name="far", address=0x00300000, size=0x4, extent=0x4,
                  source="data/far.c")
    with pytest.raises(configure.ConfigError, match="nothing holds its bytes"):
        configure.placements_by_module([record], [], geo)


def test_an_overlay_datum_outside_the_blobs_data_is_refused():
    geo = overlay_geometry()
    unit = overlay_unit(OVERLAY.name, "src/probe/ov.c", 0x00200080)
    # The window's code is split, never a datum's home.
    code = dict(name="early", address=OVERLAY.code_vram, size=0x4, extent=0x4,
                source="src/probe/ov.c")
    with pytest.raises(configure.ConfigError, match="inside probe_rel4cd's code"):
        configure.placements_by_module([code], [unit], geo)
    # Past the end of the blob there are no bytes to place.
    past = dict(name="late", address=OVERLAY.vaddr + OVERLAY.filesize - 0x4, size=0x4,
                extent=0x8, source="src/probe/ov.c")
    with pytest.raises(configure.ConfigError, match="data end"):
        configure.placements_by_module([past], [unit], geo)


def test_two_overlay_data_extents_that_overlap_are_refused():
    geo = overlay_geometry()
    unit = overlay_unit(OVERLAY.name, "src/probe/ov.c", 0x00200080)
    records = [dict(name="@53", address=OVERLAY.data_vram, size=0x20, extent=0x30,
                    source="src/probe/ov.c"),
               dict(name="@54", address=OVERLAY.data_vram + 0x20, size=0x4, extent=0x8,
                    source="src/probe/ov.c")]
    with pytest.raises(configure.ConfigError, match="cannot own one address"):
        configure.placements_by_module(records, [unit], geo)


def test_overlay_splits_are_not_the_main_links(tmp_path, monkeypatch):
    """A module's splits live under `asm/nonmatchings/<module>/`, and the main link must never
    read them: their addresses are a blob's window, not the file-backed image's."""
    asm = tmp_path / "asm" / "nonmatchings"
    (asm / "main").mkdir(parents=True)
    (asm / OVERLAY.name).mkdir(parents=True)
    (asm / "main" / "a.s").write_text(".text\n")
    (asm / OVERLAY.name / "b.s").write_text(".text\n")
    monkeypatch.setattr(configure, "REPO_ROOT", tmp_path)
    assert set(configure.split_sources()) == {f"asm/nonmatchings/main/a.s",
                                              f"asm/nonmatchings/{OVERLAY.name}/b.s"}
    assert set(configure.split_sources(skip={OVERLAY.name})) == {"asm/nonmatchings/main/a.s"}


def test_the_main_graph_gains_no_edge_without_an_overlay_link():
    """No promoted overlay unit, no second link: the graph is the one that was there before."""
    target = probe()
    ninja = configure.ninja_text([], configure.databin_segments(chunks(), target.geometry),
                                 False, [], target, target.geometry)
    built = target.built.relative_to(ROOT).as_posix()
    assert "ldovl" not in ninja and "out/overlays" not in ninja
    assert f"\ndefault {built} g1\n" in ninja


def test_an_overlay_link_is_an_edge_of_its_own_and_a_default_target():
    target = probe()
    script = ROOT / "build" / "overlays" / "probe_rel4cd.ld"
    ninja = configure.ninja_text([], configure.databin_segments(chunks(), target.geometry),
                                 False, [], target, target.geometry,
                                 overlay_links=[("probe_rel4cd", script,
                                                 ["build/src/probe/ov.c.o"])])
    overlay_elf = target.overlay_elf("probe_rel4cd").relative_to(ROOT).as_posix()
    assert f"build {overlay_elf}: ldovl build/src/probe/ov.c.o" in ninja
    assert f"  script = {script.relative_to(ROOT).as_posix()}\n" in ninja
    # The image's own edges are untouched: the same `ld`, `bin` and `cat` lines as before.
    built = target.built.relative_to(ROOT).as_posix()
    assert f"build {built}: cat build/PROBE.loadable" in ninja
    assert f"\ndefault {built} {overlay_elf} g1\n" in ninja
