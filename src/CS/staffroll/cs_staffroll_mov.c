typedef struct {
                unsigned char *data;
                int datasize;
                unsigned int width;
                unsigned int height;
                unsigned int nframes;
                unsigned int frame_cnt;
                unsigned int mbx;
                unsigned int mby;
                unsigned int tbp;
                unsigned int tbw;
                int tw;
                int th;
} anon_0_188;

typedef enum {
    SRE_MV_STEP_INIT = 0,
    SRE_MV_STEP_READ = 1,
    SRE_MV_STEP_WAIT = 2,
    SRE_MV_STEP_TERMINATE = 3,
} anon_x3552c7_188;

typedef struct {
                float timer;
                float topPos;
                float startStrPos;
                unsigned short startStrNo;
                short picseqNo;
                short picseqCom;

                float picseqTimer;
                float picseqduration;
                int movie_timer;
                int tex_id;
                int start_flg;
                int fft_kind;
                int fft_colset[3];
                int fft_type;
                int fft_reset;
                int u[4];
                int v[4];
                int fft_bright;
                int mvseq_no;
                int movie_bright;
                int read_time;
                int read_flag;
                int disp_pic : 1;
                int disp_mov : 1;
                int disp_roll : 1;
                int disp_padding : 29;
} anon_1_188;

typedef enum {
    SRE_MVREAD_STEP_WAIT = 0,
    SRE_MVREAD_STEP_INIT = 1,
    SRE_MVREAD_STEP_READ = 2,
    SRE_MVREAD_STEP_SET = 3,
    SRE_MVREAD_STEP_TERMINATE = 4,
} anon_x355751_188;

typedef union {
                int id;
                float fd;
} anon_2_188;

typedef struct {
                anon_2_188 x0;
                anon_2_188 y0;
                anon_2_188 x1;
                anon_2_188 y1;
                anon_2_188 x2;
                anon_2_188 y2;
                anon_2_188 x3;
                anon_2_188 y3;
                unsigned int z0;
                unsigned int z1;
                unsigned int z2;
                unsigned int z3;
                float s0;
                float t0;
                float q0;
                float s1;
                float t1;
                float q1;
                float s2;
                float t2;
                float q2;
                float s3;
                float t3;
                float q3;
                unsigned char r0;
                unsigned char g0;
                unsigned char b0;
                unsigned char a0;
                int flg;
} anon_3_188;

typedef struct {
                float time;
                short MvNo;
} anon_4_188;

typedef struct {
                anon_2_188 x0;
                anon_2_188 y0;
                anon_2_188 x1;
                anon_2_188 y1;
                unsigned int z0;
                unsigned int z1;
                unsigned char r0;
                unsigned char g0;
                unsigned char b0;
                unsigned char a0;
                int flg;
} anon_5_188;

static int isreMainStep;
static int isreReadStep;
static int current_buff;
unsigned char *sre_ip[11];
anon_4_188 sre_mvseq[12];
int mv_enable;
anon_x355751_188 SRE_MVREAD_STEP;
anon_x3552c7_188 SRE_MV_STEP;

#define D_0112C380 0x0112C380

static int isreMainStep = 0;
static int isreReadStep = 0;
static int current_buff = 0;

#define D_002DD418 ((unsigned char *)0x002DD418)

unsigned char *sre_ip[11] = {
    D_002DD418 + 8,
    D_002DD418 + 16,
    D_002DD418 + 24,
    D_002DD418 + 32,
    D_002DD418 + 40,
    D_002DD418 + 48,
    D_002DD418 + 56,
    D_002DD418 + 64,
    D_002DD418 + 72,
    D_002DD418 + 80,
    D_002DD418 + 88,
};

int mv_enable = 0;

anon_4_188 sre_mvseq[12] = {
    {239.76F, 0},
    {638.0934F, 1},
    {1036.4268F, 2},
    {1434.76F, 3},
    {1833.0935F, 4},
    {2231.4265F, 5},
    {2629.76F, 6},
    {3028.093F, 7},
    {3426.427F, 8},
    {3824.76F, 9},
    {4223.093F, 10},
    {4621.4263F, 11},
};

void sceGsSyncPath(int a, int b);
int func_0011DE80(void);
int func_0011E090(void *tbl, unsigned char *addr);
void func_0011F600(int a);
void *func_0011F8C0(int a);
void func_0011F8E0(int a);
unsigned int func_0011F930(int a);
void func_0011F960(int a);
void func_0011F9A0(int a);
void func_0011FBC0(int a);
void func_0011FC90(int a, int b, int c, int d);
void func_0011FE80(int a);
void func_0011FFE0(int a, int b, int c, int d, int e);
void func_001205E0(int a);
void func_001234E0(anon_3_188 *ft);
void func_00125180(unsigned long a, int b, int c);
void func_001267B0(int a, int b);
void func_001BCFA8(char *fmt, ...);
float csStaffRollPicGetBase(void);

