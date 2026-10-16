/*
 * C:\work\usam2\src\CS\staffroll\cs_staff_aid.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00242dc0-0x002442dc
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_staffroll_cs_staff_aid_c_H
#define DDR_UNIT_src_CS_staffroll_cs_staff_aid_c_H

#include "types/stf_font_rgba.h"
#include "types/stf_font_size.h"

/* anonymous types (4) */

/* anon_3_34 -- @anon3, 0x4 bytes, cs_staff_aid.c (DIE 0x6c7ec) */
union anon_3_34 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_34 -- @anon0, 0x34 bytes, cs_staff_aid.c (DIE 0x6bbd3) */
struct anon_0_34 {   // size 0x34
    /* 0x000 */ union anon_3_34 x0;                   // 0x4
    /* 0x004 */ union anon_3_34 y0;                   // 0x4
    /* 0x008 */ union anon_3_34 x1;                   // 0x4
    /* 0x00c */ union anon_3_34 y1;                   // 0x4
    /* 0x010 */ union anon_3_34 x2;                   // 0x4
    /* 0x014 */ union anon_3_34 y2;                   // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01c */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02a */ unsigned char b1;                     // 0x1
    /* 0x02b */ unsigned char a1;                     // 0x1
    /* 0x02c */ unsigned char r2;                     // 0x1
    /* 0x02d */ unsigned char g2;                     // 0x1
    /* 0x02e */ unsigned char b2;                     // 0x1
    /* 0x02f */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
};

/* anon_1_34 -- @anon1, 0x74 bytes, cs_staff_aid.c (DIE 0x6bea9) */
struct anon_1_34 {   // size 0x74
    /* 0x000 */ union anon_3_34 x0;                   // 0x4
    /* 0x004 */ union anon_3_34 y0;                   // 0x4
    /* 0x008 */ union anon_3_34 x1;                   // 0x4
    /* 0x00c */ union anon_3_34 y1;                   // 0x4
    /* 0x010 */ union anon_3_34 x2;                   // 0x4
    /* 0x014 */ union anon_3_34 y2;                   // 0x4
    /* 0x018 */ union anon_3_34 x3;                   // 0x4
    /* 0x01c */ union anon_3_34 y3;                   // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02c */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03c */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04c */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05c */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ unsigned char r1;                     // 0x1
    /* 0x065 */ unsigned char g1;                     // 0x1
    /* 0x066 */ unsigned char b1;                     // 0x1
    /* 0x067 */ unsigned char a1;                     // 0x1
    /* 0x068 */ unsigned char r2;                     // 0x1
    /* 0x069 */ unsigned char g2;                     // 0x1
    /* 0x06a */ unsigned char b2;                     // 0x1
    /* 0x06b */ unsigned char a2;                     // 0x1
    /* 0x06c */ unsigned char r3;                     // 0x1
    /* 0x06d */ unsigned char g3;                     // 0x1
    /* 0x06e */ unsigned char b3;                     // 0x1
    /* 0x06f */ unsigned char a3;                     // 0x1
    /* 0x070 */ int flg;                              // 0x4
};

/* anon_2_34 -- @anon2, 0x48 bytes, cs_staff_aid.c (DIE 0x6c3d0) */
struct anon_2_34 {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00c */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02c */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03a */ unsigned short tw;                    // 0x2
    /* 0x03c */ unsigned short th;                    // 0x2
    /* 0x03e */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
};


/* variables (1) */
static struct stf_font_size stf_font_size[160];                  /* @0x00287d60 size 0x500 */

/* functions defined (5) */
static void CsStfBBoxSetStr(unsigned char *string, float _x, float _y, int _flag); /* 0x00242dc0-0x002431a4 lines 612-662 */
static void CsStfBBoxSetXYA(struct anon_0_34 *g3a, struct anon_0_34 *g3b, int point, float _x, float _y, unsigned char _alpha); /* 0x002431b0-0x00243328 lines 556-603 */
int CsStfAidTexture(float _x, float _y, int _tex, int _flag);    /* 0x00243330-0x00243640 lines 492-536 */
static int CsStfAidGetStrSize(char *str, int num);               /* 0x00243640-0x0024391c lines 406-464 */
void CsStfAidFont(float _x, float _y, char *_string, char _color, int _type, int _flag); /* 0x00243920-0x002442dc lines 234-401 */

#endif /* DDR_UNIT_src_CS_staffroll_cs_staff_aid_c_H */
