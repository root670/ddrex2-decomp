typedef void *(*sdstr3_siffunc)(unsigned int, void *, int);

struct _sif_rpc_data {
    void *paddr;
    unsigned int pid;
    int tid;
    unsigned int mode;
};

struct _sif_client_data {
    struct _sif_rpc_data rpcd;
    unsigned int command;
    void *buff;
    void *gp;
    void (*func)(void *);
    void *para;
    struct _sif_serve_data *serve;
};

struct _sif_serve_data {
    unsigned int command;
    sdstr3_siffunc func;
    void *buff;
    int size;
    sdstr3_siffunc cfunc;
    void *cbuff;
    int csize;
    struct _sif_client_data *client;
    void *paddr;
    unsigned int fno;
    void *receive;
    int rsize;
    int rmode;
    unsigned int rid;
    struct _sif_serve_data *link;
    struct _sif_serve_data *next;
    struct _sif_queue_data *base;
};

struct _sif_queue_data {
    int key;
    int active;
    struct _sif_serve_data *link;
    struct _sif_serve_data *start;
    struct _sif_serve_data *end;
    struct _sif_queue_data *next;
};

struct ThreadParam {
    int status;
    void (*entry)(void *);
    void *stack;
    int stackSize;
    void *gpReg;
    int initPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
    int waitType;
    int waitId;
    int wakeupCount;
};

struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

typedef struct {
    int Sect;
    int Size;
    int Adrs;
} anon_0_38;

typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} anon_1_38;

static int SdStr3EeReadUse = 0;
static int SdStr3EeReadDiv = 0;
static int SdStr3EeReadDivRest = 0;
int SdStr3KtSemaId;
struct SemaParam SdStr3KtSemaParam;
int SdStr3EeReadAllow;
int SdStr3SifRes[16];
int SdStr3EeReading;
int SdStr3EeReadStat;
int SdStr3EeReadBreak;
struct _sif_client_data sdstr3_sifbd;
anon_1_38 sdstr3_cdrmode;
int SdStr3EeReadThId;
anon_0_38 SdStr3EeRead;
void *_gp;
char ThStackER[4096];

int sceSifBindRpc(struct _sif_client_data *cd, unsigned int rpcnum, unsigned int mode);
int sceSifCallRpc(struct _sif_client_data *cd, unsigned int rpcnum, unsigned int mode,
                  void *send, unsigned int ssize, void *recv, unsigned int rsize,
                  void (*endfunc)(void *), void *endpara);
int sceSifCheckStatRpc(struct _sif_client_data *cd);
int sceCdRead(unsigned int lsn, unsigned int sectors, void *buf, anon_1_38 *mode);
int sceCdSync(int mode);
int sceCdDiskReady(int mode);
int func_0010B860(struct ThreadParam *p);
int StartThread(int thid, void *arg);
int func_0010BA60(struct SemaParam *p);
int iWakeupThread(int thid);
int func_0010BAA0(int semid);
int func_0010BAC0(int semid);
int func_0010BA90(int semid);
void func_0010BCE0(int mode);
void func_0010B980(void);

static void sdstr3_eeread_th(void *data);

static void sdstr3_ret(void *data)
{
    int res;

    while (1) {
        res = SdStr3SifRes[0];
        break;
    }
    if (res == 1)
        SdStr3EeReadAllow = 1;
    asm {
        sync
    }
    asm {
        ei
    }
}

