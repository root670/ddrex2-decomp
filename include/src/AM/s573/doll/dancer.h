/*
 * C:\work\usam2\src\AM\s573\doll\dancer.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x0024e9b0-0x0024f590
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_dancer_c_H
#define DDR_UNIT_src_AM_s573_doll_dancer_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (17) */

/* anon_0_53 -- @anon0, 0x10 bytes, dancer.c (DIE 0x90382) */
struct anon_0_53 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00c */ unsigned int disp : 1;                // bits 0..0
};

/* anon_1_53 -- @anon1, 0x320 bytes, dancer.c (DIE 0x90426) */
struct anon_1_53 {   // size 0x320
    /* 0x000 */ float cam_p[4];                       // 0x10
    /* 0x010 */ float eye_p[4];                       // 0x10
    /* 0x020 */ float cam_zd[4];                      // 0x10
    /* 0x030 */ float cam_yd[4];                      // 0x10
    /* 0x040 */ float cam_rot[4];                     // 0x10
    /* 0x050 */ float lgt_amb[4];                     // 0x10
    /* 0x060 */ float lgt_vec[3][4];                  // 0x30
    /* 0x090 */ float lgt_col[3][4];                  // 0x30
    /* 0x0c0 */ float obj_trans[4];                   // 0x10
    /* 0x0d0 */ float obj_rot[4];                     // 0x10
    /* 0x0e0 */ float fog[4];                         // 0x10
    /* 0x0f0 */ float local_world[4][4];              // 0x40
    /* 0x130 */ float world_view[4][4];               // 0x40
    /* 0x170 */ float view_screen[4][4];              // 0x40
    /* 0x1b0 */ float local_screen[4][4];             // 0x40
    /* 0x1f0 */ float normal_light[4][4];             // 0x40
    /* 0x230 */ float light_color[4][4];              // 0x40
    /* 0x270 */ float local_light[4][4];              // 0x40
    /* 0x2b0 */ float local_color[4][4];              // 0x40
    /* 0x2f0 */ int pkind;                            // 0x4
    /* 0x2f4 */ int pnum;                             // 0x4
    /* 0x2f8 */ int vnct;                             // 0x4
    /* 0x2fc */ int vsize;                            // 0x4
    /* 0x300 */ unsigned int prim;                    // 0x4
    /* 0x304 */ float (*vp)[4];                       // 0x4
    /* 0x308 */ float (*np)[4];                       // 0x4
    /* 0x30c */ float (*tp)[4];                       // 0x4
    /* 0x310 */ float (*cp)[4];                       // 0x4
    /* 0x314 */ // 0xc bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_9_53 -- @anon9, 0x2 bytes, dancer.c (DIE 0x9170b) */
struct anon_9_53 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_11_53 -- @anon11, 0x4 bytes, dancer.c (DIE 0x917d3) */
struct anon_11_53 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_9_53 tbl[1];              // 0x2
};

/* anon_2_53 -- @anon2, 0x8 bytes, dancer.c (DIE 0x90bac) */
struct anon_2_53 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_11_53 data;               // 0x4
};

/* anon_3_53 -- @anon3, 0x70 bytes, dancer.c (DIE 0x90c55) */
struct anon_3_53 {   // size 0x70
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

/* anon_4_53 -- @anon4, 0xc bytes, dancer.c (DIE 0x91066) */
struct anon_4_53 {   // size 0xc
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_2_53 **offset;            // 0x4
};

/* anon_5_53 -- @anon5, 0x10 bytes, dancer.c (DIE 0x9135a) */
union anon_5_53 {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
};

/* anon_6_53 -- @anon6, 0xc bytes, dancer.c (DIE 0x91467) */
struct anon_6_53 {   // size 0xc
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_4_53 **offset;            // 0x4
};

/* anon_7_53 -- @anon7, 0x8 bytes, dancer.c (DIE 0x915a8) */
struct anon_7_53 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_6_53 *offset;             // 0x4
};

/* anon_8_53 -- @anon8, 0x10 bytes, dancer.c (DIE 0x91613) */
struct anon_8_53 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_7_53 motion[1];           // 0x8
};

/* anon_10_53 -- @anon10, 0x20 bytes, dancer.c (DIE 0x91773) */
struct anon_10_53 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xc
};

/* anon_12_53 -- @anon12, 0x10 bytes, dancer.c (DIE 0x91a13) */
struct anon_12_53 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00c */ int pad;                              // 0x4
};

/* anon_13_53 -- @anon13, 0x8 bytes, dancer.c (DIE 0x91afe) */
struct anon_13_53 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_14_53 -- @anon14, 0x28 bytes, dancer.c (DIE 0x91d31) */
struct anon_14_53 {   // size 0x28
    /* 0x000 */ struct anon_12_53 scale;              // 0x10
    /* 0x010 */ struct anon_13_53 rotate;             // 0x8
    /* 0x018 */ struct anon_12_53 trans;              // 0x10
};

/* anon_15_53 -- @anon15, 0x1a1a40 bytes, dancer.c (DIE 0x91de4) */
struct anon_15_53 {   // size 0x1a1a40
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11e8
    /* 0x11e8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11f0 */ struct dancer_model_w model_w[3];    // 0x1560
    /* 0x2750 */ unsigned int mdl_data[3][25756];     // 0x4b750
    /* 0x4dea0 */ unsigned int mot_data[3][86784];    // 0xfe400
    /* 0x14c2a0 */ unsigned int packet_w[3][29176];   // 0x557a0
};

/* anon_16_53 -- @anon16, 0x14 bytes, dancer.c (DIE 0x92115) */
struct anon_16_53 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00c */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};


/* variables (6) */
struct anon_3_53 *dancer_ctrl_w;                                 /* @0x002a2608 size 0x4 */
static float rad[8][2];                                          /* @0x0028b300 size 0x40 */
static short ofs[8];                                             /* @0x0028b340 size 0x10 */
struct anon_15_53 *dancer_data_w;                                /* @0x002a2ac4 size 0x4 */
struct anon_1_53 *gs3d;                                          /* @0x002a25c8 size 0x4 */
static struct anon_3_53 _dancer_ctrl_w;                          /* @0x006b6a60 size 0x70 */

/* functions defined (9) */
void ps2dancerSetFloor(int sw);                                  /* 0x0024e9b0-0x0024e9bc lines 421-422 */
void ps2dancerSetToon(int sw);                                   /* 0x0024e9c0-0x0024e9cc lines 416-417 */
void ps2dancerSetPlayCounter(int pid, int cur_p_counter);        /* 0x0024e9d0-0x0024e9fc lines 386-400 */
void ps2dancerSetAllPlayCounter(int cur_p_counter);              /* 0x0024ea00-0x0024ea34 lines 375-382 */
void ps2dancerAdjPos(int pid);                                   /* 0x0024ea40-0x0024eba4 lines 331-353 */
static void draw_floor(int pid, int bri);                        /* 0x0024ebb0-0x0024ef4c lines 234-291 */
static int get_floor_cull(float y);                              /* 0x0024ef50-0x0024f014 lines 194-219 */
static void clear_zbuf(void);                                    /* 0x0024f020-0x0024f0e0 lines 146-180 */
void ps2dancerDispStep(void);                                    /* 0x0024f0e0-0x0024f590 lines 37-134 */

#endif /* DDR_UNIT_src_AM_s573_doll_dancer_c_H */
