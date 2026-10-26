#include "src/common/co_qmenu.h"

unsigned char co_obj_own_step(void *work_p);
int co_obj_is_exist(void *chk_ow, int id);
int co_obj_get_id(void *ow);
void *co_obj_del(void *del_ow);
void *co_obj_set(anon_7_107 *func, void (*init)(void *), unsigned char pri);
void co_obj_step_set(void *ow, int step, void (*init)(void *));
void func_0017A8A0(int se);
void func_001B7C30(void *p, int n);
void co_cursor01_init(struct _tag_cCoCursor01 *p);
void co_cursor01_disp(struct _tag_cCoCursor01 *p, float x, float y, int a, int bri, int pri, int tex_id, int flag);

static inline int ex(anon_6_107 *q) {
    if (q->obj_p == 0) return 0;
    return co_obj_is_exist(q->obj_p, q->obj_id);
}

static int co_qmenu_disp(void *wp);
static int co_qmenu_exec(void *w);

static anon_7_107 co_qmenu_objf = {
    (int (*)(void *))co_qmenu_exec,
    (int (*)(void *))co_qmenu_exec,
    (int (*)(void *))co_qmenu_exec,
    (int (*)(void *))co_qmenu_disp,
};
static anon_6_107 co_qmenu_w;
static anon_6_107 *qmw = &co_qmenu_w;

void co_quick_menu_init(void) {
    func_001B7C30(qmw, 0x40);
}

void co_quick_menu_set(anon_0_107 **qdp, unsigned short pri, unsigned char obj_pri) {
    anon_0_107 **qd;
    unsigned char num;

    num = 0;
    if (qdp) {
        qd = qdp;
        for (;;) {
            if (*qd == 0) break;
            num++;
            qd++;
        }
        if (num) {
            if (ex(qmw)) co_obj_del(qmw->obj_p);
            qmw->obj_p = 0;
            qmw->obj_id = 0;
            qmw->stat = 0;
            qmw->num = num;
            qmw->qd = qdp;
            qmw->tmp_func = 0;
            qmw->func_req = 0;
            qmw->close_req = 0;
            qmw->open_req = 0;
            qmw->y0 = -80.0f;
            qmw->w = 0;
            qmw->max_w = 180.0f;
            qmw->h = 24.0f + 24.0f * qmw->num;
            if (qmw->h < 104.0f) qmw->h = 104.0f;
            qmw->stat = 1;
            qmw->z = pri;
            qmw->qw00_tex_id = -1;
            qmw->cur01_tex_id = -1;
            qmw->csxx20_tex_id = -1;
            qmw->obj_p = co_obj_set(&co_qmenu_objf, 0, obj_pri);
            qmw->obj_id = co_obj_get_id(qmw->obj_p);
            co_cursor01_init(&qmw->cur_w);
        }
    }
}

void co_quick_menu_disap(void) {
    if (ex(qmw)) {
        co_obj_step_set(qmw->obj_p, 2, 0);
        qmw->stat = 1;
    }
}

void co_quick_menu_data_set(anon_0_107 **qdp) {
    anon_0_107 **qd;
    int num;

    num = 0;
    qd = qdp;
    if (qdp) {
        if (ex(qmw))
        for (;;) {
            if (*qd == 0) break;
            num++;
            qd++;
        }
        if (num) {
            qmw->num = num;
            qmw->cur = 0;
            qmw->qd = qdp;
            qmw->tmp_func = 0;
            qmw->h = 24.0f + 24.0f * qmw->num;
            if (qmw->h < 104.0f) qmw->h = 104.0f;
        }
    }
}

void co_qmenu_set_width(float width) {
    if (width >= 11.0f) qmw->max_w = width;
}

void co_qmenu_set_y(float y0) {
    qmw->y0 = y0;
}

unsigned char co_qmenu_get_stat(void) {
    return qmw->stat;
}

void co_qmenu_open(void) {
    qmw->open_req = 1;
}

void co_qmenu_close(void) {
    qmw->close_req = 1;
}

void co_qmenu_cursor_set(unsigned char cur) {
    if (qmw->cur > cur) qmw->cur = cur;
}

void co_qmenu_cursor_inc(void) {
    if (qmw->num != qmw->cur + 1) {
        func_0017A8A0(100);
        qmw->cur++;
    }
}

void co_qmenu_cursor_dec(void) {
    if (qmw->cur) {
        func_0017A8A0(100);
        qmw->cur--;
    }
}

unsigned char co_qmenu_cursor_get(void) {
    return qmw->cur;
}

void co_qmenu_exec_func(void) {
    qmw->func_req = qmw->cur + 1;
}

static int co_qmenu_exec(void *w) {
    anon_5_107 *w1;
    anon_0_107 *qd;

    w1 = (anon_5_107 *)w;
    switch (co_obj_own_step(w)) {
    case 0:
        w1->alpha += 32.0f;
        if (w1->alpha >= 128.0f) {
            w1->alpha = 128.0f;
            qmw->stat = 2;
            return 1;
        }
        return 0;
    case 2:
        w1->alpha -= 32.0f;
        if (w1->alpha <= 0.0f) {
            qmw->stat = 0;
            qmw->obj_p = 0;
            qmw->obj_id = 0;
            return 1;
        }
        return 0;
    }
    switch (qmw->stat) {
    case 2:
        if (qmw->open_req) {
            qmw->stat = 3;
            w1->t = 0;
            qmw->open_req = 0;
            func_0017A8A0(0x6B);
        }
        break;
    case 3:
        w1->t += 1.0f;
        if (w1->t >= 4.0f) {
            qmw->w = qmw->max_w;
            qmw->stat = 4;
        } else {
            qmw->w = qmw->max_w * w1->t / 4.0f;
        }
        break;
    case 6:
        w1->t -= 1.0f;
        if (w1->t <= 0.0f) {
            qmw->w = 0.0f;
            qmw->stat = 2;
        } else {
            qmw->w = qmw->max_w * w1->t / 4.0f;
        }
        break;
    case 4:
        if (qmw->close_req) {
            qmw->stat = 6;
            w1->t = 4.0f;
            qmw->close_req = 0;
            func_0017A8A0(0x6B);
        } else if (qmw->func_req) {
            qd = qmw->qd[qmw->func_req - 1];
            if (qd->func) {
                qmw->tmp_func = qd->func;
                qmw->stat = 5;
                if (qd->ini) qd->ini();
                func_0017A8A0(3);
            }
            qmw->func_req = 0;
        }
        break;
    case 5:
        if (qmw->tmp_func()) qmw->stat = 4;
        break;
    }
    return 0;
}

static int co_qmenu_disp(void *wp) {
    return 0;
}
