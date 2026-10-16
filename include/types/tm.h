/* struct tm -- 9 members, size 0x24, layout 49a822cd330a.
 *
 * One definition, agreed by the 4 units that declare it: les_play.c (DIE 0x14756).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct tm *`.
 *
 * declared by: les_play.c (DIE 0x14756), onimode.c (DIE 0x2AAF5), sp_ending_d.c (DIE 0x32B94), eds_select.c (DIE 0x3E100)
 */
#ifndef DDR_types_tm_H
#define DDR_types_tm_H

struct tm {   // size 0x24
    /* 0x000 */ int tm_sec;                           // 0x4
    /* 0x004 */ int tm_min;                           // 0x4
    /* 0x008 */ int tm_hour;                          // 0x4
    /* 0x00C */ int tm_mday;                          // 0x4
    /* 0x010 */ int tm_mon;                           // 0x4
    /* 0x014 */ int tm_year;                          // 0x4
    /* 0x018 */ int tm_wday;                          // 0x4
    /* 0x01C */ int tm_yday;                          // 0x4
    /* 0x020 */ int tm_isdst;                         // 0x4
};

#endif /* DDR_types_tm_H */
