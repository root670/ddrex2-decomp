/*
 * C:\work\usam2\src\AM\s573\play\onimode.c
 * MW MIPS C Compiler, overlay main; 34 functions, code 0x00227B10-0x0022AD24
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_play_onimode_c_H
#define DDR_UNIT_src_AM_s573_play_onimode_c_H

#include "types/G_SYS_W_.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_cource_work.h"
#include "types/oni_course.h"
#include "types/oni_mode.h"
#include "types/oni_steps.h"
#include "types/play_mode.h"

/* anonymous types (2) */

/* anon_0_12 -- @anon0, 0x4 bytes, onimode.c (DIE 0x2B28C) */
struct anon_0_12 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_1_12 -- @anon1, 0xCC8 bytes, onimode.c (DIE 0x2EAB9) */
struct anon_1_12 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};


/* variables (9) */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xAB544 */
struct oni_course playing_course_work;                           /* @0x006B27D0 size 0x110 */
struct oni_cource_work *oni_w;                                   /* @0x002A2AA4 size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
struct oni_course course_list[23];                               /* @0x00283000 size 0x1870 */
struct oni_course diet_course_list[];                            /* @0x00284870 */
struct G_SYS_W_ g_sys_w;                                         /* @0x0063D5A0 size 0x90 */
struct oni_steps oni_steps_table[];                              /* not allocated */
struct oni_cource_work oni_work;                                 /* @0x006B28E0 size 0x9C */

/* functions defined (34) */
int onimode_get_total_groov_max(int n);                          /* 0x00227B10-0x00227D08 lines 2322-2339 */
int onimode_get_total_freez(int id);                             /* 0x00227D10-0x00227FC8 lines 2276-2315 */
int onimode_get_course_nm_color(int id);                         /* 0x00227FD0-0x002280B0 lines 2135-2181 */
struct oni_course *onimode_get_course_list(int id, int mode);    /* 0x002280B0-0x00228100 lines 1969-1973 */
void onimode_set_order_mode(int id, int stage_num);              /* 0x00228100-0x00228418 lines 1930-1960 */
void onimode_get_order_mode(int id, int stage_num);              /* 0x00228420-0x00228674 lines 1899-1926 */
int onimode_is_course_no_increase_point(int id);                 /* 0x00228680-0x002286B8 lines 1882-1891 */
int onimode_is_course_set_start_point(int id);                   /* 0x002286C0-0x00228700 lines 1867-1876 */
int onimode_is_course_special_calc_score(int id);                /* 0x00228700-0x00228790 lines 1840-1861 */
int onimode_is_course_selectable_option(int id);                 /* 0x00228790-0x002287C8 lines 1826-1834 */
int onimode_is_course_selectable_difficulty(int id);             /* 0x002287D0-0x00228818 lines 1809-1820 */
int onimode_is_course_order(int id);                             /* 0x00228820-0x00228858 lines 1789-1803 */
int onimode_is_course_cs_random(int id);                         /* 0x00228860-0x00228898 lines 1768-1782 */
void onimode_order_setup(void);                                  /* 0x002288A0-0x00228C28 lines 1640-1758 */
void onimode_random_setup(void);                                 /* 0x00228C30-0x002298A0 lines 1299-1621 */
void onimode_set_linknum(int id, int stage, struct music_info *mip); /* 0x002298A0-0x002299E0 lines 1278-1290 */
int onimode_ta_load(int id);                                     /* 0x002299E0-0x00229A20 lines 1234-1270 */
void onimode_set_order_stage(int id, int stage);                 /* 0x00229A20-0x00229AE8 lines 1219-1229 */
int onimode_get_real_stage_num(int id);                          /* 0x00229AF0-0x00229B58 lines 1202-1214 */
int onimode_get_stage_allnum(int id);                            /* 0x00229B60-0x00229BB0 lines 1186-1196 */
int onimode_get_stage_num(int id);                               /* 0x00229BB0-0x00229C00 lines 1170-1180 */
int onimode_set_playmode(int stage_num);                         /* 0x00229C00-0x00229EA8 lines 1104-1162 */
void onimode_set_seqkind(int id, int stage_num, int kind);       /* 0x00229EB0-0x00229FF0 lines 991-1010 */
int onimode_get_seqkind(int stage_num, int mode);                /* 0x00229FF0-0x0022A0B8 lines 930-954 */
void onimode_set_course_difficulty(int id, int mode);            /* 0x0022A0C0-0x0022A550 lines 841-923 */
void onimode_setup_nonstop_course(void);                         /* 0x0022A550-0x0022A718 lines 694-834 */
struct music_info *onimode_get_disp_mip(int id, int stage_num);  /* 0x0022A720-0x0022A7EC lines 655-686 */
struct music_info *onimode_get_mip(int stage_num);               /* 0x0022A7F0-0x0022A8CC lines 627-652 */
int onimode_get_start_life(void);                                /* 0x0022A8D0-0x0022A920 lines 525-542 */
int onimode_get_order(int id);                                   /* 0x0022A920-0x0022A970 lines 509-520 */
int onimode_course_avairable(int id);                            /* 0x0022A970-0x0022AA18 lines 342-382 */
int onimode_course_load(int id);                                 /* 0x0022AA20-0x0022ABC0 lines 270-334 */
int onimode_is_course_data(int id);                              /* 0x0022ABC0-0x0022AC00 lines 252-263 */
void onimode_boot(int mode);                                     /* 0x0022AC00-0x0022AD24 lines 120-246 */

#endif /* DDR_UNIT_src_AM_s573_play_onimode_c_H */
