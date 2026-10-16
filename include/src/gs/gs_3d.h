/*
 * C:\work\usam2\src\gs\gs_3d.c
 * MW MIPS C Compiler, overlay main; 15 functions, code 0x002472D0-0x00247C38
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_gs_gs_3d_c_H
#define DDR_UNIT_src_gs_gs_3d_c_H

/* anonymous types (2) */

/* anon_0_43 -- @anon0, 0x320 bytes, gs_3d.c (DIE 0x7C925) */
struct anon_0_43 {   // size 0x320
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

/* anon_1_43 -- @anon1, 0x10 bytes, gs_3d.c (DIE 0x7CD66) */
union anon_1_43 {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
};


/* variables (3) */
struct anon_0_43 *gs3d;                                          /* @0x002A25C8 size 0x4 */
static int vnt_vbuf_size[3];                                     /* @0x0029F658 size 0xC */
static struct anon_0_43 gs3dwork;                                /* @0x006B4300 size 0x320 */

/* functions defined (15) */
float dist3d(float *v);                                          /* 0x002472D0-0x002472F8 lines 298-299 */
float frd(float a, float b);                                     /* 0x00247300-0x0024731C lines 289-290 */
void gs3dSetRenderUnitMatrix(void);                              /* 0x00247320-0x002474A8 lines 247-251 */
void gs3dSetRenderMatrix(float (*local_world)[4]);               /* 0x002474B0-0x0024763C lines 220-244 */
void gs3dSetFrustum(float ox, float oy, float scale, float scrz); /* 0x00247640-0x002476B4 lines 213-217 */
void gs3dSetLightMatrix(float (*local_world)[4]);                /* 0x002476C0-0x00247728 lines 204-210 */
void gs3dEnd(void);                                              /* 0x00247730-0x00247900 lines 189-199 */
void gs3dTexture(float u, float v);                              /* 0x00247900-0x00247950 lines 132-137 */
void gs3dColor(float r, float g, float b, float a);              /* 0x00247950-0x0024799C lines 124-129 */
void gs3dVertex(float x, float y, float z);                      /* 0x002479A0-0x00247A00 lines 107-113 */
void gs3dBegin(int packet, int vnct, unsigned int prim);         /* 0x00247A00-0x00247AE0 lines 81-101 */
void gs3dSetLightAmbient(float r, float g, float b, float a);    /* 0x00247AE0-0x00247B04 lines 65-69 */
void gs3dSetLightVector(int id, float x, float y, float z);      /* 0x00247B10-0x00247B48 lines 57-61 */
void gs3dSetLightColor(int id, float r, float g, float b, float a); /* 0x00247B50-0x00247B88 lines 48-52 */
void gsInit3d(void);                                             /* 0x00247B90-0x00247C38 lines 17-41 */

#endif /* DDR_UNIT_src_gs_gs_3d_c_H */
