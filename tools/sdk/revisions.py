"""Which SDK archive revisions the DDR Extreme 2 (US) preview template links, byte-wise.

The template's own ``__ps2_libinfo__`` objects stamp eleven libraries:
``PsIIlibgraph3000 PsIIlibdma3000 PsIIlibvu03000 PsIIlibipu3000 PsIIlibkernl3000
PsIIlibpad3020 PsIIlibcdvd3000 PsIIlibmc3020 PsIIlibscf3000 PsIIlibeyety1300
PsIInetcnfif3020``.  A stamp names a release, not a file: several tlib releases ship
byte-identical objects for a library, and the July-2005 media is a *later* release than
some of the stamps.  So the stamp is confirmed against bytes -- an archive is only
*chosen* for a library when its members reproduce the template's code instruction for
instruction, under the relocation masking :mod:`sdk.match` defines (``j``/``jal`` targets
and I-type immediates are link addresses and carry no code).

Two directions are measured, because they answer different questions:

* *per template function*, which archive object reproduces it -- the coverage number;
* *per library*, how much of each on-disk archive reappears in the template -- the
  revision verdict (the stamp's release should reproduce strictly more than its
  neighbours, or tie with them and win on the stamp).

Nothing here writes matching C, and no SDK bytes enter the repository: the archives stay
where they were unpacked, and what is committed is the verdict.

    tools/sdk/revisions.py                 # re-measure and compare with the record
    tools/sdk/revisions.py --write         # write the record and the markdown from a run
"""

from __future__ import annotations

import argparse
import collections
import json
import pathlib
import random
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT / "tools"))

from sdk import borrow
# ``sdk.match`` under a name of its own: this module's :func:`match` is the per-library
# verdict the plan asks for, and a module-level ``match`` would shadow the comparison.
from sdk import match as masking  # noqa: E402
from elf import Elf  # noqa: E402

# The template, as the plan places it (``orig/SLUS_211.74``, gitignored), else the mounted
# prototype image -- the same binary, pinned by sha256
# ``ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd``.
TEMPLATE = ROOT / "orig" / "SLUS_211.74"
TEMPLATE_FALLBACK = pathlib.Path("/Volumes/Untitled 1/SLUS_211.74")
MARKDOWN = ROOT / "config" / "ddrex2p" / "library-revisions.md"
JSON = ROOT / "config" / "ddrex2p" / "library-revisions.json"

# The eleven stamps, read from the binary's ``__ps2_libinfo__`` objects (VAs
# 0x2A0100-0x2B8BA8), normalised to one token each.
STAMPS = {
    "libgraph": "PsIIlibgraph3000",
    "libdma": "PsIIlibdma3000",
    "libvu0": "PsIIlibvu03000",
    "libipu": "PsIIlibipu3000",
    "libkernl": "PsIIlibkernl3000",
    "libpad": "PsIIlibpad3020",
    "libcdvd": "PsIIlibcdvd3000",
    "libmc": "PsIIlibmc3020",
    "libscf": "PsIIlibscf3000",
    "libeyetoy": "PsIIlibeyety1300",
    "netcnfif": "PsIInetcnfif3020",
}

# Every archive package this tree has obtained, as the *package trees* rather than the
# library directories inside them: a directory-scoped list is how the first version of this
# scan came to miss `ee/gcc/lib` (four `libgcc.a` plus the toolchain archives), the Demo
# Disc SDK's three libraries, and `ee001003_1`'s `gcc/lib`.  A corpus that claims to be the
# archives on disk has to be the archives on disk.
#
# What is deliberately *not* in it, with the reason:
#   * ``~/sdk-downloads/scert``            -- SCE-RT, the *PSP* runtime (83 archives)
#   * ``~/sdk-downloads/tlib_251``         -- that patch drop ships no archive at all
#   * ``~/sdk-downloads/cw303j``           -- an installer, never unpacked
#   * ``~/sdk-downloads/toolchain20*``     -- a bin/cue pair, never unpacked
#   * the IOP side of the devkit          -- not present in this extraction (0 archives)
# Nothing else on this machine holds an EE runtime archive; the numbers in the record are
# therefore the whole on-disk corpus, not a bounded slice of it.
ARCHIVE_ROOTS = (
    ("~/sdk-downloads/tlib_250/sce/ee", "tlib_250"),
    ("~/sdk-downloads/tlib_252/tlib_252/ee", "tlib_252"),
    ("~/sdk-downloads/tlib_253/tlib_253/ee", "tlib_253"),
    ("~/sdk-downloads/tlib_254/tlib_254/ee", "tlib_254"),
    ("~/sdk-downloads/tlib_255/tlib_255/ee", "tlib_255"),
    ("~/sdk-downloads/rlib20/sce/ee", "rlib20"),
    ("~/sdk-downloads/toolibs242", "toolibs242"),
    ("~/sdk-downloads/ee001003_1/sce/ee", "ee001003_1"),
    ("~/sdk-extract/devkit152/RTLibs_ToolchainSetup/MAINDIR/ee", "devkit152"),
    ("~/sdk-extract/devkit152/ExtraLibsSetup/MAINDIR/Demo Disc SDK", "devkit152-demo"),
)

# The loadable image: one real PT_LOAD at 0x100000, 1,958,272 B.
LOAD_VA = 0x00100000
# The lowest PC this template's own DWARF names (``sysGetDateNotation``): the boundary a
# reader would call "below the game".  Library objects sit on both sides of it -- the SDK's
# members are appended where they are first referenced -- so it splits the *report*, never
# the measurement.
GAME_START = 0x001B3D30

# A whole body this short is not evidence: the kernel's 16-byte ``Copy`` and ``setup``
# recur throughout the image, so below this floor a match says nothing about a revision.
# The value is the one the Oni 2 measurement used (12 words).
MIN_BYTES = 48
# The instruction window that identifies a candidate before its whole body is compared.
SIGNATURE = 6
# Zero padding a slot may hold after the object's body before the slot is a *longer*
# function rather than the object's own slot (four instructions is well past the 16-byte
# function alignment this build uses).
MAX_TAIL = 8
JR_RA = 0x03E00008
ARCHIVE_JUNK = borrow.ARCHIVE_JUNK
# An archive the binary carries no stamp for still counts as evidence when it explains at
# least this much code: below it, the match is a handful of shared stubs.
MIN_UNSTAMPED = 512


# ---------------------------------------------------------------------------
# reading the archives
# ---------------------------------------------------------------------------


def normalise(stamp: str) -> str:
    """``PsIIlibdma  3000`` on disk and ``PsIIlibdma3000`` in the record are one stamp."""
    return stamp.replace(" ", "")


