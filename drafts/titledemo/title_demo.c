#include "src/AM/s573/demo/title_demo.h"

void func_001B7C30(void *p, int size);
void func_001267B0(int a, int b);
void sceMpegInit(void);
void sceMpegSetBuffType(anon_4_41 *mpeg, int type);
void sceMpegCreate(anon_4_41 *mpeg, unsigned char *addr, int size);
void sceMpegReset(anon_4_41 *mpeg);
void sceMpegAddBs(anon_4_41 *mpeg, unsigned char *buf, int size);
int sceMpegGetPicture(anon_4_41 *mpeg, anon_2_41 *csc, int a);
int func_00109508(anon_4_41 *mpeg);
int func_0011E090(unsigned char *src, unsigned char *dst);
int func_0011DE80(void);
void func_0017A090(unsigned char *p);
void func_00179C00(int a);
void func_00179C30(int a, int b, int c, float d);
void func_00124140(anon_5_41 *tl);
void func_001234E0(anon_10_41 *ft4);
void func_00122440(unsigned int pri, int a);
void func_00125180(int a, int b, int c);
void func_00127110(anon_6_41 *tex, int a);
void func_00127070(int a);
void func_001BBBF8(unsigned int a, unsigned char *buf, int size);
int sceGsSyncPath(int a, int b);

void title_movie_init(void) {
    int size;

    func_001B7C30(tmw, 0x30);
    sceMpegInit();
    g_game_w.last_data_addr = (unsigned char *)(((int)g_game_w.last_data_addr + 0x7F) & 0xFFFFFF80);
    size = ti_movie_work_set((unsigned int *)g_game_w.last_data_addr);
    g_game_w.last_data_addr = g_game_w.last_data_addr + size;
    sceMpegSetBuffType(&mpeg, 0);
    func_001267B0(0x9A0, 0);
    ti_movie_SetDecTag();
}

void title_movie_play_start(void) {
    tmw->play_flg = 1;
}

int title_movie_play_ok(void) {
    return tmw->cur_read;
}

int title_movie_manage(void) {
    if (tmw->step) {
        tmw->disp_flg = 1;
        tmw->ct = tmw->ct + 1.0f;
        if (tmw->ct >= 90.0f) {
            tmw->ct = 90.0f;
            return 1;
        }
        return 0;
    }
    switch (tmw->read_step) {
    case 0:
        if (func_0011E090((unsigned char *)ex2_movie_vag, tmw->vag_addr)) tmw->read_step++;
        break;
    case 1:
        if (func_0011DE80()) {
            func_0017A090(tmw->vag_addr);
            tmw->read_step++;
        }
    case 2:
        if (func_0011E090(ti_mv_list[tmw->cur_read], tmw->buf[tmw->cur_read])) tmw->read_step++;
        break;
    case 3:
        if (func_0011DE80()) {
            tmw->cur_read++;
            if (tmw->cur_read == 6) {
                tmw->read_step++;
                tmw->cur_read++;
            } else
                tmw->read_step = 2;
        }
        break;
    case 4:
        break;
    default:
        break;
    }
    ti_movie_play();
    if (tmw->cur_play >= 6) {
        func_00179C00(0x5A);
        tmw->step = 1;
        tmw->ct = 0.0f;
    }
    return 0;
}

void title_movie_disp(unsigned int pri) {
    anon_10_41 ft4;
    anon_6_41 tex;
    anon_5_41 tl;
    float t;

    if (tmw->disp_flg == 0) return;
    if (tmw->step) {
        tl.flg = 0;
        tl.flg |= 0x100;
        tl.b0 = tl.g0 = tl.r0 = 0xFF;
        tl.a0 = 0x80;
        tl.x0.fd = -320.0f;
        tl.y0.fd = -224.0f;
        tl.z0 = 0xF000u;
        tl.w = 640.0f;
        tl.h = 448.0f;
        func_00124140(&tl);
        t = 90.0f - tmw->ct;
        if (t <= 30.0f) {
            tl.b0 = tl.g0 = tl.r0 = 0;
            t = 128.0f - 128.0f * t / 30.0f;
            tl.a0 = t;
            func_00124140(&tl);
        }
        return;
    }
    tex.psm = 0;
    tex.cbp = 0;
    tex.cpsm = 0;
    tex.width = 448;
    tex.height = 336;
    tex.colors = 0;
    func_00122440(pri, 2);
    func_00125180(0x20, 0x14, 0);
    *(volatile unsigned int *)0x1000A030 = (unsigned int)tmw->decTags;
    *(volatile unsigned int *)0x1000A020 = 0;
    *(volatile unsigned int *)0x1000A000 = 0x105;
    sceGsSyncPath(0, 0);
    tex.tbp = 0x2600;
    func_00127110(&tex, 0xFD);
    func_00127070(0xFD);
    ft4.s0 = 0.001953125f;
    ft4.t0 = 0.001953125f;
    ft4.q0 = 1.0f;
    ft4.s1 = 0.875f;
    ft4.t1 = 0.001953125f;
    ft4.q1 = 1.0f;
    ft4.s2 = 0.001953125f;
    ft4.t2 = 0.65625f;
    ft4.q2 = 1.0f;
    ft4.s3 = 0.875f;
    ft4.t3 = 0.65625f;
    ft4.q3 = 1.0f;
    ft4.b0 = ft4.g0 = ft4.r0 = 0x80;
    ft4.a0 = 0x80;
    ft4.x0.fd = -320.0f;
    ft4.y0.fd = -224.0f;
    ft4.x1.fd = 320.0f;
    ft4.y1.fd = -224.0f;
    ft4.x2.fd = -320.0f;
    ft4.y2.fd = 224.0f;
    ft4.x3.fd = 320.0f;
    ft4.y3.fd = 224.0f;
    ft4.flg = 0;
    ft4.z0 = pri;
    ft4.z1 = pri;
    ft4.z2 = pri;
    ft4.z3 = pri;
    func_001234E0(&ft4);
    func_00122440(pri, 2);
    func_00125180(0, 0x14, 0);
}

