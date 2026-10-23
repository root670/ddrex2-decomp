#include "src/network/net_window/net_win_listdtl2.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);

static int (*NetWin_Listdtl2Func[3])(struct _CWS_WIN_W *) = {
    NetWin_Listdtl2Init,
    NetWin_Listdtl2Main,
    NetWin_Listdtl2End,
};
static void (*NetWin_Listdtl2Code[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_board[2] = {
    {
        .x = 2,
        .y = 2,
        .w = 210,
        .h = 72,
        .tu = 0,
        .tv = 0,
        .tw = 8,
        .th = 72,
        .z = 0,
        .flag = 0,
    },
    {
        .x = 212,
        .y = 2,
        .w = 282,
        .h = 72,
        .tu = 8,
        .tv = 0,
        .tw = 282,
        .th = 72,
        .z = 0,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_waku[4] = {
    {
        .x = 0,
        .y = 0,
        .w = 2,
        .h = 76,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 494,
        .y = 0,
        .w = 2,
        .h = 76,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 2,
        .y = 0,
        .w = 492,
        .h = 2,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 16,
        .flag = 0,
    },
    {
        .x = 2,
        .y = 74,
        .w = 492,
        .h = 2,
        .tu = 0,
        .tv = 0,
        .tw = 0,
        .th = 0,
        .z = 16,
        .flag = 0,
    },
};
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_font[5] = {
    {
        .x = 10,
        .y = 5,
        .w = 68,
        .h = 17,
        .tu = 0,
        .tv = 0,
        .tw = 68,
        .th = 17,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 29,
        .w = 148,
        .h = 16,
        .tu = 0,
        .tv = 34,
        .tw = 148,
        .th = 16,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 10,
        .y = 53,
        .w = 114,
        .h = 16,
        .tu = 0,
        .tv = 50,
        .tw = 114,
        .th = 16,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 274,
        .y = 29,
        .w = 66,
        .h = 16,
        .tu = 0,
        .tv = 66,
        .tw = 66,
        .th = 16,
        .z = 32,
        .flag = 0,
    },
    {
        .x = 274,
        .y = 53,
        .w = 66,
        .h = 16,
        .tu = 0,
        .tv = 66,
        .tw = 66,
        .th = 16,
        .z = 32,
        .flag = 0,
    },
};
static struct _CWS_OBJ_SET netwinlistdtl2[3] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 31,
        .ptex_obj = 2,
        .ptex = netwinlistdtl2_plate_point_board,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 4,
        .ptex = netwinlistdtl2_plate_point_waku,
        .r = 0x41,
        .g = 0xF0,
        .b = 0x6F,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 30,
        .ptex_obj = 5,
        .ptex = netwinlistdtl2_plate_point_font,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_Listdtl2(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_Listdtl2Code[win->step[1]] != 0) NetWin_Listdtl2Code[win->step[1]](win);
    rtn = NetWin_Listdtl2Func[win->step[0]](win);
    return rtn;
}

static int NetWin_Listdtl2Init(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinlistdtl2[i]);
    }

    CwsStrSetAll(win, 0, 0xA8, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 3, (unsigned char *)"%05d", 0);

    CwsStrSetTex(win, 0, 9);

    CwsStrSetAll(win, 1, 0xA8, 0x35, 0x100, 0x80, 0x80, 0x10001, 4, 3, (unsigned char *)"%05d", 0);

    CwsStrSetTex(win, 1, 9);

    CwsStrSetAll(win, 2, 0x158, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 3, (unsigned char *)"%08d", 0);

    CwsStrSetTex(win, 2, 9);

    CwsStrSetAll(win, 3, 0x158, 0x35, 0x100, 0x80, 0x80, 0x10001, 4, 3, (unsigned char *)"%08d", 0);

    CwsStrSetTex(win, 3, 9);

    win->step[0]++;
    return 0;
}

static int NetWin_Listdtl2Main(struct _CWS_WIN_W *win) {
    struct _net_win_listdtl2_w *winw = (struct _net_win_listdtl2_w *)win->work;
    int disp_max;

    if (winw->player_list_file != 0) {
        disp_max = winw->player_list_file->points_week_rank;

        CwsStrSetString(win, 0, (unsigned char *)"%05d", disp_max < 99999 ? disp_max : 99999);

        disp_max = winw->player_list_file->points_total_rank;

        CwsStrSetString(win, 1, (unsigned char *)"%05d", disp_max < 99999 ? disp_max : 99999);

        disp_max = winw->player_list_file->points_week_num;

        CwsStrSetString(win, 2, (unsigned char *)"%08d", disp_max < 99999999 ? disp_max : 99999999);

        disp_max = winw->player_list_file->points_total_num;

        CwsStrSetString(win, 3, (unsigned char *)"%08d", disp_max < 99999999 ? disp_max : 99999999);
    }
    return 0;
}

static int NetWin_Listdtl2End(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}

void NetWin_Listdtl2SetPlayerListFile(struct _CWS_WIN_W *win, struct _nsv_player_list_file *addr) { win->work[0] = (int)addr; }
