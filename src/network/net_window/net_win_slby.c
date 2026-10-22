#include "src/network/net_window/net_win_slby.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
char CwsWinSetBri(struct _CWS_WIN_W *work, int bri);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetCol(struct _CWS_WIN_W *win, int str_num, unsigned char col);
void CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_SlbyFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_SlbyInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_SlbyMain,
    NetWin_SlbyEnd,
};
static void (*NetWin_SlbyCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinslby_plate_waku_off[9] = {
    { .x = 0, .y = 0, .w = 8, .h = 16, .tu = 0x20, .tv = 0x88, .tw = 8, .th = 16, .z = 0, .flag = 0 },
    { .x = 8, .y = 0, .w = 0x1C0, .h = 16, .tu = 0x28, .tv = 0x88, .tw = 1, .th = 16, .z = 0, .flag = 0 },
    { .x = 0x1C8, .y = 0, .w = 0x18, .h = 16, .tu = 0x28, .tv = 0x88, .tw = 0x18, .th = 16, .z = 0, .flag = 0 },
    { .x = 0, .y = 0x10, .w = 8, .h = 0x1C, .tu = 0x20, .tv = 0x98, .tw = 8, .th = 1, .z = 0, .flag = 0 },
    { .x = 8, .y = 0x10, .w = 0x1C0, .h = 0x1C, .tu = 0x28, .tv = 0x98, .tw = 1, .th = 1, .z = 0, .flag = 0 },
    { .x = 0x1C8, .y = 0x10, .w = 0x18, .h = 0x1C, .tu = 0x28, .tv = 0x98, .tw = 0x18, .th = 1, .z = 0, .flag = 0 },
    { .x = 0, .y = 0x2C, .w = 8, .h = 0x10, .tu = 0x20, .tv = 0x98, .tw = 8, .th = 0x10, .z = 0, .flag = 0 },
    { .x = 8, .y = 0x2C, .w = 0x1C0, .h = 0x10, .tu = 0x28, .tv = 0x98, .tw = 1, .th = 0x10, .z = 0, .flag = 0 },
    { .x = 0x1C8, .y = 0x2C, .w = 0x18, .h = 0x10, .tu = 0x28, .tv = 0x98, .tw = 0x18, .th = 0x10, .z = 0, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinslby_plate_waku_on[9] = {
    { .x = 0, .y = 0, .w = 8, .h = 16, .tu = 0, .tv = 0x88, .tw = 8, .th = 16, .z = 0, .flag = 0 },
    { .x = 8, .y = 0, .w = 0x1C0, .h = 16, .tu = 8, .tv = 0x88, .tw = 1, .th = 16, .z = 0, .flag = 0 },
    { .x = 0x1C8, .y = 0, .w = 0x18, .h = 16, .tu = 8, .tv = 0x88, .tw = 0x18, .th = 16, .z = 0, .flag = 0 },
    { .x = 0, .y = 0x10, .w = 8, .h = 0x1C, .tu = 0, .tv = 0x98, .tw = 8, .th = 1, .z = 0, .flag = 0 },
    { .x = 8, .y = 0x10, .w = 0x1C0, .h = 0x1C, .tu = 8, .tv = 0x98, .tw = 1, .th = 1, .z = 0, .flag = 0 },
    { .x = 0x1C8, .y = 0x10, .w = 0x18, .h = 0x1C, .tu = 8, .tv = 0x98, .tw = 0x18, .th = 1, .z = 0, .flag = 0 },
    { .x = 0, .y = 0x2C, .w = 8, .h = 0x10, .tu = 0, .tv = 0x98, .tw = 8, .th = 0x10, .z = 0, .flag = 0 },
    { .x = 8, .y = 0x2C, .w = 0x1C0, .h = 0x10, .tu = 8, .tv = 0x98, .tw = 1, .th = 0x10, .z = 0, .flag = 0 },
    { .x = 0x1C8, .y = 0x2C, .w = 0x18, .h = 0x10, .tu = 8, .tv = 0x98, .tw = 0x18, .th = 0x10, .z = 0, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinslby_plate_graph[3] = {
    { .x = 0x9C, .y = 0x26, .w = 1, .h = 0xC, .tu = 0, .tv = 0, .tw = 1, .th = 0xC, .z = 0x10, .flag = 0 },
    { .x = 0x9D, .y = 0x26, .w = 0xC8, .h = 0xC, .tu = 3, .tv = 0, .tw = 2, .th = 0xC, .z = 0x10, .flag = 0 },
    { .x = 0x165, .y = 0x26, .w = 1, .h = 0xC, .tu = 5, .tv = 0, .tw = 1, .th = 0xC, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinslby_plate_gauge[1] = {
    { .x = 0x9D, .y = 0x27, .w = 0, .h = 0xA, .tu = 1, .tv = 1, .tw = 0, .th = 0xA, .z = 0x20, .flag = 0 },
};
static struct _CWS_OBJ_SET netwinslby[3] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0xE,
        .ptex_obj = 9,
        .ptex = netwinslby_plate_waku_off,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0xF,
        .ptex_obj = 3,
        .ptex = netwinslby_plate_graph,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0xF,
        .ptex_obj = 1,
        .ptex = netwinslby_plate_gauge,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_Slby(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_SlbyCode[win->step[1]] != 0) NetWin_SlbyCode[win->step[1]](win);
    rtn = NetWin_SlbyFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_SlbyInit(struct _CWS_WIN_W *win) {
    struct _net_win_slby_w *winw = (struct _net_win_slby_w *)win->work;
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinslby[i]);
    }
    winw->board_status = 1;
    winw = (struct _net_win_slby_w *)win->work;
    if (winw->board_status != 0) {
        winw->board_status = 0;
        CwsObjChangePlate(win->obj[0], netwinslby_plate_waku_off);
        CwsWinSetBri(win, 0x40);
    }
    CwsStrSetAll(win, 0, 0xA, 6, 0x100, 0x80, 0x80, 0, 2, 0, (unsigned char *)"NO NAME");
    CwsStrSetAll(win, 2, 0x4E, 0x1E, 0x100, 0x80, 0x80, 0xC000, 2, 0, (unsigned char *)"0000");
    CwsStrSetAll(win, 3, 0x9A, 0x1E, 0x100, 0x80, 0x80, 0xC000, 2, 0, (unsigned char *)"0000");
    CwsStrSetAll(win, 1, 0x4C, 0x1E, 0x100, 0x80, 0x80, 0, 2, 0, (unsigned char *)"/");
    win->step[0]++;
    return 0;
}

static int NetWin_SlbyMain(struct _CWS_WIN_W *win) {
    struct _net_win_slby_w *winw = (struct _net_win_slby_w *)win->work;

    if (winw->max_num > 0) win->obj[2]->w = winw->now_num * 200 / winw->max_num;
    return 0;
}

static int NetWin_SlbyEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}

void NetWin_SlbySetSelect(struct _CWS_WIN_W *win, char status) {
    struct _net_win_slby_w *winw = (struct _net_win_slby_w *)win->work;

    if (winw->board_status != status) {
        winw->board_status = status;
        if (status == 1) {
            CwsObjChangePlate(win->obj[0], netwinslby_plate_waku_on);
            CwsWinSetBri(win, 0x80);
        } else {
            CwsObjChangePlate(win->obj[0], netwinslby_plate_waku_off);
            CwsWinSetBri(win, 0x40);
        }
    }
}

void NetWin_SlbySetName(struct _CWS_WIN_W *win, unsigned char *name) { CwsStrSetString(win, 0, (unsigned char *)"%s", name); }

void NetWin_SlbySetNowNum(struct _CWS_WIN_W *win, int _nownum) {
    struct _net_win_slby_w *winw = (struct _net_win_slby_w *)win->work;

    if (winw->now_num != _nownum) {
        CwsStrSetString(win, 2, (unsigned char *)"%04d", _nownum);
        winw->now_num = _nownum;
        if (winw->now_num < winw->max_num) CwsStrSetCol(win, 2, 5);
        else CwsStrSetCol(win, 2, 1);
    }
}

void NetWin_SlbySetMaxNum(struct _CWS_WIN_W *win, int _maxnum) {
    struct _net_win_slby_w *winw = (struct _net_win_slby_w *)win->work;

    if (winw->max_num != _maxnum) {
        CwsStrSetString(win, 3, (unsigned char *)"%04d", _maxnum);
        winw->max_num = _maxnum;
        if (winw->now_num < winw->max_num) CwsStrSetCol(win, 2, 5);
        else CwsStrSetCol(win, 2, 1);
    }
}
