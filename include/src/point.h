/*
 * C:\work2\usaex2\src\point.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x0023E130-0x0023F2EC
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
#ifndef DDR_UNIT_src_point_c_H
#define DDR_UNIT_src_point_c_H

#include "types/_tag_cPointSaveWork.h"
#include "types/_tag_cPointWork.h"
#include "types/_tag_cPointWorkPlayer.h"
#include "types/eval_w.h"
#include "types/g_game_w.h"

/* anonymous types (1) */

/* anon_5_108 -- @anon5, 0xC bytes, point.c (DIE 0x1E6F1C) */
typedef struct {   // size 0xC
    /* 0x000 */ int mode_quit_flg;                    // 0x4
    /* 0x004 */ int state;                            // 0x4
    /* 0x008 */ int renewal_record_flag;              // 0x4
} anon_5_108;


/* variables (6) */
static struct _tag_cPointSaveWork *psw;                          /* @0x002DDC30 size 0x4 */
static struct _tag_cPointWork *pw;                               /* @0x002DDC34 size 0x4 */
static int free_play_point_table[77];                            /* @0x002BEDF0 size 0x134 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_5_108 usr_work;                                             /* @0x00328A20 size 0xC */
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
