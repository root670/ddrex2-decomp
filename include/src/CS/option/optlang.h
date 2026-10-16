/*
 * C:\work\usam2\src\CS\option\optlang.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00239680-0x0023a128
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_option_optlang_c_H
#define DDR_UNIT_src_CS_option_optlang_c_H

#include "types/_tag_cItemData.h"
#include "types/_tag_cOpt.h"
#include "types/_tag_cOptLang.h"

/* anonymous types (4) */

/* anon_1_27 -- @anon1, 0x4 bytes, optlang.c (DIE 0x60e34) */
union anon_1_27 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_27 -- @anon0, 0x24 bytes, optlang.c (DIE 0x60c80) */
struct anon_0_27 {   // size 0x24
    /* 0x000 */ union anon_1_27 x0;                   // 0x4
    /* 0x004 */ union anon_1_27 y0;                   // 0x4
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

/* anon_2_27 -- @anon2, 0x48 bytes, optlang.c (DIE 0x60fe6) */
struct anon_2_27 {   // size 0x48
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

/* anon_3_27 -- @anon3, 0x10 bytes, optlang.c (DIE 0x61aef) */
struct anon_3_27 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00c */ int h;                                // 0x4
};


/* variables (6) */
struct _tag_cOptLang *pOptLang;                                  /* @0x002a2274 size 0x4 */
static struct _tag_cItemData ItemData[5];                        /* @0x00285d80 size 0x3c */
static unsigned int button_bit_table[6];                         /* @0x00285dc0 size 0x18 */
static struct anon_3_27 button_tex[6];                           /* @0x00285de0 size 0x60 */
struct _tag_cOpt *pOpt;                                          /* @0x002a05c0 size 0x4 */
static struct _tag_cOptLang _pOptLang;                           /* @0x006b3830 size 0x44 */

/* functions defined (9) */
int Update_Optlang(void);                                        /* 0x00239680-0x00239788 lines 400-432 */
int View_Optlang(void);                                          /* 0x00239790-0x00239c98 lines 236-396 */
int Control_Optlang(void);                                       /* 0x00239ca0-0x0023a004 lines 144-230 */
int Init_Optlang(void);                                          /* 0x0023a010-0x0023a0d4 lines 102-139 */
static int GetBoolExist_spanish(void);                           /* 0x0023a0e0-0x0023a0e8 lines 52-52 */
static int GetBoolExist_italian(void);                           /* 0x0023a0f0-0x0023a0f8 lines 51-51 */
static int GetBoolExist_german(void);                            /* 0x0023a100-0x0023a108 lines 50-50 */
static int GetBoolExist_french(void);                            /* 0x0023a110-0x0023a118 lines 49-49 */
static int GetBoolExist_english(void);                           /* 0x0023a120-0x0023a128 lines 48-48 */

#endif /* DDR_UNIT_src_CS_option_optlang_c_H */
