/*
 * C:\work2\usaex2\src\CS\info_data.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x001E1110-0x001E1348
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
#ifndef DDR_UNIT_src_CS_info_data_c_H
#define DDR_UNIT_src_CS_info_data_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/music_info.h"
#include "types/oni_course.h"

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
