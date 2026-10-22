#include "src/network/net_window/net_win_rcname.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
void CwsObjMoveOpt(int *_v, int _timer, int _s, int _end_time, int _type);
int CwsObjMove(int *_v, int *_timer, int _s, int _end_time, int _type);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
void CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_RcnameFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_RcnameInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_RcnameMain,
    NetWin_RcnameEnd,
};
static void (*NetWin_RcnameCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinrcname_plate_cov_off[9] = {
    { .x = 0, .y = 0, .w = 0xC, .h = 0xC, .tu = 0, .tv = 0, .tw = 0xC, .th = 0xC, .z = 0x20, .flag = 0 },
    { .x = 0xC, .y = 0, .w = 0xEA, .h = 0xC, .tu = 0xC, .tv = 0, .tw = 1, .th = 0xC, .z = 0x20, .flag = 0 },
    { .x = 0xF6, .y = 0, .w = 0xC, .h = 0xC, .tu = 0xC, .tv = 0, .tw = 0xC, .th = 0xC, .z = 0x20, .flag = 0 },
    { .x = 0, .y = 0xC, .w = 0xC, .h = 0x3A, .tu = 0, .tv = 0xC, .tw = 0xC, .th = 1, .z = 0x20, .flag = 0 },
    { .x = 0xC, .y = 0xC, .w = 0xEA, .h = 0x3A, .tu = 0xC, .tv = 0xC, .tw = 1, .th = 1, .z = 0x20, .flag = 0 },
    { .x = 0xF6, .y = 0xC, .w = 0xC, .h = 0x3A, .tu = 0xC, .tv = 0xC, .tw = 0xC, .th = 1, .z = 0x20, .flag = 0 },
    { .x = 0, .y = 0x46, .w = 0xC, .h = 0xC, .tu = 0, .tv = 0xC, .tw = 0xC, .th = 0xC, .z = 0x20, .flag = 0 },
    { .x = 0xC, .y = 0x46, .w = 0xEA, .h = 0xC, .tu = 0xC, .tv = 0xC, .tw = 1, .th = 0xC, .z = 0x20, .flag = 0 },
    { .x = 0xF6, .y = 0x46, .w = 0xC, .h = 0xC, .tu = 0xC, .tv = 0xC, .tw = 0xC, .th = 0xC, .z = 0x20, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinrcname_plate_cov_on[9];
static struct _CWS_OBJ_TEX netwinrcname_plate_board[1] = {
    { .x = 1, .y = 1, .w = 0x100, .h = 0x50, .tu = 0, .tv = 0, .tw = 0x100, .th = 0x50, .z = 0x30, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinrcname_plate_tagup[2] = {
    { .x = 0, .y = 0, .w = 0xA0, .h = 0x16, .tu = 0, .tv = 0, .tw = 0xA0, .th = 0x16, .z = 0, .flag = 0 },
    { .x = 5, .y = 5, .w = 0x68, .h = 0x10, .tu = 0, .tv = 0x2C, .tw = 0x68, .th = 0x10, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinrcname_plate_tagdw[2] = {
    { .x = 0, .y = 0x3C, .w = 0xA0, .h = 0x16, .tu = 0, .tv = 0x16, .tw = 0xA0, .th = 0x16, .z = 0, .flag = 0 },
    { .x = 5, .y = 0x3F, .w = 0x68, .h = 0x10, .tu = 0, .tv = 0x2C, .tw = 0x68, .th = 0x10, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinrcname_plate_add_option[1] = {
    { .x = 5, .y = 0x40, .w = 0x50, .h = 0x10, .tu = 0, .tv = 0, .tw = 0x50, .th = 0x10, .z = 0x40, .flag = 0 },
};
static struct _CWS_OBJ_SET netwinrcname[6] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 1,
        .ptex_obj = 9,
        .ptex = netwinrcname_plate_cov_off,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 21,
        .ptex_obj = 0,
        .ptex = netwinrcname_plate_board,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 22,
        .ptex_obj = 0,
        .ptex = netwinrcname_plate_board,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 20,
        .ptex_obj = 2,
        .ptex = netwinrcname_plate_tagup,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 20,
        .ptex_obj = 2,
        .ptex = netwinrcname_plate_tagdw,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 33,
        .ptex_obj = 0,
        .ptex = netwinrcname_plate_add_option,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_Rcname(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_RcnameCode[win->step[1]] != 0) NetWin_RcnameCode[win->step[1]](win);
    rtn = NetWin_RcnameFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_RcnameInit(struct _CWS_WIN_W *win) {
    struct _net_win_rcname_w *winw = (struct _net_win_rcname_w *)win->work;
    int i;

    for (i = 0; i < 6; i++) {
        win->obj[i] = CwsObjCreate(&netwinrcname[i]);
    }
    win->obj[2]->status &= ~2;
    win->obj[5]->status &= ~2;
    winw->cur = 0;
    winw->sy[0] = 0;
    winw->sy[1] = 0xEC;
    CwsStrSetAll(win, 0, 4, 0x2C, 0x100, 0x80, 0x80, 0, 1, 0, (unsigned char *)"CHALLENGE NO:100");
    CwsStrSetAll(win, 1, 0xDB, 0x40, 0x100, 0x80, 0x80, 0xC000, 1, 0, (unsigned char *)"99");
    CwsStrSetAll(win, 2, 0xE8, 0x40, 0x100, 0x80, 0x80, 0x4000, 1, 0, (unsigned char *)"/");
    CwsStrSetAll(win, 3, 0xFE, 0x40, 0x100, 0x80, 0x80, 0xC000, 1, 0, (unsigned char *)"99");
    win->step[0]++;
    return 0;
}

static int NetWin_RcnameMain(struct _CWS_WIN_W *win) {
    struct _net_win_rcname_w *winw = (struct _net_win_rcname_w *)win->work;

    if (winw->flag & 1) {
        CwsObjMoveOpt(&win->obj[4]->y, winw->time, winw->sy[1], 3, 1);
        if (CwsObjMove(&win->obj[3]->y, &winw->time, winw->sy[0], 3, 1) != 0) winw->flag &= ~1;
    }
    return 0;
}

static int NetWin_RcnameEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}

void NetWin_RcnameSetType(struct _CWS_WIN_W *win, int type) {
    if (type == 0) {
        win->obj[1]->status |= 2;
        win->obj[2]->status &= ~2;
    } else {
        win->obj[1]->status &= ~2;
        win->obj[2]->status |= 2;
    }
}

void NetWin_RcnameSetCursor(struct _CWS_WIN_W *win, int cur) {
    struct _net_win_rcname_w *winw = (struct _net_win_rcname_w *)win->work;

    if (winw->cur != cur) {
        if (cur == 1) {
            winw->sy[0] = -0x16;
            winw->sy[1] = 0x3C;
        } else if (cur == 2) {
            winw->sy[0] = 0;
            winw->sy[1] = 0x52;
        } else {
            winw->sy[0] = 0;
            winw->sy[1] = 0x3C;
        }
        winw->time = 0;
        winw->flag |= 1;
        winw->cur = cur;
    }
}

void NetWin_RcnameSetName(struct _CWS_WIN_W *win, unsigned char *name, int _num) { CwsStrSetString(win, 0, name, _num); }

void NetWin_RcnameSetNow(struct _CWS_WIN_W *win, int _num) { CwsStrSetString(win, 1, (unsigned char *)"%02d", _num); }

void NetWin_RcnameSetMax(struct _CWS_WIN_W *win, int _num) { CwsStrSetString(win, 3, (unsigned char *)"%02d", _num); }

void NetWin_RcnameSetOption(struct _CWS_WIN_W *win, char on_off) {
    if (on_off == 1) win->obj[5]->status |= 2;
    else win->obj[5]->status &= ~2;
}
