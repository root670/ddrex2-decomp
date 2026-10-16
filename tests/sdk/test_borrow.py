"""``borrow``: catalogue the corpora, propose names, and accept only what validates.

The rules under test are the ones the survey measured: a corpus that publishes bytes is
checked word for word (after relocation masking), a corpus that publishes sizes is checked
against our own function bounds, and a name that is only *plausible* -- a single size that
happens to match, an alignment that could have landed in two places -- does not enter the
ledger.
"""
import pathlib
import pytest, sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from sdk import borrow, match  # noqa: E402

RECVX_SAMPLE = """\
// a corpus's own symbol file, in splat syntax
D_20000010                     = 0x20000010; // ignore:true
.L002CAEE4                     = 0x002CAEE4; // type:label
_root                          = 0x001000B8; // type:label visibility:local
sceGsResetGraph                = 0x001000C0; // size:0x110
sceGsGetGParam                 = 0x001001D0; // size:0xC
_loopMulMatrix                 = 0x001029EC; // visibility:local
write                          = 0x0010C080; // size:0x48
main                           = 0x0012B0A0; // size:0x44
sceVu0ApplyMatrix              = 0x0012B0F0; // size:0x58
"""


def words(*values):
    return b"".join(value.to_bytes(4, "little") for value in values)


def from_bytes(records, blobs):
    """The candidate callback ``borrow`` takes: address -> bytes."""
    return {record["address"]: blobs[record["address"]] for record in records}


# ---------------------------------------------------------------------------
# the corpora catalogue
# ---------------------------------------------------------------------------


def test_corpora_records_every_surveyed_source_with_its_licence():
    catalogue = {entry["key"]: entry for entry in borrow.corpora()}
    assert {"recvx", "godhand", "sly1", "ps2sdk", "ghidra-patterns", "mvc2",
            "oni2", "sdk152"} <= set(catalogue)
    assert catalogue["recvx"]["licence"] == "MIT"
    assert catalogue["godhand"]["licence"] == "MIT"
    assert catalogue["sly1"]["licence"] == "CC0-1.0"
    assert catalogue["ps2sdk"]["licence"] == "AFL-2.0"
    assert catalogue["ghidra-patterns"]["licence"] == "Apache-2.0"
    for key, entry in catalogue.items():
        assert entry["publishes"], key
        assert entry["entry_point"], key


def test_corpora_refuses_to_copy_from_the_corpus_without_a_licence():
    """mvc2-ps2-decomp declares no licence: nothing may be copied out of it."""
    entry = {e["key"]: e for e in borrow.corpora()}["mvc2"]
    assert entry["licence"] is None
    assert entry["copyable"] is False
    assert "no licence" in entry["note"].lower()


def test_corpora_that_publish_sizes_say_so():
    catalogue = {entry["key"]: entry for entry in borrow.corpora()}
    assert catalogue["recvx"]["sizes"] is True
    assert catalogue["recvx"]["bytes"] is False
    assert catalogue["godhand"]["sizes"] is False
    assert catalogue["oni2"]["bytes"] is True and catalogue["oni2"]["sizes"] is True
    assert catalogue["sdk152"]["sizes"] is True
    # An archive member *is* code: the devkit publishes the objects, so a name from it can be
    # byte-validated (77 of its names are whole-function identical under relocation masking).
    assert catalogue["sdk152"]["bytes"] is True


# ---------------------------------------------------------------------------
# reading a corpus's symbol file
# ---------------------------------------------------------------------------


def test_parse_splat_symbols_keeps_only_sized_functions_of_the_library_region():
    records = borrow.parse_splat_symbols(RECVX_SAMPLE, game_start=0x0012B0A0)
    names = [r["name"] for r in records]
    assert names == ["sceGsResetGraph", "sceGsGetGParam", "write"]
    assert records[0]["size"] == 0x110
    assert records[0]["address"] == 0x001000C0


def test_parse_splat_symbols_skips_ignored_labels_unsized_and_out_of_range_lines():
    records = borrow.parse_splat_symbols(RECVX_SAMPLE, game_start=0x0012B0A0)
    names = {r["name"] for r in records}
    assert "D_20000010" not in names          # ignore:true
    assert ".L002CAEE4" not in names           # type:label
    assert "_root" not in names                # type:label
    assert "_loopMulMatrix" not in names       # no size published
    assert "main" not in names                 # at the corpus's game start, not library code
    assert "sceVu0ApplyMatrix" not in names    # past the game start


def test_parse_function_names_counts_only_marked_functions():
    """Corroboration is about functions: a sized data symbol is not one."""
    text = ("sceGsResetGraph = 0x001000C0; // type:func\n"
            "g_table = 0x002483B8; // size:0x9\n"
            ".L002CAEE4 = 0x002CAEE4; // type:label\n"
            "D_20000010 = 0x20000010; // ignore:true\n")
    assert borrow.parse_function_names(text) == {"sceGsResetGraph"}


