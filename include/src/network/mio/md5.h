/*
 * C:\work2\usaex2\src\network\mio\md5.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x002448E0-0x00245CFC
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
#ifndef DDR_UNIT_src_network_mio_md5_c_H
#define DDR_UNIT_src_network_mio_md5_c_H

/* anonymous types (1) */

/* anon_0_115 -- @anon0, 0x58 bytes, md5.c (DIE 0x2056C5) */
typedef struct {   // size 0x58
    /* 0x000 */ unsigned int state[4];                // 0x10
    /* 0x010 */ unsigned int count[2];                // 0x8
    /* 0x018 */ unsigned char buffer[64];             // 0x40
} anon_0_115;


/* variables (1) */
static unsigned char PADDING[64];                                /* @0x002BF0A0 size 0x40 */

/* functions defined (4) */
static void MD5Transform(unsigned int *state, unsigned char *block); /* 0x002448E0-0x002459F8 lines 213-298 */
void MD5Final(unsigned char *digest, anon_0_115 *context);       /* 0x00245A00-0x00245BB4 lines 181-203 */
void MD5Update(anon_0_115 *context, unsigned char *input, unsigned int inputLen); /* 0x00245BC0-0x00245CC0 lines 138-170 */
void MD5Init(anon_0_115 *context);                               /* 0x00245CC0-0x00245CFC lines 116-123 */

#endif /* DDR_UNIT_src_network_mio_md5_c_H */
