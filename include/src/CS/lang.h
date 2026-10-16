/*
 * C:\work2\usaex2\src\CS\lang.c
 * MW MIPS C Compiler, overlay main; 1 functions, code 0x001C4720-0x001C4764
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lang_c_H
#define DDR_UNIT_src_CS_lang_c_H

/* variables (9) */
static unsigned char *mesLanguageJAPANESE[6];                    /* @0x002B3300 size 0x18 */
static unsigned char *mesLanguageENGLISH[6];                     /* @0x002B3320 size 0x18 */
static unsigned char *mesLanguageFRENCH[6];                      /* @0x002B3340 size 0x18 */
static unsigned char *mesLanguageGERMAN[6];                      /* @0x002B3360 size 0x18 */
static unsigned char *mesLanguageITALIAN[6];                     /* @0x002B3380 size 0x18 */
static unsigned char *mesLanguageSPANISH[6];                     /* @0x002B33A0 size 0x18 */
static unsigned char **mesLanguage[6];                           /* @0x002B33C0 size 0x18 */
static unsigned char *mesLanguageOK[6];                          /* not allocated size 0x18 */
static unsigned char *mesLanguageCANCEL[6];                      /* not allocated size 0x18 */

/* functions defined (1) */
unsigned char *mesGetLanguage01(int id0, int id1);               /* 0x001C4720-0x001C4764 lines 118-128 */

#endif /* DDR_UNIT_src_CS_lang_c_H */