def test_parse_source_paths_attributes_a_name_to_its_sdk_source():
    """sly1 labels its entries with the SDK source file the function came from."""
    text = ("////////////////////////////////////////\n"
            "// /usr/local/sce/ee/gcc/src/newlib/libm/math/wf_fmod.c\n"
            "////////////////////////////////////////\n"
            "fmodf = 0x2058a0; // type:func\n"
            "\n"
            "////////////////////////////////////////\n"
            "// libdma.c\n"
            "////////////////////////////////////////\n"
            "memclr = 0x202768; // type:func\n")
    assert borrow.parse_source_paths(text) == {
        "fmodf": "/usr/local/sce/ee/gcc/src/newlib/libm/math/wf_fmod.c",
        "memclr": "libdma.c"}


# ---------------------------------------------------------------------------
# proposing from a sequence of sizes
# ---------------------------------------------------------------------------


def test_align_accepts_a_unique_run_of_three():
    ours = [0x10, 0x20, 0x30, 0x40]
    theirs = [0x20, 0x30, 0x40]
    blocks, rejected = borrow.align(ours, theirs)
    assert blocks == [(1, 0, 3)]
    assert rejected == []


def test_align_rejects_a_single_size_match():
    """A lone size equality is the coincidence the survey warns about."""
    blocks, rejected = borrow.align([0x10, 0x20, 0x30], [0x20, 0x99, 0x88])
    assert blocks == []
    assert [r["reason"] for r in rejected] == ["isolated"]


def test_align_rejects_a_run_that_could_have_landed_twice():
    ours = [0x10, 0x20, 0x30, 0x10, 0x20, 0x30]
    theirs = [0x10, 0x20, 0x30]
    blocks, rejected = borrow.align(ours, theirs)
    assert blocks == []
    assert [r["reason"] for r in rejected] == ["ambiguous"]


def test_align_keeps_the_min_run_that_was_measured():
    ours = [4, 4, 8, 0x1C]
    theirs = [4, 8, 0x1C]
    blocks, _ = borrow.align(ours, theirs, min_run=3)
    assert blocks == [(1, 0, 3)]


def test_run_proposals_name_every_function_in_the_run():
    ours = [{"symbol": "func_00100008", "address": 0x100008, "size": 0x10},
            {"symbol": "func_00100018", "address": 0x100018, "size": 0x20},
            {"symbol": "func_00100038", "address": 0x100038, "size": 0x30}]
    theirs = [{"name": "sceA", "address": 0x1000, "size": 0x10},
              {"name": "sceB", "address": 0x1010, "size": 0x20},
              {"name": "sceC", "address": 0x1030, "size": 0x30}]
    proposals, refused = borrow.run_proposals(ours, theirs, source="recvx")
    assert refused == []
    assert [(p["address"], p["name"]) for p in proposals] == [
        (0x100008, "sceA"), (0x100018, "sceB"), (0x100038, "sceC")]
    assert {p["tier"] for p in proposals} == {"run"}
    assert proposals[0]["evidence"]["run"] == 3
    assert proposals[0]["evidence"]["source_address"] == 0x1000


def _split_file(text):
    return ('.include "macro.inc"\n.align 3\n' + text)


def test_split_functions_are_in_address_order_not_file_name_order(tmp_path):
    """A split file is named after its symbol, and a file name is not an address."""
    # The *file* names run backwards against the addresses, which is what a directory read
    # would hand over.
    (tmp_path / "zzz_low.s").write_text(_split_file(
        "nonmatching low, 0x30\n\n/* 88 00100008 280C0070 */  padduw $1, $0, $0\n"))
    (tmp_path / "aaa_high.s").write_text(_split_file(
        "nonmatching high, 0x10\n\n/* 38 00100038 280C0070 */  padduw $1, $0, $0\n"))
    functions = borrow.split_functions(tmp_path)
    assert [(r["symbol"], r["address"], r["size"]) for r in functions] == [
        ("low", 0x100008, 0x30), ("high", 0x100038, 0x10)]


