/*
 * C:\work\usam2\src\CS\option\optscr.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00232ee0-0x00233de0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_option_optscr_c_H
#define DDR_UNIT_src_CS_option_optscr_c_H

#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cOpt.h"
#include "types/_tag_cOptScr.h"

/* anonymous types (5) */

/* anon_0_21 -- @anon0, 0xcc8 bytes, optscr.c (DIE 0x4a6cc) */
struct anon_0_21 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_2_21 -- @anon2, 0x4 bytes, optscr.c (DIE 0x4ad26) */
union anon_2_21 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_21 -- @anon1, 0x24 bytes, optscr.c (DIE 0x4aae0) */
struct anon_1_21 {   // size 0x24
    /* 0x000 */ union anon_2_21 x0;                   // 0x4
    /* 0x004 */ union anon_2_21 y0;                   // 0x4
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

/* anon_3_21 -- @anon3, 0x48 bytes, optscr.c (DIE 0x4c05d) */
struct anon_3_21 {   // size 0x48
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

/* anon_4_21 -- @anon4, 0x10 bytes, optscr.c (DIE 0x4c889) */
struct anon_4_21 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00c */ int h;                                // 0x4
};


/* variables (6) */
struct _tag_cOptScr *pOptScr;                                    /* @0x002a2270 size 0x4 */
static unsigned int button_bit_table[6];                         /* @0x00282f00 size 0x18 */
static struct anon_4_21 button_tex[6];                           /* @0x00282f20 size 0x60 */
struct _tag_cOpt *pOpt;                                          /* @0x002a05c0 size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */
static struct _tag_cOptScr _pOptScr;                             /* @0x006b37c0 size 0x64 */

/* functions defined (4) */
int Update_Optscr(void);                                         /* 0x00232ee0-0x002330c8 lines 508-567 */
int View_Optscr(void);                                           /* 0x002330d0-0x00233768 lines 310-504 */
int Control_Optscr(void);                                        /* 0x00233770-0x00233d18 lines 133-298 */
int Init_Optscr(void);                                           /* 0x00233d20-0x00233de0 lines 99-128 */

#endif /* DDR_UNIT_src_CS_option_optscr_c_H */
