/*
 * C:\work2\usaex2\src\CS\staffroll\cs_staffroll_scrl.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 13 functions, code 0x007FF250-0x0080005C
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
#ifndef DDR_UNIT_src_CS_staffroll_cs_staffroll_scrl_c_H
#define DDR_UNIT_src_CS_staffroll_cs_staffroll_scrl_c_H

/* anonymous types (8) */

/* anon_0_190 -- @anon0, 0x78 bytes, cs_staffroll_scrl.c (DIE 0x3588B5) */
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
} anon_0_190;

/* anon_1_190 -- @anon1, 0x48 bytes, cs_staffroll_scrl.c (DIE 0x358CD2) */
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
} anon_1_190;

/* anon_x358f78_190 -- @enum, 0x1 bytes, cs_staffroll_scrl.c (DIE 0x358F78) */
typedef enum {   // size 0x1
    SRE_SCRL_STEP_KANJI_FONT_SETUP_INIT = 0,
    SRE_SCRL_STEP_KANJI_FONT_SETUP = 1,
} anon_x358f78_190;

/* anon_3_190 -- @anon3, 0x4 bytes, cs_staffroll_scrl.c (DIE 0x35921A) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_190;

/* anon_2_190 -- @anon2, 0x24 bytes, cs_staffroll_scrl.c (DIE 0x359025) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_3_190 x0;                        // 0x4
    /* 0x004 */ anon_3_190 y0;                        // 0x4
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
} anon_2_190;

/* anon_x3591b9_190 -- @enum, 0x1 bytes, cs_staffroll_scrl.c (DIE 0x3591B9) */
typedef enum {   // size 0x1
    SRE_SCRL_STEP_INIT = 0,
    SRE_SCRL_STEP_MAIN = 1,
    SRE_SCRL_STEP_TERMINATE = 2,
} anon_x3591b9_190;

/* anon_4_190 -- @anon4, 0x30 bytes, cs_staffroll_scrl.c (DIE 0x359277) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_3_190 x0;                        // 0x4
    /* 0x004 */ anon_3_190 y0;                        // 0x4
    /* 0x008 */ anon_3_190 x1;                        // 0x4
    /* 0x00C */ anon_3_190 y1;                        // 0x4
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
} anon_4_190;

/* anon_5_190 -- @anon5, 0x8 bytes, cs_staffroll_scrl.c (DIE 0x35946C) */
typedef struct {   // size 0x8
    /* 0x000 */ char *str;                            // 0x4
    /* 0x004 */ int comm;                             // 0x4
} anon_5_190;


/* variables (9) */
static float scrstr_spctable[11];                                /* @0x008005D0 size 0x2C */
static anon_5_190 scrstr_data[294];                              /* @0x00800600 size 0x930 */
static unsigned char isreInitStep;                               /* @0x002DE5EC size 0x1 */
static unsigned char isreMainStep;                               /* @0x002DE5F0 size 0x1 */
static float fsreScrollSpd;                                      /* @0x002DE5F4 size 0x4 */
void (*csStaffRollScrlDrawFunc[10])(float, unsigned char *);     /* @0x00800F30 size 0x28 */
anon_0_190 *ll_pstf;                                             /* @0x002DE5F8 size 0x4 */
anon_x3591b9_190 SRE_SCRL_STEP;                                  /* not allocated size 0x1 */
anon_x358f78_190 SRE_FONT_READ_STEP;                             /* not allocated size 0x1 */

/* functions defined (13) */
void *csStaffRollScrlDrawFunc_Copyright(float pos_y);            /* 0x007FF250-0x007FF3D0 lines 812-839 */
void *csStaffRollScrlDrawFunc_Tyo(float pos_y);                  /* 0x007FF3D0-0x007FF4EC lines 780-808 */
void *csStaffRollScrlDrawFunc_Dolby(float pos_y);                /* 0x007FF4F0-0x007FF678 lines 747-775 */
void *csStaffRollScrlDrawFunc_Xax(float pos_y);                  /* 0x007FF680-0x007FF808 lines 715-742 */
void *csStaffRollScrlDrawFunc_Konami(float pos_y);               /* 0x007FF810-0x007FFB58 lines 655-711 */
void *csStaffRollScrlDrawFunc_Name(float pos_y, unsigned char *str); /* 0x007FFB60-0x007FFBB4 lines 639-651 */
void *csStaffRollScrlDrawFunc_Title_E(float pos_y, unsigned char *str); /* 0x007FFBC0-0x007FFC14 lines 624-634 */
void *csStaffRollScrlDrawFunc_Title_A(float pos_y, unsigned char *str); /* 0x007FFC20-0x007FFC74 lines 610-620 */
void *csStaffRollScrlDrawFunc_Title_C(float pos_y, unsigned char *str); /* 0x007FFC80-0x007FFCD4 lines 596-606 */
void *csStaffRollScrlDrawFunc_License(float pos_y, unsigned char *str); /* 0x007FFCE0-0x007FFD30 lines 580-593 */
int csStaffRollScrlAct(anon_0_190 *pstf);                        /* 0x007FFD30-0x007FFE74 lines 503-530 */
int csStaffRollScrlMain(anon_0_190 *pstf);                       /* 0x007FFE80-0x007FFFBC lines 471-488 */
void csStaffRollScrlInit(void);                                  /* 0x007FFFC0-0x0080005C lines 410-424 */

#endif /* DDR_UNIT_src_CS_staffroll_cs_staffroll_scrl_c_H */
