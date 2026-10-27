#include "types/_NET_READ_DATA_W.h"
#include "types/_NSV_DATA.h"
#include "types/_NSV_PLAYER_LIST.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/_net_inter_w.h"
#include "types/_net_pack_w.h"
#include "types/_net_pad_w.h"
#include "types/_net_prg_w.h"
#include "types/_nsv_rc_table_list_work.h"
#include "types/_nsv_rc_table_param_work.h"
#include "types/sceNetcnfifData.h"

struct _NETWORK_W {
                int counter;
                unsigned int status;
                unsigned char *free_data_addr;
                int step;
                int dc_code;
                int cursor;
                void (*NewFunc)();
                void (*SubFunc)();
                void (*MainFunc)();
                void (*OldFunc)();
                void (*KeyFunc)();
                void (*OldKeyFunc)();
                struct _net_pad_w padw;
                struct _NET_READ_DATA_W readw;
                struct _net_prg_w prgw;
                struct _net_inter_w interw;
                int sel_user_file_num;
                struct _NSV_USER_FILE_WORK *dur_user_file;
                struct _NSV_USER_FILE_WORK UserFile[2];
                 struct _NSV_PLAYER_LIST *player_list;
                 struct _NSV_DATA ServerData;
                 struct _nsv_rc_table_param_work RcData[2];
                 struct _nsv_rc_table_list_work RcDataTbl;
                 struct _nsv_rc_table_param_work *dur_rc_data;
                 int work[320];
                 char work_set_mode;

                 struct _net_pack_w pack;
                 struct sceNetcnfifData netcnfdata;
                 unsigned int *net_cnf_addr;
                 int net_loaded_flag;
                 int upnp_loaded_flag;
                 int bsdsocki_irx_mid;
                 int bsdsocki_irx_result;
                 int bsdsocki_irx_flag;
                 int mc_init_flag;
                 unsigned char tail[0x24];
};
#include "types/_CWS_WIN_W.h"

#define D_0102FAD8 (*(struct _CWS_WIN_W **)0x0102FAD8)
#define D_0102FAE8 (*(struct _CWS_WIN_W **)0x0102FAE8)
#define D_0102FFCC (*(int *)0x0102FFCC)
#define D_0102FFC8 (*(int *)0x0102FFC8)
#define D_0102FFD0 ((int *)0x0102FFD0)

void NetSysMenuInit2(struct _NETWORK_W *);
void NetSysTopInit2(struct _NETWORK_W *);
int CwsWin_Multi(struct _CWS_WIN_W *);
int CwsWinsAllGetStatus(int);
int NsNetLogout(void);
unsigned char *NetReadDataGetStr(int);
struct _CWS_WIN_W *CwsWinCreate(void *, int, int, int, int, int);
char CwsWinDelete(struct _CWS_WIN_W *);
char CwsWinSetCode(struct _CWS_WIN_W *, char);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char,
                  unsigned char, unsigned int, int, unsigned char,
                  unsigned char *, ...);
char CwsStrSetCol(struct _CWS_WIN_W *, int, unsigned char);
int func_0011E1D0(int);
int func_0011E1F0(int);

static void NetSysLogoutKey(struct _NETWORK_W *);
static void NetSysLogoutMain(struct _NETWORK_W *);

static __inline void NetSysLogoutFree(void) {
    int i;
    int n;
    if (D_0102FFCC > 1)
        n = 1;
    else
        n = D_0102FFCC;
    for (i = 0; i < n; i++) {
        D_0102FFCC--;
        D_0102FFC8 -= D_0102FFD0[D_0102FFCC];
        D_0102FFD0[D_0102FFCC] = 0;
    }
}

void NetSysLogoutInit(struct _NETWORK_W *netw) {
    int i;
    netw->cursor = 1;
    CwsWinDelete(D_0102FAD8);
    D_0102FAD8 = CwsWinCreate(CwsWin_Multi, 0, 0, 0x118, 0xA4, 0x5000);
    CwsStrSetAll(D_0102FAD8, 0, 0, -0x3A, 0x100, 0x80, 0x80, 0x400, 2, 0,
                 NetReadDataGetStr(10));
    CwsStrSetAll(D_0102FAD8, 1, -0x32, 0, 0x100, 0x80, 0x80, 0, 2, 1,
                 NetReadDataGetStr(2));
    CwsStrSetAll(D_0102FAD8, 2, -0x32, 0x22, 0x100, 0x80, 0x80, 0, 2, 0,
                 NetReadDataGetStr(3));
    for (i = 0; i < 2; i++) {
        if (i == netw->cursor)
            CwsStrSetCol(D_0102FAD8, i + 1, 4);
        else
            CwsStrSetCol(D_0102FAD8, i + 1, 0);
    }
    CwsWinSetCode(D_0102FAD8, 1);
    netw->NewFunc = NetSysLogoutMain;
}

static void NetSysLogoutMain(struct _NETWORK_W *netw) {
    int i;
    switch (netw->step) {
    case 0:
        netw->cursor = 1;
        netw->step = 1;
    case 1:
        if (CwsWinsAllGetStatus(0)) {
            netw->KeyFunc = NetSysLogoutKey;
            netw->step = 2;
        }
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            if (i == netw->cursor)
                CwsStrSetCol(D_0102FAD8, i + 1, 4);
            else
                CwsStrSetCol(D_0102FAD8, i + 1, 0);
        }
        switch (netw->dc_code) {
        case 1:
            CwsWinSetCode(D_0102FAE8, 2);
            CwsWinSetCode(D_0102FAD8, 2);
            netw->step = 3;
            break;
        case 2:
            CwsWinSetCode(D_0102FAD8, 2);
            netw->step = 4;
            break;
        }
        break;
    case 3:
        if (CwsWinsAllGetStatus(0))
            netw->step = 5;
        break;
    case 4:
        netw->step = 5;
        break;
    case 5:
        switch (netw->dc_code) {
        case 1:
            if (NsNetLogout()) {
                NetSysLogoutFree();
                netw->NewFunc = NetSysTopInit2;
            }
            break;
        case 2:
            netw->NewFunc = NetSysMenuInit2;
            break;
        }
        break;
    }
}

static void NetSysLogoutKey(struct _NETWORK_W *netw) {
    if (!!(func_0011E1D0(0) & 0x1000) != 0 || !!(func_0011E1D0(1) & 0x1000) != 0) {
        netw->cursor = (netw->cursor + 1) % 2;
    } else if (!!(func_0011E1D0(0) & 0x4000) != 0 || !!(func_0011E1D0(1) & 0x4000) != 0) {
        netw->cursor = (netw->cursor + 1) % 2;
    }
    if (!!(func_0011E1F0(0) & 0x110) != 0 || !!(func_0011E1F0(1) & 0x110) != 0) {
        netw->dc_code = 2;
    } else if (!!(func_0011E1F0(0) & 0x60) != 0 || !!(func_0011E1F0(1) & 0x60) != 0) {
        if (netw->cursor == 0)
            netw->dc_code = 1;
        else
            netw->dc_code = 2;
    }
    if (netw->dc_code != 0)
        netw->KeyFunc = 0;
}
