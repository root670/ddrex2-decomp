/*
 * C:\work\usam2\src\CS\endless\eds_select.c
 * MW MIPS C Compiler, overlay main; 16 functions, code 0x0022e6a0-0x002329ac
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_endless_eds_select_c_H
#define DDR_UNIT_src_CS_endless_eds_select_c_H

#include "types/G_SYS_W_.h"
#include "types/_EDSBOX_MAIN.h"
#include "types/_EDSSYS_W.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/demo_loop_w.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/play_loop_w.h"
#include "types/play_mode.h"

/* anonymous types (7) */

/* anon_0_18 -- @anon0, 0x48 bytes, eds_select.c (DIE 0x3d82d) */
struct anon_0_18 {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00c */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02c */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03a */ unsigned short tw;                    // 0x2
    /* 0x03c */ unsigned short th;                    // 0x2
    /* 0x03e */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
};

/* anon_1_18 -- @anon1, 0xcc8 bytes, eds_select.c (DIE 0x3dc8f) */
struct anon_1_18 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_2_18 -- @anon2, 0x4 bytes, eds_select.c (DIE 0x3ddf8) */
struct anon_2_18 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_3_18 -- @anon3, 0xc bytes, eds_select.c (DIE 0x3fd0d) */
struct anon_3_18 {   // size 0xc
    /* 0x000 */ int mode_quit_flg;                    // 0x4
    /* 0x004 */ int state;                            // 0x4
    /* 0x008 */ int renewal_record_flag;              // 0x4
};

/* anon_5_18 -- @anon5, 0x4 bytes, eds_select.c (DIE 0x41cd8) */
union anon_5_18 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_4_18 -- @anon4, 0x24 bytes, eds_select.c (DIE 0x4177c) */
struct anon_4_18 {   // size 0x24
    /* 0x000 */ union anon_5_18 x0;                   // 0x4
    /* 0x004 */ union anon_5_18 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00c */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01c */ unsigned char r0;                     // 0x1
    /* 0x01d */ unsigned char g0;                     // 0x1
    /* 0x01e */ unsigned char b0;                     // 0x1
    /* 0x01f */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};

/* anon_6_18 -- @anon6, 0x8008 bytes, eds_select.c (DIE 0x42311) */
union anon_6_18 {   // size 0x8008
    /* 0x000 */ struct demo_loop_w demo_loop_w;       // 0x8008
    /* 0x000 */ struct play_loop_w play_loop_w;       // 0x8008
};


/* variables (12) */
static int EdsDefaultData[13];                                   /* @0x00282be0 size 0x34 */
static int EdsRegulationOutData[15];                             /* @0x00282c20 size 0x3c */
static int EdStatusMax[15];                                      /* @0x00282c60 size 0x3c */
static int EdsClassNum[15];                                      /* @0x00282ca0 size 0x3c */
struct _EDSSYS_W *EDSSYSW;                                       /* @0x002a2254 size 0x4 */
struct music_info minfo_tab[77];                                 /* @0x0027b340 size 0x2db8 */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xab544 */
struct G_SYS_W_ g_sys_w;                                         /* @0x0063d5a0 size 0x90 */
struct anon_3_18 usr_work;                                       /* @0x002b62a0 size 0xc */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */
char *EdsStrDataTbl[];                                           /* @0x00282ec0 */
struct _EDSBOX_MAIN *EDSBOXM;                                    /* @0x002a2280 size 0x4 */

/* functions referenced (16) */
void EdsMenuInit2(struct _EDSSYS_W *);                           /* @0x00231d40 */
void EdsOrderCommon(struct _EDSSYS_W *);                         /* @0x0022e8b0 */
void EdsOrderInit(struct _EDSSYS_W *);                           /* @0x0022fe10 */
void EdsMainMenuInit(struct _EDSSYS_W *);                        /* @0x00232800 */
void EdsBreakStageInit(struct _EDSSYS_W *);                      /* @0x00237e70 */
void EdsRecordInit(struct _EDSSYS_W *);                          /* @0x002395e0 */
void EdsPlayCommon(struct _EDSSYS_W *);                          /* @0x002301a0 */
void EdsPlayInit(struct _EDSSYS_W *);                            /* @0x002302a0 */
void EdsToOrderTexInit(struct _EDSSYS_W *);                      /* @0x00230190 */
void EdsMenuBlackWait(struct _EDSSYS_W *);                       /* @0x00230d40 */
void EdsMenuCommon(struct _EDSSYS_W *);                          /* @0x00230d90 */
void EdsMenuInit(struct _EDSSYS_W *);                            /* @0x002320e0 */
void EdsToMenuTexInit(struct _EDSSYS_W *);                       /* @0x002324c0 */
void EdsWarningCommon(struct _EDSSYS_W *);                       /* @0x00232610 */
void EdsWarningInit(struct _EDSSYS_W *);                         /* @0x00232740 */
void EdsMainMenuTexture(struct _EDSSYS_W *);                     /* @0x002327a0 */

/* functions defined (16) */
static void EdsSelectPrintDigit(int _x, int _y, unsigned int _dig00, unsigned int _dig01, char _figure, unsigned char _alpha); /* 0x0022e6a0-0x0022e8a8 lines 2577-2615 */
static void EdsOrderCommon(struct _EDSSYS_W *_eds);              /* 0x0022e8b0-0x0022fe04 lines 2085-2469 */
static void EdsOrderInit(struct _EDSSYS_W *_eds);                /* 0x0022fe10-0x00230188 lines 1974-2061 */
static void EdsToOrderTexInit(struct _EDSSYS_W *_eds);           /* 0x00230190-0x002301a0 lines 1949-1950 */
void EdsPlayCommon(struct _EDSSYS_W *_eds);                      /* 0x002301a0-0x00230298 lines 1811-1921 */
static void EdsPlayInit(struct _EDSSYS_W *_eds);                 /* 0x002302a0-0x00230d34 lines 1474-1791 */
static void EdsMenuBlackWait(struct _EDSSYS_W *_eds);            /* 0x00230d40-0x00230d88 lines 1429-1451 */
static void EdsMenuCommon(struct _EDSSYS_W *_eds);               /* 0x00230d90-0x00231d3c lines 756-1422 */
static void EdsMenuInit2(struct _EDSSYS_W *_eds);                /* 0x00231d40-0x002320dc lines 663-733 */
static void EdsMenuInit(struct _EDSSYS_W *_eds);                 /* 0x002320e0-0x002324bc lines 565-642 */
static void EdsToMenuTexInit(struct _EDSSYS_W *_eds);            /* 0x002324c0-0x00232608 lines 506-543 */
static void EdsWarningCommon(struct _EDSSYS_W *_eds);            /* 0x00232610-0x00232740 lines 442-483 */
static void EdsWarningInit(struct _EDSSYS_W *_eds);              /* 0x00232740-0x0023279c lines 404-419 */
static void EdsMainMenuTexture(struct _EDSSYS_W *_eds);          /* 0x002327a0-0x00232800 lines 369-381 */
void EdsMainMenuInit(struct _EDSSYS_W *_eds);                    /* 0x00232800-0x00232834 lines 340-346 */
int EdsSelectMain(struct _EDSSYS_W *_eds);                       /* 0x00232840-0x002329ac lines 212-315 */

#endif /* DDR_UNIT_src_CS_endless_eds_select_c_H */
