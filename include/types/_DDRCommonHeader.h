/* struct _DDRCommonHeader -- 8 members, size 0x10, layout 49f633cb3eda.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x34EC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _DDRCommonHeader *`.
 *
 * declared by: les.c (DIE 0x34EC), les_play.c (DIE 0x118AD), reconi.c (DIE 0x25628), onimode.c (DIE 0x2E431), recend.c (DIE 0x39F3B), eds_select.c (DIE 0x3CAD4), eds_main.c (DIE 0x48F06), optscr.c (DIE 0x4D0CF), eds_aid.c (DIE 0x57BAA), eds_break.c (DIE 0x5C0E0), eds_record.c (DIE 0x5C8E4), optdoll.c (DIE 0x95F34), dexport.c (DIE 0x97DBC), dinit.c (DIE 0x9CA9C)
 */
#ifndef DDR_types__DDRCommonHeader_H
#define DDR_types__DDRCommonHeader_H

struct _DDRCommonHeader {   // size 0x10
    /* 0x000 */ unsigned char Type;                   // 0x1
    /* 0x001 */ unsigned char Platform;               // 0x1
    /* 0x002 */ unsigned char Hardware;               // 0x1
    /* 0x003 */ unsigned char Version;                // 0x1
    /* 0x004 */ unsigned char Area;                   // 0x1
    /* 0x005 */ signed char tmp;                      // 0x1
    /* 0x006 */ unsigned short title;                 // 0x2
    /* 0x008 */ unsigned int t_info[2];               // 0x8
};

#endif /* DDR_types__DDRCommonHeader_H */
