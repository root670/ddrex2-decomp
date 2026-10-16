"""Borrow the public corpora's names for the library region, and validate every one.

The library region -- every function below the lowest game-code PC, ``0x0021C410`` in this
image -- is where the other decompilation projects have already done the analysis.  This
module is the borrow step, done once and with provenance:

* :func:`corpora` catalogues every surveyed corpus with its licence, what it publishes and
  its fetch/extract entry point (``docs/milestones/m3-library-sourcing.md`` is the survey).
* the *proposers* turn a corpus into name proposals for our own functions:
  :func:`byte_proposals` (masks relocated immediates and compares instructions -- the
  strongest evidence) and :func:`run_proposals` (a run of identical function sizes that
  occurs exactly once on both sides -- the size evidence, the only kind a corpus that
  publishes no bytes can give).
* :func:`validate` is the gate: a size that is not our function's own bounds, or published
  bytes that do not match after relocation masking, rejects the name.
* :func:`render_ledger` writes the committed ``config/usam2/borrowed_symbols.txt`` -- the
  input ``tools/oracle/emit_symbols.py`` merges into ``config/usam2/symbol_addrs.txt`` --
  and :func:`render_markdown` the committed ``config/usam2/library-names.md``.

Nothing is renamed silently: the ledger carries the corpus (its ``provenance:`` field), the
size the corpus published, how the name was proposed, and the licence is recorded next to
it in ``library-names.md``.  The corpus's *bytes* are never copied into this repository --
only the derived names, which are facts about the Sony SDK, not about the corpus's game.
"""

from __future__ import annotations

import argparse
import collections
import difflib
import hashlib
import pathlib
import random
import re
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT / "tools"))

from sdk import match  # noqa: E402
from elf import Elf  # noqa: E402

RETAIL = ROOT / "orig" / "SLUS_207.11"
SPLIT_ROOT = ROOT / "asm" / "nonmatchings" / "main"
CACHE = ROOT / ".cache" / "corpora"
LEDGER = ROOT / "config" / "usam2" / "borrowed_symbols.txt"
MARKDOWN = ROOT / "config" / "usam2" / "library-names.md"

# The loadable image: VA 0x100000 is file offset 0x80.
LOAD_VA = 0x00100000
LOAD_OFFSET = 0x80
# The lowest game-code PC (``sysGetDateNotation``, per orig/usam2.elf.txt): everything below
# it belongs to the statically linked library.
GAME_START = 0x0021C410

# A run of this many identical sizes, unique on both sides, is the size evidence.  Measured
# by :func:`coincidence_rate`: at 2 the expected chance-level yield is ~3 % of the observed
# one, at 3 it is ~2 %, and the runs of 2 alone are ~2/3 chance.
MIN_RUN = 3
# The archive source aligns one *archive* at a time, and a short sequence of repeated sizes
# produces unique runs by chance far more often than a whole library region does, so it needs
# a longer run to be evidence.  The value is the one this tree measured (see library-names.md
# "the control for the size evidence").
MIN_RUN_BY_SOURCE = {"oni2": 3, "recvx": 3, "sdk152": 5}
# The byte proposer only trusts a match of at least this many bytes (the Oni 2 dev build
# measurement: 12 words, 48 bytes, is where the hits stood out from identical stubs).
MIN_BYTES = 48
IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
# The provenances this tree gives itself: DWARF (the game's own debug info) and Ghidra (the
# function starts).  Everything else in the symbol ledger came from a borrow run.
BASE_PROVENANCE = ("dwarf", "ghidra")

SPLIT_BLOCK = re.compile(r"^nonmatching (\S+), (0x[0-9A-Fa-f]+)$")
SPLIT_INSN = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ")
SYMBOL_LINE = re.compile(r"^(?P<name>\S+)\s*=\s*(?P<address>0x[0-9A-Fa-f]+);\s*//\s*(?P<attrs>.*)$")
SOURCE_PATH = re.compile(r"^//\s*((?:\.\./|/)?[\w./+-]*\.(?:c|s|h))\s*$")
LEDGER_LINE = re.compile(
    r"^(?P<name>\S+) = 0x(?P<address>[0-9A-F]{8}); // type:func "
    r"size:0x(?P<size>[0-9A-F]+) provenance:(?P<source>\S+) tier:(?P<tier>\S+)")


# ---------------------------------------------------------------------------
# the corpora
# ---------------------------------------------------------------------------

