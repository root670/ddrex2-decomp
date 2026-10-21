#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

static int NetWin_InfoboardEnd(struct _CWS_WIN_W *win);
static int NetWin_InfoboardMain(void);
static int NetWin_InfoboardInit(struct _CWS_WIN_W *win);
struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_InfoboardFunc[3])(struct _CWS_WIN_W *) = { NetWin_InfoboardInit, (int (*)(struct _CWS_WIN_W *))NetWin_InfoboardMain, NetWin_InfoboardEnd };
static void (*NetWin_InfoboardCode[4])(struct _CWS_WIN_W *) = { 0, CwsWinOpen, CwsWinClose, CwsWinDestroy };
static struct _CWS_OBJ_TEX netwininfoboard_plate_back[11] = { { .x = 0, .y = 0, .w = 18, .h = 46, .tu = 0, .tv = 0, .tw = 18, .th = 46, .z = 0, .flag = 0 }, { .x = 18, .y = 0, .w = 274, .h = 46, .tu = 18, .tv = 0, .tw = 1, .th = 46, .z = 0, .flag = 0 }, { .x = 292, .y = 0, .w = 32, .h = 46, .tu = 18, .tv = 0, .tw = 32, .th = 46, .z = 0, .flag = 0 }, { .x = 324, .y = 0, .w = 226, .h = 46, .tu = 50, .tv = 0, .tw = 1, .th = 46, .z = 0, .flag = 0 }, { .x = 550, .y = 0, .w = 22, .h = 46, .tu = 50, .tv = 0, .tw = 22, .th = 46, .z = 0, .flag = 0 }, { .x = 0, .y = 46, .w = 18, .h = 246, .tu = 0, .tv = 46, .tw = 18, .th = 1, .z = 0, .flag = 0 }, { .x = 18, .y = 46, .w = 532, .h = 246, .tu = 18, .tv = 46, .tw = 1, .th = 1, .z = 0, .flag = 0 }, { .x = 550, .y = 46, .w = 22, .h = 246, .tu = 50, .tv = 46, .tw = 22, .th = 1, .z = 0, .flag = 0 }, { .x = 0, .y = 292, .w = 18, .h = 18, .tu = 0, .tv = 46, .tw = 18, .th = 18, .z = 0, .flag = 0 }, { .x = 18, .y = 292, .w = 532, .h = 18, .tu = 18, .tv = 46, .tw = 1, .th = 18, .z = 0, .flag = 0 }, { .x = 550, .y = 292, .w = 22, .h = 18, .tu = 50, .tv = 46, .tw = 22, .th = 18, .z = 0, .flag = 0 } };
static struct _CWS_OBJ_SET netwininfoboard[1] = { { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 11, .ptex_obj = 11, .ptex = netwininfoboard_plate_back, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 } };

int NetWin_Infoboard(struct _CWS_WIN_W *win) {
    int rtn;
    if (NetWin_InfoboardCode[win->step[1]] != 0) NetWin_InfoboardCode[win->step[1]](win);
    rtn = NetWin_InfoboardFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_InfoboardInit(struct _CWS_WIN_W *win) {
    win->obj[0] = CwsObjCreate(netwininfoboard);
    win->step[0] += 1;
    return 0;
}

static int NetWin_InfoboardMain(void) {
    return 0;
}

static int NetWin_InfoboardEnd(struct _CWS_WIN_W *win) {
    win->status |= 0x4;
    return 0;
}
