/* struct _NETWORK_W -- 35 members, size 0x7700, layout 84c04a7b7f9a.
 *
 * One definition, agreed by the 30 units that declare it: net_main.c (DIE 0x77470).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NETWORK_W *`.
 *
 * declared by: net_main.c (DIE 0x77470), net_prg.c (DIE 0x878FF), net_read_data.c (DIE 0x91E94), net_game_main.c (DIE 0x9AED5), net_game_window.c (DIE 0xA3F01), net_game_opt.c (DIE 0xB1E41), net_game_logout.c (DIE 0xBAE1D), net_game_menu.c (DIE 0xBE376), net_game_match.c (DIE 0xC26DA), net_game_data.c (DIE 0xCB280), net_game_prac.c (DIE 0xD1AED), net_game_list.c (DIE 0xD67C4), net_sys_main.c (DIE 0x14B2FE), net_sys_menu.c (DIE 0x154A67), net_sys_new.c (DIE 0x1576C7), net_sys_top.c (DIE 0x15DA5E), net_sys_user.c (DIE 0x16511F), net_sys_rule.c (DIE 0x16D03E), net_sys_connect.c (DIE 0x171735), net_sys_info.c (DIE 0x1747A9), net_sys_logout.c (DIE 0x19C045), net_play_main.c (DIE 0x1BFE8B), net_game_vs.c (DIE 0x1C983C), net_sys_lobby.c (DIE 0x1F0C50), net_game_rc.c (DIE 0x265443), net_game_challenge.c (DIE 0x26AA35), net_auth_main.c (DIE 0x3A3B7A), net_cnf_main.c (DIE 0x3B1F3E), net_dnas_main.c (DIE 0x3BC05D), net_router_main.c (DIE 0x3C159F)
 */
#ifndef DDR_types__NETWORK_W_H
#define DDR_types__NETWORK_W_H

struct _NET_READ_DATA_W;
struct _NSV_DATA;
struct _NSV_PLAYER_LIST;
struct _NSV_USER_FILE_WORK;
struct _net_inter_w;
struct _net_pack_w;
struct _net_pad_w;
struct _net_prg_w;
struct _nsv_rc_table_list_work;
struct _nsv_rc_table_param_work;
struct sceNetcnfifData;

#include "types/_NET_READ_DATA_W.h"
#include "types/_NSV_DATA.h"
#include "types/_NSV_PLAYER_LIST.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/_net_inter_w.h"
#include "types/_net_pack_w.h"
#include "types/_net_pad_w.h"
#include "types/_net_prg_w.h"
#include "types/_nsv_rc_table_list_work.h"
#include "types/_nsv_rc_table_param_work.h"
#include "types/sceNetcnfifData.h"

struct _NETWORK_W {   // size 0x7700
    /* 0x000 */ int counter;                          // 0x4
    /* 0x004 */ unsigned int status;                  // 0x4
    /* 0x008 */ unsigned char *free_data_addr;        // 0x4
    /* 0x00C */ int step;                             // 0x4
    /* 0x010 */ int dc_code;                          // 0x4
    /* 0x014 */ int cursor;                           // 0x4
    /* 0x018 */ void (*NewFunc)();                    // 0x4
    /* 0x01C */ void (*SubFunc)();                    // 0x4
    /* 0x020 */ void (*MainFunc)();                   // 0x4
    /* 0x024 */ void (*OldFunc)();                    // 0x4
    /* 0x028 */ void (*KeyFunc)();                    // 0x4
    /* 0x02C */ void (*OldKeyFunc)();                 // 0x4
    /* 0x030 */ struct _net_pad_w padw;               // 0x10
    /* 0x040 */ struct _NET_READ_DATA_W readw;        // 0x310
    /* 0x350 */ struct _net_prg_w prgw;               // 0xC
    /* 0x35C */ struct _net_inter_w interw;           // 0x4
    /* 0x360 */ int sel_user_file_num;                // 0x4
    /* 0x364 */ struct _NSV_USER_FILE_WORK *dur_user_file;  // 0x4
    /* 0x368 */ struct _NSV_USER_FILE_WORK UserFile[2];  // 0x1DC0
    /* 0x2128 */ struct _NSV_PLAYER_LIST *player_list;  // 0x4
    /* 0x212C */ struct _NSV_DATA ServerData;         // 0x10
    /* 0x213C */ struct _nsv_rc_table_param_work RcData[2];  // 0x100
    /* 0x223C */ struct _nsv_rc_table_list_work RcDataTbl;  // 0x3C04
    /* 0x5E40 */ struct _nsv_rc_table_param_work *dur_rc_data;  // 0x4
    /* 0x5E44 */ int work[320];                       // 0x500
    /* 0x6344 */ char work_set_mode;                  // 0x1
    /* 0x6345 */ // 0x3 bytes padding
    /* 0x6348 */ struct _net_pack_w pack;             // 0x38
    /* 0x6380 */ struct sceNetcnfifData netcnfdata;   // 0x1340
    /* 0x76C0 */ unsigned int *net_cnf_addr;          // 0x4
    /* 0x76C4 */ int net_loaded_flag;                 // 0x4
    /* 0x76C8 */ int upnp_loaded_flag;                // 0x4
    /* 0x76CC */ int bsdsocki_irx_mid;                // 0x4
    /* 0x76D0 */ int bsdsocki_irx_result;             // 0x4
    /* 0x76D4 */ int bsdsocki_irx_flag;               // 0x4
    /* 0x76D8 */ int mc_init_flag;                    // 0x4
    /* 0x76DC */ // 0x24 bytes padding
} __attribute__((aligned(64)));

#endif /* DDR_types__NETWORK_W_H */
