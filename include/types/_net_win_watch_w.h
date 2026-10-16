/* struct _net_win_watch_w -- 5 members, size 0x14, layout dfdffe2a839a.
 *
 * One definition, agreed by the 1 unit that declares it: net_win_watch.c (DIE 0x1A3866).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _net_win_watch_w *`.
 *
 * declared by: net_win_watch.c (DIE 0x1A3866)
 */
#ifndef DDR_types__net_win_watch_w_H
#define DDR_types__net_win_watch_w_H

struct _net_win_watch_w {   // size 0x14
    /* 0x000 */ unsigned int flag;                    // 0x4
    /* 0x004 */ unsigned int status;                  // 0x4
    /* 0x008 */ float timer_count;                    // 0x4
    /* 0x00C */ int rest_time;                        // 0x4
    /* 0x010 */ char week;                            // 0x1
    /* 0x011 */ // 0x3 bytes padding
};

#endif /* DDR_types__net_win_watch_w_H */
