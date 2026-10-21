#include "src/CS/dancemaster/dmm_chara.h"

#define DMM_LAST_DATA (g_game_w.last_data_addr)

anon_7_109 *dmm_get_work(void);
void func_00128600(void);
void gsInit3d(void);
void dmm_freeplay_chara_init(unsigned char *addr);
void func_0012CD70(unsigned char *addr);
int dmm_freeplay_chara_load(void);
int dmm_freeplay_step(void);
void dmm_freeplay_chara_finish(int *id_1, int *id_2);
void dmm_set_step(int step);

static inline void dmm_chara_work_init(anon_7_109 *work) {
    anon_7_109 *w = dmm_get_work();
    DMM_LAST_DATA = (unsigned char *)0xFC29D0;
    func_00128600();
    gsInit3d();
    w->chara_work_addr = DMM_LAST_DATA;
    dmm_freeplay_chara_init(w->chara_work_addr);
    func_0012CD70(DMM_LAST_DATA);
}

static inline void dmm_chara_finish(void) {
    anon_7_109 *w = dmm_get_work();
    dmm_freeplay_chara_finish(&w->dancer[0], &w->dancer[1]);
    if (w->dancer[0] == 0x2D && w->dancer[1] == 0x2D) w->is_disp_dancer = 0;
}

void dmm_chara(anon_7_109 *work) {
    int step_type = 10;
    switch (work->step) {
    case 0:
        dmm_chara_work_init(work);
        work->step++;
        break;
    case 1:
        if (dmm_freeplay_chara_load()) {
            work->free_mem_addr = DMM_LAST_DATA;
            work->step++;
        }
        break;
    case 2: {
        int dmm_t = dmm_freeplay_step();
        switch (dmm_t) {
        case 1:
            work->step = step_type; break;
        case 2:
            work->step = 20;
            break; } break;
    }
    case 10:
        dmm_chara_finish();
        work->step++;
        break;
    case 11: work->before_state = 2;
        step_type = 8;
        break;
    case 20:
        work->step++;
        break;
    case 21:
        work->before_state = 2;
        dmm_set_step(9);
        return;
    }
    dmm_set_step(step_type);
}
