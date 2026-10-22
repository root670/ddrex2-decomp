/*
 * C:\work2\usaex2\src\CS\cs_font.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x001E1350-0x001E2EE0
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
#ifndef DDR_UNIT_src_CS_cs_font_c_H
#define DDR_UNIT_src_CS_cs_font_c_H

/* anonymous types (6) */

/* anon_0_37 -- @anon0, 0x48 bytes, cs_font.c (DIE 0x5A460) */
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
} anon_0_37;

/* anon_1_37 -- @anon1, 0x8 bytes, cs_font.c (DIE 0x5A708) */
typedef struct {   // size 0x8
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int w;                                // 0x4
} anon_1_37;

/* anon_3_37 -- @anon3, 0x4 bytes, cs_font.c (DIE 0x5A8F7) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_37;

/* anon_2_37 -- @anon2, 0x24 bytes, cs_font.c (DIE 0x5A763) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_3_37 x0;                         // 0x4
    /* 0x004 */ anon_3_37 y0;                         // 0x4
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
} anon_2_37;

/* anon_4_37 -- @anon4, 0x30 bytes, cs_font.c (DIE 0x5A954) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_3_37 x0;                         // 0x4
    /* 0x004 */ anon_3_37 y0;                         // 0x4
    /* 0x008 */ anon_3_37 x1;                         // 0x4
    /* 0x00C */ anon_3_37 y1;                         // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
} anon_4_37;

/* anon_5_37 -- @anon5, 0x68 bytes, cs_font.c (DIE 0x5AB6F) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_3_37 x0;                         // 0x4
    /* 0x004 */ anon_3_37 y0;                         // 0x4
    /* 0x008 */ anon_3_37 x1;                         // 0x4
    /* 0x00C */ anon_3_37 y1;                         // 0x4
    /* 0x010 */ anon_3_37 x2;                         // 0x4
    /* 0x014 */ anon_3_37 y2;                         // 0x4
    /* 0x018 */ anon_3_37 x3;                         // 0x4
    /* 0x01C */ anon_3_37 y3;                         // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
} anon_5_37;


/* variables (4) */
static anon_1_37 csxx24_pos_table[256];                          /* @0x002B7640 size 0x800 */
static anon_1_37 mnxx28_pos_table[256];                          /* @0x002B7E40 size 0x800 */
static anon_1_37 csxx18_pos_table[160];                          /* @0x002B8640 size 0x500 */
unsigned char cs_str_font[128];                                  /* @0x00712BA0 size 0x80 */

/* functions defined (12) */
void CsFontPutsI(float _x, float _y, unsigned char *_str, int _bri, int _pri, int _col, int alpha, int tex_id, int mode, float rate); /* 0x001E1350-0x001E16D4 lines 1298-1341 */
int GetCsFontLenI(unsigned char *str, float rate);               /* 0x001E16E0-0x001E1740 lines 1286-1296 */
void CSXX20Puts(short _x, short _y, unsigned char *_str, int _bri, int _pri, int _col, int alpha, int tex_id, int mode); /* 0x001E1740-0x001E1C20 lines 1129-1232 */
int GetCSXX20Len(unsigned char *str);                            /* 0x001E1C20-0x001E1C2C lines 1127-1127 */
int CsGetFontLength(int _type, unsigned char *_str);             /* 0x001E1C30-0x001E1DB8 lines 1105-1121 */
void CsFontPrintf(short _x, short _y, int _bri, int _pri, int _col, int _alpha, int _tex_id, int _mode, int _type, unsigned char *_str); /* 0x001E1DC0-0x001E1F68 lines 1088-1102 */
void CSXX18Puts(short _x, short _y, unsigned char *_str, int _bri, int _pri, int _col, int alpha, int tex_id, int mode); /* 0x001E1F70-0x001E2240 lines 1032-1077 */
void MgFontPuts(short _x, short _y, unsigned char *_str, int _bri, int _pri, int _col, int alpha, int tex_id, int mode); /* 0x001E2240-0x001E24D8 lines 976-1024 */
void CsFontPutsRGB(short _x, short _y, unsigned char *_str, int _r, int _g, int _b, int _pri, int _col, int alpha, int tex_id, int mode); /* 0x001E24E0-0x001E2840 lines 786-847 */
void CsFontPuts(short _x, short _y, unsigned char *_str, int _bri, int _pri, int _col, int alpha, int tex_id, int mode); /* 0x001E2840-0x001E2E60 lines 655-784 */
int GetCsFontLen(unsigned char *str);                            /* 0x001E2E60-0x001E2EA0 lines 583-592 */
int GetCSXX18FontLen(unsigned char *str);                        /* 0x001E2EA0-0x001E2EE0 lines 548-557 */

#endif /* DDR_UNIT_src_CS_cs_font_c_H */
