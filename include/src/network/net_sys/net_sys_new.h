/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_new.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00224FC0-0x00225C58
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_new_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_new_c_H

#include "types/_COM_KEYBOARD_WORK.h"
#include "types/_NETWORK_W.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/g_game_w.h"

/* anonymous types (2) */

/* anon_1_79 -- @anon1, 0x58 bytes, net_sys_new.c (DIE 0x157CE6) */
typedef struct {   // size 0x58
    /* 0x000 */ struct _COM_KEYBOARD_WORK kb;         // 0x38
    /* 0x038 */ int str_cur;                          // 0x4
    /* 0x03C */ int dancer_id;                        // 0x4
    /* 0x040 */ int _x_bit;                           // 0x4
    /* 0x044 */ int _y_bit;                           // 0x4
    /* 0x048 */ int _type;                            // 0x4
    /* 0x04C */ int _flag;                            // 0x4
    /* 0x050 */ unsigned char *tmp_last_data_addr;    // 0x4
    /* 0x054 */ int player_id;                        // 0x4
} anon_1_79;

/* anon_3_79 -- @anon3, 0x90 bytes, net_sys_new.c (DIE 0x158AFC) */
typedef struct {   // size 0x90
    /* 0x000 */ void *loadaddr;                       // 0x4
    /* 0x004 */ int doll_p_counter;                   // 0x4
    /* 0x008 */ unsigned char max;                    // 0x1
    /* 0x009 */ unsigned char fpanel_max;             // 0x1
    /* 0x00A */ unsigned char step;                   // 0x1
    /* 0x00B */ unsigned char dancing;                // 0x1
    /* 0x00C */ unsigned char cur[2];                 // 0x2
    /* 0x00E */ // 0x2 bytes padding
    /* 0x010 */ float fpanel_x[2];                    // 0x8
    /* 0x018 */ float fpanel_y[2];                    // 0x8
    /* 0x020 */ float cx[3];                          // 0xC
    /* 0x02C */ float cy[3];                          // 0xC
    /* 0x038 */ float cz[3];                          // 0xC
    /* 0x044 */ float adj_y[3];                       // 0xC
    /* 0x050 */ float timer;                          // 0x4
    /* 0x054 */ // 0xC bytes padding
    /* 0x060 */ float cam_p[4] __attribute__((aligned(16)));  // 0x10
    /* 0x070 */ float eye_p[4];                       // 0x10
    /* 0x080 */ void *fpanel;                         // 0x4
    /* 0x084 */ // 0xC bytes padding
} anon_3_79;


/* variables (8) */
anon_1_79 *new_w;                                                /* @0x002DDBAC size 0x4 */
int _type;                                                       /* @0x002DE54C size 0x4 */
int _flag;                                                       /* @0x002DE548 size 0x4 */
struct _NSV_USER_FILE_WORK *tmp_user_file;                       /* @0x002DE550 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_3_79 *dw;                                                   /* @0x002DE534 size 0x4 */
int name_num;                                                    /* @0x002DE544 size 0x4 */
static anon_1_79 new_user_w;                                     /* @0x0071EF70 size 0x58 */

/* functions referenced (2) */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetSysUserInit2(struct _NETWORK_W *);                       /* @0x002274A0 */

/* functions defined (4) */
static void NetSysNewInitKeyborad(void);                         /* 0x00224FC0-0x002250A8 lines 535-558 */
static void NetSysNewKey(struct _NETWORK_W *netw);               /* 0x002250B0-0x002254D4 lines 390-458 */
static void NetSysNewMain(struct _NETWORK_W *netw);              /* 0x002254E0-0x00225B60 lines 161-371 */
void NetSysNewInit(struct _NETWORK_W *netw);                     /* 0x00225B60-0x00225C58 lines 112-154 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_new_c_H */
