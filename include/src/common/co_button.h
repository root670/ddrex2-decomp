/*
 * C:\work2\usaex2\src\common\co_button.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x0023CEC0-0x0023D340
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_common_co_button_c_H
#define DDR_UNIT_src_common_co_button_c_H

/* anonymous types (5) */

/* anon_0_106 -- @anon0, 0x48 bytes, co_button.c (DIE 0x1E0B09) */
typedef struct {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02C */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03A */ unsigned short tw;                    // 0x2
    /* 0x03C */ unsigned short th;                    // 0x2
    /* 0x03E */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
} anon_0_106;

/* anon_1_106 -- @anon1, 0x10 bytes, co_button.c (DIE 0x1E0D8B) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_1_106;

/* anon_2_106 -- @anon2, 0x8 bytes, co_button.c (DIE 0x1E0EBC) */
typedef struct {   // size 0x8
    /* 0x000 */ int tex_no;                           // 0x4
    /* 0x004 */ int width;                            // 0x4
} anon_2_106;

/* anon_4_106 -- @anon4, 0x4 bytes, co_button.c (DIE 0x1E1120) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_4_106;

/* anon_3_106 -- @anon3, 0x24 bytes, co_button.c (DIE 0x1E0F8C) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_4_106 x0;                        // 0x4
    /* 0x004 */ anon_4_106 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01C */ unsigned char r0;                     // 0x1
    /* 0x01D */ unsigned char g0;                     // 0x1
    /* 0x01E */ unsigned char b0;                     // 0x1
    /* 0x01F */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
} anon_3_106;


/* variables (2) */
static anon_2_106 co_btn_tbl[16];                                /* @0x002BECA0 size 0x80 */
static anon_2_106 co_btn_ex_tbl[23];                             /* @0x002BED20 size 0xB8 */

/* functions defined (2) */
void co_button_explain_disp(unsigned int kind, float x, float y, int pri, unsigned char alpha, unsigned char bri, int flag, int tex_id); /* 0x0023CEC0-0x0023D100 lines 161-230 */
void co_button_disp(unsigned int kind, float x, float y, int pri, unsigned char alpha, unsigned char bri, int flag, int tex_id); /* 0x0023D100-0x0023D340 lines 80-149 */

#endif /* DDR_UNIT_src_common_co_button_c_H */
