/*
 * C:\work\usam2\src\CS\lesson\les_sel_sec.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x0021E430-0x00220738
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _LESTEX_INIT_SET; struct _LESTEX_W; struct _tag_cModeData; struct _tag_cFilepackData;
struct _LESWIN_W; struct _tag_cLesSectionBannerData; struct _tag_cLes;
struct _tag_cStatusBarLesSelSection; struct _tag_cLesSelSection;

/* types (9) */
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

struct _tag_cModeData {   // size 0x14
    /* 0x000 */ int (*Init)();                        // 0x4
    /* 0x004 */ int (*Control)();                     // 0x4
    /* 0x008 */ int (*View)();                        // 0x4
    /* 0x00C */ int (*Update)();                      // 0x4
    /* 0x010 */ int level;                            // 0x4
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

struct _tag_cLesSectionBannerData {   // size 0x14
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int counter;                          // 0x4
    /* 0x00C */ int flag;                             // 0x4
    /* 0x010 */ int selcounter;                       // 0x4
};

struct _tag_cStatusBarLesSelSection {   // size 0x14
    /* 0x000 */ int level;                            // 0x4
    /* 0x004 */ int section;                          // 0x4
    /* 0x008 */ int mode;                             // 0x4
    /* 0x00C */ int counter;                          // 0x4
    /* 0x010 */ int counter2;                         // 0x4
};

struct _tag_cLesSelSection {   // size 0xCC
    /* 0x000 */ struct {   // size 0x14
        /* 0x000 */ unsigned char *msg;                   // 0x4
        /* 0x004 */ struct {   // size 0x8
            /* 0x000 */ short x;                              // 0x2
            /* 0x002 */ short y;                              // 0x2
            /* 0x004 */ short w;                              // 0x2
            /* 0x006 */ short h;                              // 0x2
        } *win;
        /* 0x008 */ short msg_num;                        // 0x2
        /* 0x00A */ short font_size;                      // 0x2
        /* 0x00C */ int ot;                               // 0x4
        /* 0x010 */ int bright;                           // 0x4
    } font_w;
    /* 0x014 */ int counter;                          // 0x4
    /* 0x018 */ float lx;                             // 0x4
    /* 0x01C */ float ly;                             // 0x4
    /* 0x020 */ int lcounter;                         // 0x4
    /* 0x024 */ int lflag;                            // 0x4
    /* 0x028 */ _tag_cLesSectionBannerData sbanner[8];  // 0xA0
    /* 0x0C8 */ int scount;                           // 0x4
};

/* variables (8) */
_tag_cLesSelSection *pLesSelSection;                             /* @0x002A212C size 0x4 */
static _tag_cStatusBarLesSelSection *pStatusBar;                 /* @0x002A2130 size 0x4 */
_tag_cLes *pLes;                                                 /* @0x002A2128 size 0x4 */
struct @anon3 kn_lesson_main_work;                               /* @0x006B25B0 size 0x88 */
static _tag_cStatusBarLesSelSection _pStatusBar;                 /* @0x006AF790 size 0x14 */
static _tag_cLesSelSection _pLesSelSection;                      /* @0x006AF7B0 size 0xCC */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (9) */
static int update_section_banner(void);                          /* 0x0021E430-0x0021E518 lines 904-932 */
static int view_section_banner(void);                            /* 0x0021E520-0x0021F184 lines 707-900 */
static int view_lesson_banner(void);                             /* 0x0021F190-0x0021F954 lines 478-625 */
int DispStatusBar_LesSelSection(int _bright, int _alpha, int _pri); /* 0x0021F960-0x0021FD64 lines 272-448 */
int InitStatusBar_LesSelSection(int level, int section, int mode); /* 0x0021FD70-0x0021FDCC lines 261-266 */
int Update_LesSelSection(void);                                  /* 0x0021FDD0-0x0021FF10 lines 232-252 */
int View_LesSelSection(void);                                    /* 0x0021FF10-0x0022008C lines 199-228 */
int Control_LesSelSection(void);                                 /* 0x00220090-0x00220518 lines 97-195 */
int Init_LesSelSection(void);                                    /* 0x00220520-0x00220738 lines 70-93 */
