/* struct _tag_OptDoll -- 17 members, size 0x2C, layout 8e3b5d5db21d.
 *
 * One definition, agreed by the 1 unit that declares it: optdoll.c (DIE 0x9364E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_OptDoll *`.
 *
 * declared by: optdoll.c (DIE 0x9364E)
 */
#ifndef DDR_types__tag_OptDoll_H
#define DDR_types__tag_OptDoll_H

struct _tag_OptDoll {   // size 0x2C
    /* 0x000 */ void *loadaddr;                       // 0x4
    /* 0x004 */ int p_counter;                        // 0x4
    /* 0x008 */ int timer;                            // 0x4
    /* 0x00C */ short dstep;                          // 0x2
    /* 0x00E */ short new_chr;                        // 0x2
    /* 0x010 */ short cur_chr;                        // 0x2
    /* 0x012 */ short sel_id[3];                      // 0x6
    /* 0x018 */ int uratimer;                         // 0x4
    /* 0x01C */ int upcounter;                        // 0x4
    /* 0x020 */ short uchrid;                         // 0x2
    /* 0x022 */ char loading;                         // 0x1
    /* 0x023 */ char uramode;                         // 0x1
    /* 0x024 */ char ustep;                           // 0x1
    /* 0x025 */ char umotid;                          // 0x1
    /* 0x026 */ char uautoplay;                       // 0x1
    /* 0x027 */ char utoon;                           // 0x1
    /* 0x028 */ char ufloor;                          // 0x1
    /* 0x029 */ // 0x3 bytes padding
};

#endif /* DDR_types__tag_OptDoll_H */
