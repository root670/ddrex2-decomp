/* src/AM/s573/play/p_anime.c
 *
 * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file
 * (rendered into include/src/AM/s573/play/p_anime.h) plus the five functions'
 * disassembly.  Statement line numbers are evidence, so the statements sit on
 * the retail line numbers.
 */
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

#line 79
void play_anime_init(void) {
    struct play_anime_db *db;
#line 80
    paw_p = &play_anime_w;
#line 82
    paw_p->mode = 0;

#line 85
    db = &paw_p->db[0];
#line 87
    db->anime_id = 0;
#line 88
    db->sub_id = 0;
#line 89
    db->note_id = 0;
#line 90
    db->pre_counter = 0;

#line 93
    db->frz_end_cnt = 0;
#line 94
    db->frz_step = 0;
#line 95
    db->bak_anime_flag = 0; db = &paw_p->db[1]; db->anime_id = 0; db->sub_id = 0; db->note_id = 0; db->pre_counter = 0; db->frz_end_cnt = 0; db->frz_step = 0; db->bak_anime_flag = 0;
#line 99
}

#line 66
void play_anime_set_inst_mode(void) {
#line 67
    paw_p->mode = 1;
#line 68
}

#line 383
void play_anime_step_inst(void) {
    int pid; struct play_anime_db *db; struct play_w *play_w; int counter; struct sequence *note;
#line 384
    int ct; int pre_ct; int end; int hold_flag; int n; int anime_id; int sub_id; int nct;
#line 385
    int inp; int step_id; struct note_status *note_status; int id; int anime_ct;
#line 386
    for (pid = 0; pid < 2; pid++) {
#line 387
        db = &paw_p->db[pid];
#line 388
        play_w = &g_game_w.player[pid].play_work;
#line 389
        counter = play_w->beat_counter + 0x400;
#line 391
        ct = counter >> 10;
#line 392
        pre_ct = db->pre_counter >> 10;
#line 393
        end = 0; n = g_game_w.player[pid].mode.style;
#line 406
        if (n == 7 || n == 0) continue;
#line 420
        n = db->note_id;
#line 422
        note = &g_game_w.player[pid].sequence_buff[n];
#line 424
        while (1) {
#line 425
            if (note->kind == -2) {
#line 426
                end = 1;
#line 427
                break;
            }
#line 430
            if (note->kind >= 0) {
#line 431
                if ((note->beat_count >> 10) >= ct) break;
#line 433
            }
#line 433
            n++; note++; }
#line 434
        db->note_id = n;
#line 438
        if (play_w->beat_counter < 0x3000) {
#line 439
            hold_flag = 0;
#line 440
            hold_release = 0;
#line 442
            pre_hold_flag = 0; } else if (play_w->beat_counter < 0x4000) { hold_flag = 1;
#line 444
        } else if (play_w->beat_counter < 0x4C00) { hold_flag = 0;
#line 446
        } else if (play_w->beat_counter < 0x5C00) { hold_flag = 1;
#line 448
        } else if (play_w->beat_counter < 0x6800) { hold_flag = 0;
#line 450
        } else if (play_w->beat_counter < 0x7000) { hold_flag = 1;
#line 452
        } else {
#line 453
            hold_flag = 0;
#line 456
        }
#line 458
        if (pre_hold_flag != hold_flag && hold_flag == 0) {
#line 459
            hold_release = 1;
        }
#line 461
        pre_hold_flag = hold_flag;
#line 465
        anime_id = 0;
        sub_id = 0;
#line 468
        if (hold_flag || hold_release) {
#line 469
            anime_id = db->anime_id;
#line 470
            sub_id = db->sub_id;
        }
#line 474
        if (ct != pre_ct) {
#line 475
            nct = note->beat_count >> 10;
#line 477
            if (hold_release == 1) {
#line 478
                hold_release = 2;
#line 479
            } else if (hold_release == 2) {
#line 480
                hold_release = 0;
#line 481
                anime_id = 0;
#line 482
                sub_id = 0;
            }
#line 486
            marker_anime_reset(pid);
#line 488
            if (nct == ct && end == 0 && hold_flag == 0 && hold_release == 0) {
#line 490
                step_id = 0;
#line 491
                note_status = &g_game_w.note_status_table[note->kind];
#line 493
                for (inp = 7; inp >= 0; inp--) {
#line 494
                    if (note_status->state[inp] == 1 || note_status->state[inp] == 4) {
#line 496
                        step_id += 1 << inp;
#line 498
                    }
#line 498
                }
#line 501
                if (0 < step_id && step_id < 11) {
#line 505
                    anime_id = anime_id_tbl[step_id];
#line 508
                    if (db->anime_id != anime_id || db->sub_id == 1) {
#line 509
                        marker_anime_set(pid, step_id);
#line 510
                        freeze_eff_set(pid, step_id);
                    }
                }
#line 526
            } else {
#line 528
                if (db->anime_id != 0 && db->sub_id != 1) {
#line 529
                    anime_id = db->anime_id;
#line 530
                    sub_id = 1;
                }
#line 533
            }
#line 534
            db->anime_id = anime_id;
#line 535
            db->sub_id = sub_id;
        }
#line 541
        db->pre_counter = counter; freeze_eff_off();
#line 545
        id = 0;
#line 546
        anime_ct = counter % 0x400; anime_ct = (anime_ct << 2) & 0xFFF;
#line 548
        if (db->anime_id != 0) {
            id = db->anime_id + db->sub_id;
#line 552
            if (db->sub_id == 1) {
#line 553
                if (hold_flag) { if (hold_release == 0) {
#line 555
                    anime_ct = 0; freeze_eff_on();
                } }
            }
#line 569
        }
#line 570
        back_anime_set_anime(pid, id, anime_ct);
#line 571
        marker_anime_set_ct(pid, anime_ct);
#line 573
    }
#line 574
}

