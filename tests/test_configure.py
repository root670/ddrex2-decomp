"""`configure.py` must split the retail ELF and emit the ninja graph the build drives.

These tests run the real toolchain: :file:`configure.py` shells out to splat and rewrites
:file:`config/usam2/splat.yaml` plus the generated symbol/undefined files from the
manifests, so a geometry or manifest mistake surfaces here rather than in the link.
"""

import json
import os
import pathlib
import re
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))  # `config.targets`, the descriptor this tool reads

from config import targets  # noqa: E402

CONFIGURE = [sys.executable, "configure.py", "--target", "usam2"]


def test_splat_splits_every_symbol():
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    splits = list((ROOT / "asm").rglob("*.s"))
    assert len(splits) >= 3161
    assert (ROOT / "build.ninja").exists()


def test_debug_chunks_are_carried_as_data():
    yaml = (ROOT / "config/usam2/splat.yaml").read_text()
    assert "databin" in yaml and ".debug" in yaml and ".line" in yaml


def test_config_without_cus_json_fails_loudly(tmp_path):
    p = subprocess.run(CONFIGURE + ["--cus", str(tmp_path / "missing.json")],
                       cwd=ROOT, capture_output=True, text=True)
    assert p.returncode != 0 and "cus.json" in p.stderr


def test_config_without_debug_chunks_fails_loudly(tmp_path):
    p = subprocess.run(CONFIGURE + ["--chunks", str(tmp_path / "gone.json")],
                       cwd=ROOT, capture_output=True, text=True)
    assert p.returncode != 0 and "debug_chunks.json" in p.stderr


def test_a_bad_chunk_manifest_is_never_repaired(tmp_path):
    """The Task 4 guard: chunks must be one per TU and start at one, or configure stops.

    A chunk grouper that keys off the file name merges two adjacent same-named TUs
    silently, so the manifest is checked against ``cus.json`` before anything is written.
    """
    cus = json.loads((ROOT / "config/usam2/cus.json").read_text())
    chunks = json.loads((ROOT / "config/usam2/debug_chunks.json").read_text())
    tus = [i for i, record in enumerate(cus) if record["kind"] == "tu"]
    debug = [c for c in chunks if c["section"] == ".debug"]
    assert [c["tunits"][0] for c in debug] == tus     # well-formed before we break it
    chunks[1]["tunits"] = chunks[1]["tunits"][1:]     # no longer starts at its TU
    broken = tmp_path / "debug_chunks.json"
    broken.write_text(json.dumps(chunks))

    yaml = (ROOT / "config/usam2/splat.yaml").read_text()
    p = subprocess.run(CONFIGURE + ["--chunks", str(broken)],
                       cwd=ROOT, capture_output=True, text=True)
    assert p.returncode != 0
    assert "chunk" in p.stderr and "tu" in p.stderr
    assert (ROOT / "config/usam2/splat.yaml").read_text() == yaml


def test_one_split_reassembles_to_the_retail_bytes(tmp_path):
    """R21, measured rather than assumed: the split of ``func_00102CB8`` is assembled
    with the very flags the ninja ``as`` rule uses and compared with the retail file.

    The function is the interesting one: it moves register 8 between a GPR and the VU,
    and register 8 is the one the o32 ABI spells ``$t0`` while ``-mabi=eabi`` renumbers
    ``$t0`` to register 12 -- which is why the config asks splat for numeric register
    names.  Every byte up to the size the split declares must match; gas pads the tail
    of ``.text`` out to its 16-byte section alignment, so only that prefix is compared.
    """
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    split = ROOT / "asm/nonmatchings/main/func_00102CB8.s"
    assert split.is_file()
    subprocess.run(["ninja", "build/asm/nonmatchings/main/func_00102CB8.s.o"],
                   cwd=ROOT, check=True)
    text = split.read_text()
    va = int(re.search(r"/\*\s*[0-9A-F]+\s+([0-9A-F]{8})", text).group(1), 16)
    size = int(re.search(r"nonmatching \S+, 0x([0-9A-Fa-f]+)", text).group(1), 16)
    binary = tmp_path / "func_00102CB8.bin"
    subprocess.run(["mips-linux-gnu-objcopy", "-O", "binary", "--only-section=.text",
                    "build/asm/nonmatchings/main/func_00102CB8.s.o", str(binary)],
                   cwd=ROOT, check=True)
    got = binary.read_bytes()[:size]
    rom = va - 0x00100000 + 0x80
    retail = (ROOT / "orig/SLUS_207.11").read_bytes()[rom:rom + size]
    assert got == retail, f"assembled {got.hex()} != retail {retail.hex()}"


