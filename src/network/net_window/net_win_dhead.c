#include "src/network/net_window/net_win_dhead.h"
#include "types/_nsv_player_list_file.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
int NetGrfGetDancerIDToNumberPoint(int dancer_id);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_DHeadFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_DHeadInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_DHeadMain,
    NetWin_DHeadEnd,
};
static void (*NetWin_DHeadCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinslby_plate_board[4] = {
    {
        .x = 0,
        .y = 0,
        .w = 36,
        .h = 24,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 84,
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
        .x = 403,
        .y = 0,
        .w = 58,
        .h = 24,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 464,
        .y = 0,
        .w = 58,
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
        .x = 39,
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
        .x = 39,
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
static void unused_dhead_types(struct _nsv_player_list_file *file) { file->status = 0; }
static struct _CWS_OBJ_SET netwininfosel[3] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 5,
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
int NetWin_DHead(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_DHeadCode[win->step[1]] != 0) NetWin_DHeadCode[win->step[1]](win);
    rtn = NetWin_DHeadFunc[win->step[0]](win);
    return rtn;
}




static int NetWin_DHeadInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwininfosel[i]);
    }

    win->work[0] = 0;

    CwsStrSetAll(win, 0, 6, 2, 0x100, 0x80, 0x80, 0x18000, 1, 0, (unsigned char *)"%02d", 0);



    CwsStrSetAll(win, 1, 0x5A, 2, 0x100, 0x80, 0x80, 0, 1, 0, (unsigned char *)"");


    CwsStrSetAll(win, 2, 0x195, 2, 0x100, 0x80, 0x80, 0x18000, 1, 0, (unsigned char *)"%04d", 0);



    CwsStrSetAll(win, 3, 0x1D2, 2, 0x100, 0x80, 0x80, 0x18000, 1, 0, (unsigned char *)"%04d", 0);



    win->step[0]++;
    return 0;
}
























static int NetWin_DHeadMain(void) { return 0; }




static int NetWin_DHeadEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}






void NetWin_DHeadSetNumber(struct _CWS_WIN_W *win, int _num) { CwsStrSetString(win, 0, (unsigned char *)"%02d", _num); }



void NetWin_DHeadSetName(struct _CWS_WIN_W *win, unsigned char *_name) { CwsStrSetString(win, 1, (unsigned char *)"%s", _name); }



void NetWin_DHeadSetDancer(struct _CWS_WIN_W *win, int dancer_id) {
    int num = NetGrfGetDancerIDToNumberPoint(dancer_id);
    win->obj[2]->tu = num % 8 * 42;
    win->obj[2]->tv = num / 8 * 24;
}


void NetWin_DHeadSetPoint(struct _CWS_WIN_W *win, int rule, unsigned int _point) {
    switch (rule) {
    case 0:
        CwsStrSetString(win, 2, (unsigned char *)"%04d", _point);
        break;
    case 1:
        CwsStrSetString(win, 2, (unsigned char *)"%04d", _point);
        break;
    case 2:
        break;
    case 3:
        break;
    }
}
