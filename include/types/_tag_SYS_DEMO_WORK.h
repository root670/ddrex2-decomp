/* struct _tag_SYS_DEMO_WORK -- 17 members, size 0x54, layout ef992d772111.
 *
 * One definition, agreed by the 1 unit that declares it: sys_demo.c (DIE 0x325).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_SYS_DEMO_WORK *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: sys_demo.c (DIE 0x325)
 */
#ifndef DDR_types__tag_SYS_DEMO_WORK_H
#define DDR_types__tag_SYS_DEMO_WORK_H

#include "types/anon_31c7db27763e.h"

struct _tag_SYS_DEMO_WORK {   // size 0x54
    /* 0x000 */ int mode;                             // 0x4
    /* 0x004 */ int inactive_flag;                    // 0x4
    /* 0x008 */ int inactive_counter;                 // 0x4
    /* 0x00C */ int gameplay_flag;                    // 0x4
    /* 0x010 */ int gameplay_counter;                 // 0x4
    /* 0x014 */ int end_screen_request;               // 0x4
    /* 0x018 */ int main_loop_break_request;          // 0x4
    /* 0x01C */ anon_31c7db27763e cdl_file;           // 0x24
    /* 0x040 */ unsigned short language;              // 0x2
    /* 0x042 */ unsigned short aspect;                // 0x2
    /* 0x044 */ unsigned short playmode;              // 0x2
    /* 0x046 */ unsigned short to_inactive;           // 0x2
    /* 0x048 */ unsigned short to_gameplay;           // 0x2
    /* 0x04A */ unsigned short mediatype;             // 0x2
    /* 0x04C */ unsigned short masterVolScale;        // 0x2
    /* 0x04E */ unsigned short dirSector;             // 0x2
    /* 0x050 */ int why;                              // 0x4
};

#endif /* DDR_types__tag_SYS_DEMO_WORK_H */
