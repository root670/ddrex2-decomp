/*
 * C:\work\usam2\src\CS\lesson\kn_ldisp.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x00223610-0x00224E14
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_kn_ldisp_c_H
#define DDR_UNIT_src_CS_lesson_kn_ldisp_c_H

#include "types/_tag_cLes.h"
#include "types/_tag_cLesPlay.h"

/* anonymous types (14) */

/* anon_0_7 -- @anon0, 0x20 bytes, kn_ldisp.c (DIE 0x1D5AF) */
struct anon_0_7 {   // size 0x20
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

/* anon_10_7 -- @anon10, 0x10 bytes, kn_ldisp.c (DIE 0x1F824) */
struct anon_10_7 {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
};

/* anon_13_7 -- @anon13, 0x10 bytes, kn_ldisp.c (DIE 0x1FB5F) */
struct anon_13_7 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float w;                              // 0x4
    /* 0x00C */ float h;                              // 0x4
};

/* anon_1_7 -- @anon1, 0x60 bytes, kn_ldisp.c (DIE 0x1D76A) */
struct anon_1_7 {   // size 0x60
    /* 0x000 */ struct anon_10_7 ang;                 // 0x10
    /* 0x010 */ struct anon_10_7 center;              // 0x10
    /* 0x020 */ struct anon_13_7 obj;                 // 0x10
    /* 0x030 */ struct anon_13_7 tex;                 // 0x10
    /* 0x040 */ unsigned int col;                     // 0x4
    /* 0x044 */ unsigned short clut;                  // 0x2
    /* 0x046 */ unsigned short tpage;                 // 0x2
    /* 0x048 */ int ot;                               // 0x4
    /* 0x04C */ int scr_z;                            // 0x4
    /* 0x050 */ int alpha;                            // 0x4
    /* 0x054 */ int tex_id;                           // 0x4
    /* 0x058 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_2_7 -- @anon2, 0x88 bytes, kn_ldisp.c (DIE 0x1DC1C) */
struct anon_2_7 {   // size 0x88
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

/* anon_6_7 -- @anon6, 0x4 bytes, kn_ldisp.c (DIE 0x1EC1F) */
union anon_6_7 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_7 -- @anon3, 0x24 bytes, kn_ldisp.c (DIE 0x1E8BA) */
struct anon_3_7 {   // size 0x24
    /* 0x000 */ union anon_6_7 x0;                    // 0x4
    /* 0x004 */ union anon_6_7 y0;                    // 0x4
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

/* anon_4_7 -- @anon4, 0x8 bytes, kn_ldisp.c (DIE 0x1EA4E) */
struct anon_4_7 {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
};

/* anon_5_7 -- @anon5, 0x8 bytes, kn_ldisp.c (DIE 0x1EB88) */
struct anon_5_7 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_7_7 -- @anon7, 0x68 bytes, kn_ldisp.c (DIE 0x1ECC6) */
struct anon_7_7 {   // size 0x68
    /* 0x000 */ union anon_6_7 x0;                    // 0x4
    /* 0x004 */ union anon_6_7 y0;                    // 0x4
    /* 0x008 */ union anon_6_7 x1;                    // 0x4
    /* 0x00C */ union anon_6_7 y1;                    // 0x4
    /* 0x010 */ union anon_6_7 x2;                    // 0x4
    /* 0x014 */ union anon_6_7 y2;                    // 0x4
    /* 0x018 */ union anon_6_7 x3;                    // 0x4
    /* 0x01C */ union anon_6_7 y3;                    // 0x4
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
};

/* anon_8_7 -- @anon8, 0x14 bytes, kn_ldisp.c (DIE 0x1F09D) */
struct anon_8_7 {   // size 0x14
    /* 0x000 */ unsigned char *msg;                   // 0x4
    /* 0x004 */ struct anon_5_7 *win;                 // 0x4
    /* 0x008 */ short msg_num;                        // 0x2
    /* 0x00A */ short font_size;                      // 0x2
    /* 0x00C */ int ot;                               // 0x4
    /* 0x010 */ int bright;                           // 0x4
};

/* anon_9_7 -- @anon9, 0x48 bytes, kn_ldisp.c (DIE 0x1F1DB) */
struct anon_9_7 {   // size 0x48
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

/* anon_11_7 -- @anon11, 0x30 bytes, kn_ldisp.c (DIE 0x1F90A) */
struct anon_11_7 {   // size 0x30
    /* 0x000 */ float m[3][3];                        // 0x24
    /* 0x024 */ float t[3];                           // 0xC
};

/* anon_12_7 -- @anon12, 0x40 bytes, kn_ldisp.c (DIE 0x1F9FE) */
struct anon_12_7 {   // size 0x40
    /* 0x000 */ struct anon_10_7 offset;              // 0x10
    /* 0x010 */ struct anon_10_7 next_ofs;            // 0x10
    /* 0x020 */ struct anon_10_7 move;                // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03A */ short release;                        // 0x2
    /* 0x03C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
};


/* variables (16) */
static struct anon_5_7 sect_win;                                 /* not allocated size 0x8 */
static struct anon_5_7 msg_win;                                  /* not allocated size 0x8 */
static struct anon_5_7 msg_rect;                                 /* @0x002A2138 size 0x8 */
static short foot_panel_pos_tbl[4][6];                           /* @0x0027ED60 size 0x30 */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002A2134 size 0x4 */
struct _tag_cLes *pLes;                                          /* @0x002A2128 size 0x4 */
struct anon_12_7 kn_foot_w[2];                                   /* @0x006B2530 size 0x80 */
struct anon_12_7 kn_touch_w[2];                                  /* @0x006B0230 size 0x80 */
struct anon_0_7 kn_fin_w;                                        /* @0x006B0210 size 0x20 */
short font_anime_pos_y;                                          /* @0x002A2A98 size 0x2 */
short font_anime_pos_x;                                          /* @0x002A2A9C size 0x2 */
short kn_msg_num;                                                /* @0x002A2A90 size 0x2 */
unsigned int cur_font_pos;                                       /* @0x002A2A94 size 0x4 */
unsigned char *LesStrDataTbl[];                                  /* @0x0027F260 */
struct anon_4_7 kn_msg_w;                                        /* @0x002A2A88 size 0x8 */
struct anon_2_7 kn_lesson_main_work;                             /* @0x006B25B0 size 0x88 */

/* functions defined (14) */
void kn_ldisp_start_exit(void);                                  /* 0x00223610-0x002236B0 lines 971-1023 */
void kn_ldisp_back(unsigned int col, int flg);                   /* 0x002236B0-0x00223770 lines 950-966 */
void kn_ldisp_foot_stage(void);                                  /* 0x00223770-0x002239BC lines 897-945 */
void kn_ldisp_foot_touch(void);                                  /* 0x002239C0-0x00223BEC lines 835-888 */
static void kn_set_ft4_gte(struct anon_1_7 *disp);               /* 0x00223BF0-0x00224020 lines 621-752 */
void kn_ldisp_face_obj(void);                                    /* 0x00224020-0x002241B8 lines 580-613 */
void kn_ldisp_foot_obj(void);                                    /* 0x002241C0-0x002245B0 lines 509-572 */
void kn_ldisp_now_teach(void);                                   /* 0x002245B0-0x00224784 lines 454-498 */
void kn_ldisp_play_msg_win(int _bright, int _alpha, int _ot);    /* 0x00224790-0x00224838 lines 362-445 */
void kn_ldisp_kanji_font_init(void);                             /* 0x00224840-0x00224854 lines 350-351 */
void kn_ldisp_reset_font_emi(void);                              /* 0x00224860-0x00224868 lines 343-343 */
void kn_ldisp_message(int flg, int _bright, int _ot);            /* 0x00224870-0x00224A0C lines 280-335 */
static int kn_kanji_font_emi(struct anon_8_7 *font);             /* 0x00224A10-0x00224BD0 lines 164-240 */
void kn_ldisp_lesson_play(void);                                 /* 0x00224BD0-0x00224E14 lines 116-149 */

#endif /* DDR_UNIT_src_CS_lesson_kn_ldisp_c_H */
