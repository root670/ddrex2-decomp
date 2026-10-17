/*
 * C:\work2\usaex2\src\network\net_dnas\net_dnas_main.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 8 functions, code 0x00804040-0x00805A00
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_dnas_net_dnas_main_c_H
#define DDR_UNIT_src_network_net_dnas_net_dnas_main_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_tag_cNetDnas.h"
#include "types/sceDNAS2Status.h"

/* anonymous types (3) */

/* anon_0_211 -- @anon0, 0x48 bytes, net_dnas_main.c (DIE 0x3BB81A) */
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
} anon_0_211;

/* anon_2_211 -- @anon2, 0x4 bytes, net_dnas_main.c (DIE 0x3BD3B6) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_2_211;

/* anon_1_211 -- @anon1, 0x24 bytes, net_dnas_main.c (DIE 0x3BD056) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_2_211 x0;                        // 0x4
    /* 0x004 */ anon_2_211 y0;                        // 0x4
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
} anon_1_211;


/* variables (4) */
unsigned char pass_phrase[8];                                    /* @0x002DDEB0 size 0x8 */
struct _tag_cNetDnas *pNetDnas;                                  /* @0x002DDEB8 size 0x4 */
static unsigned char *debug_menu_item_str[5];                    /* @0x00806E10 size 0x14 */
static struct _tag_cNetDnas _pNetDnas;                           /* @0x0080D770 size 0x70 */

/* functions referenced (4) */
void dnas_th(void *);                                            /* @0x00804040 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */
void NetSysConnectInit(struct _NETWORK_W *);                     /* @0x002285B0 */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */

/* functions defined (8) */
static void dnas_th(void);                                       /* 0x00804040-0x00804328 lines 1098-1217 */
static int debug_menu(void);                                     /* 0x00804330-0x008048A4 lines 969-1092 */
static void set_warning_msg(int id, struct sceDNAS2Status *status); /* 0x008048B0-0x00804B4C lines 819-960 */
static int fake_dnas_func(void);                                 /* 0x00804B50-0x00804D58 lines 727-813 */
static int dnas_func(void);                                      /* 0x00804D60-0x008051E8 lines 479-668 */
static int dnas_main(void);                                      /* 0x008051F0-0x0080577C lines 261-452 */
static int init(void);                                           /* 0x00805780-0x0080585C lines 189-233 */
void NetDnasMain(struct _NETWORK_W *netw);                       /* 0x00805860-0x00805A00 lines 129-184 */

#endif /* DDR_UNIT_src_network_net_dnas_net_dnas_main_c_H */
