#include "src/network/net_sys/net_sys_info.h"
#include "types/_NETWORK_W.h"
#include "types/_CWS_WIN_W.h"

#define D_0102FACC (*(struct _CWS_WIN_W **)0x0102FACC)
#define D_0102FAD4 (*(struct _CWS_WIN_W **)0x0102FAD4)
#define D_0102FCB4 (*(int *)0x0102FCB4)
#define D_0102FCB8 (*(int *)0x0102FCB8)
#define D_0102FCBC (*(int *)0x0102FCBC)
#define D_0102FCC0 (*(int *)0x0102FCC0)
#define D_0102FCC4 (*(unsigned char **)0x0102FCC4)

void NetSysMenuInit2(struct _NETWORK_W *);

void CwsStrAllDelete(struct _CWS_WIN_W *);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char,
                  unsigned char, unsigned int, int, unsigned char,
                  unsigned char *, ...);
char CwsStrSetStrightAll(struct _CWS_WIN_W *, int, int, int, unsigned char,
                         unsigned char, unsigned int, int, unsigned char,
                         unsigned char *, int, int);
char CwsStrSetCol(struct _CWS_WIN_W *, int, unsigned char);
char CwsWinSetCode(struct _CWS_WIN_W *, char);
char CwsWinDefSetXYWH(struct _CWS_WIN_W *, int, int, int, int);
void CwsWinReflash(struct _CWS_WIN_W *);
char CwsWinSetXY(struct _CWS_WIN_W *, int, int);
char CwsWinsAllGetStatus(int);
void NetWin_BarSetH(struct _CWS_WIN_W *, int);
void NetWin_BarSetMax(struct _CWS_WIN_W *, int);
void NetWin_BarSetNum(struct _CWS_WIN_W *, int);
void NetWin_BarSetNow(struct _CWS_WIN_W *, int);
unsigned char *NetReadDataGetStr(int);
int func_0011E1D0(int);
int func_0011E1F0(int);

static void NetSysInfoDispKey(struct _NETWORK_W *);
static void NetSysInfoDispMain(struct _NETWORK_W *);
static void NetSysInfoDispInit(struct _NETWORK_W *);
static void NetSysInfoKey(struct _NETWORK_W *);
static void NetSysInfoMain(struct _NETWORK_W *);

static void unused_info_types(anon_1_84 *p, anon_2_84 *q) {
    p->flg = 0;
    q->flg = 0;
}

void NetSysInfoInit(struct _NETWORK_W *netw) {
    int i;
    int j;
    int disp_num;
    int line_max;

    line_max = *(int *)D_0102FCC4 < 0x1E ? *(int *)D_0102FCC4 : 0x1E;
    disp_num = *(int *)D_0102FCC4 < 6 ? *(int *)D_0102FCC4 : 6;
    if (D_0102FCB4 < D_0102FCB8)
        D_0102FCB8 = D_0102FCB4;
    if (D_0102FCB4 >= disp_num + D_0102FCB8)
        D_0102FCB8 = D_0102FCB4 - disp_num + 1;
    CwsStrAllDelete(D_0102FAD4);
    CwsWinDefSetXYWH(D_0102FAD4, 0, 0x1F, 0x240, 0x142);
    CwsWinReflash(D_0102FAD4);
    if (D_0102FCC4) {
        D_0102FCBC = D_0102FCB8;
        for (i = 0, j = 0; i < disp_num; i++, j += 2) {
            CwsStrSetAll(D_0102FAD4, j, -0xEE, i * 0x30 - 0x89, 0x100, 0x80,
                         0x80, 0, 2, 0, (unsigned char *)"%s",
                         D_0102FCC4 + (D_0102FCB8 + i) * 0x257 + 5);
            CwsStrSetAll(D_0102FAD4, j + 1, -0xEE, i * 0x30 - 0x76, 0x100,
                         0x80, 0x80, 0, 2, 0, (unsigned char *)"%s",
                         D_0102FCC4 + (D_0102FCB8 + i) * 0x257 + 0x19);
        }
    } else {
        CwsStrSetAll(D_0102FAD4, 0, -0xEE, -0x89, 0x100, 0x80, 0x80, 0, 2, 5,
                     NetReadDataGetStr(0x1A));
    }
    CwsWinSetCode(D_0102FAD4, 1);
    D_0102FACC->mode = 0;
    CwsWinSetXY(D_0102FACC, -0x104, -0x6A);
    NetWin_BarSetH(D_0102FACC, 0x117);
    NetWin_BarSetMax(D_0102FACC, line_max);
    NetWin_BarSetNum(D_0102FACC, disp_num);
    NetWin_BarSetNow(D_0102FACC, D_0102FCB8);
    for (i = 0, j = 0; i < disp_num; i++, j += 2) {
        if (i == D_0102FCB4 - D_0102FCB8) {
            CwsStrSetCol(D_0102FAD4, j, 5);
            CwsStrSetCol(D_0102FAD4, j + 1, 5);
        } else {
            CwsStrSetCol(D_0102FAD4, j, 0);
            CwsStrSetCol(D_0102FAD4, j + 1, 0);
        }
    }
    netw->NewFunc = NetSysInfoMain;
}

