#include "src/network/net_window/net_win_watch.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id);
void CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);

static int (*NetWin_WatchFunc[3])(struct _CWS_WIN_W *) = { NetWin_WatchInit, NetWin_WatchMain, NetWin_WatchEnd };
static void (*NetWin_WatchCode[4])(struct _CWS_WIN_W *) = { 0, CwsWinOpen, CwsWinClose, CwsWinDestroy };
static struct _CWS_OBJ_TEX netwinwatch_plate_obj[3] = {
    { .x = 0, .y = 0, .w = 286, .h = 36, .tu = 0, .tv = 36, .tw = 286, .th = 36, .z = 0, .flag = 0 },
    { .x = 85, .y = 0, .w = 194, .h = 18, .tu = 0, .tv = 0, .tw = 194, .th = 18, .z = 16, .flag = 0 },
    { .x = 85, .y = 18, .w = 120, .h = 18, .tu = 0, .tv = 18, .tw = 120, .th = 18, .z = 16, .flag = 0 }
};
static struct _CWS_OBJ_SET netwinwatch[3] = {
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 15, .ptex_obj = 0, .ptex = netwinwatch_plate_obj, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 15, .ptex_obj = 0, .ptex = &netwinwatch_plate_obj[1], .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 15, .ptex_obj = 0, .ptex = &netwinwatch_plate_obj[2], .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 }
};






















































































int NetWin_Watch(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_WatchCode[win->step[1]] != 0) NetWin_WatchCode[win->step[1]](win);
    rtn = NetWin_WatchFunc[win->step[0]](win);
    return rtn;
}




static int NetWin_WatchInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinwatch[i]);
    }

    CwsStrSetAll(win, 0, 0x53, 0, 0x100, 0x80, 0x80, 0x4000, 5, 3, (unsigned char *)"%d", 0);



    CwsStrSetTex(win, 0, 10);

    CwsStrSetAll(win, 1, 0x53, 0x12, 0x100, 0x80, 0x80, 0x4000, 5, 3, (unsigned char *)"%03d:%02d", 0, 0);



    CwsStrSetTex(win, 1, 10);
    win->step[0]++;
    return 0;
}


static int NetWin_WatchMain(struct _CWS_WIN_W *win) {
    struct _net_win_watch_w *winw = (struct _net_win_watch_w *)win->work;

    winw->timer_count += 1.0f / 59.94f;
    if (winw->timer_count > 60.0f)
    {
        winw->rest_time--;
        winw->timer_count -= 60.0f;
        if (winw->rest_time < 0) {
            winw->week++;
            winw->rest_time = 10079;
        }
        winw->flag |= 1;
    }
    if (winw->flag & 2) {
        CwsStrSetString(win, 0, (unsigned char *)"%d", winw->week);

        winw->flag &= ~2;
    }
    if (winw->flag & 1) {
        CwsStrSetString(win, 1, (unsigned char *)"%03d:%02d", winw->rest_time / 60, winw->rest_time % 60);


        winw->flag &= ~1;
    }
    return 0;
}




static int NetWin_WatchEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}





void NetWin_WatchSetWeek(struct _CWS_WIN_W *win, char week) {
    struct _net_win_watch_w *winw = (struct _net_win_watch_w *)win->work;
    if (winw->week != week) {
        winw->week = week;
        winw->flag |= 2;
    }
}




void NetWin_WatchSetRestTime(struct _CWS_WIN_W *win, unsigned int rest_time) {
    struct _net_win_watch_w *winw = (struct _net_win_watch_w *)win->work; if (winw->rest_time != rest_time)
    {
        winw->timer_count = (float)(rest_time % 60);

        winw->rest_time = rest_time / 60;
        winw->flag |= 1;
    }
}
