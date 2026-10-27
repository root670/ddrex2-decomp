typedef struct {
    int pos_x;
    int pos_y;
    int depth_z;
    int cur_x;
    int cur_y;
    int item_x;
    int item_y;
    int dist_x;
    int dist_y;
    int counter;
} anon_0_239;

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
} anon_1_239;

typedef union {
    int id;
    float fd;
} anon_3_239;

typedef struct {
    anon_3_239 x0;
    anon_3_239 y0;
    unsigned int z0;
    float w;
    float h;
    float u;
    float v;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char a0;
    int flg;
} anon_2_239;

extern anon_0_239 wo_cursor[2];

void woCursorInit(int cno) {
    func_0011EEC0(&wo_cursor[cno], 0x28);
}

void woCursorAct(int cno) {
    anon_0_239 *wk;
    
    wk = &wo_cursor[cno];
    wk->counter++;
}

int woCursorGet(int cno, unsigned int flag) {
    anon_0_239 *wk;

    wk = &wo_cursor[cno];
    if (flag & 1) {
        return wk->cur_x;
    }
    if (flag & 2) {
        return wk->cur_y;
    }
    return 0;
}

void woCursorInc(int cno, unsigned int flag) {
    anon_0_239 *wk;

    wk = &wo_cursor[cno];
    if (flag & 1) {
        if (++wk->cur_x >= wk->item_x) {
            wk->cur_x = 0;
        }
    }
    if (flag & 2) {
        if (++wk->cur_y >= wk->item_y) {
            wk->cur_y = 0;
        }
    }
}

void woCursorDec(int cno, unsigned int flag) {
    anon_0_239 *wk;

    wk = &wo_cursor[cno];
    if (flag & 1) {
        if (--wk->cur_x < 0) {
            wk->cur_x = wk->item_x - 1;
        }
    }
    if (flag & 2) {
        if (--wk->cur_y < 0) {
            wk->cur_y = wk->item_y - 1;
        }
    }
}

void woCursorSet(int cno, unsigned int flag, int val) {
    anon_0_239 *wk;

    wk = &wo_cursor[cno];
    if (flag & 1) {
        wk->cur_x = val % wk->item_x;
    }
    if (flag & 2) {
        wk->cur_y = val % wk->item_y;
    }
}

void woCursorDraw(int cno) {
    anon_2_239 sprt;
    anon_1_239 info;
    anon_0_239 *wk;
    int bri;
    int anim_no;
    int depth;

    wk = &wo_cursor[cno];
    anim_no = (wk->counter >> 2) % 4;
    func_00127F60(&info, 0xC4);
    sprt.flg = 0;
    sprt.flg |= 0x100;
    sprt.x0.fd = wk->pos_x + wk->cur_x * wk->dist_x;
    sprt.y0.fd = wk->pos_y + wk->cur_y * wk->dist_y;
    depth = wk->depth_z;
    sprt.z0 = depth;
    sprt.u = anim_no * 10;
    sprt.w = 10.0f;
    sprt.h = 12.0f;
    sprt.v = 0.0f;
    bri = func_0011F4C0(depth);
    sprt.r0 = bri;
    sprt.g0 = bri;
    sprt.b0 = bri;
    sprt.a0 = 0x80;
    func_00123CF0(&sprt);
}
