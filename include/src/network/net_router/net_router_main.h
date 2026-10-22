/*
 * C:\work2\usaex2\src\network\net_router\net_router_main.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 4 functions, code 0x00805A00-0x00806410
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
#ifndef DDR_UNIT_src_network_net_router_net_router_main_c_H
#define DDR_UNIT_src_network_net_router_net_router_main_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_tag_cNetRouter.h"
#include "types/_tag_cUpnp.h"

/* anonymous types (4) */

/* anon_x3c0830_212 -- @enum, 0x2 bytes, net_router_main.c (DIE 0x3C0830) */
typedef enum {   // size 0x2
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
} anon_x3c0830_212;

/* anon_x3c411e_212 -- @enum, 0x2 bytes, net_router_main.c (DIE 0x3C411E) */
typedef enum {   // size 0x2
    mrdUPnP_INFO_START = 2100,
    mrdUPnP_INFO_END = 2101,
    mrdUPnP_INFO_NAT_TYPE = 2102,
    mrdUPnP_INFO_IP_INTERNAL_N32 = 2103,
    mrdUPnP_INFO_IP_EXTERNAL_N32 = 2104,
    mrdUPnP_INFO_PORT_INTERNAL_N16 = 2105,
    mrdUPnP_INFO_PORT_EXTERNAL_N16 = 2106,
    mrdUPnP_INFO_MAX = 2107,
} anon_x3c411e_212;

/* anon_0_212 -- @anon0, 0x10 bytes, net_router_main.c (DIE 0x3C2746) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_x3c411e_212 t;                   // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ int l;                                // 0x4
    /* 0x008 */ void *v;                              // 0x4
    /* 0x00C */ void *reserve;                        // 0x4
} anon_0_212;

/* anon_x3c3111_212 -- @enum, 0x2 bytes, net_router_main.c (DIE 0x3C3111) */
typedef enum {   // size 0x2
    mrdUPnP_STAT_CHAOS = 1200,
    mrdUPnP_STAT_OK = 1201,
    mrdUPnP_STAT_ERR = 1202,
} anon_x3c3111_212;


/* variables (4) */
struct _tag_cNetRouter *pNetRouter;                              /* @0x002DDEBC size 0x4 */
struct _tag_cUpnp *pUpnp;                                        /* @0x002DDEC0 size 0x4 */
static struct _tag_cUpnp _pUpnp;                                 /* @0x0080D7E0 size 0x14 */
static struct _tag_cNetRouter _pNetRouter;                       /* @0x0080D800 size 0x2C */

/* functions referenced (3) */
anon_x3c3111_212 event_handler(anon_x3c0830_212);                /* @0x00805A00 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */
void NetAuthMain(struct _NETWORK_W *);                           /* @0x007FF020 */

/* functions defined (4) */
static anon_x3c3111_212 event_handler(anon_x3c0830_212 event);   /* 0x00805A00-0x00805B6C lines 493-575 */
static int upnp_test(void);                                      /* 0x00805B70-0x00805F44 lines 388-487 */
static void set_warning_msg(int id, int yesno);                  /* 0x00805F50-0x008062A4 lines 235-362 */
void NetRouterMain(struct _NETWORK_W *netw);                     /* 0x008062B0-0x00806410 lines 94-140 */

#endif /* DDR_UNIT_src_network_net_router_net_router_main_c_H */
