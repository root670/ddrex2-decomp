/*
 * C:\work2\usaex2\src\network\lib\bsdsock\bsdsock.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 35 functions, code 0x007F2B60-0x007F449C
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
#ifndef DDR_UNIT_src_network_lib_bsdsock_bsdsock_c_H
#define DDR_UNIT_src_network_lib_bsdsock_bsdsock_c_H

#include "types/SemaParam.h"
#include "types/_sif_client_data.h"
#include "types/in_addr.h"
#include "types/sockaddr.h"

/* anonymous types (19) */

/* anon_0_200 -- @anon0, 0x1C bytes, bsdsock.c (DIE 0x386A66) */
typedef struct {   // size 0x1C
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int his_ip;                           // 0x4
    /* 0x008 */ int my_ip;                            // 0x4
    /* 0x00C */ int his_dns1;                         // 0x4
    /* 0x010 */ int his_dns2;                         // 0x4
    /* 0x014 */ int my_dns1;                          // 0x4
    /* 0x018 */ int my_dns2;                          // 0x4
} anon_0_200;

/* anon_1_200 -- @anon1, 0x18 bytes, bsdsock.c (DIE 0x386B7C) */
typedef struct {   // size 0x18
    /* 0x000 */ int sockfd;                           // 0x4
    /* 0x004 */ struct sockaddr serv_addr;            // 0x10
    /* 0x014 */ int addrlen;                          // 0x4
} anon_1_200;

/* anon_2_200 -- @anon2, 0x51C bytes, bsdsock.c (DIE 0x386C0A) */
typedef struct {   // size 0x51C
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ short needToInit;                     // 0x2
    /* 0x006 */ short needToDial;                     // 0x2
    /* 0x008 */ short needToCd;                       // 0x2
    /* 0x00A */ short needToDisc;                     // 0x2
    /* 0x00C */ short speed;                          // 0x2
    /* 0x00E */ short stop;                           // 0x2
    /* 0x010 */ short parity;                         // 0x2
    /* 0x012 */ short databit;                        // 0x2
    /* 0x014 */ short flow;                           // 0x2
    /* 0x016 */ short dialtype;                       // 0x2
    /* 0x018 */ short outside_line;                   // 0x2
    /* 0x01A */ short pad;                            // 0x2
    /* 0x01C */ char userid[256];                     // 0x100
    /* 0x11C */ char passwd[256];                     // 0x100
    /* 0x21C */ char phonenumber[256];                // 0x100
    /* 0x31C */ char add_at_command[256];             // 0x100
    /* 0x41C */ char outside_number[256];             // 0x100
} anon_2_200;

/* anon_3_200 -- @anon3, 0x8 bytes, bsdsock.c (DIE 0x386ECA) */
typedef struct {   // size 0x8
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ int how;                              // 0x4
} anon_3_200;

/* anon_4_200 -- @anon4, 0xC bytes, bsdsock.c (DIE 0x386F27) */
typedef struct {   // size 0xC
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ int cmd;                              // 0x4
    /* 0x008 */ int argp;                             // 0x4
} anon_4_200;

/* anon_5_200 -- @anon5, 0x204 bytes, bsdsock.c (DIE 0x386FA5) */
typedef struct {   // size 0x204
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ char vendor[256];                     // 0x100
    /* 0x104 */ char product[256];                    // 0x100
} anon_5_200;

/* anon_6_200 -- @anon6, 0x24 bytes, bsdsock.c (DIE 0x38702F) */
typedef struct {   // size 0x24
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ unsigned int len;                     // 0x4
    /* 0x008 */ int flags;                            // 0x4
    /* 0x00C */ struct sockaddr to;                   // 0x10
    /* 0x01C */ int tolen;                            // 0x4
    /* 0x020 */ char buf[1];                          // 0x1
    /* 0x021 */ // 0x3 bytes padding
} anon_6_200;

/* anon_7_200 -- @anon7, 0x18 bytes, bsdsock.c (DIE 0x387113) */
typedef struct {   // size 0x18
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ struct sockaddr addr;                 // 0x10
    /* 0x014 */ int addrlen;                          // 0x4
} anon_7_200;