COMMENT = re.compile(r"/\*\s*([0-9A-F]+)\s+([0-9A-F]{8})\s+([0-9A-F]{8})\s*\*/")


def split_span(text):
    """(virtual address, byte length) of the retail bytes a split declares.

    The extent runs from the first instruction comment to the end of the last one; every
    byte in between is emitted explicitly by the split, padding included.
    """
    comments = COMMENT.findall(text)
    assert comments, "split carries no instruction comments"
    start = int(comments[0][1], 16)
    return start, int(comments[-1][1], 16) + 4 - start


def object_text_size(path):
    """Size of an object's .text, read out of its section header table."""
    import struct
    data = path.read_bytes()
    shoff, shentsize, shnum, shstrndx = (
        struct.unpack_from("<I", data, 0x20)[0],
        struct.unpack_from("<H", data, 0x2E)[0],
        struct.unpack_from("<H", data, 0x30)[0],
        struct.unpack_from("<H", data, 0x32)[0])
    sections = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize)
                for i in range(shnum)]
    names = data[sections[shstrndx][4]:sections[shstrndx][4] + sections[shstrndx][5]]
    for section in sections:
        end = names.index(b"\0", section[0])
        if names[section[0]:end] == b".text":
            return section[5]
    return 0


def test_a_split_assembles_to_exactly_the_bytes_it_declares(tmp_path):
    """The `.align` landmine, measured: splat emits alignment that is only true in
    absolute VA terms, so in an object that starts at the function's own address it would
    add four zero bytes on top of a split whose padding is already explicit.

    Functions whose VA is 4 mod 8 are exactly where that shows, so one of those is
    assembled next to the R21 function and a few neighbours.
    """
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    splits = sorted((ROOT / "asm/nonmatchings/main").glob("*.s"))
    odd = [s for s in splits if split_span(s.read_text())[0] % 8 == 4]
    assert odd, "the manifest no longer exercises the 4 mod 8 case"
    sample = sorted({odd[0].name, odd[-1].name, "func_00102CB8.s", "sysInitScf.s"})
    targets = [f"build/asm/nonmatchings/main/{name}.o" for name in sample]
    subprocess.run(["ninja", *targets], cwd=ROOT, check=True)
    for name, target in zip(sample, targets):
        _, span = split_span((ROOT / "asm/nonmatchings/main" / name).read_text())
        size = object_text_size(ROOT / target)
        assert size == span, f"{name}: object .text {size:#x} != declared {span:#x}"


def test_the_splits_are_a_byte_exact_partition_of_the_loadable_region():
    """1,713,792 bytes of loadable image = the sum of every assembled split's .text."""
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    subprocess.run(["ninja", "objects"], cwd=ROOT, check=True)
    objects = sorted((ROOT / "build/asm/nonmatchings").rglob("*.s.o"))
    total = 0
    for obj in objects:
        total += object_text_size(obj)
    assert total == 0x1A2680, f"assembled {total} bytes, region is {0x1A2680}"


