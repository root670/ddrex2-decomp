#include "src/CS/train/tra_msel.h"

static void tr_msel_init(void);
static int Tr_ms_disap(void);
static int Tr_ms_apper(void);
void Tr_set_g_game_w(void);
int Tr_load_seq(void);
void fp_sel_option_init_all(void);
int func_00196EB0(short music);
void func_001617B0(void);
void func_0015ADF0(void);
void fp_ms_create_sel_tab(void);
void fp_ms_set_cur_lr(void);
void func_0015ACA0(void);
void func_0015A920(void);
void func_0015AC90(int a);
void func_0015A900(void);
void *co_obj_set(anon_11_155 *func, void (*init)(void *), unsigned char pri);
int co_obj_get_id(void *ow);
unsigned char co_obj_step(void *ow);
void co_obj_step_set(void *ow, int step, void (*init)(void *));
int co_obj_is_exist(void *chk_ow, int id);
int co_sel00_is_exist(void);
void co_sel00_set(unsigned char mode, unsigned short pri, unsigned char obj_pri);
void co_sel00_disap_set(void);
int co_sel00_is_apper_end(void);
void tr_obj_set(int obj_no);
void tr_obj_disap(int obj_no);
void Tr_arrow_clut_anim(int count);
int fp_ms_adj_cur_ud(short d_num, int pid);
unsigned int fp_PadPush(unsigned int key, unsigned int pid);
unsigned int fp_PadTrg(unsigned int key, unsigned int pid);
unsigned int fp_ms_PadRepeat(unsigned int key);
int fp_msel_get_sn(short d_num);
void fp_msel_sd_call(unsigned int call, float time);
short func_0011F5C0(short a, short b);
short func_0011F5E0(short a, short b);
void func_0017A8A0(int a);