static void NetSysInfoMain(struct _NETWORK_W *netw) {
    int i;
    int j;
    int disp_num;

    disp_num = *(int *)D_0102FCC4 < 6 ? *(int *)D_0102FCC4 : 6;
    switch (netw->step) {
    case 0:
        if (CwsWinsAllGetStatus(0)) {
            if (*(int *)D_0102FCC4 > 6) {
                CwsWinSetCode(D_0102FACC, 1);
                netw->step = 1;
            } else {
                netw->KeyFunc = NetSysInfoKey;
                netw->step = 2;
            }
        }
        break;
    case 1:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysInfoKey;
            netw->step = 2;
        }
        break;
    case 2:
        NetWin_BarSetNow(D_0102FACC, D_0102FCB8);
        if (D_0102FCC4 && D_0102FCB8 != D_0102FCBC) {
            D_0102FCBC = D_0102FCB8;
            for (i = 0, j = 0; i < disp_num; i++, j += 2) {
                CwsStrSetAll(D_0102FAD4, j, -0xEE, i * 0x30 - 0x89, 0x100,
                             0x80, 0x80, 0, 2, 0, (unsigned char *)"%s",
                             D_0102FCC4 + (D_0102FCB8 + i) * 0x257 + 5);
                CwsStrSetAll(D_0102FAD4, j + 1, -0xCE, i * 0x30 - 0x75, 0x100,
                             0x80, 0x80, 0, 2, 0, (unsigned char *)"%s",
                             D_0102FCC4 + (D_0102FCB8 + i) * 0x257 + 0x19);
            }
        }
        for (i = 0, j = 0; i < disp_num; i++, j += 2) {
            if (i == D_0102FCB4 - D_0102FCB8) {
                CwsStrSetCol(D_0102FAD4, j, 5);
                CwsStrSetCol(D_0102FAD4, j + 1, 5);
            } else {
                CwsStrSetCol(D_0102FAD4, j, 0);
                CwsStrSetCol(D_0102FAD4, j + 1, 0);
            }
        }
        if (netw->dc_code == 3 || netw->dc_code == 1) {
            CwsWinSetCode(D_0102FAD4, 2);
            D_0102FACC->mode = 0;
            CwsWinSetCode(D_0102FACC, 2);
            netw->step = 3;
        }
        break;
    case 3:
        if (CwsWinsAllGetStatus(0)) {
            CwsStrAllDelete(D_0102FAD4);
            netw->step = 4;
        }
        break;
    case 4:
        if (netw->dc_code == 3)
            netw->NewFunc = NetSysMenuInit2;
        else
            netw->NewFunc = NetSysInfoDispInit;
        break;
    }
}