def test_the_yield_and_its_control_are_computed_over_one_sequence(tmp_path):
    """The run proposer and the chance control must see the *same* order of our functions.

    This is the invariant behind three bugs in this file: `run_proposals` sorts its own copy of
    our functions while `coincidence_rate` is handed a sequence from somewhere else, so a control
    over a differently-ordered sequence measures nothing.  The synthetic split's file names run
    against its addresses, so the two orders differ here and the test fails if either side
    stops agreeing.
    """
    (tmp_path / "zzz_low.s").write_text(_split_file(
        "nonmatching low, 0x30\n\n/* 88 00100008 280C0070 */  padduw $1, $0, $0\n"))
    (tmp_path / "aaa_high.s").write_text(_split_file(
        "nonmatching high, 0x10\n\n/* 38 00100038 280C0070 */  padduw $1, $0, $0\n"))
    ours = borrow.split_functions(tmp_path)
    # The corpus's records run *against* their addresses too, so a re-sort on either side -- ours
    # by the proposer, the corpus's by anything that "helpfully" orders it -- breaks the alignment
    # and trips this test.  An ascending corpus would only catch the first of those.
    theirs = [{"name": "first", "address": 0x40, "size": 0x30},
              {"name": "second", "address": 0x00, "size": 0x10}]
    proposals, _ = borrow.run_proposals(ours, theirs, source="synthetic", min_run=2)
    control = borrow.coincidence_rate([r["size"] for r in ours],
                                      [r["size"] for r in theirs], min_run=2, trials=1)
    assert len(proposals) == 2
    assert control["observed"] == len(proposals), (
        "the control and the yield disagree about the sequence they measured")


def test_run_proposals_keep_the_corpus_order_it_is_given():
    """An archive member restarts at address 0, so member order is the evidence.

    Sorting the corpus's records by address would interleave the members and align our image
    against a sequence no linker produced.
    """
    ours = [{"symbol": "func_1", "address": 0x100, "size": 0x10},
            {"symbol": "func_2", "address": 0x110, "size": 0x20},
            {"symbol": "func_3", "address": 0x130, "size": 0x30}]
    # Three records, one per member, in member order -- and their addresses run *backwards*,
    # which is what an address sort would destroy.
    theirs = [{"name": "member_a", "address": 0x40, "size": 0x10},
              {"name": "member_b", "address": 0x00, "size": 0x20},
              {"name": "member_c", "address": 0x00, "size": 0x30}]
    proposals, refused = borrow.run_proposals(ours, theirs, source="sdk152:libx.a")
    assert refused == []
    assert [p["name"] for p in proposals] == ["member_a", "member_b", "member_c"]
    assert [p["address"] for p in proposals] == [0x100, 0x110, 0x130]


def test_run_proposals_report_the_size_matches_that_were_not_evidence():
    """A lone size equality is refused, and the refusal says which function it was about."""
    ours = [{"symbol": "func_00100008", "address": 0x100008, "size": 0x10},
            {"symbol": "func_00100018", "address": 0x100018, "size": 0x20}]
    theirs = [{"name": "sceA", "address": 0x1000, "size": 0x20},
              {"name": "sceB", "address": 0x1040, "size": 0x99}]
    proposals, refused = borrow.run_proposals(ours, theirs, source="recvx")
    assert proposals == []
    assert [(r["source"], r["reason"], r["address"], r["names"]) for r in refused] == [
        ("recvx", "isolated", 0x100018, ["sceA"])]


# ---------------------------------------------------------------------------
# proposing from bytes
# ---------------------------------------------------------------------------


def test_byte_proposals_are_size_exact_and_masked():
    ours = [{"symbol": "func_00100288", "address": 0x100288, "size": 0x30}]
    theirs = [{"name": "sceGsResetGraph", "address": 0x4A0000, "size": 0x30}]
    our_bytes = {0x100288: words(0x27BDFFF0, 0x3C020021, 0x2442C410, 0xAC820000,
                                 0x03E00008, 0x00000000, 0x00000000, 0x00000000,
                                 0x00000000, 0x00000000, 0x00000000, 0x00000000)}
    their_bytes = {0x4A0000: words(0x27BDFFF0, 0x3C02004A, 0x2442A0C0, 0xAC820000,
                                   0x03E00008, 0x00000000, 0x00000000, 0x00000000,
                                   0x00000000, 0x00000000, 0x00000000, 0x00000000)}
    proposals, rejected = borrow.byte_proposals(ours, theirs, our_bytes, their_bytes,
                                                source="oni2")
    assert rejected == []
    assert [(p["name"], p["tier"]) for p in proposals] == [("sceGsResetGraph", "bytes")]
    assert proposals[0]["evidence"]["masked_words"] == 2
    assert proposals[0]["evidence"]["exact"] is False


def test_byte_proposals_credit_the_whole_body_when_several_candidates_share_a_name():
    """Two members with one name still give whole-body evidence for the row's name."""
    ours = [{"symbol": "func_00100288", "address": 0x100288, "size": 0x30}]
    theirs = [{"name": "kCopy", "address": 0x4A0000, "size": 0x30},
              {"name": "kCopy", "address": 0x4B0000, "size": 0x30}]
    blob = words(*([0x27BDFFF0] * 12))
    proposals, refused = borrow.byte_proposals(
        ours, theirs, {0x100288: blob}, {0x4A0000: blob, 0x4B0000: blob}, source="sdk152")
    assert refused == []
    assert proposals[0]["name"] == "kCopy"
    assert proposals[0]["evidence"]["candidates"] == 2
    assert proposals[0]["evidence"]["whole_function"] is True


