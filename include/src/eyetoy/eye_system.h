/*
 * C:\work2\usaex2\src\eyetoy\eye_system.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x001D2180-0x001D4D74
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
#ifndef DDR_UNIT_src_eyetoy_eye_system_c_H
#define DDR_UNIT_src_eyetoy_eye_system_c_H

#include "types/_DOUBLE_DISP_W.h"
#include "types/_EYETOY_W.h"
#include "types/_eRECT.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (3) */

/* anon_x4ba1f_32 -- @enum, 0x1 bytes, eye_system.c (DIE 0x4BA1F) */
typedef enum {   // size 0x1
    SCE_EYETOY_NOCAMERA = 0,
    SCE_EYETOY_CLOSED = 1,
    SCE_EYETOY_STOPPED = 2,
    SCE_EYETOY_STARTED = 3,
} anon_x4ba1f_32;

/* anon_7_32 -- @anon7, 0x48 bytes, eye_system.c (DIE 0x4BECC) */
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
} anon_7_32;

/* anon_10_32 -- @anon10, 0x30 bytes, eye_system.c (DIE 0x4E839) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
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
} anon_10_32;


/* variables (5) */
struct _EYETOY_W *EYETOYW;                                       /* @0x002DD9A8 size 0x4 */
static int (*EyeSystem_Func[5])(struct _EYETOY_W *);             /* @0x002B6920 size 0x14 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
static struct _EYETOY_W _eyetoy_w;                               /* @0x007126E0 size 0x2DC */

/* functions defined (14) */
void EyeSceEnd(void);                                            /* 0x001D2180-0x001D21E4 lines 1092-1103 */
static void EyeSystemFilter(struct _DOUBLE_DISP_W *screen);      /* 0x001D21F0-0x001D2678 lines 944-1029 */
static void EyeSystemDispColorAnimeWindow(void);                 /* 0x001D2680-0x001D2E74 lines 668-865 */
static void EyeSystemDispWindow(struct _DOUBLE_DISP_W *screen, struct _eRECT *disp); /* 0x001D2E80-0x001D3200 lines 570-665 */
static void EyeSystemDrawPict(void);                             /* 0x001D3200-0x001D3810 lines 385-542 */
static int EyeSystemDestroy(void);                               /* 0x001D3810-0x001D392C lines 364-370 */
static int EyeSystemStop(struct _EYETOY_W *_eye);                /* 0x001D3930-0x001D3A9C lines 321-358 */
static int EyeSystemMain(struct _EYETOY_W *_eye);                /* 0x001D3AA0-0x001D3AF0 lines 303-315 */
static int EyeSystemStart(struct _EYETOY_W *_eye);               /* 0x001D3AF0-0x001D3C18 lines 262-292 */
static int EyeSystemSet(struct _EYETOY_W *_eye);                 /* 0x001D3C20-0x001D3C70 lines 239-253 */
int EyeSystemInit(void);                                         /* 0x001D3C70-0x001D4B2C lines 137-231 */
void EyeSystemFunc(void);                                        /* 0x001D4B30-0x001D4BBC lines 124-131 */
void EyeSystemReset(void);                                       /* 0x001D4BC0-0x001D4CD0 lines 61-74 */
void EyeSystemCreate(void);                                      /* 0x001D4CD0-0x001D4D74 lines 50-56 */

#endif /* DDR_UNIT_src_eyetoy_eye_system_c_H */
