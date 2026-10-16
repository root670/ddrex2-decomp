/* struct _EDSBOXPOINT_W -- 7 members, size 0x10, layout 0425eb3b2686.
 *
 * One definition, agreed by the 3 units that declare it: eds_select.c (DIE 0x4146A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSBOXPOINT_W *`.
 *
 * declared by: eds_select.c (DIE 0x4146A), eds_record.c (DIE 0x5E831), eds_box.c (DIE 0x62CDD)
 */
#ifndef DDR_types__EDSBOXPOINT_W_H
#define DDR_types__EDSBOXPOINT_W_H

struct _EDSBOXPOINT_W {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned char r;                      // 0x1
    /* 0x00D */ unsigned char g;                      // 0x1
    /* 0x00E */ unsigned char b;                      // 0x1
    /* 0x00F */ unsigned char a;                      // 0x1
};

#endif /* DDR_types__EDSBOXPOINT_W_H */
