static int anime_id_tbl[11] = {0};
static int hold_release = 0;
static int pre_hold_flag = 0;

#include "src/AM/s573/play/p_anime.h"

void marker_anime_reset(int pid);
void marker_anime_set(int pid, int id);
void marker_anime_set_ct(int pid, int ct);
void freeze_eff_set(int pid, int id);
void freeze_eff_off(void);
void freeze_eff_on(void);
void back_anime_set_anime(int id, int anime_id, int anime_ct);

void play_anime_init(void) {
    struct play_anime_db *db; paw_p = &play_anime_w;
    paw_p->mode = 0;

    db = &paw_p->db[0];
    db->anime_id = 0;
    db->sub_id = 0;
    db->note_id = 0;
    db->pre_counter = 0;

    db->frz_end_cnt = 0;
    db->frz_step = 0;
    db->bak_anime_flag = 0; db = &paw_p->db[1]; db->anime_id = 0; db->sub_id = 0; db->note_id = 0; db->pre_counter = 0; db->frz_end_cnt = 0; db->frz_step = 0; db->bak_anime_flag = 0;
}

void play_anime_set_inst_mode(void) {
    paw_p->mode = 1;
}

void play_anime_step_inst(void) {
    int pid; struct play_anime_db *db; struct play_w *play_w; int counter; struct sequence *note; int ct; int pre_ct; int end; int hold_flag; int n; int anime_id; int sub_id; int nct;
    int inp; int step_id; struct note_status *note_status; int id; int anime_ct;
    for (pid = 0; pid < 2; pid++) {
        db = &paw_p->db[pid];
        play_w = &g_game_w.player[pid].play_work;
        counter = play_w->beat_counter + 0x400;
        ct = counter >> 10;
        pre_ct = db->pre_counter >> 10;
        end = 0; n = g_game_w.player[pid].mode.style;
        if (n == 7 || n == 0) continue;
        n = db->note_id;
        note = &g_game_w.player[pid].sequence_buff[n];
        while (1) {
            if (note->kind == -2) {
                end = 1;
                break;
            }
            if (note->kind >= 0) {
                if ((note->beat_count >> 10) >= ct) break;
            } n++; note++; }
        db->note_id = n;
        if (play_w->beat_counter < 0x3000) {
            hold_flag = 0;
            hold_release = 0;
            pre_hold_flag = 0; } else if (play_w->beat_counter < 0x4000) { hold_flag = 1;
        } else if (play_w->beat_counter < 0x4C00) { hold_flag = 0;
        } else if (play_w->beat_counter < 0x5C00) { hold_flag = 1;
        } else if (play_w->beat_counter < 0x6800) { hold_flag = 0;
        } else if (play_w->beat_counter < 0x7000) { hold_flag = 1;
        } else {
            hold_flag = 0;
        }
        if (pre_hold_flag != hold_flag && hold_flag == 0) {
            hold_release = 1;
        }
        pre_hold_flag = hold_flag;
        anime_id = 0;
        sub_id = 0;
        if (hold_flag || hold_release) {
            anime_id = db->anime_id;
            sub_id = db->sub_id;
        }
        if (ct != pre_ct) {
            nct = note->beat_count >> 10;
            if (hold_release == 1) {
                hold_release = 2;
            } else if (hold_release == 2) {
                hold_release = 0;
                anime_id = 0;
                sub_id = 0;
            }
            marker_anime_reset(pid);
            if (nct == ct && end == 0 && hold_flag == 0 && hold_release == 0) {
                step_id = 0;
                note_status = &g_game_w.note_status_table[note->kind];
                for (inp = 7; inp >= 0; inp--) {
                    if (note_status->state[inp] == 1 || note_status->state[inp] == 4) {
                        step_id += 1 << inp;
                    } }
                if (0 < step_id && step_id < 11) {
                    anime_id = anime_id_tbl[step_id];
                    if (db->anime_id != anime_id || db->sub_id == 1) {
                        marker_anime_set(pid, step_id);
                        freeze_eff_set(pid, step_id);
                    }
                }
            } else {
                if (db->anime_id != 0 && db->sub_id != 1) {
                    anime_id = db->anime_id;
                    sub_id = 1;
                }
            }
            db->anime_id = anime_id;
            db->sub_id = sub_id;
        }
        db->pre_counter = counter; freeze_eff_off();
        id = 0;
        anime_ct = counter % 0x400; anime_ct = (anime_ct << 2) & 0xFFF;
        if (db->anime_id != 0) {
            id = db->anime_id + db->sub_id;
            if (db->sub_id == 1) {
                if (hold_flag) { if (hold_release == 0) {
                    anime_ct = 0; freeze_eff_on();
                } }
            }
        }
        back_anime_set_anime(pid, id, anime_ct);
        marker_anime_set_ct(pid, anime_ct);
    }
}

