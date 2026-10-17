/*
 * C:\work2\usaex2\src\network\net_window\net_win_user.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x0022EEC0-0x0022F7D8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_user_c_H
#define DDR_UNIT_src_network_net_window_net_win_user_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/_net_win_user_w.h"

/* anonymous types (2) */

/* anon_2_96 -- @anon2, 0x4 bytes, net_win_user.c (DIE 0x1AE109) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_2_96;

/* anon_1_96 -- @anon1, 0x34 bytes, net_win_user.c (DIE 0x1AD65C) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_2_96 x0;                         // 0x4
    /* 0x004 */ anon_2_96 y0;                         // 0x4
    /* 0x008 */ anon_2_96 x1;                         // 0x4
    /* 0x00C */ anon_2_96 y1;                         // 0x4
    /* 0x010 */ anon_2_96 x2;                         // 0x4
    /* 0x014 */ anon_2_96 y2;                         // 0x4
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
} anon_1_96;


/* variables (9) */
static int (*NetWin_UserFunc[3])(struct _CWS_WIN_W *);           /* @0x002BE228 size 0xC */
static void (*NetWin_UserCode[4])(struct _CWS_WIN_W *);          /* @0x002BE240 size 0x10 */
static struct _CWS_OBJ_TEX netwinuser_plate_board[1];            /* @0x002BE250 size 0x14 */
static struct _CWS_OBJ_TEX netwinuser_plate_board2[4];           /* @0x002BE270 size 0x50 */
static struct _CWS_OBJ_TEX netwinuser_plate_board3[1];           /* @0x002BE2C0 size 0x14 */
static struct _CWS_OBJ_TEX netwinuser_plate_obj[5];              /* @0x002BE2E0 size 0x64 */
static struct _CWS_OBJ_TEX netwinuser_plate_namewaku[3];         /* @0x002BE350 size 0x3C */
static struct _CWS_OBJ_TEX netwinuser_plate_chara[1];            /* @0x002BE390 size 0x14 */
static struct _CWS_OBJ_SET netwinuser[6];                        /* @0x002BE3B0 size 0x78 */

/* functions defined (6) */
void NetWin_UserSetUserFile(struct _CWS_WIN_W *win, struct _NSV_USER_FILE_WORK *addr); /* 0x0022EEC0-0x0022EEC8 lines 426-426 */
static void NetWin_UserBoardDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x0022EED0-0x0022F218 lines 360-417 */
static int NetWin_UserEnd(struct _CWS_WIN_W *win);               /* 0x0022F220-0x0022F234 lines 355-357 */
static int NetWin_UserMain(struct _CWS_WIN_W *win);              /* 0x0022F240-0x0022F430 lines 306-350 */
static int NetWin_UserInit(struct _CWS_WIN_W *win);              /* 0x0022F430-0x0022F764 lines 242-303 */
int NetWin_User(struct _CWS_WIN_W *win);                         /* 0x0022F770-0x0022F7D8 lines 231-237 */

#endif /* DDR_UNIT_src_network_net_window_net_win_user_c_H */
