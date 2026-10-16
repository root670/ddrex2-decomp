/*
 * C:\work\usam2\src\CS\option\optdoll.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x0024f590-0x00250368
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

/* anon_0_54 -- @anon0, 0xcc8 bytes, optdoll.c (DIE 0x938d8) */
struct anon_0_54 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_1_54 -- @anon1, 0x3e bytes, optdoll.c (DIE 0x953cf) */
struct anon_1_54 {   // size 0x3e
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[61];                          // 0x3d
};

/* anon_2_54 -- @anon2, 0x8 bytes, optdoll.c (DIE 0x9578e) */
struct anon_2_54 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (10) */
static struct anon_2_54 crect;                                   /* @0x002a2610 size 0x8 */
static struct _tag_OptDoll *wk;                                  /* @0x002a2618 size 0x4 */
static struct _tag_cItemData ItemData[6];                        /* @0x0028b350 size 0x48 */
static int outstr_exp[6];                                        /* @0x0028b3a0 size 0x18 */
static int outstr_title[6];                                      /* @0x0028b3c0 size 0x18 */
struct _tag_cOpt *pOpt;                                          /* @0x002a05c0 size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */
struct _tag_cDDR7Option OptionDefault;                           /* @0x00274000 size 0x40 */
struct anon_1_54 lst;                                            /* @0x006b6ad0 size 0x3e */
static struct _tag_OptDoll _pOptDoll;                            /* @0x006b6b10 size 0x2c */

/* functions defined (11) */
int Update_OptDoll(void);                                        /* 0x0024f590-0x0024f630 lines 425-440 */
int View_OptDoll(void);                                          /* 0x0024f630-0x0024fb4c lines 294-421 */
static int control_lr(int *pcursor, int _lr);                    /* 0x0024fb50-0x0024fc80 lines 265-290 */
int Control_OptDoll(void);                                       /* 0x0024fc80-0x0025015c lines 139-260 */
int Init_OptDoll(void);                                          /* 0x00250160-0x002502cc lines 98-133 */
static int GetBoolExist_exit(void);                              /* 0x002502d0-0x002502d8 lines 65-65 */
static int GetBoolExist_3p(void);                                /* 0x002502e0-0x002502f4 lines 64-64 */
static int GetBoolExist_2p(void);                                /* 0x00250300-0x00250314 lines 63-63 */
static int GetBoolExist_1p(void);                                /* 0x00250320-0x00250334 lines 62-62 */
static int GetBoolExist_guest(void);                             /* 0x00250340-0x00250354 lines 61-61 */
static int GetBoolExist_disp(void);                              /* 0x00250360-0x00250368 lines 60-60 */

#endif /* DDR_UNIT_src_CS_option_optdoll_c_H */
