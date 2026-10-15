/*
 * C:\work\usam2\src\CS\lesson\les_aid.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x00245690-0x002468E0
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _LESTEX_INIT_SET; struct _LESTEX_W; struct _LESWIN_W;

/* types (3) */
struct _LESWIN_W {   // size 0x44
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float sx;                             // 0x4
    /* 0x00C */ float sy;                             // 0x4
    /* 0x010 */ int w;                                // 0x4
    /* 0x014 */ int h;                                // 0x4
    /* 0x018 */ int sw;                               // 0x4
    /* 0x01C */ int sh;                               // 0x4
    /* 0x020 */ float waveY;                          // 0x4
    /* 0x024 */ unsigned int flag;                    // 0x4
    /* 0x028 */ unsigned char alpha;                  // 0x1
    /* 0x029 */ unsigned char salpha;                 // 0x1
    /* 0x02A */ // 0x2 bytes padding
    /* 0x02C */ int bri;                              // 0x4
    /* 0x030 */ char step;                            // 0x1
    /* 0x031 */ char s_step;                          // 0x1
    /* 0x032 */ unsigned char type;                   // 0x1
    /* 0x033 */ unsigned char tex_id;                 // 0x1
    /* 0x034 */ _LESTEX_INIT_SET *def;                // 0x4
    /* 0x038 */ _LESTEX_W *tex[3];                    // 0xC
};

struct _LESTEX_INIT_SET {   // size 0x20
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int flag;                             // 0x4
    /* 0x014 */ int id[3];                            // 0xC
};

struct _LESTEX_W {   // size 0x20
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int u;                                // 0x4
    /* 0x00C */ int v;                                // 0x4
    /* 0x010 */ int w;                                // 0x4
    /* 0x014 */ int h;                                // 0x4
    /* 0x018 */ int z;                                // 0x4
    /* 0x01C */ int tex_num;                          // 0x4
};

/* variables (3) */
static int (*LesWin_Func[5])(_LESWIN_W *);                       /* @0x002883E0 size 0x14 */
static _LESTEX_W LesMainTextureData[4];                          /* @0x00288400 size 0x80 */
static _LESTEX_INIT_SET LesMainWindowData[2];                    /* @0x00288480 size 0x40 */

/* functions defined (13) */
void LesWinSetType(_LESWIN_W *winw, char type);                  /* 0x00245690-0x002456F4 lines 617-624 */
void LesWinSetMode(_LESWIN_W *winw, int mode);                   /* 0x00245700-0x0024581C lines 580-609 */
static void LesWinSetDefaultPartsWH(_LESWIN_W *winw);            /* 0x00245820-0x00245900 lines 530-572 */
static void LesWinDefaultAllSet(_LESWIN_W *winw);                /* 0x00245900-0x002459E0 lines 496-517 */
static int LesWinXYWHMove(_LESWIN_W *winw, int speed);           /* 0x002459E0-0x00245C80 lines 433-482 */
static void LesWinDisp(_LESWIN_W *winw);                         /* 0x00245C80-0x00246350 lines 295-390 */
static int LesWinDestroy(_LESWIN_W *winw);                       /* 0x00246350-0x002463A8 lines 272-287 */
static int LesWinClose(_LESWIN_W *winw);                         /* 0x002463B0-0x00246590 lines 207-264 */
static int LesWinMain(void);                                     /* 0x00246590-0x00246598 lines 199-199 */
static int LesWinOpen(_LESWIN_W *winw);                          /* 0x002465A0-0x002467B0 lines 126-189 */
static int LesWinSet(_LESWIN_W *winw);                           /* 0x002467B0-0x002467BC lines 115-118 */
void LesWinGetInit(_LESWIN_W *winw, int id);                     /* 0x002467C0-0x00246814 lines 101-106 */
void LesWinFunc(_LESWIN_W *winw);                                /* 0x00246820-0x002468E0 lines 73-94 */
