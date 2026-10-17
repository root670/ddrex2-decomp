/*
 * C:\work2\usaex2\src\CS\freeplay\fp_hand.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x00242940-0x00244584
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_freeplay_fp_hand_c_H
#define DDR_UNIT_src_CS_freeplay_fp_hand_c_H

#include "types/_EYETOY_W.h"
#include "types/g_game_w.h"
#include "types/sq_footstep_header.h"
#include "types/sq_header.h"
#include "types/sq_indicator.h"
#include "types/sq_standard.h"
#include "types/tex_bind.h"

/* anonymous types (10) */

/* anon_3_113 -- @anon3, 0xC bytes, fp_hand.c (DIE 0x1FE9A0) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char note[6];                // 0x6
    /* 0x006 */ unsigned char just;                   // 0x1
    /* 0x007 */ unsigned char exist;                  // 0x1
    /* 0x008 */ int bct;                              // 0x4
} anon_3_113;

/* anon_1_113 -- @anon1, 0x2C bytes, fp_hand.c (DIE 0x1FE6A5) */
typedef struct {   // size 0x2C
    /* 0x000 */ anon_3_113 *temp_w;                   // 0x4
    /* 0x004 */ int last_bct;                         // 0x4
    /* 0x008 */ int rand_seed;                        // 0x4
    /* 0x00C */ int level;                            // 0x4
    /* 0x010 */ int kind_id;                          // 0x4
    /* 0x014 */ int beg_exist;                        // 0x4
    /* 0x018 */ unsigned char *org_addr;              // 0x4
    /* 0x01C */ unsigned char *dst_addr;              // 0x4
    /* 0x020 */ struct sq_standard *beg_note;         // 0x4
    /* 0x024 */ struct sq_standard *org_note;         // 0x4
    /* 0x028 */ struct sq_standard *dst_note;         // 0x4
} anon_1_113;

/* anon_11_113 -- @anon11, 0x14 bytes, fp_hand.c (DIE 0x2021CD) */
typedef struct {   // size 0x14
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float d;                              // 0x4
    /* 0x00C */ int ct;                               // 0x4
    /* 0x010 */ int state;                            // 0x4
} anon_11_113;

/* anon_12_113 -- @anon12, 0x30 bytes, fp_hand.c (DIE 0x202A98) */
typedef struct {   // size 0x30
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float th;                             // 0x4
    /* 0x00C */ float rp;                             // 0x4
    /* 0x010 */ float rv;                             // 0x4
    /* 0x014 */ float wh;                             // 0x4
    /* 0x018 */ int r;                                // 0x4
    /* 0x01C */ int g;                                // 0x4
    /* 0x020 */ int b;                                // 0x4
    /* 0x024 */ int a;                                // 0x4
    /* 0x028 */ int ct;                               // 0x4
    /* 0x02C */ int state;                            // 0x4
} anon_12_113;

/* anon_2_113 -- @anon2, 0x66C bytes, fp_hand.c (DIE 0x1FE871) */
typedef struct {   // size 0x66C
    /* 0x000 */ int hold_state[2];                    // 0x8
    /* 0x008 */ int message_id[2];                    // 0x8
    /* 0x010 */ int message_ct[2];                    // 0x8
    /* 0x018 */ anon_11_113 efspot[2];                // 0x28
    /* 0x040 */ anon_12_113 efstar[2][16];            // 0x600
    /* 0x640 */ anon_1_113 seq_info;                  // 0x2C
} anon_2_113;

/* anon_6_113 -- @anon6, 0x4 bytes, fp_hand.c (DIE 0x20135F) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_6_113;

/* anon_8_113 -- @anon8, 0x10 bytes, fp_hand.c (DIE 0x20161D) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_6_113 x0;                        // 0x4
    /* 0x004 */ anon_6_113 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_8_113;

/* anon_5_113 -- @anon5, 0x24 bytes, fp_hand.c (DIE 0x1FF3F1) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_6_113 x0;                        // 0x4
    /* 0x004 */ anon_6_113 y0;                        // 0x4
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
} anon_5_113;

/* anon_7_113 -- @anon7, 0x30 bytes, fp_hand.c (DIE 0x2013E0) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_6_113 x0;                        // 0x4
    /* 0x004 */ anon_6_113 y0;                        // 0x4
    /* 0x008 */ anon_6_113 x1;                        // 0x4
    /* 0x00C */ anon_6_113 y1;                        // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
} anon_7_113;

/* anon_9_113 -- @anon9, 0x2 bytes, fp_hand.c (DIE 0x201DD9) */
typedef struct {   // size 0x2
    /* 0x000 */ unsigned char note_bit;               // 0x1
    /* 0x001 */ unsigned char type;                   // 0x1
} anon_9_113;


/* variables (3) */
anon_2_113 fp_solo_w;                                            /* @0x007219B0 size 0x66C */
struct _EYETOY_W *EYETOYW;                                       /* @0x002DD9A8 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions defined (14) */
void fp_MgSoloDecJudgeMessageCt(void);                           /* 0x00242940-0x00242980 lines 1132-1139 */
int fp_MgSoloGetJudgeMessageCt(int pos);                         /* 0x00242980-0x00242998 lines 1127-1128 */
int fp_MgSoloGetJudgeMessageId(int pos);                         /* 0x002429A0-0x002429B8 lines 1122-1123 */
void fp_MgSoloSetJudgeMessage(int pos, int id, int ct);          /* 0x002429C0-0x002429E8 lines 1115-1117 */
void fp_MgSoloInit(void);                                        /* 0x002429F0-0x00242A80 lines 1089-1107 */
void fp_MgSoloDispHandIcon(int pos, int px, int py, int clut, int br, int br_e, int alpha); /* 0x00242A80-0x00242C30 lines 1053-1086 */
void fp_MgSoloDispHandSpot(int pos, int px, int py, int reduce); /* 0x00242C30-0x00242F00 lines 986-1049 */
void fp_MgSoloSetHoldState(int pos, int state);                  /* 0x00242F00-0x00242F18 lines 979-980 */
void fp_MgSoloSetOkEffect(int pos, int px, int py, int judge);   /* 0x00242F20-0x002430C4 lines 904-973 */
int fp_MgSoloIsInputHand(int pos);                               /* 0x002430D0-0x00243284 lines 857-874 */
static int fp_MgSoloAnalyzeSequence(anon_1_113 *seq_info);       /* 0x00243290-0x00244068 lines 251-852 */
static int fp_MgSoloMakeSequence(anon_1_113 *seq_info);          /* 0x00244070-0x00244244 lines 164-248 */
void fp_MgSoloSetupSequence(void);                               /* 0x00244250-0x0024451C lines 106-162 */
void fp_MgSoloSetupTexture(void);                                /* 0x00244520-0x00244584 lines 88-100 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_hand_c_H */
