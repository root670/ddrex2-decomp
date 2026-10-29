#include "src/CS/dancemaster/dmm_style.h"

#define D_00FC29D0 ((unsigned char *)0xFC29D0)

extern struct _CWS_WIN_W *D_00824450[];
extern struct _CWS_WIN_W *D_00824454[];

anon_4_223 *dmm_get_work(void);
int dmm_search_appear_area(void);
void dmm_copy_savedata(void);
void dmm_set_default_savedata(void);
int dmm_is_savedata(void);
void dmm_set_step(int step);
void dmm_set_obj_move(anon_4_223 *work, int obj, int mode);
int dmm_wait_obj_move(anon_4_223 *work, int obj, int cnt);
int dmm_wait(anon_4_223 *work, int cnt);
void dmm_set_wait(anon_4_223 *work);
void dmm_quit_on(void);
void dmm_bind_data_sel_tex(void);
void dmm_disp_title(anon_4_223 *work);
void dmm_bgm_set(unsigned int call);
void dmm_bgm_call(void);
void set_data_select_mess(void);
void set_data_warning_mess(void);
void MultiWindowInit(void);
void MultiWindowOpen(int win_num);
void MultiWindowClose(int win_num);
void *MultiWindowCreate(int win_num, int x, int y, int w, int h, int z, int tex_num);
void MultiWindowSetCautionMark(int win_num, int mark);
void MultiWindowCommon(void);
void MultiWindowDestroy(void);
unsigned int CwsWinGetStatus(struct _CWS_WIN_W *work);
char CwsStrSetCol(struct _CWS_WIN_W *win, int str_num, unsigned char col);
int func_0011E090(anon_26_223 *tbl, unsigned char *addr);
int func_0011DE80(void);
int func_00120250(int kind);
int func_0011E1F0(int pid);
void func_0017A8A0(int kind);

/* Retail carries the @anon28 record (the 0x24-byte
 * x0/y0/z0/w/h/u/v/r0/g0/b0/a0/flg aggregate) with nothing referring to it.  An
 * uncalled static function makes the compiler emit the type it is used through; the
 * body is dead code, so .text is unchanged. */
static void unused_style_types(anon_28_223 *p) { p->flg = 0; }

static int dmm_style_select_menu_ctrl(anon_4_223 *work) {
    anon_16_223 *menu;
    int pid;
    int ctrl;
    int rtv;

    menu = &work->style_menu;
    ctrl = 0;
    rtv = 0;
    pid = 0;
    do {
        if ((func_0011E1F0(pid) & 0x9000) ? 1 : 0) {
            ctrl--;
        } else if ((func_0011E1F0(pid) & 0x6000) ? 1 : 0) {
            ctrl++;
        }
        pid++;
    } while (pid < 2);
    pid = menu->cursor;
    if (ctrl < 0) {
        if (pid == 1) {
            menu->cursor = pid - 1;
        }
    } else if (ctrl > 0 && pid == 0 && dmm_is_savedata() != 0) {
        menu->cursor = menu->cursor + 1;
    }
    if (pid != menu->cursor) {
        func_0017A8A0(0xA);
    }
    pid = 0;
    do {
        if (ctrl != 0) {
            break;
        }
        if ((func_0011E1F0(pid) & 0x60) ? 1 : 0) {
            work->start_pid = pid;
            func_0017A8A0(3);
            rtv = 1;
            break;
        } else if ((func_0011E1F0(pid) & 0x110) ? 1 : 0) {
            func_0017A8A0(0x63);
            rtv = 2;
            break;
        }
        pid++;
    } while (pid < 2);
    return rtv;
}

static int dmm_style_select_menu(anon_4_223 *work) {
    anon_16_223 *menu;
    struct _CWS_WIN_W *winp;
    int sel_rtv;
    int i;

    menu = &work->style_menu;
    switch (work->step_s) {
    case 0:
        set_data_select_mess();
        MultiWindowOpen(0);
        work->step_s++;
        break;
    case 1:
        if ((CwsWinGetStatus(D_00824450[0]) & 4) == 0) {
            work->step_s++;
        }
        break;
    case 2:
        sel_rtv = dmm_style_select_menu_ctrl(work);
        winp = D_00824450[0];
        if (menu->cursor == 0) {
            CwsStrSetCol(winp, 0, 1);
            CwsStrSetCol(winp, 1, 0);
        } else {
            CwsStrSetCol(winp, 0, 0);
            CwsStrSetCol(winp, 1, 1);
        }
        switch (sel_rtv) {
        case 1:
            if (menu->cursor == 0 && dmm_is_savedata() != 0) {
                work->step_s = 10;
                break;
            }
            MultiWindowClose(0);
            work->step_s = 3;
            break;
        case 2:
            MultiWindowClose(0);
            work->step_s = 4;
            break;
        }
        break;
    case 3:
        if ((CwsWinGetStatus(D_00824450[0]) & 8) == 0) {
            work->step_s = 0;
            return 1;
        }
        break;
    case 4:
        if ((CwsWinGetStatus(D_00824450[0]) & 8) == 0) {
            work->step_s = 0;
            return 2;
        }
        break;
    case 10:
        set_data_warning_mess();
        MultiWindowClose(0);
        work->step_s++;
        break;
    case 11:
        if ((CwsWinGetStatus(D_00824450[0]) & 8) == 0) {
            dmm_set_wait(work);
            work->step_s++;
        }
        break;
    case 12:
        if (dmm_wait(work, 10)) {
            MultiWindowOpen(1);
            work->step_s++;
        }
        break;
    case 13:
        if ((CwsWinGetStatus(D_00824454[0]) & 4) == 0) {
            work->step_s++;
        }
        break;
    case 14:
        menu = (anon_16_223 *)0;
        i = 0;
        for (; i < 2; i++) {
            if ((func_0011E1F0(i) & 0x170) ? 1 : 0) {
                func_0017A8A0(3);
                menu = (anon_16_223 *)1;
                break;
            }
        }
        if (menu) {
            MultiWindowClose(1);
            work->step_s++;
        }
        break;
    case 15:
        if ((CwsWinGetStatus(D_00824454[0]) & 8) == 0) {
            work->step_s = 0x16;
        }
        break;
    case 0x16:
        work->step_s = 0;
        return 1;
    }
    return 0;
}

