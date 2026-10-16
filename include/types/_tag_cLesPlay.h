/* struct _tag_cLesPlay -- 21 members, size 0x54, layout 78da735fffcd.
 *
 * One definition, agreed by the 4 units that declare it: kn_ldisp.c (DIE 0x35C14C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLesPlay *`.
 *
 * declared by: kn_ldisp.c (DIE 0x35C14C), kn_lfunc.c (DIE 0x3641D6), kn_lstep.c (DIE 0x37097C), les_play.c (DIE 0x379089)
 */
#ifndef DDR_types__tag_cLesPlay_H
#define DDR_types__tag_cLesPlay_H

struct _tag_cLesPlay {   // size 0x54
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int start_beat_count;                 // 0x4
    /* 0x00C */ int start_music_count;                // 0x4
    /* 0x010 */ int end_beat_count;                   // 0x4
    /* 0x014 */ int repeat_max;                       // 0x4
    /* 0x018 */ int repeat_num;                       // 0x4
    /* 0x01C */ int demonstration_flag;               // 0x4
    /* 0x020 */ int demonstration_alpha;              // 0x4
    /* 0x024 */ int obi_wipe_mode;                    // 0x4
    /* 0x028 */ int obi_wipe_speed;                   // 0x4
    /* 0x02C */ int pass_flag;                        // 0x4
    /* 0x030 */ int force_exit_flag;                  // 0x4
    /* 0x034 */ int closing_count;                    // 0x4
    /* 0x038 */ int end_count;                        // 0x4
    /* 0x03C */ int s_counter;                        // 0x4
    /* 0x040 */ int p_counter;                        // 0x4
    /* 0x044 */ int p_flag;                           // 0x4
    /* 0x048 */ int status_disp_flag;                 // 0x4
    /* 0x04C */ int hbota_step;                       // 0x4
    /* 0x050 */ int hbota_bright;                     // 0x4
};

#endif /* DDR_types__tag_cLesPlay_H */
