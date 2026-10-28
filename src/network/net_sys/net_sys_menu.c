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

#include "types/_NETWORK_W.h"
#include "types/_CWS_WIN_W.h"

#define D_0102FAC4 ((struct _CWS_WIN_W **)0x0102FAC4)
#define D_0102FAC8 (*(struct _CWS_WIN_W **)0x0102FAC8)
#define D_0102FAD0 (*(struct _CWS_WIN_W **)0x0102FAD0)
#define D_0102FAE0 (*(struct _CWS_WIN_W **)0x0102FAE0)
#define D_0102FAE4 (*(struct _CWS_WIN_W **)0x0102FAE4)
#define D_0102FAE8 (*(struct _CWS_WIN_W **)0x0102FAE8)
#define D_0102FCCC (*(int *)0x0102FCCC)

void NetSysLogoutInit(struct _NETWORK_W *);
void NetSysInfoInit(struct _NETWORK_W *);
void NetSysUserInit(struct _NETWORK_W *);

void CwsStrAllDelete(struct _CWS_WIN_W *);
void NetWin_MenuSetFont(struct _CWS_WIN_W *, int);
void NetWin_BaseSetName(struct _CWS_WIN_W *, unsigned char *);
unsigned char *NetReadDataGetStr(int);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char,
                  unsigned char, unsigned int, int, unsigned char,
                  unsigned char *, ...);
char CwsStrSetString(struct _CWS_WIN_W *, int, unsigned char *);
void NetWin_MenuSetSelect(struct _CWS_WIN_W *, int);
char CwsWinSetCode(struct _CWS_WIN_W *, char);
char CwsWinsAllGetStatus(int);
int func_0011E1D0(int);
int func_0011E1F0(int);

static void NetSysMenuMain(struct _NETWORK_W *);
static void NetSysMenuSelectKey(struct _NETWORK_W *);

void NetSysMenuInit(struct _NETWORK_W *netw) {
    int i;

    D_0102FCCC = 0;

    CwsStrAllDelete(D_0102FAD0);

    NetWin_MenuSetFont(D_0102FAE0, 3);
    NetWin_MenuSetFont(D_0102FAE4, 4);
    NetWin_MenuSetFont(D_0102FAE8, 5);

    NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xD));

    CwsStrSetAll(D_0102FAD0, 0, -0x108, -0x29, 0x100, 0x80, 0x80, 0, 2, 0,
                 NetReadDataGetStr(0x20));

    switch (D_0102FCCC) {

    case 0:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x10));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x20));
        break;
    case 1:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x11));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x21));
        break;
    case 2:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x14));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x22));
    }
    for (i = 0; i < 3; i++) {
        if (i == D_0102FCCC) {
            NetWin_MenuSetSelect(D_0102FAC4[i + 7], 1);
            D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xC4;
            D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xC4;
        } else {
            NetWin_MenuSetSelect(D_0102FAC4[i + 7], 0);
            D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xCE;
            D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xCE;
        }
        D_0102FAC4[i + 7]->mode = 3;
        CwsWinSetCode(D_0102FAC4[i + 7], 1);
    }

    CwsWinSetCode(D_0102FAD0, 1);

    netw->NewFunc = NetSysMenuMain;
}

void NetSysMenuInit2(struct _NETWORK_W *netw) {
    int i;

    CwsStrAllDelete(D_0102FAD0);

    NetWin_MenuSetFont(D_0102FAE0, 3);
    NetWin_MenuSetFont(D_0102FAE4, 4);
    NetWin_MenuSetFont(D_0102FAE8, 5);

    NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xD));

    CwsStrSetAll(D_0102FAD0, 0, -0x108, -0x29, 0x100, 0x80, 0x80, 0, 2, 0,
                 NetReadDataGetStr(0x20));

    switch (D_0102FCCC) {

    case 0:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x10));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x20));
        break;
    case 1:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x11));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x21));
        break;
    case 2:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x14));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x22));
    }
    for (i = 0; i < 3; i++) {
        if (i == D_0102FCCC) {
            NetWin_MenuSetSelect(D_0102FAC4[i + 7], 1);
            D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xC4;
            D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xC4;
        } else {
            NetWin_MenuSetSelect(D_0102FAC4[i + 7], 0);
            D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xCE;
            D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xCE;
        }
        D_0102FAC4[i + 7]->mode = 3;
        CwsWinSetCode(D_0102FAC4[i + 7], 1);
    }

    CwsWinSetCode(D_0102FAD0, 1);

    netw->NewFunc = NetSysMenuMain;
}

