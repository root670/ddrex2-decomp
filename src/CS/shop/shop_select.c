#include "src/CS/shop/shop_select.h"

anon_0_126 *shop_get_work(void);
int shop_init_obj_move_work(anon_0_126 *work);
void shop_multi_win_init(anon_0_126 *work);
void shop_multi_win_destroy(anon_0_126 *work);
void shop_fade_in_init(void);
void shop_fade_out_init(void);
int shop_is_fade_off(void);
void shop_set_obj_move(anon_0_126 *work, int obj_kind, int type, int frame);
int shop_wait_obj_move(anon_0_126 *work, int obj_kind);
void shop_set_step(int step);
void shop_disp_title(anon_0_126 *work);
void shop_disp_tab(anon_0_126 *work);
void shop_disp_contents_frame(anon_0_126 *work);
void shop_disp_scroll_bar(anon_0_126 *work);
void shop_disp_contents(anon_0_126 *work);
void shop_disp_my_point(anon_0_126 *work);
void shop_disp_cursor(anon_0_126 *work, int x, int y, int pri, int anime_on);
void func_001253C0(anon_b14b78a0b5d3 *rect, int mode);
void func_001252F0(int mode);
int func_0011E1F0(int pid);
int func_0011E210(int pid);
void func_0017A8A0(int kind);
void shop_bgm_call(void);
int shop_is_info_disp(anon_0_126 *work);
int shop_select_info(void);
void shop_purchase(anon_0_126 *work);
int shop_is_purchasable(anon_0_126 *work);
int shop_get_contents_num(anon_0_126 *work);
int shop_get_disp_num(anon_0_126 *work);
void shop_bgm_set(unsigned int call);
void MultiWindowCommon(void);
void MultiWindowOpen(int win_num);
void MultiWindowClose(int win_num);
int CwsWinGetStatus(struct _CWS_WIN_W *work);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char,
                  unsigned char, unsigned int, int, unsigned char, unsigned char *);
char CwsStrSetBri(struct _CWS_WIN_W *, int, unsigned char);

