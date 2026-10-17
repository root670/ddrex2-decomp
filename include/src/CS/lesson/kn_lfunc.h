/*
 * C:\work2\usaex2\src\CS\lesson\kn_lfunc.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 12 functions, code 0x007F2880-0x007F3864
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_lesson_kn_lfunc_c_H
#define DDR_UNIT_src_CS_lesson_kn_lfunc_c_H

#include "types/_tag_cLesPlay.h"
#include "types/g_game_w.h"
#include "types/sequence.h"
#include "types/sq_standard.h"

/* anonymous types (13) */

/* anon_0_194 -- @anon0, 0x88 bytes, kn_lfunc.c (DIE 0x3617F3) */
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
} anon_0_194;

/* anon_2_194 -- @anon2, 0x14 bytes, kn_lfunc.c (DIE 0x362467) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short start_mct;                      // 0x2
    /* 0x006 */ short disp_ct;                        // 0x2
    /* 0x008 */ int pos;                              // 0x4
    /* 0x00C */ int move_type;                        // 0x4
    /* 0x010 */ int frame;                            // 0x4
} anon_2_194;

/* anon_3_194 -- @anon3, 0x8 bytes, kn_lfunc.c (DIE 0x36296B) */
typedef struct {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
} anon_3_194;

/* anon_4_194 -- @anon4, 0x10 bytes, kn_lfunc.c (DIE 0x3631DD) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned int beat_count;              // 0x4
    /* 0x004 */ short msg_num[4];                     // 0x8
    /* 0x00C */ short time;                           // 0x2
    /* 0x00E */ unsigned char msg_flg;                // 0x1
    /* 0x00F */ unsigned char pad[1];                 // 0x1
} anon_4_194;

/* anon_5_194 -- @anon5, 0x4 bytes, kn_lfunc.c (DIE 0x3634BC) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_5_194;

/* anon_6_194 -- @anon6, 0x10 bytes, kn_lfunc.c (DIE 0x363561) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_5_194 x0;                        // 0x4
    /* 0x004 */ anon_5_194 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_6_194;

/* anon_14_194 -- @anon14, 0x10 bytes, kn_lfunc.c (DIE 0x366445) */
typedef struct {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
} anon_14_194;

/* anon_7_194 -- @anon7, 0x40 bytes, kn_lfunc.c (DIE 0x36385B) */
typedef struct {   // size 0x40
    /* 0x000 */ anon_14_194 offset;                   // 0x10
    /* 0x010 */ anon_14_194 next_ofs;                 // 0x10
    /* 0x020 */ anon_14_194 move;                     // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03A */ short release;                        // 0x2
    /* 0x03C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_7_194;

/* anon_8_194 -- @anon8, 0x14 bytes, kn_lfunc.c (DIE 0x363A03) */
typedef struct {   // size 0x14
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00C */ int frame;                            // 0x4
    /* 0x010 */ int type;                             // 0x4
} anon_8_194;

/* anon_10_194 -- @anon10, 0x8 bytes, kn_lfunc.c (DIE 0x363F28) */
typedef struct {   // size 0x8
    /* 0x000 */ int beat_ct;                          // 0x4
    /* 0x004 */ short music_ct;                       // 0x2
    /* 0x006 */ // 0x2 bytes padding
} anon_10_194;

/* anon_13_194 -- @anon13, 0x10 bytes, kn_lfunc.c (DIE 0x366334) */
typedef struct {   // size 0x10
    /* 0x000 */ int ang;                              // 0x4
    /* 0x004 */ int pos;                              // 0x4
    /* 0x008 */ int ofs;                              // 0x4
    /* 0x00C */ int type;                             // 0x4
} anon_13_194;

/* anon_11_194 -- @anon11, 0x2C bytes, kn_lfunc.c (DIE 0x363FB5) */
typedef struct {   // size 0x2C
    /* 0x000 */ anon_13_194 state[2];                 // 0x20
    /* 0x020 */ unsigned int beat_count;              // 0x4
    /* 0x024 */ int start_mct;                        // 0x4
    /* 0x028 */ int frame;                            // 0x4
} anon_11_194;

/* anon_15_194 -- @anon15, 0x20 bytes, kn_lfunc.c (DIE 0x366550) */
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
} anon_15_194;


/* variables (21) */
static short finger_pos_tbl[9][2];                               /* @0x007FA650 size 0x24 */
int lesson_foot_pos_tbl[5][2];                                   /* @0x007FA680 size 0x28 */
int lesson_foot_offset_tbl[9][2];                                /* @0x007FA6B0 size 0x48 */
static short kn_e_rhythm_tbl[4];                                 /* not allocated size 0x8 */
static int value_begin_ct[7];                                    /* @0x007FB720 size 0x1C */
static int value_end_ct[7];                                      /* @0x007FB740 size 0x1C */
anon_15_194 kn_fin_w;                                            /* @0x007FC4C0 size 0x20 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_2_194 kn_finger_seq[50];                                    /* @0x007FC0D0 size 0x3E8 */
anon_0_194 kn_lesson_main_work;                                  /* @0x007FE860 size 0x88 */
anon_7_194 kn_touch_w[2];                                        /* @0x007FC4E0 size 0x80 */
anon_3_194 kn_msg_w;                                             /* @0x002DE618 size 0x8 */
unsigned char *kn_less_msg[];                                    /* @0x007FA180 */
anon_4_194 kn_msg_seq[50];                                       /* @0x007FBDB0 size 0x320 */
anon_7_194 kn_foot_w[2];                                         /* @0x007FE7E0 size 0x80 */
anon_8_194 kn_move_w;                                            /* @0x007FE7C0 size 0x14 */
anon_11_194 kn_foot_seq[200];                                    /* @0x007FC560 size 0x2260 */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002DDE84 size 0x4 */
anon_10_194 kn_l_timing_w[80];                                   /* @0x007FBB30 size 0x280 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (12) */
void kn_lfunc_finger_op(void);                                   /* 0x007F2880-0x007F2AC0 lines 838-860 */
void kn_lfunc_set_play_ct(void);                                 /* 0x007F2AC0-0x007F2BA0 lines 759-788 */
void kn_lfunc_set_msg_status(anon_4_194 *m_seq);                 /* 0x007F2BA0-0x007F2C50 lines 722-750 */
void kn_lfunc_set_foot_status(anon_7_194 *fw, anon_8_194 *mw);   /* 0x007F2C50-0x007F2DDC lines 682-710 */
void kn_lfunc_msg_op(void);                                      /* 0x007F2DE0-0x007F2EA8 lines 641-673 */
void kn_lfunc_set_foot_move(anon_7_194 *fw);                     /* 0x007F2EB0-0x007F30C0 lines 584-632 */
void kn_lfunc_foot_op(void);                                     /* 0x007F30C0-0x007F325C lines 535-573 */
void kn_lfunc_chk_timing(void);                                  /* 0x007F3260-0x007F34A8 lines 454-524 */
int kn_lfunc_chk_teach_mode(void);                               /* 0x007F34B0-0x007F3550 lines 420-438 */
void kn_lfunc_chk_clap(void);                                    /* 0x007F3550-0x007F35F8 lines 312-336 */
void kn_lfunc_chk_now_music(void);                               /* 0x007F3600-0x007F3624 lines 236-303 */
void kn_lfunc_set_head_data(void);                               /* 0x007F3630-0x007F3864 lines 199-224 */

#endif /* DDR_UNIT_src_CS_lesson_kn_lfunc_c_H */
