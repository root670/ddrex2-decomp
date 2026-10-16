/*
 * C:\work2\usaex2\src\network\mio\blowfish.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x00244590-0x002448D4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_mio_blowfish_c_H
#define DDR_UNIT_src_network_mio_blowfish_c_H

/* anonymous types (1) */

/* anon_0_114 -- @anon0, 0x1048 bytes, blowfish.c (DIE 0x204F8A) */
struct anon_0_114 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};


/* variables (2) */
static unsigned int ORIG_P[18];                                  /* @0x002D5250 size 0x48 */
static unsigned int ORIG_S[4][256];                              /* @0x002D52A0 size 0x1000 */

/* functions defined (3) */
void Blowfish_Init(struct anon_0_114 *ctx, unsigned char *key, int keyLen); /* 0x00244590-0x00244758 lines 735-776 */
void Blowfish_Decrypt(struct anon_0_114 *ctx, unsigned int *xl, unsigned int *xr); /* 0x00244760-0x00244814 lines 683-729 */
void Blowfish_Encrypt(struct anon_0_114 *ctx, unsigned int *xl, unsigned int *xr); /* 0x00244820-0x002448D4 lines 619-661 */

#endif /* DDR_UNIT_src_network_mio_blowfish_c_H */
