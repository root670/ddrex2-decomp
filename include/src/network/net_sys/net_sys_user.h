/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_user.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00226880-0x00227A9C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_user_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_user_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* anonymous types (2) */

/* anon_3_81 -- @anon3, 0x4 bytes, net_sys_user.c (DIE 0x169E88) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
} anon_3_81;

/* anon_4_81 -- @anon4, 0x4 bytes, net_sys_user.c (DIE 0x16A3DA) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_4_81;


/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (12) */
void NetSysLobbyInit(struct _NETWORK_W *);                       /* @0x0023FC20 */
void NetSysUserInit_Sel(struct _NETWORK_W *);                    /* @0x002273A0 */
void NetSysUserConnect(struct _NETWORK_W *);                     /* @0x00226880 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetSysUserSelKey(struct _NETWORK_W *);                      /* @0x002268C0 */
void NetSysUserSelMain(struct _NETWORK_W *);                     /* @0x00226C00 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */
void NetSysMenuInit2(struct _NETWORK_W *);                       /* @0x00224AD0 */
void NetSysNewInit(struct _NETWORK_W *);                         /* @0x00225B60 */
void NetSysUserSelInit(struct _NETWORK_W *);                     /* @0x00226F40 */
void NetSysUserKey(struct _NETWORK_W *);                         /* @0x00226A50 */
void NetSysUserMain(struct _NETWORK_W *);                        /* @0x00227140 */

/* functions defined (9) */
void NetSysUserConnect(struct _NETWORK_W *netw);                 /* 0x00226880-0x002268BC lines 543-546 */
static void NetSysUserSelKey(struct _NETWORK_W *netw);           /* 0x002268C0-0x00226A48 lines 513-535 */
static void NetSysUserKey(struct _NETWORK_W *netw);              /* 0x00226A50-0x00226BF8 lines 486-509 */
static void NetSysUserSelMain(struct _NETWORK_W *netw);          /* 0x00226C00-0x00226F3C lines 368-480 */
static void NetSysUserSelInit(struct _NETWORK_W *netw);          /* 0x00226F40-0x00227134 lines 315-365 */
static void NetSysUserMain(struct _NETWORK_W *netw);             /* 0x00227140-0x00227398 lines 239-311 */
static void NetSysUserInit_Sel(struct _NETWORK_W *netw);         /* 0x002273A0-0x002274A0 lines 217-236 */
void NetSysUserInit2(struct _NETWORK_W *netw);                   /* 0x002274A0-0x00227780 lines 136-210 */
void NetSysUserInit(struct _NETWORK_W *netw);                    /* 0x00227780-0x00227A9C lines 53-133 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_user_c_H */
