/* struct _NET_WORK_OPT_W -- 9 members, size 0x18, layout 026ae5dea002.
 *
 * One definition, agreed by the 1 unit that declares it: net_game_prg.c (DIE 0x2EA2DF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NET_WORK_OPT_W *`.
 *
 * declared by: net_game_prg.c (DIE 0x2EA2DF)
 */
#ifndef DDR_types__NET_WORK_OPT_W_H
#define DDR_types__NET_WORK_OPT_W_H

struct _NET_WORK_OPT_W {   // size 0x18
    /* 0x000 */ unsigned int bit_flag;                // 0x4
    /* 0x004 */ unsigned int rank_num;                // 0x4
    /* 0x008 */ unsigned short match;                 // 0x2
    /* 0x00A */ unsigned short win;                   // 0x2
    /* 0x00C */ unsigned short lose;                  // 0x2
    /* 0x00E */ unsigned short draw;                  // 0x2
    /* 0x010 */ unsigned short cwin;                  // 0x2
    /* 0x012 */ unsigned short port;                  // 0x2
    /* 0x014 */ signed char dancer;                   // 0x1
    /* 0x015 */ // 0x3 bytes padding
};

#endif /* DDR_types__NET_WORK_OPT_W_H */
