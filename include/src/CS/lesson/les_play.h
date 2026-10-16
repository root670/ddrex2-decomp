/*
 * C:\work\usam2\src\CS\lesson\les_play.c
 * MW MIPS C Compiler, overlay main; 10 functions, code 0x00220740-0x00222338
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_les_play_c_H
#define DDR_UNIT_src_CS_lesson_les_play_c_H

#include "types/G_DRAW_W_.h"
#include "types/G_SYS_W_.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cLes.h"
#include "types/_tag_cLesPlay.h"
#include "types/g_each_w.h"
#include "types/g_game_w.h"
#include "types/play_mode.h"
#include "types/play_w.h"
#include "types/sequence.h"
#include "types/sq_standard.h"

/* anonymous types (21) */

/* anon_5_4 -- @anon5, 0x10 bytes, les_play.c (DIE 0xE717) */
struct anon_5_4 {   // size 0x10
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00C */ int type;                             // 0x4
};

/* anon_0_4 -- @anon0, 0x2C bytes, les_play.c (DIE 0xCC22) */
struct anon_0_4 {   // size 0x2C
    /* 0x000 */ struct anon_5_4 state[2];             // 0x20
    /* 0x020 */ unsigned int beat_count;              // 0x4
    /* 0x024 */ int start_mct;                        // 0x4
    /* 0x028 */ int frame;                            // 0x4
};

/* anon_1_4 -- @anon1, 0x10 bytes, les_play.c (DIE 0xCE6D) */
struct anon_1_4 {   // size 0x10
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short msg_num[4];                     // 0x8
    /* 0x00C */ short time;                           // 0x2
    /* 0x00E */ unsigned char msg_flg;                // 0x1
    /* 0x00F */ unsigned char pad[1];                 // 0x1
};

/* anon_2_4 -- @anon2, 0x14 bytes, les_play.c (DIE 0xD17E) */
struct anon_2_4 {   // size 0x14
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short start_mct;                      // 0x2
    /* 0x006 */ short disp_ct;                        // 0x2
    /* 0x008 */ int pos;                              // 0x4
    /* 0x00C */ int move_type;                        // 0x4
    /* 0x010 */ int frame;                            // 0x4
};

/* anon_3_4 -- @anon3, 0x14 bytes, les_play.c (DIE 0xDC43) */
struct anon_3_4 {   // size 0x14
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00C */ int frame;                            // 0x4
    /* 0x010 */ int type;                             // 0x4
};

/* anon_4_4 -- @anon4, 0x8 bytes, les_play.c (DIE 0xDE91) */
struct anon_4_4 {   // size 0x8
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ // 0x2 bytes padding
};

/* anon_6_4 -- @anon6, 0x8 bytes, les_play.c (DIE 0xE825) */
struct anon_6_4 {   // size 0x8
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ unsigned char step;                   // 0x1
    /* 0x007 */ unsigned char type;                   // 0x1
};

/* anon_7_4 -- @anon7, 0x4 bytes, les_play.c (DIE 0xEAD1) */
struct anon_7_4 {   // size 0x4
    /* 0x000 */ unsigned int p : 24;                  // bits 0..23
    /* 0x003 */ unsigned char num : 8;                // bits 0..7
};

