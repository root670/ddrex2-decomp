#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"

#define D_0102FAC8 (*(struct _CWS_WIN_W **)0x0102FAC8)
#define D_0102FACC (*(struct _CWS_WIN_W **)0x0102FACC)
#define D_0102FAD4 (*(struct _CWS_WIN_W **)0x0102FAD4)
#define D_0102FAD8 (*(struct _CWS_WIN_W **)0x0102FAD8)
#define D_0102FB04 (*(int *)0x0102FB04)
#define D_0102FB08 (*(int *)0x0102FB08)
#define D_0102FB0C (*(int *)0x0102FB0C)
#define D_0102FB10 (*(unsigned char *)0x0102FB10)

void NetSysTopInit2(struct _NETWORK_W *);
void NetSysEnd(struct _NETWORK_W *);
void NetSysTopInit(struct _NETWORK_W *);
int CwsWin_Multi(struct _CWS_WIN_W *);
void CwsStrAllDelete(struct _CWS_WIN_W *);
void CwsWinSetXY(struct _CWS_WIN_W *, int, int);
void NetWin_BaseSetName(struct _CWS_WIN_W *, unsigned char *);
void NetWin_BarSetH(struct _CWS_WIN_W *, int);
void NetWin_BarSetMax(struct _CWS_WIN_W *, int);
void NetWin_BarSetNum(struct _CWS_WIN_W *, int);
void NetWin_BarSetNow(struct _CWS_WIN_W *, int);
void CwsWin_MultiSetWinClut(struct _CWS_WIN_W *, int);
unsigned char *NetReadDataGetStr(int);
int NetReadDataGetStrLFNum(unsigned char *);
char NetPadCon(unsigned int);
struct _CWS_WIN_W *CwsWinCreate(void *, int, int, int, int, int);
char CwsWinDelete(struct _CWS_WIN_W *);
char CwsWinSetCode(struct _CWS_WIN_W *, char);
char CwsStrSetCol(struct _CWS_WIN_W *, int, unsigned char);
char CwsStrSetStrightString(struct _CWS_WIN_W *, unsigned char *, int, int);
char CwsStrSetStrightAll(struct _CWS_WIN_W *, int, int, int, unsigned char,
                         unsigned char, unsigned int, int, unsigned char,
                         unsigned char *, int, int);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char,
                  unsigned char, unsigned int, int, unsigned char,
                  unsigned char *, ...);
char CwsWinsAllGetStatus(int);
void func_0011EEC0(void *, int);
int func_0011E1F0(int);

static void NetSysRuleSelectKey(struct _NETWORK_W *);
static void NetSysRuleKey(struct _NETWORK_W *);
static void NetSysRuleMain(struct _NETWORK_W *);

static void NetSysRuleSelectKey(struct _NETWORK_W *netw) {
    if (!!(func_0011E1F0(0) & 0x110) != 0 || !!(func_0011E1F0(1) & 0x110) != 0) {
        netw->dc_code = 2;
    } else if (!!(func_0011E1F0(0) & 0x60) != 0 || !!(func_0011E1F0(1) & 0x60) != 0) {
        netw->dc_code = 1;
    }
    if (!!(func_0011E1F0(0) & 0x8000) != 0 || !!(func_0011E1F0(1) & 0x8000) != 0) {
        D_0102FB0C = 0;
    } else if (!!(func_0011E1F0(0) & 0x2000) != 0 || !!(func_0011E1F0(1) & 0x2000) != 0) {
        D_0102FB0C = 1;
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}

static void NetSysRuleKey(struct _NETWORK_W *netw) {
    int old_str_line_now;
    if (!!(func_0011E1F0(0) & 0x60) != 0 || !!(func_0011E1F0(1) & 0x60) != 0) {
        if (D_0102FB10 & 2)
            netw->dc_code = 1;
    } else if (!!(func_0011E1F0(0) & 0x110) != 0 || !!(func_0011E1F0(1) & 0x110) != 0) {
        netw->dc_code = 2;
    }
    if (D_0102FB08 > 0xB) {
        old_str_line_now = D_0102FB04;
        if (NetPadCon(0x1000)) {
            D_0102FB04 = D_0102FB04 - 1 > 0 ? D_0102FB04 - 1 : 0;
        } else if (NetPadCon(0x4000)) {
            D_0102FB04 = D_0102FB04 + 1 < D_0102FB08 - 0xB ? D_0102FB04 + 1
                                                         : D_0102FB08 - 0xB;
            if (D_0102FB04 == D_0102FB08 - 0xB)
                D_0102FB10 |= 4;
        }
        if (old_str_line_now != D_0102FB04)
            D_0102FB10 |= 1;
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}

static void NetSysRuleMain(struct _NETWORK_W *netw) {
    int i;
    switch (netw->step) {
    case 0:
        if (CwsWinsAllGetStatus(0)) {
            if (D_0102FB08 > 0xB) {
                CwsWinSetCode(D_0102FACC, 1);
                netw->step = 1;
            } else {
                netw->KeyFunc = NetSysRuleKey;
                netw->step = 2;
            }
        }
        break;
    case 1:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysRuleKey;
            netw->dc_code = 0;
            netw->step = 2;
        }
        break;
    case 2:
        if (!!(D_0102FB10 & 1)) {
            NetWin_BarSetNow(D_0102FACC, D_0102FB04);
            CwsStrSetStrightString(D_0102FAD4, NetReadDataGetStr(0x28),
                                   D_0102FB04, 0xB);
            D_0102FB10 &= ~1;
        }
        switch (netw->dc_code) {
        case 1:
            D_0102FB0C = 1;
            for (i = 0; i < 2; i++) {
                if (i == D_0102FB0C)
                    CwsStrSetCol(D_0102FAD8, i + 1, 4);
                else
                    CwsStrSetCol(D_0102FAD8, i + 1, 0);
            }
            CwsWin_MultiSetWinClut(D_0102FAD8, 2);
            D_0102FAD8->mode = 6;
            CwsWinSetCode(D_0102FAD8, 1);
            netw->step = 3;
            break;
        case 2:
            CwsWinSetCode(D_0102FAD4, 2);
            CwsWinSetCode(D_0102FACC, 2);
            netw->step = 6;
            break;
        }
        break;
    case 3:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysRuleSelectKey;
            netw->dc_code = 0;
            netw->step = 4;
        }
        break;
    case 4:
        for (i = 0; i < 2; i++) {
            if (i == D_0102FB0C)
                CwsStrSetCol(D_0102FAD8, i + 1, 4);
            else
                CwsStrSetCol(D_0102FAD8, i + 1, 0);
        }
        switch (netw->dc_code) {
        case 1:
            CwsWinSetCode(D_0102FAD8, 2);
            CwsWinSetCode(D_0102FAD4, 2);
            CwsWinSetCode(D_0102FACC, 2);
            netw->step = 5;
            break;
        case 2:
            CwsWinSetCode(D_0102FAD8, 2);
            netw->step = 0;
            break;
        }
        break;
    case 5:
        if (CwsWinsAllGetStatus(0))
            netw->step = 6;
        break;
    case 6:
        if (CwsWinsAllGetStatus(0)) {
            CwsStrAllDelete(D_0102FAD4);
            if (!!(D_0102FB10 & 2)) {
                if (netw->dc_code == 2)
                    netw->NewFunc = NetSysEnd;
                else if (D_0102FB0C == 0) {
                    netw->status |= 0x20;
                    netw->NewFunc = NetSysTopInit;
                } else
                    netw->NewFunc = NetSysEnd;
            } else {
                netw->NewFunc = NetSysTopInit2;
            }
        }
        break;
    }
}

