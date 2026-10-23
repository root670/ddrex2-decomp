#include "src/CS/edit/ed_edit_disp.h"

anon_2_181 *func_00196EF0(void);
int func_00196E20(int);
int func_00127F60(void *, int);
void func_00123CF0(anon_5_181 *);
void func_00124140(anon_4_181 *);
void func_001BE7E0(unsigned char *, unsigned char *, ...);
void CSXX20Puts(short, short, unsigned char *, int, int, int, int, int, int);

anon_7_181 ed_lrframe_objf = {
    ed_lrframe_appr,
    ed_lrframe_exec,
    ed_lrframe_dsap,
    ed_lrframe_disp,
};
static int EdIconTbl[9] = { 0, 0x24, 0x48, 0x6C, 0xB4, 0xD8, 0xFC, 0x120, 0x144 };
static float ny_ico_tbl_e[9] = { 164.0f, 187.0f, 178.0f, 168.0f, 148.0f,
                                 221.0f, 227.0f, 129.0f, 112.0f };
static float *EdIconWTbl[6] = { ny_ico_tbl_e, ny_ico_tbl_e, ny_ico_tbl_e,
                                ny_ico_tbl_e, ny_ico_tbl_e, ny_ico_tbl_e };

static int ed_lrframe_appr(void *w) {
    anon_0_181 *ew = w;
    int i;

    switch (ew->step) {
    case 0:
        ew->t = 8.0f;
        i = 0;
        do {
            ew->ict[i] = 0.0f;
            ew->ict[i + 1] = 0.0f;
            ew->ict[i + 2] = 0.0f;
            i += 3;
        } while (i < 9);
        ew->step++;
    case 1:
        ew->t = ew->t - 1.0f;
        if (ew->t > 0.0f) {
            break;
        }
        ew->step++;
    case 2:
        ew->step = 0;
        return 1;
    }
    return 0;
}

static int ed_lrframe_dsap(void *w) {
    anon_0_181 *ew = w;

    switch (ew->step) {
    case 0:
        ew->t = 0.0f;
        ew->step++;
    case 1:
        ew->t = ew->t + 1.0f;
        if (ew->t < 8.0f) {
            break;
        }
        ew->step++;
    case 2:
        edw->lrframe_ow = 0;
        return 1;
    }
    return 0;
}

static int ed_lrframe_exec(void *w) {
    anon_0_181 *ew = w;
    anon_2_181 *work = func_00196EF0();
    float dt;
    int i;

    dt = work->icon_exp ? 1.0f : 12.0f;
    for (i = 0; i < 9; i++) {
        if (work->play_step == 0 && i == edw->cur_icon) {
            ew->ict[i] += dt;
        }
        else {
            ew->ict[i] -= dt;
        }
        if (ew->ict[i] < 0.0f) {
            ew->ict[i] = 0.0f;
        }
        if (ew->ict[i] > 12.0f) {
            ew->ict[i] = 12.0f;
        }
    }
    return 0;
}

