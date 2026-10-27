#include "src/CS/workout/workout_user.h"

void func_0011EEC0(void *ptr, int size);
void CsFontPuts(short x, short y, unsigned char *str, int bri, int pri, int col, int alpha, int tex_id, int mode);
void wumInit(void);
void wumGetSystemUserWork(void);
void wumSetSystemUserWork(void);
int csWorkoutGetFlagCancel(void);
int wouListtIsFinished(int pno);
int wouUserMenuIsFinished(int pno);
void wouPlayerCardDraw(int pno);
void wouPlayerCardAct(int pno);
void wouPlayerCardTerm(int pno);
void wouPressStartDraw(int pno);
void wouPressStartAct(int pno);
void wouPleaseWaitDraw(int pno);
void wouListInit(int pno);
void wouListAct(int pno);
void wouListDraw(int pno);
void wouListTerm(void);
void wouEditInit(int pno);
void wouEditAct(int pno);
void wouEditDraw(int pno);
void wouEditTerm(int pno);
void wouUserMenuInit(int pno);
void wouUserMenuAct(int pno);
void wouUserMenuDraw(int pno);
void wouUserMenuTerm(void);
void wouUserGuestCautionInit(int pno);
void wouUserGuestCautionAct(int pno);
void wouUserGuestCautionDraw(int pno);
void wouUserGuestCautionTerm(void);
void wouPleaseWaitInit(int pno);
void wouPleaseWaitAct(int pno);
void wouPleaseWaitTerm(void);

static anon_5_235 funclist[8] = {
    {0, 0, 0, 0},
    {wouListInit, wouListAct, wouListDraw, (void (*)(int))wouListTerm},
    {wouEditInit, wouEditAct, wouEditDraw, wouEditTerm},
    {wouEditInit, wouEditAct, wouEditDraw, wouEditTerm},
    {wouUserMenuInit, wouUserMenuAct, wouUserMenuDraw, (void (*)(int))wouUserMenuTerm},
    {wouUserGuestCautionInit, wouUserGuestCautionAct, wouUserGuestCautionDraw, (void (*)(int))wouUserGuestCautionTerm},
    {wouPleaseWaitInit, wouPleaseWaitAct, 0, (void (*)(int))wouPleaseWaitTerm},
    {0, 0, 0, 0},
};

anon_3_235 gwork[2];
anon_6_235 workout_work;

void WouFuncDraw(void) {
    int pno;

    for (pno = 0; pno < 2; pno++) {
        if (gwork[pno].f_Init) {
            wouPlayerCardDraw(pno);
            wouPressStartDraw(pno);
            wouPleaseWaitDraw(pno);
        }
    }
}

void WouFuncAct(void) {
    int pno;

    for (pno = 0; pno < 2; pno++) {
        if (gwork[pno].f_Init) {
            wouPlayerCardAct(pno);
            wouPressStartAct(pno);
        }
    }
}

int WorkoutUser_GetPlayerStatus(int pno) {
    anon_3_235 *gw;

    gw = &gwork[pno];
    return gw->status;
}

void WorkoutUser_SetPlayerStatus(int pno, int status) {
    anon_3_235 *gw;

    gw = &gwork[pno];
    gw->status = status;
}

void WorkoutUser_SetFinish(int pno) {
    anon_3_235 *gw;

    gw = &gwork[pno];
    gw->f_finish = 1;
}

int WorkoutUser_IsCreating(int pno) {
    anon_3_235 *gw;

    gw = &gwork[pno];
    return gw->func_no == 2 || gw->next_func == 2;
}

int WorkoutUser_GetFuncStep(int pno) {
    anon_3_235 *gw;

    gw = &gwork[pno];
    return gw->func_no;
}

void WorkoutUser_SetNextFunc(int pno, int func_no) {
    anon_3_235 *gw;

    gw = &gwork[pno];
    gw->next_func = func_no;
}

anon_0_235 WorkoutUser_Term(void) {
    anon_0_235 sres = {2, 5};
    int pno;
    int i;

    for (pno = 0; pno < 2; pno++) {
        for (i = 0; i < 8; i++) {
            if (funclist[i].term) {
                funclist[i].term(pno);
            }
        }
        wouPlayerCardTerm(pno);
    }
    if (csWorkoutGetFlagCancel()) {
        sres.type = 2;
        sres.param = 11;
    }
    wumSetSystemUserWork();
    return sres;
}

anon_0_235 WorkoutUser_Main(void) {
    anon_0_235 sres = {0, 9};
    int f;
    int pno;
    int i;

    for (pno = 0; pno < 2; pno++) {
        if (gwork[pno].next_func != -1) {
            gwork[pno].func_no = gwork[pno].next_func;
            gwork[pno].next_func = -1;
            gwork[pno].step = 0;
        }
        if (funclist[gwork[pno].func_no].act) {
            funclist[gwork[pno].func_no].act(pno);
        }
    }
    for (pno = 0; pno < 2; pno++) {
        for (i = 0; i < 8; i++) {
            if (funclist[i].draw) {
                funclist[i].draw(pno);
            }
        }
    }
    CsFontPuts(0, -208, (unsigned char *)"SELECT USER", 128, 0, 2, 128, 250, 9216);
    f = gwork[0].f_finish && wouListtIsFinished(0) && wouUserMenuIsFinished(0);
    if (f) {
        f = gwork[1].f_finish && wouListtIsFinished(1) && wouUserMenuIsFinished(1);
    }
    if (f) {
        sres.type = 2;
        sres.param = 9;
    }
    return sres;
}

anon_0_235 WorkoutUser_Init(void) {
    anon_0_235 sres = {2, 4};
    anon_3_235 *gw;
    int pno;
    int i;

    func_0011EEC0(gwork, sizeof(gwork));
    wumInit();
    wumGetSystemUserWork();
    for (pno = 0; pno < 2; pno++) {
        gw = &gwork[pno];
        if (workout_work.player[pno].active) {
            gw->next_func = 1;
            gw->status = 1;
        }
        for (i = 0; i < 8; i++) {
            if (funclist[i].init) {
                funclist[i].init(pno);
            }
        }
        gw->f_Init = 1;
    }
    return sres;
}

void WorkoutUser_DataInit(void) {
    func_0011EEC0(gwork, sizeof(gwork));
}

static int probe_str(unsigned char (*p)[12]) {
    return p[0][0];
}
