/*
 * C:\work\usam2\src\AM\s573\doll\model2.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x0024A1B0-0x0024C308
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_model2_c_H
#define DDR_UNIT_src_AM_s573_doll_model2_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (25) */

/* anon_0_49 -- @anon0, 0xC bytes, model2.c (DIE 0x86110) */
struct anon_0_49 {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_24_49 **offset;           // 0x4
};

/* anon_1_49 -- @anon1, 0x8 bytes, model2.c (DIE 0x86208) */
struct anon_1_49 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_2_49 *offset;             // 0x4
};

/* anon_2_49 -- @anon2, 0xC bytes, model2.c (DIE 0x86524) */
struct anon_2_49 {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_0_49 **offset;            // 0x4
};

/* anon_3_49 -- @anon3, 0x4 bytes, model2.c (DIE 0x865D5) */
struct anon_3_49 {   // size 0x4
    /* 0x000 */ unsigned char r0;                     // 0x1
    /* 0x001 */ unsigned char g0;                     // 0x1
    /* 0x002 */ unsigned char b0;                     // 0x1
    /* 0x003 */ unsigned char code;                   // 0x1
};

/* anon_4_49 -- @anon4, 0x70 bytes, model2.c (DIE 0x86672) */
struct anon_4_49 {   // size 0x70
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

/* anon_5_49 -- @anon5, 0x10 bytes, model2.c (DIE 0x86A83) */
struct anon_5_49 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_1_49 motion[1];           // 0x8
};

/* anon_6_49 -- @anon6, 0x30 bytes, model2.c (DIE 0x86C7D) */
struct anon_6_49 {   // size 0x30
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

/* anon_7_49 -- @anon7, 0x1A1A40 bytes, model2.c (DIE 0x86E68) */
struct anon_7_49 {   // size 0x1A1A40
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1560
    /* 0x2750 */ unsigned int mdl_data[3][25756];     // 0x4B750
    /* 0x4DEA0 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x14C2A0 */ unsigned int packet_w[3][29176];   // 0x557A0
};

/* anon_8_49 -- @anon8, 0x28 bytes, model2.c (DIE 0x86F49) */
struct anon_8_49 {   // size 0x28
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

/* anon_9_49 -- @anon9, 0x2 bytes, model2.c (DIE 0x872D6) */
struct anon_9_49 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_10_49 -- @anon10, 0x10 bytes, model2.c (DIE 0x87318) */
union anon_10_49 {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
};

/* anon_11_49 -- @anon11, 0x20 bytes, model2.c (DIE 0x8744C) */
struct anon_11_49 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
};

/* anon_12_49 -- @anon12, 0x4 bytes, model2.c (DIE 0x874AC) */
struct anon_12_49 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_9_49 tbl[1];              // 0x2
};

/* anon_13_49 -- @anon13, 0x20 bytes, model2.c (DIE 0x876EC) */
struct anon_13_49 {   // size 0x20
    /* 0x000 */ unsigned int id;                      // 0x4
    /* 0x004 */ unsigned int flag;                    // 0x4
    /* 0x008 */ unsigned int nobj;                    // 0x4
    /* 0x00C */ unsigned int nregion;                 // 0x4
    /* 0x010 */ unsigned int st_idxv;                 // 0x4
    /* 0x014 */ unsigned int st_idxn;                 // 0x4
    /* 0x018 */ unsigned int *sharedv_top;            // 0x4
    /* 0x01C */ unsigned int *sharedn_top;            // 0x4
};

/* anon_14_49 -- @anon14, 0x10 bytes, model2.c (DIE 0x8782F) */
struct anon_14_49 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
};

/* anon_15_49 -- @anon15, 0x8 bytes, model2.c (DIE 0x87940) */
struct anon_15_49 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_16_49 -- @anon16, 0xC bytes, model2.c (DIE 0x879DD) */
struct anon_16_49 {   // size 0xC
    /* 0x000 */ struct anon_6_49 *region_top;         // 0x4
    /* 0x004 */ unsigned int n_region;                // 0x4
    /* 0x008 */ int scale;                            // 0x4
};

/* anon_17_49 -- @anon17, 0x4 bytes, model2.c (DIE 0x87CDC) */
struct anon_17_49 {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
};

/* anon_18_49 -- @anon18, 0xC bytes, model2.c (DIE 0x87D75) */
struct anon_18_49 {   // size 0xC
    /* 0x000 */ unsigned short n0;                    // 0x2
    /* 0x002 */ unsigned short v0;                    // 0x2
    /* 0x004 */ unsigned short n1;                    // 0x2
    /* 0x006 */ unsigned short v1;                    // 0x2
    /* 0x008 */ unsigned short n2;                    // 0x2
    /* 0x00A */ unsigned short v2;                    // 0x2
};

