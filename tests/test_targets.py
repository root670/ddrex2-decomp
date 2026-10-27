"""The target descriptor: one registry, and no target name or retail path anywhere else.

`config/targets.py` is the single place a target's facts live -- its retail ELF and G1 pin, its
disc image and G3 pin, its config directory, its measured geometry and its per-unit build pairs
-- and every tool reads them from there.  Three properties are what this suite exists to keep:

* the registry **resolves** the registered target by name and by default, with the pins and paths
  the plan records;
* the registry is **data**: a second target is a `Target(...)` plus `Registry.add`, and nothing
  else in the tree has to learn about it (tested by adding one, not by shipping a second one);
* a descriptor **fails loudly** rather than defaulting -- an empty pin, a nameless binary, a
  config dir that is not `config/<name>`, and a geometry nobody has measured yet.

The last test is the guard for the whole design: no tool file may spell a target name or a retail
path of its own.
"""

import dataclasses
import pathlib
import re
import sys
import tokenize

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from config import targets  # noqa: E402

# The plan's target table for the one registered target, as literals: a descriptor that drifts
# from these is the finding.
ELF_SHA = "ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd"
IMAGE_SHA = "70a9056657665e978c7de9fc223cb753956902416418993176438316f6cd652b"
IMAGE = pathlib.Path(
    "$HOME/Downloads/Dance Dance Revolution Extreme 2 (May 10, 2005 prototype)"
    "/PS2 - Dance Dance Revolution Extreme 2 PS2 Preview Code 6-22-05.iso")

#: "No tool spells a target name or a retail path": every file this task threaded, minus the
#: descriptor itself.  `tools/sdk/borrow.py` and `match.py` joined it with retarget Task 9, which
#: re-pointed the borrower at `config/targets.py` (it derived `GAME_START` from the target's own
#: symbol ledger rather than a literal); `tools/sdk/revisions.py` is still out of scope: its
#: *record* names the template it verdicts (`SLUS_211.74` in `NOTES`, the paths in code), and a
#: guard that scans raw text cannot tell that prose from a coupling.  That file is the one
#: residual coupling the retarget left, and it is listed in the Task 9 report as such.
THREADED = (ROOT / "configure.py", ROOT / "ddr") \
    + tuple(sorted((ROOT / "tools" / "oracle").glob("emit_*.py"))) \
    + tuple(sorted((ROOT / "tools" / "verify").glob("*.py"))) \
    + (ROOT / "tools" / "iso" / "reinsert.py", ROOT / "tools" / "toolchain" / "compile.py") \
    + (ROOT / "tools" / "sdk" / "borrow.py", ROOT / "tools" / "sdk" / "match.py")

#: Every binary this tree has pointed at *other than* the registered target, and the addresses
#: its own geometry measured.  As integers, because one file spells `0x21C410` and another
#: `0x0021C410`.  `SLUS_202.67` is the binary `tools/oracle/dwarf1.py` was vendored against;
#: `usam2` is the target this tree was retargeted away from (its geometry is the constants at
#: `f7b6e6e^:configure.py`).  A tool may *document* those numbers; it may not use one.
FOREIGN_ADDRESSES = {
    0x400800: "SLUS_202.67's overlay base (dwarf1's old main-image end)",
    0x21C410: "DDRMAX2 (US)'s lowest game-code PC (borrow.py's GAME_START)",
    0x1A2700: "DDRMAX2 (US)'s loadable_end", 0x1A2740: "its .debug offset",
    0x225A0: "its .line size", 0x2430E0: "its .line offset",
    0x265680: "its .comment offset", 0x2656AC: "its .reginfo offset",
    0x2656C4: "its section header offset", 0x265854: "its elf_size",
    0x6B6B80: "its bss_end", 0x2A2680: "its bss base", 0xA0997: "its .debug size",
    0x92000: "its boot-ELF offset in the disc image",
}

