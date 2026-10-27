#include "src/CS/staffroll/cs_staffroll.h"

static int isreMainStep = 0;
static int isreReadStep = 0;
static int isreSdReadStep = 0;
anon_0_186 g_staffroll;
anon_1_186 sound_bin[];

#define D_016B6380 ((unsigned char *)0x016B6380)
#define D_00E4D380 0x00E4D380
#define D_00E4D390 ((int *)0x00E4D390)

void func_0011E440(unsigned int mask);
int func_0011E430(void);
void func_0011EEC0(void *p, int size);
int func_0011E090(anon_1_186 *tbl, unsigned char *addr);
int func_0011DE80(void);
int func_0011E1F0(int a);
void func_001205E0(int a);
void func_001255A0(int a, int b, int c, int d);
void func_001267B0(int a, int b);
void func_00179BE0(void);
void func_00179C00(int a);
void func_00179C30(int a, int b, int c, float d);
void func_0017A090(unsigned char *p);
void func_0017A0A0(void);
void func_0017A8A0(int a);
void func_0017AC30(unsigned char *p, int size);
void csStaffRollFadeInit(void);
void csStaffRollScrlInit(void);
void csStaffRollPicStepInit(void);
int StaffRollTexInit(anon_0_186 *p, unsigned char *addr);
void csStaffRollMovieInit(anon_0_186 *p);
void StaffRollFFTDispInit(void);
void StaffRollFFTDisp(anon_0_186 *p);
void StaffRollCapScreen(void);
void EdBkEffectColSet(anon_0_186 *p);
void csStaffRollFadeStart(int a, float b);
int csStaffRollFadeCheck(void);
void csStaffRollFadeAct(void);
void csStaffRollFadeDraw(void);
int csStaffRollPicActBaseFO(anon_0_186 *p);
void csStaffRollMovieMain(anon_0_186 *p);
void csStaffRollScrlMain(anon_0_186 *p);
void csStaffRollPicDraw(anon_0_186 *p);

int csStaffRollSdMain(void)
{
    int ret;

    switch (isreSdReadStep) {
    case SRE_SDREAD_STEP_VAG_INIT:
        if (!func_0011DE80()) {
            break;
        }
        func_0017AC30(D_016B6380, 0x18);
        func_0017A090(D_016B6380);
        isreSdReadStep = SRE_SDREAD_STEP_VAG_READ;
        break;
    case SRE_SDREAD_STEP_VAG_READ:
        func_001205E0(0);
        if (func_0011DE80()) {
            isreSdReadStep = SRE_SDREAD_STEP_VAG_WAIT;
        }
        break;
    case SRE_SDREAD_STEP_VAG_WAIT:
        func_001205E0(0);
        if (g_staffroll.timer < 0.0f) {
            break;
        }
        func_00179C30(0, 0, 0, 1.0f);
        isreSdReadStep = SRE_SDREAD_STEP_VAG_TERMINATE;
    case SRE_SDREAD_STEP_VAG_TERMINATE:
        if (g_staffroll.timer < 5364.63f) {
            break;
        }
        isreSdReadStep = SRE_SDREAD_STEP_INIT;
        break;
    case SRE_SDREAD_STEP_INIT:
        if (!func_0011DE80()) {
            break;
        }
        if (!func_0011E090(sound_bin, D_016B6380)) {
            break;
        }
        func_0017A090(D_016B6380);
        isreSdReadStep = SRE_SDREAD_STEP_DISC_START;
        break;
    case SRE_SDREAD_STEP_DISC_START:
        if (!func_0011DE80()) {
            break;
        }
        if (isreMainStep < 3) {
            break;
        }
        if (isreMainStep == 0xB) {
            isreSdReadStep = SRE_SDREAD_STEP_TERMINATE;
            break;
        }
        isreSdReadStep = SRE_SDREAD_STEP_READ;
        break;
    case SRE_SDREAD_STEP_READ:
        isreSdReadStep = SRE_SDREAD_STEP_WAIT;
        break;
    case SRE_SDREAD_STEP_WAIT:
        if (g_staffroll.timer < 5424.57f) {
            break;
        }
        if (isreMainStep == 0xB) {
            isreSdReadStep = SRE_SDREAD_STEP_TERMINATE;
            break;
        }
        func_0017A8A0(0xF100);
        func_00179BE0();
        func_00179C30(0, 0, 0, 1.0f);
        StaffRollFFTDispInit();
        g_staffroll.fft_bright = 0;
        EdBkEffectColSet(&g_staffroll);
        isreSdReadStep = SRE_SDREAD_STEP_TERMINATE;
    case SRE_SDREAD_STEP_TERMINATE:
        func_0017A0A0();
        StaffRollFFTDisp(&g_staffroll);
        StaffRollCapScreen();
        if ((int)g_staffroll.timer == 0x1710 || (int)g_staffroll.timer == 0x1B0B ||
            (int)g_staffroll.timer == 0x1E8E || (int)g_staffroll.timer == 0x2211) {
            EdBkEffectColSet(&g_staffroll);
        }
        ret = 1;
    }
    return ret;
}