def archive_versions(path: pathlib.Path | str) -> list[str]:
    """The ``PsII<library><version>`` strings an archive's own members carry.

    Each is a 16-byte ``__ps2_libinfo__`` object -- ``PsIIlibgraph3000``, ``PsIIlibvu0
    `` 3000`` -- so the stamp is the 16 bytes from the ``Ps``, never a longer run.
    """
    found = []
    for _, body in borrow.archive_members(path):
        for index in range(len(body) - 15):
            if body[index:index + 4] != b"PsII":
                continue
            stamp = body[index:index + 16].split(b"\0")[0].decode("latin-1")
            stamp = normalise("".join(ch for ch in stamp if ch.isalnum() or ch == " "))
            if stamp not in found:
                found.append(stamp)
    return found


def archive_functions(path: pathlib.Path | str) -> list[dict]:
    """``{name, size, member, bytes}`` for every text symbol of an ``ar`` archive.

    A member's ``.text`` is read from the symbol that owns it, so a function's body is
    exactly ``size`` bytes -- the unit the comparison needs.
    """
    functions, _ = _archive_parts(path)
    return functions


def archive_members_code(path: pathlib.Path | str) -> list[dict]:
    """``{member, text}`` for every code member: the whole object, for a whole-object test."""
    return [{"member": member, "text": text} for member, text in _archive_parts(path)[1]]


def _archive_parts(path: pathlib.Path | str) -> tuple[list[dict], list[tuple[str, bytes]]]:
    """``(functions, [(member, .text)])`` for one archive -- one pass over its members."""
    out: list[dict] = []
    texts: list[tuple[str, bytes]] = []
    with tempfile.TemporaryDirectory() as work:
        scratch = pathlib.Path(work) / "member.o"
        for member, body in borrow.archive_members(path):
            if body[:4] != b"\x7fELF":
                continue
            scratch.write_bytes(body)
            try:
                elf = Elf(scratch)
            except Exception:
                continue
            text_section = next((s for s in elf.sections if s.name == ".text"), None)
            if text_section is not None and text_section.size >= 4:
                size = text_section.size - text_section.size % 4
                texts.append((member,
                              elf.data[text_section.offset:text_section.offset + size]))
            for symbol in elf.symbols:
                if (symbol.type != 2 or not symbol.size
                        or ARCHIVE_JUNK.match(symbol.name)
                        or symbol.shndx >= len(elf.sections)):
                    continue
                section = elf.sections[symbol.shndx]
                if section.type != 1 or not section.flags & 0x4:   # PROGBITS + exec
                    continue
                offset = section.offset + (symbol.value - section.addr)
                blob = elf.data[offset:offset + symbol.size]
                if len(blob) != symbol.size or symbol.size % 4:
                    continue                      # not whole instructions: not code
                out.append({"name": symbol.name, "size": symbol.size,
                            "member": member, "bytes": blob})
    return out, texts


def load_archive(path: pathlib.Path | str, set_name: str) -> dict:
    """One archive, as :func:`match` wants it: identity, revision stamps, functions."""
    path = pathlib.Path(path)
    functions, members = _archive_parts(path)
    return {"set": set_name, "path": str(path), "lib": path.name[:-2],
            "versions": archive_versions(path), "functions": functions,
            "members": [{"member": member, "text": text} for member, text in members]}


def roots(roots_spec=ARCHIVE_ROOTS) -> list[tuple[pathlib.Path, str]]:
    """The package roots that exist on this machine, in the order given."""
    out = []
    for spec, set_name in roots_spec:
        path = pathlib.Path(spec).expanduser()
        if path.is_dir():
            out.append((path, set_name))
    return out


def corpus(roots_spec=ARCHIVE_ROOTS) -> list[dict]:
    """Every EE archive in every package on this machine, sorted by set and path."""
    out = []
    for path, set_name in roots(roots_spec):
        for archive in sorted(path.rglob("*.a")):
            set_of = set_name
            if "/soft-float/" in str(archive):
                set_of = set_name + "/soft"      # the soft-float twin: the same source twice
            try:
                entry = load_archive(archive, set_of)
            except Exception:
                continue                        # a malformed container is not evidence
            if entry["functions"]:
                out.append(entry)
    return out


def versions_on_disk(corpus_entries: list[dict], lib: str) -> list[str]:
    """Every revision of ``lib`` the corpus holds, sorted."""
    return sorted({version for entry in corpus_entries if entry["lib"] == lib
                   for version in entry["versions"]})


# ---------------------------------------------------------------------------
# the comparison
# ---------------------------------------------------------------------------


def classify(object_bytes: bytes, slot_bytes: bytes) -> dict:
    """What one archive object says about one slot of the template.

    ``slot_bytes`` is a whole function slot -- the object's code plus whatever padding
    follows it.  Three answers, and only the first is a match:

    * ``identical`` -- every instruction equal after relocation masking, and the rest of
      the slot is zero padding (so the slot is this object's own function);
    * ``differs`` -- same size, one or more instructions are not the same code;
    * ``size`` -- the two are not the same length.  A size mismatch is never identity,
      however much of the head agrees.
    """
    object_words, slot_words = masking.words(object_bytes), masking.words(slot_bytes)
    result = {"size": len(object_bytes), "slot": len(slot_bytes), "identical": False,
              "exact": False, "differing_words": 0, "masked_words": 0,
              "first_difference": None, "verdict": "size"}
    if len(object_words) > len(slot_words):
        result["differing_words"] = len(object_words) - len(slot_words)
        result["first_difference"] = len(slot_words)
        return result
    compared = masking.compare(object_bytes, slot_bytes[:len(object_bytes)])
    result.update({k: compared[k] for k in
                   ("exact", "differing_words", "masked_words", "first_difference")})
    if not compared["identical"]:
        result["verdict"] = "differs"
    elif any(slot_words[len(object_words):]):
        result["verdict"] = "size"              # the slot holds more code than the object
        result["differing_words"] = len(slot_words) - len(object_words)
        result["first_difference"] = len(object_words)
    else:
        result["verdict"] = "identical"
        result["identical"] = True
    return result


def boundaries(region_bytes: bytes, base: int, extra=()) -> list[int]:
    """Function boundaries in a linked image, where nothing but the bytes is available.

    A function ends with ``jr ra`` and its delay slot; what follows is zero padding up to
    the link's alignment, so the next function starts at the next non-zero word.  The rule
    is validated against the template's own DWARF in :func:`main`: it finds 1,763 of the
    1,816 named functions it names (97.1 %), and what it misses are functions that do not
    end in ``jr ra``.  A rule error can only *split* a slot, which makes a function
    unmatchable -- a floor on the count, never two functions merged into one match.
    ``extra`` are offsets a whole archive object is known to start at (the refinement
    pass).
    """
    words = masking.words(region_bytes)
    out = [base]
    index = 0
    while index + 1 < len(words):
        if words[index] == JR_RA:
            nxt = index + 2
            while nxt < len(words) and words[nxt] == 0:
                nxt += 1
            if nxt < len(words):
                out.append(base + 4 * nxt)
            index = nxt if nxt > index else index + 1
            continue
        index += 1
    end = base + len(region_bytes)
    return sorted({start for start in list(out) + list(extra)
                   if base <= start < end})


