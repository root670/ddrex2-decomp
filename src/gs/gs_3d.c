#include "hw/vu1_mem.h"
typedef float FVEC4[4];
typedef float FMAT4[4][4];
typedef float sceVu0FVECTOR[4];
typedef float sceVu0FMATRIX[4][4] __attribute__((aligned(16)));

typedef union {
    unsigned __int128 ul128;
    unsigned long ul64[2];
    unsigned int ui32[4];
    int i32[4];
    float f32[4];
    float fv[4];
    int iv[4];
} anon_0_22;
typedef struct {
    FVEC4 cam_p __attribute__((aligned(16)));
    FVEC4 eye_p;
    FVEC4 cam_zd;
    FVEC4 cam_yd;
    FVEC4 cam_rot;
    FVEC4 lgt_amb;
    FVEC4 lgt_vec[3];
    FVEC4 lgt_col[3];
    FVEC4 obj_trans;
    FVEC4 obj_rot;
    FVEC4 fog;
    FMAT4 local_world;
    FMAT4 world_view;
    FMAT4 view_screen;
    FMAT4 local_screen;
    FMAT4 normal_light;
    FMAT4 light_color;
    FMAT4 local_light;
    FMAT4 local_color;
    int pkind;
    int pnum;
    int vnct;
    int vsize;
    unsigned int prim;
    FVEC4 *vp;
    FVEC4 *np;
    FVEC4 *tp;
    FVEC4 *cp;
} anon_1_22;

anon_1_22 *gs3d;
static int vnt_vbuf_size[3] = { 2, 3, 4 };
static anon_1_22 gs3dwork;

void func_001B7C30(void *p, int size);
void func_00102E90(FVEC4 *m);
void func_00102B68(float *v0, FVEC4 *m, float *v1);
anon_0_22 *func_00121E70(int h);
void func_00121E40(int h, int n);
void sceVu0LightColorMatrix(FVEC4 *m, float *c0, float *c1, float *c2, float *amb);
void sceVu0NormalLightMatrix(FVEC4 *m, float *l0, float *l1, float *l2);
void sceVu0MulMatrix(FVEC4 *m0, FVEC4 *m1, FVEC4 *m2);
void sceVu0Normalize(float *v0, float *v1);
void sceVu0RotMatrixX(FVEC4 *m0, FVEC4 *m1, float rx);
void sceVu0RotMatrixY(FVEC4 *m0, FVEC4 *m1, float ry);
void sceVu0RotMatrixZ(FVEC4 *m0, FVEC4 *m1, float rz);
void sceVu0CameraMatrix(FVEC4 *m, float *p, float *zd, float *yd);
void sceVu0ViewScreenMatrix(FVEC4 *m, float scrz, float ax, float ay, float cx, float cy, float zmin, float zmax, float nearz, float farz);
void gxRenderVC(anon_0_22 *v0, FVEC4 *m0, int a, int n);
void gxRenderVCT(anon_0_22 *v0, FVEC4 *m0, int a, int n);
void gxRenderVNCT(anon_0_22 *v0, FVEC4 *m0, int a, FVEC4 *ll, FVEC4 *lc, int n);

void gsInit3d(void)
{
    func_001B7C30(gs3d, 0x320);
    gs3d->cam_p[0] = 0.0f;
    gs3d->cam_p[1] = 0.0f;
    gs3d->cam_p[2] = -25.0f;
    gs3d->cam_p[3] = 0.0f;
    gs3d->cam_zd[0] = 0.0f;
    gs3d->cam_zd[1] = 0.0f;
    gs3d->cam_zd[2] = 1.0f;
    gs3d->cam_zd[3] = 1.0f;
    gs3d->cam_yd[0] = 0.0f;
    gs3d->cam_yd[1] = 1.0f;
    gs3d->cam_yd[2] = 0.0f;
    gs3d->cam_yd[3] = 1.0f;
    gs3d->cam_rot[0] = 0.0f;
    gs3d->cam_rot[1] = 0.0f;
    gs3d->cam_rot[2] = 0.0f;
    gs3d->cam_rot[3] = 0.0f;
}

