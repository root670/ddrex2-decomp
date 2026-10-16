/*
 * C:\work\usam2\src\music_all.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0022ad30-0x0022ae60
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_music_all_c_H
#define DDR_UNIT_src_music_all_c_H

#include "types/_tag_cMusicData.h"

/* variables (1) */
static struct _tag_cMusicData tblMusicData[546];                 /* @0x0027f800 size 0x2aa8 */

/* functions defined (3) */
struct _tag_cMusicData *GetMusicData_by_link_num(unsigned short link_num); /* 0x0022ad30-0x0022ad90 lines 803-815 */
struct _tag_cMusicData *GetMusicData_by_base_name(unsigned char *base_name); /* 0x0022ad90-0x0022ae28 lines 786-799 */
struct _tag_cMusicData *GetMusicData_by_index(int id);           /* 0x0022ae30-0x0022ae60 lines 779-783 */

#endif /* DDR_UNIT_src_music_all_c_H */
