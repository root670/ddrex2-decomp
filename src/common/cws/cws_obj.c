#include "src/common/cws/cws_obj.h"
#include "types/_CWS_WINS_W.h"

float sinf(float x);
struct _CWS_WINS_W *GetWinsAddr(void);
void func_0011EEC0(void *ptr, int size);
void func_00127F60(anon_2_61 *info, int tex_id);
void func_00123950(anon_4_61 *sp);
void func_00124800(anon_1_61 *sp);
void func_001BCFA8(char *fmt, ...);












struct _CWS_OBJ *CwsObjCreate(struct _CWS_OBJ_SET *data) {
    struct _CWS_WINS_W *wins; struct _CWS_OBJ *work; int i;
    wins = GetWinsAddr(); for (i = 0; i < wins->obj_max; i++) { if (wins->obj[i] != 0 && wins->obj[i]->status == 0) { work = wins->obj[i]; goto found; } } func_001BCFA8((char *)"***************************ERR NO OBJ Work\n"); work = 0; found:
    if (work == 0) goto out;
    func_0011EEC0(work, 0x3C);
    work->def = data;
    work->tex_num = data->tex_num;
    work->alpha = data->a;
    work->red = data->r;
    work->green = data->g;
    work->blue = data->b;
    if (data->ptex != 0) {
        work->ptex = data->ptex;
        work->x = work->ptex->x;
        work->y = work->ptex->y;
        work->w = work->ptex->w;
        work->h = work->ptex->h;
        work->tu = work->ptex->tu;
        work->tv = work->ptex->tv;
        work->tw = work->ptex->tw;
        work->th = work->ptex->th;
        work->z = work->ptex->z;
    }
    work->status |= 1;
    work->status |= 2;
out:
    return work;
}
char CwsObjChangePlate(struct _CWS_OBJ *work, struct _CWS_OBJ_TEX *plate) {




























    if (work != 0) {
        work->ptex = plate;
        work->x = work->ptex->x;
        work->y = work->ptex->y;
        work->w = work->ptex->w;
        work->h = work->ptex->h;
        work->tu = work->ptex->tu;
        work->tv = work->ptex->tv;
        work->tw = work->ptex->tw;
        work->th = work->ptex->th;
        work->z = work->ptex->z;
        return 1;
    } else {
        return 0; }
}
char CwsObjSetXYWH(struct _CWS_OBJ *work, int x, int y, int w, int h) {


    if (work != 0) {
        work->x = x;
        work->y = y;
        work->w = w;
        work->h = h;
        return 1;
    } else {
        return 0; }
}
char CwsObjChangeTex(struct _CWS_OBJ *work, int tex_num) {


    if (work != 0) {
        work->tex_num = tex_num;
        return 1;
    } else {
        return 0; }
}


char CwsObjDelete(struct _CWS_OBJ *work) {
    if (work != 0) {
        func_0011EEC0(work, 0x3C);

        return 1;
    } else {
        return 0; }
}










char CwsObjMove(int *_v, int *_timer, int _s, int _end_time, int _type) {
    if (*_timer < _end_time) {
        if (_type == 0) {
            *_v += (int)((float)(_s - *_v) * sinf(3.141592f * (float)*_timer / (float)_end_time));
        } else {
            *_v += (_s - *_v) / (_end_time - *_timer);
        }
        (*_timer)++;
        goto out; }
    *_v = _s;
    return 1;
out:
    return 0;
}


char CwsObjMoveOpt(int *_v, int _timer, int _s, int _end_time, int _type) {
    if (_timer < _end_time) {
        if (_type == 0) {
            *_v += (int)((float)(_s - *_v) * sinf(3.141592f * (float)_timer / (float)_end_time));
        } else {
            *_v += (_s - *_v) / (_end_time - _timer);
        }
        goto out; }
    *_v = _s;
    return 1;
out:
    return 0;
}





void CwsObjDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw) {
    anon_2_61 info;
    anon_4_61 sp2;
    anon_1_61 g3;
    int mx;
    int my;
    int mz;
    int move_x;
    int move_y;
    int dx;
    int dy; int dw; int dh; int tu; int tv; int tw; int th; int dr; int dg; int db; int da; int dz; int i = 0;
    if (objw == 0) return;
    if (!(objw->status & 2)) return;
    if (win->master_link == 0) {
        mx = win->v.x;
        my = win->v.y;
        mz = win->v.z;
        dx = mx + objw->x;
        dy = my + objw->y;
        dz = mz + objw->z;
    } else {
        mx = win->master_link->v.x + win->v.x;
        my = win->master_link->v.y + win->v.y;
        mz = win->master_link->v.z + win->v.z;
        dx = mx + objw->x;
        dy = my + objw->y;
        dz = mz + objw->z;
    }
    dw = objw->w;
    dh = objw->h;
    tu = objw->tu;
    tv = objw->tv;
    tw = objw->tw;
    th = objw->th;

    dr = win->v.r * objw->red * win->v.bri / 0x4000;
    dg = win->v.g * objw->green * win->v.bri / 0x4000;
    db = win->v.b * objw->blue * win->v.bri / 0x4000;
    da = win->v.a * objw->alpha / 0x80;
    if (objw->tex_num >= 0) {
        func_00127F60(&info, objw->tex_num);
        sp2.flg = 0;
        if (!(objw->status & 4)) {

            if (dz != 0) {
                sp2.flg |= 0x100;
            }
        }
        sp2.u = tu; sp2.v = tv;
        sp2.w = tw; sp2.h = th;
        sp2.r0 = dr; sp2.g0 = dg; sp2.b0 = db; sp2.a0 = da;
        sp2.x0.fd = (float)dx; sp2.y0.fd = (float)dy; sp2.z0 = dz;
        sp2.x1.fd = (float)(dx + dw); sp2.y1.fd = (float)(dy + dh); sp2.z1 = dz;
        func_00123950(&sp2);

        if (objw->def->ptex_obj > 1) {
            move_x = objw->x - objw->ptex[0].x;
            move_y = objw->y - objw->ptex[0].y;
            for (i = 1; i < objw->def->ptex_obj; i++) {

                if (objw->ptex[i].flag < -1) return;
                sp2.flg = 0;
                if (!(objw->status & 4)) {
                    sp2.flg |= 0x100;
                }
                sp2.u = objw->ptex[i].tu; sp2.v = objw->ptex[i].tv;
                sp2.w = objw->ptex[i].tw; sp2.h = objw->ptex[i].th;
                sp2.r0 = dr; sp2.g0 = dg; sp2.b0 = db; sp2.a0 = da;
                dx = mx + objw->ptex[i].x + move_x;
                dy = my + objw->ptex[i].y + move_y;
                dw = objw->ptex[i].w;
                dh = objw->ptex[i].h;
                dz = mz + objw->ptex[i].z;
                sp2.x0.fd = (float)dx; sp2.y0.fd = (float)dy; sp2.z0 = dz;
                sp2.x1.fd = (float)(dx + dw); sp2.y1.fd = (float)(dy + dh); sp2.z1 = dz;
                func_00123950(&sp2);
            }
        }
    } else {

        g3.flg = 0;
        if (!(objw->status & 4)) {
            g3.flg |= 0x100;
        }
        g3.x0.fd = (float)dx; g3.y0.fd = (float)dy; g3.z0 = dz;
        g3.x1.fd = (float)(dx + dw); g3.y1.fd = (float)dy; g3.z1 = dz;
        g3.x2.fd = (float)dx; g3.y2.fd = (float)(dy + dh); g3.z2 = dz;
        g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
        g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
        g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
        func_00124800(&g3);
        g3.flg = 0;
        if (!(objw->status & 4)) {
            g3.flg |= 0x100;
        }
        g3.x0.fd = (float)dx; g3.y0.fd = (float)(dy + dh); g3.z0 = dz;
        g3.x1.fd = (float)(dx + dw); g3.y1.fd = (float)dy; g3.z1 = dz;
        g3.x2.fd = (float)(dx + dw); g3.y2.fd = (float)(dy + dh); g3.z2 = dz;
        g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
        g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
        g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
        func_00124800(&g3);

        if (objw->def->ptex_obj > 1) {
            move_x = objw->x - objw->ptex[0].x;
            move_y = objw->y - objw->ptex[0].y;
            for (i = 1; i < objw->def->ptex_obj; i++) {
                dx = mx + objw->ptex[i].x + move_x;
                dy = my + objw->ptex[i].y + move_y;
                dw = objw->ptex[i].w;
                dh = objw->ptex[i].h;
                dz = mz + objw->ptex[i].z;
                g3.flg = 0;
                if (!(objw->status & 4)) {
                    g3.flg |= 0x100;
                }
                g3.x0.fd = (float)dx; g3.y0.fd = (float)dy; g3.z0 = dz;
                g3.x1.fd = (float)(dx + dw); g3.y1.fd = (float)dy; g3.z1 = dz;
                g3.x2.fd = (float)dx; g3.y2.fd = (float)(dy + dh); g3.z2 = dz;
                g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
                g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
                g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
                func_00124800(&g3);
                g3.flg = 0;
                if (!(objw->status & 4)) {
                    g3.flg |= 0x100;
                }
                g3.x0.fd = (float)dx; g3.y0.fd = (float)(dy + dh); g3.z0 = dz;
                g3.x1.fd = (float)(dx + dw); g3.y1.fd = (float)dy; g3.z1 = dz;
                g3.x2.fd = (float)(dx + dw); g3.y2.fd = (float)(dy + dh); g3.z2 = dz;
                g3.r0 = dr; g3.g0 = dg; g3.b0 = db; g3.a0 = da;
                g3.r1 = dr; g3.g1 = dg; g3.b1 = db; g3.a1 = da;
                g3.r2 = dr; g3.g2 = dg; g3.b2 = db; g3.a2 = da;
                func_00124800(&g3);
            }
        }


    }
}
