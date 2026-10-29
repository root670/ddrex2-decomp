/*
 * C:\work2\ktps2\cd\libstr3.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x001E2EE0-0x001E347C
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
#ifndef DDR_UNIT_libstr3_c_H
#define DDR_UNIT_libstr3_c_H

#include "types/SemaParam.h"
#include "types/ThreadParam.h"
#include "types/_sif_client_data.h"

/* anonymous types (2) */

/* anon_0_38 -- @anon0, 0xC bytes, libstr3.c (DIE 0x5D2AE) */
typedef struct {   // size 0xC
    /* 0x000 */ int Sect;                             // 0x4
    /* 0x004 */ int Size;                             // 0x4
    /* 0x008 */ int Adrs;                             // 0x4
} anon_0_38;

/* anon_1_38 -- @anon1, 0x4 bytes, libstr3.c (DIE 0x5D964) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char trycount;               // 0x1
    /* 0x001 */ unsigned char spindlctrl;             // 0x1
    /* 0x002 */ unsigned char datapattern;            // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
} anon_1_38;


/* variables (16) */
static int SdStr3EeReadUse;                                      /* @0x002DE4D8 size 0x4 */
static int SdStr3EeReadDiv;                                      /* @0x002DDA74 size 0x4 */
static int SdStr3EeReadDivRest;                                  /* @0x002DDA78 size 0x4 */
int SdStr3KtSemaId;                                              /* @0x002DE4E0 size 0x4 */
struct SemaParam SdStr3KtSemaParam;                              /* @0x00712C20 size 0x18 */
int SdStr3EeReadAllow;                                           /* @0x002DE4EC size 0x4 */
int SdStr3SifRes[16];                                            /* @0x00712C40 size 0x40 */
int SdStr3EeReading;                                             /* @0x002DE4E8 size 0x4 */
int SdStr3EeReadStat;                                            /* @0x002DE4F0 size 0x4 */
int SdStr3EeReadBreak;                                           /* @0x002DE4E4 size 0x4 */
struct _sif_client_data sdstr3_sifbd;                            /* @0x00712C80 size 0x28 */
anon_1_38 sdstr3_cdrmode;                                        /* @0x002DE4F8 size 0x4 */
int SdStr3EeReadThId;                                            /* @0x002DE4F4 size 0x4 */
anon_0_38 SdStr3EeRead;                                          /* @0x00712CA8 size 0xC */
void *_gp;                                                       /* @0x002E20F0 size 0x4 */
char ThStackER[4096];                                            /* @0x00712CC0 size 0x1000 */

/* functions defined (7) */
static void sdstr3_ret(void);                                    /* 0x001E2EE0-0x001E2F04 lines 444-448 */
static void sdstr3_eeread_th(void *data);                        /* 0x001E2F10-0x001E3220 lines 256-434 */
int SdStrSetDiv(int div, int divrest);                           /* 0x001E3220-0x001E3230 lines 240-246 */
int SdStriVsync(void);                                           /* 0x001E3230-0x001E328C lines 202-213 */
int SdStrCdSync(int mode);                                       /* 0x001E3290-0x001E3310 lines 162-184 */
int SdStrCdRead(unsigned int lsn, unsigned int sectors, void *buf); /* 0x001E3310-0x001E3370 lines 138-156 */
void SdStrCdInit(void);                                          /* 0x001E3370-0x001E347C lines 89-130 */

#endif /* DDR_UNIT_libstr3_c_H */
