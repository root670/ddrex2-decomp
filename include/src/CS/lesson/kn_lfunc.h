/*
 * C:\work\usam2\src\CS\lesson\kn_lfunc.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x00222620-0x0022360C
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct sq_header; struct play_hist; struct play_mode; struct play_his; struct eval_w;
struct play_w; struct sequence; struct music_info; struct g_each_w; struct note_status;
struct _tag_cLesPlay; struct sq_standard; struct g_game_w;

/* types (13) */
struct play_his {   // size 0x8
    /* 0x000 */ short music;                          // 0x2
    /* 0x002 */ short edit_id;                        // 0x2
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ signed char roulette;                 // 0x1
    /* 0x006 */ signed char extra;                    // 0x1
    /* 0x007 */ signed char pad;                      // 0x1
};

struct _tag_cLesPlay {   // size 0x54
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int start_beat_count;                 // 0x4
    /* 0x00C */ int start_music_count;                // 0x4
    /* 0x010 */ int end_beat_count;                   // 0x4
    /* 0x014 */ int repeat_max;                       // 0x4
    /* 0x018 */ int repeat_num;                       // 0x4
    /* 0x01C */ int demonstration_flag;               // 0x4
    /* 0x020 */ int demonstration_alpha;              // 0x4
    /* 0x024 */ int obi_wipe_mode;                    // 0x4
    /* 0x028 */ int obi_wipe_speed;                   // 0x4
    /* 0x02C */ int pass_flag;                        // 0x4
    /* 0x030 */ int force_exit_flag;                  // 0x4
    /* 0x034 */ int closing_count;                    // 0x4
    /* 0x038 */ int end_count;                        // 0x4
    /* 0x03C */ int s_counter;                        // 0x4
    /* 0x040 */ int p_counter;                        // 0x4
    /* 0x044 */ int p_flag;                           // 0x4
    /* 0x048 */ int status_disp_flag;                 // 0x4
    /* 0x04C */ int hbota_step;                       // 0x4
    /* 0x050 */ int hbota_bright;                     // 0x4
};

struct sequence {   // size 0x38
    /* 0x000 */ int beat_count;                       // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ short next_change;                    // 0x2
    /* 0x008 */ short music_count;                    // 0x2
    /* 0x00A */ short judge_count;                    // 0x2
    /* 0x00C */ short stolen_count;                   // 0x2
    /* 0x00E */ short op_note_ct;                     // 0x2
    /* 0x010 */ unsigned int hold_length[8];          // 0x20
    /* 0x030 */ unsigned char hold_stat[8];           // 0x8
};

struct sq_header {   // size 0x8
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short kind;                  // 0x2
    /* 0x006 */ unsigned short division;              // 0x2
};

struct sq_standard {   // size 0x10
    /* 0x000 */ sq_header header;                     // 0x8
    /* 0x008 */ unsigned int num;                     // 0x4
    /* 0x00C */ int body[1];                          // 0x4
};

struct play_mode {   // size 0xC
    /* 0x000 */ unsigned char seq_kind;               // 0x1
    /* 0x001 */ unsigned char seq_transfer;           // 0x1
    /* 0x002 */ unsigned char style;                  // 0x1
    /* 0x003 */ unsigned char pccard_seq;             // 0x1
    /* 0x004 */ unsigned char mcard_seq;              // 0x1
    /* 0x005 */ unsigned char padding;                // 0x1
    /* 0x006 */ short edseq_id;                       // 0x2
    /* 0x008 */ unsigned int hidden : 2;              // bits 0..1
    /* 0x008 */ unsigned int thinout : 1;             // bits 2..2
    /* 0x008 */ unsigned int free : 1;                // bits 3..3
    /* 0x008 */ unsigned int soft : 1;                // bits 4..4
    /* 0x008 */ unsigned int boost : 2;               // bits 5..6
    /* 0x008 */ unsigned int speed : 5;               // bits 7..11
    /* 0x008 */ unsigned int scroll : 2;              // bits 12..13
    /* 0x008 */ unsigned int freeze : 1;              // bits 14..14
    /* 0x008 */ unsigned int vivid : 2;               // bits 15..16
    /* 0x008 */ unsigned int anime : 2;               // bits 17..18
    /* 0x008 */ unsigned int dark : 1;                // bits 19..19
    /* 0x008 */ unsigned int pad : 12;                // bits 20..31
};

