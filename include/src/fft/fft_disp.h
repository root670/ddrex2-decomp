/*
 * C:\work2\usaex2\src\fft\fft_disp.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x001E4610-0x001E758C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_fft_fft_disp_c_H
#define DDR_UNIT_src_fft_fft_disp_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (17) */

/* anon_7_39 -- @anon7, 0x4 bytes, fft_disp.c (DIE 0x62FCB) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_7_39;

/* anon_0_39 -- @anon0, 0xC bytes, fft_disp.c (DIE 0x5E636) */
typedef struct {   // size 0xC
    /* 0x000 */ anon_7_39 x0;                         // 0x4
    /* 0x004 */ anon_7_39 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
} anon_0_39;

/* anon_1_39 -- @anon1, 0x3 bytes, fft_disp.c (DIE 0x5E6B6) */
typedef struct {   // size 0x3
    /* 0x000 */ unsigned char rgb[3];                 // 0x3
} anon_1_39;

/* anon_2_39 -- @anon2, 0x1C bytes, fft_disp.c (DIE 0x6102A) */
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
} anon_2_39;

/* anon_21_39 -- @anon21, 0x10 bytes, fft_disp.c (DIE 0x65899) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_0_39 *data;                      // 0x4
    /* 0x004 */ unsigned char r0;                     // 0x1
    /* 0x005 */ unsigned char g0;                     // 0x1
    /* 0x006 */ unsigned char b0;                     // 0x1
    /* 0x007 */ unsigned char a0;                     // 0x1
    /* 0x008 */ int vertex_num;                       // 0x4
    /* 0x00C */ int flg;                              // 0x4
} anon_21_39;

/* anon_3_39 -- @anon3, 0x1CA0 bytes, fft_disp.c (DIE 0x61558) */
typedef struct {   // size 0x1CA0
    /* 0x000 */ anon_21_39 lspf[4];                   // 0x40
    /* 0x040 */ anon_0_39 l_ver[128];                 // 0x600
    /* 0x640 */ anon_0_39 r_ver[128];                 // 0x600
    /* 0xC40 */ anon_0_39 cl_ver[128];                // 0x600
    /* 0x1240 */ anon_0_39 cr_ver[128];               // 0x600
    /* 0x1840 */ float down[140];                     // 0x230
    /* 0x1A70 */ float down_speed[140];               // 0x230
} anon_3_39;

/* anon_5_39 -- @anon5, 0x1C bytes, fft_disp.c (DIE 0x61AC6) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_7_39 x0;                         // 0x4
    /* 0x004 */ anon_7_39 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_5_39;

/* anon_6_39 -- @anon6, 0x5140 bytes, fft_disp.c (DIE 0x61C8E) */
typedef struct {   // size 0x5140
    /* 0x000 */ anon_0_39 u_Rch_wire0[100];           // 0x4B0
    /* 0x4B0 */ anon_0_39 d_Rch_wire0[100];           // 0x4B0
    /* 0x960 */ anon_0_39 u_Rch_pwire0[100];          // 0x4B0
    /* 0xE10 */ anon_0_39 d_Rch_pwire0[100];          // 0x4B0
    /* 0x12C0 */ anon_0_39 u_Lch_wire0[100];          // 0x4B0
    /* 0x1770 */ anon_0_39 d_Lch_wire0[100];          // 0x4B0
    /* 0x1C20 */ anon_0_39 u_Lch_pwire0[100];         // 0x4B0
    /* 0x20D0 */ anon_0_39 d_Lch_pwire0[100];         // 0x4B0
    /* 0x2580 */ anon_0_39 u_Rch_wire1[100];          // 0x4B0
    /* 0x2A30 */ anon_0_39 d_Rch_wire1[100];          // 0x4B0
    /* 0x2EE0 */ anon_0_39 u_Rch_pwire1[100];         // 0x4B0
    /* 0x3390 */ anon_0_39 d_Rch_pwire1[100];         // 0x4B0
    /* 0x3840 */ anon_0_39 u_Lch_wire1[100];          // 0x4B0
    /* 0x3CF0 */ anon_0_39 d_Lch_wire1[100];          // 0x4B0
    /* 0x41A0 */ anon_0_39 u_Lch_pwire1[100];         // 0x4B0
    /* 0x4650 */ anon_0_39 d_Lch_pwire1[100];         // 0x4B0
    /* 0x4B00 */ float Rch_peak[100];                 // 0x190
    /* 0x4C90 */ float Lch_peak[100];                 // 0x190
    /* 0x4E20 */ float Rch_peak_sp[100];              // 0x190
    /* 0x4FB0 */ float Lch_peak_sp[100];              // 0x190
} anon_6_39;