def test_byte_proposals_reject_a_different_size():
    ours = [{"symbol": "func_00100288", "address": 0x100288, "size": 0x30}]
    theirs = [{"name": "sceGsResetGraph", "address": 0x4A0000, "size": 0x2C}]
    blob = words(*([0x27BDFFF0] * 12))
    proposals, rejected = borrow.byte_proposals(
        ours, theirs, {0x100288: blob}, {0x4A0000: blob}, source="oni2")
    assert proposals == [] and rejected == []


def test_byte_proposals_reject_candidates_that_disagree_about_the_name():
    ours = [{"symbol": "func_00100288", "address": 0x100288, "size": 0x30}]
    theirs = [{"name": "sceOne", "address": 0x4A0000, "size": 0x30},
              {"name": "sceTwo", "address": 0x4B0000, "size": 0x30}]
    blob = words(*([0x27BDFFF0] * 12))
    proposals, rejected = borrow.byte_proposals(
        ours, theirs, {0x100288: blob},
        {0x4A0000: blob, 0x4B0000: blob}, source="oni2")
    assert proposals == []
    assert rejected[0]["reason"] == "names disagree"
    assert rejected[0]["names"] == ["sceOne", "sceTwo"]


# ---------------------------------------------------------------------------
# deciding between sources
# ---------------------------------------------------------------------------


def test_decide_refuses_a_tie_that_disagrees():
    """Equally strong sources naming one address differently: nothing is renamed."""
    proposals = [
        {"address": 0x100288, "symbol": "func_00100288", "size": 0x30, "name": "sceAlpha",
         "tier": "run", "source": "recvx", "evidence": {"run": 3}},
        {"address": 0x100288, "symbol": "func_00100288", "size": 0x30, "name": "sceBeta",
         "tier": "run", "source": "sdk152:libgp.a", "evidence": {"run": 3}},
    ]
    accepted, rejected = borrow.decide(proposals)
    assert accepted == []
    assert rejected[0]["reason"] == "conflict"
    assert rejected[0]["names"] == ["sceAlpha", "sceBeta"]


def test_decide_prefers_the_byte_tier_and_keeps_the_other_as_corroboration():
    proposals = [
        {"address": 0x100288, "symbol": "func_00100288", "size": 0x30, "name": "sceAlpha",
         "tier": "run", "source": "recvx", "evidence": {"run": 5}},
        {"address": 0x100288, "symbol": "func_00100288", "size": 0x30, "name": "sceAlpha",
         "tier": "bytes", "source": "oni2", "evidence": {"whole_function": True}},
    ]
    accepted, rejected = borrow.decide(proposals)
    assert rejected == []
    assert accepted[0]["source"] == "oni2"
    assert accepted[0]["tier"] == "bytes"
    assert accepted[0]["also"] == ["recvx"]


def test_decide_prefers_a_long_run_to_a_short_one_and_records_the_loser():
    """A run of 37 beats a run of 3: the chance-level yield lives in the short runs."""
    proposals = [
        {"address": 0x100288, "symbol": "func_00100288", "size": 0x30, "name": "sceVu0AddVector",
         "tier": "run", "source": "recvx", "evidence": {"run": 37}},
        {"address": 0x100288, "symbol": "func_00100288", "size": 0x30, "name": "sceGpSetAbe",
         "tier": "run", "source": "sdk152:libgp.a", "evidence": {"run": 3}},
    ]
    accepted, rejected = borrow.decide(proposals)
    assert rejected == []
    assert accepted[0]["name"] == "sceVu0AddVector"
    assert accepted[0]["contested"] == ["sceGpSetAbe (sdk152:libgp.a)"]


def test_decide_rejects_a_name_another_symbol_already_carries():
    proposals = [{"address": 0x100288, "symbol": "func_00100288", "size": 0x30,
                  "name": "sysInitScf", "tier": "run", "source": "recvx", "evidence": {}}]
    accepted, rejected = borrow.decide(proposals, taken={"sysInitScf": 0x0021C420})
    assert accepted == []
    assert rejected[0]["reason"] == "name taken"


def test_disambiguate_gives_repeated_names_the_ledgers_own_suffix():
    """A routine linked into several members is several functions with one name."""
    rows = [{"address": 0x200, "name": "kCopy"}, {"address": 0x100, "name": "kCopy"},
            {"address": 0x300, "name": "sceA"}]
    out, renamed = borrow.disambiguate(rows)
    assert [(r["address"], r["name"]) for r in out] == [
        (0x100, "kCopy"), (0x200, "kCopy_1"), (0x300, "sceA")]
    assert renamed[0]["borrowed_as"] == "kCopy"


