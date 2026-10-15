/*
 * C:\work\usam2\src\CS\endless\eds_win.c
 * MW MIPS C Compiler, overlay main; 25 functions, code 0x00233DE0-0x00236160
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _EDSTEX_INIT_SET; struct _EDSTEX_W; struct _GAME_MODE_W; struct _EDSWIN_W;
struct _EDSRECORD_W; struct _EDSBREAK_W; struct demo_loop_w; struct play_loop_w;
struct _EDSSYS_W;

/* types (9) */
struct demo_loop_w {   // size 0x8008
    /* 0x000 */ int demo_loop_step;                   // 0x4
    /* 0x004 */ int loop_ntimes;                      // 0x4
    /* 0x008 */ unsigned int game_mode_memory[8192];  // 0x8000
};

struct play_loop_w {   // size 0x8008
    /* 0x000 */ int play_loop_step;                   // 0x4
    /* 0x004 */ int select_step;                      // 0x4
    /* 0x008 */ unsigned int game_mode_memory[8192];  // 0x8000
};

struct _GAME_MODE_W {   // size 0x800C
    /* 0x000 */ int game_mode_step;                   // 0x4
    /* 0x004 */ union {   // size 0x8008
        /* 0x000 */ demo_loop_w demo_loop_w;              // 0x8008
        /* 0x000 */ play_loop_w play_loop_w;              // 0x8008
    } u;
};

struct _EDSWIN_W {   // size 0x48
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
    /* 0x02A */ char step;                            // 0x1
    /* 0x02B */ char s_step;                          // 0x1
    /* 0x02C */ unsigned char type;                   // 0x1
    /* 0x02D */ unsigned char tex_id;                 // 0x1
    /* 0x02E */ // 0x2 bytes padding
    /* 0x030 */ _EDSTEX_INIT_SET *def;                // 0x4
    /* 0x034 */ _EDSTEX_W *tex[5];                    // 0x14
};

struct _EDSRECORD_W {   // size 0x4
    /* 0x000 */ int flag;                             // 0x4
};

struct _EDSBREAK_W {   // size 0x4
    /* 0x000 */ char music_no;                        // 0x1
    /* 0x001 */ char BackTex;                         // 0x1
    /* 0x002 */ char FontVTime;                       // 0x1
    /* 0x003 */ char MainStep;                        // 0x1
};

struct _EDSSYS_W {   // size 0xB00
    /* 0x000 */ void (*MainFunc)();                   // 0x4
    /* 0x004 */ _GAME_MODE_W *game_w;                 // 0x4
    /* 0x008 */ _EDSWIN_W *work[34];                  // 0x88
    /* 0x090 */ float sys_timer;                      // 0x4
    /* 0x094 */ int all_music_max;                    // 0x4
    /* 0x098 */ int music_max;                        // 0x4
    /* 0x09C */ int SystemFlag;                       // 0x4
    /* 0x0A0 */ int GameFlag;                         // 0x4
    /* 0x0A4 */ char Sorting;                         // 0x1
    /* 0x0A5 */ char MainStep;                        // 0x1
    /* 0x0A6 */ char TexInitStep;                     // 0x1
    /* 0x0A7 */ char WarningStep;                     // 0x1
    /* 0x0A8 */ char MenuStep;                        // 0x1
    /* 0x0A9 */ char ReturnGStep;                     // 0x1
    /* 0x0AA */ char OrderStep;                       // 0x1
    /* 0x0AB */ char RecordStep;                      // 0x1
    /* 0x0AC */ char MenuCursor;                      // 0x1
    /* 0x0AD */ char MenuStCursor[12];                // 0xC
    /* 0x0B9 */ char OrderCursorX;                    // 0x1
    /* 0x0BA */ unsigned char OrderCursorY;           // 0x1
    /* 0x0BB */ unsigned char OldOrderMusic;          // 0x1
    /* 0x0BC */ char OrderTopID;                      // 0x1
    /* 0x0BD */ unsigned char PlayTbl[69];            // 0x45
    /* 0x102 */ // 0x2 bytes padding
    /* 0x104 */ int Level;                            // 0x4
    /* 0x108 */ int Combo;                            // 0x4
    /* 0x10C */ int ComboMax;                         // 0x4
    /* 0x110 */ int StageMax;                         // 0x4
    /* 0x114 */ unsigned int ScoreMax[2];             // 0x8
    /* 0x11C */ short Gauge;                          // 0x2
    /* 0x11E */ char BreakStage;                      // 0x1
    /* 0x11F */ unsigned char HelpAlpha;              // 0x1
    /* 0x120 */ unsigned char CurAlpha;               // 0x1
    /* 0x121 */ unsigned char MusicNo[69];            // 0x45
    /* 0x166 */ // 0x2 bytes padding
    /* 0x168 */ _EDSWIN_W Obj[34];                    // 0x990
    /* 0xAF8 */ _EDSRECORD_W rwork;                   // 0x4
    /* 0xAFC */ _EDSBREAK_W bwork;                    // 0x4
};

