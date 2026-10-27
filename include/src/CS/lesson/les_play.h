/*
 * C:\work2\usaex2\src\CS\lesson\les_play.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 10 functions, code 0x007F47D0-0x007F63F0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_CS_lesson_les_play_c_H
#define DDR_UNIT_src_CS_lesson_les_play_c_H

#include "types/G_DRAW_W_.h"
#include "types/G_SYS_W_.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cLes.h"
#include "types/_tag_cLesPlay.h"
#include "types/g_each_w.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/play_mode.h"
#include "types/play_w.h"
#include "types/sequence.h"
#include "types/sq_standard.h"

/* anonymous types (16) */

/* anon_0_197 -- @anon0, 0x88 bytes, les_play.c (DIE 0x37171D) */
typedef struct {   // size 0x88
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
} anon_0_197;

/* anon_32_197 -- @anon32, 0x10 bytes, les_play.c (DIE 0x37B466) */
typedef struct {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
} anon_32_197;

/* anon_3_197 -- @anon3, 0x40 bytes, les_play.c (DIE 0x372A42) */
typedef struct {   // size 0x40
    /* 0x000 */ anon_32_197 offset;                   // 0x10
    /* 0x010 */ anon_32_197 next_ofs;                 // 0x10
    /* 0x020 */ anon_32_197 move;                     // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03A */ short release;                        // 0x2
    /* 0x03C */ // 0x4 bytes padding
} __attribute__((aligned(16))) anon_3_197;

/* anon_4_197 -- @anon4, 0x14 bytes, les_play.c (DIE 0x373554) */
typedef struct {   // size 0x14
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00C */ int frame;                            // 0x4
    /* 0x010 */ int type;                             // 0x4
} anon_4_197;

/* anon_5_197 -- @anon5, 0x10 bytes, les_play.c (DIE 0x373909) */
typedef struct {   // size 0x10
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00C */ int type;                             // 0x4
} anon_5_197;

/* anon_7_197 -- @anon7, 0x8 bytes, les_play.c (DIE 0x373B00) */
typedef struct {   // size 0x8
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ // 0x2 bytes padding
} anon_7_197;

/* anon_8_197 -- @anon8, 0x2C bytes, les_play.c (DIE 0x373BAA) */
typedef struct {   // size 0x2C
    /* 0x000 */ anon_5_197 state[2];                  // 0x20
    /* 0x020 */ unsigned int beat_count;              // 0x4
    /* 0x024 */ int start_mct;                        // 0x4
    /* 0x028 */ int frame;                            // 0x4
} anon_8_197;

/* anon_9_197 -- @anon9, 0x8 bytes, les_play.c (DIE 0x373DA3) */
typedef struct {   // size 0x8
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ unsigned char step;                   // 0x1
    /* 0x007 */ unsigned char type;                   // 0x1
} anon_9_197;

/* anon_11_197 -- @anon11, 0x20 bytes, les_play.c (DIE 0x375266) */
typedef struct {   // size 0x20
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
} anon_11_197;

/* anon_12_197 -- @anon12, 0x14 bytes, les_play.c (DIE 0x375446) */
typedef struct {   // size 0x14
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ short msg_no[4];                      // 0x8
    /* 0x00E */ short time;                           // 0x2
    /* 0x010 */ short disp_flg;                       // 0x2
    /* 0x012 */ short pad;                            // 0x2
} anon_12_197;

/* anon_14_197 -- @anon14, 0xC bytes, les_play.c (DIE 0x375C26) */
typedef struct {   // size 0xC
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ char pos;                             // 0x1
    /* 0x007 */ char ofs;                             // 0x1
    /* 0x008 */ char time;                            // 0x1
    /* 0x009 */ char type;                            // 0x1
    /* 0x00A */ short rotate;                         // 0x2
} anon_14_197;

/* anon_15_197 -- @anon15, 0x14 bytes, les_play.c (DIE 0x376062) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short start_mct;                      // 0x2
    /* 0x006 */ short disp_ct;                        // 0x2
    /* 0x008 */ int pos;                              // 0x4
    /* 0x00C */ int move_type;                        // 0x4
    /* 0x010 */ int frame;                            // 0x4
} anon_15_197;

