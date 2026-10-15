/*
 * C:\work\usam2\src\CS\lesson\les_sel_lv.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0021C450-0x0021D8CC
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _LESTEX_INIT_SET; struct _LESTEX_W; struct _tag_cModeData; struct _tag_cFilepackData;
struct _LESWIN_W; struct _tag_cLesSelLevelCursor; struct _tag_cLes; struct _tag_cLesSelLevel;

/* types (8) */
struct _tag_cLesSelLevelCursor {   // size 0xA0
    /* 0x000 */ int pmode;                            // 0x4
    /* 0x004 */ int pcount;                           // 0x4
    /* 0x008 */ int pcounter;                         // 0x4
    /* 0x00C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x010 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } pos;
    /* 0x020 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } npos;
    /* 0x030 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } ipos;
    /* 0x040 */ int amode;                            // 0x4
    /* 0x044 */ int acount;                           // 0x4
    /* 0x048 */ int acounter;                         // 0x4
    /* 0x04C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x050 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } angle;
    /* 0x060 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } nangle;
    /* 0x070 */ struct {   // size 0x10
        /* 0x000 */ float vx;                             // 0x4
        /* 0x004 */ float vy;                             // 0x4
        /* 0x008 */ float vz;                             // 0x4
        /* 0x00C */ float vw;                             // 0x4
    } iangle;
    /* 0x080 */ int step;                             // 0x4
    /* 0x084 */ int can_select;                       // 0x4
    /* 0x088 */ int bright;                           // 0x4
    /* 0x08C */ int alpha;                            // 0x4
    /* 0x090 */ int pri;                              // 0x4
    /* 0x094 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
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

struct _tag_cModeData {   // size 0x14
    /* 0x000 */ int (*Init)();                        // 0x4
    /* 0x004 */ int (*Control)();                     // 0x4
    /* 0x008 */ int (*View)();                        // 0x4
    /* 0x00C */ int (*Update)();                      // 0x4
    /* 0x010 */ int level;                            // 0x4
};

struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
};

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

struct _tag_cLes {   // size 0x284
    /* 0x000 */ int StepLes;                          // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int Cursor[4];                        // 0x10
    /* 0x020 */ int Step;                             // 0x4
    /* 0x024 */ int Mode;                             // 0x4
    /* 0x028 */ int NextMode;                         // 0x4
    /* 0x02C */ int bDraw;                            // 0x4
    /* 0x030 */ int bTopDown;                         // 0x4
    /* 0x034 */ int Step2;                            // 0x4
    /* 0x038 */ int init_ok;                          // 0x4
    /* 0x03C */ int sd_dir;                           // 0x4
    /* 0x040 */ int nItemLetter;                      // 0x4
    /* 0x044 */ unsigned char **ExpKanji;             // 0x4
    /* 0x048 */ _tag_cModeData *mode_data_table;      // 0x4
    /* 0x04C */ _tag_cModeData *mode_data;            // 0x4
    /* 0x050 */ int base_tex_id;                      // 0x4
    /* 0x054 */ int level;                            // 0x4
    /* 0x058 */ int section;                          // 0x4
    /* 0x05C */ int play_pid;                         // 0x4
    /* 0x060 */ int ret_dance_play_step;              // 0x4
    /* 0x064 */ int music_label;                      // 0x4
    /* 0x068 */ int loaded_music_label;               // 0x4
    /* 0x06C */ _tag_cFilepackData tblFilepack[10];   // 0x50
    /* 0x0BC */ int sd_play_flag;                     // 0x4
    /* 0x0C0 */ int sd_called_flag;                   // 0x4
    /* 0x0C4 */ int sd_stopped_flag;                  // 0x4
    /* 0x0C8 */ int timing_cursor;                    // 0x4
    /* 0x0CC */ int timing_keep_flag[3];              // 0xC
    /* 0x0D8 */ unsigned int timing_keep_data[3][3];  // 0x24
    /* 0x0FC */ unsigned char font[4][64];            // 0x100
    /* 0x1FC */ _LESWIN_W winp[2];                    // 0x88
};

struct _tag_cLesSelLevel {   // size 0xB0
    /* 0x000 */ int counter;                          // 0x4
    /* 0x004 */ int disp_level;                       // 0x4
    /* 0x008 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x010 */ _tag_cLesSelLevelCursor Cursor;       // 0xA0
};

/* variables (7) */
_tag_cLesSelLevel *pLesSelLevel;                                 /* @0x002A2124 size 0x4 */
static short anime_offset[18];                                   /* @0x00294F50 size 0x24 */
static int cur_y_table[3];                                       /* @0x0027EB68 size 0xC */
_tag_cLes *pLes;                                                 /* @0x002A2128 size 0x4 */
static _tag_cLesSelLevel _pLesSelLevel;                          /* @0x006AF450 size 0xB0 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (8) */
static void draw_cur(void);                                      /* 0x0021C450-0x0021C8F0 lines 693-771 */
static void control_cur(void);                                   /* 0x0021C8F0-0x0021CC28 lines 627-677 */
static void init_cur(void);                                      /* 0x0021CC30-0x0021CD40 lines 596-625 */
int Update_LesSelLevel(void);                                    /* 0x0021CD40-0x0021CE70 lines 484-503 */
int View_LesSelLevel(void);                                      /* 0x0021CE70-0x0021D470 lines 325-480 */
static int cursor_ud(int dir);                                   /* 0x0021D470-0x0021D570 lines 283-309 */
int Control_LesSelLevel(void);                                   /* 0x0021D570-0x0021D7BC lines 186-280 */
int Init_LesSelLevel(void);                                      /* 0x0021D7C0-0x0021D8CC lines 108-182 */
