#include "types/_CWS_WIN_W.h"
#include "types/_NET_READ_DATA_W.h"
#include "types/_NSV_DATA.h"
#include "types/_NSV_PLAYER_LIST.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_playerdata.h"
#include "types/g_game_w.h"
#include "types/_net_inter_w.h"
#include "types/_net_pack_w.h"
#include "types/_net_pad_w.h"
#include "types/_net_prg_w.h"
#include "types/_nsv_rc_table_list_work.h"
#include "types/_nsv_rc_table_param_work.h"
#include "types/sceNetcnfifData.h"

struct _NETWORK_W {
    int counter;
    unsigned int status;
    unsigned char *free_data_addr;
    int step;
    int dc_code;
    int cursor;
    void (*NewFunc)();
    void (*SubFunc)();
    void (*MainFunc)();
    void (*OldFunc)();
    void (*KeyFunc)();
    void (*OldKeyFunc)();
    struct _net_pad_w padw;
    struct _NET_READ_DATA_W readw;
    struct _net_prg_w prgw;
    struct _net_inter_w interw;
    int sel_user_file_num;
    struct _NSV_USER_FILE_WORK *dur_user_file;
    struct _NSV_USER_FILE_WORK UserFile[2];
    struct _NSV_PLAYER_LIST *player_list;
    struct _NSV_DATA ServerData;
    struct _nsv_rc_table_param_work RcData[2];
    struct _nsv_rc_table_list_work RcDataTbl;
    struct _nsv_rc_table_param_work *dur_rc_data;
    int work[320];
    char work_set_mode;
    struct _net_pack_w pack;
    struct sceNetcnfifData netcnfdata;
    unsigned int *net_cnf_addr;
    int net_loaded_flag;
    int upnp_loaded_flag;
    int bsdsocki_irx_mid;
    int bsdsocki_irx_result;
    int bsdsocki_irx_flag;
    int mc_init_flag;
} __attribute__((aligned(64)));

typedef struct {
    void *func;
    int x;
    int y;
    int w;
    int h;
    int z;
} anon_10_48;

extern struct _NS_NET_INFO_W *netiw;
struct g_game_w g_game_w;

/* g_game_w.last_data_addr (0x006B2F58) as the int CwsWinsCreate() returns.  The volatile
 * keeps the read below from being rematerialised behind the call, and the member access --
 * not an address literal -- is what names g_game_w in this unit's DWARF reference list. */
#define NET_GAME_LAST_DATA (*(volatile int *)&g_game_w.last_data_addr)
#define D_01029C88 (*(int *)0x01029C88)
#define D_01029FE4 (*(unsigned char **)0x01029FE4)
#define D_0102BDAC (*(int *)0x0102BDAC)
#define D_0102BDB0 (*(int *)0x0102BDB0)
#define D_0102BDB8 (*(unsigned char *)0x0102BDB8)
#define D_0102BDB9 (*(unsigned char *)0x0102BDB9)
#define D_0102FAC4 ((struct _CWS_WIN_W **)0x0102FAC4)
#define D_0102FE1C (*(int *)0x0102FE1C)
#define D_0102FF68 (*(unsigned char **)0x0102FF68)
#define D_0102FF6C (*(unsigned char **)0x0102FF6C)
#define D_0102FF70 (*(unsigned char **)0x0102FF70)
#define D_0102FF74 (*(unsigned char **)0x0102FF74)
#define D_0102FF78 ((unsigned char *)0x0102FF78)
#define D_0102FFC8 (*(unsigned char **)0x0102FFC8)
#define D_0102FFCC (*(int *)0x0102FFCC)
#define D_0102FFD0 ((int *)0x0102FFD0)

