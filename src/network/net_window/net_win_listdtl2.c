#include "src/network/net_window/net_win_listdtl2.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, ...);
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string, ...);




static int (*NetWin_Listdtl2Func[3])(struct _CWS_WIN_W *) = { NetWin_Listdtl2Init, NetWin_Listdtl2Main, NetWin_Listdtl2End };
static void (*NetWin_Listdtl2Code[4])(struct _CWS_WIN_W *) = { 0, (void (*)(struct _CWS_WIN_W *))0x00207360, (void (*)(struct _CWS_WIN_W *))0x00206E60, (void (*)(struct _CWS_WIN_W *))0x00206E50 };
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_board[2] = { { 2, 2, 210, 72, 0, 0, 8, 72, 0, 0 }, { 212, 2, 282, 72, 8, 0, 282, 72, 0, 0 } };
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_waku[4] = { { 0, 0, 2, 76, 0, 0, 0, 0, 16, 0 }, { 494, 0, 2, 76, 0, 0, 0, 0, 16, 0 }, { 2, 0, 492, 2, 0, 0, 0, 0, 16, 0 }, { 2, 74, 492, 2, 0, 0, 0, 0, 16, 0 } };
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_font[5] = { { 10, 5, 68, 17, 0, 0, 68, 17, 32, 0 }, { 10, 29, 148, 16, 0, 34, 148, 16, 32, 0 }, { 10, 53, 114, 16, 0, 50, 114, 16, 32, 0 }, { 274, 29, 66, 16, 0, 66, 66, 16, 32, 0 }, { 274, 53, 66, 16, 0, 66, 66, 16, 32, 0 } };
static struct _CWS_OBJ_SET netwinlistdtl2[3] = { { (int (*)(void *, void *))0x002046C0, 31, 2, netwinlistdtl2_plate_point_board, 0x80, 0x80, 0x80, 0x80 }, { (int (*)(void *, void *))0x002046C0, -1, 4, netwinlistdtl2_plate_point_waku, 0x41, 0xF0, 0x6F, 0x80 }, { (int (*)(void *, void *))0x002046C0, 30, 5, netwinlistdtl2_plate_point_font, 0x80, 0x80, 0x80, 0x80 } };


































































































































































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
