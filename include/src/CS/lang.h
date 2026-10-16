/*
 * C:\work\usam2\src\CS\lang.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x00242D10-0x00242DB4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lang_c_H
#define DDR_UNIT_src_CS_lang_c_H

/* variables (9) */
static unsigned char *mesLanguageJAPANESE[6];                    /* @0x00287C40 size 0x18 */
static unsigned char *mesLanguageENGLISH[6];                     /* @0x00287C60 size 0x18 */
static unsigned char *mesLanguageFRENCH[6];                      /* @0x00287C80 size 0x18 */
static unsigned char *mesLanguageGERMAN[6];                      /* @0x00287CA0 size 0x18 */
static unsigned char *mesLanguageITALIAN[6];                     /* @0x00287CC0 size 0x18 */
static unsigned char *mesLanguageSPANISH[6];                     /* @0x00287CE0 size 0x18 */
static unsigned char **mesLanguage[6];                           /* @0x00287D00 size 0x18 */
static unsigned char *mesLanguageOK[6];                          /* @0x00287D20 size 0x18 */
static unsigned char *mesLanguageCANCEL[6];                      /* @0x00287D40 size 0x18 */

/* functions defined (3) */
unsigned char *mesGetCancel(int id0);                            /* 0x00242D10-0x00242D38 lines 140-144 */
unsigned char *mesGetOk(int id0);                                /* 0x00242D40-0x00242D68 lines 132-136 */
unsigned char *mesGetLanguage01(int id0, int id1);               /* 0x00242D70-0x00242DB4 lines 118-128 */

#endif /* DDR_UNIT_src_CS_lang_c_H */
