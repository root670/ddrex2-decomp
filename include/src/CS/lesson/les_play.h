/*
 * C:\work\usam2\src\CS\lesson\les_play.c
 * MW MIPS C Compiler, overlay main; 10 functions, code 0x00220740-0x00222338
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct play_hist; struct play_mode; struct play_his; struct eval_w; struct play_w;
struct sequence; struct sq_header; struct _LESTEX_INIT_SET; struct _LESTEX_W;
struct _tag_cModeData; struct _tag_cFilepackData; struct _LESWIN_W; struct _EDSS_DATA_W;
struct _InputData; struct _InputBuffer; struct G_INPUT_W_; struct tm; struct _EDSS_PLAY_W;
struct oni_mode; struct music_info; struct g_each_w; struct note_status; struct double_buffer;
struct _DDRCommonHeader; struct _tag_cDDR7Option; struct _tag_cDDR7Record1;
struct _tag_cDDR7OniRecord1; struct popular; struct G_RANKING_W_; struct machine_point_work;
struct _EDSSAVE_W; struct oni_course; struct sq_standard; struct _tag_cLes; struct G_SYS_W_;
struct _tag_cLesPlay; struct g_game_w; struct G_DRAW_W_; struct _tag_cDDR7SaveData;

/* types (39) */
struct play_his {   // size 0x8
    /* 0x000 */ short music;                          // 0x2
    /* 0x002 */ short edit_id;                        // 0x2
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ signed char roulette;                 // 0x1
    /* 0x006 */ signed char extra;                    // 0x1
    /* 0x007 */ signed char pad;                      // 0x1
};

struct _tag_cDDR7Record1 {   // size 0x90
    /* 0x000 */ unsigned int Score[10];               // 0x28
    /* 0x028 */ unsigned int Bonus[10];               // 0x28
    /* 0x050 */ unsigned int nPlayed;                 // 0x4
    /* 0x054 */ unsigned short LinkNum;               // 0x2
    /* 0x056 */ unsigned short Combo[10];             // 0x14
    /* 0x06A */ unsigned short ComboMax[10];          // 0x14
    /* 0x07E */ unsigned char Level[10];              // 0xA
    /* 0x088 */ unsigned char little_flag[2];         // 0x2
    /* 0x08A */ char pad[6];                          // 0x6
};

struct _LESTEX_W {   // size 0x20
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int u;                                // 0x4
    /* 0x00C */ int v;                                // 0x4
    /* 0x010 */ int w;                                // 0x4
    /* 0x014 */ int h;                                // 0x4
    /* 0x018 */ int z;                                // 0x4
    /* 0x01C */ int tex_num;                          // 0x4
};

struct popular {   // size 0x4B4
    /* 0x000 */ short cur_c;                          // 0x2
    /* 0x002 */ short last_c;                         // 0x2
    /* 0x004 */ unsigned short count[150][4];         // 0x4B0
};

struct sq_header {   // size 0x8
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short kind;                  // 0x2
    /* 0x006 */ unsigned short division;              // 0x2
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

struct sq_standard {   // size 0x10
    /* 0x000 */ sq_header header;                     // 0x8
    /* 0x008 */ unsigned int num;                     // 0x4
    /* 0x00C */ int body[1];                          // 0x4
};

struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
};

struct _LESWIN_W {   // size 0x44
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float sx;                             // 0x4
    /* 0x00C */ float sy;                             // 0x4
    /* 0x010 */ int w;                                // 0x4
    /* 0x014 */ int h;                                // 0x4
    /* 0x018 */ int sw;                               // 0x4
    /* 0x01C */ int sh;                               // 0x4
    /* 0x020 */ float waveY;                          // 0x4
    /* 0x024 */ unsigned int flag;                    // 0x4
    /* 0x028 */ unsigned char alpha;                  // 0x1
    /* 0x029 */ unsigned char salpha;                 // 0x1
    /* 0x02A */ // 0x2 bytes padding
    /* 0x02C */ int bri;                              // 0x4
    /* 0x030 */ char step;                            // 0x1
    /* 0x031 */ char s_step;                          // 0x1
    /* 0x032 */ unsigned char type;                   // 0x1
    /* 0x033 */ unsigned char tex_id;                 // 0x1
    /* 0x034 */ _LESTEX_INIT_SET *def;                // 0x4
    /* 0x038 */ _LESTEX_W *tex[3];                    // 0xC
};

