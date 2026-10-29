/*
 * C:\work2\usaex2\src\CS\option\opt_menu.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 13 functions, code 0x007F3760-0x007F5EE4
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
#ifndef DDR_UNIT_src_CS_option_opt_menu_c_H
#define DDR_UNIT_src_CS_option_opt_menu_c_H

#include "types/_OPTSYS_W.h"
#include "types/_tag_cDDR8Option.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

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

/* functions referenced (6) */
void OptLangInit(struct _OPTSYS_W *);                            /* @0x007F1F80 */
void OptMcLoadInit(struct _OPTSYS_W *);                          /* @0x007F3650 */
void OptMcSaveInit(struct _OPTSYS_W *);                          /* @0x007F3720 */
void OptKConfigDoubleInit(struct _OPTSYS_W *);                   /* @0x007F1870 */
void OptKConfigInit(struct _OPTSYS_W *);                         /* @0x007F1B50 */
void OptAdjustInit(struct _OPTSYS_W *);                          /* @0x007F05A0 */

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
