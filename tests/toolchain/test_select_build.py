"""The pair sweep has to measure the way the gate does: with retail's metadata adopted.

Measured before adoption, a unit whose ``.line`` is adopted failed condition 1 for *every*
candidate -- including the pair its own row records -- so ``select_build.py`` reported "no
installed compiler reproduces" for units that are green, and a hand-off had to guess a pair.
The flag axis was a second, smaller gap: no form carried ``-opt full``, the optimizer every
row in ``tu_builds`` records.
"""
from __future__ import annotations

from tools.toolchain import select_build as sb


def test_the_sweep_measures_with_adoption(monkeypatch):
    """The placement call is what has to adopt; that, not the flag list, was the defect."""
    seen = {}

    def fake_place(tu, manifests, compiler_dir, wibo, flags, **kwargs):
        seen.update(kwargs)
        raise RuntimeError("stop before the compiler runs")

    monkeypatch.setattr(sb.cc, "place", fake_place)
    monkeypatch.setattr(sb.fetch, "compiler", lambda *a, **k: None)
    monkeypatch.setattr(sb.fetch, "wibo", lambda *a, **k: None)
    outcome = sb.measure(object(), "3.0b38-030307", ("-c",), manifests=None)
    assert seen.get("adopt") is True
    assert all(not ok for ok, _ in outcome.values())


def test_the_flag_axis_carries_the_full_optimizer():
    """`-O3 -opt full -g` is what every row records, so the sweep must try it."""
    sets = [" ".join(flags) for flags in sb.flag_sets()]
    assert "-c -lang c -O3 -opt full -g" in sets
    assert sets[0] == "-c -lang c -O3 -opt full -g"


def test_the_preferred_build_leads():
    """`--first` must return the build this tree's rows use, not the fetcher's required one."""
    assert sb.CANDIDATES[0] == "3.0b38-030307"
    assert len(set(sb.CANDIDATES)) == len(sb.CANDIDATES)
