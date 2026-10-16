/*
 * C:\work\usam2\src\AM\s573\doll\model1.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00249D10-0x0024A1AC
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

/* anon_11_48 -- @anon11, 0x2 bytes, model1.c (DIE 0x842D6) */
struct anon_11_48 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_13_48 -- @anon13, 0x4 bytes, model1.c (DIE 0x843C3) */
struct anon_13_48 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_11_48 tbl[1];             // 0x2
};

/* anon_0_48 -- @anon0, 0x8 bytes, model1.c (DIE 0x83247) */
struct anon_0_48 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_13_48 data;               // 0x4
};

/* anon_1_48 -- @anon1, 0x14 bytes, model1.c (DIE 0x832F0) */
struct anon_1_48 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00C */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};

/* anon_2_48 -- @anon2, 0x28 bytes, model1.c (DIE 0x8340F) */
struct anon_2_48 {   // size 0x28
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

/* anon_3_48 -- @anon3, 0xC bytes, model1.c (DIE 0x8379C) */
struct anon_3_48 {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_0_48 **offset;            // 0x4
};

/* anon_4_48 -- @anon4, 0x10 bytes, model1.c (DIE 0x838B8) */
struct anon_4_48 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_5_48 -- @anon5, 0x1C bytes, model1.c (DIE 0x8395C) */
struct anon_5_48 {   // size 0x1C
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

/* anon_6_48 -- @anon6, 0xC bytes, model1.c (DIE 0x83BCF) */
struct anon_6_48 {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_3_48 **offset;            // 0x4
};

/* anon_7_48 -- @anon7, 0x8 bytes, model1.c (DIE 0x83C80) */
struct anon_7_48 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_6_48 *offset;             // 0x4
};

/* anon_8_48 -- @anon8, 0x70 bytes, model1.c (DIE 0x83CEB) */
struct anon_8_48 {   // size 0x70
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

/* anon_9_48 -- @anon9, 0x10 bytes, model1.c (DIE 0x840FC) */
struct anon_9_48 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_7_48 motion[1];           // 0x8
};

/* anon_10_48 -- @anon10, 0x1A1A40 bytes, model1.c (DIE 0x841F4) */
struct anon_10_48 {   // size 0x1A1A40
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1560
    /* 0x2750 */ unsigned int mdl_data[3][25756];     // 0x4B750
    /* 0x4DEA0 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x14C2A0 */ unsigned int packet_w[3][29176];   // 0x557A0
};

/* anon_12_48 -- @anon12, 0x20 bytes, model1.c (DIE 0x8433F) */
struct anon_12_48 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
};

/* anon_14_48 -- @anon14, 0x10 bytes, model1.c (DIE 0x845DF) */
struct anon_14_48 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
};

/* anon_15_48 -- @anon15, 0x20 bytes, model1.c (DIE 0x8467C) */
struct anon_15_48 {   // size 0x20
    /* 0x000 */ unsigned int id;                      // 0x4
    /* 0x004 */ unsigned int flag;                    // 0x4
    /* 0x008 */ unsigned int nobj;                    // 0x4
    /* 0x00C */ unsigned int nregion;                 // 0x4
    /* 0x010 */ unsigned int st_idxv;                 // 0x4
    /* 0x014 */ unsigned int st_idxn;                 // 0x4
    /* 0x018 */ unsigned int *sharedv_top;            // 0x4
    /* 0x01C */ unsigned int *sharedn_top;            // 0x4
};

/* anon_16_48 -- @anon16, 0x8 bytes, model1.c (DIE 0x8480D) */
struct anon_16_48 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_17_48 -- @anon17, 0x30 bytes, model1.c (DIE 0x84B3A) */
struct anon_17_48 {   // size 0x30
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

/* anon_18_48 -- @anon18, 0x28 bytes, model1.c (DIE 0x84D26) */
struct anon_18_48 {   // size 0x28
    /* 0x000 */ struct anon_14_48 scale;              // 0x10
    /* 0x010 */ struct anon_16_48 rotate;             // 0x8
    /* 0x018 */ struct anon_14_48 trans;              // 0x10
};

/* anon_19_48 -- @anon19, 0xC bytes, model1.c (DIE 0x84F4A) */
struct anon_19_48 {   // size 0xC
    /* 0x000 */ struct anon_17_48 *region_top;        // 0x4
    /* 0x004 */ unsigned int n_region;                // 0x4
    /* 0x008 */ int scale;                            // 0x4
};

/* anon_20_48 -- @anon20, 0xC bytes, model1.c (DIE 0x85107) */
struct anon_20_48 {   // size 0xC
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


/* variables (3) */
static unsigned int chara_lst[2][16];                            /* @0x0028B090 size 0x80 */
struct anon_8_48 *dancer_ctrl_w;                                 /* @0x002A2608 size 0x4 */
struct anon_10_48 *dancer_data_w;                                /* @0x002A2AC4 size 0x4 */

/* functions defined (5) */
static unsigned int *NMDPrsetPacketGT3(unsigned int *dop, unsigned int prim_no, struct anon_20_48 *prsp); /* 0x00249D10-0x00249D88 lines 266-283 */
static unsigned int *NMDPrsetPacketG3(unsigned int *dop, unsigned int prim_no); /* 0x00249D90-0x00249DF0 lines 241-255 */
unsigned int *NMDPresetObject(struct anon_1_48 *objp, unsigned int *addr); /* 0x00249DF0-0x00249E9C lines 181-230 */
static void NMDMapModelingData(unsigned int *p);                 /* 0x00249EA0-0x00249F70 lines 146-172 */
void dancer_model_setup(int pid, int chara);                     /* 0x00249F70-0x0024A1AC lines 50-121 */

#endif /* DDR_UNIT_src_AM_s573_doll_model1_c_H */
