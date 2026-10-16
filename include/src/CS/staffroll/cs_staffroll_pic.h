/*
 * C:\work2\usaex2\src\CS\staffroll\cs_staffroll_pic.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 12 functions, code 0x007FE060-0x007FF248
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_staffroll_cs_staffroll_pic_c_H
#define DDR_UNIT_src_CS_staffroll_cs_staffroll_pic_c_H

/* anonymous types (12) */

/* anon_0_189 -- @anon0, 0x78 bytes, cs_staffroll_pic.c (DIE 0x3567B7) */
struct anon_0_189 {   // size 0x78
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
};

/* anon_x356bd4_189 -- @enum, 0x1 bytes, cs_staffroll_pic.c (DIE 0x356BD4) */
enum anon_x356bd4_189 {   // size 0x1
    SRE_PIC_STEP_INIT = 0,
    SRE_PIC_STEP_MAIN = 1,
    SRE_PIC_STEP_TERMINATE = 2,
};

/* anon_x356c32_189 -- @enum, 0x1 bytes, cs_staffroll_pic.c (DIE 0x356C32) */
enum anon_x356c32_189 {   // size 0x1
    SRE_PIC_INIT_STEP_PARAM = 0,
    SRE_PIC_INIT_STEP_READ = 1,
    SRE_PIC_INIT_STEP_TERMINATE = 2,
};

/* anon_x356ca0_189 -- @enum, 0x1 bytes, cs_staffroll_pic.c (DIE 0x356CA0) */
enum anon_x356ca0_189 {   // size 0x1
    SRE_PIC_COM_STEP_INIT = 0,
    SRE_PIC_COM_STEP_WAIT = 1,
    SRE_PIC_COM_STEP_MAIN = 2,
    SRE_PIC_COM_STEP_TERMINATE = 3,
};

/* anon_1_189 -- @anon1, 0x18 bytes, cs_staffroll_pic.c (DIE 0x356D21) */
struct anon_1_189 {   // size 0x18
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float time;                           // 0x4
    /* 0x008 */ float counter;                        // 0x4
    /* 0x00C */ int step;                             // 0x4
    /* 0x010 */ unsigned char r;                      // 0x1
    /* 0x011 */ unsigned char g;                      // 0x1
    /* 0x012 */ unsigned char b;                      // 0x1
    /* 0x013 */ unsigned char a;                      // 0x1
    /* 0x014 */ int result;                           // 0x4
};

/* anon_2_189 -- @anon2, 0x48 bytes, cs_staffroll_pic.c (DIE 0x356E62) */
struct anon_2_189 {   // size 0x48
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
};

/* anon_x3570e4_189 -- @enum, 0x1 bytes, cs_staffroll_pic.c (DIE 0x3570E4) */
enum anon_x3570e4_189 {   // size 0x1
    SRE_PICBACK_FI_STEP_MAIN = 0,
    SRE_PICBACK_FI_STEP_TERMINATE = 1,
    SRE_PICBACK_FO_STEP_INIT = 1,
    SRE_PICBACK_FO_STEP_MAIN = 2,
    SRE_PICBACK_FO_STEP_TERMINATE = 3,
    SRE_PICBACK_FI_STEP_INIT = 3,
};