static int ed_lrframe_disp(void *w) {
    anon_0_181 *ew = w;
    anon_2_181 *work;
    anon_5_181 sp;
    anon_3_181 info;
    float dx;
    float lx0;
    float rx0;
    float ix0;
    int i;
    float v;
    int alpha;
    float rx;

    work = func_00196EF0();
    dx = 3.0f * ew->t * ew->t;
    lx0 = -320.0f - dx;
    rx0 = 208.0f + dx;
    ix0 = 23.0f + lx0;
    func_00127F60(&info, func_00196E20(6));
    sp.flg = 0;
    sp.flg |= 0x100;
    sp.r0 = 0x80;
    sp.g0 = 0x80;
    sp.b0 = 0x80;
    sp.a0 = 0x80;
    sp.u = 0.0f;
    sp.v = 0.0f;
    sp.w = 112.0f;
    sp.h = 448.0f;
    sp.x0.fd = lx0;
    sp.y0.fd = -224.0f;
    sp.z0 = 0x1000;
    func_00123CF0(&sp);
    sp.u = 112.0f;
    sp.v = 0.0f;
    sp.x0.fd = rx0;
    sp.y0.fd = -224.0f;
    sp.z0 = 0x1000;
    func_00123CF0(&sp);
    func_00127F60(&info, func_00196E20(0x2C));
    {
    float w;
    for (i = 0; i < 9; i++) {
        v = EdIconTbl[i];
        if (i == 3 && (work->play_type == 1 || work->play_type == 2)) {
            v = 144.0f;
        }
        sp.flg = 0;
        sp.flg |= 0x100;
        sp.r0 = 0x80;
        sp.g0 = 0x80;
        sp.b0 = 0x80;
        sp.a0 = 0x80;
        sp.u = 0.0f;
        sp.v = v;
        sp.w = 54.0f;
        sp.h = 36.0f;
        sp.x0.fd = ix0;
        sp.y0.fd = -195.0f + (float)(i * 38);
        sp.z0 = 0x7FFF;
        func_00123CF0(&sp);
        if (ew->ict[i] > 0.0f) {
            alpha = 32.0f + 96.0f * ew->ict[i] / 12.0f;
            w = ew->ict[i] * EdIconWTbl[1][i] / 12.0f;
            if (w < 54.0f || work->icon_exp == 0) {
                w = 54.0f;
            }
            sp.r0 = 0x80;
            sp.g0 = 0x80;
            sp.b0 = 0x80;
            sp.a0 = alpha;
            sp.u = work->icon_exp ? 112.0f : 56.0f;
            sp.v = v;
            sp.w = w;
            sp.h = 36.0f;
            sp.x0.fd = ix0;
            sp.y0.fd = -195.0f + (float)(i * 38);
            sp.z0 = 0x8000;
            func_00123CF0(&sp);
        }
    }
    }
    func_00127F60(&info, func_00196E20(1));
    {
        int posi_y;
        int btm;
        btm = (work->bar_max << 4) - 0x10;
        rx = 42.0f + rx0;
        {
        int y[2] = { 0 };
        anon_4_181 tile;
        int ct;
        int alpha;
        int num;
        int x;
        unsigned char str[5];  dx = 38.0f;

        if (work->test_play_flg == 0 || work->play_step == 8) {
            if (work->zoom_mode == 0) {
                posi_y = (work->cur_seq_pos - 0x10) * 312 / btm - 0xAE;
            }
            else {
                posi_y = ((work->cur_seq_pos - 0x10) - work->scroll_ct / work->zoom_mode / 8) * 312 / btm - 0xAE;
            }
        }
        else {
            posi_y = (work->beat_ct - 0x1000) * 312 / (work->bar_max * 4096 - 0x1000) - 0xAE;
        }
        sp.flg = 0;
        sp.flg |= 0x100;
        sp.x0.fd = rx;
        sp.y0.fd = posi_y - 9;
        sp.z0 = 0x1002;
        sp.u = 24.0f;
        sp.v = 0.0f;
        sp.w = 36.0f;
        sp.h = 12.0f;
        sp.r0 = 0x80;
        sp.g0 = 0x80;
        sp.b0 = 0x80;
        sp.a0 = 0x80;
        func_00123CF0(&sp);
        for (i = 0; i < 2; i++) {
            if (work->area[i].pos != 0) {
                y[i] = (work->area[i].pos - 0x10) * 312 / btm - 0xAE;
                sp.flg = 0;
                sp.flg |= 0x100;
                sp.x0.fd = rx;
                sp.y0.fd = y[i] - 9;
                sp.z0 = 0x1003;
                sp.u = 24.0f;
                sp.v = 0.0f;
                sp.w = 36.0f;
                sp.h = 12.0f;
                sp.r0 = 0x80;
                sp.g0 = 0x80;
                sp.b0 = 0x80;
                sp.a0 = 0x80;
                func_00123CF0(&sp);
                sp.flg = 0;
                sp.flg |= 0x100;
                if (work->area[i].side == 0) {
                    sp.x0.fd = rx - 24.0f + 1.0f;
                    sp.y0.fd = y[i] - 0xB;
                    sp.z0 = 0x1004;
                }
                else {
                    sp.x0.fd = rx + dx - 3.0f;
                    sp.y0.fd = y[i] - 9;
                    sp.z0 = 0x1004;
                }
                sp.u = 0.0f;
                sp.v = 0.0f;
                sp.w = 24.0f;
                sp.h = 12.0f;
                sp.r0 = 0x80;
                sp.g0 = 0x80;
                sp.b0 = 0x80;
                sp.a0 = 0x80;
                func_00123CF0(&sp);
            }
        }
        if (work->area[0].pos != 0 && work->area[1].pos != 0) {
            ct = g_sys_w.s_counter % 0x60;
            if (ct < 0x30) {
                alpha = 0x80 - ct * 2;
            }
            else {
                alpha = (ct - 0x30) * 2 + 0x20;
            }
            tile.flg = 0;
            tile.flg |= 0x100;
            tile.r0 = 0x80;
            tile.g0 = 0x80;
            tile.b0 = 0x10;
            tile.a0 = alpha;
            tile.x0.fd = rx - 1.0f;
            tile.y0.fd = (float)y[0];
            tile.z0 = 0x1001;
            tile.w = 38.0f;
            tile.h = (float)(y[1] - y[0]);
            func_00124140(&tile);
        }
        for (i = 0; i < 2; i++) {
            num = work->note_num[i] % 10000;
            x = i == 0 ? 50.0f + lx0 : 62.0f + rx0;
            if (i == 1 && work->player != 1) {
                func_001BE7E0(str, (unsigned char *)"----", num);
            }
            else {
                func_001BE7E0(str, (unsigned char *)"%04d", num);
            }
            CSXX20Puts(x, 0xB6, str, 0x80, 0x1000, 0, 0x80, func_00196E20(0x33), 0x1400);
        }
        }
    }
    return 1;
}
