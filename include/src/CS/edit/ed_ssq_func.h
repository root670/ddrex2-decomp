/*
 * C:\work2\usaex2\src\CS\edit\ed_ssq_func.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x00287DF0-0x0028864C
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
#ifndef DDR_UNIT_src_CS_edit_ed_ssq_func_c_H
#define DDR_UNIT_src_CS_edit_ed_ssq_func_c_H

#include "types/sq_header.h"
#include "types/sq_indicator.h"
#include "types/sq_standard.h"

/* anonymous types (5) */

/* anon_3_173 -- @anon3, 0x8 bytes, ed_ssq_func.c (DIE 0x3055C8) */
typedef struct {   // size 0x8
    /* 0x000 */ int beat_count;                       // 0x4
    /* 0x004 */ int music_count;                      // 0x4
} anon_3_173;

/* anon_2_173 -- @anon2, 0x3C4 bytes, ed_ssq_func.c (DIE 0x305545) */
typedef struct {   // size 0x3C4
    /* 0x000 */ int num;                              // 0x4
    /* 0x004 */ anon_3_173 val[80];                   // 0x280
    /* 0x284 */ float bpm[80];                        // 0x140
} anon_2_173;

/* anon_4_173 -- @anon4, 0xC bytes, ed_ssq_func.c (DIE 0x305680) */
typedef struct {   // size 0xC
    /* 0x000 */ int beat_count;                       // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int note_kind;                        // 0x4
} anon_4_173;

/* anon_1_173 -- @anon1, 0x64 bytes, ed_ssq_func.c (DIE 0x3053AB) */
typedef struct {   // size 0x64
    /* 0x000 */ int num;                              // 0x4
    /* 0x004 */ anon_4_173 val[8];                    // 0x60
} anon_1_173;

/* anon_0_173 -- @anon0, 0x434 bytes, ed_ssq_func.c (DIE 0x3052BC) */
typedef struct {   // size 0x434
    /* 0x000 */ int *ssq_addr;                        // 0x4
    /* 0x004 */ unsigned char *edit_seq_addr;         // 0x4
    /* 0x008 */ unsigned char *edit_freeze_addr;      // 0x4
    /* 0x00C */ anon_2_173 timing;                    // 0x3C4
    /* 0x3D0 */ anon_1_173 sp_note;                   // 0x64
} anon_0_173;


/* variables (2) */
static anon_0_173 *p_ssq_info_work;                              /* @0x002DDE18 size 0x4 */
static anon_0_173 ssq_info_work;                                 /* @0x00723150 size 0x434 */

/* functions defined (11) */
int get_ssq_timing_music_count(int index);                       /* 0x00287DF0-0x00287E04 lines 418-419 */
int get_ssq_timing_beat_count(int index);                        /* 0x00287E10-0x00287E24 lines 413-414 */
int get_ssq_timing_num(void);                                    /* 0x00287E30-0x00287E3C lines 408-409 */
unsigned char *get_ssq_edit_freeze_addr(void);                   /* 0x00287E40-0x00287E4C lines 401-402 */
unsigned char *get_ssq_edit_seq_addr(void);                      /* 0x00287E50-0x00287E5C lines 396-397 */
int get_ssq_special_note_music_count(int note_kind);             /* 0x00287E60-0x00287EC0 lines 380-389 */
int get_ssq_special_note_beat_count(int note_kind);              /* 0x00287EC0-0x00287F20 lines 364-373 */
void init_ssq_info(void *ssq_addr, unsigned char *edit_seq_addr, unsigned char *edit_freeze_addr); /* 0x00287F20-0x00287F50 lines 330-348 */
static int calc_ssq_music_count_from_beat_count(int bc);         /* 0x00287F50-0x00288098 lines 186-245 */
static void set_ssq_special_note_info(void);                     /* 0x002880A0-0x002881CC lines 113-179 */
static void set_ssq_timing_info(void);                           /* 0x002881D0-0x0028864C lines 41-107 */

#endif /* DDR_UNIT_src_CS_edit_ed_ssq_func_c_H */
