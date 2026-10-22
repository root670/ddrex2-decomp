/*
 * C:\work2\usaex2\src\CS\staffroll\cs_staffroll_fft.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 9 functions, code 0x007FA560-0x007FD764
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
#ifndef DDR_UNIT_src_CS_staffroll_cs_staffroll_fft_c_H
#define DDR_UNIT_src_CS_staffroll_cs_staffroll_fft_c_H

#include "types/_sceDmaTag.h"

/* anonymous types (46) */

/* anon_0_187 -- @anon0, 0x58 bytes, cs_staffroll_fft.c (DIE 0x34D99B) */
typedef struct {   // size 0x58
    /* 0x000 */ unsigned long regTest[2];             // 0x10
    /* 0x010 */ unsigned long regAlpha[2];            // 0x10
    /* 0x020 */ unsigned long regClamp[2];            // 0x10
    /* 0x030 */ unsigned long regFrame[2];            // 0x10
    /* 0x040 */ unsigned long regTex1[2];             // 0x10
    /* 0x050 */ unsigned long regTexa;                // 0x8
} anon_0_187;

/* anon_29_187 -- @anon29, 0x4 bytes, cs_staffroll_fft.c (DIE 0x350785) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_29_187;

/* anon_1_187 -- @anon1, 0xC bytes, cs_staffroll_fft.c (DIE 0x34DA9F) */
typedef struct {   // size 0xC
    /* 0x000 */ anon_29_187 x0;                       // 0x4
    /* 0x004 */ anon_29_187 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
} anon_1_187;

/* anon_2_187 -- @anon2, 0x78 bytes, cs_staffroll_fft.c (DIE 0x34DBB1) */
typedef struct {   // size 0x78
    /* 0x000 */ float timer;                          // 0x4
    /* 0x004 */ float topPos;                         // 0x4
    /* 0x008 */ float startStrPos;                    // 0x4
    /* 0x00C */ unsigned short startStrNo;            // 0x2
    /* 0x00E */ short picseqNo;                       // 0x2
    /* 0x010 */ short picseqCom;                      // 0x2
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ float picseqTimer;                    // 0x4
    /* 0x018 */ float picseqduration;                 // 0x4
    /* 0x01C */ int movie_timer;                      // 0x4
    /* 0x020 */ int tex_id;                           // 0x4
    /* 0x024 */ int start_flg;                        // 0x4
    /* 0x028 */ int fft_kind;                         // 0x4
    /* 0x02C */ int fft_colset[3];                    // 0xC
    /* 0x038 */ int fft_type;                         // 0x4
    /* 0x03C */ int fft_reset;                        // 0x4
    /* 0x040 */ int u[4];                             // 0x10
    /* 0x050 */ int v[4];                             // 0x10
    /* 0x060 */ int fft_bright;                       // 0x4
    /* 0x064 */ int mvseq_no;                         // 0x4
    /* 0x068 */ int movie_bright;                     // 0x4
    /* 0x06C */ int read_time;                        // 0x4
    /* 0x070 */ int read_flag;                        // 0x4
    /* 0x074 */ int disp_pic : 1;                     // bits 0..0
    /* 0x074 */ int disp_mov : 1;                     // bits 1..1
    /* 0x074 */ int disp_roll : 1;                    // bits 2..2
    /* 0x074 */ int disp_padding : 29;                // bits 3..31
} anon_2_187;

/* anon_42_187 -- @anon42, 0x8 bytes, cs_staffroll_fft.c (DIE 0x351FB7) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int EN1 : 1;                 // bits 0..0
    /* 0x000 */ unsigned int EN2 : 1;                 // bits 1..1
    /* 0x000 */ unsigned int CRTMD : 3;               // bits 2..4
    /* 0x000 */ unsigned int MMOD : 1;                // bits 5..5
    /* 0x000 */ unsigned int AMOD : 1;                // bits 6..6
    /* 0x000 */ unsigned int SLBG : 1;                // bits 7..7
    /* 0x000 */ unsigned int ALP : 8;                 // bits 8..15
    /* 0x000 */ unsigned int p0 : 16;                 // bits 16..31
    /* 0x004 */ unsigned int p1;                      // 0x4
} anon_42_187;