def test_disambiguate_skips_a_suffix_the_tree_already_carries():
    rows = [{"address": 0x100, "name": "kCopy"}, {"address": 0x200, "name": "kCopy"}]
    out, _ = borrow.disambiguate(rows, taken={"kCopy_1"})
    assert [r["name"] for r in out] == ["kCopy", "kCopy_2"]


# ---------------------------------------------------------------------------
# validation
# ---------------------------------------------------------------------------


def test_validate_accepts_a_size_that_matches_our_bounds():
    blob = words(0x27BDFFF0, 0x03E00008)
    result = borrow.validate("sceGsGetGParam", len(blob), blob)
    assert result["accepted"] is True
    assert result["evidence"]["bytes"] is None
    assert "size alone" in result["reason"]


def test_validate_rejects_a_size_mismatch():
    blob = words(0x27BDFFF0, 0x03E00008)
    result = borrow.validate("sceGsGetGParam", 0x30, blob)
    assert result["accepted"] is False
    assert "size mismatch" in result["reason"]
    assert "0x30" in result["reason"] and "0x8" in result["reason"]


def test_validate_rejects_published_bytes_that_differ():
    ours = words(0x27BDFFF0, 0x03E00008)
    theirs = words(0x27BDFFF0, 0x00000025)
    result = borrow.validate("sceGsGetGParam", len(ours), ours, published_bytes=theirs)
    assert result["accepted"] is False
    assert "word 1" in result["reason"]


def test_validate_accepts_published_bytes_that_differ_only_by_relocation():
    ours = words(0x3C020021, 0x03E00008)
    theirs = words(0x3C02004A, 0x03E00008)
    result = borrow.validate("sceGsGetGParam", len(ours), ours, published_bytes=theirs)
    assert result["accepted"] is True
    assert result["evidence"]["masked_words"] == 1


def test_validate_checks_only_the_published_window():
    """A corpus from another revision keeps the head of a function and not its body."""
    ours = words(0x27BDFFF0, 0x3C020021, 0x00000021, 0x03E00008)
    theirs = words(0x27BDFFF0, 0x3C02004A, 0x00000023, 0x03E00008)
    assert borrow.validate("sceA", len(ours), ours, published_bytes=theirs,
                           window=8)["accepted"] is True
    assert borrow.validate("sceA", len(ours), ours, published_bytes=theirs,
                           window=12)["accepted"] is False


def test_validate_rejects_a_published_digest_that_does_not_match():
    import hashlib
    blob = words(0x27BDFFF0, 0x03E00008)
    result = borrow.validate("sceGsGetGParam", len(blob), blob,
                             published_digest=hashlib.sha256(b"other").hexdigest())
    assert result["accepted"] is False
    assert "digest" in result["reason"]


def test_validate_rejects_a_name_that_is_not_an_identifier():
    blob = words(0x27BDFFF0)
    result = borrow.validate("$L0", len(blob), blob)
    assert result["accepted"] is False
    assert "identifier" in result["reason"]


def test_validate_rejects_a_size_that_is_not_a_positive_multiple_of_four():
    result = borrow.validate("sceGsGetGParam", 0x6, words(0x27BDFFF0, 0x03E00008)[:6])
    assert result["accepted"] is False
    assert "multiple of four" in result["reason"]


def test_taken_names_ignores_the_names_a_previous_borrow_placed(tmp_path):
    """The borrow step is idempotent: its own ledger must not refuse the names it derived."""
    ledger = tmp_path / "symbol_addrs.txt"
    ledger.write_text(
        "sysInitScf = 0x0021C420; // type:func size:0x30 provenance:dwarf\n"
        "sceGsResetGraph = 0x00100288; // type:func size:0x0 provenance:oni2\n"
        "sceScfGetLanguage = 0x0021BDD0; // type:func size:0x0 provenance:sdk152:libscf.a\n")
    assert borrow.taken_names(ledger) == {"sysInitScf": 0x0021C420}


# ---------------------------------------------------------------------------
# the ledger
# ---------------------------------------------------------------------------


def test_the_ledger_round_trips_through_its_own_parser():
    records = [{"name": "sceGsResetGraph", "address": 0x00100288, "size": 0x190,
                "source": "oni2", "tier": "bytes"},
               {"name": "_sceSDC", "address": 0x00103DD0, "size": 0x10,
                "source": "recvx", "tier": "run"}]
    text = borrow.render_ledger(records)
    assert "sceGsResetGraph = 0x00100288; // type:func size:0x190 provenance:oni2" in text
    parsed = borrow.parse_ledger(text)
    assert [(r["name"], r["address"], r["source"], r["size"]) for r in parsed] == [
        ("sceGsResetGraph", 0x00100288, "oni2", 0x190),
        ("_sceSDC", 0x00103DD0, "recvx", 0x10)]


