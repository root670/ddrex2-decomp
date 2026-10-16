"""``revisions``: which SDK archive revision reproduces each library, byte for byte.

The rule under test is the one the survey measured on the previous target: an archive's
object can be linked as-is only when its *whole body* equals retail's, instruction for
instruction, once the fields that carry a link address are masked.  One changed
instruction is a different revision; a size that does not fit the slot is a different
function, and must never be reported as identity.
"""
import pathlib, sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from sdk import match, revisions  # noqa: E402

DEVKIT = pathlib.Path("~/sdk-extract/devkit152/RTLibs_ToolchainSetup/MAINDIR/ee/lib"
                      ).expanduser()
# The header of a real function: `lui`/`addiu` on a relocation-bearing address.
LUI = 0x3C040001          # lui a0, 0x0001  -- the immediate is a link address
ADDIU = 0x24840000        # addiu a0, a0, 0   -- ditto
JR_RA = 0x03E00008
NOP = 0x00000000


def words(*values):
    return b"".join(value.to_bytes(4, "little") for value in values)


def body(count, first=0x00851020):
    """``count`` R-type words: register-register code, never masked."""
    return words(*[first + index for index in range(count)])


def function(name, blob, member="member.o"):
    return {"name": name, "size": len(blob), "member": member, "bytes": blob}


def archive(lib, version, functions, set_name="synthetic"):
    return {"set": set_name, "path": f"/elsewhere/{lib}.a", "lib": lib,
            "versions": [version], "functions": list(functions)}


def image(*pieces, lead=0x100):
    """An image whose first 0x100 bytes are filler and which then holds ``pieces``."""
    data = bytearray(lead)
    at = {}
    for name, blob in pieces:
        at[name] = 0x100000 + len(data)
        data += blob
        data += bytes(8)                       # pad the slot out
    return bytes(data), at


# ---------------------------------------------------------------------------
# the three answers one candidate can give
# ---------------------------------------------------------------------------


def test_a_function_copied_byte_for_byte_is_identical():
    """The baseline: the slot holds exactly the object's body."""
    blob = body(16) + words(JR_RA, NOP)
    result = revisions.classify(blob, blob + bytes(12))
    assert result["verdict"] == "identical"
    assert result["identical"] is True
    assert result["size"] == len(blob)


def test_one_changed_instruction_is_not_identical():
    """A single R-type word differs: the same size, different code."""
    blob = body(16) + words(JR_RA, NOP)
    other = body(16)[:-4] + words(0x00851020 + 999) + words(JR_RA, NOP)
    result = revisions.classify(blob, other + bytes(12))
    assert result["verdict"] == "differs"
    assert result["identical"] is False
    assert result["differing_words"] == 1


def test_a_relocated_immediate_is_masked_and_still_identical():
    """`lui`/`addiu` on a link address are the same instructions at another address."""
    blob = words(LUI, ADDIU, *[0x00851020] * 10, JR_RA, NOP)
    other = words(0x3C04000B, 0x248400F4, *[0x00851020] * 10, JR_RA, NOP)
    result = revisions.classify(blob, other + bytes(4))
    assert result["verdict"] == "identical"
    assert result["masked_words"] == 2
    assert result["exact"] is False


def test_a_size_mismatch_is_reported_as_a_size_mismatch_and_never_as_identity():
    """The slot holds more code than the object: a different function, not a match."""
    blob = body(12) + words(JR_RA, NOP)
    slot = blob + body(4)
    result = revisions.classify(blob, slot)
    assert result["verdict"] == "size"
    assert result["identical"] is False
    assert result["size"] == len(blob)
    assert result["slot"] == len(slot)

    longer = body(20) + words(JR_RA, NOP)
    result = revisions.classify(longer, blob + bytes(4))
    assert result["verdict"] == "size"
    assert result["identical"] is False


def test_a_length_that_is_not_whole_instructions_is_refused():
    with pytest.raises(ValueError):
        revisions.classify(body(12) + b"\0\0\0", body(12) + bytes(8))


# ---------------------------------------------------------------------------
# match: per library stamp, which archive reproduces it
# ---------------------------------------------------------------------------


def test_a_library_whose_object_appears_whole_is_matched():
    blob = body(16) + words(JR_RA, NOP)
    data, at = image(("f", blob))
    corpus = [archive("libdma", "PsIIlibdma2500", [function("sceDmaReset", blob)])]
    result = revisions.match(data, corpus, base=0x100000,
                             stamps={"libdma": "PsIIlibdma3000"})
    entry = result["libraries"]["libdma"]
    assert entry["chosen"] is not None
    assert entry["functions"] == 1
    assert entry["bytes"] == len(blob)
    assert entry["matched"][0]["va"] == at["f"]
    assert entry["stamp_matched"] is False


