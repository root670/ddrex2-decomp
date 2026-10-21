#include "src/common/co_button.h"

anon_1_106 *func_00121E70(void *p);
void func_00121E40(void *p, int n);
void func_0012D070(int tex_no);
void func_00127F60(anon_0_106 *info, int tex_id);
void func_00123CF0(anon_3_106 *sp);

static anon_2_106 co_btn_tbl[16] = { { 0x13, 0x10 }, { 0x14, 0x10 }, { 0x15, 0x10 }, { 0x16, 0x10 }, { 0x17, 0x20 }, { 0x18, 0x20 }, { 0x19, 0x10 }, { 0x1A, 0x10 }, { 0x1B, 0x10 }, { 0x1C, 0x10 }, { 0x1D, 0x20 }, { 0x1E, 0x20 }, { 0x1F, 0x20 }, { 0x20, 0x20 }, { 0x22, 0x28 }, { 0x21, 0x28 } };
static anon_2_106 co_btn_ex_tbl[23] = { { 0x23, 0x38 }, { 0x24, 0x60 }, { 0x25, 0x50 }, { 0x26, 0x3E }, { 0x27, 0x46 }, { 0x28, 0x3A }, { 0x29, 0x48 }, { 0x2A, 0x48 }, { 0x2B, 0x22 }, { 0x2C, 0x30 }, { 0x2D, 0x22 }, { 0x2E, 0x34 }, { 0x2F, 0x30 }, { 0x30, 0x1A }, { 0x31, 0x26 }, { 0x32, 0x5C }, { 0x33, 0x30 }, { 0x34, 0x36 }, { 0x35, 0x5C }, { 0x36, 0x56 }, { 0x37, 0x2E }, { 0x38, 0x2E }, { 0x39, 0x3C } };

void co_button_disp(unsigned int kind, float x, float y, int pri, unsigned char alpha, unsigned char bri, int flag, int tex_id)
{
    anon_1_106 *pkt;
    anon_2_106 *btn;
    anon_0_106 info;
    anon_3_106 sp;

    if (kind >= 17) return;
    btn = &co_btn_tbl[kind];

    x = (flag & 1) ? x - btn->width / 2.0f : x;
    y = (flag & 2) ? y - 8.0f : y;

    if (flag & 4) {
        func_00127F60(&info, tex_id);
    } else
        func_0012D070(btn->tex_no);

    if (flag & 8)
    {
        pkt = func_00121E70(0);

        pkt[0].ul64[0] = 0x1000000000008001;
        pkt[0].ul64[1] = 1;

        pkt[1].ui32[0] = pkt[1].ui32[1] = pkt[1].ui32[2] = bri;

        pkt[1].ui32[3] = alpha;

        pkt[2].ul64[0] = 0x20AB400000008002;
        pkt[2].ul64[1] = 0x53;

        pkt[3].ui32[0] = 0;
        pkt[3].ui32[1] = 0;
        pkt[3].ui32[2] = 0;
        pkt[3].ui32[3] = 0;

        pkt[4].ui32[0] = ((int)x + 0x800) << 4;
        pkt[4].ui32[1] = ((int)y + 0x800) << 4;
        pkt[4].ui32[2] = pri;
        pkt[4].ui32[3] = 0;

        pkt[5].ui32[0] = btn->width << 4;
        pkt[5].ui32[1] = 0x100;
        pkt[5].ui32[2] = 0;
        pkt[5].ui32[3] = 0;

        pkt[6].ui32[0] = ((int)x + 0x800 + btn->width) << 4;
        pkt[6].ui32[1] = ((int)y + 0x810) << 4;
        pkt[6].ui32[2] = pri;
        pkt[6].ui32[3] = 0;
        func_00121E40(0, 7);
    } else {
        sp.flg = 0;
        sp.flg |= 0x100;
        sp.w = btn->width; sp.h = 16.0f;
        sp.b0 = sp.g0 = sp.r0 = bri; sp.a0 = alpha;
        sp.u = 0; sp.v = 0;
        sp.z0 = pri; sp.x0.fd = x; sp.y0.fd = y;
        func_00123CF0(&sp);
    }
}

void co_button_explain_disp(unsigned int kind, float x, float y, int pri, unsigned char alpha, unsigned char bri, int flag, int tex_id)
{
    anon_1_106 *pkt;
    anon_2_106 *ex;
    anon_0_106 info;
    anon_3_106 sp;

    if (kind >= 24) return;
    ex = &co_btn_ex_tbl[kind];

    x = (flag & 1) ? x - ex->width / 2.0f : x;
    y = (flag & 2) ? y - 9.0f : y;

    if (flag & 4) {
        func_00127F60(&info, tex_id);
    } else
        func_0012D070(ex->tex_no);

    if (flag & 8)
    {
        pkt = func_00121E70(0);

        pkt[0].ul64[0] = 0x1000000000008001;
        pkt[0].ul64[1] = 1;

        pkt[1].ui32[0] = pkt[1].ui32[1] = pkt[1].ui32[2] = bri;

        pkt[1].ui32[3] = alpha;

        pkt[2].ul64[0] = 0x20AB400000008002;
        pkt[2].ul64[1] = 0x53;

        pkt[3].ui32[0] = 0;
        pkt[3].ui32[1] = 0;
        pkt[3].ui32[2] = 0;
        pkt[3].ui32[3] = 0;

        pkt[4].ui32[0] = ((int)x + 0x800) << 4;
        pkt[4].ui32[1] = ((int)y + 0x800) << 4;
        pkt[4].ui32[2] = pri;
        pkt[4].ui32[3] = 0;

        pkt[5].ui32[0] = ex->width << 4;
        pkt[5].ui32[1] = 0x120;
        pkt[5].ui32[2] = 0;
        pkt[5].ui32[3] = 0;

        pkt[6].ui32[0] = ((int)x + 0x800 + ex->width) << 4;
        pkt[6].ui32[1] = ((int)y + 0x812) << 4;
        pkt[6].ui32[2] = pri;
        pkt[6].ui32[3] = 0;
        func_00121E40(0, 7);
    } else {
        sp.flg = 0;
        sp.flg |= 0x100;
        sp.w = ex->width; sp.h = 16.0f;
        sp.b0 = sp.g0 = sp.r0 = bri; sp.a0 = alpha;
        sp.u = 0; sp.v = 0;
        sp.z0 = pri; sp.x0.fd = x; sp.y0.fd = y;
        func_00123CF0(&sp);
    }
}
