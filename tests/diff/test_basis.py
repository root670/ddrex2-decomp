"""The diff basis: retail's bytes for one symbol, and our own, as objects objdiff can pair.

Nothing here builds anything.  The retail image these tests read is a *synthetic* one -- a
miniature 32-bit ELF with one ``PT_LOAD`` -- because ``orig/SLUS_211.74`` is gitignored and
the bytes of the real one are not this suite's business; what has to hold is that the bytes
at a virtual address come back verbatim, under the symbol's own name, with no
``.NON_MATCHING`` alias for objdiff to ignore.  The one place the premise itself (a split
object is unscorable, a stand-in for it is not) is pinned runs the real ``objdiff-cli`` --
the diff tool, not a build machine -- against a real split, and skips when either is absent.
"""

import json
import pathlib
import shutil
import struct
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))     # `diff.basis`, the module `ddr` imports
sys.path.insert(0, str(ROOT / "tools" / "oracle"))   # the vendored ELF reader, as basis reads it
sys.path.insert(0, str(ROOT))

import elf  # noqa: E402  the vendored 32-bit little-endian MIPS reader
from diff import basis  # noqa: E402

#: A code image small enough to read by eye: 32 bytes of words at the image's base.
BASE = 0x100000
FILE_OFFSET = 0x100
CODE = bytes(range(32))
SYMBOL = "func_00100008"


def image_bytes(payload: bytes = CODE, base: int = BASE, file_offset: int = FILE_OFFSET,
                flags: int = 0x20924000) -> bytes:
    """A miniature retail image: ``ET_EXEC`` for the EE, one ``PT_LOAD``, no sections.

    The shape the real binary has (one loadable segment whose file offset and virtual
    address differ), which is what ``Elf.read`` walks -- so a reader that ignored the
    program headers would return the wrong bytes here too.
    """
    header = (b"\x7fELF\x01\x01\x01" + b"\0" * 9
              + struct.pack("<HHIIIIIHHHHHH", 2, 8, 1, base, 52, 0, flags, 52, 32, 1, 40, 0, 0))
    phdr = struct.pack("<8I", 1, file_offset, base, base, len(payload), len(payload), 5, 4)
    return header + phdr + b"\0" * (file_offset - 52 - 32) + payload


@pytest.fixture
def retail(tmp_path):
    """The synthetic image, on disk, and the path to it."""
    path = tmp_path / "SLUS_000.00"
    path.write_bytes(image_bytes())
    return path


def symbols_of(path):
    return [s for s in elf.Elf(path).symbols if s.name]


def test_the_object_holds_the_retail_bytes_under_the_symbol_name(retail, tmp_path):
    """The target side *is* retail's bytes for the symbol, named exactly as objdiff pairs it."""
    path = basis.retail(SYMBOL, BASE + 8, 12, retail, directory=tmp_path / "out")
    image = elf.Elf(path)
    text = next(s for s in image.sections if s.name == ".text")
    assert image.data[text.offset:text.offset + text.size] == CODE[8:20]
    assert [(s.name, s.type, s.size, s.bind, s.shndx) for s in symbols_of(path)] == [
        (SYMBOL, 2, 12, 1, 1)]                                   # FUNC, GLOBAL, .text
    assert image.type == 1 and image.machine == 8                # ET_REL, EM_MIPS


def test_the_object_carries_no_non_matching_alias_and_no_relocations(retail, tmp_path):
    """What objdiff must not find: an alias it would ignore, or a relocation to compare.

    An object with ``<name>.NON_MATCHING`` has every symbol of that name ignored by
    objdiff -- on the base side the alias ignores the plain name too -- which is how the
    verb used to print a score it never computed.  Relocations are absent on purpose: our
    compiled objects are fully placed, so comparing addresses is comparing the code.
    """
    path = basis.retail(SYMBOL, BASE, 16, retail, directory=tmp_path)
    image = elf.Elf(path)
    assert [s.name for s in image.symbols if s.name] == [SYMBOL]
    assert not any(s.name.endswith(".NON_MATCHING") for s in image.symbols)
    assert [s.name for s in image.sections] == ["", ".text", ".symtab", ".strtab", ".shstrtab"]


def test_the_image_flags_come_from_the_image_they_were_read_from(retail, tmp_path):
    """The object's `e_flags` are the image's: the bytes are the image's own."""
    default = elf.Elf(basis.retail(SYMBOL, BASE, 8, retail, directory=tmp_path / "a")).flags
    other = tmp_path / "other.elf"
    other.write_bytes(image_bytes(flags=0x20924001))
    changed = elf.Elf(basis.retail(SYMBOL, BASE, 8, other, directory=tmp_path / "b")).flags
    assert (default, changed) == (0x20924000, 0x20924001)