static void NetSysMenuMain(struct _NETWORK_W *netw) {
    int i;

    switch (netw->step) {

    case 0:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysMenuSelectKey;
            netw->step++;
        }
        break;
    case 1:
        for (i = 0; i < 3; i++) {
            if (i == D_0102FCCC) {
                NetWin_MenuSetSelect(D_0102FAC4[i + 7], 1);
                D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xC4;
                D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xC4;
            } else {
                NetWin_MenuSetSelect(D_0102FAC4[i + 7], 0);
                D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xCE;
            D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xCE;
            }
        }
        switch (D_0102FCCC) {

        case 0:
            NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x10));

            CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x20));
            break;
        case 1:
            NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x11));

            CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x21));
            break;
        case 2:
            NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x14));

            CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x22));
        }
        switch (netw->dc_code) {

        case 1:
            D_0102FAE0->mode = 0;
            D_0102FAE4->mode = 3;
            D_0102FAE8->mode = 3;
            CwsWinSetCode(D_0102FAE0, 2);
            CwsWinSetCode(D_0102FAE4, 2);
            CwsWinSetCode(D_0102FAE8, 2);
            CwsWinSetCode(D_0102FAD0, 2);
            netw->step = 2;
            break;
        case 2:
            D_0102FAE0->mode = 3;
            D_0102FAE8->mode = 3;
            CwsWinSetCode(D_0102FAE0, 2);
            CwsWinSetCode(D_0102FAE8, 2);
            CwsWinSetCode(D_0102FAD0, 2);
            netw->step = 3;
            break;
        case 3:
            D_0102FAE0->mode = 3;
            D_0102FAE4->mode = 3;
            CwsWinSetCode(D_0102FAE0, 2);
            CwsWinSetCode(D_0102FAE4, 2);
            CwsWinSetCode(D_0102FAD0, 2);
            netw->step = 3;
        }
        break;
    case 2:
        if (CwsWinsAllGetStatus(0))
            netw->step = 3;
        break;
    case 3:
        switch (netw->dc_code) {

        case 1:
            netw->NewFunc = NetSysUserInit;
            break;
        case 2:
            netw->NewFunc = NetSysInfoInit;
            break;
        case 3:
            netw->NewFunc = NetSysLogoutInit;
        }
        break;
    }
}

static void NetSysMenuSelectKey(struct _NETWORK_W *netw) {
    if (!!(func_0011E1D0(0) & 0x1000) != 0 || !!(func_0011E1D0(1) & 0x1000) != 0) {
        D_0102FCCC = (D_0102FCCC + 2) % 3;
    } else if (!!(func_0011E1D0(0) & 0x4000) != 0 || !!(func_0011E1D0(1) & 0x4000) != 0) {
        D_0102FCCC = (D_0102FCCC + 1) % 3;
    }
    if (!!(func_0011E1F0(0) & 0x110) != 0 || !!(func_0011E1F0(1) & 0x110) != 0) {
        netw->dc_code = 3;
    } else if (!!(func_0011E1F0(0) & 0x60) != 0 || !!(func_0011E1F0(1) & 0x60) != 0) {
        if (D_0102FCCC == 0)
            netw->dc_code = 1;
        else if (D_0102FCCC == 1)
            netw->dc_code = 2;
        else
            netw->dc_code = 3;
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}
