#include "types/_CWS_WIN_W.h"
#include "types/_NET_READ_DATA_W.h"
#include "types/_NSV_DATA.h"
#include "types/_NSV_PLAYER_LIST.h"
#include "types/_NSV_USER_FILE_WORK.h"
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

int func_0011E1D0(int pid);
int func_0011E1F0(int pid);
char CwsWinsAllGetStatus(int flag);
char CwsStrSetCol(struct _CWS_WIN_W *win, int str_num, unsigned char col);
char CwsWinSetCode(struct _CWS_WIN_W *work, char _code);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri,
                  unsigned char bri, unsigned char alpha, unsigned int flag,
                  int type, unsigned char col, unsigned char *string, ...);
void NetWin_AnySetTexture(struct _CWS_WIN_W *win, int _tex_id, int _tu, int _tv, int _tw, int _th);
unsigned char *NetReadDataGetStr(int str_num);
int NsNetLogout(void);
void NetGameEnd(struct _NETWORK_W *netw);
void NetGameMenuInit2(struct _NETWORK_W *netw);
void NetGameLogoutStepout(struct _NETWORK_W *netw);
static void NetGameLogoutKey(struct _NETWORK_W *netw);
static void NetGameLogoutMain(struct _NETWORK_W *netw);

static void NetGameLogoutKey(struct _NETWORK_W *netw) {
    if (((func_0011E1D0(0) & 0x1000) ? 1 : 0) || ((func_0011E1D0(1) & 0x1000) ? 1 : 0)) {
        *(char *)0x0102FE88 = (*(char *)0x0102FE88 + 1) % 2;
    } else if (((func_0011E1D0(0) & 0x4000) ? 1 : 0) || ((func_0011E1D0(1) & 0x4000) ? 1 : 0)) {
        *(char *)0x0102FE88 = (*(char *)0x0102FE88 + 1) % 2;
    }
    if (((func_0011E1F0(0) & 0x110) ? 1 : 0) || ((func_0011E1F0(1) & 0x110) ? 1 : 0)) {
        netw->dc_code = 1;
    } else if (((func_0011E1F0(0) & 0x60) ? 1 : 0) || ((func_0011E1F0(1) & 0x60) ? 1 : 0)) {
        if (!*(char *)0x0102FE88)
            netw->dc_code = 2;
        else
            netw->dc_code = 1;
    }
    if (netw->dc_code)
        netw->KeyFunc = 0;
}

static void NetGameLogoutMain(struct _NETWORK_W *netw) {
    int i;

    switch (netw->step) {
    case 0:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetGameLogoutKey;
            netw->step = 1;
        }
        break;
    case 1:
        for (i = 0; i < 2; i++) {
            if (i == *(char *)0x0102FE88)
                CwsStrSetCol(*(struct _CWS_WIN_W **)0x0102FBCC, i + 1, 4);
            else
                CwsStrSetCol(*(struct _CWS_WIN_W **)0x0102FBCC, i + 1, 0);
        }
        switch (netw->dc_code) {
        case 1:
        case 2:
            (*(struct _CWS_WIN_W **)0x0102FBCC)->mode = 6;
            CwsWinSetCode(*(struct _CWS_WIN_W **)0x0102FBCC, 2);
            netw->step = 2;
            break;
        }
        break;
    case 2:
        if (CwsWinsAllGetStatus(0))
            netw->step = 3;
        break;
    case 3:
        switch (netw->dc_code) {
        case 1:
            netw->NewFunc = NetGameLogoutStepout;
            break;
        case 2:
            if (NsNetLogout())
                netw->NewFunc = NetGameEnd;
            break;
        }
        break;
    }
}

void NetGameLogoutStepout(struct _NETWORK_W *netw) {
    NetWin_AnySetTexture(*(struct _CWS_WIN_W **)0x0102FADC, 0x17, 0, 0xB4, 0x4B, 0x24);
    netw->NewFunc = NetGameMenuInit2;
}

void NetGameLogoutStepin(struct _NETWORK_W *netw) {
    int i;

    *(char *)0x0102FE88 = 1;
    for (i = 0; i < 2; i++) {
        if (i == *(char *)0x0102FE88)
            CwsStrSetCol(*(struct _CWS_WIN_W **)0x0102FBCC, i + 1, 4);
        else
            CwsStrSetCol(*(struct _CWS_WIN_W **)0x0102FBCC, i + 1, 0);
    }
    (*(struct _CWS_WIN_W **)0x0102FADC)->v.y = (*(struct _CWS_WIN_W **)0x0102FADC)->s.y = -0xAA;
    NetWin_AnySetTexture(*(struct _CWS_WIN_W **)0x0102FADC, 0x17, 0x4B, 0xB4, 0x4B, 0x24);
    (*(struct _CWS_WIN_W **)0x0102FBCC)->mode = 6;
    CwsWinSetCode(*(struct _CWS_WIN_W **)0x0102FBCC, 1);
    netw->NewFunc = NetGameLogoutMain;
}

void NetGameLogoutExCursorOff(void) {
}

void NetGameLogoutExClose(void) {
}

void NetGameLogoutExOpen(void) {
}

void NetGameLogoutInit(void) {
    CwsStrSetAll(*(struct _CWS_WIN_W **)0x0102FBCC, 0, 0, -0x3A, 0x100, 0x80, 0x80, 0x400, 2, 0, NetReadDataGetStr(0xA));
    CwsStrSetAll(*(struct _CWS_WIN_W **)0x0102FBCC, 1, -0x32, 0, 0x100, 0x80, 0x80, 0, 2, 1, NetReadDataGetStr(2));
    CwsStrSetAll(*(struct _CWS_WIN_W **)0x0102FBCC, 2, -0x32, 0x22, 0x100, 0x80, 0x80, 0, 2, 0, NetReadDataGetStr(3));
}