/* anon_5_187 -- @anon5, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34E260) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int INT : 1;                 // bits 0..0
    /* 0x000 */ unsigned int FFMD : 1;                // bits 1..1
    /* 0x000 */ unsigned int DPMS : 2;                // bits 2..3
    /* 0x000 */ unsigned int p0 : 28;                 // bits 4..31
    /* 0x004 */ unsigned int p1;                      // 0x4
} anon_5_187;

/* anon_43_187 -- @anon43, 0x8 bytes, cs_staffroll_fft.c (DIE 0x35214A) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int FBP : 9;                 // bits 0..8
    /* 0x000 */ unsigned int FBW : 6;                 // bits 9..14
    /* 0x000 */ unsigned int PSM : 5;                 // bits 15..19
    /* 0x000 */ unsigned int p0 : 12;                 // bits 20..31
    /* 0x004 */ unsigned int DBX : 11;                // bits 0..10
    /* 0x004 */ unsigned int DBY : 11;                // bits 11..21
    /* 0x004 */ unsigned int p1 : 10;                 // bits 22..31
} anon_43_187;

/* anon_11_187 -- @anon11, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34E98C) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int DX : 12;                 // bits 0..11
    /* 0x000 */ unsigned int DY : 11;                 // bits 12..22
    /* 0x000 */ unsigned int MAGH : 4;                // bits 23..26
    /* 0x000 */ unsigned int MAGV : 2;                // bits 27..28
    /* 0x000 */ unsigned int p0 : 3;                  // bits 29..31
    /* 0x004 */ unsigned int DW : 12;                 // bits 0..11
    /* 0x004 */ unsigned int DH : 11;                 // bits 12..22
    /* 0x004 */ unsigned int p1 : 9;                  // bits 23..31
} anon_11_187;

/* anon_7_187 -- @anon7, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34E3DE) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int R : 8;                   // bits 0..7
    /* 0x000 */ unsigned int G : 8;                   // bits 8..15
    /* 0x000 */ unsigned int B : 8;                   // bits 16..23
    /* 0x000 */ unsigned int p0 : 8;                  // bits 24..31
    /* 0x004 */ unsigned int p1;                      // 0x4
} anon_7_187;

/* anon_3_187 -- @anon3, 0x28 bytes, cs_staffroll_fft.c (DIE 0x34E016) */
typedef struct {   // size 0x28
    /* 0x000 */ anon_42_187 pmode;                    // 0x8
    /* 0x008 */ anon_5_187 smode2;                    // 0x8
    /* 0x010 */ anon_43_187 dispfb;                   // 0x8
    /* 0x018 */ anon_11_187 display;                  // 0x8
    /* 0x020 */ anon_7_187 bgcolor;                   // 0x8
} anon_3_187;

/* anon_4_187 -- @anon4, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34E113) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long FBP : 9;                // bits 0..8
    /* 0x000 */ unsigned long pad09 : 7;              // bits 9..15
    /* 0x000 */ unsigned long FBW : 6;                // bits 16..21
    /* 0x000 */ unsigned long pad22 : 2;              // bits 22..23
    /* 0x000 */ unsigned long PSM : 6;                // bits 24..29
    /* 0x000 */ unsigned long pad30 : 2;              // bits 30..31
    /* 0x000 */ unsigned long FBMSK : 32;             // bits 32..63
} anon_4_187;

/* anon_6_187 -- @anon6, 0x4 bytes, cs_staffroll_fft.c (DIE 0x34E347) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char a;                      // 0x1
} anon_6_187;

/* anon_27_187 -- @anon27, 0x8 bytes, cs_staffroll_fft.c (DIE 0x3502E7) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long ZBP : 9;                // bits 0..8
    /* 0x000 */ unsigned long pad09 : 15;             // bits 9..23
    /* 0x000 */ unsigned long PSM : 4;                // bits 24..27
    /* 0x000 */ unsigned long pad28 : 4;              // bits 28..31
    /* 0x000 */ unsigned long ZMSK : 1;               // bits 32..32
    /* 0x000 */ unsigned long pad33 : 31;             // bits 33..63
} anon_27_187;

/* anon_15_187 -- @anon15, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34ED41) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long OFX : 16;               // bits 0..15
    /* 0x000 */ unsigned long pad16 : 16;             // bits 16..31
    /* 0x000 */ unsigned long OFY : 16;               // bits 32..47
    /* 0x000 */ unsigned long pad48 : 16;             // bits 48..63
} anon_15_187;

