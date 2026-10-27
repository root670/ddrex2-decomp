"""Twin grouping: identical split words, the promoted-twin hint, and a deterministic report.

Every test here builds its own split files under ``tmp_path`` and calls the pure functions,
so nothing reads the retail ELF, a compiler, the build graph or the network.  The one
measured test reads the generated split tree, which is what the tool reports on, and skips
when ``./ddr build`` has not produced it.
"""

import pathlib
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))

from units import twins  # noqa: E402

SPLITS = ROOT / "asm" / "nonmatchings" / "main"


def split_text(*words: str) -> str:
    """One split file whose comment word column carries ``words``, spelled the way splat does."""
    lines = [".include \"macro.inc\"", "nonmatching Body, 0x%X" % (4 * len(words)), "glabel Body"]
    for index, word in enumerate(words):
        lines.append(f"    /* B{index:04X} 00{index:06X} {word} */  nop")
    return "\n".join(lines) + "\n"


def write_split(directory: pathlib.Path, name: str, *words: str) -> pathlib.Path:
    path = directory / f"{name}.s"
    path.write_text(split_text(*words))
    return path


A = ("27BDFFD0", "FFBF0010", "27BDFFE0", "03E00008")
B = ("27BDFFD0", "FFBF0010", "27BDFFE0", "03E00008")
C = ("27BDFFD0", "FFBF0010", "27BDFFE0", "00000000")


def test_identical_words_group_and_singletons_do_not(tmp_path):
    write_split(tmp_path, "Alpha", *A)
    write_split(tmp_path, "Beta", *B)
    write_split(tmp_path, "Gamma", *C)

    signatures = twins.read_splits(tmp_path)
    index = twins.groups(signatures)

    assert signatures["Alpha"] == A
    assert index == {A: ("Alpha", "Beta")}


def test_a_split_that_prints_no_words_is_not_a_body(tmp_path):
    write_split(tmp_path, "Empty")
    write_split(tmp_path, "AlsoEmpty")

    signatures = twins.read_splits(tmp_path)

    assert twins.groups(signatures) == {}


def test_a_missing_split_tree_names_the_command_that_makes_it(tmp_path):
    with pytest.raises(twins.Missing) as caught:
        twins.read_splits(tmp_path / "absent")

    assert "./ddr build" in str(caught.value)


def test_a_body_with_no_twin_says_so(tmp_path):
    write_split(tmp_path, "Alpha", *A)
    write_split(tmp_path, "Gamma", *C)

    signatures = twins.read_splits(tmp_path)
    found = twins.bodies(["Gamma"], signatures, twins.groups(signatures))

    assert found[0].twins == ()
    assert found[0].words == len(C)
    assert twins.note(found[0], {}, frozenset()) == "no twin"


def test_a_twin_in_a_promoted_unit_names_its_source_and_the_split_to_copy(tmp_path):
    source = tmp_path / "src" / "CS" / "twin.c"
    source.parent.mkdir(parents=True)
    source.write_text("void Twin(void) {}\n")
    rows = (("src/CS/twin.c", "3.0b38-030307", "-c -lang c -O3 -opt full -g"),)

    promoted = twins.promoted_units(rows, tmp_path)
    body = twins.Body("Body", len(A), ("Twin", "Other"))

    assert promoted == frozenset({"src/CS/twin.c"})
    assert twins.note(body, {"Twin": "src/CS/twin.c", "Other": "src/CS/other.c"},
                      promoted) == (f"2 twins, 1 promoted: Twin (src/CS/twin.c) — "
                                    f"copy {twins.split_path('Twin')}")


def test_a_source_without_a_tu_builds_row_is_not_promoted(tmp_path):
    source = tmp_path / "src" / "CS" / "half.c"
    source.parent.mkdir(parents=True)
    source.write_text("void Half(void) {}\n")

    assert twins.promoted_units((), tmp_path) == frozenset()


def test_twins_none_promoted_say_one_shape_serves_all(tmp_path):
    write_split(tmp_path, "Alpha", *A)
    write_split(tmp_path, "Beta", *B)

    signatures = twins.read_splits(tmp_path)
    body = twins.bodies(["Alpha"], signatures, twins.groups(signatures))[0]

    assert twins.note(body, {"Beta": "src/CS/beta.c"}, frozenset()) == (
        "1 twin candidate, none promoted - one source shape serves all — "
        f"copy {twins.split_path('Beta')}")


def test_an_absent_split_says_run_the_build():
    body = twins.Body("Gone", None, ())

    assert twins.note(body, {}, frozenset()) == "split absent — run ./ddr build"


