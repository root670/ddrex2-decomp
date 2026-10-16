/*
 * C:\work\usam2\src\CS\opening\openinglogo.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x002468e0-0x00246f6c
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_opening_openinglogo_c_H
#define DDR_UNIT_src_CS_opening_openinglogo_c_H

#include "types/_tag_cOpening.h"
#include "types/_tag_cOpeninglogo.h"

/* anonymous types (3) */

/* anon_1_40 -- @anon1, 0x4 bytes, openinglogo.c (DIE 0x7b0ef) */
union anon_1_40 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_40 -- @anon0, 0x24 bytes, openinglogo.c (DIE 0x7af4b) */
struct anon_0_40 {   // size 0x24
    /* 0x000 */ union anon_1_40 x0;                   // 0x4
    /* 0x004 */ union anon_1_40 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00c */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01c */ unsigned char r0;                     // 0x1
    /* 0x01d */ unsigned char g0;                     // 0x1
    /* 0x01e */ unsigned char b0;                     // 0x1
    /* 0x01f */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};

/* anon_2_40 -- @anon2, 0x48 bytes, openinglogo.c (DIE 0x7b5db) */
struct anon_2_40 {   // size 0x48
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


/* variables (5) */
struct _tag_cOpeninglogo *pOpeninglogo;                          /* @0x002a259c size 0x4 */
static int logo_tex_num[2];                                      /* @0x002a25a0 size 0x8 */
static int warn_tex_num[1];                                      /* @0x002a25a8 size 0x4 */
struct _tag_cOpening *pOpening;                                  /* @0x002a06c4 size 0x4 */
static struct _tag_cOpeninglogo _pOpeninglogo;                   /* @0x006b42e0 size 0x1c */

/* functions defined (8) */
int Update_Openingwarn(void);                                    /* 0x002468e0-0x00246908 lines 300-304 */
int View_Openingwarn(void);                                      /* 0x00246910-0x00246a38 lines 271-297 */
int Control_Openingwarn(void);                                   /* 0x00246a40-0x00246b9c lines 223-270 */
int Init_Openingwarn(void);                                      /* 0x00246ba0-0x00246c1c lines 206-222 */
int Update_Openinglogo(void);                                    /* 0x00246c20-0x00246c48 lines 184-192 */
int View_Openinglogo(void);                                      /* 0x00246c50-0x00246d78 lines 152-178 */
int Control_Openinglogo(void);                                   /* 0x00246d80-0x00246ee4 lines 78-148 */
int Init_Openinglogo(void);                                      /* 0x00246ef0-0x00246f6c lines 55-74 */

#endif /* DDR_UNIT_src_CS_opening_openinglogo_c_H */
