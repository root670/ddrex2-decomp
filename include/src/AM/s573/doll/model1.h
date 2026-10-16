/*
 * C:\work2\usaex2\src\AM\s573\doll\model1.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001C7730-0x001C7BA4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_model1_c_H
#define DDR_UNIT_src_AM_s573_doll_model1_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (21) */

/* anon_0_17 -- @anon0, 0x30 bytes, model1.c (DIE 0x2464D) */
struct anon_0_17 {   // size 0x30
    /* 0x000 */ unsigned int type;                    // 0x4
    /* 0x004 */ unsigned int *vert_top;               // 0x4
    /* 0x008 */ unsigned int n_vert;                  // 0x4
    /* 0x00C */ unsigned int n_calcv;                 // 0x4
    /* 0x010 */ unsigned int n_sharev;                // 0x4
    /* 0x014 */ unsigned int *normal_top;             // 0x4
    /* 0x018 */ unsigned int n_normal;                // 0x4
    /* 0x01C */ unsigned int n_calcn;                 // 0x4
    /* 0x020 */ unsigned int n_sharen;                // 0x4
    /* 0x024 */ unsigned int *primitive_top;          // 0x4
    /* 0x028 */ unsigned int *preset_top;             // 0x4
    /* 0x02C */ unsigned int n_primitive;             // 0x4
};

/* anon_1_17 -- @anon1, 0xC bytes, model1.c (DIE 0x24BC2) */
struct anon_1_17 {   // size 0xC
    /* 0x000 */ struct anon_0_17 *region_top;         // 0x4
    /* 0x004 */ unsigned int n_region;                // 0x4
    /* 0x008 */ int scale;                            // 0x4
};

/* anon_2_17 -- @anon2, 0x20 bytes, model1.c (DIE 0x24C54) */
struct anon_2_17 {   // size 0x20
    /* 0x000 */ unsigned int id;                      // 0x4
    /* 0x004 */ unsigned int flag;                    // 0x4
    /* 0x008 */ unsigned int nobj;                    // 0x4
    /* 0x00C */ unsigned int nregion;                 // 0x4
    /* 0x010 */ unsigned int st_idxv;                 // 0x4
    /* 0x014 */ unsigned int st_idxn;                 // 0x4
    /* 0x018 */ unsigned int *sharedv_top;            // 0x4
    /* 0x01C */ unsigned int *sharedn_top;            // 0x4
};

/* anon_14_17 -- @anon14, 0x2 bytes, model1.c (DIE 0x25B19) */
struct anon_14_17 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_15_17 -- @anon15, 0x4 bytes, model1.c (DIE 0x25B82) */
struct anon_15_17 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_14_17 tbl[1];             // 0x2
};

/* anon_3_17 -- @anon3, 0x8 bytes, model1.c (DIE 0x24D96) */
struct anon_3_17 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_15_17 data;               // 0x4
};

/* anon_4_17 -- @anon4, 0xC bytes, model1.c (DIE 0x24E3F) */
struct anon_4_17 {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_3_17 **offset;            // 0x4
};

/* anon_5_17 -- @anon5, 0x10 bytes, model1.c (DIE 0x25133) */
struct anon_5_17 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_6_17 -- @anon6, 0xC bytes, model1.c (DIE 0x251D7) */
struct anon_6_17 {   // size 0xC
    /* 0x000 */ unsigned char u0;                     // 0x1
    /* 0x001 */ unsigned char v0;                     // 0x1
    /* 0x002 */ unsigned short clut;                  // 0x2
    /* 0x004 */ unsigned char u1;                     // 0x1
    /* 0x005 */ unsigned char v1;                     // 0x1
    /* 0x006 */ unsigned short tpage;                 // 0x2
    /* 0x008 */ unsigned char u2;                     // 0x1
    /* 0x009 */ unsigned char v2;                     // 0x1
    /* 0x00A */ unsigned short p0;                    // 0x2
};

/* anon_7_17 -- @anon7, 0xC bytes, model1.c (DIE 0x25312) */
struct anon_7_17 {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_4_17 **offset;            // 0x4
};

