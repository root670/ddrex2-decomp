/* struct sceHTTPParsedURI -- 7 members, size 0x1C, layout 637f9c1e96c5.
 *
 * One definition, agreed by the 1 unit that declares it: ddrex2_usa_id.c (DIE 0x396E60).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceHTTPParsedURI *`.
 *
 * declared by: ddrex2_usa_id.c (DIE 0x396E60)
 */
#ifndef DDR_types_sceHTTPParsedURI_H
#define DDR_types_sceHTTPParsedURI_H

struct sceHTTPParsedURI {   // size 0x1C
    /* 0x000 */ char *scheme;                         // 0x4
    /* 0x004 */ char *username;                       // 0x4
    /* 0x008 */ char *password;                       // 0x4
    /* 0x00C */ char *hostname;                       // 0x4
    /* 0x010 */ int port;                             // 0x4
    /* 0x014 */ char *filename;                       // 0x4
    /* 0x018 */ char *search;                         // 0x4
};

#endif /* DDR_types_sceHTTPParsedURI_H */
