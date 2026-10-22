/* struct _NS_NET_INFO_W -- 27 members, size 0x2C8, layout 994faca83fcd.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x6DADA).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NS_NET_INFO_W *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: net.c (DIE 0x6DADA), net_main.c (DIE 0x78E83), net_type.c (DIE 0x81B4D), net_prg.c (DIE 0x855B5), net_game_main.c (DIE 0x9980F), net_game_window.c (DIE 0xA6931), net_game_opt.c (DIE 0xB41E2), net_game_match.c (DIE 0xC46B6), net_game_list.c (DIE 0xD7D08), net_sys_top.c (DIE 0x15EE4A), net_sys_user.c (DIE 0x1665FA), net_win_search.c (DIE 0x1A5203), net_game_vs.c (DIE 0x1C8AD5), net_sys_lobby.c (DIE 0x1EE5DA), net_game_prg.c (DIE 0x2E8EF7), ddrex2_usa_util.c (DIE 0x39F65E), net_auth_main.c (DIE 0x3A59C9)
 */
#ifndef DDR_types__NS_NET_INFO_W_H
#define DDR_types__NS_NET_INFO_W_H

struct _NS_NET_SOCK_W;
struct _NetP2PRecvW;
struct _NetP2PSendW;
struct _NetUDPRecvWork;
struct _NetUDPSendWork;
struct _ddrnet;

#include "types/_NS_NET_SOCK_W.h"
#include "types/_NetP2PRecvW.h"
#include "types/_NetP2PSendW.h"
#include "types/_NetUDPRecvWork.h"
#include "types/_NetUDPSendWork.h"
#include "types/_ddrnet.h"
#include "types/anon_11313902d7fa.h"

struct _NS_NET_INFO_W {   // size 0x2C8
    /* 0x000 */ unsigned int mode;                    // 0x4
    /* 0x004 */ int def_gw_disc;                      // 0x4
    /* 0x008 */ char domain[256];                     // 0x100
    /* 0x108 */ int dns_addr_pri;                     // 0x4
    /* 0x10C */ int dns_addr_sec;                     // 0x4
    /* 0x110 */ int dhcp_up;                          // 0x4
    /* 0x114 */ anon_11313902d7fa dhcp_property;      // 0x10
    /* 0x124 */ struct _NS_NET_SOCK_W sock[1];        // 0x28
    /* 0x14C */ unsigned int connect_flag;            // 0x4
    /* 0x150 */ int connect_step;                     // 0x4
    /* 0x154 */ int connect_rtn;                      // 0x4
    /* 0x158 */ int connect_s_step;                   // 0x4
    /* 0x15C */ int connect_counter;                  // 0x4
    /* 0x160 */ unsigned short my_udp_port;           // 0x2
    /* 0x162 */ // 0x2 bytes padding
    /* 0x164 */ struct _NetUDPSendWork send;          // 0x40
    /* 0x1A4 */ struct _NetUDPRecvWork recv;          // 0xAC
    /* 0x250 */ struct _NetP2PSendW p2psend;          // 0x24
    /* 0x274 */ struct _NetP2PRecvW p2precv;          // 0x21
    /* 0x295 */ // 0x3 bytes padding
    /* 0x298 */ unsigned int packet_flag;             // 0x4
    /* 0x29C */ struct _ddrnet *d2uc;                 // 0x4
    /* 0x2A0 */ signed char start_status;             // 0x1
    /* 0x2A1 */ // 0x3 bytes padding
    /* 0x2A4 */ int rtn_proc_mes;                     // 0x4
    /* 0x2A8 */ unsigned int frame_timer;             // 0x4
    /* 0x2AC */ int next_server;                      // 0x4
    /* 0x2B0 */ unsigned char gate_ip_addr[16];       // 0x10
    /* 0x2C0 */ int gate_port;                        // 0x4
    /* 0x2C4 */ char sel_gate;                        // 0x1
    /* 0x2C5 */ // 0x3 bytes padding
};

#endif /* DDR_types__NS_NET_INFO_W_H */