/* anon_8_17 -- @anon8, 0x8 bytes, model1.c (DIE 0x253C3) */
struct anon_8_17 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_7_17 *offset;             // 0x4
};

/* anon_9_17 -- @anon9, 0x20 bytes, model1.c (DIE 0x2542E) */
struct anon_9_17 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
};

/* anon_10_17 -- @anon10, 0x10 bytes, model1.c (DIE 0x254FB) */
struct anon_10_17 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_8_17 motion[1];           // 0x8
};

/* anon_11_17 -- @anon11, 0x14 bytes, model1.c (DIE 0x255CE) */
struct anon_11_17 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00C */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};

/* anon_12_17 -- @anon12, 0x10 bytes, model1.c (DIE 0x256EE) */
struct anon_12_17 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
};

/* anon_13_17 -- @anon13, 0x28 bytes, model1.c (DIE 0x2578B) */
struct anon_13_17 {   // size 0x28
    /* 0x000 */ unsigned int tag;                     // 0x4
    /* 0x004 */ unsigned char r0;                     // 0x1
    /* 0x005 */ unsigned char g0;                     // 0x1
    /* 0x006 */ unsigned char b0;                     // 0x1
    /* 0x007 */ unsigned char code;                   // 0x1
    /* 0x008 */ short x0;                             // 0x2
    /* 0x00A */ short y0;                             // 0x2
    /* 0x00C */ unsigned char u0;                     // 0x1
    /* 0x00D */ unsigned char v0;                     // 0x1
    /* 0x00E */ unsigned short clut;                  // 0x2
    /* 0x010 */ unsigned char r1;                     // 0x1
    /* 0x011 */ unsigned char g1;                     // 0x1
    /* 0x012 */ unsigned char b1;                     // 0x1
    /* 0x013 */ unsigned char p1;                     // 0x1
    /* 0x014 */ short x1;                             // 0x2
    /* 0x016 */ short y1;                             // 0x2
    /* 0x018 */ unsigned char u1;                     // 0x1
    /* 0x019 */ unsigned char v1;                     // 0x1
    /* 0x01A */ unsigned short tpage;                 // 0x2
    /* 0x01C */ unsigned char r2;                     // 0x1
    /* 0x01D */ unsigned char g2;                     // 0x1
    /* 0x01E */ unsigned char b2;                     // 0x1
    /* 0x01F */ unsigned char p2;                     // 0x1
    /* 0x020 */ short x2;                             // 0x2
    /* 0x022 */ short y2;                             // 0x2
    /* 0x024 */ unsigned char u2;                     // 0x1
    /* 0x025 */ unsigned char v2;                     // 0x1
    /* 0x026 */ unsigned short pad2;                  // 0x2
};

/* anon_16_17 -- @anon16, 0x8 bytes, model1.c (DIE 0x25BEA) */
struct anon_16_17 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_17_17 -- @anon17, 0x1C bytes, model1.c (DIE 0x25D81) */
struct anon_17_17 {   // size 0x1C
    /* 0x000 */ unsigned int tag;                     // 0x4
    /* 0x004 */ unsigned char r0;                     // 0x1
    /* 0x005 */ unsigned char g0;                     // 0x1
    /* 0x006 */ unsigned char b0;                     // 0x1
    /* 0x007 */ unsigned char code;                   // 0x1
    /* 0x008 */ short x0;                             // 0x2
    /* 0x00A */ short y0;                             // 0x2
    /* 0x00C */ unsigned char r1;                     // 0x1
    /* 0x00D */ unsigned char g1;                     // 0x1
    /* 0x00E */ unsigned char b1;                     // 0x1
    /* 0x00F */ unsigned char pad1;                   // 0x1
    /* 0x010 */ short x1;                             // 0x2
    /* 0x012 */ short y1;                             // 0x2
    /* 0x014 */ unsigned char r2;                     // 0x1
    /* 0x015 */ unsigned char g2;                     // 0x1
    /* 0x016 */ unsigned char b2;                     // 0x1
    /* 0x017 */ unsigned char pad2;                   // 0x1
    /* 0x018 */ short x2;                             // 0x2
    /* 0x01A */ short y2;                             // 0x2
};

