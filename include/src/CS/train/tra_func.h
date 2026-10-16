/*
 * C:\work2\usaex2\src\CS\train\tra_func.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x0027C1F0-0x0028064C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_train_tra_func_c_H
#define DDR_UNIT_src_CS_train_tra_func_c_H

#include "types/G_SYS_W_.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"
#include "types/sequence.h"
#include "types/sq_standard.h"

/* anonymous types (20) */

/* anon_13_159 -- @anon13, 0x4 bytes, tra_func.c (DIE 0x2D51F0) */
union anon_13_159 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_159 -- @anon0, 0x34 bytes, tra_func.c (DIE 0x2D2C35) */
struct anon_0_159 {   // size 0x34
    /* 0x000 */ union anon_13_159 x0;                 // 0x4
    /* 0x004 */ union anon_13_159 y0;                 // 0x4
    /* 0x008 */ union anon_13_159 x1;                 // 0x4
    /* 0x00C */ union anon_13_159 y1;                 // 0x4
    /* 0x010 */ union anon_13_159 x2;                 // 0x4
    /* 0x014 */ union anon_13_159 y2;                 // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
};

/* anon_1_159 -- @anon1, 0x48 bytes, tra_func.c (DIE 0x2D3442) */
struct anon_1_159 {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02C */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03A */ unsigned short tw;                    // 0x2
    /* 0x03C */ unsigned short th;                    // 0x2
    /* 0x03E */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
};

/* anon_2_159 -- @anon2, 0xD40 bytes, tra_func.c (DIE 0x2D3829) */
struct anon_2_159 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_3_159 -- @anon3, 0x14 bytes, tra_func.c (DIE 0x2D3E90) */
struct anon_3_159 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_4_159 -- @anon4, 0xC bytes, tra_func.c (DIE 0x2D4136) */
struct anon_4_159 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_5_159 -- @anon5, 0x14 bytes, tra_func.c (DIE 0x2D42A0) */
struct anon_5_159 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_6_159 -- @anon6, 0x1300 bytes, tra_func.c (DIE 0x2D4492) */
struct anon_6_159 {   // size 0x1300
    /* 0x000 */ unsigned char evboot[24];             // 0x18
    /* 0x018 */ unsigned char is_savedata;            // 0x1
    /* 0x019 */ signed char max_area;                 // 0x1
    /* 0x01A */ signed char disp_type;                // 0x1
    /* 0x01B */ char pading;                          // 0x1
    /* 0x01C */ unsigned char dancer_use_cnt[24];     // 0x18
    /* 0x034 */ int cur_cursor;                       // 0x4
    /* 0x038 */ unsigned int all_clear_count;         // 0x4
    /* 0x03C */ unsigned int all_play_time;           // 0x4
    /* 0x040 */ int route[200];                       // 0x320
    /* 0x360 */ struct anon_3_159 subject[200];       // 0xFA0
};

/* anon_9_159 -- @anon9, 0x4 bytes, tra_func.c (DIE 0x2D4A36) */
struct anon_9_159 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_7_159 -- @anon7, 0x4 bytes, tra_func.c (DIE 0x2D47FC) */
union anon_7_159 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_9_159 s;                  // 0x4
};

/* anon_8_159 -- @anon8, 0x24 bytes, tra_func.c (DIE 0x2D487E) */
struct anon_8_159 {   // size 0x24
    /* 0x000 */ union anon_13_159 x0;                 // 0x4
    /* 0x004 */ union anon_13_159 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01C */ unsigned char r0;                     // 0x1
    /* 0x01D */ unsigned char g0;                     // 0x1
    /* 0x01E */ unsigned char b0;                     // 0x1
    /* 0x01F */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};

/* anon_10_159 -- @anon10, 0x12E0 bytes, tra_func.c (DIE 0x2D4CAF) */
struct anon_10_159 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_4_159 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_11_159 -- @anon11, 0x4 bytes, tra_func.c (DIE 0x2D4F50) */
struct anon_11_159 {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
};

/* anon_12_159 -- @anon12, 0x2134 bytes, tra_func.c (DIE 0x2D500D) */
struct anon_12_159 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_7_159 userpass;            // 0x4
    /* 0x008 */ struct anon_10_159 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_2_159 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_14_159 -- @anon14, 0x30 bytes, tra_func.c (DIE 0x2D59CC) */
