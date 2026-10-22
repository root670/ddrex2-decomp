/*
 * C:\work2\usaex2\src\AM\s573\doll\dcamera.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x001CD3D0-0x001CEEFC
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
#ifndef DDR_UNIT_src_AM_s573_doll_dcamera_c_H
#define DDR_UNIT_src_AM_s573_doll_dcamera_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (4) */

/* anon_0_24 -- @anon0, 0x70 bytes, dcamera.c (DIE 0x33C58) */
typedef struct {   // size 0x70
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
} anon_0_24;

/* anon_3_24 -- @anon3, 0x320 bytes, dcamera.c (DIE 0x341A6) */
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
} anon_3_24;

/* anon_8_24 -- @anon8, 0x80 bytes, dcamera.c (DIE 0x348BE) */
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
} anon_8_24;

/* anon_16_24 -- @anon16, 0x246380 bytes, dcamera.c (DIE 0x3585E) */
typedef struct {   // size 0x246380
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1590
    /* 0x2780 */ unsigned int mdl_data[3][45568];     // 0x85800
    /* 0x87F80 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x186380 */ unsigned int packet_w[3][65536];   // 0xC0000
} anon_16_24;


/* variables (4) */
anon_0_24 camera_w;                                              /* @0x00712600 size 0x70 */
anon_3_24 *gs3d;                                                 /* @0x002DD998 size 0x4 */
anon_16_24 *dancer_data_w;                                       /* @0x002DE4A8 size 0x4 */
anon_8_24 *dancer_ctrl_w;                                        /* @0x002DD94C size 0x4 */

/* functions defined (12) */
static void camera_tst(anon_0_24 *cw);                           /* 0x001CD3D0-0x001CD970 lines 458-473 */
void ps2dancerSetCameraPos(float cx, float cy);                  /* 0x001CD970-0x001CD984 lines 449-451 */
anon_0_24 *GetDancerCameraW(void);                               /* 0x001CD990-0x001CD99C lines 442-443 */
static void camera_ero(anon_0_24 *cw, struct dancer_model_w *mdl); /* 0x001CD9A0-0x001CDC0C lines 346-366 */
static void camera_roll(anon_0_24 *cw);                          /* 0x001CDC10-0x001CDFD8 lines 307-341 */
static void camera_s03(anon_0_24 *cw, struct dancer_model_w *mdl); /* 0x001CDFE0-0x001CE3A0 lines 276-302 */
static void camera_s02(anon_0_24 *cw, struct dancer_model_w *mdl); /* 0x001CE3A0-0x001CE500 lines 242-271 */
static void camera_s01(anon_0_24 *cw, struct dancer_model_w *mdl); /* 0x001CE500-0x001CE72C lines 226-237 */
static int change_camera_type(anon_0_24 *cw, int nmea);          /* 0x001CE730-0x001CEA24 lines 137-183 */
void ps2dancerCameraStep(void);                                  /* 0x001CEA30-0x001CED0C lines 104-132 */
int ps2dancerCameraPreStep(void);                                /* 0x001CED10-0x001CEDC0 lines 77-100 */
void ps2dancerCameraInit(float cx, float cy, float scale);       /* 0x001CEDC0-0x001CEEFC lines 38-73 */

#endif /* DDR_UNIT_src_AM_s573_doll_dcamera_c_H */
