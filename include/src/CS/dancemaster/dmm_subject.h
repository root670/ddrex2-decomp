/*
 * C:\work2\usaex2\src\CS\dancemaster\dmm_subject.c
 * MW MIPS C Compiler, overlay dmm_rel4cd.prg; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_dancemaster_dmm_subject_c_H
#define DDR_UNIT_src_CS_dancemaster_dmm_subject_c_H

/* anonymous types (3) */

/* anon_0_224 -- @anon0, 0x1C bytes, dmm_subject.c (DIE 0x42CCE2) */
struct anon_0_224 {   // size 0x1C
    /* 0x000 */ short music_num;                      // 0x2
    /* 0x002 */ unsigned char seq_number;             // 0x1
    /* 0x003 */ unsigned char seq_kind;               // 0x1
    /* 0x004 */ unsigned int attribute;               // 0x4
    /* 0x008 */ unsigned int data_num;                // 0x4
    /* 0x00C */ unsigned int bar_start;               // 0x4
    /* 0x010 */ unsigned int bar_end;                 // 0x4
    /* 0x014 */ signed char start_life;               // 0x1
    /* 0x015 */ unsigned char difficulty;             // 0x1
    /* 0x016 */ unsigned char perfect_type;           // 0x1
    /* 0x017 */ // 0x1 bytes padding
    /* 0x018 */ unsigned int play_mode;               // 0x4
};

/* anon_1_224 -- @anon1, 0xC bytes, dmm_subject.c (DIE 0x42CEA5) */
struct anon_1_224 {   // size 0xC
    /* 0x000 */ int id;                               // 0x4
    /* 0x004 */ int hide;                             // 0x4
    /* 0x008 */ int func_No;                          // 0x4
};

/* anon_2_224 -- @anon2, 0x90 bytes, dmm_subject.c (DIE 0x42CF28) */
struct anon_2_224 {   // size 0x90
    /* 0x000 */ struct anon_1_224 connect[8];         // 0x60
    /* 0x060 */ unsigned int area;                    // 0x4
    /* 0x064 */ int pos_x;                            // 0x4
    /* 0x068 */ int pos_y;                            // 0x4
    /* 0x06C */ int hide;                             // 0x4
    /* 0x070 */ int ex_arrow;                         // 0x4
    /* 0x074 */ struct anon_0_224 sbj_data;           // 0x1C
};


/* variables (1) */
struct anon_2_224 dmm_subject_w[200];                            /* @0x00806220 size 0x7080 */

#endif /* DDR_UNIT_src_CS_dancemaster_dmm_subject_c_H */