struct anon_14_159 {   // size 0x30
    /* 0x000 */ union anon_13_159 x0;                 // 0x4
    /* 0x004 */ union anon_13_159 y0;                 // 0x4
    /* 0x008 */ union anon_13_159 x1;                 // 0x4
    /* 0x00C */ union anon_13_159 y1;                 // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
};

/* anon_15_159 -- @anon15, 0x10 bytes, tra_func.c (DIE 0x2D5CE6) */
struct anon_15_159 {   // size 0x10
    /* 0x000 */ union anon_13_159 x0;                 // 0x4
    /* 0x004 */ union anon_13_159 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_16_159 -- @anon16, 0x4 bytes, tra_func.c (DIE 0x2D5DE3) */
struct anon_16_159 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_17_159 -- @anon17, 0xB8 bytes, tra_func.c (DIE 0x2D6634) */
struct anon_17_159 {   // size 0xB8
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char step_s;                 // 0x1
    /* 0x002 */ unsigned char mode;                   // 0x1
    /* 0x003 */ unsigned char next_mode;              // 0x1
    /* 0x004 */ unsigned char sub_win_alpha;          // 0x1
    /* 0x005 */ unsigned char cur;                    // 0x1
    /* 0x006 */ unsigned char old_cur;                // 0x1
    /* 0x007 */ unsigned char opt_cur;                // 0x1
    /* 0x008 */ unsigned char asi_cur;                // 0x1
    /* 0x009 */ unsigned char co_win_suu;             // 0x1
    /* 0x00A */ // 0x6 bytes padding
    /* 0x010 */ unsigned long arrow_clut_ct;          // 0x8
    /* 0x018 */ unsigned int flag;                    // 0x4
    /* 0x01C */ int repcnt;                           // 0x4
    /* 0x020 */ float ftimer;                         // 0x4
    /* 0x024 */ short music_num;                      // 0x2
    /* 0x026 */ short old_music_num;                  // 0x2
    /* 0x028 */ unsigned char player;                 // 0x1
    /* 0x029 */ unsigned char level;                  // 0x1
    /* 0x02A */ unsigned char mspeed;                 // 0x1
    /* 0x02B */ unsigned char edit_data_on;           // 0x1
    /* 0x02C */ unsigned char clap;                   // 0x1
    /* 0x02D */ unsigned char metro;                  // 0x1
    /* 0x02E */ unsigned char track;                  // 0x1
    /* 0x02F */ unsigned char arrow_speed;            // 0x1
    /* 0x030 */ unsigned char boost;                  // 0x1
    /* 0x031 */ unsigned char appear;                 // 0x1
    /* 0x032 */ unsigned char turn;                   // 0x1
    /* 0x033 */ unsigned char little;                 // 0x1
    /* 0x034 */ unsigned char dark;                   // 0x1
    /* 0x035 */ unsigned char simu;                   // 0x1
    /* 0x036 */ unsigned char scroll;                 // 0x1
    /* 0x037 */ unsigned char freeze;                 // 0x1
    /* 0x038 */ unsigned char real_turn;              // 0x1
    /* 0x039 */ unsigned char c_bar_max;              // 0x1
    /* 0x03A */ unsigned char c_bar_adjust;           // 0x1
    /* 0x03B */ unsigned char bar_start;              // 0x1
    /* 0x03C */ unsigned char bar_end;                // 0x1
    /* 0x03D */ unsigned char bar_max;                // 0x1
    /* 0x03E */ unsigned char adjust_bar;             // 0x1
    /* 0x03F */ unsigned char cur_bar_w;              // 0x1
    /* 0x040 */ unsigned char special_bar;            // 0x1
    /* 0x041 */ // 0x1 bytes padding
    /* 0x042 */ short scroll_ct;                      // 0x2
    /* 0x044 */ unsigned char scroll_spd;             // 0x1
    /* 0x045 */ unsigned char start_side;             // 0x1
    /* 0x046 */ unsigned char finish_flg;             // 0x1
    /* 0x047 */ unsigned char music_step;             // 0x1
    /* 0x048 */ unsigned char finish_step;            // 0x1
    /* 0x049 */ unsigned char now_play_bar;           // 0x1
    /* 0x04A */ unsigned char old_play_bar;           // 0x1
    /* 0x04B */ unsigned char cur_point_pos[2];       // 0x2
    /* 0x04D */ unsigned char play_bright;            // 0x1
    /* 0x04E */ short obi_deg;                        // 0x2
    /* 0x050 */ short cur_clap_pos[2];                // 0x4
    /* 0x054 */ short cur_metro_pos;                  // 0x2
    /* 0x056 */ // 0x2 bytes padding
    /* 0x058 */ int now_music_data;                   // 0x4
    /* 0x05C */ int check_music_ct;                   // 0x4
    /* 0x060 */ unsigned long push_cont_timer;        // 0x8
    /* 0x068 */ unsigned char rs_cur;                 // 0x1
    /* 0x069 */ unsigned char ck_cur;                 // 0x1
    /* 0x06A */ unsigned char cur_chk_bar;            // 0x1
    /* 0x06B */ unsigned char check_mode_flg;         // 0x1
    /* 0x06C */ void *obj_p[10];                      // 0x28
    /* 0x094 */ void *ms_display;                     // 0x4
    /* 0x098 */ unsigned short tex_no[15];            // 0x1E
    /* 0x0B6 */ // 0x2 bytes padding
};

/* anon_18_159 -- @anon18, 0x4 bytes, tra_func.c (DIE 0x2D8729) */
struct anon_18_159 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_19_159 -- @anon19, 0x184 bytes, tra_func.c (DIE 0x2D8DCC) */
struct anon_19_159 {   // size 0x184
    /* 0x000 */ struct anon_15_159 line_a[8];         // 0x80
    /* 0x080 */ struct anon_15_159 line_b[8];         // 0x80
    /* 0x100 */ struct anon_15_159 line_c[8];         // 0x80
    /* 0x180 */ int num;                              // 0x4
};


/* variables (9) */
static int tr_turn_tbl[12];                                      /* @0x002C0E20 size 0x30 */
static struct anon_11_159 tr_bar_col[6];                         /* @0x002C0E70 size 0x18 */
struct anon_17_159 *trw;                                         /* @0x002DDDDC size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
unsigned int tr_arrow_clut_buff[256];                            /* @0x00722CF0 size 0x400 */
unsigned int tra_seq_buff_th_addr;                               /* @0x002DE57C size 0x4 */
unsigned int tra_seq_buff_addr;                                  /* @0x002DE580 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */

/* functions referenced (1) */
void tr_load_seq_th(void *);                                     /* @0x0027FD00 */

/* functions defined (14) */
static void tr_disp_number(float x, float y, float scale_x, int num, int deg, unsigned char bri, unsigned char alpha); /* 0x0027C1F0-0x0027C3B8 lines 1475-1503 */
void Tr_check_seq_panel_disp(unsigned char alpha);               /* 0x0027C3C0-0x0027C998 lines 1311-1463 */
void Tr_seq_panel_disp(unsigned char alpha, unsigned char style); /* 0x0027C9A0-0x0027CED8 lines 1169-1305 */
static void Tr_freeze_arrow_disp(float x, float y, int z, int dir, int h, int flg, unsigned char alpha); /* 0x0027CEE0-0x0027D2B8 lines 1078-1162 */
void Tr_disp_bar(int flg, unsigned char alpha, unsigned char level); /* 0x0027D2C0-0x0027D544 lines 1021-1069 */
void Tr_bar_disp_one(float sx, float sy, int w, int h, int pri, unsigned char alpha0, unsigned char level); /* 0x0027D550-0x0027E818 lines 872-1014 */
void Tr_disp_bar_number(short y, short num, short mode, unsigned char alpha); /* 0x0027E820-0x0027ECF0 lines 736-854 */
void Tr_disp_step_zone(unsigned char alpha, unsigned char style); /* 0x0027ECF0-0x0027EEA0 lines 687-729 */
void Tr_arrow_clut_anim_ck(int count);                           /* 0x0027EEA0-0x0027F7A0 lines 487-669 */
void Tr_arrow_clut_anim(int count);                              /* 0x0027F7A0-0x0027FC90 lines 347-481 */
void Tr_load_seq_th(int mode);                                   /* 0x0027FC90-0x0027FCF8 lines 328-336 */
static void tr_load_seq_th(void);                                /* 0x0027FD00-0x0027FEF0 lines 250-325 */
int Tr_load_seq(void);                                           /* 0x0027FEF0-0x00280080 lines 184-246 */
void Tr_set_g_game_w(void);                                      /* 0x00280080-0x0028064C lines 50-178 */

#endif /* DDR_UNIT_src_CS_train_tra_func_c_H */
