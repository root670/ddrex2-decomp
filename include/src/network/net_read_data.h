/*
 * C:\work2\usaex2\src\network\net_read_data.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001F5F20-0x001F6770
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_read_data_c_H
#define DDR_UNIT_src_network_net_read_data_c_H

#include "types/_NETWORK_W.h"
#include "types/_tag_cFilepackData.h"
#include "types/g_game_w.h"

/* anonymous types (3) */

/* anon_2_47 -- @anon2, 0x20 bytes, net_read_data.c (DIE 0x9324A) */
typedef struct {   // size 0x20
    /* 0x000 */ unsigned char *data;                  // 0x4
    /* 0x004 */ int dec_top_id;                       // 0x4
    /* 0x008 */ int tcb_top_id;                       // 0x4
    /* 0x00C */ int dec_font_top_id;                  // 0x4
    /* 0x010 */ int font_top_id;                      // 0x4
    /* 0x014 */ int tex_num;                          // 0x4
    /* 0x018 */ int font_num;                         // 0x4
    /* 0x01C */ unsigned int write_addr;              // 0x4
} anon_2_47;

/* anon_5_47 -- @anon5, 0x4 bytes, net_read_data.c (DIE 0x97C8D) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_5_47;

/* anon_6_47 -- @anon6, 0x10 bytes, net_read_data.c (DIE 0x987E5) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_5_47 x0;                         // 0x4
    /* 0x004 */ anon_5_47 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_6_47;


/* variables (2) */
static int nrd_free_tbl[12];                                     /* @0x002B8C40 size 0x30 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (1) */
void DecodeFilepackData_Th(void *);                              /* @0x0016DC50 */

/* functions defined (5) */
static unsigned int NetReadDataDecode(int id, unsigned char *dest_addr); /* 0x001F5F20-0x001F5FE4 lines 366-400 */
int NetReadDataInitFreeDataAddr(struct _NETWORK_W *netw, unsigned int free_addr); /* 0x001F5FF0-0x001F622C lines 257-360 */
int NetReadDataGetStrLFNum(unsigned char *str);                  /* 0x001F6230-0x001F6280 lines 244-252 */
unsigned char *NetReadDataGetStr(int str_num);                   /* 0x001F6280-0x001F6294 lines 226-227 */
int NetReadData(struct _NETWORK_W *netw, int type);              /* 0x001F62A0-0x001F6770 lines 30-221 */

#endif /* DDR_UNIT_src_network_net_read_data_c_H */
