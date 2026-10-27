#include "src/network/net_window/net_win_peruser.h"
#include "types/_NSV_USER_FILE_WORK.h"
extern struct _NSV_USER_FILE_WORK *D_01029FE4;

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id);
int NetGrfGetDancerIDToNumberPoint(int dancer_id);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_PerUserPointFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_PerUserPointInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_PerUserPointMain,
    NetWin_PerUserPointEnd,
};
static void (*NetWin_PerUserCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinperuser_chara[1] = {
    {
        .x = 0,
        .y = 0,
        .w = 0x2A,
        .h = 0x3E,
        .tu = 0,
        .tv = 0,
        .tw = 0x2A,
        .th = 0x3E,
        .z = 0x20,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinperuser_name[1] = {
    {
        .x = 0x2A,
        .y = 2,
        .w = 0x40,
        .h = 0x10,
        .tu = 0,
        .tv = 0,
        .tw = 0x40,
        .th = 0x10,
        .z = 0x10,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinperuser_point[1] = {
    {
        .x = 0x2A,
        .y = 0x18,
        .w = 0x40,
        .h = 0x10,
        .tu = 0,
        .tv = 0x20,
        .tw = 0x40,
        .th = 0x10,
        .z = 0,
        .flag = 0,
    },
};
static struct _CWS_OBJ_SET netwinperuser0[3] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 6,
        .ptex_obj = 0,
        .ptex = netwinperuser_chara,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 8,
        .ptex_obj = 0,
        .ptex = netwinperuser_name,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 8,
        .ptex_obj = 0,
        .ptex = netwinperuser_point,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

static void peruser_user_file(struct _NSV_USER_FILE_WORK *file) { file->status = 0; }

static int NetWin_PerUserPointEnd(struct _CWS_WIN_W *win) {
    win->status |= 4;
    return 0;
}

static int NetWin_PerUserPointMain(void) { return 0; }

static int NetWin_PerUserPointInit(struct _CWS_WIN_W *win) {
    int i;
    int num;
    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinperuser0[i]);
    }
    CwsStrSetAll(win, 0, 0x6A, 0, 0x100, 0x80, 0x80, 0, 2, 0, D_01029FE4->name);
    CwsStrSetAll(win, 1, 0x6A, 0x18, 0x100, 0x80, 0x80, 1, 4, 3, (unsigned char *)"%06d", D_01029FE4->points.year_param.points);
    CwsStrSetTex(win, 1, 9);
    num = NetGrfGetDancerIDToNumberPoint(D_01029FE4->dancer_number);
    win->obj[0]->tu = num % 8 * 42;
    win->obj[0]->tv = num / 8 * 62;
    win->step[0]++;
    return 0;
}

int NetWin_PerUserPoint(struct _CWS_WIN_W *win) {
    int rtn;
    if (NetWin_PerUserCode[win->step[1]]) NetWin_PerUserCode[win->step[1]](win);
    rtn = NetWin_PerUserPointFunc[win->step[0]](win);
    return rtn;
}