static void NetSysInfoKey(struct _NETWORK_W *netw) {
    int line_max;
    int disp_num;

    line_max = *(int *)D_0102FCC4 < 0x1E ? *(int *)D_0102FCC4 : 0x1E;
    disp_num = *(int *)D_0102FCC4 < 6 ? *(int *)D_0102FCC4 : 6;
    if (!!(func_0011E1F0(0) & 0x110) != 0 ||
        !!(func_0011E1F0(1) & 0x110) != 0) {
        netw->dc_code = 3;
    }
    if (!!(func_0011E1F0(0) & 0x60) != 0 ||
        !!(func_0011E1F0(1) & 0x60) != 0) {
        netw->dc_code = 1;
    }
    if (!!(func_0011E1D0(0) & 0x1000) != 0 ||
        !!(func_0011E1D0(1) & 0x1000) != 0) {
        if (D_0102FCB4 > 0) {
            D_0102FCB4--;
            if (D_0102FCB4 < D_0102FCB8)
                D_0102FCB8--;
        }
    } else if (!!(func_0011E1D0(0) & 0x4000) != 0 ||
               !!(func_0011E1D0(1) & 0x4000) != 0) {
        if (D_0102FCB4 < line_max - 1) {
            D_0102FCB4++;
            if (D_0102FCB4 >= disp_num + D_0102FCB8)
                D_0102FCB8++;
        }
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}

static void NetSysInfoDispInit(struct _NETWORK_W *netw) {
    CwsStrAllDelete(D_0102FAD4);
    D_0102FAD4->s.h = 0x142;
    D_0102FAD4->v.h = 0x142;
    D_0102FAD4->s.y = 0x3F;
    D_0102FAD4->v.y = 0x3F;
    CwsWinDefSetXYWH(D_0102FAD4, 0, 0x3F, 0x240, 0x122);
    CwsWinReflash(D_0102FAD4);
    CwsStrSetStrightAll(D_0102FAD4, -0x106, -0x69, 0x100, 0x80, 0x80, 0, 1,
                        0, D_0102FCC4 + D_0102FCB4 * 0x257 + 0x5A, 0, 0xA);
    CwsWinSetCode(D_0102FAD4, 1);
    D_0102FACC->mode = 0;
    CwsWinSetXY(D_0102FACC, -0x104, -0x6A);
    NetWin_BarSetH(D_0102FACC, 0);
    NetWin_BarSetMax(D_0102FACC, 1);
    NetWin_BarSetNum(D_0102FACC, 1);
    NetWin_BarSetNow(D_0102FACC, 0);
    netw->NewFunc = NetSysInfoDispMain;
}

static void NetSysInfoDispMain(struct _NETWORK_W *netw) {
    switch (netw->step) {
    case 0:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysInfoDispKey;
            netw->step = 2;
        }
        break;
    case 1:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysInfoDispKey;
            netw->step = 1;
        }
        break;
    case 2:
        NetWin_BarSetH(D_0102FACC, 0);
        CwsWinSetXY(D_0102FACC, -0x104, 0);
        if (netw->dc_code == 3 || netw->dc_code == 2) {
            CwsWinSetCode(D_0102FAD4, 2);
            netw->step = 3;
        }
        break;
    case 3:
        if (CwsWinsAllGetStatus(0)) {
            D_0102FACC->mode = 0;
            CwsWinSetCode(D_0102FACC, 2);
            CwsStrAllDelete(D_0102FAD4);
            netw->step = 4;
        }
        break;
    case 4:
        if (netw->dc_code == 2)
            netw->NewFunc = NetSysInfoDispInit;
        else
            netw->NewFunc = NetSysInfoInit;
        break;
    }
}

static void NetSysInfoDispKey(struct _NETWORK_W *netw) {
    int line_max;

    line_max = *(int *)D_0102FCC4 < 0x1E ? *(int *)D_0102FCC4 : 0x1E;
    if (!!(func_0011E1F0(0) & 0x110) != 0 ||
        !!(func_0011E1F0(1) & 0x110) != 0 ||
        !!(func_0011E1F0(0) & 0x60) != 0 ||
        !!(func_0011E1F0(1) & 0x60) != 0) {
        netw->dc_code = 3;
    }
    if (!!(func_0011E1D0(0) & 0x1000) != 0 ||
        !!(func_0011E1D0(1) & 0x1000) != 0) {
        if (D_0102FCC0 > 0)
            D_0102FCC0--;
    } else if (!!(func_0011E1D0(0) & 0x4000) != 0 ||
               !!(func_0011E1D0(1) & 0x4000) != 0) {
        if (D_0102FCC0 < 9)
            D_0102FCC0++;
    } else if (!!(func_0011E1D0(0) & 0x2000) != 0 ||
               !!(func_0011E1D0(1) & 0x2000) != 0) {
        if (D_0102FCB4 < line_max - 1) {
            D_0102FCB4++;
            netw->dc_code = 2;
        }
    } else if (!!(func_0011E1D0(0) & 0x8000) != 0 ||
               !!(func_0011E1D0(1) & 0x8000) != 0) {
        if (D_0102FCB4 > 0) {
            D_0102FCB4--;
            netw->dc_code = 2;
        }
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}