struct eval_w {   // size 0x6C
    /* 0x000 */ int value_ct[7];                      // 0x1C
    /* 0x01C */ int freez_value_ct[4];                // 0x10
    /* 0x02C */ int groov_bonus[6];                   // 0x18
    /* 0x044 */ int groov_bonus_max[6];               // 0x18
    /* 0x05C */ int score;                            // 0x4
    /* 0x060 */ int max_combo_ct;                     // 0x4
    /* 0x064 */ int jump_ct;                          // 0x4
    /* 0x068 */ short dance_level;                    // 0x2
    /* 0x06A */ short fixed_level;                    // 0x2
};

struct play_hist {   // size 0xC
    /* 0x000 */ int music_count;                      // 0x4
    /* 0x004 */ unsigned char input[8];               // 0x8
};

struct play_w {   // size 0xEC
    /* 0x000 */ int music_counter;                    // 0x4
    /* 0x004 */ int beat_counter;                     // 0x4
    /* 0x008 */ int cur_p_counter;                    // 0x4
    /* 0x00C */ int last_p_counter;                   // 0x4
    /* 0x010 */ int begin_beat_count;                 // 0x4
    /* 0x014 */ int go_beat_count;                    // 0x4
    /* 0x018 */ int finish_beat_count;                // 0x4
    /* 0x01C */ int end_beat_count;                   // 0x4
    /* 0x020 */ int game_start_music_count;           // 0x4
    /* 0x024 */ int game_finish_music_count;          // 0x4
    /* 0x028 */ int back_trans_start_music_count;     // 0x4
    /* 0x02C */ int last_fs_nct;                      // 0x4
    /* 0x030 */ short last_input_count[8];            // 0x10
    /* 0x040 */ play_hist history[8];                 // 0x60
    /* 0x0A0 */ int cur_his;                          // 0x4
    /* 0x0A4 */ int pre_nct;                          // 0x4
    /* 0x0A8 */ int cur_nct;                          // 0x4
    /* 0x0AC */ int disp_nct;                         // 0x4
    /* 0x0B0 */ int cur_great_combo;                  // 0x4
    /* 0x0B4 */ int cur_miss_combo;                   // 0x4
    /* 0x0B8 */ int max_great_combo;                  // 0x4
    /* 0x0BC */ int max_miss_combo;                   // 0x4
    /* 0x0C0 */ int miss_start_count;                 // 0x4
    /* 0x0C4 */ unsigned short input;                 // 0x2
    /* 0x0C6 */ unsigned char dead;                   // 0x1
    /* 0x0C7 */ signed char strictness;               // 0x1
    /* 0x0C8 */ short panel_count[8];                 // 0x10
    /* 0x0D8 */ short message_ct;                     // 0x2
    /* 0x0DA */ short message_id;                     // 0x2
    /* 0x0DC */ short meter_cur;                      // 0x2
    /* 0x0DE */ short meter_vol;                      // 0x2
    /* 0x0E0 */ short meter_ct;                       // 0x2
    /* 0x0E2 */ short dance_class;                    // 0x2
    /* 0x0E4 */ int bar_start;                        // 0x4
    /* 0x0E8 */ int bar_end;                          // 0x4
};

