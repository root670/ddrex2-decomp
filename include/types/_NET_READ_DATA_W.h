/* struct _NET_READ_DATA_W -- 8 members, size 0x310, layout 5e59d9ffa1d3.
 *
 * One definition, agreed by the 30 units that declare it: net_main.c (DIE 0x79E7A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NET_READ_DATA_W *`.
 *
 * declared by: net_main.c (DIE 0x79E7A), net_prg.c (DIE 0x866B0), net_read_data.c (DIE 0x94B34), net_game_main.c (DIE 0x9C919), net_game_window.c (DIE 0xA6E4B), net_game_opt.c (DIE 0xB4AD4), net_game_logout.c (DIE 0xBACB6), net_game_menu.c (DIE 0xBF5B8), net_game_match.c (DIE 0xC50F8), net_game_data.c (DIE 0xCC5E8), net_game_prac.c (DIE 0xD267A), net_game_list.c (DIE 0xD85FA), net_sys_main.c (DIE 0x14D4E0), net_sys_menu.c (DIE 0x1530DF), net_sys_new.c (DIE 0x1584E6), net_sys_top.c (DIE 0x1601E8), net_sys_user.c (DIE 0x167B50), net_sys_rule.c (DIE 0x16E492), net_sys_connect.c (DIE 0x1720B8), net_sys_info.c (DIE 0x175DB5), net_sys_logout.c (DIE 0x19C976), net_play_main.c (DIE 0x1C43AE), net_game_vs.c (DIE 0x1CA511), net_sys_lobby.c (DIE 0x1F144D), net_game_rc.c (DIE 0x266792), net_game_challenge.c (DIE 0x26E111), net_auth_main.c (DIE 0x3AA314), net_cnf_main.c (DIE 0x3B2B21), net_dnas_main.c (DIE 0x3BD5FF), net_router_main.c (DIE 0x3C0A48)
 */
#ifndef DDR_types__NET_READ_DATA_W_H
#define DDR_types__NET_READ_DATA_W_H

struct _tag_cFilepackData;

#include "types/_tag_cFilepackData.h"

struct _NET_READ_DATA_W {   // size 0x310
    /* 0x000 */ int read_step;                        // 0x4
    /* 0x004 */ int now_read_data;                    // 0x4
    /* 0x008 */ unsigned int read_flag;               // 0x4
    /* 0x00C */ int free_step;                        // 0x4
    /* 0x010 */ int free_counter;                     // 0x4
    /* 0x014 */ unsigned char *free_addr[12];         // 0x30
    /* 0x044 */ struct _tag_cFilepackData tblFilepack[38];  // 0x130
    /* 0x174 */ unsigned char *font_tbl[103];         // 0x19C
};

#endif /* DDR_types__NET_READ_DATA_W_H */
