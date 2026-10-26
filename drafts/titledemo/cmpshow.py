"""cmpshow.py <C file> <function> [...] : compile with the retail pair, print ours vs retail's
split asm side by side, marking differing words.  Registers normalised to $N; objdump
relocations rendered as %SYM% so the texts line up with the split's %hi/%lo form."""
import pathlib, re, subprocess, sys
ROOT = pathlib.Path("<checkout>")
sys.path.insert(0, str(ROOT)); sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch, probe
PAIR = "3.0b38-030307"
FLAGS = ["-c", "-lang", "c", "-O3", "-opt", "full", "-g"]
OUT = pathlib.Path("/tmp/regrules"); OUT.mkdir(exist_ok=True)
NAMES = "zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra".split()

def hexnorm(m):
    t = m.group(0)
    neg = t.startswith("-")
    if neg: t = t[1:]
    v = int(t, 16) if t.lower().startswith("0x") else int(t)
    return ("-" if neg else "") + hex(v)

def imm(s):
    return re.sub(r"(?<![\w$])-?(?:0x[0-9a-fA-F]+|\d+)(?![\w$])", hexnorm, s)

JUMPS = ("jal", "j", "b", "beq", "bne", "beqz", "bnez", "bc1t", "bc1f", "bgez", "bltz", "blez", "bgtz")

def nr(s):
    for i, n in enumerate(NAMES):
        s = re.sub(rf"(?<![$\w]){n}(?![$\w])", f"${i}", s)
    return re.sub(r"\s*\(\$1\)", "($1)", re.sub(r"\s+", " ", s)).strip()

def spl(s):
    s = re.sub(r"%hi\((\w+)\)", r"%\1%", s)
    s = re.sub(r"%lo\((\w+)\)", r"%\1%", s)
    return nr(s)

def retail(fn):
    p = next(ROOT.glob(f"asm/nonmatchings/*/{fn}.s"))
    out = []
    first = [None]
    for l in p.read_text().splitlines():
        m = re.match(r"\s*/\* \w+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(.*)", l)
        if m:
            if first[0] is None: first[0] = int(m.group(1), 16)
            out.append((fold(norm(spl(m.group(3).split("#")[0].strip()))), first[0]))
    start = first[0]
    res = []
    for t, st in out:
        t = re.sub(r"\.L([0-9A-F]{8})", lambda mm: "%%T%x%%" % (int(mm.group(1), 16) - st), t)
        res.append(t)
    return res

def ours(c, fn):
    src = pathlib.Path(c).resolve()
    obj = OUT / (src.stem + ".o")
    probe.compile(src, obj, fetch.compiler(PAIR), fetch.wibo(), FLAGS + ["-i", str(ROOT / "include")])
    t = subprocess.run(["mips-linux-gnu-objdump", "-d", "-r", "-EL", "-m", "mips:5900", "--no-show-raw-insn", str(obj)],
                       capture_output=True, text=True, check=True).stdout
    body, grab, pend = [], False, []
    for l in t.splitlines():
        if re.match(rf"^[0-9a-f]+ <{fn}>:", l):
            grab = True; continue
        if grab and re.match(r"^[0-9a-f]+ <", l):
            break
        if not grab:
            continue
        m = re.match(r"\s+([0-9a-f]+):\t(.*)", l)
        if m:
            if pend:
                body[-1] = sub_rel(body[-1], pend); pend = []
            body.append(re.sub(r"\s+", " ", m.group(2).replace("\t", " ")).strip())
            continue
        r = re.search(r"^\s+[0-9a-f]+:\s+(?:R_MIPS_\w+|UNKNOWN)\s+(\S+)", l)
        if r and body:
            pend.append(r.group(1))
    if pend:
        body[-1] = sub_rel(body[-1], pend)
    res = []
    for s in body:
        s = brtarget(s)
        res.append(norm(s))
    return res

BR = ("b", "beq", "bne", "beqz", "bnez", "bc1t", "bc1f", "bgez", "bltz", "blez", "bgtz")

def brtarget(s):
    """objdump prints branch targets in hex without 0x; rewrite them as %Toff%."""
    t = s.split(" <")[0].strip()
    mn, _, rest = t.partition(" ")
    if mn not in BR or not rest:
        return t
    if "," in rest:
        head, _, last = rest.rpartition(",")
        sep = ","
    else:
        head, _, last = rest.rpartition(" ")
        sep = " "
    m = re.fullmatch(r"(0x)?([0-9a-f]+)", last.strip())
    if m:
        last = "%%T%x%%" % int(m.group(2), 16)
    return f"{mn} {head}{sep}{last}" if head else f"{mn} {last}"

def fold(s):
    s = re.sub(r"\(0x([0-9a-f]+) >> 0x10\)", lambda m: hex(int(m.group(1), 16) >> 16), s)
    s = re.sub(r"\(0x([0-9a-f]+) & 0xffff\)", lambda m: hex(int(m.group(1), 16) & 0xFFFF), s)
    return s

def norm(s):
    s = imm(nr(s))
    s = re.sub(r"\s*\(\$28\)", "($28)", s)
    s = re.sub(r"(?<![\w$])-?0x[0-9a-f]+(?=\(\$28\))", "%GP%", s)
    s = re.sub(r"^move (\$\d+),(\$\d+)$", r"daddu \1,\2,$0", s)
    s = s.replace("move ", "daddu ")
    s = re.sub(r",\s*", ",", s)
    s = re.sub(r"%\w+%\(\$28\)", "%GP%($28)", s)
    s = re.sub(r"^(jal|j) (?!%)(\S+)$", r"\1 %\2%", s)
    s = re.sub(r"\s*\(\$1\)", "($1)", s)
    s = re.sub(r"^li (\$\d+),(-?0x[0-9a-f]+)$", r"addiu \1,$0,\2", s)
    return s

def sub_rel(ins, syms):
    s = ins
    for sym in syms:
        mn = s.split(" ")[0]
        if mn in ("jal", "j"):
            s = mn + f" %{sym}%"
            continue
        s = re.sub(r"(?<![\w$])-?(0x[0-9a-f]+|\d+)", f"%{sym}%", s, count=1)
    return s

def collapsesyms(A, B):
    f = lambda x: re.sub(r"%[\w.]+%", "%SYM%", x)
    return [f(a) for a in A], [f(b) for b in B]

if __name__ == "__main__":
    c = sys.argv[1]
    for fn in sys.argv[2:]:
        A, B = ours(c, fn), retail(fn)
        while A and B and len(A) != len(B) and (A[-1] == "nop" or B[-1] == "nop"):
            if len(A) > len(B) and A[-1] == "nop": A.pop()
            elif len(B) > len(A) and B[-1] == "nop": B.pop()
            else: break
        print(f"== {fn}: ours {len(A)} retail {len(B)}")
        bad = 0
        for i in range(max(len(A), len(B))):
            a = A[i] if i < len(A) else "--"
            b = B[i] if i < len(B) else "--"
            if a != b:
                bad += 1
                print(f"{i*4:>4}  {a:<42} | {b}")
        print(f"differing words: {bad}/{max(len(A), len(B))}")
        As, Bs = collapsesyms(A, B)
        exact = sum(1 for a, b in zip(As, Bs) if a != b) + abs(len(As) - len(Bs))
        print(f"differing words (symbol names collapsed): {exact}")