/* anon_45_187 -- @anon45, 0x8 bytes, cs_staffroll_fft.c (DIE 0x352409) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long SCAX0 : 11;             // bits 0..10
    /* 0x000 */ unsigned long pad11 : 5;              // bits 11..15
    /* 0x000 */ unsigned long SCAX1 : 11;             // bits 16..26
    /* 0x000 */ unsigned long pad27 : 5;              // bits 27..31
    /* 0x000 */ unsigned long SCAY0 : 11;             // bits 32..42
    /* 0x000 */ unsigned long pad43 : 5;              // bits 43..47
    /* 0x000 */ unsigned long SCAY1 : 11;             // bits 48..58
    /* 0x000 */ unsigned long pad59 : 5;              // bits 59..63
} anon_45_187;

/* anon_38_187 -- @anon38, 0x8 bytes, cs_staffroll_fft.c (DIE 0x35196A) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long AC : 1;                 // bits 0..0
    /* 0x000 */ unsigned long pad01 : 63;             // bits 1..63
} anon_38_187;

/* anon_23_187 -- @anon23, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34FA20) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long CLAMP : 1;              // bits 0..0
    /* 0x000 */ unsigned long pad01 : 63;             // bits 1..63
} anon_23_187;

/* anon_41_187 -- @anon41, 0x8 bytes, cs_staffroll_fft.c (DIE 0x351F40) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long DTHE : 1;               // bits 0..0
    /* 0x000 */ unsigned long pad01 : 63;             // bits 1..63
} anon_41_187;

/* anon_9_187 -- @anon9, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34E74A) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long ATE : 1;                // bits 0..0
    /* 0x000 */ unsigned long ATST : 3;               // bits 1..3
    /* 0x000 */ unsigned long AREF : 8;               // bits 4..11
    /* 0x000 */ unsigned long AFAIL : 2;              // bits 12..13
    /* 0x000 */ unsigned long DATE : 1;               // bits 14..14
    /* 0x000 */ unsigned long DATM : 1;               // bits 15..15
    /* 0x000 */ unsigned long ZTE : 1;                // bits 16..16
    /* 0x000 */ unsigned long ZTST : 2;               // bits 17..18
    /* 0x000 */ unsigned long pad19 : 45;             // bits 19..63
} anon_9_187;

/* anon_8_187 -- @anon8, 0x80 bytes, cs_staffroll_fft.c (DIE 0x34E4BD) */
typedef struct {   // size 0x80
    /* 0x000 */ anon_4_187 frame1;                    // 0x8
    /* 0x008 */ unsigned long frame1addr;             // 0x8
    /* 0x010 */ anon_27_187 zbuf1;                    // 0x8
    /* 0x018 */ long zbuf1addr;                       // 0x8
    /* 0x020 */ anon_15_187 xyoffset1;                // 0x8
    /* 0x028 */ long xyoffset1addr;                   // 0x8
    /* 0x030 */ anon_45_187 scissor1;                 // 0x8
    /* 0x038 */ long scissor1addr;                    // 0x8
    /* 0x040 */ anon_38_187 prmodecont;               // 0x8
    /* 0x048 */ long prmodecontaddr;                  // 0x8
    /* 0x050 */ anon_23_187 colclamp;                 // 0x8
    /* 0x058 */ long colclampaddr;                    // 0x8
    /* 0x060 */ anon_41_187 dthe;                     // 0x8
    /* 0x068 */ long dtheaddr;                        // 0x8
    /* 0x070 */ anon_9_187 test1;                     // 0x8
    /* 0x078 */ long test1addr;                       // 0x8
} anon_8_187;

/* anon_21_187 -- @anon21, 0x10 bytes, cs_staffroll_fft.c (DIE 0x34F727) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_21_187;

/* anon_10_187 -- @anon10, 0x20 bytes, cs_staffroll_fft.c (DIE 0x34E8EC) */
typedef struct {   // size 0x20
    /* 0x000 */ anon_21_187 bri;                      // 0x10
    /* 0x010 */ unsigned long pri;                    // 0x8
    /* 0x018 */ float zx;                             // 0x4
    /* 0x01C */ float zy;                             // 0x4
} anon_10_187;

