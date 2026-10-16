/*
 * C:\work2\usaex2\src\CS\lesson\les_sel_sec.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 11 functions, code 0x007F8120-0x007FA0B0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_les_sel_sec_c_H
#define DDR_UNIT_src_CS_lesson_les_sel_sec_c_H

#include "types/_LES_RECT.h"
#include "types/_tag_cLes.h"
#include "types/_tag_cLesSectionBannerData.h"
#include "types/_tag_cLesSelSection.h"
#include "types/_tag_cStatusBarLesSelSection.h"

/* anonymous types (8) */

/* anon_0_199 -- @anon0, 0x48 bytes, les_sel_sec.c (DIE 0x382F9C) */
struct anon_0_199 {   // size 0x48
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

/* anon_1_199 -- @anon1, 0x30 bytes, les_sel_sec.c (DIE 0x38341B) */
struct anon_1_199 {   // size 0x30
    /* 0x000 */ int t;                                // 0x4
    /* 0x004 */ int t_max;                            // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ float sx;                             // 0x4
    /* 0x014 */ float sy;                             // 0x4
    /* 0x018 */ float fx;                             // 0x4
    /* 0x01C */ float fy;                             // 0x4
    /* 0x020 */ float ofs_x;                          // 0x4
    /* 0x024 */ float ofs_y;                          // 0x4
    /* 0x028 */ unsigned char alpha;                  // 0x1
    /* 0x029 */ unsigned char salpha;                 // 0x1
    /* 0x02A */ unsigned char Mode;                   // 0x1
    /* 0x02B */ unsigned char step;                   // 0x1
    /* 0x02C */ unsigned char flag;                   // 0x1
    /* 0x02D */ unsigned char dummy;                  // 0x1
    /* 0x02E */ // 0x2 bytes padding
};

/* anon_2_199 -- @anon2, 0x8 bytes, les_sel_sec.c (DIE 0x3838EF) */
struct anon_2_199 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_3_199 -- @anon3, 0x88 bytes, les_sel_sec.c (DIE 0x383986) */
struct anon_3_199 {   // size 0x88
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

/* anon_4_199 -- @anon4, 0x4 bytes, les_sel_sec.c (DIE 0x384A38) */
union anon_4_199 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_5_199 -- @anon5, 0x30 bytes, les_sel_sec.c (DIE 0x384ADD) */
struct anon_5_199 {   // size 0x30
    /* 0x000 */ union anon_4_199 x0;                  // 0x4
    /* 0x004 */ union anon_4_199 y0;                  // 0x4
    /* 0x008 */ union anon_4_199 x1;                  // 0x4
    /* 0x00C */ union anon_4_199 y1;                  // 0x4
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
};

/* anon_6_199 -- @anon6, 0x10 bytes, les_sel_sec.c (DIE 0x384DB8) */
struct anon_6_199 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};

/* anon_7_199 -- @anon7, 0x14 bytes, les_sel_sec.c (DIE 0x385202) */
struct anon_7_199 {   // size 0x14
    /* 0x000 */ unsigned char *msg;                   // 0x4
    /* 0x004 */ struct anon_2_199 *win;               // 0x4
    /* 0x008 */ short msg_num;                        // 0x2
    /* 0x00A */ short font_size;                      // 0x2
    /* 0x00C */ int ot;                               // 0x4
    /* 0x010 */ int bright;                           // 0x4
};


/* variables (10) */
struct _tag_cLesSelSection *pLesSelSection;                      /* @0x002DDE8C size 0x4 */
static struct _tag_cStatusBarLesSelSection *pStatusBar;          /* @0x002DDE90 size 0x4 */
struct anon_6_199 les_se_objf;                                   /* @0x007FA910 size 0x10 */
struct _tag_cLes *pLes;                                          /* @0x002DDE80 size 0x4 */
struct anon_6_199 les_lv_objf;                                   /* @0x007FA7F0 size 0x10 */
struct anon_3_199 kn_lesson_main_work;                           /* @0x007FE860 size 0x88 */
static struct _tag_cStatusBarLesSelSection _pStatusBar;          /* @0x007FEA10 size 0x14 */
static struct _tag_cLesSelSection _pLesSelSection;               /* @0x007FEA30 size 0xD8 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (11) */
static int les_se_item_disp(void *w);                            /* 0x007F8120-0x007F8A0C lines 1168-1332 */
static int les_se_item_disap(void *w);                           /* 0x007F8A10-0x007F8C50 lines 1117-1165 */
static int les_se_item_exec(void *w);                            /* 0x007F8C50-0x007F92C0 lines 974-1114 */
static int les_se_item_apper(void *w);                           /* 0x007F92C0-0x007F9600 lines 910-971 */
static int update_section_banner(void);                          /* 0x007F9600-0x007F96E8 lines 775-803 */
int DispStatusBar_LesSelSection(void);                           /* 0x007F96F0-0x007F96F8 lines 417-417 */
int InitStatusBar_LesSelSection(int level, int section, int mode); /* 0x007F9700-0x007F975C lines 317-322 */
int Update_LesSelSection(void);                                  /* 0x007F9760-0x007F98A0 lines 288-308 */
int View_LesSelSection(void);                                    /* 0x007F98A0-0x007F98A8 lines 284-284 */
int Control_LesSelSection(void);                                 /* 0x007F98B0-0x007F9E7C lines 115-239 */
int Init_LesSelSection(void);                                    /* 0x007F9E80-0x007FA0B0 lines 86-111 */

#endif /* DDR_UNIT_src_CS_lesson_les_sel_sec_c_H */
