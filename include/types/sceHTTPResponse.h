/* struct sceHTTPResponse -- 11 members, size 0x40, layout f6f7b2de2dee.
 *
 * One definition, agreed by the 1 unit that declares it: ddrex2_usa_id.c (DIE 0x395ED0).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceHTTPResponse *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: ddrex2_usa_id.c (DIE 0x395ED0)
 */
#ifndef DDR_types_sceHTTPResponse_H
#define DDR_types_sceHTTPResponse_H

struct sceHTTPHeaderList;

#include "types/sceHTTPHeaderList.h"
#include "types/anon_30540355b260.h"

struct sceHTTPResponse {   // size 0x40
    /* 0x000 */ int http_ver;                         // 0x4
    /* 0x004 */ int http_rev;                         // 0x4
    /* 0x008 */ anon_30540355b260 code;               // 0x2
    /* 0x00A */ // 0x2 bytes padding
    /* 0x00C */ char *reason;                         // 0x4
    /* 0x010 */ int server_prot;                      // 0x4
    /* 0x014 */ struct sceHTTPHeaderList *headers;    // 0x4
    /* 0x018 */ unsigned char *entity;                // 0x4
    /* 0x01C */ // 0x4 bytes padding
    /* 0x020 */ long long length;                     // 0x8
    /* 0x028 */ int interrupted;                      // 0x4
    /* 0x02C */ // 0x4 bytes padding
    /* 0x030 */ long long date;                       // 0x8
    /* 0x038 */ long long content_length;             // 0x8
};

#endif /* DDR_types_sceHTTPResponse_H */