/* anon_44_187 -- @anon44, 0x10 bytes, cs_staffroll_fft.c (DIE 0x35228E) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_1_187 *data;                     // 0x4
    /* 0x004 */ unsigned char r0;                     // 0x1
    /* 0x005 */ unsigned char g0;                     // 0x1
    /* 0x006 */ unsigned char b0;                     // 0x1
    /* 0x007 */ unsigned char a0;                     // 0x1
    /* 0x008 */ int vertex_num;                       // 0x4
    /* 0x00C */ int flg;                              // 0x4
} anon_44_187;

/* anon_12_187 -- @anon12, 0x1CA0 bytes, cs_staffroll_fft.c (DIE 0x34EAF8) */
typedef struct {   // size 0x1CA0
    /* 0x000 */ anon_44_187 lspf[4];                  // 0x40
    /* 0x040 */ anon_1_187 l_ver[128];                // 0x600
    /* 0x640 */ anon_1_187 r_ver[128];                // 0x600
    /* 0xC40 */ anon_1_187 cl_ver[128];               // 0x600
    /* 0x1240 */ anon_1_187 cr_ver[128];              // 0x600
    /* 0x1840 */ float down[140];                     // 0x230
    /* 0x1A70 */ float down_speed[140];               // 0x230
} anon_12_187;

/* anon_13_187 -- @anon13, 0x3 bytes, cs_staffroll_fft.c (DIE 0x34EC19) */
typedef struct {   // size 0x3
    /* 0x000 */ unsigned char rgb[3];                 // 0x3
} anon_13_187;

/* anon_14_187 -- @anon14, 0x30 bytes, cs_staffroll_fft.c (DIE 0x34EC5B) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_21_187 rgba;                     // 0x10
    /* 0x010 */ int step;                             // 0x4
    /* 0x014 */ short io_flg;                         // 0x2
    /* 0x016 */ short type;                           // 0x2
    /* 0x018 */ float spd;                            // 0x4
    /* 0x01C */ // 0x4 bytes padding
    /* 0x020 */ unsigned long z;                      // 0x8
    /* 0x028 */ // 0x8 bytes padding
} anon_14_187;

/* anon_16_187 -- @anon16, 0x1C bytes, cs_staffroll_fft.c (DIE 0x34EE0D) */
typedef struct {   // size 0x1C
    /* 0x000 */ int disp;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int timer;                            // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char r1;                     // 0x1
    /* 0x010 */ unsigned char g1;                     // 0x1
    /* 0x011 */ unsigned char b1;                     // 0x1
    /* 0x012 */ unsigned char r2;                     // 0x1
    /* 0x013 */ unsigned char g2;                     // 0x1
    /* 0x014 */ unsigned char b2;                     // 0x1
    /* 0x015 */ // 0x3 bytes padding
    /* 0x018 */ unsigned int *disp_work;              // 0x4
} anon_16_187;

/* anon_17_187 -- @anon17, 0x5140 bytes, cs_staffroll_fft.c (DIE 0x34EFD1) */
typedef struct {   // size 0x5140
    /* 0x000 */ anon_1_187 u_Rch_wire0[100];          // 0x4B0
    /* 0x4B0 */ anon_1_187 d_Rch_wire0[100];          // 0x4B0
    /* 0x960 */ anon_1_187 u_Rch_pwire0[100];         // 0x4B0
    /* 0xE10 */ anon_1_187 d_Rch_pwire0[100];         // 0x4B0
    /* 0x12C0 */ anon_1_187 u_Lch_wire0[100];         // 0x4B0
    /* 0x1770 */ anon_1_187 d_Lch_wire0[100];         // 0x4B0
    /* 0x1C20 */ anon_1_187 u_Lch_pwire0[100];        // 0x4B0
    /* 0x20D0 */ anon_1_187 d_Lch_pwire0[100];        // 0x4B0
    /* 0x2580 */ anon_1_187 u_Rch_wire1[100];         // 0x4B0
    /* 0x2A30 */ anon_1_187 d_Rch_wire1[100];         // 0x4B0
    /* 0x2EE0 */ anon_1_187 u_Rch_pwire1[100];        // 0x4B0
    /* 0x3390 */ anon_1_187 d_Rch_pwire1[100];        // 0x4B0
    /* 0x3840 */ anon_1_187 u_Lch_wire1[100];         // 0x4B0
    /* 0x3CF0 */ anon_1_187 d_Lch_wire1[100];         // 0x4B0
    /* 0x41A0 */ anon_1_187 u_Lch_pwire1[100];        // 0x4B0
    /* 0x4650 */ anon_1_187 d_Lch_pwire1[100];        // 0x4B0
    /* 0x4B00 */ float Rch_peak[100];                 // 0x190
    /* 0x4C90 */ float Lch_peak[100];                 // 0x190
    /* 0x4E20 */ float Rch_peak_sp[100];              // 0x190
    /* 0x4FB0 */ float Lch_peak_sp[100];              // 0x190
} anon_17_187;

