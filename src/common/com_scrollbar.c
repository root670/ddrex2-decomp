struct _COM_SCROLLBAR_WORK {
    int tex_id;
    int x;
    int y;
    int h;
    int z;
    int c_max;
    int c_num;
    int c_now;
    unsigned int flag;
    unsigned char alpha;
    unsigned char bri;
};

typedef struct {
    unsigned long *addr;
    unsigned long *pict_addr;
    unsigned long *clut_addr;
    unsigned long regTex0;
    unsigned long size;
    unsigned long flg;
    float rw;
    float rh;
    unsigned short pict_size;
    unsigned short clut_size;
    unsigned short w;
    unsigned short h;
    unsigned short tbw;
    unsigned short tw;
    unsigned short th;
    unsigned short psm;
    unsigned short cpsm;
    unsigned short colors;
} texinfo;

typedef union {
    int id;
    float fd;
} coord;

typedef struct {
    coord x0;
    coord y0;
    coord x1;
    coord y1;
    unsigned int z0;
    unsigned int z1;
    float w;
    float h;
    float u;
    float v;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char a0;
    int flg;
} sprite;

void ComScrollBarDisp(struct _COM_SCROLLBAR_WORK *scrbw) {
    texinfo info;
    sprite sp2;

    if (scrbw->c_max == 0) return;
    if (scrbw->z > 0xFEFF) scrbw->z = 0xFEFF;
    func_00127F60(&info, scrbw->tex_id);
    sp2.flg = 0;

    sp2.flg |= 0x100;
    sp2.r0 = scrbw->bri; sp2.g0 = scrbw->bri; sp2.b0 = scrbw->bri; sp2.a0 = scrbw->alpha;

    sp2.u = 0.0f; sp2.v = 0.0f;
    sp2.w = 9.0f; sp2.h = 2.0f;
    sp2.x0.fd = (float)scrbw->x; sp2.y0.fd = (float)scrbw->y; sp2.z0 = scrbw->z;
    sp2.x1.fd = (float)(scrbw->x + 9); sp2.y1.fd = (float)(scrbw->y + 2); sp2.z1 = scrbw->z;
    func_00123950(&sp2);

    sp2.u = 0.0f; sp2.v = 2.0f;
    sp2.w = 9.0f; sp2.h = 1.0f;
    sp2.x0.fd = (float)scrbw->x; sp2.y0.fd = (float)(scrbw->y + 2); sp2.z0 = scrbw->z;
    sp2.x1.fd = (float)(scrbw->x + 9); sp2.y1.fd = (float)(scrbw->y + scrbw->h - 2); sp2.z1 = scrbw->z;
    func_00123950(&sp2);

    sp2.u = 0.0f; sp2.v = 22.0f;
    sp2.w = 9.0f; sp2.h = 2.0f;
    sp2.x0.fd = (float)scrbw->x; sp2.y0.fd = (float)(scrbw->y + scrbw->h - 2); sp2.z0 = scrbw->z;
    sp2.x1.fd = (float)(scrbw->x + 9); sp2.y1.fd = (float)(scrbw->y + scrbw->h); sp2.z1 = scrbw->z;
    func_00123950(&sp2);

    sp2.u = 2.0f; sp2.v = 24.0f;
    sp2.w = 5.0f; sp2.h = 1.0f;
    if (scrbw->flag & 1) {
        int bar_y, bar_h, sa, dw_h;
        bar_y = (scrbw->h - 4) * scrbw->c_now / scrbw->c_max;
        bar_h = (scrbw->h - 4) * scrbw->c_num / scrbw->c_max;
        sa = bar_y + bar_h - scrbw->h;
        sa = (sa > 0) ? sa : 0;
        dw_h = bar_h - sa;
        if (sa > 0) {
            sp2.x0.fd = (float)(scrbw->x + 2); sp2.y0.fd = (float)(scrbw->y + 2); sp2.z0 = scrbw->z + 16;
            sp2.x1.fd = (float)(scrbw->x + 7); sp2.y1.fd = (float)(scrbw->y + 2 + sa); sp2.z1 = scrbw->z + 16;
            func_00123950(&sp2);
        }
        if (dw_h > 0) {
            sp2.x0.fd = (float)(scrbw->x + 2); sp2.y0.fd = (float)(scrbw->y + 2 + bar_y); sp2.z0 = scrbw->z + 16;
            sp2.x1.fd = (float)(scrbw->x + 7); sp2.y1.fd = (float)(scrbw->y + 2 + bar_y + dw_h); sp2.z1 = scrbw->z + 16;
            func_00123950(&sp2);
        }
    }
    else if (!(scrbw->flag & 1)) {
        int bar_y, bar_h;

        bar_y = (scrbw->h - 4) * scrbw->c_now / scrbw->c_max;
        bar_h = (scrbw->h - 4) * scrbw->c_num / scrbw->c_max;
        if (bar_y < 0) bar_y = 0;
        if (scrbw->h - bar_h < bar_y) bar_y = scrbw->h - bar_h;
        sp2.x0.fd = (float)(scrbw->x + 2); sp2.y0.fd = (float)(scrbw->y + 2 + bar_y); sp2.z0 = scrbw->z + 16;
        sp2.x1.fd = (float)(scrbw->x + 7); sp2.y1.fd = (float)(scrbw->y + 2 + bar_y + bar_h); sp2.z1 = scrbw->z + 16;
        func_00123950(&sp2);
    }
}