def test_render_unit_is_one_line_per_body_and_says_how_many_it_hid():
    found = [twins.Body(f"Body{index}", 4, ()) for index in range(5)]

    text = twins.render_unit("src/CS/x.c", found, {}, frozenset(), limit=2)

    assert text.count("no twin") == 2
    assert "… 3 more bodies (--limit 0 prints all)" in text
    assert len(text.splitlines()) < 12


def test_the_report_is_deterministic_whatever_order_the_splits_arrive_in(tmp_path):
    write_split(tmp_path, "Beta", *B)
    write_split(tmp_path, "Alpha", *A)
    write_split(tmp_path, "Gamma", *C)

    signatures = twins.read_splits(tmp_path)
    shuffled = dict(reversed(list(signatures.items())))

    assert twins.read_splits(tmp_path) == signatures
    assert twins.groups(shuffled) == twins.groups(signatures)
    assert twins.render_all(twins.groups(shuffled), {}, frozenset(), limit=0) == \
        twins.render_all(twins.groups(signatures), {}, frozenset(), limit=0)

    first = twins.bodies(["Gamma", "Alpha"], signatures, twins.groups(signatures))
    second = twins.bodies(["Gamma", "Alpha"], shuffled, twins.groups(shuffled))
    assert first == second
    assert twins.render_unit("u", first, {}, frozenset(), limit=0) == \
        twins.render_unit("u", second, {}, frozenset(), limit=0)


def test_main_reports_an_absent_split_tree_and_does_not_crash(monkeypatch, capsys):
    monkeypatch.setattr(twins, "resolve_target",
                        lambda name=None: types.SimpleNamespace(name="t", tu_builds=()))
    monkeypatch.setattr(twins, "read_splits",
                        lambda directory=None: (_ for _ in ()).throw(
                            twins.Missing("asm/nonmatchings/main is absent; run ./ddr build")))

    assert twins.main(["--all"]) == 2
    assert "twins: asm/nonmatchings/main is absent; run ./ddr build" in capsys.readouterr().err


@pytest.mark.skipif(not SPLITS.is_dir(), reason="the split tree is generated by ./ddr build")
def test_the_generated_tree_groups_the_twin_rule_18_names():
    signatures = twins.read_splits(SPLITS)
    index = twins.groups(signatures)

    assert "NetWin_DHeadEnd" in index[signatures["NetWin_VSWinEnd"]]
    assert all(members == tuple(sorted(members)) for members in index.values())


# ---------------------------------------------------------------------------
# overlay units: their names and their splits come from their own module
# ---------------------------------------------------------------------------


def overlay_manifests(overlay="probe_rel4cd", low_pc=0x00200080):
    """The two lookups `unit_functions` makes, in the shape `compile.Manifests` gives them."""
    return types.SimpleNamespace(
        chunks=[dict(section=".debug", offset=0, size=0x40, tunits=[0, 1])],
        cus=[dict(index=0, kind="tu", file="src/probe/ov.c", overlay=overlay),
             dict(index=1, kind="function", file="src/probe/ov.c", low_pc=low_pc)],
        by_address={},
        overlay_symbols={(overlay, low_pc): "nrmesGetNo"})


def test_an_overlay_function_is_named_from_its_modules_records():
    """`by_address` holds no overlay record -- seven modules share one base -- so the name
    comes from the withheld ledger's `(module, address)` key, which is the build's rule."""
    _, by_unit, declared = twins.unit_functions(overlay_manifests())

    assert by_unit == {"src/probe/ov.c": ("nrmesGetNo",)}
    assert declared == {"src/probe/ov.c": 1}


def test_a_main_unit_never_reads_an_overlay_record():
    manifests = overlay_manifests(overlay="main")

    _, by_unit, declared = twins.unit_functions(manifests)

    assert by_unit == {} and declared == {"src/probe/ov.c": 1}


def test_a_units_split_tree_is_its_own_modules(tmp_path):
    manifests = overlay_manifests()

    assert twins.split_directory(manifests, "src/probe/ov.c") == \
        pathlib.PurePosixPath("asm/nonmatchings/probe_rel4cd")
    assert twins.split_directory(overlay_manifests(overlay="main"), "src/probe/ov.c") == \
        twins.SPLITS
    # A unit nothing names is still reported against the main tree, not against nothing.
    assert twins.split_directory(manifests, "src/unknown.c") == twins.SPLITS


def test_the_copy_hint_points_into_the_units_own_tree(tmp_path):
    write_split(tmp_path, "Alpha", *A)
    write_split(tmp_path, "Beta", *B)
    signatures = twins.read_splits(tmp_path)
    body = twins.bodies(["Alpha"], signatures, twins.groups(signatures))[0]

    hinted = twins.note(body, {"Beta": "src/probe/ov.c"}, frozenset(),
                        pathlib.PurePosixPath("asm/nonmatchings/probe_rel4cd"))

    assert "copy asm/nonmatchings/probe_rel4cd/Beta.s" in hinted
