#include "src/CS/edit/ed_menu.h"

anon_5_176 *func_00196EF0(void);
int func_00196E20(int);
int func_001B7C30(void *, int);
void func_00196DB0(void);
void func_00192850(int, int, int, int);
void func_0017A8A0(int);
void func_00127F60(void *, int);
void func_00123CF0(anon_6_176 *);
void func_00123950(anon_9_176 *);
struct tex_bind *func_0012D070(int);
void CSXX20Puts(short, short, unsigned char *, int, int, int, int, int, int);
void *co_obj_set(anon_11_176 *func, void (*init)(void *), unsigned char pri);
void co_obj_step_set(void *ow, int step, void (*init)(void *));
void co_base00_set(unsigned short pri, unsigned char obj_pri, int tex_id);
void co_caption_disap(void);
void co_cursor01_init(struct _tag_cCoCursor01 *p);
void co_cursor01_disp(struct _tag_cCoCursor01 *p, float x, float y, int a, int bri, int pri, int tex_id, int flag);
float co_sel00_x(void);
int co_sel00_is_exist(void);
void co_sel00_disap_set(void);
struct _MULTI_WIN_W *MultiWindowCreate(int win_num, int x, int y, int w, int h, int z, int tex_num);
void MultiWindowOpen(int win_num);
void MultiWindowClose(int win_num);
void MultiWindowDelete(int win_num);
unsigned int CwsWinGetStatus(struct _CWS_WIN_W *work);
extern struct _CWS_WIN_W *D_00824450[];

static anon_8_176 *mw = &ed_menu_w;
anon_11_176 edit_menu_leftbase_objf = {
    (int (*)(void *))edit_menu_leftbase_appr,
    (int (*)(void *))edit_menu_leftbase_exec,
    edit_menu_leftbase_dsap,
    (int (*)(void *))edit_menu_leftbase_disp,
};
anon_11_176 edit_menu_item_objf = {
    edit_menu_item_appr,
    (int (*)(void *))edit_menu_item_exec,
    edit_menu_item_dsap,
    edit_menu_item_disp,
};

static inline void menu_icon_set(void) {
    anon_5_176 *w2 = func_00196EF0();
    int n = mw->cur_menu;
    if (w2->mc_check == 1) {
        n += 6;
    }
    func_00192850(0, n, 0xC, 0);
}

void ed_menu_init(void) {
    anon_5_176 *work;

    work = func_00196EF0();
    func_001B7C30(mw, 0x1C);
    mw->cur_menu = work->first_menu_num;
    mw->old_mc_check = work->mc_check;
    func_00196DB0();
    mw->leftbase_ow = co_obj_set(&edit_menu_leftbase_objf, 0, 0x80);
    mw->menuitem_ow = co_obj_set(&edit_menu_item_objf, 0, 0x80);
    MultiWindowCreate(0, 0, 0x8C, 0x258, 0x5A, 0x1008, -0xE);
    menu_icon_set();
    MultiWindowOpen(0);
}

int ed_menu_step(void) {
    anon_5_176 *work;
    int next_step;
    int ud;
    int is_exit;

    work = func_00196EF0();
    next_step = work->main_step;
    {
        int next_tab[6] = { 10, 12, 13, 14, 15, 16 };
        ud = 0;
        switch (mw->step) {
        case 0:
            mw->step++;
        case 1:
            if (edit_joy_rep & 0x1000) {
                ud = -1;
            }
            else if (edit_joy_rep & 0x4000) {
                ud = 1;
            }
            mw->cur_menu = (mw->cur_menu + 6 + ud) % 6;
            if (ud) {
                func_0017A8A0(0x67);
                menu_icon_set();
            }
            if (ud == 0) {
                is_exit = 0;
                if (edit_joy_trg & 0x60) {
                    work->tmp_step = 9;
                    is_exit = 1;
                    switch (mw->cur_menu) {
                    case 0:
                    case 4:
                        func_0017A8A0(3);
                        break;
                    case 1:
                    case 2:
                    case 3:
                        if (work->mc_check) {
                            func_0017A8A0(0x17);
                            is_exit = 0;
                        }
                        else {
                            func_0017A8A0(3);
                        }
                        break;
                    case 5:
                        func_0017A8A0(0x63);
                        break;
                    }
                }
                else if (edit_joy_trg & 0x110) {
                    is_exit = 1;
                    mw->cur_menu = 5;
                    func_0017A8A0(0x63);
                }
                if (is_exit) {
                    if (mw->cur_menu != 0 && mw->cur_menu != 4) {
                        co_caption_disap();
                    }
                    co_obj_step_set(mw->leftbase_ow, 2, 0);
                    co_obj_step_set(mw->menuitem_ow, 2, 0);
                    MultiWindowClose(0);
                    mw->step++;
                }
            }
            break;
        case 2:
            if (mw->leftbase_ow == 0 && mw->menuitem_ow == 0 && !(CwsWinGetStatus(D_00824450[0]) & 2)) {
                MultiWindowDelete(0);
                next_step = next_tab[mw->cur_menu];
            }
            break;
        }
        if (work->mc_check != mw->old_mc_check) {
            menu_icon_set();
            mw->old_mc_check = work->mc_check;
        }
        return next_step;
    }
}

void ed_menu_fini(void) {
    anon_5_176 *work = func_00196EF0();
    work->first_menu_num = mw->cur_menu;
}

static int edit_menu_leftbase_appr(void) {
    co_base00_set(0x1000, 0x80, func_00196E20(4));
    return 1;
}

