/*
 * C:\work2\usaex2\src\CS\lesson\kn_lstep.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 3 functions, code 0x007F44F0-0x007F47C4
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
#ifndef DDR_UNIT_src_CS_lesson_kn_lstep_c_H
#define DDR_UNIT_src_CS_lesson_kn_lstep_c_H

#include "types/_tag_cLesPlay.h"

/* anonymous types (5) */

/* anon_0_196 -- @anon0, 0x88 bytes, kn_lstep.c (DIE 0x36FC7F) */
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
} anon_0_196;

/* anon_1_196 -- @anon1, 0x20 bytes, kn_lstep.c (DIE 0x37063D) */
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
} anon_1_196;

/* anon_2_196 -- @anon2, 0x8 bytes, kn_lstep.c (DIE 0x370864) */
typedef struct {   // size 0x8
    /* 0x000 */ short msg_num;                        // 0x2
    /* 0x002 */ unsigned short disp_ct;               // 0x2
    /* 0x004 */ unsigned short timer;                 // 0x2
    /* 0x006 */ unsigned char disp_flg;               // 0x1
    /* 0x007 */ char pad[1];                          // 0x1
} anon_2_196;

/* anon_4_196 -- @anon4, 0x10 bytes, kn_lstep.c (DIE 0x370F13) */
typedef struct {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
} anon_4_196;

/* anon_3_196 -- @anon3, 0x40 bytes, kn_lstep.c (DIE 0x370DB3) */
typedef struct {   // size 0x40
    /* 0x000 */ anon_4_196 offset;                    // 0x10
    /* 0x010 */ anon_4_196 next_ofs;                  // 0x10
    /* 0x020 */ anon_4_196 move;                      // 0x10
    /* 0x030 */ short ang;                            // 0x2
    /* 0x032 */ short next_ang;                       // 0x2
    /* 0x034 */ short ang_deg;                        // 0x2
    /* 0x036 */ short move_flg;                       // 0x2
    /* 0x038 */ short pos;                            // 0x2
    /* 0x03A */ short release;                        // 0x2
    /* 0x03C */ // 0x4 bytes padding
} __attribute__((aligned(16))) anon_3_196;


/* variables (9) */
anon_3_196 kn_touch_w[2];                                        /* @0x007FC4E0 size 0x80 */
anon_1_196 kn_fin_w;                                             /* @0x007FC4C0 size 0x20 */
anon_2_196 kn_msg_w;                                             /* @0x002DE618 size 0x8 */
anon_3_196 kn_foot_w[2];                                         /* @0x007FE7E0 size 0x80 */
int lesson_foot_offset_tbl[9][2];                                /* @0x007FA6B0 size 0x48 */
anon_0_196 kn_lesson_main_work;                                  /* @0x007FE860 size 0x88 */
struct _tag_cLesPlay *pLesPlay;                                  /* @0x002DDE84 size 0x4 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (3) */
int kn_lstep_lesson_play(void);                                  /* 0x007F44F0-0x007F455C lines 142-272 */
void kn_lstep_lesson_play_init(void);                            /* 0x007F4560-0x007F4724 lines 65-132 */
void kn_lstep_main_init(void);                                   /* 0x007F4730-0x007F47C4 lines 43-57 */

#endif /* DDR_UNIT_src_CS_lesson_kn_lstep_c_H */
