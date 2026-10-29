#include "src/network/net_inter.h"

#define D_01029FDC (*(struct _CWS_WIN_W **)0x01029FDC)

unsigned int CwsWinGetStatus(struct _CWS_WIN_W *);
char CwsWinSetCode(struct _CWS_WIN_W *, char);
void CwsWin_MultiSetWinClut(struct _CWS_WIN_W *, int);
void CwsWin_MultiSetCautionMark(struct _CWS_WIN_W *, int);
struct _CWS_WIN_W *CwsWinCreate(void *, int, int, int, int, int);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char,
                  unsigned char, unsigned int, int, unsigned char,
                  unsigned char *, ...);
unsigned char *NetReadDataGetStr(int);

char NetInterErrGetStatus(void) {
    return !(CwsWinGetStatus(D_01029FDC) & 0xC);
}

void NetInterErrClose(void) {
    CwsWinSetCode(D_01029FDC, 2);
}

void NetInterErrOpen(void) {
    CwsWin_MultiSetWinClut(D_01029FDC, 3);
    CwsWin_MultiSetCautionMark(D_01029FDC, 3);
    CwsWinSetCode(D_01029FDC, 1);
}

void NetInterErrSet2Code(int _answer, int _proc, unsigned char *_func_str) {
    if (D_01029FDC == 0)
        return;
    CwsStrSetAll(D_01029FDC, 0, 0, -0x3C, 0x100, 0x80, 0x80, 0x400, 2, 0,
                 NetReadDataGetStr(0), _answer, _proc, 0, _func_str);
}

void NetInterErrSet1Code(int _err_num, unsigned char *_str) {
    if (D_01029FDC == 0)
        return;
    CwsStrSetAll(D_01029FDC, 0, 0, -0x24, 0x100, 0x80, 0x80, 0x400, 2, 0,
                 NetReadDataGetStr(1), _err_num, _str);
}

void NetInterErrSet0Code(unsigned char *_str) {
    if (D_01029FDC == 0)
        return;
    CwsStrSetAll(D_01029FDC, 0, 0, -0xC, 0x100, 0x80, 0x80, 0x400, 2, 0, _str);
}

void NetInterErrInit(void) {
    D_01029FDC = CwsWinCreate(CwsWin_Multi, 0, 0, 0x190, 0xE0, 0xF000);
    D_01029FDC->mode = 6;
}
