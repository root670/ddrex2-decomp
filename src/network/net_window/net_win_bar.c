#include "src/network/net_window/net_win_bar.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
void ComScrollBarDisp(struct _COM_SCROLLBAR_WORK *scrbw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_BarFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_BarInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_BarMain,
    NetWin_BarEnd,
};
static void (*NetWin_BarCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_SET netwinbar[1] = {
    {
        .func = (int (*)(void *, void *))NetWin_BarDisp,
        .tex_num = 5,
        .ptex_obj = 0,
        .ptex = 0,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};




























int NetWin_Bar(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_BarCode[win->step[1]] != 0) NetWin_BarCode[win->step[1]](win);
    rtn = NetWin_BarFunc[win->step[0]](win);
    return rtn;
}




static int NetWin_BarInit(struct _CWS_WIN_W *win) {



    win->obj[0] = CwsObjCreate(netwinbar);

    win->step[0]++;
    return 0;
}






static int NetWin_BarMain(void) { return 0; }




static int NetWin_BarEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}


static void NetWin_BarDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw) {
    struct _net_win_bar_w *barw = (struct _net_win_bar_w *)win->work;
    struct _COM_SCROLLBAR_WORK scrw;
    scrw.tex_id = objw->tex_num;
    scrw.x = win->v.x;
    scrw.y = win->v.y;
    scrw.h = barw->h;
    scrw.z = win->v.z;
    scrw.c_max = barw->c_max;
    scrw.c_num = barw->c_num;
    scrw.c_now = barw->c_now;
    scrw.flag = barw->flag;
    scrw.alpha = win->v.a;
    scrw.bri = win->v.bri;
    ComScrollBarDisp(&scrw);
}






void NetWin_BarSetMax(struct _CWS_WIN_W *win, int max) { ((struct _net_win_bar_w *)win->work)->c_max = max; }




void NetWin_BarSetNum(struct _CWS_WIN_W *win, int num) { ((struct _net_win_bar_w *)win->work)->c_num = num; }




void NetWin_BarSetNow(struct _CWS_WIN_W *win, int now) { ((struct _net_win_bar_w *)win->work)->c_now = now; }




void NetWin_BarSetH(struct _CWS_WIN_W *win, int h) { ((struct _net_win_bar_w *)win->work)->h = h; }
