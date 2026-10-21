#include "src/network/net_window/net_win_listdtl3.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);

static int (*NetWin_Listdtl3Func[3])(struct _CWS_WIN_W *) = { NetWin_Listdtl3Init, NetWin_Listdtl3Main, NetWin_Listdtl3End };
static void (*NetWin_Listdtl3Code[4])(struct _CWS_WIN_W *) = { 0, CwsWinOpen, CwsWinClose, CwsWinDestroy };
static struct _CWS_OBJ_TEX netwinlistdtl3_plate_board[6] = {
    { .x = 2, .y = 2, .w = 210, .h = 48, .tu = 0, .tv = 0, .tw = 8, .th = 48, .z = 0, .flag = 0 },
    { .x = 212, .y = 2, .w = 282, .h = 48, .tu = 8, .tv = 0, .tw = 282, .th = 48, .z = 0, .flag = 0 },
    { .x = 2, .y = 50, .w = 210, .h = 88, .tu = 0, .tv = 48, .tw = 8, .th = 24, .z = 0, .flag = 0 },
    { .x = 212, .y = 50, .w = 282, .h = 88, .tu = 8, .tv = 48, .tw = 282, .th = 24, .z = 0, .flag = 0 },
    { .x = 2, .y = 138, .w = 210, .h = 24, .tu = 0, .tv = 72, .tw = 8, .th = 24, .z = 0, .flag = 0 },
    { .x = 212, .y = 138, .w = 282, .h = 24, .tu = 8, .tv = 72, .tw = 282, .th = 24, .z = 0, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinlistdtl3_plate_waku[4] = {
    { .x = 0, .y = 0, .w = 2, .h = 164, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 16, .flag = 0 },
    { .x = 494, .y = 0, .w = 2, .h = 164, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 16, .flag = 0 },
    { .x = 2, .y = 0, .w = 492, .h = 2, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 16, .flag = 0 },
    { .x = 2, .y = 162, .w = 492, .h = 2, .tu = 0, .tv = 0, .tw = 0, .th = 0, .z = 16, .flag = 0 }
};
static struct _CWS_OBJ_TEX netwinlistdtl3_plate_font[8] = {
    { .x = 10, .y = 5, .w = 170, .h = 17, .tu = 0, .tv = 17, .tw = 170, .th = 17, .z = 32, .flag = 0 },
    { .x = 10, .y = 29, .w = 148, .h = 16, .tu = 0, .tv = 34, .tw = 148, .th = 16, .z = 32, .flag = 0 },
    { .x = 10, .y = 53, .w = 114, .h = 16, .tu = 0, .tv = 50, .tw = 114, .th = 16, .z = 32, .flag = 0 },
    { .x = 282, .y = 53, .w = 58, .h = 16, .tu = 0, .tv = 82, .tw = 58, .th = 16, .z = 32, .flag = 0 },
    { .x = 309, .y = 75, .w = 31, .h = 16, .tu = 0, .tv = 98, .tw = 31, .th = 16, .z = 32, .flag = 0 },
    { .x = 300, .y = 97, .w = 40, .h = 16, .tu = 0, .tv = 114, .tw = 40, .th = 16, .z = 32, .flag = 0 },
    { .x = 294, .y = 119, .w = 46, .h = 16, .tu = 0, .tv = 130, .tw = 46, .th = 16, .z = 32, .flag = 0 },
    { .x = 148, .y = 141, .w = 185, .h = 16, .tu = 0, .tv = 146, .tw = 185, .th = 16, .z = 32, .flag = 0 }
};
static struct _CWS_OBJ_SET netwinlistdtl3[3] = {
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 31, .ptex_obj = 6, .ptex = netwinlistdtl3_plate_board, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = -1, .ptex_obj = 4, .ptex = netwinlistdtl3_plate_waku, .r = 0x41, .g = 0xF0, .b = 0x6F, .a = 0x80 },
    { .func = (int (*)(void *, void *))CwsObjDisp, .tex_num = 30, .ptex_obj = 8, .ptex = netwinlistdtl3_plate_font, .r = 0x80, .g = 0x80, .b = 0x80, .a = 0x80 }
};













































































































































































































int NetWin_Listdtl3(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_Listdtl3Code[win->step[1]] != 0) NetWin_Listdtl3Code[win->step[1]](win);
    rtn = NetWin_Listdtl3Func[win->step[0]](win);
    return rtn;
}




