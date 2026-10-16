/*
 * C:\work2\usaex2\src\CS\workout\workout_message.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 7 functions, code 0x00800E40-0x0080116C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_message_c_H
#define DDR_UNIT_src_CS_workout_workout_message_c_H

#include "types/_CWS_WIN_W.h"

/* anonymous types (3) */

/* anon_0_241 -- @anon0, 0x4 bytes, workout_message.c (DIE 0x46E77A) */
struct anon_0_241 {   // size 0x4
    /* 0x000 */ unsigned char *message;               // 0x4
};

/* anon_1_241 -- @anon1, 0x4 bytes, workout_message.c (DIE 0x46E7E4) */
struct anon_1_241 {   // size 0x4
    /* 0x000 */ int step;                             // 0x4
};

/* anon_2_241 -- @anon2, 0x8 bytes, workout_message.c (DIE 0x46E9DB) */
struct anon_2_241 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (4) */
static struct anon_0_241 msgdata_us[26];                         /* @0x00801840 size 0x68 */
struct anon_0_241 *msgdata_list[8];                              /* @0x008018B0 size 0x20 */
static struct anon_0_241 *pmsgdata;                              /* @0x002DDFB0 size 0x4 */
struct anon_1_241 msgwin[2];                                     /* @0x002DE6C8 size 0x8 */

/* functions defined (7) */
unsigned char *WorkoutMsgGetStr(int msg_no);                     /* 0x00800E40-0x00800E8C lines 171-174 */
void WorkoutMsgSet(int win_no, int str_no, int msg_no, int type, unsigned int flag, int pri); /* 0x00800E90-0x00800FE4 lines 151-168 */
void WorkoutMsgWinClose(int pno);                                /* 0x00800FF0-0x00801008 lines 147-148 */
void WorkoutMsgWinOpen(int pno);                                 /* 0x00801010-0x00801028 lines 142-143 */
void WorkoutMsgWinTerm(void);                                    /* 0x00801030-0x0080106C lines 132-137 */
void WorkoutMsgWinMain(void);                                    /* 0x00801070-0x008010F4 lines 113-129 */
void WorkoutMsgWinInit(void);                                    /* 0x00801100-0x0080116C lines 104-110 */

#endif /* DDR_UNIT_src_CS_workout_workout_message_c_H */
