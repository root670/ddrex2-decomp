/*
 * C:\work2\usaex2\src\CS\info_data.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x001E1110-0x001E1348
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_info_data_c_H
#define DDR_UNIT_src_CS_info_data_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (6) */

/* anon_0_36 -- @anon0, 0xC bytes, info_data.c (DIE 0x56DC1) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_0_36;

/* anon_1_36 -- @anon1, 0x12E0 bytes, info_data.c (DIE 0x571A4) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_0_36 history[400];               // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_1_36;

/* anon_2_36 -- @anon2, 0xD40 bytes, info_data.c (DIE 0x57322) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_2_36;

/* anon_3_36 -- @anon3, 0x14 bytes, info_data.c (DIE 0x575F8) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_3_36;

/* anon_6_36 -- @anon6, 0x4 bytes, info_data.c (DIE 0x57C9C) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_6_36;

/* anon_5_36 -- @anon5, 0x4 bytes, info_data.c (DIE 0x57C1A) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_6_36 s;                          // 0x4
} anon_5_36;


/* variables (6) */
int tblInfoOrder[29];                                            /* @0x002B72C0 size 0x74 */
int tblInfoOrder_for_music[76];                                  /* @0x002B7340 size 0x130 */
int tblInfoOrder_for_course[26];                                 /* @0x002B7470 size 0x68 */
static unsigned short link_num_dt[75];                           /* @0x002B74E0 size 0x96 */
int tblDancerByInfotext[45];                                     /* @0x002B7580 size 0xB4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (9) */
void ReleaseInformation_AllSongsUnlocked(void);                  /* 0x001E1110-0x001E1144 lines 459-466 */
int get_dancer_id_by_infotext_num(int num);                      /* 0x001E1150-0x001E1190 lines 449-454 */
int get_course_id_by_infotxt_num(int num);                       /* 0x001E1190-0x001E11B8 lines 362-366 */
int get_table_no_by_infotxt_num(int infotxt_num);                /* 0x001E11C0-0x001E1244 lines 324-332 */
int get_infotxt_num_by_mip(struct music_info *mip);              /* 0x001E1250-0x001E12A8 lines 301-312 */
struct music_info *get_minfo_by_infotxt_num(int infotxt_num);    /* 0x001E12B0-0x001E131C lines 276-289 */
int GetInfoOrderNum_for_course(void);                            /* 0x001E1320-0x001E1328 lines 184-184 */
int GetInfoOrderNum_for_music(void);                             /* 0x001E1330-0x001E1338 lines 150-150 */
int GetInfoOrderNum(void);                                       /* 0x001E1340-0x001E1348 lines 65-65 */

#endif /* DDR_UNIT_src_CS_info_data_c_H */
