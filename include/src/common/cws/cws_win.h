/*
 * C:\work2\usaex2\src\common\cws\cws_win.c
 * MW MIPS C Compiler, overlay main; 17 functions, code 0x00206E50-0x00208150
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_common_cws_cws_win_c_H
#define DDR_UNIT_src_common_cws_cws_win_c_H

#include "types/_CWS_WINS_W.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (1) */

/* anon_0_63 -- @anon0, 0x8 bytes, cws_win.c (DIE 0xF3FDF) */
struct anon_0_63 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* functions defined (17) */
void CwsWinDestroy(struct _CWS_WIN_W *win);                      /* 0x00206E50-0x00206E5C lines 759-760 */
void CwsWinClose(struct _CWS_WIN_W *win);                        /* 0x00206E60-0x00207360 lines 537-754 */
void CwsWinOpen(struct _CWS_WIN_W *win);                         /* 0x00207360-0x00207860 lines 320-534 */
char cws_win_move_xywh(struct _CWS_WIN_W *work, int _end_time);  /* 0x00207860-0x00207C2C lines 261-315 */
char CwsWinDelete(struct _CWS_WIN_W *work);                      /* 0x00207C30-0x00207CD0 lines 226-241 */
char CwsWinMoveH(struct _CWS_WIN_W *work, unsigned int h, int flg); /* 0x00207CD0-0x00207D28 lines 213-223 */
char CwsWinMoveW(struct _CWS_WIN_W *work, unsigned int w, int flg); /* 0x00207D30-0x00207D88 lines 199-209 */
char CwsWinSetRGBA(struct _CWS_WIN_W *work, unsigned int rgba);  /* 0x00207D90-0x00207DD8 lines 146-154 */
char CwsWinSetBri(struct _CWS_WIN_W *work, int bri);             /* 0x00207DE0-0x00207E08 lines 137-142 */
char CwsWinSetPri(struct _CWS_WIN_W *work, int z);               /* 0x00207E10-0x00207E38 lines 128-133 */
char CwsWinSetWH(struct _CWS_WIN_W *work, int w, int h);         /* 0x00207E40-0x00207E70 lines 118-124 */
char CwsWinSetXY(struct _CWS_WIN_W *work, int x, int y);         /* 0x00207E70-0x00207EA0 lines 108-114 */
char CwsWinDefSetXYWH(struct _CWS_WIN_W *work, int x, int y, int w, int h); /* 0x00207EA0-0x00207ED0 lines 96-104 */
struct _CWS_WIN_W *CwsWinCreate(void *func, int x, int y, int w, int h, int z); /* 0x00207ED0-0x00208028 lines 50-79 */
void CwsWinReflash(struct _CWS_WIN_W *work);                     /* 0x00208030-0x00208070 lines 40-46 */
char CwsWinSetCode(struct _CWS_WIN_W *work, char _code);         /* 0x00208070-0x00208098 lines 30-36 */
unsigned int CwsWinGetStatus(struct _CWS_WIN_W *work);           /* 0x002080A0-0x00208150 lines 8-26 */

#endif /* DDR_UNIT_src_common_cws_cws_win_c_H */
