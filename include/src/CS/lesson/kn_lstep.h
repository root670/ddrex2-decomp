/*
 * C:\work\usam2\src\CS\lesson\kn_lstep.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x00222340-0x00222614
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _tag_cLesPlay;

/* types (1) */
struct _tag_cLesPlay {   // size 0x54
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int start_beat_count;                 // 0x4
    /* 0x00C */ int start_music_count;                // 0x4
    /* 0x010 */ int end_beat_count;                   // 0x4
    /* 0x014 */ int repeat_max;                       // 0x4
    /* 0x018 */ int repeat_num;                       // 0x4
    /* 0x01C */ int demonstration_flag;               // 0x4
    /* 0x020 */ int demonstration_alpha;              // 0x4
    /* 0x024 */ int obi_wipe_mode;                    // 0x4
    /* 0x028 */ int obi_wipe_speed;                   // 0x4
    /* 0x02C */ int pass_flag;                        // 0x4
    /* 0x030 */ int force_exit_flag;                  // 0x4
    /* 0x034 */ int closing_count;                    // 0x4
    /* 0x038 */ int end_count;                        // 0x4
    /* 0x03C */ int s_counter;                        // 0x4
    /* 0x040 */ int p_counter;                        // 0x4
    /* 0x044 */ int p_flag;                           // 0x4
    /* 0x048 */ int status_disp_flag;                 // 0x4
    /* 0x04C */ int hbota_step;                       // 0x4
    /* 0x050 */ int hbota_bright;                     // 0x4
};

/* variables (9) */
struct @anon0 kn_touch_w[2];                                     /* @0x006B0230 size 0x80 */
struct @anon3 kn_fin_w;                                          /* @0x006B0210 size 0x20 */
struct @anon4 kn_msg_w;                                          /* @0x002A2A88 size 0x8 */
struct @anon0 kn_foot_w[2];                                      /* @0x006B2530 size 0x80 */
int lesson_foot_offset_tbl[9][2];                                /* @0x0027ED10 size 0x48 */
struct @anon1 kn_lesson_main_work;                               /* @0x006B25B0 size 0x88 */
_tag_cLesPlay *pLesPlay;                                         /* @0x002A2134 size 0x4 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (3) */
int kn_lstep_lesson_play(void);                                  /* 0x00222340-0x002223AC lines 142-272 */
void kn_lstep_lesson_play_init(void);                            /* 0x002223B0-0x00222574 lines 65-132 */
void kn_lstep_main_init(void);                                   /* 0x00222580-0x00222614 lines 43-57 */
