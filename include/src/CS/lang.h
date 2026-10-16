/*
 * C:\work\usam2\src\CS\lang.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x00242d10-0x00242db4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lang_c_H
#define DDR_UNIT_src_CS_lang_c_H

/* variables (9) */
static unsigned char *mesLanguageJAPANESE[6];                    /* @0x00287c40 size 0x18 */
static unsigned char *mesLanguageENGLISH[6];                     /* @0x00287c60 size 0x18 */
static unsigned char *mesLanguageFRENCH[6];                      /* @0x00287c80 size 0x18 */
static unsigned char *mesLanguageGERMAN[6];                      /* @0x00287ca0 size 0x18 */
static unsigned char *mesLanguageITALIAN[6];                     /* @0x00287cc0 size 0x18 */
static unsigned char *mesLanguageSPANISH[6];                     /* @0x00287ce0 size 0x18 */
static unsigned char **mesLanguage[6];                           /* @0x00287d00 size 0x18 */
static unsigned char *mesLanguageOK[6];                          /* @0x00287d20 size 0x18 */
static unsigned char *mesLanguageCANCEL[6];                      /* @0x00287d40 size 0x18 */

/* functions defined (3) */
unsigned char *mesGetCancel(int id0);                            /* 0x00242d10-0x00242d38 lines 140-144 */
unsigned char *mesGetOk(int id0);                                /* 0x00242d40-0x00242d68 lines 132-136 */
unsigned char *mesGetLanguage01(int id0, int id1);               /* 0x00242d70-0x00242db4 lines 118-128 */

#endif /* DDR_UNIT_src_CS_lang_c_H */
