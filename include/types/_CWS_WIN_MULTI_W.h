/* struct _CWS_WIN_MULTI_W -- 9 members, size 0x24, layout d9e51953f467.
 *
 * One definition, agreed by the 1 unit that declares it: cws_win_multi.c (DIE 0xF7F6C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _CWS_WIN_MULTI_W *`.
 *
 * declared by: cws_win_multi.c (DIE 0xF7F6C)
 */
#ifndef DDR_types__CWS_WIN_MULTI_W_H
#define DDR_types__CWS_WIN_MULTI_W_H

struct _CWS_WIN_MULTI_W {   // size 0x24
    /* 0x000 */ int anime_time;                       // 0x4
    /* 0x004 */ int move_timer;                       // 0x4
    /* 0x008 */ int caution_mark;                     // 0x4
    /* 0x00C */ int line_w;                           // 0x4
    /* 0x010 */ int line_alpha;                       // 0x4
    /* 0x014 */ int font_alpha;                       // 0x4
    /* 0x018 */ int font_blur_x;                      // 0x4
    /* 0x01C */ int win_clut;                         // 0x4
    /* 0x020 */ unsigned int flag;                    // 0x4
};

#endif /* DDR_types__CWS_WIN_MULTI_W_H */
