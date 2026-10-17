/*
 * C:\work2\usaex2\src\network\net_game\net_game_vs_win.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x00278C20-0x0027A578
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_vs_win_c_H
#define DDR_UNIT_src_network_net_game_net_game_vs_win_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_vs_w.h"
#include "types/g_game_w.h"

/* anonymous types (6) */

/* anon_7_156 -- @anon7, 0x4 bytes, net_game_vs_win.c (DIE 0x2C2013) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_7_156;

/* anon_1_156 -- @anon1, 0x20 bytes, net_game_vs_win.c (DIE 0x2BEB0F) */
typedef struct {   // size 0x20
    /* 0x000 */ anon_7_156 x0;                        // 0x4
    /* 0x004 */ anon_7_156 y0;                        // 0x4
    /* 0x008 */ anon_7_156 x1;                        // 0x4
    /* 0x00C */ anon_7_156 y1;                        // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ int flg;                              // 0x4
} anon_1_156;

/* anon_4_156 -- @anon4, 0x48 bytes, net_game_vs_win.c (DIE 0x2C0672) */
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
} anon_4_156;

/* anon_5_156 -- @anon5, 0x1C bytes, net_game_vs_win.c (DIE 0x2C0AFE) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_7_156 x0;                        // 0x4
    /* 0x004 */ anon_7_156 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_5_156;

/* anon_9_156 -- @anon9, 0x10 bytes, net_game_vs_win.c (DIE 0x2C2E61) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_7_156 x0;                        // 0x4
    /* 0x004 */ anon_7_156 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_9_156;

/* anon_8_156 -- @anon8, 0x30 bytes, net_game_vs_win.c (DIE 0x2C2C6C) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_7_156 x0;                        // 0x4
    /* 0x004 */ anon_7_156 y0;                        // 0x4
    /* 0x008 */ anon_7_156 x1;                        // 0x4
    /* 0x00C */ anon_7_156 y1;                        // 0x4
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
} anon_8_156;


/* variables (11) */
struct _net_win_vs_w *vs_p;                                      /* @0x002DDDE0 size 0x4 */
static int (*NetWin_VSWinFunc[3])(struct _CWS_WIN_W *);          /* @0x002C0B40 size 0xC */
static void (*NetWin_VSWinCode[4])(struct _CWS_WIN_W *);         /* @0x002C0B50 size 0x10 */
static struct _CWS_OBJ_TEX netwinvs_plate00[1];                  /* @0x002C0B60 size 0x14 */
static struct _CWS_OBJ_TEX netwinvs_plate01[1];                  /* @0x002C0B80 size 0x14 */
static struct _CWS_OBJ_TEX netwinvs_plate_chara[2];              /* @0x002C0BA0 size 0x28 */
static struct _CWS_OBJ_TEX netwinvs_plate_namewaku0[3];          /* @0x002C0BD0 size 0x3C */
static struct _CWS_OBJ_TEX netwinvs_plate_namewaku1[3];          /* @0x002C0C10 size 0x3C */
static struct _CWS_OBJ_SET netwinvs[6];                          /* @0x002C0C50 size 0x78 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
static struct _net_win_vs_w netwin_vs_w;                         /* @0x00722CD0 size 0x14 */

/* functions defined (8) */
static int NetWin_VSWinDataSet(struct _CWS_WIN_W *win);          /* 0x00278C20-0x00279328 lines 707-820 */
static void NetWin_VSWinMoveStr(struct _CWS_WIN_W *win);         /* 0x00279330-0x002795D0 lines 600-640 */
static void NetWin_VSWinDispWire2P(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x002795D0-0x00279B90 lines 516-591 */
static void NetWin_VSWinDispWire1P(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x00279B90-0x0027A154 lines 475-515 */
static int NetWin_VSWinEnd(struct _CWS_WIN_W *win);              /* 0x0027A160-0x0027A174 lines 458-460 */
static int NetWin_VSWinMain(struct _CWS_WIN_W *win);             /* 0x0027A180-0x0027A478 lines 410-453 */
static int NetWin_VSWinInit(struct _CWS_WIN_W *win);             /* 0x0027A480-0x0027A510 lines 388-407 */
int NetWin_VSWin(struct _CWS_WIN_W *win);                        /* 0x0027A510-0x0027A578 lines 377-383 */

#endif /* DDR_UNIT_src_network_net_game_net_game_vs_win_c_H */
