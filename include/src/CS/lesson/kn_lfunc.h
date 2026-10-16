/*
 * C:\work\usam2\src\CS\lesson\kn_lfunc.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x00222620-0x0022360c
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_kn_lfunc_c_H
#define DDR_UNIT_src_CS_lesson_kn_lfunc_c_H

#include "types/_tag_cLesPlay.h"
#include "types/g_game_w.h"
#include "types/sequence.h"
#include "types/sq_standard.h"

/* anonymous types (12) */

/* anon_0_6 -- @anon0, 0x14 bytes, kn_lfunc.c (DIE 0x177e9) */
struct anon_0_6 {   // size 0x14
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00c */ int frame;                            // 0x4
    /* 0x010 */ int type;                             // 0x4
};

/* anon_1_6 -- @anon1, 0x88 bytes, kn_lfunc.c (DIE 0x178cf) */
struct anon_1_6 {   // size 0x88
    /* 0x000 */ unsigned int end_bc;                  // 0x4
    /* 0x004 */ unsigned int lesson_col[3];           // 0xc
    /* 0x010 */ int mode_chng_ct;                     // 0x4
    /* 0x014 */ int mode_chng_deg;                    // 0x4
    /* 0x018 */ int sect_menu_ct;                     // 0x4
    /* 0x01c */ int lv_menu_ct[3];                    // 0xc
    /* 0x028 */ short start_mc;                       // 0x2
    /* 0x02a */ short finish_mc;                      // 0x2
    /* 0x02c */ short cur_mc;                         // 0x2
    /* 0x02e */ short end_mc;                         // 0x2
    /* 0x030 */ short iron_deg[2];                    // 0x4
    /* 0x034 */ short end_msg_ct;                     // 0x2
    /* 0x036 */ short cur_note;                       // 0x2
    /* 0x038 */ short old_bar[4];                     // 0x8
    /* 0x040 */ short cur_clap_pos;                   // 0x2
    /* 0x042 */ short miss_num;                       // 0x2
    /* 0x044 */ short next_foot;                      // 0x2
    /* 0x046 */ short next_finger;                    // 0x2
    /* 0x048 */ short next_msg;                       // 0x2
    /* 0x04a */ short info_ct;                        // 0x2
    /* 0x04c */ short info_flg;                       // 0x2
    /* 0x04e */ short first_msg_ct;                   // 0x2
    /* 0x050 */ short obi_deg;                        // 0x2
    /* 0x052 */ short screen_deg;                     // 0x2
    /* 0x054 */ short disp_ct;                        // 0x2
    /* 0x056 */ short music_wait_ct;                  // 0x2
    /* 0x058 */ unsigned char music_num;              // 0x1
    /* 0x059 */ unsigned char music_start;            // 0x1
    /* 0x05a */ unsigned char music_end;              // 0x1
    /* 0x05b */ unsigned char music_repeat;           // 0x1
    /* 0x05c */ unsigned char music_flg;              // 0x1
    /* 0x05d */ unsigned char music_step;             // 0x1
    /* 0x05e */ unsigned char shade_col[4];           // 0x4
    /* 0x062 */ unsigned char fade_col;               // 0x1
    /* 0x063 */ unsigned char fade_step;              // 0x1
    /* 0x064 */ unsigned char input_flg;              // 0x1
    /* 0x065 */ unsigned char lesson_level;           // 0x1
    /* 0x066 */ unsigned char now_section;            // 0x1
    /* 0x067 */ unsigned char sel_info_ct;            // 0x1
    /* 0x068 */ unsigned char speaker_ct[4];          // 0x4
    /* 0x06c */ unsigned char iron_wait_ct;           // 0x1
    /* 0x06d */ unsigned char result;                 // 0x1
    /* 0x06e */ unsigned char rhythm_flg;             // 0x1
    /* 0x06f */ unsigned char emi_anime_flg;          // 0x1
    /* 0x070 */ unsigned char no_play_flg;            // 0x1
    /* 0x071 */ unsigned char is_stream;              // 0x1
    /* 0x072 */ unsigned char teach_flg;              // 0x1
    /* 0x073 */ unsigned char teach_ct;               // 0x1
    /* 0x074 */ unsigned char clear_flg;              // 0x1
    /* 0x075 */ unsigned char clear_wait_ct;          // 0x1
    /* 0x076 */ unsigned char face_type;              // 0x1
    /* 0x077 */ unsigned char dead_ct[6];             // 0x6
    /* 0x07d */ unsigned char clap_ct;                // 0x1
    /* 0x07e */ unsigned char play_fade_ct;           // 0x1
    /* 0x07f */ unsigned char now_loop_num;           // 0x1
    /* 0x080 */ unsigned char tempo;                  // 0x1
    /* 0x081 */ unsigned char button_ct[2];           // 0x2
    /* 0x083 */ unsigned char wipe_mode;              // 0x1
    /* 0x084 */ unsigned char msg_line;               // 0x1
    /* 0x085 */ unsigned char msg_pos;                // 0x1
    /* 0x086 */ unsigned char tmp_mem;                // 0x1
    /* 0x087 */ // 0x1 bytes padding
};