def test_the_emitted_object_is_deterministic(retail, tmp_path):
    """Two runs write the same bytes: nothing in the object depends on when it was written."""
    first = basis.retail(SYMBOL, BASE, 16, retail, directory=tmp_path)
    before = first.read_bytes()
    assert basis.retail(SYMBOL, BASE, 16, retail, directory=tmp_path).read_bytes() == before


def test_a_size_that_runs_past_the_image_is_refused(retail, tmp_path):
    """Read short of the ledger's size is a refusal, never a truncated object."""
    with pytest.raises(basis.Unusable):
        basis.retail(SYMBOL, BASE + 24, 32, retail, directory=tmp_path)


def test_a_symbol_no_split_defines_is_refused(tmp_path):
    """The stand-in is only ever made of bytes a split really holds."""
    stand_in = basis.object_bytes(CODE[:8], "other", 8)
    path = tmp_path / "split.o"
    path.write_bytes(stand_in)
    with pytest.raises(basis.Unusable):
        basis.split(SYMBOL, path, directory=tmp_path)
    assert basis.split("other", path, directory=tmp_path).with_suffix("").name == "other.split"


def test_the_stand_in_reads_the_split_s_own_bytes(tmp_path):
    """``split`` copies the split's ``.text`` at the symbol's offset, under the plain name."""
    path = tmp_path / "split.o"
    path.write_bytes(basis.object_bytes(CODE[:16], "func", 16))
    stand_in = basis.split("func", path, directory=tmp_path / "out")
    image = elf.Elf(stand_in)
    text = next(s for s in image.sections if s.name == ".text")
    assert image.data[text.offset:text.offset + text.size] == CODE[:16]
    assert [(s.name, s.size) for s in symbols_of(stand_in)] == [("func", 16)]


def test_a_report_without_a_percentage_is_not_a_comparison():
    """``scored`` is what keeps the verb from printing a number objdiff never computed."""
    def report(percent="both"):
        entry = {"name": SYMBOL, "kind": "SYMBOL_FUNCTION"}
        other = {"name": SYMBOL, "kind": "SYMBOL_FUNCTION"}
        if percent in ("both", "left"):
            entry["match_percent"] = 99.5
        if percent in ("both", "right"):
            other["match_percent"] = 99.5
        return {"left": {"symbols": [entry]}, "right": {"symbols": [other]}}

    assert basis.scored(report(), SYMBOL)
    assert not basis.scored(report("left"), SYMBOL)
    assert not basis.scored(report("right"), SYMBOL)
    assert not basis.scored(report("none"), SYMBOL)
    assert not basis.scored(report(), "another_symbol")
    assert not basis.scored({"left": {}, "right": {}}, SYMBOL)


def test_the_emitted_objects_are_invisible_to_the_link(tmp_path):
    """They live in the build's generated outputs, and no edge or segment names them.

    The object is derived from the retail image, so it must never enter the linked game:
    ``configure.py``'s graph and the pinned ``ld`` script are where such an input would have
    to appear, and neither mentions the directory.  Skipped when the tree has no graph.
    """
    assert basis.DIRECTORY == ROOT / "build" / "diff"
    generated = [ROOT / "build.ninja", ROOT / "build" / "SLUS_211.74.ld"]
    if not all(path.is_file() for path in generated):
        pytest.skip("no generated graph or ld script in this tree")
    for path in generated:
        assert "build/diff" not in path.read_text(), path


def test_a_split_object_is_unscorable_and_its_stand_in_is_not(tmp_path):
    """The premise the stand-in exists for, measured with objdiff-cli against a real split.

    ``objdiff-core`` reads ``<name>.NON_MATCHING`` as "this is not an attempt at the
    target": on the base side it ignores the plain name as well, so the pair is never
    scored.  The stand-in carries the same bytes without the alias, and does score.
    """
    objdiff = shutil.which("objdiff-cli")
    if objdiff is None:
        pytest.skip("objdiff-cli is not installed: the pairing premise needs it")
    split = ROOT / "build" / "asm" / "nonmatchings" / "main" / "sysInitScf.s.o"
    if not split.is_file():
        pytest.skip("no split object in this tree")
    stand_in = basis.split("sysInitScf", split, directory=tmp_path)

    def report(target, base):
        argv = [objdiff, "diff", "sysInitScf", "-1", str(target), "-2", str(base), "-o", "-"]
        done = subprocess.run(argv, cwd=ROOT, capture_output=True, text=True)
        assert done.returncode == 0, done.stderr[:400]
        return json.loads(done.stdout or "{}")

    assert not basis.scored(report(stand_in, split), "sysInitScf")
    assert basis.scored(report(stand_in, stand_in), "sysInitScf")


