/*
 * C:\work2\usaex2\src\CS\option\opt_win.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 13 functions, code 0x007F5EF0-0x007F7DB8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_option_opt_win_c_H
#define DDR_UNIT_src_CS_option_opt_win_c_H

#include "types/G_SYS_W_.h"
#include "types/_OPTSYS_W.h"
#include "types/_OPT_RECT.h"
#include "types/tex_bind.h"

/* anonymous types (6) */

/* anon_0_232 -- @anon0, 0x8 bytes, opt_win.c (DIE 0x44F71F) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_0_232;

/* anon_4_232 -- @anon4, 0x4 bytes, opt_win.c (DIE 0x450DFE) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_4_232;

/* anon_1_232 -- @anon1, 0x34 bytes, opt_win.c (DIE 0x44FE41) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_4_232 x0;                        // 0x4
    /* 0x004 */ anon_4_232 y0;                        // 0x4
    /* 0x008 */ anon_4_232 x1;                        // 0x4
    /* 0x00C */ anon_4_232 y1;                        // 0x4
    /* 0x010 */ anon_4_232 x2;                        // 0x4
    /* 0x014 */ anon_4_232 y2;                        // 0x4
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
} anon_1_232;

/* anon_2_232 -- @anon2, 0x48 bytes, opt_win.c (DIE 0x450117) */
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
} anon_2_232;

/* anon_3_232 -- @anon3, 0x24 bytes, opt_win.c (DIE 0x450C6A) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_4_232 x0;                        // 0x4
    /* 0x004 */ anon_4_232 y0;                        // 0x4
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
} anon_3_232;

/* anon_5_232 -- @anon5, 0x30 bytes, opt_win.c (DIE 0x450EA5) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_4_232 x0;                        // 0x4
    /* 0x004 */ anon_4_232 y0;                        // 0x4
    /* 0x008 */ anon_4_232 x1;                        // 0x4
    /* 0x00C */ anon_4_232 y1;                        // 0x4
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
} anon_5_232;


/* variables (2) */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */

/* functions defined (13) */
void OptLeftMenuBoxDisp(float x, float y, int pri, int onoff);   /* 0x007F5EF0-0x007F63D4 lines 1124-1222 */
void OptRightMenuCursorDisp(int n, int pri);                     /* 0x007F63E0-0x007F6718 lines 1067-1122 */
void OptWinMenuLineWindowClose(void);                            /* 0x007F6720-0x007F6838 lines 924-942 */
void OptWinMenuLineWindowMain(void);                             /* 0x007F6840-0x007F7628 lines 675-921 */
void OptWinMenuLineWindowOpen(void);                             /* 0x007F7630-0x007F76DC lines 656-672 */
int OptWinMenuLineWindowSet(int _y_pos, unsigned char _status, unsigned char *_str, unsigned char *_str2); /* 0x007F76E0-0x007F7850 lines 637-652 */
void OptWinSetWML_Str2(int _num, unsigned char *_str2);          /* 0x007F7850-0x007F78CC lines 630-635 */
int OptWinMenuLineWindowGetST_Stop(void);                        /* 0x007F78D0-0x007F790C lines 588-598 */
void OptWinAdjustClose(void);                                    /* 0x007F7910-0x007F7920 lines 573-574 */
void OptWinAdjustMain(void);                                     /* 0x007F7920-0x007F7D88 lines 403-569 */
void OptWinAdjustOpen(void);                                     /* 0x007F7D90-0x007F7DA0 lines 399-400 */
void OptWinTopBarClose(void);                                    /* 0x007F7DA0-0x007F7DA8 lines 52-52 */
void OptWinTopBarOpen(void);                                     /* 0x007F7DB0-0x007F7DB8 lines 40-40 */

#endif /* DDR_UNIT_src_CS_option_opt_win_c_H */