struct g_each_w {   // size 0x54298
    /* 0x000 */ unsigned int play_time;               // 0x4
    /* 0x004 */ unsigned int game_time;               // 0x4
    /* 0x008 */ unsigned int game_time_total;         // 0x4
    /* 0x00C */ signed char select;                   // 0x1
    /* 0x00D */ signed char character;                // 0x1
    /* 0x00E */ signed char costume;                  // 0x1
    /* 0x00F */ signed char motiontype;               // 0x1
    /* 0x010 */ signed char loaded_model;             // 0x1
    /* 0x011 */ signed char loaded_texture;           // 0x1
    /* 0x012 */ signed char loaded_motion;            // 0x1
    /* 0x013 */ unsigned char play_disp_flag;         // 0x1
    /* 0x014 */ unsigned char model_disp_flag;        // 0x1
    /* 0x015 */ unsigned char gauge_disp_flag;        // 0x1
    /* 0x016 */ short cur_point;                      // 0x2
    /* 0x018 */ int cur_life;                         // 0x4
    /* 0x01C */ unsigned int score;                   // 0x4
    /* 0x020 */ unsigned int old_score;               // 0x4
    /* 0x024 */ unsigned int real_score;              // 0x4
    /* 0x028 */ unsigned int bonus;                   // 0x4
    /* 0x02C */ unsigned int old_bonus;               // 0x4
    /* 0x030 */ unsigned int max_score;               // 0x4
    /* 0x034 */ unsigned int old_max_score;           // 0x4
    /* 0x038 */ unsigned int max_bonus;               // 0x4
    /* 0x03C */ unsigned int old_max_bonus;           // 0x4
    /* 0x040 */ unsigned int cal;                     // 0x4
    /* 0x044 */ unsigned int old_cal;                 // 0x4
    /* 0x048 */ unsigned int real_cal;                // 0x4
    /* 0x04C */ unsigned int disp_cal;                // 0x4
    /* 0x050 */ unsigned int average_cal;             // 0x4
    /* 0x054 */ int diet_norm_cal;                    // 0x4
    /* 0x058 */ int diet_norm_minute;                 // 0x4
    /* 0x05C */ int old_norm_cal;                     // 0x4
    /* 0x060 */ int old_norm_minute;                  // 0x4
    /* 0x064 */ int minimum_cal;                      // 0x4
    /* 0x068 */ unsigned char add_cal_flg;            // 0x1
    /* 0x069 */ unsigned char chk_cal_flg;            // 0x1
    /* 0x06A */ unsigned char pad[2];                 // 0x2
    /* 0x06C */ unsigned int play_stage;              // 0x4
    /* 0x070 */ unsigned int decode_key1;             // 0x4
    /* 0x074 */ unsigned int decode_key2;             // 0x4
    /* 0x078 */ unsigned int decode_key3;             // 0x4
    /* 0x07C */ play_mode mode;                       // 0xC
    /* 0x088 */ play_his his[7];                      // 0x38
    /* 0x0C0 */ eval_w stage_evaluation;              // 0x6C
    /* 0x12C */ eval_w total_evaluation;              // 0x6C
    /* 0x198 */ play_w play_work;                     // 0xEC
    /* 0x284 */ int total_notes;                      // 0x4
    /* 0x288 */ int total_jump;                       // 0x4
    /* 0x28C */ int total_freez;                      // 0x4
    /* 0x290 */ int category;                         // 0x4
    /* 0x294 */ int total_category;                   // 0x4
    /* 0x298 */ sequence sequence_buff[6144];         // 0x54000
};

struct note_status {   // size 0x28
    /* 0x000 */ unsigned char state[8];               // 0x8
    /* 0x008 */ unsigned int length[8];               // 0x20
};

struct music_info {   // size 0x98
    /* 0x000 */ char base_name[6];                    // 0x6
    /* 0x006 */ signed char kind;                     // 0x1
    /* 0x007 */ signed char album;                    // 0x1
    /* 0x008 */ short dance_num;                      // 0x2
    /* 0x00A */ short order;                          // 0x2
    /* 0x00C */ unsigned short main_track;            // 0x2
    /* 0x00E */ unsigned short select_track;          // 0x2
    /* 0x010 */ unsigned short bpm_max;               // 0x2
    /* 0x012 */ unsigned short bpm_min;               // 0x2
    /* 0x014 */ unsigned short verm_num;              // 0x2
    /* 0x016 */ unsigned short pcseq_num;             // 0x2
    /* 0x018 */ unsigned long hide;                   // 0x8
    /* 0x020 */ short adjust_mc;                      // 0x2
    /* 0x022 */ // 0x2 bytes padding
    /* 0x024 */ unsigned int difficulty[2];           // 0x8
    /* 0x02C */ unsigned int special;                 // 0x4
    /* 0x030 */ unsigned short max_spm[9];            // 0x12
    /* 0x042 */ unsigned short avg_spm[9];            // 0x12
    /* 0x054 */ unsigned short avg_jpm[9];            // 0x12
    /* 0x066 */ unsigned short chaos_v[9];            // 0x12
    /* 0x078 */ unsigned short freez_v[9];            // 0x12
    /* 0x08A */ // 0x2 bytes padding
    /* 0x08C */ char *title;                          // 0x4
    /* 0x090 */ char *l_name;                         // 0x4
    /* 0x094 */ // 0x4 bytes padding
};

