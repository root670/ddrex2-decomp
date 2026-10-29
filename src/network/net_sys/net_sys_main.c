#include "src/network/net_sys/net_sys_main.h"
#include "types/_NETWORK_W.h"
#include "types/_CWS_WIN_W.h"

#define NET_SYS_LAST_DATA (*(volatile int *)&g_game_w.last_data_addr)
extern unsigned int D_01029C88[];
#define D_0102FAC4 ((struct _CWS_WIN_W **)0x0102FAC4)
#define D_0102FAC8 (*(struct _CWS_WIN_W **)0x0102FAC8)
#define D_0102FFC8 (*(unsigned char **)0x0102FFC8)
extern int D_0102FFCC[];
#define D_0102FFD0 ((int *)0x0102FFD0)

void CwsWinsDelete(void);
unsigned int CwsWinsCreate(unsigned int, int);
struct _CWS_WIN_W *CwsWinCreate(void *, int, int, int, int, int);
char CwsWinSetCode(struct _CWS_WIN_W *, char);
void NetInterErrInit(void);
int NetReadData(struct _NETWORK_W *, int);
void func_0011EEC0(void *, int);
void co_caption_disap(void);
void co_caption_set(unsigned short, unsigned short, unsigned char, unsigned short,
                    unsigned char);
void co_caption_tex_id_set(int);
int co_caption_is_exist(void);
void init_libmc_set(void);
int main_libmc_set(void);
int CwsWin_Multi(struct _CWS_WIN_W *);
int NetWin_Base(struct _CWS_WIN_W *);
int NetWin_Bar(struct _CWS_WIN_W *);
int NetWin_Menu(struct _CWS_WIN_W *);
int NetWin_Suser(struct _CWS_WIN_W *);
int NetWin_Slby(struct _CWS_WIN_W *);

void NetSysEnd(struct _NETWORK_W *netw) {
    int val;

    switch (netw->step) {
    case 0:
        co_caption_disap();
        CwsWinsDelete();
        netw->step++;
        break;
    case 1:
        init_libmc_set();
        netw->step++;
        break;
    case 2:
        val = main_libmc_set();
        if (val == 1)
            netw->step++;
        break;
    case 3:
        netw->NewFunc = 0;
        break;
    }
}

void NetSysInit(struct _NETWORK_W *netw) {
    int i;
    int flg;

    switch (netw->step) {
    case 0:
        D_0102FFCC[0] = 0;
        func_0011EEC0(D_0102FFD0, 0x18);
        if (netw->work_set_mode != 1) {
            func_0011EEC0(D_0102FAC4, 0x214);
            netw->work_set_mode = 1;
        }
        CwsWinsDelete();
        netw->step = 1;
        break;
    case 1:
        if (NetReadData(netw, 2) == 1)
            netw->step = 2;
        break;
    case 2:
        NET_SYS_LAST_DATA = CwsWinsCreate(D_01029C88[0], 1);
        flg = NET_SYS_LAST_DATA;
        func_0011EEC0(&D_0102FFC8, 0x38);
        D_0102FFC8 = (unsigned char *)((flg + 0x3F) & ~0x3F);
        NetInterErrInit();
        {
            anon_2_77 set_w[16] = {
                { CwsWin_Multi, 0, 0, 0x1CC, 0x12C, 0x5400 },
                { NetWin_Base, -0x140, -0xC0, 0, 0, 0x4600 },
                { NetWin_Bar, -0x140, -0xE0, 0, 0, 0x4E00 },
                { CwsWin_Multi, 0, 0x8B, 0x240, 0x6A, 0x4800 },
                { CwsWin_Multi, 0, 0x1F, 0x240, 0x142, 0x4A00 },
                { CwsWin_Multi, 0, 0, 0, 0, 0 },
                { CwsWin_Multi, 0, 0, 0, 0, 0 },
                { NetWin_Menu, -0xCE, -0x7C, 0, 0, 0x4000 },
                { NetWin_Menu, -0xBA, -0x49, 0, 0, 0x4000 },
                { NetWin_Menu, -0xA6, -0x16, 0, 0, 0x4000 },
                { NetWin_Suser, -0xF5, -0x7C, 0, 0, 0x4200 },
                { NetWin_Suser, -0xE1, -0x18, 0, 0, 0x4200 },
                { NetWin_Suser, -0xDE, -0x7C, 0, 0, 0x4200 },
                { NetWin_Slby, -0xDC, -0x7C, 0, 0, 0x4400 },
                { NetWin_Slby, -0xDC, -0x38, 0, 0, 0x4400 },
                { NetWin_Slby, -0xDC, 0xC, 0, 0, 0x4400 }
            };

            for (i = 0; i < 0x10; i++)
                D_0102FAC4[i] = CwsWinCreate(set_w[i].func, set_w[i].x, set_w[i].y,
                                             set_w[i].w, set_w[i].h, set_w[i].z);
        }
        netw->step++;
        break;
    case 3: {
        flg = co_caption_is_exist();
        if (flg == 0) {
            co_caption_set(0x9C, 0, 1, 0x5200, 0);
            co_caption_tex_id_set(0x24);
        }
        D_0102FAC8->mode = 4;
        CwsWinSetCode(D_0102FAC8, 1);
        netw->step++;
        break;
    }
    case 4:
    default:
        if (netw->status & 0x20)
            netw->NewFunc = NetSysTopInit;
        else
            netw->NewFunc = NetSysRuleStartInit;
        break;
    }
}
