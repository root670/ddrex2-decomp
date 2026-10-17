/*
 * C:\work2\usaex2\src\eyetoy\eye_ref.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x001D4D80-0x001D549C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_eyetoy_eye_ref_c_H
#define DDR_UNIT_src_eyetoy_eye_ref_c_H

#include "types/_EYETOY_CHECK_POS_W.h"
#include "types/_EYETOY_CHECK_W.h"
#include "types/_EYETOY_W.h"

/* anonymous types (1) */

/* anon_0_33 -- @anon0, 0x10 bytes, eye_ref.c (DIE 0x514C9) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned int ipu_identifier;          // 0x4
    /* 0x004 */ int bytesize;                         // 0x4
    /* 0x008 */ unsigned short width;                 // 0x2
    /* 0x00A */ unsigned short height;                // 0x2
    /* 0x00C */ unsigned short num_frames;            // 0x2
    /* 0x00E */ unsigned short reserved;              // 0x2
} anon_0_33;


/* variables (1) */
struct _EYETOY_W *EYETOYW;                                       /* @0x002DD9A8 size 0x4 */

/* functions defined (14) */
void EyeRefSetIPUCode(unsigned char *addr);                      /* 0x001D4D80-0x001D4DB0 lines 763-773 */
unsigned int *EyeRefGetPeerBitstreamAddr(int num);               /* 0x001D4DB0-0x001D4DC4 lines 648-649 */
unsigned int *EyeRefGetMyBitstreamAddr(void);                    /* 0x001D4DD0-0x001D4DEC lines 639-641 */
void EyeRefSetPeerBitstreamNum(int num);                         /* 0x001D4DF0-0x001D4DFC lines 632-633 */
int EyeRefGetPeerBitstreamNum(void);                             /* 0x001D4E00-0x001D4E0C lines 625-626 */
int EyeRefChangeMyBitstream(void);                               /* 0x001D4E10-0x001D4E44 lines 615-618 */
void EyeRefSetDefaultMemAddr(unsigned int addr);                 /* 0x001D4E50-0x001D4E74 lines 580-582 */
static void EyeRefGetCircleCheckTotal(void *check_data, struct _EYETOY_CHECK_W *check, struct _EYETOY_CHECK_POS_W *pos); /* 0x001D4E80-0x001D4FD4 lines 343-370 */
int EyeRefGetCircleCheckStrikePDF(int _x, int _y, int _r, int _frame, int _pdf); /* 0x001D4FE0-0x001D508C lines 290-307 */
static void EyeRefGetCheckTotal(void *check_data, struct _EYETOY_CHECK_W *check, struct _EYETOY_CHECK_POS_W *pos); /* 0x001D5090-0x001D5184 lines 250-274 */
int EyeRefGetCheckStrikePDF(int _x, int _y, int _w, int _h, int _frame, int _pdf); /* 0x001D5190-0x001D523C lines 198-216 */
void EyeRefSetOneWindow(short _x, short _y, short _w, short _h); /* 0x001D5240-0x001D5360 lines 90-106 */
void EyeRefSetPositionZ(int _z);                                 /* 0x001D5360-0x001D5388 lines 78-80 */
int EyeRegGetSystemStatus(void);                                 /* 0x001D5390-0x001D549C lines 20-43 */

#endif /* DDR_UNIT_src_eyetoy_eye_ref_c_H */
