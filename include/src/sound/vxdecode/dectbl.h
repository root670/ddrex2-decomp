/*
 * C:\work2\usaex2\src\sound\vxdecode\dectbl.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_sound_vxdecode_dectbl_c_H
#define DDR_UNIT_src_sound_vxdecode_dectbl_c_H

/* anonymous types (2) */

/* anon_0_29 -- @anon0, 0x10 bytes, dectbl.c (DIE 0x4585C) */
typedef struct {   // size 0x10
    /* 0x000 */ long dH;                              // 0x8
    /* 0x008 */ long dL;                              // 0x8
} anon_0_29;

/* anon_1_29 -- @anon1, 0x10 bytes, dectbl.c (DIE 0x458DD) */
typedef struct {   // size 0x10
    /* 0x000 */ double dH;                            // 0x8
    /* 0x008 */ double dL;                            // 0x8
} anon_1_29;


/* variables (12) */
double dfltA[5];                                                 /* not allocated size 0x28 */
double dfltB[5];                                                 /* not allocated size 0x28 */
long multbl[240];                                                /* @0x002B5EA0 size 0x780 */
double multblF[224];                                             /* not allocated size 0x700 */
unsigned char fr[8];                                             /* not allocated size 0x8 */
unsigned char getSoundDataIndex[224];                            /* not allocated size 0xE0 */
unsigned char *tL[8];                                            /* not allocated size 0x20 */
unsigned char *tH[8];                                            /* not allocated size 0x20 */
anon_1_29 *pWorkf;                                               /* @0x002DE4C8 size 0x4 */
anon_0_29 *pWork;                                                /* @0x002DE4CC size 0x4 */
anon_1_29 workf[2];                                              /* @0x00712690 size 0x20 */
anon_0_29 work[2];                                               /* @0x007126B0 size 0x20 */

#endif /* DDR_UNIT_src_sound_vxdecode_dectbl_c_H */
