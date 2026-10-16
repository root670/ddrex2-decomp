/*
 * C:\work2\usaex2\src\common\cws\cws_obj.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x002046C0-0x00205510
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_common_cws_cws_obj_c_H
#define DDR_UNIT_src_common_cws_cws_obj_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (5) */

/* anon_0_61 -- @anon0, 0x8 bytes, cws_obj.c (DIE 0xEE9C4) */
struct anon_0_61 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_3_61 -- @anon3, 0x4 bytes, cws_obj.c (DIE 0xEF7B9) */
union anon_3_61 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_61 -- @anon1, 0x34 bytes, cws_obj.c (DIE 0xEEBED) */
struct anon_1_61 {   // size 0x34
    /* 0x000 */ union anon_3_61 x0;                   // 0x4
    /* 0x004 */ union anon_3_61 y0;                   // 0x4
    /* 0x008 */ union anon_3_61 x1;                   // 0x4
    /* 0x00C */ union anon_3_61 y1;                   // 0x4
    /* 0x010 */ union anon_3_61 x2;                   // 0x4
    /* 0x014 */ union anon_3_61 y2;                   // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
};

/* anon_2_61 -- @anon2, 0x48 bytes, cws_obj.c (DIE 0xEEEC3) */
struct anon_2_61 {   // size 0x48
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

/* anon_4_61 -- @anon4, 0x30 bytes, cws_obj.c (DIE 0xEF816) */
struct anon_4_61 {   // size 0x30
    /* 0x000 */ union anon_3_61 x0;                   // 0x4
    /* 0x004 */ union anon_3_61 y0;                   // 0x4
    /* 0x008 */ union anon_3_61 x1;                   // 0x4
    /* 0x00C */ union anon_3_61 y1;                   // 0x4
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


/* functions defined (8) */
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);  /* 0x002046C0-0x00205078 lines 171-310 */
char CwsObjMoveOpt(int *_v, int _timer, int _s, int _end_time, int _type); /* 0x00205080-0x0020516C lines 153-165 */
char CwsObjMove(int *_v, int *_timer, int _s, int _end_time, int _type); /* 0x00205170-0x00205280 lines 137-150 */
char CwsObjDelete(struct _CWS_OBJ *work);                        /* 0x00205280-0x002052B4 lines 119-126 */
char CwsObjChangeTex(struct _CWS_OBJ *work, int tex_num);        /* 0x002052C0-0x002052E8 lines 111-116 */
char CwsObjSetXYWH(struct _CWS_OBJ *work, int x, int y, int w, int h); /* 0x002052F0-0x00205320 lines 99-107 */
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate); /* 0x00205320-0x002053B0 lines 81-95 */
struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);        /* 0x002053B0-0x00205510 lines 24-51 */

#endif /* DDR_UNIT_src_common_cws_cws_obj_c_H */
