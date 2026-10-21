#include "src/common/cws/cws_wins.h"

static struct _CWS_WINS_W _wins = { 0 };
struct _CWS_WINS_W *wins = &_wins;
static int def_set_work_num[3][3] = {
    { 8, 50, 32 },
    { 100, 224, 320 },
    { 2, 16, 16 }
};

void WinsInit(void) {
    func_0011EEC0(wins, 0xA30);
}

unsigned int CwsWinsCreate(unsigned int _top_addr, int init_type) {
    int i;

    if (wins->status != 0) {
        func_0011EEC0(wins, 0xA30);
    }

    wins->top_addr = wins->end_addr = _top_addr;
    wins->size = 0;
    wins->win_max = def_set_work_num[init_type][0];
    wins->str_max = def_set_work_num[init_type][1];
    wins->obj_max = def_set_work_num[init_type][2];

    for (i = 0; i < wins->str_max; i++) {
        wins->str[i] = (struct _CWS_STR *)wins->end_addr;
        wins->end_addr += 0xB0;
        wins->size += 0xB0;
    }


    for (i = 0; i < wins->obj_max; i++) {
        wins->obj[i] = (struct _CWS_OBJ *)wins->end_addr;
        wins->end_addr += 0x3C;
        wins->size += 0x3C;
    }


    for (i = 0; i < wins->win_max; i++) {
        wins->win[i] = (struct _CWS_WIN_W *)wins->end_addr;
        wins->end_addr += 0x158;
        wins->size += 0x158;
    }

    func_0011EEC0((void *)wins->top_addr, wins->size);

    wins->status |= 1;

    return wins->end_addr;
}

void CwsWinsDelete(void) {
    func_0011EEC0(wins, 0xA30);
}

void CwsWins_Func(void) {
    int i, n;
    int test_count[3] = { 0 };
    if (wins->status & 1) {
        struct _CWS_WIN_W *pack[100];
        int min_num;
        int minx;

        for (i = 0; i < wins->win_max; i++) {
            pack[i] = wins->win[i];
        }
        for (i = 0; i < wins->win_max; i++) {
            minx = 0xFFFF;
            min_num = -1;
            for (n = 0; n < wins->win_max; n++) {
                if (pack[n] != 0) {
                    if (minx >= pack[n]->v.z) {
                        min_num = n;
                        minx = pack[n]->v.z;
                    }
                }
            }
            wins->win[i] = pack[min_num];
            pack[min_num] = 0;
        }


        for (i = 0; i < wins->win_max; i++) {
            if (wins->win[i] != 0) {
                if (wins->win[i]->status & 0x4) {
                    CwsWinDelete(wins->win[i]);
                } else if (wins->win[i]->status & 0x1) {
                    if (wins->win[i]->step[1] == 0) {
                        if ((wins->win[i]->code == 1 && !(wins->win[i]->status & 0x2)) ||
                            (wins->win[i]->code == 2 && (wins->win[i]->status & 0x2)) ||
                            (wins->win[i]->code == 3)) {
                            wins->win[i]->step[1] = wins->win[i]->code;
                            wins->win[i]->code = 0;
                        }
                    }

                    wins->win[i]->func(wins->win[i]);
                    if (wins->win[i]->status & 0x2) {
                        for (n = 0; n < 16; n++) {
                            if (wins->win[i]->obj[n] != 0) {
                                if (wins->win[i]->obj[n]->def->func != 0)
                                    wins->win[i]->obj[n]->def->func(wins->win[i], wins->win[i]->obj[n]);
                            }
                        }

                        for (n = 0; n < 16; n++) {
                            if (wins->win[i]->str[n] != 0)
                                CwsStrDisp(wins->win[i], wins->win[i]->str[n]);

                        }
                    }
                }
            }
        }
    }
}

struct _CWS_WINS_W *GetWinsAddr(void) {
    return wins;
}

char CwsWinsAllGetStatus(int flag) {
    int i;
    if (flag == 0) {
        for (i = 0; i < wins->win_max; i++) {
            if (wins->win[i] != 0) {
                if (CwsWinGetStatus(wins->win[i]) & 0xC)
                    return 0;
            }
        }
    }
    else if (flag == 1) {
        for (i = 0; i < wins->win_max; i++) {
            if (wins->win[i] != 0) {
                if (CwsWinGetStatus(wins->win[i]) & 0x2)
                    return 0;
            }
        }
    }
    return 1;
}

char CwsWinsAllDestroy(void) {
    int i, count;
    for (i = 0, count = 0; i < wins->win_max; i++) {
        if (wins->win[i] != 0) {
            if (CwsWinGetStatus(wins->win[i]) & 0x2) {
                CwsWinSetCode(wins->win[i], 0x2);
                count++;
            } else {
                CwsWinDelete(wins->win[i]);
            }
        }
    }

    return count == 0;
}
