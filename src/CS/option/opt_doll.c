#include "types/_OPTSYS_W.h"
#include "types/_tag_OptDoll.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

typedef struct {
    char n;
    char id[48];
} anon_8_226;

typedef struct {
    short x;
    short y;
    short w;
    short h;
} anon_9_226;

void func_001253C0(anon_9_226 *rect, int mode);
void func_001252F0(int mode);
void ps2dancerResetEntry(void);
void ps2dancerEntry(int pid, int chara);
void ps2dancerLoadInit(void *readtmpaddr);
int ps2dancerLoadStep(void);
void ps2dancerSetup(void);
void ps2dancerCameraInit(float cx, float cy, float scale);
void ps2dancerSetPlayCounter(int pid, int cur_p_counter);
void ps2dancerSetToon(int sw);
void ps2dancerSetFloor(int sw);
void ps2dancerDispStep(void);

static anon_9_226 crect = {-296, -132, 592, 244};
struct _tag_cDDR8SaveData SaveData;
struct _OPTSYS_W *OPTSYSW;
anon_8_226 lst;

int View_OptDoll(void)
{
    struct _tag_OptDoll *wk;

    wk = &OPTSYSW->opt_doll;
    switch (OPTSYSW->MenuCursor[OPTSYSW->MenuMode]) {
    case 1:
    case 2:
    case 3:
        wk->new_chr = ((struct _tag_cDDR8Option *)&SaveData.Option)->DollChara[(int)(OPTSYSW->MenuCursor[OPTSYSW->MenuMode] - 1)];
        if (wk->new_chr >= 0x2D) {
            wk->new_chr = -1;
        }
        break;
    default:
        wk->new_chr = -1;
        break;
    }
    switch (wk->dstep) {
    case 0:
        if (wk->new_chr < 0) {
            break;
        }
        wk->cur_chr = wk->new_chr;
        ps2dancerResetEntry();
        ps2dancerEntry(0, wk->cur_chr);
        ps2dancerLoadInit(wk->loadaddr);
        wk->loading = 1;
        wk->dstep++;
        break;
    case 1:
        if (ps2dancerLoadStep()) {
            ps2dancerSetup();
            wk->loading = 0;
            if (wk->cur_chr != wk->new_chr) {
                wk->dstep = 0;
            } else {
                ps2dancerCameraInit(16.0F, -10.0F, 0.5F);
                wk->p_counter = 0;
                wk->dstep++;
            }
        }
        break;
    case 2:
        wk->p_counter += 0x20;
        if (!(wk->p_counter & 0xFFFFF)) {
            ps2dancerSetup();
        }
        ps2dancerSetPlayCounter(0, wk->p_counter);
        ps2dancerSetToon(1);
        ps2dancerSetFloor(0);
        func_001253C0(&crect, 0);
        ps2dancerDispStep();
        func_001252F0(0);
        if (wk->cur_chr != wk->new_chr) {
            wk->dstep = 0;
        }
        break;
    }
    return 1;
}
