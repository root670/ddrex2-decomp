#include "src/CS/option/opt_lang.h"

void OptOutStrInit(void);
void OptMenuModeSet(int mode);
void OptWinTopBarOpen(void);
void OptWinMenuLineWindowOpen(void);
int OptWinMenuLineWindowGetST_Stop(void);
void OptWinTopBarClose(void);
void OptWinMenuLineWindowClose(void);
int func_0011E1D0(int a);
int func_0011E1F0(int a);
int func_00171E40(void);
void func_00171E50(int a);
void func_00175EA0(int a, int b, int c, int d, int e, int f, int g, int h);
void func_0017A8A0(int a);
void func_001B7C30(void *p, int size);
void func_001BE7E0(unsigned char *, unsigned char *, ...);
unsigned char *mesGetLanguage01(int id0, int id1);
int GetCsFontLen(unsigned char *str);
void OptPrintFont(int x, int y, int z, unsigned char *str, int color,
                  unsigned char bri, unsigned char alpha, int texid, ...);

void OptLangMain(struct _OPTSYS_W *_opt) {
    int i;
    int font_bri;
    int col;
    unsigned char *str[64];

    switch (_opt->LangStep) {
    case 4:
        OptOutStrInit();
        OptMenuModeSet(9);
        OptWinTopBarOpen();
        OptWinMenuLineWindowOpen();
        _opt->LangStep = 0;
    case 0:
        if (OptWinMenuLineWindowGetST_Stop() == 1) {
            _opt->LangStep = 1;
        }
        break;
    case 1:
        if (((func_0011E1D0(0) & 0x1000) ? 1 : 0) || ((func_0011E1D0(1) & 0x1000) ? 1 : 0)) {
            if (OPTSYSW->MenuCursor[5] - 1 < 0) {
                OPTSYSW->MenuCursor[5] = 4;
            } else {
                OPTSYSW->MenuCursor[5] = OPTSYSW->MenuCursor[5] - 1;
            }
            func_0017A8A0(0x64);
        } else if (((func_0011E1D0(0) & 0x4000) ? 1 : 0) || ((func_0011E1D0(1) & 0x4000) ? 1 : 0)) {
            if (OPTSYSW->MenuCursor[5] + 1 >= 5) {
                OPTSYSW->MenuCursor[5] = 0;
            } else {
                OPTSYSW->MenuCursor[5] = OPTSYSW->MenuCursor[5] + 1;
            }
            func_0017A8A0(0x64);
        }
        if (((func_0011E1F0(0) & 0x60) ? 1 : 0) || ((func_0011E1F0(1) & 0x60) ? 1 : 0)) {
            if (OPTSYSW->MenuCursor[5] + 2 != func_00171E40()) {
                _opt->LangStep = 3;
                func_0017A8A0(3);
            }
        } else if (((func_0011E1F0(0) & 0x110) ? 1 : 0) || ((func_0011E1F0(1) & 0x110) ? 1 : 0)) {
            _opt->LangStep = 2;
            func_0017A8A0(3);
            func_0017A8A0(0x16);
        }
        break;
    case 3:
        func_00171E50(OPTSYSW->MenuCursor[5] + 2);
        OptWinTopBarClose();
        OptWinMenuLineWindowClose();
        _opt->LangStep = 4;
        break;
    case 2:
    default:
        _opt->MainFunc = OptMenuInit3;
        break;
    }
    func_00175EA0(0, 0, 0x190, 0xF0, 0x80, 0xA000, 7, 0xD);
    for (i = 0; i < 5; i++) {
        func_001B7C30(str, 0x40);
        if (i == OPTSYSW->MenuCursor[5]) {
            col = g_sys_w.u_counter % 32 - 0x10;
            font_bri = (col >= 0 ? col * 4 : -col * 4) + 0x50;
        } else {
            font_bri = 0x40;
        }
        col = i + 1 == func_00171E40() ? 3 : 0;
        func_001BE7E0((unsigned char *)str, (unsigned char *)"%s/%s",
                      mesGetLanguage01(i + 2, i + 2),
                      mesGetLanguage01(func_00171E40(), i + 2));
        OptPrintFont(0x140 - GetCsFontLen((unsigned char *)str) / 2,
                     i * 0x28 + 0x7C, 0xA100, (unsigned char *)str, col,
                     font_bri & 0xFF, 0x80, 0, 0xB5, 0);
    }
}

void OptLangInit(struct _OPTSYS_W *_opt) {
    _opt->LangStep = 0;
    OPTSYSW->MenuCursor[5] = func_00171E40() - 1;
    _opt->MainFunc = OptLangMain;
}
