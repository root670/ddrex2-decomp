typedef float sceVu0FMATRIX[4][4] __attribute__((aligned(16)));

struct _GsCOORDINATE2;

typedef struct {
    unsigned int type;
    unsigned int *vert_top;
    unsigned int n_vert;
    unsigned int n_calcv;
    unsigned int n_sharev;
    unsigned int *normal_top;
    unsigned int n_normal;
    unsigned int n_calcn;
    unsigned int n_sharen;
    unsigned int *primitive_top;
    unsigned int *preset_top;
    unsigned int n_primitive;
} anon_0_17;

typedef struct {
    anon_0_17 *region_top;
    unsigned int n_region;
    int scale;
} anon_1_17;

typedef struct {
    unsigned int id;
    unsigned int flag;
    unsigned int nobj;
    unsigned int nregion;
    unsigned int st_idxv;
    unsigned int st_idxn;
    unsigned int *sharedv_top;
    unsigned int *sharedn_top;
} anon_2_17;

typedef struct {
    unsigned short offset;
} anon_14_17;

typedef struct {
    unsigned short shift_bit;
    anon_14_17 tbl[1];
} anon_15_17;

typedef struct {
    unsigned char kind;
    unsigned char pad[3];
    anon_15_17 data;
} anon_3_17;

typedef struct {
    unsigned char id;
    unsigned char format;
    unsigned char hastrans;
    unsigned char parent_id;
    unsigned int nbwave;
    anon_3_17 **offset;
} anon_4_17;

typedef struct {
    unsigned char u0;
    unsigned char v0;
    unsigned short clut;
    unsigned char u1;
    unsigned char v1;
    unsigned short tpage;
    unsigned char u2;
    unsigned char v2;
    unsigned short p0;
} anon_6_17;

typedef struct {
    unsigned int size;
    unsigned short nbparts;
    unsigned short nbframe;
    anon_4_17 **offset;
} anon_7_17;

typedef struct {
    char *name;
    anon_7_17 *offset;
} anon_8_17;

typedef struct {
    unsigned int attribute;
    struct _GsCOORDINATE2 *coord2;
    unsigned int *tmd;
    unsigned int *packet;
    unsigned int id;
} anon_11_17;

typedef struct {
    int vx;
    int vy;
    int vz;
    int pad;
} anon_12_17;

typedef struct {
    unsigned int tag;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char code;
    short x0;
    short y0;
    unsigned char u0;
    unsigned char v0;
    unsigned short clut;
    unsigned char r1;
    unsigned char g1;
    unsigned char b1;
    unsigned char p1;
    short x1;
    short y1;
    unsigned char u1;
    unsigned char v1;
    unsigned short tpage;
    unsigned char r2;
    unsigned char g2;
    unsigned char b2;
    unsigned char p2;
    short x2;
    short y2;
    unsigned char u2;
    unsigned char v2;
    unsigned short pad2;
} anon_13_17;

typedef struct {
    short vx;
    short vy;
    short vz;
    short pad;
} anon_16_17;

typedef struct {
    unsigned int tag;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char code;
    short x0;
    short y0;
    unsigned char r1;
    unsigned char g1;
    unsigned char b1;
    unsigned char pad1;
    short x1;
    short y1;
    unsigned char r2;
    unsigned char g2;
    unsigned char b2;
    unsigned char pad2;
    short x2;
    short y2;
} anon_17_17;

typedef struct {
    float x;
    float y;
    float z;
    unsigned int disp : 1;
} anon_5_17;

typedef struct {
    short m[3][3];
    int t[3];
} anon_9_17;

typedef struct {
    char magic[2];
    short nbmdt;
    int reserve;
    anon_8_17 motion[1];
} anon_10_17;

typedef struct {
    anon_12_17 scale;
    anon_16_17 rotate;
    anon_12_17 trans;
} anon_19_17;

struct _tag_cFilepackData {
    unsigned int address;
    unsigned int size;
};

typedef struct {
    struct _tag_cFilepackData tblFilepack[2];
    short loadstep;
    char loadpid;
    char loadmid;
    unsigned int topaddr;
    unsigned int readaddr;
    unsigned int pdataaddr;
    short ploadstep;
    short chgstep[3];
    unsigned int *tex_buff[3];
    unsigned int *nmd_buff[3];
    char nmd_loaded_id[3];
    char mot_loaded_id[3][2];
    char data_buf_broken;
    char playmode;
    char toon;
    char shadow;
    char effect;
    char floor;
    char unison;
    char chr_num;
    char chr_id[3];
    char mot_id[3];
    unsigned int *mot_adr[3];
    int base_bri;
    int bright;
    int pid_bri[3];
    unsigned int vcnt;
    int common_rand;
} anon_18_17;

