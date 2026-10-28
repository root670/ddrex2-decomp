#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_CWS_WIN_W.h"

#define D_0102FB14 (*(int *)0x0102FB14)
#define D_0102FB18 (*(int *)0x0102FB18)
#define D_0102FB1C (*(int *)0x0102FB1C)
#define D_0102FB20 (*(int *)0x0102FB20)
#define D_0102FB24 ((int *)0x0102FB24)
#define D_0102FAC4 ((struct _CWS_WIN_W **)0x0102FAC4)
#define D_0102FAC8 (*(struct _CWS_WIN_W **)0x0102FAC8)
#define D_0102FACC (*(struct _CWS_WIN_W **)0x0102FACC)
#define D_0102FAD0 (*(struct _CWS_WIN_W **)0x0102FAD0)

extern struct _NS_NET_INFO_W *netiw;

void NetToLogout(struct _NETWORK_W *);
void NetSysUserInit2(struct _NETWORK_W *);
void NetGameInit(struct _NETWORK_W *);

void CwsStrAllDelete(struct _CWS_WIN_W *);
void NetWin_BaseSetName(struct _CWS_WIN_W *, unsigned char *);
unsigned char *NetReadDataGetStr(int);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char,
                  unsigned char, unsigned int, int, unsigned char,
                  unsigned char *, ...);
char CwsWinSetCode(struct _CWS_WIN_W *, char);
char CwsWinSetXY(struct _CWS_WIN_W *, int, int);
char CwsWinsAllGetStatus(int);
char CwsWinsAllDestroy(void);
void NetWin_SlbySetSelect(struct _CWS_WIN_W *, char);
void NetWin_SlbySetName(struct _CWS_WIN_W *, unsigned char *);
void NetWin_SlbySetNowNum(struct _CWS_WIN_W *, int);
void NetWin_SlbySetMaxNum(struct _CWS_WIN_W *, int);
void NetWin_BarSetH(struct _CWS_WIN_W *, int);
void NetWin_BarSetNow(struct _CWS_WIN_W *, int);
void NetWin_BarSetNum(struct _CWS_WIN_W *, int);
void NetWin_BarSetMax(struct _CWS_WIN_W *, int);
char NetInterErrGetStatus(void);
void NetInterErrClose(void);
void NetInterErrOpen(int);
void NetInterErrSet1Code(int, unsigned char *);
int NetPrgConnectAccountServer(int, int);
int NetPrgConnectLobbyServer(int, int);
int NetPrgSelectPlayerFile(int);
int NetPrgGetBlockList(int);
int NetPrgEntryBlock(int);
void func_007F5460(void *, int);
int func_007F8AE0(void *, int, int *);
void func_0010E748(char *, ...);
void func_0011EEC0(void *, int);
int func_0011E1D0(int);
int func_0011E1F0(int);

static void NetSysLobbySelectKey(struct _NETWORK_W *);
static void NetSysLobbyMain(struct _NETWORK_W *);

static void NetSysLobbyToAccountConnect(struct _NETWORK_W *netw) {
    int answer;

    switch (netw->step) {
    case 0:
        func_007F5460(netiw->d2uc, 2);
        netw->step++;
        break;
    case 1:
        answer = NetPrgConnectAccountServer(0, 1);
        if (answer == 1) {
            netw->NewFunc = NetSysUserInit2;
        } else if (answer < 0) {
            netw->NewFunc = NetToLogout;
        }
        break;
    }
}

