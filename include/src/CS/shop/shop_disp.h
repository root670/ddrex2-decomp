/*
 * C:\work2\usaex2\src\CS\shop\shop_disp.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x002533F0-0x00253AD8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_shop_shop_disp_c_H
#define DDR_UNIT_src_CS_shop_shop_disp_c_H

#include "types/G_SYS_W_.h"
#include "types/_CWS_WIN_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/tex_bind.h"

/* anonymous types (21) */

/* anon_0_127 -- @anon0, 0x10 bytes, shop_disp.c (DIE 0x22D9E5) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_0_127;

/* anon_1_127 -- @anon1, 0x8 bytes, shop_disp.c (DIE 0x22DAA5) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_1_127;

/* anon_2_127 -- @anon2, 0x10 bytes, shop_disp.c (DIE 0x22DC18) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_2_127;

/* anon_4_127 -- @anon4, 0x14 bytes, shop_disp.c (DIE 0x22F238) */
typedef struct {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
} anon_4_127;

/* anon_5_127 -- @anon5, 0x10 bytes, shop_disp.c (DIE 0x22F2F8) */
typedef struct {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
} anon_5_127;

/* anon_9_127 -- @anon9, 0x4 bytes, shop_disp.c (DIE 0x23123F) */
typedef struct {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
} anon_9_127;

/* anon_22_127 -- @anon22, 0x14 bytes, shop_disp.c (DIE 0x235A48) */
typedef struct {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
} anon_22_127;

/* anon_7_127 -- @anon7, 0x8 bytes, shop_disp.c (DIE 0x230AA5) */
typedef struct {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
} anon_7_127;

/* anon_6_127 -- @anon6, 0x518 bytes, shop_disp.c (DIE 0x22F4DD) */
typedef struct {   // size 0x518
    /* 0x000 */ unsigned char *free_mem_addr;         // 0x4
    /* 0x004 */ unsigned char *mv_data_addr;          // 0x4
    /* 0x008 */ unsigned char *shop_data_addr;        // 0x4
    /* 0x00C */ unsigned char *course_data_addr;      // 0x4
    /* 0x010 */ unsigned char *mess_data_addr;        // 0x4
    /* 0x014 */ unsigned char step;                   // 0x1
    /* 0x015 */ unsigned char step_s;                 // 0x1
    /* 0x016 */ unsigned char mess_str[512];          // 0x200
    /* 0x216 */ // 0x2 bytes padding
    /* 0x218 */ unsigned int syscnt;                  // 0x4
    /* 0x21C */ unsigned int syscnt0;                 // 0x4
    /* 0x220 */ char tab_cursor;                      // 0x1
    /* 0x221 */ char tab_cursor_new;                  // 0x1
    /* 0x222 */ char contents_cursor;                 // 0x1
    /* 0x223 */ char contents_cursor_new;             // 0x1
    /* 0x224 */ char contents_cursor_disp_top;        // 0x1
    /* 0x225 */ char contents_cursor_disp_top_new;    // 0x1
    /* 0x226 */ char tab_state;                       // 0x1
    /* 0x227 */ char cont_state;                      // 0x1
    /* 0x228 */ char cursor_anime;                    // 0x1
    /* 0x229 */ char cursor_anime_flag;               // 0x1
    /* 0x22A */ char confirm_cursor;                  // 0x1
    /* 0x22B */ char info_cursor;                     // 0x1
    /* 0x22C */ char info_list_disp;                  // 0x1
    /* 0x22D */ unsigned char is_disp_dancer;         // 0x1
    /* 0x22E */ signed char start_pid_first;          // 0x1
    /* 0x22F */ signed char start_pid;                // 0x1
    /* 0x230 */ unsigned int secret_list_num;         // 0x4
    /* 0x234 */ anon_9_127 secret_list[50];           // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ anon_5_127 text_w;                    // 0x10
    /* 0x310 */ anon_0_127 button_disp_w;             // 0x10
    /* 0x320 */ anon_2_127 fade_env;                  // 0x10
    /* 0x330 */ anon_22_127 pad_w;                    // 0x14
    /* 0x344 */ anon_7_127 mess_w;                    // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ anon_4_127 move_w[9];                 // 0xB4
    /* 0x510 */ anon_1_127 shop_rect;                 // 0x8
} anon_6_127;

/* anon_10_127 -- @anon10, 0x48 bytes, shop_disp.c (DIE 0x2312CA) */
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
} anon_10_127;

/* anon_14_127 -- @anon14, 0x4 bytes, shop_disp.c (DIE 0x234854) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_14_127;

/* anon_16_127 -- @anon16, 0x10 bytes, shop_disp.c (DIE 0x234D55) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_14_127 x0;                       // 0x4
    /* 0x004 */ anon_14_127 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_16_127;

/* anon_12_127 -- @anon12, 0x1C bytes, shop_disp.c (DIE 0x231FE2) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_14_127 x0;                       // 0x4
    /* 0x004 */ anon_14_127 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_12_127;

/* anon_13_127 -- @anon13, 0x24 bytes, shop_disp.c (DIE 0x2340F4) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_14_127 x0;                       // 0x4
    /* 0x004 */ anon_14_127 y0;                       // 0x4
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
} anon_13_127;

/* anon_15_127 -- @anon15, 0xD40 bytes, shop_disp.c (DIE 0x2348FA) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_15_127;

/* anon_17_127 -- @anon17, 0x14 bytes, shop_disp.c (DIE 0x234E76) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_17_127;

/* anon_18_127 -- @anon18, 0xC bytes, shop_disp.c (DIE 0x2350F9) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_18_127;

/* anon_19_127 -- @anon19, 0x68 bytes, shop_disp.c (DIE 0x23521C) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_14_127 x0;                       // 0x4
    /* 0x004 */ anon_14_127 y0;                       // 0x4
    /* 0x008 */ anon_14_127 x1;                       // 0x4
    /* 0x00C */ anon_14_127 y1;                       // 0x4
    /* 0x010 */ anon_14_127 x2;                       // 0x4
    /* 0x014 */ anon_14_127 y2;                       // 0x4
    /* 0x018 */ anon_14_127 x3;                       // 0x4
    /* 0x01C */ anon_14_127 y3;                       // 0x4
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
} anon_19_127;

/* anon_24_127 -- @anon24, 0x4 bytes, shop_disp.c (DIE 0x235D30) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_24_127;

/* anon_23_127 -- @anon23, 0x4 bytes, shop_disp.c (DIE 0x235CAD) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_24_127 s;                        // 0x4
} anon_23_127;

/* anon_25_127 -- @anon25, 0x12E0 bytes, shop_disp.c (DIE 0x235FAA) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_18_127 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_25_127;


/* variables (3) */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions defined (7) */
int shop_is_fade_off(void);                                      /* 0x002533F0-0x0025343C lines 527-534 */
void shop_fade_main(void);                                       /* 0x00253440-0x00253624 lines 496-523 */
void shop_fade_set(int type);                                    /* 0x00253630-0x00253690 lines 473-486 */
void shop_fade_out_init(void);                                   /* 0x00253690-0x002536B8 lines 464-468 */
void shop_fade_in_init(void);                                    /* 0x002536C0-0x002536E8 lines 456-460 */
void shop_fade_init(void);                                       /* 0x002536F0-0x00253728 lines 446-452 */
void shop_disp_text(unsigned char *str, int x, int y, int z, int br, int alpha, int width, int flg, int font, struct _CWS_WIN_W *winp); /* 0x00253730-0x00253AD8 lines 128-232 */

#endif /* DDR_UNIT_src_CS_shop_shop_disp_c_H */
