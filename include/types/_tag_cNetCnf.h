/* struct _tag_cNetCnf -- 28 members, size 0x9100, layout d377951d72e1.
 *
 * One definition, agreed by the 1 unit that declares it: net_cnf_main.c (DIE 0x3B3829).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetCnf *`.
 *
 * declared by: net_cnf_main.c (DIE 0x3B3829)
 */
#ifndef DDR_types__tag_cNetCnf_H
#define DDR_types__tag_cNetCnf_H

struct _NETWORK_W;
struct _tag_cCoCursor01;
struct sceNetcnfifData;
struct sceNetcnfifList;

#include "types/_NETWORK_W.h"
#include "types/_tag_cCoCursor01.h"
#include "types/sceNetcnfifData.h"
#include "types/sceNetcnfifList.h"

struct _tag_cNetCnf {   // size 0x9100
    /* 0x000 */ struct _NETWORK_W *ntw;               // 0x4
    /* 0x004 */ int counter;                          // 0x4
    /* 0x008 */ int crepeat[2];                       // 0x8
    /* 0x010 */ int step;                             // 0x4
    /* 0x014 */ int msg_id;                           // 0x4
    /* 0x018 */ int list_cursor;                      // 0x4
    /* 0x01C */ int list_disp_flag;                   // 0x4
    /* 0x020 */ int warning_msg_id;                   // 0x4
    /* 0x024 */ int next_state;                       // 0x4
    /* 0x028 */ int alpha[2];                         // 0x8
    /* 0x030 */ int alpha_mode[2];                    // 0x8
    /* 0x038 */ int exit_state;                       // 0x4
    /* 0x03C */ int mc_get_info_type;                 // 0x4
    /* 0x040 */ int mc_get_info_format;               // 0x4
    /* 0x044 */ int mc_get_info_result;               // 0x4
    /* 0x048 */ int mc_get_dir_result;                // 0x4
    /* 0x04C */ int net_num;                          // 0x4
    /* 0x050 */ // 0x30 bytes not in DWARF (a member CodeWarrior did not describe)
    /* 0x080 */ struct sceNetcnfifList net_list[6];   // 0xD80
    /* 0xE00 */ int ifc_num;                          // 0x4
    /* 0xE04 */ // 0x3C bytes not in DWARF (a member CodeWarrior did not describe)
    /* 0xE40 */ struct sceNetcnfifList ifc_list[4];   // 0x900
    /* 0x1740 */ struct sceNetcnfifData net_entry[6];  // 0x7380
    /* 0x8AC0 */ int ret_net_load_entry[6];           // 0x18
    /* 0x8AD8 */ int net_entry_loaded_num;            // 0x4
    /* 0x8ADC */ int net_load_entry_result;           // 0x4
    /* 0x8AE0 */ int load_entry_error_level;          // 0x4
    /* 0x8AE4 */ unsigned char net_ifc_name[6][256];  // 0x600
    /* 0x90E4 */ struct _tag_cCoCursor01 cursor_work;  // 0xC
    /* 0x90F0 */ int hcounter;                        // 0x4
    /* 0x90F4 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
};

#endif /* DDR_types__tag_cNetCnf_H */
