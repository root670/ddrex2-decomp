/*
 * C:\work2\usaex2\src\AM\s573\doll\motion2.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x001CAE30-0x001CC004
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_motion2_c_H
#define DDR_UNIT_src_AM_s573_doll_motion2_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/dancer_motion_w.h"

/* anonymous types (1) */

/* anon_10_20 -- @anon10, 0x4 bytes, motion2.c (DIE 0x2F6CA) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short time;                  // 0x2
    /* 0x002 */ short data;                           // 0x2
} anon_10_20;


/* variables (1) */
int state;                                                       /* @0x002DE4BC size 0x4 */

/* functions defined (8) */
static int decodeMimeParam(anon_fc1cdcfc0514 *md, struct _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x001CAE30-0x001CB25C lines 564-627 */
static int mimeAnimation_local(struct _GsCOORDINATE2 *dst, struct _GsCOORDINATE2 *src1, struct _GsCOORDINATE2 *src2, int hastrans, short rot1, short rot2, short w1, short w2); /* 0x001CB260-0x001CB474 lines 494-559 */
static int mimeAnimation(struct _GsCOORDINATE2 *coord2, anon_fc1cdcfc0514 *md1, int frame1, anon_fc1cdcfc0514 *md2, int frame2, int pidx, int weight); /* 0x001CB480-0x001CB728 lines 416-491 */
static void decodeRotateFormat(anon_b6ba1fe93475 *m, anon_9e7dd0ae7596 *trans, anon_00dccc0f5082 *rotate); /* 0x001CB730-0x001CB870 lines 377-407 */
static void decodeVectorFormat(anon_b6ba1fe93475 *mm, anon_9e7dd0ae7596 *trans, anon_00dccc0f5082 *dir, short rotate); /* 0x001CB870-0x001CBA5C lines 271-355 */
static short decodeBody(anon_4c0903f15570 *ptr, int frame);      /* 0x001CBA60-0x001CBB70 lines 197-233 */
static int decodeAnimation(anon_fc1cdcfc0514 *md, struct _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x001CBB70-0x001CBE94 lines 79-163 */
void dancer_motion_decode(struct dancer_motion_w *dancer_motion_w); /* 0x001CBEA0-0x001CC004 lines 31-68 */

#endif /* DDR_UNIT_src_AM_s573_doll_motion2_c_H */