/* anon_8_4 -- @anon8, 0x88 bytes, les_play.c (DIE 0xEB42) */
struct anon_8_4 {   // size 0x88
    /* 0x000 */ unsigned int end_bc;                  // 0x4
    /* 0x004 */ unsigned int lesson_col[3];           // 0xC
    /* 0x010 */ int mode_chng_ct;                     // 0x4
    /* 0x014 */ int mode_chng_deg;                    // 0x4
    /* 0x018 */ int sect_menu_ct;                     // 0x4
    /* 0x01C */ int lv_menu_ct[3];                    // 0xC
    /* 0x028 */ short start_mc;                       // 0x2
    /* 0x02A */ short finish_mc;                      // 0x2
    /* 0x02C */ short cur_mc;                         // 0x2
    /* 0x02E */ short end_mc;                         // 0x2
    /* 0x030 */ short iron_deg[2];                    // 0x4
    /* 0x034 */ short end_msg_ct;                     // 0x2
    /* 0x036 */ short cur_note;                       // 0x2
    /* 0x038 */ short old_bar[4];                     // 0x8
    /* 0x040 */ short cur_clap_pos;                   // 0x2
    /* 0x042 */ short miss_num;                       // 0x2
    /* 0x044 */ short next_foot;                      // 0x2
    /* 0x046 */ short next_finger;                    // 0x2
    /* 0x048 */ short next_msg;                       // 0x2
    /* 0x04A */ short info_ct;                        // 0x2
    /* 0x04C */ short info_flg;                       // 0x2
    /* 0x04E */ short first_msg_ct;                   // 0x2
    /* 0x050 */ short obi_deg;                        // 0x2
    /* 0x052 */ short screen_deg;                     // 0x2
    /* 0x054 */ short disp_ct;                        // 0x2
    /* 0x056 */ short music_wait_ct;                  // 0x2
    /* 0x058 */ unsigned char music_num;              // 0x1
    /* 0x059 */ unsigned char music_start;            // 0x1
    /* 0x05A */ unsigned char music_end;              // 0x1
    /* 0x05B */ unsigned char music_repeat;           // 0x1
    /* 0x05C */ unsigned char music_flg;              // 0x1
    /* 0x05D */ unsigned char music_step;             // 0x1
    /* 0x05E */ unsigned char shade_col[4];           // 0x4
    /* 0x062 */ unsigned char fade_col;               // 0x1
    /* 0x063 */ unsigned char fade_step;              // 0x1
    /* 0x064 */ unsigned char input_flg;              // 0x1
    /* 0x065 */ unsigned char lesson_level;           // 0x1
    /* 0x066 */ unsigned char now_section;            // 0x1
    /* 0x067 */ unsigned char sel_info_ct;            // 0x1
    /* 0x068 */ unsigned char speaker_ct[4];          // 0x4
    /* 0x06C */ unsigned char iron_wait_ct;           // 0x1
    /* 0x06D */ unsigned char result;                 // 0x1
    /* 0x06E */ unsigned char rhythm_flg;             // 0x1
    /* 0x06F */ unsigned char emi_anime_flg;          // 0x1
    /* 0x070 */ unsigned char no_play_flg;            // 0x1
    /* 0x071 */ unsigned char is_stream;              // 0x1
    /* 0x072 */ unsigned char teach_flg;              // 0x1
    /* 0x073 */ unsigned char teach_ct;               // 0x1
    /* 0x074 */ unsigned char clear_flg;              // 0x1
    /* 0x075 */ unsigned char clear_wait_ct;          // 0x1
    /* 0x076 */ unsigned char face_type;              // 0x1
    /* 0x077 */ unsigned char dead_ct[6];             // 0x6
    /* 0x07D */ unsigned char clap_ct;                // 0x1
    /* 0x07E */ unsigned char play_fade_ct;           // 0x1
    /* 0x07F */ unsigned char now_loop_num;           // 0x1
    /* 0x080 */ unsigned char tempo;                  // 0x1
    /* 0x081 */ unsigned char button_ct[2];           // 0x2
    /* 0x083 */ unsigned char wipe_mode;              // 0x1
    /* 0x084 */ unsigned char msg_line;               // 0x1
    /* 0x085 */ unsigned char msg_pos;                // 0x1
    /* 0x086 */ unsigned char tmp_mem;                // 0x1
    /* 0x087 */ // 0x1 bytes padding
};

/* anon_9_4 -- @anon9, 0x28 bytes, les_play.c (DIE 0xF57B) */
struct anon_9_4 {   // size 0x28
    /* 0x000 */ unsigned long length;                 // 0x8
    /* 0x008 */ struct anon_7_4 *org;                 // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long offset;                 // 0x8
    /* 0x018 */ unsigned long point;                  // 0x8
    /* 0x020 */ struct anon_7_4 *tag;                 // 0x4
    /* 0x024 */ // 0x4 bytes padding
};

/* anon_10_4 -- @anon10, 0x20 bytes, les_play.c (DIE 0xF680) */
struct anon_10_4 {   // size 0x20
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short base_x;                         // 0x2
    /* 0x006 */ short base_y;                         // 0x2
    /* 0x008 */ short next_x;                         // 0x2
    /* 0x00A */ short next_y;                         // 0x2
    /* 0x00C */ short disp_ct;                        // 0x2
    /* 0x00E */ short counter;                        // 0x2
    /* 0x010 */ int pos;                              // 0x4
    /* 0x014 */ int disp_flg;                         // 0x4
    /* 0x018 */ int move_flg;                         // 0x4
    /* 0x01C */ int frame;                            // 0x4
};

