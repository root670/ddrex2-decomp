/* struct _MULTI_WIN_W -- 1 members, size 0x20, layout c228d3cd8894.
 *
 * One definition, agreed by the 1 unit that declares it: multi_window.c (DIE 0xFA544).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _MULTI_WIN_W *`.
 *
 * declared by: multi_window.c (DIE 0xFA544)
 */
#ifndef DDR_types__MULTI_WIN_W_H
#define DDR_types__MULTI_WIN_W_H

struct _CWS_WIN_W;

#include "types/_CWS_WIN_W.h"

struct _MULTI_WIN_W {   // size 0x20
    /* 0x000 */ struct _CWS_WIN_W *pwin[8];           // 0x20
};

#endif /* DDR_types__MULTI_WIN_W_H */
