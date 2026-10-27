/*
 * C:\work2\usaex2\src\CS\lesson\kn_ldisp.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 12 functions, code 0x007F0080-0x007F15E8
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
#ifndef DDR_UNIT_src_CS_lesson_kn_ldisp_c_H
#define DDR_UNIT_src_CS_lesson_kn_ldisp_c_H

#include "types/_tag_cLes.h"
#include "types/_tag_cLesPlay.h"

/* anonymous types (14) */

/* anon_0_191 -- @anon0, 0x30 bytes, kn_ldisp.c (DIE 0x35A979) */
typedef struct {   // size 0x30
    /* 0x000 */ float m[3][3];                        // 0x24
    /* 0x024 */ float t[3];                           // 0xC
} anon_0_191;

/* anon_1_191 -- @anon1, 0x10 bytes, kn_ldisp.c (DIE 0x35ACF5) */
typedef struct {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
} anon_1_191;

/* anon_2_191 -- @anon2, 0x10 bytes, kn_ldisp.c (DIE 0x35AD90) */
typedef struct {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float w;                              // 0x4
    /* 0x00C */ float h;                              // 0x4
} anon_2_191;

/* anon_3_191 -- @anon3, 0x8 bytes, kn_ldisp.c (DIE 0x35AE27) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_3_191;

/* anon_4_191 -- @anon4, 0x14 bytes, kn_ldisp.c (DIE 0x35AEBE) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char *msg;                   // 0x4
    /* 0x004 */ anon_3_191 *win;                      // 0x4
    /* 0x008 */ short msg_num;                        // 0x2
    /* 0x00A */ short font_size;                      // 0x2
    /* 0x00C */ int ot;                               // 0x4
    /* 0x010 */ int bright;                           // 0x4
} anon_4_191;

/* anon_7_191 -- @anon7, 0x4 bytes, kn_ldisp.c (DIE 0x35BB2E) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_7_191;

/* anon_5_191 -- @anon5, 0x24 bytes, kn_ldisp.c (DIE 0x35AFD5) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_7_191 x0;                        // 0x4
    /* 0x004 */ anon_7_191 y0;                        // 0x4
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
} anon_5_191;

/* anon_6_191 -- @anon6, 0x60 bytes, kn_ldisp.c (DIE 0x35B953) */
typedef struct {   // size 0x60
    /* 0x000 */ anon_1_191 ang;                       // 0x10
    /* 0x010 */ anon_1_191 center;                    // 0x10
    /* 0x020 */ anon_2_191 obj;                       // 0x10
    /* 0x030 */ anon_2_191 tex;                       // 0x10
    /* 0x040 */ unsigned int col;                     // 0x4
    /* 0x044 */ unsigned short clut;                  // 0x2
    /* 0x046 */ unsigned short tpage;                 // 0x2
    /* 0x048 */ int ot;                               // 0x4
    /* 0x04C */ int scr_z;                            // 0x4
    /* 0x050 */ int alpha;                            // 0x4
    /* 0x054 */ int tex_id;                           // 0x4
    /* 0x058 */ // 0x8 bytes padding
} __attribute__((aligned(16))) anon_6_191;

/* anon_8_191 -- @anon8, 0x68 bytes, kn_ldisp.c (DIE 0x35BBD3) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_7_191 x0;                        // 0x4
    /* 0x004 */ anon_7_191 y0;                        // 0x4
    /* 0x008 */ anon_7_191 x1;                        // 0x4
    /* 0x00C */ anon_7_191 y1;                        // 0x4
    /* 0x010 */ anon_7_191 x2;                        // 0x4
    /* 0x014 */ anon_7_191 y2;                        // 0x4
    /* 0x018 */ anon_7_191 x3;                        // 0x4
    /* 0x01C */ anon_7_191 y3;                        // 0x4
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
} anon_8_191;