unsigned char Train_Msel(void) {
    int scr_end = 0;
    int d_num;
    trw->arrow_clut_ct += 0x10;
    Tr_arrow_clut_anim(trw->arrow_clut_ct);
    func_0015A900();
    switch (trw->step_s) {
    case 0:
        tr_msel_init();
        trw->step_s = 1;
    case 1:
        if (!Tr_ms_apper()) return 1;
        trw->step_s = 3;
        msw->sn_f = 0;
        msw->sn_t = 4.0f;
        break;
    case 3:
        break;
    case 2:
        msw->scr_ct += msw->scr_sp;
        if (msw->scr_sp >= 0.0f) {
            msw->scr_sp = msw->scr_sp + 2.0f;
            if (msw->scr_sp >= 200.0f) msw->scr_sp = 200.0f;
        } else {
            msw->scr_sp = msw->scr_sp - 2.0f;
            if (msw->scr_sp <= -200.0f) msw->scr_sp = -200.0f;
        }
        if (msw->scr_ct >= 1024.0f) {
            msw->scr_ct = msw->scr_ct - 1024.0f;
            msw->cur_lr = func_0011F5C0(msw->cur_lr, msw->ena_num);
            scr_end = 1;
        } else if (msw->scr_ct <= -1024.0f) {
            msw->scr_ct = msw->scr_ct + 1024.0f;
            msw->cur_lr = func_0011F5E0(msw->cur_lr, msw->ena_num);
            scr_end = 1;
        } else {
            return 1;
        }
        break;
    case 4:
        if (!Tr_ms_disap()) return 1;
        co_obj_step_set(trw->ms_display, 2, 0);
        trw->ms_display = 0;
        return trw->next_mode;
    }
    d_num = msw->sel_tab[msw->cur_lr];
    if (scr_end) {
        fp_ms_adj_cur_ud(d_num, 0);
        trw->level = msw->cur_ud[0] - 1;
        trw->music_num = d_num - 1;
    }
    if (fp_PadPush(0xA000, 2)) {
        if (msw->repcnt <= 32.0f) msw->repcnt = msw->repcnt + 1.0f;
    } else {
        msw->repcnt = 0.0f;
    }
    if (fp_ms_PadRepeat(0x2000)) {
        trw->step_s = 2;
        if (!scr_end || msw->scr_sp >= 0.0f) {
            msw->scr_sp = -96.0f;
            fpw->flag &= 0xFFFFFFEF;
        }
        {
            short next_lr;
            int next_call;
            next_lr = func_0011F5E0(msw->cur_lr, msw->ena_num);
            next_call = fp_msel_get_sn(msw->sel_tab[next_lr]);
            if (next_call == fp_msel_get_sn(d_num) && next_call == 0x56E0099)
                func_0017A8A0(0x11);
            else
                fp_msel_sd_call(0x11, 4.0f);
        }
        return 1;
    }
    if (fp_ms_PadRepeat(0x8000)) {
        trw->step_s = 2;
        if (!scr_end || msw->scr_sp <= 0.0f) {
            msw->scr_sp = 96.0f;
            fpw->flag &= 0xFFFFFFEF;
        }
        {
            short next_lr;
            int next_call;
            next_lr = func_0011F5C0(msw->cur_lr, msw->ena_num);
            next_call = fp_msel_get_sn(msw->sel_tab[next_lr]);
            if (next_call == fp_msel_get_sn(d_num) && next_call == 0x56E0099)
                func_0017A8A0(0x11);
            else
                fp_msel_sd_call(0x11, 4.0f);
        }
        return 1;
    }
    if (scr_end) {
        msw->scr_ct = 0.0f;
        trw->step_s = 3;
    }
    if (msw->sn_t <= 0.0f) {
        if (!msw->sn_f) {
            func_0017A8A0(fp_msel_get_sn(d_num));
            msw->sn_f = 1;
        }
    } else {
        msw->sn_t = msw->sn_t - 1.0f;
    }
    if (fp_PadTrg(0x60, 2)) {
        trw->step_s = 4;
        msw->ftimer = 0.0f;
        trw->next_mode = 2;
        func_0017A8A0(3);
    } else if (fp_PadTrg(0x110, 2)) {
        trw->step_s = 4;
        msw->ftimer = 0.0f;
        trw->next_mode = 5;
        func_0017A8A0(0x63);
    }
    return 1;
}

static int Tr_ms_apper(void) {
    int end_num = 0;
    if (msw->ftimer >= 8.0f)
        if (!trw->obj_p[2]) tr_obj_set(2);
    if (msw->ftimer >= 0.0f)
        if (!msw->lr) {
            msw->lr = co_obj_set(fp_ms_objf, 0, 8);
            msw->lr_obj_id = co_obj_get_id(msw->lr);
        }
    if (msw->ftimer >= 16.0f)
        if (!msw->scr) msw->scr = co_obj_set(&fp_ms_objf[7], 0, 0xA0);
    if (msw->ftimer >= 0.0f)
        if (!co_sel00_is_exist()) co_sel00_set(1, 0x100, 0x40);
    if (msw->ftimer >= 16.0f)
        if (!msw->base) msw->base = co_obj_set(&fp_ms_objf[8], 0, 4);
    if (msw->ftimer >= 8.0f)
        if (!msw->radar) msw->radar = co_obj_set(&fp_ms_objf[4], 0, 0xA0);
    if (msw->ftimer >= 6.0f)
        if (!msw->opt) msw->opt = co_obj_set(&fp_ms_objf[5], 0, 0xA0);
    if (msw->opt)
        if (co_obj_step(msw->opt) == 1) end_num++;
    if (msw->lr)
        if (co_obj_step(msw->lr) == 1) end_num++;
    if (co_sel00_is_exist())
        if (co_sel00_is_apper_end()) {
            end_num++;
            if (!fpw->btn) {
                fpw->btn = co_obj_set(&fp_objf[0], 0, 0x10);
                fpw->btn_obj_id = co_obj_get_id(fpw->btn);
            }
        }
    if (trw->obj_p[2])
        if (co_obj_step(trw->obj_p[2]) == 1) end_num++;
    if (end_num == 4) return 1;
    msw->ftimer = msw->ftimer + 1.0f;
    return 0;
}