struct _GsCOORDINATE2 {
    unsigned int flg;
    anon_9_17 coord;
    anon_9_17 workm;
    anon_19_17 *param;
    struct _GsCOORDINATE2 *super;
    struct _GsCOORDINATE2 *sub;
};

struct dancer_model_w {
    anon_11_17 obj[30];
    int entry[17];
    unsigned int model;
    unsigned int *packet;
    unsigned int *header;
    sceVu0FMATRIX m[17];
    unsigned int *prim_tbl;
    float dist;
    float scale;
    float sscale;
    float x;
    float y;
    float z;
    short winkcnt;
    unsigned short chara;
    char hide;
    float sel_ox;
    float sel_oy;
    float sel_oz;
    unsigned char id;
    unsigned char pad[2];
    anon_5_17 *einf;
};

struct one_motion_w {
    int m_id;
    int frame;
    unsigned int state;
    anon_7_17 *mdata;
    int weight;
};

struct dancer_motion_w {
    struct _GsCOORDINATE2 coord2[18];
    unsigned char model_change[16];
    int cur_dance_id;
    int last_dance_id;
    struct one_motion_w motion[2];
    anon_10_17 *mpack;
    int cur_p_counter;
    int last_p_counter;
    int dance_class;
    float adj_x;
    float adj_z;
};

typedef struct {
    struct dancer_motion_w motion_w[3];
    struct dancer_model_w model_w[3];
    unsigned int mdl_data[3][45568];
    unsigned int mot_data[3][86784];
    unsigned int packet_w[3][65536];
} anon_20_17;

static unsigned int chara_lst[2][16] = { 0 };
anon_18_17 *dancer_ctrl_w;
anon_20_17 *dancer_data_w;

void func_001B7C30(void *p, int size);
int func_001BDAB8(void);
float get_dancer_scale(int chara);
unsigned int *get_primdt_tbl(int chara);
int get_chara_lst_id(int chara);
static void NMDMapModelingData(unsigned int *p);
unsigned int *NMDPresetObject(anon_11_17 *objp, unsigned int *addr);
static unsigned int *NMDPrsetPacketG3(unsigned int *dop, unsigned int prim_no);
static unsigned int *NMDPrsetPacketGT3(unsigned int *dop, unsigned int prim_no, anon_6_17 *prsp);

static unsigned int *NMDPrsetPacketG3(unsigned int *dop, unsigned int prim_no) {
    anon_17_17 *g3p;
    int i;

    g3p = (anon_17_17 *)dop;
    for (i = 0; i < prim_no; i++) {
        g3p[0].tag = 0x30;
        ((unsigned int *)g3p)[1] = 0;
        ((unsigned int *)g3p)[2] = 0;
        ((unsigned int *)g3p)[3] = 0;
        ((unsigned int *)g3p)[4] = 0;
        ((unsigned int *)g3p)[5] = 0;
        ((unsigned int *)g3p)[6] = 0;
        g3p[1].tag = 0x30;
        ((unsigned int *)g3p)[8] = 0;
        ((unsigned int *)g3p)[9] = 0;
        ((unsigned int *)g3p)[10] = 0;
        ((unsigned int *)g3p)[11] = 0;
        ((unsigned int *)g3p)[12] = 0;
        ((unsigned int *)g3p)[13] = 0;
        g3p += 2;
    }
    return (unsigned int *)g3p;
}

static unsigned int *NMDPrsetPacketGT3(unsigned int *dop, unsigned int prim_no, anon_6_17 *prsp) {
    anon_13_17 *gt3p;
    int i;
    int j;

    gt3p = (anon_13_17 *)dop;
    for (i = 0; i < prim_no; i++) {
        for (j = 0; j < 2; j++) {
            gt3p->tag = 0x34;
            *(unsigned int *)&gt3p->r0 = 0;
            *(unsigned int *)&gt3p->x0 = 0;
            *(unsigned int *)&gt3p->u0 = *(unsigned int *)&prsp->u0;
            *(unsigned int *)&gt3p->r1 = 0;
            *(unsigned int *)&gt3p->x1 = 0;
            *(unsigned int *)&gt3p->u1 = *(unsigned int *)&prsp->u1;
            *(unsigned int *)&gt3p->r2 = 0;
            *(unsigned int *)&gt3p->x2 = 0;
            *(unsigned int *)&gt3p->u2 = *(unsigned int *)&prsp->u2;
            gt3p++;
        }
        prsp++;
    }
    return (unsigned int *)gt3p;
}

