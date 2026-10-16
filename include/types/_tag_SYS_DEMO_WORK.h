/* struct _tag_SYS_DEMO_WORK -- 17 members, size 0x54, layout ef992d772111.
 *
 * One definition, agreed by the 1 unit that declares it: sys_demo.c (DIE 0x325).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_SYS_DEMO_WORK *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: sys_demo.c (DIE 0x325)
 */
#ifndef DDR_types__tag_SYS_DEMO_WORK_H
#define DDR_types__tag_SYS_DEMO_WORK_H

struct _tag_SYS_DEMO_WORK {   // size 0x54
    /* 0x000 */ int mode;                             // 0x4
    /* 0x004 */ int inactive_flag;                    // 0x4
    /* 0x008 */ int inactive_counter;                 // 0x4
    /* 0x00C */ int gameplay_flag;                    // 0x4
    /* 0x010 */ int gameplay_counter;                 // 0x4
    /* 0x014 */ int end_screen_request;               // 0x4
    /* 0x018 */ int main_loop_break_request;          // 0x4
    /* 0x01C */ struct {   // size 0x24
        /* 0x000 */ unsigned int lsn;                     // 0x4
        /* 0x004 */ unsigned int size;                    // 0x4
        /* 0x008 */ char name[16];                        // 0x10
        /* 0x018 */ unsigned char date[8];                // 0x8
        /* 0x020 */ unsigned int flag;                    // 0x4
    } cdl_file;
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