/* anon_9_191 -- @anon9, 0x40 bytes, kn_ldisp.c (DIE 0x35C4F1) */
typedef struct {   // size 0x40
    /* 0x000 */ anon_1_191 offset;                    // 0x10
    /* 0x010 */ anon_1_191 next_ofs;                  // 0x10
    /* 0x020 */ anon_1_191 move;                      // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03A */ short release;                        // 0x2
    /* 0x03C */ // 0x4 bytes padding
} __attribute__((aligned(16))) anon_9_191;

/* anon_10_191 -- @anon10, 0x88 bytes, kn_ldisp.c (DIE 0x35C651) */
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
} anon_10_191;

/* anon_11_191 -- @anon11, 0x20 bytes, kn_ldisp.c (DIE 0x35D17C) */
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
} anon_11_191;

/* anon_12_191 -- @anon12, 0x48 bytes, kn_ldisp.c (DIE 0x35D414) */
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
} anon_12_191;

/* anon_13_191 -- @anon13, 0x8 bytes, kn_ldisp.c (DIE 0x35D697) */
typedef struct {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
} anon_13_191;


/* variables (16) */
static anon_3_191 sect_win;                                      /* not allocated size 0x8 */
static anon_3_191 msg_win;                                       /* not allocated size 0x8 */
static anon_3_191 msg_rect;                                      /* @0x002DDE78 size 0x8 */
static short foot_panel_pos_tbl[4][6];                           /* @0x007FA100 size 0x30 */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002DDE84 size 0x4 */
struct _tag_cLes *pLes;                                          /* @0x002DDE80 size 0x4 */
anon_9_191 kn_foot_w[2];                                         /* @0x007FE7E0 size 0x80 */
anon_9_191 kn_touch_w[2];                                        /* @0x007FC4E0 size 0x80 */
anon_11_191 kn_fin_w;                                            /* @0x007FC4C0 size 0x20 */
short font_anime_pos_y;                                          /* @0x002DE604 size 0x2 */
short font_anime_pos_x;                                          /* @0x002DE608 size 0x2 */
short kn_msg_num;                                                /* @0x002DE5FC size 0x2 */
unsigned int cur_font_pos;                                       /* @0x002DE600 size 0x4 */
unsigned char *kn_less_msg[];                                    /* @0x007FA180 */
anon_13_191 kn_msg_w;                                            /* @0x002DE618 size 0x8 */
anon_10_191 kn_lesson_main_work;                                 /* @0x007FE860 size 0x88 */

/* functions defined (12) */
void kn_ldisp_start_exit(void);                                  /* 0x007F0080-0x007F0120 lines 896-948 */
void kn_ldisp_foot_stage(unsigned int col);                      /* 0x007F0120-0x007F034C lines 814-858 */
void kn_ldisp_foot_touch(void);                                  /* 0x007F0350-0x007F057C lines 770-805 */
static void kn_set_ft4_gte(anon_6_191 *disp);                    /* 0x007F0580-0x007F09B0 lines 559-690 */
void kn_ldisp_face_obj(void);                                    /* 0x007F09B0-0x007F0B40 lines 520-551 */
void kn_ldisp_foot_obj(void);                                    /* 0x007F0B40-0x007F0F34 lines 459-512 */
void kn_ldisp_now_teach(void);                                   /* 0x007F0F40-0x007F1110 lines 402-448 */
void kn_ldisp_kanji_font_init(void);                             /* 0x007F1110-0x007F1124 lines 368-369 */
void kn_ldisp_reset_font_emi(void);                              /* 0x007F1130-0x007F1138 lines 361-361 */
void kn_ldisp_message(int flg, int _bright, int _ot);            /* 0x007F1140-0x007F12C8 lines 298-353 */
static int kn_kanji_font_emi(anon_4_191 *font);                  /* 0x007F12D0-0x007F148C lines 173-258 */
void kn_ldisp_lesson_play(void);                                 /* 0x007F1490-0x007F15E8 lines 118-158 */

#endif /* DDR_UNIT_src_CS_lesson_kn_ldisp_c_H */
