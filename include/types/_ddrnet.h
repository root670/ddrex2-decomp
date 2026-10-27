/* struct _ddrnet -- 36 members, size 0x2B5C0, layout 104805d050ab.
 *
 * One definition, agreed by the 19 units that declare it: net.c (DIE 0x6DF25).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet *`.
 *
 * declared by: net.c (DIE 0x6DF25), net_main.c (DIE 0x7621E), net_type.c (DIE 0x80DF8), net_prg.c (DIE 0x8A9D9), net_game_main.c (DIE 0xA2147), net_game_window.c (DIE 0xA4EC7), net_game_opt.c (DIE 0xB2E0F), net_game_match.c (DIE 0xC6B66), net_game_list.c (DIE 0xD61E5), net_sys_top.c (DIE 0x160514), net_sys_user.c (DIE 0x167EA0), net_win_search.c (DIE 0x1A96F3), net_game_vs.c (DIE 0x1CAC5A), net_sys_lobby.c (DIE 0x1EFB18), net_game_prg.c (DIE 0x2EAE37), ddrex2_usa_account.c (DIE 0x38C963), ddrex2_usa_connect.c (DIE 0x3924D5), ddrex2_usa_util.c (DIE 0x39E239), net_auth_main.c (DIE 0x3A414D)
 */
#ifndef DDR_types__ddrnet_H
#define DDR_types__ddrnet_H

struct _ddrnet_blocklist;
struct _ddrnet_conmgr;
struct _ddrnet_infolist;
struct _ddrnet_opponent;
struct _ddrnet_playerdata;
struct _ddrnet_playerdata_h2h;
struct _ddrnet_playerdata_pointrank;
struct _ddrnet_playerdata_rankchallenge;
struct _ddrnet_playerlistinblock;
struct _ddrnet_playerselectlist;
struct _ddrnet_ranking_column;
struct _ddrnet_roomlist;
struct _ddrnet_rule_mask;
struct _ddrnet_svrlist;
struct _mio_message;
struct _mio_system;
struct ddrnet_rc_info;

#include "types/_ddrnet_blocklist.h"
#include "types/_ddrnet_conmgr.h"
#include "types/_ddrnet_infolist.h"
#include "types/_ddrnet_opponent.h"
#include "types/_ddrnet_playerdata.h"
#include "types/_ddrnet_playerdata_h2h.h"
#include "types/_ddrnet_playerdata_pointrank.h"
#include "types/_ddrnet_playerdata_rankchallenge.h"
#include "types/_ddrnet_playerlistinblock.h"
#include "types/_ddrnet_playerselectlist.h"
#include "types/_ddrnet_ranking_column.h"
#include "types/_ddrnet_roomlist.h"
#include "types/_ddrnet_rule_mask.h"
#include "types/_ddrnet_svrlist.h"
#include "types/_mio_message.h"
#include "types/_mio_system.h"
#include "types/ddrnet_rc_info.h"

struct _ddrnet {   // size 0x2B5C0
    /* 0x000 */ struct _ddrnet_conmgr conmgr;         // 0x100
    /* 0x100 */ struct _ddrnet_svrlist svrlist;       // 0x2584
    /* 0x2684 */ unsigned int svrtime;                // 0x4
    /* 0x2688 */ struct _mio_system msys;             // 0x1050
    /* 0x36D8 */ // 0x28 bytes padding
    /* 0x3700 */ struct _mio_message msg[4] __attribute__((aligned(64)));  // 0x1200
    /* 0x4900 */ int mresult;                         // 0x4
    /* 0x4904 */ int login_border;                    // 0x4
    /* 0x4908 */ struct _ddrnet_infolist infolist;    // 0x46CC
    /* 0x8FD4 */ unsigned char use_pindex;            // 0x1
    /* 0x8FD5 */ // 0x3 bytes padding
    /* 0x8FD8 */ unsigned int use_pid;                // 0x4
    /* 0x8FDC */ struct _ddrnet_playerselectlist plsellist;  // 0x60
    /* 0x903C */ struct _ddrnet_playerdata pldata;    // 0x90
    /* 0x90CC */ int count_h2h;                       // 0x4
    /* 0x90D0 */ struct _ddrnet_playerdata_h2h pldata_h2h[60];  // 0x2D0
    /* 0x93A0 */ int count_point;                     // 0x4
    /* 0x93A4 */ struct _ddrnet_playerdata_pointrank pldata_point[60];  // 0x1E0
    /* 0x9584 */ int count_rc;                        // 0x4
    /* 0x9588 */ struct _ddrnet_playerdata_rankchallenge pldata_rc[120];  // 0x780
    /* 0x9D08 */ struct _ddrnet_blocklist blocklist;  // 0x18
    /* 0x9D20 */ struct _ddrnet_playerlistinblock pllistinblock;  // 0x13884
    /* 0x1D5A4 */ struct _ddrnet_playerdata select_pldata;  // 0x90
    /* 0x1D634 */ struct _ddrnet_roomlist roomlist;   // 0xCB24
    /* 0x2A158 */ struct _ddrnet_opponent opp;        // 0x44
    /* 0x2A19C */ signed char room_status;            // 0x1
    /* 0x2A19D */ unsigned char match_stats;          // 0x1
    /* 0x2A19E */ struct _ddrnet_rule_mask rule_mask;  // 0x3
    /* 0x2A1A1 */ signed char rc_trycnt[2];           // 0x2
    /* 0x2A1A3 */ unsigned char rc_cur_week;          // 0x1
    /* 0x2A1A4 */ unsigned char rc_id_num;            // 0x1
    /* 0x2A1A5 */ // 0x3 bytes padding
    /* 0x2A1A8 */ unsigned int rc_cur_time;           // 0x4
    /* 0x2A1AC */ unsigned int rc_term;               // 0x4
    /* 0x2A1B0 */ struct ddrnet_rc_info rc_info;      // 0x8C
    /* 0x2A23C */ unsigned char rc_id[120];           // 0x78
    /* 0x2A2B4 */ int count_ranking;                  // 0x4
    /* 0x2A2B8 */ struct _ddrnet_ranking_column ranking[100];  // 0x12C0
    /* 0x2B578 */ unsigned char ploption[33];         // 0x21
    /* 0x2B599 */ // 0x27 bytes padding
};

#endif /* DDR_types__ddrnet_H */