def test_the_ledger_says_whether_the_whole_body_matched():
    """Both are byte evidence; only one is evidence for the whole function."""
    text = borrow.render_ledger([
        {"name": "sceA", "address": 0x00100288, "size": 0x190, "source": "oni2",
         "tier": "bytes", "evidence": {"whole_function": True}},
        {"name": "sceB", "address": 0x00100300, "size": 0x40, "source": "oni2",
         "tier": "bytes", "evidence": {"whole_function": False}}])
    lines = {l.split(" = ")[0]: l for l in text.splitlines() if " = " in l}
    assert "match:whole" in lines["sceA"]
    assert "match:window" in lines["sceB"]


def test_the_ledger_carries_the_size_the_validation_used():
    """The size check must stay live in the build, not be dropped into a comment."""
    text = borrow.render_ledger([{"name": "sceGsResetGraph", "address": 0x00100288,
                                  "size": 0x190, "source": "oni2", "tier": "bytes",
                                  "evidence": {"whole_function": True}}])
    line = [l for l in text.splitlines() if l.startswith("sceGsResetGraph")][0]
    assert "size:0x190 " in line
    assert "corpus_size:" not in line


def test_a_name_row_renders_the_evidence_and_not_the_raw_record():
    """The `evidence` cell is prose: a row must not leak the proposal's own dict into the table.

    The traceability fix touched this function, and clobbering the rendered cell with
    ``row["evidence"]`` is invisible to every assertion about the *source* cell -- the table would
    still be a table, and a reader would get Python's dict repr in a committed record.
    """
    row = {"name": "sceA", "address": 0x00100288, "size": 0x190, "source": "devkit152",
           "tier": "bytes", "evidence": {
               "source_archives": ["~/sdk/libgraph.a"], "source_members": ["graph023.o"],
               "candidates": 3, "masked_words": 5, "exact": False, "whole_function": True}}
    line = [l for l in borrow.render_markdown([row], [], [], [], []).splitlines()
            if l.startswith("| `0x00100288`")][0]
    cells = [cell.strip() for cell in line.strip("|").split("|")]
    assert cells[4] == "whole body, masked-equal, 5 relocated word(s)"
    assert "source_key" not in line and "{" not in line
    assert cells[2] == "`devkit152` `~/sdk/libgraph.a` `graph023.o`"


def test_a_name_row_names_the_archive_and_member_the_bytes_came_from():
    """The archive's *path* is the provenance, not the member name alone.

    A package can hold several archives of one name (`toolibs242` ships four `libiberty.a` and
    three `libgcc.a`), and a member name recurs across archives, so a row that named only the
    member could not be traced back to the object the bytes were compared with.
    """
    row = {"name": "sceScfGetLanguage", "address": 0x001B34C0, "size": 0x60,
           "source": "sdk152", "tier": "bytes", "evidence": {
               "source_archives": ["~/sdk/lib/libscf.a"], "source_members": ["scf.o"],
               "window": 48, "masked_words": 0, "whole_function": True}}
    text = borrow.render_markdown([row], [], [], [], [])
    assert "`sdk152` `~/sdk/lib/libscf.a` `scf.o`" in text


def test_a_name_row_says_so_when_there_is_no_archive_to_trace_to():
    """The artifact promises traceability: a row that cannot give it must not imply it.

    A corpus that is a linked binary (Oni 2's ELF) or a symbol file has no archive member, and
    the row says that rather than printing a source column that reads like one.
    """
    row = {"name": "sceGsSetDefClear", "address": 0x00100CB8, "size": 0x104,
           "source": "oni2", "tier": "bytes", "evidence": {
               "window": 0x104, "masked_words": 0, "whole_function": True}}
    text = borrow.render_markdown([row], [], [], [], [])
    assert "`oni2` *(no archive member)*" in text


def test_the_ledger_takes_no_evidence_the_markdown_needs():
    """The build artifact is five fields plus the match claim: extra evidence must not leak.

    Where a name's bytes were read is provenance for a reader, not an input to the split -- and a
    field that leaked into `borrowed_symbols.txt` would re-segment the split (a non-zero `size:`,
    a colon in `provenance:`), so the renderer ignores everything it does not name.
    """
    bare = {"name": "sceA", "address": 0x00100288, "size": 0x190, "source": "devkit152",
            "tier": "bytes", "evidence": {"whole_function": True}}
    loaded = dict(bare, evidence={
        "whole_function": True, "source_archives": ["~/sdk/lib/libgraph.a"],
        "source_members": ["graph023.o"], "candidates": 3, "masked_words": 5, "exact": False})
    assert borrow.render_ledger([loaded]) == borrow.render_ledger([bare])


def test_no_corpus_entry_point_breaks_the_markdown_cell():
    """The Sources table wraps ``entry_point`` in a code span: an inner backtick fragments it."""
    for entry in borrow.corpora():
        assert "`" not in entry["entry_point"], entry["key"]


