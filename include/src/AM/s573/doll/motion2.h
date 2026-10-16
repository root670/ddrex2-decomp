/*
 * C:\work\usam2\src\AM\s573\doll\motion2.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0024d0e0-0x0024e2b4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_motion2_c_H
#define DDR_UNIT_src_AM_s573_doll_motion2_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/dancer_motion_w.h"

/* anonymous types (12) */

/* anon_6_51 -- @anon6, 0x2 bytes, motion2.c (DIE 0x8d83f) */
struct anon_6_51 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_8_51 -- @anon8, 0x4 bytes, motion2.c (DIE 0x8d92a) */
struct anon_8_51 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_6_51 tbl[1];              // 0x2
};

/* anon_0_51 -- @anon0, 0x8 bytes, motion2.c (DIE 0x8d34d) */
struct anon_0_51 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_8_51 data;                // 0x4
};

/* anon_1_51 -- @anon1, 0xc bytes, motion2.c (DIE 0x8d4f8) */
struct anon_1_51 {   // size 0xc
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_2_51 **offset;            // 0x4
};

/* anon_2_51 -- @anon2, 0xc bytes, motion2.c (DIE 0x8d5a9) */
struct anon_2_51 {   // size 0xc
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_0_51 **offset;            // 0x4
};

/* anon_3_51 -- @anon3, 0x4 bytes, motion2.c (DIE 0x8d6a1) */
struct anon_3_51 {   // size 0x4
    /* 0x000 */ unsigned short time;                  // 0x2
    /* 0x002 */ short data;                           // 0x2
};

/* anon_4_51 -- @anon4, 0x8 bytes, motion2.c (DIE 0x8d702) */
struct anon_4_51 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_1_51 *offset;             // 0x4
};

/* anon_5_51 -- @anon5, 0x10 bytes, motion2.c (DIE 0x8d76d) */
struct anon_5_51 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_4_51 motion[1];           // 0x8
};

/* anon_7_51 -- @anon7, 0x20 bytes, motion2.c (DIE 0x8d8a7) */
struct anon_7_51 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xc
};

/* anon_9_51 -- @anon9, 0x10 bytes, motion2.c (DIE 0x8dad5) */
struct anon_9_51 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00c */ int pad;                              // 0x4
};

/* anon_10_51 -- @anon10, 0x8 bytes, motion2.c (DIE 0x8db71) */
struct anon_10_51 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_11_51 -- @anon11, 0x28 bytes, motion2.c (DIE 0x8de30) */
struct anon_11_51 {   // size 0x28
    /* 0x000 */ struct anon_9_51 scale;               // 0x10
    /* 0x010 */ struct anon_10_51 rotate;             // 0x8
    /* 0x018 */ struct anon_9_51 trans;               // 0x10
};


/* variables (1) */
int state;                                                       /* @0x002a2ac0 size 0x4 */

/* functions defined (8) */
static int decodeMimeParam(struct anon_1_51 *md, struct _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x0024d0e0-0x0024d50c lines 566-629 */
static int mimeAnimation_local(struct _GsCOORDINATE2 *dst, struct _GsCOORDINATE2 *src1, struct _GsCOORDINATE2 *src2, int hastrans, short rot1, short rot2, short w1, short w2); /* 0x0024d510-0x0024d724 lines 496-561 */
static int mimeAnimation(struct _GsCOORDINATE2 *coord2, struct anon_1_51 *md1, int frame1, struct anon_1_51 *md2, int frame2, int pidx, int weight); /* 0x0024d730-0x0024d9d8 lines 418-493 */
static void decodeRotateFormat(struct anon_7_51 *m, struct anon_9_51 *trans, struct anon_10_51 *rotate); /* 0x0024d9e0-0x0024db20 lines 379-409 */
static void decodeVectorFormat(struct anon_7_51 *mm, struct anon_9_51 *trans, struct anon_10_51 *dir, short rotate); /* 0x0024db20-0x0024dd0c lines 273-357 */
static short decodeBody(struct anon_8_51 *ptr, int frame);       /* 0x0024dd10-0x0024de20 lines 199-235 */
static int decodeAnimation(struct anon_1_51 *md, struct _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x0024de20-0x0024e144 lines 81-165 */
void dancer_motion_decode(struct dancer_motion_w *dancer_motion_w); /* 0x0024e150-0x0024e2b4 lines 33-70 */

#endif /* DDR_UNIT_src_AM_s573_doll_motion2_c_H */
