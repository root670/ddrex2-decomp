#include "src/network/net_window/net_win_tab.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_TabFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_TabInit,
    NetWin_TabMain,
    NetWin_TabEnd,
};
static void (*NetWin_TabCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinmenu_plate_tab_line[6] = {
    {
        .x = 0,
        .y = 36,
        .w = 640,
        .h = 5,
        .tu = 0,
        .tv = 31,
        .tw = 1,
        .th = 5,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 36,
        .w = 640,
        .h = 5,
        .tu = 0,
        .tv = 67,
        .tw = 1,
        .th = 5,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 36,
        .w = 640,
        .h = 5,
        .tu = 0,
        .tv = 103,
        .tw = 1,
        .th = 5,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 36,
        .w = 640,
        .h = 5,
        .tu = 0,
        .tv = 139,
        .tw = 1,
        .th = 5,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 36,
        .w = 640,
        .h = 5,
        .tu = 0,
        .tv = 175,
        .tw = 1,
        .th = 5,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 0,
        .w = 0,
        .h = 0,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 0,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinmenu_plate_tab_box[5] = {
    {
        .x = 8,
        .y = 0,
        .w = 129,
        .h = 36,
        .tu = 0,
        .tv = 0,
        .tw = 129,
        .th = 36,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 139,
        .y = 0,
        .w = 176,
        .h = 36,
        .tu = 0,
        .tv = 36,
        .tw = 176,
        .th = 36,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 317,
        .y = 0,
        .w = 93,
        .h = 36,
        .tu = 0,
        .tv = 72,
        .tw = 93,
        .th = 36,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 412,
        .y = 0,
        .w = 60,
        .h = 36,
        .tu = 0,
        .tv = 108,
        .tw = 60,
        .th = 36,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 474,
        .y = 0,
        .w = 82,
        .h = 36,
        .tu = 0,
        .tv = 144,
        .tw = 82,
        .th = 36,
        .z = 16,
        .flag = 0,
    },
};
static struct _CWS_OBJ_SET netwintab[6] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 23,
        .ptex_obj = 0,
        .ptex = netwinmenu_plate_tab_line,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 23,
        .ptex_obj = 0,
        .ptex = netwinmenu_plate_tab_box,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 23,
        .ptex_obj = 0,
        .ptex = &netwinmenu_plate_tab_box[1],
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 23,
        .ptex_obj = 0,
        .ptex = &netwinmenu_plate_tab_box[2],
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 23,
        .ptex_obj = 0,
        .ptex = &netwinmenu_plate_tab_box[3],
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 23,
        .ptex_obj = 0,
        .ptex = &netwinmenu_plate_tab_box[4],
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_Tab(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_TabCode[win->step[1]] != 0) NetWin_TabCode[win->step[1]](win);
    rtn = NetWin_TabFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_TabInit(struct _CWS_WIN_W *win) {
    int i;
    struct _net_win_tab_w *winw;

    winw = (struct _net_win_tab_w *)win->work;
    for (i = 0; i < 6; i++) {
        win->obj[i] = CwsObjCreate(&netwintab[i]);
    }
    winw->tab_num = -1;
    win->step[0]++;
    return 0;
}

static int NetWin_TabMain(struct _CWS_WIN_W *win) {
    int i;
    struct _net_win_tab_w *winw;
    int st;

    winw = (struct _net_win_tab_w *)win->work;
    if (winw->status & 1) {
        for (i = 0; i < 5; i++) {
            st = winw->tab_state[i];
            if (st & 0x0002) {
                win->obj[i + 1]->y = 5;
                win->obj[i + 1]->red = 0x80;
                win->obj[i + 1]->green = 0x80;
                win->obj[i + 1]->blue = 0x80;
            }
            else if (st & 0x0004) {
                win->obj[i + 1]->y = 0;
                win->obj[i + 1]->red = 0x40;
                win->obj[i + 1]->green = 0x40;
                win->obj[i + 1]->blue = 0x40;
            }
            else if (st & 0x0001) {
                st = (int)g_sys_w.s_counter % 24 / 2 - 6;
                win->obj[i + 1]->y = st >= 0 ? st : -st;
                win->obj[i + 1]->red = 0x80;
                win->obj[i + 1]->green = 0x80;
                win->obj[i + 1]->blue = 0x80;
            }
            else {
                win->obj[i + 1]->y = 0;
                win->obj[i + 1]->red = 0x80;
                win->obj[i + 1]->green = 0x80;
                win->obj[i + 1]->blue = 0x80;
            }
        }
    }
    return 0;
}

static int NetWin_TabEnd(struct _CWS_WIN_W *win) {
    win->status |= 4;
    return 0;
}

void NetWin_TabSetSelect(struct _CWS_WIN_W *win, int tab_num) {
    int i;
    struct _net_win_tab_w *winw;

    winw = (struct _net_win_tab_w *)win->work;
    if (tab_num < 0 || tab_num >= 6) return;
    if (winw->tab_num == tab_num) return;
    winw->tab_num = tab_num;
    for (i = 0; i < 5; i++) {
        if (i == tab_num) {
            winw->tab_state[i] = 1;
        } else {
            winw->tab_state[i] = 0;
        }
    }
    winw->status |= 1;
    CwsObjChangePlate(win->obj[0], &netwinmenu_plate_tab_line[tab_num]);
}

void NetWin_TabSetOn(struct _CWS_WIN_W *win, int tab_num) {
    int i;
    struct _net_win_tab_w *winw;

    winw = (struct _net_win_tab_w *)win->work;
    for (i = 0; i < 5; i++) {
        if (i == tab_num) {
            winw->tab_state[i] |= 0x0002;
        } else {
            winw->tab_state[i] |= 0x0004;
        }
    }
    winw->status |= 1;
}

void NetWin_TabSetOff(struct _CWS_WIN_W *win) {
    struct _net_win_tab_w *winw;

    winw = (struct _net_win_tab_w *)win->work;
    winw->tab_state[0] &= ~0x0002;
    winw->tab_state[0] &= ~0x0004;
    winw->tab_state[1] &= ~0x0002;
    winw->tab_state[1] &= ~0x0004;
    winw->tab_state[2] &= ~0x0002;
    winw->tab_state[2] &= ~0x0004;
    winw->tab_state[3] &= ~0x0002;
    winw->tab_state[3] &= ~0x0004;
    winw->tab_state[4] &= ~0x0002;
    winw->tab_state[4] &= ~0x0004;
    winw->status |= 1;
}
