/*
 * C:\work2\usaex2\src\CS\option\opt_menu.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 13 functions, code 0x007F3760-0x007F5EE4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_option_opt_menu_c_H
#define DDR_UNIT_src_CS_option_opt_menu_c_H

#include "types/_OPTSYS_W.h"
#include "types/_tag_cDDR8Option.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (6) */

/* anon_1_231 -- @anon1, 0xD40 bytes, opt_menu.c (DIE 0x44CC40) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_1_231;

/* anon_2_231 -- @anon2, 0x14 bytes, opt_menu.c (DIE 0x44D096) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_2_231;

/* anon_3_231 -- @anon3, 0xC bytes, opt_menu.c (DIE 0x44D365) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_3_231;

/* anon_6_231 -- @anon6, 0x4 bytes, opt_menu.c (DIE 0x44DA5F) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_6_231;

/* anon_5_231 -- @anon5, 0x4 bytes, opt_menu.c (DIE 0x44D9DD) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_6_231 s;                         // 0x4
} anon_5_231;

/* anon_7_231 -- @anon7, 0x12E0 bytes, opt_menu.c (DIE 0x44DCD8) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_3_231 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_7_231;


/* variables (28) */
static int opt_menu_mode_str_table[8][9];                        /* @0x007F82F0 size 0x120 */
static int opt_menu_mode_stex_table[8][9];                       /* not allocated size 0x120 */
static int opt_menu_exp_str_table[8][9];                         /* @0x007F8410 size 0x120 */
static int opt_sound_sound_tbl[3];                               /* @0x007F8530 size 0xC */
static int opt_sound_voice_tbl[3];                               /* @0x007F8540 size 0xC */
static int opt_cont_vib_tbl[4];                                  /* not allocated size 0x10 */
static int opt_cont_dms_tbl[2];                                  /* @0x002DDF00 size 0x8 */
static int opt_cont_double_tbl[2];                               /* @0x002DDF08 size 0x8 */
static int opt_mc_auto_tbl[2];                                   /* @0x002DDF10 size 0x8 */
static int opt_mc_folder_tbl[2];                                 /* @0x002DDF18 size 0x8 */
static int opt_game_level_tbl[8];                                /* @0x007F8550 size 0x20 */
static int opt_game_stage_tbl[5];                                /* not allocated size 0x14 */
static int opt_game_over_tbl[2];                                 /* @0x002DDF20 size 0x8 */
static int opt_game_event_tbl[2];                                /* @0x002DDF28 size 0x8 */
static int opt_game_diff_tbl[5];                                 /* @0x007F8570 size 0x14 */
static int opt_graphic_doll_tbl[2];                              /* @0x002DDF30 size 0x8 */
static int opt_graphic_song_tbl[2];                              /* not allocated size 0x8 */
static int opt_graphic_movie_tbl[2];                             /* @0x002DDF38 size 0x8 */
static int opt_graphic_danger_tbl[3];                            /* not allocated size 0xC */
static int opt_graphic_bright_tbl[16];                           /* @0x007F8590 size 0x40 */
static int opt_graphic_step_tbl[2];                              /* @0x002DDF40 size 0x8 */
static int opt_graphic_flicker_tbl[2];                           /* @0x002DDF48 size 0x8 */
static int opt_graphic_marvellous_tbl[2];                        /* @0x002DDF50 size 0x8 */
static int opt_dance_play_tbl[2];                                /* @0x002DDF58 size 0x8 */
static int opt_network_automatic_tbl[2];                         /* @0x002DDF60 size 0x8 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
struct _tag_cDDR8Option OptionDefault;                           /* @0x002A6510 size 0x58 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions referenced (8) */
void OptMenuInit2(struct _OPTSYS_W *);                           /* @0x007F5E70 */
void OptLangInit(struct _OPTSYS_W *);                            /* @0x007F1F80 */
void OptMcLoadInit(struct _OPTSYS_W *);                          /* @0x007F3650 */
void OptMcSaveInit(struct _OPTSYS_W *);                          /* @0x007F3720 */
void OptKConfigDoubleInit(struct _OPTSYS_W *);                   /* @0x007F1870 */
void OptKConfigInit(struct _OPTSYS_W *);                         /* @0x007F1B50 */
void OptAdjustInit(struct _OPTSYS_W *);                          /* @0x007F05A0 */
void OptMenuMain(struct _OPTSYS_W *);                            /* @0x007F55D0 */

/* functions defined (13) */
char *OptGetMenuHelp(void);                                      /* 0x007F3760-0x007F3854 lines 2483-2505 */
static int OptMenuModeGetType(int _line, int _mode);             /* 0x007F3860-0x007F4238 lines 2188-2479 */
static int OptMenuModeGetStLine(int _line);                      /* 0x007F4240-0x007F4300 lines 2138-2169 */
int OptMenuModeGetLine(void);                                    /* 0x007F4300-0x007F4398 lines 2118-2134 */
static int OptMenuModeChangeType(int num);                       /* 0x007F43A0-0x007F48B8 lines 1820-1982 */
static int OptNextMenuModePAGE(int _flag);                       /* 0x007F48C0-0x007F4D78 lines 1586-1815 */
void OptMenuModeSet(int _mode);                                  /* 0x007F4D80-0x007F533C lines 1379-1580 */
void OptMenuHelpDisp(void);                                      /* 0x007F5340-0x007F5348 lines 1370-1370 */
void OptMenuModeDisp(void);                                      /* 0x007F5350-0x007F55C8 lines 1033-1163 */
void OptMenuMain(struct _OPTSYS_W *_opt);                        /* 0x007F55D0-0x007F5E44 lines 745-1029 */
void OptMenuInit3(struct _OPTSYS_W *_opt);                       /* 0x007F5E50-0x007F5E70 lines 739-742 */
void OptMenuInit2(struct _OPTSYS_W *_opt);                       /* 0x007F5E70-0x007F5E98 lines 732-735 */
void OptMenuInit(struct _OPTSYS_W *_opt);                        /* 0x007F5EA0-0x007F5EE4 lines 721-728 */

#endif /* DDR_UNIT_src_CS_option_opt_menu_c_H */
