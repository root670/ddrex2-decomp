#include "src/CS/option/opt_mc.h"

#define D_01199380 ((void *)0x01199380)

void func_001777C0(int a, int b);
void func_001759D0(void *p, int size);
void func_00175E00(void);
int func_00175A20(void);
void func_00177780(int a, int b);
int func_00175E80(void);
void func_001B7B48(void *p, struct _tag_cDDR8SaveData *save, int size);
void func_00177BB0(void);
void func_00172460(void);
void func_001B7C30(void *p, int size);
void func_00175420(struct _tag_cDDR8SaveData *save, int size);
void func_00175920(void);
int func_00175590(void);
int func_001759A0(void);
void func_00177BD0(struct _tag_cDDR8SaveData *save);
int func_00175E90(void);
void func_00177340(int a, int b, int c, int d, int e, int f, int g);
int func_001759B0(void);

static int OptMcLoadExe(void) {
    int val;
    int rtn;

    rtn = 0;
    switch (OPTSYSW->McExeStep) {
    case 0:
        func_001777C0(1, 1);
        func_001759D0(D_01199380, 0x1FF50);
        func_00175E00();
        OPTMCW->swap_fg = 0;
        OPTSYSW->McExeStep++;
        break;
    case 1:
        OPTMCW->draw_mcwnd = 1;
        if (func_00175A20() == 1) {
            func_00177780(1, 1);
            OPTSYSW->McExeStep = 0;
            rtn = 1;
        }
        val = func_00175E80();
        if (val == 1 && OPTMCW->swap_fg == 0) {
            func_001B7B48(D_01199380, &SaveData, 0x1FF50);
            func_00177BB0();
            func_00172460();
            OPTMCW->swap_fg = 1;
            RequestAutoSave = 0;
        }
        break;
    }
    return rtn;
}

static int OptMcSaveExe(void) {
    int val;
    int rtn;

    rtn = 0;
    switch (OPTSYSW->McExeStep) {
    case 0:
        func_001777C0(1, 1);
        func_00175420(&SaveData, 0x1FF50);
        func_00175920();
        OPTMCW->swap_fg = 0;
        OPTSYSW->McExeStep++;
        break;
    case 1:
        OPTMCW->draw_mcwnd = 1;
        if (func_00175590() == 1) {
            func_00177780(1, 1);
            OPTSYSW->McExeStep = 0;
            rtn = 1;
        }
        val = func_001759A0();
        if (val == 1 && OPTMCW->swap_fg == 0) {
            func_00177BD0(&SaveData);
            OPTMCW->swap_fg = 1;
            RequestAutoSave = 0;
        }
        break;
    }
    return rtn;
}

void OptMcLoadMain(struct _OPTSYS_W *_opt) {
    int val;

    if (OPTMCW->draw_mcwnd == 1) {
        val = func_00175E90();
        if (val != -1) {
            func_00177340(1, 1, 0, 0x5A, val, 0x80, 0xA000);
        }
        OPTMCW->draw_mcwnd = 0;
    }
    if (OptMcLoadExe() == 1) {
        _opt->MainFunc = OptMenuInit3;
    }
}

void OptMcLoadInit(struct _OPTSYS_W *_opt) {
    func_001B7C30(OPTMCW, 0x54);
    _opt->McExeStep = 0;
    _opt->MainFunc = OptMcLoadMain;
}

void OptMcSaveMain(struct _OPTSYS_W *_opt) {
    int val;

    if (OPTMCW->draw_mcwnd == 1) {
        val = func_001759B0();
        if (val != -1) {
            func_00177340(1, 1, 0, 0x5A, val, 0x80, 0xA000);
        }
        OPTMCW->draw_mcwnd = 0;
    }
    if (OptMcSaveExe() == 1) {
        _opt->MainFunc = OptMenuInit3;
    }
}

void OptMcSaveInit(struct _OPTSYS_W *_opt) {
    func_001B7C30(OPTMCW, 0x54);
    _opt->McExeStep = 0;
    _opt->MainFunc = OptMcSaveMain;
}
