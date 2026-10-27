"""Shared plumbing for the target-aware suites: probe targets, and the no-real-build rule.

Two rules this module exists to keep:

* **A test never invokes a real build.**  ``ninja``, ``splat`` and ``configure.py`` are the
  machinery one agent owns at a time (`AGENTS.md`: only one agent builds at a time), so a test
  that ran them would race every other test and every other agent.  Tests drive the *mechanisms*
  -- the generators as functions, the gates as functions, the CLI in process against a target
  whose binary and config live under ``tmp_path`` -- and the machines themselves are exercised by
  the agent that owns the tree.
* **A state is pinned by a probe, not by the registered target.**  "Unmeasured geometry", "no
  binary yet" and "no config yet" are states of a *target*, not facts about ``ddrex2p``; a test
  that asserted them of the registered target would go red the moment its config lands.  The
  probes below build such a target out of the descriptor's public fields, with everything inside
  ``tmp_path``, so nothing they do can touch the real tree.
"""

import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from config import targets  # noqa: E402


def registered():
    """The target this tree is built for -- the one whose artifacts tests may *read*, never write."""
    return targets.get()


def probe(tmp_path, name="probe", **overrides):
    """A target whose binary and image are absent and whose geometry is unmeasured.

    Its ``config_dir`` is ``config/<name>`` because that is what a target's config directory *is*
    (the descriptor refuses anything else, and a test that worked around that check would stop
    testing the descriptor).  Nothing writes there: every verb these probes drive stops before it
    could, which is the property the tests assert -- `config/<name>` must not appear on disk.
    """
    real = registered()
    fields = dict(name=name, config_dir=ROOT / "config" / name,
                  elf=tmp_path / "absent-SLUS_999.99",
                  elf_sha256=real.elf_sha256, image=tmp_path / "absent.iso",
                  image_sha256=real.image_sha256, geometry=None)
    fields.update(overrides)
    return targets.Target(**fields)


def unmeasured(target):
    """``target`` with no geometry: the state a target is in before anybody measures its ELF."""
    import dataclasses
    return dataclasses.replace(target, geometry=None)


def geometry():
    """A small, self-consistent measurement: what a target's ELF has to add up to."""
    return targets.Geometry(
        elf_size=0x2000, loadable_rom=0x80, loadable_end=0x1000, loadable_vram=0x00100000,
        bss_end=0x00110000,
        trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400),
                  ("line", 0x1410, 0x100), ("section_headers", 0x1510, 0x2000 - 0x1510)),
        debug_size=0x400, line_size=0x100, image_elf_offset=0x92000)


def without_binary(tmp_path, monkeypatch, module, name="probe"):
    """Patch ``module``'s target lookup to a probe whose binary is absent, and return the probe.

    ``module`` is a module that resolves its target through ``config.targets`` (``ddr``, ``g1``,
    ``g2``, ``configure``): replacing the lookup keeps every path the verb touches inside
    ``tmp_path``, so a verb that *would* have proceeded cannot touch the real tree.
    """
    target = probe(tmp_path, name)
    monkeypatch.setattr(module.targets, "get", lambda name=None: target)
    return target


#: The bytes a synthetic ELF's program headers start at: a 52-byte ELF header, then 32-byte
#: program headers.  Small enough to keep a fixture readable and exact enough for
#: ``tools/oracle/elf.py``, which is the only reader the tests hand these files to.
EHDR = 52
PHDR = 32


def write_elf(path, segments=(), sections=()):
    """Write a minimal 32-bit little-endian MIPS ELF the tools' own reader accepts.

    ``segments`` is ``[(vaddr, memsz, data)]`` in one file-backed ``PT_LOAD`` each (``filesz``
    is ``len(data)``, so ``memsz - filesz`` is the zero-fill tail) and ``sections`` is
    ``[(name, data)]`` in ``SHT_PROGBITS`` sections named in a ``.shstrtab``.  Both are what
    the reader under test actually looks at: ``file_offset``/``read`` for the program headers,
    and ``.sections``/``.data`` for the chunk reads.  Nothing else (symbols, relocations,
    ``.reginfo``) is needed, and inventing them would only make the fixture look like a build.
    """
    import struct

    path = pathlib.Path(path)
    body = bytearray()
    phdrs = bytearray()
    for vaddr, memsz, data in segments:
        phdrs += struct.pack("<8I", 1, EHDR + len(segments) * PHDR + len(body), vaddr, vaddr,
                             len(data), memsz, 5, 4)
        body += data
    strings = bytearray(b"\x00")
    offsets = {}
    for name, _data in sections:
        offsets[name] = len(strings)
        strings += name.encode() + b"\x00"
    offsets[".shstrtab"] = len(strings)
    strings += b".shstrtab\x00"
    shdrs = bytearray(b"\x00" * 40)
    for name, data in sections:
        shdrs += struct.pack("<10I", offsets[name], 1, 2, 0,
                             EHDR + len(segments) * PHDR + len(body), len(data), 0, 0, 4, 0)
        body += data
    strings_offset = EHDR + len(segments) * PHDR + len(body)
    body += strings
    shoff = EHDR + len(segments) * PHDR + len(body)
    shdrs += struct.pack("<10I", offsets[".shstrtab"], 3, 0, 0, strings_offset, len(strings),
                         0, 0, 1, 0)
    header = bytearray(EHDR)
    header[0:4] = b"\x7fELF"
    header[4:7] = bytes((1, 1, 1))          # 32-bit, little-endian, current version
    struct.pack_into("<HHIIIIIHHHHHH", header, 16, 2, 8, 1, 0, EHDR, shoff, 0, EHDR,
                     PHDR, len(segments), 40, len(sections) + 2, len(sections) + 1)
    path.write_bytes(bytes(header) + bytes(phdrs) + bytes(body) + bytes(shdrs))
