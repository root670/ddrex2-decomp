#include "src/CS/shop/shop_info.h"

anon_1_129 *shop_get_work(void);
void MultiWindowSetMode(int win_num, int mode);
void MultiWindowOpen(int win_num);
void MultiWindowClose(int win_num);
int shop_wait_obj_move(anon_1_129 *work, int obj_kind);
int shop_get_obj_count(anon_1_129 *work, int obj_kind);
void shop_set_obj_move(anon_1_129 *work, int obj_kind, int type, int frame);
void shop_select_info_disp_music(anon_1_129 *work, struct _CWS_WIN_W *winp, int x0, int y0);
void shop_select_info_disp_course(anon_1_129 *work, struct _CWS_WIN_W *winp, int x0, int y0);
int func_0011E1F0(int pid);
void func_0017A8A0(int);

int shop_is_info_disp(anon_1_129 *work) {
    int rtv = 0;
    switch (work->tab_cursor) {
    case 0:
    case 1:
        rtv = 1;
        break;
    }
    return rtv;
}

int shop_select_info(void) {
    anon_1_129 *work;
    int rtv;

    work = shop_get_work();
    rtv = 0;
    switch (work->step_s) {
    case 0:
        rtv = (int)shop_get_work();
        ((anon_1_129 *)rtv)->info_cursor = 0;
        ((anon_1_129 *)rtv)->info_list_disp = 0;
        rtv = 0;
        work->step_s++;
        break;

    case 1:
        MultiWindowSetMode(7, 1);
        MultiWindowOpen(7);
        shop_set_obj_move(work, 7, 1, 0x14);
        work->step_s++;
        break;
    case 2:
        if (shop_wait_obj_move(work, 7))
            work->step_s++;
        break;
    case 3:
        if (shop_select_info_ctrl())
            work->step_s++;
        break;
    case 4:
        shop_set_obj_move(work, 7, 2, 0x14);
        work->step_s++;
        break;
    case 5:
        if (shop_wait_obj_move(work, 7)) {
            MultiWindowClose(7);
            work->step_s = 0;
            rtv = 1;
        }
        break;
    }

    shop_select_info_disp();
    return rtv;
}

static void shop_select_info_disp(void) {
    anon_1_129 *work;
    struct _CWS_WIN_W *winp;
    int x0;
    int y0;
    int ofsx;
    int count;

    work = shop_get_work();
    winp = *(struct _CWS_WIN_W **)0x82446C;
    count = shop_get_obj_count(work, 7);
    switch (work->move_w[7].type) {
    case 1:
        ofsx = (0x14 - count) * 0x280 / 0x14;
        if (shop_wait_obj_move(work, 7)) {
            ofsx = 0;
            work->move_w[7].type = 3;
        }
        x0 = -ofsx;
        y0 = 0;
        break;
    case 2:
        ofsx = count * 0x280 / 0x14;
        if (shop_wait_obj_move(work, 7)) {
            ofsx = 0x280;
            work->move_w[7].type = 4;
        }
        x0 = -ofsx;
        y0 = 0;
        break;
    case 3:
        x0 = 0;
        y0 = 0;
        break;
    case 4:
        x0 = -0x280;
        y0 = 0;
        break;
    }
    switch (work->tab_cursor) {
    case 0:
        shop_select_info_disp_music(work, winp, x0, y0);
        break;
    case 1:
        shop_select_info_disp_course(work, winp, x0, y0);
        break;
    }
}

static int shop_select_info_ctrl(void) {
    anon_1_129 *work;
    anon_4_129 *padw;
    int pid;
    int rtv;

    work = shop_get_work();
    padw = &work->pad_w;
    rtv = 0;
    padw->dx = 0;
    padw->dy = 0;
    padw->decide = 0;
    padw->cancel = 0;
    for (pid = 0; pid < 2; pid++) {
        if ((func_0011E1F0(pid) & 0x8000) ? 1 : 0) {
            padw->dx--;
        } else if ((func_0011E1F0(pid) & 0x2000) ? 1 : 0) {
            padw->dx++;
        } else if ((func_0011E1F0(pid) & 0x1000) ? 1 : 0) {
            padw->dy--;
        } else if ((func_0011E1F0(pid) & 0x4000) ? 1 : 0) {
            padw->dy++;
        } else if ((func_0011E1F0(pid) & 0x60) ? 1 : 0) {
            padw->decide++;
        } else if ((func_0011E1F0(pid) & 0x110) ? 1 : 0) {
            padw->cancel++;
        }
    }
    if (padw->dx == 0 && padw->dy == 0) {
        if (padw->decide != 0 || padw->cancel != 0) {
            func_0017A8A0(3);
            rtv = 1;
        }
    } else if (padw->dx < 0 || padw->dy < 0) {
        work->confirm_cursor--;
        if (work->confirm_cursor < 0)
            work->confirm_cursor = 0;
    } else if (padw->dx > 0 || padw->dy > 0) {
        work->confirm_cursor++;
        if (work->confirm_cursor > 1)
            work->confirm_cursor = 1;
    }
    return rtv;
}
