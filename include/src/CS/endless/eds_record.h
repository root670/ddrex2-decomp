/*
 * C:\work\usam2\src\CS\endless\eds_record.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x00237F50-0x00239678
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_endless_eds_record_c_H
#define DDR_UNIT_src_CS_endless_eds_record_c_H

#include "types/_EDSBOX_MAIN.h"
#include "types/_EDSSYS_W.h"
#include "types/_EDSS_PLAY_W.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/demo_loop_w.h"
#include "types/play_loop_w.h"

/* anonymous types (5) */

/* anon_0_26 -- @anon0, 0x8008 bytes, eds_record.c (DIE 0x5CD8B) */
union anon_0_26 {   // size 0x8008
    /* 0x000 */ struct demo_loop_w demo_loop_w;       // 0x8008
    /* 0x000 */ struct play_loop_w play_loop_w;       // 0x8008
};

/* anon_1_26 -- @anon1, 0x48 bytes, eds_record.c (DIE 0x5CE6A) */
struct anon_1_26 {   // size 0x48
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

/* anon_2_26 -- @anon2, 0xCC8 bytes, eds_record.c (DIE 0x5D828) */
struct anon_2_26 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_4_26 -- @anon4, 0x4 bytes, eds_record.c (DIE 0x5EFFE) */
union anon_4_26 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_26 -- @anon3, 0x24 bytes, eds_record.c (DIE 0x5EE1E) */
struct anon_3_26 {   // size 0x24
    /* 0x000 */ union anon_4_26 x0;                   // 0x4
    /* 0x004 */ union anon_4_26 y0;                   // 0x4
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


/* variables (4) */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
struct _EDSSYS_W *EDSSYSW;                                       /* @0x002A2254 size 0x4 */
char *EdsStrDataTbl[];                                           /* @0x00282EC0 */
struct _EDSBOX_MAIN *EDSBOXM;                                    /* @0x002A2280 size 0x4 */

/* functions referenced (4) */
void EdsMainMenuInit(struct _EDSSYS_W *);                        /* @0x00232800 */
void EdsRecordEnd(struct _EDSSYS_W *);                           /* @0x00238580 */
void EdsRecordCommon(struct _EDSSYS_W *);                        /* @0x002385C0 */
void EdsRecordTexture(struct _EDSSYS_W *);                       /* @0x002390D0 */

/* functions defined (6) */
static void EdsRecordPrintDigit(int _x, int _y, unsigned int _dig00, unsigned int _dig01, char _figure, unsigned char _alpha, int _tex); /* 0x00237F50-0x00238178 lines 755-826 */
static int EdsRenewalRecord(struct _EDSSYS_W *_eds, int flag);   /* 0x00238180-0x00238578 lines 600-725 */
static void EdsRecordEnd(struct _EDSSYS_W *_eds);                /* 0x00238580-0x002385B8 lines 537-541 */
static void EdsRecordCommon(struct _EDSSYS_W *_eds);             /* 0x002385C0-0x002390D0 lines 282-514 */
static void EdsRecordTexture(struct _EDSSYS_W *_eds);            /* 0x002390D0-0x002395D8 lines 95-260 */
void EdsRecordInit(struct _EDSSYS_W *_eds);                      /* 0x002395E0-0x00239678 lines 43-73 */

#endif /* DDR_UNIT_src_CS_endless_eds_record_c_H */
