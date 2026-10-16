/*
 * C:\work\usam2\src\AM\s573\doll\dcamera.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x00247E00-0x0024982C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_dcamera_c_H
#define DDR_UNIT_src_AM_s573_doll_dcamera_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (17) */

/* anon_9_45 -- @anon9, 0x2 bytes, dcamera.c (DIE 0x7F5A9) */
struct anon_9_45 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_11_45 -- @anon11, 0x4 bytes, dcamera.c (DIE 0x7F695) */
struct anon_11_45 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_9_45 tbl[1];              // 0x2
};

/* anon_0_45 -- @anon0, 0x8 bytes, dcamera.c (DIE 0x7E602) */
struct anon_0_45 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_11_45 data;               // 0x4
};

/* anon_1_45 -- @anon1, 0x70 bytes, dcamera.c (DIE 0x7E6AB) */
struct anon_1_45 {   // size 0x70
    /* 0x000 */ float view_scrz;                      // 0x4
    /* 0x004 */ float view_cx;                        // 0x4
    /* 0x008 */ float view_cy;                        // 0x4
    /* 0x00C */ float view_scale;                     // 0x4
    /* 0x010 */ float pos[4];                         // 0x10
    /* 0x020 */ float vec[4];                         // 0x10
    /* 0x030 */ float rot[4];                         // 0x10
    /* 0x040 */ float dist;                           // 0x4
    /* 0x044 */ float height;                         // 0x4
    /* 0x048 */ float ddist;                          // 0x4
    /* 0x04C */ float dheight;                        // 0x4
    /* 0x050 */ int lastcnt;                          // 0x4
    /* 0x054 */ int curcnt;                           // 0x4
    /* 0x058 */ int startcnt;                         // 0x4
    /* 0x05C */ int cnt;                              // 0x4
    /* 0x060 */ short measure;                        // 0x2
    /* 0x062 */ short type;                           // 0x2
    /* 0x064 */ short step;                           // 0x2
    /* 0x066 */ char init1st;                         // 0x1
    /* 0x067 */ char pid;                             // 0x1
    /* 0x068 */ char pnum;                            // 0x1
    /* 0x069 */ char ent_pid[3];                      // 0x3
    /* 0x06C */ signed char see_pid;                  // 0x1
    /* 0x06D */ char debug;                           // 0x1
    /* 0x06E */ char dir;                             // 0x1
    /* 0x06F */ // 0x1 bytes padding
};

/* anon_2_45 -- @anon2, 0xC bytes, dcamera.c (DIE 0x7EA32) */
struct anon_2_45 {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_0_45 **offset;            // 0x4
};

/* anon_3_45 -- @anon3, 0x10 bytes, dcamera.c (DIE 0x7EB4E) */
struct anon_3_45 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_4_45 -- @anon4, 0xC bytes, dcamera.c (DIE 0x7EEA3) */
struct anon_4_45 {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_2_45 **offset;            // 0x4
};

/* anon_5_45 -- @anon5, 0x8 bytes, dcamera.c (DIE 0x7EF54) */
struct anon_5_45 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_4_45 *offset;             // 0x4
};

/* anon_6_45 -- @anon6, 0x70 bytes, dcamera.c (DIE 0x7EFBF) */
struct anon_6_45 {   // size 0x70
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

/* anon_7_45 -- @anon7, 0x10 bytes, dcamera.c (DIE 0x7F3D0) */
struct anon_7_45 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_5_45 motion[1];           // 0x8
};

/* anon_8_45 -- @anon8, 0x1A1A40 bytes, dcamera.c (DIE 0x7F4C8) */
struct anon_8_45 {   // size 0x1A1A40
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1560
    /* 0x2750 */ unsigned int mdl_data[3][25756];     // 0x4B750
    /* 0x4DEA0 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x14C2A0 */ unsigned int packet_w[3][29176];   // 0x557A0
};

/* anon_10_45 -- @anon10, 0x20 bytes, dcamera.c (DIE 0x7F611) */
struct anon_10_45 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
};

/* anon_12_45 -- @anon12, 0x10 bytes, dcamera.c (DIE 0x7F8B1) */
struct anon_12_45 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
};

/* anon_13_45 -- @anon13, 0x8 bytes, dcamera.c (DIE 0x7F99C) */
struct anon_13_45 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_14_45 -- @anon14, 0x28 bytes, dcamera.c (DIE 0x7FCED) */
struct anon_14_45 {   // size 0x28
    /* 0x000 */ struct anon_12_45 scale;              // 0x10
    /* 0x010 */ struct anon_13_45 rotate;             // 0x8
    /* 0x018 */ struct anon_12_45 trans;              // 0x10
};

