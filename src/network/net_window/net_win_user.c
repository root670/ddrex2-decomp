#include "src/network/net_window/net_win_user.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id);
int NetGrfGetDancerIDToNumberPoint(int dancer_id);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void func_00124800(anon_1_96 *sp);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_UserFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_UserInit,
    NetWin_UserMain,
    NetWin_UserEnd,
};
static void (*NetWin_UserCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinuser_plate_board[1] = {
    {
        .x = 0,
        .y = 0,
        .w = 640,
        .h = 112,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 0,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinuser_plate_board2[4] = {
    {
        .x = 262,
        .y = 54,
        .w = 86,
        .h = 17,
        .tu = 22,
        .tv = 102,
        .tw = 1,
        .th = 17,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 348,
        .y = 54,
        .w = 20,
        .h = 17,
        .tu = 22,
        .tv = 102,
        .tw = 20,
        .th = 17,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 262,
        .y = 88,
        .w = 200,
        .h = 17,
        .tu = 22,
        .tv = 102,
        .tw = 1,
        .th = 17,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 462,
        .y = 88,
        .w = 20,
        .h = 17,
        .tu = 22,
        .tv = 102,
        .tw = 20,
        .th = 17,
        .z = 16,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinuser_plate_board3[1] = {
    {
        .x = 24,
        .y = 58,
        .w = 228,
        .h = 48,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 16,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinuser_plate_obj[5] = {
    {
        .x = 28,
        .y = 36,
        .w = 66,
        .h = 17,
        .tu = 0,
        .tv = 85,
        .tw = 66,
        .th = 17,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 28,
        .y = 58,
        .w = 56,
        .h = 17,
        .tu = 0,
        .tv = 34,
        .tw = 56,
        .th = 17,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 140,
        .y = 58,
        .w = 112,
        .h = 17,
        .tu = 0,
        .tv = 51,
        .tw = 112,
        .th = 17,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 262,
        .y = 40,
        .w = 56,
        .h = 17,
        .tu = 0,
        .tv = 34,
        .tw = 56,
        .th = 17,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 262,
        .y = 74,
        .w = 136,
        .h = 17,
        .tu = 0,
        .tv = 68,
        .tw = 136,
        .th = 17,
        .z = 32,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinuser_plate_namewaku[3] = {
    {
        .x = 24,
        .y = 6,
        .w = 8,
        .h = 32,
        .tu = 0,
        .tv = 0,
        .tw = 8,
        .th = 32,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 32,
        .y = 6,
        .w = 360,
        .h = 32,
        .tu = 8,
        .tv = 0,
        .tw = 1,
        .th = 32,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 392,
        .y = 6,
        .w = 20,
        .h = 32,
        .tu = 8,
        .tv = 0,
        .tw = 20,
        .th = 32,
        .z = 16,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinuser_plate_chara[1] = {
    {
        .x = 28,
        .y = 9,
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
static struct _CWS_OBJ_SET netwinuser[6] = {
    {
        .func = (int (*)(void *, void *))NetWin_UserBoardDisp,
        .tex_num = -1,
        .ptex_obj = 0,
        .ptex = netwinuser_plate_board,
        .r = 0x0,
        .g = 0x0,
        .b = 0x0,
        .a = 0x30,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 8,
        .ptex_obj = 4,
        .ptex = netwinuser_plate_board2,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 0,
        .ptex = netwinuser_plate_board3,
        .r = 0x0,
        .g = 0x0,
        .b = 0x0,
        .a = 0x66,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 8,
        .ptex_obj = 5,
        .ptex = netwinuser_plate_obj,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 7,
        .ptex_obj = 3,
        .ptex = netwinuser_plate_namewaku,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 24,
        .ptex_obj = 0,
        .ptex = netwinuser_plate_chara,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

void NetWin_UserSetUserFile(struct _CWS_WIN_W *win, struct _NSV_USER_FILE_WORK *addr) { ((struct _net_win_user_w *)win->work)->user_file = addr; }

static void NetWin_UserBoardDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw) {
    anon_1_96 g3;
    int dx;
    int dy;
    int dw;
    int dh;
    int dr;
    int dg;
    int db;
    int da;
    int dz;
    int mx, my, mz;

    if (objw == 0) return;
    if ((objw->status & 2) == 0) return;

    if (win->master_link == 0) {
        dx = win->v.x + objw->x;
        dy = win->v.y + objw->y;
        dz = win->v.z + objw->z;
    } else {
        mx = win->master_link->v.x + win->v.x; dx = mx + objw->x;
        my = win->master_link->v.y + win->v.y; dy = my + objw->y;
        mz = win->master_link->v.z + win->v.z; dz = mz + objw->z;

    }

    dw = objw->w;
    dh = objw->h;
    dr = win->v.bri * (win->v.r * objw->red) / 0x4000;
    dg = win->v.bri * (win->v.g * objw->green) / 0x4000;
    db = win->v.bri * (win->v.b * objw->blue) / 0x4000;
    da = win->v.a * objw->alpha / 0x80;

    g3.flg = 0;
    g3.flg |= 0x100;

    g3.x0.fd = dx;
    g3.y0.fd = dy;
    g3.z0 = dz;
    g3.x1.fd = dx + dw;
    g3.y1.fd = dy;
    g3.z1 = dz;
    g3.x2.fd = dx;
    g3.y2.fd = dy + dh;
    g3.z2 = dz;
    g3.r0 = dr;
    g3.g0 = dg;
    g3.b0 = db;
    g3.a0 = da;
    g3.r1 = dr;
    g3.g1 = dg;
    g3.b1 = db;
    g3.a1 = 0;
    g3.r2 = dr;
    g3.g2 = dg;
    g3.b2 = db;
    g3.a2 = da;
    func_00124800(&g3);

    g3.flg = 0;
    g3.flg |= 0x100;

    g3.x0.fd = dx;
    g3.y0.fd = dy + dh;
    g3.z0 = dz;
    g3.x1.fd = dx + dw;
    g3.y1.fd = dy;
    g3.z1 = dz;
    g3.x2.fd = dx + dw;
    g3.y2.fd = dy + dh;
    g3.z2 = dz;
    g3.r0 = dr;
    g3.g0 = dg;
    g3.b0 = db;
    g3.a0 = da;
    g3.r1 = dr;
    g3.g1 = dg;
    g3.b1 = db;
    g3.a1 = 0;
    g3.r2 = dr;
    g3.g2 = dg;
    g3.b2 = db;
    g3.a2 = 0;
    func_00124800(&g3);
}

static int NetWin_UserEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}

static int NetWin_UserMain(struct _CWS_WIN_W *win) {
    struct _net_win_user_w *winw;
    int disp_max;
    int num;

    winw = (struct _net_win_user_w *)win->work;
    if (winw->user_file != 0) {
        num = NetGrfGetDancerIDToNumberPoint(winw->user_file->dancer_number);
        win->obj[5]->tu = num % 8 * 42;
        win->obj[5]->tv = num / 8 * 24;

        CwsStrSetString(win, 2, (unsigned char *)"%s", winw->user_file->name);

        disp_max = winw->user_file->points.week_param.rank_num;
        CwsStrSetString(win, 3, (unsigned char *)"%04d", disp_max < 9999 ? disp_max : 9999);
        disp_max = winw->user_file->htoh.week_param.rank_num;
        CwsStrSetString(win, 4, (unsigned char *)"%04d", disp_max < 9999 ? disp_max : 9999);
        disp_max = winw->user_file->points.week_param.points;
        CwsStrSetString(win, 5, (unsigned char *)"%06d", disp_max < 999999 ? disp_max : 999999);
        disp_max = winw->user_file->htoh.week_param.win;
        CwsStrSetString(win, 6, (unsigned char *)"%04d", disp_max < 9999 ? disp_max : 9999);
        disp_max = winw->user_file->htoh.week_param.lose;
        CwsStrSetString(win, 7, (unsigned char *)"%04d", disp_max < 9999 ? disp_max : 9999);
        disp_max = winw->user_file->htoh.week_param.draw;
        CwsStrSetString(win, 8, (unsigned char *)"%04d", disp_max < 9999 ? disp_max : 9999);
    }
    return 0;
}

static int NetWin_UserInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 6; i++) {
        win->obj[i] = CwsObjCreate(&netwinuser[i]);
    }

    CwsStrSetAll(win, 0, 0x146, 0x58, 0x100, 0x80, 0x80, 0, 4, 0, (unsigned char *)"/");
    CwsStrSetTex(win, 0, 9);
    CwsStrSetAll(win, 1, 0x18F, 0x58, 0x100, 0x80, 0x80, 0, 4, 0, (unsigned char *)"/");
    CwsStrSetTex(win, 1, 9);
    CwsStrSetAll(win, 2, 0x4A, 8, 0x100, 0x80, 0x80, 0, 2, 0, (unsigned char *)"%s", 0);
    CwsStrSetAll(win, 3, 0x18, 0x4B, 0x100, 0x80, 0x80, 1, 3, 3, (unsigned char *)"%04d", 0);
    CwsStrSetTex(win, 3, 0x1B);
    CwsStrSetAll(win, 4, 0x8C, 0x4B, 0x100, 0x80, 0x80, 1, 3, 3, (unsigned char *)"%04d", 0);
    CwsStrSetTex(win, 4, 0x1B);
    CwsStrSetAll(win, 5, 0x106, 0x36, 0x100, 0x80, 0x80, 1, 4, 3, (unsigned char *)"%06d", 0);
    CwsStrSetTex(win, 5, 9);
    CwsStrSetAll(win, 6, 0x106, 0x58, 0x100, 0x80, 0x80, 1, 4, 2, (unsigned char *)"%04d", 0);
    CwsStrSetTex(win, 6, 9);
    CwsStrSetAll(win, 7, 0x14F, 0x58, 0x100, 0x80, 0x80, 1, 4, 1, (unsigned char *)"%04d", 0);
    CwsStrSetTex(win, 7, 9);
    CwsStrSetAll(win, 8, 0x198, 0x58, 0x100, 0x80, 0x80, 1, 4, 4, (unsigned char *)"%04d", 0);
    CwsStrSetTex(win, 5, 9);

    win->step[0]++;
    return 0;
}

int NetWin_User(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_UserCode[win->step[1]] != 0) NetWin_UserCode[win->step[1]](win);
    rtn = NetWin_UserFunc[win->step[0]](win);
    return rtn;
}
