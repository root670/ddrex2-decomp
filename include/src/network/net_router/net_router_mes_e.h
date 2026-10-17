/*
 * C:\work2\usaex2\src\network\net_router\net_router_mes_e.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 3 functions, code 0x00806410-0x00806468
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_router_net_router_mes_e_c_H
#define DDR_UNIT_src_network_net_router_net_router_mes_e_c_H

/* variables (6) */
static unsigned char *CHECKING[2];                               /* @0x002DDEC8 size 0x8 */
static unsigned char *UPNP_YN[4];                                /* @0x00806E60 size 0x10 */
static unsigned char *UPNP_EXP[3];                               /* @0x00806E70 size 0xC */
static unsigned char *BAD_ROUTER[3];                             /* @0x00806E80 size 0xC */
unsigned char **nrMessageTbl_ENGLISH[4];                         /* @0x00806E90 size 0x10 */
unsigned char *cmes_yesno_str_english[];                         /* @0x002DD738 */

/* functions defined (3) */
unsigned char *nrmesGetNo(void);                                 /* 0x00806410-0x0080641C lines 79-80 */
unsigned char *nrmesGetYes(void);                                /* 0x00806420-0x0080642C lines 76-77 */
unsigned char **nrmesGetMessageTable(int id);                    /* 0x00806430-0x00806468 lines 67-72 */

#endif /* DDR_UNIT_src_network_net_router_net_router_mes_e_c_H */
