#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

typedef float FVEC4[4];
typedef float FMAT4[4][4];

typedef struct {
    float ofs_x;
    float ofs_y;
    int step;
    void *doll;
} anon_0_98;
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
} anon_1_98;
typedef struct {
    unsigned char n;
    unsigned char cur[2];
    unsigned char **str;
} anon_3_98;
typedef struct {
    void *loadaddr;
    int doll_p_counter;
    unsigned char max;
    unsigned char fpanel_max;
    unsigned char step;
    unsigned char dancing;
    unsigned char cur[2];
    float fpanel_x[2];
    float fpanel_y[2];
    float cx[3];
    float cy[3];
    float cz[3];
    float adj_y[3];
    float timer;
    FVEC4 cam_p __attribute__((aligned(16)));
    FVEC4 eye_p;
    void *fpanel;
} anon_5_98;
typedef struct {
    unsigned char cur;
    int timer;
    void *item;
} anon_7_98;
typedef struct {
    unsigned char cur;
    unsigned char max;
    void *item;
    int timer;
} anon_9_98;
typedef struct {
    unsigned char end_num;
    unsigned char decide;
    unsigned char cancel;
    unsigned char cur[2];
    unsigned char rand_id[2];
    float repcnt[2];
    int timer;
    void *item;
    void *entry;
} anon_11_98;
typedef struct {
    float ftimer;
    float repcnt;
    float scr_sp;
    float scr_ct;
    unsigned int lr_obj_id;
    void *lr;
    void *ud;
    void *radar;
    void *entry;
    void *base;
    void *sort_obj;
    void *scr;
    void *opt;
    void *edmc;
    unsigned char *th_up_addr;
    unsigned char *th_dw_addr;
    unsigned char ud_start;
    unsigned char ud_end;
    unsigned char cur_ud[2];
    unsigned char cur_ud_old[2];
    unsigned char cur_ud_edi_old[2];
    short cur_lr;
    short old_d_num;
    short old_lr;
    short ena_num;
    short sel_tab[128];
    short base_num;
    short base_tab[250];
    short kind_key[50];
    short kind_ofs[50];
    short kind_len[50];
    short abc_open;
    unsigned char edit_sel;
    unsigned char sort;
    unsigned char step;
    unsigned char rlt_stop_mode;
    unsigned char rlt_turn_num;
    unsigned char rlt_remain;
    float rlt_t;
    float rlt_wait;
    char mcard_type;
    char msg_id;
    char yesno;
    char lib_num;
    char lib_sel_num;
    unsigned char lib_loaded;
    short edi_start;
    unsigned char sn_f;
    float sn_t;
} anon_25_98;
typedef struct {
    int timer;
    unsigned char cur[2];
    unsigned char auto_f[2];
    float repcnt[2];
    void *item;
    void *win;
    anon_3_98 one[11];
} anon_6_98;
typedef struct {
    int value_ct[8];
    int score;
    int bonus;
    int oni_point;
    short dance_level;
    unsigned char is_fcombo;
    unsigned char is_newrec;
    int pnt;
} anon_20_98;
typedef struct {
    float ftimer;
    void *base;
    void *value;
    void *point;
    void *score;
    void *btn;
    unsigned char *th_addr;
    int total_pnt;
    int vo_code;
    short d_num;
    unsigned char push[2];
    unsigned char edi_str[11];
    unsigned char cheer;
    unsigned char vo_pid;
    anon_20_98 eva[2];
} anon_22_98;
typedef struct {
    FMAT4 wsm;
    unsigned char step;
    unsigned char step_s;
    unsigned char next_step;
    unsigned char qm_step;
    unsigned char pad_type;
    float fade_ct;
    int fade_kind;
    int tex_start;
    float quit_ct;
    unsigned char eye_step;
    unsigned char fade_step;
    unsigned char dp_alpha;
    unsigned char start_pid;
    unsigned char prev_step;
    unsigned int flag;
    void *btn;
    unsigned int btn_obj_id;
    unsigned char *str_addr;
    unsigned char str_buf[256];
    anon_5_98 doll;
    anon_7_98 eyetoy;
    anon_9_98 style;
    anon_11_98 chara;
    anon_25_98 music;
    anon_6_98 option;
    anon_22_98 result;
} anon_4_98;
typedef struct {
    int (*appr)(void *);
    int (*exec)(void *);
    int (*disap)(void *);
    int (*disp)(void *);
} anon_24_98;
typedef struct {
    short x;
    short y;
    short w;
    short h;
} anon_27_98;
extern anon_24_98 fp_doll_objf;
extern anon_24_98 fp_fpanel_objf;
extern anon_5_98 *dw;
extern anon_4_98 *fpw;
extern anon_11_98 *chw;
extern anon_7_98 *etw;
extern anon_9_98 *stw;
extern anon_1_98 *gs3d;
extern struct g_game_w g_game_w;
extern struct _tag_cDDR8SaveData SaveData;

