/*
 * C:\work2\usaex2\src\common\com_keyboard.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0022BA50-0x0022C4A8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_common_com_keyboard_c_H
#define DDR_UNIT_src_common_com_keyboard_c_H

#include "types/FRAME_W.h"
#include "types/G_SYS_W_.h"
#include "types/_COM_KEYBOARD_WORK.h"

/* anonymous types (4) */

/* anon_0_89 -- @anon0, 0x48 bytes, com_keyboard.c (DIE 0x19A0F7) */
struct anon_0_89 {   // size 0x48
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
};

/* anon_2_89 -- @anon2, 0x4 bytes, com_keyboard.c (DIE 0x19A902) */
union anon_2_89 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_89 -- @anon1, 0x24 bytes, com_keyboard.c (DIE 0x19A76E) */
struct anon_1_89 {   // size 0x24
    /* 0x000 */ union anon_2_89 x0;                   // 0x4
    /* 0x004 */ union anon_2_89 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01C */ unsigned char r0;                     // 0x1
    /* 0x01D */ unsigned char g0;                     // 0x1
    /* 0x01E */ unsigned char b0;                     // 0x1
    /* 0x01F */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};

/* anon_3_89 -- @anon3, 0x30 bytes, com_keyboard.c (DIE 0x19A95F) */
struct anon_3_89 {   // size 0x30
    /* 0x000 */ union anon_2_89 x0;                   // 0x4
    /* 0x004 */ union anon_2_89 y0;                   // 0x4
    /* 0x008 */ union anon_2_89 x1;                   // 0x4
    /* 0x00C */ union anon_2_89 y1;                   // 0x4
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
};


/* variables (2) */
static unsigned char keyset_mark_code[2][13];                    /* @0x002BD2D0 size 0x1A */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */

/* functions defined (3) */
int ComKeyBoardIsAvailableKey(struct _COM_KEYBOARD_WORK *kb, unsigned int _x_num, unsigned int _y_num); /* 0x0022BA50-0x0022BA80 lines 218-226 */
int ComKeyBoardGetCode(int _type, unsigned int _x_num, unsigned int _y_num, unsigned int _flag); /* 0x0022BA80-0x0022BC48 lines 170-212 */
void ComKeyBoardDisp(struct _COM_KEYBOARD_WORK *kb);             /* 0x0022BC50-0x0022C4A8 lines 11-153 */

#endif /* DDR_UNIT_src_common_com_keyboard_c_H */
