#include "src/network/net_window/net_win_suser.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
char CwsWinSetBri(struct _CWS_WIN_W *work, int bri);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetCol(struct _CWS_WIN_W *win, int str_num, unsigned char col);
char CwsStrSetDispStatus(struct _CWS_WIN_W *win, int str_num, char on_off);
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
int NetGrfGetDancerIDToNumberPoint(int dancer_id);
unsigned char *NetReadDataGetStr(int str_num);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_SuserFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_SuserInit,
    (int (*)(struct _CWS_WIN_W *))NetWin_SuserMain,
    NetWin_SuserEnd,
};
static void (*NetWin_SuserCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinsuser_plate_board_off[9] = {
    { .x = 0, .y = 0, .w = 21, .h = 22, .tu = 52, .tv = 44, .tw = 21, .th = 22, .z = 0, .flag = 0 },
    { .x = 21, .y = 0, .w = 482, .h = 22, .tu = 72, .tv = 44, .tw = 1, .th = 22, .z = 0, .flag = 0 },
    { .x = 503, .y = 0, .w = 21, .h = 22, .tu = 73, .tv = 44, .tw = 21, .th = 22, .z = 0, .flag = 0 },
    { .x = 0, .y = 22, .w = 21, .h = 32, .tu = 52, .tv = 66, .tw = 21, .th = 1, .z = 0, .flag = 0 },
    { .x = 21, .y = 22, .w = 482, .h = 32, .tu = 72, .tv = 66, .tw = 1, .th = 1, .z = 0, .flag = 0 },
    { .x = 503, .y = 22, .w = 21, .h = 32, .tu = 73, .tv = 66, .tw = 21, .th = 1, .z = 0, .flag = 0 },
    { .x = 0, .y = 54, .w = 21, .h = 22, .tu = 52, .tv = 66, .tw = 21, .th = 22, .z = 0, .flag = 0 },
    { .x = 21, .y = 54, .w = 482, .h = 22, .tu = 72, .tv = 66, .tw = 1, .th = 22, .z = 0, .flag = 0 },
    { .x = 503, .y = 54, .w = 21, .h = 22, .tu = 73, .tv = 66, .tw = 21, .th = 22, .z = 0, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinsuser_plate_board_on[9] = {
    { .x = 0, .y = 0, .w = 21, .h = 22, .tu = 52, .tv = 0, .tw = 21, .th = 22, .z = 0, .flag = 0 },
    { .x = 21, .y = 0, .w = 482, .h = 22, .tu = 72, .tv = 0, .tw = 1, .th = 22, .z = 0, .flag = 0 },
    { .x = 503, .y = 0, .w = 21, .h = 22, .tu = 73, .tv = 0, .tw = 21, .th = 22, .z = 0, .flag = 0 },
    { .x = 0, .y = 22, .w = 21, .h = 32, .tu = 52, .tv = 22, .tw = 21, .th = 1, .z = 0, .flag = 0 },
    { .x = 21, .y = 22, .w = 482, .h = 32, .tu = 72, .tv = 22, .tw = 1, .th = 1, .z = 0, .flag = 0 },
    { .x = 503, .y = 22, .w = 21, .h = 32, .tu = 73, .tv = 22, .tw = 21, .th = 1, .z = 0, .flag = 0 },
    { .x = 0, .y = 54, .w = 21, .h = 22, .tu = 52, .tv = 22, .tw = 21, .th = 22, .z = 0, .flag = 0 },
    { .x = 21, .y = 54, .w = 482, .h = 22, .tu = 72, .tv = 22, .tw = 1, .th = 22, .z = 0, .flag = 0 },
    { .x = 503, .y = 54, .w = 21, .h = 22, .tu = 73, .tv = 22, .tw = 21, .th = 22, .z = 0, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinsuser_plate_col00[3] = {
    { .x = 0, .y = 0, .w = 26, .h = 22, .tu = 0, .tv = 0, .tw = 26, .th = 22, .z = 0x10, .flag = 0 },
    { .x = 0, .y = 22, .w = 26, .h = 32, .tu = 0, .tv = 22, .tw = 26, .th = 1, .z = 0x10, .flag = 0 },
    { .x = 0, .y = 54, .w = 26, .h = 22, .tu = 0, .tv = 22, .tw = 26, .th = 22, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinsuser_plate_col01[3] = {
    { .x = 0, .y = 0, .w = 26, .h = 22, .tu = 0, .tv = 44, .tw = 26, .th = 22, .z = 0x10, .flag = 0 },
    { .x = 0, .y = 22, .w = 26, .h = 32, .tu = 0, .tv = 66, .tw = 26, .th = 1, .z = 0x10, .flag = 0 },
    { .x = 0, .y = 54, .w = 26, .h = 22, .tu = 0, .tv = 66, .tw = 26, .th = 22, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinsuser_plate_namewaku[3] = {
    { .x = 76, .y = 6, .w = 8, .h = 32, .tu = 0, .tv = 0, .tw = 8, .th = 32, .z = 0x10, .flag = 0 },
    { .x = 84, .y = 6, .w = 330, .h = 32, .tu = 8, .tv = 0, .tw = 1, .th = 32, .z = 0x10, .flag = 0 },
    { .x = 414, .y = 6, .w = 20, .h = 32, .tu = 8, .tv = 0, .tw = 20, .th = 32, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinsuser_plate_obj[3] = {
    { .x = 76, .y = 35, .w = 56, .h = 17, .tu = 0, .tv = 34, .tw = 56, .th = 17, .z = 0x10, .flag = 0 },
    { .x = 76, .y = 53, .w = 56, .h = 17, .tu = 0, .tv = 17, .tw = 56, .th = 17, .z = 0x10, .flag = 0 },
    { .x = 254, .y = 35, .w = 136, .h = 17, .tu = 0, .tv = 68, .tw = 136, .th = 17, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_TEX netwinsuser_plate_chara[1] = {
    { .x = 30, .y = 6, .w = 42, .h = 62, .tu = 0, .tv = 0, .tw = 42, .th = 62, .z = 0x10, .flag = 0 },
};
static struct _CWS_OBJ_SET netwinsuser[6] = {
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 11,
        .ptex_obj = 9,
        .ptex = netwinsuser_plate_board_off,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 11,
        .ptex_obj = 3,
        .ptex = netwinsuser_plate_col00,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 7,
        .ptex_obj = 3,
        .ptex = netwinsuser_plate_namewaku,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 8,
        .ptex_obj = 3,
        .ptex = netwinsuser_plate_obj,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = -1,
        .ptex_obj = 0,
        .ptex = netwinsuser_plate_chara,
        .r = 0xFF,
        .g = 0xFF,
        .b = 0xFF,
        .a = 0x26,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 6,
        .ptex_obj = 0,
        .ptex = netwinsuser_plate_chara,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_Suser(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_SuserCode[win->step[1]] != 0) NetWin_SuserCode[win->step[1]](win);
    rtn = NetWin_SuserFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_SuserInit(struct _CWS_WIN_W *win) {
    struct _net_win_suser_w *winw = (struct _net_win_suser_w *)win->work;
    int i;

    for (i = 0; i < 6; i++) {
        win->obj[i] = CwsObjCreate(&netwinsuser[i]);
    }
    win->obj[5]->status &= ~2;
    win->obj[3]->status &= ~2;
    winw->board_status = 1;
    winw = (struct _net_win_suser_w *)win->work;
    if (winw->board_status != 0) {
        winw->board_status = 0;
        CwsObjChangePlate(win->obj[0], netwinsuser_plate_board_off);
        CwsWinSetBri(win, 0x40);
    }
    CwsStrSetAll(win, 0, 0x54, 8, 0x100, 0x80, 0x80, 0, 2, 5, (unsigned char *)"%s", NetReadDataGetStr(0x1C));
    CwsStrSetAll(win, 1, 0x14E, 0x35, 0x100, 0x80, 0x80, 0, 4, 0, (unsigned char *)"/");
    CwsStrSetTex(win, 1, 9);
    CwsStrSetAll(win, 2, 0x1A7, 0x35, 0x100, 0x80, 0x80, 0, 4, 0, (unsigned char *)"/");
    CwsStrSetTex(win, 2, 9);
    CwsStrSetAll(win, 3, 0x84, 0x23, 0x100, 0x80, 0x80, 1, 4, 3, (unsigned char *)"%06d", 0);
    CwsStrSetTex(win, 3, 9);
    CwsStrSetAll(win, 4, 0x84, 0x35, 0x100, 0x80, 0x80, 1, 4, 3, (unsigned char *)"%05d:%02d", 0, 0);
    CwsStrSetTex(win, 4, 9);
    CwsStrSetAll(win, 5, 0xFE, 0x35, 0x100, 0x80, 0x80, 1, 4, 2, (unsigned char *)"%05d", 0);
    CwsStrSetTex(win, 5, 9);
    CwsStrSetAll(win, 6, 0x157, 0x35, 0x100, 0x80, 0x80, 1, 4, 1, (unsigned char *)"%05d", 0);
    CwsStrSetTex(win, 6, 9);
    CwsStrSetAll(win, 7, 0x1B0, 0x35, 0x100, 0x80, 0x80, 1, 4, 4, (unsigned char *)"%05d", 0);
    CwsStrSetTex(win, 7, 9);
    for (i = 1; i < 8; i++) {
        CwsStrSetDispStatus(win, i, 0);
    }
    win->step[0]++;
    return 0;
}

static int NetWin_SuserMain(struct _CWS_WIN_W *win) {
    struct _net_win_suser_w *winw = (struct _net_win_suser_w *)win->work;
    int i;

    if (winw->user_file != 0) {
        if (winw->user_file->pid != 0) {
            int num;

            if (winw->user_file->dancer_number < 45) {
                win->obj[4]->status &= ~2;
                win->obj[5]->status |= 2;
                num = NetGrfGetDancerIDToNumberPoint(winw->user_file->dancer_number);
                win->obj[5]->tu = num % 8 * 42;
                win->obj[5]->tv = num / 8 * 62;
            } else {
                win->obj[4]->status |= 2;
                win->obj[5]->status &= ~2;
            }
            win->obj[3]->status |= 2;
            CwsStrSetCol(win, 0, 0);
            CwsStrSetString(win, 0, (unsigned char *)"%s", winw->user_file->name);
            CwsStrSetString(win, 3, (unsigned char *)"%06d", winw->user_file->points.year_param.points);
            CwsStrSetString(win, 4, (unsigned char *)"%05d:%02d", winw->user_file->play_time / 3600, winw->user_file->play_time / 60 % 60);
            CwsStrSetString(win, 5, (unsigned char *)"%05d", winw->user_file->htoh.year_param.win);
            CwsStrSetString(win, 6, (unsigned char *)"%05d", winw->user_file->htoh.year_param.lose);
            CwsStrSetString(win, 7, (unsigned char *)"%05d", winw->user_file->htoh.year_param.draw);
            for (i = 1; i < 8; i++) {
                CwsStrSetDispStatus(win, i, 1);
            }
        } else if (winw->entry_flag == 1) {
            int num;

            if (winw->user_file->dancer_number < 45) {
                win->obj[4]->status &= ~2;
                win->obj[5]->status |= 2;
                num = NetGrfGetDancerIDToNumberPoint(winw->user_file->dancer_number);
                win->obj[5]->tu = num % 8 * 42;
                win->obj[5]->tv = num / 8 * 62;
            } else {
                win->obj[4]->status |= 2;
                win->obj[5]->status &= ~2;
            }
            CwsStrSetCol(win, 0, 0);
            CwsStrSetString(win, 0, (unsigned char *)"%s", winw->user_file->name);
            win->obj[3]->status &= ~2;
            for (i = 1; i < 8; i++) {
                CwsStrSetDispStatus(win, i, 0);
            }
        } else {
            CwsStrSetCol(win, 0, 5);
            CwsStrSetString(win, 0, NetReadDataGetStr(0x1C));
            win->obj[5]->status &= ~2;
            win->obj[3]->status &= ~2;
            for (i = 1; i < 8; i++) {
                CwsStrSetDispStatus(win, i, 0);
            }
        }
    }
    return 0;
}

static int NetWin_SuserEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}

void NetWin_SuserSetNum(struct _CWS_WIN_W *win, int file_num) {
    struct _net_win_suser_w *winw = (struct _net_win_suser_w *)win->work;

    if (winw->file_num != file_num) {
        winw->file_num = file_num;
        if (file_num == 0) {
            CwsObjChangePlate(win->obj[0], netwinsuser_plate_col00);
        } else {
            CwsObjChangePlate(win->obj[1], netwinsuser_plate_col01);
        }
    }
}

void NetWin_SuserSetSelect(struct _CWS_WIN_W *win, int status) {
    struct _net_win_suser_w *winw = (struct _net_win_suser_w *)win->work;

    if (winw->board_status != status) {
        winw->board_status = status;
        if (status == 1) {
            CwsObjChangePlate(win->obj[0], netwinsuser_plate_board_on);
            CwsWinSetBri(win, 0x80);
        } else {
            CwsObjChangePlate(win->obj[0], netwinsuser_plate_board_off);
            CwsWinSetBri(win, 0x40);
        }
    }
}

void NetWin_SuserSetUserFile(struct _CWS_WIN_W *win, struct _NSV_USER_FILE_WORK *addr) {
    struct _net_win_suser_w *winw = (struct _net_win_suser_w *)win->work;

    winw->user_file = addr;
}

void NetWin_SuserSetEntryMode(struct _CWS_WIN_W *win, char onoff) {
    struct _net_win_suser_w *winw = (struct _net_win_suser_w *)win->work;

    if (onoff == 1) winw->entry_flag = 1;
    else winw->entry_flag = 0;
}