#: The tools that read a target's binary or its geometry.  `dwarf1.py` is here because it is
#: where a literal of exactly this kind survived two retargets: the name/path guard above
#: cannot see a number, and `THREADED` did not include the vendored reader.
BUILD_PATH_TOOLS = THREADED + (ROOT / "tools" / "oracle" / "dwarf1.py",)


def scan_addresses(path):
    """``(line, literal, why)`` for every *code* literal that is a removed target's address.

    Comments and strings are dropped: an address in a docstring is provenance ("verified
    against SLUS_202.67"), while an address in code is a measurement of some binary, and the
    only licensed sources for one are the descriptor and the ELF being read.
    """
    hits = []
    with path.open() as handle:
        for token in tokenize.generate_tokens(handle.readline):
            if token.type in (tokenize.COMMENT, tokenize.STRING):
                continue
            for literal in re.findall(r"0x[0-9A-Fa-f]+", token.string):
                value = int(literal, 16)
                if value in FOREIGN_ADDRESSES:
                    hits.append((token.start[0], literal, FOREIGN_ADDRESSES[value]))
    return hits


def probe_target(name="probe", **overrides):
    """A second descriptor, built only from this module's public surface.

    Nothing here reads or writes the repository: it is the "adding a target is configuration"
    case, expressed as the least a caller must supply.
    """
    fields = dict(name=name, config_dir=ROOT / "config" / name, elf=ROOT / "orig" / "PROBE",
                  elf_sha256=ELF_SHA, image=pathlib.Path("/tmp/probe.iso"),
                  image_sha256=IMAGE_SHA)
    fields.update(overrides)
    return targets.Target(**fields)


def probe_geometry(**overrides):
    """A small, self-consistent geometry: the numbers a measurement has to add up to."""
    fields = dict(
        elf_size=0x2000,
        loadable_rom=0x80,
        loadable_end=0x1000,
        loadable_vram=0x00100000,
        bss_end=0x00110000,
        trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400),
                  ("line", 0x1410, 0x100), ("section_headers", 0x1510, 0x2000 - 0x1510)),
        debug_size=0x400,
        line_size=0x100,
        image_elf_offset=0x92000,
    )
    fields.update(overrides)
    return targets.Geometry(**fields)


# ---------------------------------------------------------------------------
# the registered target
# ---------------------------------------------------------------------------


def test_the_registry_resolves_the_target_and_its_pins():
    target = targets.get("ddrex2p")
    assert target.name == "ddrex2p"
    assert target.config_dir == ROOT / "config/ddrex2p"
    assert target.elf == ROOT / "orig/SLUS_211.74"
    assert target.elf_sha256 == ELF_SHA
    assert target.image == IMAGE
    assert target.image_sha256 == IMAGE_SHA


def test_the_default_target_is_the_registered_one():
    """A bare `--target`-less invocation works on the target this tree is built for."""
    assert targets.names() == ("ddrex2p",)
    assert targets.DEFAULT == "ddrex2p"
    assert targets.get() == targets.get(targets.DEFAULT) == targets.get("ddrex2p")
    assert targets.TARGETS.default == targets.DEFAULT


def test_every_gate_input_resolves_the_targets_own_paths():
    """Paths are derived, never spelled twice: one config dir, one ELF, one built image."""
    target = targets.get()
    for path in (target.checksums, target.cus, target.chunks, target.symbols, target.ghidra,
                 target.borrowed, target.unplaced, target.splat_symbols,
                 target.undefined_funcs, target.undefined_syms):
        assert path.parent == target.config_dir, path
        assert target.name in str(path.relative_to(ROOT)), path
    assert target.built == ROOT / "out" / target.elf.name
    assert target.ld_script == ROOT / "build" / f"{target.elf.name}.ld"