static int NetWin_Listdtl3Init(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 3; i++) {
        win->obj[i] = CwsObjCreate(&netwinlistdtl3[i]);
    }

    CwsStrSetAll(win, 0, 0xA8, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 3, (unsigned char *)"%05d", 0);



    CwsStrSetTex(win, 0, 9);


    CwsStrSetAll(win, 1, 0xA8, 0x35, 0x100, 0x80, 0x80, 0x10001, 4, 3, (unsigned char *)"%05d", 0);



    CwsStrSetTex(win, 1, 9);


    CwsStrSetAll(win, 2, 0x112, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 2, (unsigned char *)"%04d", 0);



    CwsStrSetTex(win, 2, 9);


    CwsStrSetAll(win, 3, 0x15B, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 1, (unsigned char *)"%04d", 0);



    CwsStrSetTex(win, 3, 9);


    CwsStrSetAll(win, 4, 0x1A4, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 4, (unsigned char *)"%04d", 0);



    CwsStrSetTex(win, 4, 9);


    CwsStrSetAll(win, 5, 0x158, 0x35, 0x100, 0x80, 0x80, 0x10001, 4, 0, (unsigned char *)"%08d", 0);



    CwsStrSetTex(win, 5, 9);


    CwsStrSetAll(win, 6, 0x158, 0x4B, 0x100, 0x80, 0x80, 0x10001, 4, 2, (unsigned char *)"%08d", 0);



    CwsStrSetTex(win, 6, 9);


    CwsStrSetAll(win, 7, 0x158, 0x61, 0x100, 0x80, 0x80, 0x10001, 4, 1, (unsigned char *)"%08d", 0);



    CwsStrSetTex(win, 7, 9);


    CwsStrSetAll(win, 8, 0x158, 0x77, 0x100, 0x80, 0x80, 0x10001, 4, 4, (unsigned char *)"%08d", 0);



    CwsStrSetTex(win, 8, 9);


    CwsStrSetAll(win, 9, 0x158, 0x8D, 0x100, 0x80, 0x80, 0x10001, 4, 0, (unsigned char *)"%06d", 0);



    CwsStrSetTex(win, 9, 9);


    CwsStrSetAll(win, 0xA, 0x152, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 0, (unsigned char *)"/");



    CwsStrSetTex(win, 0xA, 9);


    CwsStrSetAll(win, 0xB, 0x19B, 0x1D, 0x100, 0x80, 0x80, 0x10001, 4, 0, (unsigned char *)"/");



    CwsStrSetTex(win, 0xB, 9);

    win->step[0]++;
    return 0;
}


static int NetWin_Listdtl3Main(struct _CWS_WIN_W *win) {
    struct _net_win_listdtl3_w *winw = (struct _net_win_listdtl3_w *)win->work;

    if (winw->player_list_file != 0)



    {
        CwsStrSetString(win, 0, (unsigned char *)"%05d", winw->player_list_file->htoh_week_rank < 99999 ? winw->player_list_file->htoh_week_rank : 99999);



        CwsStrSetString(win, 1, (unsigned char *)"%05d", winw->player_list_file->htoh_total_rank < 99999 ? winw->player_list_file->htoh_total_rank : 99999);



        CwsStrSetString(win, 2, (unsigned char *)"%04d", winw->player_list_file->htoh_week_win < 9999 ? winw->player_list_file->htoh_week_win : 9999);



        CwsStrSetString(win, 3, (unsigned char *)"%04d", winw->player_list_file->htoh_week_lose < 9999 ? winw->player_list_file->htoh_week_lose : 9999);



        CwsStrSetString(win, 4, (unsigned char *)"%04d", winw->player_list_file->htoh_week_draw < 9999 ? winw->player_list_file->htoh_week_draw : 9999);



        CwsStrSetString(win, 5, (unsigned char *)"%08d", winw->player_list_file->htoh_total_match < 99999999 ? winw->player_list_file->htoh_total_match : 99999999);



        CwsStrSetString(win, 6, (unsigned char *)"%08d", winw->player_list_file->htoh_total_win < 99999999 ? winw->player_list_file->htoh_total_win : 99999999);



        CwsStrSetString(win, 7, (unsigned char *)"%08d", winw->player_list_file->htoh_total_lose < 99999999 ? winw->player_list_file->htoh_total_lose : 99999999);



        CwsStrSetString(win, 8, (unsigned char *)"%08d", winw->player_list_file->htoh_total_draw < 99999999 ? winw->player_list_file->htoh_total_draw : 99999999);



        CwsStrSetString(win, 9, (unsigned char *)"%06d", winw->player_list_file->dis_connect_count < 999999 ? winw->player_list_file->dis_connect_count : 999999);
    }
    return 0;
}




static int NetWin_Listdtl3End(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}








void NetWin_Listdtl3SetPlayerListFile(struct _CWS_WIN_W *win, struct _nsv_player_list_file *addr) { win->work[0] = (int)addr; }