void play_anime_step(void) {
    int pid;
    int pid_total = 0;
    struct play_anime_db *db; struct play_w *play_w; int counter; struct sequence *note; int ct; int pre_ct; int end; int n;
    int anime_id; int sub_id; int nct; int inp; int step_id;
    struct note_status *note_status; int freeze_len; int id; int anime_ct; for (pid = 0; pid < 2; pid++) {
        db = &paw_p->db[pid];
        play_w = &g_game_w.player[pid].play_work;
        counter = play_w->beat_counter + 0x400;
        ct = counter >> 10;
        pre_ct = db->pre_counter >> 10;
        end = 0; n = g_game_w.player[pid].mode.style;
        if (n == 7 || n == 0) continue;
        if ((g_game_w.state == 2 || g_game_w.state == 5 || g_game_w.state == 4)
                && g_game_w.player[pid].mode.seq_kind != 7) continue;
        if (g_game_w.player[pid].mode.edseq_id != -1) continue;
        if (paw_p->mode == 1) {
            if (pid_total) continue;
            pid_total++;
        }

        n = db->note_id;
        note = &g_game_w.player[pid].sequence_buff[n];
        while (1) {
            if (note->kind == -2) {
                end = 1;
                break;
            }
            if (note->kind >= 0) {
                if ((note->beat_count >> 10) >= ct) break; }
            n++; note++;
        } db->note_id = n;
        anime_id = 0;
        sub_id = 0; if (db->frz_end_cnt) {
            if (db->frz_end_cnt <= (play_w->beat_counter >> 10)) {
                db->frz_end_cnt = 0;
                db->frz_step = 1;
            }
            anime_id = db->anime_id;
            sub_id = db->sub_id;
        }

        if (ct != pre_ct) {
            nct = note->beat_count >> 10;
            marker_anime_reset(pid);
            if (nct == ct && end == 0) {
                step_id = 0;
                note_status = &g_game_w.note_status_table[note->kind];
                freeze_len = 0;
                sub_id = 0;
                for (inp = 7; inp >= 0; inp--) {
                    if (note_status->state[inp] == 1 || note_status->state[inp] == 4) {
                        step_id += 1 << inp;
                        if (note_status->length[inp]) {
                            if (note_status->length[inp] > freeze_len) {
                                freeze_len = note_status->length[inp];
                            }
                        }
                    }
                }
                if (0 < step_id && step_id < 11) {
                    anime_id = anime_id_tbl[step_id];
                    if (freeze_len) {
                        db->frz_end_cnt = nct + (freeze_len >> 8);
                        freeze_eff_set(pid, step_id);
                    } else {
                        db->frz_end_cnt = 0;
                    }
                    if (db->anime_id != anime_id || db->sub_id == 1) {
                        marker_anime_set(pid, step_id);
                    }
                }
                if (anime_id) {
                    if (db->anime_id) {
                        if (db->anime_id == anime_id && db->bak_anime_flag == 0) {
                            if (db->frz_step) {
                                if (db->sub_id == 1) {
                                    db->frz_step = 2;
                                }
                                sub_id = 2; } else if (db->sub_id == 0 || db->sub_id == 2) {
                                sub_id = 2;
                                if (db->frz_end_cnt) db->frz_step = 2;
                            }
                        }
                    }
                } if (db->frz_step) {
                    db->frz_step--;
                }
            } else {
                if (db->anime_id && db->sub_id != 1) {
                    sub_id = 1;
                    anime_id = db->anime_id;
                    if (db->frz_end_cnt) db->frz_step = 0;
                }
            }
            db->anime_id = anime_id; db->sub_id = sub_id;
        }
        db->pre_counter = counter; freeze_eff_off();
        id = 0;
        anime_ct = counter % 0x400;
        anime_ct = (anime_ct << 2) & 0xFFF;
        if (db->anime_id != 0) {
            id = db->anime_id + db->sub_id;
            if (db->sub_id == 1 || db->sub_id == 2) {
                if (db->frz_end_cnt != 0) {
                    if (db->frz_step == 0) { freeze_eff_on();
                        anime_ct = 0;
                    }
                }
            }
        }
        back_anime_set_anime(pid, id, anime_ct);
        if (db->sub_id == 1) {
            db->bak_anime_flag = 1;
        } else {
            db->bak_anime_flag = 0; }
        marker_anime_set_ct(pid, anime_ct);
    }
}

void play_anime_finish(void) {
}
