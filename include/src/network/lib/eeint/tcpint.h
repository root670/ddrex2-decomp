/*
 * C:\work2\usaex2\src\network\lib\eeint\tcpint.c
 * MW MIPS C Compiler, overlay main; 54 functions, code 0x00241020-0x0024293C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_lib_eeint_tcpint_c_H
#define DDR_UNIT_src_network_lib_eeint_tcpint_c_H

#include "types/_sif_client_data.h"
#include "types/dginfo.h"
#include "types/pp_status.h"

/* anonymous types (32) */

/* anon_0_112 -- @anon0, 0xC bytes, tcpint.c (DIE 0x1F7E29) */
struct anon_0_112 {   // size 0xC
    /* 0x000 */ unsigned int leasetime;               // 0x4
    /* 0x004 */ unsigned int t1;                      // 0x4
    /* 0x008 */ unsigned int t2;                      // 0x4
};

/* anon_1_112 -- @anon1, 0x6 bytes, tcpint.c (DIE 0x1F7ED0) */
struct anon_1_112 {   // size 0x6
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ short len;                            // 0x2
    /* 0x004 */ unsigned char buf[1];                 // 0x1
    /* 0x005 */ // 0x1 bytes padding
};

/* anon_2_112 -- @anon2, 0x8 bytes, tcpint.c (DIE 0x1F7F50) */
struct anon_2_112 {   // size 0x8
    /* 0x000 */ unsigned int lease_time;              // 0x4
    /* 0x004 */ int max_retry_cnt;                    // 0x4
};

/* anon_3_112 -- @anon3, 0x20 bytes, tcpint.c (DIE 0x1F8008) */
struct anon_3_112 {   // size 0x20
    /* 0x000 */ unsigned char hostname[32];           // 0x20
};

/* anon_4_112 -- @anon4, 0x8 bytes, tcpint.c (DIE 0x1F8072) */
struct anon_4_112 {   // size 0x8
    /* 0x000 */ unsigned int ipaddr;                  // 0x4
    /* 0x004 */ unsigned short dstport;               // 0x2
    /* 0x006 */ unsigned short srcport;               // 0x2
};

/* anon_5_112 -- @anon5, 0x10 bytes, tcpint.c (DIE 0x1F80FC) */
struct anon_5_112 {   // size 0x10
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ unsigned int youraddr;                // 0x4
    /* 0x008 */ short len;                            // 0x2
    /* 0x00A */ unsigned char ttl;                    // 0x1
    /* 0x00B */ unsigned char svctype;                // 0x1
    /* 0x00C */ unsigned char df_flag;                // 0x1
    /* 0x00D */ unsigned char buf[1];                 // 0x1
    /* 0x00E */ // 0x2 bytes padding
};

/* anon_6_112 -- @anon6, 0x14 bytes, tcpint.c (DIE 0x1F8209) */
struct anon_6_112 {   // size 0x14
    /* 0x000 */ unsigned int lease_time;              // 0x4
    /* 0x004 */ unsigned int ipaddr;                  // 0x4
    /* 0x008 */ unsigned int netmask;                 // 0x4
    /* 0x00C */ unsigned int bcaddr;                  // 0x4
    /* 0x010 */ int max_retry_cnt;                    // 0x4
};

/* anon_7_112 -- @anon7, 0x8 bytes, tcpint.c (DIE 0x1F82E3) */
struct anon_7_112 {   // size 0x8
    /* 0x000 */ unsigned int dstaddr;                 // 0x4
    /* 0x004 */ unsigned int gtwayaddr;               // 0x4
};

/* anon_8_112 -- @anon8, 0xC bytes, tcpint.c (DIE 0x1F834C) */
struct anon_8_112 {   // size 0xC
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ unsigned int ipaddr;                  // 0x4
    /* 0x008 */ unsigned short dstport;               // 0x2
    /* 0x00A */ unsigned short srcport;               // 0x2
};