# Fetchable corpora are pinned by digest: the borrow step is evidence, and evidence that
# cannot be re-fetched byte-for-byte is not evidence.  The local ones (`path`) are pinned by
# a digest of the file (oni2) or of the archive set (sdk152) recorded by `main`.
CORPORA = (
    {
        "key": "oni2",
        "title": "Oni 2 (SCPS_123.45) dev build, 2002-12-10 -- local, unstripped ELF",
        "licence": None,
        "licence_note": "an unreleased build of someone else's game: no licence is declared, "
                        "so nothing of it is committed or redistributed.  Only the SDK names "
                        "its .symtab exposes are derived here, and the file itself stays "
                        "outside the repository (it is evidence, not an input).",
        "entry_point": "path: /tmp/oni2dev/SCPS_123.45 (also /tmp/oni2/SCPS_123.45)",
        "path": "/tmp/oni2dev/SCPS_123.45",
        "sha256": "20dfb29d3fdecdf3c2065dd195c6dc50907c604d45ed24793958446d45569ea4",
        "publishes": "15,788 .symtab symbols (10,615 FUNC with sizes) and a 2.5 MB .mdebug "
                     "naming the Sony EE runtime sources; the library blob sits at the top of "
                     ".text (0x4a0000-0x4b4ddc)",
        "sizes": True, "bytes": True, "names": True, "copyable": True,
        "fetch": "place the image at /tmp/oni2dev/SCPS_123.45; sha256 must equal the pin",
        "note": "a *different SDK revision* (December 2002) from this 2003 title: a size-exact "
                "match is byte-validated, a size-only match carries the revision caveat",
    },
    {
        "key": "sdk152",
        "title": "Sony PS2 SDK 1.5.2 (devkit) -- local, extracted installers",
        "licence": None,
        "licence_note": "proprietary Sony SDK media: the archives stay on this machine and are "
                        "never committed.  Only the names their member symbol tables expose are "
                        "recorded, with the same policy as the corpus's own bytes.",
        "entry_point": "path: ~/sdk-extract/devkit152/RTLibs_ToolchainSetup/MAINDIR/ee/lib/*.a",
        "path": "~/sdk-extract/devkit152/RTLibs_ToolchainSetup/MAINDIR/ee/lib",
        "publishes": "66 SDK archives whose *member objects* are the code itself "
                     "(relocatable, so the comparison masks the relocation fields) with their "
                     "symbol tables: names with sizes, in member order (the order the linker "
                     "preserves) -- libkernl.a, libgraph.a, libvu0.a, libdma.a, libpad.a, "
                     "libcdvd.a, libssyn.a and the rest",
        "sizes": True, "bytes": True, "names": True, "copyable": True,
        "fetch": "unpack the devkit 1.5.2 installers (the survey's Task 5 Step 4)",
        "note": "the July-2005 era -- one generation *later* than this title, so a name whose "
                "whole body matches relocation-masked is a byte-validated name and a size-only "
                "match carries the revision caveat (member order is not the game's link order)",
    },
    {
        "key": "recvx",
        "title": "AshfordFamily/recvx-decomp (Resident Evil Code: Veronica X, PS2)",
        "licence": "MIT",
        "licence_note": "MIT: reuse is permitted with attribution; the attribution is in "
                        "config/usam2/library-names.md",
        "entry_point": "config/symbol_addrs.txt",
        "url": "https://raw.githubusercontent.com/AshfordFamily/recvx-decomp/master/config/symbol_addrs.txt",
        "sha256": "116426162377b4a35fe60c4c26b900687ebf9ea699c87bd12949a9267cc8c9e6",
        "publishes": "~921 named SDK functions with explicit sizes in its library region "
                     "(0x1000C0-0x12B060), local statics included; no bytes, no objects",
        "sizes": True, "bytes": False, "names": True, "copyable": True,
        "fetch": "curl the entry_point URL",
        "note": "an SDK 2.0.0 build: a size-only match is coincidence-prone, so only runs of "
                "identical sizes that occur exactly once on both sides are accepted",
    },
    {
        "key": "godhand",
        "title": "LucasPicoli/god-hand-decomp (God Hand, PS2)",
        "licence": "MIT",
        "licence_note": "MIT: reuse is permitted with attribution",
        "entry_point": "config/symbol_addrs.txt",
        "url": "https://raw.githubusercontent.com/LucasPicoli/god-hand-decomp/main/config/symbol_addrs.txt",
        "sha256": "efe18a9417825a9c77936c1331eb696b535eed2a1e63bd8d8bca7de143837994",
        "publishes": "~6,917 SDK function names, no sizes (the 40,215 `size:` entries are "
                     "data symbols); a later SDK generation",
        "sizes": False, "bytes": False, "names": True, "copyable": True,
        "fetch": "curl the entry_point URL",
        "note": "proposes nothing on its own (no size to validate with); used to corroborate "
                "the names other corpora propose",
    },
    {
        "key": "sly1",
        "title": "TheOnlyZac/sly1 (Sly Cooper, PS2)",
        "licence": "CC0-1.0",
        "licence_note": "CC0-1.0: public domain dedication; attribution is given anyway",
        "entry_point": "config/symbol_addrs.txt",
        "url": "https://raw.githubusercontent.com/TheOnlyZac/sly1/main/config/symbol_addrs.txt",
        "sha256": "4824a7b9ed267c2e62edda5af9edddffa7c9b01d24287c5bbb831b1012b1c253",
        "publishes": "3,938 named library functions grouped under the *original SDK source "
                     "path* (`/usr/local/sce/ee/gcc/src/newlib/libm/math/wf_fmod.c`, `libdma.c`, "
                     "`../eecdvd.c`, `klib.s`, `sifrpc.c`); no function sizes",
        "sizes": False, "bytes": False, "names": True, "copyable": True,
        "fetch": "curl the entry_point URL",
        "note": "proposes nothing on its own; corroborates a borrowed name *and* attributes it "
                "to the SDK source file",
    },
    {
        "key": "ps2sdk",
        "title": "ps2dev/ps2sdk",
        "licence": "AFL-2.0",
        "licence_note": "AFL-2.0: reuse is permitted with attribution",
        "entry_point": "https://github.com/ps2dev/ps2sdk (ee/{kernel,dma,graph,rpc,libgs,math3d})",
        "url": "https://github.com/ps2dev/ps2sdk",
        "sha256": None,
        "publishes": "an independent C reimplementation with headers and doxygen: names and "
                     "semantics/types, but no SDK bytes and no sizes",
        "sizes": False, "bytes": False, "names": True, "copyable": True,
        "fetch": "git clone https://github.com/ps2dev/ps2sdk",
        "note": "proposes nothing: an independent implementation cannot validate a *mapping*, "
                "and it publishes no sizes.  Its use is the semantics of an accepted name, "
                "which is the next step after this one",
    },
    {
        "key": "ghidra-patterns",
        "title": "ghidra-emotionengine-reloaded r5900_LE_patterns.xml",
        "licence": "Apache-2.0",
        "licence_note": "Apache-2.0: reuse is permitted with attribution",
        "entry_point": "https://github.com/chaoticgd/ghidra-emotionengine-reloaded "
                       "(data/patterns/r5900_LE_patterns.xml)",
        "url": "https://github.com/chaoticgd/ghidra-emotionengine-reloaded",
        "sha256": None,
        "publishes": "138 `<funcstart label=...>` SDK signatures (67 of which matched this "
                     "binary when the survey ran Ghidra over it)",
        "sizes": False, "bytes": False, "names": True, "copyable": True,
        "fetch": "git clone the repository, then apply the patterns with Ghidra",
        "note": "proposes nothing here: applying signature patterns needs Ghidra, which this "
                "step does not run; the survey's 67 hits stay a separate reference",
    },
    {
        "key": "mvc2",
        "title": "g-guthrie/mvc2-ps2-decomp",
        "licence": None,
        "licence_note": "no licence declared: all rights reserved, so nothing may be copied "
                        "out of it -- not one name, and not its bundled ELF.",
        "entry_point": "build-inputs/mvc2-ps2-build-inputs.tar.gz (their ELF, MWCCPS2 3.0.3, "
                       "Wibo 1.2.0, SHA-256 manifest) and config/functions.csv",
        "url": "https://github.com/g-guthrie/mvc2-ps2-decomp",
        "sha256": None,
        "publishes": "their retail ELF, their own function names (no `sce*`/`Gs*` names), and "
                     "a MWCCPS2 3.0.3 compiler bundle",
        "sizes": True, "bytes": True, "names": False, "copyable": False,
        "fetch": "not fetched: nothing may be copied from it",
        "note": "no licence declared, so it is read but not used: nothing may be copied from it, "
                "not one name.  Its one legitimate value -- a compiler/flag cross-check for the "
                "toolchain sample -- is Task 3's, and needs a licence question the user must "
                "answer first",
    },
)


def corpora() -> list[dict]:
    """Every surveyed corpus: licence, what it publishes, how to get it, whether to copy."""
    return [dict(entry) for entry in CORPORA]


def corpus(key: str) -> dict:
    for entry in CORPORA:
        if entry["key"] == key:
            return dict(entry)
    raise KeyError(f"no surveyed corpus is called {key!r}")


# ---------------------------------------------------------------------------
# our own functions, and the retail bytes
# ---------------------------------------------------------------------------


def split_functions(split_root: pathlib.Path | str = SPLIT_ROOT,
                    game_start: int = GAME_START) -> list[dict]:
    """Our library functions from the split: ``{symbol, address, size}``, address order.

    The split's own bounds are the truth here -- ``nonmatching <symbol>, 0x<size>`` is what
    the linker places and what ``objdiff`` measures -- so a borrowed size is compared against
    these, never against the corpus's own game.
    """
    root = pathlib.Path(split_root)
    if not root.is_dir():
        raise FileNotFoundError(
            f"{root}: no split: run ./ddr build first (the split is a build artifact)")
    out = []
    for path in sorted(root.glob("*.s")):
        current = None
        for line in path.read_text().splitlines():
            block = SPLIT_BLOCK.match(line)
            if block:
                current = {"symbol": block.group(1), "size": int(block.group(2), 16),
                           "address": None}
                out.append(current)
                continue
            if current is not None and current["address"] is None:
                insn = SPLIT_INSN.search(line)
                if insn:
                    current["address"] = int(insn.group(1), 16)
    return [r for r in out
            if r["address"] is not None and r["address"] < game_start]


def retail_bytes(address: int, size: int, elf_path: pathlib.Path | str = RETAIL) -> bytes:
    """The retail bytes of ``[address, address + size)``, in the pinned binary."""
    blob = pathlib.Path(elf_path).read_bytes()
    offset = LOAD_OFFSET + (address - LOAD_VA)
    return blob[offset:offset + size]


