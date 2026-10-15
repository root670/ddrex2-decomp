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