static int shop_select_confirm_ctrl(void) {
    anon_0_126 *work;
    anon_1_126 *padw;
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
        if (padw->decide != 0) {
            if (work->confirm_cursor == 0) {
                func_0017A8A0(3);
                rtv = 1;
            } else {
                func_0017A8A0(0x5E);
                rtv = 2;
            }
        } else if (padw->cancel != 0) {
            func_0017A8A0(0x5E);
            rtv = 2;
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

static int shop_select_confirm(void) {
    anon_0_126 *work;
    struct _CWS_WIN_W *winp;
    int x;
    int y;
    int rtv_sel;
    int rtv;

    work = shop_get_work();
    winp = *(struct _CWS_WIN_W **)0x824468;
    rtv = 0;
    switch (work->step_s) {
    case 0:
        CwsStrSetAll(winp, 0, 0, -0x1B, 0xA000, 0x80, 0x80, 0x400, 1, 0,
                     (unsigned char *)"Korede iidesuka?");

        CwsStrSetAll(winp, 1, -0x48, 6, 0xA000, 0x80, 0x80, 0x400, 1, 0,
                     (unsigned char *)"YES");

        CwsStrSetAll(winp, 2, 0x48, 6, 0xA000, 0x80, 0x80, 0x400, 1, 0,
                     (unsigned char *)"NO");

        work->confirm_cursor = 0;
        if (work->confirm_cursor == 0) {
            CwsStrSetBri(winp, 1, 0x80);
            CwsStrSetBri(winp, 2, 0x40);
        } else {
            CwsStrSetBri(winp, 1, 0x40);
            CwsStrSetBri(winp, 2, 0x80);
        }
        work->step_s++;
        break;
    case 1:
        MultiWindowOpen(6);
        work->step_s++;
        break;
    case 2:
        if (!(CwsWinGetStatus(winp) & 4))
            work->step_s++;
        break;
    case 3:
        rtv_sel = shop_select_confirm_ctrl();
        if (work->confirm_cursor == 0) {
            CwsStrSetBri(winp, 1, 0x80);
            CwsStrSetBri(winp, 2, 0x40);
        } else {
            CwsStrSetBri(winp, 1, 0x40);
            CwsStrSetBri(winp, 2, 0x80);
        }
        if (work->confirm_cursor == 0) {
            x = -0xDE;
            y = 0x96;
        } else {
            x = -0x4A;
            y = 0x96;
        }
        shop_disp_cursor(work, x, y, 0xB000, 1);
        switch (rtv_sel) {
        case 1:
            work->step_s++;
            break;
        case 2:
            work->step_s = 6;
            break;
        }
        break;
    case 4:
        shop_purchase(work);
        MultiWindowClose(6);
        work->step_s++;
        break;
    case 5:
        if (!(CwsWinGetStatus(winp) & 8)) {
            work->step_s = 0;
            rtv = 1;
        }
        break;
    case 6:
        MultiWindowClose(6);
        work->step_s++;
        break;
    case 7:
        if (!(CwsWinGetStatus(winp) & 8)) {
            work->step_s = 0;
            rtv = 2;
        }
        break;
    }
    return rtv;
}

static void shop_select_disp(void) {
    anon_0_126 *work;

    work = shop_get_work();
    shop_disp_title(work);
    shop_disp_tab(work);
    shop_disp_contents_frame(work);
    func_001253C0(&work->shop_rect, 4);
    func_001253C0(&work->shop_rect, 2);
    func_001253C0(&work->shop_rect, 0);
    shop_disp_scroll_bar(work);
    shop_disp_contents(work);
    func_001252F0(4);
    func_001252F0(2);
    func_001252F0(0);
    shop_disp_my_point(work);
    MultiWindowCommon();
}

static int shop_select_ctrl(void) {
    anon_0_126 *work;
    anon_1_126 *padw;
    int set_frame;
    int pid;
    int rtv;
    int list_num;
    int disp_num;

    work = shop_get_work();
    padw = &work->pad_w;
    rtv = 0;
    padw->dx = 0;
    padw->dy = 0;
    padw->decide = 0;
    padw->cancel = 0;
    for (pid = 0; pid < 2; pid++) {
        if ((func_0011E210(pid) & 0x8000) ? 1 : 0) {
            padw->dx--;
            break;
        } else if ((func_0011E210(pid) & 0x2000) ? 1 : 0) {
            padw->dx++;
            break;
        } else if ((func_0011E210(pid) & 0x1000) ? 1 : 0) {
            padw->dy--;
            padw->repeat_y--;
            if (padw->repeat_y < -0x3C)
                padw->repeat_y = -0x3C;
            break;
        } else if ((func_0011E210(pid) & 0x4000) ? 1 : 0) {
            padw->dy++;
            padw->repeat_y++;
            if (padw->repeat_y > 0x3C)
                padw->repeat_y = 0x3C;
            break;
        } else if ((func_0011E1F0(pid) & 0x60) ? 1 : 0) {
            padw->decide++;
            break;
        } else if ((func_0011E1F0(pid) & 0x110) ? 1 : 0) {
            padw->cancel++;
            break;
        }
        padw->repeat_y = 0;
    }
    if (work->tab_state)
        return 0;
    if (work->cont_state)
        return 0;
    if (padw->dx == 0 && padw->dy == 0) {
        if (padw->decide != 0) {
            if (shop_is_purchasable(work)) {
                func_0017A8A0(3);
                rtv = 1;
            } else {
                func_0017A8A0(0x17);
            }
        } else if (padw->cancel != 0) {
            func_0017A8A0(0x5E);
            rtv = 2;
        }
    } else {
        list_num = shop_get_contents_num(work);
        disp_num = shop_get_disp_num(work);
        if (padw->dx < 0) {
            work->tab_cursor_new--;
            if (work->tab_cursor_new < 0)
                work->tab_cursor_new = 5;
            work->tab_state = 1;
            shop_set_obj_move(work, 1, 7, 0x14);
            shop_set_obj_move(work, 2, 7, 0x14);
        } else if (padw->dx > 0) {
            work->tab_cursor_new++;
            if (work->tab_cursor_new > 5)
                work->tab_cursor_new = 0;
            work->tab_state = 2;
            shop_set_obj_move(work, 1, 7, 0x14);
            shop_set_obj_move(work, 2, 7, 0x14);
        } else if (padw->dy < 0) {
            if (list_num == 0)
                return 0;
            if (padw->repeat_y < -0x3B)
                set_frame = 4;
            else
                set_frame = 0x14;
            work->contents_cursor--;
            if (work->contents_cursor >= 0) {
                shop_set_obj_move(work, 4, 8, set_frame);
                shop_set_obj_move(work, 5, 8, set_frame);
                work->cont_state = 3;
            } else {
                work->contents_cursor = 0;
            }
            work->contents_cursor_new = work->contents_cursor;
            if (work->contents_cursor < work->contents_cursor_disp_top
                || work->contents_cursor_disp_top + (disp_num - 1) < work->contents_cursor) {
                work->contents_cursor_disp_top--;
                work->contents_cursor_disp_top_new = work->contents_cursor_disp_top;
                shop_set_obj_move(work, 3, 8, set_frame);
                shop_set_obj_move(work, 6, 8, set_frame);
                shop_set_obj_move(work, 5, 8, set_frame);
                work->cont_state = 3;
            }
        } else if (padw->dy > 0) {
            if (list_num == 0)
                return 0;
            set_frame = (padw->repeat_y >= 0x3C) ? 4 : 0x14;
            work->contents_cursor_new++;
            if (work->contents_cursor_new <= list_num - 1) {
                shop_set_obj_move(work, 4, 9, set_frame);
                shop_set_obj_move(work, 5, 9, set_frame);
                work->cont_state = 4;
            } else {
                work->contents_cursor_new = list_num - 1;
            }
            if (work->contents_cursor_new < work->contents_cursor_disp_top
                || work->contents_cursor_disp_top + (disp_num - 2) < work->contents_cursor_new) {
                work->contents_cursor_disp_top_new++;
                shop_set_obj_move(work, 3, 9, set_frame);
                shop_set_obj_move(work, 6, 9, set_frame);
                shop_set_obj_move(work, 5, 9, set_frame);
                work->cont_state = 4;
            }
        }
    }
    shop_get_work();
    shop_bgm_set(0x56E009D);
    return rtv;
}

void shop_select(anon_0_126 *work) {
    int rtv_sel;

    switch (work->step) {
    case 0:
        rtv_sel = (int)shop_get_work();
        shop_init_obj_move_work((anon_0_126 *)rtv_sel);
        shop_multi_win_init((anon_0_126 *)rtv_sel);
        ((anon_0_126 *)rtv_sel)->shop_rect.x = -0x140;
        ((anon_0_126 *)rtv_sel)->shop_rect.y = -0xE0;
        ((anon_0_126 *)rtv_sel)->shop_rect.w = 0x280;
        ((anon_0_126 *)rtv_sel)->shop_rect.h = 0x1C0;
        if (work->before_mode != 0x37)
            shop_fade_in_init();
        work->step = 1;
        break;
    case 1:
        if (shop_is_fade_off()) {
            shop_set_obj_move(work, 0, 1, 0x14);
            shop_set_obj_move(work, 1, 1, 0x14);
            shop_set_obj_move(work, 8, 1, 0x14);
            work->step++;
        }
        break;
    case 2:
        if (shop_wait_obj_move(work, 0)) {
            shop_set_obj_move(work, 1, 6, 0x14);
            shop_set_obj_move(work, 2, 1, 0x14);
            work->step++;
        }
        break;
    case 3:
        if (shop_wait_obj_move(work, 1))
            work->step++;
        break;
    case 4:
        work->cursor_anime_flag = 1;
        rtv_sel = shop_select_ctrl();
        switch (rtv_sel) {
        case 1:
            work->step++;
            work->step_s = 0;
            break;
        case 2:
            work->step = 7;
            break;
        }
        break;
    case 5:
        work->cursor_anime_flag = 0;
        rtv_sel = shop_select_confirm();
        switch (rtv_sel) {
        case 1:
            if (shop_is_info_disp(work))
                work->step = 6;
            else
                work->step = 4;
            work->step_s = 0;
            break;
        case 2:
            work->step = 4;
            work->step_s = 0;
            break;
        }
        break;
    case 6:
        if (shop_select_info()) {
            work->step = 4;
            work->step_s = 0;
        }
        break;
    case 7:
        shop_set_obj_move(work, 1, 7, 0x14);
        shop_set_obj_move(work, 2, 2, 0x14);
        work->step++;
        break;
    case 8:
        if (shop_wait_obj_move(work, 2)) {
            if (work->before_mode != 0x37)
                shop_fade_out_init();
            shop_set_obj_move(work, 0, 2, 0x14);
            shop_set_obj_move(work, 1, 2, 0x14);
            shop_set_obj_move(work, 8, 2, 0x14);
            work->step++;
        }
        break;
    case 9:
        if (shop_wait_obj_move(work, 0)) {
            if (shop_is_fade_off()) {
                shop_multi_win_destroy(work);
                shop_set_step(4);
                return;
            }
        }
        break;
    }
    shop_select_disp();
    shop_bgm_call();
    shop_set_step(5);
}