/* anon_9_112 -- @anon9, 0x108 bytes, tcpint.c (DIE 0x1F83F5) */
struct anon_9_112 {   // size 0x108
    /* 0x000 */ unsigned char domain[256];            // 0x100
    /* 0x100 */ unsigned int pr_server;               // 0x4
    /* 0x104 */ unsigned int se_server;               // 0x4
};

/* anon_10_112 -- @anon10, 0x108 bytes, tcpint.c (DIE 0x1F8485) */
struct anon_10_112 {   // size 0x108
    /* 0x000 */ unsigned char def_domain[256];        // 0x100
    /* 0x100 */ unsigned int prim_svr;                // 0x4
    /* 0x104 */ unsigned int sec_svr;                 // 0x4
};

/* anon_11_112 -- @anon11, 0xA bytes, tcpint.c (DIE 0x1F8517) */
struct anon_11_112 {   // size 0xA
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ unsigned short stat;                  // 0x2
    /* 0x004 */ unsigned short reserve;               // 0x2
    /* 0x006 */ unsigned short sendwin;               // 0x2
    /* 0x008 */ unsigned short recvwin;               // 0x2
};

/* anon_12_112 -- @anon12, 0x8 bytes, tcpint.c (DIE 0x1F85E3) */
struct anon_12_112 {   // size 0x8
    /* 0x000 */ unsigned int ipaddr;                  // 0x4
    /* 0x004 */ short protocol;                       // 0x2
    /* 0x006 */ // 0x2 bytes padding
};

/* anon_13_112 -- @anon13, 0xC bytes, tcpint.c (DIE 0x1F864B) */
struct anon_13_112 {   // size 0xC
    /* 0x000 */ unsigned int ipaddr;                  // 0x4
    /* 0x004 */ unsigned int netmask;                 // 0x4
    /* 0x008 */ unsigned int bcaddr;                  // 0x4
};

/* anon_14_112 -- @anon14, 0x504 bytes, tcpint.c (DIE 0x1F8877) */
struct anon_14_112 {   // size 0x504
    /* 0x000 */ short use_ipcp;                       // 0x2
    /* 0x002 */ short dialtype;                       // 0x2
    /* 0x004 */ unsigned char telephone_number[256];  // 0x100
    /* 0x104 */ unsigned char login[256];             // 0x100
    /* 0x204 */ unsigned char password[256];          // 0x100
    /* 0x304 */ unsigned char outside_number[256];    // 0x100
    /* 0x404 */ unsigned char additional_at_command[256];  // 0x100
};

/* anon_15_112 -- @anon15, 0x4 bytes, tcpint.c (DIE 0x1F89BC) */
struct anon_15_112 {   // size 0x4
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ short what;                           // 0x2
};

/* anon_16_112 -- @anon16, 0xC bytes, tcpint.c (DIE 0x1F8A1C) */
struct anon_16_112 {   // size 0xC
    /* 0x000 */ unsigned int ipaddr;                  // 0x4
    /* 0x004 */ unsigned int netmask;                 // 0x4
    /* 0x008 */ unsigned int broadcast;               // 0x4
};

/* anon_17_112 -- @anon17, 0x104 bytes, tcpint.c (DIE 0x1F8AA9) */
struct anon_17_112 {   // size 0x104
    /* 0x000 */ short option;                         // 0x2
    /* 0x002 */ short optlen;                         // 0x2
    /* 0x004 */ unsigned char optval[256];            // 0x100
};

/* anon_18_112 -- @anon18, 0x8 bytes, tcpint.c (DIE 0x1F8B34) */
struct anon_18_112 {   // size 0x8
    /* 0x000 */ unsigned int ipaddr;                  // 0x4
    /* 0x004 */ int retrans_cnt;                      // 0x4
};

/* anon_19_112 -- @anon19, 0xC bytes, tcpint.c (DIE 0x1F8B9F) */
struct anon_19_112 {   // size 0xC
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ short new_nh;                         // 0x2
    /* 0x004 */ unsigned int dstaddr;                 // 0x4
    /* 0x008 */ unsigned short dstport;               // 0x2
    /* 0x00A */ // 0x2 bytes padding
};

