/*
 * C:\work2\usaex2\src\AM\s573\doll\model2.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x001C7BB0-0x001CA058
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_model2_c_H
#define DDR_UNIT_src_AM_s573_doll_model2_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (12) */

/* anon_1_18 -- @anon1, 0x10 bytes, model2.c (DIE 0x277D4) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_1_18;

/* anon_2_18 -- @anon2, 0x20 bytes, model2.c (DIE 0x278E1) */
typedef struct {   // size 0x20
    /* 0x000 */ unsigned int id;                      // 0x4
    /* 0x004 */ unsigned int flag;                    // 0x4
    /* 0x008 */ unsigned int nobj;                    // 0x4
    /* 0x00C */ unsigned int nregion;                 // 0x4
    /* 0x010 */ unsigned int st_idxv;                 // 0x4
    /* 0x014 */ unsigned int st_idxn;                 // 0x4
    /* 0x018 */ unsigned int *sharedv_top;            // 0x4
    /* 0x01C */ unsigned int *sharedn_top;            // 0x4
} anon_2_18;

/* anon_3_18 -- @anon3, 0x30 bytes, model2.c (DIE 0x27A23) */
typedef struct {   // size 0x30
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
} anon_3_18;

/* anon_4_18 -- @anon4, 0xC bytes, model2.c (DIE 0x27DE6) */
typedef struct {   // size 0xC
    /* 0x000 */ anon_3_18 *region_top;                // 0x4
    /* 0x004 */ unsigned int n_region;                // 0x4
    /* 0x008 */ int scale;                            // 0x4
} anon_4_18;

/* anon_5_18 -- @anon5, 0x28 bytes, model2.c (DIE 0x27E78) */
typedef struct {   // size 0x28
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
} anon_5_18;

/* anon_6_18 -- @anon6, 0x1C bytes, model2.c (DIE 0x28567) */
typedef struct {   // size 0x1C
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
} anon_6_18;

/* anon_7_18 -- @anon7, 0x4 bytes, model2.c (DIE 0x28827) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r0;                     // 0x1
    /* 0x001 */ unsigned char g0;                     // 0x1
    /* 0x002 */ unsigned char b0;                     // 0x1
    /* 0x003 */ unsigned char code;                   // 0x1
} anon_7_18;

/* anon_8_18 -- @anon8, 0x80 bytes, model2.c (DIE 0x288E8) */
typedef struct {   // size 0x80
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
} anon_8_18;

/* anon_9_18 -- @anon9, 0x246380 bytes, model2.c (DIE 0x28D47) */
typedef struct {   // size 0x246380
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1590
    /* 0x2780 */ unsigned int mdl_data[3][45568];     // 0x85800
    /* 0x87F80 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x186380 */ unsigned int packet_w[3][65536];   // 0xC0000
} anon_9_18;

/* anon_11_18 -- @anon11, 0xC bytes, model2.c (DIE 0x28EEB) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned short n0;                    // 0x2
    /* 0x002 */ unsigned short v0;                    // 0x2
    /* 0x004 */ unsigned short n1;                    // 0x2
    /* 0x006 */ unsigned short v1;                    // 0x2
    /* 0x008 */ unsigned short n2;                    // 0x2
    /* 0x00A */ unsigned short v2;                    // 0x2
} anon_11_18;

/* anon_15_18 -- @anon15, 0x320 bytes, model2.c (DIE 0x294CD) */
typedef struct {   // size 0x320
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
} anon_15_18;

/* anon_23_18 -- @anon23, 0x4 bytes, model2.c (DIE 0x29F38) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
} anon_23_18;


/* variables (14) */
static anon_1_18 *wk;                                            /* @0x002DD96C size 0x4 */
static anon_1_18 *lw;                                            /* @0x002DD970 size 0x4 */
static float (*tmp)[4];                                          /* @0x002DD980 size 0x4 */
static float (*rmat)[4][4];                                      /* @0x002DD990 size 0x4 */
static struct _GsCOORDINATE2 **DSTACK;                           /* @0x002DD994 size 0x4 */
static float lc[2][4];                                           /* @0x002B5C80 size 0x20 */
static float lct[2][4];                                          /* @0x002B5CA0 size 0x20 */
anon_8_18 *dancer_ctrl_w;                                        /* @0x002DD94C size 0x4 */
anon_1_18 *sharenk;                                              /* @0x002DE4B8 size 0x4 */
anon_15_18 *gs3d;                                                /* @0x002DD998 size 0x4 */
float shadow_bri;                                                /* @0x002DE4AC size 0x4 */
anon_1_18 *sharewk;                                              /* @0x002DE4B4 size 0x4 */
unsigned int *prim_tbl;                                          /* @0x002DE4B0 size 0x4 */
anon_9_18 *dancer_data_w;                                        /* @0x002DE4A8 size 0x4 */

/* functions defined (13) */
static void NormCulcG3US(anon_2_18 *hp, anon_3_18 *rp);          /* 0x001C7BB0-0x001C7F50 lines 800-842 */
static void NormCulcG3U(anon_2_18 *hp, anon_3_18 *rp);           /* 0x001C7F50-0x001C82DC lines 742-795 */
static void VertCulcU(anon_2_18 *hp, anon_3_18 *rp, float scalex, float scaley, float scalez); /* 0x001C82E0-0x001C8738 lines 684-737 */
static void drawGT3(anon_3_18 *rp, anon_5_18 *prp, int cull, unsigned int prmask); /* 0x001C8740-0x001C8A78 lines 618-679 */
static void drawGT3L(anon_3_18 *rp, anon_5_18 *prp, int cull, unsigned int prmask); /* 0x001C8A80-0x001C8D94 lines 551-613 */
static void drawLcore(anon_3_18 *rp, int r, int g, int b, unsigned int prmask); /* 0x001C8DA0-0x001C8F30 lines 508-541 */
static void drawG3core(anon_3_18 *rp, int cull, int r, int g, int b, unsigned int prmask); /* 0x001C8F30-0x001C910C lines 445-483 */
static void drawG3L(anon_3_18 *rp, int cull, unsigned int prmask); /* 0x001C9110-0x001C92F4 lines 400-440 */
static void NMDSortObject5(struct dancer_model_w *mdl, anon_934863761eeb *objp, int id, int render); /* 0x001C9300-0x001C96E4 lines 321-395 */
static void nmd_model_disp(struct dancer_model_w *mdl, anon_934863761eeb *obj_p, int id, int render); /* 0x001C96F0-0x001C9A38 lines 266-316 */
void draw_dancer_model(int pid, int toon);                       /* 0x001C9A40-0x001C9D04 lines 191-261 */
static void PsGsGetLs(struct _GsCOORDINATE2 *coord, float (*mat)[4]); /* 0x001C9D10-0x001C9E5C lines 150-183 */
void pre_draw_dancer_model(int pid);                             /* 0x001C9E60-0x001CA058 lines 104-130 */

#endif /* DDR_UNIT_src_AM_s573_doll_model2_c_H */