static void dmm_style_finish(void) {
    anon_4_223 *work;
    int pid;

    work = dmm_get_work();
    SaveData.dmm.max_area = dmm_search_appear_area();
    if (work->style_menu.cursor == 0) {
        if (dmm_is_savedata() == 0) {
            dmm_set_default_savedata();
            SaveData.dmm.is_savedata = 1;
            SaveData.dmm.disp_type = 0;
            SaveData.dmm.cur_cursor = SaveData.dmm.max_area == 1;
            work->old_cursor = SaveData.dmm.cur_cursor;
            work->next_cursor = SaveData.dmm.cur_cursor;
            work->sel_cursor = 0;
            work->sel_old_cursor = work->sel_cursor;
            pid = work->sel_cursor;
            work->sel_cursor_disp = pid;
        } else {
            dmm_copy_savedata();
            dmm_set_default_savedata();
            SaveData.dmm.is_savedata = 1;
            SaveData.dmm.disp_type = 0;
            SaveData.dmm.cur_cursor = SaveData.dmm.max_area == 1;
            work->old_cursor = SaveData.dmm.cur_cursor;
            work->next_cursor = SaveData.dmm.cur_cursor;
            work->sel_cursor = 0;
            work->sel_old_cursor = work->sel_cursor;
            pid = work->sel_cursor;
            work->sel_cursor_disp = pid;
        }
    } else if (work->style_menu.cursor == 1 && dmm_is_savedata() != 0) {
        if (SaveData.dmm.cur_cursor == -1) {
            SaveData.dmm.cur_cursor = SaveData.dmm.max_area == 1;
        }
        work->old_cursor = SaveData.dmm.cur_cursor;
        work->next_cursor = SaveData.dmm.cur_cursor;
        work->sel_cursor = 0;
        work->sel_old_cursor = work->sel_cursor;
        pid = work->sel_cursor;
        work->sel_cursor_disp = pid;
    }
    pid = work->start_pid;
    g_game_w.player[pid].select = 2;
    g_game_w.player[1 - pid].select = 0;
    g_game_w.player[pid].mode.style = 1;
    g_game_w.player[1 - pid].mode.style = 0;
    g_game_w.style = 1;
}

void dmm_style(anon_4_223 *work) {
    int step_type;
    int rtv_sel;
    anon_4_223 *work2;

    step_type = 10;
    switch (work->step) {
    case 0:
        if (func_0011E090(dmm_bin, D_00FC29D0) != 0) {
            work->step++;
        }
        break;
    case 1:
        if (func_0011DE80() != 0) {
            work->step++;
        }
        break;
    case 2:
        if (func_00120250(2) == 1) {
            dmm_bind_data_sel_tex();
            work->free_mem_addr = g_game_w.last_data_addr;
            work->step++;
        }
        break;
    case 3:
        dmm_quit_on();
        work2 = dmm_get_work();
        if (dmm_is_savedata() != 0) {
            work2->style_menu.cursor = 1;
        } else {
            work2->style_menu.cursor = 0;
        }
        MultiWindowInit();
        MultiWindowCreate(0, 0, 0, 0xC8, 0x60, 0x6000, -1);
        MultiWindowCreate(1, 0, 0, 0x190, 0xC4, 0x7000, -0xD);
        MultiWindowSetCautionMark(1, 3);
        dmm_bgm_set(0x56E009D);
        func_0017A8A0(0x54);
        dmm_set_obj_move(work, 0, 1);
        work->step++;
        break;
    case 4:
        if (dmm_wait_obj_move(work, 0, 0x12)) {
            work->step++;
        }
        break;
    case 5:
        rtv_sel = dmm_style_select_menu(work);
        switch (rtv_sel) {
        case 1:
            work->step = step_type;
            break;
        case 2:
            work->step = 0x14;
            break;
        }
        break;
    case 0xA:
        work->step = work->step + 2;
        break;
    case 0xB:
        work->step = work->step + 1;
        break;
    case 0xC:
        dmm_style_finish();
        dmm_set_obj_move(work, 0, 2);
        work->step++;
        break;
    case 0xD:
        if (dmm_wait_obj_move(work, 0, 0x12) != 0) {
            MultiWindowDestroy();
            work->before_state = 1;
            if (work->is_disp_dancer == 1) {
                step_type = 8;
            } else {
                step_type = 3;
            }
        }
        break;
    case 0x14:
        dmm_set_obj_move(work, 0, 2);
        work->step++;
        break;
    case 0x15:
        if (dmm_wait_obj_move(work, 0, 0x12) != 0) {
            MultiWindowDestroy();
            work->before_state = 1;
            dmm_set_step(9);
            return;
        }
        break;
    }
    dmm_disp_title(dmm_get_work());
    MultiWindowCommon();
    dmm_bgm_call();
    dmm_set_step(step_type);
}
