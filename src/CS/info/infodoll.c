#include "src/CS/info/infodoll.h"

#define D_01015380 ((void *)0x01015380)

void func_001B7C30(void *p, int size);
void func_001253C0(anon_1_184 *rect, int mode);
void func_001252F0(int mode);
void ps2dancerResetEntry(void);
void ps2dancerEntry(int pid, int chara);
void ps2dancerLoadInit(void *readtmpaddr);
int ps2dancerLoadStep(void);
void ps2dancerSetup(void);
void ps2dancerCameraInit(float cx, float cy, float scale);
void ps2dancerSetPlayCounter(int pid, int cur_p_counter);
void ps2dancerSetToon(int sw);
void ps2dancerSetFloor(int sw);
void ps2dancerSetCameraPos(float x, float y);
void ps2dancerDispStep(void);
void *ps2dancerInit(void *workaddr, int playmode);

static anon_1_184 crect = {-293, -138, 585, 306};
static anon_0_184 idd_work;
static anon_0_184 *wk = &idd_work;

void req_info_doll_chara(int chara) {
    if (chara >= 0x2D) {
        chara = -1;
    }
    wk->new_chr = chara;
}

void req_info_doll_in(int sw) {
    wk->req_in = sw;
}

int is_info_doll_loading(void) {
    return wk->loading;
}

void View_InfoDollDisp(int disp) {
    switch (wk->step) {
    case 0:
        if (wk->new_chr < 0) {
            break;
        }
        wk->cur_chr = wk->new_chr;
        ps2dancerResetEntry();
        ps2dancerEntry(0, wk->cur_chr);
        ps2dancerLoadInit(wk->loadaddr);
        wk->loading = 1;
        wk->step++;
        break;
    case 1:
        if (ps2dancerLoadStep()) {
            ps2dancerSetup();
            wk->loading = 0;
            if (wk->cur_chr != wk->new_chr) {
                wk->step = 0;
            } else {
                wk->cx = -400.0F;
                wk->cy = 48.0F;
                ps2dancerCameraInit(wk->cx, wk->cy, 0.5F);
                wk->p_counter = 0;
                wk->step++;
            }
        }
        break;
    case 2:
        wk->p_counter += 0x20;
        if (!(wk->p_counter & 0xFFFFF)) {
            ps2dancerSetup();
        }
        if (wk->req_in) {
            wk->cx = wk->cx + -wk->cx * 0.02F;
        } else {
            wk->cx = wk->cx + (-400.0F - wk->cx) * 0.1F;
        }
        if (disp && !(wk->cx <= -399.0F)) {
            ps2dancerSetPlayCounter(0, wk->p_counter);
            ps2dancerSetToon(1);
            ps2dancerSetCameraPos(wk->cx, wk->cy);
            ps2dancerSetFloor(0);
            func_001253C0(&crect, 0);
            ps2dancerDispStep();
            func_001252F0(0);
        }
        if (wk->cur_chr != wk->new_chr) {
            wk->step = 0;
        }
        break;
    }
}

void Init_InfoDollDisp(void) {
    func_001B7C30(wk, 0x18);
    wk->loadaddr = ps2dancerInit(D_01015380, 3);
    wk->new_chr = -1;
    wk->cur_chr = -1;
}