void gs3dSetLightColor(int id, float r, float g, float b, float a)
{
    gs3d->lgt_col[id][0] = r;
    gs3d->lgt_col[id][1] = g;
    gs3d->lgt_col[id][2] = b;
    gs3d->lgt_col[id][3] = a;
}

void gs3dSetLightVector(int id, float x, float y, float z)
{
    gs3d->lgt_vec[id][0] = x;
    gs3d->lgt_vec[id][1] = y;
    gs3d->lgt_vec[id][2] = z;
    gs3d->lgt_vec[id][3] = 0.0f;
}

void gs3dSetLightAmbient(float r, float g, float b, float a)
{
    gs3d->lgt_amb[0] = r;
    gs3d->lgt_amb[1] = g;
    gs3d->lgt_amb[2] = b;
    gs3d->lgt_amb[3] = a;
}

void gs3dBegin(int packet, int vnct, unsigned int prim)
{
    gs3d->pnum = 0;
    gs3d->vnct = vnct;
    gs3d->vsize = vnt_vbuf_size[vnct];
    gs3d->pkind = packet;
    gs3d->prim = prim;
    if (vnct == 0) {
        gs3d->vp = VU1_MEM_PTR(FVEC4, 0x00);
        gs3d->cp = VU1_MEM_PTR(FVEC4, 0x10);
    } else if (vnct == 1) {
        gs3d->vp = VU1_MEM_PTR(FVEC4, 0x00);
        gs3d->cp = VU1_MEM_PTR(FVEC4, 0x10);
        gs3d->tp = VU1_MEM_PTR(FVEC4, 0x20);
    } else if (vnct == 2) {
        gs3d->vp = VU1_MEM_PTR(FVEC4, 0x00);
        gs3d->np = VU1_MEM_PTR(FVEC4, 0x10);
        gs3d->cp = VU1_MEM_PTR(FVEC4, 0x20);
        gs3d->tp = VU1_MEM_PTR(FVEC4, 0x30);
    } else {
    }
}

void gs3dVertex(float x, float y, float z)
{
    gs3d->vp[0][0] = x;
    gs3d->vp[0][1] = y;
    gs3d->vp[0][2] = z;
    gs3d->vp[0][3] = 1.0f;
    gs3d->vp += gs3d->vsize;
    gs3d->pnum++;
}

void gs3dColor(float r, float g, float b, float a)
{
    gs3d->cp[0][0] = r;
    gs3d->cp[0][1] = g;
    gs3d->cp[0][2] = b;
    gs3d->cp[0][3] = a;
    gs3d->cp += gs3d->vsize;
}

void gs3dTexture(float u, float v)
{
    gs3d->tp[0][0] = u;
    gs3d->tp[0][1] = v;
    gs3d->tp[0][2] = 1.0f;
    gs3d->tp[0][3] = 0.0f;
    gs3d->tp += gs3d->vsize;
}

