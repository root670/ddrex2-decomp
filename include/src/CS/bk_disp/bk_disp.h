/*
 * C:\work2\usaex2\src\CS\bk_disp\bk_disp.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x00203EB0-0x002046C0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_CS_bk_disp_bk_disp_c_H
#define DDR_UNIT_src_CS_bk_disp_bk_disp_c_H

#include "types/_EYETOY_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/play_w.h"
#include "types/tex_bind.h"

/* anonymous types (2) */

/* anon_1_60 -- @anon1, 0x48 bytes, bk_disp.c (DIE 0xE6A88) */
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
} anon_1_60;

/* anon_5_60 -- @anon5, 0x10 bytes, bk_disp.c (DIE 0xE856D) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_5_60;


/* variables (4) */
static int ti_cnt;                                               /* @0x002DE520 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _EYETOY_W *EYETOYW;                                       /* @0x002DD9A8 size 0x4 */

/* functions defined (6) */
static void bk_disp_title(int bright, int blend);                /* 0x00203EB0-0x0020426C lines 272-358 */
void bk_play_disp_finish(void);                                  /* 0x00204270-0x0020429C lines 261-264 */
void bk_play_disp_step(void);                                    /* 0x002042A0-0x002045B4 lines 117-256 */
void bk_play_disp_init(void);                                    /* 0x002045C0-0x0020466C lines 88-112 */
int bk_disp_read_wait(void);                                     /* 0x00204670-0x002046AC lines 74-80 */
void bk_disp_read_set(int flg);                                  /* 0x002046B0-0x002046C0 lines 67-67 */

#endif /* DDR_UNIT_src_CS_bk_disp_bk_disp_c_H */