def our_blobs(ours: list[dict], elf_path: pathlib.Path | str = RETAIL) -> dict[int, bytes]:
    """``address -> retail bytes`` for every one of our functions (one read of the ELF)."""
    blob = pathlib.Path(elf_path).read_bytes()
    return {r["address"]: blob[LOAD_OFFSET + (r["address"] - LOAD_VA):][:r["size"]]
            for r in ours}


# ---------------------------------------------------------------------------
# reading a corpus
# ---------------------------------------------------------------------------


def parse_splat_symbols(text: str, game_start: int) -> list[dict]:
    """The sized library functions a splat-format symbol file publishes, address order.

    Only lines that carry a ``size:`` can take part in a size validation, ``type:label``
    (data) and ``ignore:true`` lines are not functions, and everything at or above the
    corpus's own game start is the corpus's game, not its library.
    """
    out = []
    for line in text.splitlines():
        if line.lstrip().startswith("//"):
            continue
        record = SYMBOL_LINE.match(line.strip())
        if record is None:
            continue
        attrs = record["attrs"]
        if "ignore:true" in attrs.replace(" ", "") or "type:label" in attrs.replace(" ", ""):
            continue
        size = re.search(r"\bsize:(0x[0-9A-Fa-f]+)", attrs)
        if size is None:
            continue
        address = int(record["address"], 16)
        if address >= game_start:
            continue
        out.append({"name": record["name"], "address": address,
                    "size": int(size.group(1), 16), "attrs": attrs})
    out.sort(key=lambda r: r["address"])
    return out


def parse_elf_symbols(path: pathlib.Path | str) -> list[dict]:
    """Every sized FUNC symbol in an unstripped ELF's symbol table (``{name, address, size}``)."""
    elf = Elf(str(path))
    out = [{"name": s.name, "address": s.value, "size": s.size}
           for s in elf.symbols if s.type == 2 and s.size and s.shndx != 0]
    out.sort(key=lambda r: (r["address"], -r["size"]))
    kept, end = [], 0
    for record in out:                      # aliases and overlapping symbols: keep the first
        if record["address"] < end:
            continue
        if not IDENTIFIER.match(record["name"]):
            continue
        kept.append(record)
        end = record["address"] + record["size"]
    return kept


ARCHIVE_JUNK = re.compile(r"^(gcc2_compiled\.|__gnu_compiled_c|__ps2_libinfo__|gp\.\d+|\.L)")


def member_bytes(elf, symbol) -> bytes:
    """A relocatable object's symbol bytes, read through the symbol's own *section*.

    ``Elf.read`` follows program headers, and an archive member has none -- it is an object, not
    an image -- so its code is located by section: the section's file offset plus the symbol's
    address inside it.  Those bytes are the member's code with the address-carrying fields
    unrelocated, which is exactly what :func:`match.compare` masks.
    """
    section = elf.sections[symbol.shndx]
    start = section.offset + (symbol.value - section.addr)
    return elf.data[start:start + symbol.size]


def archive_members(path: pathlib.Path | str) -> list[tuple[str, bytes]]:
    """``(member name, member bytes)`` of an ``ar`` archive, in member order."""
    data = pathlib.Path(path).read_bytes()
    if data[:8] != b"!<arch>\n":
        raise ValueError(f"{path}: not an ar archive")
    members, long_names, offset = [], b"", 8
    while offset + 60 <= len(data):
        header = data[offset:offset + 60]
        offset += 60
        if header[58:60] != b"`\n":
            raise ValueError(f"{path}: malformed member header at 0x{offset - 60:x}")
        name = header[:16].decode("latin-1").strip()
        size = int(header[48:58].decode("latin-1").strip())
        body = data[offset:offset + size]
        offset += size + (size % 2)
        if name == "//":
            long_names = body
            continue
        if name == "/":
            continue
        if name.startswith("/") and name[1:].isdigit():
            index = int(name[1:])
            name = long_names[index:long_names.index(b"/\n", index)].decode("latin-1")
        members.append((name.rstrip("/"), body))
    return members


def parse_archive(path: pathlib.Path | str, blobs: dict | None = None) -> list[dict]:
    """One archive's text symbols with sizes, in member order (the linker's own order).

    A member's functions are linked contiguously, and the linker walks the archive in member
    order, so this sequence is the layout evidence the size alignment keys on -- and because
    every member restarts at address 0, the *order* is the only thing that makes it evidence.

    ``blobs`` (when given) is filled with the member object's own bytes for each record, keyed
    by ``blob_key``: an archive member is a relocatable object, so those bytes are the code
    with the address-carrying fields unrelocated, which is exactly what ``match.compare``
    masks.
    """
    out = []
    with tempfile.TemporaryDirectory() as work:
        scratch = pathlib.Path(work) / "member.o"
        for member, body in archive_members(path):
            if body[:4] != b"\x7fELF":
                continue                    # a symbol table or a text member: no code
            scratch.write_bytes(body)
            try:
                elf = Elf(scratch)
            except Exception:
                continue
            symbols = [s for s in elf.symbols
                       if s.type == 2 and s.size and not ARCHIVE_JUNK.match(s.name)]
            symbols.sort(key=lambda s: (s.value, -s.size))
            end = 0
            for symbol in symbols:
                if symbol.value < end:
                    continue
                record = {"name": symbol.name, "address": symbol.value,
                          "size": symbol.size, "member": member,
                          "blob_key": (member, symbol.value)}
                out.append(record)
                if blobs is not None:
                    blobs[record["blob_key"]] = member_bytes(elf, symbol)
                end = symbol.value + symbol.size
    return out


def parse_source_paths(text: str) -> dict[str, str]:
    """``name -> the SDK source path`` a symbol file labels its entries with (sly1's shape)."""
    out, path = {}, None
    for line in text.splitlines():
        stripped = line.strip()
        labelled = SOURCE_PATH.match(stripped)
        if labelled:
            path = labelled.group(1)
            continue
        record = SYMBOL_LINE.match(stripped)
        if record is not None and path:
            out[record["name"]] = path
    return out


def parse_function_names(text: str) -> set[str]:
    """Every name a symbol file *marks* as a function (the corroboration set).

    Only an explicit ``type:func`` counts: a sized entry may be a data symbol
    (``g_chzCiphertext = 0x2483b8; // size:0x9``), and a name that is data in another project
    is not evidence about a function here.
    """
    out = set()
    for line in text.splitlines():
        stripped = line.strip()
        if stripped.startswith("//"):
            continue
        record = SYMBOL_LINE.match(stripped)
        if record is None:
            continue
        if "type:func" in record["attrs"].replace(" ", ""):
            out.add(record["name"])
    return out


# ---------------------------------------------------------------------------
# proposing: the two pieces of evidence
# ---------------------------------------------------------------------------


