#include "src/network/net_window/net_win_rccssel.h"

struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data);
char CwsObjChangeTex(struct _CWS_OBJ *work, int tex_num);
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate);
void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw);
unsigned int CwsWinGetStatus(struct _CWS_WIN_W *work);
void CwsWinOpen(struct _CWS_WIN_W *win);
void CwsWinClose(struct _CWS_WIN_W *win);
void CwsWinDestroy(struct _CWS_WIN_W *win);
int CwsObjMove(int *_v, int *_timer, int _s, int _end_time, int _type);
char CwsObjMoveOpt(int *_v, int _timer, int _s, int _end_time, int _type);
void func_00124800(anon_1_152 *g3);

static int (*NetWin_RccsselFunc[3])(struct _CWS_WIN_W *) = {
    NetWin_RccsselInit,
    NetWin_RccsselMain,
    NetWin_RccsselEnd,
};
static void (*NetWin_RccsselCode[4])(struct _CWS_WIN_W *) = {
    0,
    CwsWinOpen,
    CwsWinClose,
    CwsWinDestroy,
};
static struct _CWS_OBJ_TEX netwinrccssel_plate_back[5] = {
    {
        .x = 22,
        .y = 4,
        .w = 304,
        .h = 36,
    },
    {
        .x = 22,
        .y = 48,
        .w = 304,
        .h = 36,
    },
    {
        .x = 22,
        .y = 92,
        .w = 304,
        .h = 36,
    },
    {
        .x = 22,
        .y = 136,
        .w = 304,
        .h = 36,
    },
    {
        .x = 22,
        .y = 180,
        .w = 304,
        .h = 36,
    },
};
static struct _CWS_OBJ_TEX netwinrccssel_plate_num1_5[5] = {
    {
        .x = 22,
        .y = 7,
        .w = 30,
        .h = 30,
        .tu = 0,
        .tv = 0,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 51,
        .w = 30,
        .h = 30,
        .tu = 0,
        .tv = 30,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 95,
        .w = 30,
        .h = 30,
        .tu = 0,
        .tv = 60,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 139,
        .w = 30,
        .h = 30,
        .tu = 0,
        .tv = 90,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 183,
        .w = 30,
        .h = 30,
        .tu = 0,
        .tv = 120,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
};
static struct _CWS_OBJ_TEX netwinrccssel_plate_num6_10[5] = {
    {
        .x = 22,
        .y = 7,
        .w = 30,
        .h = 30,
        .tu = 30,
        .tv = 0,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 51,
        .w = 30,
        .h = 30,
        .tu = 30,
        .tv = 30,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 95,
        .w = 30,
        .h = 30,
        .tu = 30,
        .tv = 60,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 139,
        .w = 30,
        .h = 30,
        .tu = 30,
        .tv = 90,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
    {
        .x = 22,
        .y = 183,
        .w = 30,
        .h = 30,
        .tu = 30,
        .tv = 120,
        .tw = 30,
        .th = 30,
        .z = 16,
    },
};
static struct _CWS_OBJ_TEX netwinrccssel_plate_nm[1] = {
    {
        .x = 326,
        .y = 0,
        .w = 224,
        .h = 32,
        .tu = 0,
        .tv = 0,
        .tw = 224,
        .th = 32,
        .z = 32,
    },
};
static struct _CWS_OBJ_SET netwinrccssel[7] = {
    {
        .func = (int (*)(void *, void *))NetWin_RccsselBoardDisp,
        .tex_num = -1,
        .ptex_obj = 5,
        .ptex = netwinrccssel_plate_back,
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 0x59,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x13,
        .ptex_obj = 5,
        .ptex = netwinrccssel_plate_num1_5,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x30,
        .ptex_obj = 0,
        .ptex = netwinrccssel_plate_nm,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x31,
        .ptex_obj = 0,
        .ptex = netwinrccssel_plate_nm,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x32,
        .ptex_obj = 0,
        .ptex = netwinrccssel_plate_nm,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x33,
        .ptex_obj = 0,
        .ptex = netwinrccssel_plate_nm,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
    {
        .func = (int (*)(void *, void *))CwsObjDisp,
        .tex_num = 0x34,
        .ptex_obj = 0,
        .ptex = netwinrccssel_plate_nm,
        .r = 0x80,
        .g = 0x80,
        .b = 0x80,
        .a = 0x80,
    },
};

int NetWin_Rccssel(struct _CWS_WIN_W *win) {
    int rtn;

    if (NetWin_RccsselCode[win->step[1]] != 0) NetWin_RccsselCode[win->step[1]](win);
    rtn = NetWin_RccsselFunc[win->step[0]](win);
    return rtn;
}

static int NetWin_RccsselInit(struct _CWS_WIN_W *win) {
    int i;

    for (i = 0; i < 7; i++) {
        win->obj[i] = CwsObjCreate(&netwinrccssel[i]);
    }
    win->obj[2]->y = 6;
    win->obj[3]->y = 0x32;
    win->obj[4]->y = 0x5E;
    win->obj[5]->y = 0x8A;
    win->obj[6]->y = 0xB6;
    ((struct _net_win_rccssel_w *)win->work)->RcData = 0;
    win->step[0]++;
    return 0;
}

static int NetWin_RccsselMain(struct _CWS_WIN_W *win) {
    struct _net_win_rccssel_w *winw;
    int i;
    int num;
    int loop_num;
    unsigned int status;

    winw = (struct _net_win_rccssel_w *)win->work;
    num = 0;
    loop_num = 0;
    status = CwsWinGetStatus(win);
    if ((status & 2) && (status & 0x80)) {
        if (winw->counter == 0) {
            winw->line_step = 1;
            for (i = 0; i < 5; i++) {
                win->obj[2 + i]->status |= 2;
                winw->move_time[i] = 0;
                win->obj[2 + i]->y = 6 + i * 44;
            }
        }
        if (!(winw->status & 2)) {
            if (winw->RcData != 0) {
                for (i = 0; i < 5; i++) {
                    if (winw->RcData->music_data[winw->nm_page == 0 ? i : i + 5].music_id >= 0) loop_num++;
                }
            } else {
                loop_num = 5;
            }
            for (i = 0; i < loop_num; i++) {
                if (winw->counter >= 5 + i * 3) {
                    if (CwsObjMove((int *)win->obj[2 + i], &winw->move_time[i], 0x3A, 0x14, 0) != 0) num++;
                }
                if (num >= loop_num) winw->status |= 2;
            }
            winw->counter++;
        }
        winw->status &= ~1;
    } else {
        if (!(winw->status & 1)) {
            for (i = 0; i < 5; i++) {
                win->obj[2 + i]->status &= ~2;
                winw->move_time[i] = 0;
                win->obj[2 + i]->x = 0x146;
            }
            winw->status &= ~2;
            winw->line_step = 0;
            winw->counter = 0;
            winw->status |= 1;
        }
    }
    NetWin_RccsselLineDisp(win);
    return 0;
}

static int NetWin_RccsselEnd(struct _CWS_WIN_W *win) { win->status |= 4;
    return 0;
}

static void NetWin_RccsselBoardDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw) {
    anon_1_152 g3;
    int mx;
    int my;
    int mz;
    int move_x;
    int move_y;
    int dx;
    int dy;
    int dw;
    int dh;
    int dr;
    int dg;
    int db;
    int da;
    int dz;
    int i;

    if (objw == 0) return;
    if (!(objw->status & 2)) return;
    if (win->master_link == 0) {
        mx = win->v.x;
        my = win->v.y;
        mz = win->v.z;
        dx = mx + objw->x;
        dy = my + objw->y;
        dz = mz + objw->z;
    } else {
        mx = win->master_link->v.x + win->v.x;
        my = win->master_link->v.y + win->v.y;
        mz = win->master_link->v.z + win->v.z;
        dx = mx + objw->x;
        dy = my + objw->y;
        dz = mz + objw->z;
    }
    dw = objw->w;
    dh = objw->h;
    dr = win->v.r * objw->red * win->v.bri / 0x4000;
    dg = win->v.g * objw->green * win->v.bri / 0x4000;
    db = win->v.b * objw->blue * win->v.bri / 0x4000;
    da = win->v.a * objw->alpha / 0x80;

    g3.flg = 0;
    g3.flg |= 0x100;
    g3.x0.fd = dx; g3.y0.fd = dy; g3.z0 = dz;
    g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = dz;
    g3.x2.fd = dx; g3.y2.fd = dy + dh; g3.z2 = dz;
    g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = 0;
    g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
    g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = 0;
    func_00124800(&g3);

    g3.flg = 0;
    g3.flg |= 0x100;
    g3.x0.fd = dx; g3.y0.fd = dy + dh; g3.z0 = dz;
    g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = dz;
    g3.x2.fd = dx + dw; g3.y2.fd = dy + dh; g3.z2 = dz;
    g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = 0;
    g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
    g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
    func_00124800(&g3);

    if (objw->def->ptex_obj > 1) {
        move_x = objw->x - objw->ptex[0].x;
        move_y = objw->y - objw->ptex[0].y;
        for (i = 1; i < objw->def->ptex_obj; i++) {
            dx = mx + objw->ptex[i].x + move_x;
            dy = my + objw->ptex[i].y + move_y;
            dw = objw->ptex[i].w;
            dh = objw->ptex[i].h;
            dz = mz + objw->ptex[i].z;
            g3.flg = 0;
            g3.flg |= 0x100;
            g3.x0.fd = dx; g3.y0.fd = dy; g3.z0 = dz;
            g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = dz;
            g3.x2.fd = dx; g3.y2.fd = dy + dh; g3.z2 = dz;
            g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = 0;
            g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
            g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = 0;
            func_00124800(&g3);

            g3.flg = 0;
            g3.flg |= 0x100;
            g3.x0.fd = dx; g3.y0.fd = dy + dh; g3.z0 = dz;
            g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = dz;
            g3.x2.fd = dx + dw; g3.y2.fd = dy + dh; g3.z2 = dz;
            g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = 0;
            g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
            g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
            func_00124800(&g3);
        }
    }
}

static void NetWin_RccsselLineDisp(struct _CWS_WIN_W *win) {
    struct _net_win_rccssel_w *winw;
    int i;
    anon_1_152 g3;
    int dx;
    int dy;
    int dw;
    int dh;
    int dr;
    int dg;
    int db;
    int da;
    int dz;
    int dar;

    winw = (struct _net_win_rccssel_w *)win->work;
    switch (winw->line_step) {
    case 0:
    case 1:
        winw->line_pos[0].x = 0;
        winw->line_pos[0].y = winw->line_start_point_y;
        winw->line_pos[0].w = 0;
        winw->line_pos[0].h = 3;
        winw->line_disp_flag[0] = 0;
        winw->line_pos[1].x = 10;
        winw->line_pos[1].y = winw->line_start_point_y;
        winw->line_pos[1].w = 3;
        winw->line_pos[1].h = 0;
        winw->line_disp_flag[1] = 0;
        winw->line_pos[2].x = 10;
        winw->line_pos[2].y = winw->line_start_point_y;
        winw->line_pos[2].w = 3;
        winw->line_pos[2].h = 0;
        winw->line_disp_flag[2] = 0;
        winw->line_pos[3].x = 13;
        winw->line_pos[3].y = 0;
        winw->line_pos[3].w = 0;
        winw->line_pos[3].h = 3;
        winw->line_disp_flag[3] = 0;
        winw->line_pos[4].x = 13;
        winw->line_pos[4].y = 0xD9;
        winw->line_pos[4].w = 0;
        winw->line_pos[4].h = 3;
        winw->line_disp_flag[4] = 0;
        winw->line_move_time = 0;
        if (winw->line_step == 1) winw->line_step++;
        break;
    case 2:
        winw->line_disp_flag[0] = 1;
        if (CwsObjMove(&winw->line_pos[0].w, &winw->line_move_time, 0xA, 5, 1) != 0) {
            winw->line_move_time = 0;
            winw->line_step++;
        }
        break;
    case 3:
        winw->line_disp_flag[1] = 1;
        winw->line_disp_flag[2] = 1;
        CwsObjMoveOpt(&winw->line_pos[1].y, winw->line_move_time, 0, 0xA, 1);
        winw->line_pos[1].h = winw->line_start_point_y - winw->line_pos[1].y >= 0
                            ? winw->line_start_point_y - winw->line_pos[1].y
                            : -(winw->line_start_point_y - winw->line_pos[1].y);
        if (CwsObjMove(&winw->line_pos[2].h, &winw->line_move_time, 0xDC - winw->line_pos[2].y, 0xA, 1) != 0) {
            winw->line_move_time = 0;
            winw->line_step++;
        }
        break;
    case 4:
        winw->line_disp_flag[3] = 1;
        winw->line_disp_flag[4] = 1;
        CwsObjMoveOpt(&winw->line_pos[3].w, winw->line_move_time, 0x64, 0xA, 1);
        if (CwsObjMove(&winw->line_pos[4].w, &winw->line_move_time, 0x64, 0xA, 1) != 0) {
            winw->line_move_time = 0;
            winw->line_step++;
        }
        break;
    case 5:
        winw->line_move_time = 0;
        break;
    }
    for (i = 0; i < 5; i++) {
        if (winw->line_disp_flag[i] > 0) {
            dx = win->v.x + winw->line_pos[i].x;
            dy = win->v.y + winw->line_pos[i].y;
            dw = winw->line_pos[i].w;
            dh = winw->line_pos[i].h;
            dz = win->v.z + 0x20;
            dr = win->v.r * 7 * win->v.bri / 0x4000;
            dg = win->v.g * 246 * win->v.bri / 0x4000;
            db = win->v.b * 176 * win->v.bri / 0x4000;
            da = win->v.a;
            if (i == 3 || i == 4) {
                dar = (0x64 - winw->line_pos[3].w) * 0x80 / 0x64;
            } else {
                dar = 0x80;
            }

            g3.flg = 0;
            g3.flg |= 0x100;
            g3.x0.fd = dx; g3.y0.fd = dy; g3.z0 = dz;
            g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = dz;
            g3.x2.fd = dx; g3.y2.fd = dy + dh; g3.z2 = dz;
            g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
            g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = dar;
            g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
            func_00124800(&g3);

            g3.flg = 0;
            g3.flg |= 0x100;
            g3.x0.fd = dx; g3.y0.fd = dy + dh; g3.z0 = dz;
            g3.x1.fd = dx + dw; g3.y1.fd = dy; g3.z1 = dz;
            g3.x2.fd = dx + dw; g3.y2.fd = dy + dh; g3.z2 = dz;
            g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
            g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = dar;
            g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = dar;
            func_00124800(&g3);
        }
    }
}

void NetWin_RccsselSetRcData(struct _CWS_WIN_W *win, struct _nsv_rc_table_param_work *addr) { ((struct _net_win_rccssel_w *)win->work)->RcData = addr; }

void NetWin_RccsselSetLinePosY(struct _CWS_WIN_W *win, int pos_y) { ((struct _net_win_rccssel_w *)win->work)->line_start_point_y = pos_y; }

void NetWin_RccsselSetPage(struct _CWS_WIN_W *win, int page) {
    struct _net_win_rccssel_w *winw;
    int i;

    winw = (struct _net_win_rccssel_w *)win->work;
    if (winw->nm_page != page) {
        winw->nm_page = page;
        if (page == 0) {
            for (i = 0; i < 5; i++) {
                CwsObjChangeTex(win->obj[2 + i], i + 0x30);
            }
            CwsObjChangePlate(win->obj[1], netwinrccssel_plate_num1_5);
        } else {
            for (i = 0; i < 5; i++) {
                CwsObjChangeTex(win->obj[2 + i], i + 0x35);
            }
            CwsObjChangePlate(win->obj[1], netwinrccssel_plate_num6_10);
        }
        for (i = 0; i < 5; i++) {
            winw->move_time[i] = 0;
            win->obj[2 + i]->x = 0x146;
        }
        winw->status &= ~2;
        winw->counter = 0;
    }
}

void NetWin_RccsselReflash(struct _CWS_WIN_W *win) {
    struct _net_win_rccssel_w *winw;

    winw = (struct _net_win_rccssel_w *)win->work;
    NetWin_RccsselSetPage(win, 0);
    winw->move_time[0] = 0;
    win->obj[2]->x = 0x146;
    winw->move_time[1] = 0;
    win->obj[3]->x = 0x146;
    winw->move_time[2] = 0;
    win->obj[4]->x = 0x146;
    winw->move_time[3] = 0;
    win->obj[5]->x = 0x146;
    winw->move_time[4] = 0;
    win->obj[6]->x = 0x146;
    winw->status &= ~2;
    winw->counter = 0;
}