/* anon_20_112 -- @anon20, 0xC bytes, tcpint.c (DIE 0x1F8C49) */
struct anon_20_112 {   // size 0xC
    /* 0x000 */ unsigned int ipaddr;                  // 0x4
    /* 0x004 */ unsigned int netmask;                 // 0x4
    /* 0x008 */ unsigned int broadcast;               // 0x4
};

/* anon_21_112 -- @anon21, 0x10 bytes, tcpint.c (DIE 0x1F8CFA) */
struct anon_21_112 {   // size 0x10
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ unsigned int youraddr;                // 0x4
    /* 0x008 */ unsigned short yourport;              // 0x2
    /* 0x00A */ short len;                            // 0x2
    /* 0x00C */ unsigned char ttl;                    // 0x1
    /* 0x00D */ unsigned char svctype;                // 0x1
    /* 0x00E */ unsigned char df_flag;                // 0x1
    /* 0x00F */ unsigned char buf[1];                 // 0x1
};

/* anon_22_112 -- @anon22, 0x8 bytes, tcpint.c (DIE 0x1F8E54) */
struct anon_22_112 {   // size 0x8
    /* 0x000 */ unsigned int ipaddr;                  // 0x4
    /* 0x004 */ unsigned short dstport;               // 0x2
    /* 0x006 */ unsigned short srcport;               // 0x2
};

/* anon_23_112 -- @anon23, 0x200 bytes, tcpint.c (DIE 0x1F8EDF) */
struct anon_23_112 {   // size 0x200
    /* 0x000 */ unsigned char host[512];              // 0x200
};

/* anon_24_112 -- @anon24, 0x10 bytes, tcpint.c (DIE 0x1F906D) */
struct anon_24_112 {   // size 0x10
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ unsigned int youraddr;                // 0x4
    /* 0x008 */ unsigned short yourport;              // 0x2
    /* 0x00A */ short len;                            // 0x2
    /* 0x00C */ unsigned char buf[1];                 // 0x1
    /* 0x00D */ // 0x3 bytes padding
};

/* anon_25_112 -- @anon25, 0xC34 bytes, tcpint.c (DIE 0x1F9138) */
struct anon_25_112 {   // size 0xC34
    /* 0x000 */ int bufnum;                           // 0x4
    /* 0x004 */ struct dginfo buf[4];                 // 0xC30
};

/* anon_26_112 -- @anon26, 0x10 bytes, tcpint.c (DIE 0x1F9474) */
struct anon_26_112 {   // size 0x10
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ short len;                            // 0x2
    /* 0x004 */ unsigned short srcport;               // 0x2
    /* 0x006 */ // 0x2 bytes padding
    /* 0x008 */ unsigned int srcaddr;                 // 0x4
    /* 0x00C */ unsigned char buf[1];                 // 0x1
    /* 0x00D */ // 0x3 bytes padding
};

/* anon_27_112 -- @anon27, 0x6 bytes, tcpint.c (DIE 0x1F9587) */
struct anon_27_112 {   // size 0x6
    /* 0x000 */ unsigned char addr[6];                // 0x6
};

/* anon_28_112 -- @anon28, 0xC bytes, tcpint.c (DIE 0x1F9780) */
struct anon_28_112 {   // size 0xC
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ short len;                            // 0x2
    /* 0x004 */ unsigned int srcaddr;                 // 0x4
    /* 0x008 */ unsigned char buf[1];                 // 0x1
    /* 0x009 */ // 0x3 bytes padding
};

/* anon_29_112 -- @anon29, 0x104 bytes, tcpint.c (DIE 0x1F98E2) */
struct anon_29_112 {   // size 0x104
    /* 0x000 */ short optname;                        // 0x2
    /* 0x002 */ short optlen;                         // 0x2
    /* 0x004 */ unsigned char optval[256];            // 0x100
};