struct _tag_cLes {   // size 0x284
    /* 0x000 */ int StepLes;                          // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int Cursor[4];                        // 0x10
    /* 0x020 */ int Step;                             // 0x4
    /* 0x024 */ int Mode;                             // 0x4
    /* 0x028 */ int NextMode;                         // 0x4
    /* 0x02C */ int bDraw;                            // 0x4
    /* 0x030 */ int bTopDown;                         // 0x4
    /* 0x034 */ int Step2;                            // 0x4
    /* 0x038 */ int init_ok;                          // 0x4
    /* 0x03C */ int sd_dir;                           // 0x4
    /* 0x040 */ int nItemLetter;                      // 0x4
    /* 0x044 */ unsigned char **ExpKanji;             // 0x4
    /* 0x048 */ _tag_cModeData *mode_data_table;      // 0x4
    /* 0x04C */ _tag_cModeData *mode_data;            // 0x4
    /* 0x050 */ int base_tex_id;                      // 0x4
    /* 0x054 */ int level;                            // 0x4
    /* 0x058 */ int section;                          // 0x4
    /* 0x05C */ int play_pid;                         // 0x4
    /* 0x060 */ int ret_dance_play_step;              // 0x4
    /* 0x064 */ int music_label;                      // 0x4
    /* 0x068 */ int loaded_music_label;               // 0x4
    /* 0x06C */ _tag_cFilepackData tblFilepack[10];   // 0x50
    /* 0x0BC */ int sd_play_flag;                     // 0x4
    /* 0x0C0 */ int sd_called_flag;                   // 0x4
    /* 0x0C4 */ int sd_stopped_flag;                  // 0x4
    /* 0x0C8 */ int timing_cursor;                    // 0x4
    /* 0x0CC */ int timing_keep_flag[3];              // 0xC
    /* 0x0D8 */ unsigned int timing_keep_data[3][3];  // 0x24
    /* 0x0FC */ unsigned char font[4][64];            // 0x100
    /* 0x1FC */ _LESWIN_W winp[2];                    // 0x88
};

struct G_RANKING_W_ {   // size 0x10
    /* 0x000 */ char name[4];                         // 0x4
    /* 0x004 */ // 0x4 bytes padding
    /* 0x008 */ unsigned long score;                  // 0x8
};

