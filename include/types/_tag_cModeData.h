/* struct _tag_cModeData -- 5 members, size 0x14, layout a19efe20929a.
 *
 * One definition, agreed by the 11 units that declare it: les_sel_lv.c (DIE 0x946).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cModeData *`.
 *
 * declared by: les_sel_lv.c (DIE 0x946), les.c (DIE 0x2DDE), les_sel_sec.c (DIE 0x9BEC), les_play.c (DIE 0xE8ED), kn_ldisp.c (DIE 0x1E56C), reconi.c (DIE 0x228B0), recend.c (DIE 0x38B03), optscr.c (DIE 0x4A2BC), optlang.c (DIE 0x60B56), openinglogo.c (DIE 0x7ACD8), optdoll.c (DIE 0x9425A)
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
