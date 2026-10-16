/* struct sceNetcnfifData -- 40 members, size 0x1340, layout 446056729e36.
 *
 * One definition, agreed by the 31 units that declare it: net_main.c (DIE 0x7B02C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceNetcnfifData *`.
 *
 * declared by: net_main.c (DIE 0x7B02C), net_prg.c (DIE 0x898E4), net_read_data.c (DIE 0x95192), net_game_main.c (DIE 0x9D13C), net_game_window.c (DIE 0xA7255), net_game_opt.c (DIE 0xB4F02), net_game_logout.c (DIE 0xBB4D3), net_game_menu.c (DIE 0xBF821), net_game_match.c (DIE 0xC5502), net_game_data.c (DIE 0xCC856), net_game_prac.c (DIE 0xD28BF), net_game_list.c (DIE 0xD8A04), net_sys_main.c (DIE 0x14DB3E), net_sys_menu.c (DIE 0x153324), net_sys_new.c (DIE 0x158DC9), net_sys_top.c (DIE 0x160EA3), net_sys_user.c (DIE 0x1684ED), net_sys_rule.c (DIE 0x16E6D7), net_sys_connect.c (DIE 0x1722FD), net_sys_info.c (DIE 0x175FFA), net_sys_logout.c (DIE 0x19CBBB), net_play_main.c (DIE 0x1C36DF), net_game_vs.c (DIE 0x1CB1ED), net_sys_lobby.c (DIE 0x1F1857), net_game_rc.c (DIE 0x2669D7), net_game_challenge.c (DIE 0x26CCCD), net_auth_main.c (DIE 0x3A880C), net_cnf_main.c (DIE 0x3B3F37), net_dnas_ave.c (DIE 0x3BA170), net_dnas_main.c (DIE 0x3BC79C), net_router_main.c (DIE 0x3C39DD)
 */
#ifndef DDR_types_sceNetcnfifData_H
#define DDR_types_sceNetcnfifData_H

struct sceNetcnfifData {   // size 0x1340
    /* 0x000 */ char attach_ifc[256];                 // 0x100
    /* 0x100 */ char attach_dev[256];                 // 0x100
    /* 0x200 */ char dhcp_host_name[256];             // 0x100
    /* 0x300 */ char address[256];                    // 0x100
    /* 0x400 */ char netmask[256];                    // 0x100
    /* 0x500 */ char gateway[256];                    // 0x100
    /* 0x600 */ char dns1_address[256];               // 0x100
    /* 0x700 */ char dns2_address[256];               // 0x100
    /* 0x800 */ char phone_numbers1[256];             // 0x100
    /* 0x900 */ char phone_numbers2[256];             // 0x100
    /* 0xA00 */ char phone_numbers3[256];             // 0x100
    /* 0xB00 */ char auth_name[256];                  // 0x100
    /* 0xC00 */ char auth_key[256];                   // 0x100
    /* 0xD00 */ char peer_name[256];                  // 0x100
    /* 0xE00 */ char vendor[256];                     // 0x100
    /* 0xF00 */ char product[256];                    // 0x100
    /* 0x1000 */ char chat_additional[256];           // 0x100
    /* 0x1100 */ char outside_number[256];            // 0x100
    /* 0x1200 */ char outside_delay[256];             // 0x100
    /* 0x1300 */ int ifc_type;                        // 0x4
    /* 0x1304 */ int mtu;                             // 0x4
    /* 0x1308 */ int ifc_idle_timeout;                // 0x4
    /* 0x130C */ int dev_type;                        // 0x4
    /* 0x1310 */ int phy_config;                      // 0x4
    /* 0x1314 */ int dialing_type;                    // 0x4
    /* 0x1318 */ int dev_idle_timeout;                // 0x4
    /* 0x131C */ int p0;                              // 0x4
    /* 0x1320 */ unsigned char dhcp;                  // 0x1
    /* 0x1321 */ unsigned char dns1_nego;             // 0x1
    /* 0x1322 */ unsigned char dns2_nego;             // 0x1
    /* 0x1323 */ unsigned char f_auth;                // 0x1
    /* 0x1324 */ unsigned char auth;                  // 0x1
    /* 0x1325 */ unsigned char pppoe;                 // 0x1
    /* 0x1326 */ unsigned char prc_nego;              // 0x1
    /* 0x1327 */ unsigned char acc_nego;              // 0x1
    /* 0x1328 */ unsigned char accm_nego;             // 0x1
    /* 0x1329 */ unsigned char p1;                    // 0x1
    /* 0x132A */ unsigned char p2;                    // 0x1
    /* 0x132B */ unsigned char p3;                    // 0x1
    /* 0x132C */ int p4[5];                           // 0x14
};

#endif /* DDR_types_sceNetcnfifData_H */
