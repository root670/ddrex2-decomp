#include "src/CS/workout/workout_message.h"

void func_001B7C30(void *ptr, int size);
int func_00171E40(void);
char CwsStrSetPri(struct _CWS_WIN_W *win, int str_num, int z);
unsigned int CwsWinGetStatus(struct _CWS_WIN_W *work);
char CwsStrSetDispStatus(struct _CWS_WIN_W *win, int str_num, char on_off);
char CwsStrSetX(struct _CWS_WIN_W *win, int str_num, int x);
char CwsStrSetY(struct _CWS_WIN_W *win, int str_num, int y);
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string);
char CwsStrSetFontType(struct _CWS_WIN_W *win, int str_num, int font_type);
char CwsStrSetFlag(struct _CWS_WIN_W *win, int str_num, unsigned int flag);
void MultiWindowDelete(int win_num);
void MultiWindowOpen(int win_num);
void MultiWindowClose(int win_num);
struct _MULTI_WIN_W *MultiWindowCreate(int win_num, int x, int y, int w, int h, int z, int tex_num);
#define D_00824450 ((struct _CWS_WIN_W **)0x00824450)

static anon_0_241 msgdata_us[26] = {
    {(unsigned char *)""},
    {(unsigned char *)"Select a user file."},
    {(unsigned char *)"Start game as a guest \nuser."},
    {(unsigned char *)"Create a new user."},
    {(unsigned char *)"Password ON/OFF"},
    {(unsigned char *)"Enter password"},
    {(unsigned char *)"Incorrect password"},
    {(unsigned char *)"Password \ndoes not match."},
    {(unsigned char *)"Create a new user with \nthese settings. Ok?"},
    {(unsigned char *)"Delete this user. Ok?"},
    {(unsigned char *)"Create user with these settings."},
    {(unsigned char *)"Turn SIMULTANEOUS STEPS \noff and Simultaneous Step \narrows will not be shown."},
    {(unsigned char *)"Start game."},
    {(unsigned char *)"Edit user data."},
    {(unsigned char *)"Exit Workout Mode."},
    {(unsigned char *)"Workout Play"},
    {(unsigned char *)"Records"},
    {(unsigned char *)"Select character icon."},
    {(unsigned char *)"Select frame tag color."},
    {(unsigned char *)"Use this password?"},
    {(unsigned char *)"Enter password."},
    {(unsigned char *)"Enter password again."},
    {(unsigned char *)"SIMULTANEOUS STEPS"},
    {(unsigned char *)"Delete user data."},
    {(unsigned char *)""},
    {0},
};

anon_0_241 *msgdata_list[8] = {
    {0},
    {msgdata_us},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
};

static anon_0_241 *pmsgdata = 0;

anon_1_241 msgwin[2];

unsigned char *WorkoutMsgGetStr(int msg_no) {
    pmsgdata = msgdata_list[func_00171E40()];
    return pmsgdata[msg_no].message;
}

void WorkoutMsgSet(int win_no, int str_no, int msg_no, int type, unsigned int flag, int pri) {
    struct _CWS_WIN_W *ww;

    ww = D_00824450[win_no];
    CwsStrSetPri(ww, str_no, pri);
    if ((CwsWinGetStatus(ww) & 0xC) == 0) {
        CwsStrSetDispStatus(ww, str_no, 1);
    }
    if (flag & 0x400) {
        CwsStrSetX(ww, str_no, 0);
    } else {
        CwsStrSetX(ww, str_no, -ww->s.w / 2 + 0x10);
    }
    CwsStrSetY(ww, str_no, -ww->s.h / 2 + 0x8);
    pmsgdata = msgdata_list[func_00171E40()]; CwsStrSetString(ww, str_no, pmsgdata[msg_no].message);
    CwsStrSetFontType(ww, str_no, type);
    CwsStrSetFlag(ww, str_no, flag);
}

void WorkoutMsgWinClose(int pno) {
    msgwin[pno].step = 10;
}

void WorkoutMsgWinOpen(int pno) {
    msgwin[pno].step = 1;
}

void WorkoutMsgWinTerm(void) {
    int pno;

    for (pno = 0; pno < 2; pno++) {
        MultiWindowDelete(pno);
    }
}

void WorkoutMsgWinMain(void) {
    int pno;

    for (pno = 0; pno < 2;) {
        switch (msgwin[pno].step) {
        case 1:
            MultiWindowOpen(pno);
            msgwin[pno].step++;
            break;
        case 10:
            MultiWindowClose(pno);
            msgwin[pno].step = 0;
            break;
        }
        pno++;
    }
}

void WorkoutMsgWinInit(void) {
    int pno;

    func_001B7C30(msgwin, 8);
    for (pno = 0; pno < 2; pno++) {
        MultiWindowCreate(pno, pno * 0x140 - 0xA0, 0x88, 0x12A, 0x60, 0x80, -1);
    }
}
