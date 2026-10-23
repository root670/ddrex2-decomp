#include "src/CS/bk_disp/bk_disp.h"

static int ti_cnt = 0;

struct tex_bind *func_0012D070(int id);
void func_00127F60(anon_1_60 *info, short id);
int func_00122440(int a, int b);
int func_00125180(int a, int b, int c);
anon_5_60 *func_00121E70(int a);
void func_00121E40(int a, int b);
int func_0011E210(int a);
void func_00121270(int color, void *buf, int status, float x, float y);
void func_0017A0A0(void);
int bk_is_eyetoy(void);
int bk_is_err(void);
int bk_is_start(void);
int bk_is_prarare(void);
void bk_mpeg_init(struct music_info *mip, int flg);
void bk_mpeg_manager(void);
void bk_mpeg_term(void);
void bk_mpeg_play(void);
void bk_mpeg_play_start(void);
void bk_mpeg_disp(void);
int *bk_cur_mv_tbl(void);
int SdFFTInit(unsigned int addr);
void SdSetFFTStart(void);
int SetFFTDispWork(unsigned int addr);
void SetBeginnerFlg1p(int flg);
void SetBeginnerFlg2p(int flg);
int EyeSystemInit(void);
int EyeRegGetSystemStatus(void);
void EyeRefSetOneWindow(short x, short y, short w, short h);
void EyeRefSetPositionZ(int z);

extern unsigned int D_006B2F58[];
extern int D_006B47F0[];

void bk_disp_read_set(int flg) {
    bk_mpeg_init(g_game_w.mip, flg);
}

int bk_disp_read_wait(void) {
    if (bk_is_eyetoy()) {
        return 1;
    }
    bk_mpeg_manager();
    return bk_is_prarare();
}

void bk_play_disp_init(void) {
    int size;

    if (bk_is_eyetoy()) {
        return;
    }
    if (SaveData.Option.BgEffect == 0 && g_game_w.mip->verm_num == 0x7012) {
        size = SdFFTInit(D_006B2F58[0]);
        D_006B2F58[0] += size;
        SdSetFFTStart();
        size = SetFFTDispWork(D_006B2F58[0]);
        D_006B47F0[0] = 0;
        D_006B2F58[0] += size;
    }
    SetBeginnerFlg1p(0);
    SetBeginnerFlg2p(0);
    ti_cnt = 0;
}

void bk_play_disp_step(void) {
    struct play_w *play_w;
    int bright;
    int b_ct;

    play_w = &g_game_w.player[0].play_work;
    if (g_game_w.mip != 0 && SaveData.Option.BgEffect == 0
        && g_game_w.mip->verm_num == 0x7012 && !bk_is_eyetoy()) {
        func_0017A0A0();
    }
    if ((!bk_is_eyetoy() && SaveData.Option.BgEffect == 1) || g_game_w.state == 5
        || (bk_is_err() && !bk_is_eyetoy() && SaveData.Option.BgEffect != 3)) {
        if (!bk_is_eyetoy()) {
            bright = play_w->music_counter;
            if (bright < 0) {
                bright = 0;
            }
            if (0x80 < bright) {
                bright = 0x80;
            }
            bk_disp_title(bright, -1);
        }
        return;
    }
    if (bk_is_eyetoy()) {
        if ((func_0011E210(0) & 0x20) ? 1 : 0) {
            EyeSystemInit();
        }
        func_00121270(0x30, (unsigned char *)"eye stat %d", EyeRegGetSystemStatus(), -300.0f, -200.0f);
        if (EyeRegGetSystemStatus() == 4) {
            EyeRefSetOneWindow(0, 0, 0, 0);
            EyeRefSetPositionZ(0x140);
            if (g_game_w.state != 0x23) {
                EYETOYW->di_flg |= 0x80;
            }
            EYETOYW->code = 1;
        }
        bright = play_w->music_counter;
        if (bright < 0) {
            bright = 0;
        }
        if (0x80 < bright) {
            bright = 0x80;
        }
        bk_disp_title(bright, -1);
        return;
    }
    b_ct = play_w->beat_counter;
    if (!bk_is_start() && b_ct >= bk_cur_mv_tbl()[0]) {
        bk_mpeg_play_start();
    }
    if (bk_is_start()) {
        bk_mpeg_play();
    }
    bk_mpeg_manager();
    if (b_ct >= bk_cur_mv_tbl()[2] || b_ct < bk_cur_mv_tbl()[1]) {
        bright = play_w->music_counter;
        if (bright < 0) {
            bright = 0;
        }
        if (0x80 < bright) {
            bright = 0x80;
        }
        bk_disp_title(bright, 1);
    } else {
        if (0x20 <= ti_cnt) {
            bk_mpeg_disp();
        } else {
            ti_cnt++;
            bk_mpeg_disp();
            bright = 0x80 - ti_cnt * 0x80 / 0x20;
            bk_disp_title(bright, 1);
        }
    }
}

void bk_play_disp_finish(void) {
    if (!bk_is_eyetoy()) {
        bk_mpeg_term();
    }
}

static void bk_disp_title(int bright, int blend) {
    struct tex_bind *bp;
    anon_1_60 info;
    float rw;
    float rh;
    int i;
    int rate;
    int alpha;
    anon_5_60 *pkt;

    bp = func_0012D070(0xAE);
    rate = SaveData.Option.BgBright * 5 + 0x19;
    if (blend < 0) {
        alpha = 0x80;
        if (g_game_w.state != 0x23) {
            bright = bright * rate / 100;
        }
    } else {
        alpha = bright;
        bright = rate * 0x80 / 100;
    }
    func_00127F60(&info, bp->id);
    for (i = 0, rw = 1.0f; i < info.tw; i++) {
        rw *= 2.0f;
    }
    for (i = 0, rh = 1.0f; i < info.th; i++) {
        rh *= 2.0f;
    }
    func_00122440(0x101, 4);
    func_00125180(0x20, 0x14, 0);
    func_00125180(0x44, 0x42, 0);
    pkt = func_00121E70(0);
    pkt[0].ul64[0] = 0x1000000000008001ULL;
    pkt[0].ul64[1] = 1;
    pkt[1].i32[2] = bright;
    pkt[1].i32[1] = bright;
    pkt[1].i32[0] = bright;
    pkt[1].i32[3] = alpha;
    pkt[2].ul64[0] = 0x202B400000008002ULL;
    pkt[2].ul64[1] = 0x52;
    pkt[3].i32[0] = 0x3C23D70A;
    pkt[3].i32[1] = 0;
    pkt[3].i32[2] = 0x3F800000;
    pkt[3].i32[3] = 0;
    pkt[4].i32[0] = (0x800 - info.w) << 4;
    pkt[4].i32[1] = (0x800 - info.h) << 4;
    pkt[4].i32[2] = 0x101;
    pkt[4].i32[3] = 0;
    pkt[5].f32[0] = (float)info.w / rw;
    pkt[5].f32[1] = (float)info.h / rh;
    pkt[5].f32[2] = 1.0f;
    pkt[5].f32[3] = 0;
    pkt[6].i32[0] = (0x800 + info.w) << 4;
    pkt[6].i32[1] = (0x800 + info.h) << 4;
    pkt[6].i32[2] = 0x101;
    pkt[6].i32[3] = 0;
    func_00121E40(0, 7);
    func_00122440(0x101, 2);
    func_00125180(0, 0x14, 0);
}