static short svr_tbl_minfo_num[75] = {
    24, 27, 28, 31, 32, 34, 40, 41, 45, 73, 74, 49, 55, 57, 58, 51, 46, 38, 36, 47,
    59, 56, 52, 43, 42, 44, 25, 26, 29, 30, 33, 35, 37, 39, 48, 50, 53, 54, 60, 61,
    62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 11, 14, 0, 6, 12, 21, 3, 5, 13,
    4, 8, 2, 17, 10, 1, 9, 22, 19, 20, 23, 16, 18, 7, 15
};

struct _CWS_WIN_W *CwsWinCreate(void *, int, int, int, int, int);
unsigned int CwsWinsCreate(unsigned int, int);
void CwsWinsDelete(void);
void NetInterErrInit(void);
int NetReadData(struct _NETWORK_W *, int);
int NetPrgGetSchedule(int);
int NetPrgGetRuleMask(int);
int NetPrgGetPlayerInfo(int, unsigned int);
int NetPrgGetPlayerOption(int, unsigned int);
int NetPrgGetRCInfo(int, unsigned char, unsigned char, struct _nsv_rc_table_param_work *);
int NetPrgGetRCTrycount(int);
int NetPrgSetMyAddr(int);
void func_0011EEC0(void *, int);
void *func_001BBBF8(void *, void *, unsigned int);
void func_001BCFA8(char *, ...);
void NetGameHelpDisp(void);
void NetGameWinInterVSMain(struct _NETWORK_W *);
void NetSysInit(struct _NETWORK_W *);
void NetGameMenuInit(struct _NETWORK_W *);
void NetToLogout(struct _NETWORK_W *);
int CwsWin_Multi(struct _CWS_WIN_W *);
int CwsWin_Multi2(struct _CWS_WIN_W *);
int NetWin_Watch(struct _CWS_WIN_W *);
int NetWin_Search(struct _CWS_WIN_W *);
int NetWin_Tab(struct _CWS_WIN_W *);
int NetWin_Any(struct _CWS_WIN_W *);
int NetWin_User(struct _CWS_WIN_W *);
int NetWin_Item(struct _CWS_WIN_W *);
int NetWin_Rcname(struct _CWS_WIN_W *);
int NetWin_Rccssel(struct _CWS_WIN_W *);
int NetWin_Infoboard(struct _CWS_WIN_W *);
int NetWin_Infosel(struct _CWS_WIN_W *);
int NetWin_Bar(struct _CWS_WIN_W *);
int NetWin_Listbk(struct _CWS_WIN_W *);
int NetWin_Listsel(struct _CWS_WIN_W *);
int NetWin_VSWin(struct _CWS_WIN_W *);

int NetGameGetMusicNum(int num) {
    if (num >= 0)
        return svr_tbl_minfo_num[num];
    return -1;
}

void NetGameReverseMenu(struct _NETWORK_W *netw) {
    if (D_0102FE1C == 1 && netiw->rtn_proc_mes == 0x44B0) {
        netw->NewFunc = NetGameWinInterVSMain;
        netw->SubFunc = 0;
    }
    NetGameHelpDisp();
}

void NetGameEnd(struct _NETWORK_W *netw) {
    D_0102FFCC = 0;
    func_0011EEC0(D_0102FFD0, 0x18);
    CwsWinsDelete();
    netw->SubFunc = 0;
    netw->NewFunc = NetSysInit;
}

/* Retail's types CU carries a declaration record for NetGameEnd -- a global_variable whose
 * type is a subroutine_type taking struct _NETWORK_W * -- that no function CU's reference
 * list names, so the unit's own code never refers to it.  An uncalled static that takes the
 * function's address makes the compiler record the declaration; the static has no code of
 * its own, so .text is unchanged. */
static void *unused_function_decl(void) { return (void *)NetGameEnd; }

static __inline void *NetGameGetWork(int size) {
    unsigned char *p;
    unsigned char *r;

    r = 0;
    p = D_0102FFC8;
    if (p != 0 && D_0102FFCC < 0xC) {
        D_0102FFC8 = p + size;
        r = p;
        D_0102FFD0[D_0102FFCC] = size;
        D_0102FFCC++;
        func_0011EEC0(p, size);
    }
    return r;
}

