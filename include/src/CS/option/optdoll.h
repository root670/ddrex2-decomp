/*
 * C:\work\usam2\src\CS\option\optdoll.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x0024F590-0x00250368
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_option_optdoll_c_H
#define DDR_UNIT_src_CS_option_optdoll_c_H

#include "types/_tag_OptDoll.h"
#include "types/_tag_cDDR7Option.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cItemData.h"
#include "types/_tag_cOpt.h"

/* anonymous types (3) */

/* anon_0_54 -- @anon0, 0xCC8 bytes, optdoll.c (DIE 0x938D8) */
struct anon_0_54 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_1_54 -- @anon1, 0x3E bytes, optdoll.c (DIE 0x953CF) */
struct anon_1_54 {   // size 0x3E
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[61];                          // 0x3D
};

/* anon_2_54 -- @anon2, 0x8 bytes, optdoll.c (DIE 0x9578E) */
struct anon_2_54 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (10) */
static struct anon_2_54 crect;                                   /* @0x002A2610 size 0x8 */
static struct _tag_OptDoll *wk;                                  /* @0x002A2618 size 0x4 */
static struct _tag_cItemData ItemData[6];                        /* @0x0028B350 size 0x48 */
static int outstr_exp[6];                                        /* @0x0028B3A0 size 0x18 */
static int outstr_title[6];                                      /* @0x0028B3C0 size 0x18 */
struct _tag_cOpt *pOpt;                                          /* @0x002A05C0 size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
struct _tag_cDDR7Option OptionDefault;                           /* @0x00274000 size 0x40 */
struct anon_1_54 lst;                                            /* @0x006B6AD0 size 0x3E */
static struct _tag_OptDoll _pOptDoll;                            /* @0x006B6B10 size 0x2C */

/* functions defined (11) */
int Update_OptDoll(void);                                        /* 0x0024F590-0x0024F630 lines 425-440 */
int View_OptDoll(void);                                          /* 0x0024F630-0x0024FB4C lines 294-421 */
static int control_lr(int *pcursor, int _lr);                    /* 0x0024FB50-0x0024FC80 lines 265-290 */
int Control_OptDoll(void);                                       /* 0x0024FC80-0x0025015C lines 139-260 */
int Init_OptDoll(void);                                          /* 0x00250160-0x002502CC lines 98-133 */
static int GetBoolExist_exit(void);                              /* 0x002502D0-0x002502D8 lines 65-65 */
static int GetBoolExist_3p(void);                                /* 0x002502E0-0x002502F4 lines 64-64 */
static int GetBoolExist_2p(void);                                /* 0x00250300-0x00250314 lines 63-63 */
static int GetBoolExist_1p(void);                                /* 0x00250320-0x00250334 lines 62-62 */
static int GetBoolExist_guest(void);                             /* 0x00250340-0x00250354 lines 61-61 */
static int GetBoolExist_disp(void);                              /* 0x00250360-0x00250368 lines 60-60 */

#endif /* DDR_UNIT_src_CS_option_optdoll_c_H */