def test_a_unit_object_holds_every_function_at_its_retail_offset(retail, tmp_path):
    """One target object per *unit*: the unit's retail bytes, every function named in it.

    The object the report is handed must be the unit as retail laid it out -- not a
    per-function split -- so the symbols are at their retail offsets inside one ``.text`` and
    the bytes are the image's own.
    """
    functions = [("later", BASE + 8, 8), ("earlier", BASE, 8), ("last", BASE + 16, 8)]
    path = basis.unit(functions, retail, BASE, BASE + 24, "main/synthetic",
                      directory=tmp_path / "out")
    assert path == basis.unit_path("main/synthetic", tmp_path / "out")
    image = elf.Elf(path)
    text = next(s for s in image.sections if s.name == ".text")
    assert image.data[text.offset:text.offset + text.size] == CODE[:24]
    # Address order, not the order the caller asked in: a report keys on the symbol table.
    assert [(s.name, s.value, s.size, s.bind, s.type) for s in symbols_of(path)] == [
        ("earlier", 0, 8, 1, 2), ("later", 8, 8, 1, 2), ("last", 16, 8, 1, 2)]
    assert image.type == 1 and image.machine == 8


def test_a_unit_object_carries_the_padding_the_promotion_fills(retail, tmp_path):
    """``.text`` is the whole retail region: a promoted object fills the splits' padding too,
    so a target object that stopped at the last symbol would describe a shorter unit."""
    path = basis.unit([("one", BASE, 8)], retail, BASE, BASE + 20, "main/padded",
                      directory=tmp_path)
    image = elf.Elf(path)
    text = next(s for s in image.sections if s.name == ".text")
    assert text.size == 20
    assert image.data[text.offset:text.offset + 20] == CODE[:20]
    assert [s.name for s in image.sections] == ["", ".text", ".symtab", ".strtab", ".shstrtab"]


def test_a_unit_function_outside_the_region_is_refused(retail, tmp_path):
    """Every symbol has to be in the region the object claims to hold."""
    with pytest.raises(basis.Unusable):
        basis.unit([("one", BASE, 8), ("past", BASE + 32, 8)], retail, BASE, BASE + 24,
                   "main/synthetic", directory=tmp_path)
    with pytest.raises(basis.Unusable):
        basis.unit([("before", BASE - 8, 8)], retail, BASE, BASE + 24, "main/synthetic",
                   directory=tmp_path)


def test_a_unit_with_no_region_or_no_functions_is_refused(retail, tmp_path):
    with pytest.raises(basis.Unusable):
        basis.unit([("one", BASE, 8)], retail, BASE, BASE, "main/empty", directory=tmp_path)
    with pytest.raises(basis.Unusable):
        basis.unit([], retail, BASE, BASE + 8, "main/none", directory=tmp_path)


def test_a_unit_object_refuses_the_same_name_twice_and_a_zero_size_symbol(tmp_path):
    """Two functions of one name cannot be paired, and a size-less symbol has no bytes."""
    text = bytes(16)
    with pytest.raises(basis.Unusable):
        basis.object_with_symbols(text, [("one", 0, 8), ("one", 8, 8)])
    with pytest.raises(basis.Unusable):
        basis.object_with_symbols(text, [("one", 0, 0)])
    with pytest.raises(basis.Unusable):
        basis.object_with_symbols(text, [])


def test_the_real_tree_emits_a_units_retail_bytes_under_its_own_names(tmp_path):
    """A known unit of this tree, against the real image: names, offsets and bytes agree.

    Skipped unless the retail ELF and the split tree are in place -- both are gitignored
    inputs, and this test is the claim, not the substitute for them.
    """
    from config import targets
    from toolchain import compile as cc

    target = targets.get()
    if not target.elf.is_file():
        pytest.skip("no retail ELF in this tree")
    try:
        manifests = cc.Manifests(target)
        tu = manifests.tu_named("src/sys/sys_scf.c")
        start, end = cc.split_extent(tu, manifests)
    except Exception as exc:                       # asm/ has not been generated
        pytest.skip(f"the split tree is not configured: {exc}")
    path = basis.unit([(function.name, function.address, function.size)
                       for function in tu.functions],
                      target.elf, start, end, "main/sys_scf", directory=tmp_path)
    image = elf.Elf(path)
    retail = elf.Elf(target.elf)
    assert [(s.name, s.value, s.size) for s in symbols_of(path)] == [
        (function.name, function.address - start, function.size)
        for function in tu.functions]
    text = next(section for section in image.sections if section.name == ".text")
    assert text.size == end - start
    assert image.data[text.offset:text.offset + text.size] == retail.read(start, end - start)
