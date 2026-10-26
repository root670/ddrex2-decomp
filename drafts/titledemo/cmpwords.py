"""cmpwords.py <C> <fn> [...] : raw-word comparison, relocations masked.

Retail's split prints each word's little-endian bytes in hex (3rd column).  Ours comes from
objdump's raw word column.  A word with a relocation in our object is compared with the
relocated field masked, so `lui`/`addiu` symbol pairs and `jal` targets never count."""
import pathlib, re, subprocess, sys
ROOT = pathlib.Path("<checkout>")
sys.path.insert(0, str(ROOT)); sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch, probe
PAIR = "3.0b38-030307"
import os
FLAGS = ["-c", "-lang", "c"] + os.environ.get("OPTS", "-O3 -opt full").split() + ["-g"]
OUT = pathlib.Path("/tmp/cmpwords"); OUT.mkdir(exist_ok=True)

def retail(fn):
    p = next(ROOT.glob(f"asm/nonmatchings/*/{fn}.s"))
    words = []
    for l in p.read_text().splitlines():
        m = re.match(r"\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/", l)
        if m:
            words.append(int.from_bytes(bytes.fromhex(m.group(2)), "little"))
    return words

def ours(c, fn):
    src = pathlib.Path(c).resolve()
    obj = OUT / (src.stem + ".o")
    probe.compile(src, obj, fetch.compiler(PAIR), fetch.wibo(), FLAGS + ["-i", str(ROOT / "include")])
    d = subprocess.run(["mips-linux-gnu-objdump", "-d", "-r", "-EL", "-m", "mips:5900", str(obj)],
                       capture_output=True, text=True, check=True).stdout
    words, rel, grab, pend = [], set(), False, False
    for l in d.splitlines():
        if re.match(rf"^[0-9a-f]+ <{fn}>:", l):
            grab = True; continue
        if grab and re.match(r"^[0-9a-f]+ <", l):
            break
        if not grab:
            continue
        m = re.match(r"\s+([0-9a-f]+):\t([0-9a-f]{8})\s", l)
        if m:
            if pend:
                rel.add(len(words) - 1); pend = False
            words.append(int(m.group(2), 16))
            continue
        if re.match(r"^\s+[0-9a-f]+:\s+(?:R_MIPS_\w+|UNKNOWN)", l) and words:
            pend = True
    if pend:
        rel.add(len(words) - 1)
    return words, rel

def masked_ok(w, r):
    """A relocated word: only the fields the relocation does not fill are compared."""
    op = w >> 26
    if op in (2, 3):
        return (w >> 26) == (r >> 26)
    return (w >> 16) == (r >> 16)


def show(c, fn):
    A, rel = ours(c, fn)
    B = retail(fn)
    while len(A) > len(B) and A[-1] == 0: A.pop()
    print(f"== {fn}: ours {len(A)} retail {len(B)}")
    bad = 0
    for i in range(max(len(A), len(B))):
        a = A[i] if i < len(A) else None
        b = B[i] if i < len(B) else None
        if a is None or b is None or not (a == b or (i in rel and masked_ok(a, b))):
            bad += 1
            print(f"{i*4:>4}  0x{a:08X}  |  0x{b:08X}" if a is not None and b is not None
                  else f"{i*4:>4}  {a if a is not None else '--':>10}  |  0x{b:08X}" if b is not None
                  else f"{i*4:>4}  0x{a:08X}  |  --")
    print(f"differing words: {bad}/{max(len(A), len(B))}")

if __name__ == "__main__":
    for fn in sys.argv[2:]:
        show(sys.argv[1], fn)