static void NetSysLobbySelectKey(struct _NETWORK_W *netw) {
    if (!!(func_0011E1D0(0) & 0x1000) != 0
        || !!(func_0011E1D0(1) & 0x1000) != 0) {
        if (D_0102FB14 == 0) {
            D_0102FB18 = D_0102FB18 - 1 > 0 ? D_0102FB18 - 1 : 0;
        }
        D_0102FB14 = D_0102FB14 - 1 > 0 ? D_0102FB14 - 1 : 0;
    } else if (!!(func_0011E1D0(0) & 0x4000) != 0
               || !!(func_0011E1D0(1) & 0x4000) != 0) {
        if (D_0102FB14 == (D_0102FB20 < 3 ? D_0102FB20 : 3) - 1) {
            D_0102FB18 = D_0102FB18 + 1
                                 < D_0102FB20 - (D_0102FB20 < 3 ? D_0102FB20 : 3)
                             ? D_0102FB18 + 1
                             : D_0102FB20 - (D_0102FB20 < 3 ? D_0102FB20 : 3);
        }
        D_0102FB14 = D_0102FB14 + 1 < (D_0102FB20 < 3 ? D_0102FB20 : 3) - 1
                         ? D_0102FB14 + 1
                         : (D_0102FB20 < 3 ? D_0102FB20 : 3) - 1;
    }
    if (!!(func_0011E1F0(0) & 0x110) != 0
        || !!(func_0011E1F0(1) & 0x110) != 0) {
        netw->dc_code = 2;
    } else if (!!(func_0011E1F0(0) & 0x60) != 0
               || !!(func_0011E1F0(1) & 0x60) != 0) {
        netw->dc_code = 1;
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}

static void NetSysLobbyMain(struct _NETWORK_W *netw) {
    int i;
    int answer;

    switch (netw->step) {
    case 0:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysLobbySelectKey;
            netw->step++;
        }
        break;
    case 1:
        for (i = 0; i < (D_0102FB20 < 3 ? D_0102FB20 : 3); i++) {
            if (D_0102FB14 == i) {
                NetWin_SlbySetSelect(D_0102FAC4[i + 13], 1);
            } else {
                NetWin_SlbySetSelect(D_0102FAC4[i + 13], 0);
            }
            NetWin_SlbySetName(D_0102FAC4[i + 13],
                               (unsigned char *)netiw->d2uc->svrlist
                                   .entry[D_0102FB24[i + D_0102FB18]]
                                   .svname);
            NetWin_SlbySetNowNum(D_0102FAC4[i + 13],
                                 netiw->d2uc->svrlist.entry[D_0102FB24[i + D_0102FB18]].ucount);
            NetWin_SlbySetMaxNum(D_0102FAC4[i + 13], 0x3E8);
        }
        NetWin_BarSetNow(D_0102FACC, D_0102FB18);
        switch (netw->dc_code) {
        case 1:
            for (i = 0; i < (D_0102FB20 < 3 ? D_0102FB20 : 3); i++) {
                if (D_0102FB14 == i) {
                    D_0102FAC4[i + 13]->mode = 0;
                } else {
                    D_0102FAC4[i + 13]->mode = 3;
                }
                CwsWinSetCode(D_0102FAC4[i + 13], 2);
            }
            if ((D_0102FB20 < 3 ? D_0102FB20 : 3) < D_0102FB20) {
                CwsWinSetCode(D_0102FACC, 2);
            }
            CwsWinSetCode(D_0102FAD0, 2);
            D_0102FB1C = D_0102FB18 + D_0102FB14;
            netw->step = 2;
            break;
        case 2:
            for (i = 0; i < (D_0102FB20 < 3 ? D_0102FB20 : 3); i++) {
                CwsWinSetCode(D_0102FAC4[i + 13], 2);
            }
            if ((D_0102FB20 < 3 ? D_0102FB20 : 3) < D_0102FB20) {
                CwsWinSetCode(D_0102FACC, 2);
            }
            CwsWinSetCode(D_0102FAD0, 2);
            netw->step = 6;
            break;
        }
        break;
    case 2:
        answer = NetPrgConnectLobbyServer(0, D_0102FB24[D_0102FB1C]);
        if (answer == 1) {
            netw->step = 3;
        } else if (answer < 0) {
            netw->step = 9;
        }
        break;
    case 3:
        answer = NetPrgSelectPlayerFile(0);
        if (answer == 1) {
            netw->step = 4;
        } else if (answer < 0) {
            netw->step = 9;
        }
        break;
    case 4:
        answer = NetPrgGetBlockList(0);
        if (answer == 1) {
            netw->step = 5;
        } else if (answer < 0) {
            netw->step = 9;
        }
        break;
    case 5:
        answer = NetPrgEntryBlock(0);
        if (answer == 1) {
            netw->step = 7;
        } else if (answer < 0) {
            netw->step = 9;
        }
        break;
    case 6:
        if (CwsWinsAllGetStatus(0))
            netw->step = 8;
        break;
    case 7:
        if (CwsWinsAllDestroy())
            netw->step = 8;
        break;
    case 8:
        switch (netw->dc_code) {
        case 1:
            netw->NewFunc = NetGameInit;
            break;
        case 2:
            netw->NewFunc = NetSysLobbyToAccountConnect;
            break;
        }
        break;
    case 9:
        netw->NewFunc = NetToLogout;
    }
}

