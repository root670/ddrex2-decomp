#include "src/CS/dancemaster/dmm_mc.h"

#define DMM_LAST_DATA (g_game_w.last_data_addr)

void func_001777C0(int a, int b);
void func_00175420(struct _tag_cDDR8SaveData *save, int size);
void func_00175920(void);
int func_00175590(void);
void func_00177780(int a, int b);
int func_001759A0(void);
void func_00177BD0(struct _tag_cDDR8SaveData *save);
int func_001759B0(void);
void func_00177340(int a, int b, int c, int d, int e, int f, int g);
void func_001B7C30(void *p, int size);
void func_001B7B48(void *dst, void *src, int size);
void func_001759F0(unsigned char *addr);
void func_00175560(unsigned char *addr);
int func_00175440(void);
anon_1_133 *dmm_get_subject_w(int sbj_id);
int dmm_get_subject_area(int sbj_id);
int dmm_is_default_connect_appear_ok(anon_1_133 *sbjw, int connect_id);
anon_7_133 *dmm_get_work(void);

int dmm_save(anon_7_133 *work) {
    anon_12_133 *mc_w;
    int msg_id;
    mc_w = &work->mc_w;
    switch (mc_w->step) {
    case 0:
        func_001777C0(2, 1);
        func_00175420(&SaveData, 0x1FF50);
        func_00175920();
        mc_w->swap_fg = 0;
        mc_w->step++;
        break;
    case 1:
        mc_w->disp_win = 1;
        if (func_00175590()) mc_w->step++;
        break;
    case 2:
        func_00177780(2, 1);
        if (func_001759A0() && mc_w->swap_fg == 0) {
            func_00177BD0(&SaveData);
            mc_w->swap_fg = 1;
            RequestAutoSave = 0;
            mc_w->step = 0;
        }
        return 1;
    }
    if (mc_w->disp_win == 1) {
        msg_id = func_001759B0();
        if (msg_id != -1) func_00177340(2, 1, 0, 0x5A, msg_id, 0x80, 0xC000);
        mc_w->disp_win = 0;
    }
    return 0;
}

void dmm_copy_savedata(void) {
    func_001B7B48(&SaveData.dmm, &dmm_get_work()->swap_save_data, 0x1300);
}

void dmm_set_default_savedata(void) {
    anon_3de85bd4740a *w;
    int i;
    int j;
    anon_1_133 *sbjw;
    w = &SaveData.dmm;
    func_001B7C30(w, 0x1300);
    w->is_savedata = 0;
    for (i = 0; i < 0x17; i++) w->evboot[i] = 0;
    w->disp_type = 0;
    w->cur_cursor = 1;
    w->max_area = 1;
    for (i = 0; i < 0xC8; i++) {
        if (dmm_get_subject_area(i) == 1) {
            SaveData.dmm.subject[i].state = 1;
            SaveData.dmm.subject[i].cone_state[0] = 0;
            SaveData.dmm.subject[i].cone_state[1] = 0;
            SaveData.dmm.subject[i].cone_state[2] = 0;
            SaveData.dmm.subject[i].cone_state[3] = 0;
            SaveData.dmm.subject[i].cone_state[4] = 0;
            SaveData.dmm.subject[i].cone_state[5] = 0;
            SaveData.dmm.subject[i].cone_state[6] = 0;
            SaveData.dmm.subject[i].cone_state[7] = 0;
        } else {
            SaveData.dmm.subject[i].state = 0;
            SaveData.dmm.subject[i].cone_state[0] = 0;
            SaveData.dmm.subject[i].cone_state[1] = 0;
            SaveData.dmm.subject[i].cone_state[2] = 0;
            SaveData.dmm.subject[i].cone_state[3] = 0;
            SaveData.dmm.subject[i].cone_state[4] = 0;
            SaveData.dmm.subject[i].cone_state[5] = 0;
            SaveData.dmm.subject[i].cone_state[6] = 0;
            SaveData.dmm.subject[i].cone_state[7] = 0;
        }
        if (i == 0) {
            SaveData.dmm.subject[i].state = 0;
            SaveData.dmm.subject[i].cone_state[0] = 0;
            SaveData.dmm.subject[i].cone_state[1] = 0;
            SaveData.dmm.subject[i].cone_state[2] = 0;
            SaveData.dmm.subject[i].cone_state[3] = 0;
            SaveData.dmm.subject[i].cone_state[4] = 0;
            SaveData.dmm.subject[i].cone_state[5] = 0;
            SaveData.dmm.subject[i].cone_state[6] = 0;
            SaveData.dmm.subject[i].cone_state[7] = 0;
        } else if (i == 1) {
            SaveData.dmm.subject[i].state = 4;
            SaveData.dmm.subject[i].cone_state[0] = 2;
            SaveData.dmm.subject[i].cone_state[1] = 2;
            SaveData.dmm.subject[i].cone_state[2] = 2;
            SaveData.dmm.subject[i].cone_state[3] = 2;
            SaveData.dmm.subject[i].cone_state[4] = 2;
            SaveData.dmm.subject[i].cone_state[5] = 2;
            SaveData.dmm.subject[i].cone_state[6] = 2;
            SaveData.dmm.subject[i].cone_state[7] = 2;
        }
        sbjw = dmm_get_subject_w(1);
        for (j = 0; j < 8; j++) {
            if (dmm_is_default_connect_appear_ok(sbjw, j) && sbjw->connect[j].id == i) {
                SaveData.dmm.subject[i].state = 4;
                SaveData.dmm.subject[i].cone_state[0] = 0;
                SaveData.dmm.subject[i].cone_state[1] = 0;
                SaveData.dmm.subject[i].cone_state[2] = 0;
                SaveData.dmm.subject[i].cone_state[3] = 0;
                SaveData.dmm.subject[i].cone_state[4] = 0;
                SaveData.dmm.subject[i].cone_state[5] = 0;
                SaveData.dmm.subject[i].cone_state[6] = 0;
                SaveData.dmm.subject[i].cone_state[7] = 0;
            }
        }
        if (i == 0) w->route[i] = 1;
        else w->route[i] = -1;
    }
}

int dmm_is_savedata(void) {
    return SaveData.dmm.is_savedata;
}

int dmm_icon(void) {
    anon_12_133 *mc_w;
    int rtv;
    mc_w = &dmm_get_work()->mc_w;
    rtv = 0;
    switch (mc_w->step) {
    case 0:
        func_001759F0(DMM_LAST_DATA);
        func_00175560(DMM_LAST_DATA);
        mc_w->step++;
        break;
    case 1:
        if (func_00175440()) mc_w->step++;
        break;
    case 2:
        mc_w->step = 0;
        rtv = 1;
        break;
    }
    return rtv;
}
