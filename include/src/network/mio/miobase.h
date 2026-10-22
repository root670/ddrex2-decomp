/*
 * C:\work2\usaex2\src\network\mio\miobase.c
 * MW MIPS C Compiler, overlay main; 25 functions, code 0x00245D00-0x00246DB8
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
#ifndef DDR_UNIT_src_network_mio_miobase_c_H
#define DDR_UNIT_src_network_mio_miobase_c_H

#include "types/_mio_message.h"
#include "types/_mio_system.h"

/* anonymous types (1) */

/* anon_0_116 -- @anon0, 0x58 bytes, miobase.c (DIE 0x20614E) */
typedef struct {   // size 0x58
    /* 0x000 */ unsigned int state[4];                // 0x10
    /* 0x010 */ unsigned int count[2];                // 0x8
    /* 0x018 */ unsigned char buffer[64];             // 0x40
} anon_0_116;


/* variables (1) */
static char scrambler[4];                                        /* @0x002DDC38 size 0x4 */

/* functions defined (25) */
void mio_crypto_body(struct _mio_system *pmsys, struct _mio_message *msg, int flg); /* 0x00245D00-0x00245EB8 lines 837-870 */
void mio_init_crypto(struct _mio_system *pmsys, unsigned char *key, int keylen); /* 0x00245EC0-0x00245EC8 lines 831-831 */
int mio_check_bp(struct _mio_message *msg);                      /* 0x00245ED0-0x00245F08 lines 790-804 */
int mio_get_vstr(struct _mio_message *msg, char *value, char delim); /* 0x00245F10-0x00245F88 lines 776-785 */
int mio_get_strn(struct _mio_message *msg, char *value, int size); /* 0x00245F90-0x00246010 lines 759-768 */
int mio_get_u32(struct _mio_message *msg, unsigned int *value);  /* 0x00246010-0x002460E8 lines 696-708 */
int mio_get_32(struct _mio_message *msg, int *value);            /* 0x002460F0-0x002461B8 lines 675-686 */
int mio_get_u16(struct _mio_message *msg, unsigned short *value); /* 0x002461C0-0x00246208 lines 657-665 */
int mio_get_16(struct _mio_message *msg, short *value);          /* 0x00246210-0x00246258 lines 644-652 */
int mio_get_u8(struct _mio_message *msg, unsigned char *value);  /* 0x00246260-0x002462A0 lines 632-639 */
int mio_get_8(struct _mio_message *msg, char *value);            /* 0x002462A0-0x002462E0 lines 620-627 */
int mio_set_strn(struct _mio_message *msg, void *value, int size); /* 0x002462E0-0x0024634C lines 592-600 */
int mio_set_u32(struct _mio_message *msg, void *value);          /* 0x00246350-0x002463F8 lines 528-544 */
int mio_set_32(struct _mio_message *msg, void *value);           /* 0x00246400-0x002464A8 lines 507-523 */
int mio_set_u16(struct _mio_message *msg, void *value);          /* 0x002464B0-0x00246508 lines 489-502 */
int mio_set_16(struct _mio_message *msg, void *value);           /* 0x00246510-0x00246568 lines 471-484 */
int mio_set_u8(struct _mio_message *msg, void *value);           /* 0x00246570-0x002465B0 lines 454-465 */
int mio_set_8(struct _mio_message *msg, void *value);            /* 0x002465B0-0x002465F0 lines 438-449 */
void mio_unpack_end(struct _mio_message *msg);                   /* 0x002465F0-0x00246600 lines 429-433 */
void mio_unpack_start(struct _mio_message *msg);                 /* 0x00246600-0x00246610 lines 419-423 */
void mio_pack_end(struct _mio_message *msg);                     /* 0x00246610-0x00246628 lines 408-413 */
void mio_pack_start(struct _mio_message *msg, int mid);          /* 0x00246630-0x00246674 lines 394-402 */
void mio_message_init(struct _mio_message *msg);                 /* 0x00246680-0x002466D0 lines 379-389 */
int mio_write_message(struct _mio_message *msg, int sockfd);     /* 0x002466D0-0x002468D8 lines 272-345 */
int mio_read_message(struct _mio_message *msg, int sockfd);      /* 0x002468E0-0x00246DB8 lines 34-267 */

#endif /* DDR_UNIT_src_network_mio_miobase_c_H */
