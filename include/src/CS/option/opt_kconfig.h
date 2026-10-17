/*
 * C:\work2\usaex2\src\CS\option\opt_kconfig.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 9 functions, code 0x007F07F0-0x007F1BB4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_option_opt_kconfig_c_H
#define DDR_UNIT_src_CS_option_opt_kconfig_c_H

#include "types/G_SYS_W_.h"
#include "types/_OPTSYS_W.h"
#include "types/_tag_cDDR8Option.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cKeyConfigDir.h"
#include "types/_tag_cKeyConfigLR.h"
#include "types/oni_course.h"

/* anonymous types (10) */

/* anon_10_227 -- @anon10, 0x14 bytes, opt_kconfig.c (DIE 0x43A6DB) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_10_227;

/* anon_3_227 -- @anon3, 0x4 bytes, opt_kconfig.c (DIE 0x43619A) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_3_227;

/* anon_1_227 -- @anon1, 0x4 bytes, opt_kconfig.c (DIE 0x435FBE) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_3_227 s;                         // 0x4
} anon_1_227;

/* anon_12_227 -- @anon12, 0xC bytes, opt_kconfig.c (DIE 0x43ACCA) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_12_227;

/* anon_2_227 -- @anon2, 0x12E0 bytes, opt_kconfig.c (DIE 0x43601C) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_12_227 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_2_227;

/* anon_9_227 -- @anon9, 0xD40 bytes, opt_kconfig.c (DIE 0x43A3FE) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_9_227;

/* anon_6_227 -- @anon6, 0x48 bytes, opt_kconfig.c (DIE 0x438AE5) */
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
} anon_6_227;

/* anon_7_227 -- @anon7, 0x4 bytes, opt_kconfig.c (DIE 0x439D6A) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_7_227;

/* anon_8_227 -- @anon8, 0x30 bytes, opt_kconfig.c (DIE 0x439FAD) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_7_227 x0;                        // 0x4
    /* 0x004 */ anon_7_227 y0;                        // 0x4
    /* 0x008 */ anon_7_227 x1;                        // 0x4
    /* 0x00C */ anon_7_227 y1;                        // 0x4
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
} anon_8_227;

/* anon_11_227 -- @anon11, 0x68 bytes, opt_kconfig.c (DIE 0x43A8F0) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_7_227 x0;                        // 0x4
    /* 0x004 */ anon_7_227 y0;                        // 0x4
    /* 0x008 */ anon_7_227 x1;                        // 0x4
    /* 0x00C */ anon_7_227 y1;                        // 0x4
    /* 0x010 */ anon_7_227 x2;                        // 0x4
    /* 0x014 */ anon_7_227 y2;                        // 0x4
    /* 0x018 */ anon_7_227 x3;                        // 0x4
    /* 0x01C */ anon_7_227 y3;                        // 0x4
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
} anon_11_227;


/* variables (11) */
static char opt_kconfig_default_tbl[24];                         /* not allocated size 0x18 */
static int test_x;                                               /* not allocated size 0x4 */
static int test_y;                                               /* not allocated size 0x4 */
static int test_x2;                                              /* not allocated size 0x4 */
static int test_y2;                                              /* not allocated size 0x4 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
struct _tag_cKeyConfigDir TblKeyConfigDir[2][7];                 /* @0x002A6670 size 0x1C0 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _tag_cKeyConfigLR TblKeyConfigLR[2][8];                   /* @0x002A6570 size 0x100 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct _tag_cDDR8Option OptionDefault;                           /* @0x002A6510 size 0x58 */

/* functions referenced (3) */
void OptMenuInit2(struct _OPTSYS_W *);                           /* @0x007F5E70 */
void OptKConfigDoubleMain(struct _OPTSYS_W *);                   /* @0x007F14E0 */
void OptKConfigMain(struct _OPTSYS_W *);                         /* @0x007F18C0 */

/* functions defined (9) */
static void OptKConfigSetEditKey(void);                          /* 0x007F07F0-0x007F0978 lines 1140-1168 */
static int OptKConfigGetTblKey(int _pos);                        /* 0x007F0980-0x007F0AB0 lines 1067-1135 */
static void OptWinKConfigArrow(int _pos, int _aspect, int _flag); /* 0x007F0AB0-0x007F0CA0 lines 604-985 */
void OptWinKConfigBackDisp(void);                                /* 0x007F0CA0-0x007F0F3C lines 497-591 */
void OptWinKConfigObjDisp(void);                                 /* 0x007F0F40-0x007F14DC lines 215-490 */
void OptKConfigDoubleMain(struct _OPTSYS_W *_opt);               /* 0x007F14E0-0x007F1870 lines 134-196 */
void OptKConfigDoubleInit(struct _OPTSYS_W *_opt);               /* 0x007F1870-0x007F18C0 lines 120-129 */
void OptKConfigMain(struct _OPTSYS_W *_opt);                     /* 0x007F18C0-0x007F1B50 lines 60-111 */
void OptKConfigInit(struct _OPTSYS_W *_opt);                     /* 0x007F1B50-0x007F1BB4 lines 47-56 */

#endif /* DDR_UNIT_src_CS_option_opt_kconfig_c_H */
