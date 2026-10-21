#include "src/CS/ani_load.h"

int func_0011DE80(void);
unsigned int func_0011E090(void *tbl, unsigned int size);
void ps2dancerBreakDataArea(void);

int sysReadAnimeInit2(int player) {
    ps2dancerBreakDataArea();
    if (player != 0) goto two;
    return 0 < func_0011E090(ani_data_1p, 0x1881E00);
two:
    return 0 < func_0011E090(ani_data_2p, 0x1ABBD00);
}

int sysReadAnimeWait2(int player) {
    int ret;
    ret = 0; if (func_0011DE80()) {
        if (player == 0) {
            g_game_w.anime1_load_flg = 1;
        } else {
            g_game_w.anime2_load_flg = 1;
        }
        ret = 1;
    }
    return ret;
}

void SetBeginnerFlg1p(int flg) {
    g_game_w.anime1_load_flg = flg;
}

void SetBeginnerFlg2p(int flg) {
    g_game_w.anime2_load_flg = flg;
}