/* anon_15_45 -- @anon15, 0x320 bytes, dcamera.c (DIE 0x7FF35) */
struct anon_15_45 {   // size 0x320
    /* 0x000 */ float cam_p[4];                       // 0x10
    /* 0x010 */ float eye_p[4];                       // 0x10
    /* 0x020 */ float cam_zd[4];                      // 0x10
    /* 0x030 */ float cam_yd[4];                      // 0x10
    /* 0x040 */ float cam_rot[4];                     // 0x10
    /* 0x050 */ float lgt_amb[4];                     // 0x10
    /* 0x060 */ float lgt_vec[3][4];                  // 0x30
    /* 0x090 */ float lgt_col[3][4];                  // 0x30
    /* 0x0C0 */ float obj_trans[4];                   // 0x10
    /* 0x0D0 */ float obj_rot[4];                     // 0x10
    /* 0x0E0 */ float fog[4];                         // 0x10
    /* 0x0F0 */ float local_world[4][4];              // 0x40
    /* 0x130 */ float world_view[4][4];               // 0x40
    /* 0x170 */ float view_screen[4][4];              // 0x40
    /* 0x1B0 */ float local_screen[4][4];             // 0x40
    /* 0x1F0 */ float normal_light[4][4];             // 0x40
    /* 0x230 */ float light_color[4][4];              // 0x40
    /* 0x270 */ float local_light[4][4];              // 0x40
    /* 0x2B0 */ float local_color[4][4];              // 0x40
    /* 0x2F0 */ int pkind;                            // 0x4
    /* 0x2F4 */ int pnum;                             // 0x4
    /* 0x2F8 */ int vnct;                             // 0x4
    /* 0x2FC */ int vsize;                            // 0x4
    /* 0x300 */ unsigned int prim;                    // 0x4
    /* 0x304 */ float (*vp)[4];                       // 0x4
    /* 0x308 */ float (*np)[4];                       // 0x4
    /* 0x30C */ float (*tp)[4];                       // 0x4
    /* 0x310 */ float (*cp)[4];                       // 0x4
    /* 0x314 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_16_45 -- @anon16, 0x14 bytes, dcamera.c (DIE 0x8039D) */
struct anon_16_45 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00C */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};


/* variables (4) */
struct anon_1_45 camera_w;                                       /* @0x006B4620 size 0x70 */
struct anon_15_45 *gs3d;                                         /* @0x002A25C8 size 0x4 */
struct anon_8_45 *dancer_data_w;                                 /* @0x002A2AC4 size 0x4 */
struct anon_6_45 *dancer_ctrl_w;                                 /* @0x002A2608 size 0x4 */

/* functions defined (11) */
static void camera_tst(struct anon_1_45 *cw);                    /* 0x00247E00-0x002483BC lines 410-425 */
struct anon_1_45 *GetDancerCameraW(void);                        /* 0x002483C0-0x002483CC lines 394-395 */
static void camera_ero(struct anon_1_45 *cw, struct dancer_model_w *mdl); /* 0x002483D0-0x00248644 lines 319-339 */
static void camera_roll(struct anon_1_45 *cw);                   /* 0x00248650-0x00248A18 lines 280-314 */
static void camera_s03(struct anon_1_45 *cw, struct dancer_model_w *mdl); /* 0x00248A20-0x00248DF0 lines 249-275 */
static void camera_s02(struct anon_1_45 *cw, struct dancer_model_w *mdl); /* 0x00248DF0-0x00248F50 lines 215-244 */
static void camera_s01(struct anon_1_45 *cw, struct dancer_model_w *mdl); /* 0x00248F50-0x00249194 lines 199-210 */
static int change_camera_type(struct anon_1_45 *cw, int nmea);   /* 0x002491A0-0x0024936C lines 128-156 */
void ps2dancerCameraStep(void);                                  /* 0x00249370-0x0024966C lines 96-123 */
int ps2dancerCameraPreStep(void);                                /* 0x00249670-0x00249720 lines 69-92 */
void ps2dancerCameraInit(float cx, float cy, float scale);       /* 0x00249720-0x0024982C lines 38-65 */

#endif /* DDR_UNIT_src_AM_s573_doll_dcamera_c_H */