void csStaffRollMovieDraw(anon_1_188 *pstf) {
    anon_0_188 *info;
    anon_3_188 ft4;
    static int MovDraw;

    if ((pstf->movie_timer & 1) || MovDraw != 0) {
        func_0011F600(current_buff);
        if (func_0011F930(current_buff) < 0xEF) {
            func_0011F8E0(current_buff);
        }
        MovDraw = 0;
    } else {
        MovDraw = 1;
    }
    func_0011F960(current_buff);
    sceGsSyncPath(0, 0);
    info = func_0011F8C0(current_buff);
    func_00125180((unsigned long)info->tbp | ((unsigned long)info->tbw << 14) |
                      ((unsigned long)info->tw << 26) | ((unsigned long)info->th << 30) |
                      0x2000000400000000, 6, 0);
    ft4.flg = 0;
    ft4.r0 = pstf->movie_bright;
    ft4.g0 = pstf->movie_bright;
    ft4.b0 = pstf->movie_bright;
    ft4.a0 = 0x80;
    ft4.x0.fd = -8.0F;
    ft4.y0.fd = -180.0F;
    ft4.z0 = 0x106;
    ft4.x1.fd = 312.0F;
    ft4.y1.fd = -180.0F;
    ft4.z1 = 0x106;
    ft4.x2.fd = -8.0F;
    ft4.y2.fd = 44.0F;
    ft4.z2 = 0x106;
    ft4.x3.fd = 312.0F;
    ft4.y3.fd = 44.0F;
    ft4.z3 = 0x106;
    ft4.s0 = 0.001953125F;
    ft4.t0 = 0.00390625F;
    ft4.q0 = 1.0F;
    ft4.s1 = ((float)info->width - 1.0F) / 512.0F;
    ft4.t1 = 0.00390625F;
    ft4.q1 = 1.0F;
    ft4.s2 = 0.001953125F;
    ft4.t2 = ((float)info->height - 1.0F) / 256.0F;
    ft4.q2 = 1.0F;
    ft4.s3 = ((float)info->width - 1.0F) / 512.0F;
    ft4.t3 = ((float)info->height - 1.0F) / 256.0F;
    ft4.q3 = 1.0F;
    func_001234E0(&ft4);
    ft4.r0 = 0x80;
    ft4.g0 = 0x80;
    ft4.b0 = 0x80;
    ft4.a0 = (int)(8.0F * csStaffRollPicGetBase() / 128.0F);
    ft4.x0.fd = -320.0F;
    ft4.y0.fd = -240.0F;
    ft4.z0 = 0x101;
    ft4.x1.fd = 320.0F;
    ft4.y1.fd = -240.0F;
    ft4.z1 = 0x101;
    ft4.x2.fd = -320.0F;
    ft4.y2.fd = 240.0F;
    ft4.z2 = 0x101;
    ft4.x3.fd = 320.0F;
    ft4.y3.fd = 240.0F;
    ft4.z3 = 0x101;
    func_001234E0(&ft4);
}

int csStaffRollMovieRead(int idx, anon_1_188 *pstf) {
    int read_buff;
    int ret = 0;

    read_buff = (current_buff + 1) % 2;
    switch (isreReadStep) {
    case 0:
        if (func_0011DE80() != 0) {
            isreReadStep = 1;
        }
        break;
    case 1:
        if (func_0011E090(sre_ip[idx], (unsigned char *)(D_0112C380 + read_buff * 0x2C5000)) != 0) {
            isreReadStep = 2;
        }
        break;
    case 2:
        if (func_0011DE80() != 0) {
            isreReadStep = 3;
        }
        break;
    case 3:
        isreReadStep = 4;
        func_0011FE80(0x0102C380);
        func_0011FC90(D_0112C380 + read_buff * 0x2C5000, read_buff,
                      (unsigned int)(9728.0F + 1200.9961F * read_buff), 0x100000);
        func_0011FBC0(read_buff);
        func_0011F9A0(read_buff);
        break;
    case 4:
        ret = 1;
        break;
    }
    if (ret == 0 && idx == 0) {
        func_001205E0(0);
    }
    return ret;
}

int csStaffRollMovieMain(anon_1_188 *pstf) {
    int ret = 0;

    switch (isreMainStep) {
    case 0:
        isreMainStep = 1;
        isreReadStep = 0;
    case 1:
        if (csStaffRollMovieRead(sre_mvseq[pstf->mvseq_no].MvNo, pstf) != 0) {
            pstf->start_flg = 1;
            isreMainStep = 2;
        case 2:
            if (pstf->timer < 692.307F) {
                break;
            }
            if (pstf->movie_timer >= 0x1E1 ||
                (pstf->mvseq_no == 0 && pstf->movie_timer == 0)) {
                func_001BCFA8("[%d >= %d]\n", (unsigned int)pstf->timer,
                              (unsigned int)sre_mvseq[pstf->mvseq_no].time);
                mv_enable = 1;
                current_buff = (current_buff + 1) % 2;
                pstf->mvseq_no += 1;
                pstf->movie_timer = 0;
                if (sre_mvseq[pstf->mvseq_no].MvNo == 0xB) {
                    isreMainStep = 3;
                } else {
                    isreMainStep = 0;
                }
            }
        }
        break;
    case 3:
        if (pstf->movie_timer == 0x1DF) {
            mv_enable = 0;
            func_001267B0(0, 0);
            pstf->movie_timer += 1;
            func_001BCFA8("movie_finish\n");
        }
        if (pstf->timer < sre_mvseq[pstf->mvseq_no].time) {
            break;
        }
        ret = 1;
        break;
    }
    if (mv_enable != 0) {
        csStaffRollMovieDraw(pstf);
        pstf->movie_timer += 1;
    }
    return ret;
}

void csStaffRollMovieInit(anon_1_188 *pstf) {
    isreMainStep = 0;
    isreReadStep = 0;
    pstf->mvseq_no = 0;
    mv_enable = 0;
    pstf->movie_timer = 0;
    pstf->start_flg = 0;
    pstf->movie_bright = 0x80;
    func_001267B0(0x540, 0);
    func_0011FFE0(0x100000, 0xF1, 2, 0x140, 0xF0);
}

static void probe_mov(anon_5_188 *p) {
    p->flg = 1;
}
