#include "src/network/net_read_data.h"

#define D_002DD478 ((unsigned char *)0x002DD478)
#define D_002DD480 ((unsigned char *)0x002DD480)
#define D_002DD488 ((unsigned char *)0x002DD488)
#define D_00F4E580 ((unsigned int)0x00F4E580)
#define D_00F72780 ((unsigned int)0x00F72780)

#define D_0093D350 ((unsigned int *)0x0093D350)
#define D_00975350 ((unsigned int *)0x00975350)
#define D_01029C84 (*(unsigned int *)0x01029C84)
#define D_01029C88 (*(unsigned char **)0x01029C88)
#define D_01029E34 ((unsigned char **)0x01029E34)

extern struct g_game_w g_game_w;

void co_disp_all_init(void);
int co_obj_init(void *, int);
void co_movie_restart(void);
void co_movie_change_start(void);
int co_movie_get_stat(void);
void co_movie_set(int, unsigned int);
unsigned int func_00153330(unsigned char *);
int func_0016DC60(void *, unsigned int, void *, int);
void func_0016E0C0(void *, int);
int func_0016DED0(void);
int func_0011F150(void);
int func_0011E090(unsigned char *, unsigned char *);
int func_0011DE80(void);
void func_001274C0(void *, int);

static int nrd_free_tbl[12] = {
    0x3B, 0x13, 0x14, 0x15, 0x16, 0x21, 0x22, 0x18, 0x34, 0x26, 0x2D, 0x32,
};

static unsigned int NetReadDataDecode(int id, unsigned char *dest_addr) {
    unsigned int *base_addr;
    unsigned int size;
    int idx;

    idx = id;
    if (idx < 0x51 && !(dest_addr < (unsigned char *)0)) {
        base_addr = D_0093D350;
    } else {
        if (idx >= 0xA9) {
            return 0;
        }
        if (g_game_w.rloadtex_num == 1) {
            idx -= 0x51;
            base_addr = D_00975350;
        } else if (g_game_w.rloadtex_num == 2) {
            base_addr = D_00975350;
            idx -= 0x51;
        } else if (g_game_w.rloadtex_num == 2) {
            base_addr = D_00975350;
            idx -= 0x51;
        } else {
            return 0;
        }
    }
    size = func_00153330((unsigned char *)base_addr + base_addr[idx]);
    return (size + 0xF) & ~0xF;
}

int NetReadDataInitFreeDataAddr(struct _NETWORK_W *netw, unsigned int free_addr) {
    int rtn;
    int i;
    int ret;

    rtn = 0;
    if (netw->readw.read_flag & 8) {
        netw->readw.free_step = 5;
    }
    switch (netw->readw.free_step) {
    case 0:
        D_01029C88 = (unsigned char *)free_addr;
        netw->readw.free_counter = 0;
        netw->readw.free_step++;
    case 1:
        netw->readw.free_addr[netw->readw.free_counter] = D_01029C88;
        D_01029C88 += NetReadDataDecode(nrd_free_tbl[netw->readw.free_counter],
                                        D_01029C88);
        netw->readw.free_counter++;
        if (netw->readw.free_counter < 12) {
            break;
        }
        netw->readw.free_step++;
        break;
    case 2:
        co_disp_all_init();
        D_01029C88 += co_obj_init(D_01029C88, 8);
        D_01029C84 |= 2;
        netw->readw.free_step++;
    case 3:
        if (D_01029C84 & 0x10) {
            netw->readw.free_step = 5;
            break;
        }
        co_movie_set(8, 0x1721F00);
        netw->readw.free_step++;
        break;
    case 4:
        ret = co_movie_get_stat();
        if ((ret & 0xFF) != 2) {
            break;
        }
        D_01029C84 |= 0x10;
        netw->readw.free_step++;
        break;
    case 5:
        for (i = 0; i < 12; i++) {
            func_001274C0(netw->readw.free_addr[i], i + 0x24);
        }
        netw->readw.free_step++;
    case 6:
    default:
        if (netw->readw.read_flag & 8) {
            co_movie_restart();
        } else {
            co_movie_change_start();
        }
        netw->readw.read_flag |= 8;
        rtn = 1;
        break;
    }
    return rtn;
}

int NetReadDataGetStrLFNum(unsigned char *str) {
    int rtn;
    int i;

    rtn = 0;
    if (str != 0) {
        for (i = 0; str[i] != 0; i++) {
            if (str[i] == '\n') {
                rtn++;
            }
        }
    }
    return rtn;
}

unsigned char *NetReadDataGetStr(int str_num) {
    return D_01029E34[str_num];
}