def test_a_changed_instruction_leaves_the_library_unmatched():
    blob = body(16) + words(JR_RA, NOP)
    other = body(16)[:-4] + words(0x00851020 + 999) + words(JR_RA, NOP)
    data, _ = image(("f", other))
    corpus = [archive("libdma", "PsIIlibdma2500", [function("sceDmaReset", blob)])]
    result = revisions.match(data, corpus, base=0x100000,
                             stamps={"libdma": "PsIIlibdma2500"})
    entry = result["libraries"]["libdma"]
    assert entry["functions"] == 0
    assert entry["chosen"] is None


def test_a_size_that_does_not_fit_the_slot_is_not_identity():
    """The object is longer than retail's slot: a different revision, not a match."""
    retail = body(12) + words(JR_RA, NOP)                 # retail's revision: 14 words
    other = retail + body(6)                              # the archive's: 20 words
    data, _ = image(("f", other))
    corpus = [archive("libdma", "PsIIlibdma2500", [function("sceDmaReset", other)])]
    result = revisions.match(data, corpus, base=0x100000,
                             stamps={"libdma": "PsIIlibdma2500"})
    assert result["libraries"]["libdma"]["functions"] == 0
    assert result["region"]["size_mismatches"] == 1


def test_the_stamp_picks_between_two_revisions_that_both_appear():
    """Byte-identity cannot separate two revisions; the stamp in the binary does."""
    blob = body(16) + words(JR_RA, NOP)
    data, _ = image(("f", blob))
    corpus = [archive("libgraph", "PsIIlibgraph2500", [function("sceGsResetGraph", blob)]),
              archive("libgraph", "PsIIlibgraph3000", [function("sceGsResetGraph", blob)],
                      set_name="devkit152")]
    result = revisions.match(data, corpus, base=0x100000,
                             stamps={"libgraph": "PsIIlibgraph3000"})
    entry = result["libraries"]["libgraph"]
    assert entry["stamp_matched"] is True
    assert entry["chosen"]["set"] == "devkit152"
    assert {c["set"] for c in entry["candidates"]} == {"synthetic", "devkit152"}


def test_a_library_with_nothing_on_disk_says_so():
    data, _ = image(("f", body(16) + words(JR_RA, NOP)))
    corpus = [archive("libgraph", "PsIIlibgraph3000", [function("sceGsResetGraph", body(16))])]
    result = revisions.match(data, corpus, base=0x100000,
                             stamps={"libmc": "PsIIlibmc3020"})
    entry = result["libraries"]["libmc"]
    assert entry["chosen"] is None
    assert entry["functions"] == 0
    assert entry["candidates"] == []


def test_a_smaller_floor_still_counts_the_same_objects():
    """``min_bytes`` is a *floor on evidence*, not a different comparison."""
    blob = body(4) + words(JR_RA, NOP)          # 24 bytes: below the default floor
    data, at = image(("f", blob))
    corpus = [archive("libdma", "PsIIlibdma2500", [function("tiny", blob)])]
    strict = revisions.match(data, corpus, base=0x100000,
                             stamps={"libdma": "PsIIlibdma2500"})
    loose = revisions.match(data, corpus, base=0x100000, min_bytes=1,
                            stamps={"libdma": "PsIIlibdma2500"})
    assert strict["libraries"]["libdma"]["functions"] == 0
    assert loose["libraries"]["libdma"]["functions"] == 1


def test_the_control_finds_nothing_in_shuffled_instructions():
    """The measurement's own noise floor: shuffle the words, and the matches vanish."""
    blob = body(16) + words(JR_RA, NOP)
    data, _ = image(("f", blob), ("g", body(64) + words(JR_RA, NOP)))
    corpus = [archive("libdma", "PsIIlibdma2500", [function("sceDmaReset", blob)])]
    result = revisions.match(data, corpus, base=0x100000,
                             stamps={"libdma": "PsIIlibdma2500"})
    assert result["region"]["control_functions"] == 0


# ---------------------------------------------------------------------------
# the corpus on this machine
# ---------------------------------------------------------------------------


def test_archive_functions_are_the_members_text_symbols(tmp_path):
    """Read a real archive's functions, or skip where the SDK media is not."""
    path = DEVKIT / "libdma.a"
    if not path.exists():
        pytest.skip("the July-2005 devkit extraction is not on this machine")
    functions = revisions.archive_functions(path)
    assert functions, path
    names = {f["name"] for f in functions}
    assert "sceDmaReset" in names
    for f in functions:
        assert f["size"] == len(f["bytes"]) == f["size"] // 4 * 4
        assert f["member"].endswith(".o")


