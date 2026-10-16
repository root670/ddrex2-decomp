"""The generated headers are C, and every named type is defined exactly once.

The contract this file guards (plan Task 1): a use is `struct <tag> *`, never a bare tag
(CodeWarrior labels every compile unit `LANG_CPLUSPLUS` even for a `.c` file, and DWARF 1
resolves typedefs away, so `struct <tag>` is the only spelling the evidence offers); every
generated header compiles under the *original* compiler; a named type is defined once,
under `include/types/`; and an anonymous type -- `@anon0..24`, which is per-unit numbering,
so the same name means different types in different units -- stays in the unit that
declares it, under a tag that says which unit that is.
"""
import collections, pathlib, re, subprocess, sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
import emit_headers  # noqa: E402
import dwarf1  # noqa: E402  the vendored reader, for the disagreement fixture

RETAIL = ROOT / "orig/SLUS_207.11"
INCLUDE = ROOT / "include"
COMPILE = ROOT / "tools/toolchain/compile.py"

#: A definition, as the emitters spell it: the keyword and the tag, then the body.
DEFINITION = re.compile(r"^(?:struct|union|enum)\s+(\w+)\s*\{", re.M)


def code(text):
    """`text` with comments and preprocessor lines removed.

    The two are where a header may name something it cannot spell -- a provenance
    comment quoting `@anon7`, an `#include` line naming a file -- so a spelling rule is
    checked against the code, not against the whole file.
    """
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", " ", text)
    return "\n".join(line for line in text.splitlines() if not line.lstrip().startswith("#"))


def definitions():
    """`{tag: {header, ...}}` -- every aggregate definition in the generated tree."""
    out = collections.defaultdict(set)
    for path in sorted(INCLUDE.rglob("*.h")):
        for match in DEFINITION.finditer(code(path.read_text())):
            out[match.group(1)].add(path.relative_to(INCLUDE))
    return out


def named_types():
    return emit_headers.render_types(emit_headers.dwarf(RETAIL))


# ---------------------------------------------------------------------------
# C spelling
# ---------------------------------------------------------------------------


def test_the_sys_scf_header_is_c_mode():
    text = emit_headers.render(RETAIL, "sys_scf.c")
    assert '#include "types/_tag_SYS_SCF_WORK.h"' in text         # includes, not defines
    assert "struct _tag_SYS_SCF_WORK *pscf;" in text            # the C spelling
    assert "void sysInitScf(struct _tag_SYS_SCF_WORK *p);" in text
    assert re.search(r"^_tag_SYS_SCF_WORK \*pscf;", text, re.M) is None
    assert "0x0021C410-0x0021C41C" in text                     # retail line range kept


def test_a_named_type_header_carries_its_layout_and_provenance():
    text = named_types()["_tag_SYS_SCF_WORK"]
    assert "struct _tag_SYS_SCF_WORK {   // size 0x8" in text
    assert "/* 0x000 */ int date_notation;" in text
    assert "/* 0x004 */ int language;" in text
    assert "DIE 0x" in text and "sys_scf.c" in text            # where the evidence is
    assert "layout" in text                                    # the layout signature


def test_a_per_tu_header_defines_no_named_type():
    """It includes the canonical ones; only its own anonymous types are defined here."""
    for tu in ("sys_scf.c", "dcamera.c"):
        text = emit_headers.render(RETAIL, tu)
        tags = DEFINITION.findall(code(text))
        assert all(tag.startswith("anon_") for tag in tags), (tu, tags)


def test_no_declaration_starts_with_a_bare_tag():
    """`_tag_X *p;` is C++: a use has to say which kind of aggregate it means."""
    tags = set(named_types())
    for path in sorted(INCLUDE.rglob("*.h")):
        for line in code(path.read_text()).splitlines():
            first = line.split()[:1]
            if first:
                assert first[0] not in tags, f"{path}: {line!r}"


def test_no_generated_code_names_an_at_sign():
    """`@` is not a legal C identifier: `@anonN` survives in provenance comments only."""
    for path in sorted(INCLUDE.rglob("*.h")):
        assert "@" not in code(path.read_text()), path


def test_every_generated_header_compiles_as_c(tmp_path):
    """The gate is the original compiler, not a host `cc` (plan Task 1 Step 3).

    Each header is included on its own by a probe translation unit, so a header that
    needs a neighbour has to say so itself; ~157 mwcc runs is what that costs.
    """
    headers = sorted(INCLUDE.rglob("*.h"))
    assert len(headers) > 100
    probe = tmp_path / "probe.c"
    for header in headers:
        probe.write_text(f'#include "{header.relative_to(INCLUDE)}"\n'
                         "int main(void) { return 0; }\n")
        run = subprocess.run([sys.executable, str(COMPILE), "--syntax-only",
                              "--include", str(INCLUDE), str(probe)],
                             capture_output=True, text=True)
        assert run.returncode == 0, \
            f"{header}: exit {run.returncode}\n{run.stdout[-2000:]}{run.stderr[-2000:]}"


# ---------------------------------------------------------------------------
# one definition per named type; anonymous types stay per unit
# ---------------------------------------------------------------------------


def test_no_aggregate_is_defined_twice():
    """Named or anonymous: a tag in two headers is a layout waiting to be picked wrongly."""
    twice = {tag: paths for tag, paths in definitions().items() if len(paths) > 1}
    assert twice == {}


def test_every_named_type_is_defined_once_under_types():
    found = definitions()
    named = {tag: paths for tag, paths in found.items() if not tag.startswith("anon_")}
    assert len(named) == 98 and len(named) == len(named_types())
    for tag, paths in named.items():
        path, = paths
        assert path == pathlib.Path("types") / f"{tag}.h", tag


