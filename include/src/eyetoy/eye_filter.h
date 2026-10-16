/*
 * C:\work2\usaex2\src\eyetoy\eye_filter.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001E7590-0x001E7704
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_eyetoy_eye_filter_c_H
#define DDR_UNIT_src_eyetoy_eye_filter_c_H

#include "types/sceImage.h"

/* functions defined (2) */
void sepia(struct sceImage *_dest_r, struct sceImage *_dest_b);  /* 0x001E7590-0x001E7660 lines 318-340 */
void negaposi(struct sceImage *_dest_rgba, struct sceImage *_src_rgba); /* 0x001E7660-0x001E7704 lines 252-284 */

#endif /* DDR_UNIT_src_eyetoy_eye_filter_c_H */
