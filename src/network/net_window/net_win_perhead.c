#include "src/network/net_window/net_win_perhead.h"

#define D_01029FE4 (*(int *)0x01029FE4)

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
void func_00125540(int);
void func_00125550(int);
void func_00125520(int);
void CsFontPrintf(short _x, short _y, int _bri, int _pri, int _col, int _alpha,
                  int _tex_id, int _mode, int _type, unsigned char *_str, ...);

static int (*NetWin_PerHeadFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_PerHeadInit,
    NetWin_PerHeadMain,
    NetWin_PerHeadEnd,
};
static void (*NetWin_PerHeadCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static unsigned char *perstats_title[5];
static struct _CWS_OBJ_TEX per_stats_match[4] = {
    {
        .x = 0x92,
        .y = 1,
        .w = 0x4A,
        .h = 0xB,
        .tu = 0,
        .tv = 0x16,
        .tw = 0x4A,
        .th = 0xB,
        .z = 0x20,
        .flag = 0,
    },
    {
        .x = 0xF9,
        .y = 1,
        .w = 0x4A,
        .h = 0xB,
        .tu = 0,
        .tv = 0x21,
        .tw = 0x4A,
        .th = 0xB,
        .z = 0x20,
        .flag = 0,
    },
    {
        .x = 0x160,
        .y = 1,
        .w = 0x4A,
        .h = 0xB,
        .tu = 0,
        .tv = 0x2C,
        .tw = 0x4A,
        .th = 0xB,
        .z = 0x20,
        .flag = 0,
    },
    {
        .x = 0x1C7,
        .y = 1,
        .w = 0x4A,
        .h = 0xB,
        .tu = 0,
        .tv = 0x37,
        .tw = 0x4A,
        .th = 0xB,
        .z = 0x20,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX per_stats_title[5] = {
    {
        .x = -0xA,
        .y = 0,
        .w = 0x82,
        .h = 0x10,
    },
    {
        .x = 0x85,
        .y = 0,
        .w = 0x64,
        .h = 0x10,
    },
    {
        .x = 0xEC,
        .y = 0,
        .w = 0x64,
        .h = 0x10,
    },
    {
        .x = 0x153,
        .y = 0,
        .w = 0x64,
        .h = 0x10,
    },
    {
        .x = 0x1BA,
        .y = 0,
        .w = 0x64,
        .h = 0x10,
    },
};
static struct _CWS_OBJ_TEX per_stats_borad[30] = {
    {
        .x = -0xA,
        .y = 0x13,
        .w = 0x82,
        .h = 0x18,
    },
    {
        .x = 0x85,
        .y = 0x13,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0xEC,
        .y = 0x13,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x153,
        .y = 0x13,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x1BA,
        .y = 0x13,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = -0xA,
        .y = 0x2E,
        .w = 0x82,
        .h = 0x18,
    },
    {
        .x = 0x85,
        .y = 0x2E,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0xEC,
        .y = 0x2E,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x153,
        .y = 0x2E,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x1BA,
        .y = 0x2E,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = -0xA,
        .y = 0x49,
        .w = 0x82,
        .h = 0x18,
    },
    {
        .x = 0x85,
        .y = 0x49,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0xEC,
        .y = 0x49,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x153,
        .y = 0x49,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x1BA,
        .y = 0x49,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = -0xA,
        .y = 0x64,
        .w = 0x82,
        .h = 0x18,
    },
    {
        .x = 0x85,
        .y = 0x64,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0xEC,
        .y = 0x64,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x153,
        .y = 0x64,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x1BA,
        .y = 0x64,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = -0xA,
        .y = 0x7F,
        .w = 0x82,
        .h = 0x18,
    },
    {
        .x = 0x85,
        .y = 0x7F,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0xEC,
        .y = 0x7F,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x153,
        .y = 0x7F,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x1BA,
        .y = 0x7F,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = -0xA,
        .y = 0x9A,
        .w = 0x82,
        .h = 0x18,
    },
    {
        .x = 0x85,
        .y = 0x9A,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0xEC,
        .y = 0x9A,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x153,
        .y = 0x9A,
        .w = 0x64,
        .h = 0x18,
    },
    {
        .x = 0x1BA,
        .y = 0x9A,
        .w = 0x64,
        .h = 0x18,
    },
};
static struct _CWS_OBJ_SET netwinperhed[3] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 5,
        .ptex = per_stats_title,
        .a = 0x40,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 0x1E,
        .ptex = per_stats_borad,
        .a = 0x40,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x10,
        .ptex_obj = 4,
        .ptex = per_stats_match,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

static int NetWin_PerHeadMain(struct _CWS_WIN_W *win) {
    int loop;
    int i;
    int week;
    int pri;
    struct _nsv_user_htoh_week_log_work *log;

    loop = *(int *)(D_01029FE4 + 0x2C);
    loop = loop < 6 ? loop : 6;
    pri = win->v.z + 0x100;
    func_00125540(win->v.a);
    func_00125550(0x80);
    func_00125520(win->v.z + 0x100);
    if (win->v.a > 0 && win->v.a < 0x81 && (win->status & 2)) {
        for (i = 0; i < 6; i++) {
            log = (struct _nsv_user_htoh_week_log_work *)(D_01029FE4 + i * 0xC + 0x88);
            week = i + 1;
            CsFontPrintf(win->v.x + 0xE, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a,
                         0xFB, 0x5250, 0, (unsigned char *)"%d", week);
            if (week % 100 == 11 || week % 100 == 12 || week % 100 == 13) {
                CsFontPrintf(win->v.x + 0xE, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a,
                             0xFB, 0x1250, 0, (unsigned char *)"th WEEKS");
            } else if (week % 10 == 1) {
                if (week == 1)
                    CsFontPrintf(win->v.x + 0xE, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                                 win->v.a, 0xFB, 0x1250, 0, (unsigned char *)"st WEEK");
                else
                    CsFontPrintf(win->v.x + 0xE, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                                 win->v.a, 0xFB, 0x1250, 0, (unsigned char *)"st WEEKS");
            } else if (week % 10 == 2) {
                CsFontPrintf(win->v.x + 0xE, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a,
                             0xFB, 0x1250, 0, (unsigned char *)"nd WEEKS");
            } else if (week % 10 == 3) {
                CsFontPrintf(win->v.x + 0xE, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a,
                             0xFB, 0x1250, 0, (unsigned char *)"rd WEEKS");
            } else {
                CsFontPrintf(win->v.x + 0xE, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0, win->v.a,
                             0xFB, 0x1250, 0, (unsigned char *)"th WEEKS");
            }
            if (i >= loop) {
                CsFontPrintf(win->v.x + 0xB7, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", 0);
                CsFontPrintf(win->v.x + 0x11E, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", 0);
                CsFontPrintf(win->v.x + 0x185, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", 0);
                CsFontPrintf(win->v.x + 0x1EC, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", 0);
            } else {
                CsFontPrintf(win->v.x + 0xB7, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", log->match);
                CsFontPrintf(win->v.x + 0x11E, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", log->win);
                CsFontPrintf(win->v.x + 0x185, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", log->lose);
                CsFontPrintf(win->v.x + 0x1EC, win->v.y + (i * 0x1B + 0x15), 0x80, pri, 0,
                             win->v.a, 0xFB, 0x9650, 0, (unsigned char *)"%04d", log->draw);
            }
        }
    }
    return 0;
}

static int NetWin_PerHeadInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinperhed[i]);
    }
    win->step[0]++;
    return 0;
}

int NetWin_PerHead(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_PerHeadCode[win->step[1]] != 0)
        NetWin_PerHeadCode[win->step[1]](win);
    rtn = NetWin_PerHeadFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_PerHeadEnd(struct _CWS_WIN_W *win) {
    win->status |= 4;
    return 0;
}
