/*
 * C:\work2\usaex2\src\common\com_scrollbar.c
 * MW MIPS C Compiler, overlay main; 1 functions, code 0x00248050-0x00248590
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_common_com_scrollbar_c_H
#define DDR_UNIT_src_common_com_scrollbar_c_H

#include "types/_COM_SCROLLBAR_WORK.h"

/* anonymous types (3) */

/* anon_0_120 -- @anon0, 0x48 bytes, com_scrollbar.c (DIE 0x20ADBD) */
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
} anon_0_120;

/* anon_1_120 -- @anon1, 0x4 bytes, com_scrollbar.c (DIE 0x20B03F) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_1_120;

/* anon_2_120 -- @anon2, 0x30 bytes, com_scrollbar.c (DIE 0x20B09C) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_1_120 x0;                        // 0x4
    /* 0x004 */ anon_1_120 y0;                        // 0x4
    /* 0x008 */ anon_1_120 x1;                        // 0x4
    /* 0x00C */ anon_1_120 y1;                        // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
} anon_2_120;


/* functions defined (1) */
void ComScrollBarDisp(struct _COM_SCROLLBAR_WORK *scrbw);        /* 0x00248050-0x00248590 lines 12-80 */

#endif /* DDR_UNIT_src_common_com_scrollbar_c_H */
