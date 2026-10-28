#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_CWS_WIN_W.h"

#define D_0102FAC4 ((struct _CWS_WIN_W **)0x0102FAC4)
#define D_0102FAC8 (*(struct _CWS_WIN_W **)0x0102FAC8)
#define D_0102FAD0 (*(struct _CWS_WIN_W **)0x0102FAD0)
#define D_0102FAE0 (*(struct _CWS_WIN_W **)0x0102FAE0)
#define D_0102FAE4 (*(struct _CWS_WIN_W **)0x0102FAE4)
#define D_0102FAE8 (*(struct _CWS_WIN_W **)0x0102FAE8)
#define D_0102FCC8 (*(int *)0x0102FCC8)

extern struct _NS_NET_INFO_W *netiw;

void NetCnfMain(struct _NETWORK_W *);
void NetSysRuleInit(struct _NETWORK_W *);
void NetSysEnd(struct _NETWORK_W *);

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
char CwsWinsAllDestroy(void);
int func_0011E1D0(int);
int func_0011E1F0(int);
int func_0011E430(void);
void func_0011E440(int);
void func_00121270(int, unsigned char *, float, float, ...);
void *func_001BBBF8(void *, void *, unsigned int);

static void NetSysTopMain(struct _NETWORK_W *);
static void NetSysTopKey(struct _NETWORK_W *);

void NetSysTopInit(struct _NETWORK_W *netw) {
    int i;

    D_0102FCC8 = 0;

    CwsStrAllDelete(D_0102FAD0);

    NetWin_MenuSetFont(D_0102FAE0, 0);
    NetWin_MenuSetFont(D_0102FAE4, 1);
    NetWin_MenuSetFont(D_0102FAE8, 2);

    NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xD));

    CwsStrSetAll(D_0102FAD0, 0, -0x108, -0x29, 0x100, 0x80, 0x80, 0, 2, 0,
                 NetReadDataGetStr(0x1D));

    switch (D_0102FCC8) {
    case 0:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xD));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1D));
        break;
    case 1:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xE));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1E));
        break;
    case 2:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xF));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1F));
    }
    for (i = 0; i < 3; i++) {
        if (i == D_0102FCC8) {
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

    netw->NewFunc = NetSysTopMain;
}

void NetSysTopInit2(struct _NETWORK_W *netw) {
    int i;

    func_0011E440(func_0011E430() & ~0x100);

    CwsStrAllDelete(D_0102FAD0);

    CwsWinSetCode(D_0102FAD0, 1);

    NetWin_MenuSetFont(D_0102FAE0, 0);
    NetWin_MenuSetFont(D_0102FAE4, 1);
    NetWin_MenuSetFont(D_0102FAE8, 2);

    NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xD));

    CwsStrSetAll(D_0102FAD0, 0, -0x108, -0x29, 0x100, 0x80, 0x80, 0, 2, 0,
                 NetReadDataGetStr(0x1D));

    switch (D_0102FCC8) {
    case 0:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xD));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1D));
        break;
    case 1:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xE));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1E));
        break;
    case 2:
        NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xF));

        CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1F));
    }
    for (i = 0; i < 3; i++) {
        if (i == D_0102FCC8) {
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

    netw->NewFunc = NetSysTopMain;
}

static void NetSysTopMain(struct _NETWORK_W *netw) {
    unsigned char *svr_name[4] = {(unsigned char *)"OLC:abjure",
                                  (unsigned char *)"R&D:freddy",
                                  (unsigned char *)"OLC:Internet",
                                  (unsigned char *)"OPEN INTERNET"};
    unsigned char *svr_ip[4] = {(unsigned char *)"10.190.20.149",
                                (unsigned char *)"10.190.49.82",
                                (unsigned char *)"220.151.173.211",
                                (unsigned char *)"133.221.34.80"};
    int svr_gate_port[4] = {0x4C75, 0x4C75, 0x2565, 0x2565};
    int i;

    switch (netw->step) {
    case 0:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysTopKey;
            netw->step++;
        }
        break;
    case 1:
        func_00121270(0x30, (unsigned char *)"SERVER=%s[%s]\n", -270.0f, -192.0f,
                      svr_name[netiw->sel_gate], svr_ip[netiw->sel_gate]);
        func_00121270(0x30, (unsigned char *)"Ver:2005-05-09\n", -270.0f, -176.0f);
        for (i = 0; i < 3; i++) {
            if (i == D_0102FCC8) {
                NetWin_MenuSetSelect(D_0102FAC4[i + 7], 1);
                D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xC4;
                D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xC4;
            } else {
                NetWin_MenuSetSelect(D_0102FAC4[i + 7], 0);
                D_0102FAC4[i + 7]->s.x = i * 0x14 - 0xCE;
                D_0102FAC4[i + 7]->v.x = i * 0x14 - 0xCE;
            }
        }
        switch (D_0102FCC8) {
        case 0:
            func_001BBBF8(netiw->gate_ip_addr, svr_ip[netiw->sel_gate], 0x10);
            netiw->gate_port = svr_gate_port[netiw->sel_gate];
            NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xD));

            CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1D));
            break;
        case 1:
            NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xE));

            CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1E));
            break;
        case 2:
            NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xF));

            CwsStrSetString(D_0102FAD0, 0, NetReadDataGetStr(0x1F));
        }
        switch (netw->dc_code) {
        case 1:
            func_0011E440(func_0011E430() | 0x100);
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
            netw->step = 4;
            break;
        case 3:
            D_0102FAE0->mode = 3;
            D_0102FAE4->mode = 3;
            D_0102FAE8->mode = 0;
            CwsWinSetCode(D_0102FAE0, 2);
            CwsWinSetCode(D_0102FAE4, 2);
            CwsWinSetCode(D_0102FAE8, 2);
            netw->step = 3;
        }
        break;
    case 2:
        if (CwsWinsAllGetStatus(0))
            netw->step = 4;
        break;
    case 3:
        if (CwsWinsAllDestroy())
            netw->step = 4;
        break;
    case 4:
        switch (netw->dc_code) {
        case 1:
            netw->NewFunc = NetCnfMain;
            break;
        case 2:
            netw->NewFunc = NetSysRuleInit;
            break;
        case 3:
            netw->NewFunc = NetSysEnd;
        }
        break;
    }
}

