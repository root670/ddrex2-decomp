/* struct _tag_cModeData -- 5 members, size 0x14, layout a19efe20929a.
 *
 * One definition, agreed by the 10 units that declare it: openinglogo.c (DIE 0x3775E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cModeData *`.
 *
 * declared by: openinglogo.c (DIE 0x3775E), infosel.c (DIE 0x32FAA1), info.c (DIE 0x331C3E), infoshow.c (DIE 0x347502), kn_ldisp.c (DIE 0x35BF86), les_aid.c (DIE 0x35EC2F), les.c (DIE 0x36C4BC), les_play.c (DIE 0x378FA3), les_sel_lv.c (DIE 0x37EB96), les_sel_sec.c (DIE 0x384CD2)
 */
#ifndef DDR_types__tag_cModeData_H
#define DDR_types__tag_cModeData_H

struct _tag_cModeData {   // size 0x14
    /* 0x000 */ int (*Init)();                        // 0x4
    /* 0x004 */ int (*Control)();                     // 0x4
    /* 0x008 */ int (*View)();                        // 0x4
    /* 0x00C */ int (*Update)();                      // 0x4
    /* 0x010 */ int level;                            // 0x4
};

#endif /* DDR_types__tag_cModeData_H */
