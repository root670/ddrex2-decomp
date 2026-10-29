#include "src/common/obj/co_obj.h"

void func_0011EEC0(void *ptr, int size);

void co_obj_all_del(void) {
    co_obj_man.top = 0;
    func_0011EEC0(co_obj_man.ow_addr, co_obj_man.max * 0x280);
}

unsigned char co_obj_own_step(void *work_p) {
    return *(unsigned char *)((unsigned char *)work_p - 4);
}

unsigned char co_obj_step(void *ow) {
    return ((struct CO_OBJ_W *)ow)->step;
}

void co_obj_disp_on_off(void *ow, int on_off) {
    ((struct CO_OBJ_W *)ow)->disp_flag = on_off;
}

void co_obj_step_set(void *ow, int step, void (*init)(void *)) {
    struct CO_OBJ_W *obj_w;
    if (ow == 0)
        return;
    obj_w = (struct CO_OBJ_W *)ow;
    obj_w->step = step;
    obj_w->ini_flag = 0;
    if (init != 0)
        init(obj_w->work);
}

int co_obj_is_exist(void *chk_ow, int id) {
    struct CO_OBJ_W *p;
    p = chk_ow;
    if (p->id != 0)
        goto cmp;
    return 0;
cmp:
    return p->id == id;
}

int co_obj_get_id(void *ow) {
    return ((struct CO_OBJ_W *)ow)->id;
}

void *co_obj_work_p(void *ow) {
    return ((struct CO_OBJ_W *)ow)->work;
}

int co_obj_own_ini_flag(void *work_p) {
    return *(unsigned char *)((unsigned char *)work_p - 1);
}

int co_obj_ini_flag(void *chk_ow) {
    return ((struct CO_OBJ_W *)chk_ow)->ini_flag;
}

void *co_obj_del(void *del_ow) {
    struct CO_OBJ_W *ow;
    struct CO_OBJ_W *prev;
    anon_1_99 *man;
    ow = co_obj_man.top;
    prev = 0;
    man = &co_obj_man;
    while (ow != 0) {
        if (ow == del_ow) {
            if (ow == man->top) {
                if (ow->next != 0)
                    man->top = ow->next;
                else
                    man->top = 0;
            } else {
                prev->next = ow->next;
            }
            ow->id = 0;
            return ow->next;
        }
        prev = ow;
        ow = ow->next;
    }
    return 0;
}

static __inline struct CO_OBJ_W *co_obj_free_ow(void) {
    struct CO_OBJ_W *p;
    unsigned int i;
    p = co_obj_man.ow_addr;
    for (i = 0; i < co_obj_man.max; i++) {
        if (p->id == 0)
            return p;
        p++;
    }
    return 0;
}

void *co_obj_set(anon_1fa6d74458f3 *func, void (*init)(void *), unsigned char pri) {
    struct CO_OBJ_W *p;
    struct CO_OBJ_W *ow;
    struct CO_OBJ_W *prev;
    struct CO_OBJ_W *next;
    int prev_flg;
    anon_1_99 *man;
    p = co_obj_free_ow();
    prev = 0;
    prev_flg = 0;
    man = &co_obj_man;
    if (p == 0) {
        return;
    }
    ow = man->top;
    while (ow != 0) {
        if (pri < ow->pri) {
            prev_flg = 1;
            break;
        }
        if (ow->next == 0)
            break;
        prev = ow;
        ow = ow->next;
    }
    if (man->obj_id == 0)
        man->obj_id++;
    p->id = man->obj_id;
    man->obj_id++;
    p->disp_flag = 1;
    p->ini_flag = 0;
    p->pri = pri;
    p->step = 0;
    p->f = func;
    if (ow == 0) {
        man->top = p;
        p->next = 0;
    } else if (prev_flg) {
        if (prev != 0)
            prev->next = p;
        p->next = ow;
        if (ow == man->top)
            man->top = p;
    } else {
        next = ow->next;
        ow->next = p;
        p->next = next;
    }
    func_0011EEC0(p->work, 0x270);
    if (init != 0)
        init(p->work);
    return p;
}

void co_obj_disp(void) {
    struct CO_OBJ_W *ow;
    for (ow = co_obj_man.top; ow != 0; ow = ow->next) {
        if (ow->disp_flag == 0)
            continue;
        if (ow->f->disp == 0)
            continue;
        if (ow->step != 0 || ow->ini_flag != 0)
            ow->f->disp(ow->work);
    }
}

void co_obj_exec(void) {
    struct CO_OBJ_W *ow;
    ow = co_obj_man.top;
    while (ow != 0) {
        switch (ow->step) {
        case 0:
            if (ow->f->appr != 0) {
                if (ow->f->appr(ow->work) == 0)
                    goto ini1;
            }
            ow->ini_flag = 0;
            ow->step++;
        case 1:
            if (ow->f->exec == 0)
                goto ini1;
            if (ow->f->exec(ow->work) == 0)
                goto ini1;
            ow->step++;
            ow->ini_flag = 0;
        case 2:
            if (ow->f->disap != 0) {
                if (ow->f->disap(ow->work) == 0)
                    goto ini1;
            }
            ow = co_obj_del(ow);
            if (ow == 0)
                return;
            continue;
        case 3:
        default:
        ini1:
            ow->ini_flag = 1;
            break;
        }
        ow = ow->next;
    }
}

unsigned int co_obj_init(unsigned char *addr, unsigned int num) {
    unsigned int size;
    size = num * 0x280;
    co_obj_man.top = 0;
    co_obj_man.ow_addr = (struct CO_OBJ_W *)addr;
    co_obj_man.max = num;
    co_obj_man.obj_id = 1;
    func_0011EEC0(co_obj_man.ow_addr, size);
    return size;
}