struct g_game_w {   // size 0xAB544
    /* 0x000 */ short state;                          // 0x2
    /* 0x002 */ short genre;                          // 0x2
    /* 0x004 */ music_info *mip;                      // 0x4
    /* 0x008 */ signed char start_chip;               // 0x1
    /* 0x009 */ signed char extra_chip;               // 0x1
    /* 0x00A */ signed char use_chip;                 // 0x1
    /* 0x00B */ signed char lost_chip;                // 0x1
    /* 0x00C */ short stage;                          // 0x2
    /* 0x00E */ short next_stage;                     // 0x2
    /* 0x010 */ short failed;                         // 0x2
    /* 0x012 */ short level;                          // 0x2
    /* 0x014 */ signed char game_kind;                // 0x1
    /* 0x015 */ signed char world;                    // 0x1
    /* 0x016 */ signed char nonstop;                  // 0x1
    /* 0x017 */ signed char event_mode;               // 0x1
    /* 0x018 */ signed char style;                    // 0x1
    /* 0x019 */ signed char music_group;              // 0x1
    /* 0x01A */ signed char music_select_mode;        // 0x1
    /* 0x01B */ signed char extra_stage;              // 0x1
    /* 0x01C */ signed char extra_fix;                // 0x1
    /* 0x01D */ signed char final_fix;                // 0x1
    /* 0x01E */ signed char meter_kind;               // 0x1
    /* 0x01F */ signed char roulette_stage;           // 0x1
    /* 0x020 */ signed char edit_total;               // 0x1
    /* 0x021 */ signed char roulette_total;           // 0x1
    /* 0x022 */ short music;                          // 0x2
    /* 0x024 */ signed char oni_mode;                 // 0x1
    /* 0x025 */ unsigned char oni_load_step;          // 0x1
    /* 0x026 */ short oni_next_music;                 // 0x2
    /* 0x028 */ signed char oni_nonstop_difficulty;   // 0x1
    /* 0x029 */ signed char oni_nonstop_option_selected;  // 0x1
    /* 0x02A */ signed char oni_pad[2];               // 0x2
    /* 0x02C */ signed char beginner_mode;            // 0x1
    /* 0x02D */ signed char beginner_selected;        // 0x1
    /* 0x02E */ signed char freez_selected;           // 0x1
    /* 0x02F */ signed char beginner_pad[1];          // 0x1
    /* 0x030 */ music_info *oni_next_mip;             // 0x4
    /* 0x034 */ g_each_w player[2];                   // 0xA8530
    /* 0xA8564 */ signed char music_table[128];       // 0x80
    /* 0xA85E4 */ note_status note_status_table[300];  // 0x2EE0
    /* 0xAB4C4 */ struct {   // size 0x4
        /* 0x000 */ unsigned char old_stat;               // 0x1
        /* 0x001 */ unsigned char cur_stat;               // 0x1
        /* 0x002 */ unsigned char release_ct;             // 0x1
        /* 0x003 */ unsigned char warning;                // 0x1
    } hc_work[8];
    /* 0xAB4E4 */ int demoloop_ct;                    // 0x4
    /* 0xAB4E8 */ int mode_quit_ct[2];                // 0x8
    /* 0xAB4F0 */ int force_exit_ct[2];               // 0x8
    /* 0xAB4F8 */ int diet_play_time;                 // 0x4
    /* 0xAB4FC */ int old_play_time;                  // 0x4
    /* 0xAB500 */ int menu_num;                       // 0x4
    /* 0xAB504 */ int total_stage;                    // 0x4
    /* 0xAB508 */ int now_bpm;                        // 0x4
    /* 0xAB50C */ unsigned char *last_data_addr;      // 0x4
    /* 0xAB510 */ unsigned char *anime_data_addr;     // 0x4
    /* 0xAB514 */ unsigned char *anime_buff_addr;     // 0x4
    /* 0xAB518 */ unsigned char anime_load_flg;       // 0x1
    /* 0xAB519 */ unsigned char anime1_load_flg;      // 0x1
    /* 0xAB51A */ unsigned char anime2_load_flg;      // 0x1
    /* 0xAB51B */ unsigned char edit_name[12];        // 0xC
    /* 0xAB527 */ unsigned char diet_flg;             // 0x1
    /* 0xAB528 */ unsigned char auto_play_flg;        // 0x1
    /* 0xAB529 */ unsigned char caution_flg;          // 0x1
    /* 0xAB52A */ unsigned char mode_quit_flg;        // 0x1
    /* 0xAB52B */ unsigned char lib_loaded;           // 0x1
    /* 0xAB52C */ unsigned char force_exit_flg;       // 0x1
    /* 0xAB52D */ unsigned char music_stop_flg;       // 0x1
    /* 0xAB52E */ unsigned char train_state;          // 0x1
    /* 0xAB52F */ unsigned char lesson_flag;          // 0x1
    /* 0xAB530 */ unsigned char lesson_auto_play_flag;  // 0x1
    /* 0xAB531 */ unsigned char lesson_pad[2];        // 0x2
    /* 0xAB533 */ unsigned char oni_load_start0;      // 0x1
    /* 0xAB534 */ unsigned char oni_load_start1;      // 0x1
    /* 0xAB535 */ unsigned char oni_load_end0;        // 0x1
    /* 0xAB536 */ unsigned char oni_load_end1;        // 0x1
    /* 0xAB537 */ unsigned char oni_order_step;       // 0x1
    /* 0xAB538 */ unsigned char oni_order_stage;      // 0x1
    /* 0xAB539 */ unsigned char oni_order_cursor;     // 0x1
    /* 0xAB53A */ unsigned char oni_order_top_stage;  // 0x1
    /* 0xAB53B */ unsigned char temp_sqk[2];          // 0x2
    /* 0xAB53D */ unsigned char disp_seltu_flag;      // 0x1
    /* 0xAB53E */ unsigned char temp_pad[1];          // 0x1
    /* 0xAB53F */ unsigned char endless_flag;         // 0x1
    /* 0xAB540 */ unsigned char endless_pad[3];       // 0x3
    /* 0xAB543 */ // 0x1 bytes padding
};

