/* struct _tag_cLesSelLevelCursor -- 17 members, size 0xA0, layout dfb9bf6f6651.
 *
 * One definition, agreed by the 1 unit that declares it: les_sel_lv.c (DIE 0x400).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLesSelLevelCursor *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: les_sel_lv.c (DIE 0x400)
 */
#ifndef DDR_types__tag_cLesSelLevelCursor_H
#define DDR_types__tag_cLesSelLevelCursor_H

struct _tag_cLesSelLevelCursor {   // size 0xA0
    /* 0x000 */ int pmode;                            // 0x4
    /* 0x004 */ int pcount;                           // 0x4
    /* 0x008 */ int pcounter;                         // 0x4
    /* 0x00C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x010 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } pos;
    /* 0x020 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } npos;
    /* 0x030 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } ipos;
    /* 0x040 */ int amode;                            // 0x4
    /* 0x044 */ int acount;                           // 0x4
    /* 0x048 */ int acounter;                         // 0x4
    /* 0x04C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x050 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } angle;
    /* 0x060 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } nangle;
    /* 0x070 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } iangle;
    /* 0x080 */ int step;                             // 0x4
    /* 0x084 */ int can_select;                       // 0x4
    /* 0x088 */ int bright;                           // 0x4
    /* 0x08C */ int alpha;                            // 0x4
    /* 0x090 */ int pri;                              // 0x4
    /* 0x094 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
};

#endif /* DDR_types__tag_cLesSelLevelCursor_H */
