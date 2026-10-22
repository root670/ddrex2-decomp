/*
 * C:\work2\usaex2\src\CS\staffroll\cs_staffroll_mov.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 4 functions, code 0x007FD770-0x007FE058
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
#ifndef DDR_UNIT_src_CS_staffroll_cs_staffroll_mov_c_H
#define DDR_UNIT_src_CS_staffroll_cs_staffroll_mov_c_H

/* anonymous types (8) */

/* anon_0_188 -- @anon0, 0x30 bytes, cs_staffroll_mov.c (DIE 0x355112) */
typedef struct {   // size 0x30
    /* 0x000 */ unsigned char *data;                  // 0x4
    /* 0x004 */ int datasize;                         // 0x4
    /* 0x008 */ unsigned int width;                   // 0x4
    /* 0x00C */ unsigned int height;                  // 0x4
    /* 0x010 */ unsigned int nframes;                 // 0x4
    /* 0x014 */ unsigned int frame_cnt;               // 0x4
    /* 0x018 */ unsigned int mbx;                     // 0x4
    /* 0x01C */ unsigned int mby;                     // 0x4
    /* 0x020 */ unsigned int tbp;                     // 0x4
    /* 0x024 */ unsigned int tbw;                     // 0x4
    /* 0x028 */ int tw;                               // 0x4
    /* 0x02C */ int th;                               // 0x4
} anon_0_188;

/* anon_x3552c7_188 -- @enum, 0x1 bytes, cs_staffroll_mov.c (DIE 0x3552C7) */
typedef enum {   // size 0x1
    SRE_MV_STEP_INIT = 0,
    SRE_MV_STEP_READ = 1,
    SRE_MV_STEP_WAIT = 2,
    SRE_MV_STEP_TERMINATE = 3,
} anon_x3552c7_188;

/* anon_1_188 -- @anon1, 0x78 bytes, cs_staffroll_mov.c (DIE 0x355334) */
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
} anon_1_188;

/* anon_x355751_188 -- @enum, 0x1 bytes, cs_staffroll_mov.c (DIE 0x355751) */
typedef enum {   // size 0x1
    SRE_MVREAD_STEP_WAIT = 0,
    SRE_MVREAD_STEP_INIT = 1,
    SRE_MVREAD_STEP_READ = 2,
    SRE_MVREAD_STEP_SET = 3,
    SRE_MVREAD_STEP_TERMINATE = 4,
} anon_x355751_188;

/* anon_2_188 -- @anon2, 0x4 bytes, cs_staffroll_mov.c (DIE 0x35584F) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_2_188;

/* anon_3_188 -- @anon3, 0x68 bytes, cs_staffroll_mov.c (DIE 0x3558D3) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_2_188 x0;                        // 0x4
    /* 0x004 */ anon_2_188 y0;                        // 0x4
    /* 0x008 */ anon_2_188 x1;                        // 0x4
    /* 0x00C */ anon_2_188 y1;                        // 0x4
    /* 0x010 */ anon_2_188 x2;                        // 0x4
    /* 0x014 */ anon_2_188 y2;                        // 0x4
    /* 0x018 */ anon_2_188 x3;                        // 0x4
    /* 0x01C */ anon_2_188 y3;                        // 0x4
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
} anon_3_188;

/* anon_4_188 -- @anon4, 0x8 bytes, cs_staffroll_mov.c (DIE 0x355C86) */
typedef struct {   // size 0x8
    /* 0x000 */ float time;                           // 0x4
    /* 0x004 */ short MvNo;                           // 0x2
    /* 0x006 */ // 0x2 bytes padding
} anon_4_188;

/* anon_5_188 -- @anon5, 0x20 bytes, cs_staffroll_mov.c (DIE 0x355D0D) */
typedef struct {   // size 0x20
    /* 0x000 */ anon_2_188 x0;                        // 0x4
    /* 0x004 */ anon_2_188 y0;                        // 0x4
    /* 0x008 */ anon_2_188 x1;                        // 0x4
    /* 0x00C */ anon_2_188 y1;                        // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ int flg;                              // 0x4
} anon_5_188;


/* variables (8) */
static int isreMainStep;                                         /* @0x002DE5B0 size 0x4 */
static int isreReadStep;                                         /* @0x002DE5B4 size 0x4 */
static int current_buff;                                         /* @0x002DE5B8 size 0x4 */
unsigned char *sre_ip[11];                                       /* @0x00800540 size 0x2C */
anon_4_188 sre_mvseq[12];                                        /* @0x00800570 size 0x60 */
int mv_enable;                                                   /* @0x002DE5C0 size 0x4 */
anon_x355751_188 SRE_MVREAD_STEP;                                /* not allocated size 0x1 */
anon_x3552c7_188 SRE_MV_STEP;                                    /* not allocated size 0x1 */

/* functions defined (4) */
void csStaffRollMovieDraw(anon_1_188 *pstf);                     /* 0x007FD770-0x007FDB5C lines 239-312 */
int csStaffRollMovieRead(int idx);                               /* 0x007FDB60-0x007FDD7C lines 168-222 */
int csStaffRollMovieMain(anon_1_188 *pstf);                      /* 0x007FDD80-0x007FE000 lines 100-156 */
void csStaffRollMovieInit(anon_1_188 *pstf);                     /* 0x007FE000-0x007FE058 lines 82-93 */

#endif /* DDR_UNIT_src_CS_staffroll_cs_staffroll_mov_c_H */
