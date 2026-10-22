/*
 * C:\work2\usaex2\src\CS\train\tra_menu.c
 * MW MIPS C Compiler, overlay main; 16 functions, code 0x00273520-0x00276514
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
#ifndef DDR_UNIT_src_CS_train_tra_menu_c_H
#define DDR_UNIT_src_CS_train_tra_menu_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_tag_cCoCursor01.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/tex_bind.h"

/* anonymous types (7) */

/* anon_0_153 -- @anon0, 0x48 bytes, tra_menu.c (DIE 0x2A714B) */
typedef struct {   // size 0x48
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
} anon_0_153;

/* anon_1_153 -- @anon1, 0x44 bytes, tra_menu.c (DIE 0x2A73CD) */
typedef struct {   // size 0x44
    /* 0x000 */ unsigned char step[10];               // 0xA
    /* 0x00A */ // 0x2 bytes padding
    /* 0x00C */ float t[10];                          // 0x28
    /* 0x034 */ float bri_t;                          // 0x4
    /* 0x038 */ struct _tag_cCoCursor01 cur_w;        // 0xC
} anon_1_153;

/* anon_2_153 -- @anon2, 0x20 bytes, tra_menu.c (DIE 0x2A7684) */
typedef struct {   // size 0x20
    /* 0x000 */ struct _CWS_WIN_W *win;               // 0x4
    /* 0x004 */ unsigned char win_no;                 // 0x1
    /* 0x005 */ unsigned char kind;                   // 0x1
    /* 0x006 */ unsigned char alpha;                  // 0x1
    /* 0x007 */ // 0x1 bytes padding
    /* 0x008 */ float win_t;                          // 0x4
    /* 0x00C */ float dy;                             // 0x4
    /* 0x010 */ float t;                              // 0x4
    /* 0x014 */ struct _tag_cCoCursor01 cur_w;        // 0xC
} anon_2_153;

/* anon_4_153 -- @anon4, 0x24 bytes, tra_menu.c (DIE 0x2A825A) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
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
} anon_4_153;

/* anon_6_153 -- @anon6, 0x30 bytes, tra_menu.c (DIE 0x2A8F35) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
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
} anon_6_153;

/* anon_8_153 -- @anon8, 0xB8 bytes, tra_menu.c (DIE 0x2A943C) */
typedef struct {   // size 0xB8
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
} anon_8_153;

/* anon_10_153 -- @anon10, 0x24 bytes, tra_menu.c (DIE 0x2AA033) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ unsigned char r1;                     // 0x1
    /* 0x01D */ unsigned char g1;                     // 0x1
    /* 0x01E */ unsigned char b1;                     // 0x1
    /* 0x01F */ unsigned char a1;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
} anon_10_153;


/* variables (5) */
anon_8_153 *trw;                                                 /* @0x002DDDDC size 0x4 */
struct tex_bind tex_bind[375];                                   /* @0x0058C390 size 0x2904 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (16) */
static void tr_opt_line_disp(float y0, unsigned char alpha);     /* 0x00273520-0x002736D0 lines 1140-1163 */
static void asi_item_value_disp(float y0, unsigned char item_no, unsigned char kind, unsigned char alpha); /* 0x002736D0-0x0027399C lines 1081-1134 */
static void opt_item_value_disp(float y0, unsigned char item_no, unsigned char kind, unsigned char alpha); /* 0x002739A0-0x00273CEC lines 1014-1076 */
static void menu_item_value_disp(float dx, float y0, unsigned char item_no, unsigned char kind); /* 0x00273CF0-0x002743FC lines 882-1011 */
static void tr_update_opt_lr(int lr);                            /* 0x00274400-0x002745BC lines 834-876 */
static int tr_update_lr(void);                                   /* 0x002745C0-0x00274B3C lines 672-831 */
static int tr_menu_disap(void);                                  /* 0x00274B40-0x00274C7C lines 635-665 */
static int tr_menu_apper(void);                                  /* 0x00274C80-0x00274E50 lines 573-631 */
int TRObj_option_disp(void *wp);                                 /* 0x00274E50-0x00275128 lines 519-567 */
int TRObj_option_func(void *wp);                                 /* 0x00275130-0x00275198 lines 499-510 */
int TRObj_assist_disp(void *wp);                                 /* 0x002751A0-0x00275490 lines 436-494 */
int TRObj_assist_func(void *wp);                                 /* 0x00275490-0x002754F8 lines 419-430 */
int TRObj_menu_item_disp(void *wp);                              /* 0x00275500-0x00275C00 lines 300-414 */
int TRObj_menu_item_disap(void *wp);                             /* 0x00275C00-0x00275DAC lines 265-297 */
int TRObj_menu_item_apper(void *wp);                             /* 0x00275DB0-0x00275F3C lines 227-262 */
unsigned char Train_Menu(void);                                  /* 0x00275F40-0x00276514 lines 46-197 */

#endif /* DDR_UNIT_src_CS_train_tra_menu_c_H */