struct _tag_cModeData {   // size 0x14
    /* 0x000 */ int (*Init)();                        // 0x4
    /* 0x004 */ int (*Control)();                     // 0x4
    /* 0x008 */ int (*View)();                        // 0x4
    /* 0x00C */ int (*Update)();                      // 0x4
    /* 0x010 */ int level;                            // 0x4
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

struct _LESTEX_INIT_SET {   // size 0x20
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int flag;                             // 0x4
    /* 0x014 */ int id[3];                            // 0xC
};

struct _tag_cDDR7OniRecord1 {   // size 0x38
    /* 0x000 */ unsigned int Score[4];                // 0x10
    /* 0x010 */ unsigned short Time[4];               // 0x8
    /* 0x018 */ unsigned short Combo[4];              // 0x8
    /* 0x020 */ unsigned short Miss[4];               // 0x8
    /* 0x028 */ unsigned char Stage[4];               // 0x4
    /* 0x02C */ unsigned char Clear[4];               // 0x4
    /* 0x030 */ unsigned char Level[4];               // 0x4
    /* 0x034 */ unsigned char is_first_clear;         // 0x1
    /* 0x035 */ unsigned char pad[3];                 // 0x3
};

struct oni_mode {   // size 0xC
    /* 0x000 */ unsigned int link_num;                // 0x4
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ unsigned char seq_transfer;           // 0x1
    /* 0x006 */ unsigned char sp_music;               // 0x1
    /* 0x007 */ unsigned char add_life;               // 0x1
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

struct _tag_cDDR7Option {   // size 0x40
    /* 0x000 */ unsigned char Sound;                  // 0x1
    /* 0x001 */ unsigned char Voice;                  // 0x1
    /* 0x002 */ signed char Timing;                   // 0x1
    /* 0x003 */ char pad_sound[1];                    // 0x1
    /* 0x004 */ unsigned char KeyConfig[4];           // 0x4
    /* 0x008 */ unsigned char Vibration;              // 0x1
    /* 0x009 */ unsigned char DPlay;                  // 0x1
    /* 0x00A */ char pad_cont[2];                     // 0x2
    /* 0x00C */ unsigned char AutoSave;               // 0x1
    /* 0x00D */ unsigned char FolderLoad;             // 0x1
    /* 0x00E */ char pad_mc[2];                       // 0x2
    /* 0x010 */ unsigned char Level;                  // 0x1
    /* 0x011 */ unsigned char MaxStage[3];            // 0x3
    /* 0x014 */ unsigned char GameOver;               // 0x1
    /* 0x015 */ unsigned char TimeLimit;              // 0x1
    /* 0x016 */ unsigned char EventMode;              // 0x1
    /* 0x017 */ unsigned char DefaultDifficulty;      // 0x1
    /* 0x018 */ char pad_game[8];                     // 0x8
    /* 0x020 */ unsigned char BgEffect;               // 0x1
    /* 0x021 */ unsigned char BgBright;               // 0x1
    /* 0x022 */ unsigned char DangerDisplay;          // 0x1
    /* 0x023 */ unsigned char StepMarkColor;          // 0x1
    /* 0x024 */ signed char screen_x;                 // 0x1
    /* 0x025 */ signed char screen_y;                 // 0x1
    /* 0x026 */ unsigned char FlickerFree;            // 0x1
    /* 0x027 */ unsigned char SongDisplay;            // 0x1
    /* 0x028 */ unsigned char DietMeasure;            // 0x1
    /* 0x029 */ unsigned char DietDisplay;            // 0x1
    /* 0x02A */ unsigned char DietTime;               // 0x1
    /* 0x02B */ unsigned char DietPlayDefault;        // 0x1
    /* 0x02C */ unsigned char DietWeightUnit;         // 0x1
    /* 0x02D */ char pad_diet[3];                     // 0x3
    /* 0x030 */ unsigned char Language;               // 0x1
    /* 0x031 */ char pad_lang[7];                     // 0x7
    /* 0x038 */ unsigned char DollDisp;               // 0x1
    /* 0x039 */ unsigned char DollGuestNum;           // 0x1
    /* 0x03A */ unsigned char DollChara[3];           // 0x3
    /* 0x03D */ char pad[3];                          // 0x3
};

struct _EDSS_DATA_W {   // size 0x10
    /* 0x000 */ unsigned int score[2];                // 0x8
    /* 0x008 */ int combo;                            // 0x4
    /* 0x00C */ int stage;                            // 0x4
};

struct _DDRCommonHeader {   // size 0x10
    /* 0x000 */ unsigned char Type;                   // 0x1
    /* 0x001 */ unsigned char Platform;               // 0x1
    /* 0x002 */ unsigned char Hardware;               // 0x1
    /* 0x003 */ unsigned char Version;                // 0x1
    /* 0x004 */ unsigned char Area;                   // 0x1
    /* 0x005 */ signed char tmp;                      // 0x1
    /* 0x006 */ unsigned short title;                 // 0x2
    /* 0x008 */ unsigned int t_info[2];               // 0x8
};

struct _EDSS_PLAY_W {   // size 0x60
    /* 0x000 */ _EDSS_DATA_W p_single[3];             // 0x30
    /* 0x030 */ _EDSS_DATA_W p_double[3];             // 0x30
};

struct _InputData {   // size 0x20
    /* 0x000 */ unsigned short player_input[4];       // 0x8
    /* 0x008 */ unsigned short player_input_trigger[4];  // 0x8
    /* 0x010 */ unsigned short player_input_released[4];  // 0x8
    /* 0x018 */ unsigned short etc;                   // 0x2
    /* 0x01A */ unsigned short etc_trigger;           // 0x2
    /* 0x01C */ unsigned short etc_released;          // 0x2
    /* 0x01E */ unsigned short padding;               // 0x2
};

struct _InputBuffer {   // size 0x48
    /* 0x000 */ unsigned long current_buffer;         // 0x8
    /* 0x008 */ _InputData data[2];                   // 0x40
};

struct G_INPUT_W_ {   // size 0x50
    /* 0x000 */ _InputData *dp;                       // 0x4
    /* 0x004 */ // 0x4 bytes padding
    /* 0x008 */ _InputBuffer buffer;                  // 0x48
};

struct tm {   // size 0x24
    /* 0x000 */ int tm_sec;                           // 0x4
    /* 0x004 */ int tm_min;                           // 0x4
    /* 0x008 */ int tm_hour;                          // 0x4
    /* 0x00C */ int tm_mday;                          // 0x4
    /* 0x010 */ int tm_mon;                           // 0x4
    /* 0x014 */ int tm_year;                          // 0x4
    /* 0x018 */ int tm_wday;                          // 0x4
    /* 0x01C */ int tm_yday;                          // 0x4
    /* 0x020 */ int tm_isdst;                         // 0x4
};

struct G_SYS_W_ {   // size 0x90
    /* 0x000 */ G_INPUT_W_ input_w;                   // 0x50
    /* 0x050 */ tm start_tm;                          // 0x24
    /* 0x074 */ unsigned int v_counter;               // 0x4
    /* 0x078 */ unsigned long v_counter2;             // 0x8
    /* 0x080 */ unsigned int s_counter;               // 0x4
    /* 0x084 */ int u_counter;                        // 0x4
    /* 0x088 */ unsigned char entry_bit;              // 0x1
    /* 0x089 */ char vpf;                             // 0x1
    /* 0x08A */ char pad[2];                          // 0x2
    /* 0x08C */ // 0x4 bytes padding
};

struct _EDSSAVE_W {   // size 0x238
    /* 0x000 */ _EDSS_PLAY_W reg[2];                  // 0xC0
    /* 0x0C0 */ _EDSS_DATA_W max_point;               // 0x10
    /* 0x0D0 */ unsigned int PlayFlag[90];            // 0x168
};

struct oni_course {   // size 0x110
    /* 0x000 */ unsigned int course_allnum;           // 0x4
    /* 0x004 */ unsigned int course_defnum;           // 0x4
    /* 0x008 */ short flag;                           // 0x2
    /* 0x00A */ short order;                          // 0x2
    /* 0x00C */ short start_life;                     // 0x2
    /* 0x00E */ short stage;                          // 0x2
    /* 0x010 */ int single_steps;                     // 0x4
    /* 0x014 */ int double_steps;                     // 0x4
    /* 0x018 */ int hide;                             // 0x4
    /* 0x01C */ int option;                           // 0x4
    /* 0x020 */ oni_mode mode[20];                    // 0xF0
};

struct machine_point_work {   // size 0x14
    /* 0x000 */ unsigned int hide_show[2];            // 0x8
    /* 0x008 */ unsigned int status;                  // 0x4
    /* 0x00C */ unsigned int period_time;             // 0x4
    /* 0x010 */ int cur_point;                        // 0x4
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

struct double_buffer {   // size 0x628
    /* 0x000 */ struct {   // size 0x28
        /* 0x000 */ unsigned long length;                 // 0x8
        /* 0x008 */ struct {   // size 0x4
            /* 0x000 */ unsigned int p : 24;                  // bits 0..23
            /* 0x003 */ unsigned char num : 8;                // bits 0..7
        } *org;
        /* 0x00C */ // 0x4 bytes padding
        /* 0x010 */ unsigned long offset;                 // 0x8
        /* 0x018 */ unsigned long point;                  // 0x8
        /* 0x020 */ struct {   // size 0x4
            /* 0x000 */ unsigned int p : 24;                  // bits 0..23
            /* 0x003 */ unsigned char num : 8;                // bits 0..7
        } *tag;
        /* 0x024 */ // 0x4 bytes padding
    } gs_ot;
    /* 0x028 */ struct {   // size 0x4
        /* 0x000 */ unsigned int p : 24;                  // bits 0..23
        /* 0x003 */ unsigned char num : 8;                // bits 0..7
    } z_sort[256];
    /* 0x428 */ unsigned char packet[512];            // 0x200
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

struct G_DRAW_W_ {   // size 0xDE8
    /* 0x000 */ int buffer_id;                        // 0x4
    /* 0x004 */ // 0x4 bytes padding
    /* 0x008 */ double_buffer double_buffer[2];       // 0xC50
    /* 0xC58 */ double_buffer *cur_db;                // 0x4
    /* 0xC5C */ struct {   // size 0x8
        /* 0x000 */ short x;                              // 0x2
        /* 0x002 */ short y;                              // 0x2
        /* 0x004 */ short w;                              // 0x2
        /* 0x006 */ short h;                              // 0x2
    } li_rect[32];
    /* 0xD5C */ unsigned int *li_buff[32];            // 0x80
    /* 0xDDC */ signed char clear_flag;               // 0x1
    /* 0xDDD */ signed char cancel_flag;              // 0x1
    /* 0xDDE */ signed char tmp_flag;                 // 0x1
    /* 0xDDF */ signed char tmp_flag2;                // 0x1
    /* 0xDE0 */ unsigned char cur_resolution : 4;     // bits 0..3
    /* 0xDE0 */ unsigned char req_resolution : 4;     // bits 4..7
    /* 0xDE1 */ unsigned char cur_dither : 4;         // bits 0..3
    /* 0xDE1 */ unsigned char req_dither : 4;         // bits 4..7
    /* 0xDE2 */ // 0x6 bytes padding
};

struct _tag_cDDR7SaveData {   // size 0x5E30
    /* 0x000 */ _DDRCommonHeader CommonHeader;        // 0x10
    /* 0x010 */ _tag_cDDR7Option Option;              // 0x40
    /* 0x050 */ _tag_cDDR7Record1 MRecord[80];        // 0x2D00
    /* 0x2D50 */ unsigned char Information[144];      // 0x90
    /* 0x2DE0 */ unsigned int nMusic;                 // 0x4
    /* 0x2DE4 */ unsigned int nBoot;                  // 0x4
    /* 0x2DE8 */ unsigned int nPlayerType[3];         // 0xC
    /* 0x2DF4 */ unsigned int nDifficulty[5];         // 0x14
    /* 0x2E08 */ int nwork[2];                        // 0x8
    /* 0x2E10 */ unsigned char LessonWork[32];        // 0x20
    /* 0x2E30 */ _tag_cDDR7OniRecord1 OniRecord[32];  // 0x700
    /* 0x3530 */ popular popular;                     // 0x4B4
    /* 0x39E4 */ // 0x4 bytes padding
    /* 0x39E8 */ G_RANKING_W_ high_score[30];         // 0x1E0
    /* 0x3BC8 */ machine_point_work machine_p;        // 0x14
    /* 0x3BDC */ unsigned int HideMusic[4];           // 0x10
    /* 0x3BEC */ unsigned int HideFlag[4];            // 0x10
    /* 0x3BFC */ unsigned int HideDoll[2];            // 0x8
    /* 0x3C04 */ _EDSSAVE_W EdsRecords;               // 0x238
    /* 0x3E3C */ oni_course oni_order[3];             // 0x330
    /* 0x416C */ oni_course dietprogram_order[3];     // 0x330
    /* 0x449C */ struct {   // size 0xCC8
        /* 0x000 */ unsigned int program_calorie[9];      // 0x24
        /* 0x024 */ unsigned int program_play_count[9];   // 0x24
        /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
        /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
    } diet_calorie_record[2];
    /* 0x5E2C */ // 0x4 bytes padding
};

/* variables (23) */
_tag_cLesPlay *pLesPlay;                                         /* @0x002A2134 size 0x4 */
static unsigned int LesTimingTable1[6];                          /* @0x0027EC50 size 0x18 */
static unsigned int LesTimingTable2[6];                          /* @0x0027EC70 size 0x18 */
static unsigned int LesTimingTable3[6];                          /* @0x0027EC90 size 0x18 */
unsigned char kn_l_section_num_tbl[4];                           /* not allocated size 0x4 */
g_game_w g_game_w;                                               /* @0x00592050 size 0xAB544 */
struct @anon2 kn_finger_seq[50];                                 /* @0x006AFE20 size 0x3E8 */
struct @anon0 kn_foot_seq[200];                                  /* @0x006B02B0 size 0x2260 */
struct @anon1 kn_msg_seq[50];                                    /* @0x006AFB00 size 0x320 */
struct @anon8 kn_lesson_main_work;                               /* @0x006B25B0 size 0x88 */
_tag_cLes *pLes;                                                 /* @0x002A2128 size 0x4 */
G_SYS_W_ g_sys_w;                                                /* @0x0063D5A0 size 0x90 */
_tag_cDDR7SaveData SaveData;                                     /* @0x002B0470 size 0x5E30 */
G_DRAW_W_ g_draw_w;                                              /* @0x005875C0 size 0xDE8 */
struct @anon19 kn_l_timing_w[80];                                /* @0x006AF880 size 0x280 */
struct @anon15 kn_msg_w;                                         /* @0x002A2A88 size 0x8 */
struct @anon10 kn_fin_w;                                         /* @0x006B0210 size 0x20 */
struct @anon20 kn_touch_w[2];                                    /* @0x006B0230 size 0x80 */
struct @anon3 kn_move_w;                                         /* @0x006B2510 size 0x14 */
struct @anon20 kn_foot_w[2];                                     /* @0x006B2530 size 0x80 */
static _tag_cLesPlay _pLesPlay;                                  /* @0x006B2640 size 0x54 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (10) */
static void lesson_data_setup(unsigned int l_data_address);      /* 0x00220740-0x00220CB0 lines 1152-1386 */
void make_ssq_at_lesson(unsigned int ind_address, unsigned int l_data_address, unsigned int ssq_address); /* 0x00220CB0-0x00221014 lines 985-1138 */
static void disp_step(void);                                     /* 0x00221020-0x0022111C lines 886-948 */
static int play_main(void);                                      /* 0x00221120-0x00221560 lines 700-845 */
static int intro_play(void);                                     /* 0x00221560-0x00221678 lines 653-695 */
static void play_init(void);                                     /* 0x00221680-0x00221C84 lines 410-647 */
int Update_LesPlay(void);                                        /* 0x00221C90-0x00221CC8 lines 395-401 */
int View_LesPlay(void);                                          /* 0x00221CD0-0x00221CD8 lines 389-389 */
int Control_LesPlay(void);                                       /* 0x00221CE0-0x00221F2C lines 310-383 */
int Init_LesPlay(void);                                          /* 0x00221F30-0x00222338 lines 174-306 */