void func_0012D070(int tex_no);
void fp_sel_tex_set(void *info, int _id);
int fp_get_doll_num(int pid);
void *co_obj_del(void *del_ow);
void *co_obj_set(void *func, void *init, unsigned char pri);
int co_obj_own_ini_flag(void *work_p);
void fp_prim_packet_set_sp(anon_27_98 pos, anon_27_98 uv, int pri,
                           unsigned char alpha, unsigned char bri);
void *ps2dancerInit(void *workaddr, int playmode);
void ps2dancerPdataLoadInit(void *pdataaddr);
int ps2dancerPdataLoadStep(void);
void ps2dancerResetEntry(void);
void ps2dancerEntry(int pid, int chara);
void ps2dancerLoadInit(void *readtmpaddr);
int ps2dancerLoadStep(void);
void ps2dancerSetup(void);
void ps2dancerCameraInit(float cx, float cy, float scale);
void ps2dancerSetPlayCounter(int pid, int cur_p_counter);
void ps2dancerChange(int pid, int chara);
void ps2dancerSetPidBright(int pid, int bright);
void ps2dancerSetToon(int sw);
void ps2dancerSetFloor(int sw);
void ps2dancerDispStep(void);

static int fp_foot_panel_disp(void *w);
static int fp_foot_panel_disap(void *w);
static int fp_foot_panel_exec(void *w);
static int fp_foot_panel_apper(void *w);
static int fp_doll_disp(void);
static int fp_doll_exec(void);
static void fp_doll_set_pos(void);
void fp_doll_fpanel_update(void);
void fp_doll_cam_set(int pid, float mdl_x, float mdl_z);
int fp_doll_load(void);
void fp_doll_init(void);

anon_24_98 fp_doll_objf = {
    0,
    (int (*)(void *))fp_doll_exec,
    0,
    (int (*)(void *))fp_doll_disp,
};
anon_24_98 fp_fpanel_objf = {
    fp_foot_panel_apper,
    fp_foot_panel_exec,
    fp_foot_panel_disap,
    fp_foot_panel_disp,
};

static int fp_foot_panel_disp(void *w) {
    int i;
    anon_0_98 *fw = (anon_0_98 *)w;
    anon_27_98 pos;
    anon_27_98 uv;
    for (i = 0; i < dw->fpanel_max; i++) {
        if (222.0f + (dw->fpanel_x[i] + fw->ofs_x) >= -320.0f) {
            if (g_game_w.network_flag & 1) {
                func_0012D070(0x77);
            } else {
                fp_sel_tex_set(0, fpw->tex_start + 4);
            }
            pos.x = (short)(dw->fpanel_x[i] + fw->ofs_x);
            pos.y = (short)(dw->fpanel_y[i] + fw->ofs_y);
            pos.w = (short)(222.0f + (dw->fpanel_x[i] + fw->ofs_x));
            pos.h = (short)(66.0f + (dw->fpanel_y[i] + fw->ofs_y));
            uv.x = 1 + i * 222;
            uv.y = 1;
            uv.w = 222 + i * 222;
            uv.h = 0x42;
            fp_prim_packet_set_sp(pos, uv, 0x110, 0x80, 0x80);
        }
    }
    return 0;
}