def test_the_alignment_the_manifest_needs_is_what_the_config_asks_for(tmp_path):
    """Derived, not hardcoded: the splits and the chunk manifest decide the alignment.

    Functions sit at VAs that are 4 mod 8, so forcing 8-byte input alignment would move
    them; databins have byte lengths, so any forcing at all pads them apart and moves
    `.debug_000` / `.line_000` off 0x1A2740 / 0x2430E0.  Only "force nothing" satisfies
    both, so the generated yaml must say `subalign: 1`.
    """
    import yaml
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    splits = sorted((ROOT / "asm/nonmatchings/main").glob("*.s"))
    starts = [split_span(s.read_text())[0] for s in splits]
    assert all(va % 4 == 0 for va in starts), "a function is not even 4-aligned"
    assert any(va % 8 == 4 for va in starts), "no function needs 4-but-not-8 alignment"
    yaml_text = (ROOT / "config/usam2/splat.yaml").read_text()
    segments = yaml.safe_load(yaml_text)["segments"][1]["subsegments"]
    offsets = [s[0] for s in segments if isinstance(s, list)]
    sizes = [b - a for a, b in zip(offsets, offsets[1:])]
    assert any(size % 4 for size in sizes), "no databin has a byte length any more"
    assert "  subalign: 1\n" in yaml_text, "subalign must not force input alignment"


def test_include_asm_expands_to_a_split_that_exists():
    """Finding 3: splat passes the folder *with* its path, so the macro must not add one.

    Every call splat generated for the loadable region is expanded with `inline_asm.h`'s
    rule and the resulting `.include` path must exist.
    """
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    generated = (ROOT / "build/src/main.c").read_text()
    header = (ROOT / "inline_asm.h").read_text()
    assert '".include \\"" folder "/" #name ".s\\"\\n"' in header
    calls = re.findall(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\)', generated)
    assert len(calls) >= 3161, f"only {len(calls)} INCLUDE_ASM calls were generated"
    missing = [f"{folder}/{name}.s" for folder, name in calls
               if not (ROOT / f"{folder}/{name}.s").is_file()]
    assert not missing, f"{len(missing)} INCLUDE_ASM targets do not exist: {missing[:3]}"


SHA = "a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc"
ELF_SIZE = 0x265854
LOADABLE_END = 0x1A2700


def test_the_pinned_link_reproduces_the_retail_file():
    """M1's gate as a test: bare `ninja` must produce the retail image byte for byte."""
    import hashlib
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    subprocess.run(["ninja"], cwd=ROOT, check=True)
    built = ROOT / "out/SLUS_207.11"
    assert built.stat().st_size == ELF_SIZE, f"{built} is {built.stat().st_size} bytes"
    digest = hashlib.sha256(built.read_bytes()).hexdigest()
    assert digest == SHA, f"built {digest}"
    assert SHA in (ROOT / "config/usam2/checksums.txt").read_text()


def test_the_file_assembly_covers_every_byte_the_elf_does_not_load():
    """The loadable image comes from ld + objcopy; the file's tail is databin content.

    The tail edge's inputs must be the databin assets *in manifest order* -- a glob
    would sort `.debug_000` after `shstrtab` and produce a plausible wrong image -- with a
    promoted unit's own `.debug`/`.line` payload in place of the databins of the chunks it
    owns (M2).  Together with the loadable image they must tile the file exactly, which is
    also what makes a payload of the wrong size a file-length failure rather than a silent
    reflow -- so the payloads, which the compiler writes, have to be built first.
    """
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    subprocess.run(["ninja"], cwd=ROOT, check=True)
    edge = next(line for line in (ROOT / "build.ninja").read_text().splitlines()
                if line.startswith("build build/SLUS_207.11.tail: cat "))
    # The edge also declares the code that generates it as an implicit input (`|`, R35a);
    # the tail is the explicit part, which is exactly what the `cat` command is given.
    tail = edge.split(": cat ", 1)[1].split("|", 1)[0].split()
    total = sum((ROOT / name).stat().st_size for name in tail)
    assert total == ELF_SIZE - LOADABLE_END, f"the tail covers {total} bytes"
    assert tail[0].endswith("shstrtab.databin.bin"), tail[0]
    assert tail[-1].endswith("section_headers.databin.bin"), tail[-1]
    script = (ROOT / "build/SLUS_207.11.ld").read_text()
    assert ".elf_header 0x0 : AT(0x0)" in script
    assert ".main 0x100000 : AT(0x80)" in script
    assert ".bss 0x2A2680 (NOLOAD)" in script
    # The sizes are asserted by the linker itself, so a padded split cannot slip through.
    assert "SIZEOF(.main) == 0x1A2680" in script
    assert "SIZEOF(.bss) == 0x414500" in script


