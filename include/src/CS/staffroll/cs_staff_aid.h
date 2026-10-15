/*
 * C:\work\usam2\src\CS\staffroll\cs_staff_aid.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00242DC0-0x002442DC
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct stf_font_size; struct stf_font_rgba;

/* types (2) */
struct stf_font_size {   // size 0x8
    /* 0x000 */ int tu;                               // 0x4
    /* 0x004 */ int tw;                               // 0x4
};

struct stf_font_rgba {   // size 0x10
    /* 0x000 */ unsigned char r[4];                   // 0x4
    /* 0x004 */ unsigned char g[4];                   // 0x4
    /* 0x008 */ unsigned char b[4];                   // 0x4
    /* 0x00C */ unsigned char a[4];                   // 0x4
};

/* variables (1) */
static stf_font_size stf_font_size[160];                         /* @0x00287D60 size 0x500 */

/* functions defined (5) */
static void CsStfBBoxSetStr(unsigned char *string, float _x, float _y, int _flag); /* 0x00242DC0-0x002431A4 lines 612-662 */
static void CsStfBBoxSetXYA(struct @anon0 *g3a, struct @anon0 *g3b, int point, float _x, float _y, unsigned char _alpha); /* 0x002431B0-0x00243328 lines 556-603 */
int CsStfAidTexture(float _x, float _y, int _tex, int _flag);    /* 0x00243330-0x00243640 lines 492-536 */
static int CsStfAidGetStrSize(char *str, int num);               /* 0x00243640-0x0024391C lines 406-464 */
void CsStfAidFont(float _x, float _y, char *_string, char _color, int _type, int _flag); /* 0x00243920-0x002442DC lines 234-401 */
