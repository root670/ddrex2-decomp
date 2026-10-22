/*
 * C:\work2\usaex2\src\common\cws\multi_window.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00209E20-0x0020A1E4
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
#ifndef DDR_UNIT_src_common_cws_multi_window_c_H
#define DDR_UNIT_src_common_cws_multi_window_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_MULTI_WIN_W.h"

/* functions referenced (2) */
int CwsWin_Multi2(struct _CWS_WIN_W *);                          /* @0x00240FB0 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */

/* functions defined (9) */
void MultiWindowSetCautionMark(int win_num, int mark);           /* 0x00209E20-0x00209F3C lines 275-288 */
void MultiWindowSetMode(int win_num, int mode);                  /* 0x00209F40-0x00209F58 lines 269-270 */
void MultiWindowClose(int win_num);                              /* 0x00209F60-0x00209F78 lines 262-262 */
void MultiWindowOpen(int win_num);                               /* 0x00209F80-0x00209F98 lines 255-255 */
void MultiWindowDelete(int win_num);                             /* 0x00209FA0-0x00209FD8 lines 246-250 */
struct _MULTI_WIN_W *MultiWindowCreate(int win_num, int x, int y, int w, int h, int z, int tex_num); /* 0x00209FE0-0x0020A168 lines 215-243 */
void MultiWindowDestroy(void);                                   /* 0x0020A170-0x0020A19C lines 207-211 */
void MultiWindowCommon(void);                                    /* 0x0020A1A0-0x0020A1A8 lines 203-203 */
void MultiWindowInit(void);                                      /* 0x0020A1B0-0x0020A1E4 lines 190-199 */

#endif /* DDR_UNIT_src_common_cws_multi_window_c_H */
