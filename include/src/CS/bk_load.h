/*
 * C:\work2\usaex2\src\CS\bk_load.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001B7A30-0x001B7AB0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_bk_load_c_H
#define DDR_UNIT_src_CS_bk_load_c_H

/* variables (1) */
static unsigned char *xxxx_bk_tm2_tbl[75];                       /* @0x002AF6F0 size 0x12C */

/* functions defined (2) */
int sysWaitMusicBk(void);                                        /* 0x001B7A30-0x001B7A64 lines 188-194 */
int sysSetMusicBk(unsigned int *load_addr, int id);              /* 0x001B7A70-0x001B7AB0 lines 171-180 */

#endif /* DDR_UNIT_src_CS_bk_load_c_H */
