/*
 * C:\work2\usaex2\src\network\net_inter.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x00257450-0x002576CC
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
#ifndef DDR_UNIT_src_network_net_inter_c_H
#define DDR_UNIT_src_network_net_inter_c_H

#include "types/_CWS_WIN_W.h"

/* functions referenced (1) */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */

/* functions defined (7) */
char NetInterErrGetStatus(void);                                 /* 0x00257450-0x00257484 lines 75-80 */
void NetInterErrClose(void);                                     /* 0x00257490-0x002574A0 lines 70-70 */
void NetInterErrOpen(void);                                      /* 0x002574A0-0x002574E4 lines 61-65 */
void NetInterErrSet2Code(int _answer, int _proc, unsigned char *_func_str); /* 0x002574F0-0x00257588 lines 48-56 */
void NetInterErrSet1Code(int _err_num, unsigned char *_str);     /* 0x00257590-0x00257614 lines 33-40 */
void NetInterErrSet0Code(unsigned char *_str);                   /* 0x00257620-0x0025767C lines 22-29 */
void NetInterErrInit(void);                                      /* 0x00257680-0x002576CC lines 14-18 */

#endif /* DDR_UNIT_src_network_net_inter_c_H */
