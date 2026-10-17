/*
 * C:\work2\usaex2\src\common\obj\co_obj.c
 * MW MIPS C Compiler, overlay main; 15 functions, code 0x00230540-0x00230A50
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_common_obj_co_obj_c_H
#define DDR_UNIT_src_common_obj_co_obj_c_H

#include "types/CO_OBJ_W.h"

/* anonymous types (2) */

/* anon_0_99 -- @anon0, 0x10 bytes, co_obj.c (DIE 0x1B933F) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_0_99;

/* anon_1_99 -- @anon1, 0x10 bytes, co_obj.c (DIE 0x1B95EF) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned int obj_id;                  // 0x4
    /* 0x004 */ unsigned int max;                     // 0x4
    /* 0x008 */ struct CO_OBJ_W *top;                 // 0x4
    /* 0x00C */ struct CO_OBJ_W *ow_addr;             // 0x4
} anon_1_99;


/* variables (1) */
anon_1_99 co_obj_man;                                            /* @0x0071EFD0 size 0x10 */

/* functions defined (15) */
void co_obj_all_del(void);                                       /* 0x00230540-0x00230568 lines 342-343 */
unsigned char co_obj_own_step(void *work_p);                     /* 0x00230570-0x00230578 lines 334-334 */
unsigned char co_obj_step(void *ow);                             /* 0x00230580-0x00230588 lines 326-326 */
void co_obj_disp_on_off(void *ow, int on_off);                   /* 0x00230590-0x00230598 lines 321-321 */
void co_obj_step_set(void *ow, int step, void (*init)(void *));  /* 0x002305A0-0x002305CC lines 307-316 */
int co_obj_is_exist(void *chk_ow, int id);                       /* 0x002305D0-0x002305F8 lines 294-303 */
int co_obj_get_id(void *ow);                                     /* 0x00230600-0x00230608 lines 291-291 */
void *co_obj_work_p(void *ow);                                   /* 0x00230610-0x00230618 lines 285-285 */
int co_obj_own_ini_flag(void *work_p);                           /* 0x00230620-0x00230628 lines 279-279 */
int co_obj_ini_flag(void *chk_ow);                               /* 0x00230630-0x00230638 lines 271-271 */
void *co_obj_del(void *del_ow);                                  /* 0x00230640-0x002306C0 lines 243-263 */
void *co_obj_set(anon_0_99 *func, void (*init)(void *), unsigned char pri); /* 0x002306C0-0x00230844 lines 174-237 */
void co_obj_disp(void);                                          /* 0x00230850-0x002308D0 lines 134-149 */
void co_obj_exec(void);                                          /* 0x002308D0-0x002309F0 lines 81-131 */
unsigned int co_obj_init(unsigned char *addr, unsigned int num); /* 0x002309F0-0x00230A50 lines 64-78 */

#endif /* DDR_UNIT_src_common_obj_co_obj_c_H */
