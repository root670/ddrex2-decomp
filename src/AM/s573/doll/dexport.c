#include "src/AM/s573/doll/dexport.h"

int get_chara_hide(int chara);
char *ps2dancerGetName(int chara);
int func_001BED10(char *, char *);























































void ps2dancerGetDollList(anon_1_26 *wk, int mode) { int i, j, n, t;
    n = 0;
    i = 0; do {
    if (mode == 1 && i > -1) continue;
        if (mode == 2 && i <= -1) continue;
        if (SaveData.HideFlag[(i + 0x46) >> 5] & (1 << ((i + 0x46) & 0x1F))) {
            wk->id[n] = i;
            n++;
        }
    } while (++i < 0x2D);
    wk->n = n;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (func_001BED10(ps2dancerGetName(wk->id[j]), ps2dancerGetName(wk->id[j + 1])) > 0) {
                t = wk->id[j];
                wk->id[j] = wk->id[j + 1];
                wk->id[j + 1] = t;
            }
        }
    }
}















void ps2dancerInitHide(void) { int i;

    i = 0; do {
        if (get_chara_hide(i)) {
            SaveData.HideFlag[(i + 0x46) >> 5] |= 1 << ((i + 0x46) & 0x1F);
        }
        i++; } while (i < 0x2D);
}