def align(our_sizes: list[int], their_sizes: list[int],
          min_run: int = MIN_RUN) -> tuple[list[tuple[int, int, int]], list[dict]]:
    """Maximal runs of identical sizes, unique on both sides.

    Returns ``[(our index, their index, length)]`` for the runs that carry evidence, and the
    blocks that were refused: ``isolated`` (shorter than ``min_run`` -- a single equal size is
    coincidence, the survey measured ~3 % of the yield arriving this way) and ``ambiguous``
    (the run's size list occurs somewhere else in one of the two sequences, so the alignment
    could have landed on the wrong functions).
    """
    matcher = difflib.SequenceMatcher(a=our_sizes, b=their_sizes, autojunk=False)

    def occurrences(sequence, run):
        length = len(run)
        return sum(1 for k in range(len(sequence) - length + 1)
                   if sequence[k:k + length] == list(run))

    blocks, refused = [], []
    for block in matcher.get_matching_blocks():
        if block.size == 0:
            continue
        if block.size < min_run:
            refused.append({"reason": "isolated", "length": block.size,
                            "our_index": block.a, "their_index": block.b})
            continue
        ours = our_sizes[block.a:block.a + block.size]
        theirs = their_sizes[block.b:block.b + block.size]
        here, there = occurrences(their_sizes, ours), occurrences(our_sizes, theirs)
        if here == 1 and there == 1:
            blocks.append((block.a, block.b, block.size))
        else:
            refused.append({"reason": "ambiguous", "length": block.size,
                            "our_index": block.a, "their_index": block.b,
                            "occurrences": {"their_side": here, "our_side": there}})
    return blocks, refused


def run_proposals(ours: list[dict], theirs: list[dict], source: str,
                  min_run: int = MIN_RUN) -> tuple[list[dict], list[dict]]:
    """Name our functions from runs of identical sizes (the size-evidence proposer).

    Returns ``(proposals, refused)``: the runs that were *not* evidence -- shorter than
    ``min_run``, or occurring more than once on one side -- are refusals, and they are counted
    in the ledger's yield so the yield accounts for everything the source offered.

    The corpus's records are used **in the order the caller gives them**, because for an archive
    that order *is* the evidence: a member restarts at address 0, so sorting the records by
    address would interleave the members and align our image against a sequence no linker ever
    produced.  Our own side is address-sorted, which is the order the linker placed it in.
    """
    ours = sorted(ours, key=lambda r: r["address"])
    blocks, refused = align([r["size"] for r in ours], [r["size"] for r in theirs], min_run)
    for refusal in refused:
        mine = ours[refusal["our_index"]]
        refusal.update(source=source, address=mine["address"], symbol=mine["symbol"],
                       names=[theirs[refusal["their_index"]]["name"]])
    proposals = []
    for our_index, their_index, length in blocks:
        for step in range(length):
            mine, other = ours[our_index + step], theirs[their_index + step]
            proposals.append({"address": mine["address"], "symbol": mine["symbol"],
                              "size": mine["size"], "name": other["name"], "tier": "run",
                              "source": source,
                              "evidence": {"run": length,
                                           "source_address": other["address"],
                                           "source_member": other.get("member")}})
    return proposals, refused


def byte_proposals(ours: list[dict], theirs: list[dict], our_bytes: dict, their_bytes: dict,
                   source: str, window: int = MIN_BYTES) -> tuple[list[dict], list[dict]]:
    """Name our functions from the corpus's *bytes* (the strongest proposer).

    A candidate must have our function's own size -- a name whose size differs is a different
    revision, not the same function -- and its first ``window`` bytes must be the same
    instructions after relocation masking.  Several candidates may match one function (the
    same routine is linked into more than one archive member); the name is accepted only when
    every matching candidate agrees on it.
    """
    by_size = collections.defaultdict(list)
    for record in theirs:
        by_size[record["size"]].append(record)
    proposals, refused = [], []
    for mine in sorted(ours, key=lambda r: r["address"]):
        if mine["size"] < window or mine["address"] not in our_bytes:
            continue
        blob = our_bytes[mine["address"]]
        matches = []
        for candidate in by_size.get(mine["size"], []):
            key = corpus_key(candidate)
            if key not in their_bytes:
                continue
            theirs_blob = their_bytes[key]
            result = match.compare(theirs_blob[:window], blob[:window])
            if result["identical"]:
                matches.append((candidate, result))
        if not matches:
            continue
        names = sorted({candidate["name"] for candidate, _ in matches})
        if len(names) > 1:
            refused.append({"address": mine["address"], "symbol": mine["symbol"],
                            "reason": "names disagree", "names": names})
            continue
        candidate, result = matches[0]
        full = match.compare(their_bytes[corpus_key(candidate)], blob) \
            if len(matches) == 1 else None
        proposals.append({
            "address": mine["address"], "symbol": mine["symbol"], "size": mine["size"],
            "name": candidate["name"], "tier": "bytes", "source": source,
            "evidence": {"source_key": corpus_key(candidate),
                         "source_address": candidate["address"],
                         "source_member": candidate.get("member"),
                         "candidates": len(matches), "window": window,
                         "masked_words": result["masked_words"],
                         "exact": result["exact"],
                         "whole_function": bool(full and full["identical"])}})
    return proposals, refused


def corpus_key(record: dict):
    """Where a corpus record's bytes live in the blob table its parser filled.

    An archive member restarts at address 0, so its records are keyed by ``(member, address)``;
    a linked image's records are keyed by their address.
    """
    return record.get("blob_key", record["address"])


def _rank(proposal: dict) -> tuple:
    """How strong a proposal's evidence is: the tier, then the match itself.

    A byte match beats a size run; a whole-function byte match beats a prefix of one; and a
    longer run of identical sizes beats a shorter one -- which is the measured shape of the
    coincidence: the chance-level yield concentrates in short runs.
    """
    evidence = proposal["evidence"]
    if proposal["tier"] == "bytes":
        return (0, 0 if evidence.get("whole_function") else 1, 0)
    return (1, 0, -evidence.get("run", 0))


def _order(proposal: dict) -> tuple:
    """``_rank`` with the source appended, so the choice between equal evidence is stable."""
    return _rank(proposal) + (proposal["source"],)


def decide(proposals: list[dict], taken: dict[str, int] | None = None
           ) -> tuple[list[dict], list[dict]]:
    """One name per address, by the strength of the evidence.

    The strongest proposal wins; a weaker one that disagrees is never dropped silently -- it
    travels on the record as ``contested``, and library-names.md prints it.  A *tie* that
    disagrees is refused: two equally strong sources naming one address differently is the
    coincidence the survey warns about, and nothing is renamed on a coin toss.

    ``taken`` maps a name already in the symbol ledger to its address, so a borrowed name
    cannot silently collide with a name this tree already has.
    """
    taken = taken or {}
    accepted, refused = [], []
    by_address = collections.defaultdict(list)
    for proposal in proposals:
        by_address[proposal["address"]].append(proposal)
    for address in sorted(by_address):
        group = sorted(by_address[address], key=_order)
        best = group[0]
        ties = [p for p in group if _rank(p) == _rank(best)]
        if any(p["name"] != best["name"] for p in ties):
            refused.append({"address": address, "symbol": best["symbol"],
                            "reason": "conflict",
                            "names": sorted({p["name"] for p in ties}),
                            "sources": [p["source"] for p in ties]})
            continue
        rest = [p for p in group if p is not best]
        record = dict(best)
        record["also"] = sorted({p["source"] for p in rest if p["name"] == best["name"]})
        record["contested"] = sorted({f"{p['name']} ({p['source']})"
                                      for p in rest if p["name"] != best["name"]})
        if best["name"] in taken and taken[best["name"]] != address:
            refused.append({"address": address, "symbol": best["symbol"],
                            "reason": "name taken", "names": [best["name"]],
                            "sources": [p["source"] for p in group],
                            "taken_at": taken[best["name"]]})
            continue
        accepted.append(record)
    return accepted, refused


# ---------------------------------------------------------------------------
# validating
# ---------------------------------------------------------------------------


