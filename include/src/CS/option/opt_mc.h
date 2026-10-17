/*
 * C:\work2\usaex2\src\CS\option\opt_mc.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 6 functions, code 0x007F33A0-0x007F375C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_option_opt_mc_c_H
#define DDR_UNIT_src_CS_option_opt_mc_c_H

#include "types/_OPTMC_W.h"
#include "types/_OPTSYS_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (6) */

/* anon_1_230 -- @anon1, 0xD40 bytes, opt_mc.c (DIE 0x4478FB) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_1_230;

/* anon_2_230 -- @anon2, 0x14 bytes, opt_mc.c (DIE 0x447D2D) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_2_230;

/* anon_3_230 -- @anon3, 0xC bytes, opt_mc.c (DIE 0x447FF9) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_3_230;

/* anon_6_230 -- @anon6, 0x4 bytes, opt_mc.c (DIE 0x448685) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_6_230;

/* anon_5_230 -- @anon5, 0x4 bytes, opt_mc.c (DIE 0x448627) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_6_230 s;                         // 0x4
} anon_5_230;

/* anon_7_230 -- @anon7, 0x12E0 bytes, opt_mc.c (DIE 0x448927) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_3_230 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_7_230;


/* variables (5) */
struct _OPTMC_W *OPTMCW;                                         /* @0x002DDEF8 size 0x4 */
int RequestAutoSave;                                             /* @0x002DE1AC size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
static struct _OPTMC_W _opt_mc_w;                                /* @0x00803770 size 0x54 */

/* functions referenced (3) */
void OptMenuInit3(struct _OPTSYS_W *);                           /* @0x007F5E50 */
void OptMcLoadMain(struct _OPTSYS_W *);                          /* @0x007F35C0 */
void OptMcSaveMain(struct _OPTSYS_W *);                          /* @0x007F3690 */

/* functions defined (6) */
static int OptMcLoadExe(void);                                   /* 0x007F33A0-0x007F34B4 lines 128-166 */
static int OptMcSaveExe(void);                                   /* 0x007F34C0-0x007F35B4 lines 90-123 */
void OptMcLoadMain(struct _OPTSYS_W *_opt);                      /* 0x007F35C0-0x007F3648 lines 63-80 */
void OptMcLoadInit(struct _OPTSYS_W *_opt);                      /* 0x007F3650-0x007F368C lines 54-60 */
void OptMcSaveMain(struct _OPTSYS_W *_opt);                      /* 0x007F3690-0x007F3718 lines 32-49 */
void OptMcSaveInit(struct _OPTSYS_W *_opt);                      /* 0x007F3720-0x007F375C lines 23-29 */

#endif /* DDR_UNIT_src_CS_option_opt_mc_c_H */
