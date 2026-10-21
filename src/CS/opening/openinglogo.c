#include "src/CS/opening/openinglogo.h"

int func_001B7C30(struct _tag_cOpeninglogo *p, int size);
int func_0011F000(int id);
int func_00127F60(anon_0_25 *info, int tex);
void func_00123CF0(anon_1_25 *sp);
void func_0017CD50(int a, int b);

struct _tag_cOpeninglogo *pOpeninglogo = &_pOpeninglogo;
static int logo_tex_num[1] = { 0 };
struct _tag_cOpening *pOpening = (struct _tag_cOpening *)0x006D33A0;
static struct _tag_cOpeninglogo _pOpeninglogo = { 0 };

int Init_Openinglogo(void) {
    pOpening->cWait = 0;

    func_001B7C30(pOpeninglogo, 0x1C);

    pOpeninglogo->logo_num = 0;

    pOpeninglogo->fi_count = func_0011F000(1);
    pOpeninglogo->fo_count = func_0011F000(1);
    pOpeninglogo->disp_count = func_0011F000(2);

    return 1;
}

int Control_Openinglogo(void) {
    int counter;
    int count2;

    counter = pOpening->cWait;
    count2 = pOpeninglogo->fi_count + pOpeninglogo->disp_count + pOpeninglogo->fo_count;

    if (counter < pOpeninglogo->fi_count) {
        pOpeninglogo->bright = counter * 128 / pOpeninglogo->fi_count;
    } else if (counter < pOpeninglogo->fi_count + pOpeninglogo->disp_count) {
        pOpeninglogo->bright = 0x80;
    } else if (counter < count2) {
        pOpeninglogo->bright = 0x80 + -(counter - (pOpeninglogo->fi_count + pOpeninglogo->disp_count)) * 128 / pOpeninglogo->fo_count;
    } else {
        pOpeninglogo->bright = 0;

        pOpeninglogo->logo_num++;
        pOpening->cWait = -1;
        if (pOpeninglogo->logo_num > 0) {
            pOpeninglogo->logo_num = 0;

            func_0017CD50(3, 2);
        }
    }

    return 1;
}

int View_Openinglogo(void) {
    anon_0_25 info;
    anon_1_25 sp;
    int bright;

    bright = pOpeninglogo->bright;

    func_00127F60(&info, logo_tex_num[pOpeninglogo->logo_num]);

    sp.flg = 0;
    sp.flg |= 0x100;
    sp.w = info.w; sp.h = info.h;
    sp.r0 = bright; sp.g0 = bright; sp.b0 = bright; sp.a0 = 0x80;
    sp.u = 0; sp.v = 0;
    sp.x0.fd = -info.w / 2.0f; sp.y0.fd = -info.h / 2.0f; sp.z0 = 0xF000;
    func_00123CF0(&sp);

    return 1;
}

int Update_Openinglogo(void) {
    pOpening->cWait++;

    return 1;
}
