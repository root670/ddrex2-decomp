/*
 * C:\work2\usaex2\src\music_all.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x001B7900-0x001B7A30
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
#ifndef DDR_UNIT_src_music_all_c_H
#define DDR_UNIT_src_music_all_c_H

#include "types/_tag_cMusicData.h"

/* variables (1) */
static struct _tag_cMusicData tblMusicData[674];                 /* @0x002AC240 size 0x34A8 */

/* functions defined (3) */
struct _tag_cMusicData *GetMusicData_by_link_num(unsigned short link_num); /* 0x001B7900-0x001B7960 lines 977-989 */
struct _tag_cMusicData *GetMusicData_by_base_name(unsigned char *base_name); /* 0x001B7960-0x001B79F8 lines 960-973 */
struct _tag_cMusicData *GetMusicData_by_index(int id);           /* 0x001B7A00-0x001B7A30 lines 953-957 */

#endif /* DDR_UNIT_src_music_all_c_H */
