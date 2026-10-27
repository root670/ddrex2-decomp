"""G2 -- the promotion rule: a unit's `.text` **and** its `.debug` **and** its `.line` bytes.

`verdicts` is what every promotion is judged by, so it is tested here on synthetic files: the
three parts are compared independently (G1 can be green while a chunk is not, and vice versa), a
divergence in each is reported as *that* part failing, and a name that matches no translation unit
is a usage error rather than an empty report.
"""

import json
import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))

from config import targets  # noqa: E402
from verify import g2  # noqa: E402

GEOMETRY = targets.Geometry(
    elf_size=0x2000, loadable_rom=0x80, loadable_end=0x1000, loadable_vram=0x00100000,
    bss_end=0x00110000,
    trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400), ("line", 0x1410, 0x100),
              ("section_headers", 0x1510, 0x2000 - 0x1510)),
    debug_size=0x400, line_size=0x100, image_elf_offset=0x92000)
TU = "src/probe.c"
FUNCTIONS = ((0x00100000, 0x00100010, "probe_one"), (0x00100010, 0x00100040, "probe_two"))


@pytest.fixture
def manifests(tmp_path):
    cus = [dict(index=0, kind="tu", offset=0, size=0x40, name="probe.c", file=TU,
                low_pc=None, high_pc=None, stmt_list=None)]
    chunks = [dict(section=".debug", offset=0, size=0x400, tunits=[0])]
    for index, (low, high, _) in enumerate(FUNCTIONS, start=1):
        cus.append(dict(index=index, kind="function", offset=0x40 * index, size=0x40,
                        name=f"probe_{index}", file=TU, low_pc=low, high_pc=high,
                        stmt_list=(index - 1) * 0x40))
        chunks[0]["tunits"].append(index)
        chunks.append(dict(section=".line", offset=(index - 1) * 0x40, size=0x40,
                           tunits=[index]))
    cus_path, chunks_path = tmp_path / "cus.json", tmp_path / "debug_chunks.json"
    symbols_path = tmp_path / "symbol_addrs.txt"
    cus_path.write_text(json.dumps(cus))
    chunks_path.write_text(json.dumps(chunks))
    symbols_path.write_text("".join(
        f"{name} = 0x{low:08X};  // type:func size:0x{high - low:X} provenance:dwarf\n"
        for low, high, name in FUNCTIONS))
    return cus_path, chunks_path, symbols_path


def target_image(tmp_path, name="built", flip=None):
    """A stand-in for both sides of the comparison; ``flip`` changes one byte of the copy."""
    path = tmp_path / name
    data = bytearray(b"\x3D" * GEOMETRY.elf_size)
    if flip is not None:
        data[flip] ^= 0xFF
    path.write_bytes(bytes(data))
    return path


def verdicts(tmp_path, manifests, flip=None):
    cus, chunks, symbols = manifests
    retail = target_image(tmp_path, "retail")
    built = target_image(tmp_path, "built", flip)
    return g2.verdicts(built, retail, TU, cus, chunks, symbols, GEOMETRY)


def test_a_unit_whose_bytes_all_match_is_promoted(tmp_path, manifests):
    tu, report = verdicts(tmp_path, manifests)
    assert tu == TU
    assert [verdict.what for verdict in report] == ["text", "debug chunk", "line chunk"]
    assert all(verdict.ok for verdict in report), report
    assert "VA 0x00100000-0x00100040" in report[0].detail


def test_a_code_byte_fails_the_text_part_and_names_its_function(tmp_path, manifests):
    offset = GEOMETRY.offset_of(0x00100014)          # inside `probe_two`, the second function
    _, report = verdicts(tmp_path, manifests, flip=offset)
    assert report[0].what == "text" and report[0].ok is False
    assert f"0x{offset:X}" in report[0].detail and "probe_two" in report[0].detail
    assert report[1].ok and report[2].ok, "the debug bytes are untouched and must stay green"


def test_a_debug_byte_fails_only_the_debug_part(tmp_path, manifests):
    _, report = verdicts(tmp_path, manifests, flip=0x1014)
    assert report[0].ok and report[1].ok is False and report[2].ok
    assert "0x1014" in report[1].detail and ".debug" in report[1].detail


def test_a_line_byte_fails_only_the_line_part(tmp_path, manifests):
    _, report = verdicts(tmp_path, manifests, flip=0x1414)
    assert report[0].ok and report[1].ok and report[2].ok is False
    assert "0x1414" in report[2].detail and ".line" in report[2].detail


def test_the_manifests_join_names_addresses_and_chunks(tmp_path, manifests):
    cus, chunks, symbols = manifests
    loaded = g2.Manifests(cus, chunks, symbols, GEOMETRY)
    assert loaded.tu_named("probe") == TU
    assert loaded.tu_named("probe.c") == TU
    assert loaded.tu_named(TU) == TU
    assert loaded.symbol_at(0x00100010) == "probe_two"
    # The ledger names function *starts*: an address inside one has no entry, and falls back to
    # the name its address gives it rather than to the function that contains it.
    assert loaded.symbol_at(0x00100011) == "func_00100011"
    owner = loaded.record_at_pc(0x00100020)
    assert owner["low_pc"] == 0x00100010 and owner["file"] == TU
    assert [chunk["offset"] for chunk in loaded.line_chunks_of(TU)] == [0, 0x40]
    assert [chunk["offset"] for chunk in loaded.debug_chunks_of(TU)] == [0]
    assert loaded.describe(0x84)["function"] == "probe_one"


