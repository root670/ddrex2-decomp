/* struct _ddrnet_opponent -- 10 members, size 0x44, layout 97a3bf90e0db.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x70A76).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_opponent *`.
 *
 * declared by: net.c (DIE 0x70A76), net_main.c (DIE 0x7B6AC), net_type.c (DIE 0x82C2F), net_prg.c (DIE 0x863BD), net_game_main.c (DIE 0x9CDC1), net_game_window.c (DIE 0xA6FB2), net_game_opt.c (DIE 0xB4C5F), net_game_match.c (DIE 0xC525F), net_game_list.c (DIE 0xD8761), net_sys_top.c (DIE 0x16034F), net_sys_user.c (DIE 0x167CB7), net_win_search.c (DIE 0x1A6A9B), net_game_vs.c (DIE 0x1CA737), net_sys_lobby.c (DIE 0x1F15B4), net_game_prg.c (DIE 0x2EBFAA), ddrex2_usa_account.c (DIE 0x38C592), ddrex2_usa_connect.c (DIE 0x393AB5), ddrex2_usa_lobby.c (DIE 0x3988B5), ddrex2_usa_util.c (DIE 0x3A0D09), net_auth_main.c (DIE 0x3A82A8)
 */
#ifndef DDR_types__ddrnet_opponent_H
#define DDR_types__ddrnet_opponent_H

struct _ddrnet_opponent {   // size 0x44
    /* 0x000 */ unsigned char rule;                   // 0x1
    /* 0x001 */ unsigned char difficulty_player;      // 0x1
    /* 0x002 */ unsigned char difficulty_opponent;    // 0x1
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ short bgm_id;                         // 0x2
    /* 0x006 */ // 0x2 bytes padding
    /* 0x008 */ unsigned int pid;                     // 0x4
    /* 0x00C */ unsigned char pname[17];              // 0x11
    /* 0x01D */ unsigned char addr[17];               // 0x11
    /* 0x02E */ unsigned short port;                  // 0x2
    /* 0x030 */ unsigned char addr_int[17];           // 0x11
    /* 0x041 */ // 0x1 bytes padding
    /* 0x042 */ unsigned short port_int;              // 0x2
};

#endif /* DDR_types__ddrnet_opponent_H */
