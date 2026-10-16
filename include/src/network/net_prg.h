/*
 * C:\work2\usaex2\src\network\net_prg.c
 * MW MIPS C Compiler, overlay main; 38 functions, code 0x001EBE00-0x001F5F20
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_prg_c_H
#define DDR_UNIT_src_network_net_prg_c_H

#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_con.h"
#include "types/_ddrnet_result.h"
#include "types/_nsv_music_data_work.h"
#include "types/_nsv_ranking_htoh_list_work.h"
#include "types/_nsv_ranking_point_list_work.h"
#include "types/_nsv_ranking_rc_work.h"
#include "types/_nsv_rc_table_param_work.h"
#include "types/_tag_cNetAuth.h"
#include "types/ddrnet_rc_music.h"

/* anonymous types (6) */

/* anon_1_46 -- @anon1, 0x4 bytes, net_prg.c (DIE 0x88F6F) */
struct anon_1_46 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_2_46 -- @anon2, 0x4 bytes, net_prg.c (DIE 0x8977E) */
struct anon_2_46 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_0_46 -- @anon0, 0x4 bytes, net_prg.c (DIE 0x88EBF) */
union anon_0_46 {   // size 0x4
    /* 0x000 */ struct anon_1_46 S_un_b;              // 0x4
    /* 0x000 */ struct anon_2_46 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_3_46 -- @anon3, 0x10 bytes, net_prg.c (DIE 0x8C369) */
struct anon_3_46 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};

/* anon_4_46 -- @anon4, 0x1048 bytes, net_prg.c (DIE 0x8CB43) */
struct anon_4_46 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_5_46 -- @anon5, 0x8 bytes, net_prg.c (DIE 0x8D2C3) */
struct anon_5_46 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions defined (38) */
int NetPrgGetRCIdList(int err_mode);                             /* 0x001EBE00-0x001EC194 lines 5002-5108 */
int NetPrgGetSchedule(int err_mode);                             /* 0x001EC1A0-0x001EC534 lines 4889-4995 */
int NetPrgGetRuleMask(int err_mode);                             /* 0x001EC540-0x001EC8D4 lines 4774-4880 */
int NetPrgSetMyAddr(int err_mode);                               /* 0x001EC8E0-0x001ECD54 lines 4656-4766 */
int NetPrgGetRCRanking(int err_mode, short week, unsigned char sub, struct _nsv_ranking_rc_work *dest_addr); /* 0x001ECD60-0x001ED310 lines 4501-4648 */
int NetPrgGetPointRanking(int err_mode, short week, struct _nsv_ranking_point_list_work *dest_addr); /* 0x001ED310-0x001ED854 lines 4346-4486 */
int NetPrgGetHtoHRanking(int err_mode, short week, struct _nsv_ranking_htoh_list_work *dest_addr); /* 0x001ED860-0x001EDEE4 lines 4184-4334 */
int NetPrgGetPlyerRCLog(int err_mode);                           /* 0x001EDEF0-0x001EE494 lines 4036-4172 */
int NetPrgGetPlyerHtoHLog(int err_mode);                         /* 0x001EE4A0-0x001EE988 lines 3756-3888 */
int NetPrgGetRCRegist(int err_mode, int score, int time, short combo, short gauge); /* 0x001EE990-0x001EED4C lines 3643-3749 */
int NetPrgGetRCEntry(int err_mode, unsigned char type);          /* 0x001EED50-0x001EF0F4 lines 3529-3635 */
int NetPrgGetRCTrycount(int err_mode);                           /* 0x001EF100-0x001EF49C lines 3416-3522 */
int NetPrgGetRCInfo(int err_mode, unsigned char type, unsigned char week, struct _nsv_rc_table_param_work *rcw); /* 0x001EF4A0-0x001EF9F0 lines 3260-3409 */
int NetPrgConfiscate(int err_mode, char win, char disconnect);   /* 0x001EF9F0-0x001EFF54 lines 2973-3118 */
int NetPrgGetEndgame(int err_mode, struct _ddrnet_result *result); /* 0x001EFF60-0x001F041C lines 2839-2966 */
int NetPrgGetStartStaus(int err_mode, int status);               /* 0x001F0420-0x001F08E4 lines 2698-2831 */
int NetPrgGetRoomList(int err_mode);                             /* 0x001F08F0-0x001F0DF8 lines 2553-2690 */
int NetPrgOutRoom(int err_mode);                                 /* 0x001F0E00-0x001F1314 lines 2401-2545 */
int NetPrgCreateRoom(int err_mode, unsigned char rule, unsigned char difficulty); /* 0x001F1320-0x001F1784 lines 2269-2393 */
int NetPrgSavePlayerOption(int err_mode);                        /* 0x001F1790-0x001F1CA0 lines 2118-2262 */
int NetPrgGetPlayerOption(int err_mode, unsigned int pid);       /* 0x001F1CA0-0x001F2034 lines 2005-2111 */
int NetPrgGetPlayerInfo(int err_mode, unsigned int pid);         /* 0x001F2040-0x001F23D4 lines 1892-1998 */
int NetPrgGetPlayerList(int err_mode);                           /* 0x001F23E0-0x001F2834 lines 1743-1884 */
int NetPrgEntryBlock(int err_mode);                              /* 0x001F2840-0x001F2BD4 lines 1629-1735 */
int NetPrgGetBlockList(int err_mode);                            /* 0x001F2BE0-0x001F2F74 lines 1516-1622 */
int NetPrgSelectPlayerFile(int err_mode);                        /* 0x001F2F80-0x001F337C lines 1399-1508 */
int NetPrgDeletePlayerFile(int err_mode, int _num);              /* 0x001F3380-0x001F36FC lines 1291-1392 */
int NetPrgNewCreatePlayerFile(int err_mode, int _num, unsigned char *_name, char _dancer); /* 0x001F3700-0x001F3ADC lines 1165-1283 */
int NetPrgGetPlayerFileList(int err_mode);                       /* 0x001F3AE0-0x001F3E94 lines 1056-1157 */
int NetPrgConnectLobbyServer(int err_mode, int svr_index);       /* 0x001F3EA0-0x001F45A4 lines 840-1049 */
int NetPrgConnectAccountServer(int err_mode, int auto_auth);     /* 0x001F45B0-0x001F4D74 lines 586-829 */
int NetPrgSvrTime(int err_mode);                                 /* 0x001F4D80-0x001F50C4 lines 481-576 */
int NetPrgSvrList(int err_mode);                                 /* 0x001F50D0-0x001F55A8 lines 346-472 */
int NetPrgSvrInfo(int err_mode);                                 /* 0x001F55B0-0x001F58C4 lines 253-338 */
int NetPrgConnectGate(int err_mode);                             /* 0x001F58D0-0x001F5B38 lines 182-246 */
int NetPrgEtherStart(int err_mode);                              /* 0x001F5B40-0x001F5CBC lines 128-173 */
int NetPrgBsdsocketInit(int err_mode);                           /* 0x001F5CC0-0x001F5DEC lines 84-121 */
static int NetPrgErrorFunc(int flag);                            /* 0x001F5DF0-0x001F5F20 lines 36-77 */

#endif /* DDR_UNIT_src_network_net_prg_c_H */