def test_the_targets_geometry_is_the_measurement_of_its_own_binary():
    """The geometry is read out of the target's own ELF, and it has to add up to what is there.

    The numbers below are the measurement (retarget Task 4: the ELF header, the program headers
    and the section header table of `orig/SLUS_211.74`, plus the boot ELF's offset in the pinned
    image), spelled as literals so a descriptor that drifts from the binary is the finding --
    which is the same guard the two pins get above.
    """
    target = targets.get()
    geometry = target.geometry_required()
    assert geometry.elf_size == 0x75DFEC == 7725036       # the file `orig/SLUS_211.74`
    assert target.elf.name == "SLUS_211.74"
    assert (geometry.loadable_rom, geometry.loadable_end, geometry.loadable_vram) \
        == (0x200, 0x1DE380, 0x100000)
    assert geometry.code_size == 0x1DE180 == 1958272     # the one file-backed PT_LOAD
    assert geometry.bss_end == 0x723700                  # ... plus the memsz it claims
    assert (geometry.bss_vram, geometry.bss_size) == (0x2DE180, 0x445580)
    assert geometry.trailing == (
        ("shstrtab", 0x1DE380, 0x3A),
        ("debug", 0x1DE3C0, 0x491376),
        ("line", 0x66F740, 0xEE546),
        ("comment", 0x75DC86, 0x2B),
        ("reginfo", 0x75DCB4, 0x18),
        ("section_headers", 0x75DCCC, 0x320),
    )
    assert geometry.sections == ((".debug", 0x1DE3C0, 0x491376),
                                 (".line", 0x66F740, 0xEE546))
    assert geometry.image_elf_offset == 0x6D261000        # LBA 894146 of the pinned image
    # ... and the mapping the split and the link share is that measurement, inverted:
    assert geometry.offset_of(geometry.loadable_vram) == geometry.loadable_rom
    assert geometry.address_of(geometry.loadable_rom) == geometry.loadable_vram


def test_an_unmeasured_target_stops_naming_what_has_to_be_measured():
    """A target whose geometry nobody has measured is a stop, not a guess: another target's
    segment list would split this binary at the wrong addresses."""
    target = probe_target()
    assert target.geometry is None
    with pytest.raises(targets.NotMeasured) as exc:
        target.geometry_required()
    message = str(exc.value)
    assert target.name in message and target.elf.name in message


# ---------------------------------------------------------------------------
# the registry is data: a second target is configuration
# ---------------------------------------------------------------------------


def test_a_second_target_is_added_by_configuration_alone():
    """`Registry.add` is the whole of "support another target": no tool learns a new name.

    The probe is added to a registry built here, and every path a tool reads resolves for it
    without any other module changing -- which is the property the retarget needs to stay
    cheap, rather than a second target's existence in this tree.
    """
    registry = targets.Registry(targets.get(), default="ddrex2p")
    probe = probe_target()
    assert registry.add(probe) is probe
    assert registry.names() == ("ddrex2p", "probe")
    assert registry.get("probe") is probe
    assert registry.get() is targets.get()          # the default is unchanged
    assert probe.built == ROOT / "out" / "PROBE"
    assert probe.checksums == ROOT / "config" / "probe" / "checksums.txt"
    assert probe.geometry is None                   # a new target starts unmeasured


def test_a_new_target_can_be_the_default():
    registry = targets.Registry(targets.get())
    registry.add(probe_target("probe2"))
    assert registry.default == "ddrex2p"
    assert targets.Registry(targets.get(), probe_target("probe2"), default="probe2").default \
        == "probe2"


def test_a_targets_include_path_is_spelled_from_the_repository_root():
    """The include search path is a target fact, repo-relative in the descriptor.

    The promotion compile hands these directories to the compiler (``compile.py``'s
    ``include_flags``, one ``-I`` each), and the C units spell their includes the way the
    generated headers are laid out under ``include/`` -- so the path is derived here, once,
    rather than spelled by each driver that needs it.
    """
    assert probe_target(include_dirs=("headers", "types")).include_paths \
        == (ROOT / "headers", ROOT / "types")
    registered = targets.get()
    assert registered.include_dirs == ("include", "hwinclude")
    assert registered.include_paths == (ROOT / "include", ROOT / "hwinclude")


