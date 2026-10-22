/*
 * C:\work2\usaex2\src\network\net_window\net_win_search.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x0022DDE0-0x0022E738
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
#ifndef DDR_UNIT_src_network_net_window_net_win_search_c_H
#define DDR_UNIT_src_network_net_window_net_win_search_c_H

#include "types/G_SYS_W_.h"
#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_net_win_search_w.h"

/* anonymous types (3) */

/* anon_6_94 -- @anon6, 0x4 bytes, net_win_search.c (DIE 0x1A942F) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_6_94;

/* anon_1_94 -- @anon1, 0x74 bytes, net_win_search.c (DIE 0x1A591F) */
typedef struct {   // size 0x74
    /* 0x000 */ anon_6_94 x0;                         // 0x4
    /* 0x004 */ anon_6_94 y0;                         // 0x4
    /* 0x008 */ anon_6_94 x1;                         // 0x4
    /* 0x00C */ anon_6_94 y1;                         // 0x4
    /* 0x010 */ anon_6_94 x2;                         // 0x4
    /* 0x014 */ anon_6_94 y2;                         // 0x4
    /* 0x018 */ anon_6_94 x3;                         // 0x4
    /* 0x01C */ anon_6_94 y3;                         // 0x4
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
    /* 0x064 */ unsigned char r1;                     // 0x1
    /* 0x065 */ unsigned char g1;                     // 0x1
    /* 0x066 */ unsigned char b1;                     // 0x1
    /* 0x067 */ unsigned char a1;                     // 0x1
    /* 0x068 */ unsigned char r2;                     // 0x1
    /* 0x069 */ unsigned char g2;                     // 0x1
    /* 0x06A */ unsigned char b2;                     // 0x1
    /* 0x06B */ unsigned char a2;                     // 0x1
    /* 0x06C */ unsigned char r3;                     // 0x1
    /* 0x06D */ unsigned char g3;                     // 0x1
    /* 0x06E */ unsigned char b3;                     // 0x1
    /* 0x06F */ unsigned char a3;                     // 0x1
    /* 0x070 */ int flg;                              // 0x4
} anon_1_94;

/* anon_4_94 -- @anon4, 0x48 bytes, net_win_search.c (DIE 0x1A78B8) */
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
} anon_4_94;


/* variables (11) */
static int (*NetWin_SearchFunc[3])(struct _CWS_WIN_W *);         /* @0x002BD900 size 0xC */
static void (*NetWin_SearchCode[4])(struct _CWS_WIN_W *);        /* @0x002BD910 size 0x10 */
static struct _CWS_OBJ_TEX netwinsearch_plate_board_big[3];      /* @0x002BD920 size 0x3C */
static struct _CWS_OBJ_TEX netwinsearch_plate_board_mini[3];     /* @0x002BD960 size 0x3C */
static struct _CWS_OBJ_TEX netwinsearch_plate_font[1];           /* @0x002BD9A0 size 0x14 */
static struct _CWS_OBJ_TEX netwinsearch_plate_ic_big[5];         /* @0x002BD9C0 size 0x64 */
static struct _CWS_OBJ_TEX netwinsearch_plate_ic_mini[5];        /* @0x002BDA30 size 0x64 */
static struct _CWS_OBJ_TEX netwinsearch_plate_gulegule[3];       /* @0x002BDAA0 size 0x3C */
static struct _CWS_OBJ_SET netwinsearch[4];                      /* @0x002BDAE0 size 0x50 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions defined (6) */
void NetWin_SearchType(struct _CWS_WIN_W *win, char *type);      /* 0x0022DDE0-0x0022DE08 lines 401-404 */
static void NetWin_RotDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x0022DE10-0x0022E2E8 lines 315-394 */
static int NetWin_SearchEnd(struct _CWS_WIN_W *win);             /* 0x0022E2F0-0x0022E304 lines 310-312 */
static int NetWin_SearchMain(struct _CWS_WIN_W *win);            /* 0x0022E310-0x0022E568 lines 252-305 */
static int NetWin_SearchInit(struct _CWS_WIN_W *win);            /* 0x0022E570-0x0022E6D0 lines 226-249 */
int NetWin_Search(struct _CWS_WIN_W *win);                       /* 0x0022E6D0-0x0022E738 lines 215-221 */

#endif /* DDR_UNIT_src_network_net_window_net_win_search_c_H */
