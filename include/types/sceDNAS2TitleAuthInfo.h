/* struct sceDNAS2TitleAuthInfo -- 3 members, size 0x14, layout 7f3b2e4fb705.
 *
 * One definition, agreed by the 1 unit that declares it: net_dnas_main.c (DIE 0x3BD559).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceDNAS2TitleAuthInfo *`.
 *
 * declared by: net_dnas_main.c (DIE 0x3BD559)
 */
#ifndef DDR_types_sceDNAS2TitleAuthInfo_H
#define DDR_types_sceDNAS2TitleAuthInfo_H

struct sceDNAS2Data;

#include "types/sceDNAS2Data.h"

struct sceDNAS2TitleAuthInfo {   // size 0x14
    /* 0x000 */ int line_type;                        // 0x4
    /* 0x004 */ struct sceDNAS2Data pass_phrase;      // 0x8
    /* 0x00C */ struct sceDNAS2Data auth_data;        // 0x8
};

#endif /* DDR_types_sceDNAS2TitleAuthInfo_H */