/* anon_18_187 -- @anon18, 0x44 bytes, cs_staffroll_fft.c (DIE 0x34F361) */
typedef struct {   // size 0x44
    /* 0x000 */ int x[4];                             // 0x10
    /* 0x010 */ int y[4];                             // 0x10
    /* 0x020 */ int u[4];                             // 0x10
    /* 0x030 */ int v[4];                             // 0x10
    /* 0x040 */ unsigned char alpha;                  // 0x1
    /* 0x041 */ unsigned char bri;                    // 0x1
    /* 0x042 */ unsigned char request;                // 0x1
    /* 0x043 */ unsigned char pad[1];                 // 0x1
} anon_18_187;

/* anon_19_187 -- @anon19, 0x4 bytes, cs_staffroll_fft.c (DIE 0x34F4AD) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned int DIR : 1;                 // bits 0..0
    /* 0x000 */ unsigned int p0 : 1;                  // bits 1..1
    /* 0x000 */ unsigned int MOD : 2;                 // bits 2..3
    /* 0x000 */ unsigned int ASP : 2;                 // bits 4..5
    /* 0x000 */ unsigned int TTE : 1;                 // bits 6..6
    /* 0x000 */ unsigned int TIE : 1;                 // bits 7..7
    /* 0x000 */ unsigned int STR : 1;                 // bits 8..8
    /* 0x000 */ unsigned int p1 : 7;                  // bits 9..15
    /* 0x000 */ unsigned int TAG : 16;                // bits 16..31
} anon_19_187;

/* anon_20_187 -- @anon20, 0x8 bytes, cs_staffroll_fft.c (DIE 0x34F68F) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long X : 16;                 // bits 0..15
    /* 0x000 */ unsigned long Y : 16;                 // bits 16..31
    /* 0x000 */ unsigned long Z : 32;                 // bits 32..63
} anon_20_187;

/* anon_22_187 -- @anon22, 0x1C bytes, cs_staffroll_fft.c (DIE 0x34F8A3) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_29_187 x0;                       // 0x4
    /* 0x004 */ anon_29_187 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_22_187;

/* anon_24_187 -- @anon24, 0x1C bytes, cs_staffroll_fft.c (DIE 0x34FAE2) */
typedef struct {   // size 0x1C
    /* 0x000 */ int tbp;                              // 0x4
    /* 0x004 */ int psm;                              // 0x4
    /* 0x008 */ int cbp;                              // 0x4
    /* 0x00C */ int cpsm;                             // 0x4
    /* 0x010 */ int width;                            // 0x4
    /* 0x014 */ int height;                           // 0x4
    /* 0x018 */ int colors;                           // 0x4
} anon_24_187;

/* anon_25_187 -- @anon25, 0x80 bytes, cs_staffroll_fft.c (DIE 0x34FCA3) */
typedef struct {   // size 0x80
    /* 0x000 */ anon_4_187 frame2;                    // 0x8
    /* 0x008 */ unsigned long frame2addr;             // 0x8
    /* 0x010 */ anon_27_187 zbuf2;                    // 0x8
    /* 0x018 */ long zbuf2addr;                       // 0x8
    /* 0x020 */ anon_15_187 xyoffset2;                // 0x8
    /* 0x028 */ long xyoffset2addr;                   // 0x8
    /* 0x030 */ anon_45_187 scissor2;                 // 0x8
    /* 0x038 */ long scissor2addr;                    // 0x8
    /* 0x040 */ anon_38_187 prmodecont;               // 0x8
    /* 0x048 */ long prmodecontaddr;                  // 0x8
    /* 0x050 */ anon_23_187 colclamp;                 // 0x8
    /* 0x058 */ long colclampaddr;                    // 0x8
    /* 0x060 */ anon_41_187 dthe;                     // 0x8
    /* 0x068 */ long dtheaddr;                        // 0x8
    /* 0x070 */ anon_9_187 test2;                     // 0x8
    /* 0x078 */ long test2addr;                       // 0x8
} anon_25_187;