static void NMDMapModelingData(unsigned int *p) {
    anon_1_17 *op;
    anon_0_17 *rp;
    anon_2_17 *hp;
    int nobj;
    int i;
    int j;
    unsigned int oadr;
    unsigned int radr;

    hp = (anon_2_17 *)p;
    hp->st_idxv = 0;
    hp->st_idxn = 0;
    if (hp->flag != 0) {
        return;
    }
    op = (anon_1_17 *)&hp[1];
    oadr = (unsigned int)op;
    hp->flag = 1;
    hp->sharedv_top = (unsigned int *)((unsigned int)p + (unsigned int)hp->sharedv_top);
    hp->sharedn_top = (unsigned int *)((unsigned int)p + (unsigned int)hp->sharedn_top);
    nobj = hp->nobj;
    for (i = 0; i < nobj; i++) {
        op->region_top = (anon_0_17 *)(oadr + (unsigned int)op->region_top);
        rp = op->region_top;
        radr = (unsigned int)rp;
        for (j = 0; j < op->n_region; j++) {
            rp->vert_top = (unsigned int *)(radr + (unsigned int)rp->vert_top);
            rp->normal_top = (unsigned int *)(radr + (unsigned int)rp->normal_top);
            rp->primitive_top = (unsigned int *)(radr + (unsigned int)rp->primitive_top);
            rp->preset_top = (unsigned int *)(radr + (unsigned int)rp->preset_top);
            rp++;
        }
        op++;
    }
}

unsigned int *NMDPresetObject(anon_11_17 *objp, unsigned int *addr) {
    unsigned int *dop;
    unsigned int *prim_top;
    anon_1_17 *nodp;
    anon_0_17 *nrdp;
    int i;
    int type;

    i = 0;
    nodp = (anon_1_17 *)objp->tmd;
    nrdp = nodp->region_top;
    objp->packet = addr;
    dop = addr;
    for (;;) {
        type = (unsigned char)nrdp->type;
        prim_top = dop;
        dop[1] = nrdp->n_primitive;
        dop += 2;
        switch (type) {
        case 0x30:
            dop = NMDPrsetPacketG3(dop, nrdp->n_primitive);
            break;
        case 0x34:
            dop = NMDPrsetPacketGT3(dop, nrdp->n_primitive, (anon_6_17 *)nrdp->preset_top);
            break;
        }
        i++;
        if (i >= nodp->n_region) {
            break;
        }
        prim_top[0] = (unsigned int)dop;
        nrdp++;
    }
    prim_top[0] = 0;
    return dop;
}

void dancer_model_setup(int pid, int chara) {
    struct dancer_model_w *mdl;
    struct dancer_motion_w *mot;
    unsigned char *model_list;
    unsigned int *cur_packet;
    int obj_id;
    int parts_id;
    int num_of_obj;

    mot = &dancer_data_w->motion_w[pid];
    mdl = &dancer_data_w->model_w[pid];
    func_001B7C30(mdl, 0x730);
    NMDMapModelingData(dancer_ctrl_w->nmd_buff[pid]);
    mdl->packet = dancer_data_w->packet_w[pid];
    mdl->header = dancer_ctrl_w->nmd_buff[pid];
    mdl->model = (unsigned int)dancer_ctrl_w->nmd_buff[pid] + 0x20;
    mdl->chara = chara;
    mdl->winkcnt = func_001BDAB8() % 120 + 60;
    mdl->scale = get_dancer_scale(chara) * 0.01f;
    mdl->prim_tbl = get_primdt_tbl(chara);
    mdl->hide = 0;
    model_list = (unsigned char *)chara_lst[get_chara_lst_id(chara)];
    cur_packet = mdl->packet;
    parts_id = 0;
    num_of_obj = model_list[0];
    for (parts_id = 0; parts_id < 16; parts_id++) {
        mdl->entry[parts_id] = 0x1E;
    }
    if (0 < num_of_obj) {
        obj_id = 0;
        do {
            mdl->obj[obj_id].tmd = (unsigned int *)(mdl->model + obj_id * 0xC);
            cur_packet = NMDPresetObject((anon_11_17 *)&mdl->obj[obj_id], cur_packet);
            parts_id = model_list[1];
            if (obj_id < mdl->entry[parts_id]) {
                mdl->entry[parts_id] = obj_id;
            }
            mdl->obj[obj_id].coord2 = mot->coord2 + parts_id + 2;
            obj_id++;
            model_list += 2;
        } while (obj_id < num_of_obj);
    }
    mdl->entry[16] = num_of_obj;
}
