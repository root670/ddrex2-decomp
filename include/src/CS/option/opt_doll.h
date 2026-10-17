/*
 * C:\work2\usaex2\src\CS\option\opt_doll.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 1 functions, code 0x007F0600-0x007F07E4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_option_opt_doll_c_H
#define DDR_UNIT_src_CS_option_opt_doll_c_H

#include "types/_OPTSYS_W.h"
#include "types/_tag_OptDoll.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (8) */

/* anon_10_226 -- @anon10, 0xC bytes, opt_doll.c (DIE 0x4353CC) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_10_226;

/* anon_0_226 -- @anon0, 0x12E0 bytes, opt_doll.c (DIE 0x431793) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_10_226 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_0_226;

/* anon_1_226 -- @anon1, 0xD40 bytes, opt_doll.c (DIE 0x431911) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_1_226;

/* anon_2_226 -- @anon2, 0x14 bytes, opt_doll.c (DIE 0x431BC5) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_2_226;

/* anon_5_226 -- @anon5, 0x4 bytes, opt_doll.c (DIE 0x43238F) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_5_226;

/* anon_4_226 -- @anon4, 0x4 bytes, opt_doll.c (DIE 0x432331) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_5_226 s;                         // 0x4
} anon_4_226;

/* anon_8_226 -- @anon8, 0x31 bytes, opt_doll.c (DIE 0x433AD4) */
typedef struct {   // size 0x31
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[48];                          // 0x30
} anon_8_226;

/* anon_9_226 -- @anon9, 0x8 bytes, opt_doll.c (DIE 0x433E87) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_9_226;


/* variables (4) */
static anon_9_226 crect;                                         /* @0x002DDEE8 size 0x8 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
anon_8_226 lst;                                                  /* not allocated size 0x31 */

/* functions defined (1) */
int View_OptDoll(void);                                          /* 0x007F0600-0x007F07E4 lines 106-203 */

#endif /* DDR_UNIT_src_CS_option_opt_doll_c_H */