def disambiguate(records: list[dict], taken: set[str] | None = None
                 ) -> tuple[list[dict], list[dict]]:
    """Give repeated names a suffix, the way the symbol ledger does: lowest address bare.

    A routine such as ``kCopy`` is linked into more than one archive member, so more than one
    of our functions really is called ``kCopy``.  The symbol ledger keeps the lowest address
    bare and suffixes the rest (`resolve_names` in tools/oracle/emit_symbols.py), so the
    borrow step does the same *here*: the ledger it writes is collision-free, and what
    library-names.md records is exactly what the build gets, with no oracle-side renaming.
    """
    names = collections.Counter(r["name"] for r in records)
    claimed = set(taken or ())
    out, renamed = [], []
    for record in sorted(records, key=lambda r: r["address"]):
        name = record["name"]
        if names[name] == 1 or name not in claimed:
            out.append(record)
            claimed.add(name)
            continue
        suffix = 1
        while f"{name}_{suffix}" in claimed:
            suffix += 1
        renamed_record = dict(record, name=f"{name}_{suffix}", borrowed_as=name)
        claimed.add(renamed_record["name"])
        out.append(renamed_record)
        renamed.append(renamed_record)
    return out, renamed


def validate(name: str, size: int, retail_bytes: bytes, *, published_bytes: bytes | None = None,
             published_digest: str | None = None, window: int | None = None) -> dict:
    """Is this borrowed name *accepted* for our function?

    ``size`` is what the corpus publishes and ``retail_bytes`` is our function at its own
    bounds, so the size test is exactly "the corpus's size is our size".  Where the corpus
    publishes the function's bytes or a digest, they must match too -- after relocation
    masking, since the corpus is linked at a different address.

    ``window`` is how many of the corpus's bytes the proposer actually matched (the byte
    proposer uses a 48-byte prefix, the length at which the Oni 2 measurement separated real
    matches from identical stubs).  A corpus built from a different SDK *revision* keeps the
    same function with a different body far past its first instructions, so beyond the window
    the size is the evidence and the bytes are a revision question -- the record says which.

    Returns ``{name, size, accepted, reason, evidence}``; ``evidence["bytes"]`` is ``None``
    when the corpus published no bytes, which is the "size alone" case the ledger marks.
    """
    evidence = {"bytes": None, "masked_words": None, "exact": None, "digest": None,
                "window": None}
    if not isinstance(size, int) or size <= 0 or size % 4:
        return _refused(name, size, evidence,
                        f"size 0x{size:X} is not a positive multiple of four")
    if size != len(retail_bytes):
        return _refused(name, size, evidence,
                        f"size mismatch: the corpus publishes 0x{size:X}, our bounds are "
                        f"0x{len(retail_bytes):X}")
    if not IDENTIFIER.match(name):
        return _refused(name, size, evidence, f"{name!r} is not a C identifier")
    if published_bytes is not None:
        length = len(published_bytes) if window is None else min(window, len(published_bytes))
        result = match.compare(published_bytes[:length], retail_bytes[:length])
        evidence["window"] = length
        if not result["identical"]:
            return _refused(name, size, evidence,
                            f"bytes differ at word {result['first_difference']} of the first "
                            f"{length // 4} ({result['differing_words']} word(s) differ after "
                            f"masking)")
        whole = length >= len(retail_bytes)
        evidence["bytes"] = "whole function" if whole else f"first {length} bytes"
        evidence["masked_words"] = result["masked_words"]
        evidence["exact"] = result["exact"]
        return {"name": name, "size": size, "accepted": True, "evidence": evidence,
                "reason": f"size and bytes match ({evidence['bytes']}, "
                          f"{result['masked_words']} relocated word(s) masked)"}
    if published_digest is not None:
        actual = hashlib.sha256(retail_bytes).hexdigest()
        evidence["digest"] = actual
        if actual != published_digest:
            return _refused(name, size, evidence,
                            f"digest mismatch: the corpus publishes {published_digest[:16]}..., "
                            f"our bytes hash to {actual[:16]}...")
        return {"name": name, "size": size, "accepted": True, "evidence": evidence,
                "reason": "size and digest match"}
    return {"name": name, "size": size, "accepted": True, "evidence": evidence,
            "reason": f"size alone (the corpus publishes no bytes): 0x{size:X}"}


def _refused(name: str, size: int, evidence: dict, reason: str) -> dict:
    return {"name": name, "size": size, "accepted": False, "evidence": evidence,
            "reason": reason}


def coincidence_rate(our_sizes: list[int], their_sizes: list[int], min_run: int = MIN_RUN,
                     trials: int = 200, seed: int = 20261015) -> dict:
    """What the same alignment finds when the layout evidence is destroyed by shuffling.

    The control for the size evidence: permuting the corpus's sizes keeps every value (so
    every name is still "plausible") and destroys only the order, which is the thing the runs
    claim to be evidence of.  A yield far above this is layout evidence; a yield near it is
    coincidence.
    """
    random.seed(seed)
    ours = list(our_sizes)
    theirs = list(their_sizes)
    observed = sum(block[2] for block in align(ours, theirs, min_run)[0])
    shuffled = []
    for _ in range(trials):
        permuted = theirs[:]
        random.shuffle(permuted)
        shuffled.append(sum(block[2] for block in align(ours, permuted, min_run)[0]))
    return {"trials": trials, "seed": seed, "min_run": min_run, "observed": observed,
            "chance_mean": round(sum(shuffled) / len(shuffled), 2),
            "chance_max": max(shuffled),
            "chance_nonzero": sum(1 for value in shuffled if value)}


# ---------------------------------------------------------------------------
# the ledger
# ---------------------------------------------------------------------------

LEDGER_HEADER = """\
// Borrowed library names -- generated by tools/sdk/borrow.py; do not hand-edit.
//
// Every line is a name a corpus published for one of this image's library functions, and
// passed tools/sdk/borrow.validate: the corpus's size is our function's own split bounds
// (which is why `size:` here is the validated number and not 0), and where the corpus
// publishes bytes they match after relocation masking -- so **every line is byte-proven**: the
// run tier (a run of identical sizes in another link's layout) is a proposal and stays in
// config/usam2/library-names.md, because a symbol file line carries no tier and a layout guess
// would be indistinguishable from a name that was proved word for word.  `size:` is that
// validated number;
// what reaches splat is `size:0x0`, on purpose, because splat uses the attribute to lay the
// split out: forwarding a non-zero size re-segments the bytes around it and produced a split
// with no address comment (`asm/nonmatchings/main/func_001A6AE0.s`), which the link refuses.
// The split therefore keeps detecting the bounds itself -- the same bounds this ledger
// checked -- and config/usam2/library-names.md carries the licence, evidence and provenance.
"""


def render_ledger(records: list[dict]) -> str:
    """The build artifact's input: one line per *byte-proven* name, address-sorted."""
    lines = [LEDGER_HEADER]
    for record in sorted(records, key=lambda r: r["address"]):
        lines.append(
            f"{record['name']} = 0x{record['address']:08X}; // type:func "
            f"size:0x{record['size']:X} provenance:{provenance_of(record)} "
            f"tier:{record['tier']}\n")
    return "".join(lines)


def provenance_of(record: dict) -> str:
    """The ledger's provenance key for a record: the corpus, without its archive.

    ``configure.py`` rewrites the comment into splat's syntax as ``provenance=KEY``, and splat
    reads that as a boolean -- ``provenance=sdk152:libdma.a`` splits into the attribute
    ``provenance=sdk152`` with the value ``libdma.a`` and the build stops with
    "Invalid Boolean value".  So the key is the corpus alone and the archive or member it came
    from is recorded in config/usam2/library-names.md's own ``source`` column.
    """
    return record["source"].split(":")[0]


