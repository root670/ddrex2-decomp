/*
 * C:\work2\usaex2\src\CS\info\infoshow.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 24 functions, code 0x007F5070-0x007F9D18
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_info_infoshow_c_H
#define DDR_UNIT_src_CS_info_infoshow_c_H

#include "types/G_SYS_W_.h"
#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cInfo.h"
#include "types/_tag_cInfoScrBar.h"
#include "types/_tag_cInfoshow.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"
#include "types/sequence.h"
#include "types/sq_standard.h"
#include "types/tex_bind.h"

/* anonymous types (19) */

/* anon_0_185 -- @anon0, 0x18 bytes, infoshow.c (DIE 0x340087) */
typedef struct {   // size 0x18
    /* 0x000 */ unsigned long arrow_clut_ct;          // 0x8
    /* 0x008 */ short ny_music_num;                   // 0x2
    /* 0x00A */ short scroll_ct;                      // 0x2
    /* 0x00C */ unsigned char scroll_spd;             // 0x1
    /* 0x00D */ unsigned char special_bar;            // 0x1
    /* 0x00E */ unsigned char adjust_bar;             // 0x1
    /* 0x00F */ unsigned char bar_start;              // 0x1
    /* 0x010 */ unsigned char bar_end;                // 0x1
    /* 0x011 */ unsigned char bar_max;                // 0x1
    /* 0x012 */ unsigned char c_bar_max;              // 0x1
    /* 0x013 */ unsigned char c_bar_adjust;           // 0x1
    /* 0x014 */ unsigned char train_alpha0;           // 0x1
    /* 0x015 */ unsigned char player;                 // 0x1
    /* 0x016 */ unsigned char level;                  // 0x1
    /* 0x017 */ unsigned char dummy;                  // 0x1
} anon_0_185;

/* anon_2_185 -- @anon2, 0x10 bytes, infoshow.c (DIE 0x340420) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_2_185;

/* anon_6_185 -- @anon6, 0x4 bytes, infoshow.c (DIE 0x342CC9) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_6_185;

/* anon_3_185 -- @anon3, 0x1C bytes, infoshow.c (DIE 0x3410E8) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_6_185 x0;                        // 0x4
    /* 0x004 */ anon_6_185 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_3_185;

/* anon_4_185 -- @anon4, 0x10 bytes, infoshow.c (DIE 0x341240) */
typedef struct {   // size 0x10
    /* 0x000 */ int flag;                             // 0x4
    /* 0x004 */ int music_id;                         // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int beat_count;                       // 0x4
} anon_4_185;

/* anon_5_185 -- @anon5, 0x24 bytes, infoshow.c (DIE 0x341AC1) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_6_185 x0;                        // 0x4
    /* 0x004 */ anon_6_185 y0;                        // 0x4
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
} anon_5_185;

/* anon_7_185 -- @anon7, 0x30 bytes, infoshow.c (DIE 0x3433B8) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_6_185 x0;                        // 0x4
    /* 0x004 */ anon_6_185 y0;                        // 0x4
    /* 0x008 */ anon_6_185 x1;                        // 0x4
    /* 0x00C */ anon_6_185 y1;                        // 0x4
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
} anon_7_185;

/* anon_8_185 -- @anon8, 0x10 bytes, infoshow.c (DIE 0x3439A4) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_6_185 x0;                        // 0x4
    /* 0x004 */ anon_6_185 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_8_185;

/* anon_10_185 -- @anon10, 0x68 bytes, infoshow.c (DIE 0x343DB5) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_6_185 x0;                        // 0x4
    /* 0x004 */ anon_6_185 y0;                        // 0x4
    /* 0x008 */ anon_6_185 x1;                        // 0x4
    /* 0x00C */ anon_6_185 y1;                        // 0x4
    /* 0x010 */ anon_6_185 x2;                        // 0x4
    /* 0x014 */ anon_6_185 y2;                        // 0x4
    /* 0x018 */ anon_6_185 x3;                        // 0x4
    /* 0x01C */ anon_6_185 y3;                        // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
} anon_10_185;

/* anon_12_185 -- @anon12, 0x8 bytes, infoshow.c (DIE 0x344DD0) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_12_185;

/* anon_13_185 -- @anon13, 0xC bytes, infoshow.c (DIE 0x3450CD) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_13_185;

/* anon_14_185 -- @anon14, 0x12E0 bytes, infoshow.c (DIE 0x347630) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_13_185 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_14_185;

/* anon_15_185 -- @anon15, 0xD40 bytes, infoshow.c (DIE 0x3477D3) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_15_185;

/* anon_16_185 -- @anon16, 0x14 bytes, infoshow.c (DIE 0x347B00) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_16_185;

/* anon_17_185 -- @anon17, 0x4 bytes, infoshow.c (DIE 0x347DDD) */
typedef struct {   // size 0x4
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
} anon_17_185;

