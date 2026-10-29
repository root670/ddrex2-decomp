/*
 * C:\work2\usaex2\src\network\net_auth\net_auth_main.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 22 functions, code 0x007F98F0-0x007FF568
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
#ifndef DDR_UNIT_src_network_net_auth_net_auth_main_c_H
#define DDR_UNIT_src_network_net_auth_net_auth_main_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_con.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cNetAuth.h"
#include "types/oni_course.h"

/* anonymous types (3) */

/* anon_14_208 -- @anon14, 0x48 bytes, net_auth_main.c (DIE 0x3AB393) */
typedef struct {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02C */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03A */ unsigned short tw;                    // 0x2
    /* 0x03C */ unsigned short th;                    // 0x2
    /* 0x03E */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
} anon_14_208;

/* anon_17_208 -- @anon17, 0x4 bytes, net_auth_main.c (DIE 0x3ADDA2) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_17_208;

/* anon_15_208 -- @anon15, 0x24 bytes, net_auth_main.c (DIE 0x3AD41E) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_17_208 x0;                       // 0x4
    /* 0x004 */ anon_17_208 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01C */ unsigned char r0;                     // 0x1
    /* 0x01D */ unsigned char g0;                     // 0x1
    /* 0x01E */ unsigned char b0;                     // 0x1
    /* 0x01F */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
} anon_15_208;


/* variables (6) */
struct _tag_cNetAuth *pNetAuth;                                  /* @0x002DDE94 size 0x4 */
static unsigned char *reg_uri_table[2];                          /* @0x002DDE98 size 0x8 */
static unsigned char *chg_uri_table[2];                          /* @0x002DDEA0 size 0x8 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
static struct _tag_cNetAuth _pNetAuth;                           /* @0x0080C6C0 size 0x340 */

/* functions referenced (4) */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */
void NetSysMenuInit(struct _NETWORK_W *);                        /* @0x00224D40 */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */

/* functions defined (22) */
static void change_th(void);                                     /* 0x007F98F0-0x007F9A74 lines 3206-3274 */
static int change_main(void);                                    /* 0x007F9A80-0x007F9B74 lines 3163-3203 */
static void register_th(void);                                   /* 0x007F9B80-0x007F9D04 lines 3084-3150 */
static int register_main(void);                                  /* 0x007F9D10-0x007F9E04 lines 3041-3081 */
static int auth_main(void);                                      /* 0x007F9E10-0x007FA3B4 lines 2816-3028 */
static void set_warning_msg(int id, int yesno, int auth_result); /* 0x007FA3C0-0x007FA8E4 lines 2613-2803 */
static void set_msg(int id, int yesno);                          /* 0x007FA8F0-0x007FAA1C lines 2528-2609 */
static int display_at_id_menu(void);                             /* 0x007FAA20-0x007FB0D8 lines 2326-2522 */
static void disp_auth(float bx, float by, float bw, float bh, int alpha, int mode, int type); /* 0x007FB0E0-0x007FB530 lines 2182-2320 */
static void disp_small_frame(int _flag, float _x, float _y, float _w, int _bri, int _alpha, int _pri); /* 0x007FB530-0x007FB820 lines 2103-2173 */
static int display(void);                                        /* 0x007FB820-0x007FBFA0 lines 1897-2096 */
static int load_https(void);                                     /* 0x007FBFA0-0x007FC064 lines 1864-1890 */
static int id_menu(void);                                        /* 0x007FC070-0x007FD6C0 lines 1209-1857 */
static int howto(void);                                          /* 0x007FD6C0-0x007FD80C lines 1087-1132 */
static int logout(void);                                         /* 0x007FD810-0x007FDA80 lines 993-1056 */
static int authenticate(void);                                   /* 0x007FDA80-0x007FE050 lines 829-987 */
static void init_kb(int disp_mode);                              /* 0x007FE050-0x007FE2DC lines 704-776 */
static int input_id(int mode);                                   /* 0x007FE2E0-0x007FE9D4 lines 553-698 */
static int menu(void);                                           /* 0x007FE9E0-0x007FED98 lines 442-523 */
static int init(void);                                           /* 0x007FEDA0-0x007FF01C lines 348-436 */
void NetAuthMain(struct _NETWORK_W *netw);                       /* 0x007FF020-0x007FF560 lines 200-342 */
struct _tag_cNetAuth *NetAuthGetAddr(void);                      /* 0x007FF560-0x007FF568 lines 74-74 */

#endif /* DDR_UNIT_src_network_net_auth_net_auth_main_c_H */