def test_types_h_aggregates_every_named_type():
    types = named_types()
    index = (INCLUDE / "types.h").read_text()
    assert len(types) == 98
    for tag in types:
        assert f'#include "types/{tag}.h"' in index


def test_anonymous_types_stay_per_tu():
    """`@anonN` is one unit's numbering, so the tag it becomes names that unit."""
    text = emit_headers.render(RETAIL, "dcamera.c")
    tags = set(re.findall(r"\banon_\d+_\d+\b", code(text)))
    assert tags, "dcamera.c's `struct @anon1 camera_w` needs a tag"
    assert re.search(r"^struct anon_\d+_\d+ \{", code(text), re.M), text[:400]
    for tag in sorted(tags):                                    # provenance, per definition
        assert re.search(rf"^/\* {tag} -- @anon\d+, 0x[0-9a-fA-F]+ bytes, "
                         rf"\w+\.c \(DIE 0x[0-9a-fA-F]+\) \*/$", text, re.M), tag

    other = emit_headers.render(RETAIL, "sys_scf.c")
    for tag in tags:
        assert tag not in other                     # another unit's numbering, another type
    shared = [p for p in (INCLUDE / "types").rglob("*.h")] + [INCLUDE / "types.h"]
    for path in shared:
        assert "anon_" not in code(path.read_text()), path


def _die(off, tag, attrs, children=()):
    d = dwarf1.Die(off, tag, dict(attrs))
    d.cu = None
    for child in children:
        child.parent = d
    d.children = list(children)
    return d


def _member(off, name, ty=0x0007):
    """A member DIE: `AT_location` is the offset, as `member_offset` reads it."""
    return _die(off, dwarf1.TAG_member,
                {dwarf1.AT_name: name,
                 dwarf1.AT_location: b"\x04" + off.to_bytes(4, "little") + b"\x07",
                 dwarf1.AT_fund_type: ty})


def _disagreeing_dwarf():
    """Two copies of `_tag_W`, same size, whose `c` member sits at a different offset."""
    class Two(dwarf1.Dwarf):
        def __init__(self, dies):
            self.dies = {d.off: d for d in dies}
            self.tus = []

    attrs = {dwarf1.AT_name: "_tag_W", dwarf1.AT_byte_size: 0x10}
    first = _die(0x1000, dwarf1.TAG_structure_type, attrs,
                 [_member(0, "a"), _member(4, "b"), _member(8, "c")])
    second = _die(0x2000, dwarf1.TAG_structure_type, attrs,
                  [_member(0, "a"), _member(4, "b"), _member(0xC, "c")])
    return Two([first, second])


def test_a_named_layout_disagreement_fails_loudly():
    """Two units spelling one named type differently is news, not a coin toss."""
    with pytest.raises(emit_headers.LayoutDisagreement) as excinfo:
        emit_headers.render_types(_disagreeing_dwarf())
    message = str(excinfo.value)
    assert "_tag_W" in message
    assert "'c'" in message and "0x008" in message and "0x00c" in message


# ---------------------------------------------------------------------------
# the written tree
# ---------------------------------------------------------------------------


def generated(root):
    """Every file the emitter owns below `root`: its headers, and its README."""
    return {path.relative_to(root) for path in root.rglob("*")
            if path.is_file() and (path.suffix == ".h" or path.name == "README.md")}


def test_write_all_writes_the_whole_generated_tree(tmp_path):
    """Nothing extra, nothing missing: the committed tree is exactly what a run writes.

    `write_all` returns the translation-unit headers (what `./ddr oracle` counts); the
    shared tree is checked on disk, which is also what makes a stray file fail here.  The
    emitter never deletes, so a target switch that leaves another target's headers behind is
    *expected* to fail this test until they are removed — that is the check, not noise.
    """
    units = emit_headers.write_all(RETAIL, tmp_path)
    assert len(units) == 57
    assert all(str(path.relative_to(tmp_path)).startswith("src/") for path in units)
    fresh = {path.relative_to(tmp_path) for path in tmp_path.rglob("*") if path.is_file()}
    assert fresh == generated(INCLUDE)
    assert sum(1 for rel in fresh if str(rel).startswith("types/")) == 98
    assert {pathlib.Path("types.h"), pathlib.Path("README.md")} <= fresh


def test_every_header_spells_hex_the_same_way():
    """Upper-case offsets, as every header under `include/` has spelled them.

    The two families are written by two calls (`write_all` writes the unit headers from
    `_unit_header`, the shared tree from `render_types`), and a run that upper-cased one and
    not the other would be a tree that reads two ways.  Every offset here is a comment, so
    this is the only thing that makes the convention real.
    """
    lower = re.compile(r"0x[0-9a-f]*[a-f][0-9a-f]*")
    for path in sorted(INCLUDE.rglob("*.h")):
        text = path.read_text()
        assert not lower.search(text), f"{path}: {lower.search(text).group(0)}"


def test_committed_headers_match_a_fresh_run(tmp_path):
    emit_headers.write_all(RETAIL, tmp_path)
    fresh = sorted(path for path in tmp_path.rglob("*") if path.is_file())
    for path in fresh:
        assert path.read_bytes() == (INCLUDE / path.relative_to(tmp_path)).read_bytes(), path


def test_render_refuses_a_name_that_matches_nothing():
    with pytest.raises(emit_headers.NoSuchUnit):
        emit_headers.render(RETAIL, "no_such_unit.c")
