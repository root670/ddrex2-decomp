#include "src/CS/shop/shop_init.h"

#define SHOP_LAST_DATA (g_game_w.last_data_addr)

int func_0011E430(void);
void func_0011E440(int);
void func_00128600(void);
int co_movie_set(int kind, unsigned char *addr);
unsigned char co_movie_get_stat(void);
int func_0011E090(anon_19_122 *tbl, unsigned char *addr);
int func_0011DE80(void);
int func_00120250(int);
void shop_bind_tex(void);
void shop_make_contents_list(anon_3_122 *work);
void shop_bgm_init(void);
void co_movie_change_start(void);
void func_0017A8A0(int);
void shop_set_step(int step);

void shop_init(anon_3_122 *work) {
    switch (work->step) {
    case 0:
        func_0011E440(func_0011E430() | 0x10);
        usr_work.mode_quit_flg = 0;

        func_00128600();

        if (work->before_mode == 0x37) {
            work->mv_data_addr = SHOP_LAST_DATA;
            work->step = 1;
            break;
        } else {
            work->shop_data_addr = SHOP_LAST_DATA;
            work->step = 3;
        }
        break;

    case 1:
        co_movie_set(11, (unsigned char *)(((unsigned int)work->mv_data_addr + 0x7F) & 0xFFFFFF80));
        SHOP_LAST_DATA += 0x1520C0;
        work->step++;
        break;

    case 2:
        if (co_movie_get_stat() == 2 || co_movie_get_stat() == 3) {
            work->shop_data_addr = SHOP_LAST_DATA;
            work->step++;
        }
        break;

    case 3:
        if (func_0011E090(shop_bin, work->shop_data_addr)) {
            SHOP_LAST_DATA += 0x40000;

            work->step++;
        }
        break;
    case 4:
        if (func_0011DE80()) {
            work->course_data_addr = SHOP_LAST_DATA;

            work->step++;
        }
        break;

    case 5:
        if (func_0011E090(course_bin, work->course_data_addr)) {
            SHOP_LAST_DATA += 0x6A000;

            work->step++;
        }
        break;
    case 6:
        if (func_0011DE80()) {
            work->step++;
        }
        break;

    case 7:
        if (func_00120250(2) == 1) {
            shop_bind_tex();

            work->free_mem_addr = SHOP_LAST_DATA;

            work->step++;
        }
        break;

    case 8:
        func_0011E440(func_0011E430() & ~0x10);
        usr_work.mode_quit_flg = 1;

        shop_init_work(work);

        shop_make_contents_list(work);

        shop_bgm_init();

        co_movie_change_start();

        work->step++;
        break;

    case 9:
        func_0017A8A0(0x15);
        shop_set_step(3);
    }
}

static void shop_init_work(anon_3_122 *work) {
    int i;
    work->start_pid_first = g_game_w.player[0].select != 1;

    work->tab_cursor = 0;
    work->contents_cursor = 0;
    work->contents_cursor_new = 0;
    work->contents_cursor_disp_top = 0;
    work->contents_cursor_disp_top_new = 0;

    work->tab_state = 0;
    work->cont_state = 0;

    work->confirm_cursor = 0;
    work->info_cursor = 0;
    work->info_list_disp = 0;

    work->cursor_anime = 0;
    work->cursor_anime_flag = 1;

    for (i = 1; i < 0xCE; i++) {
        if (SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))) SaveData.HideAppNewFlag[(i - 1) >> 5] &= ~(1 << ((i - 1) & 31));
    }
}
