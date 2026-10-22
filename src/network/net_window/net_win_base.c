#include "src/network/net_window/net_win_base.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
void CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
void func_00124800(anon_1_163 *g3);

static int (*NetWin_BaseFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_BaseInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_BaseMain,
    NetWin_BaseEnd,
};
static void (*NetWin_BaseCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinbase_plate_back[1] = {
    { .x = 0, .y = 0x32, .w = 0x156, .h = 0x16E, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 0, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinbase_plate_cover[1] = {
    { .x = 0, .y = 0, .w = 0x190, .h = 0x1A0, .tu = 0, .tv = 0, .tw = 0x190, .th = 0x1A0, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_SET netwinbase[2] = {
    {
        .func = (int (*)(void *, void *))NetWin_BaseBoardDisp,
        .tex_num = -1,
        .ptex_obj = 0,
        .ptex = netwinbase_plate_back,
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x13,
        .ptex_obj = 0,
        .ptex = netwinbase_plate_cover,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_Base(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_BaseCode[win->step[1]] != 0) NetWin_BaseCode[win->step[1]](win);
    rtn = NetWin_BaseFunc[win->step[0]](win);

    return rtn;
}

static int NetWin_BaseInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 2; i++) {
        win->obj[i] = CwsObjCreate(&netwinbase[i]);
    }

    CwsStrSetAll(win, 0, 0x2A, 0x11, 0x100, 0x80, 0x80, 0, 2, 3, (unsigned char *)"");

    win->step[0]++;
    return 0;
}

static int NetWin_BaseMain(void) { return 0; }

static int NetWin_BaseEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}

static void NetWin_BaseBoardDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw) {
    anon_1_163 g3;
    int dx;
    int dy;
    int dw;
    int dh;
    int dr, dg, db;
    int da; int mx, my;
    if (objw == 0) return;
    if (!(objw->status & 2)) return;
    if (win->master_link == 0) {
        dx = win->v.x + objw->x;
        dy = win->v.y + objw->y;
    } else {
        mx = win->master_link->v.x + win->v.x; dx = mx + objw->x;
        my = win->master_link->v.y + win->v.y; dy = my + objw->y;
    }

    dw = objw->w;
    dh = objw->h;

    dr = win->v.r * objw->red * win->v.bri / 0x4000;
    dg = win->v.g * objw->green * win->v.bri / 0x4000;
    db = win->v.b * objw->blue * win->v.bri / 0x4000;
    da = win->v.a * objw->alpha / 0x80;

    g3.flg = 0;
    g3.flg |= 0x100;
    g3.x0.fd = dx; g3.y0.fd = dy; g3.z0 = 0x100;
    g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = 0x100;
    g3.x2.fd = dx; g3.y2.fd = dy + dh; g3.z2 = 0x100;
    g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
    g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = 0;
    g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
    func_00124800(&g3);
    g3.flg = 0;
    g3.flg |= 0x100;
    g3.x0.fd = dx; g3.y0.fd = dy + dh; g3.z0 = 0x100;
    g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = 0x100;
    g3.x2.fd = dx + dw; g3.y2.fd = dy + dh; g3.z2 = 0x100;
    g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
    g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = 0;
    g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = 0;
    func_00124800(&g3);
}

void NetWin_BaseSetName(struct _CWS_WIN_W *win, unsigned char *_str) { CwsStrSetString(win, 0, _str); }
