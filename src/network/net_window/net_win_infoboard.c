#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

static int (*NetWin_InfoboardFunc[3])(struct _CWS_WIN_W *) = { 0 };
static void (*NetWin_InfoboardCode[4])(struct _CWS_WIN_W *) = { 0 };
static struct _CWS_OBJ_TEX netwininfoboard_plate_back[11] = { 0 };
static struct _CWS_OBJ_SET netwininfoboard[1] = { 0 };

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