def test_a_duplicate_target_name_is_refused():
    """Two descriptors for one name would make every path ambiguous."""
    registry = targets.Registry(targets.get())
    with pytest.raises(ValueError, match="already registered"):
        registry.add(probe_target("ddrex2p"))


def test_a_registry_needs_a_target_and_a_default_that_exists():
    with pytest.raises(ValueError, match="at least one target"):
        targets.Registry()
    with pytest.raises(ValueError, match="not one of its targets"):
        targets.Registry(targets.get(), default="nosuch")
    with pytest.raises(TypeError, match="not a Target"):
        targets.Registry(targets.get()).add("probe")


def test_an_unknown_target_name_fails_loudly():
    """A typo must not silently work on the default target."""
    with pytest.raises(targets.UnknownTarget) as exc:
        targets.get("usam2")
    assert "usam2" in str(exc.value) and "ddrex2p" in str(exc.value)


# ---------------------------------------------------------------------------
# a descriptor that is missing something fails loudly
# ---------------------------------------------------------------------------


def test_tu_builds_rows_are_a_measured_pair_and_nothing_more():
    """A row is `(source, compiler build, flags)`; promotion is always adoption.

    `.text` byte equality is the proof and the debug metadata (`.line`, `AT_location`s, DIE
    order) is reconstructed from retail's inventory by `--adopt-retail-meta`, so the row
    carries no state: the pair is a fact of the measurement, not a build setting a caller
    improvises.  A four-element row is a leftover of the removed state ladder and fails
    loudly rather than being silently ignored.
    """
    measured = probe_target(tu_builds=(("src/a.c", "3.0", "-g"),))
    assert measured.build_pair("src/a.c") == ("3.0", "-g")
    assert measured.build_table() == {"src/a.c": ("3.0", "-g")}
    assert measured.build_pair("src/b.c") is None

    for stale in (("src/a.c", "3.0", "-g", "adopt"),
                  ("src/a.c", "3.0", "-g", True),
                  ("src/a.c", "3.0", "-g", False)):
        with pytest.raises(ValueError) as excinfo:
            probe_target(tu_builds=(stale,))
        message = str(excinfo.value)
        assert "three elements" in message
        assert "--adopt-retail-meta" in message


def test_a_descriptor_missing_a_required_field_fails_loudly():
    fields = {field.name for field in dataclasses.fields(targets.Target)}
    assert {"name", "config_dir", "elf", "elf_sha256", "image", "image_sha256"} <= fields
    with pytest.raises(TypeError):  # absent entirely
        targets.Target(name="probe", config_dir=ROOT / "config/probe", elf=ROOT / "orig/PROBE",
                       image=pathlib.Path("/tmp/probe.iso"), image_sha256=IMAGE_SHA)
    for broken in (dict(elf_sha256=""), dict(elf_sha256="ef31c90f"),
                   dict(image_sha256="not-a-digest"), dict(name=""),
                   dict(elf=pathlib.Path("")), dict(image=pathlib.Path("")),
                   dict(config_dir=ROOT / "config/ddrex2p"),      # another target's config
                   dict(config_dir=pathlib.Path("config/probe")),
                   dict(tu_builds=(("src/a.c", "3.0", ""),)),
                   dict(tu_builds=(("src/a.c", "3.0", "-g"), ("src/a.c", "3.0", "-g"))),
                   dict(include_dirs=("/include",)),
                   dict(include_dirs=("",)),
                   dict(geometry="0x80")):
        with pytest.raises(ValueError):
            probe_target(**broken)


# ---------------------------------------------------------------------------
# geometry: measured numbers that have to add up
# ---------------------------------------------------------------------------


def test_a_measured_geometry_is_the_fixed_point_of_its_own_derivations():
    geometry = probe_geometry()
    assert geometry.code_size == 0x1000 - 0x80
    assert geometry.bss_vram == 0x1000 + 0x100000 - 0x80
    assert geometry.bss_size == 0x110000 - geometry.bss_vram
    assert geometry.sections == ((".debug", 0x1010, 0x400), (".line", 0x1410, 0x100))
    assert geometry.trailing_of("line") == (0x1410, 0x100)
    assert geometry.offset_of(geometry.address_of(0x100)) == 0x100
    with pytest.raises(KeyError):
        geometry.trailing_of("nosuch")