/* anon_11_4 -- @anon11, 0x14 bytes, les_play.c (DIE 0x10157) */
struct anon_11_4 {   // size 0x14
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ short msg_no[4];                      // 0x8
    /* 0x00E */ short time;                           // 0x2
    /* 0x010 */ short disp_flg;                       // 0x2
    /* 0x012 */ short pad;                            // 0x2
};

/* anon_12_4 -- @anon12, 0xC bytes, les_play.c (DIE 0x10696) */
struct anon_12_4 {   // size 0xC
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ char pos;                             // 0x1
    /* 0x007 */ char ofs;                             // 0x1
    /* 0x008 */ char time;                            // 0x1
    /* 0x009 */ char type;                            // 0x1
    /* 0x00A */ short rotate;                         // 0x2
};

/* anon_13_4 -- @anon13, 0xC bytes, les_play.c (DIE 0x10CFC) */
struct anon_13_4 {   // size 0xC
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ short time;                           // 0x2
    /* 0x008 */ short speed;                          // 0x2
    /* 0x00A */ char type;                            // 0x1
    /* 0x00B */ char pos;                             // 0x1
};

/* anon_14_4 -- @anon14, 0x8 bytes, les_play.c (DIE 0x10E07) */
struct anon_14_4 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_15_4 -- @anon15, 0x8 bytes, les_play.c (DIE 0x114E9) */
struct anon_15_4 {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
};

/* anon_16_4 -- @anon16, 0x4 bytes, les_play.c (DIE 0x120A1) */
struct anon_16_4 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_17_4 -- @anon17, 0x10 bytes, les_play.c (DIE 0x122A0) */
struct anon_17_4 {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
};

/* anon_18_4 -- @anon18, 0xCC8 bytes, les_play.c (DIE 0x1258A) */
struct anon_18_4 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_19_4 -- @anon19, 0x8 bytes, les_play.c (DIE 0x14921) */
struct anon_19_4 {   // size 0x8
    /* 0x000 */ int beat_ct;                          // 0x4
    /* 0x004 */ short music_ct;                       // 0x2
    /* 0x006 */ // 0x2 bytes padding
};

/* anon_20_4 -- @anon20, 0x40 bytes, les_play.c (DIE 0x1498A) */
struct anon_20_4 {   // size 0x40
    /* 0x000 */ struct anon_17_4 offset;              // 0x10
    /* 0x010 */ struct anon_17_4 next_ofs;            // 0x10
    /* 0x020 */ struct anon_17_4 move;                // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03A */ short release;                        // 0x2
    /* 0x03C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
};


/* variables (23) */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002A2134 size 0x4 */
static unsigned int LesTimingTable1[6];                          /* @0x0027EC50 size 0x18 */
static unsigned int LesTimingTable2[6];                          /* @0x0027EC70 size 0x18 */
static unsigned int LesTimingTable3[6];                          /* @0x0027EC90 size 0x18 */
unsigned char kn_l_section_num_tbl[4];                           /* not allocated size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xAB544 */
struct anon_2_4 kn_finger_seq[50];                               /* @0x006AFE20 size 0x3E8 */
struct anon_0_4 kn_foot_seq[200];                                /* @0x006B02B0 size 0x2260 */
struct anon_1_4 kn_msg_seq[50];                                  /* @0x006AFB00 size 0x320 */
struct anon_8_4 kn_lesson_main_work;                             /* @0x006B25B0 size 0x88 */
struct _tag_cLes *pLes;                                          /* @0x002A2128 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x0063D5A0 size 0x90 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
struct G_DRAW_W_ g_draw_w;                                       /* @0x005875C0 size 0xDE8 */
struct anon_19_4 kn_l_timing_w[80];                              /* @0x006AF880 size 0x280 */
struct anon_15_4 kn_msg_w;                                       /* @0x002A2A88 size 0x8 */
struct anon_10_4 kn_fin_w;                                       /* @0x006B0210 size 0x20 */
struct anon_20_4 kn_touch_w[2];                                  /* @0x006B0230 size 0x80 */
struct anon_3_4 kn_move_w;                                       /* @0x006B2510 size 0x14 */
struct anon_20_4 kn_foot_w[2];                                   /* @0x006B2530 size 0x80 */
static struct _tag_cLesPlay _pLesPlay;                           /* @0x006B2640 size 0x54 */
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

#endif /* DDR_UNIT_src_CS_lesson_les_play_c_H */
