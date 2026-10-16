/*
 * C:\work2\usaex2\src\CS\staffroll\cs_staffroll.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 4 functions, code 0x007F9D20-0x007FA558
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_staffroll_cs_staffroll_c_H
#define DDR_UNIT_src_CS_staffroll_cs_staffroll_c_H

/* anonymous types (4) */

/* anon_x34cde8_186 -- @enum, 0x1 bytes, cs_staffroll.c (DIE 0x34CDE8) */
enum anon_x34cde8_186 {   // size 0x1
    SRE_BINREAD_STEP_INIT = 0,
    SRE_BINREAD_STEP_READ = 1,
    SRE_BINREAD_STEP_TERMINATE = 2,
};

/* anon_0_186 -- @anon0, 0x78 bytes, cs_staffroll.c (DIE 0x34CE52) */
struct anon_0_186 {   // size 0x78
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

/* anon_x34d26f_186 -- @enum, 0x1 bytes, cs_staffroll.c (DIE 0x34D26F) */
enum anon_x34d26f_186 {   // size 0x1
    SRE_SDREAD_STEP_VAG_INIT = 0,
    SRE_SDREAD_STEP_VAG_READ = 1,
    SRE_SDREAD_STEP_VAG_WAIT = 2,
    SRE_SDREAD_STEP_VAG_TERMINATE = 3,
    SRE_SDREAD_STEP_INIT = 4,
    SRE_SDREAD_STEP_DISC_START = 5,
    SRE_SDREAD_STEP_READ = 6,
    SRE_SDREAD_STEP_WAIT = 7,
    SRE_SDREAD_STEP_TERMINATE = 8,
};

/* anon_1_186 -- @anon1, 0x8 bytes, cs_staffroll.c (DIE 0x34D375) */
struct anon_1_186 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};


/* variables (7) */
static int isreMainStep;                                         /* @0x002DE59C size 0x4 */
static int isreReadStep;                                         /* @0x002DE5A0 size 0x4 */
static int isreSdReadStep;                                       /* @0x002DE5A4 size 0x4 */
struct anon_0_186 g_staffroll;                                   /* @0x00807D60 size 0x78 */
struct anon_1_186 sound_bin[];                                   /* @0x002DD418 */
enum anon_x34d26f_186 SRE_SDREAD_STEP;                           /* not allocated size 0x1 */
enum anon_x34cde8_186 SRE_BINREAD_STEP;                          /* not allocated size 0x1 */

/* functions defined (4) */
int csStaffRollSdMain(void);                                     /* 0x007F9D20-0x007F9FD4 lines 434-553 */
void csStaffRollFinish(void);                                    /* 0x007F9FE0-0x007FA010 lines 333-339 */
int csStaffRollStep(void);                                       /* 0x007FA010-0x007FA534 lines 100-327 */
void csStaffRollInit(void);                                      /* 0x007FA540-0x007FA558 lines 62-62 */

#endif /* DDR_UNIT_src_CS_staffroll_cs_staffroll_c_H */