/* anon_30_112 -- @anon30, 0x100 bytes, tcpint.c (DIE 0x1F9992) */
struct anon_30_112 {   // size 0x100
    /* 0x000 */ struct anon_7_112 entry[32];          // 0x100
};

/* anon_31_112 -- @anon31, 0x106 bytes, tcpint.c (DIE 0x1F9AF8) */
struct anon_31_112 {   // size 0x106
    /* 0x000 */ short nh;                             // 0x2
    /* 0x002 */ short optname;                        // 0x2
    /* 0x004 */ short optlen;                         // 0x2
    /* 0x006 */ unsigned char optval[256];            // 0x100
};


/* variables (3) */
unsigned __int128 outdata[256];                                  /* @0x0071F980 size 0x1000 */
unsigned int indata[1024];                                       /* @0x00720980 size 0x1000 */
struct _sif_client_data cdAveTcp;                                /* @0x00721980 size 0x28 */

/* functions defined (54) */
short SelectDevice(int device_uid);                              /* 0x00241020-0x00241078 lines 2158-2165 */
short GetDeviceInfo(struct dginfo *buf, int bufnum);             /* 0x00241080-0x0024113C lines 2129-2152 */
short GetDeviceInfoNum(int *num);                                /* 0x00241140-0x002411A8 lines 2117-2123 */
short DnsLookUpRev(short ticket_id, unsigned char *name);        /* 0x002411B0-0x00241224 lines 2066-2082 */
short DnsLookUp(short ticket_id, unsigned int *addr);            /* 0x00241230-0x002412A0 lines 2037-2053 */
short DnsReleaseTicket(short ticket_id);                         /* 0x002412A0-0x002412F8 lines 2012-2025 */
short DnsGetTicket(unsigned char *host);                         /* 0x00241300-0x00241374 lines 1985-2001 */
short DnsDisp(void);                                             /* 0x00241380-0x002413D0 lines 1967-1973 */
short DnsInit(unsigned char *def_domain, unsigned int prim_svr, unsigned int sec_svr); /* 0x002413D0-0x00241474 lines 1940-1959 */
short DhcpReleaseNb(unsigned int ipaddr, int retrans_cnt);       /* 0x00241480-0x002414E0 lines 1913-1927 */
short DhcpTimer(void);                                           /* 0x002414E0-0x00241530 lines 1869-1875 */
short DhcpGetIfInfo(unsigned int *ip_addr, unsigned int *netmask, unsigned int *bcaddr); /* 0x00241530-0x002415C4 lines 1847-1861 */
short DhcpRequestNb(unsigned int lease_time, int max_retry_cnt); /* 0x002415D0-0x00241630 lines 1819-1833 */
short DhcpGetGateway(unsigned int *gateway);                     /* 0x00241630-0x00241698 lines 1690-1701 */
short DhcpGetDns(unsigned char *domain, unsigned int *pr_server, unsigned int *se_server); /* 0x002416A0-0x00241738 lines 1666-1679 */
short DhcpDisp(void);                                            /* 0x00241740-0x00241790 lines 1645-1651 */
short DhcpInit(void);                                            /* 0x00241790-0x002417E0 lines 1631-1637 */
short NdgFinish(void);                                           /* 0x002417E0-0x00241830 lines 1617-1623 */
short NdgStartPollStatus(void);                                  /* 0x00241830-0x00241880 lines 1604-1609 */
short NdgStart(int mode);                                        /* 0x00241880-0x002418D8 lines 1588-1595 */
short NdgDisp(void);                                             /* 0x002418E0-0x00241930 lines 1567-1573 */
short NdgInit(void);                                             /* 0x00241930-0x00241980 lines 1553-1559 */
short PppStatus(struct pp_status *pp_status);                    /* 0x00241980-0x00241A3C lines 1450-1462 */
short PppFinish(void);                                           /* 0x00241A40-0x00241A90 lines 1432-1438 */
short PppStart(short use_ipcp, short dialtype, char *telephone_number, char *login, char *password, char *outside_number, char *at_command, short use_pppoe, int eth_nego); /* 0x00241A90-0x00241B80 lines 1402-1424 */
short PppDisp(void);                                             /* 0x00241B80-0x00241BD0 lines 1364-1370 */
short PppInit(void);                                             /* 0x00241BD0-0x00241C20 lines 1350-1356 */
short UdpClose(short nh);                                        /* 0x00241C20-0x00241C78 lines 1213-1225 */
short UdpRecv(short *nh, short *len, unsigned int *srcaddr, unsigned short *srcport, unsigned char *buf); /* 0x00241C80-0x00241D58 lines 1183-1202 */
short UdpCheckRecv(void);                                        /* 0x00241D60-0x00241DB0 lines 1159-1165 */
short UdpSend2(short nh, short len, unsigned int youraddr, unsigned short yourport, unsigned char *buf, unsigned char ttl, unsigned char svctype, unsigned char df_flag); /* 0x00241DB0-0x00241E70 lines 1121-1148 */
short UdpSend(short nh, short len, unsigned int youraddr, unsigned short yourport, unsigned char *buf); /* 0x00241E70-0x00241F20 lines 1082-1102 */
short UdpOpen(unsigned int ipaddr, unsigned short dstport, unsigned short srcport); /* 0x00241F20-0x00241F84 lines 1052-1066 */
short RouteDel(unsigned int dstaddr, unsigned int gtwayaddr);    /* 0x00241F90-0x00241FF0 lines 990-1004 */
short RouteAdd(unsigned int dstaddr, unsigned int gtwayaddr);    /* 0x00241FF0-0x00242050 lines 964-978 */
short TcpSendNotifyCheck(short nh);                              /* 0x00242050-0x002420A8 lines 940-952 */
short TcpGetEvent(short nh);                                     /* 0x002420B0-0x00242108 lines 878-890 */
short TcpDelete(short nh);                                       /* 0x00242110-0x00242168 lines 845-857 */
short TcpCancel(short nh, short what);                           /* 0x00242170-0x002421D0 lines 819-834 */
short TcpRecvNb(short nh, unsigned char *buf, short len);        /* 0x002421D0-0x002422F0 lines 777-807 */
short TcpSendNb(short nh, unsigned char *buf, short len);        /* 0x002422F0-0x002423A8 lines 666-685 */
short TcpStat(short nh, short *stat, short *sendwin, short *recvwin); /* 0x002423B0-0x0024244C lines 601-620 */
short TcpGetaddr(short nh, unsigned int *ipaddr, unsigned short *myport, unsigned short *yourport); /* 0x00242450-0x002424F0 lines 569-587 */
short TcpAbort(short nh);                                        /* 0x002424F0-0x00242548 lines 542-554 */
short TcpClose(short nh);                                        /* 0x00242550-0x002425A8 lines 519-531 */
short TcpAccept(short nh);                                       /* 0x002425B0-0x00242608 lines 475-486 */
short TcpPopen(unsigned int ipaddr, unsigned short dstport, unsigned short srcport); /* 0x00242610-0x00242674 lines 451-464 */
short TcpOpen(unsigned int ipaddr, unsigned short dstport, unsigned short srcport); /* 0x00242680-0x002426E4 lines 425-438 */
short Ifdown(void);                                              /* 0x002426F0-0x00242740 lines 284-290 */
short Ifconfig(unsigned int ipaddr, unsigned int netmask, unsigned int broadcast); /* 0x00242740-0x002427A4 lines 261-276 */
short Getconfig(unsigned int *ipaddr, unsigned int *netmask, unsigned int *broadcast); /* 0x002427B0-0x00242844 lines 233-248 */
short TcpTerminate(void);                                        /* 0x00242850-0x002428A0 lines 214-220 */
short TcpInitialize(void);                                       /* 0x002428A0-0x002428F0 lines 200-206 */
void AveTcpRpcInit(void);                                        /* 0x002428F0-0x0024293C lines 166-179 */

#endif /* DDR_UNIT_src_network_lib_eeint_tcpint_c_H */