struct _EDSTEX_INIT_SET {   // size 0x28
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int flag;                             // 0x4
    /* 0x014 */ int id[5];                            // 0x14
};

struct _EDSTEX_W {   // size 0x20
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int u;                                // 0x4
    /* 0x00C */ int v;                                // 0x4
    /* 0x010 */ int w;                                // 0x4
    /* 0x014 */ int h;                                // 0x4
    /* 0x018 */ int z;                                // 0x4
    /* 0x01C */ int tex_num;                          // 0x4
};

/* variables (4) */
static int (*EdsWin_Func[5])(_EDSWIN_W *);                       /* @0x00285200 size 0x14 */
static _EDSTEX_W EdsMainTextureData[54];                         /* @0x00285220 size 0x6C0 */
static _EDSTEX_INIT_SET EdsMainWindowData[28];                   /* @0x002858E0 size 0x460 */
_EDSSYS_W *EDSSYSW;                                              /* @0x002A2254 size 0x4 */

/* functions defined (25) */
void EdsWinSelectAllFrameDisp(unsigned char _alpha);             /* 0x00233DE0-0x00233E6C lines 1572-1582 */
static void EdsWinSelectFrame(int _x, int _y, unsigned char _alpha, int _size); /* 0x00233E70-0x00234148 lines 1496-1564 */
void EdsWinSelectBox(int _x, int _y, char _flag);                /* 0x00234150-0x00234214 lines 1471-1490 */
static void EdsOrderCheckList(int _y, char _no, unsigned char _alpha); /* 0x00234220-0x0023434C lines 1443-1463 */
static void EdsCheck(int _x, int _y, int _type, unsigned char _alpha); /* 0x00234350-0x00234528 lines 1397-1435 */
void EdsWinAllDestroy(void);                                     /* 0x00234530-0x002346D8 lines 1358-1376 */
void EdsWinSetTex(_EDSWIN_W *winw, unsigned char _tex, int _flag); /* 0x002346E0-0x00234764 lines 1337-1345 */
void EdsWinSetMoveXY(_EDSWIN_W *winw, float x, float y);         /* 0x00234770-0x002347F0 lines 1309-1316 */
void EdsWinSetXY(_EDSWIN_W *winw, float x, float y);             /* 0x002347F0-0x00234848 lines 1285-1289 */
void EdsWinSetType(_EDSWIN_W *winw, char type);                  /* 0x00234850-0x002348B4 lines 1270-1277 */
void EdsWinSetMode(_EDSWIN_W *winw, int mode);                   /* 0x002348C0-0x002349DC lines 1233-1262 */
static void EdsWinSetDefaultPartsWH(_EDSWIN_W *winw);            /* 0x002349E0-0x00234AC0 lines 1183-1225 */
static void EdsWinDefaultAllSet(_EDSWIN_W *winw);                /* 0x00234AC0-0x00234B98 lines 1150-1170 */
static int EdsWinAlphaAnime(_EDSWIN_W *winw);                    /* 0x00234BA0-0x00234E38 lines 1089-1112 */
static int EdsWinWHMove(_EDSWIN_W *winw);                        /* 0x00234E40-0x00235008 lines 1042-1082 */
static int EdsWinXYMove(_EDSWIN_W *winw, int speed);             /* 0x00235010-0x00235220 lines 991-1035 */
static int EdsWinXYWHMove(_EDSWIN_W *winw, int speed);           /* 0x00235220-0x002354C0 lines 934-983 */
static void EdsWinDisp(_EDSWIN_W *winw);                         /* 0x002354C0-0x00235A18 lines 761-891 */
static int EdsWinDestroy(_EDSWIN_W *winw);                       /* 0x00235A20-0x00235A80 lines 738-753 */
static int EdsWinClose(_EDSWIN_W *winw);                         /* 0x00235A80-0x00235C60 lines 670-730 */
static int EdsWinMain(_EDSWIN_W *winw);                          /* 0x00235C60-0x00235D28 lines 656-662 */
static int EdsWinOpen(_EDSWIN_W *winw);                          /* 0x00235D30-0x00235F98 lines 571-648 */
static int EdsWinSet(_EDSWIN_W *winw);                           /* 0x00235FA0-0x00235FAC lines 560-563 */
_EDSWIN_W *EdsWinGetInit(int id);                                /* 0x00235FB0-0x00236094 lines 512-551 */
void EdsWinFunc(_EDSWIN_W *winw);                                /* 0x002360A0-0x00236160 lines 479-505 */
