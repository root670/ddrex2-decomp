/*
 * C:\work\usam2\src\AM\s573\doll\dinit.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x00250710-0x002513e8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_dinit_c_H
#define DDR_UNIT_src_AM_s573_doll_dinit_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (18) */

/* anon_0_56 -- @anon0, 0x10 bytes, dinit.c (DIE 0x9c217) */
struct anon_0_56 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00c */ unsigned int disp : 1;                // bits 0..0
};

/* anon_1_56 -- @anon1, 0x70 bytes, dinit.c (DIE 0x9c2bb) */
struct anon_1_56 {   // size 0x70
    /* 0x000 */ struct _tag_cFilepackData tblFilepack[2];  // 0x10
    /* 0x010 */ short loadstep;                       // 0x2
    /* 0x012 */ char loadpid;                         // 0x1
    /* 0x013 */ char loadmid;                         // 0x1
    /* 0x014 */ unsigned int topaddr;                 // 0x4
    /* 0x018 */ unsigned int readaddr;                // 0x4
    /* 0x01c */ unsigned int pdataaddr;               // 0x4
    /* 0x020 */ short ploadstep;                      // 0x2
    /* 0x022 */ short pad0;                           // 0x2
    /* 0x024 */ unsigned int *tex_buff[3];            // 0xc
    /* 0x030 */ unsigned int *nmd_buff[3];            // 0xc
    /* 0x03c */ char nmd_loaded_id[3];                // 0x3
    /* 0x03f */ char mot_loaded_id[3][2];             // 0x6
    /* 0x045 */ char data_buf_broken;                 // 0x1
    /* 0x046 */ char playmode;                        // 0x1
    /* 0x047 */ char toon;                            // 0x1
    /* 0x048 */ char shadow;                          // 0x1
    /* 0x049 */ char floor;                           // 0x1
    /* 0x04a */ char unison;                          // 0x1
    /* 0x04b */ char chr_num;                         // 0x1
    /* 0x04c */ char chr_id[3];                       // 0x3
    /* 0x04f */ char mot_id[3];                       // 0x3
    /* 0x052 */ // 0x2 bytes padding
    /* 0x054 */ unsigned int *mot_adr[3];             // 0xc
    /* 0x060 */ int base_bri;                         // 0x4
    /* 0x064 */ int bright;                           // 0x4
    /* 0x068 */ unsigned int vcnt;                    // 0x4
    /* 0x06c */ int common_rand;                      // 0x4
};

/* anon_10_56 -- @anon10, 0x2 bytes, dinit.c (DIE 0x9dbf1) */
struct anon_10_56 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_12_56 -- @anon12, 0x4 bytes, dinit.c (DIE 0x9dd28) */
struct anon_12_56 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_10_56 tbl[1];             // 0x2
};

/* anon_2_56 -- @anon2, 0x8 bytes, dinit.c (DIE 0x9cd2d) */
struct anon_2_56 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_12_56 data;               // 0x4
};

/* anon_3_56 -- @anon3, 0xc bytes, dinit.c (DIE 0x9ceb4) */
struct anon_3_56 {   // size 0xc
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_2_56 **offset;            // 0x4
};

/* anon_4_56 -- @anon4, 0xcc8 bytes, dinit.c (DIE 0x9d1d4) */
struct anon_4_56 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_5_56 -- @anon5, 0xc bytes, dinit.c (DIE 0x9d2f3) */
struct anon_5_56 {   // size 0xc
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_3_56 **offset;            // 0x4
};

/* anon_6_56 -- @anon6, 0x3e bytes, dinit.c (DIE 0x9d3a4) */
struct anon_6_56 {   // size 0x3e
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[61];                          // 0x3d
};

/* anon_7_56 -- @anon7, 0x8 bytes, dinit.c (DIE 0x9d5c8) */
struct anon_7_56 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_5_56 *offset;             // 0x4
};

/* anon_8_56 -- @anon8, 0x10 bytes, dinit.c (DIE 0x9d657) */
struct anon_8_56 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_7_56 motion[1];           // 0x8
};

/* anon_9_56 -- @anon9, 0x1a1a40 bytes, dinit.c (DIE 0x9db10) */
struct anon_9_56 {   // size 0x1a1a40
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11e8
    /* 0x11e8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11f0 */ struct dancer_model_w model_w[3];    // 0x1560
    /* 0x2750 */ unsigned int mdl_data[3][25756];     // 0x4b750
    /* 0x4dea0 */ unsigned int mot_data[3][86784];    // 0xfe400
    /* 0x14c2a0 */ unsigned int packet_w[3][29176];   // 0x557a0
};

/* anon_11_56 -- @anon11, 0x20 bytes, dinit.c (DIE 0x9dca4) */
struct anon_11_56 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xc
};

/* anon_13_56 -- @anon13, 0x10 bytes, dinit.c (DIE 0x9dfd7) */
struct anon_13_56 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00c */ int pad;                              // 0x4
};

/* anon_14_56 -- @anon14, 0x8 bytes, dinit.c (DIE 0x9e12e) */
struct anon_14_56 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_15_56 -- @anon15, 0x28 bytes, dinit.c (DIE 0x9e735) */
struct anon_15_56 {   // size 0x28
    /* 0x000 */ struct anon_13_56 scale;              // 0x10
    /* 0x010 */ struct anon_14_56 rotate;             // 0x8
    /* 0x018 */ struct anon_13_56 trans;              // 0x10
};

/* anon_16_56 -- @anon16, 0x8 bytes, dinit.c (DIE 0x9eb79) */
struct anon_16_56 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};

/* anon_17_56 -- @anon17, 0x14 bytes, dinit.c (DIE 0x9ecb4) */
struct anon_17_56 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00c */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};


/* variables (6) */
static char male_mot[4];                                         /* @0x002a0418 size 0x4 */
struct anon_1_56 *dancer_ctrl_w;                                 /* @0x002a2608 size 0x4 */
struct anon_16_56 dollpack_bin[];                                /* not allocated */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */
unsigned int tex_floor[];                                        /* @0x00288660 */
struct anon_9_56 *dancer_data_w;                                 /* @0x002a2ac4 size 0x4 */

/* functions referenced (1) */
void DecodeFilepackData_Th(void *);                              /* @0x00180b60 */

/* functions defined (11) */
static void shape_mot_id(void);                                  /* 0x00250710-0x00250924 lines 384-434 */
void ps2dancerSetup(void);                                       /* 0x00250930-0x002509f8 lines 354-373 */
int ps2dancerLoadStep(void);                                     /* 0x00250a00-0x00250e2c lines 249-347 */
static int get_free_motbuf(int mot_id);                          /* 0x00250e30-0x00250ec8 lines 227-242 */
void ps2dancerLoadInit(void *readtmpaddr);                       /* 0x00250ed0-0x002510d4 lines 158-211 */
void ps2dancerEntry2(int pid, int chara, int motion);            /* 0x002510e0-0x00251168 lines 131-151 */
void ps2dancerEntry(int pid, int chara);                         /* 0x00251170-0x00251208 lines 114-128 */
static int auto_chara_select(int chara);                         /* 0x00251210-0x002512ec lines 85-111 */
void ps2dancerResetEntry(void);                                  /* 0x002512f0-0x00251308 lines 72-78 */
void ps2dancerBreakDataArea(void);                               /* 0x00251310-0x00251320 lines 63-64 */
void *ps2dancerInit(void *workaddr, int playmode);               /* 0x00251320-0x002513e8 lines 27-55 */

#endif /* DDR_UNIT_src_AM_s573_doll_dinit_c_H */