void gs3dEnd(void)
{
    int h;
    anon_0_22 *p;
    if (gs3d->vnct == 0) {
        h = gs3d->pkind;
        p = func_00121E70(h);
        p->ul64[0] = (unsigned long)gs3d->pnum | 0x8000 | ((unsigned long)0x4000 << 32) | ((unsigned long)gs3d->prim << 47) | ((unsigned long)0x20000000 << 32);
        p->ul64[1] = 0x51;
        gxRenderVC(p + 1, gs3d->local_screen, VU1_MEM_BASE, gs3d->pnum);
        func_00121E40(h, gs3d->pnum * 2 + 1);
    } else if (gs3d->vnct == 1) {
        h = gs3d->pkind;
        p = func_00121E70(h);
        p->ul64[0] = (unsigned long)gs3d->pnum | 0x8000 | ((unsigned long)0x4000 << 32) | ((unsigned long)gs3d->prim << 47) | ((unsigned long)0x30000000 << 32);
        p->ul64[1] = 0x512;
        gxRenderVCT(p + 1, gs3d->local_screen, VU1_MEM_BASE, gs3d->pnum);
        func_00121E40(h, gs3d->pnum * 3 + 1);
    } else if (gs3d->vnct == 2) {
        h = gs3d->pkind;
        p = func_00121E70(h);
        p->ul64[0] = (unsigned long)gs3d->pnum | 0x8000 | ((unsigned long)0x4000 << 32) | ((unsigned long)gs3d->prim << 47) | ((unsigned long)0x30000000 << 32);
        p->ul64[1] = 0x512;
        gxRenderVNCT(p + 1, gs3d->local_screen, VU1_MEM_BASE, gs3d->local_light, gs3d->light_color, gs3d->pnum);
        func_00121E40(h, gs3d->pnum * 3 + 1);
    } else {
    }
}

void gs3dSetLightMatrix(FVEC4 *local_world)
{
    sceVu0LightColorMatrix(gs3d->light_color, gs3d->lgt_col[0], gs3d->lgt_col[1], gs3d->lgt_col[2], gs3d->lgt_amb);
    sceVu0NormalLightMatrix(gs3d->normal_light, gs3d->lgt_vec[0], gs3d->lgt_vec[1], gs3d->lgt_vec[2]);
    sceVu0MulMatrix(gs3d->local_light, gs3d->normal_light, local_world);
}

void gs3dSetFrustum(float ox, float oy, float scale, float scrz)
{
    sceVu0ViewScreenMatrix(gs3d->view_screen, scrz, scale, 0.94f * scale, 2048.0f + ox, 2048.0f + oy, 1.0f, 4095.9375f, 1.0f, 65536.0f);
}

static inline void gs3dCamera(void)
{

        anon_1_22 *g = gs3d;
        FVEC4 *wv;
        float *zd;
        float *yd;
        float *rot;
        sceVu0FMATRIX rm;
        sceVu0FVECTOR a, b, c;
        rot = g->cam_rot;
        yd = g->cam_yd;
        zd = g->cam_zd;
        wv = g->world_view;
        func_00102E90(rm);
        sceVu0RotMatrixX(rm, rm, rot[0]);
        sceVu0RotMatrixY(rm, rm, rot[1]);
        sceVu0RotMatrixZ(rm, rm, rot[2]);
        func_00102B68(a, rm, zd);
        func_00102B68(b, rm, yd);
        func_00102B68(c, rm, g->cam_p);
        sceVu0CameraMatrix(wv, c, a, b);
}

void gs3dSetRenderMatrix(FVEC4 *local_world)
{
    sceVu0FMATRIX work;
    float v[4];
    gs3dSetLightMatrix(local_world);
    v[0] = gs3d->eye_p[0] - gs3d->cam_p[0];
    v[1] = gs3d->eye_p[1] - gs3d->cam_p[1];
    v[2] = gs3d->eye_p[2] - gs3d->cam_p[2];
    v[3] = 0.0f;
    sceVu0Normalize(gs3d->cam_zd, v);
    gs3dCamera();
    sceVu0MulMatrix(work, gs3d->world_view, local_world);
    sceVu0MulMatrix(gs3d->local_screen, gs3d->view_screen, work);
}

void gs3dSetRenderUnitMatrix(void)
{
    sceVu0FMATRIX m;
    func_00102E90(m);
    gs3dSetRenderMatrix(m);
}

float frd(float a, float b)
{
    return b * (float)(int)(a / b);
}

float dist3d(float *v)
{
    asm {
        .set noreorder
        lwc1 $f2, 4(v)
        lwc1 $f1, 0(v)
        lwc1 $f0, 8(v)
        mul.s $f2, $f2, $f2
        mul.s $f1, $f1, $f1
        adda.s $f1, $f2
        madd.s $f0, $f0, $f0
        sqrt.s $f0, $f0
    }
}
