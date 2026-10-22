/*
 * C:\work2\usaex2\src\CS\lesson\les.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 12 functions, code 0x007F3870-0x007F44E4
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
#ifndef DDR_UNIT_src_CS_lesson_les_c_H
#define DDR_UNIT_src_CS_lesson_les_c_H

#include "types/_LESWIN_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cFilepackData.h"
#include "types/_tag_cLes.h"
#include "types/_tag_cModeData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* variables (9) */
struct _tag_cLes *pLes;                                          /* @0x002DDE80 size 0x4 */
static struct _tag_cModeData ModeData[5];                        /* @0x007FA700 size 0x64 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
unsigned int less_joy_new;                                       /* @0x002DE60C size 0x4 */
unsigned int less_joy_trg;                                       /* @0x002DE610 size 0x4 */
static struct _tag_cLes _pLes;                                   /* @0x007FB880 size 0x2A4 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions referenced (1) */
void DecodeFilepackData_Th(void *);                              /* @0x0016DC50 */

/* functions defined (12) */
int is_can_play_last_section(int level);                         /* 0x007F3870-0x007F38C0 lines 583-601 */
void SetLessonState(int level, int section, int val);            /* 0x007F38C0-0x007F38DC lines 572-576 */
int GetLessonState(int level, int section);                      /* 0x007F38E0-0x007F38FC lines 568-569 */
static int init_tex(void);                                       /* 0x007F3900-0x007F3AD0 lines 468-562 */
static int init_kanji(void);                                     /* 0x007F3AD0-0x007F3BB4 lines 434-463 */
static void close_func(void);                                    /* 0x007F3BC0-0x007F3CBC lines 373-405 */
static void open_func(void);                                     /* 0x007F3CC0-0x007F3E5C lines 312-361 */
static void init_func(void);                                     /* 0x007F3E60-0x007F408C lines 256-309 */
void Term_Les(void);                                             /* 0x007F4090-0x007F40A4 lines 242-247 */
int Step_Les(void);                                              /* 0x007F40B0-0x007F4320 lines 187-236 */
void Init_Les(void);                                             /* 0x007F4320-0x007F44B4 lines 105-183 */
void SetStep_Les(int _step, int _next_mode);                     /* 0x007F44C0-0x007F44E4 lines 79-84 */

#endif /* DDR_UNIT_src_CS_lesson_les_c_H */
