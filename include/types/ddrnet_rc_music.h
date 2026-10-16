/* struct ddrnet_rc_music -- 11 members, size 0xC, layout d27de25efbb7.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x6EA19).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct ddrnet_rc_music *`.
 *
 * declared by: net.c (DIE 0x6EA19), net_main.c (DIE 0x77A43), net_type.c (DIE 0x816FA), net_prg.c (DIE 0x8C05E), net_game_main.c (DIE 0xA35D7), net_game_window.c (DIE 0xAAECE), net_game_opt.c (DIE 0xB8B66), net_game_match.c (DIE 0xC9500), net_game_list.c (DIE 0xDC48E), net_sys_top.c (DIE 0x164648), net_sys_user.c (DIE 0x16BEE3), net_win_search.c (DIE 0x1AA061), net_game_vs.c (DIE 0x1D0F90), net_sys_lobby.c (DIE 0x1F52CC), net_game_prg.c (DIE 0x2EFDA0), ddrex2_usa_account.c (DIE 0x38DD03), ddrex2_usa_challenge.c (DIE 0x38F59D), ddrex2_usa_connect.c (DIE 0x392A8E), ddrex2_usa_util.c (DIE 0x39EFED), net_auth_main.c (DIE 0x3ADBA3)
 */
#ifndef DDR_types_ddrnet_rc_music_H
#define DDR_types_ddrnet_rc_music_H

struct ddrnet_rc_music {   // size 0xC
    /* 0x000 */ unsigned char level;                  // 0x1
    /* 0x001 */ unsigned char speed;                  // 0x1
    /* 0x002 */ unsigned char boost;                  // 0x1
    /* 0x003 */ unsigned char appearance;             // 0x1
    /* 0x004 */ unsigned char turn;                   // 0x1
    /* 0x005 */ unsigned char scroll;                 // 0x1
    /* 0x006 */ unsigned char freeze_arrow;           // 0x1
    /* 0x007 */ unsigned char little;                 // 0x1
    /* 0x008 */ unsigned char dark;                   // 0x1
    /* 0x009 */ unsigned char simultaneous;           // 0x1
    /* 0x00A */ short bgm_id;                         // 0x2
};

#endif /* DDR_types_ddrnet_rc_music_H */