/* anon_16_197 -- @anon16, 0xC bytes, les_play.c (DIE 0x376269) */
typedef struct {   // size 0xC
    /* 0x000 */ int frame;                            // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ short time;                           // 0x2
    /* 0x008 */ short speed;                          // 0x2
    /* 0x00A */ char type;                            // 0x1
    /* 0x00B */ char pos;                             // 0x1
} anon_16_197;

/* anon_18_197 -- @anon18, 0x8 bytes, les_play.c (DIE 0x378259) */
typedef struct {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
} anon_18_197;

/* anon_21_197 -- @anon21, 0x10 bytes, les_play.c (DIE 0x378990) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short msg_num[4];                     // 0x8
    /* 0x00C */ short time;                           // 0x2
    /* 0x00E */ unsigned char msg_flg;                // 0x1
    /* 0x00F */ unsigned char pad[1];                 // 0x1
} anon_21_197;

/* anon_29_197 -- @anon29, 0x8 bytes, les_play.c (DIE 0x37A90D) */
typedef struct {   // size 0x8
    /* 0x000 */ int beat_ct;                          // 0x4
    /* 0x004 */ short music_ct;                       // 0x2
    /* 0x006 */ // 0x2 bytes padding
} anon_29_197;


/* variables (24) */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002DDE84 size 0x4 */
static unsigned int LesTimingTable1[6];                          /* @0x007FA770 size 0x18 */
static unsigned int LesTimingTable2[6];                          /* @0x007FA790 size 0x18 */
static unsigned int LesTimingTable3[6];                          /* @0x007FA7B0 size 0x18 */
unsigned char kn_l_section_num_tbl[4];                           /* not allocated size 0x4 */
static int les_play_music[3];                                    /* @0x007FA7C8 size 0xC */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_15_197 kn_finger_seq[50];                                   /* @0x007FC0D0 size 0x3E8 */
anon_8_197 kn_foot_seq[200];                                     /* @0x007FC560 size 0x2260 */
anon_21_197 kn_msg_seq[50];                                      /* @0x007FBDB0 size 0x320 */
anon_0_197 kn_lesson_main_work;                                  /* @0x007FE860 size 0x88 */
struct _tag_cLes *pLes;                                          /* @0x002DDE80 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct G_DRAW_W_ g_draw_w;                                       /* @0x005F52E0 size 0xDE8 */
anon_29_197 kn_l_timing_w[80];                                   /* @0x007FBB30 size 0x280 */
anon_18_197 kn_msg_w;                                            /* @0x002DE618 size 0x8 */
anon_11_197 kn_fin_w;                                            /* @0x007FC4C0 size 0x20 */
anon_3_197 kn_touch_w[2];                                        /* @0x007FC4E0 size 0x80 */
anon_4_197 kn_move_w;                                            /* @0x007FE7C0 size 0x14 */
anon_3_197 kn_foot_w[2];                                         /* @0x007FE7E0 size 0x80 */
static struct _tag_cLesPlay _pLesPlay;                           /* @0x007FE8F0 size 0x54 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (10) */
static void lesson_data_setup(unsigned int l_data_address);      /* 0x007F47D0-0x007F4D40 lines 1175-1409 */
void make_ssq_at_lesson(unsigned int ind_address, unsigned int l_data_address, unsigned int ssq_address); /* 0x007F4D40-0x007F50B4 lines 1008-1161 */
static void disp_step(void);                                     /* 0x007F50C0-0x007F51BC lines 909-971 */
static int play_main(void);                                      /* 0x007F51C0-0x007F5628 lines 711-868 */
static int intro_play(void);                                     /* 0x007F5630-0x007F5750 lines 661-706 */
static void play_init(void);                                     /* 0x007F5750-0x007F5D54 lines 416-655 */
int Update_LesPlay(void);                                        /* 0x007F5D60-0x007F5D98 lines 401-407 */
int View_LesPlay(void);                                          /* 0x007F5DA0-0x007F5DA8 lines 395-395 */
int Control_LesPlay(void);                                       /* 0x007F5DB0-0x007F6044 lines 307-389 */
int Init_LesPlay(void);                                          /* 0x007F6050-0x007F63F0 lines 157-303 */

#endif /* DDR_UNIT_src_CS_lesson_les_play_c_H */
