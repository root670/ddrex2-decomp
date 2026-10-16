/*
 * C:\work\usam2\src\CS\bk_load.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0022AF60-0x0022B050
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_bk_load_c_H
#define DDR_UNIT_src_CS_bk_load_c_H

/* variables (1) */
static unsigned char *xxxx_bk_tm2_tbl[69];                       /* @0x00282820 size 0x114 */

/* functions defined (3) */
int sysReadMusicBk(unsigned int *load_addr, int id);             /* 0x0022AF60-0x0022AFCC lines 243-256 */
int sysWaitMusicBk(void);                                        /* 0x0022AFD0-0x0022B004 lines 230-236 */
int sysSetMusicBk(unsigned int *load_addr, int id);              /* 0x0022B010-0x0022B050 lines 211-222 */

#endif /* DDR_UNIT_src_CS_bk_load_c_H */
