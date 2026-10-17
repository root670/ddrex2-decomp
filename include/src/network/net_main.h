/*
 * C:\work2\usaex2\src\network\net_main.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x001EB010-0x001EB9C0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_main_c_H
#define DDR_UNIT_src_network_net_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/g_game_w.h"

/* anonymous types (4) */

/* anon_8_43 -- @anon8, 0x4 bytes, net_main.c (DIE 0x7F319) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_8_43;

/* anon_9_43 -- @anon9, 0x10 bytes, net_main.c (DIE 0x7F909) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_8_43 x0;                         // 0x4
    /* 0x004 */ anon_8_43 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_9_43;

/* anon_6_43 -- @anon6, 0x4 bytes, net_main.c (DIE 0x7CD1E) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
} anon_6_43;

/* anon_7_43 -- @anon7, 0x4 bytes, net_main.c (DIE 0x7EE6A) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_7_43;


/* variables (3) */
static int test_shutdown;                                        /* @0x002DE504 size 0x4 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (5) */
void NetToSysInit(struct _NETWORK_W *);                          /* @0x001EB340 */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */
void NetGameInit(struct _NETWORK_W *);                           /* @0x001F6830 */
void NetSysInit(struct _NETWORK_W *);                            /* @0x00224330 */
void NetSysEnd(struct _NETWORK_W *);                             /* @0x00224270 */

/* functions defined (7) */
char NetPadCon(unsigned int key);                                /* 0x001EB010-0x001EB198 lines 288-312 */
void NetToLogout(struct _NETWORK_W *netw);                       /* 0x001EB1A0-0x001EB260 lines 246-262 */
void NetToGameInit(struct _NETWORK_W *netw);                     /* 0x001EB260-0x001EB340 lines 209-241 */
void NetToSysInit(struct _NETWORK_W *netw);                      /* 0x001EB340-0x001EB460 lines 153-205 */
void NetEnd(void);                                               /* 0x001EB460-0x001EB4A4 lines 142-148 */
int NetMain(void);                                               /* 0x001EB4B0-0x001EB92C lines 64-138 */
void NetInit(void);                                              /* 0x001EB930-0x001EB9C0 lines 35-60 */

#endif /* DDR_UNIT_src_network_net_main_c_H */
