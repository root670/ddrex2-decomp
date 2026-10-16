/*
 * C:\work\usam2\src\CS\lesson\les.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x0021d8d0-0x0021e424
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_les_c_H
#define DDR_UNIT_src_CS_lesson_les_c_H

#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cLes.h"
#include "types/_tag_cModeData.h"
#include "types/g_game_w.h"

/* anonymous types (2) */

/* anon_0_2 -- @anon0, 0x4 bytes, les.c (DIE 0x3982) */
struct anon_0_2 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_1_2 -- @anon1, 0xcc8 bytes, les.c (DIE 0x5783) */
struct anon_1_2 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};


/* variables (10) */
static unsigned char *les_bin_data[5];                           /* @0x0027ebc0 size 0x14 */
struct _tag_cLes *pLes;                                          /* @0x002a2128 size 0x4 */
static struct _tag_cModeData ModeData[5];                        /* @0x0027ebe0 size 0x64 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xab544 */
unsigned int less_joy_new;                                       /* @0x002a2a7c size 0x4 */
unsigned int less_joy_trg;                                       /* @0x002a2a80 size 0x4 */
static struct _tag_cLes _pLes;                                   /* @0x006af500 size 0x284 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions referenced (1) */
void DecodeFilepackData_Th(void *);                              /* @0x00180b60 */

/* functions defined (13) */
int is_can_play_last_section(int level);                         /* 0x0021d8d0-0x0021d920 lines 543-561 */
void SetLessonState(int level, int section, int val);            /* 0x0021d920-0x0021d93c lines 532-536 */
int GetLessonState(int level, int section);                      /* 0x0021d940-0x0021d95c lines 528-529 */
static int init_tex(void);                                       /* 0x0021d960-0x0021dbcc lines 430-522 */
void SetPreRead_Les(void);                                       /* 0x0021dbd0-0x0021dc0c lines 423-426 */
static int init_kanji(void);                                     /* 0x0021dc10-0x0021dcf4 lines 390-419 */
static void close_func(void);                                    /* 0x0021dd00-0x0021ddfc lines 329-361 */
static void open_func(void);                                     /* 0x0021de00-0x0021df9c lines 268-317 */
static void init_func(void);                                     /* 0x0021dfa0-0x0021e0ec lines 231-265 */
void Term_Les(void);                                             /* 0x0021e0f0-0x0021e120 lines 212-223 */
int Step_Les(void);                                              /* 0x0021e120-0x0021e378 lines 170-208 */
void Init_Les(void);                                             /* 0x0021e380-0x0021e3fc lines 130-166 */
void SetStep_Les(int _step, int _next_mode);                     /* 0x0021e400-0x0021e424 lines 104-109 */

#endif /* DDR_UNIT_src_CS_lesson_les_c_H */
