"""``tools/diff`` -- the two objects ``ddr diff`` hands ``objdiff-cli``.

``basis.py`` is the whole package: the target side of the diff (the retail bytes of the
symbol under work, emitted as a relocatable object) and the one stand-in it needs when the
unit under edit has no C object at all (the same bytes out of a split, whose
``.NON_MATCHING`` alias no diff tool will score).  Nothing here is a gate and nothing here
links: the objects are a measuring device, written under the build's generated output
directory.
"""