int NetReadData(struct _NETWORK_W *netw, int type) {
    int rtn = 0;
    int flg;
    int i;
    int num;
    anon_2_47 nrd_data_w[4] = {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { D_002DD478, 0, 0, 0xB, 0, 0xB, 0xD, D_00F4E580 },
        { D_002DD480, 0xC, 0xB, 0x15, 0xD, 0x9, 0x1C, D_00F72780 },
        { D_002DD488, 0xC, 0xB, 0x25, 0xD, 0x19, 0x5A, D_00F72780 },
    };
    struct _tag_cFilepackData *p;
    unsigned char *string;
    int open_flag;
    int coment_flag;

    if (type == 0) {
        netw->readw.read_step = 0;
        netw->readw.now_read_data = type;
        netw->readw.read_flag &= ~1;
        netw->readw.read_flag &= ~2;
        netw->readw.read_flag &= ~4;
        return -1;
    }
    if (netw->readw.now_read_data == type) {
        goto step;
    }
    netw->readw.now_read_data = type;
    switch (type) {
    case 1:
        if (netw->readw.read_flag & 1) {
            netw->readw.read_step = 6;
        } else {
            netw->readw.read_step = 0;
        }
        break;
    case 2:
        if (netw->readw.read_flag & 2) {
            netw->readw.read_step = 6;
        } else {
            netw->readw.read_flag &= ~4;
            netw->readw.read_step = 1;
        }
        break;
    case 3:
        if (netw->readw.read_flag & 4) {
            netw->readw.read_step = 6;
        } else {
            netw->readw.read_flag &= ~2;
            netw->readw.read_step = 1;
        }
        break;
    }
step:
    switch (netw->readw.read_step) {
    case 0:
        flg = func_0011F150();
        netw->readw.read_step = 1;
        if (flg & 1) {
            netw->readw.read_step = 2;
        }
        if (flg & 2) {
            netw->readw.read_step = 3;
        }
        break;
    case 1:
        if (func_0011E090(nrd_data_w[netw->readw.now_read_data].data,
                          g_game_w.last_data_addr) == 1) {
            netw->readw.read_step = 2;
        }
        break;
    case 2:
        if (func_0011DE80() == 1) {
            netw->readw.read_step = 3;
        }
        break;
    case 3:
        func_0016DC60(g_game_w.last_data_addr,
                      nrd_data_w[netw->readw.now_read_data].write_addr,
                      &netw->readw.tblFilepack[nrd_data_w[netw->readw.now_read_data].dec_top_id],
                      nrd_data_w[netw->readw.now_read_data].tex_num + 1);
        func_0016E0C0(DecodeFilepackData_Th, -1);
        netw->readw.read_step = 4;
    case 4:
        if (func_0016DED0() == 1) {
            netw->readw.read_step = 5;
        }
        break;
    case 5:
        open_flag = 0;
        coment_flag = 0;
        num = 0;
        p = &netw->readw.tblFilepack[nrd_data_w[netw->readw.now_read_data].dec_font_top_id];
        string = (unsigned char *)p->address;
        for (i = 0; i < p->size; i++) {
            if (!open_flag) {
                if (!coment_flag) {
                    if (string[i] == '/' && string[i + 1] == '*') {
                        i++;
                        coment_flag = 1;
                    } else if (string[i] == '[') {
                        netw->readw.font_tbl[nrd_data_w[netw->readw.now_read_data].font_top_id + num] =
                            &string[i + 1];
                        num++;
                        open_flag = 1;
                    }
                } else {
                    if (coment_flag == 1 && string[i] == '*' && string[i + 1] == '/') {
                        i++;
                        coment_flag = 0;
                    }
                }
            } else {
                if (open_flag == 1 && string[i] == ']') {
                    string[i] = 0;
                    open_flag = 0;
                }
            }
        }
        netw->readw.read_step = 6;
        break;
    case 6:
        for (i = 0; i < nrd_data_w[netw->readw.now_read_data].tex_num; i++) {
            func_001274C0((void *)netw->readw.tblFilepack[nrd_data_w[netw->readw.now_read_data].dec_top_id + i].address,
                          nrd_data_w[netw->readw.now_read_data].tcb_top_id + i);
        }
        netw->readw.read_step = 7;
        break;
    case 7:
    default:
        switch (netw->readw.now_read_data) {
        case 1:
            netw->readw.read_flag |= 1;
            break;
        case 2:
            netw->readw.read_flag |= 2;
            netw->readw.read_flag &= ~4;
            break;
        case 3:
            netw->readw.read_flag |= 4;
            netw->readw.read_flag &= ~2;
            break;
        }
        rtn = 1;
        break;
    }
    return rtn;
}
