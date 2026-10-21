#include "src/network/net_window/net_win_item.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_ItemFunc[3])(struct _CWS_WIN_W *) = { NetWin_ItemInit, (int (*)(struct _CWS_WIN_W *))NetWin_ItemMain, NetWin_ItemEnd };
static void (*NetWin_ItemCode[4])(struct _CWS_WIN_W *) = { 0, CwsWinOpen, CwsWinClose, CwsWinDestroy };
static struct _CWS_OBJ_TEX netwinitem_plate_mini_off[9] = {
    { .x = 0, .y = 0, .w = 12, .h = 24, .tu = 0, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 12, .y = 0, .w = 156, .h = 24, .tu = 12, .tv = 0, .tw = 1, .th = 24, .z = 0, .flag = 0 },
    { .x = 168, .y = 0, .w = 12, .h = 24, .tu = 12, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 0, .y = 0, .w = 0, .h = 0, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 0, .flag = -1 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_mini_on[9] = {
    { .x = 0, .y = 0, .w = 12, .h = 24, .tu = 24, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 12, .y = 0, .w = 156, .h = 24, .tu = 36, .tv = 0, .tw = 1, .th = 24, .z = 0, .flag = 0 },
    { .x = 168, .y = 0, .w = 12, .h = 24, .tu = 36, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 0, .y = 0, .w = 0, .h = 0, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 0, .flag = -1 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_big_off[9] = {
    { .x = 0, .y = 0, .w = 12, .h = 24, .tu = 0, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 12, .y = 0, .w = 226, .h = 24, .tu = 12, .tv = 0, .tw = 1, .th = 24, .z = 0, .flag = 0 },
    { .x = 238, .y = 0, .w = 12, .h = 24, .tu = 12, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 0, .y = 0, .w = 0, .h = 0, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 0, .flag = -1 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_big_on[9] = {
    { .x = 0, .y = 0, .w = 12, .h = 24, .tu = 0, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 12, .y = 0, .w = 226, .h = 24, .tu = 12, .tv = 0, .tw = 1, .th = 24, .z = 0, .flag = 0 },
    { .x = 238, .y = 0, .w = 12, .h = 24, .tu = 12, .tv = 0, .tw = 12, .th = 24, .z = 0, .flag = 0 },
    { .x = 0, .y = 0, .w = 0, .h = 0, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 0, .flag = -1 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_music_off[9] = {
    {
        .x = 0,
        .y = 0,
        .w = 10,
        .h = 10,
        .tu = 0,
        .tv = 0,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 0,
        .w = 238,
        .h = 10,
        .tu = 12,
        .tv = 0,
        .tw = 1,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 248,
        .y = 0,
        .w = 10,
        .h = 10,
        .tu = 14,
        .tv = 0,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 10,
        .w = 10,
        .h = 60,
        .tu = 0,
        .tv = 10,
        .tw = 10,
        .th = 1,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 10,
        .w = 238,
        .h = 60,
        .tu = 12,
        .tv = 10,
        .tw = 1,
        .th = 1,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 248,
        .y = 10,
        .w = 10,
        .h = 60,
        .tu = 14,
        .tv = 10,
        .tw = 10,
        .th = 1,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 70,
        .w = 10,
        .h = 10,
        .tu = 0,
        .tv = 14,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 70,
        .w = 238,
        .h = 10,
        .tu = 12,
        .tv = 14,
        .tw = 1,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 248,
        .y = 70,
        .w = 10,
        .h = 10,
        .tu = 14,
        .tv = 14,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinitem_plate_music_on[9] = {
    {
        .x = 0,
        .y = 0,
        .w = 10,
        .h = 10,
        .tu = 24,
        .tv = 0,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 0,
        .w = 238,
        .h = 10,
        .tu = 36,
        .tv = 0,
        .tw = 1,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 248,
        .y = 0,
        .w = 10,
        .h = 10,
        .tu = 38,
        .tv = 0,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 10,
        .w = 10,
        .h = 60,
        .tu = 24,
        .tv = 10,
        .tw = 10,
        .th = 1,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 10,
        .w = 238,
        .h = 60,
        .tu = 36,
        .tv = 10,
        .tw = 1,
        .th = 1,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 248,
        .y = 10,
        .w = 10,
        .h = 60,
        .tu = 38,
        .tv = 10,
        .tw = 10,
        .th = 1,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 0,
        .y = 70,
        .w = 10,
        .h = 10,
        .tu = 24,
        .tv = 14,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 70,
        .w = 238,
        .h = 10,
        .tu = 36,
        .tv = 14,
        .tw = 1,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 248,
        .y = 70,
        .w = 10,
        .h = 10,
        .tu = 38,
        .tv = 14,
        .tw = 10,
        .th = 10,
        .z = 0,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinitem_plate_rc_off[9] = {
    { .x = 0, .y = 0, .w = 12, .h = 18, .tu = 0, .tv = 0, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 12, .y = 0, .w = 236, .h = 18, .tu = 12, .tv = 0, .tw = 1, .th = 18, .z = 0, .flag = 0 },
    { .x = 248, .y = 0, .w = 12, .h = 18, .tu = 12, .tv = 0, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 0, .y = 18, .w = 12, .h = 18, .tu = 0, .tv = 6, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 12, .y = 18, .w = 236, .h = 18, .tu = 12, .tv = 6, .tw = 1, .th = 18, .z = 0, .flag = 0 },
    { .x = 248, .y = 18, .w = 12, .h = 18, .tu = 12, .tv = 6, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 0, .y = 0, .w = 0, .h = 0, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 0, .flag = -1 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_rc_on[9] = {
    { .x = 0, .y = 0, .w = 12, .h = 18, .tu = 24, .tv = 0, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 12, .y = 0, .w = 236, .h = 18, .tu = 36, .tv = 0, .tw = 1, .th = 18, .z = 0, .flag = 0 },
    { .x = 248, .y = 0, .w = 12, .h = 18, .tu = 36, .tv = 0, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 0, .y = 18, .w = 12, .h = 18, .tu = 24, .tv = 6, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 12, .y = 18, .w = 236, .h = 18, .tu = 36, .tv = 6, .tw = 1, .th = 18, .z = 0, .flag = 0 },
    { .x = 248, .y = 18, .w = 12, .h = 18, .tu = 36, .tv = 6, .tw = 12, .th = 18, .z = 0, .flag = 0 },
    { .x = 0, .y = 0, .w = 0, .h = 0, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 0, .flag = -1 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_arrow[2] = {
    { .x = -12, .y = 3, .w = 10, .h = 18, .tu = 0, .tv = 0, .tw = 10, .th = 18, .z = 0, .flag = 0 },
    { .x = 182, .y = 3, .w = 10, .h = 18, .tu = 10, .tv = 0, .tw = 10, .th = 18, .z = 0, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_th[1] = {
    { .x = 0, .y = 0, .w = 256, .h = 80, .tu = 0, .tv = 0, .tw = 256, .th = 80, .z = 32, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinitem_plate_option[1] = {
    { .x = 170, .y = 30, .w = 80, .h = 16, .tu = 0, .tv = 0, .tw = 80, .th = 16, .z = 32, .flag = 0 },
};
static struct _CWS_OBJ_SET netwinitem[5] = {
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 1, .ptex_obj = 9, .ptex = netwinitem_plate_mini_off, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 2, .ptex_obj = 0, .ptex = netwinitem_plate_arrow, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 2, .ptex_obj = 0, .ptex = &netwinitem_plate_arrow[1], .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 58, .ptex_obj = 0, .ptex = netwinitem_plate_th, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 33, .ptex_obj = 0, .ptex = netwinitem_plate_option, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 }
};







































































int NetWin_Item(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_ItemCode[win->step[1]] != 0) NetWin_ItemCode[win->step[1]](win);
    rtn = NetWin_ItemFunc[win->step[0]](win);
    return rtn;
}




static int NetWin_ItemInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 5; i++) {
        win->obj[i] = CwsObjCreate(&netwinitem[i]);
    }
    win->obj[1]->status &= ~2;
    win->obj[2]->status &= ~2;
    win->obj[3]->status &= ~2;
    win->obj[4]->status &= ~2;
    win->step[0]++;
    return 0;
}





static int NetWin_ItemMain(void) { return 0; }




static int NetWin_ItemEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}





void NetWin_ItemSetType(struct _CWS_WIN_W *win, int type) {
    struct _net_win_item_w *winw = (struct _net_win_item_w *)win->work;

    if (winw->type == type) return;
    winw->type = type;

    if (winw->status == 1) {
        if (type == 0) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_mini_on);
            win->obj[3]->status &= ~2;
        } else if (type == 1) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_big_on);
            win->obj[3]->status &= ~2;
        } else if (type == 3) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_music_on);
            win->obj[3]->status |= 2;
        } else {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_rc_on);
            win->obj[3]->status &= ~2;
        }
    } else {
        if (type == 0) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_mini_off);
            win->obj[3]->status &= ~2;
        } else if (type == 1) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_big_off);
            win->obj[3]->status &= ~2;
        } else if (type == 3) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_music_off);
            win->obj[3]->status |= 2;
        } else {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_rc_off);
            win->obj[3]->status &= ~2;
        }
    }
    return;
}



void NetWin_ItemSetSelect(struct _CWS_WIN_W *win, int status) {
    struct _net_win_item_w *winw = (struct _net_win_item_w *)win->work;

    if (winw->status == status) return;
    winw->status = status;

    if (winw->type == 0) {
        if (status == 2) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_mini_on);
            win->obj[1]->status |= 2;
            win->obj[2]->status |= 2;
        } else if (status == 1) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_mini_on);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        } else {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_mini_off);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        }
    } else if (winw->type == 1) {
        if (status == 2) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_big_on);
            win->obj[1]->status |= 2;
            win->obj[2]->status |= 2;
        } else if (status == 1) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_big_on);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        } else {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_big_off);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        }
    } else if (winw->type == 3) {
        if (status == 2) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_music_on);
            win->obj[1]->status |= 2;
            win->obj[2]->status |= 2;
        } else if (status == 1) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_music_on);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        } else {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_music_off);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        }
    } else {
        if (status == 2) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_rc_on);
            win->obj[1]->status |= 2;
            win->obj[2]->status |= 2;
        } else if (status == 1) {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_rc_on);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        } else {
            win->obj[0]->status |= 2;
            CwsObjChangePlate(win->obj[0], netwinitem_plate_rc_off);
            win->obj[1]->status &= ~2;
            win->obj[2]->status &= ~2;
        }
    }
    return;
}
