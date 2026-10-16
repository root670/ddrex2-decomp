/*
 * C:\work\usam2\src\CS\edit\ny_tbl.c
 * MW MIPS C Compiler, overlay main; 1 functions, code 0x0022AF30-0x0022AF60
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_edit_ny_tbl_c_H
#define DDR_UNIT_src_CS_edit_ny_tbl_c_H

/* anonymous types (1) */

/* anon_0_15 -- @anon0, 0x14 bytes, ny_tbl.c (DIE 0x361EB) */
struct anon_0_15 {   // size 0x14
    /* 0x000 */ unsigned char name[6];                // 0x6
    /* 0x006 */ // 0x2 bytes padding
    /* 0x008 */ int number;                           // 0x4
    /* 0x00C */ short code;                           // 0x2
    /* 0x00E */ short beat;                           // 0x2
    /* 0x010 */ unsigned char *music_name;            // 0x4
};


/* variables (1) */
struct anon_0_15 ny_mtbl[69];                                    /* @0x002822B0 size 0x564 */

/* functions defined (1) */
struct anon_0_15 *NyGetMusicData_by_index(int id);               /* 0x0022AF30-0x0022AF60 lines 128-132 */

#endif /* DDR_UNIT_src_CS_edit_ny_tbl_c_H */
