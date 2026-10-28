#include "src/network/net_window/net_win_perstats.h"

#define D_01029FE4 (*(int *)0x01029FE4)

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
void func_00121270(int color, unsigned char *fmt, unsigned char *string, float x, float y);
void func_00125540(int);
void func_00125550(int);
void func_00125520(int);
void CsFontPrintf(short _x, short _y, int _bri, int _pri, int _col, int _alpha,
                  int _tex_id, int _mode, int _type, unsigned char *_str, ...);

static int (*NetWin_PerStatsFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_PerStatsInit,
    NetWin_PerStatsMain,
    NetWin_PerStatsEnd,
};
static void (*NetWin_PerStatsCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static unsigned char *perstats_title[5] = {
    (unsigned char *)"TOTAL ",
    (unsigned char *)"SCORE",
    (unsigned char *)"COMBO",
    (unsigned char *)"SURVIVAL",
    (unsigned char *)"ERROR",
};
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
        .x = 0,
        .y = 0,
        .w = 0x6E,
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
static struct _CWS_OBJ_TEX per_stats_borad[20] = {
    {
        .x = 0,
        .y = 0x13,
        .w = 0x6E,
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
        .x = 0,
        .y = 0x2E,
        .w = 0x6E,
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
        .x = 0,
        .y = 0x49,
        .w = 0x6E,
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
        .x = 0,
        .y = 0x64,
        .w = 0x6E,
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
        .ptex_obj = 0x14,
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

static int NetWin_PerStatsMain(struct _CWS_WIN_W *win) {
    int pri;

    pri = win->v.z + 0x100;
    func_00125540(win->v.a);
    func_00125550(0x80);
    func_00125520(win->v.z + 0x100);
    if (win->v.a > 0 && win->v.a < 0x81 && (win->status & 2)) {
        func_00121270(0x1250, (unsigned char *)"%s", perstats_title[0], (float)(win->v.x + 4),
                      (float)(win->v.y + 0x15));
        CsFontPrintf(win->v.x + 0xB7, win->v.y + 0x15, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x38));

        CsFontPrintf(win->v.x + 0x11E, win->v.y + 0x15, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x3C));

        CsFontPrintf(win->v.x + 0x185, win->v.y + 0x15, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x40));

        CsFontPrintf(win->v.x + 0x1EC, win->v.y + 0x15, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x44));

        func_00121270(0x1250, (unsigned char *)"%s", perstats_title[1], (float)(win->v.x + 4),
                      (float)(win->v.y + 0x30));
        CsFontPrintf(win->v.x + 0xB7, win->v.y + 0x30, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x48));

        CsFontPrintf(win->v.x + 0x11E, win->v.y + 0x30, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x4C));

        CsFontPrintf(win->v.x + 0x185, win->v.y + 0x30, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x50));

        CsFontPrintf(win->v.x + 0x1EC, win->v.y + 0x30, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x54));

        func_00121270(0x1250, (unsigned char *)"%s", perstats_title[2], (float)(win->v.x + 4),
                      (float)(win->v.y + 0x4B));
        CsFontPrintf(win->v.x + 0xB7, win->v.y + 0x4B, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x58));

        CsFontPrintf(win->v.x + 0x11E, win->v.y + 0x4B, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x5C));

        CsFontPrintf(win->v.x + 0x185, win->v.y + 0x4B, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x60));

        CsFontPrintf(win->v.x + 0x1EC, win->v.y + 0x4B, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x64));

        func_00121270(0x1250, (unsigned char *)"%s", perstats_title[3], (float)(win->v.x + 4),
                      (float)(win->v.y + 0x66));
        CsFontPrintf(win->v.x + 0xB7, win->v.y + 0x66, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x68));

        CsFontPrintf(win->v.x + 0x11E, win->v.y + 0x66, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x6C));

        CsFontPrintf(win->v.x + 0x185, win->v.y + 0x66, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x70));

        CsFontPrintf(win->v.x + 0x1EC, win->v.y + 0x66, 0x80, pri, 0, win->v.a, 0xFB, 0x9650, 0,
                     (unsigned char *)"%04d", *(int *)(D_01029FE4 + 0x74));
    }
    return 0;
}

static int NetWin_PerStatsInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinperhed[i]);
    }
    win->step[0]++;
    return 0;
}

int NetWin_PerStats(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_PerStatsCode[win->step[1]] != 0)
        NetWin_PerStatsCode[win->step[1]](win);
    rtn = NetWin_PerStatsFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_PerStatsEnd(struct _CWS_WIN_W *win) {
    win->status |= 4;
    return 0;
}