/* anon_8_200 -- @anon8, 0x24 bytes, bsdsock.c (DIE 0x38724D) */
typedef struct {   // size 0x24
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ unsigned int len;                     // 0x4
    /* 0x008 */ int flags;                            // 0x4
    /* 0x00C */ struct sockaddr from;                 // 0x10
    /* 0x01C */ int fromlen;                          // 0x4
    /* 0x020 */ char buf[1];                          // 0x1
    /* 0x021 */ // 0x3 bytes padding
} anon_8_200;

/* anon_9_200 -- @anon9, 0x10 bytes, bsdsock.c (DIE 0x387480) */
typedef struct {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
} anon_9_200;

/* anon_10_200 -- @anon10, 0x10 bytes, bsdsock.c (DIE 0x38752D) */
typedef struct {   // size 0x10
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ unsigned int len;                     // 0x4
    /* 0x008 */ int flags;                            // 0x4
    /* 0x00C */ char buf[1];                          // 0x1
    /* 0x00D */ // 0x3 bytes padding
} anon_10_200;

/* anon_11_200 -- @anon11, 0x10 bytes, bsdsock.c (DIE 0x38771C) */
typedef struct {   // size 0x10
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ unsigned int len;                     // 0x4
    /* 0x008 */ int flags;                            // 0x4
    /* 0x00C */ char buf[1];                          // 0x1
    /* 0x00D */ // 0x3 bytes padding
} anon_11_200;

/* anon_12_200 -- @anon12, 0x18 bytes, bsdsock.c (DIE 0x3878E5) */
typedef struct {   // size 0x18
    /* 0x000 */ int s;                                // 0x4
    /* 0x004 */ struct sockaddr name;                 // 0x10
    /* 0x014 */ int namelen;                          // 0x4
} anon_12_200;

/* anon_13_200 -- @anon13, 0x10C bytes, bsdsock.c (DIE 0x3879D1) */
typedef struct {   // size 0x10C
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int pri;                              // 0x4
    /* 0x008 */ int sec;                              // 0x4
    /* 0x00C */ char domain[256];                     // 0x100
} anon_13_200;

/* anon_16_200 -- @anon16, 0x8 bytes, bsdsock.c (DIE 0x387BCB) */
typedef struct {   // size 0x8
    /* 0x000 */ int dns_pri;                          // 0x4
    /* 0x004 */ int dns_sec;                          // 0x4
} anon_16_200;

/* anon_18_200 -- @anon18, 0x10 bytes, bsdsock.c (DIE 0x387D4A) */
typedef struct {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
} anon_18_200;

/* anon_19_200 -- @anon19, 0x18 bytes, bsdsock.c (DIE 0x387DF8) */
typedef struct {   // size 0x18
    /* 0x000 */ int sockfd;                           // 0x4
    /* 0x004 */ struct sockaddr my_addr;              // 0x10
    /* 0x014 */ int addrlen;                          // 0x4
} anon_19_200;

/* anon_20_200 -- @anon20, 0xC bytes, bsdsock.c (DIE 0x387ECD) */
typedef struct {   // size 0xC
    /* 0x000 */ int domain;                           // 0x4
    /* 0x004 */ int type;                             // 0x4
    /* 0x008 */ int protocol;                         // 0x4
} anon_20_200;

/* anon_21_200 -- @anon21, 0x8 bytes, bsdsock.c (DIE 0x3880B9) */
typedef struct {   // size 0x8
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int gw;                               // 0x4
} anon_21_200;


/* variables (8) */
static int startflag;                                            /* @0x002DE620 size 0x4 */
char _ctype_[];                                                  /* @0x002CFC6F */
int netsemaid;                                                   /* @0x002DE62C size 0x4 */
int sdata[1088];                                                 /* @0x0080B5C0 size 0x1100 */
struct _sif_client_data cdBsdSocket;                             /* @0x0080B570 size 0x28 */
unsigned int dnssec;                                             /* @0x002DE624 size 0x4 */
unsigned int dnspri;                                             /* @0x002DE628 size 0x4 */
int myip;                                                        /* @0x002DE630 size 0x4 */