int csStaffRollStep(void)
{
    int rtn = 0;
    static float stepwait;

    switch (isreMainStep) {
    case 0:
        func_0011E440(func_0011E430() | 0x10);
        func_0011EEC0(&g_staffroll, 0x78);
        g_staffroll.timer = -50.0f;
        isreSdReadStep = 0;
        csStaffRollFadeInit();
        isreReadStep = 0;
        csStaffRollScrlInit();
        csStaffRollPicStepInit();
        isreMainStep = 1;
        g_staffroll.disp_mov = 0;
        g_staffroll.disp_roll = 0;
    case 1:
        if (!StaffRollTexInit(&g_staffroll, (unsigned char *)(D_00E4D380 + *D_00E4D390))) {
            break;
        }
        csStaffRollMovieInit(&g_staffroll);
        func_0011E440(func_0011E430() & ~0x10);
        isreMainStep = 3;
        break;
    case 2:
        break;
    case 3:
        g_staffroll.disp_roll = 1;
        g_staffroll.disp_mov = 1;
        if (g_staffroll.start_flg) {
            isreMainStep = 4;
        }
        break;
    case 4:
        if (g_staffroll.timer >= 119.88f) {
            isreMainStep = 5;
        }
        g_staffroll.disp_mov = 1;
        g_staffroll.disp_roll = 1;
        break;
    case 5:
        isreMainStep = 6;
        g_staffroll.disp_mov = 1;
        g_staffroll.disp_roll = 1;
        break;
    case 6:
        if (g_staffroll.timer >= 10519.47f) {
            isreMainStep = 7;
        }
        break;
    case 7:
        if (!csStaffRollPicActBaseFO(&g_staffroll)) {
            break;
        }
        isreMainStep = 8;
        break;
    case 8:
        if (g_staffroll.timer >= 10609.38f) {
            csStaffRollFadeStart(5, 1.0f);
            isreMainStep = 0xC;
        }
        g_staffroll.disp_mov = 0;
        break;
    case 9:
        if (!csStaffRollFadeCheck()) {
            break;
        }
        g_staffroll.disp_roll = 0;
        stepwait = g_staffroll.timer + 239.76f;
        isreMainStep = 0xA;
        break;
    case 10:
        if (g_staffroll.timer < stepwait) {
            break;
        }
        csStaffRollFadeStart(3, 0.15f);
        isreMainStep = 0xC;
        break;
    case 11:
        if (!csStaffRollFadeCheck()) {
            break;
        }
        g_staffroll.disp_mov = 0;
        g_staffroll.disp_roll = 0;
        isreMainStep = 0xC;
        break;
    case 12:
        if (!csStaffRollFadeCheck()) {
            break;
        }
        if (func_0011DE80()) {
            rtn = 1;
        }
        break;
    }
    csStaffRollSdMain();
    if (g_staffroll.disp_mov) {
        csStaffRollMovieMain(&g_staffroll);
    }
    if (g_staffroll.disp_roll) {
        csStaffRollScrlMain(&g_staffroll);
    }
    if (g_staffroll.disp_pic) {
        csStaffRollPicDraw(&g_staffroll);
    }
    csStaffRollFadeAct();
    csStaffRollFadeDraw();
    if (3 < isreMainStep) {
        g_staffroll.timer += 0.83416754f;
        if (isreMainStep < 0xB) {
            if (((func_0011E1F0(0) & 0x800) ? 1 : 0) || ((func_0011E1F0(1) & 0x800) ? 1 : 0)) {
                csStaffRollFadeStart(5, 1.0f);
                isreMainStep = 0xB;
                func_00179C00(0);
                func_0017A8A0(0xF100);
                func_0017A8A0(2);
            }
        }
    }
    return rtn;
}

void csStaffRollFinish(void)
{
    func_00179C00(0);
    func_0017A8A0(0xF100);
    func_001267B0(0, 0);
}

void csStaffRollInit(void)
{
    isreMainStep = 0;
    func_001255A0(0, 0, 0, 0);
}
