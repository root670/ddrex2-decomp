/* struct _tag_cOlData -- 9 members, size 0x68, layout 7c834054657c.
 *
 * One definition, agreed by the 1 unit that declares it: olmain.c (DIE 0x543C5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOlData *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: olmain.c (DIE 0x543C5)
 */
#ifndef DDR_types__tag_cOlData_H
#define DDR_types__tag_cOlData_H

struct _tag_cOlData {   // size 0x68
    /* 0x000 */ unsigned int prog_addr;               // 0x4
    /* 0x004 */ unsigned char *prog_file;             // 0x4
    /* 0x008 */ struct {   // size 0x24
        /* 0x000 */ unsigned int lsn;                     // 0x4
        /* 0x004 */ unsigned int size;                    // 0x4
        /* 0x008 */ char name[16];                        // 0x10
        /* 0x018 */ unsigned char date[8];                // 0x8
        /* 0x020 */ unsigned int flag;                    // 0x4
    } fp;
    /* 0x02C */ // 0x4 bytes padding
    /* 0x030 */ struct {   // size 0x8
        /* 0x000 */ unsigned long number : 16;            // bits 0..15
        /* 0x000 */ unsigned long sector : 24;            // bits 16..39
        /* 0x000 */ unsigned long size : 24;              // bits 40..63
    } prog_pos;
    /* 0x038 */ unsigned int data_addr;               // 0x4
    /* 0x03C */ void *data_file[7];                   // 0x1C
    /* 0x058 */ void (*init_func)();                  // 0x4
    /* 0x05C */ int (*main_func)();                   // 0x4
    /* 0x060 */ void (*term_func)();                  // 0x4
    /* 0x064 */ // 0x4 bytes padding
};

#endif /* DDR_types__tag_cOlData_H */