@pytest.mark.parametrize("broken", [
    dict(elf_size=0),                                   # a size nothing can be
    dict(loadable_end=0x4000),                          # the segment past the file
    dict(loadable_rom=0x1000),                          # the segment inverted
    dict(bss_end=0x00100000),                           # bss below its own base
    dict(trailing=()),                                  # no measurement of the tail
    dict(trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x10, 0x400),
                   ("line", 0x1410, 0x100), ("section_headers", 0x1510, 0x2000 - 0x1510))),
    dict(trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400),
                   ("debug", 0x1410, 0x100))),           # a name twice, and no .line
    dict(trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400),
                   ("line", 0x1410, 0x100))),            # the tail does not reach the end
    dict(debug_size=0x100),                              # one measurement, two numbers
    dict(code_segment=""),
])
def test_a_geometry_that_does_not_add_up_is_refused(broken):
    with pytest.raises(ValueError):
        probe_geometry(**broken)


def test_a_measured_geometry_makes_the_target_configurable():
    target = probe_target(geometry=probe_geometry())
    assert target.geometry_required() is target.geometry


# ---------------------------------------------------------------------------
# the guard: no tool spells a target name or a retail path
# ---------------------------------------------------------------------------


def test_no_tool_spells_a_target_name_or_a_retail_path():
    """Every path a tool uses comes from the descriptor -- checked, not remembered.

    `SLUS_` is a retail binary's name, and the registered target's own name (or config dir) in
    a tool file is the same coupling: this test is what keeps a future retarget from being a
    dozen edits again.  The descriptor itself is the one place they are allowed.
    """
    patterns = re.compile(r"SLUS_\d|usam2|\"ddrex2p\"|'ddrex2p'|config/ddrex2p")
    offenders = {}
    for path in THREADED:
        hits = patterns.findall(path.read_text())
        if hits:
            offenders[path.relative_to(ROOT).as_posix()] = sorted(set(hits))
    assert targets.get().name not in (ROOT / "config").name  # sanity: the scan is live
    assert not offenders, f"target names/paths outside the descriptor: {offenders}"


def test_no_tool_spells_a_removed_targets_address():
    """The guard the literal `0x400800` walked through: names and paths were scanned, numbers
    were not.

    `tools/oracle/dwarf1.py` decided main-versus-overlay with `0x400800`, a boundary of the
    binary it was vendored against, so this target inherited that game's address space (four
    bss globals came out as 16 records at 4 addresses, and splat refuses those).  The guard
    above cannot see it, because it is a number; this one is checked by integer, since one
    file spells an address `0x21C410` and another `0x0021C410`.
    """
    assert FOREIGN_ADDRESSES and BUILD_PATH_TOOLS  # sanity: the scan is live
    offenders = {}
    for path in BUILD_PATH_TOOLS:
        hits = scan_addresses(path)
        if hits:
            offenders[path.relative_to(ROOT).as_posix()] = hits
    assert not offenders, f"a removed target's address in tool code: {offenders}"


def test_the_address_guard_reads_code_and_not_provenance(tmp_path):
    """A docstring may name an address ("verified against ..."), code may not.

    Without this split the guard would have to allow-list the very documentation that records
    where the numbers came from -- and an allow-list is what lets the next one through.
    """
    provenance = tmp_path / "provenance.py"
    provenance.write_text('"""Vendored against the binary whose overlay base was 0x400800."""\n'
                          "KIND = 'DDRMAX2 (US)'\n")
    assert scan_addresses(provenance) == []

    literal = tmp_path / "literal.py"
    literal.write_text("# its game start\nGAME_START = 0x0021C410\n")
    assert scan_addresses(literal) == [(2, "0x0021C410", FOREIGN_ADDRESSES[0x21C410])]