/* anon_2_6 -- @anon2, 0x10 bytes, kn_lfunc.c (DIE 0x18312) */
struct anon_2_6 {   // size 0x10
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00c */ int type;                             // 0x4
};

/* anon_3_6 -- @anon3, 0x2c bytes, kn_lfunc.c (DIE 0x189d4) */
struct anon_3_6 {   // size 0x2c
    /* 0x000 */ struct anon_2_6 state[2];             // 0x20
    /* 0x020 */ unsigned int beat_count;              // 0x4
    /* 0x024 */ int start_mct;                        // 0x4
    /* 0x028 */ int frame;                            // 0x4
};

/* anon_9_6 -- @anon9, 0x10 bytes, kn_lfunc.c (DIE 0x1a1e0) */
struct anon_9_6 {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00c */ float vw;                             // 0x4
};

/* anon_4_6 -- @anon4, 0x40 bytes, kn_lfunc.c (DIE 0x18a86) */
struct anon_4_6 {   // size 0x40
    /* 0x000 */ struct anon_9_6 offset;               // 0x10
    /* 0x010 */ struct anon_9_6 next_ofs;             // 0x10
    /* 0x020 */ struct anon_9_6 move;                 // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03a */ short release;                        // 0x2
    /* 0x03c */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_5_6 -- @anon5, 0x14 bytes, kn_lfunc.c (DIE 0x19459) */
struct anon_5_6 {   // size 0x14
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short start_mct;                      // 0x2
    /* 0x006 */ short disp_ct;                        // 0x2
    /* 0x008 */ int pos;                              // 0x4
    /* 0x00c */ int move_type;                        // 0x4
    /* 0x010 */ int frame;                            // 0x4
};

/* anon_6_6 -- @anon6, 0x20 bytes, kn_lfunc.c (DIE 0x19551) */
struct anon_6_6 {   // size 0x20
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short base_x;                         // 0x2
    /* 0x006 */ short base_y;                         // 0x2
    /* 0x008 */ short next_x;                         // 0x2
    /* 0x00a */ short next_y;                         // 0x2
    /* 0x00c */ short disp_ct;                        // 0x2
    /* 0x00e */ short counter;                        // 0x2
    /* 0x010 */ int pos;                              // 0x4
    /* 0x014 */ int disp_flg;                         // 0x4
    /* 0x018 */ int move_flg;                         // 0x4
    /* 0x01c */ int frame;                            // 0x4
};

/* anon_7_6 -- @anon7, 0x10 bytes, kn_lfunc.c (DIE 0x1982d) */
struct anon_7_6 {   // size 0x10
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short msg_num[4];                     // 0x8
    /* 0x00c */ short time;                           // 0x2
    /* 0x00e */ unsigned char msg_flg;                // 0x1
    /* 0x00f */ unsigned char pad[1];                 // 0x1
};

/* anon_8_6 -- @anon8, 0x8 bytes, kn_lfunc.c (DIE 0x19d56) */
struct anon_8_6 {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
};

/* anon_10_6 -- @anon10, 0x4 bytes, kn_lfunc.c (DIE 0x1a6d5) */
struct anon_10_6 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_11_6 -- @anon11, 0x8 bytes, kn_lfunc.c (DIE 0x1be31) */
struct anon_11_6 {   // size 0x8
    /* 0x000 */ int beat_ct;                          // 0x4
    /* 0x004 */ short music_ct;                       // 0x2
    /* 0x006 */ // 0x2 bytes padding
};


/* variables (21) */
static short finger_pos_tbl[9][2];                               /* @0x0027ecb0 size 0x24 */
int lesson_foot_pos_tbl[5][2];                                   /* @0x0027ece0 size 0x28 */
int lesson_foot_offset_tbl[9][2];                                /* @0x0027ed10 size 0x48 */
static short kn_e_rhythm_tbl[4];                                 /* not allocated size 0x8 */
static int value_begin_ct[6];                                    /* @0x00294fa0 size 0x18 */
static int value_end_ct[6];                                      /* @0x00294fc0 size 0x18 */
struct anon_6_6 kn_fin_w;                                        /* @0x006b0210 size 0x20 */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xab544 */
struct anon_5_6 kn_finger_seq[50];                               /* @0x006afe20 size 0x3e8 */
struct anon_1_6 kn_lesson_main_work;                             /* @0x006b25b0 size 0x88 */
struct anon_4_6 kn_touch_w[2];                                   /* @0x006b0230 size 0x80 */
struct anon_8_6 kn_msg_w;                                        /* @0x002a2a88 size 0x8 */
unsigned char *LesStrDataTbl[];                                  /* @0x0027f260 */
struct anon_7_6 kn_msg_seq[50];                                  /* @0x006afb00 size 0x320 */
struct anon_4_6 kn_foot_w[2];                                    /* @0x006b2530 size 0x80 */
struct anon_0_6 kn_move_w;                                       /* @0x006b2510 size 0x14 */
struct anon_3_6 kn_foot_seq[200];                                /* @0x006b02b0 size 0x2260 */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002a2134 size 0x4 */
struct anon_11_6 kn_l_timing_w[80];                              /* @0x006af880 size 0x280 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (12) */
void kn_lfunc_finger_op(void);                                   /* 0x00222620-0x00222860 lines 836-858 */
void kn_lfunc_set_play_ct(void);                                 /* 0x00222860-0x00222940 lines 757-786 */
void kn_lfunc_set_msg_status(struct anon_7_6 *m_seq);            /* 0x00222940-0x00222a10 lines 717-748 */
void kn_lfunc_set_foot_status(struct anon_4_6 *fw, struct anon_0_6 *mw); /* 0x00222a10-0x00222b9c lines 680-708 */
void kn_lfunc_msg_op(void);                                      /* 0x00222ba0-0x00222c68 lines 639-671 */
void kn_lfunc_set_foot_move(struct anon_4_6 *fw);                /* 0x00222c70-0x00222e80 lines 582-630 */
void kn_lfunc_foot_op(void);                                     /* 0x00222e80-0x0022301c lines 533-571 */
void kn_lfunc_chk_timing(void);                                  /* 0x00223020-0x00223260 lines 451-522 */
int kn_lfunc_chk_teach_mode(void);                               /* 0x00223260-0x00223300 lines 419-437 */
void kn_lfunc_chk_clap(void);                                    /* 0x00223300-0x002233a8 lines 311-335 */
void kn_lfunc_chk_now_music(void);                               /* 0x002233b0-0x002233d4 lines 236-302 */
void kn_lfunc_set_head_data(void);                               /* 0x002233e0-0x0022360c lines 199-224 */

#endif /* DDR_UNIT_src_CS_lesson_kn_lfunc_c_H */