def test_the_ledger_provenance_is_one_boolean_token():
    """``configure.py`` hands the comment to splat as ``provenance=KEY``: no colons."""
    text = borrow.render_ledger([{"name": "sceDmaGetEnv", "address": 0x00101CD8,
                                  "size": 0x40, "source": "sdk152:libdma.a", "tier": "run",
                                  "evidence": {"run": 3}}])
    line = [l for l in text.splitlines() if l.startswith("sceDmaGetEnv")][0]
    assert "provenance:sdk152 " in line
    assert "libdma.a" not in line


def test_the_tool_is_pointed_at_the_registered_target():
    """Every constant this tool works from is the target's, not a memory of another game.

    The descriptor supplies the binary, the config directory and the load geometry; the target's
    own symbol ledger supplies the game/library boundary.  A tool that spelled any of them would
    be the residual coupling the retarget exists to remove -- and a *derived* boundary is the
    difference between borrowing names for this image and for a binary that happens to have been
    in the tree once.
    """
    import sys as _sys
    _sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
    from tests import target_support

    target = target_support.registered()
    geometry = target.geometry_required()
    assert borrow.TARGET is target
    assert borrow.RETAIL == target.elf
    assert borrow.LEDGER == target.borrowed
    assert borrow.SYMBOLS == target.symbols
    assert borrow.MARKDOWN == target.config_dir / "library-names.md"
    assert borrow.SPLIT_ROOT == ROOT / "asm" / "nonmatchings" / geometry.code_segment
    assert borrow.LOAD_VA == geometry.loadable_vram
    assert borrow.LOAD_OFFSET == geometry.loadable_rom
    # The boundary is read out of the target's ledger, and `tools/sdk/revisions.py` records the
    # same measurement independently: two files that disagree would silently move the region.
    lowest = borrow.game_start(target.symbols)
    assert borrow.GAME_START == lowest
    assert all(address >= borrow.GAME_START for address in borrow.taken_names().values())
    from sdk import revisions
    assert revisions.GAME_START == borrow.GAME_START


def test_the_game_boundary_needs_the_targets_own_unity_of_evidence(tmp_path):
    """A ledger with no DWARF record cannot define the library region, and says so."""
    empty = tmp_path / "symbol_addrs.txt"
    empty.write_text("func_00100000 = 0x00100000; // type:func size:0x10 provenance:ghidra\n")
    with pytest.raises(ValueError, match="provenance:dwarf"):
        borrow.game_start(empty)


# ---------------------------------------------------------------------------
# the SDK archives: the whole-body proposer
# ---------------------------------------------------------------------------


def test_archive_proposals_credit_a_whole_body_and_every_member_that_agrees():
    """An archive member is the function's own object, so the case is body against body.

    Two members of one package carrying the identical routine name our function -- the same
    source linked twice -- are one proposal that names *both* archives and both members: a
    member name alone is not traceable (a package can hold several archives of one name), so the
    row has to carry the archive's path.
    """
    body = words(0x27BDFFF0, 0x3C020021, 0x03E00008, 0x27BDFFF0, 0x3C020021, 0x03E00008,
                 0x27BDFFF0, 0x3C020021, 0x03E00008, 0x27BDFFF0, 0x3C020021, 0x03E00008)
    assert len(body) == borrow.MIN_BYTES
    ours = [{"symbol": "func_00100000", "address": 0x100000, "size": len(body)}]
    theirs = [{"name": "sceA", "size": len(body), "member": "a.o", "blob_key": "a",
               "archive": "/sdk/libone.a"},
              {"name": "sceA", "size": len(body), "member": "b.o", "blob_key": "b",
               "archive": "/sdk/libtwo.a"}]
    proposals, refused = borrow.archive_proposals(
        ours, theirs, {0x100000: body}, {"a": body, "b": body}, "devkit152")
    assert refused == []
    assert proposals[0]["name"] == "sceA"
    assert proposals[0]["tier"] == "bytes"
    assert proposals[0]["evidence"]["whole_function"] is True
    assert proposals[0]["evidence"]["candidates"] == 2
    assert proposals[0]["evidence"]["source_archives"] == ["/sdk/libone.a", "/sdk/libtwo.a"]
    assert proposals[0]["evidence"]["source_members"] == ["a.o", "b.o"]


def test_archive_proposals_refuse_a_head_that_matches_and_a_body_that_does_not():
    """Another revision keeps the head of a function and not its body: that names nothing here."""
    ours_words = [0x27BDFFF0, 0x3C020021, 0x03E00008, 0x8FBF0000] * 4
    theirs_words = list(ours_words)
    theirs_words[13] = 0x00000025              # one instruction, past the 48-byte window
    ours, theirs_body = words(*ours_words), words(*theirs_words)
    mine = [{"symbol": "func_00100000", "address": 0x100000, "size": len(ours)}]
    theirs = [{"name": "sceB", "size": len(ours), "member": "b.o", "blob_key": "b"}]
    proposals, refused = borrow.archive_proposals(mine, theirs, {0x100000: ours},
                                                 {"b": theirs_body}, "devkit152")
    assert proposals == []
    assert refused[0]["reason"] == "body differs"
    assert refused[0]["names"] == ["sceB"]


