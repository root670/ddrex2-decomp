#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

typedef struct _CWS_WIN_W NetWin_AnchorType;

static int (*NetWin_InfoboardFunc[3])(struct _CWS_WIN_W *) = { 0 };
static void (*NetWin_InfoboardCode[4])(struct _CWS_WIN_W *) = { 0 };
static struct _CWS_OBJ_TEX netwininfoboard_plate_back[11] = { 0 };
static struct _CWS_OBJ_SET netwininfoboard[1] = { 0 };
struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);

#line 105
int NetWin_Infoboard(struct _CWS_WIN_W *win) {
    int rtn;
#line 108
    if (NetWin_InfoboardCode[win->step[1]] != 0) NetWin_InfoboardCode[win->step[1]](win);
#line 109
    rtn = NetWin_InfoboardFunc[win->step[0]](win);
#line 110
    return rtn;
#line 111
}

#line 116
static int NetWin_InfoboardInit(struct _CWS_WIN_W *win) {
#line 120
    win->obj[0] = CwsObjCreate(netwininfoboard);
#line 122
    win->step[0] += 1;
#line 123
    return 0;
#line 124
}

#line 127
static int NetWin_InfoboardMain(void)
{
    return 0;
}

#line 134
static int NetWin_InfoboardEnd(struct _CWS_WIN_W *win)
{
#line 135
    win->status |= 0x4;
#line 136
    return 0;
}
