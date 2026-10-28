#include "src/CS/option/opt_adjust.h"

void OptMenuModeSet(int mode);
void OptWinMenuLineWindowOpen(void);
void OptWinMenuLineWindowClose(void);
int OptWinMenuLineWindowGetST_Stop(void);
void OptWinAdjustOpen(void);
void OptWinAdjustClose(void);
int func_0011E1D0(int a);
int func_0011E1F0(int a);
void func_001252B0(int a);
void func_001252C0(int a);
void func_0017A8A0(int a);

void OptAdjustMain(struct _OPTSYS_W *_opt) {
    switch (_opt->AdjustStep) {
    case 0:
        if (OptWinMenuLineWindowGetST_Stop() == 1) {
            _opt->AdjustStep = 1;
        }
        break;
    case 1:
        if (((func_0011E1F0(0) & 0x110) ? 1 : 0) || ((func_0011E1F0(1) & 0x110) ? 1 : 0)) {
            if (((func_0011E1D0(0) & 0x100) ? 1 : 0) || ((func_0011E1D0(1) & 0x100) ? 1 : 0)) {
                OPTSYSW->opt_win.AdjustCheck |= 0x80;
            }
            if (((func_0011E1D0(0) & 0x10) ? 1 : 0) || ((func_0011E1D0(1) & 0x10) ? 1 : 0)) {
                OPTSYSW->opt_win.AdjustCheck |= 0x200;
            }
            _opt->TmpX = SaveData.Option.screen_x;
            _opt->TmpY = SaveData.Option.screen_y;
            _opt->NextMenuMode = 0xE;
            OptWinAdjustClose();
            _opt->AdjustStep = 2;
            func_0017A8A0(0x16);
        } else if (((func_0011E1F0(0) & 0x60) ? 1 : 0) || ((func_0011E1F0(1) & 0x60) ? 1 : 0)) {
            if (((func_0011E1F0(0) & 0x20) ? 1 : 0) || ((func_0011E1F0(1) & 0x20) ? 1 : 0)) {
                OPTSYSW->opt_win.AdjustCheck |= 0x40;
            }
            if (((func_0011E1F0(0) & 0x40) ? 1 : 0) || ((func_0011E1F0(1) & 0x40) ? 1 : 0)) {
                OPTSYSW->opt_win.AdjustCheck |= 0x100;
            }
            SaveData.Option.screen_x = _opt->TmpX;
            SaveData.Option.screen_y = _opt->TmpY;
            _opt->NextMenuMode = 0xE;
            OptWinAdjustClose();
            _opt->AdjustStep = 2;
            func_0017A8A0(3);
            func_0017A8A0(0x16);
        } else if (((func_0011E1F0(0) & 0x880) ? 1 : 0) || ((func_0011E1F0(1) & 0x880) ? 1 : 0)) {
            if (((func_0011E1F0(0) & 0x800) ? 1 : 0) || ((func_0011E1F0(1) & 0x800) ? 1 : 0)) {
                OPTSYSW->opt_win.AdjustCheck |= 0x10;
            }
            if (((func_0011E1F0(0) & 0x80) ? 1 : 0) || ((func_0011E1F0(1) & 0x80) ? 1 : 0)) {
                OPTSYSW->opt_win.AdjustCheck |= 0x20;
            }
            OPTSYSW->opt_win.AdjustCheck |= 0xF;
            _opt->TmpX = 0;
            _opt->TmpY = 0;
            func_0017A8A0(0x6B);
        }
        if (((func_0011E1D0(0) & 0x1000) ? 1 : 0) || ((func_0011E1D0(1) & 0x1000) ? 1 : 0)) {
            if (_opt->TmpY - 1 >= -0x14) {
                OPTSYSW->opt_win.AdjustCheck |= 1;
                _opt->TmpY = _opt->TmpY - 1;
                func_0017A8A0(0x61);
            }
        } else if (((func_0011E1D0(0) & 0x4000) ? 1 : 0) || ((func_0011E1D0(1) & 0x4000) ? 1 : 0)) {
            if (_opt->TmpY + 1 < 0x15) {
                OPTSYSW->opt_win.AdjustCheck |= 2;
                _opt->TmpY = _opt->TmpY + 1;
                func_0017A8A0(0x61);
            }
        }
        if (((func_0011E1D0(0) & 0x8000) ? 1 : 0) || ((func_0011E1D0(1) & 0x8000) ? 1 : 0)) {
            if (_opt->TmpX - 1 >= -0x14) {
                OPTSYSW->opt_win.AdjustCheck |= 8;
                _opt->TmpX = _opt->TmpX - 1;
                func_0017A8A0(0x61);
            }
        } else if (((func_0011E1D0(0) & 0x2000) ? 1 : 0) || ((func_0011E1D0(1) & 0x2000) ? 1 : 0)) {
            if (_opt->TmpX + 1 < 0x15) {
                OPTSYSW->opt_win.AdjustCheck |= 4;
                _opt->TmpX = _opt->TmpX + 1;
                func_0017A8A0(0x61);
            }
        }
        func_001252C0(_opt->TmpX);
        func_001252B0(_opt->TmpY);
        break;
    case 2:
        func_001252C0(SaveData.Option.screen_x);
        func_001252B0(SaveData.Option.screen_y);
        OptWinMenuLineWindowClose();
        _opt->MainFunc = OptMenuInit2;
        break;
    }
}

void OptAdjustInit(struct _OPTSYS_W *_opt) {
    OptMenuModeSet(_opt->NextMenuMode);
    OptWinMenuLineWindowOpen();
    OptWinAdjustOpen();
    _opt->AdjustStep = 0;
    _opt->TmpX = SaveData.Option.screen_x;
    _opt->TmpY = SaveData.Option.screen_y;
    _opt->MainFunc = OptAdjustMain;
}
