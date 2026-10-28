#include "src/network/net_window/net_win_perrank.h"
extern unsigned char *D_01029FE4;

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
void CsFontPrintf(short _x, short _y, int _bri, int _pri, int _col, int _alpha,
                  int _tex_id, int _mode, int _type, unsigned char *_str, ...);
void func_00125540(int);
void func_00125550(int);
void func_00125520(int);

static int (*NetWin_PerRankFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_PerRankInit,
    NetWin_PerRankMain,
    NetWin_PerRankEnd,
};
static void (*NetWin_PerRankCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static unsigned char *perstats_title[5];
static struct _CWS_OBJ_TEX per_stats_rank[3] = {
    {
        .x = 0x26,
        .y = 0x1,
        .w = 0x4A,
        .h = 0xB,
        .tu = 0x0,
        .tv = 0x4D,
        .tw = 0x4A,
        .th = 0xB,
        .z = 0x20,
        .flag = 0x0,
    },
    {
        .x = 0xEE,
        .y = 0x1,
        .w = 0x4A,
        .h = 0xB,
        .tu = 0x0,
        .tv = 0xB,
        .tw = 0x4A,
        .th = 0xB,
        .z = 0x20,
        .flag = 0x0,
    },
    {
        .x = 0x187,
        .y = 0x1,
        .w = 0x4A,
        .h = 0xB,
        .tu = 0x0,
        .tv = 0x58,
        .tw = 0x4A,
        .th = 0xB,
        .z = 0x20,
        .flag = 0x0,
    },
};
static struct _CWS_OBJ_TEX per_stats_title[3] = {
    {
        .x = 0x0,
        .y = 0x0,
        .w = 0xB4,
        .h = 0x10,
    },
    {
        .x = 0xC8,
        .y = 0x0,
        .w = 0x96,
        .h = 0x10,
    },
    {
        .x = 0x161,
        .y = 0x0,
        .w = 0x96,
        .h = 0x10,
    },
};
static struct _CWS_OBJ_TEX per_stats_borad[18] = {
    {
        .x = 0x0,
        .y = 0x13,
        .w = 0xB4,
        .h = 0x18,
    },
    {
        .x = 0xC8,
        .y = 0x13,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x161,
        .y = 0x13,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x0,
        .y = 0x2E,
        .w = 0xB4,
        .h = 0x18,
    },
    {
        .x = 0xC8,
        .y = 0x2E,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x161,
        .y = 0x2E,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x0,
        .y = 0x49,
        .w = 0xB4,
        .h = 0x18,
    },
    {
        .x = 0xC8,
        .y = 0x49,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x161,
        .y = 0x49,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x0,
        .y = 0x64,
        .w = 0xB4,
        .h = 0x18,
    },
    {
        .x = 0xC8,
        .y = 0x64,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x161,
        .y = 0x64,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x0,
        .y = 0x7F,
        .w = 0xB4,
        .h = 0x18,
    },
    {
        .x = 0xC8,
        .y = 0x7F,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x161,
        .y = 0x7F,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x0,
        .y = 0x9A,
        .w = 0xB4,
        .h = 0x18,
    },
    {
        .x = 0xC8,
        .y = 0x9A,
        .w = 0x96,
        .h = 0x18,
    },
    {
        .x = 0x161,
        .y = 0x9A,
        .w = 0x96,
        .h = 0x18,
    },
};
static struct _CWS_OBJ_SET netwinperhed[3] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 3,
        .ptex = per_stats_title,
        .a = 0x40,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 0x12,
        .ptex = per_stats_borad,
        .a = 0x40,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x10,
        .ptex_obj = 3,
        .ptex = per_stats_rank,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_PerRank(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_PerRankCode[win->step[1]] != 0)
        NetWin_PerRankCode[win->step[1]](win);
    rtn = NetWin_PerRankFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_PerRankInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinperhed[i]);
    }
    win->step[0]++;
    return 0;
}

static int NetWin_PerRankMain(struct _CWS_WIN_W *win) {
    int loop;
    int i;
    int pri;
    struct _nsv_user_rc_param_work *rc_data;

    loop = *(int *)(D_01029FE4 + 0x554);
    loop = loop < 6 ? loop : 6;
    pri = win->v.z + 0x100;
    func_00125540(win->v.a);
    func_00125550(0x80);
    func_00125520(win->v.z + 0x100);
    if (win->v.a > 0 && win->v.a < 0x81 && (win->status & 2)) {
        for (i = 0; i < 6; i++) {
            rc_data = (struct _nsv_user_rc_param_work *)(D_01029FE4 + i * 0x14 + 0x55C);
            CsFontPrintf(win->v.x + 4, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a, 0xFB, 0x1250, 0, (unsigned char *)"%s:NO:%2d", (unsigned char *)"NORMAL", rc_data->ranking_challenge_num);

            if (i >= loop) {
                CsFontPrintf(win->v.x + 0x113, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", 0);
                CsFontPrintf(win->v.x + 0x1AC, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", 0);
            } else {
                CsFontPrintf(win->v.x + 0x113, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", rc_data->rank_num);
                CsFontPrintf(win->v.x + 0x1AC, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", rc_data->score);
            }
        }
    }
    return 0;
}

static int NetWin_PerRankEnd(struct _CWS_WIN_W *win) {
    win->status |= 4;
    return 0;
}