def _index(corpus_entries: list[dict]) -> dict:
    """``(signature) -> [(entry, function)]``: the candidate window."""
    index = collections.defaultdict(list)
    for entry in corpus_entries:
        for function in entry["functions"]:
            masked = [masking.mask(word) for word in masking.words(function["bytes"])]
            function["masked"] = masked
            index[tuple(masked[:min(SIGNATURE, len(masked))])].append((entry, function))
    return index


def _placements(masked: list[int], index: dict, min_bytes: int) -> dict:
    """``word index -> [(entry, function)]`` wherever a whole body reappears."""
    out = {}
    for start in range(len(masked)):
        for window in (SIGNATURE, 5, 4, 3):
            if start + window > len(masked):
                continue
            for entry, function in index.get(tuple(masked[start:start + window]), []):
                body = function["masked"]
                if len(body) * 4 < min_bytes or len(body) > len(masked) - start:
                    continue
                if all(body[k] == masked[start + k] for k in range(len(body))):
                    out.setdefault(start, []).append((entry, function))
            break
    return out


def objects_of(entry: dict, masked: list[int], min_bytes: int) -> dict:
    """How much of one archive reappears as *whole objects* (``.text`` members).

    A whole-object match is the strict version of the per-function answer -- every
    instruction of the member, in order, masking aside -- and it is what a link can pin
    without touching the object.  A member the linker splits or aligns differently does
    not show, so this is a floor, not the object count the build will use.
    """
    members = [member for member in entry.get("members", [])
               if len(member["text"]) >= min_bytes]
    if not members:
        return {"objects": 0, "objects_total": 0, "object_bytes": 0}
    index = collections.defaultdict(list)
    for member in members:
        words = masking.words(member["text"])
        while words and words[-1] == 0:
            words.pop()                          # the object's own trailing alignment
        member["masked"] = [masking.mask(word) for word in words]
        if len(member["masked"]) >= 3:
            index[tuple(member["masked"][:3])].append(member)
    found, bytes_found = 0, 0
    for start in range(len(masked) - 3):
        for member in index.get(tuple(masked[start:start + 3]), []):
            body = member["masked"]
            if len(body) > len(masked) - start:
                continue
            if all(body[k] == masked[start + k] for k in range(3, len(body))):
                found += 1
                bytes_found += len(member["text"])
                break
    return {"objects": found, "objects_total": len(members), "object_bytes": bytes_found}