static void NetSysTopKey(struct _NETWORK_W *netw) {
    if (!!(func_0011E1D0(0) & 0x1000) != 0
        || !!(func_0011E1D0(1) & 0x1000) != 0) {
        D_0102FCC8 = (D_0102FCC8 + 2) % 3;
    } else if (!!(func_0011E1D0(0) & 0x4000) != 0
               || !!(func_0011E1D0(1) & 0x4000) != 0) {
        D_0102FCC8 = (D_0102FCC8 + 1) % 3;
    } else if (!!(func_0011E1D0(0) & 0x8000) != 0
               || !!(func_0011E1D0(1) & 0x8000) != 0) {
        netiw->sel_gate = (netiw->sel_gate + 1) % 3;
    } else if (!!(func_0011E1D0(0) & 0x2000) != 0
               || !!(func_0011E1D0(1) & 0x2000) != 0) {
        netiw->sel_gate = (netiw->sel_gate + 2) % 3;
    }
    if (!!(func_0011E1F0(0) & 0x110) != 0
        || !!(func_0011E1F0(1) & 0x110) != 0) {
        netw->dc_code = 3;
    } else if (!!(func_0011E1F0(0) & 0x60) != 0
               || !!(func_0011E1F0(1) & 0x60) != 0) {
        if (D_0102FCC8 == 0)
            netw->dc_code = 1;
        else if (D_0102FCC8 == 1)
            netw->dc_code = 2;
        else
            netw->dc_code = 3;
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}
