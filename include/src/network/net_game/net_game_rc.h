/*
 * C:\work2\usaex2\src\network\net_game\net_game_rc.c
 * MW MIPS C Compiler, overlay main; 17 functions, code 0x0025C7B0-0x0025EDA4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_rc_c_H
#define DDR_UNIT_src_network_net_game_net_game_rc_c_H

#include "types/_NETWORK_W.h"
#include "types/_nsv_rc_table_param_work.h"

/* functions referenced (13) */
void NetGameMenuChangeTab(struct _NETWORK_W *);                  /* @0x001FABC0 */
void NetGameRCInit2(struct _NETWORK_W *);                        /* @0x0025DE50 */
void NetGameRCRankingKey(struct _NETWORK_W *);                   /* @0x0025C8C0 */
void NetGameRCRankingMain(struct _NETWORK_W *);                  /* @0x0025CBB0 */
void NetGameRCRankingInit(struct _NETWORK_W *);                  /* @0x0025CF70 */
void NetGameChallengeInit(struct _NETWORK_W *);                  /* @0x0025F2C0 */
void NetGameRCSelectKey(struct _NETWORK_W *);                    /* @0x0025D390 */
void NetGameRCSelectMain(struct _NETWORK_W *);                   /* @0x0025D610 */
void NetGameRCStepout(struct _NETWORK_W *);                      /* @0x0025DF10 */
void NetGameRCSelectInit(struct _NETWORK_W *);                   /* @0x0025D8F0 */
void NetGameRCKey(struct _NETWORK_W *);                          /* @0x0025D9B0 */
void NetGameRCMain(struct _NETWORK_W *);                         /* @0x0025DC90 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */

/* functions defined (17) */
static void NetGameRCSetNM(struct _nsv_rc_table_param_work *rc_data); /* 0x0025C7B0-0x0025C8BC lines 837-865 */
static void NetGameRCRankingKey(struct _NETWORK_W *netw);        /* 0x0025C8C0-0x0025CBB0 lines 793-828 */
static void NetGameRCRankingMain(struct _NETWORK_W *netw);       /* 0x0025CBB0-0x0025CF70 lines 703-787 */
static void NetGameRCRankingInit(struct _NETWORK_W *netw);       /* 0x0025CF70-0x0025D388 lines 586-701 */
static void NetGameRCSelectKey(struct _NETWORK_W *netw);         /* 0x0025D390-0x0025D610 lines 546-578 */
static void NetGameRCSelectMain(struct _NETWORK_W *netw);        /* 0x0025D610-0x0025D8E8 lines 474-540 */
static void NetGameRCSelectInit(struct _NETWORK_W *netw);        /* 0x0025D8F0-0x0025D9A4 lines 455-472 */
static void NetGameRCKey(struct _NETWORK_W *netw);               /* 0x0025D9B0-0x0025DC88 lines 415-448 */
static void NetGameRCMain(struct _NETWORK_W *netw);              /* 0x0025DC90-0x0025DE48 lines 361-409 */
void NetGameRCInit2(struct _NETWORK_W *netw);                    /* 0x0025DE50-0x0025DF0C lines 342-356 */
void NetGameRCStepout(struct _NETWORK_W *netw);                  /* 0x0025DF10-0x0025E030 lines 332-336 */
void NetGameRCStepin(struct _NETWORK_W *netw);                   /* 0x0025E030-0x0025E0C0 lines 316-330 */
void NetGameRCExCursorOn(struct _NETWORK_W *netw);               /* 0x0025E0C0-0x0025E2F4 lines 271-310 */
void NetGameRCExCursorOff(struct _NETWORK_W *netw);              /* 0x0025E300-0x0025E404 lines 252-269 */
void NetGameRCExClose(struct _NETWORK_W *netw);                  /* 0x0025E410-0x0025E674 lines 215-246 */
void NetGameRCExOpen(struct _NETWORK_W *netw);                   /* 0x0025E680-0x0025E81C lines 176-213 */
void NetGameRCInit(struct _NETWORK_W *netw);                     /* 0x0025E820-0x0025EDA4 lines 73-170 */

#endif /* DDR_UNIT_src_network_net_game_net_game_rc_c_H */
