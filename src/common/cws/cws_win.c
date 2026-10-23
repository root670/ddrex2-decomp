#include "src/common/cws/cws_win.h"

float sinf(float x);
struct _CWS_WINS_W *GetWinsAddr(void);
void func_0011EEC0(void *ptr, int size);
void func_001BCFA8(char *fmt, ...);
char CwsStrDelete(struct _CWS_WIN_W *win, int str_num);
char CwsObjDelete(struct _CWS_OBJ *work);
char CwsObjMoveOpt(int *_v, int _timer, int _s, int _end_time, int _type);
char CwsObjMove(int *_v, int *_timer, int _s, int _end_time, int _type);

void CwsWinDestroy(struct _CWS_WIN_W *win) {
    win->step[0] = 2;
}

void CwsWinClose(struct _CWS_WIN_W *win) {
    int i;
    int char_pack = 0;
    switch (win->mode) {
    case 0:
        switch (win->step[2]) {
        case 0:
            win->timer = 0;
            win->s.a = 0;
            win->step[2] = 1;
        case 1:
            char_pack = win->v.a;
            if (CwsObjMove(&char_pack, &win->timer, win->s.a, 20, 0)) {
                win->step[2] = 2;
            }
            win->v.a = char_pack;
            break;
        case 2:
        default:
            win->status &= ~2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->status &= ~2;
                }
            }
            win->s.a = 0x80;
            win->v.a = 0x80;
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 1:
        win->status &= ~2;
        for (i = 0; i < 16; i++) {
            if (win->str[i] != 0) {
                win->str[i]->status &= ~2;
            }
        }
        win->s.a = 0x80;
        win->v.a = 0x80;
        win->step[1] = 0;
        win->step[2] = 0;
        break;
    case 2:
        switch (win->step[2]) {
        case 0:
            win->timer = 0;
            win->s.x = win->v.x - 0x32;
            win->s.a = 0;
            win->step[2] = 1;
        case 1:
            char_pack = win->v.a;
            CwsObjMoveOpt(&char_pack, win->timer, win->s.a, 20, 0);
            win->v.a = char_pack;
            if (CwsObjMove(&win->v.x, &win->timer, win->s.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->status &= ~2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->status &= ~2;
                }
            }
            win->v.x = win->s.x = win->def.x;
            win->s.a = 0x80;
            win->v.a = 0x80;
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 3:
        switch (win->step[2]) {
        case 0:
            win->timer = 0;
            win->s.x = win->v.x + 0x32;
            win->s.a = 0;
            win->step[2] = 1;
        case 1:
            char_pack = win->v.a;
            CwsObjMoveOpt(&char_pack, win->timer, win->s.a, 20, 0);
            win->v.a = char_pack;
            if (CwsObjMove(&win->v.x, &win->timer, win->s.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->status &= ~2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->status &= ~2;
                }
            }
            win->v.x = win->s.x = win->def.x;
            win->s.a = 0x80;
            win->v.a = 0x80;
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 4:
        switch (win->step[2]) {
        case 0:
            win->timer = 0;
            win->s.x = win->v.x - 0x280;
            win->step[2] = 1;
        case 1:
            if (CwsObjMove(&win->v.x, &win->timer, win->s.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->status &= ~2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->status &= ~2;
                }
            }
            win->v.x = win->s.x = win->def.x;
            win->s.a = 0x80;
            win->v.a = 0x80;
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 5:
        switch (win->step[2]) {
        case 0:
            win->timer = 0;
            win->s.x = win->v.x + 0x280;
            win->step[2] = 1;
        case 1:
            if (CwsObjMove(&win->v.x, &win->timer, win->s.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->status &= ~2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->status &= ~2;
                }
            }
            win->v.x = win->s.x = win->def.x;
            win->s.a = 0x80;
            win->v.a = 0x80;
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    }
}

void CwsWinOpen(struct _CWS_WIN_W *win) {
    int i;
    int char_pack = 0;
    switch (win->mode) {
    case 0:
        switch (win->step[2]) {
        case 0:
            win->status |= 2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->a = 0x80;
                    win->str[i]->status |= 2;
                }
            }
            win->s.a = 0;
            win->v.a = 0;
            win->timer = 0;
            win->step[2] = 1;
        case 1:
            char_pack = win->v.a;
            if (CwsObjMove(&char_pack, &win->timer, 0x80, 20, 0)) {
                win->step[2] = 2;
            }
            win->v.a = char_pack;
            break;
        case 2:
        default:
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 1:
        win->status |= 2;
        for (i = 0; i < 16; i++) {
            if (win->str[i] != 0) {
                win->str[i]->a = 0x80;
                win->str[i]->status |= 2;
            }
        }
        win->s.a = 0x80;
        win->v.a = 0x80;
        win->step[1] = 0;
        win->step[2] = 0;
        break;
    case 2:
        switch (win->step[2]) {
        case 0:
            win->status |= 2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->a = 0x80;
                    win->str[i]->status |= 2;
                }
            }
            win->v.x = win->s.x = win->def.x - 0x32;
            win->s.a = 0;
            win->v.a = 0;
            win->timer = 0;
            win->step[2] = 1;
        case 1:
            char_pack = win->v.a;
            CwsObjMoveOpt(&char_pack, win->timer, 0x80, 20, 0);
            win->v.a = char_pack;
            if (CwsObjMove(&win->v.x, &win->timer, win->def.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 3:
        switch (win->step[2]) {
        case 0:
            win->status |= 2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->a = 0x80;
                    win->str[i]->status |= 2;
                }
            }
            win->v.x = win->s.x = win->def.x + 0x32;
            win->s.a = 0;
            win->v.a = 0;
            win->timer = 0;
            win->step[2] = 1;
        case 1:
            char_pack = win->v.a;
            CwsObjMoveOpt(&char_pack, win->timer, 0x80, 20, 0);
            win->v.a = char_pack;
            if (CwsObjMove(&win->v.x, &win->timer, win->def.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 4:
        switch (win->step[2]) {
        case 0:
            win->status |= 2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->a = 0x80;
                    win->str[i]->status |= 2;
                }
            }
            win->v.x = win->s.x = win->def.x - 0x280;
            win->timer = 0;
            win->step[2] = 1;
        case 1:
            if (CwsObjMove(&win->v.x, &win->timer, win->def.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    case 5:
        switch (win->step[2]) {
        case 0:
            win->status |= 2;
            for (i = 0; i < 16; i++) {
                if (win->str[i] != 0) {
                    win->str[i]->a = 0x80;
                    win->str[i]->status |= 2;
                }
            }
            win->v.x = win->s.x = win->def.x + 0x280;
            win->timer = 0;
            win->step[2] = 1;
        case 1:
            if (CwsObjMove(&win->v.x, &win->timer, win->def.x, 20, 0)) {
                win->step[2] = 2;
            }
            break;
        case 2:
        default:
            win->step[1] = 0;
            win->step[2] = 0;
            break;
        }
        break;
    }
}

char cws_win_move_xywh(struct _CWS_WIN_W *work, int _end_time) {
    if (work->status & 0xF0) {
        if (work->timer < _end_time) {
            if (work->status & 0x10) {
                if (work->status & 0x100) {
                    work->v.x += (work->s.x - work->v.x) / (_end_time - work->timer);
                } else {
                    work->v.x += (int)((work->s.x - work->v.x) * sinf(3.141592f * work->timer / _end_time));
                }
            }
            if (work->status & 0x20) {
                if (work->status & 0x100) {
                    work->v.y += (work->s.y - work->v.y) / (_end_time - work->timer);
                } else {
                    work->v.y += (int)((work->s.y - work->v.y) * sinf(3.141592f * work->timer / _end_time));
                }
            }
            if (work->status & 0x40) {
                if (work->status & 0x100) {
                    work->v.w += (work->s.w - work->v.w) / (_end_time - work->timer);
                } else {
                    work->v.w += (int)((work->s.w - work->v.w) * sinf(3.141592f * work->timer / _end_time));
                }
            }
            if (work->status & 0x80) {
                if (work->status & 0x100) {
                    work->v.h += (work->s.h - work->v.h) / (_end_time - work->timer);
                } else {
                    work->v.h += (int)((work->s.h - work->v.h) * sinf(3.141592f * work->timer / _end_time));
                }
            }
            work->timer++;
        } else {
            if (work->status & 0x10) {
                work->v.x = work->s.x;
                work->status &= ~0x10;
            }
            if (work->status & 0x20) {
                work->v.y = work->s.y;
                work->status &= ~0x20;
            }
            if (work->status & 0x40) {
                work->v.w = work->s.w;
                work->status &= ~0x40;
            }
            if (work->status & 0x80) {
                work->v.h = work->s.h;
                work->status &= ~0x80;
            }
            work->status &= ~0x100;
            return 1;
        }
    }
    return 0;
}

char CwsWinDelete(struct _CWS_WIN_W *work) {
    int i;
    if (work != 0 && work->func != 0) {
        for (i = 0; i < 16; i++) {
            CwsStrDelete(work, i);
        }
        for (i = 0; i < 16; i++) {
            CwsObjDelete(work->obj[i]);
        }
        func_0011EEC0(work, 0x158);
        return 1;
    }
    return 0;
}

char CwsWinMoveH(struct _CWS_WIN_W *work, unsigned int h, int flg) {
    if (work != 0 && !(work->status & 0x80)) {
        work->s.h = h;
        work->timer = 0;
        work->status |= 0x80;
        if (flg) {
            work->status |= 0x100;
        }
        return 1;
    }
    return 0;
}

char CwsWinMoveW(struct _CWS_WIN_W *work, unsigned int w, int flg) {
    if (work != 0 && !(work->status & 0x40)) {
        work->s.w = w;
        work->timer = 0;
        work->status |= 0x40;
        if (flg) {
            work->status |= 0x100;
        }
        return 1;
    }
    return 0;
}

char CwsWinSetRGBA(struct _CWS_WIN_W *work, unsigned int rgba) {
    if (work != 0) {
        work->v.r = work->s.r = rgba >> 24;
        work->v.g = work->s.g = rgba >> 16;
        work->v.b = work->s.b = rgba >> 8;
        work->v.a = work->s.a = rgba;
        return 1;
    }
    return 0;
}

char CwsWinSetBri(struct _CWS_WIN_W *work, int bri) {
    if (work != 0) {
        work->v.bri = work->s.bri = bri;
        return 1;
    }
    return 0;
}

char CwsWinSetPri(struct _CWS_WIN_W *work, int z) {
    if (work != 0) {
        work->v.z = work->s.z = z;
        return 1;
    }
    return 0;
}

char CwsWinSetWH(struct _CWS_WIN_W *work, int w, int h) {
    if (work != 0) {
        work->v.w = work->s.w = w;
        work->v.h = work->s.h = h;
        return 1;
    }
    return 0;
}

char CwsWinSetXY(struct _CWS_WIN_W *work, int x, int y) {
    if (work != 0) {
        work->v.x = work->s.x = x;
        work->v.y = work->s.y = y;
        return 1;
    }
    return 0;
}

char CwsWinDefSetXYWH(struct _CWS_WIN_W *work, int x, int y, int w, int h) {
    if (work != 0) {
        work->def.x = x;
        work->def.y = y;
        work->def.w = w;
        work->def.h = h;
        return 1;
    }
    return 0;
}

struct _CWS_WIN_W *CwsWinCreate(void *func, int x, int y, int w, int h, int z) {
    struct _CWS_WINS_W *wins_work;
    struct _CWS_WIN_W *work;
    int i;
    wins_work = GetWinsAddr();
    for (i = 0; i < wins_work->win_max; i++) {
        if (wins_work->win[i] != 0 && wins_work->win[i]->status == 0) {
            work = wins_work->win[i];
            func_0011EEC0(work, 0x158);
            work->func = (int (*)(struct _CWS_WIN_W *))func;
            work->def.x = work->v.x = work->s.x = x;
            work->def.y = work->v.y = work->s.y = y;
            work->v.z = work->s.z = z;
            work->def.w = work->v.w = work->s.w = w;
            work->def.h = work->v.h = work->s.h = h;
            work->v.bri = work->s.bri = 0x80;
            work->v.a = work->s.a = 0x80;
            work->v.b = work->s.b = 0x80;
            work->v.g = work->s.g = 0x80;
            work->v.r = work->s.r = 0x80;
            work->status |= 1;
            work->func(work);
            return work;
        }
    }
    func_001BCFA8((char *)"***************************ERR NO WIN Work\n");
    return 0;
}

void CwsWinReflash(struct _CWS_WIN_W *work) {
    if (work != 0) {
        work->v.x = work->s.x = work->def.x;
        work->v.y = work->s.y = work->def.y;
        work->v.w = work->s.w = work->def.w;
        work->v.h = work->s.h = work->def.h;
    }
}

char CwsWinSetCode(struct _CWS_WIN_W *work, char _code) {
    if (work != 0) {
        work->code = _code;
        return 1;
    }
    return 0;
}

unsigned int CwsWinGetStatus(struct _CWS_WIN_W *work) {
    unsigned int get_flag = 0;
    if (work != 0) {
        if (work->status & 1) {
            get_flag |= 1;
        }
        if (work->status & 2) {
            get_flag |= 2;
        }
        if (work->status & 0xF0) {
            get_flag |= 0x10;
        }
        if (work->step[1] == 1) {
            get_flag |= 4;
        }
        if (work->step[1] == 2) {
            get_flag |= 8;
        }
        if ((get_flag & 2) && !work->step[1] && !(get_flag & 0x10)) {
            get_flag |= 0x80;
        }
        if (!(get_flag & 2) && !work->step[1] && !(get_flag & 0x10)) {
            get_flag |= 0x40;
        }
    }
    return get_flag;
}
