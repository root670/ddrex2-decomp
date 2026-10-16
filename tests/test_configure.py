"""``configure.py`` writes the *named* target's config from the *named* target's geometry.

The full run needs the target's retail ELF (gitignored, supplied by its owner) and a generated
config, so these tests drive the pieces that decide the artifacts -- the manifest checks, the
segment list, the yaml, the linker script and the ninja graph -- with a synthetic but
self-consistent geometry and a probe target.  What they assert is the retarget's whole point: the
memory of target-specific numbers lives in the descriptor, and every generated artifact is a
function of the target it was given, not of a constant in the tool.
"""

import json
import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

import configure  # noqa: E402
from config import targets  # noqa: E402

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


def test_configure_refuses_a_target_whose_geometry_is_unmeasured(tmp_path, capsys):
    """The state this tree is in: the config is generated from the binary, so neither the
    segment list nor the pipeline can be guessed -- and nothing is written on the way out."""
    status = configure.main(["--target", targets.DEFAULT])
    err = capsys.readouterr().err
    assert status == 2
    assert "geometry" in err and targets.DEFAULT in err and "Traceback" not in err
    assert not (targets.get().config_dir / "splat.yaml").exists()


def test_an_unknown_target_is_a_configuration_error_not_a_traceback(capsys):
    status = configure.main(["--target", "usam2"])
    err = capsys.readouterr().err
    assert status == 2
    assert "usam2" in err and targets.DEFAULT in err and "Traceback" not in err
