/*
 * C:\work\usam2\src\gs\gs_3d.c
 * MW MIPS C Compiler, overlay main; 15 functions, code 0x002472D0-0x00247C38
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* variables (3) */
struct @anon0 *gs3d;                                             /* @0x002A25C8 size 0x4 */
static int vnt_vbuf_size[3];                                     /* @0x0029F658 size 0xC */
static struct @anon0 gs3dwork;                                   /* @0x006B4300 size 0x320 */

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
