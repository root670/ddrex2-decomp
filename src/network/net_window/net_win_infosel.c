#include "src/network/net_window/net_win_infosel.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
int NetGrfGetDancerIDToNumberPoint(int dancer_id);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_InfoselFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_InfoselInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_InfoselMain,
    NetWin_InfoselEnd,
};
static void (*NetWin_InfoselCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinslby_plate_board[3] = {
    {
        .x = 0,
        .y = 0,
        .w = 50,
        .h = 24,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 98,
        .y = 0,
        .w = 316,
        .h = 24,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 417,
        .y = 0,
        .w = 114,
        .h = 24,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 0,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinslby_plate_chara_back[1] = {
    {
        .x = 53,
        .y = 0,
        .w = 42,
        .h = 24,
        .tu = 0,
        .tv = 0,
        .tw = 42,
        .th = 24,
        .z = 16,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinslby_plate_chara_face[1] = {
    {
        .x = 53,
        .y = 0,
        .w = 42,
        .h = 24,
        .tu = 0,
        .tv = 0,
        .tw = 42,
        .th = 24,
        .z = 32,
        .flag = 0,
    },
};
static struct _CWS_OBJ_SET netwininfosel[3] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 3,
        .ptex = netwinslby_plate_board,
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 0x40,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 0,
        .ptex = netwinslby_plate_chara_back,
        .r = 0x61,
        .g = 0x61,
        .b = 0x61,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x18,
        .ptex_obj = 0,
        .ptex = netwinslby_plate_chara_face,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};
int NetWin_Infosel(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_InfoselCode[win->step[1]] != 0) NetWin_InfoselCode[win->step[1]](win);
    rtn = NetWin_InfoselFunc[win->step[0]](win);
    return rtn;
}




static int NetWin_InfoselInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwininfosel[i]);
    }
    win->obj[2]->status &= ~2;

    CwsStrSetAll(win, 0, 6, 2, 0x100, 0x80, 0x80, 0x18000, 1, 0, (unsigned char *)"%03d", 0);



    CwsStrSetAll(win, 1, 0x72, 2, 0x100, 0x80, 0x80, 0, 1, 0, (unsigned char *)"");


    CwsStrSetAll(win, 2, 0x20E, 2, 0x100, 0x80, 0x80, 0x1C000, 1, 0, (unsigned char *)"%06d", 0);



    win->step[0]++;
    return 0;
}





static int NetWin_InfoselMain(void) { return 0; }




static int NetWin_InfoselEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}






void NetWin_InfoselSetNumber(struct _CWS_WIN_W *win, int _num) { CwsStrSetString(win, 0, (unsigned char *)"%03d", _num); }



void NetWin_InfoselSetName(struct _CWS_WIN_W *win, unsigned char *_name) { CwsStrSetString(win, 1, (unsigned char *)"%s", _name); }


void NetWin_InfoselSetDancer(struct _CWS_WIN_W *win, int _num) {
    int num;
    num = NetGrfGetDancerIDToNumberPoint(_num);
    win->obj[2]->tu = num % 8 * 42;
    win->obj[2]->tv = num / 8 * 24;
    win->obj[2]->status |= 2;
}


void NetWin_InfoselSetPoint(struct _CWS_WIN_W *win, int rule, unsigned int _point) {
    switch (rule) {
    case 0:
        CwsStrSetString(win, 2, (unsigned char *)"%06d", _point);
        break;
    case 1:
        CwsStrSetString(win, 2, (unsigned char *)"%08d", _point);
        break;
    case 2:
        CwsStrSetString(win, 2, (unsigned char *)"%02d:%02d:%02d", _point / 100 / 60, _point / 100 % 60, _point % 100);

        break;
    case 3:
        CwsStrSetString(win, 2, (unsigned char *)"%06d", _point);
        break;
    }
}
