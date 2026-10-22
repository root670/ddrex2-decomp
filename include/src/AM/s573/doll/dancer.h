/*
 * C:\work2\usaex2\src\AM\s573\doll\dancer.c
 * MW MIPS C Compiler, overlay main; 10 functions, code 0x001C6740-0x001C7250
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
#ifndef DDR_UNIT_src_AM_s573_doll_dancer_c_H
#define DDR_UNIT_src_AM_s573_doll_dancer_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (4) */

/* anon_0_14 -- @anon0, 0x80 bytes, dancer.c (DIE 0x1FE3E) */
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
} anon_0_14;

/* anon_6_14 -- @anon6, 0x320 bytes, dancer.c (DIE 0x20871) */
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
} anon_6_14;

/* anon_8_14 -- @anon8, 0x10 bytes, dancer.c (DIE 0x20DAC) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_8_14;

/* anon_11_14 -- @anon11, 0x246380 bytes, dancer.c (DIE 0x21368) */
typedef struct {   // size 0x246380
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1590
    /* 0x2780 */ unsigned int mdl_data[3][45568];     // 0x85800
    /* 0x87F80 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x186380 */ unsigned int packet_w[3][65536];   // 0xC0000
} anon_11_14;


/* variables (6) */
anon_0_14 *dancer_ctrl_w;                                        /* @0x002DD94C size 0x4 */
static float rad[8][2];                                          /* @0x002B3430 size 0x40 */
static short ofs[8];                                             /* @0x002B3470 size 0x10 */
anon_11_14 *dancer_data_w;                                       /* @0x002DE4A8 size 0x4 */
anon_6_14 *gs3d;                                                 /* @0x002DD998 size 0x4 */
static anon_0_14 _dancer_ctrl_w;                                 /* @0x0070FED0 size 0x80 */

/* functions defined (10) */
void ps2dancerSetPidBright(int pid, int bright);                 /* 0x001C6740-0x001C6754 lines 470-471 */
void ps2dancerSetFloor(int sw);                                  /* 0x001C6760-0x001C676C lines 444-445 */
void ps2dancerSetToon(int sw);                                   /* 0x001C6770-0x001C677C lines 439-440 */
void ps2dancerSetPlayCounter(int pid, int cur_p_counter);        /* 0x001C6780-0x001C67AC lines 409-423 */
void ps2dancerSetAllPlayCounter(int cur_p_counter);              /* 0x001C67B0-0x001C67E4 lines 398-405 */
void ps2dancerAdjPos(int pid);                                   /* 0x001C67F0-0x001C6974 lines 343-376 */
static void draw_floor(int pid, int bri);                        /* 0x001C6980-0x001C6D0C lines 246-303 */
static int get_floor_cull(float y);                              /* 0x001C6D10-0x001C6DD4 lines 206-231 */
static void clear_zbuf(void);                                    /* 0x001C6DE0-0x001C6EA0 lines 158-192 */
void ps2dancerDispStep(void);                                    /* 0x001C6EA0-0x001C7250 lines 36-146 */

#endif /* DDR_UNIT_src_AM_s573_doll_dancer_c_H */
