/* struct _tag_cNetDnas -- 22 members, size 0x70, layout d02119b819ad.
 *
 * One definition, agreed by the 1 unit that declares it: net_dnas_main.c (DIE 0x3BE555).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetDnas *`.
 *
 * declared by: net_dnas_main.c (DIE 0x3BE555)
 */
#ifndef DDR_types__tag_cNetDnas_H
#define DDR_types__tag_cNetDnas_H

struct _NETWORK_W;
struct sceDNAS2Status;

#include "types/_NETWORK_W.h"
#include "types/sceDNAS2Status.h"

struct _tag_cNetDnas {   // size 0x70
    /* 0x000 */ struct _NETWORK_W *ntw;               // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step2;                            // 0x4
    /* 0x00C */ int next_step;                        // 0x4
    /* 0x010 */ int counter;                          // 0x4
    /* 0x014 */ int cursor;                           // 0x4
    /* 0x018 */ int logo_disp_flag;                   // 0x4
    /* 0x01C */ int dnas_server_debug_flag;           // 0x4
    /* 0x020 */ int close_open_flag;                  // 0x4
    /* 0x024 */ int setup_flag;                       // 0x4
    /* 0x028 */ int setup_err_flag;                   // 0x4
    /* 0x02C */ int dnas_start_flag;                  // 0x4
    /* 0x030 */ int auth_mode;                        // 0x4
    /* 0x034 */ int overlay_loaded_flag;              // 0x4
    /* 0x038 */ int logo_tex_id;                      // 0x4
    /* 0x03C */ int atng2proc_flag;                   // 0x4
    /* 0x040 */ int msg_id;                           // 0x4
    /* 0x044 */ int warning_msg_id;                   // 0x4
    /* 0x048 */ int next_state;                       // 0x4
    /* 0x04C */ int exit_state;                       // 0x4
    /* 0x050 */ struct sceDNAS2Status status;         // 0x10
    /* 0x060 */ struct sceDNAS2Status debug_status;   // 0x10
};

#endif /* DDR_types__tag_cNetDnas_H */