static int fp_foot_panel_disap(void *w) {
    anon_0_98 *fw = (anon_0_98 *)w;
    if (!co_obj_own_ini_flag(w)) {
        dw->timer = 0;
    }
    dw->timer += 1.0f;
    fw->ofs_y = (-1.0f * (dw->timer * dw->timer)) / 2.0f;
    fw->ofs_x = (-4.0f * (dw->timer * dw->timer)) / 2.0f;
    if (dw->timer >= 16.0f) {
        co_obj_del(fw->doll);
        return 1;
    }
    return 0;
}

static int fp_foot_panel_exec(void *w) {
    if (!co_obj_own_ini_flag(w)) {
        dw->timer = 0;
    }
    return 0;
}

static int fp_foot_panel_apper(void *w) {
    anon_0_98 *fw = (anon_0_98 *)w;
    if (!co_obj_own_ini_flag(w)) {
        fp_doll_fpanel_update();
        dw->timer = 16.0f;
        dw->dancing = 0;
        fw->doll = co_obj_set(&fp_doll_objf, 0, 0x80);
    }
    dw->timer -= 1.0f;
    fw->ofs_y = (-1.0f * (dw->timer * dw->timer)) / 2.0f;
    fw->ofs_x = (-4.0f * (dw->timer * dw->timer)) / 2.0f;
    if (dw->timer <= 0.0f) {
        fw->ofs_x = 0.0f;
        fw->ofs_y = 0.0f;
        dw->timer = 0.0f;
        dw->dancing = 1;
        return 1;
    }
    return 0;
}

static int fp_doll_disp(void) {
    int bright[3] = {100, 100, 0};
    int i;
    int ch_id;
    if (!SaveData.Option.DollDisp || etw->cur) {
        bright[0] = bright[1] = 0;
    } else {
        bright[0] = bright[1] = 100;
    }
    dw->doll_p_counter += 0x28;
    if (dw->doll_p_counter >= 0xFFFFF) {
        dw->doll_p_counter = 0;
        ps2dancerSetup();
    }
    for (i = 0; i < 3; i++) {
        if (i == 2) {
            ch_id = 0;
        } else {
            if (fp_get_doll_num(i) == 0x2E) {
                ch_id = chw->rand_id[i];
                bright[i] = 0;
            } else {
                ch_id = fp_get_doll_num(i);
            }
        }
        if (ch_id < 0x2D && !(SaveData.HideFlag[(ch_id + 0x46) >> 5] & (1 << ((ch_id + 0x46) & 0x1F)))) {
            ch_id = 0x2D;
        }
        if (i != 2) {
            if (ch_id >= 0x2D) {
                dw->adj_y[i] = 999.0f;
            } else {
                dw->adj_y[i] = 0.0f;
            }
        }
        if (dw->dancing) {
            ps2dancerSetPlayCounter(i, dw->doll_p_counter);
        } else {
            ps2dancerSetPlayCounter(i, dw->doll_p_counter & 0xFFF);
        }
        ps2dancerChange(i, ch_id);
        ps2dancerSetPidBright(i, bright[i]);
    }
    ps2dancerSetToon(0);
    ps2dancerSetFloor(0);
    ps2dancerDispStep();
    return 0;
}

static int fp_doll_exec(void) {
    float dx;
    float v;
    dx = dw->timer;
    if (dx > 0.0f) {
        v = -11.0f + (-0.3125f * (dx * dx)) / 2.0f;
        dw->eye_p[0] = v;
        dw->cam_p[0] = -16.0f + v;
        dw->eye_p[1] = (0.0625f * (dx * dx)) / 2.0f;
        dw->cam_p[1] = (0.0625f * (dx * dx)) / 2.0f;
    } else {
        dw->eye_p[0] = -11.0f;
        dw->cam_p[0] = -27.0f;
        dw->eye_p[1] = 0.0f;
        dw->cam_p[1] = 0.0f;
    }
    return 0;
}

