/*
 * C:\work2\usaex2\src\AM\s573\doll\motion2.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x001CAE30-0x001CC004
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_motion2_c_H
#define DDR_UNIT_src_AM_s573_doll_motion2_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/dancer_motion_w.h"

/* anonymous types (10) */

/* anon_8_20 -- @anon8, 0x2 bytes, motion2.c (DIE 0x2F4CC) */
typedef struct {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
} anon_8_20;

/* anon_3_20 -- @anon3, 0x4 bytes, motion2.c (DIE 0x2F1BF) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ anon_8_20 tbl[1];                     // 0x2
} anon_3_20;

/* anon_0_20 -- @anon0, 0x8 bytes, motion2.c (DIE 0x2EE6B) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ anon_3_20 data;                       // 0x4
} anon_0_20;

/* anon_1_20 -- @anon1, 0xC bytes, motion2.c (DIE 0x2F016) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ anon_0_20 **offset;                   // 0x4
} anon_1_20;

/* anon_2_20 -- @anon2, 0xC bytes, motion2.c (DIE 0x2F10E) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ anon_1_20 **offset;                   // 0x4
} anon_2_20;

/* anon_4_20 -- @anon4, 0x8 bytes, motion2.c (DIE 0x2F226) */
typedef struct {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ anon_2_20 *offset;                    // 0x4
} anon_4_20;

/* anon_5_20 -- @anon5, 0x20 bytes, motion2.c (DIE 0x2F291) */
typedef struct {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
} anon_5_20;

/* anon_7_20 -- @anon7, 0x10 bytes, motion2.c (DIE 0x2F430) */
typedef struct {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
} anon_7_20;

/* anon_9_20 -- @anon9, 0x8 bytes, motion2.c (DIE 0x2F534) */
typedef struct {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
} anon_9_20;

/* anon_10_20 -- @anon10, 0x4 bytes, motion2.c (DIE 0x2F6CA) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short time;                  // 0x2
    /* 0x002 */ short data;                           // 0x2
} anon_10_20;


/* variables (1) */
int state;                                                       /* @0x002DE4BC size 0x4 */

/* functions defined (8) */
static int decodeMimeParam(anon_2_20 *md, struct _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x001CAE30-0x001CB25C lines 564-627 */
static int mimeAnimation_local(struct _GsCOORDINATE2 *dst, struct _GsCOORDINATE2 *src1, struct _GsCOORDINATE2 *src2, int hastrans, short rot1, short rot2, short w1, short w2); /* 0x001CB260-0x001CB474 lines 494-559 */
static int mimeAnimation(struct _GsCOORDINATE2 *coord2, anon_2_20 *md1, int frame1, anon_2_20 *md2, int frame2, int pidx, int weight); /* 0x001CB480-0x001CB728 lines 416-491 */
static void decodeRotateFormat(anon_5_20 *m, anon_7_20 *trans, anon_9_20 *rotate); /* 0x001CB730-0x001CB870 lines 377-407 */
static void decodeVectorFormat(anon_5_20 *mm, anon_7_20 *trans, anon_9_20 *dir, short rotate); /* 0x001CB870-0x001CBA5C lines 271-355 */
static short decodeBody(anon_3_20 *ptr, int frame);              /* 0x001CBA60-0x001CBB70 lines 197-233 */
static int decodeAnimation(anon_2_20 *md, struct _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x001CBB70-0x001CBE94 lines 79-163 */
void dancer_motion_decode(struct dancer_motion_w *dancer_motion_w); /* 0x001CBEA0-0x001CC004 lines 31-68 */

#endif /* DDR_UNIT_src_AM_s573_doll_motion2_c_H */
