static int step0 = 0;
#include "src/CS/shop/shop_main.h"
#define D_00E4D380 ((unsigned char *)0xE4D380)

void func_001B7C30(anon_3_124 *p, int n);
void func_0017A8A0(int);
void func_00169430(void);
void shop_init(anon_3_124 *work);
void shop_select(anon_3_124 *work);
void shop_fade_main(void);
void shop_fade_init(void);
void shop_fade_set(int type);

void shop_set_step(int step) {
    anon_3_124 *work = shop_w;
    if (step == 5) return;
    if (step == 3) {
        step = step0;
        switch (step) {
        case 0: step = 1; break;
        case 1: step = 2; break;
        }
        step0 = step;
    } else if (step == 4) {
        step = step0;
        switch (step) {
        case 0: step = 1; break;
        case 1: step = 2; break;
        }
        step0 = step;
    } else {
        step0 = step;
    }
    work->step = 0;
    work->step_s = 0;
}

anon_3_124 *shop_get_work(void) {
    return shop_w;
}

void ShopFinish(void) {
    func_0017A8A0(0xF101);
}

int ShopStep(void) {
    anon_3_124 *work = shop_w;
    switch (step0) {
    case 0:
        shop_init(work);
        break;
    case 1:
        shop_select(work);
        break;
    case 2:
        return 1;
    }
    work->syscnt++;
    shop_fade_main();
    func_00169430();
    return g_game_w.mode_quit_flg != 0;
}

void ShopAddrInit(unsigned char *addr) {
    g_game_w.last_data_addr = addr;
    shop_w = (anon_3_124 *)g_game_w.last_data_addr;
    func_001B7C30(shop_w, 0x520);
    g_game_w.last_data_addr += 0x520;
    shop_fade_init();
    shop_fade_set(1);
    shop_w->before_mode = *(short *)&g_game_w;
    {
        anon_3_124 *w = shop_w;
        step0 = 0;
        w->step = 0;
        w->step_s = 0;
    }
    func_0017A8A0(0xF100);
}

void ShopInit(void) {
    g_game_w.last_data_addr = D_00E4D380;
    shop_w = (anon_3_124 *)g_game_w.last_data_addr;
    func_001B7C30(shop_w, 0x520);
    g_game_w.last_data_addr += 0x520;
    shop_fade_init();
    shop_w->before_mode = 0x37;
    {
        anon_3_124 *w = shop_w;
        step0 = 0;
        w->step = 0;
        w->step_s = 0;
    }
}