/* anon_21_185 -- @anon21, 0x4 bytes, infoshow.c (DIE 0x34848C) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_21_185;

/* anon_20_185 -- @anon20, 0x4 bytes, infoshow.c (DIE 0x3483E3) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_21_185 s;                        // 0x4
} anon_20_185;

/* anon_22_185 -- @anon22, 0x34 bytes, infoshow.c (DIE 0x3487E2) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_6_185 x0;                        // 0x4
    /* 0x004 */ anon_6_185 y0;                        // 0x4
    /* 0x008 */ anon_6_185 x1;                        // 0x4
    /* 0x00C */ anon_6_185 y1;                        // 0x4
    /* 0x010 */ anon_6_185 x2;                        // 0x4
    /* 0x014 */ anon_6_185 y2;                        // 0x4
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
} anon_22_185;

/* anon_24_185 -- @anon24, 0x48 bytes, infoshow.c (DIE 0x348E50) */
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
} anon_24_185;


/* variables (11) */
static unsigned char csxx24_color_table[16];                     /* not allocated size 0x10 */
static unsigned char csxx20_color_table[16];                     /* not allocated size 0x10 */
struct _tag_cInfoshow *pInfoshow;                                /* @0x002DDE6C size 0x4 */
anon_4_185 test_ex_arrow_data[30];                               /* @0x00800240 size 0x1E0 */
int test_ending_list_data[16];                                   /* @0x00800420 size 0x40 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cInfo *pInfo;                                        /* @0x002DDE54 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
unsigned int info_arrow_clut_buff[256];                          /* @0x008078C0 size 0x400 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
static struct _tag_cInfoshow _pInfoshow;                         /* @0x00807CC0 size 0x94 */

/* functions defined (24) */
static void info_extra_arrow_init(void);                         /* 0x007F5070-0x007F516C lines 2918-2951 */
static void info_tdisp_sequence_panel(int alpha);                /* 0x007F5170-0x007F5700 lines 2764-2915 */
static void TrDispBarMenu(void);                                 /* 0x007F5700-0x007F59C0 lines 2689-2754 */
static void TrBarDisp(float sx, float sy, int w, int h, int pri); /* 0x007F59C0-0x007F5FB0 lines 2572-2677 */
static void info_tfunc_arrow_clut_anim(void);                    /* 0x007F5FB0-0x007F6440 lines 2428-2566 */
static int info_tfunc_load_seq(void);                            /* 0x007F6440-0x007F65D4 lines 2357-2422 */
static void info_tfunc_set_g_game_w(void);                       /* 0x007F65E0-0x007F67B8 lines 2170-2348 */
static void TrFreezeArrowDisp(float x, float y, int z, int dir, int h, int flg); /* 0x007F67C0-0x007F6B68 lines 2077-2159 */
void draw_ending_list_item(void);                                /* 0x007F6B70-0x007F725C lines 1833-2005 */
void select_ending_list_item(void);                              /* 0x007F7260-0x007F73A8 lines 1811-1828 */
void draw_dance_master_item(void);                               /* 0x007F73B0-0x007F7918 lines 1712-1809 */
void init_dance_master_item(void);                               /* 0x007F7920-0x007F79AC lines 1704-1710 */
void select_dance_master_item(void);                             /* 0x007F79B0-0x007F7B6C lines 1680-1702 */
static void draw_question_no(float x, float y, int alpha, int no); /* 0x007F7B70-0x007F7DEC lines 1581-1627 */
static void draw_music_banner(float x, float y, int alpha, float rate); /* 0x007F7DF0-0x007F808C lines 1525-1579 */
static void init_thumbnail(int infotxt_num);                     /* 0x007F8090-0x007F8160 lines 1140-1177 */
static void init_bar(void);                                      /* 0x007F8160-0x007F82D4 lines 997-1043 */
static void control_move(void);                                  /* 0x007F82E0-0x007F86D4 lines 895-990 */
void update_Infoshow(void);                                      /* 0x007F86E0-0x007F8754 lines 857-870 */
void draw_Infoshow(void);                                        /* 0x007F8760-0x007F9380 lines 414-852 */
static void control_loop(void);                                  /* 0x007F9380-0x007F9728 lines 285-380 */
static void init(void);                                          /* 0x007F9730-0x007F9A8C lines 206-283 */
int main_Infoshow(void);                                         /* 0x007F9A90-0x007F9CE4 lines 161-204 */
void init_Infoshow(void);                                        /* 0x007F9CF0-0x007F9D18 lines 150-156 */

#endif /* DDR_UNIT_src_CS_info_infoshow_c_H */
