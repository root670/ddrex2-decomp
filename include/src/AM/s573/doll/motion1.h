/*
 * C:\work\usam2\src\AM\s573\doll\motion1.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x0024C310-0x0024D0E0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_motion1_c_H
#define DDR_UNIT_src_AM_s573_doll_motion1_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dance_set.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (16) */

/* anon_9_50 -- @anon9, 0x2 bytes, motion1.c (DIE 0x8B901) */
struct anon_9_50 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_11_50 -- @anon11, 0x4 bytes, motion1.c (DIE 0x8B9ED) */
struct anon_11_50 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_9_50 tbl[1];              // 0x2
};

/* anon_0_50 -- @anon0, 0x8 bytes, motion1.c (DIE 0x8AD1D) */
struct anon_0_50 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_11_50 data;               // 0x4
};

/* anon_1_50 -- @anon1, 0xC bytes, motion1.c (DIE 0x8ADEA) */
struct anon_1_50 {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_0_50 **offset;            // 0x4
};

/* anon_2_50 -- @anon2, 0x14 bytes, motion1.c (DIE 0x8AEE2) */
struct anon_2_50 {   // size 0x14
    /* 0x000 */ char *dance_name;                     // 0x4
    /* 0x004 */ char *tail_name[4];                   // 0x10
};

/* anon_3_50 -- @anon3, 0x10 bytes, motion1.c (DIE 0x8AF77) */
struct anon_3_50 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_4_50 -- @anon4, 0xC bytes, motion1.c (DIE 0x8B042) */
struct anon_4_50 {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_1_50 **offset;            // 0x4
};

/* anon_5_50 -- @anon5, 0x8 bytes, motion1.c (DIE 0x8B2AC) */
struct anon_5_50 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_4_50 *offset;             // 0x4
};

/* anon_6_50 -- @anon6, 0x70 bytes, motion1.c (DIE 0x8B317) */
struct anon_6_50 {   // size 0x70
    /* 0x000 */ struct _tag_cFilepackData tblFilepack[2];  // 0x10
    /* 0x010 */ short loadstep;                       // 0x2
    /* 0x012 */ char loadpid;                         // 0x1
    /* 0x013 */ char loadmid;                         // 0x1
    /* 0x014 */ unsigned int topaddr;                 // 0x4
    /* 0x018 */ unsigned int readaddr;                // 0x4
    /* 0x01C */ unsigned int pdataaddr;               // 0x4
    /* 0x020 */ short ploadstep;                      // 0x2
    /* 0x022 */ short pad0;                           // 0x2
    /* 0x024 */ unsigned int *tex_buff[3];            // 0xC
    /* 0x030 */ unsigned int *nmd_buff[3];            // 0xC
    /* 0x03C */ char nmd_loaded_id[3];                // 0x3
    /* 0x03F */ char mot_loaded_id[3][2];             // 0x6
    /* 0x045 */ char data_buf_broken;                 // 0x1
    /* 0x046 */ char playmode;                        // 0x1
    /* 0x047 */ char toon;                            // 0x1
    /* 0x048 */ char shadow;                          // 0x1
    /* 0x049 */ char floor;                           // 0x1
    /* 0x04A */ char unison;                          // 0x1
    /* 0x04B */ char chr_num;                         // 0x1
    /* 0x04C */ char chr_id[3];                       // 0x3
    /* 0x04F */ char mot_id[3];                       // 0x3
    /* 0x052 */ // 0x2 bytes padding
    /* 0x054 */ unsigned int *mot_adr[3];             // 0xC
    /* 0x060 */ int base_bri;                         // 0x4
    /* 0x064 */ int bright;                           // 0x4
    /* 0x068 */ unsigned int vcnt;                    // 0x4
    /* 0x06C */ int common_rand;                      // 0x4
};

/* anon_7_50 -- @anon7, 0x10 bytes, motion1.c (DIE 0x8B728) */
struct anon_7_50 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_5_50 motion[1];           // 0x8
};

/* anon_8_50 -- @anon8, 0x1A1A40 bytes, motion1.c (DIE 0x8B820) */
struct anon_8_50 {   // size 0x1A1A40
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1560
    /* 0x2750 */ unsigned int mdl_data[3][25756];     // 0x4B750
    /* 0x4DEA0 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x14C2A0 */ unsigned int packet_w[3][29176];   // 0x557A0
};

/* anon_10_50 -- @anon10, 0x20 bytes, motion1.c (DIE 0x8B969) */
struct anon_10_50 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
};

/* anon_12_50 -- @anon12, 0x10 bytes, motion1.c (DIE 0x8BC09) */
struct anon_12_50 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
};

/* anon_13_50 -- @anon13, 0x8 bytes, motion1.c (DIE 0x8BCF4) */
struct anon_13_50 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_14_50 -- @anon14, 0x28 bytes, motion1.c (DIE 0x8C102) */
struct anon_14_50 {   // size 0x28
    /* 0x000 */ struct anon_12_50 scale;              // 0x10
    /* 0x010 */ struct anon_13_50 rotate;             // 0x8
    /* 0x018 */ struct anon_12_50 trans;              // 0x10
};

/* anon_15_50 -- @anon15, 0x14 bytes, motion1.c (DIE 0x8C2E3) */
struct anon_15_50 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00C */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};


/* variables (12) */
static char *dset[8][5];                                         /* @0x0028B150 size 0xA0 */
static struct dance_set normal_dance_set[9];                     /* @0x002A0010 size 0x144 */
static struct anon_2_50 dance_con[20];                           /* @0x002A0230 size 0x190 */
static char *dance_name[20];                                     /* @0x0028B1F0 size 0x50 */
static int parent_parts[18];                                     /* @0x0028B240 size 0x48 */
static unsigned int chara_pos[28];                               /* @0x0028B290 size 0x70 */
void *dance_motion_pack_tab[3][20];                              /* @0x006B46D0 size 0xF0 */
struct anon_6_50 *dancer_ctrl_w;                                 /* @0x002A2608 size 0x4 */
struct anon_8_50 *dancer_data_w;                                 /* @0x002A2AC4 size 0x4 */
int player_dance_top[3][17];                                     /* @0x006B6980 size 0xCC */
struct dance_set player_dance_set[3][80];                        /* @0x006B47C0 size 0x21C0 */
int motiontype[3];                                               /* @0x006B6A50 size 0xC */

/* functions defined (5) */
void set_dance_motion_pack_tab(int pid);                         /* 0x0024C310-0x0024C4F0 lines 501-527 */
static struct anon_7_50 *get_dance_mpack(int pid, char *dname);  /* 0x0024C4F0-0x0024C5A8 lines 457-474 */
void set_dance_motion(int pid);                                  /* 0x0024C5B0-0x0024CB3C lines 276-394 */
void init_dance_motion(int pid);                                 /* 0x0024CB40-0x0024CEAC lines 219-267 */
int dancer_motion_setup(int pid, int motion_id);                 /* 0x0024CEB0-0x0024D0E0 lines 163-211 */

#endif /* DDR_UNIT_src_AM_s573_doll_motion1_c_H */
