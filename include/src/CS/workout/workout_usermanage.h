/*
 * C:\work2\usaex2\src\CS\workout\workout_usermanage.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 15 functions, code 0x007F25B0-0x007F29A8
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
#ifndef DDR_UNIT_src_CS_workout_workout_usermanage_c_H
#define DDR_UNIT_src_CS_workout_workout_usermanage_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* variables (5) */
static anon_b37e5ce36d96 *gw;                                    /* @0x002DE680 size 0x4 */
int g_worknum;                                                   /* @0x002DE684 size 0x4 */
anon_b37e5ce36d96 *g_workwork[2];                                /* @0x002DE688 size 0x8 */
int g_workno[2];                                                 /* @0x002DE690 size 0x8 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (15) */
void wumSetNormaCalorie(anon_b37e5ce36d96 *w, int iCalorie);     /* 0x007F25B0-0x007F25D8 lines 232-235 */
void wumSetNormaPlayTime(anon_b37e5ce36d96 *w, int iPlayTime);   /* 0x007F25E0-0x007F2608 lines 223-226 */
void wumSetWeight(anon_b37e5ce36d96 *w, unsigned int weight);    /* 0x007F2610-0x007F26C4 lines 211-216 */
int wumGetUserBlankNoSecond(void);                               /* 0x007F26D0-0x007F2730 lines 186-199 */
int wumGetUserBlankNoFirst(void);                                /* 0x007F2730-0x007F2778 lines 171-181 */
int wumGetUserPos(int uno);                                      /* 0x007F2780-0x007F2810 lines 148-161 */
anon_b37e5ce36d96 *wumGetUserWork(int uno);                      /* 0x007F2810-0x007F2824 lines 139-140 */
int wumGetUserNum(void);                                         /* 0x007F2830-0x007F2838 lines 122-122 */
void wumDeleteUser(int uno);                                     /* 0x007F2840-0x007F287C lines 110-113 */
anon_b37e5ce36d96 *wumCreateUser(int uno);                       /* 0x007F2880-0x007F2908 lines 83-99 */
anon_b37e5ce36d96 *wumGetPlayUserWork(int player);               /* 0x007F2910-0x007F2924 lines 77-78 */
anon_b37e5ce36d96 *wumSetPlayUserWork(int player, int uno);      /* 0x007F2930-0x007F2964 lines 68-71 */
void wumSetSystemUserWork(void);                                 /* 0x007F2970-0x007F2980 lines 51-53 */
void wumGetSystemUserWork(void);                                 /* 0x007F2980-0x007F299C lines 41-44 */
void wumInit(void);                                              /* 0x007F29A0-0x007F29A8 lines 33-33 */

#endif /* DDR_UNIT_src_CS_workout_workout_usermanage_c_H */
