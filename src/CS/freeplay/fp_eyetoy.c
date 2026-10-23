#include "src/CS/freeplay/fp_eyetoy.h"

float dptofp(double d);
void func_0017A8A0(int kind);
void co_cursor01_disp(struct _tag_cCoCursor01 *p, float x, float y, int a, int bri, int pri, int tex_id, int flag);
unsigned char *fp_OutStrGet(int id);
extern void *D_00824450[];

static anon_4_70 fp_es_objf[2] = {
    {
        fp_es_item_func,
        fp_es_item_func,
        fp_es_item_func,
        fp_es_item_disp,
    },
    {
        (int (*)(void *))fp_es_warn_apper,
        (int (*)(void *))fp_es_warn_exec,
        (int (*)(void *))fp_es_warn_disap,
        (int (*)(void *))fp_es_warn_disp,
    },
};

void fp_eyetoy_sel_init_all(void) {
    if (!(g_game_w.eyetoy_flag & 1))
        etw->cur = 0;
    else
        etw->cur = 1;
}

void fp_eyetoy_sel_init(void) {
    etw->timer = 0;
    fpw->step_s = 0;
    if (!(fpw->flag & 8)) {
        fpw->flag |= 8;
        func_0017A8A0(0x056E00A5);
    }
}

static inline int fp_es_open(void) {
    if (!etw->timer && !etw->item)
        etw->item = (void *)co_obj_set(&fp_es_objf[0], 0, 0xD0);
    if (etw->item && (co_obj_step(etw->item) & 0xFF) == 1 && fpw->fade_step == 2)
        return 1;
    return 0;
}

static inline int fp_es_wait(void) {
    if (!etw->timer && etw->item) {
        co_obj_step_set(etw->item, 2, 0);
        etw->item = 0;
    }
    if (fpw->next_step == 0xC) {
        if (etw->timer++ >= 0x10)
            return 1;
    } else if (etw->timer++ > 0)
        return 1;
    return 0;
}

int fp_eyetoy_sel_step(void) {
    switch (fpw->step_s) {
    case 0:
        if (!fp_es_open())
            return 1;
        fpw->step_s = 1;
        break;
    case 1:
        break;
    case 2:
        if (fp_es_wait())
            return fpw->next_step;
        return 1;
    }
    if (fp_PadTrg(0xA000, 2)) {
        etw->cur ^= 1;
        func_0017A8A0(0x64);
    }
    if (fp_PadTrg(0x60, 2)) {
        fpw->next_step = 2;
        etw->timer = 0;
        fpw->step_s = 2;
        func_0017A8A0(3);
    } else if (fp_cancel_quit_check()) {
        fpw->next_step = 0xC;
        etw->timer = 0;
        fpw->step_s = 2;
        func_0017A8A0(0x63);
    }
    return 1;
}

void fp_eyetoy_sel_finish(void) {
}

void fp_eyetoy_sel_finish_all(void) {
    if (fpw->flag & 1) {
        if (etw->cur) {
            g_game_w.eyetoy_flag |= 1;
            if (stw->cur == 3) {
                g_game_w.eyetoy_flag &= ~4;
                g_game_w.eyetoy_flag |= 8;
            } else {
                g_game_w.eyetoy_flag &= ~8;
                g_game_w.eyetoy_flag |= 4;
            }
        } else {
            g_game_w.eyetoy_flag = 0;
        }
    }
    if (etw->cur) {
        g_game_w.eyetoy_flag &= ~2;
        if (stw->cur == 3) {
            g_game_w.eyetoy_flag |= 8;
            if (!msw->cur_ud[fpw->start_pid])
                g_game_w.hand_solo_seq_kind = 1;
            else
                g_game_w.hand_solo_seq_kind = 0;
        } else {
            g_game_w.eyetoy_flag &= ~8;
        }
    }
}

static int fp_es_item_func(void *w) {
    anon_9_70 *iw;
    unsigned char *str;

    iw = w;
    if (!co_obj_own_ini_flag(w)) {
        if ((co_obj_own_step(w) & 0xFF) == 0) {
            MultiWindowInit();
            iw->win = (struct _CWS_WIN_W *)MultiWindowCreate(0, 0, -0xA, 0x1CC, 0x118, 0xA000, -1);
            iw->win = (struct _CWS_WIN_W *)D_00824450[0];
            MultiWindowSetMode(0, 0);
            str = fp_OutStrGet(0x27);
            CwsStrSetAll(iw->win, 0, 0, -0x7C, 0, 0x80, 0x80, 0x400, 2, 0, str);
            str = fp_OutStrGet(0x25);
            CwsStrSetAll(iw->win, 1, -0x28, -0x5A, 0, 0x80, 0x80, 0x400, 2,
                         etw->cur ? 6 : 0, str);
            str = fp_OutStrGet(0x26);
            CwsStrSetAll(iw->win, 2, 0x28, -0x5A, 0, 0x80, 0x80, 0x400, 2,
                         etw->cur ? 0 : 6, str);
            MultiWindowOpen(0);
            co_cursor01_init(&iw->cur_w);
            return 0;
        }
        if ((co_obj_own_step(w) & 0xFF) == 2) {
            MultiWindowClose(0);
            return 0;
        }
    }
    CwsStrSetCol(iw->win, 1, etw->cur ? 6 : 0);
    CwsStrSetCol(iw->win, 2, etw->cur ? 0 : 6);
    if ((co_obj_own_step(w) & 0xFF) == 0) {
        if (!(CwsWinGetStatus(iw->win) & 4))
            return 1;
    } else if ((co_obj_own_step(w) & 0xFF) == 2) {
        if (!(CwsWinGetStatus(iw->win) & 8)) {
            MultiWindowDelete(0);
            return 1;
        }
    }
    return 0;
}

static int fp_es_item_disp(void *w) {
    anon_5_70 sp;
    anon_9_70 *iw;
    struct tex_bind *bp;
    unsigned char alpha;

    iw = w;
    bp = &tex_bind[68];
    MultiWindowCommon();
    alpha = iw->win->v.a;
    if ((co_obj_own_step(w) & 0xFF) == 2 && !(CwsWinGetStatus(iw->win) & 8))
        alpha = 0;
    fp_sel_tex_set(0, fpw->tex_start + 0x1C);
    sp.flg = 0;
    sp.flg |= 0x100;
    sp.r0 = 0x80;
    sp.g0 = 0x80;
    sp.b0 = 0x80;
    sp.a0 = alpha;
    sp.w = 168.0f;
    sp.h = 160.0f;
    sp.x0.fd = -84.0f;
    sp.y0.fd = -50.0f;
    sp.z0 = 0xA000;
    sp.u = 0;
    sp.v = 0;
    func_00123CF0(&sp);
    co_cursor01_disp(&iw->cur_w, dptofp(etw->cur ? -68.0 : 18.0), -88.0f, alpha,
                     0x80, 0xA000, bp->id, 2);
    return 0;
}

static int fp_es_warn_apper(void) {
    return 1;
}

static int fp_es_warn_exec(void) {
    return 0;
}

static int fp_es_warn_disap(void) {
    return 1;
}

static int fp_es_warn_disp(void) {
    return 0;
}