static void sdstr3_eeread_th(void *data)
{
    anon_0_38 *info;
    int step;
    int div;
    int divrest;
    int sect;
    int size;
    int adrs;
    int sum;

    info = (anon_0_38 *)data;
    step = 0;
    div = 0;
    divrest = 0;
    sect = 0;
    size = 0;
    adrs = 0;
    sum = 0;
    for (;;) {
        if (SdStr3EeReadStat == 0) {
            step = 0;
            func_0010B980();
            continue;
        }
        switch (step) {
        case 0:
            div = SdStr3EeReadDiv;
            sect = info->Sect;
            adrs = info->Adrs;
            divrest = SdStr3EeReadDivRest;
            if (div == 0) {
                size = info->Size;
            }
            else {
                if (div + divrest < info->Size) {
                    size = div;
                }
                else {
                    size = info->Size;
                }
            }
            sum = 0;
            step++;
        case 1:
            if (SdStr3EeReadBreak == 1) {
                step = 7;
                break;
            }
            SdStr3EeReadAllow = 0;
            if (sceSifCheckStatRpc(&sdstr3_sifbd) != 0)
                break;
            func_0010BCE0(0);
            if (sceSifCallRpc(&sdstr3_sifbd, 1, 1, 0, 0, SdStr3SifRes, 0x40,
                              (void (*)(void *))sdstr3_ret, SdStr3SifRes) == 0)
                step++;
            break;
        case 2:
            if (SdStr3EeReadAllow == 1) {
                step++;
                break;
            }
            if (sceSifCheckStatRpc(&sdstr3_sifbd) != 0)
                break;
            func_0010BCE0(0);
            sceSifCallRpc(&sdstr3_sifbd, 0, 1, 0, 0, SdStr3SifRes, 0x40,
                          (void (*)(void *))sdstr3_ret, SdStr3SifRes);
            break;
        case 3:
            if (SdStr3EeReadBreak == 1) {
                step = 4;
                break;
            }
            if (sceCdDiskReady(1) != 2)
                break;
            if (sceCdRead(sect, size, (void *)adrs, &sdstr3_cdrmode) != 1)
                break;
            SdStr3EeReading = 1;
            step++;
            break;
        case 4:
            if (sceCdSync(1) != 0)
                break;
            SdStr3EeReading = 0;
            step++;
            break;
        case 5:
            if (sceSifCheckStatRpc(&sdstr3_sifbd) != 0)
                break;
            func_0010BCE0(0);
            if (sceSifCallRpc(&sdstr3_sifbd, 2, 1, 0, 0, SdStr3SifRes, 0x40,
                              (void (*)(void *))sdstr3_ret, SdStr3SifRes) == 0)
                step++;
            break;
        case 6:
            if (SdStr3EeReadBreak != 1) {
                sum += size;
                if (sum < info->Size) {
                    sect += size;
                    adrs += size << 11;
                    size = info->Size - sum;
                    if (div + divrest < size) {
                        size = div;
                    }
                    else {
                        size = info->Size - sum;
                    }
                    step = 1;
                    break;
                }
            }
        case 7:
            SdStr3EeReadAllow = 0;
            SdStr3EeReadStat = 0;
            step = 0;
            SdStr3EeReading = 0;
            break;
        }
        func_0010B980();
    }
}

int SdStrSetDiv(int div, int divrest)
{
    SdStr3EeReadDiv = div;
    SdStr3EeReadDivRest = divrest;
    return 0;
}

int SdStriVsync(void)
{
    int id;

    if (SdStr3EeReadStat == 1)
        iWakeupThread(SdStr3EeReadThId);
    id = SdStr3KtSemaId;
    if (func_0010BAC0(id) == id)
        func_0010BA90(id);
    return 0;
}

int SdStrCdSync(int mode)
{
    if (SdStr3EeReadUse != 1)
        return -1;
    if (SdStr3EeReadStat == 0)
        return 0;
    for (;;) {
        if (mode == 1)
            break;
        if (SdStr3EeReadStat == 0)
            break;
        func_0010BAA0(SdStr3KtSemaId);
    }
    return SdStr3EeReadStat;
}

int SdStrCdRead(unsigned int lsn, unsigned int sectors, void *buf)
{
    if (SdStr3EeReadUse != 1)
        return 0;
    if (SdStr3EeReadStat)
        return 0;
    SdStr3EeRead.Sect = lsn;
    SdStr3EeRead.Size = sectors;
    SdStr3EeRead.Adrs = (int)buf;
    SdStr3EeReadStat = 1;
    SdStr3EeReadBreak = 0;
    SdStr3EeReading = 0;
    return 1;
}

void SdStrCdInit(void)
{
    static int InitFg;
    struct ThreadParam st;

    if (SdStr3EeReadUse == 1)
        return;
    if (InitFg)
        return;
    InitFg = 1;
    SdStr3EeReadStat = 0;
    sdstr3_cdrmode.trycount = 0;
    sdstr3_cdrmode.spindlctrl = 0;
    sdstr3_cdrmode.datapattern = 0;
    st.entry = sdstr3_eeread_th;
    st.stack = ThStackER;
    st.stackSize = 0x1000;
    st.initPriority = 2;
    st.gpReg = &_gp;
    SdStr3EeReadThId = func_0010B860(&st);
    StartThread(SdStr3EeReadThId, &SdStr3EeRead);
    SdStr3KtSemaParam.initCount = 0;
    SdStr3KtSemaParam.maxCount = 1;
    SdStr3KtSemaId = func_0010BA60(&SdStr3KtSemaParam);
    SdStr3EeReadUse = 1;
    do {
        if (sceSifBindRpc(&sdstr3_sifbd, 0x30, 0) < 0) {
            for (;;) {
            }
        }
    } while (sdstr3_sifbd.serve == 0);
}