def test_a_name_that_matches_no_unit_is_a_usage_error(tmp_path, manifests):
    cus, chunks, symbols = manifests
    loaded = g2.Manifests(cus, chunks, symbols, GEOMETRY)
    with pytest.raises(g2.UnknownUnit):
        loaded.tu_named("nosuch")
    with pytest.raises(g2.UnknownUnit):
        g2.verdicts(target_image(tmp_path), target_image(tmp_path, "retail"), "nosuch",
                    cus, chunks, symbols, GEOMETRY)


# ---------------------------------------------------------------------------
# overlay units: the retail side is the disc image's blob, not the ELF's zero fill
# ---------------------------------------------------------------------------

#: One overlay window, and the addresses the overlay unit's functions load at (the code region
#: is ``vaddr + 0x40`` .. ``vaddr + 0x40 + code_end``, which is where the first function sits).
OVERLAY = targets.Overlay("probe_rel4cd", 0x00200000, 0x200, 0x100, 0xC0, 0x100, 0x1000)
OVERLAY_FUNCTIONS = ((0x00200080, 0x00200090), (0x00200090, 0x002000C0))
OVERLAY_TU = "src/probe/ov.c"
OVERLAY_BLOB = (bytes((index * 3) & 0xFF for index in range(0x100 + targets.OVERLAY_HEADER))
                + b"\xAA" * 0xC0)


def overlay_geometry():
    return targets.Geometry(
        elf_size=GEOMETRY.elf_size, loadable_rom=GEOMETRY.loadable_rom,
        loadable_end=GEOMETRY.loadable_end, loadable_vram=GEOMETRY.loadable_vram,
        bss_end=GEOMETRY.bss_end, trailing=GEOMETRY.trailing,
        debug_size=GEOMETRY.debug_size, line_size=GEOMETRY.line_size,
        image_elf_offset=GEOMETRY.image_elf_offset, overlays=(OVERLAY,))


@pytest.fixture
def overlay_manifests(tmp_path):
    """The same shape as ``manifests``, with the unit in an overlay and its records withheld.

    ``unplaced_symbols.txt`` is where an overlay record lives (the oracle withholds it with the
    reason and the module): the placed ledger has nothing at those addresses.
    """
    cus = [dict(index=0, kind="tu", offset=0, size=0x40, name="ov.c", file=OVERLAY_TU,
                overlay=OVERLAY.name, low_pc=None, high_pc=None, stmt_list=None)]
    chunks = [dict(section=".debug", offset=0, size=0x400, tunits=[0])]
    for index, (low, high) in enumerate(OVERLAY_FUNCTIONS, start=1):
        cus.append(dict(index=index, kind="function", offset=0x40 * index, size=0x40,
                        name=f"probe_ov_{index}", file=OVERLAY_TU, overlay=OVERLAY.name,
                        low_pc=low, high_pc=high, stmt_list=0))
        chunks[0]["tunits"].append(index)
        chunks.append(dict(section=".line", offset=(index - 1) * 0x40, size=0x40,
                           tunits=[index]))
    cus_path, chunks_path = tmp_path / "cus.json", tmp_path / "debug_chunks.json"
    symbols_path = tmp_path / "symbol_addrs.txt"
    cus_path.write_text(json.dumps(cus))
    chunks_path.write_text(json.dumps(chunks))
    symbols_path.write_text("")
    (tmp_path / "unplaced_symbols.txt").write_text("".join(
        f"nrmes{index} = 0x{low:08X}; // type:func provenance:dwarf "
        f"reason:outside every declared segment overlay:{OVERLAY.name}\n"
        for index, (low, _high) in enumerate(OVERLAY_FUNCTIONS, start=1)))
    return cus_path, chunks_path, symbols_path


def overlay_image(tmp_path):
    path = tmp_path / "disc.iso"
    path.write_bytes(b"\x00" * OVERLAY.image_offset + OVERLAY_BLOB)
    return path


def overlay_built(tmp_path, payload, name="built.elf", mapped=True):
    """A built ELF for the overlay: with ``mapped`` it carries ``payload`` at the window's code
    base (what a per-overlay link would produce), without it the address maps no bytes at all
    (what the current graph produces -- its reservation is zero-fill)."""
    from tests import target_support
    path = tmp_path / name
    segments = ([(OVERLAY.code_vram, len(payload), payload)] if mapped
                else [(0x00100000, 0x40, b"\x3D" * 0x40)])
    target_support.write_elf(path, segments=segments,
                             sections=[(".debug", b"\x3D" * 0x400),
                                       (".line", b"\x3D" * 0x100)])
    # The chunked sections are read at the geometry's *file* offsets (0x1010/0x1410), so the
    # synthetic image is padded to the measured size with the byte both sides carry there: the
    # overlay verdict must not disturb the `.debug`/`.line` comparison.
    path.write_bytes(path.read_bytes().ljust(GEOMETRY.elf_size, b"\x3D"))
    return path


