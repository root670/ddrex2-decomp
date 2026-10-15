"""`configure.py` must split the retail ELF and emit the ninja graph the build drives.

These tests run the real toolchain: :file:`configure.py` shells out to splat and rewrites
:file:`config/usam2/splat.yaml` plus the generated symbol/undefined files from the
manifests, so a geometry or manifest mistake surfaces here rather than in the link.
"""

import json
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
CONFIGURE = [sys.executable, "configure.py", "--config", "usam2"]


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