/* variables (21) */
static short finger_pos_tbl[9][2];                               /* @0x0027ECB0 size 0x24 */
int lesson_foot_pos_tbl[5][2];                                   /* @0x0027ECE0 size 0x28 */
int lesson_foot_offset_tbl[9][2];                                /* @0x0027ED10 size 0x48 */
static short kn_e_rhythm_tbl[4];                                 /* not allocated size 0x8 */
static int value_begin_ct[6];                                    /* @0x00294FA0 size 0x18 */
static int value_end_ct[6];                                      /* @0x00294FC0 size 0x18 */
struct @anon6 kn_fin_w;                                          /* @0x006B0210 size 0x20 */
g_game_w g_game_w;                                               /* @0x00592050 size 0xAB544 */
struct @anon5 kn_finger_seq[50];                                 /* @0x006AFE20 size 0x3E8 */
struct @anon1 kn_lesson_main_work;                               /* @0x006B25B0 size 0x88 */
struct @anon4 kn_touch_w[2];                                     /* @0x006B0230 size 0x80 */
struct @anon8 kn_msg_w;                                          /* @0x002A2A88 size 0x8 */
unsigned char *LesStrDataTbl[];                                  /* @0x0027F260 */
struct @anon7 kn_msg_seq[50];                                    /* @0x006AFB00 size 0x320 */
struct @anon4 kn_foot_w[2];                                      /* @0x006B2530 size 0x80 */
struct @anon0 kn_move_w;                                         /* @0x006B2510 size 0x14 */
struct @anon3 kn_foot_seq[200];                                  /* @0x006B02B0 size 0x2260 */
_tag_cLesPlay *pLesPlay;                                         /* @0x002A2134 size 0x4 */
struct @anon11 kn_l_timing_w[80];                                /* @0x006AF880 size 0x280 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (12) */
void kn_lfunc_finger_op(void);                                   /* 0x00222620-0x00222860 lines 836-858 */
void kn_lfunc_set_play_ct(void);                                 /* 0x00222860-0x00222940 lines 757-786 */
void kn_lfunc_set_msg_status(struct @anon7 *m_seq);              /* 0x00222940-0x00222A10 lines 717-748 */
void kn_lfunc_set_foot_status(struct @anon4 *fw, struct @anon0 *mw); /* 0x00222A10-0x00222B9C lines 680-708 */
void kn_lfunc_msg_op(void);                                      /* 0x00222BA0-0x00222C68 lines 639-671 */
void kn_lfunc_set_foot_move(struct @anon4 *fw);                  /* 0x00222C70-0x00222E80 lines 582-630 */
void kn_lfunc_foot_op(void);                                     /* 0x00222E80-0x0022301C lines 533-571 */
void kn_lfunc_chk_timing(void);                                  /* 0x00223020-0x00223260 lines 451-522 */
int kn_lfunc_chk_teach_mode(void);                               /* 0x00223260-0x00223300 lines 419-437 */
void kn_lfunc_chk_clap(void);                                    /* 0x00223300-0x002233A8 lines 311-335 */
void kn_lfunc_chk_now_music(void);                               /* 0x002233B0-0x002233D4 lines 236-302 */
void kn_lfunc_set_head_data(void);                               /* 0x002233E0-0x0022360C lines 199-224 */
