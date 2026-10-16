"""The oracle's CU map, from the target's own ELF -- and the committed map, reproduced.

Re-pointed at the registered target (retarget plan Task 4 places its binary and generates its
config): the assertions are *properties* of a DWARF 1 compile-unit map -- records tiling `.debug`,
one translation-unit record per contiguous run of a `file`, every function CU carrying its
statement list -- plus the determinism property the suites exist for: a fresh walk of the binary
renders the committed `cus.json` byte for byte.  Nothing here writes to the tree.
"""

import json
import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
sys.path.insert(0, str(ROOT))

import emit_cus  # noqa: E402
from tests import target_support  # noqa: E402

TARGET = target_support.registered()
pytestmark = pytest.mark.skipif(
    not TARGET.elf.is_file(), reason=f"{TARGET.name}: orig/{TARGET.elf.name} is not placed")


@pytest.fixture(scope="module")
def cus():
    return emit_cus.build(TARGET.elf)


def test_the_cu_map_tiles_the_debug_section(cus):
    geometry = TARGET.geometry_required()
    assert cus[0]["offset"] == 0
    for previous, following in zip(cus, cus[1:]):
        assert previous["offset"] + previous["size"] == following["offset"]
    assert cus[-1]["offset"] + cus[-1]["size"] == geometry.debug_size
    assert json.loads(TARGET.cus.read_text()) != []          # the committed map is not empty


def test_every_record_identifies_a_translation_unit(cus):
    runs = []
    for record in cus:
        assert record["file"], record
        if not runs or runs[-1]["file"] != record["file"]:
            runs.append(record)
    assert len(runs) == len({record["file"] for record in cus})
    assert all(run["kind"] == "tu" for run in runs)
    assert all(record["stmt_list"] is not None for record in cus
               if record["kind"] == "function")


def test_the_walk_reproduces_the_committed_map(cus):
    """Determinism: the committed `cus.json` is this walk's own output."""
    assert emit_cus.render(cus) == TARGET.cus.read_text()


def test_owner_of_covers_the_section_and_refuses_what_is_outside_it(cus):
    geometry = TARGET.geometry_required()
    for offset in (0, 1, cus[1]["offset"], geometry.debug_size - 1):
        owner = emit_cus.owner_of(cus, offset)
        assert owner["offset"] <= offset < owner["offset"] + owner["size"]
    with pytest.raises(emit_cus.NoCompileUnit):
        emit_cus.owner_of(cus, geometry.debug_size + 5)


def test_a_source_path_is_made_tree_relative():
    """The recorded path is the retail build host's; the tree spelling is what identifies a unit."""
    assert emit_cus.relpath("C:\\work\\<anywhere>\\src\\sys\\sys_scf.c") == \
        "src/sys/sys_scf.c"
    assert emit_cus.relpath("src/mov/foo.c") == "src/mov/foo.c"
    assert emit_cus.relpath("") == ""