def parse_ledger(text: str) -> list[dict]:
    out = []
    for line in text.splitlines():
        record = LEDGER_LINE.match(line.strip())
        if record is None:
            continue
        out.append({"name": record["name"], "address": int(record["address"], 16),
                    "source": record["source"], "size": int(record["size"], 16),
                    "tier": record["tier"]})
    return out


def taken_names(path: pathlib.Path | str = ROOT / "config" / "usam2" / "symbol_addrs.txt"
                ) -> dict[str, int]:
    """``name -> address`` for the names this tree gave *itself* (DWARF and Ghidra).

    Names a previous borrow run placed are excluded: the borrow step is idempotent, so the
    ledger it already produced must not make the next run refuse the names it derived.  Only a
    name the tree already carried makes a borrowed name a collision.
    """
    out = {}
    for line in pathlib.Path(path).read_text().splitlines():
        record = SYMBOL_LINE.match(line.strip())
        if record is None:
            continue
        provenance = re.search(r"\bprovenance:(\S+)", record["attrs"])
        if provenance is None or provenance.group(1) not in BASE_PROVENANCE:
            continue
        out[record["name"]] = int(record["address"], 16)
    return out


# ---------------------------------------------------------------------------
# rendering the ledger's human half
# ---------------------------------------------------------------------------


def _name_row(row: dict, run: bool = False) -> str:
    """One row of either name table."""
    if run:
        evidence = f"`{row['evidence']['run']}`"
    else:
        evidence = (f"masked-equal over {row['evidence'].get('window')} bytes"
                    + (", the whole function" if row["evidence"].get("whole_function")
                       else ", the first instructions; the rest is a revision question")
                    + f", {row['evidence'].get('masked_words')} relocated word(s)")
    name = f"`{row['name']}`"
    if row.get("borrowed_as"):
        name += f" (the corpus's `{row['borrowed_as']}`, repeated in the image)"
    source = f"`{row['source']}`"
    member = row["evidence"].get("source_member")
    if member:                      # an archive member is where the name and the bytes came from
        source += f" `{member}`"
    return (f"| `0x{row['address']:08X}` | {name} | {source} | `0x{row['size']:X}` | "
            f"{evidence} | {row.get('sdk_source') or '-'} | "
            f"{', '.join(row.get('corroborated_by') or []) or '-'} | "
            f"{', '.join(row.get('contested') or []) or '-'} |")


def render_markdown(artifact: list[dict], proposed_only: list[dict], yields: list[dict],
                    rejections: list[dict], controls: list[dict]) -> str:
    """``config/usam2/library-names.md``: what was borrowed, from where, and how it was checked.

    Two tables of names, because the two kinds of evidence are not interchangeable: the byte
    tier is what goes into the build artifact (`borrowed_symbols.txt` -> `./ddr oracle` ->
    `symbol_addrs.txt`), and the run tier is a proposal about another link's layout that stays
    here with its run length recorded.
    """
    out = [
        "# Borrowed library names (M3 Task 5)\n",
        "Generated by `tools/sdk/borrow.py`; do not hand-edit.  Two lists: the names that went",
        "into the build artifact (`config/usam2/borrowed_symbols.txt`, and from there via",
        "`./ddr oracle` into `config/usam2/symbol_addrs.txt`) and the names that were *proposed*",
        "but kept out of it, plus everything that was refused and why.\n",
        "Attribution: this file is derived from the decompilation projects below.  The corpora's",
        "bytes are never copied into this repository -- what is recorded is the *derived* name",
        "for one of this image's functions, with the licence of the corpus it came from.\n",
        "## Sources\n",
        "| key | corpus | licence | publishes | entry point | digest |",
        "|---|---|---|---|---|---|",
    ]
    for entry in CORPORA:
        digest = entry.get("sha256") or "-"
        out.append(f"| `{entry['key']}` | {entry['title']} | {entry['licence'] or 'none declared'} "
                   f"| {entry['publishes']} | `{entry['entry_point']}` | `{digest[:16]}` |")
    out += ["\n## Yield per source\n",
            "`proposed` is the number of *names* the source proposed; `accepted` the number that",
            "passed `validate`; `in artifact` the subset whose evidence is the function's own",
            "bytes (the only names the build gets); `proposed only` the rest, which rest on a run",
            "of identical sizes; `refused` the proposals refused (a conflict, disagreeing byte",
            "candidates, a name this tree already carries, or a failed validation); and `runs",
            "refused` counts the candidate runs the proposer itself refused as not evidence (too",
            "short, or occurring more than once on one side) -- no name was proposed for those,",
            "so they are counted rather than listed.  Proposals for one address are *merged* (the",
            "strongest evidence wins; see `also` and `contested` below), so `accepted` is lower",
            "than the sum of `proposed` by design.\n",
            "`accepted` counts the names a source *won* (the strongest evidence at that",
            "address); a name several sources propose is won once, and the others appear in the",
            "winner's `also` and `contested` columns.  A source that publishes no sizes or bytes",
            "cannot propose a mapping, so its row is its corroboration instead: how many accepted",
            "names it independently publishes as a function.\n",
            "| source | proposes | proposed | accepted | in artifact | proposed only | refused | runs refused | corroborates |",
            "|---|---|---|---|---|---|---|---|---|"]
    for row in yields:
        out.append(f"| `{row['key']}` | {row['proposes']} | {row['proposed']} | "
                   f"{row['accepted']} | {row.get('in_artifact', 0)} | "
                   f"{row.get('proposed_only', 0)} | {row['rejected']} | "
                   f"{row.get('runs_refused', 0)} | {row.get('supports', 0)} |")
    out += ["\n## The control for the size evidence\n",
            "The size proposers claim that a *run* of identical function sizes which occurs",
            "exactly once on both sides is layout evidence.  The control shuffles the corpus's",
            "sizes -- every value survives, only the order the claim rests on is destroyed -- and",
            "runs the same alignment:\n",
            "| source | positions named by runs | chance mean | chance max | shuffles with any hit |",
            "|---|---|---|---|---|"]
    for control in controls:
        out.append(f"| `{control['key']}` | {control['observed']} | {control['chance_mean']} | "
                   f"{control['chance_max']} | {control['chance_nonzero']}/{control['trials']} |")
    out += [f"\n**{len(artifact)} names are in the build artifact (every one of them",
            f"byte-proven); {len(artifact) + len(proposed_only)} names were accepted in total and",
            f"{len(proposed_only)} of those stay here as proposals.**\n"]
    out += ["\n## Names in the build artifact (byte evidence)\n",
            "Every name here was accepted because the corpus publishes the function's own bytes",
            "and they matched ours after relocation masking, at our function's own size.  These",
            "are the lines of `config/usam2/borrowed_symbols.txt`.  `evidence` says whether the",
            "whole body matched or only the first 48 bytes (beyond which a corpus from another SDK",
            "revision is a different question).  `size` is the corpus's published size, which",
            "`validate` required to equal our split bounds.  `sdk source` is sly1's attribution of",
            "the name to its original SDK source file; `corroborated by` lists the further corpora",
            "that publish the same name; `contested by` lists a weaker proposal that named this",
            "address differently (it did not win).\n",
            "| address | name | source (member) | size | evidence | sdk source | corroborated by | contested by |",
            "|---|---|---|---|---|---|---|---|"]
    for row in sorted(artifact, key=lambda r: r["address"]):
        out.append(_name_row(row))
    out += ["\n## Names proposed, not in the build artifact (size-run evidence)\n",
            "These rest on a run of identical function sizes that occurs exactly once on both",
            "sides -- evidence about the *layout* of another link, not about this function -- so",
            "they are proposals with a measured chance level (see the control above), and they stay",
            "out of `symbol_addrs.txt`, whose lines carry no tier.  `run` is how many consecutive",
            "functions agreed, which is the strength of the claim.\n",
            "| address | name | source (member) | size | run | sdk source | corroborated by | contested by |",
            "|---|---|---|---|---|---|---|---|"]
    for row in sorted(proposed_only, key=lambda r: r["address"]):
        out.append(_name_row(row, run=True))

    out += ["\n## Refused names\n",
            "`conflict` = two *equally strong* proposals disagree about one address (nothing was",
            "renamed);",
            "`names disagree` = several byte-matching candidates carried different names;",
            "`isolated` = candidate runs too short to anchor anything (counted, not listed: no",
            "name was proposed);",
            "`ambiguous` = a candidate run that occurs more than once on one side (likewise);",
            "`name taken` = the name already names another address in this tree;\n",
            "| our symbol | name | source(s) | reason | detail |", "|---|---|---|---|---|"]
    for row in sorted(rejections, key=lambda r: (r["reason"], r.get("address") or 0)):
        names = ", ".join(f"`{n}`" for n in row.get("names") or [] if n) or "-"
        detail = row.get("detail") or ""
        if row.get("taken_at"):
            detail = f"already names `0x{row['taken_at']:08X}`"
        address = f"`0x{row['address']:08X}`" if row.get("address") else "-"
        out.append(f"| {address} | {names} | "
                   f"{', '.join(row.get('sources') or [row.get('source')]) or '-'} | "
                   f"{row['reason']} | {detail} |")
    return "\n".join(out) + "\n"


