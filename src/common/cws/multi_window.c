#include "src/common/cws/multi_window.h"
#define D_00824450 (*(struct _MULTI_WIN_W *)0x824450)
#define D_00824470 ((char *)0x824470)
void func_0011EEC0(void *ptr, int size);
unsigned int CwsWinsCreate(unsigned int _top_addr, int init_type);
void CwsWinsDelete(void);
void CwsWins_Func(void);
struct _CWS_WIN_W *CwsWinCreate(void *func, int x, int y, int w, int h, int z);
char CwsWinDelete(struct _CWS_WIN_W *work);
char CwsWinSetCode(struct _CWS_WIN_W *work, char _code);
void CwsWin_MultiSetCautionMark(struct _CWS_WIN_W *win, int mark);
void CwsWin_Multi2SetCautionMark(struct _CWS_WIN_W *win, int mark);
void CwsWin_MultiSetWinClut(struct _CWS_WIN_W *win, int clut);
void CwsWin_Multi2SetWinClut(struct _CWS_WIN_W *win, int clut);
char CwsObjChangeTex(struct _CWS_OBJ *work, int tex_num);














































































































































































void MultiWindowInit(void) {


    func_0011EEC0(&D_00824450, 0x20);

    CwsWinsCreate((unsigned int)D_00824470, 0);



}



void MultiWindowCommon(void) { CwsWins_Func(); }



void MultiWindowDestroy(void) {

    CwsWinsDelete();
    func_0011EEC0(&D_00824450, 0x20);
}



struct _MULTI_WIN_W *MultiWindowCreate(int win_num, int x, int y, int w, int h, int z, int tex_num) {
    int clut;
    struct _CWS_WIN_W *p;

    switch (tex_num + 14) {
    case 0: clut = 0; p = (struct _CWS_WIN_W *)CwsWin_Multi; break;
    case 1: clut = 1; p = (struct _CWS_WIN_W *)CwsWin_Multi; break;
    case 2: clut = 2; p = (struct _CWS_WIN_W *)CwsWin_Multi; break;
    case 3: clut = 3; p = (struct _CWS_WIN_W *)CwsWin_Multi; break;

    case 4: clut = 0; p = (struct _CWS_WIN_W *)CwsWin_Multi2; break;
    case 5: clut = 1; p = (struct _CWS_WIN_W *)CwsWin_Multi2; break;
    case 6: clut = 2; p = (struct _CWS_WIN_W *)CwsWin_Multi2; break;
    case 7: clut = 3; p = (struct _CWS_WIN_W *)CwsWin_Multi2; break;
    case 8: clut = 4; p = (struct _CWS_WIN_W *)CwsWin_Multi2; break;
    case 9: clut = 5; p = (struct _CWS_WIN_W *)CwsWin_Multi2; break;

    default: clut = 0; p = (struct _CWS_WIN_W *)CwsWin_Multi; break; }

    D_00824450.pwin[win_num] = CwsWinCreate(p, x, y, w, h, z);
    if (D_00824450.pwin[win_num] != 0) {
        if (p == (struct _CWS_WIN_W *)CwsWin_Multi) {
            CwsWin_MultiSetWinClut(D_00824450.pwin[win_num], clut);
        } else if (p == (struct _CWS_WIN_W *)CwsWin_Multi2) {
            CwsWin_Multi2SetWinClut(D_00824450.pwin[win_num], clut); }
        CwsObjChangeTex(D_00824450.pwin[win_num]->obj[0], tex_num);
    }
    return (struct _MULTI_WIN_W *)D_00824450.pwin[win_num];
}


void MultiWindowDelete(int win_num) {

    CwsWinDelete(D_00824450.pwin[win_num]);
    D_00824450.pwin[win_num] = 0;
}




void MultiWindowOpen(int win_num) { CwsWinSetCode(D_00824450.pwin[win_num], 1); }






void MultiWindowClose(int win_num) { CwsWinSetCode(D_00824450.pwin[win_num], 2); }






void MultiWindowSetMode(int win_num, int mode) {
    D_00824450.pwin[win_num]->mode = mode; }




void MultiWindowSetCautionMark(int win_num, int mark) {

    if (D_00824450.pwin[win_num]->func == CwsWin_Multi) {
        if (mark == 1) CwsWin_MultiSetCautionMark(D_00824450.pwin[win_num], 1);
        else if (mark == 2) CwsWin_MultiSetCautionMark(D_00824450.pwin[win_num], 2);
        else if (mark == 3) CwsWin_MultiSetCautionMark(D_00824450.pwin[win_num], 3);
        else CwsWin_MultiSetCautionMark(D_00824450.pwin[win_num], 0);
    } else if (D_00824450.pwin[win_num]->func == CwsWin_Multi2) {
        if (mark == 1) CwsWin_Multi2SetCautionMark(D_00824450.pwin[win_num], 1);
        else if (mark == 2) CwsWin_Multi2SetCautionMark(D_00824450.pwin[win_num], 2);
        else if (mark == 3) CwsWin_Multi2SetCautionMark(D_00824450.pwin[win_num], 3);
        else CwsWin_Multi2SetCautionMark(D_00824450.pwin[win_num], 0);
    }
}
