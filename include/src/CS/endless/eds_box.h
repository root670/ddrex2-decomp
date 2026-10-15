/*
 * C:\work\usam2\src\CS\endless\eds_box.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x0023A130-0x0023B77C
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _EDSBOXPOINT_W; struct _EDSBOX_W; struct _EDSBOX_MAIN;

/* types (3) */
struct _EDSBOXPOINT_W {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned char r;                      // 0x1
    /* 0x00D */ unsigned char g;                      // 0x1
    /* 0x00E */ unsigned char b;                      // 0x1
    /* 0x00F */ unsigned char a;                      // 0x1
};

struct _EDSBOX_W {   // size 0x98
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float sx;                             // 0x4
    /* 0x00C */ float sy;                             // 0x4
    /* 0x010 */ _EDSBOXPOINT_W p[4];                  // 0x40
    /* 0x050 */ _EDSBOXPOINT_W s[4];                  // 0x40
    /* 0x090 */ unsigned int flag;                    // 0x4
    /* 0x094 */ char col;                             // 0x1
    /* 0x095 */ char step;                            // 0x1
    /* 0x096 */ char s_step;                          // 0x1
    /* 0x097 */ unsigned char type;                   // 0x1
};

struct _EDSBOX_MAIN {   // size 0x8E8
    /* 0x000 */ _EDSBOX_W work[15];                   // 0x8E8
};

/* variables (4) */
static int (*EdsBox_Func[5])(_EDSBOX_W *);                       /* @0x00285E40 size 0x14 */
static unsigned char EdsBoxRgbTbl[2][3];                         /* @0x002A2278 size 0x6 */
_EDSBOX_MAIN *EDSBOXM;                                           /* @0x002A2280 size 0x4 */
static _EDSBOX_MAIN _eds_box_w;                                  /* @0x006B3880 size 0x8E8 */

/* functions defined (19) */
void EdsBox4SetRGBA(int num, int pos, unsigned char r, unsigned char g, unsigned char b, unsigned char a); /* 0x0023A130-0x0023A290 lines 643-656 */
void EdsBox4SetUV(int num, int pos, float u, float v);           /* 0x0023A290-0x0023A2DC lines 629-633 */
void EdsBoxSetWH(int num, float w, float h);                     /* 0x0023A2E0-0x0023A388 lines 603-613 */
void EdsBoxSetY(int num, float y);                               /* 0x0023A390-0x0023A3C0 lines 594-597 */
void EdsBoxSetXY(int num, float x, float y);                     /* 0x0023A3C0-0x0023A408 lines 572-589 */
void EdsBoxSetRGBAnime(int num, int type, int col);              /* 0x0023A410-0x0023A4C8 lines 553-565 */
void EdsBoxSetType(int num, char type);                          /* 0x0023A4D0-0x0023A530 lines 539-544 */
void EdsBoxSetMode(int num, int mode);                           /* 0x0023A530-0x0023A640 lines 513-531 */
static void EdsBoxRGBAnime(_EDSBOX_W *boxw);                     /* 0x0023A640-0x0023ADE0 lines 355-500 */
static int EdsBoxOpenCloseMove(_EDSBOX_W *boxw, int speed);      /* 0x0023ADE0-0x0023AEF0 lines 309-348 */
static void EdsBoxDisp(_EDSBOX_W *boxw);                         /* 0x0023AEF0-0x0023B3F8 lines 260-297 */
static int EdsBoxDestroy(void);                                  /* 0x0023B400-0x0023B408 lines 253-253 */
static int EdsBoxClose(_EDSBOX_W *boxw);                         /* 0x0023B410-0x0023B4C8 lines 196-230 */
static int EdsBoxMain(_EDSBOX_W *boxw);                          /* 0x0023B4D0-0x0023B4F0 lines 182-189 */
static int EdsBoxOpen(_EDSBOX_W *boxw);                          /* 0x0023B4F0-0x0023B5C0 lines 141-174 */
static int EdsBoxSet(void);                                      /* 0x0023B5C0-0x0023B5C8 lines 133-133 */
void EdsBoxGetInit(int num);                                     /* 0x0023B5D0-0x0023B658 lines 96-122 */
void EdsBoxFunc(void);                                           /* 0x0023B660-0x0023B76C lines 65-89 */
void EdsBoxAllInit(void);                                        /* 0x0023B770-0x0023B77C lines 56-56 */
