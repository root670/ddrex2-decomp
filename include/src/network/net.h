/*
 * C:\work2\usaex2\src\network\net.c
 * MW MIPS C Compiler, overlay main; 20 functions, code 0x001E9250-0x001EB00C
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
#ifndef DDR_UNIT_src_network_net_c_H
#define DDR_UNIT_src_network_net_c_H

#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet.h"
#include "types/g_game_w.h"
#include "types/sockaddr_in.h"

/* anonymous types (1) */

/* anon_2_42 -- @anon2, 0x10 bytes, net.c (DIE 0x6E948) */
typedef struct {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
} anon_2_42;


/* variables (9) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
int libmc_reset_step;                                            /* @0x002DE4FC size 0x4 */
int McmanId;                                                     /* @0x002DE188 size 0x4 */
int McservId;                                                    /* @0x002DE180 size 0x4 */
int McservResult;                                                /* @0x002DE184 size 0x4 */
int McmanResult;                                                 /* @0x002DE18C size 0x4 */
int libmc_set_step;                                              /* @0x002DE500 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
static struct _NS_NET_INFO_W ns_neti_w;                          /* @0x00715EF0 size 0x2C8 */

/* functions referenced (8) */
void libmc_set_th(void *);                                       /* @0x001E94B0 */
void unload_bsdsocki_th(void *);                                 /* @0x001E9630 */
void net_ave_end(void *);                                        /* @0x001EA6D0 */
void NetD2ucMsgErr(struct _ddrnet *, int, int);                  /* @0x001E9760 */
void NetD2ucMsgRecv(struct _ddrnet *, int);                      /* @0x001E97A0 */
int getmyinetaddr();                                             /* @0x007F4360 */
void net_ave_start(void *);                                      /* @0x001EAFD0 */
void load_bsdsocki_th(void *);                                   /* @0x001E9700 */

/* functions defined (20) */
int main_libmc_reset(void);                                      /* 0x001E9250-0x001E9494 lines 1102-1182 */
void init_libmc_reset(void);                                     /* 0x001E94A0-0x001E94A8 lines 1100-1100 */
static void libmc_set_th(void);                                  /* 0x001E94B0-0x001E9538 lines 1061-1092 */
int main_libmc_set(void);                                        /* 0x001E9540-0x001E961C lines 1026-1060 */
void init_libmc_set(void);                                       /* 0x001E9620-0x001E9628 lines 1024-1024 */
void unload_bsdsocki_th(void);                                   /* 0x001E9630-0x001E96F4 lines 986-1012 */
void load_bsdsocki_th(void);                                     /* 0x001E9700-0x001E975C lines 974-983 */
void NetD2ucMsgErr(int stype, int ret);                          /* 0x001E9760-0x001E9798 lines 963-967 */
void NetD2ucMsgRecv(void);                                       /* 0x001E97A0-0x001E97AC lines 955-955 */
void NsNetFunc(void);                                            /* 0x001E97B0-0x001E9874 lines 921-947 */
void NsNetSend(void);                                            /* 0x001E9880-0x001E9B9C lines 794-916 */
void NsNetRecv(void);                                            /* 0x001E9BA0-0x001EA070 lines 626-790 */
int NsNetSocketClose(int _num);                                  /* 0x001EA070-0x001EA148 lines 590-622 */
void NsNetSocketSetPeer(int _num, unsigned int _ip, int _port);  /* 0x001EA150-0x001EA1C0 lines 556-563 */
int NsNetSocketCreate(int _num, int _type, int _port);           /* 0x001EA1C0-0x001EA2FC lines 506-553 */
int NsNetLogout(void);                                           /* 0x001EA300-0x001EA6C4 lines 372-501 */
void net_ave_end(void);                                          /* 0x001EA6D0-0x001EA6F4 lines 366-370 */
int NsNetLogin(void);                                            /* 0x001EA700-0x001EAFC4 lines 48-363 */
void net_ave_start(void);                                        /* 0x001EAFD0-0x001EAFF4 lines 40-44 */
void NsNetInitialize(void);                                      /* 0x001EB000-0x001EB00C lines 35-35 */

#endif /* DDR_UNIT_src_network_net_c_H */