static void fp_doll_set_pos(void) {
    float pos_xz[4][2] = {{0.0f, 70.0f}, {-6.4f, 70.0f}, {5.6f, 70.0f}, {999.0f, 999.0f}};
    unsigned char ref[5][3] = {{0, 3, 3}, {3, 0, 3}, {1, 2, 3}, {0, 0, 0}, {0, 0, 0}};
    unsigned char *cp;
    if (dw->max == 2) {
        cp = ref[2];
    } else if (fpw->pad_type == 0 || fpw->pad_type == 3) {
        cp = ref[0];
    } else {
        cp = ref[1];
    }
    dw->cx[0] = pos_xz[cp[0]][0];
    dw->cz[0] = pos_xz[cp[0]][1];
    dw->cx[1] = pos_xz[cp[1]][0];
    dw->cz[1] = pos_xz[cp[1]][1];
    dw->cx[2] = pos_xz[cp[2]][0];
    dw->cz[2] = pos_xz[cp[2]][1];
    dw->cy[1] = -20.0f;
    dw->cy[0] = -20.0f;
    dw->cy[2] = 999.0f;
    dw->adj_y[2] = 0.0f;
}

void fp_doll_fpanel_update(void) {
    int i;
    FVEC4 fpanel_si_pos = {60.0f, 356.0f, 0.0f, 1.0f};
    FVEC4 fpanel_vs_pos[2] = {
        {-22.0f, 356.0f, 0.0f, 1.0f},
        {137.0f, 367.0f, 0.0f, 1.0f},
    };
    FVEC4 fpanel_db_pos[2] = {
        {-12.0f, 356.0f, 0.0f, 1.0f},
        {137.0f, 367.0f, 0.0f, 1.0f},
    };
    FVEC4 *fv;
    switch (stw->cur) {
    case 1:
        dw->max = 2;
        fv = fpanel_vs_pos;
        dw->fpanel_max = 2;
        break;
    case 2:
        dw->max = 1;
        fv = fpanel_db_pos;
        dw->fpanel_max = 2;
        break;
    default:
        dw->max = 1;
        fv = &fpanel_si_pos;
        dw->fpanel_max = 1;
        break;
    }
    for (i = 0; i < dw->fpanel_max; i++) {
        dw->fpanel_x[i] = -320.0f + (*fv)[0];
        dw->fpanel_y[i] = -224.0f + (*fv)[1];
        fv++;
    }
    fp_doll_set_pos();
}

void fp_doll_cam_set(int pid, float mdl_x, float mdl_z) {
    gs3d->cam_p[0] = dw->cx[pid] + (mdl_x + dw->cam_p[0]);
    gs3d->eye_p[0] = dw->cx[pid] + (mdl_x + dw->eye_p[0]);
    gs3d->cam_p[1] = dw->adj_y[pid] + (dw->cam_p[1] + dw->cy[pid]);
    gs3d->eye_p[1] = dw->adj_y[pid] + (dw->eye_p[1] + dw->cy[pid]);
    gs3d->cam_p[2] = dw->cz[pid] + (mdl_z + dw->cam_p[2]);
    gs3d->eye_p[2] = mdl_z + dw->eye_p[2];
    gs3d->cam_p[3] = 0.0f;
}

int fp_doll_load(void) {
    int i;
    switch (dw->step) {
    case 0:
        if (!ps2dancerPdataLoadStep()) {
            return 0;
        }
        dw->step++;
        ps2dancerResetEntry();
        for (i = 0; i <= 1; i++) {
            ps2dancerEntry(i, 0);
        }
        ps2dancerEntry(2, 0);
        ps2dancerLoadInit(dw->loadaddr);
    case 1:
        if (ps2dancerLoadStep()) {
            ps2dancerSetup();
            ps2dancerCameraInit(0.0f, -100.0f, 0.7f);
            dw->eye_p[2] = -2.0f;
            dw->cam_p[2] = -2.0f;
            fp_doll_set_pos();
            dw->doll_p_counter = 0;
            return 1;
        }
        break;
    }
    return 0;
}

void fp_doll_init(void) {
    dw->step = 0;
    dw->loadaddr = ps2dancerInit(g_game_w.last_data_addr, 4);
    ps2dancerPdataLoadInit((void *)0x01874000);
}
