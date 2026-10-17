#!/usr/bin/env python3
"""nopline round 2 -- the join-point / empty-`else` family and the other `__asm` spellings.

Round 1 (`measure.py`) found exactly one construct that adds both the record and the pad
`nop`: an inline-assembly `nop` statement on line 103 inside the `if` body.  Round 2 asks the
two questions it left open:

* is there a *C* construct that does the same -- specifically an empty `else` (which would put
  the compiler's join point, and possibly a `nop`, exactly where retail's pad is), a `goto` to
  the join label, or a `do {} while (0)`;
* is there a construct that adds the *record* with no bytes at all (the two gates then differ).

Each candidate is a whole function body with its `#line` markers, so a shape that adds a brace
stays honest about which physical line it sits on.

    python3 drafts/nopline/round2.py
"""

from __future__ import annotations

import pathlib
import sys

sys.path[:0] = [str(pathlib.Path(__file__).resolve().parent)]
import measure  # noqa: E402

HEAD = measure.HEAD
STORE = ("#line 102\n"
         "            SaveData.HideFlag[(i + 0x46) >> 5] |= 1 << ((i + 0x46) & 0x1F);")

#: name -> what replaces the `if (...) { ... }` statement (line 101 .. 103)
SHAPES = {
    "control":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n        }",
    "else-brace":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n        } else { }",
    "else-stmt":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n        } else ;",
    "else-label":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n        } else {\n"
        "            nop103: ;\n        }",
    "else-brace-before-brace":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n        } else\n        { }",
    "goto-join":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            goto done103;\n        }\n    done103: ;",
    "goto-join-eol":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            goto done103;\n    done103: ;\n        }",
    "goto-label-only":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "        nop103: ;\n        }",
    "asm-block":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            asm { nop }\n        }",
    "asm-volatile":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            __asm__ volatile (\"nop\");\n        }",
    "asm-string-two":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            asm (\"nop\\nnop\");\n        }",
    "dotline-then-asm":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            __asm__ (\"nop\");\n        }",
    "while-0":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            while (0) ;\n        }",
    "for-break":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            for (;;) break;\n        }",
    "if-negated-empty":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            if (!i) { }\n        }",
    "ternary-void":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            i ? 0 : 0;\n        }",
    "comma-expr":
        "        if (get_chara_hide(i)) {\n" + STORE + "\n#line 103\n"
        "            (void)(i, 0);\n        }",
}

TMPL = HEAD + """\
#line 98
void ps2dancerInitHide(void) { int i;
#line 99

#line 100
    i = 0;
    do {
#line 101
@SHAPE@
#line 104
        i++;
    } while (i < 0x2D);
#line 105
}
"""


def main() -> int:
    control = measure.measure(TMPL.replace("@SHAPE@", SHAPES["control"]), "control")
    c = next(iter(control["funcs"].values()))
    print(f"control: .text 0x{len(c['bytes']):X}, records " +
          " ".join(f"{ln}@{a:#x}" for a, ln in c["rows"]))
    print("| shape | .text | delta | first diff | insert | line |")
    print("|---|---|---|---|---|---|")
    for name, shape in SHAPES.items():
        if name == "control":
            continue
        try:
            v = measure.measure(TMPL.replace("@SHAPE@", shape), name)
        except Exception as exc:
            print(f"| {name:<22} | COMPILE FAILED: {type(exc).__name__} |")
            continue
        print(measure.summarise(control, v))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
