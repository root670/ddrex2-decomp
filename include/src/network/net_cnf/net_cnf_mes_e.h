/*
 * C:\work2\usaex2\src\network\net_cnf\net_cnf_mes_e.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0020A1F0-0x0020A248
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_cnf_net_cnf_mes_e_c_H
#define DDR_UNIT_src_network_net_cnf_net_cnf_mes_e_c_H

/* variables (26) */
static unsigned char warning0[51];                               /* @0x002BB5D0 size 0x33 */
static unsigned char warning1[56];                               /* @0x002BB610 size 0x38 */
static unsigned char *NETDEV_CHECKING[3];                        /* @0x002BB648 size 0xC */
static unsigned char *NETDEV_OK[3];                              /* @0x002BB658 size 0xC */
static unsigned char *NETDEV_ERR[6];                             /* @0x002BB670 size 0x18 */
static unsigned char *MC_CHECKING[4];                            /* @0x002BB690 size 0x10 */
static unsigned char *MC_UNFORMAT_YN_CHECK[5];                   /* @0x002BB6A0 size 0x14 */
static unsigned char *MC_NO_CARD_YN_CHECK[5];                    /* @0x002BB6C0 size 0x14 */
static unsigned char *MC_CHECK_ERR_YN_CHECK[5];                  /* @0x002BB6E0 size 0x14 */
static unsigned char *MC_NO_YNCF_YN_CHECK[4];                    /* @0x002BB700 size 0x10 */
static unsigned char *NETCNF_CHECKING[4];                        /* @0x002BB710 size 0x10 */
static unsigned char *NETCNF_NO_NET_YN_CHECK[4];                 /* @0x002BB720 size 0x10 */
static unsigned char *NETCNF_NO_IFC_YN_CHECK[4];                 /* @0x002BB730 size 0x10 */
static unsigned char *NETCNF_ERR_YN_CHECK[5];                    /* @0x002BB740 size 0x14 */
static unsigned char *NETCNF_LETHAL_ERR_YN_CHECK[5];             /* @0x002BB760 size 0x14 */
static unsigned char *NETCNF_MAGIC_ERR_YN_CHECK[5];              /* @0x002BB780 size 0x14 */
static unsigned char *WARNING_HOWTO_EDIT[4];                     /* @0x002BB7A0 size 0x10 */
static unsigned char *WARNING_NOT_AVAILABLE[3];                  /* @0x002BB7B0 size 0xC */
static unsigned char *SELECT_IFC[2];                             /* @0x002DDAF0 size 0x8 */
static unsigned char *BASE_TITLE[2];                             /* @0x002DDAF8 size 0x8 */
static unsigned char *UPNP_YN[4];                                /* @0x002BB7C0 size 0x10 */
static unsigned char *UPNP_EXP[3];                               /* @0x002BB7D0 size 0xC */
static unsigned char *IRX_LOADING[2];                            /* @0x002DDB00 size 0x8 */
static unsigned char *IRX_LOAD_ERR[2];                           /* @0x002DDB08 size 0x8 */
unsigned char **ncMessageTbl_ENGLISH[22];                        /* @0x002BB7E0 size 0x58 */
unsigned char *cmes_yesno_str_english[];                         /* @0x002DD738 */

/* functions defined (3) */
unsigned char *ncmesGetNo(void);                                 /* 0x0020A1F0-0x0020A1FC lines 250-251 */
unsigned char *ncmesGetYes(void);                                /* 0x0020A200-0x0020A20C lines 247-248 */
unsigned char **ncmesGetMessageTable(int id);                    /* 0x0020A210-0x0020A248 lines 238-243 */

#endif /* DDR_UNIT_src_network_net_cnf_net_cnf_mes_e_c_H */
