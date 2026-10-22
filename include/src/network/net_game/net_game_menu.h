/*
 * C:\work2\usaex2\src\network\net_game\net_game_menu.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001FABC0-0x001FB61C
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
#ifndef DDR_UNIT_src_network_net_game_net_game_menu_c_H
#define DDR_UNIT_src_network_net_game_net_game_menu_c_H

#include "types/G_SYS_W_.h"
#include "types/_NETWORK_W.h"

/* variables (6) */
static void (*NetGameMenuTabOpen[6])(struct _NETWORK_W *);       /* @0x002B9600 size 0x18 */
static void (*NetGameMenuTabClose[6])(struct _NETWORK_W *);      /* @0x002B9620 size 0x18 */
static void (*NetGameMenuTabCursorOff[6])(struct _NETWORK_W *);  /* @0x002B9640 size 0x18 */
static void *NetGameMenuTabStepin[6];                            /* @0x002B9660 size 0x18 */
static void *NetGameMenuTabStepout[6];                           /* not allocated size 0x18 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */

/* functions referenced (3) */
void NetGameListInit(struct _NETWORK_W *);                       /* @0x00202140 */
void NetGameMenuSelectKey(struct _NETWORK_W *);                  /* @0x001FAE20 */
void NetGameMenuSelect(struct _NETWORK_W *);                     /* @0x001FAFC0 */

/* functions defined (5) */
void NetGameMenuChangeTab(struct _NETWORK_W *netw);              /* 0x001FABC0-0x001FAE1C lines 339-394 */
static void NetGameMenuSelectKey(struct _NETWORK_W *netw);       /* 0x001FAE20-0x001FAFC0 lines 294-316 */
static void NetGameMenuSelect(struct _NETWORK_W *netw);          /* 0x001FAFC0-0x001FB278 lines 224-288 */
void NetGameMenuInit2(struct _NETWORK_W *netw);                  /* 0x001FB280-0x001FB354 lines 202-217 */
void NetGameMenuInit(struct _NETWORK_W *netw);                   /* 0x001FB360-0x001FB61C lines 134-199 */

#endif /* DDR_UNIT_src_network_net_game_net_game_menu_c_H */
