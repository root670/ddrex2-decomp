#include "src/CS/lesson/kn_lstep.h"

void kn_lfunc_chk_now_music(void);
void kn_lfunc_foot_op(void);
void kn_lfunc_finger_op(void);
void kn_lfunc_msg_op(void);
void kn_lfunc_chk_timing(void);
void kn_ldisp_lesson_play(void);
void kn_lfunc_set_play_ct(void);
int kn_lfunc_chk_teach_mode(void);
void kn_lfunc_chk_clap(void);
int func_00154DF0(void);
int func_00170A30(int count);
void func_001B7C30(void *p, int size);

int lesson_foot_offset_tbl[9][2] = {
    {-131072, -131072},
    {0, -131072},
    {131072, -131072},
    {-131072, 0},
    {0, 0},
    {131072, 0},
    {-131072, 131072},
    {0, 131072},
    {131072, 131072},
};

void kn_lstep_main_init(void) {
    kn_lesson_main_work.fade_col = 0xFF;
    kn_lesson_main_work.speaker_ct[0] = 8;
    kn_lesson_main_work.speaker_ct[1] = kn_lesson_main_work.speaker_ct[2] = 0;
    kn_lesson_main_work.iron_deg[0] = 0x1000;
    kn_lesson_main_work.iron_deg[1] = 0;
    kn_lesson_main_work.lesson_col[0] = kn_lesson_main_work.lesson_col[1] =
        kn_lesson_main_work.lesson_col[2] = 0x404040;
    kn_lesson_main_work.screen_deg = 0;
    kn_lesson_main_work.mode_chng_ct = 12;
    kn_lesson_main_work.sect_menu_ct = 0;
    kn_lesson_main_work.lv_menu_ct[1] = kn_lesson_main_work.lv_menu_ct[2] = 0;
    kn_lesson_main_work.lv_menu_ct[0] = 0;
}

void kn_lstep_lesson_play_init(void) {
    anon_0_196 *work;
    int i;

    work = &kn_lesson_main_work;
    kn_lesson_main_work.cur_mc = 0;
    kn_lesson_main_work.music_step = 0;
    kn_lesson_main_work.music_flg = 0;
    kn_lesson_main_work.music_wait_ct = 0;
    kn_lesson_main_work.start_mc = pLesPlay->start_music_count;
    kn_lesson_main_work.finish_mc = func_00170A30(pLesPlay->end_beat_count);
    kn_lesson_main_work.next_foot = 0;
    kn_lesson_main_work.next_finger = 0;
    kn_lesson_main_work.next_msg = 0;
    kn_lesson_main_work.end_msg_ct = 0;
    kn_lesson_main_work.old_bar[0] = kn_lesson_main_work.old_bar[1] =
        kn_lesson_main_work.old_bar[2] = kn_lesson_main_work.old_bar[3] = 0;
    kn_lesson_main_work.cur_clap_pos = 1;
    kn_lesson_main_work.rhythm_flg = 1;
    kn_lesson_main_work.end_bc = 0;
    kn_lesson_main_work.miss_num = 0;
    kn_lesson_main_work.emi_anime_flg = 0;
    kn_lesson_main_work.is_stream = 0;
    kn_lesson_main_work.cur_note = 0;
    kn_lesson_main_work.teach_ct = 0;
    kn_lesson_main_work.clear_flg = 0;
    kn_lesson_main_work.clear_wait_ct = 0;
    kn_lesson_main_work.tempo = 0;
    kn_lesson_main_work.result = 0;
    for (i = 0; i < 6; i++) {
        work->dead_ct[i] = 0;
    }
    func_001B7C30(&kn_foot_w[0].offset, 0x30);
    func_001B7C30(&kn_foot_w[1].offset, 0x30);
    kn_foot_w[0].offset.vx = kn_foot_w[0].next_ofs.vx =
        (float)lesson_foot_offset_tbl[3][0];
    kn_foot_w[1].offset.vx = kn_foot_w[1].next_ofs.vx =
        (float)lesson_foot_offset_tbl[5][0];
    kn_foot_w[0].pos = kn_foot_w[1].pos = 0;
    kn_foot_w[0].ang = kn_foot_w[1].ang = 0;
    kn_foot_w[0].move_flg = kn_foot_w[1].move_flg = 0;
    kn_msg_w.disp_flg = 0;
    kn_fin_w.disp_flg = 0;
    kn_touch_w[0].move_flg = kn_touch_w[1].move_flg = 0;
}

int kn_lstep_lesson_play(void) {
    int ret;

    kn_lfunc_chk_now_music();
    ret = func_00154DF0();
    kn_lfunc_foot_op();
    kn_lfunc_finger_op();
    kn_lfunc_msg_op();
    kn_lfunc_chk_timing();
    kn_ldisp_lesson_play();
    kn_lfunc_set_play_ct();
    kn_lfunc_chk_teach_mode();
    kn_lfunc_chk_clap();
    return ret;
}