def overlay_verdicts(tmp_path, manifests, payload=None, built_name="built.elf"):
    cus, chunks, symbols = manifests
    image = overlay_image(tmp_path)
    built = overlay_built(tmp_path, payload, built_name, mapped=payload is not None)
    retail = target_image(tmp_path, "retail")
    return g2.verdicts(built, retail, OVERLAY_TU, cus, chunks, symbols, overlay_geometry(),
                       image=image)


def test_an_overlay_units_text_compares_the_disc_blob_and_fails_loudly(tmp_path,
                                                                      overlay_manifests):
    """The build maps no bytes at an overlay address, so ``text ok`` would be the lie: the
    verdict names the span, the module, the image offset and retail's first byte there."""
    _, report = overlay_verdicts(tmp_path, overlay_manifests)
    text = report[0]
    assert text.what == "text" and text.ok is False
    assert "VA 0x00200080-0x002000C0" in text.detail and "overlay probe_rel4cd" in text.detail
    assert "maps no bytes there" in text.detail
    assert "0x1080" in text.detail and "0x00200080" in text.detail
    assert report[1].ok and report[2].ok, "the ELF's chunks are untouched"


def test_an_overlay_units_text_is_ok_when_the_build_carries_the_blobs_bytes(
        tmp_path, overlay_manifests):
    """The comparison is real in both directions: identical bytes are green."""
    payload = OVERLAY_BLOB[0x40:0x140]                 # the whole code region
    _, report = overlay_verdicts(tmp_path, overlay_manifests, payload=payload)
    assert report[0].ok, report[0].detail
    assert "overlay probe_rel4cd" in report[0].detail


def test_an_overlay_text_difference_names_the_first_byte_and_its_va(tmp_path,
                                                                   overlay_manifests):
    payload = bytearray(OVERLAY_BLOB[0x40:0x140])
    payload[0x44] ^= 0xFF                              # VA 0x00200084, image 0x1084
    _, report = overlay_verdicts(tmp_path, overlay_manifests, payload=bytes(payload))
    text = report[0]
    assert text.ok is False
    assert "first differing byte at image 0x1084" in text.detail
    assert "VA 0x00200084" in text.detail
    assert report[1].ok and report[2].ok


def test_an_overlay_unit_without_the_image_is_a_named_refusal(tmp_path, overlay_manifests):
    cus, chunks, symbols = overlay_manifests
    built = target_image(tmp_path, "built")
    retail = target_image(tmp_path, "retail")
    with pytest.raises(g2.UnknownUnit) as refusal:
        g2.verdicts(built, retail, OVERLAY_TU, cus, chunks, symbols, overlay_geometry())
    assert "disc image" in str(refusal.value)


def test_a_main_unit_at_an_overlay_address_is_refused_not_mapped(tmp_path, manifests):
    """No window, no mapping: the address has no file offset, and the verdict says so instead
    of comparing ``.line`` against itself."""
    cus, chunks, symbols = manifests
    cus_path = pathlib.Path(cus)
    records = json.loads(cus_path.read_text())
    for record in records:
        if record.get("kind") == "function":
            record["low_pc"] += 0x6F0000
            record["high_pc"] += 0x6F0000
    cus_path.write_text(json.dumps(records))

    built = target_image(tmp_path, "built")
    retail = target_image(tmp_path, "retail")
    with pytest.raises(targets.OutsideLoadableImage) as refusal:
        g2.verdicts(built, retail, TU, cus, chunks, symbols, GEOMETRY)
    assert "0x007F0000" in str(refusal.value) and "no file offset" in str(refusal.value)


def test_an_overlay_unit_reads_its_text_from_the_modules_own_link(tmp_path,
                                                                  overlay_manifests):
    """The main image never carries an overlay blob's bytes, so the built side comes from the
    module's link; without it the verdict has nothing to compare and says so."""
    cus, chunks, symbols = overlay_manifests
    payload = OVERLAY_BLOB[0x40:0x140]
    image = overlay_image(tmp_path)
    retail = target_image(tmp_path, "retail")
    main_only = overlay_built(tmp_path, None, "main.elf", mapped=False)
    linked = overlay_built(tmp_path, payload, "net_rel4cd.elf")
    with pytest.raises(AssertionError):
        # The main image alone is still the "no bytes there" refusal, not a silent pass.
        assert g2.verdicts(main_only, retail, OVERLAY_TU, cus, chunks, symbols,
                           overlay_geometry(), image=image)[1][0].ok
    _, report = g2.verdicts(main_only, retail, OVERLAY_TU, cus, chunks, symbols,
                            overlay_geometry(), image=image, overlay_elf=linked)
    assert report[0].ok, report[0].detail
    assert "overlay probe_rel4cd" in report[0].detail
    assert report[1].ok and report[2].ok