/* functions defined (35) */
unsigned int inet_addr(char *cp);                                /* 0x007F2B60-0x007F2ED8 lines 1036-1090 */
char *inet_ntoa(struct in_addr in);                              /* 0x007F2EE0-0x007F2F3C lines 1015-1026 */
unsigned short htons(unsigned short hostshort);                  /* 0x007F2F40-0x007F2F64 lines 993-994 */
int ktNetDhcpGetGw(int *gw);                                     /* 0x007F2F70-0x007F301C lines 898-910 */
int ktNetDhcpGetDns(char *domain, int *pri, int *sec);           /* 0x007F3020-0x007F30FC lines 877-891 */
int ktNetDhcpTimer(void);                                        /* 0x007F3100-0x007F318C lines 860-870 */
int ktNetDhcpRelease(int ip);                                    /* 0x007F3190-0x007F3228 lines 843-854 */
int ktNetDhcpRequest(anon_9_200 *dhcpreq);                       /* 0x007F3230-0x007F32E4 lines 824-836 */
int ktNetDhcpEnd(void);                                          /* 0x007F32F0-0x007F337C lines 808-817 */
int ktNetDhcpStart(void);                                        /* 0x007F3380-0x007F340C lines 792-801 */
int ktNetEtherEnd(void);                                         /* 0x007F3410-0x007F349C lines 759-768 */
int ktNetEtherDown(void);                                        /* 0x007F34A0-0x007F352C lines 741-750 */
int ktNetEtherUp(anon_18_200 *eth);                              /* 0x007F3530-0x007F35D8 lines 721-735 */
int ktNetEtherStart(void);                                       /* 0x007F35E0-0x007F366C lines 706-715 */
int ktNetAVETCPEnd(void);                                        /* 0x007F3670-0x007F3724 lines 637-651 */
int ktNetAVETCPStart(int an986);                                 /* 0x007F3730-0x007F37F8 lines 616-631 */
unsigned int gethostbyname_nb(char *name);                       /* 0x007F3800-0x007F38B8 lines 497-512 */
int ioctlsocket(int s, int cmd, unsigned int *argp);             /* 0x007F38C0-0x007F3978 lines 458-475 */
int recvcheck(int sockfd);                                       /* 0x007F3980-0x007F3A18 lines 440-453 */
int recvfrom(int s, void *buf, unsigned int len, int flags, struct sockaddr *from, int *fromlen); /* 0x007F3A20-0x007F3B64 lines 408-431 */
int sendto(int s, void *msg, unsigned int len, int flags, struct sockaddr *to, int tolen); /* 0x007F3B70-0x007F3C80 lines 384-404 */
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);     /* 0x007F3C80-0x007F3D4C lines 341-358 */
int closesocket(int s);                                          /* 0x007F3D50-0x007F3E04 lines 305-319 */
int recv(int s, void *buf, unsigned int len, int flags);         /* 0x007F3E10-0x007F3EFC lines 264-282 */
int send(int s, void *msg, unsigned int len, int flags);         /* 0x007F3F00-0x007F3FDC lines 251-253 */
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen); /* 0x007F3FE0-0x007F40AC lines 209-226 */
int socket(int domain, int type, int protocol);                  /* 0x007F40B0-0x007F4164 lines 189-206 */
int unsetdefaultgw(int gw);                                      /* 0x007F4170-0x007F41FC lines 172-184 */
int setdefaultgw(int gw);                                        /* 0x007F4200-0x007F428C lines 155-169 */
int getdnsaddr(int *dns_pri, int *dns_sec);                      /* 0x007F4290-0x007F42AC lines 147-150 */
int setdnsaddr(int dns_pri, int dns_sec);                        /* 0x007F42B0-0x007F435C lines 124-142 */
int getmyinetaddr(void);                                         /* 0x007F4360-0x007F436C lines 118-119 */
void setmyinetaddr(int setmyip);                                 /* 0x007F4370-0x007F437C lines 112-113 */
int bsdsocket_terminate(void);                                   /* 0x007F4380-0x007F43C8 lines 102-107 */
int bsdsocket_init(void);                                        /* 0x007F43D0-0x007F449C lines 67-99 */

#endif /* DDR_UNIT_src_network_lib_bsdsock_bsdsock_c_H */