# ---------------------------------------------------------------------------
# the borrow run
# ---------------------------------------------------------------------------


def _source_text(entry: dict, cache: pathlib.Path) -> str | None:
    """A fetchable corpus's text, from the cache, verified against its pinned digest."""
    fetch = entry.get("url")
    if not fetch:
        return None
    path = cache / entry["key"] / "symbol_addrs.txt"
    if not path.is_file():
        return None
    text = path.read_text()
    actual = hashlib.sha256(text.encode()).hexdigest()
    if entry.get("sha256") and actual != entry["sha256"]:
        raise ValueError(f"{path}: sha256 {actual} != pinned {entry['sha256']}")
    return text


def fetch(entry: dict, cache: pathlib.Path | str = CACHE, override_url: str | None = None
          ) -> pathlib.Path:
    """Download a fetchable corpus into ``cache`` and verify its pinned digest."""
    import urllib.request
    if not entry.get("copyable", False):
        raise ValueError(f"{entry['key']}: no licence declares this corpus reusable")
    url = override_url or entry["url"]
    path = pathlib.Path(cache) / entry["key"] / "symbol_addrs.txt"
    path.parent.mkdir(parents=True, exist_ok=True)
    with urllib.request.urlopen(url, timeout=120) as response:   # noqa: S310 (pinned URLs)
        blob = response.read()
    actual = hashlib.sha256(blob).hexdigest()
    if actual != entry["sha256"]:
        raise ValueError(f"{url}: sha256 {actual} != pinned {entry['sha256']}")
    path.write_bytes(blob)
    return path


def library_region(records: list[dict], low: int, high: int) -> list[dict]:
    """The records inside ``[low, high)`` -- a corpus's own library blob, in link order."""
    return [r for r in records if low <= r["address"] < high]


# The corpus's own lowest game-code PC: what sits below it is its library region.  Only the
# corpora the *run* proposer reads need one -- god-hand links its library at the *top* of its
# .text, so its library is not a lower range at all, and it proposes nothing anyway.
CORPUS_GAME_START = {"recvx": 0x0012B0A0, "sly1": 0x00185758}


def game_start_of(key: str) -> int:
    """The corpus's own lowest game-code PC, for the corpora whose library sits below it."""
    if key not in CORPUS_GAME_START:
        raise ValueError(f"{key}: no game-code start recorded, so it has no lower library "
                         f"range to align against")
    return CORPUS_GAME_START[key]


def oni2_library_region(records: list[dict]) -> list[dict]:
    """Oni 2's own library blob: the top of its ``.text``, 0x4a0000-0x4b4ddc."""
    return library_region(records, 0x004A0000, 0x004B4DDC)


def corpus_text(key: str, cache: pathlib.Path | str = CACHE) -> str | None:
    """A fetchable corpus's text: from the cache, else fetched; ``None`` if neither works.

    A corpus that is not reachable proposes nothing and corroborates nothing: the ledger is
    evidence, and evidence that cannot be obtained is not evidence.
    """
    entry = corpus(key)
    text = _source_text(entry, cache)
    if text is not None:
        return text
    try:
        return fetch(entry, cache).read_text()
    except Exception as exc:                       # no cache and no network
        print(f"borrow: {key}: {exc}", file=sys.stderr)
        return None


def corpus_records(key: str, cache: pathlib.Path) -> tuple[list[dict], str, dict]:
    """A corpus's records, how it was obtained, and the code bytes it publishes.

    The third element is ``{}`` for a corpus that publishes no code: only a corpus that
    publishes the function's own bytes can be byte-compared, and byte evidence is what decides a
    name for the build artifact.
    """
    entry = corpus(key)
    if entry.get("path"):
        root = pathlib.Path(entry["path"]).expanduser()
        if not root.exists():
            return [], "absent", {}
        if key == "sdk152":
            records, blobs = [], {}
            for archive in sorted(root.glob("*.a")):
                records += [dict(r, source=f"sdk152:{archive.name}")
                            for r in parse_archive(archive, blobs)]
            return records, "local", blobs
        records = parse_elf_symbols(root)
        elf = Elf(str(root))
        return (records, "local",
                {r["address"]: elf.read(r["address"], r["size"]) for r in records})
    text = corpus_text(key, cache)
    if text is None:
        return [], "absent", {}
    return parse_splat_symbols(text, game_start_of(key)), "cache", {}


