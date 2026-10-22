#include "src/CS/freeplay/fp_qmenu.h"

void fp_msel_sd_call(unsigned int call, float time);
int co_obj_is_exist(void *chk_ow, int id);

static anon_0_170 fp_qm_save = {
    fp_qm_save_func,
    fp_qm_save_init,
    (unsigned char *)"SAVE",
};
static anon_0_170 fp_qm_rec = {
    0,
    0,
    (unsigned char *)"RECORDS",
};
static anon_0_170 fp_qm_sort = {
    fp_qm_sort_func,
    fp_qm_sort_ini,
    (unsigned char *)"SORT",
};
static anon_0_170 fp_qm_camera = {
    0,
    0,
    (unsigned char *)"CAMERA",
};
struct _OPTMC_W *qmsw = &fp_qm_save_w;
static anon_0_170 *fp_nms_qm[2] = {
    &fp_qm_save,
    0,
};
static anon_0_170 *fp_ms_qm[4] = {
    &fp_qm_sort,
    &fp_qm_save,
    &fp_qm_rec,
    0,
};
static anon_0_170 *fp_ms_qm_eye[5] = {
    &fp_qm_sort,
    &fp_qm_save,
    &fp_qm_rec,
    &fp_qm_camera,
    0,
};
static anon_0_170 *fp_ms_qm_edi[3] = {
    &fp_qm_save,
    &fp_qm_rec,
    0,
};
static anon_0_170 *fp_ms_qm_edi_eye[4] = {
    &fp_qm_save,
    &fp_qm_rec,
    &fp_qm_camera,
    0,
};
struct _tag_cCmes *pCmes = (struct _tag_cCmes *)0x006D2E30;

int fp_qmenu_func(void) {
    switch (co_qmenu_get_stat() & 0xFF) {
    case 0:
    case 1:
        if (fpw->flag & 0x20) {
            if (fpw->step == 4) {
                if (msw->edit_sel) {
                    co_quick_menu_set(etw->cur ? fp_ms_qm_edi_eye : fp_ms_qm_edi, 0xC000, 0xC8);
                } else {
                    co_quick_menu_set(etw->cur ? fp_ms_qm_eye : fp_ms_qm, 0xC000, 0xC8);
                }
            } else {
                co_quick_menu_set(fp_nms_qm, 0xC000, 0xC8);
            }
            fpw->flag &= ~0x20;
        }
        break;
    case 2:
        if (fpw->flag & 0x20) {
            if (fpw->step == 4) {
                if (msw->edit_sel) {
                    co_quick_menu_data_set(etw->cur ? fp_ms_qm_edi_eye : fp_ms_qm_edi);
                } else {
                    co_quick_menu_data_set(etw->cur ? fp_ms_qm_eye : fp_ms_qm);
                }
            } else {
                co_quick_menu_data_set(fp_nms_qm);
            }
            fpw->flag &= ~0x20;
        }
        break;
    case 4:
        if (fp_PadTrg(0x1000, 2)) {
            co_qmenu_cursor_dec();
        } else if (fp_PadTrg(0x4000, 2)) {
            co_qmenu_cursor_inc();
        } else if (fp_PadTrg(0x60, 2)) {
            co_qmenu_exec_func();
            fpw->qm_step = 0;
        } else if (fp_PadTrg(0x800, 2)) {
            co_qmenu_close();
        }
        break;
    }
    if (fpw->flag & 0x40) {
        co_quick_menu_disap();
        fpw->flag &= ~0x40;
    }
    return 0;
}

static int fp_qm_sort_ini(void) {
    msw->step = 0;
    return 0;
}

static int fp_qm_sort_func(void) {
    int i;
    short abc;

    switch (msw->step) {
    case 0:
        msw->step++;
        co_obj_step_set(msw->lr, 2, 0);
        co_obj_step_set(msw->sort_obj, 2, 0);
        fpw->flag &= ~0x10;
        msw->sort_obj = 0;
        func_0017A8A0(0x16);
    case 1:
        if (co_obj_is_exist(msw->lr, msw->lr_obj_id)) {
            return 0;
        }
        for (i = 0; i < 4; i++) {
            if (msw->sort == fp_msm_tab[i]) {
                break;
            }
        }
        msw->sort = fp_msm_tab[(i + 1) % 4];
        fp_ms_create_sel_tab();
        abc = fp_ms_get_abc_kind(msw->old_d_num);
        if (abc) {
            if (msw->abc_open >= 0) {
                fp_ms_close_abc_kind(msw->abc_open);
            }
            fp_ms_open_abc_kind(abc);
        }
        fp_ms_set_cur_lr();
        if (fp_msel_get_sn(msw->sel_tab[msw->cur_lr]) != fp_msel_get_sn(msw->old_d_num)) {
            fp_msel_sd_call(0xF100, 4.0f);
        }
        msw->lr = (void *)co_obj_set(&fp_ms_objf[1], 0, 8);
        msw->lr_obj_id = co_obj_get_id(msw->lr);
        msw->sort_obj = (void *)co_obj_set(&fp_ms_objf[6], 0, 0xA0);
        msw->step++;
    case 2:
        if ((co_obj_step(msw->lr) & 0xFF) == 1) {
            return 1;
        }
        break;
    }
    return 0;
}

static int fp_qm_save_init(void) {
    func_0011EEC0(qmsw, 0x54);
    fpw->flag |= 0x80;
    return 0;
}

static int fp_qm_save_func(void) {
    int val;

    if (qmsw->draw_mcwnd == 1) {
        val = func_001759B0();
        if (qmsw->step == 0) {
            MultiWindowInit();
            MultiWindowCreate(0, 0, 0x5A, pCmes->genwnd_w, pCmes->genwnd_h, 0xF000, -0xC);
            MultiWindowSetMode(0, 1);
            MultiWindowOpen(0);
            CwsWinSetBri(*(void **)0x824450, 0x80);
            qmsw->step++;
        }
        if (val != -1) {
            func_00176F80(0, 0x5A, val, 0x80, 0xF000);
        }
        qmsw->draw_mcwnd = 0;
        if (qmsw->step != 0) {
            MultiWindowCommon();
        }
    }
    if (fp_qm_save_exec() == 1) {
        fpw->flag &= ~0x80;
        return 1;
    }
    return 0;
}

static int fp_qm_save_exec(void) {
    int val;
    int rtn;

    rtn = 0;
    switch (fpw->qm_step) {
    case 0:
        func_001777C0(1, 1);
        func_00175420(&SaveData, 0x1FF50);
        func_00175920();
        qmsw->swap_fg = 0;
        fpw->qm_step++;
        break;
    case 1:
        qmsw->draw_mcwnd = 1;
        if (func_00175590() == 1) {
            func_00177780(1, 1);
            rtn = 1;
        }
        val = func_001759A0();
        if (val == 1) {
            if (qmsw->swap_fg == 0) {
                func_00177BD0(&SaveData);
                qmsw->swap_fg = 1;
                RequestAutoSave = 0;
            }
        }
        break;
    }
    return rtn;
}