/* anon_39_187 -- @anon39, 0x10 bytes, cs_staffroll_fft.c (DIE 0x351A03) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned long NLOOP : 15;             // bits 0..14
    /* 0x000 */ unsigned long EOP : 1;                // bits 15..15
    /* 0x000 */ unsigned long pad16 : 16;             // bits 16..31
    /* 0x000 */ unsigned long id : 14;                // bits 32..45
    /* 0x000 */ unsigned long PRE : 1;                // bits 46..46
    /* 0x000 */ unsigned long PRIM : 11;              // bits 47..57
    /* 0x000 */ unsigned long FLG : 2;                // bits 58..59
    /* 0x000 */ unsigned long NREG : 4;               // bits 60..63
    /* 0x008 */ unsigned long REGS0 : 4;              // bits 0..3
    /* 0x008 */ unsigned long REGS1 : 4;              // bits 4..7
    /* 0x008 */ unsigned long REGS2 : 4;              // bits 8..11
    /* 0x008 */ unsigned long REGS3 : 4;              // bits 12..15
    /* 0x008 */ unsigned long REGS4 : 4;              // bits 16..19
    /* 0x008 */ unsigned long REGS5 : 4;              // bits 20..23
    /* 0x008 */ unsigned long REGS6 : 4;              // bits 24..27
    /* 0x008 */ unsigned long REGS7 : 4;              // bits 28..31
    /* 0x008 */ unsigned long REGS8 : 4;              // bits 32..35
    /* 0x008 */ unsigned long REGS9 : 4;              // bits 36..39
    /* 0x008 */ unsigned long REGS10 : 4;             // bits 40..43
    /* 0x008 */ unsigned long REGS11 : 4;             // bits 44..47
    /* 0x008 */ unsigned long REGS12 : 4;             // bits 48..51
    /* 0x008 */ unsigned long REGS13 : 4;             // bits 52..55
    /* 0x008 */ unsigned long REGS14 : 4;             // bits 56..59
    /* 0x008 */ unsigned long REGS15 : 4;             // bits 60..63
} anon_39_187;

/* anon_33_187 -- @anon33, 0x8 bytes, cs_staffroll_fft.c (DIE 0x350E0D) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long PRIM : 3;               // bits 0..2
    /* 0x000 */ unsigned long IIP : 1;                // bits 3..3
    /* 0x000 */ unsigned long TME : 1;                // bits 4..4
    /* 0x000 */ unsigned long FGE : 1;                // bits 5..5
    /* 0x000 */ unsigned long ABE : 1;                // bits 6..6
    /* 0x000 */ unsigned long AA1 : 1;                // bits 7..7
    /* 0x000 */ unsigned long FST : 1;                // bits 8..8
    /* 0x000 */ unsigned long CTXT : 1;               // bits 9..9
    /* 0x000 */ unsigned long FIX : 1;                // bits 10..10
    /* 0x000 */ unsigned long pad11 : 53;             // bits 11..63
} anon_33_187;

/* anon_40_187 -- @anon40, 0x8 bytes, cs_staffroll_fft.c (DIE 0x351E62) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int R : 8;                   // bits 0..7
    /* 0x000 */ unsigned int G : 8;                   // bits 8..15
    /* 0x000 */ unsigned int B : 8;                   // bits 16..23
    /* 0x000 */ unsigned int A : 8;                   // bits 24..31
    /* 0x004 */ float Q;                              // 0x4
} anon_40_187;

