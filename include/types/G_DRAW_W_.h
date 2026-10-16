/* struct G_DRAW_W_ -- 13 members, size 0xDE8, layout 0cb70e7dc489.
 *
 * One definition, agreed by the 1 unit that declares it: les_play.c (DIE 0x37A2DF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct G_DRAW_W_ *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: les_play.c (DIE 0x37A2DF)
 */
#ifndef DDR_types_G_DRAW_W__H
#define DDR_types_G_DRAW_W__H

struct double_buffer;

#include "types/double_buffer.h"

struct G_DRAW_W_ {   // size 0xDE8
    /* 0x000 */ int buffer_id;                        // 0x4
    /* 0x004 */ // 0x4 bytes padding
    /* 0x008 */ struct double_buffer double_buffer[2];  // 0xC50
    /* 0xC58 */ struct double_buffer *cur_db;         // 0x4
    /* 0xC5C */ struct {   // size 0x8
        /* 0x000 */ short x;                              // 0x2
        /* 0x002 */ short y;                              // 0x2
        /* 0x004 */ short w;                              // 0x2
        /* 0x006 */ short h;                              // 0x2
    } li_rect[32];
    /* 0xD5C */ unsigned int *li_buff[32];            // 0x80
    /* 0xDDC */ signed char clear_flag;               // 0x1
    /* 0xDDD */ signed char cancel_flag;              // 0x1
    /* 0xDDE */ signed char tmp_flag;                 // 0x1
    /* 0xDDF */ signed char tmp_flag2;                // 0x1
    /* 0xDE0 */ unsigned char cur_resolution : 4;     // bits 0..3
    /* 0xDE0 */ unsigned char req_resolution : 4;     // bits 4..7
    /* 0xDE1 */ unsigned char cur_dither : 4;         // bits 0..3
    /* 0xDE1 */ unsigned char req_dither : 4;         // bits 4..7
    /* 0xDE2 */ // 0x6 bytes padding
};

#endif /* DDR_types_G_DRAW_W__H */