/* anon_19_49 -- @anon19, 0x28 bytes, model2.c (DIE 0x87E73) */
struct anon_19_49 {   // size 0x28
    /* 0x000 */ struct anon_14_49 scale;              // 0x10
    /* 0x010 */ struct anon_15_49 rotate;             // 0x8
    /* 0x018 */ struct anon_14_49 trans;              // 0x10
};

/* anon_20_49 -- @anon20, 0x320 bytes, model2.c (DIE 0x8804B) */
struct anon_20_49 {   // size 0x320
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

/* anon_21_49 -- @anon21, 0x14 bytes, model2.c (DIE 0x884B3) */
struct anon_21_49 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00C */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};

/* anon_22_49 -- @anon22, 0x1C bytes, model2.c (DIE 0x886B3) */
struct anon_22_49 {   // size 0x1C
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

/* anon_23_49 -- @anon23, 0x10 bytes, model2.c (DIE 0x889BB) */
struct anon_23_49 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_24_49 -- @anon24, 0x8 bytes, model2.c (DIE 0x88AF4) */
struct anon_24_49 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_12_49 data;               // 0x4
};


/* variables (14) */
static union anon_10_49 *wk;                                     /* @0x002A25E8 size 0x4 */
static union anon_10_49 *lw;                                     /* @0x002A25EC size 0x4 */
static float (*tmp)[4];                                          /* @0x002A25F0 size 0x4 */
static float (*rmat)[4][4];                                      /* @0x002A2600 size 0x4 */
static struct _GsCOORDINATE2 **DSTACK;                           /* @0x002A2604 size 0x4 */
static float lc[2][4];                                           /* @0x0028B110 size 0x20 */
static float lct[2][4];                                          /* @0x0028B130 size 0x20 */
struct anon_4_49 *dancer_ctrl_w;                                 /* @0x002A2608 size 0x4 */
union anon_10_49 *sharenk;                                       /* @0x002A2ABC size 0x4 */
struct anon_20_49 *gs3d;                                         /* @0x002A25C8 size 0x4 */
float shadow_bri;                                                /* @0x002A2AB0 size 0x4 */
union anon_10_49 *sharewk;                                       /* @0x002A2AB8 size 0x4 */
unsigned int *prim_tbl;                                          /* @0x002A2AB4 size 0x4 */
struct anon_7_49 *dancer_data_w;                                 /* @0x002A2AC4 size 0x4 */

/* functions defined (12) */
static void NormCulcG3US(struct anon_13_49 *hp, struct anon_6_49 *rp); /* 0x0024A1B0-0x0024A550 lines 709-751 */
static void NormCulcG3U(struct anon_13_49 *hp, struct anon_6_49 *rp); /* 0x0024A550-0x0024A8DC lines 651-704 */
static void VertCulcU(struct anon_13_49 *hp, struct anon_6_49 *rp, float scalex, float scaley, float scalez); /* 0x0024A8E0-0x0024AD38 lines 593-646 */
static void drawGT3(struct anon_6_49 *rp, struct anon_8_49 *prp, int cull, unsigned int prmask); /* 0x0024AD40-0x0024B078 lines 527-588 */
static void drawGT3L(struct anon_6_49 *rp, struct anon_8_49 *prp, int cull, unsigned int prmask); /* 0x0024B080-0x0024B394 lines 460-522 */
static void drawG3core(struct anon_6_49 *rp, int cull, int r, int g, int b, unsigned int prmask); /* 0x0024B3A0-0x0024B57C lines 403-441 */
static void drawG3L(struct anon_6_49 *rp, int cull, unsigned int prmask); /* 0x0024B580-0x0024B764 lines 358-398 */
static void NMDSortObject5(struct dancer_model_w *mdl, struct anon_21_49 *objp, int id, int render); /* 0x0024B770-0x0024BAFC lines 283-353 */
static void nmd_model_disp(struct dancer_model_w *mdl, struct anon_21_49 *obj_p, int id, int render); /* 0x0024BB00-0x0024BD28 lines 235-278 */
void draw_dancer_model(int pid, int toon);                       /* 0x0024BD30-0x0024BFAC lines 187-230 */
static void PsGsGetLs(struct _GsCOORDINATE2 *coord, float (*mat)[4]); /* 0x0024BFB0-0x0024C0FC lines 146-179 */
void pre_draw_dancer_model(int pid);                             /* 0x0024C100-0x0024C308 lines 100-126 */

#endif /* DDR_UNIT_src_AM_s573_doll_model2_c_H */