/* anon_32_187 -- @anon32, 0x60 bytes, cs_staffroll_fft.c (DIE 0x350C0F) */
typedef struct {   // size 0x60
    /* 0x000 */ anon_9_187 testa;                     // 0x8
    /* 0x008 */ long testaaddr;                       // 0x8
    /* 0x010 */ anon_33_187 prim;                     // 0x8
    /* 0x018 */ long primaddr;                        // 0x8
    /* 0x020 */ anon_40_187 rgbaq;                    // 0x8
    /* 0x028 */ long rgbaqaddr;                       // 0x8
    /* 0x030 */ anon_20_187 xyz2a;                    // 0x8
    /* 0x038 */ long xyz2aaddr;                       // 0x8
    /* 0x040 */ anon_20_187 xyz2b;                    // 0x8
    /* 0x048 */ long xyz2baddr;                       // 0x8
    /* 0x050 */ anon_9_187 testb;                     // 0x8
    /* 0x058 */ long testbaddr;                       // 0x8
} anon_32_187;

/* anon_37_187 -- @anon37, 0x330 bytes, cs_staffroll_fft.c (DIE 0x3517B3) */
typedef struct {   // size 0x330
    /* 0x000 */ anon_3_187 disp[2];                   // 0x50
    /* 0x050 */ anon_39_187 giftag0;                  // 0x10
    /* 0x060 */ anon_8_187 draw01;                    // 0x80
    /* 0x0E0 */ anon_25_187 draw02;                   // 0x80
    /* 0x160 */ anon_32_187 clear0;                   // 0x60
    /* 0x1C0 */ anon_39_187 giftag1;                  // 0x10
    /* 0x1D0 */ anon_8_187 draw11;                    // 0x80
    /* 0x250 */ anon_25_187 draw12;                   // 0x80
    /* 0x2D0 */ anon_32_187 clear1;                   // 0x60
} anon_37_187;

/* anon_28_187 -- @anon28, 0x90 bytes, cs_staffroll_fft.c (DIE 0x350430) */
typedef struct {   // size 0x90
    /* 0x000 */ anon_19_187 chcr;                     // 0x4
    /* 0x004 */ unsigned int p0[3];                   // 0xC
    /* 0x010 */ void *madr;                           // 0x4
    /* 0x014 */ unsigned int p1[3];                   // 0xC
    /* 0x020 */ unsigned int qwc;                     // 0x4
    /* 0x024 */ unsigned int p2[3];                   // 0xC
    /* 0x030 */ struct _sceDmaTag *tadr;              // 0x4
    /* 0x034 */ unsigned int p3[3];                   // 0xC
    /* 0x040 */ void *as0;                            // 0x4
    /* 0x044 */ unsigned int p4[3];                   // 0xC
    /* 0x050 */ void *as1;                            // 0x4
    /* 0x054 */ unsigned int p5[3];                   // 0xC
    /* 0x060 */ unsigned int p6[4];                   // 0x10
    /* 0x070 */ unsigned int p7[4];                   // 0x10
    /* 0x080 */ void *sadr;                           // 0x4
    /* 0x084 */ unsigned int p8[3];                   // 0xC
} anon_28_187;

/* anon_36_187 -- @anon36, 0x8 bytes, cs_staffroll_fft.c (DIE 0x35168B) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_36_187;

/* anon_26_187 -- @anon26, 0x530 bytes, cs_staffroll_fft.c (DIE 0x34FF31) */
typedef struct {   // size 0x530
    /* 0x000 */ anon_3_187 disp_env;                  // 0x28
    /* 0x028 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x030 */ anon_39_187 draw_gtag;                // 0x10
    /* 0x040 */ anon_8_187 draw_env;                  // 0x80
    /* 0x0C0 */ anon_37_187 db;                       // 0x330
    /* 0x3F0 */ anon_28_187 *dmaVif0;                 // 0x4
    /* 0x3F4 */ anon_28_187 *dmaVif1;                 // 0x4
    /* 0x3F8 */ anon_28_187 *dmaGif;                  // 0x4
    /* 0x3FC */ int odev;                             // 0x4
    /* 0x400 */ int frip;                             // 0x4
    /* 0x404 */ int clear;                            // 0x4
    /* 0x408 */ int disp_adj_x;                       // 0x4
    /* 0x40C */ int disp_adj_y;                       // 0x4
    /* 0x410 */ int flickerfree;                      // 0x4
    /* 0x414 */ int noclear_cnt;                      // 0x4
    /* 0x418 */ anon_6_187 bg_color;                  // 0x4
    /* 0x41C */ // 0x4 bytes padding
    /* 0x420 */ anon_0_187 reg_info;                  // 0x58
    /* 0x478 */ // 0x8 bytes padding
    /* 0x480 */ anon_10_187 font_env;                 // 0x20
    /* 0x4A0 */ anon_14_187 fade_env;                 // 0x30
    /* 0x4D0 */ anon_36_187 cur_draw_area;            // 0x8
    /* 0x4D8 */ int get_frame;                        // 0x4
    /* 0x4DC */ int capture;                          // 0x4
    /* 0x4E0 */ anon_18_187 cframe;                   // 0x44
    /* 0x524 */ // 0xC bytes padding
} anon_26_187;

