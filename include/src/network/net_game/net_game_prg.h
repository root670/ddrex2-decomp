/*
 * C:\work2\usaex2\src\network\net_game\net_game_prg.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00282930-0x00283390
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
#ifndef DDR_UNIT_src_network_net_game_net_game_prg_c_H
#define DDR_UNIT_src_network_net_game_net_game_prg_c_H

#include "types/_NET_WORK_DEAD_W.h"
#include "types/_NET_WORK_FLAG.h"
#include "types/_NET_WORK_OPT_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_result.h"
#include "types/eval_w.h"
#include "types/g_game_w.h"

/* variables (2) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions defined (5) */
int NetGamePrgGetWinLoseDraw(int pid);                           /* 0x00282930-0x0028294C lines 422-423 */
int NetGamePrgGetResult(int err_mode);                           /* 0x00282950-0x00282B6C lines 312-415 */
int NetGamePrgGetOption(int err_mode);                           /* 0x00282B70-0x00282DE8 lines 224-305 */
void NetGamePrgReverseMenu(void);                                /* 0x00282DF0-0x00283258 lines 75-218 */
static int NetGamePrgErrorFunc(int flag);                        /* 0x00283260-0x00283390 lines 26-67 */

#endif /* DDR_UNIT_src_network_net_game_net_game_prg_c_H */
