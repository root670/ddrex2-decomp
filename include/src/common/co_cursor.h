/*
 * C:\work2\usaex2\src\common\co_cursor.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x0023CA40-0x0023CEB8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_common_co_cursor_c_H
#define DDR_UNIT_src_common_co_cursor_c_H

#include "types/_tag_cCoCursor01.h"

/* anonymous types (3) */

/* anon_0_105 -- @anon0, 0x48 bytes, co_cursor.c (DIE 0x1DFE2E) */
typedef struct {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02C */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03A */ unsigned short tw;                    // 0x2
    /* 0x03C */ unsigned short th;                    // 0x2
    /* 0x03E */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
} anon_0_105;

/* anon_1_105 -- @anon1, 0x4 bytes, co_cursor.c (DIE 0x1E0141) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_1_105;

/* anon_2_105 -- @anon2, 0x68 bytes, co_cursor.c (DIE 0x1E019E) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_1_105 x0;                        // 0x4
    /* 0x004 */ anon_1_105 y0;                        // 0x4
    /* 0x008 */ anon_1_105 x1;                        // 0x4
    /* 0x00C */ anon_1_105 y1;                        // 0x4
    /* 0x010 */ anon_1_105 x2;                        // 0x4
    /* 0x014 */ anon_1_105 y2;                        // 0x4
    /* 0x018 */ anon_1_105 x3;                        // 0x4
    /* 0x01C */ anon_1_105 y3;                        // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
} anon_2_105;


/* functions defined (2) */
void co_cursor01_disp(struct _tag_cCoCursor01 *p, float x, float y, int a, int bri, int pri, int tex_id, int flag); /* 0x0023CA40-0x0023CE7C lines 62-173 */
void co_cursor01_init(struct _tag_cCoCursor01 *p);               /* 0x0023CE80-0x0023CEB8 lines 28-32 */

#endif /* DDR_UNIT_src_common_co_cursor_c_H */
