/* struct _tag_cNetAuth -- 47 members, size 0x340, layout a4eabed33678.
 *
 * One definition, agreed by the 2 units that declare it: net_prg.c (DIE 0x86FC5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetAuth *`.
 *
 * declared by: net_prg.c (DIE 0x86FC5), net_auth_main.c (DIE 0x3A4D7E)
 */
#ifndef DDR_types__tag_cNetAuth_H
#define DDR_types__tag_cNetAuth_H

struct _COM_KEYBOARD_WORK;
struct _NETWORK_W;
struct _ddrnet;
struct _tag_cCoCursor01;

#include "types/_COM_KEYBOARD_WORK.h"
#include "types/_NETWORK_W.h"
#include "types/_ddrnet.h"
#include "types/_tag_cCoCursor01.h"

struct _tag_cNetAuth {   // size 0x340
    /* 0x000 */ struct _NETWORK_W *ntw;               // 0x4
    /* 0x004 */ int step1;                            // 0x4
    /* 0x008 */ int step2;                            // 0x4
    /* 0x00C */ int next_step1;                       // 0x4
    /* 0x010 */ int counter;                          // 0x4
    /* 0x014 */ int cursor;                           // 0x4
    /* 0x018 */ int msg_id;                           // 0x4
    /* 0x01C */ int warning_msg_id;                   // 0x4
    /* 0x020 */ int display_mode;                     // 0x4
    /* 0x024 */ int alpha[2];                         // 0x8
    /* 0x02C */ int alpha_mode[2];                    // 0x8
    /* 0x034 */ unsigned char auth_name[8][64];       // 0x200
    /* 0x234 */ unsigned char tmp_input_buf[64];      // 0x40
    /* 0x274 */ int input_exit_state;                 // 0x4
    /* 0x278 */ int kb_disp_mode;                     // 0x4
    /* 0x27C */ int kb_x_pos;                         // 0x4
    /* 0x280 */ int kb_y_pos;                         // 0x4
    /* 0x284 */ int kb_i_pos;                         // 0x4
    /* 0x288 */ int kb_counter;                       // 0x4
    /* 0x28C */ struct _COM_KEYBOARD_WORK kb;         // 0x38
    /* 0x2C4 */ int auth_step;                        // 0x4
    /* 0x2C8 */ int auth_result;                      // 0x4
    /* 0x2CC */ int retry_counter;                    // 0x4
    /* 0x2D0 */ int retry_wait_counter;               // 0x4
    /* 0x2D4 */ struct _ddrnet *d2uc;                 // 0x4
    /* 0x2D8 */ int abort_flag;                       // 0x4
    /* 0x2DC */ int id_menu_cursor;                   // 0x4
    /* 0x2E0 */ int id_menu_hist_msg_id;              // 0x4
    /* 0x2E4 */ int id_menu_target_cursor;            // 0x4
    /* 0x2E8 */ int id_menu_input_state;              // 0x4
    /* 0x2EC */ struct _tag_cCoCursor01 id_menu_cursor_work;  // 0xC
    /* 0x2F8 */ int https_loaded_flag;                // 0x4
    /* 0x2FC */ int atng2proc_flag;                   // 0x4
    /* 0x300 */ int https_load_step;                  // 0x4
    /* 0x304 */ int reg_step;                         // 0x4
    /* 0x308 */ int reg_result;                       // 0x4
    /* 0x30C */ int reg_th_result;                    // 0x4
    /* 0x310 */ int reg_uri_table_id;                 // 0x4
    /* 0x314 */ int reg_use_ssl_flag;                 // 0x4
    /* 0x318 */ int chg_step;                         // 0x4
    /* 0x31C */ int chg_result;                       // 0x4
    /* 0x320 */ int chg_th_result;                    // 0x4
    /* 0x324 */ int chg_uri_table_id;                 // 0x4
    /* 0x328 */ int chg_use_ssl_flag;                 // 0x4
    /* 0x32C */ int next_state;                       // 0x4
    /* 0x330 */ int exit_state;                       // 0x4
    /* 0x334 */ struct _tag_cCoCursor01 cursor_work;  // 0xC
};

#endif /* DDR_types__tag_cNetAuth_H */
