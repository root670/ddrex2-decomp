/* struct _net_win_search_w -- 7 members, size 0x34, layout 1e87d5f205d0.
 *
 * One definition, agreed by the 1 unit that declares it: net_win_search.c (DIE 0x1A5FE4).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _net_win_search_w *`.
 *
 * declared by: net_win_search.c (DIE 0x1A5FE4)
 */
#ifndef DDR_types__net_win_search_w_H
#define DDR_types__net_win_search_w_H

struct _net_win_search_w {   // size 0x34
    /* 0x000 */ float gule_x[4];                      // 0x10
    /* 0x010 */ float gule_y[4];                      // 0x10
    /* 0x020 */ float rot_speed;                      // 0x4
    /* 0x024 */ int change_count;                     // 0x4
    /* 0x028 */ unsigned int status;                  // 0x4
    /* 0x02C */ int ic_anime;                         // 0x4
    /* 0x030 */ char *type;                           // 0x4
};

#endif /* DDR_types__net_win_search_w_H */
