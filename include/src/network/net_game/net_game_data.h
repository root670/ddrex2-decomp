/*
 * C:\work2\usaex2\src\network\net_game\net_game_data.c
 * MW MIPS C Compiler, overlay main; 29 functions, code 0x001FCD20-0x00200B8C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_data_c_H
#define DDR_UNIT_src_network_net_game_net_game_data_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_nsv_ranking_htoh_param_w.h"
#include "types/_nsv_ranking_point_param_w.h"
#include "types/_nsv_rc_table_param_work.h"

/* functions referenced (35) */
int NetWin_PerPoint(struct _CWS_WIN_W *);                        /* @0x00286320 */
int NetWin_PerRank(struct _CWS_WIN_W *);                         /* @0x002866E0 */
int NetWin_PerHead(struct _CWS_WIN_W *);                         /* @0x00285D00 */
int NetWin_PerStats(struct _CWS_WIN_W *);                        /* @0x00286F20 */
void NetGameMenuChangeTab(struct _NETWORK_W *);                  /* @0x001FABC0 */
void NetGameDataInit2(struct _NETWORK_W *);                      /* @0x002006A0 */
void NetGameDataPersonalKey(struct _NETWORK_W *);                /* @0x001FD0B0 */
void NetGameDataPersonalMain(struct _NETWORK_W *);               /* @0x001FD2C0 */
int NetWin_PerUserPoint(struct _CWS_WIN_W *);                    /* @0x00285590 */
void NetGameDataPointKey(struct _NETWORK_W *);                   /* @0x001FD960 */
void NetGameDataPointMain(struct _NETWORK_W *);                  /* @0x001FDAA0 */
int NetWin_DPoint(struct _CWS_WIN_W *);                          /* @0x00287D80 */
void NetGameDataRCInit2(struct _NETWORK_W *);                    /* @0x001FF5A0 */
void NetGameDataRCListKey(struct _NETWORK_W *);                  /* @0x001FE020 */
void NetGameDataRCListMain(struct _NETWORK_W *);                 /* @0x001FE310 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */
int NetWin_Infosel(struct _CWS_WIN_W *);                         /* @0x002722C0 */
void NetGameRCInit2(struct _NETWORK_W *);                        /* @0x0025DE50 */
void NetGameDataRCListInit(struct _NETWORK_W *);                 /* @0x001FE5B0 */
void NetGameDataRCKey(struct _NETWORK_W *);                      /* @0x001FEC80 */
void NetGameDataRCMain(struct _NETWORK_W *);                     /* @0x001FF160 */
int NetWin_Bar(struct _CWS_WIN_W *);                             /* @0x002486C0 */
int NetWin_Item(struct _CWS_WIN_W *);                            /* @0x0022EE50 */
int NetWin_Rccssel(struct _CWS_WIN_W *);                         /* @0x002734B0 */
void NetGameDataHtoHKey(struct _NETWORK_W *);                    /* @0x001FFB90 */
void NetGameDataHtoHMain(struct _NETWORK_W *);                   /* @0x001FFCD0 */
int NetWin_DHead(struct _CWS_WIN_W *);                           /* @0x002879E0 */
void NetGameDataPersonalInit(struct _NETWORK_W *);               /* @0x001FD590 */
void NetGameDataPointInit(struct _NETWORK_W *);                  /* @0x001FDC90 */
void NetGameDataRCInit(struct _NETWORK_W *);                     /* @0x001FF690 */
void NetGameDataHtoHInit(struct _NETWORK_W *);                   /* @0x001FFEB0 */
void NetGameDataStepout(struct _NETWORK_W *);                    /* @0x00200700 */
void NetGameDataKey(struct _NETWORK_W *);                        /* @0x00200280 */
void NetGameDataMain(struct _NETWORK_W *);                       /* @0x002004B0 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */

/* functions defined (29) */
static void NetGameDataPersonalDataClose(int id, int dir);       /* 0x001FCD20-0x001FCF20 lines 1927-1993 */
static void NetGameDataPersonalDataSet(int id, int dir);         /* 0x001FCF20-0x001FD0A8 lines 1830-1924 */
static void NetGameDataPersonalKey(struct _NETWORK_W *netw);     /* 0x001FD0B0-0x001FD2B8 lines 1790-1823 */
static void NetGameDataPersonalMain(struct _NETWORK_W *netw);    /* 0x001FD2C0-0x001FD590 lines 1666-1784 */
static void NetGameDataPersonalInit(struct _NETWORK_W *netw);    /* 0x001FD590-0x001FD960 lines 1531-1664 */
static void NetGameDataPointKey(struct _NETWORK_W *netw);        /* 0x001FD960-0x001FDA98 lines 1498-1523 */
static void NetGameDataPointMain(struct _NETWORK_W *netw);       /* 0x001FDAA0-0x001FDC90 lines 1428-1492 */
static void NetGameDataPointInit(struct _NETWORK_W *netw);       /* 0x001FDC90-0x001FE014 lines 1314-1426 */
static void NetGameDataRCListKey(struct _NETWORK_W *netw);       /* 0x001FE020-0x001FE310 lines 1271-1306 */
static void NetGameDataRCListMain(struct _NETWORK_W *netw);      /* 0x001FE310-0x001FE5B0 lines 1192-1265 */
static void NetGameDataRCListInit(struct _NETWORK_W *netw);      /* 0x001FE5B0-0x001FEB68 lines 1067-1190 */
static void NetGameDataRCSetNM(struct _nsv_rc_table_param_work *rc_data); /* 0x001FEB70-0x001FEC7C lines 1021-1050 */
static void NetGameDataRCKey(struct _NETWORK_W *netw);           /* 0x001FEC80-0x001FF158 lines 960-1016 */
static void NetGameDataRCMain(struct _NETWORK_W *netw);          /* 0x001FF160-0x001FF598 lines 856-954 */
static void NetGameDataRCInit2(struct _NETWORK_W *netw);         /* 0x001FF5A0-0x001FF68C lines 838-854 */
static void NetGameDataRCInit(struct _NETWORK_W *netw);          /* 0x001FF690-0x001FFB90 lines 714-836 */
static void NetGameDataHtoHKey(struct _NETWORK_W *netw);         /* 0x001FFB90-0x001FFCC8 lines 681-706 */
static void NetGameDataHtoHMain(struct _NETWORK_W *netw);        /* 0x001FFCD0-0x001FFEB0 lines 610-675 */
static void NetGameDataHtoHInit(struct _NETWORK_W *netw);        /* 0x001FFEB0-0x0020027C lines 486-608 */
static void NetGameDataKey(struct _NETWORK_W *netw);             /* 0x00200280-0x002004B0 lines 454-478 */
static void NetGameDataMain(struct _NETWORK_W *netw);            /* 0x002004B0-0x002006A0 lines 379-448 */
static void NetGameDataInit2(struct _NETWORK_W *netw);           /* 0x002006A0-0x002006F8 lines 371-377 */
void NetGameDataStepout(struct _NETWORK_W *netw);                /* 0x00200700-0x00200778 lines 361-365 */
void NetGameDataStepin(struct _NETWORK_W *netw);                 /* 0x00200780-0x00200840 lines 336-359 */
void NetGameDataExCursorOn(struct _NETWORK_W *netw);             /* 0x00200840-0x00200A14 lines 295-329 */
void NetGameDataExCursorOff(void);                               /* 0x00200A20-0x00200A74 lines 283-291 */
void NetGameDataExClose(void);                                   /* 0x00200A80-0x00200A90 lines 275-275 */
void NetGameDataExOpen(void);                                    /* 0x00200A90-0x00200AA0 lines 271-271 */
void NetGameDataInit(void);                                      /* 0x00200AA0-0x00200B8C lines 247-264 */

#endif /* DDR_UNIT_src_network_net_game_net_game_data_c_H */