static void ti_movie_play(void) {
    unsigned char buf[14592];
    int val;
    int i_ct;

    tmw->disp_flg = 0;
    if (tmw->play_flg == 0) return;
    if (tmw->cur_play + 1 > tmw->cur_read) return;
    if (tmw->ini_flg == 0) {
        tmw->ct = 0.0f;
        sceMpegReset(&mpeg);
        tmw->ini_flg = 1;
        sceMpegAddBs(&mpeg, tmw->buf[tmw->cur_play], 0x100000);
    }
    val = (int)tmw->ct;
    tmw->disp_flg = 1;
    i_ct = val % 2;
    if (i_ct == 0) {
        func_001BBBF8((unsigned int)buf, (unsigned char *)0x70000000, 0x3900);
        if (sceMpegGetPicture(&mpeg, tmw->cscBuff, 0x24C) < 0) tmw->disp_flg = 0;
        func_001BBBF8(0x70000000, buf, 0x3900);
        if (tmw->vag_flg == 0) {
            tmw->vag_flg = 1;
            func_00179C30(0, 0, 0, 1.0f);
        }
    }
    if (func_00109508(&mpeg)) {
        tmw->ini_flg = 0;
        tmw->cur_play++;
    }
    tmw->ct = tmw->ct + 1.0f;
}

static int ti_movie_work_set(unsigned int *addr) {
    unsigned char *tmp_addr;

    tmp_addr = (unsigned char *)addr;
    tmw->vag_addr = (unsigned char *)addr;
    tmw->buf[0] = (unsigned char *)addr + 0x100000;
    tmw->buf[1] = (unsigned char *)addr + 0x200000;
    tmw->buf[2] = (unsigned char *)addr + 0x300000;
    tmw->buf[3] = (unsigned char *)addr + 0x400000;
    tmw->buf[4] = (unsigned char *)addr + 0x500000;
    tmw->buf[5] = (unsigned char *)addr + 0x600000;
    sceMpegCreate(&mpeg, (unsigned char *)addr + 0x700000, 0xA7E00);
    tmw->decTags = (anon_1_41 *)((unsigned char *)addr + 0x7A7E00);
    tmw->cscBuff = (anon_2_41 *)((unsigned char *)addr + 0x7B5AC0);
    return (int)((unsigned char *)addr + 0x848AC0) - (int)tmp_addr;
}

#pragma opt_propagation off
static void ti_movie_SetDecTag(void) {
    anon_1_41 *list;
    unsigned char *buff;
    anon_1_41 *tag;
    int i;
    int j;
    int j4;
    int flag;

    tag = tmw->decTags;
    buff = (unsigned char *)tmw->cscBuff;
    list = 0;
    tag[0].ul128 = 0;
    tag[0].ui32[0] = 0x10000003;
    tag[1].ul128 = 0;
    tag[1].ul64[0] = 0x1000000000000002UL;
    tag[1].ul64[1] = 0xE;
    tag += 2;
    tag[0].ul128 = 0;
    tag[0].ul64[0] = 0x7260000000000UL;
    tag[0].ul64[1] = 0x50;
    tag[1].ul128 = 0;
    tag[1].ul64[0] = 0x1000000010UL;
    tag[1].ul64[1] = 0x52;
    tag += 2;
    i = 0;
    do {
        j = 0;
        j4 = 0;
        do {
            flag = (j == 0x14) && (i == 0x1B);
            tag[0].ul128 = 0;
            tag[0].ui32[0] = 0x10000004;
            tag[1].ul128 = 0;
            tag[1].ul64[0] = 0x1000000000000002UL;
            tag[1].ul64[1] = 0xE;
            tag += 2;
            tag[0].ul128 = 0;
            tag[0].ul64[0] = ((unsigned long)(unsigned int)list << 32) | ((unsigned long)(unsigned int)j4 << 48);
            tag[0].ul64[1] = 0x51;
            tag[1].ul128 = 0;
            tag[1].ul64[0] = 0;
            tag[1].ul64[1] = 0x53;
            tag += 2;
            tag[0].ul128 = 0;
            tag[0].ul64[0] = ((long)flag << 15) | 0x0800000000000040UL;
            tag[1].ul128 = 0;
            tag[1].ui32[0] = (flag ? 0 : 0x30000000) | 0x40;
            tag[1].ui32[1] = (unsigned int)buff;
            tag += 2;
            j++;
            j4 += 0x10;
            buff += 0x400;
        } while (j < 0x15);
        i++;
        list = (anon_1_41 *)((int)list + 0x10);
    } while (i < 0x1C);
}
