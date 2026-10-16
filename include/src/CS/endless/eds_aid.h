/*
 * C:\work\usam2\src\CS\endless\eds_aid.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x00236160-0x00237C30
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_endless_eds_aid_c_H
#define DDR_UNIT_src_CS_endless_eds_aid_c_H

#include "types/_EDSSYS_W.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cMusicData.h"
#include "types/demo_loop_w.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/play_loop_w.h"
#include "types/play_mode.h"
#include "types/play_w.h"

/* anonymous types (6) */

/* anon_0_24 -- @anon0, 0x8008 bytes, eds_aid.c (DIE 0x526C8) */
union anon_0_24 {   // size 0x8008
    /* 0x000 */ struct demo_loop_w demo_loop_w;       // 0x8008
    /* 0x000 */ struct play_loop_w play_loop_w;       // 0x8008
};

/* anon_1_24 -- @anon1, 0x48 bytes, eds_aid.c (DIE 0x52963) */
struct anon_1_24 {   // size 0x48
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
};

/* anon_2_24 -- @anon2, 0xCC8 bytes, eds_aid.c (DIE 0x52C0B) */
struct anon_2_24 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_3_24 -- @anon3, 0x4 bytes, eds_aid.c (DIE 0x52D06) */
struct anon_3_24 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_5_24 -- @anon5, 0x4 bytes, eds_aid.c (DIE 0x56AF0) */
union anon_5_24 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_4_24 -- @anon4, 0x24 bytes, eds_aid.c (DIE 0x5680B) */
struct anon_4_24 {   // size 0x24
    /* 0x000 */ union anon_5_24 x0;                   // 0x4
    /* 0x004 */ union anon_5_24 y0;                   // 0x4
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
};


/* variables (6) */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xAB544 */
struct _EDSSYS_W *EDSSYSW;                                       /* @0x002A2254 size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
struct music_info minfo_tab[77];                                 /* @0x0027B340 size 0x2DB8 */
struct _tag_cMusicData *msm_new_order_table[128];                /* @0x00589390 size 0x200 */
struct _tag_cMusicData *alphabet_order_table[128];               /* @0x00589590 size 0x200 */

/* functions defined (12) */
void EdsAidPrintFont(int _x, int _y, char *_str, int _color, unsigned char _alpha, int texid); /* 0x00236160-0x00236310 lines 1893-1951 */
void EdsScoreCreate(int _value);                                 /* 0x00236310-0x0023651C lines 1606-1687 */
void EdsNextStageCreate(void);                                   /* 0x00236520-0x00236814 lines 1367-1560 */
void EdsBeforeStageDataSet(void);                                /* 0x00236820-0x002368C0 lines 1310-1344 */
int EdsMOMax(void);                                              /* 0x002368C0-0x00236960 lines 1263-1278 */
int EdsPlayFlag(int _music, unsigned int _mode, unsigned int _bit); /* 0x00236960-0x00236D10 lines 1132-1258 */
struct music_info *EdsGetMipTable(int _num);                     /* 0x00236D10-0x00236DE8 lines 802-837 */
static void EdsInitMipTable(struct _EDSSYS_W *_eds);             /* 0x00236DF0-0x00236FA8 lines 707-778 */
static int EdsGetLevelType(struct _EDSSYS_W *_eds, int num);     /* 0x00236FB0-0x002373F8 lines 609-683 */
void EdsInitOrderFlag(void);                                     /* 0x00237400-0x002376D0 lines 531-584 */
void EdsTrackSorting(int _flag);                                 /* 0x002376D0-0x00237B54 lines 364-510 */
void EdsInitAllMusicMax(int flag);                               /* 0x00237B60-0x00237C30 lines 320-342 */

#endif /* DDR_UNIT_src_CS_endless_eds_aid_c_H */
