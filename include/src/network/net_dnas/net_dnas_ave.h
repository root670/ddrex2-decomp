/*
 * C:\work2\usaex2\src\network\net_dnas\net_dnas_ave.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 5 functions, code 0x00802E20-0x00804034
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_dnas_net_dnas_ave_c_H
#define DDR_UNIT_src_network_net_dnas_net_dnas_ave_c_H

#include "types/_tag_cNetDnasAve.h"
#include "types/dginfo.h"
#include "types/pp_status.h"
#include "types/sceNetcnfifData.h"

/* variables (2) */
struct _tag_cNetDnasAve *pNetDnasAve;                            /* @0x002DDEA8 size 0x4 */
static struct _tag_cNetDnasAve _pNetDnasAve;                     /* @0x0080CA00 size 0xD6C */

/* functions defined (5) */
int reset_ave_for_dnas_main(void);                               /* 0x00802E20-0x008031D8 lines 492-605 */
int reset_ave_for_dnas_init(void);                               /* 0x008031E0-0x008031F8 lines 484-490 */
static unsigned int aton(unsigned char *addr);                   /* 0x00803200-0x008032F0 lines 435-476 */
int setup_ave_for_dnas_main(void);                               /* 0x008032F0-0x00803FC0 lines 104-430 */
int setup_ave_for_dnas_init(struct sceNetcnfifData *net_cnf_data); /* 0x00803FC0-0x00804034 lines 87-102 */

#endif /* DDR_UNIT_src_network_net_dnas_net_dnas_ave_c_H */
