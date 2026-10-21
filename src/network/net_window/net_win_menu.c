#include "src/network/net_window/net_win_menu.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);

static int (*NetWin_MenuFunc[3])(struct _CWS_WIN_W *) = { NetWin_MenuInit, (int (*)(struct _CWS_WIN_W *))NetWin_MenuMain, NetWin_MenuEnd };
static void (*NetWin_MenuCode[4])(struct _CWS_WIN_W *) = { 0, CwsWinOpen, CwsWinClose, CwsWinDestroy };
static struct _CWS_OBJ_TEX netwinmenu_plate_board_off[3] = {
    { .x = 0, .y = 0, .w = 21, .h = 44, .tu = 52, .tv = 44, .tw = 21, .th = 44, .z = 0, .flag = 0 },
    { .x = 21, .y = 0, .w = 288, .h = 44, .tu = 72, .tv = 44, .tw = 1, .th = 44, .z = 0, .flag = 0 },
    { .x = 309, .y = 0, .w = 21, .h = 44, .tu = 73, .tv = 44, .tw = 21, .th = 44, .z = 0, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinmenu_plate_board_on[3] = {
    { .x = 0, .y = 0, .w = 21, .h = 44, .tu = 52, .tv = 0, .tw = 21, .th = 44, .z = 0, .flag = 0 },
    { .x = 21, .y = 0, .w = 288, .h = 44, .tu = 72, .tv = 0, .tw = 1, .th = 44, .z = 0, .flag = 0 },
    { .x = 309, .y = 0, .w = 21, .h = 44, .tu = 73, .tv = 0, .tw = 21, .th = 44, .z = 0, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinmenu_plate_board_col[4] = {
    { .x = 0, .y = 0, .w = 26, .h = 44, .tu = 0, .tv = 0, .tw = 26, .th = 44, .z = 16, .flag = 0 },
    { .x = 0, .y = 0, .w = 26, .h = 44, .tu = 0, .tv = 44, .tw = 26, .th = 44, .z = 16, .flag = 0 },
    { .x = 0, .y = 0, .w = 26, .h = 44, .tu = 0, .tv = 88, .tw = 26, .th = 44, .z = 16, .flag = 0 },
    { .x = 0, .y = 0, .w = 26, .h = 44, .tu = 26, .tv = 44, .tw = 26, .th = 44, .z = 16, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinmenu_plate_font[6] = {
    { .x = 26, .y = 10, .w = 192, .h = 24, .tu = 0, .tv = 0, .tw = 192, .th = 24, .z = 32, .flag = 0 },
    { .x = 26, .y = 10, .w = 192, .h = 24, .tu = 0, .tv = 24, .tw = 192, .th = 24, .z = 32, .flag = 0 },
    { .x = 26, .y = 10, .w = 192, .h = 24, .tu = 0, .tv = 48, .tw = 192, .th = 24, .z = 32, .flag = 0 },
    { .x = 26, .y = 10, .w = 192, .h = 24, .tu = 0, .tv = 72, .tw = 192, .th = 24, .z = 32, .flag = 0 },
    { .x = 26, .y = 10, .w = 192, .h = 24, .tu = 0, .tv = 96, .tw = 192, .th = 24, .z = 32, .flag = 0 },
    { .x = 26, .y = 10, .w = 192, .h = 24, .tu = 0, .tv = 120, .tw = 192, .th = 24, .z = 32, .flag = 0 }
};
static struct _CWS_OBJ_SET netwinmenu[3] = {
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 11, .ptex_obj = 3, .ptex = netwinmenu_plate_board_off, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 11, .ptex_obj = 0, .ptex = netwinmenu_plate_board_col, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 12, .ptex_obj = 0, .ptex = netwinmenu_plate_font, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 }
};






































































































































int NetWin_Menu(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_MenuCode[win->step[1]] != 0) NetWin_MenuCode[win->step[1]](win);
    rtn = NetWin_MenuFunc[win->step[0]](win);
    return rtn;
}




static int NetWin_MenuInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinmenu[i]);
    }
    win->step[0]++;
    return 0;
}





static int NetWin_MenuMain(void) { return 0; }




static int NetWin_MenuEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}





void NetWin_MenuSetFont(struct _CWS_WIN_W *win, int font_num) {
    struct _net_win_menu_w *winw = (struct _net_win_menu_w *)win->work;

    if (winw->font_num != font_num) {
        winw->font_num = font_num;
        switch (font_num)
        {
        case 0:
            CwsObjChangePlate(win->obj[2], netwinmenu_plate_font);
            CwsObjChangePlate(win->obj[1], netwinmenu_plate_board_col);
            break;

        case 1:
            CwsObjChangePlate(win->obj[2], &netwinmenu_plate_font[1]);
            CwsObjChangePlate(win->obj[1], &netwinmenu_plate_board_col[1]);
            break;

        case 2:
            CwsObjChangePlate(win->obj[2], &netwinmenu_plate_font[2]);
            CwsObjChangePlate(win->obj[1], &netwinmenu_plate_board_col[2]);
            break;

        case 3:
            CwsObjChangePlate(win->obj[2], &netwinmenu_plate_font[3]);
            CwsObjChangePlate(win->obj[1], netwinmenu_plate_board_col);
            break;

        case 4:
            CwsObjChangePlate(win->obj[2], &netwinmenu_plate_font[4]);
            CwsObjChangePlate(win->obj[1], &netwinmenu_plate_board_col[1]);
            break;

        case 5:
            CwsObjChangePlate(win->obj[2], &netwinmenu_plate_font[5]);
            CwsObjChangePlate(win->obj[1], &netwinmenu_plate_board_col[3]);
            break;

        default: {
            return;
        }
        }
    }
}



void NetWin_MenuSetSelect(struct _CWS_WIN_W *win, int status) {
    struct _net_win_menu_w *winw = (struct _net_win_menu_w *)win->work;

    if (winw->board_status != status) {
        winw->board_status = status;

        if (status == 1) {
            CwsObjChangePlate(win->obj[0], netwinmenu_plate_board_on);
        } else {
            CwsObjChangePlate(win->obj[0], netwinmenu_plate_board_off);
        }
    }
}