def test_archive_proposals_refuse_two_names_for_one_identical_body():
    """Two aliased members of one package name one body differently: nothing is renamed."""
    body = words(*([0x27BDFFF0, 0x3C020021, 0x03E00008] * 4))
    mine = [{"symbol": "func_00100000", "address": 0x100000, "size": len(body)}]
    theirs = [{"name": "sceOne", "size": len(body), "member": "a.o", "blob_key": "a"},
              {"name": "sceTwo", "size": len(body), "member": "b.o", "blob_key": "b"}]
    proposals, refused = borrow.archive_proposals(mine, theirs, {0x100000: body},
                                                 {"a": body, "b": body}, "devkit152")
    assert proposals == []
    assert refused[0]["reason"] == "names disagree"
    assert refused[0]["names"] == ["sceOne", "sceTwo"]


def test_archive_proposals_ignore_a_body_below_the_floor():
    """A 16-byte stub is not evidence, however identical: the kernel's stubs recur."""
    body = words(0x03E00008, 0x00000000, 0x03E00008, 0x00000000)
    mine = [{"symbol": "func_00100000", "address": 0x100000, "size": len(body)}]
    theirs = [{"name": "Copy", "size": len(body), "member": "k.o", "blob_key": "k"}]
    proposals, refused = borrow.archive_proposals(mine, theirs, {0x100000: body},
                                                 {"k": body}, "devkit152")
    assert proposals == [] and refused == []


def test_archive_records_keep_every_member_apart():
    """A relocatable member restarts at address 0: the blob key is what keeps two apart."""
    records, blobs = borrow.archive_records([
        {"set": "devkit152", "path": "/x/libkernl.a",
         "functions": [{"name": "kCopy", "size": 8, "member": "a.o", "bytes": b"\x01" * 8},
                       {"name": "kCopy", "size": 8, "member": "b.o", "bytes": b"\x02" * 8}]}])
    keys = [borrow.corpus_key(record) for record in records]
    assert len(set(keys)) == 2
    assert blobs[keys[0]] != blobs[keys[1]]
    assert {record["source"] for record in records} == {"devkit152:libkernl.a"}


def test_the_archive_corpus_is_the_one_the_revision_record_verdicts_against():
    """One scan, two questions: the ledger and library-revisions.json share the corpus.

    Re-discovering the archives here would let the two records drift apart -- a name borrowed
    from an archive the revision record never saw is exactly the kind of provenance nobody
    could check.
    """
    from sdk import revisions

    entries = borrow.archive_corpus()
    if not entries:
        pytest.skip("no SDK archive on this machine")
    assert ([entry["path"] for entry in entries]
            == [entry["path"] for entry in revisions.corpus()])


def test_the_committed_ledger_is_what_the_tool_derives(tmp_path):
    """The ledger a target's config carries is this tool's own output.

    Skipped when a corpus is not on this machine (or when the SDK archives are not, which is the
    evidence the ledger mostly rests on), when the target has no ledger yet, or when the split
    has not been built here -- it is a build artifact, and the tool measures our functions
    through it.  The committed artifact is evidence about the corpora, so it can only be
    re-derived where the evidence is; the same rule as `tests/sdk/test_revisions.py`.
    """
    import sys as _sys
    _sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
    from tests import target_support

    target = target_support.registered()
    if not target.borrowed.is_file():
        pytest.skip(f"{target.name}: no borrowed_symbols.txt yet (the library pass)")
    if not borrow.archive_corpus():
        pytest.skip("no SDK archive on this machine")
    if not borrow.SPLIT_ROOT.is_dir():
        pytest.skip(f"{borrow.SPLIT_ROOT} is a build artifact and has not been built here")
    for key in ("oni2", "sdk152", "recvx"):
        if not borrow.corpus_records(key, borrow.CACHE)[0]:
            pytest.skip(f"{key} is unreachable on this machine")
    for key in ("godhand", "sly1"):
        if borrow.corpus_text(key, borrow.CACHE) is None:
            pytest.skip(f"{key} is unreachable on this machine")
    ledger, markdown = tmp_path / "borrowed_symbols.txt", tmp_path / "library-names.md"
    assert borrow.main(["--ledger", str(ledger), "--markdown", str(markdown)]) == 0
    assert ledger.read_bytes() == target.borrowed.read_bytes()
    # The ledger is the artifact; the markdown is the same run's provenance, and it is what a
    # reader checks a name's archive member and licence against.
    assert markdown.read_bytes() == (target.config_dir / "library-names.md").read_bytes()
