/*
 * C:\work2\usaex2\src\CS\lesson\les.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 12 functions, code 0x007F3870-0x007F44E4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
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

/* anonymous types (8) */

/* anon_13_195 -- @anon13, 0xC bytes, les.c (DIE 0x36E9C2) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_13_195;

/* anon_0_195 -- @anon0, 0x12E0 bytes, les.c (DIE 0x367991) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_13_195 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_0_195;

/* anon_1_195 -- @anon1, 0xD40 bytes, les.c (DIE 0x367B33) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_1_195;

/* anon_2_195 -- @anon2, 0x14 bytes, les.c (DIE 0x367E09) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_2_195;

/* anon_6_195 -- @anon6, 0x4 bytes, les.c (DIE 0x368C28) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_6_195;

/* anon_5_195 -- @anon5, 0x4 bytes, les.c (DIE 0x368850) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_6_195 s;                         // 0x4
} anon_5_195;

/* anon_7_195 -- @anon7, 0x4 bytes, les.c (DIE 0x368EC7) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_7_195;

/* anon_9_195 -- @anon9, 0x10 bytes, les.c (DIE 0x36A051) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_7_195 x0;                        // 0x4
    /* 0x004 */ anon_7_195 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_9_195;


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
