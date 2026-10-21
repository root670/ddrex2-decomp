#include "src/network/net_window/net_win_any.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangeTex(struct _CWS_OBJ *work, int tex_num);
char cws_win_move_xywh(struct _CWS_WIN_W *work, int _end_time);

static int (*NetWin_AnyFunc[3])(struct _CWS_WIN_W *) = { 0 };
static void (*NetWin_AnyCode[4])(struct _CWS_WIN_W *) = { 0 };
static struct _CWS_OBJ_SET netwinany[2] = { 0 };

int NetWin_Any(struct _CWS_WIN_W *win)
{
    int rtn;

    if (NetWin_AnyCode[win->step[1]] != 0)
        NetWin_AnyCode[win->step[1]](win);
    rtn = NetWin_AnyFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_AnyInit(struct _CWS_WIN_W *win)
{
    int i;

    for (i = 0; i < 2; i++) {
        win->obj[i] = CwsObjCreate(&netwinany[i]);
    }
    win->obj[1]->status &= ~2;
    win->step[0]++;
    return 0;
}

static int NetWin_AnyMain(struct _CWS_WIN_W *win)
{
    win->obj[0]->x = 0;
    win->obj[0]->y = 0;
    win->obj[0]->w = win->v.w;
    win->obj[0]->h = win->v.h;
    win->obj[1]->x = 0;
    win->obj[1]->y = 0;
    win->obj[1]->w = win->v.w;
    win->obj[1]->h = win->v.h;
    cws_win_move_xywh(win, 30);
    return 0;
}

static int NetWin_AnyEnd(struct _CWS_WIN_W *win)
{
    win->status |= 4;
    return 0;
}

void NetWin_AnySetTexture(struct _CWS_WIN_W *win, int _tex_id, int _tu, int _tv, int _tw, int _th)
{
    CwsObjChangeTex(win->obj[0], _tex_id);
    win->obj[0]->tu = _tu;
    win->obj[0]->tv = _tv;
    win->obj[0]->tw = _tw;
    win->obj[0]->th = _th;
}