def test_the_pinned_link_lists_its_inputs_in_address_order():
    """The link places the i-th input at the i-th address, so the order *is* the layout.

    A promoted unit breaks the one-input-per-split rule on purpose: the C object is linked
    where the unit's splits used to be, and those splits are *gone* from the script, because
    linking both would define their functions twice.  Every other split is listed, so the
    i-th input's address is still the layout, and the set of addresses is still complete.
    """
    import configure  # the promotion table the build itself reads

    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    script = (ROOT / "build/SLUS_207.11.ld").read_text()
    listed = re.findall(r"^\s+(\S+)\(\.text\)$", script, re.M)
    splits = {s.relative_to(ROOT).as_posix() for s in (ROOT / "asm/nonmatchings").rglob("*.s")}
    promoted = {p.object: p.address for p in configure.promotions()}
    replaced = {path for p in configure.promotions() for path in p.splits}
    assert promoted and set(promoted) <= set(listed), "the promoted object must be linked"
    assert not replaced & set(listed), "a replaced split must not be linked"
    def repo_path(obj: str) -> str:
        """The repo-relative input a script line names: a split's ``.s``, or the object."""
        obj = obj.removeprefix("build/")
        return obj[:-2] if obj.endswith(".s.o") else obj

    assert {repo_path(name) for name in listed if name.endswith(".s.o")} == splits - replaced
    assert len(listed) == len(splits) - len(replaced) + len(promoted)
    rows = [(promoted.get(name) or split_span((ROOT / repo_path(name)).read_text())[0], name)
            for name in listed]
    assert rows == sorted(rows), "the script must list its inputs in address order"


def test_configure_is_deterministic():
    """Every generated artefact is a function of the manifests, not of a previous run."""
    generated = ("build.ninja", "build/SLUS_207.11.ld", "config/usam2/splat.yaml")
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    first = {name: (ROOT / name).read_bytes() for name in generated}
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    for name, content in first.items():
        assert (ROOT / name).read_bytes() == content, f"{name} changed between runs"


def test_objects_only_configuration_keeps_the_link_out_of_the_graph():
    """The objdiff CI job assembles splits without ever linking the image."""
    subprocess.run(CONFIGURE + ["--objects"], cwd=ROOT, check=True)
    ninja = (ROOT / "build.ninja").read_text()
    assert "default objects" in ninja
    assert "build out/SLUS_207.11.elf:" not in ninja and "build g1:" not in ninja
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)  # leave the full graph behind


#: The three edges whose content the compiler driver computes: the promoted object and the
#: two payloads dumped out of it.
COMPILE_EDGES = ("cc src/sys/sys_scf.c",
                 "objsec .debug build/src/sys/sys_scf.c.o.debug",
                 "objsec .line build/src/sys/sys_scf.c.o.line")


def _dirty_edges(targets):
    """The edges ninja would run for ``targets``: its ``-n`` output, as descriptions."""
    p = subprocess.run(["ninja", "-n", *targets], cwd=ROOT, capture_output=True, text=True)
    assert p.returncode == 0, p.stdout + p.stderr
    return {match.group(1) for match in
            (re.match(r"^\[\d+/\d+\] (.*)$", line) for line in p.stdout.splitlines())
            if match}


def test_editing_the_compiler_driver_invalidates_the_compile_edges():
    """R35a: the graph depends on the code that generates it, not just on its inputs.

    ``compile.py`` decides the *bytes* of a promoted object (it stages the source at a path
    whose length is baked into the DWARF), but ninja does not hash command lines and the
    object's only declared input was the C source -- so editing it left the object, and the
    payloads dumped from it, in place.  Every gate stays green over a stale object, which is
    the failure this asserts away: touch the driver and the three compile edges go dirty.
    """
    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    built = ["build/src/sys/sys_scf.c.o", "build/src/sys/sys_scf.c.o.debug",
             "build/src/sys/sys_scf.c.o.line"]
    subprocess.run(["ninja"] + built, cwd=ROOT, check=True)
    stale = _dirty_edges(built) & set(COMPILE_EDGES)
    assert not stale, f"already stale before the touch: {sorted(stale)}"

    driver = ROOT / "tools/toolchain/compile.py"
    stat = driver.stat()
    try:
        # Two seconds past the object the driver produced, so the comparison cannot tie
        # (and cannot lose to a rebuild this test itself just triggered).
        os.utime(driver, ns=(stat.st_atime_ns,
                             os.stat(ROOT / built[0]).st_mtime_ns + 2_000_000_000))
        dirty = _dirty_edges(built)
    finally:
        os.utime(driver, (stat.st_atime, stat.st_mtime))
    missing = set(COMPILE_EDGES) - dirty
    assert not missing, f"touching {driver.name} did not invalidate: {sorted(missing)}"