/* anon_5_189 -- @anon5, 0x4 bytes, cs_staffroll_pic.c (DIE 0x357506) */
union anon_5_189 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_189 -- @anon3, 0x1C bytes, cs_staffroll_pic.c (DIE 0x3571F4) */
struct anon_3_189 {   // size 0x1C
    /* 0x000 */ union anon_5_189 x0;                  // 0x4
    /* 0x004 */ union anon_5_189 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_4_189 -- @anon4, 0x18 bytes, cs_staffroll_pic.c (DIE 0x357394) */
struct anon_4_189 {   // size 0x18
    /* 0x000 */ short picNo;                          // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ float u;                              // 0x4
    /* 0x008 */ float v;                              // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char a;                      // 0x1
    /* 0x015 */ unsigned char enable;                 // 0x1
    /* 0x016 */ // 0x2 bytes padding
};

/* anon_6_189 -- @anon6, 0x30 bytes, cs_staffroll_pic.c (DIE 0x357563) */
struct anon_6_189 {   // size 0x30
    /* 0x000 */ union anon_5_189 x0;                  // 0x4
    /* 0x004 */ union anon_5_189 y0;                  // 0x4
    /* 0x008 */ union anon_5_189 x1;                  // 0x4
    /* 0x00C */ union anon_5_189 y1;                  // 0x4
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
};

/* anon_7_189 -- @anon7, 0xC bytes, cs_staffroll_pic.c (DIE 0x357758) */
struct anon_7_189 {   // size 0xC
    /* 0x000 */ float time;                           // 0x4
    /* 0x004 */ short picNo;                          // 0x2
    /* 0x006 */ short conectType;                     // 0x2
    /* 0x008 */ float duration;                       // 0x4
};


/* variables (18) */
static unsigned char isreInitStep;                               /* @0x002DE5C4 size 0x1 */
static unsigned char isreMainStep;                               /* @0x002DE5C8 size 0x1 */
static unsigned char isreBackStep;                               /* @0x002DE5CC size 0x1 */
static float base_bri;                                           /* @0x002DE5D0 size 0x4 */
static float base_bri_fo;                                        /* @0x002DE5D4 size 0x4 */
static float base_start;                                         /* @0x002DE5D8 size 0x4 */
static float cepia_alpha;                                        /* @0x002DE5DC size 0x4 */
static int cepia_sw;                                             /* @0x002DE5E0 size 0x4 */
static struct anon_7_189 pecseq[36];                             /* not allocated size 0x1B0 */
void (*csStaffRollPicComFunc[13])(struct anon_0_189 *);          /* not allocated size 0x34 */
struct anon_1_189 d_fade;                                        /* @0x00807E00 size 0x18 */
unsigned int current_pic;                                        /* @0x002DE5E8 size 0x4 */
struct anon_4_189 picInfo[2];                                    /* @0x00807E20 size 0x30 */
unsigned int com_step;                                           /* @0x002DE5E4 size 0x4 */
enum anon_x3570e4_189 SRE_PICBACK_STEP;                          /* not allocated size 0x1 */
enum anon_x356ca0_189 SRE_PIC_COM_STEP;                          /* not allocated size 0x1 */
enum anon_x356c32_189 SRE_PIC_INIT_STEP;                         /* not allocated size 0x1 */
enum anon_x356bd4_189 SRE_PIC_STEP;                              /* not allocated size 0x1 */

/* functions defined (12) */
int csStaffRollFadeCheck(void);                                  /* 0x007FE060-0x007FE06C lines 1023-1024 */
void csStaffRollFadeDraw(void);                                  /* 0x007FE070-0x007FE0FC lines 1008-1019 */
int csStaffRollFadeAct(void);                                    /* 0x007FE100-0x007FE2E0 lines 974-1004 */
int csStaffRollFadeStart(int type, float time);                  /* 0x007FE2E0-0x007FE4A8 lines 922-970 */
void csStaffRollFadeInit(void);                                  /* 0x007FE4B0-0x007FE4C0 lines 916-916 */
float csStaffRollPicGetBase(void);                               /* 0x007FE4C0-0x007FE4C8 lines 872-872 */
int csStaffRollPicActBaseFO(struct anon_0_189 *pstf);            /* 0x007FE4D0-0x007FE578 lines 847-862 */
void csStaffRollPicDraw_Noise(float x0, float y0, unsigned char alpha); /* 0x007FE580-0x007FE6C8 lines 778-798 */
void csStaffRollPicDraw_Picture(float x0, float y0, unsigned char alpha); /* 0x007FE6D0-0x007FE9F8 lines 683-725 */
void csStaffRollPicDraw(struct anon_0_189 *pstf);                /* 0x007FEA00-0x007FF19C lines 638-678 */
int StaffRollTexInit(int load_addr);                             /* 0x007FF1A0-0x007FF228 lines 114-124 */
void csStaffRollPicStepInit(void);                               /* 0x007FF230-0x007FF248 lines 92-97 */

#endif /* DDR_UNIT_src_CS_staffroll_cs_staffroll_pic_c_H */