void NetGameInit(struct _NETWORK_W *netw) {
    int i;
    int rec;
    struct _ddrnet_playerdata *src;

    switch (netw->step) {
    case 0:
        D_0102FFCC = 0;
        func_0011EEC0(D_0102FFD0, 0x18);
        if (netw->work_set_mode != 2) {
            func_0011EEC0(D_0102FAC4, 0x4BC);
            netw->work_set_mode = 2;
        } else {
            func_0011EEC0(D_0102FF78, 6);
        }
        CwsWinsDelete();
        netw->step++;
        return;
    case 1:
        NET_GAME_LAST_DATA = CwsWinsCreate(D_01029C88, 1);
        rec = NET_GAME_LAST_DATA;
        func_0011EEC0(&D_0102FFC8, 0x38);
        D_0102FFC8 = (unsigned char *)((rec + 0x3F) & ~0x3F);
        NetInterErrInit();
        {
            anon_10_48 set_w[82] = {
                { CwsWin_Multi, 0, 0, 0, 0, 61440 },
                { CwsWin_Multi2, 0, 0, 0, 0, 61440 },
                { CwsWin_Multi2, 0, 139, 576, 96, 34304 },
                { NetWin_Watch, -117, -214, 0, 0, 32768 },
                { NetWin_Search, 166, -208, 0, 0, 37376 },
                { NetWin_Tab, -320, -170, 0, 0, 33280 },
                { NetWin_Any, 238, -170, 75, 36, 33280 },
                { NetWin_User, -320, 76, 0, 0, 17920 },
                { NetWin_Item, 58, -96, 0, 0, 16896 },
                { NetWin_Item, 58, -60, 0, 0, 16896 },
                { NetWin_Any, -320, -129, 640, 317, 17408 },
                { CwsWin_Multi, 0, -36, 340, 132, 18432 },
                { NetWin_Rcname, -264, -100, 0, 0, 18944 },
                { NetWin_Rcname, -264, -6, 0, 0, 18944 },
                { NetWin_Rccssel, -6, -124, 0, 0, 19456 },
                { CwsWin_Multi, 0, -36, 340, 132, 20480 },
                { CwsWin_Multi, 0, 144, 576, 76, 19968 },
                { NetWin_Infoboard, -286, -120, 0, 0, 20992 },
                { NetWin_Infosel, -260, -85, 0, 0, 21504 },
                { NetWin_Infosel, -260, -58, 0, 0, 21504 },
                { NetWin_Infosel, -260, -31, 0, 0, 21504 },
                { NetWin_Infosel, -260, -4, 0, 0, 21504 },
                { NetWin_Infosel, -260, 23, 0, 0, 21504 },
                { NetWin_Infosel, -260, 50, 0, 0, 21504 },
                { NetWin_Infosel, -260, 77, 0, 0, 21504 },
                { NetWin_Infosel, -260, 104, 0, 0, 21504 },
                { NetWin_Infosel, -260, 131, 0, 0, 21504 },
                { NetWin_Infosel, -260, 158, 0, 0, 21504 },
                { NetWin_Item, 0, 0, 0, 0, 21504 },
                { NetWin_Bar, 0, 0, 0, 0, 21504 },
                { CwsWin_Multi, 0, 0, 340, 132, 22016 },
                { NetWin_Item, -130, -100, 0, 0, 22016 },
                { NetWin_Item, 6, 12, 0, 0, 22016 },
                { NetWin_Any, -320, -129, 640, 317, 22528 },
                { NetWin_Any, -320, -129, 640, 317, 23040 },
                { NetWin_Infoboard, -286, -120, 0, 0, 23552 },
                { NetWin_Bar, 0, 0, 0, 0, 0 },
                { NetWin_Item, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Any, 0, 0, 0, 0, 0 },
                { NetWin_Item, 58, -96, 0, 0, 28160 },
                { NetWin_Item, 58, -62, 0, 0, 28160 },
                { NetWin_Item, 58, -28, 0, 0, 28160 },
                { NetWin_Item, 58, 6, 0, 0, 28160 },
                { NetWin_Item, 58, 40, 0, 0, 28160 },
                { NetWin_Item, 58, 74, 0, 0, 28160 },
                { NetWin_Item, 58, 108, 0, 0, 28160 },
                { NetWin_Any, -320, -129, 640, 317, 28672 },
                { CwsWin_Multi, 0, 0, 280, 164, 38400 },
                { NetWin_Listbk, 0, 0, 0, 0, 34816 },
                { NetWin_Bar, 0, 0, 0, 0, 35328 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Listsel, 0, 0, 0, 0, 35840 },
                { NetWin_Any, 0, 0, 0, 0, 33792 },
                { NetWin_VSWin, -320, -224, 0, 0, 37888 },
                { NetWin_Any, -320, -224, 640, 424, 37888 }
            };

            for (i = 0; i < 0x52; i++) {
                D_0102FAC4[i] = CwsWinCreate(set_w[i].func, set_w[i].x, set_w[i].y, set_w[i].w,
                                             set_w[i].h, set_w[i].z);
                D_0102FAC4[i]->mode = 1;
            }
            netw->step++;
            return;
        }
    case 2:
        if (NetReadData(netw, 3) == 1) {
            netw->step++;
            return;
        }
        break;
    case 3:
        rec = NetPrgGetSchedule(0);
        if (rec == 1) {
            D_0102BDAC = netiw->d2uc->rc_cur_time;
            D_0102BDB0 = netiw->d2uc->rc_term;
            D_0102BDB8 = netiw->d2uc->rc_cur_week;
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 4:
        rec = NetPrgGetRuleMask(0);
        if (rec == 1) {
            D_0102BDB9 = 0;
            if (netiw->d2uc->rule_mask.score == 0)
                D_0102BDB9 |= 1;
            if (netiw->d2uc->rule_mask.combo == 0)
                D_0102BDB9 |= 2;
            if (netiw->d2uc->rule_mask.survival == 0)
                D_0102BDB9 |= 4;
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 5:
        rec = NetPrgGetPlayerInfo(0, *(unsigned int *)D_01029FE4);
        if (rec == 1) {
            src = &netiw->d2uc->select_pldata;
            *(int *)(D_01029FE4 + 0x20) = src->playtime;
            *(int *)(D_01029FE4 + 0x24) = src->login_count;
            *(int *)(D_01029FE4 + 0x28) = src->disconnect;
            *(int *)(D_01029FE4 + 0x30) = src->total_rank;
            *(int *)(D_01029FE4 + 0x34) = src->total_rank_last;
            *(int *)(D_01029FE4 + 0x38) = src->match[0].match;
            *(int *)(D_01029FE4 + 0x3C) = src->match[0].win;
            *(int *)(D_01029FE4 + 0x40) = src->match[0].lose;
            *(int *)(D_01029FE4 + 0x44) = src->match[0].draw;
            *(int *)(D_01029FE4 + 0x48) = src->match[1].match;
            *(int *)(D_01029FE4 + 0x4C) = src->match[1].win;
            *(int *)(D_01029FE4 + 0x50) = src->match[1].lose;
            *(int *)(D_01029FE4 + 0x54) = src->match[1].draw;
            *(int *)(D_01029FE4 + 0x58) = src->match[2].match;
            *(int *)(D_01029FE4 + 0x5C) = src->match[2].win;
            *(int *)(D_01029FE4 + 0x60) = src->match[2].lose;
            *(int *)(D_01029FE4 + 0x64) = src->match[2].draw;
            *(int *)(D_01029FE4 + 0x68) = src->match[3].match;
            *(int *)(D_01029FE4 + 0x6C) = src->match[3].win;
            *(int *)(D_01029FE4 + 0x70) = src->match[3].lose;
            *(int *)(D_01029FE4 + 0x74) = src->match[3].draw;
            *(int *)(D_01029FE4 + 0x78) = src->rank_thisweek;
            *(int *)(D_01029FE4 + 0x7C) = src->rank_lastweek;
            *(unsigned short *)(D_01029FE4 + 0x80) = src->match_thisweek;
            *(unsigned short *)(D_01029FE4 + 0x82) = src->win_thisweek;
            *(unsigned short *)(D_01029FE4 + 0x84) = src->lose_thisweek;
            *(unsigned short *)(D_01029FE4 + 0x86) = src->draw_thisweek;
            *(int *)(D_01029FE4 + 0x35C) = src->total_point_rank;
            *(int *)(D_01029FE4 + 0x360) = src->point_rank_thisweek;
            *(int *)(D_01029FE4 + 0x364) = src->point_rank_lastweek;
            *(int *)(D_01029FE4 + 0x368) = src->point_rank_thisweek;
            *(int *)(D_01029FE4 + 0x36C) = src->point_rank_lastweek;
            *(int *)(D_01029FE4 + 0x370) = src->point_thisweek;
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 6:
        netiw->my_udp_port = 0xC58D;
        if (*(int *)(D_01029FE4 + 0x20) == 0 && (netw->status & 8) == 0) {
            *(int *)(D_01029FE4 + 0xEC0) &= ~1;
            *(int *)(D_01029FE4 + 0xEC0) |= 2;
            *(int *)(D_01029FE4 + 0xEC0) &= ~4;
            *(int *)(D_01029FE4 + 0xEC0) &= ~8;
            *(int *)(D_01029FE4 + 0xEC0) &= ~0x10;
            *(int *)(D_01029FE4 + 0xEC0) |= 0x20;
            netw->status |= 8;
            netw->step++;
            return;
        }
        rec = NetPrgGetPlayerOption(0, *(unsigned int *)D_01029FE4);
        if (rec == 1) {
            func_001BBBF8(D_01029FE4 + 0xEC0, netiw->d2uc->ploption, 0x20);
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 7:
        rec = NetPrgGetRCInfo(0, 0, 0, &netw->RcData[0]);
        if (rec == 1) {
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 8:
        rec = NetPrgGetRCInfo(0, 1, 0, &netw->RcData[1]);
        if (rec == 1) {
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 9:
        rec = NetPrgGetRCTrycount(0);
        if (rec == 1) {
            *(signed char *)(D_01029FE4 + 0x558) = netiw->d2uc->rc_trycnt[0];
            *(signed char *)(D_01029FE4 + 0x559) = netiw->d2uc->rc_trycnt[1];
            func_001BCFA8("RC A:%d B:%d\n", *(signed char *)(D_01029FE4 + 0x558),
                          *(signed char *)(D_01029FE4 + 0x559));
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 10:
        rec = NetPrgSetMyAddr(0);
        if (rec == 1) {
            netw->step++;
            return;
        }
        if (rec < 0) {
            netw->NewFunc = NetToLogout;
            return;
        }
        break;
    case 11:
        D_0102FF68 = NetGameGetWork(0x3D00);
        func_0011EEC0(D_0102FF68, 0x3CFC);
        D_0102FF6C = NetGameGetWork(0x2A40);
        func_0011EEC0(D_0102FF6C, 0x2A3C);
        D_0102FF70 = NetGameGetWork(0x1300);
        func_0011EEC0(D_0102FF70, 0x12C4);
        D_0102FF74 = NetGameGetWork(0x1300);
        func_0011EEC0(D_0102FF74, 0x12C4);
        netw->step++;
        return;
    case 12:
    default:
        netw->NewFunc = NetGameMenuInit;
        netw->SubFunc = NetGameReverseMenu;
        break;
    }
    }
