/* struct _net_win_tab_w -- 3 members, size 0x20, layout f6eac5c9c87a.
 *
 * One definition, agreed by the 1 unit that declares it: net_win_tab.c (DIE 0x1A177C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _net_win_tab_w *`.
 *
 * declared by: net_win_tab.c (DIE 0x1A177C)
 */
#ifndef DDR_types__net_win_tab_w_H
#define DDR_types__net_win_tab_w_H

struct _net_win_tab_w {   // size 0x20
    /* 0x000 */ int tab_num;                          // 0x4
    /* 0x004 */ unsigned int tab_state[6];            // 0x18
    /* 0x01C */ unsigned int status;                  // 0x4
};

#endif /* DDR_types__net_win_tab_w_H */
