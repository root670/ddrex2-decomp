/*
 * C:\work2\usaex2\src\common\cws\cws_wins.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x00208150-0x002088BC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_common_cws_cws_wins_c_H
#define DDR_UNIT_src_common_cws_cws_wins_c_H

#include "types/_CWS_WINS_W.h"
#include "types/_CWS_WIN_W.h"

/* variables (3) */
struct _CWS_WINS_W *wins;                                        /* @0x002DDAE8 size 0x4 */
static int def_set_work_num[3][3];                               /* @0x002BB420 size 0x24 */
static struct _CWS_WINS_W _wins;                                 /* @0x0071DA80 size 0xA30 */

/* functions defined (7) */
char CwsWinsAllDestroy(void);                                    /* 0x00208150-0x00208208 lines 218-236 */
char CwsWinsAllGetStatus(int flag);                              /* 0x00208210-0x0020831C lines 195-214 */
struct _CWS_WINS_W *GetWinsAddr(void);                           /* 0x00208320-0x00208328 lines 190-190 */
void CwsWins_Func(void);                                         /* 0x00208330-0x0020869C lines 93-185 */
void CwsWinsDelete(void);                                        /* 0x002086A0-0x002086AC lines 85-85 */
unsigned int CwsWinsCreate(unsigned int _top_addr, int init_type); /* 0x002086B0-0x002088AC lines 33-77 */
void WinsInit(void);                                             /* 0x002088B0-0x002088BC lines 25-25 */

#endif /* DDR_UNIT_src_common_cws_cws_wins_c_H */