static int Tr_ms_disap(void) {
    if (msw->ftimer == 0.0f) {
        fpw->flag &= 0x9FFFFFFF;
    }
    if (msw->ftimer >= 8.0f)
        if (msw->lr) {
            co_obj_step_set(msw->lr, 2, 0);
            msw->lr = 0;
        }
    if (msw->ftimer >= 16.0f)
        if (msw->scr) {
            co_obj_step_set(msw->scr, 2, 0);
            msw->scr = 0;
        }
    if (msw->ftimer >= 8.0f)
        if (msw->radar) {
            co_obj_step_set(msw->radar, 2, 0);
            msw->radar = 0;
        }
    if (msw->ftimer >= 6.0f)
        if (msw->opt) {
            co_obj_step_set(msw->opt, 2, 0);
            msw->opt = 0;
        }
    if (msw->ftimer >= 0.0f)
        if (msw->base) {
            co_obj_step_set(msw->base, 2, 0);
            msw->base = 0;
        }
    if (!(fpw->flag & 0x40000000))
        if (msw->ftimer >= 0.0f)
            if (fpw->btn) {
                co_obj_step_set(fpw->btn, 2, 0);
                fpw->flag |= 0x40000000;
            }
    if (fpw->btn && (fpw->flag & 0x40000000)) {
        if (!co_obj_is_exist(fpw->btn, fpw->btn_obj_id)) {
            if (co_sel00_is_exist()) {
                co_sel00_disap_set();
            }
            fpw->btn = 0;
            fpw->btn_obj_id = 0;
        }
    }
    if (trw->next_mode == 5) {
        if (msw->ftimer >= 8.0f) tr_obj_disap(2);
        msw->ftimer = msw->ftimer + 1.0f;
        if (msw->ftimer >= 40.0f) return 1;
    } else {
        msw->ftimer = msw->ftimer + 1.0f;
        if (msw->ftimer >= 30.0f) return 1;
    }
    return 0;
}

static void tr_msel_init(void) {
    short code;
    trw->old_music_num = trw->music_num;
    if (!trw->next_mode) {
        code = func_00196EB0(trw->music_num);
        if (code == -1) return;
        g_game_w.player[0].mode.edseq_id = -1;
        g_game_w.player[1].mode.edseq_id = -1;
        Tr_set_g_game_w();
        Tr_load_seq();
        trw->adjust_bar = trw->c_bar_adjust;
        trw->bar_start = trw->adjust_bar + 1;
        trw->bar_end = trw->bar_max = trw->c_bar_max + trw->adjust_bar;
    }
    fp_sel_option_init_all();
    fpw->pad_type = (((g_game_w.player[0].select == 2 || g_game_w.player[0].select == 4) ? 0 : (g_game_w.player[1].select == 2 || g_game_w.player[1].select == 4) ? 1 : ((g_game_w.player[0].mode.style == 7 || g_game_w.player[0].mode.style == 0) && (g_game_w.player[1].mode.style == 7 || g_game_w.player[1].mode.style == 0)) ? -1 : 0) == 1) ? 4 : 3;
    msw->cur_ud_old[0] = msw->cur_ud[0] = trw->level + 1;
    func_001617B0();
    func_0015ADF0();
    fp_ms_create_sel_tab();
    msw->old_d_num = trw->music_num + 1;
    fp_ms_set_cur_lr();
    msw->ftimer = 0.0f;
    msw->repcnt = 0.0f;
    func_0015ACA0();
    func_0015A920();
    func_0015AC90(0);
    msw->sn_f = 1;
    fpw->step = 4;
    if (!trw->ms_display) {
        trw->ms_display = co_obj_set(&fp_objf[1], 0, 0x20);
    }
}