/* anon_8_39 -- @anon8, 0xD40 bytes, fft_disp.c (DIE 0x63098) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_8_39;

/* anon_9_39 -- @anon9, 0x10 bytes, fft_disp.c (DIE 0x6353A) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_7_39 x0;                         // 0x4
    /* 0x004 */ anon_7_39 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_9_39;

/* anon_10_39 -- @anon10, 0x14 bytes, fft_disp.c (DIE 0x6365A) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_10_39;

/* anon_11_39 -- @anon11, 0x960 bytes, fft_disp.c (DIE 0x638BB) */
typedef struct {   // size 0x960
    /* 0x000 */ int peak_time[200];                   // 0x320
    /* 0x320 */ float down_l[100];                    // 0x190
    /* 0x4B0 */ float down_r[100];                    // 0x190
    /* 0x640 */ float down_speed_l[100];              // 0x190
    /* 0x7D0 */ float down_speed_r[100];              // 0x190
} anon_11_39;

/* anon_12_39 -- @anon12, 0xC bytes, fft_disp.c (DIE 0x63B39) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_12_39;

/* anon_13_39 -- @anon13, 0x640 bytes, fft_disp.c (DIE 0x63C80) */
typedef struct {   // size 0x640
    /* 0x000 */ float Rch_peak[100];                  // 0x190
    /* 0x190 */ float Lch_peak[100];                  // 0x190
    /* 0x320 */ float Rch_peak_sp[100];               // 0x190
    /* 0x4B0 */ float Lch_peak_sp[100];               // 0x190
} anon_13_39;

/* anon_16_39 -- @anon16, 0x4 bytes, fft_disp.c (DIE 0x6428C) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_16_39;

/* anon_15_39 -- @anon15, 0x4 bytes, fft_disp.c (DIE 0x641E5) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_16_39 s;                         // 0x4
} anon_15_39;

/* anon_17_39 -- @anon17, 0x12E0 bytes, fft_disp.c (DIE 0x64506) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_12_39 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_17_39;


/* variables (5) */
anon_2_39 *p_fft_disp_w;                                         /* @0x002DDA7C size 0x4 */
anon_1_39 colset[8];                                             /* @0x002B8B70 size 0x18 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
static anon_2_39 fft_disp_work;                                  /* @0x00713DD0 size 0x1C */

/* functions defined (9) */
static void DispFFTFlower1(void);                                /* 0x001E4610-0x001E4B8C lines 1256-1370 */
static void DispFFTMeter1(void);                                 /* 0x001E4B90-0x001E53C4 lines 1016-1228 */
static void DispFFTWire2(void);                                  /* 0x001E53D0-0x001E5EA4 lines 744-999 */
static void DispFFTWire1(void);                                  /* 0x001E5EB0-0x001E6A34 lines 479-735 */
static void DispFFTMeter2(void);                                 /* 0x001E6A40-0x001E7318 lines 243-434 */
void FFTDisp(void);                                              /* 0x001E7320-0x001E73D4 lines 175-218 */
int SetFFTDispWork(unsigned int *addr);                          /* 0x001E73E0-0x001E7410 lines 160-167 */
void BkEffectTypeSet(void);                                      /* 0x001E7410-0x001E74B4 lines 132-151 */
void BkEffectColSet(void);                                       /* 0x001E74C0-0x001E758C lines 102-124 */

#endif /* DDR_UNIT_src_fft_fft_disp_c_H */