def match(region_bytes: bytes, archives: list[dict], base: int = LOAD_VA,
          stamps: dict | None = None, min_bytes: int = MIN_BYTES,
          control: bool = True, seed: int = 20261016,
          dwarf: list[int] | None = None) -> dict:
    """Per library stamp: which archive reproduces its members byte-for-byte.

    ``archives`` is the corpus :func:`corpus` loads (or a hand-built one, in the tests).
    Returns ``{"region": …, "libraries": {library: …}, "unstamped": […]}``.  Every slot of
    the region is a function candidate; a slot is explained when some archive's *whole*
    body fits it after masking.  The stamp decides between archives that explain equally
    much -- byte identity alone cannot separate two releases that ship the same objects.
    """
    if stamps is None:
        stamps = STAMPS
    region = masking.words(region_bytes)
    masked = [masking.mask(word) for word in region]
    end = base + len(region_bytes)
    index = _index(archives)
    placements = _placements(masked, index, min_bytes)

    starts = boundaries(region_bytes, base,
                        extra=[base + 4 * offset for offset in placements])
    starts = [start for start in starts if start < end] + [end]

    slots: list[dict] = []
    per_archive: dict = collections.defaultdict(lambda: {"functions": set(), "bytes": 0,
                                                         "exact": 0})
    for number in range(len(starts) - 1):
        start, nxt = starts[number], starts[number + 1]
        if nxt - start < min_bytes:
            continue
        slot = {"va": start, "span": nxt - start, "candidates": [], "sizes": 0}
        for entry, function in placements.get((start - base) // 4, []):
            outcome = classify(function["bytes"], region_bytes[start - base:nxt - base])
            if outcome["verdict"] == "size":
                slot["sizes"] += 1
                continue
            slot["candidates"].append((entry, function, outcome))
        if slot["candidates"]:
            best = max(outcome["size"] for _, _, outcome in slot["candidates"])
            for entry, function, outcome in slot["candidates"]:
                if outcome["size"] != best:
                    continue
                record = per_archive[id(entry)]
                record["functions"].add((start, function["name"], function["size"]))
                record["bytes"] += function["size"]
                record["exact"] += 1 if outcome["exact"] else 0
            slot["outcome"] = "identical"
            slot["size"] = best
        slots.append(slot)

    libraries = {}
    for lib, stamp in stamps.items():
        wanted = normalise(stamp)
        candidates = []
        for entry in archives:
            if entry["lib"] != lib:
                continue
            record = per_archive.get(id(entry))
            candidates.append({"_entry": entry,
                               "set": entry["set"], "archive": _display(entry["path"]),
                               "versions": list(entry["versions"]),
                               "stamp": any(normalise(v) == wanted
                                            for v in entry["versions"]),
                               "functions": len(record["functions"]) if record else 0,
                               "bytes": record["bytes"] if record else 0,
                               "exact": record["exact"] if record else 0})
        candidates.sort(key=lambda c: (-c["bytes"], c["set"], c["archive"]))
        matched = [c for c in candidates if c["functions"]]
        stamped = [c for c in matched if c["stamp"]]
        chosen = max(stamped or matched or [None], key=lambda c: c and (c["bytes"],
                                                                       c["archive"]))
        entry_record = {
            "stamp": stamp, "functions": chosen["functions"] if chosen else 0,
            "bytes": chosen["bytes"] if chosen else 0,
            "exact": chosen["exact"] if chosen else 0,
            "stamp_matched": bool(chosen and chosen["stamp"]),
            "chosen": chosen, "candidates": candidates,
            "on_disk": versions_on_disk(archives, lib),
            "matched": sorted(({"va": va, "name": name, "size": size}
                               for va, name, size in
                               (per_archive[id(chosen["_entry"])]["functions"]
                                if chosen else set())),
                              key=lambda m: m["va"]),
        }
        entry_record.update(objects_of(chosen["_entry"], masked, min_bytes) if chosen
                            else {"objects": 0, "objects_total": 0, "object_bytes": 0})
        libraries[lib] = entry_record

    stamped_libraries = set(stamps)
    rows: dict[tuple, dict] = {}
    for entry in archives:
        if entry["lib"] in stamped_libraries:
            continue                            # reported per stamp, above
        record = per_archive.get(id(entry))
        if not record or record["bytes"] < MIN_UNSTAMPED:
            continue
        key = (entry["lib"], tuple(entry["versions"]), len(record["functions"]),
               record["bytes"])
        row = rows.setdefault(key, {"library": entry["lib"],
                                    "library_file": entry["path"].rsplit("/", 1)[-1],
                                    "sets": [], "versions": list(entry["versions"]),
                                    "functions": len(record["functions"]),
                                    "bytes": record["bytes"], "exact": record["exact"]})
        row["sets"].append(entry["set"])
    unstamped = sorted(rows.values(), key=lambda r: (-r["bytes"], r["library"]))

    explained = [slot for slot in slots if slot.get("outcome")]
    # The union over the *chosen* archive of each stamp: how much of the image the eleven
    # stamped libraries account for, counting a slot once even when two libraries share it.
    stamped: dict[int, int] = {}
    for entry in libraries.values():
        for match_ in entry["matched"]:
            stamped[match_["va"]] = max(stamped.get(match_["va"], 0), match_["size"])
    region_record = {
        "base": base, "bytes": len(region_bytes), "min_bytes": min_bytes,
        "functions": len(slots),
        "matched_functions": len(explained),
        "matched_bytes": sum(slot["size"] for slot in explained),
        "exact_bytes": sum(slot["size"] for slot in explained
                           if any(outcome["exact"] for _, _, outcome in slot["candidates"]
                                  if outcome["size"] == slot["size"])),
        "size_mismatches": sum(slot["sizes"] for slot in slots),
        "slot_bytes": sum(slot["span"] for slot in slots),
        "stamped_functions": len(stamped),
        "stamped_bytes": sum(stamped.values()),
        "stamped_window_functions": len([va for va in stamped if va < GAME_START]),
        "stamped_window_bytes": sum(size for va, size in stamped.items()
                                    if va < GAME_START),
        "unexplained_functions": sum(1 for slot in slots if not slot.get("outcome")),
        "unexplained_bytes": sum(slot["span"] for slot in slots if not slot.get("outcome")),
        "runs": _runs([slot for slot in slots if not slot.get("outcome")]),
        "below_game_start": _window(slots, GAME_START),
    }
    if dwarf is not None:
        named = set(dwarf)
        region_record["dwarf_starts"] = len(named)
        region_record["dwarf_found"] = len(named & set(starts))
    if control:
        shuffled = list(region)
        random.Random(seed).shuffle(shuffled)
        shuffled_masked = [masking.mask(word) for word in shuffled]
        shuffled_placements = _placements(shuffled_masked, index, min_bytes)
        shuffled_starts = boundaries(bytes(b"".join(
            word.to_bytes(4, "little") for word in shuffled)), base)
        region_record["control_functions"] = len(shuffled_placements)
        region_record["control_boundaries"] = len(shuffled_starts)
    else:
        region_record["control_functions"] = 0
        region_record["control_boundaries"] = 0
    return {"region": region_record, "libraries": libraries, "unstamped": unstamped,
            "slots": slots}


def _runs(slots: list[dict], keep: int = 8) -> list[list[int]]:
    """The longest contiguous stretches of unexplained slots: ``[start, end, bytes]``."""
    out = []
    for slot in slots:
        lo, hi = slot["va"], slot["va"] + slot["span"]
        if out and lo <= out[-1][1]:
            out[-1][1] = max(out[-1][1], hi)
        else:
            out.append([lo, hi])
    for run in out:
        run.append(run[1] - run[0])
    out.sort(key=lambda run: -run[2])
    return out[:keep]


def _window(slots: list[dict], end_va: int) -> dict:
    """What the slots below ``end_va`` add up to, matched and not.

    ``end_va`` is the lowest PC this binary's own DWARF names (``sysGetDateNotation``), so
    this is the region a reader would call "below the game" -- it holds most of the SDK
    objects, but, as the numbers show, it is not all library code.
    """
    window = [slot for slot in slots if slot["va"] < end_va]
    matched = [slot for slot in window if slot.get("outcome")]
    return {"end": end_va,
            "functions": len(window), "bytes": sum(slot["span"] for slot in window),
            "matched_functions": len(matched),
            "matched_bytes": sum(slot["size"] for slot in matched),
            "unexplained_bytes": sum(slot["span"] for slot in window
                                     if not slot.get("outcome"))}


def _display(path) -> str:
    """A path as a reader types it: repo-relative when it is inside the repo."""
    text = str(path)
    if text.startswith(str(ROOT)):
        return text[len(str(ROOT)) + 1:]
    return text


# ---------------------------------------------------------------------------
# the template itself
# ---------------------------------------------------------------------------


def template_path() -> pathlib.Path | None:
    for candidate in (TEMPLATE, TEMPLATE_FALLBACK):
        if candidate.exists():
            return candidate
    return None


def image(path: pathlib.Path | str) -> tuple[int, bytes]:
    """``(base VA, loadable bytes)`` of the one real segment a PS2 template loads."""
    elf = Elf(str(path))
    for segment in elf.segments:
        if segment.type == 1 and segment.filesz:
            return segment.vaddr, elf.data[segment.offset:segment.offset + segment.filesz]
    raise ValueError(f"{path}: no loadable segment")


# ---------------------------------------------------------------------------
# the record
# ---------------------------------------------------------------------------

# The prose half of the record: what the numbers mean and what they do not settle.  The
# numbers themselves are measured (``library-revisions.json``); these are written once and
# read by :func:`render_markdown`.
NOTES = {
    "head": """\
`SLUS_211.74`, sha256 `ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd`, one
loadable segment at `0x100000`, 1,958,272 B. This is plan Task 2's record: the SDK revisions the
prototype links, confirmed byte-wise per library, names only. **No matching C was written for any
library function, and no SDK bytes enter this repository** -- the archives stay where they were
unpacked and only the verdict is committed.""",

    "method": """\
- **The stamps.** The binary's own `__ps2_libinfo__` objects name eleven libraries, at VAs
  `0x2A0100`-`0x2B8BA8`: the eleven in `tools/sdk/revisions.py:STAMPS`. A stamp names a *release*, not
  a file, and the 2005 media is a later release than some of them -- so every stamp is confirmed
  against bytes, never trusted.
- **The corpus.** Every `ar` archive under every package tree on this machine --
  `revisions.py:ARCHIVE_ROOTS`, {archives} archives and {archive_functions} functions, from tlib
  2.5.0-2.5.5, SCE Tool-Libs 2.4.2, PS2 Runtime Library 2.0, EE 1.00.03 and the July-2005 devkit
  (runtime library 3.0.3) with its GNU trees. A first version of this scan pointed at library
  *directories* and silently missed `ee/gcc/lib` (four `libgcc.a` and the toolchain archives), the
  Demo Disc SDK's three libraries and `ee001003_1`'s `gcc/lib`; the roots are package trees now, so
  "every archive on disk" is a fact rather than an intention. Deliberately out, with reasons: SCE-RT
  (`scert` is the *PSP* runtime), `tlib_251` (ships no archive), `cw303j` and the toolchain 2.0 image
  (never unpacked). Nothing else on this machine holds an EE archive.
- **Function slots.** The image is cut into functions by the bytes alone: a function ends with
  `jr ra` and its delay slot, and the next one starts at the next non-zero word (the link's
  alignment padding is zeros). Every offset where a whole archive object reappears is added as a
  boundary. The rule is validated against this binary's own DWARF every run: it finds
  **{dwarf_found} of the {dwarf_starts} named functions ({dwarf_pct} %)**, and what it misses are
  functions that do not end in `jr ra`. A rule error can only *split* a slot, which makes a function
  unmatchable -- a floor on the count, never two functions merged into one match.
- **The match.** An archive object fits a slot when its **whole body** equals the slot's
  instructions after relocation masking (`sdk.match`: `j`/`jal` targets and I-type immediates are
  link addresses and carry no code) *and* the rest of the slot is padding. One changed instruction
  is a different revision; a body that does not fit the slot is a different function and is never
  reported as identity.
- **The floor.** A body shorter than 48 B is not evidence -- the kernel's 16-byte `Copy` and `setup`
  recur throughout the image -- so the counts use a 48-byte floor.
- **The control.** The same measurement against the same image with its instruction words shuffled
  finds **0** matches, so a 48-byte whole-body hit is not chance.
- **Whole objects.** `whole objects` counts the members of the chosen archive whose entire `.text`
  reappears in the image: the strictest form of the answer, and what a link can pin without
  touching the object.""",

    "after_table": """\
`stamp and bytes agree` means the chosen archive carries the stamp *and* is the best byte-wise
match on disk. `stamp absent` means nothing on disk carries the stamp, so the closest revision is
reported instead and the residue is unexplained. Note that `functions` counts only the objects that
reappear: an archive that reproduces 247 functions may still have members that retail does not
contain at all, and nothing on disk separates "not linked" from "not this revision" without the
split (plan Task 4).""",

    "after_alternatives": """\
Where the bytes are the only evidence, they agree with the stamp. `libkernl` reproduces 247
functions against 129 for the 2.5.x archives, `libcdvd` 39 against 19, `libpad` 38 against 21,
`libscf` 16 / 1,588 B against 15 / 1,476 B, and `libipu` 10 against 4: in each case the revision the
stamp names reproduces strictly more, so the bytes choose it without help.

Where bytes cannot separate two releases that ship the same objects, the stamp does it. `libgraph`,
`libdma` and `libvu0` tie instruction for instruction with their 2.5.x counterparts (19/6,208,
16/1,724 and 18/2,208 on both sides) -- which is exactly why the stamp is recorded next to the bytes
rather than instead of them.""",

    "after_numbers": """\
Read the coverage two ways. Against the whole image, the archives on this machine explain
**{share} %** of it. Against the region a reader would call the library region they explain
**{window_share} %**: the {window_bytes} B below the game's first DWARF function (`0x{window_end:06X}`)
hold {window_matched} slots an archive reproduces ({window_matched_bytes} B), about three times the
whole-image rate, and that is where the SDK's objects sit.

The eleven stamped libraries, counted over the whole image, account for **{stamped} slots /
{stamped_bytes} B**; restricted to the same region below `0x{window_end:06X}` they are
**{stamped_window} slots / {stamped_window_bytes} B**. Both numbers are the *union* over each stamp's
chosen archive, so a slot two libraries share is counted once.

The rest the numbers also name: {unexplained_bytes} B ({unexplained_share} %) has no whole-body
identical object anywhere in the corpus -- game code the DWARF backs and game code it does not, the
newlib/GNU runtime whose revision no stamp pins, library code from the one revision that is not on
disk as an archive, and the data section. The old target's survey measured its own SDK subset at 757
functions / 86,944 B; this template's is the same order of magnitude, larger because the title links
more of the SDK.""",

    "after_runs": """\
These {top} stretches are {bytes} B, {share} % of everything no archive explains. Nothing in them
is reproduced by any archive on disk: the DWARF names no code between `0x100000` and `0x1B3D30` at
all (736 KB of the image), the newlib/GNU runtime matches only in part, and the topmost stretch,
`0x2A16E8`-`0x2DE180`, is the data and read-only-data tail where the library banners and the game's
strings sit rather than code.""",

    "unstamped_intro": """\
The stamp list is a **lower bound**. `__ps2_libinfo__` is one member of each archive, and the linker
only pulls that member in when something references it -- so a library can be linked with no stamp
in the image at all. These archives reproduce code the binary carries no stamp for. Packages are
listed together where the same source appears more than once (hard- and soft-float twins of the GNU
runtime usually produce identical counts; where they do not (the two `libgcc.a` builds) both rows are
shown).""",

    "after_unstamped": """\
`libmpeg` is the largest: 84 functions / 28,712 B reproduced by the 3.0.3 archive, 21 of them
byte-exact -- and the binary carries no `PsIIlibmpeg` string anywhere, which is why the stamp list
cannot be read as the linked-library list. Whatever the reason no
`__ps2_libinfo__` member was pulled in, the code is there and it is tlib 3.0.3's. `libdev`,
`libtimer`, `libsdr`, `libpad2`, `libmrpc` and the GNU runtime (`libc`, `libg`, `libm`, `libgcc`,
`libstdc++`, `libiberty`, `libidt`, from the devkit's `ee/gcc` trees) are the rest of the linked
runtime; they carry no stamp of their own in this build either. Nothing here is reversed to C -- these are names for a
ledger, and the pinned objects are the ones that match.""",

    "unexplained": """\
**`libmc` needs `PsIIlibmc3020`; no *archive* on disk is 3020 -- but a 3.0.2 *link* is.** The 2005
media ships `PsIIlibmc3030` (built 2005-05-19) and every other package 2000/2400/2500/2530/2540, so
the release the prototype links cannot be linked from anything here: 3030 reproduces 27 functions /
6,272 B of the template and **none** of its two objects whole.

A correction to the first version of this record, which said "nothing on disk is 3020": the SCEE
YNCF Tool 1.1 of the *same* July-2005 devkit carries the stamp. `{lead_stamp}` sits at
`0x{lead_offset:X}` in `{lead_path}` (and in `{lead_iso}`), so libmc 3.0.2 bytes **are** on this
machine. The limitation is what it can be used for: it is a **linked binary**, not an archive -- it
can validate a candidate's bytes for libmc 3.0.2, but there is no relocatable member to pin or to
link, which is the whole capability an archive gives.

Measured, so the lead is not overread: searching the template's `libmc` neighbourhood
(`0x{lead_lo:06X}`-`0x{lead_hi:06X}`, the {lead_slots} slots within ±8 KiB of the functions 3030 does
reproduce) against that image finds {lead_identical} slots whole-body identical
({lead_identical_bytes} B) -- {lead_explained} of the {lead_explained_total} an archive already
explains, and only **{lead_unexplained} of the {lead_unexplained_total}** that no archive explains.
So the 3.0.2 link confirms the shared code and does **not** close the `libmc` gap: the template's
unexplained `libmc` code is not in it either.

**`libeyetoy` needs `PsIIlibeyety1300`; the only archive on disk is 1.4.0.** That archive explains a
single 48-byte function in the whole image (byte-exact, so the code is real), and nothing else: the
EyeToy revision the prototype links is not on disk, and the 1.4.0 objects are not it. No linked
binary carrying `PsIIlibeyety1300` was found either.

**The rest.** {unexplained_slots} slots / {unexplained_bytes} B of the image
({unexplained_share} %) have no whole-body identical archive object anywhere in the corpus. That is
not a statement that the code is unknown: it is game code (DWARF-backed and DWARF-less), GNU runtime
code whose revision is not pinned by any stamp, library code from the missing revision, and the data
section. Plan Task 9 names what matches and leaves the rest as split assembly -- the residue is
listed here as numbers rather than summarised away.""",
}


def range_of(matched: list[dict]) -> list[int] | None:
    """The lowest and highest address one library's reproduced functions span."""
    if not matched:
        return None
    return [matched[0]["va"], max(m["va"] + m["size"] for m in matched)]


def slim(fresh: dict) -> dict:
    """The record's shape: the numbers a reader needs, without the per-function dump.

    ``match`` returns every matched function by name and address; the committed record
    keeps the counts, the alternatives and the address ranges, and the tool re-derives the
    rest -- the per-function list is a ledger task's input, not a document.
    """
    libraries = []
    for lib, entry in fresh["libraries"].items():
        chosen = entry["chosen"]
        libraries.append({
            "library": lib, "stamp": entry["stamp"],
            "set": chosen["set"] if chosen else None,
            "library_file": (chosen["archive"].rsplit("/", 1)[-1] if chosen else None),
            "versions": chosen["versions"] if chosen else [],
            "functions": entry["functions"], "bytes": entry["bytes"],
            "exact": entry["exact"], "stamp_matched": entry["stamp_matched"],
            "on_disk": entry["on_disk"],
            "objects": entry["objects"], "objects_total": entry["objects_total"],
            "object_bytes": entry["object_bytes"],
            "range": range_of(entry["matched"]),
            "alternatives": [{"set": c["set"], "versions": c["versions"],
                              "functions": c["functions"], "bytes": c["bytes"],
                              "stamp": c["stamp"]}
                             for c in entry["candidates"] if c["functions"]][:4],
        })
    libraries.sort(key=lambda e: list(STAMPS).index(e["library"]))
    out = {"region": fresh["region"], "libraries": libraries,
           "unstamped": fresh["unstamped"]}
    if fresh.get("libmc_lead"):
        out["libmc_lead"] = fresh["libmc_lead"]
    return out


# `libmc 3020` is the one revision the template needs that no *archive* on disk carries --
# and it does exist on disk, as a **linked binary**: the SCEE YNCF Tool 1.1 that ships with
# the same July-2005 devkit.  That distinction decides what it can be used for: it can
# validate bytes (compare a function against its image) but it cannot be pinned as an
# object, because there is no relocatable member to link.
LIBM_C_LEAD = {
    "path": ("~/sdk-extract/devkit152/SoftwareToolsSetup/MAINDIR/SCEE_Tools/YNCFTool/"
             "Cdburn/Slus_123.45"),
    "also_in": ("~/sdk-extract/devkit152/SoftwareToolsSetup/MAINDIR/SCEE_Tools/YNCFTool/"
                "Iso/SCEE_YNCF_Tool_1.1.iso"),
    "stamp": "PsIIlibmc3020",
}


def _tilde(path) -> str:
    """A path as a reader types it: ``~`` for the home directory, so the record is portable."""
    text = str(path)
    home = str(pathlib.Path.home())
    return "~" + text[len(home):] if text.startswith(home) else text


def lead_offset(path: pathlib.Path | str, stamp: str = "PsIIlibmc3020") -> int | None:
    """Where a binary carries a library stamp, or ``None``: the lead's own check."""
    blob = pathlib.Path(path).read_bytes()
    index = blob.find(b"PsII")
    while index != -1:
        head = blob[index:index + 16].split(b"\0")[0].decode("latin-1")
        if normalise("".join(ch for ch in head if ch.isalnum() or ch == " ")) == stamp:
            return index
        index = blob.find(b"PsII", index + 4)
    return None


def libmc_lead(fresh: dict, region_bytes: bytes, base: int,
               lead: dict = LIBM_C_LEAD, span: int = 0x2000) -> dict | None:
    """Does the `libmc` 3.0.2 *link* on disk explain the `libmc` code archives cannot?

    Bounded on purpose: the search window is ``span`` bytes around the functions `libmc`
    3030 does reproduce, where the linker placed the neighbouring members, and the answer is
    reported whether or not it flatters the lead.  ``None`` when the binary is not on this
    machine -- the record then says so rather than claiming a check that did not happen.
    """
    path = pathlib.Path(lead["path"]).expanduser()
    if not path.exists():
        return None
    offset = lead_offset(path, lead["stamp"])
    matched = fresh["libraries"].get("libmc", {}).get("matched") or []
    if not matched or offset is None:
        return None
    lo = min(m["va"] for m in matched) - span
    hi = max(m["va"] + m["size"] for m in matched) + span
    window = [slot for slot in fresh["slots"] if lo <= slot["va"] <= hi]
    _, blob = image(path)
    tool = masking.words(blob)
    masked_tool = [masking.mask(word) for word in tool]
    index = collections.defaultdict(list)
    for slot in window:
        body = region_bytes[slot["va"] - base:slot["va"] - base + slot["span"]]
        body = masking.words(body[:len(body) - len(body) % 4])
        while body and body[-1] == 0:
            body.pop()
        if len(body) * 4 < MIN_BYTES:
            continue
        index[tuple(masking.mask(word) for word in body[:3])].append(
            (slot, [masking.mask(word) for word in body]))
    found = {}
    for start in range(len(masked_tool) - 3):
        for slot, body in index.get(tuple(masked_tool[start:start + 3]), []):
            if len(body) > len(masked_tool) - start:
                continue
            if all(body[k] == masked_tool[start + k] for k in range(3, len(body))):
                found[slot["va"]] = len(body) * 4
    explained = [slot for slot in window if slot.get("outcome")]
    unexplained = [slot for slot in window if not slot.get("outcome")]
    return {
        "path": _tilde(path), "in_iso": lead["also_in"],
        "stamp": lead["stamp"], "stamp_offset": offset,
        "window": [lo, hi], "slots": len(window),
        "explained": len(explained), "unexplained": len(unexplained),
        "identical": len(found), "identical_bytes": sum(found.values()),
        "explained_identical": sum(1 for slot in explained if slot["va"] in found),
        "unexplained_identical": sum(1 for slot in unexplained if slot["va"] in found),
        "limitation": ("a linked binary, not an archive: it can validate bytes for libmc "
                       "3.0.2, but it has no relocatable member to pin or link"),
    }


def dwarf_starts(path: pathlib.Path | str) -> list[int]:
    """The function starts this binary's own DWARF names, in the main image."""
    from dwarf1 import AT_low_pc, Dwarf     # only the run needs it: it reads .debug
    dwarf = Dwarf(str(path))
    return sorted({function.attrs[AT_low_pc] for function in dwarf.funcs
                   if dwarf.overlay(function) == "main"})


def record() -> dict:
    """The committed measurement: ``config/ddrex2p/library-revisions.json``.

    A measurement needs the template and the SDK media; the *record* does not, so the
    verdicts are a committed artifact that this module reads rather than a table embedded
    in code.  :func:`main` writes it, and re-running it checks the record against a fresh
    measurement.
    """
    if not JSON.exists():
        return {"region": {}, "libraries": [], "unstamped": []}
    return json.loads(JSON.read_text())


def verdicts() -> list[dict]:
    """The recorded, human-readable verdict per library stamp."""
    return record()["libraries"]


def region_drift(old: dict, new: dict) -> list[str]:
    """The region keys whose value moved since the record was written."""
    return sorted(key for key in new if key in old and old[key] != new[key])


def _table(headers: list[str], rows: list[list[str]]) -> list[str]:
    out = ["| " + " | ".join(headers) + " |",
           "|" + "|".join("---" for _ in headers) + "|"]
    out += ["| " + " | ".join(row) + " |" for row in rows]
    return out


def verdict_of(entry: dict) -> str:
    """One phrase for the reader: how well the bytes and the stamp agree."""
    if not entry["functions"]:
        return "**unexplained** — nothing on disk reproduces it"
    if entry["stamp_matched"]:
        return "stamp and bytes agree"
    return f"**stamp absent** — the closest revision reproduces {entry['functions']}"


def render_markdown(entries=None, region=None, unstamped=None, notes=None) -> str:
    """``config/ddrex2p/library-revisions.md``: the record, as the reader wants it."""
    data = record()
    entries = data["libraries"] if entries is None else entries
    region = data.get("region", {}) if region is None else region
    unstamped = data.get("unstamped", []) if unstamped is None else unstamped
    notes = NOTES if notes is None else notes

    out = ["# Library revisions: the DDR Extreme 2 (US) preview template", ""]
    out += [notes["head"], ""]

    out += ["## Method", "", notes["method"].format(
        archives=f"{region.get('archives', 0):,}",
        archive_functions=f"{region.get('archive_functions', 0):,}",
        dwarf_found=f"{region.get('dwarf_found', 0):,}",
        dwarf_starts=f"{region.get('dwarf_starts', 0):,}",
        dwarf_pct=f"{100 * region.get('dwarf_found', 0) / max(region.get('dwarf_starts', 1), 1):.1f}",
    ), ""]

    out += ["## Per library: the eleven stamps the binary carries", ""]
    rows = []
    for entry in entries:
        archive = "—" if not entry["library_file"] else (
            f"`{entry['set']}` `{entry['library_file']}`")
        objects = (f"{entry['objects']}/{entry['objects_total']}"
                   if entry["objects_total"] else "—")
        rows.append([entry["library"], f"`{entry['stamp']}`", archive,
                     str(entry["functions"]), f"{entry['bytes']:,}",
                     f"{entry['exact']:,}", objects, verdict_of(entry)])
    out += _table(["library", "stamp", "chosen archive", "functions", "bytes",
                   "byte-exact", "whole objects", "verdict"], rows)
    out += ["", notes["after_table"], ""]

    out += ["## What each choice was measured against", ""]
    rows = []
    for entry in entries:
        alternatives = [f"`{c['set']}` {c['functions']}f/{c['bytes']:,}B"
                        + (" (stamp)" if c["stamp"] else "")
                        for c in entry["alternatives"] if c["set"] != entry["set"]]
        rows.append([entry["library"],
                     ", ".join(f"`{v}`" for v in entry["on_disk"]) or "—",
                     "; ".join(alternatives) or "—"])
    out += _table(["library", "revisions on disk", "the next best archives"], rows)
    out += ["", notes["after_alternatives"], ""]

    out += ["## Explained, as numbers", ""]
    rows = [
        ["function slots the bytes alone find (>= "
         f"{region.get('min_bytes', MIN_BYTES)} B)", f"{region.get('functions', 0):,}"],
        ["bytes those slots span", f"{region.get('slot_bytes', 0):,}"],
        ["slots a whole-body identical archive object explains",
         f"{region.get('matched_functions', 0):,}"],
        ["bytes those objects explain", f"{region.get('matched_bytes', 0):,}"],
        ["…as a share of the image",
         f"{100 * region.get('matched_bytes', 0) / region.get('bytes', 1):.2f} %"],
        ["…of which byte-exact, immediates and all",
         f"{region.get('exact_bytes', 0):,} B"],
        ["…in the eleven stamped libraries (union)",
         f"{region.get('stamped_functions', 0):,} slots / "
         f"{region.get('stamped_bytes', 0):,} B"],
        ["head matches rejected: the object does not fit the slot",
         f"{region.get('size_mismatches', 0):,}"],
        ["slots nothing on disk explains",
         f"{region.get('unexplained_functions', 0):,} / "
         f"{region.get('unexplained_bytes', 0):,} B"],
        ["control: whole-body matches with the image's instructions shuffled",
         f"{region.get('control_functions', 0):,}"],
    ]
    window = region.get("below_game_start") or {}
    if window:
        rows += [
            [f"…below the game's first DWARF function "
             f"(`0x{window['end']:06X}`)", f"{window['bytes']:,} B in "
             f"{window['functions']:,} slots"],
            ["…of that, what an archive explains",
             f"{window['matched_functions']:,} slots / {window['matched_bytes']:,} B "
             f"({100 * window['matched_bytes'] / max(window['bytes'], 1):.2f} %)"],
            ["…and what nothing explains", f"{window['unexplained_bytes']:,} B"],
        ]
    out += _table(["quantity", "value"], rows)
    window = region.get("below_game_start") or {}
    lead = data.get("libmc_lead") or {}
    out += ["", notes["after_numbers"].format(
        share=f"{100 * region.get('matched_bytes', 0) / region.get('bytes', 1):.2f}",
        window_share=f"{100 * window.get('matched_bytes', 0) / max(window.get('bytes', 1), 1):.1f}",
        window_bytes=f"{window.get('bytes', 0):,}", window_end=window.get("end", 0),
        window_matched=f"{window.get('matched_functions', 0):,}",
        window_matched_bytes=f"{window.get('matched_bytes', 0):,}",
        stamped=f"{region.get('stamped_functions', 0):,}",
        stamped_bytes=f"{region.get('stamped_bytes', 0):,}",
        stamped_window=f"{region.get('stamped_window_functions', 0):,}",
        stamped_window_bytes=f"{region.get('stamped_window_bytes', 0):,}",
        unexplained_bytes=f"{region.get('unexplained_bytes', 0):,}",
        unexplained_share=f"{100 * region.get('unexplained_bytes', 0) / region.get('bytes', 1):.1f}",
    ), ""]

    out += ["## The longest unexplained stretches", ""]
    rows = [[f"`0x{lo:06X}`–`0x{hi:06X}`", f"{size:,}"] for lo, hi, size
            in region.get("runs", [])]
    out += _table(["addresses", "bytes"], rows)
    explained = sum(run[2] for run in region.get("runs", []))
    out += ["", notes["after_runs"].format(
        top=len(region.get("runs", [])), bytes=f"{explained:,}",
        share=f"{100 * explained / max(region.get('unexplained_bytes', 1), 1):.0f}"), ""]

    out += ["## Code the bytes name that carries no stamp in this binary", ""]
    out += [notes["unstamped_intro"], ""]
    rows = [[f"`{u['library']}`", f"`{u['library_file']}`",
             ", ".join(f"`{s}`" for s in u["sets"]),
             ", ".join(f"`{v}`" for v in u["versions"]) or "—",
             str(u["functions"]), f"{u['bytes']:,}", f"{u['exact']:,}"]
            for u in unstamped]
    out += _table(["library", "archive", "packages", "revision", "functions", "bytes",
                   "byte-exact"], rows)
    out += ["", notes["after_unstamped"], ""]

    out += ["## Unexplained", "", notes["unexplained"].format(
        lead_stamp=lead.get("stamp", "PsIIlibmc3020"),
        lead_offset=lead.get("stamp_offset", 0),
        lead_path=lead.get("path", "not on this machine"),
        lead_iso=lead.get("in_iso", ""),
        lead_lo=(lead.get("window") or [0, 0])[0],
        lead_hi=(lead.get("window") or [0, 0])[1],
        lead_slots=lead.get("slots", 0),
        lead_identical=lead.get("identical", 0),
        lead_identical_bytes=f"{lead.get('identical_bytes', 0):,}",
        lead_explained=lead.get("explained_identical", 0),
        lead_explained_total=lead.get("explained", 0),
        lead_unexplained=lead.get("unexplained_identical", 0),
        lead_unexplained_total=lead.get("unexplained", 0),
        unexplained_slots=f"{region.get('unexplained_functions', 0):,}",
        unexplained_bytes=f"{region.get('unexplained_bytes', 0):,}",
        unexplained_share=f"{100 * region.get('unexplained_bytes', 0) / region.get('bytes', 1):.1f}",
    ), ""]
    return "\n".join(out)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--template", type=pathlib.Path, default=None)
    parser.add_argument("--write", action="store_true",
                        help="write the record and the markdown from this run")
    parser.add_argument("--min-bytes", type=int, default=MIN_BYTES)
    args = parser.parse_args(argv)

    path = args.template or template_path()
    if path is None:
        print("revisions: nothing was compared (no template at "
              f"{TEMPLATE} or {TEMPLATE_FALLBACK})")
        return 0
    archives = corpus()
    if not archives:
        print("revisions: nothing was compared (no SDK archives on this machine)")
        return 0
    base, blob = image(path)
    print(f"revisions: {path} (image 0x{base:X}, {len(blob)} B), {len(archives)} archives, "
          f"{sum(len(a['functions']) for a in archives)} indexed functions")
    named = dwarf_starts(path)
    measured = match(blob, archives, base=base, min_bytes=args.min_bytes, dwarf=named)
    measured["libmc_lead"] = libmc_lead(measured, blob, base)
    fresh = slim(measured)
    region = fresh["region"]
    region["archives"] = len(archives)
    region["archive_functions"] = sum(len(entry["functions"]) for entry in archives)
    held, total = region["dwarf_found"], region["dwarf_starts"]
    print(f"  boundary rule: {held}/{total} DWARF function starts "
          f"({100 * held / max(total, 1):.1f} %)")
    print(f"  slots {region['functions']}, explained {region['matched_functions']} "
          f"({region['matched_bytes']} B, "
          f"{100 * region['matched_bytes'] / region['bytes']:.2f} % of the image), "
          f"stamped {region['stamped_functions']} / {region['stamped_bytes']} B "
          f"(window {region['stamped_window_functions']} / {region['stamped_window_bytes']} B), "
          f"control {region['control_functions']}")
    lead = fresh.get("libmc_lead")
    if lead:
        print(f"  libmc 3.0.2 lead: {lead['stamp']} at 0x{lead['stamp_offset']:X} in "
              f"{lead['path'].rsplit('/', 1)[-1]}: {lead['unexplained_identical']} of "
              f"{lead['unexplained']} unexplained slots reproduced there")
    recorded = {entry["library"]: entry for entry in verdicts()}
    drift = 0
    for entry in fresh["libraries"]:
        old = recorded.get(entry["library"])
        same = old is not None and (old["functions"], old["bytes"]) == \
            (entry["functions"], entry["bytes"])
        chosen = entry["set"] or "-"
        print(f"  {entry['library']:10s} {entry['stamp']:22s} {chosen:14s} "
              f"functions={entry['functions']:4d} bytes={entry['bytes']:7d}"
              f"{'' if same else '   <-- differs from the record'}")
        drift += 0 if same else 1
    for key in region_drift(record().get("region", {}), region):
        print(f"  region {key}: record {record()['region'][key]} now {region[key]}")
        drift += 1
    rendered = render_markdown(fresh["libraries"], fresh["region"], fresh["unstamped"])
    if MARKDOWN.exists() and MARKDOWN.read_text() != rendered:
        print("  the committed markdown is not what this run renders")
        drift += 1
    if args.write:
        JSON.write_text(json.dumps(fresh, indent=1, sort_keys=True) + "\n")
        MARKDOWN.write_text(rendered)
        print(f"revisions: wrote {JSON.name} and {MARKDOWN.name} from this run"
              + (f" ({drift} differences from the previous record)" if drift else ""))
        return 0
    if drift:
        print(f"revisions: {drift} differences from the committed record")
        return 1
    print("revisions: the committed record is what this run derives")
    return 0


if __name__ == "__main__":
    sys.exit(main())

