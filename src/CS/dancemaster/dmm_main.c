static int step0 = 0;
#include "src/CS/dancemaster/dmm_main.h"
static anon_7_88 *dmm_w = 0;

void dmm_chara(anon_7_88 *work);
void dmm_init(anon_7_88 *work);
void dmm_sys_fade(void);
void func_00169430(void);
void func_001B7C30(void *p, int size);
void func_0017A8A0(int kind);
void func_007F9BA0(anon_7_88 *work);
void func_007FAB10(anon_7_88 *work);
void func_007FC2D0(anon_7_88 *work);
void func_00804EB0(anon_7_88 *work);
void func_00805BA0(anon_7_88 *work);

static int dmm_get_back_step(int step) {
    int ret;
    ret = step;
    switch (step) {
    case 0:
        break;
    case 1:
        ret = 7;
        break;
    case 2:
        ret = 1;
        break;
    case 3:
        ret = 2;
        break;
    case 4:
        ret = 3;
        break;
    case 5:
        ret = 3;
        break;
    case 6:
        ret = 1;
        break;
    }
    return ret;
}

static int dmm_get_next_step(int step) {
    int ret;
    ret = step;
    switch (step) {
    case 0:
        ret = 1;
        break;
    case 1:
        ret = 2;
        break;
    case 2:
        ret = 3;
        break;
    case 3:
        if (g_game_w.oni_nonstop_mode) ret = 5;
        else ret = 4;
        break;
    case 4:
        ret = 6;
        break;
    case 5:
        ret = 6;
        break;
    case 6:
        ret = 3;
        break;
    }
    return ret;
}

static __inline void dmm_set_step_body(anon_7_88 *work, int step) {
    if (step == 10) return;
    if (step == 8) {
        step0 = dmm_get_next_step(step0);
    } else if (step == 9) {
        step0 = dmm_get_back_step(step0);
    } else {
        step0 = step;
    }
    work->step = 0;
    work->step_s = 0;
}

void dmm_set_step(int step) {
    dmm_set_step_body(dmm_w, step);
}

anon_7_88 *dmm_get_work(void) {
    return dmm_w;
}

void DanceMasterFinish(void) {
    func_0017A8A0(0xF101);
    g_game_w.dancemaster_flag = 0;
}

static __inline int DanceMasterStep_body(anon_7_88 *work) {
    switch (step0) {
    case 0:
        dmm_init(work);
        break;
    case 1:
        func_00805BA0(work);
        break;
    case 2:
        dmm_chara(work);
        break;
    case 3:
        func_00804EB0(work);
        break;
    case 4:
        func_007F9BA0(work);
        break;
    case 5:
        func_007FAB10(work);
        break;
    case 6:
        func_007FC2D0(work);
        break;
    case 7:
        return 1;
    }
    work->syscnt++;
    dmm_sys_fade();
    func_00169430();
    return g_game_w.mode_quit_flg != 0;
}

int DanceMasterStep(void) {
    return DanceMasterStep_body(dmm_w);
}

static __inline void dmm_work_reset(anon_7_88 *work) {
    step0 = 0;
    work->step = 0;
    work->step_s = 0;
}

void DanceMasterInit(void) {
    g_game_w.dancemaster_flag = 1;
    func_001B7C30(dmm_w, 0x3D80);
    dmm_work_reset(dmm_w);
}
