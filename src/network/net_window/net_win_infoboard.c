#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

static int (*NetWin_InfoboardFunc[3])(struct _CWS_WIN_W *) = { (int (*)(struct _CWS_WIN_W *))0x0025C700, (int (*)(struct _CWS_WIN_W *))0x0025C6F0, (int (*)(struct _CWS_WIN_W *))0x0025C6D0 };
static void (*NetWin_InfoboardCode[4])(struct _CWS_WIN_W *) = { 0, (void (*)(struct _CWS_WIN_W *))0x00207360, (void (*)(struct _CWS_WIN_W *))0x00206E60, (void (*)(struct _CWS_WIN_W *))0x00206E50 };
static struct _CWS_OBJ_TEX netwininfoboard_plate_back[11] = { { 0, 0, 18, 46, 0, 0, 18, 46, 0, 0 }, { 18, 0, 274, 46, 18, 0, 1, 46, 0, 0 }, { 292, 0, 32, 46, 18, 0, 32, 46, 0, 0 }, { 324, 0, 226, 46, 50, 0, 1, 46, 0, 0 }, { 550, 0, 22, 46, 50, 0, 22, 46, 0, 0 }, { 0, 46, 18, 246, 0, 46, 18, 1, 0, 0 }, { 18, 46, 532, 246, 18, 46, 1, 1, 0, 0 }, { 550, 46, 22, 246, 50, 46, 22, 1, 0, 0 }, { 0, 292, 18, 18, 0, 46, 18, 18, 0, 0 }, { 18, 292, 532, 18, 18, 46, 1, 18, 0, 0 }, { 550, 292, 22, 18, 50, 46, 22, 18, 0, 0 } };
static struct _CWS_OBJ_SET netwininfoboard[1] = { { (int (*)(void *, void *))0x002046C0, 11, 11, netwininfoboard_plate_back, 0x80, 0x80, 0x80, 0x80 } };

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);

int NetWin_Infoboard(struct _CWS_WIN_W *win)
{
    int rtn;
    if (NetWin_InfoboardCode[win->step[1]] != 0) NetWin_InfoboardCode[win->step[1]](win);
    rtn = NetWin_InfoboardFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_InfoboardInit(struct _CWS_WIN_W *win)
{
    win->obj[0] = CwsObjCreate(netwininfoboard);
    win->step[0] += 1;
    return 0;
}

static int NetWin_InfoboardMain(void)
{
    return 0;
}

static int NetWin_InfoboardEnd(struct _CWS_WIN_W *win)
{
    win->status |= 0x4;
    return 0;
}