void NetSysRuleInit(struct _NETWORK_W *netw) {
    unsigned char *disp_str;
    disp_str = NetReadDataGetStr(0x28);
    func_0011EEC0(&D_0102FB04, 0x10);
    D_0102FB10 &= ~2;
    D_0102FB04 = 0;
    D_0102FB08 = NetReadDataGetStrLFNum(disp_str) + 1;
    CwsStrAllDelete(D_0102FAD4);
    CwsStrSetStrightAll(D_0102FAD4, -0xEE, -0x89, 0x100, 0x80, 0x80, 0, 2, 0,
                        disp_str, 0, 0xB);
    CwsWinSetCode(D_0102FAD4, 1);
    if (D_0102FB08 > 0xB) {
        D_0102FACC->mode = 0;
        CwsWinSetXY(D_0102FACC, -0x107, -0x6A);
        NetWin_BarSetH(D_0102FACC, 0x108);
        NetWin_BarSetMax(D_0102FACC, D_0102FB08);
        NetWin_BarSetNum(D_0102FACC, 0xB);
        NetWin_BarSetNow(D_0102FACC, D_0102FB04);
    }
    netw->NewFunc = NetSysRuleMain;
}

void NetSysRuleStartInit(struct _NETWORK_W *netw) {
    unsigned char *disp_str;
    disp_str = NetReadDataGetStr(0x28);
    func_0011EEC0(&D_0102FB04, 0x10);
    D_0102FB10 |= 2;
    D_0102FB04 = 0;
    D_0102FB08 = NetReadDataGetStrLFNum(disp_str) + 1;
    CwsStrAllDelete(D_0102FAD4);
    CwsStrSetStrightAll(D_0102FAD4, -0xEE, -0x89, 0x100, 0x80, 0x80, 0, 2, 0,
                        disp_str, 0, 0xB);
    CwsWinSetCode(D_0102FAD4, 1);
    if (D_0102FB08 > 0xB) {
        D_0102FACC->mode = 0;
        CwsWinSetXY(D_0102FACC, -0x107, -0x6A);
        NetWin_BarSetH(D_0102FACC, 0x108);
        NetWin_BarSetMax(D_0102FACC, D_0102FB08);
        NetWin_BarSetNum(D_0102FACC, 0xB);
        NetWin_BarSetNow(D_0102FACC, D_0102FB04);
    }
    CwsWinDelete(D_0102FAD8);
    D_0102FAD8 = CwsWinCreate(CwsWin_Multi, 0, 0, 0x17C, 0x7E, 0x5000);
    CwsStrSetAll(D_0102FAD8, 0, 0, -0x35, 0x100, 0x80, 0x80, 0x400, 2, 0,
                 NetReadDataGetStr(0x17));
    CwsStrSetAll(D_0102FAD8, 1, -0x5A, 9, 0x100, 0x80, 0x80, 0x400, 2, 0,
                 NetReadDataGetStr(0x18));
    CwsStrSetAll(D_0102FAD8, 2, 0x5A, 9, 0x100, 0x80, 0x80, 0x400, 2, 0,
                 NetReadDataGetStr(0x19));
    NetWin_BaseSetName(D_0102FAC8, NetReadDataGetStr(0xE));
    netw->NewFunc = NetSysRuleMain;
}
