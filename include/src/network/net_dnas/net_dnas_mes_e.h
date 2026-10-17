/*
 * C:\work2\usaex2\src\network\net_dnas\net_dnas_mes_e.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x0022F7E0-0x0022F988
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_dnas_net_dnas_mes_e_c_H
#define DDR_UNIT_src_network_net_dnas_net_dnas_mes_e_c_H

#include "types/sceDNAS2Status.h"

/* anonymous types (2) */

/* anon_0_97 -- @anon0, 0x10 bytes, net_dnas_mes_e.c (DIE 0x1AF39B) */
typedef struct {   // size 0x10
    /* 0x000 */ short lo;                             // 0x2
    /* 0x002 */ short hi;                             // 0x2
    /* 0x004 */ unsigned char *header;                // 0x4
    /* 0x008 */ unsigned char *body;                  // 0x4
    /* 0x00C */ unsigned char *footer;                // 0x4
} anon_0_97;

/* anon_1_97 -- @anon1, 0x24 bytes, net_dnas_mes_e.c (DIE 0x1AF4DC) */
typedef struct {   // size 0x24
    /* 0x000 */ short lo;                             // 0x2
    /* 0x002 */ short hi;                             // 0x2
    /* 0x004 */ unsigned char *message[8];            // 0x20
} anon_1_97;


/* variables (10) */
static unsigned char *BASE_TITLE[2];                             /* @0x002DDBB8 size 0x8 */
static unsigned char *NOTICE[3];                                 /* @0x002BE428 size 0xC */
static unsigned char *AUTH_RUN[2];                               /* @0x002DDBC0 size 0x8 */
static unsigned char *AUTH_OK[2];                                /* @0x002DDBC8 size 0x8 */
static unsigned char *AUTH_ERR[2];                               /* @0x002DDBD0 size 0x8 */
static unsigned char *SETUP[2];                                  /* @0x002DDBD8 size 0x8 */
static unsigned char *SETUP_ERR[2];                              /* @0x002DDBE0 size 0x8 */
unsigned char **ndMessageTbl_ENGLISH[7];                         /* @0x002BE440 size 0x1C */
anon_1_97 dnasErrorMsgs[8];                                      /* @0x002BE460 size 0x120 */
anon_1_97 networkErrorMsgs[13];                                  /* @0x002BE580 size 0x1D4 */

/* functions defined (2) */
void ndmesMakeDNASErrorMessage(struct sceDNAS2Status *status, unsigned char *msgBuf); /* 0x0022F7E0-0x0022F950 lines 362-410 */
unsigned char **ndmesGetMessageTable(int id);                    /* 0x0022F950-0x0022F988 lines 93-98 */

#endif /* DDR_UNIT_src_network_net_dnas_net_dnas_mes_e_c_H */
