/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_main.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x00224270-0x0022457C
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
#ifndef DDR_UNIT_src_network_net_sys_net_sys_main_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_main_c_H

#include "types/_NETWORK_W.h"
#include "types/g_game_w.h"

/* anonymous types (1) */

/* anon_2_77 -- @anon2, 0x18 bytes, net_sys_main.c (DIE 0x14E195) */
typedef struct {   // size 0x18
    /* 0x000 */ void *func;                           // 0x4
    /* 0x004 */ int x;                                // 0x4
    /* 0x008 */ int y;                                // 0x4
    /* 0x00C */ int w;                                // 0x4
    /* 0x010 */ int h;                                // 0x4
    /* 0x014 */ int z;                                // 0x4
} anon_2_77;


/* variables (1) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (2) */
void NetSysRuleStartInit(struct _NETWORK_W *);                   /* @0x00228290 */
void NetSysTopInit(struct _NETWORK_W *);                         /* @0x00226600 */

/* functions defined (2) */
void NetSysEnd(struct _NETWORK_W *netw);                         /* 0x00224270-0x00224330 lines 150-183 */
void NetSysInit(struct _NETWORK_W *netw);                        /* 0x00224330-0x0022457C lines 14-146 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_main_c_H */