#line 110
void play_anime_step(void) {
    int pid;
#line 112
    int pid_total = 0;
#line 113
    struct play_anime_db *db; struct play_w *play_w; int counter; struct sequence *note; int ct; int pre_ct; int end; int n;
    int anime_id; int sub_id; int nct; int inp; int step_id;
    struct note_status *note_status; int freeze_len; int id; int anime_ct;
#line 114
    for (pid = 0; pid < 2; pid++) {
#line 115
        db = &paw_p->db[pid];
#line 116
        play_w = &g_game_w.player[pid].play_work;
#line 117
        counter = play_w->beat_counter + 0x400;
#line 119
        ct = counter >> 10;
#line 120
        pre_ct = db->pre_counter >> 10;
#line 121
        end = 0; n = g_game_w.player[pid].mode.style;
#line 167
        if (n == 7 || n == 0) continue;
#line 169
        if ((g_game_w.state == 2 || g_game_w.state == 5 || g_game_w.state == 4)
                && g_game_w.player[pid].mode.seq_kind != 7) continue;
#line 174
        if (g_game_w.player[pid].mode.edseq_id != -1) continue;
#line 176
        if (paw_p->mode == 1) {
#line 177
            if (pid_total) continue;
#line 178
            pid_total++;
#line 179
        }

#line 183
        n = db->note_id;
#line 185
        note = &g_game_w.player[pid].sequence_buff[n];
#line 187
        while (1) {
#line 188
            if (note->kind == -2) {
#line 189
                end = 1;
#line 190
                break;
            }
#line 192
            if (note->kind >= 0) {
#line 193
                if ((note->beat_count >> 10) >= ct) break; }
#line 195
            n++; note++;
        }
#line 195
        db->note_id = n;
#line 201
        anime_id = 0;
        sub_id = 0;
#line 202
        if (db->frz_end_cnt) {
#line 205
            if (db->frz_end_cnt <= (play_w->beat_counter >> 10)) {
#line 207
                db->frz_end_cnt = 0;
#line 208
                db->frz_step = 1;
            }
#line 210
            anime_id = db->anime_id;
#line 211
            sub_id = db->sub_id;
        }

#line 216
        if (ct != pre_ct) {
#line 217
            nct = note->beat_count >> 10;
#line 220
            marker_anime_reset(pid);
#line 221
            if (nct == ct && end == 0) {
#line 223
                step_id = 0;
#line 225
                note_status = &g_game_w.note_status_table[note->kind];
#line 228
                freeze_len = 0;
#line 229
                sub_id = 0;
#line 232
                for (inp = 7; inp >= 0; inp--) {
#line 233
                    if (note_status->state[inp] == 1 || note_status->state[inp] == 4) {
#line 235
                        step_id += 1 << inp;
#line 239
                        if (note_status->length[inp]) {
#line 240
                            if (note_status->length[inp] > freeze_len) {
#line 241
                                freeze_len = note_status->length[inp];
                            }
                        }
                    }
#line 246
                }
#line 249
                if (0 < step_id && step_id < 11) {
#line 253
                    anime_id = anime_id_tbl[step_id];
#line 256
                    if (freeze_len) {
#line 257
                        db->frz_end_cnt = nct + (freeze_len >> 8);
#line 258
                        freeze_eff_set(pid, step_id);
#line 259
                    } else {
#line 260
                        db->frz_end_cnt = 0;
#line 261
                    }
#line 264
                    if (db->anime_id != anime_id || db->sub_id == 1) {
#line 265
                        marker_anime_set(pid, step_id);
#line 266
                    }
                }
#line 271
                if (anime_id) {
#line 272
                    if (db->anime_id) {
#line 273
                        if (db->anime_id == anime_id && db->bak_anime_flag == 0) {
#line 274
                            if (db->frz_step) {
#line 277
                                if (db->sub_id == 1) {
#line 278
                                    db->frz_step = 2;
                                }
                                sub_id = 2;
#line 280
                            } else if (db->sub_id == 0 || db->sub_id == 2) {
                                sub_id = 2;
                                if (db->frz_end_cnt) db->frz_step = 2;
                            }
                        }
                    }
                }
#line 286
                if (db->frz_step) {
                    db->frz_step--;
                }
#line 300
            } else {
#line 301
                if (db->anime_id && db->sub_id != 1) {
#line 303
                    sub_id = 1;
#line 305
                    anime_id = db->anime_id;
                    if (db->frz_end_cnt) db->frz_step = 0;
                }
#line 309
            }
            db->anime_id = anime_id;
#line 310
            db->sub_id = sub_id;
        }
#line 316
        db->pre_counter = counter; freeze_eff_off();
#line 320
        id = 0;
#line 321
        anime_ct = counter % 0x400;
        anime_ct = (anime_ct << 2) & 0xFFF;
#line 323
        if (db->anime_id != 0) {
            id = db->anime_id + db->sub_id;
#line 328
            if (db->sub_id == 1 || db->sub_id == 2) {
#line 329
                if (db->frz_end_cnt != 0) {
#line 330
                    if (db->frz_step == 0) { freeze_eff_on();
#line 331
                        anime_ct = 0;
                    }
                }
            }
        }
#line 346
#line 347
        back_anime_set_anime(pid, id, anime_ct);
#line 350
        if (db->sub_id == 1) {
#line 352
            db->bak_anime_flag = 1;
#line 353
        } else {
            db->bak_anime_flag = 0;
#line 354
        }
#line 356
        marker_anime_set_ct(pid, anime_ct);
#line 358
    }
#line 359
}

#line 364
void play_anime_finish(void) {
#line 365
}