/* anon_30_187 -- @anon30, 0x960 bytes, cs_staffroll_fft.c (DIE 0x350809) */
typedef struct {   // size 0x960
    /* 0x000 */ int peak_time[200];                   // 0x320
    /* 0x320 */ float down_l[100];                    // 0x190
    /* 0x4B0 */ float down_r[100];                    // 0x190
    /* 0x640 */ float down_speed_l[100];              // 0x190
    /* 0x7D0 */ float down_speed_r[100];              // 0x190
} anon_30_187;

/* anon_31_187 -- @anon31, 0x30 bytes, cs_staffroll_fft.c (DIE 0x3508F1) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_29_187 x0;                       // 0x4
    /* 0x004 */ anon_29_187 y0;                       // 0x4
    /* 0x008 */ anon_29_187 x1;                       // 0x4
    /* 0x00C */ anon_29_187 y1;                       // 0x4
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
} anon_31_187;

/* anon_34_187 -- @anon34, 0x640 bytes, cs_staffroll_fft.c (DIE 0x350FD5) */
typedef struct {   // size 0x640
    /* 0x000 */ float Rch_peak[100];                  // 0x190
    /* 0x190 */ float Lch_peak[100];                  // 0x190
    /* 0x320 */ float Rch_peak_sp[100];               // 0x190
    /* 0x4B0 */ float Lch_peak_sp[100];               // 0x190
} anon_34_187;

/* anon_35_187 -- @anon35, 0x68 bytes, cs_staffroll_fft.c (DIE 0x3511B7) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_29_187 x0;                       // 0x4
    /* 0x004 */ anon_29_187 y0;                       // 0x4
    /* 0x008 */ anon_29_187 x1;                       // 0x4
    /* 0x00C */ anon_29_187 y1;                       // 0x4
    /* 0x010 */ anon_29_187 x2;                       // 0x4
    /* 0x014 */ anon_29_187 y2;                       // 0x4
    /* 0x018 */ anon_29_187 x3;                       // 0x4
    /* 0x01C */ anon_29_187 y3;                       // 0x4
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
} anon_35_187;


/* variables (4) */
anon_16_187 *p_end_fft_disp_w;                                   /* @0x002DDE70 size 0x4 */
static anon_13_187 colset[6];                                    /* @0x00800520 size 0x12 */
anon_26_187 gs_w;                                                /* @0x0057EE90 size 0x530 */
static anon_16_187 fft_disp_work;                                /* @0x00807DE0 size 0x1C */

/* functions defined (9) */
static void DispFFTFlower1(anon_2_187 *pstf);                    /* 0x007FA560-0x007FAAB4 lines 1456-1570 */
static void DispFFTMeter1(anon_2_187 *pstf);                     /* 0x007FAAC0-0x007FB2EC lines 1216-1428 */
static void DispFFTWire2(anon_2_187 *pstf);                      /* 0x007FB2F0-0x007FBDCC lines 944-1199 */
static void DispFFTWire1(anon_2_187 *pstf);                      /* 0x007FBDD0-0x007FC92C lines 679-935 */
static void DispFFTMeter2(anon_2_187 *pstf);                     /* 0x007FC930-0x007FD208 lines 443-634 */
void StaffRollFFTDisp(anon_2_187 *pstf);                         /* 0x007FD210-0x007FD434 lines 281-418 */
void EdBkEffectColSet(anon_2_187 *pstf);                         /* 0x007FD440-0x007FD53C lines 178-207 */
void StaffRollCapScreen(void);                                   /* 0x007FD540-0x007FD6CC lines 130-169 */
void StaffRollFFTDispInit(void);                                 /* 0x007FD6D0-0x007FD764 lines 82-101 */

#endif /* DDR_UNIT_src_CS_staffroll_cs_staffroll_fft_c_H */
