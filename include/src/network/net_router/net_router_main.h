/*
 * C:\work2\usaex2\src\network\net_router\net_router_main.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 4 functions, code 0x00805A00-0x00806410
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_router_net_router_main_c_H
#define DDR_UNIT_src_network_net_router_net_router_main_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_tag_cNetRouter.h"
#include "types/_tag_cUpnp.h"

/* anonymous types (5) */

/* anon_x3c0830_212 -- @enum, 0x2 bytes, net_router_main.c (DIE 0x3C0830) */
enum anon_x3c0830_212 {   // size 0x2
    mrdUPnP_EVENT_START = 1400,
    mrdUPnP_EVENT_END = 1401,
    mrdUPnP_EVENT_NOP = 1402,
    mrdUPnP_EVENT_SET_EVENT_HANDLER = 1403,
    mrdUPnP_EVENT_LOCAL_PORT_BIND_OK = 1404,
    mrdUPnP_EVENT_LOCAL_PORT_BIND_ERR = 1405,
    mrdUPnP_EVENT_THREAD_UP = 1406,
    mrdUPnP_EVENT_THREAD_DOWN = 1407,
    mrdUPnP_EVENT_HEART_BEAT_ON = 1408,
    mrdUPnP_EVENT_HEART_BEAT_OFF = 1409,
    mrdUPnP_EVENT_HEART_BEAT_SEND = 1410,
    mrdUPnP_EVENT_MAX = 1411,
};

/* anon_x3c411e_212 -- @enum, 0x2 bytes, net_router_main.c (DIE 0x3C411E) */
enum anon_x3c411e_212 {   // size 0x2
    mrdUPnP_INFO_START = 2100,
    mrdUPnP_INFO_END = 2101,
    mrdUPnP_INFO_NAT_TYPE = 2102,
    mrdUPnP_INFO_IP_INTERNAL_N32 = 2103,
    mrdUPnP_INFO_IP_EXTERNAL_N32 = 2104,
    mrdUPnP_INFO_PORT_INTERNAL_N16 = 2105,
    mrdUPnP_INFO_PORT_EXTERNAL_N16 = 2106,
    mrdUPnP_INFO_MAX = 2107,
};

/* anon_0_212 -- @anon0, 0x10 bytes, net_router_main.c (DIE 0x3C2746) */
struct anon_0_212 {   // size 0x10
    /* 0x000 */ enum anon_x3c411e_212 t;              // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ int l;                                // 0x4
    /* 0x008 */ void *v;                              // 0x4
    /* 0x00C */ void *reserve;                        // 0x4
};

/* anon_x3c3111_212 -- @enum, 0x2 bytes, net_router_main.c (DIE 0x3C3111) */
enum anon_x3c3111_212 {   // size 0x2
    mrdUPnP_STAT_CHAOS = 1200,
    mrdUPnP_STAT_OK = 1201,
    mrdUPnP_STAT_ERR = 1202,
};

/* anon_1_212 -- @anon1, 0x8 bytes, net_router_main.c (DIE 0x3C3258) */
struct anon_1_212 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (4) */
struct _tag_cNetRouter *pNetRouter;                              /* @0x002DDEBC size 0x4 */
struct _tag_cUpnp *pUpnp;                                        /* @0x002DDEC0 size 0x4 */
static struct _tag_cUpnp _pUpnp;                                 /* @0x0080D7E0 size 0x14 */
static struct _tag_cNetRouter _pNetRouter;                       /* @0x0080D800 size 0x2C */

/* functions referenced (3) */
enum anon_x3c3111_212 event_handler(enum anon_x3c0830_212);      /* @0x00805A00 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */
void NetAuthMain(struct _NETWORK_W *);                           /* @0x007FF020 */

/* functions defined (4) */
static enum anon_x3c3111_212 event_handler(enum anon_x3c0830_212 event); /* 0x00805A00-0x00805B6C lines 493-575 */
static int upnp_test(void);                                      /* 0x00805B70-0x00805F44 lines 388-487 */
static void set_warning_msg(int id, int yesno);                  /* 0x00805F50-0x008062A4 lines 235-362 */
void NetRouterMain(struct _NETWORK_W *netw);                     /* 0x008062B0-0x00806410 lines 94-140 */

#endif /* DDR_UNIT_src_network_net_router_net_router_main_c_H */