static int edit_menu_leftbase_exec(void) {
    return 0;
}

static int edit_menu_leftbase_dsap(void *w) {
    anon_10_176 *mlbw = w;

    if (mlbw->step == 0) {
        co_sel00_disap_set();
        mlbw->step++;
    }
    else if (!co_sel00_is_exist()) {
        mw->leftbase_ow = 0;
        return 1;
    }
    return 0;
}

static int edit_menu_leftbase_disp(void) {
    float x;

    if (co_sel00_is_exist()) {
        x = co_sel00_x();
        CSXX20Puts(45.0f + x, -0xB1, (unsigned char *)"SELECT THE MENU", 0x80, 0x1010, 3, 0x80, 0xFB, 0);
    }
}

static int edit_menu_item_appr(void *w) {
    anon_4_176 *miw = w;
    int i;
    float dstx;
    int ct = 0;

    switch (miw->step) {
    case 0:
        miw->each[0].x = 320.0f;
        miw->each[0].y = -136.0f;
        miw->each[0].timer = 0.0f;
        miw->each[1].x = 400.0f;
        miw->each[1].y = -98.0f;
        miw->each[1].timer = 0.0f;
        miw->each[2].x = 480.0f;
        miw->each[2].y = -60.0f;
        miw->each[2].timer = 0.0f;
        miw->each[3].x = 560.0f;
        miw->each[3].y = -22.0f;
        miw->each[3].timer = 0.0f;
        miw->each[4].x = 640.0f;
        miw->each[4].y = 16.0f;
        miw->each[4].timer = 0.0f;
        miw->each[5].x = 720.0f;
        miw->each[5].y = 54.0f;
        miw->each[5].timer = 0.0f;
        co_cursor01_init(&miw->co_curw);
        miw->step++;
        break;
    case 1:
        for (i = 0; i < 6; i++) {
            dstx = -204.0f + (float)(i * 30);
            miw->each[i].x -= 50.0f;
            if (miw->each[i].x < dstx) {
                miw->each[i].x = dstx;
                ct++;
            }
        }
        if (ct == 6) {
            miw->step = 0;
            return 1;
        }
        break;
    }
    return 0;
}

static int edit_menu_item_exec(void) {
    return 0;
}

static int edit_menu_item_dsap(void *w) {
    anon_4_176 *miw = w;
    int i;
    int ct = 0;

    for (i = 0; i < 6; i++) {
        miw->each[i].x += 50.0f;
        if (miw->each[i].x >= 320.0f) {
            ct++;
        }
    }
    if (ct == 6) {
        mw->menuitem_ow = 0;
        return 1;
    }
    return 0;
}

static int edit_menu_item_disp(void *w) {
    anon_4_176 *miw = w;
    anon_2_176 info;
    int i;
    int cur;
    anon_6_176 sp;
    anon_9_176 sp2;
    float x;
    float y;
    float u;
    int ix;
    struct tex_bind *bp;
    float dw;
    float dh;

    cur = mw->cur_menu;
    for (i = 0; i < 6; i++) {
        func_00127F60(&info, func_00196E20(0x2A));
        sp.flg = 0;
        sp.flg |= 0x100;
        sp.x0.fd = 26.0f + miw->each[i].x;
        sp.y0.fd = 6.0f + miw->each[i].y;
        sp.z0 = 0x4000;
        sp.r0 = 0x80;
        sp.g0 = 0x80;
        sp.b0 = 0x80;
        sp.a0 = 0x80;
        sp.u = (float)(i == cur ? 168 : 0);
        sp.v = (float)(i * 24);
        sp.w = 168.0f;
        sp.h = 24.0f;
        func_00123CF0(&sp);
        func_00127F60(&info, func_00196E20(8));
        sp.flg = 0;
        sp.flg |= 0x100;
        sp.x0.fd = 2.0f + miw->each[i].x;
        sp.y0.fd = 1.0f + miw->each[i].y;
        sp.z0 = 0x4000;
        sp.r0 = 0x80;
        sp.g0 = 0x80;
        sp.b0 = 0x80;
        sp.a0 = 0x80;
        sp.u = 0;
        sp.v = (float)(i * 32);
        sp.w = 24.0f;
        sp.h = 32.0f;
        func_00123CF0(&sp);
        x = miw->each[i].x;
        y = miw->each[i].y;
        u = 0.0f;
        func_00127F60(&info, func_00196E20(9));
        sp2.flg = 0;
        sp2.flg |= 0x100;
        sp2.r0 = 0x80;
        sp2.g0 = 0x80;
        sp2.b0 = 0x80;
        sp2.a0 = 0x80;
        for (ix = 0; ix < 3; ix++) {
            dw = ix == 1 ? 4.0f : 16.0f;
            dh = ix == 1 ? 256.0f : dw;
            sp2.u = u;
            sp2.v = (float)(i == cur ? 34 : 0);
            sp2.w = dw;
            sp2.h = 34.0f;
            sp2.x0.fd = x;
            sp2.y0.fd = y;
            sp2.z0 = 0x3FF0;
            sp2.x1.fd = x + dh;
            sp2.y1.fd = 34.0f + y;
            sp2.z1 = 0x3FF0;
            func_00123950(&sp2);
            u += dw;
            x += dh;
        }
        if (i == cur) {
            bp = func_0012D070(0x44);
            co_cursor01_disp(&miw->co_curw, miw->each[i].x, 17.0f + miw->each[i].y, 0x80, 0x80, 0x4000, bp->id, 2);
        }
    }
}