def _display(path) -> str:
    """A path as a reader types it: repo-relative when it is inside the repo."""
    try:
        return str(pathlib.Path(path).relative_to(ROOT))
    except ValueError:
        return str(path)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Borrow the corpora's library names, validate them, write the ledger.")
    parser.add_argument("--cache", type=pathlib.Path, default=CACHE)
    parser.add_argument("--ledger", type=pathlib.Path, default=LEDGER)
    parser.add_argument("--markdown", type=pathlib.Path, default=MARKDOWN)
    parser.add_argument("--split", type=pathlib.Path, default=SPLIT_ROOT)
    parser.add_argument("--retail", type=pathlib.Path, default=RETAIL)
    parser.add_argument("--symbols", type=pathlib.Path,
                        default=ROOT / "config" / "usam2" / "symbol_addrs.txt")
    parser.add_argument("--trials", type=int, default=100,
                        help="shuffles per source for the coincidence control")
    args = parser.parse_args(argv)

    ours = split_functions(args.split)
    retail = Elf(str(args.retail))
    blobs = {r["address"]: retail.read(r["address"], r["size"]) for r in ours}
    print(f"borrow: {len(ours)} library functions of our own below 0x{GAME_START:X} "
          f"(split bounds, {sum(r['size'] for r in ours)} bytes)")

    proposals: list[dict] = []
    rejections: list[dict] = []
    yields: list[dict] = []
    controls: list[dict] = []
    isolates: list[dict] = []
    corpus_blobs: dict[str, dict] = {}
    our_sizes = [r["size"] for r in ours]

    for key, label in (("oni2", "bytes and runs, over its library blob"),
                       ("sdk152", "bytes and runs, per archive member order"),
                       ("recvx", "runs only, over its library region")):
        records, how, their_blobs = corpus_records(key, args.cache)
        if not records:
            print(f"borrow: {key} is {how}: a ledger without it would be a partial ledger, "
                  f"so nothing was written", file=sys.stderr)
            return 2
        print(f"borrow: {key}: {len(records)} records ({how}), "
              f"{len(their_blobs)} with code")
        corpus_blobs[key] = their_blobs
        hits = []
        if their_blobs:                       # the corpus publishes the function's own code
            byte_hits, refused = byte_proposals(ours, records, blobs, their_blobs, key)
            hits += byte_hits
            rejections += [dict(r, source=key) for r in refused]
        minimum = MIN_RUN_BY_SOURCE[key]
        if key == "sdk152":
            # One sequence per archive: a member restarts at address 0, and the archive's own
            # member order is the only thing that makes the run evidence.
            by_archive = collections.defaultdict(list)
            for record in records:
                by_archive[record["source"]].append(record)
            total = {"observed": 0, "chance_mean": 0.0, "chance_max": 0, "chance_nonzero": 0,
                     "trials": args.trials, "min_run": minimum, "key": key, "sequences": 0}
            for archive, group in sorted(by_archive.items()):
                archive_hits, archive_refused = run_proposals(ours, group, archive, minimum)
                hits += archive_hits
                isolates += archive_refused
                if not archive_hits:
                    continue
                control = coincidence_rate(our_sizes, [r["size"] for r in group],
                                           minimum, args.trials)
                for field in ("observed", "chance_mean", "chance_max", "chance_nonzero"):
                    total[field] += control[field]
                total["sequences"] += 1
            total["chance_mean"] = round(total["chance_mean"], 2)
            controls.append(total)
        else:
            inside = oni2_library_region(records) if key == "oni2" else records
            run_hits, run_refused = run_proposals(ours, inside, key, minimum)
            hits += run_hits
            isolates += run_refused
            controls.append(dict(coincidence_rate(our_sizes, [r["size"] for r in inside],
                                                  minimum, args.trials), key=key,
                                 sequences=1))
        proposals += hits
        yields.append({"key": key, "proposes": label, "proposed": len(hits),
                       "accepted": 0, "in_artifact": 0, "proposed_only": 0, "rejected": 0})

    for key in ("godhand", "sly1"):
        # Both publish names and no function sizes, so neither can *propose* a mapping; what
        # they can do is corroborate one, and sly1 can attribute it to an SDK source file.
        text = corpus_text(key, args.cache)
        yields.append({"key": key,
                       "proposes": f"nothing (names only, {'cache' if text else 'absent'}): "
                                   f"corroboration, attribution",
                       "proposed": 0, "accepted": 0, "in_artifact": 0, "proposed_only": 0,
                       "rejected": 0})

    tree_names = taken_names(args.symbols)
    accepted, refused = decide(proposals, tree_names)
    rejections += refused

    # The run proposers' own refusals, one row per (source, reason) with a count of *runs*: a
    # candidate run too short to anchor anything is not a name proposal, so there is no name.
    grouped = collections.Counter((r["source"].split(":")[0], r["reason"]) for r in isolates)
    for (source, reason), count in sorted(grouped.items()):
        rejections.append({"source": source, "reason": reason, "names": [], "runs": count,
                           "detail": f"{count} candidate run(s)"
                                     + (" shorter than the minimum"
                                        if reason == "isolated" else
                                        " that occur more than once on one side")})

    corroborating: dict[str, set] = collections.defaultdict(set)
    texts = {key: corpus_text(key, args.cache) for key in ("godhand", "sly1")}
    for key, text in texts.items():
        for name in parse_function_names(text) if text else ():
            corroborating[name].add(key)
    sdk_source_paths = parse_source_paths(texts["sly1"]) if texts["sly1"] else {}

    rows = []
    for record in accepted:
        published = corpus_blobs[record["source"].split(":")[0]].get(
            record["evidence"].get("source_key")) if record["tier"] == "bytes" else None
        verdict = validate(record["name"], record["size"], blobs[record["address"]],
                           published_bytes=published,
                           window=record["evidence"].get("window"))
        if not verdict["accepted"]:
            rejections.append(dict(record, source=record["source"], reason="validation",
                                   names=[record["name"]], detail=verdict["reason"]))
            continue
        row = dict(record)
        row["corroborated_by"] = sorted(corroborating.get(record["name"], set()))
        row["sdk_source"] = sdk_source_paths.get(record["name"])
        rows.append(row)

    # A routine linked into several members is several of our functions with one name; the
    # suffixing happens here, so the ledger that is committed is already collision-free.
    rows, renamed = disambiguate(rows, set(tree_names))
    if renamed:
        print(f"borrow: {len(renamed)} names are a repeat of a name already placed at a lower "
              f"address: suffixed the way resolve_names does")

    # Only the byte tier goes into the build artifact.  A run of identical sizes is a proposal
    # about the *layout* of a different link, and `symbol_addrs.txt` carries no tier, so a
    # layout guess in it would be indistinguishable from a name that was proved word for word.
    artifact = [row for row in rows if row["tier"] == "bytes"]
    proposed_only = [row for row in rows if row["tier"] != "bytes"]

    per_source = collections.Counter(row["source"].split(":")[0] for row in rows)
    per_artifact = collections.Counter(row["source"].split(":")[0] for row in artifact)
    per_reject: collections.Counter = collections.Counter()
    per_run: collections.Counter = collections.Counter()
    for refusal in rejections:
        if not refusal.get("source"):
            continue
        key = refusal["source"].split(":")[0]
        if "runs" in refusal:                # an aggregate row: no name was proposed
            per_run[key] += refusal["runs"]
        else:
            per_reject[key] += 1
    supports = collections.Counter(key for row in rows for key in row["corroborated_by"])
    for row in yields:
        row["accepted"] = per_source[row["key"]]
        row["in_artifact"] = per_artifact[row["key"]]
        row["proposed_only"] = row["accepted"] - row["in_artifact"]
        row["rejected"] = per_reject[row["key"]]
        row["runs_refused"] = per_run[row["key"]]
        row["supports"] = supports[row["key"]]

    args.ledger.parent.mkdir(parents=True, exist_ok=True)
    args.ledger.write_text(render_ledger(artifact))
    args.markdown.write_text(render_markdown(artifact, proposed_only, yields, rejections,
                                             controls))
    print(f"borrow: {len(artifact)} names into the build artifact and {len(proposed_only)} "
          f"proposed only, {len(rejections)} refused -> {_display(args.ledger)} and "
          f"{_display(args.markdown)}")
    for row in yields:
        print(f"  {row['key']:14s} {row['proposes']:36s} proposed {row['proposed']:5d} "
              f"accepted {row['accepted']:5d} artifact {row['in_artifact']:5d} "
              f"proposed-only {row['proposed_only']:5d} refused {row['rejected']:4d} "
              f"runs-refused {row['runs_refused']:5d}")
    for control in controls:
        print(f"  control {control['key']:12s} observed {control['observed']:5d} "
              f"chance mean {control['chance_mean']:6} max {control['chance_max']:4d} "
              f"over {control['trials']} shuffles of {control['sequences']} sequence(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