/* anon_18_17 -- @anon18, 0x80 bytes, model1.c (DIE 0x25FF5) */
struct anon_18_17 {   // size 0x80
    /* 0x000 */ struct _tag_cFilepackData tblFilepack[2];  // 0x10
    /* 0x010 */ short loadstep;                       // 0x2
    /* 0x012 */ char loadpid;                         // 0x1
    /* 0x013 */ char loadmid;                         // 0x1
    /* 0x014 */ unsigned int topaddr;                 // 0x4
    /* 0x018 */ unsigned int readaddr;                // 0x4
    /* 0x01C */ unsigned int pdataaddr;               // 0x4
    /* 0x020 */ short ploadstep;                      // 0x2
    /* 0x022 */ short chgstep[3];                     // 0x6
    /* 0x028 */ unsigned int *tex_buff[3];            // 0xC
    /* 0x034 */ unsigned int *nmd_buff[3];            // 0xC
    /* 0x040 */ char nmd_loaded_id[3];                // 0x3
    /* 0x043 */ char mot_loaded_id[3][2];             // 0x6
    /* 0x049 */ char data_buf_broken;                 // 0x1
    /* 0x04A */ char playmode;                        // 0x1
    /* 0x04B */ char toon;                            // 0x1
    /* 0x04C */ char shadow;                          // 0x1
    /* 0x04D */ char effect;                          // 0x1
    /* 0x04E */ char floor;                           // 0x1
    /* 0x04F */ char unison;                          // 0x1
    /* 0x050 */ char chr_num;                         // 0x1
    /* 0x051 */ char chr_id[3];                       // 0x3
    /* 0x054 */ char mot_id[3];                       // 0x3
    /* 0x057 */ // 0x1 bytes padding
    /* 0x058 */ unsigned int *mot_adr[3];             // 0xC
    /* 0x064 */ int base_bri;                         // 0x4
    /* 0x068 */ int bright;                           // 0x4
    /* 0x06C */ int pid_bri[3];                       // 0xC
    /* 0x078 */ unsigned int vcnt;                    // 0x4
    /* 0x07C */ int common_rand;                      // 0x4
};

/* anon_19_17 -- @anon19, 0x28 bytes, model1.c (DIE 0x2647B) */
struct anon_19_17 {   // size 0x28
    /* 0x000 */ struct anon_12_17 scale;              // 0x10
    /* 0x010 */ struct anon_16_17 rotate;             // 0x8
    /* 0x018 */ struct anon_12_17 trans;              // 0x10
};

/* anon_20_17 -- @anon20, 0x246380 bytes, model1.c (DIE 0x26837) */
struct anon_20_17 {   // size 0x246380
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1590
    /* 0x2780 */ unsigned int mdl_data[3][45568];     // 0x85800
    /* 0x87F80 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x186380 */ unsigned int packet_w[3][65536];   // 0xC0000
};


/* variables (3) */
static unsigned int chara_lst[2][16];                            /* @0x002B5C00 size 0x80 */
struct anon_18_17 *dancer_ctrl_w;                                /* @0x002DD94C size 0x4 */
struct anon_20_17 *dancer_data_w;                                /* @0x002DE4A8 size 0x4 */

/* functions defined (5) */
static unsigned int *NMDPrsetPacketGT3(unsigned int *dop, unsigned int prim_no, struct anon_6_17 *prsp); /* 0x001C7730-0x001C77A8 lines 264-281 */
static unsigned int *NMDPrsetPacketG3(unsigned int *dop, unsigned int prim_no); /* 0x001C77B0-0x001C7810 lines 239-253 */
unsigned int *NMDPresetObject(struct anon_11_17 *objp, unsigned int *addr); /* 0x001C7810-0x001C78BC lines 179-228 */
static void NMDMapModelingData(unsigned int *p);                 /* 0x001C78C0-0x001C7990 lines 144-170 */
void dancer_model_setup(int pid, int chara);                     /* 0x001C7990-0x001C7BA4 lines 48-119 */

#endif /* DDR_UNIT_src_AM_s573_doll_model1_c_H */