def test_objdiff_project_covers_every_linked_code_object():
    """The progress report's project: every function the link places, one unit each.

    The unit set is the *linked* set, not the set that already has a source: a project that
    listed only what is written in C would report a skeleton with zero C as matched, which is
    the opposite of what a progress report is for.  A function with no source yet therefore
    has a ``null`` base (objdiff counts it as un-matched), and the promoted unit's functions
    compare retail's split object against the C object the build links in its place.
    """
    import configure

    subprocess.run(CONFIGURE, cwd=ROOT, check=True)
    project = json.loads((ROOT / "objdiff.json").read_text())
    assert project["min_version"] and project["custom_make"] == "ninja"
    units = {unit["name"]: unit for unit in project["units"]}
    segment = targets.get("usam2").geometry_required().code_segment
    code = {f"{segment}/{pathlib.Path(name).stem}"
            for _, name in configure.code_splits(configure.split_sources())}
    assert set(units) == code, "every code split the link places is a unit"

    promoted = {f"{segment}/{pathlib.Path(split).stem}": promotion.object
                for promotion in configure.promotions() for split in promotion.splits}
    assert promoted, "the promotion table is what makes a base non-null"
    for name, unit in units.items():
        assert (ROOT / unit["target_path"]).is_file(), f"{name}: no such target object"
        assert unit["target_path"].endswith(".s.o")
        assert unit["base_path"] == promoted.get(name), name
        if unit["base_path"] is not None:
            assert (ROOT / unit["base_path"]).is_file(), f"{name}: no such base object"
            assert unit["base_path"] != unit["target_path"], "a self-comparison measures nothing"


# ---------------------------------------------------------------------------
# --target: configure writes one target's config, and refuses to guess the other's
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("name", targets.names())
def test_configure_either_writes_the_named_targets_config_or_fails_loudly(name):
    """One invariant per target, whatever its measurement state happens to be.

    ``configure.py`` works on exactly one target: it either succeeds -- and then the yaml it
    wrote is *this* target's (its own config dir, its own retail ELF basename) -- or it stops
    with a message naming the target, exit 2 and no traceback.  A target whose geometry has
    not been measured yet (``ddrex2p``'s segment list is Task 5's) takes the second path and
    says which file has to be measured; it must never fall back to the old target's numbers,
    which would produce a plausible image of the wrong game.
    """
    target = targets.get(name)
    p = subprocess.run([sys.executable, "configure.py", "--target", name], cwd=ROOT,
                       capture_output=True, text=True)
    assert "Traceback" not in p.stderr, p.stderr
    if p.returncode == 0:
        yaml_text = (target.config_dir / "splat.yaml").read_text()
        assert target.elf.name in yaml_text
        assert f"config/{name}/" in yaml_text
        assert (target.config_dir / "splat.yaml").is_file()
    else:
        assert p.returncode == 2, p.stdout + p.stderr
        assert name in p.stderr
        if target.geometry is None:
            assert target.elf.name in p.stderr and "geometry" in p.stderr
            assert not (target.config_dir / "splat.yaml").exists()


def test_an_unknown_target_is_a_configuration_error_not_a_traceback():
    p = subprocess.run([sys.executable, "configure.py", "--target", "ddrmax2"], cwd=ROOT,
                       capture_output=True, text=True)
    assert p.returncode == 2
    assert "ddrmax2" in p.stderr and "usam2" in p.stderr and "ddrex2p" in p.stderr
    assert "Traceback" not in p.stderr
