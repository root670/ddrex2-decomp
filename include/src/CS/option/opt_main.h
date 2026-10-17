/*
 * C:\work2\usaex2\src\CS\option\opt_main.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 19 functions, code 0x007F1FC0-0x007F3398
 * functions come from: opt_ex2.c (10), opt_main.c (9)
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_option_opt_main_c_H
#define DDR_UNIT_src_CS_option_opt_main_c_H

#include "types/CO_OBJ_W.h"
#include "types/_CWS_WIN_W.h"
#include "types/_OPTSYS_W.h"
#include "types/g_game_w.h"

/* anonymous types (10) */

/* anon_0_229 -- @anon0, 0x44 bytes, opt_main.c (DIE 0x43D785) */
typedef struct {   // size 0x44
    /* 0x000 */ void *obj_p[16];                      // 0x40
    /* 0x040 */ char *str_help_message;               // 0x4
} anon_0_229;

/* anon_3_229 -- @anon3, 0x4 bytes, opt_main.c (DIE 0x43E2C2) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_229;

/* anon_1_229 -- @anon1, 0x1C bytes, opt_main.c (DIE 0x43D7F8) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_3_229 x0;                        // 0x4
    /* 0x004 */ anon_3_229 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_1_229;

/* anon_4_229 -- @anon4, 0x10 bytes, opt_main.c (DIE 0x43F141) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_3_229 x0;                        // 0x4
    /* 0x004 */ anon_3_229 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_4_229;

/* anon_5_229 -- @anon5, 0x4 bytes, opt_main.c (DIE 0x43F3F4) */
typedef struct {   // size 0x4
    /* 0x000 */ struct _CWS_WIN_W *win;               // 0x4
} anon_5_229;

/* anon_6_229 -- @anon6, 0x18 bytes, opt_main.c (DIE 0x43F438) */
typedef struct {   // size 0x18
    /* 0x000 */ short t;                              // 0x2
    /* 0x002 */ short t_max;                          // 0x2
    /* 0x004 */ float x;                              // 0x4
    /* 0x008 */ float y;                              // 0x4
    /* 0x00C */ float sx;                             // 0x4
    /* 0x010 */ float sy;                             // 0x4
    /* 0x014 */ unsigned char alpha;                  // 0x1
    /* 0x015 */ unsigned char salpha;                 // 0x1
    /* 0x016 */ unsigned char step;                   // 0x1
    /* 0x017 */ unsigned char dummy;                  // 0x1
} anon_6_229;

/* anon_7_229 -- @anon7, 0x8 bytes, opt_main.c (DIE 0x43FE64) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_7_229;

/* anon_9_229 -- @anon9, 0x10 bytes, opt_main.c (DIE 0x4407D1) */
typedef struct {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
} anon_9_229;

/* anon_10_229 -- @anon10, 0x10 bytes, opt_main.c (DIE 0x440B02) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_10_229;

/* anon_12_229 -- @anon12, 0x34 bytes, opt_main.c (DIE 0x442BF2) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_3_229 x0;                        // 0x4
    /* 0x004 */ anon_3_229 y0;                        // 0x4
    /* 0x008 */ anon_3_229 x1;                        // 0x4
    /* 0x00C */ anon_3_229 y1;                        // 0x4
    /* 0x010 */ anon_3_229 x2;                        // 0x4
    /* 0x014 */ anon_3_229 y2;                        // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
} anon_12_229;


/* variables (8) */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
anon_0_229 *optex2w;                                             /* @0x002DDEF4 size 0x4 */
static anon_10_229 option_obj_f[3];                              /* @0x007F82C0 size 0x30 */
char udp_port_number[5];                                         /* @0x002DE678 size 0x5 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct CO_OBJ_W co_obj_addr[64];                                 /* @0x007F9770 size 0xA000 */
static anon_0_229 option_ex2_w;                                  /* @0x007F8800 size 0x44 */
static struct _OPTSYS_W _opt_sys_w;                              /* @0x007F8850 size 0xF1C */

/* functions referenced (2) */
void DecodeFilepackData_Th(void *);                              /* @0x0016DC50 */
void OptMenuInit(struct _OPTSYS_W *);                            /* @0x007F5EA0 */

/* functions defined (19) */

/* opt_ex2.c */
void Option_Board_Disp(anon_7_229 r, int pri_add, unsigned char flag); /* 0x007F1FC0-0x007F2208 lines 367-402 */
int Option_base00_disp(void *wp);                                /* 0x007F2210-0x007F2288 lines 331-357 */
int Option_base00_disap(void *wp);                               /* 0x007F2290-0x007F2448 lines 287-329 */
int Option_base00_appear(void *wp);                              /* 0x007F2450-0x007F2714 lines 238-284 */
int Option_caption_disap(void *wp);                              /* 0x007F2720-0x007F27C8 lines 213-232 */
int Option_caption_appear(void *wp);                             /* 0x007F27D0-0x007F2868 lines 196-210 */
int Option_win_disp(void);                                       /* 0x007F2870-0x007F2890 lines 185-190 */
int Option_win_func(void *w);                                    /* 0x007F2890-0x007F2B10 lines 110-183 */
void option_obj_disap(int obj_no);                               /* 0x007F2B10-0x007F2B58 lines 91-96 */
void option_obj_set(int obj_no);                                 /* 0x007F2B60-0x007F2BC0 lines 84-88 */

/* opt_main.c */
int OptGetFontSize(char *str, int type);                         /* 0x007F2BC0-0x007F2BF0 lines 575-596 */
void OptPrintFont(int _x, int _y, int _z, unsigned char *_str, int _color, unsigned char _bri, unsigned char _alpha, int texid); /* 0x007F2BF0-0x007F2CA4 lines 552-572 */
unsigned char *OptOutStrGet(int id);                             /* 0x007F2CB0-0x007F2D14 lines 477-496 */
void OptOutStrInit(void);                                        /* 0x007F2D20-0x007F2D48 lines 473-475 */
static int OptInitTex(void);                                     /* 0x007F2D50-0x007F2F04 lines 302-389 */
static int OptInitKanji(void);                                   /* 0x007F2F10-0x007F2FF4 lines 268-298 */
void OptSystemEnd(void);                                         /* 0x007F3000-0x007F3028 lines 256-259 */
int OptSystemMain(void);                                         /* 0x007F3030-0x007F3330 lines 120-233 */
void OptSystemInit(void);                                        /* 0x007F3330-0x007F3398 lines 77-97 */

#endif /* DDR_UNIT_src_CS_option_opt_main_c_H */
