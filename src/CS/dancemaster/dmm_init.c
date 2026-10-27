#include "src/CS/dancemaster/dmm_init.h"
#define D_0104A9D0 ((unsigned char *)0x104A9D0)
#define D_00FB4C40 ((unsigned char *)0xFB4C40)
#define D_00E62B80 ((unsigned char *)0xE62B80)

#define DMM_LAST_DATA (g_game_w.last_data_addr)

void dmm_quit_off(void);
void Init_Dmm_ol(void);
int Main_Dmm_ol(void);
int dmm_icon(void);
void dmm_sys_fade_init(void);
void dmm_sys_fade_set(int mode);
void func_00128600(void);
void dmm_func_init_g_game_w(void);
void dmm_bgm_init(void);
int co_movie_set(int kind, unsigned char *addr);
unsigned char co_movie_get_stat(void);
void co_movie_change_start(void);
int func_0011E090(anon_25_87 *tbl, unsigned char *addr);
int func_0011DE80(void);
void func_0017A8A0(int kind);
void dmm_set_step(int step);
void dmm_init_obj_move_work(anon_0_87 *work, int no);
anon_28_87 *func_007FB400(void);
void func_007FB630(void);
struct music_info *dmm_get_minfo_music_num(int music_num);
unsigned char *func_00160ED0(struct music_info *mip);

void dmm_init(anon_0_87 *work) {
    int val;
    switch (work->step) {
    case 0:
        dmm_quit_off();
        DMM_LAST_DATA = D_0104A9D0;
        func_00128600();
        dmm_sys_fade_init();
        dmm_sys_fade_set(0);
        work->step++;
        break;
    case 1:
        Init_Dmm_ol();
        work->step++;
        break;
    case 2:
        val = Main_Dmm_ol();
        if (val == 1) work->step++;
        break;
    case 3:
        if (dmm_icon()) work->step++;
        break;
    case 4:
        if (func_0011E090(dmm_font, D_00FB4C40)) work->step++;
        break;
    case 5:
        if (func_0011DE80()) work->step++;
        break;
    case 6:
        co_movie_set(1, D_00E62B80);
        work->step++;
        break;
    case 7:
        if (co_movie_get_stat() == 2 || co_movie_get_stat() == 3) work->step++;
        break;
    case 8:
        dmm_init_work(work);
        dmm_func_init_g_game_w();
        dmm_bgm_init();
        co_movie_change_start();
        work->step++;
        break;
    case 9:
        dmm_calc_max_bar(work->max_bar);
        work->step++;
        break;
    case 10:
        func_0017A8A0(0x15);
        dmm_set_step(8);
    }
}

static void dmm_init_work(anon_0_87 *work) {
    int i;
    work->zoom = 1.0f;
    work->before_state = 0;
    work->music_speed = 4.0f;
    work->music_num = 0;
    work->loaded_music_num = -1;
    work->start_pid_first = g_game_w.player[0].select != 1;
    work->is_retry = 0;
    work->is_retry_sel = 0;
    work->is_disp_dancer = SaveData.Option.DollDisp;
    work->dancer[0] = work->dancer[1] = 0x2D;
    work->is_disp_movie = SaveData.Option.BgEffect;
    for (i = 0; i < 6; i++) {
        dmm_init_obj_move_work(work, i);
        work->move_w[i].type = 4;
    }
    work->is_area_disp = 1;
    work->is_shop_info_disp = 0;
    func_007FB400()->shop_mode_flag = 0;
    func_007FB630();
}

static void dmm_calc_max_bar(int *max_bar) {
    struct sq_standard *addr;
    struct sq_indicator *id_top;
    struct music_info *mip;
    unsigned char *temp_addr;
    int num;
    int n;
    int first_bct;
    int last_bct;
    int bar;
    temp_addr = DMM_LAST_DATA;
    for (num = 0; num < 0x4C; num++) {
        first_bct = 0;
        last_bct = 0;
        if (num == 0x4B) continue;
        mip = dmm_get_minfo_music_num(num);
        addr = (struct sq_standard *)func_00160ED0(mip);
        while (addr->header.kind != 2) addr = (struct sq_standard *)((unsigned char *)addr + addr->header.size);
        id_top = (struct sq_indicator *)&addr->body[addr->num];
        for (n = 0; n < addr->num; n++) {
            if (id_top->class == 2) {
                switch (id_top->icode) {
                case 5:
                    first_bct = addr->body[n];
                    break;
                case 3:
                    last_bct = addr->body[n];
                    break;
                }
            }
            id_top++;
        }
        bar = last_bct - first_bct;
        bar = (bar + 0xFFF) / 0x1000 * 0x1000;
        max_bar[num] = bar / 0x1000;
    }
    DMM_LAST_DATA = temp_addr;
}
