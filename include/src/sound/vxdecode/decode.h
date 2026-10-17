/*
 * C:\work2\usaex2\src\sound\vxdecode\decode.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x001D03C0-0x001D08AC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_sound_vxdecode_decode_c_H
#define DDR_UNIT_src_sound_vxdecode_decode_c_H

/* anonymous types (2) */

/* anon_0_28 -- @anon0, 0x10 bytes, decode.c (DIE 0x45010) */
typedef struct {   // size 0x10
    /* 0x000 */ long dH;                              // 0x8
    /* 0x008 */ long dL;                              // 0x8
} anon_0_28;

/* anon_1_28 -- @anon1, 0x10 bytes, decode.c (DIE 0x45091) */
typedef struct {   // size 0x10
    /* 0x000 */ double dH;                            // 0x8
    /* 0x008 */ double dL;                            // 0x8
} anon_1_28;


/* variables (11) */
anon_1_28 *pWorkf;                                               /* @0x002DE4C8 size 0x4 */
unsigned char nHigh[];                                           /* @0x002B6720 */
unsigned char nLow[];                                            /* @0x002B6620 */
double dfltB[];                                                  /* not allocated */
double dfltA[];                                                  /* not allocated */
double multblF[];                                                /* not allocated */
unsigned char nL[];                                              /* @0x002B6820 */
anon_0_28 *pWork;                                                /* @0x002DE4CC size 0x4 */
long multbl[];                                                   /* @0x002B5EA0 */
anon_1_28 workf[2];                                              /* @0x00712690 size 0x20 */
anon_0_28 work[2];                                               /* @0x007126B0 size 0x20 */

/* functions defined (3) */
long decodeVAG(unsigned char *s, short *d, long p_len);          /* 0x001D03C0-0x001D0864 lines 69-220 */
void setR(void);                                                 /* 0x001D0870-0x001D088C lines 24-26 */
void setL(void);                                                 /* 0x001D0890-0x001D08AC lines 15-17 */

#endif /* DDR_UNIT_src_sound_vxdecode_decode_c_H */