void NetSysLobbyInit(struct _NETWORK_W *netw) {
    int i;
    int answer;

    switch (netw->step) {
    case 0:
        netw->cursor = 0;
        func_0011EEC0(&D_0102FB14, 0x1A0);
        netiw->next_server = 0;
        netw->step++;
        break;
    case 1:
        answer = func_007F8AE0(netiw->d2uc, 2, &netiw->next_server);
        if (answer == -0x6E) {
            if (D_0102FB20 > 0) {
                netw->step = 2;
            } else {
                NetInterErrSet1Code(D_0102FB20, (unsigned char *)"no lobby proc");
                NetInterErrOpen(0);
                netw->step = 3;
            }
        } else if (answer < 0) {
            NetInterErrSet1Code(answer, (unsigned char *)__func__);
            NetInterErrOpen(0);
            netw->step = 3;
        } else if (D_0102FB20 + 1 < 0x64) {
            D_0102FB24[D_0102FB20] = answer;
            func_0010E748("found: num %d index %d\n", D_0102FB20, answer);
            D_0102FB20++;
        } else {
            netw->step = 2;
        }
        break;
    case 2:
        for (i = 0; i < (D_0102FB20 < 3 ? D_0102FB20 : 3); i++) {
            if (D_0102FB14 == i) {
                NetWin_SlbySetSelect(D_0102FAC4[i + 13], 1);
            } else {
                NetWin_SlbySetSelect(D_0102FAC4[i + 13], 0);
            }
            NetWin_SlbySetName(D_0102FAC4[i + 13],
                               (unsigned char *)netiw->d2uc->svrlist
                                   .entry[D_0102FB24[i + D_0102FB18]]
                                   .svname);
            NetWin_SlbySetNowNum(D_0102FAC4[i + 13],
                                 netiw->d2uc->svrlist.entry[D_0102FB24[i + D_0102FB18]].ucount);
            NetWin_SlbySetMaxNum(D_0102FAC4[i + 13], 0x3E8);
            D_0102FAC4[i + 13]->mode = 3;
            CwsWinSetCode(D_0102FAC4[i + 13], 1);
        }
        if ((D_0102FB20 < 3 ? D_0102FB20 : 3) < D_0102FB20) {
            D_0102FACC->mode = 0;
            CwsWinSetXY(D_0102FACC, -0xFA, -0x7C);
            NetWin_BarSetH(D_0102FACC, 0xC4);
            NetWin_BarSetMax(D_0102FACC, D_0102FB20);
            NetWin_BarSetNum(D_0102FACC, (D_0102FB20 < 3 ? D_0102FB20 : 3));
            NetWin_BarSetNow(D_0102FACC, D_0102FB18);
            D_0102FACC->mode = 0;
            CwsWinSetCode(D_0102FACC, 1);
        }
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0x16));
        CwsStrAllDelete(D_0102FAD0);
        CwsStrSetAll(D_0102FAD0, 0, -0x108, -0x29, 0x100, 0x80, 0x80, 0, 2, 0,
                     NetReadDataGetStr(0x27));
        CwsWinSetCode(D_0102FAD0, 1);
        netw->NewFunc = NetSysLobbyMain;
        break;
    case 3:
        if (NetInterErrGetStatus()) {
            if (!!(func_0011E1F0(0) & 0x170) != 0
                || !!(func_0011E1F0(1) & 0x170) != 0) {
                NetInterErrClose();
                netw->step = 4;
            }
        }
        break;
    case 4:
        if (NetInterErrGetStatus())
            netw->NewFunc = NetSysLobbyToAccountConnect;
        break;
    }
}
