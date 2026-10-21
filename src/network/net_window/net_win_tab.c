#include "src/network/net_window/net_win_tab.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_TabFunc[3])(struct _CWS_WIN_W *) = { NetWin_TabInit, NetWin_TabMain, NetWin_TabEnd };
static void (*NetWin_TabCode[4])(struct _CWS_WIN_W *) = { 0, CwsWinOpen, CwsWinClose, CwsWinDestroy };
static struct _CWS_OBJ_TEX netwinmenu_plate_tab_line[6] = {
    { 0, 36, 640, 5, 0, 31, 1, 5, 0, 0 },
    { 0, 36, 640, 5, 0, 67, 1, 5, 0, 0 },
    { 0, 36, 640, 5, 0, 103, 1, 5, 0, 0 },
    { 0, 36, 640, 5, 0, 139, 1, 5, 0, 0 },
    { 0, 36, 640, 5, 0, 175, 1, 5, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
static struct _CWS_OBJ_TEX netwinmenu_plate_tab_box[5] = {
    { 8, 0, 129, 36, 0, 0, 129, 36, 16, 0 },
    { 139, 0, 176, 36, 0, 36, 176, 36, 16, 0 },
    { 317, 0, 93, 36, 0, 72, 93, 36, 16, 0 },
    { 412, 0, 60, 36, 0, 108, 60, 36, 16, 0 },
    { 474, 0, 82, 36, 0, 144, 82, 36, 16, 0 }
};
static struct _CWS_OBJ_SET netwintab[6] = {
    { (int (*)(void *, void *))CwsObjDisp, 23, 0, netwinmenu_plate_tab_line, 0x80, 0x80, 0x80, 0x80 },
    { (int (*)(void *, void *))CwsObjDisp, 23, 0, netwinmenu_plate_tab_box, 0x80, 0x80, 0x80, 0x80 },
    { (int (*)(void *, void *))CwsObjDisp, 23, 0, &netwinmenu_plate_tab_box[1], 0x80, 0x80, 0x80, 0x80 },
    { (int (*)(void *, void *))CwsObjDisp, 23, 0, &netwinmenu_plate_tab_box[2], 0x80, 0x80, 0x80, 0x80 },
    { (int (*)(void *, void *))CwsObjDisp, 23, 0, &netwinmenu_plate_tab_box[3], 0x80, 0x80, 0x80, 0x80 },
    { (int (*)(void *, void *))CwsObjDisp, 23, 0, &netwinmenu_plate_tab_box[4], 0x80, 0x80, 0x80, 0x80 }
};

int NetWin_Tab(struct _CWS_WIN_W *win)
{
    int rtn;

    if (NetWin_TabCode[win->step[1]] != 0) NetWin_TabCode[win->step[1]](win);
    rtn = NetWin_TabFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_TabInit(struct _CWS_WIN_W *win)
{
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

static int NetWin_TabMain(struct _CWS_WIN_W *win)
{
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

static int NetWin_TabEnd(struct _CWS_WIN_W *win)
{
    win->status |= 4;
    return 0;
}

void NetWin_TabSetSelect(struct _CWS_WIN_W *win, int tab_num)
{
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

void NetWin_TabSetOn(struct _CWS_WIN_W *win, int tab_num)
{
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

void NetWin_TabSetOff(struct _CWS_WIN_W *win)
{
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
