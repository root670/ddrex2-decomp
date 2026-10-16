/* struct _nsv_ranking_rc_param_w -- 8 members, size 0x30, layout 7519396636c3.
 *
 * One definition, agreed by the 1 unit that declares it: net_prg.c (DIE 0x8683B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_ranking_rc_param_w *`.
 *
 * declared by: net_prg.c (DIE 0x8683B)
 */
#ifndef DDR_types__nsv_ranking_rc_param_w_H
#define DDR_types__nsv_ranking_rc_param_w_H

struct _nsv_ranking_rc_param_w {   // size 0x30
    /* 0x000 */ unsigned int pid;                     // 0x4
    /* 0x004 */ unsigned char name[20];               // 0x14
    /* 0x018 */ short dancer_number;                  // 0x2
    /* 0x01A */ // 0x2 bytes padding
    /* 0x01C */ unsigned int rank;                    // 0x4
    /* 0x020 */ unsigned int gauge;                   // 0x4
    /* 0x024 */ unsigned int combo;                   // 0x4
    /* 0x028 */ unsigned int time;                    // 0x4
    /* 0x02C */ unsigned int score;                   // 0x4
};

#endif /* DDR_types__nsv_ranking_rc_param_w_H */
