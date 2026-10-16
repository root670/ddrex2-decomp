/*
 * C:\work\usam2\src\CS\lesson\kn_lstep.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x00222340-0x00222614
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_kn_lstep_c_H
#define DDR_UNIT_src_CS_lesson_kn_lstep_c_H

#include "types/_tag_cLesPlay.h"

/* anonymous types (5) */

/* anon_2_5 -- @anon2, 0x10 bytes, kn_lstep.c (DIE 0x16d2d) */
struct anon_2_5 {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00c */ float vw;                             // 0x4
};

/* anon_0_5 -- @anon0, 0x40 bytes, kn_lstep.c (DIE 0x16233) */
struct anon_0_5 {   // size 0x40
    /* 0x000 */ struct anon_2_5 offset;               // 0x10
    /* 0x010 */ struct anon_2_5 next_ofs;             // 0x10
    /* 0x020 */ struct anon_2_5 move;                 // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03a */ short release;                        // 0x2
    /* 0x03c */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_1_5 -- @anon1, 0x88 bytes, kn_lstep.c (DIE 0x163b9) */
struct anon_1_5 {   // size 0x88
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

/* anon_3_5 -- @anon3, 0x20 bytes, kn_lstep.c (DIE 0x16dc8) */
struct anon_3_5 {   // size 0x20
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

/* anon_4_5 -- @anon4, 0x8 bytes, kn_lstep.c (DIE 0x17039) */
struct anon_4_5 {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
};


/* variables (9) */
struct anon_0_5 kn_touch_w[2];                                   /* @0x006b0230 size 0x80 */
struct anon_3_5 kn_fin_w;                                        /* @0x006b0210 size 0x20 */
struct anon_4_5 kn_msg_w;                                        /* @0x002a2a88 size 0x8 */
struct anon_0_5 kn_foot_w[2];                                    /* @0x006b2530 size 0x80 */
int lesson_foot_offset_tbl[9][2];                                /* @0x0027ed10 size 0x48 */
struct anon_1_5 kn_lesson_main_work;                             /* @0x006b25b0 size 0x88 */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002a2134 size 0x4 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (3) */
int kn_lstep_lesson_play(void);                                  /* 0x00222340-0x002223ac lines 142-272 */
void kn_lstep_lesson_play_init(void);                            /* 0x002223b0-0x00222574 lines 65-132 */
void kn_lstep_main_init(void);                                   /* 0x00222580-0x00222614 lines 43-57 */

#endif /* DDR_UNIT_src_CS_lesson_kn_lstep_c_H */
