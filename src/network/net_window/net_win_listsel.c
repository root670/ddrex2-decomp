#include "src/network/net_window/net_win_listsel.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
char CwsStrSetCol(struct _CWS_WIN_W *win, int str_num, int col);
int NetGrfGetDancerIDToNumberPoint(int dancer_id);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_ListselFunc[3])(struct _CWS_WIN_W *) = { NetWin_ListselInit, NetWin_ListselMain, NetWin_ListselEnd };
static void (*NetWin_ListselCode[4])(struct _CWS_WIN_W *) = { 0, CwsWinOpen, CwsWinClose, CwsWinDestroy };
static struct _CWS_OBJ_TEX netwinslby_plate_board[1] = {
    { .x = 0, .y = 0, .w = 488, .h = 26, .tu = 0, .tv = 0, .tw = 488, .th = 26, .z = 0, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinslby_plate_chara_back[1] = {
    { .x = 110, .y = 1, .w = 42, .h = 24, .tu = 0, .tv = 0, .tw = 42, .th = 24, .z = 16, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinslby_plate_chara_face[1] = {
    { .x = 110, .y = 1, .w = 42, .h = 24, .tu = 0, .tv = 0, .tw = 42, .th = 24, .z = 32, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinslby_plate_status[3] = {
    { .x = 70, .y = 0, .w = 31, .h = 25, .tu = 0, .tv = 0, .tw = 31, .th = 25, .z = 16, .flag = 0 },
    { .x = 70, .y = 0, .w = 31, .h = 25, .tu = 0, .tv = 25, .tw = 31, .th = 25, .z = 16, .flag = 0 },
    { .x = 70, .y = 0, .w = 31, .h = 25, .tu = 0, .tv = 50, .tw = 31, .th = 25, .z = 16, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinslby_plate_line[4] = {
    { .x = -2, .y = -2, .w = 2, .h = 30, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 32, .flag = 0 },
    { .x = 488, .y = -2, .w = 2, .h = 30, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 32, .flag = 0 },
    { .x = 0, .y = -2, .w = 488, .h = 2, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 32, .flag = 0 },
    { .x = 0, .y = 26, .w = 488, .h = 2, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 32, .flag = 0 }
};
static struct _CWS_OBJ_SET netwinlistsel[5] = {
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = -1, .ptex_obj = 0, .ptex = netwinslby_plate_board, .r = 0, .g = 0, .b = 0, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = -1, .ptex_obj = 0, .ptex = netwinslby_plate_chara_back, .r = 0x61, .g = 0x61, .b = 0x61, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 0x18, .ptex_obj = 0, .ptex = netwinslby_plate_chara_face, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 0x1D, .ptex_obj = 0, .ptex = netwinslby_plate_status, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = -1, .ptex_obj = 4, .ptex = netwinslby_plate_line, .r = 0x31, .g = 0xEF, .b = 0x63, .a = 0x80 }
};
int NetWin_Listsel(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_ListselCode[win->step[1]] != 0) NetWin_ListselCode[win->step[1]](win);
    rtn = NetWin_ListselFunc[win->step[0]](win);
    return rtn;
}




static int NetWin_ListselInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 5; i++) {
        win->obj[i] = CwsObjCreate(&netwinlistsel[i]);
    }
    win->obj[2]->status &= ~2;
    win->obj[4]->status &= ~2;
    win->work[0] = 0;

    CwsStrSetAll(win, 0, 5, 2, 0x100, 0x80, 0x80, 0x10000, 1, 0, (unsigned char *)"%04d", 0);



    CwsStrSetAll(win, 1, 0x9D, 2, 0x100, 0x80, 0x80, 0, 1, 0, (unsigned char *)"");


    win->step[0]++;
    return 0;
}




static int NetWin_ListselMain(struct _CWS_WIN_W *win) {
    struct _net_win_listsel_w *winw = (struct _net_win_listsel_w *)win->work;
    int num;

    if (winw->player_list_file != 0) {
        CwsStrSetString(win, 1, (unsigned char *)"%s", winw->player_list_file->name);

        num = NetGrfGetDancerIDToNumberPoint(winw->player_list_file->dancer_number);
        win->obj[2]->tu = num % 8 * 42;
        win->obj[2]->tv = num / 8 * 24;
        win->obj[2]->status |= 2;

        switch (winw->player_list_file->status) {
        case 2:
            CwsObjChangePlate(win->obj[3], &netwinslby_plate_status[1]);
            CwsStrSetCol(win, 0, 5);
            CwsStrSetCol(win, 1, 5);
            break;
        case 3:
            CwsObjChangePlate(win->obj[3], &netwinslby_plate_status[2]);
            CwsStrSetCol(win, 0, 7);
            CwsStrSetCol(win, 1, 7);
            break;
        case 1:
            CwsObjChangePlate(win->obj[3], netwinslby_plate_status);
            CwsStrSetCol(win, 0, 0);
            CwsStrSetCol(win, 1, 0);
            break;
        default:
            CwsObjChangePlate(win->obj[3], netwinslby_plate_status);
            CwsStrSetCol(win, 0, 6);
            CwsStrSetCol(win, 1, 6);
            break;
        }

        win->obj[3]->status |= 2;
    } else {
        CwsStrSetString(win, 1, (unsigned char *)"");

        win->obj[2]->status &= ~2;
        win->obj[3]->status &= ~2;

        CwsStrSetCol(win, 0, 0);
        CwsStrSetCol(win, 1, 0);
    }
    return 0;
}




static int NetWin_ListselEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}




void NetWin_ListselSetNumber(struct _CWS_WIN_W *win, int _num) { CwsStrSetString(win, 0, (unsigned char *)"%04d", _num); }



void NetWin_ListselSetPlayerListFile(struct _CWS_WIN_W *win, struct _nsv_player_list_file *addr) { win->work[0] = (int)addr; }



void NetWin_ListselSetSelect(struct _CWS_WIN_W *win, char onoff) {
    if (onoff == 1) {
        win->obj[4]->status |= 2;
    } else {
        win->obj[4]->status &= ~2;
    }
}