def test_an_archive_carries_its_own_revision_stamp():
    path = DEVKIT / "libdma.a"
    if not path.exists():
        pytest.skip("the July-2005 devkit extraction is not on this machine")
    assert "PsIIlibdma3000" in revisions.archive_versions(path)


# ---------------------------------------------------------------------------
# the committed record
# ---------------------------------------------------------------------------


def test_the_recorded_verdicts_cover_every_stamp_the_template_carries():
    assert {v["library"] for v in revisions.verdicts()} == set(revisions.STAMPS)
    for verdict in revisions.verdicts():
        assert verdict["stamp"] == revisions.STAMPS[verdict["library"]]
        assert verdict["functions"] >= 0 and verdict["bytes"] >= 0


def test_the_committed_record_is_what_the_tool_renders():
    assert revisions.MARKDOWN.read_text() == revisions.render_markdown(revisions.verdicts())


def test_the_record_says_what_is_not_explained():
    """The one revision the template needs that no archive on disk carries."""
    text = revisions.MARKDOWN.read_text()
    assert "PsIIlibmc3020" in text and "PsIIlibeyety1300" in text
    assert "unexplained" in text.lower()
    # Round 1 claimed nothing on disk was 3020. The record now states the corrected claim, and
    # names the claim it corrects -- so the correction cannot quietly disappear either way.
    assert "no *archive* on disk is 3020" in text
    assert 'said "nothing on disk is 3020"' in text


def test_the_record_carries_the_coverage_numbers_the_prose_quotes():
    """Every figure the prose states is a field of the record, so it cannot drift."""
    region = revisions.record()["region"]
    for key in ("functions", "matched_functions", "matched_bytes", "exact_bytes",
                "stamped_functions", "stamped_bytes", "stamped_window_functions",
                "stamped_window_bytes", "dwarf_starts", "dwarf_found",
                "control_functions", "archives", "archive_functions",
                "unexplained_functions", "unexplained_bytes", "below_game_start", "runs"):
        assert key in region, key
    text = revisions.MARKDOWN.read_text()
    assert f"{region['dwarf_found']:,} of the {region['dwarf_starts']:,}" in text
    assert f"{region['stamped_window_functions']:,} slots /" in text
    assert f"{region['archives']:,} archives" in text


def test_the_stamped_union_is_stated_for_both_scopes():
    """The whole-image union and the window-restricted one are different numbers."""
    region = revisions.record()["region"]
    assert region["stamped_window_functions"] <= region["stamped_functions"]
    text = revisions.MARKDOWN.read_text()
    whole = f"{region['stamped_functions']:,} slots /\n{region['stamped_bytes']:,} B"
    assert whole in text, "the whole-image union is not labelled as such"
    window = (f"{region['stamped_window_functions']:,} slots / "
              f"{region['stamped_window_bytes']:,} B")
    assert window in text


def test_the_committed_lead_names_the_libmc_3020_link_and_its_limitation():
    """`libmc` 3.0.2 exists on disk as a linked binary: a lead, not a pinnable object."""
    lead = revisions.record()["libmc_lead"]
    assert lead["stamp"] == "PsIIlibmc3020"
    assert lead["path"].endswith("YNCFTool/Cdburn/Slus_123.45")
    assert "linked binary, not an archive" in lead["limitation"]
    assert 0 <= lead["unexplained_identical"] <= lead["unexplained"]
    assert lead["path"] in revisions.MARKDOWN.read_text()


def test_the_lead_stamp_is_where_the_record_says_it_is():
    import pytest
    lead = revisions.record()["libmc_lead"]
    path = pathlib.Path(lead["path"]).expanduser()
    if not path.exists():
        pytest.skip("the July-2005 devkit extraction is not on this machine")
    assert revisions.lead_offset(path) == lead["stamp_offset"]


def test_the_corpus_holds_every_archive_under_the_package_roots():
    """The scan is the archives on disk, not the archives one directory happened to hold.

    An archive the corpus leaves out must be one with no code at all, or one whose container
    does not parse -- never an archive that simply was not looked at.
    """
    seen = {pathlib.Path(entry["path"]) for entry in revisions.corpus()}
    missing = []
    for root, _ in revisions.roots():
        for archive in sorted(root.rglob("*.a")):
            if archive in seen:
                continue
            try:
                found = revisions.archive_functions(archive)
            except Exception:
                continue
            if found:
                missing.append(str(archive))
    assert missing == []


def test_the_stamp_of_a_library_is_normalised_to_one_token():
    """`PsIIlibdma  3000` on disk and `PsIIlibdma3000` in the record are the same stamp."""
    assert revisions.normalise("PsIIlibdma  3000") == revisions.normalise("PsIIlibdma3000")
