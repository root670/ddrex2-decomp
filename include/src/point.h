/*
 * C:\work2\usaex2\src\point.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x0023E130-0x0023F2EC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_point_c_H
#define DDR_UNIT_src_point_c_H

#include "types/_tag_cPointSaveWork.h"
#include "types/_tag_cPointWork.h"
#include "types/_tag_cPointWorkPlayer.h"
#include "types/eval_w.h"
#include "types/g_game_w.h"

/* anonymous types (6) */

/* anon_0_108 -- @anon0, 0x4 bytes, point.c (DIE 0x1E3FAF) */
union anon_0_108 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_108 -- @anon1, 0x4 bytes, point.c (DIE 0x1E4395) */
struct anon_1_108 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_2_108 -- @anon2, 0x10 bytes, point.c (DIE 0x1E446D) */
struct anon_2_108 {   // size 0x10
    /* 0x000 */ union anon_0_108 x0;                  // 0x4
    /* 0x004 */ union anon_0_108 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_3_108 -- @anon3, 0x184 bytes, point.c (DIE 0x1E4803) */
struct anon_3_108 {   // size 0x184
    /* 0x000 */ struct anon_2_108 line_a[8];          // 0x80
    /* 0x080 */ struct anon_2_108 line_b[8];          // 0x80
    /* 0x100 */ struct anon_2_108 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_4_108 -- @anon4, 0x14 bytes, point.c (DIE 0x1E6515) */
struct anon_4_108 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_5_108 -- @anon5, 0xC bytes, point.c (DIE 0x1E6F1C) */
struct anon_5_108 {   // size 0xC
    /* 0x000 */ int mode_quit_flg;                    // 0x4
    /* 0x004 */ int state;                            // 0x4
    /* 0x008 */ int renewal_record_flag;              // 0x4
};


/* variables (6) */
static struct _tag_cPointSaveWork *psw;                          /* @0x002DDC30 size 0x4 */
static struct _tag_cPointWork *pw;                               /* @0x002DDC34 size 0x4 */
static int free_play_point_table[77];                            /* @0x002BEDF0 size 0x134 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct anon_5_108 usr_work;                                      /* @0x00328A20 size 0xC */
static struct _tag_cPointWork _pw;                               /* @0x0071F8E0 size 0xA0 */

/* functions defined (13) */
int PointGetHistPoint(void);                                     /* 0x0023E130-0x0023E13C lines 588-589 */
static int register_free_play(void);                             /* 0x0023E140-0x0023E260 lines 552-581 */
int PointRegisterPoint(void);                                    /* 0x0023E260-0x0023E294 lines 534-544 */
int PointCalcDispPoint(int pid);                                 /* 0x0023E2A0-0x0023E398 lines 496-528 */
static int calc_free_play(int pid);                              /* 0x0023E3A0-0x0023E500 lines 441-489 */
int PointCalcPoint(int pid);                                     /* 0x0023E500-0x0023E534 lines 408-418 */
int PointGetDispPoint(int pid);                                  /* 0x0023E540-0x0023E564 lines 397-398 */
static void init_endless_play(int mode);                         /* 0x0023E570-0x0023E6C0 lines 355-388 */
static void init_free_play(void);                                /* 0x0023E6C0-0x0023EA78 lines 217-322 */
void PointInitPlay(void);                                        /* 0x0023EA80-0x0023F25C lines 122-203 */
int PointAddTotalPoint(int point);                               /* 0x0023F260-0x0023F2CC lines 86-96 */
int PointGetTotalPoint(void);                                    /* 0x0023F2D0-0x0023F2DC lines 75-76 */
void PointInitSaveWork(void);                                    /* 0x0023F2E0-0x0023F2EC lines 68-68 */

#endif /* DDR_UNIT_src_point_c_H */
