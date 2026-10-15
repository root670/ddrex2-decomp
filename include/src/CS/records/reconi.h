/*
 * C:\work\usam2\src\CS\records\reconi.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x00224E20-0x00227B00
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _EDSS_DATA_W; struct _tag_cRecRecord1; struct _tag_cRecmData; struct _tag_cRecmDelWnd;
struct _tag_cModeData; struct _tag_cRecItem; struct _tag_cRecBK1; struct _tag_cFilepackData;
struct _tag_cRecTitleInfo; struct _tag_cRecOniTitleInfo; struct _EDSS_PLAY_W;
struct _tag_cDDR7OniRecord1; struct _tag_cRecOniRecord1; struct oni_mode;
struct _DDRCommonHeader; struct _tag_cDDR7Option; struct _tag_cDDR7Record1; struct popular;
struct G_RANKING_W_; struct machine_point_work; struct _EDSSAVE_W; struct oni_course;
struct _tag_cRecOniData; struct _tag_cRecm; struct _tag_cRec; struct _tag_cDDR7SaveData;
struct _tag_cRecOni;

/* types (27) */
struct _EDSS_DATA_W {   // size 0x10
    /* 0x000 */ unsigned int score[2];                // 0x8
    /* 0x008 */ int combo;                            // 0x4
    /* 0x00C */ int stage;                            // 0x4
};

struct _EDSS_PLAY_W {   // size 0x60
    /* 0x000 */ _EDSS_DATA_W p_single[3];             // 0x30
    /* 0x030 */ _EDSS_DATA_W p_double[3];             // 0x30
};

struct _tag_cDDR7OniRecord1 {   // size 0x38
    /* 0x000 */ unsigned int Score[4];                // 0x10
    /* 0x010 */ unsigned short Time[4];               // 0x8
    /* 0x018 */ unsigned short Combo[4];              // 0x8
    /* 0x020 */ unsigned short Miss[4];               // 0x8
    /* 0x028 */ unsigned char Stage[4];               // 0x4
    /* 0x02C */ unsigned char Clear[4];               // 0x4
    /* 0x030 */ unsigned char Level[4];               // 0x4
    /* 0x034 */ unsigned char is_first_clear;         // 0x1
    /* 0x035 */ unsigned char pad[3];                 // 0x3
};

struct _tag_cRecmData {   // size 0x18
    /* 0x000 */ _tag_cRecRecord1 *data;               // 0x4
    /* 0x004 */ int y[2];                             // 0x8
    /* 0x00C */ int a[2];                             // 0x8
    /* 0x014 */ int bright;                           // 0x4
};

struct _tag_cRecmDelWnd {   // size 0x1C
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int bri;                              // 0x4
    /* 0x010 */ int msg_id;                           // 0x4
    /* 0x014 */ int draw_wnd;                         // 0x4
    /* 0x018 */ int draw_yn;                          // 0x4
};

struct _tag_cRecm {   // size 0x158
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int fade_count;                       // 0x4
    /* 0x00C */ int fade_mode;                        // 0x4
    /* 0x010 */ int music_num;                        // 0x4
    /* 0x014 */ int cur_seg;                          // 0x4
    /* 0x018 */ int cur_off;                          // 0x4
    /* 0x01C */ int cur_col;                          // 0x4
    /* 0x020 */ int move_mode;                        // 0x4
    /* 0x024 */ int accelerate_flag;                  // 0x4
    /* 0x028 */ int cursor_count;                     // 0x4
    /* 0x02C */ int base_y;                           // 0x4
    /* 0x030 */ int level_count;                      // 0x4
    /* 0x034 */ int focus_bright_flag;                // 0x4
    /* 0x038 */ int focus_trg;                        // 0x4
    /* 0x03C */ _tag_cRecmData table_data[8];         // 0xC0
    /* 0x0FC */ int dir_arrow_count[2];               // 0x8
    /* 0x104 */ int dir_arrow_step[2];                // 0x8
    /* 0x10C */ int dir_arrow_bright[2];              // 0x8
    /* 0x114 */ _tag_cRecRecord1 *del_data;           // 0x4
    /* 0x118 */ int del_entry_mode;                   // 0x4
    /* 0x11C */ _tag_cRecmDelWnd wnd;                 // 0x1C
    /* 0x138 */ int ope_step[4];                      // 0x10
    /* 0x148 */ int ope_bright[4];                    // 0x10
};

struct _tag_cRecItem {   // size 0x30
    /* 0x000 */ int x[3];                             // 0xC
    /* 0x00C */ int y[3];                             // 0xC
    /* 0x018 */ int a[3];                             // 0xC
    /* 0x024 */ int bright;                           // 0x4
    /* 0x028 */ int col;                              // 0x4
    /* 0x02C */ unsigned char *str;                   // 0x4
};

struct _tag_cRecBK1 {   // size 0x18
    /* 0x000 */ int h[3];                             // 0xC
    /* 0x00C */ int y[3];                             // 0xC
};

struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
};

struct _tag_cRecTitleInfo {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

struct _tag_cRecOniTitleInfo {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short course;                // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

struct _tag_cRec {   // size 0x644
    /* 0x000 */ int StepRec;                          // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int cRepeat2[2];                      // 0x8
    /* 0x018 */ int Cursor[4];                        // 0x10
    /* 0x028 */ int cWait2;                           // 0x4
    /* 0x02C */ int Step;                             // 0x4
    /* 0x030 */ int Mode;                             // 0x4
    /* 0x034 */ int NextMode;                         // 0x4
    /* 0x038 */ int bDraw;                            // 0x4
    /* 0x03C */ int bTopDown;                         // 0x4
    /* 0x040 */ int Step2;                            // 0x4
    /* 0x044 */ int init_ok;                          // 0x4
    /* 0x048 */ int control_ok;                       // 0x4
    /* 0x04C */ int nItemLetter;                      // 0x4
    /* 0x050 */ unsigned int str_base_address;        // 0x4
    /* 0x054 */ int out_str_exp_id;                   // 0x4
    /* 0x058 */ _tag_cModeData *mode_data_table;      // 0x4
    /* 0x05C */ _tag_cModeData *mode_data;            // 0x4
    /* 0x060 */ _tag_cRecItem item[6];                // 0x120
    /* 0x180 */ int item_select_num;                  // 0x4
    /* 0x184 */ int item_count;                       // 0x4
    /* 0x188 */ int item_state;                       // 0x4
    /* 0x18C */ _tag_cRecBK1 bk1[4];                  // 0x60
    /* 0x1EC */ int bk1_open;                         // 0x4
    /* 0x1F0 */ int bk1_flag;                         // 0x4
    /* 0x1F4 */ int bk1_count;                        // 0x4
    /* 0x1F8 */ int bk1_fill_num;                     // 0x4
    /* 0x1FC */ _tag_cFilepackData tblFilepack[22];   // 0xB0
    /* 0x2AC */ _tag_cRecTitleInfo TitleInfo[80];     // 0x280
    /* 0x52C */ _tag_cRecOniTitleInfo OniTitleInfo[32];  // 0x100
    /* 0x62C */ int diet_date;                        // 0x4
    /* 0x630 */ struct {   // size 0xC
        /* 0x000 */ int year;                             // 0x4
        /* 0x004 */ int month;                            // 0x4
        /* 0x008 */ int day;                              // 0x4
    } date;
    /* 0x63C */ int diet_mode;                        // 0x4
    /* 0x640 */ int diet_swap_flag;                   // 0x4
};

struct _EDSSAVE_W {   // size 0x238
    /* 0x000 */ _EDSS_PLAY_W reg[2];                  // 0xC0
    /* 0x0C0 */ _EDSS_DATA_W max_point;               // 0x10
    /* 0x0D0 */ unsigned int PlayFlag[90];            // 0x168
};

struct _tag_cRecOniRecord1 {   // size 0x40
    /* 0x000 */ _tag_cDDR7OniRecord1 data;            // 0x38
    /* 0x038 */ _tag_cDDR7OniRecord1 *original;       // 0x4
    /* 0x03C */ int course;                           // 0x4
};

struct _tag_cRecOniData {   // size 0x18
    /* 0x000 */ _tag_cRecOniRecord1 *data;            // 0x4
    /* 0x004 */ int y[2];                             // 0x8
    /* 0x00C */ int a[2];                             // 0x8
    /* 0x014 */ int bright;                           // 0x4
};

struct oni_mode {   // size 0xC
    /* 0x000 */ unsigned int link_num;                // 0x4
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ unsigned char seq_transfer;           // 0x1
    /* 0x006 */ unsigned char sp_music;               // 0x1
    /* 0x007 */ unsigned char add_life;               // 0x1
    /* 0x008 */ unsigned int hidden : 2;              // bits 0..1
    /* 0x008 */ unsigned int thinout : 1;             // bits 2..2
    /* 0x008 */ unsigned int free : 1;                // bits 3..3
    /* 0x008 */ unsigned int soft : 1;                // bits 4..4
    /* 0x008 */ unsigned int boost : 2;               // bits 5..6
    /* 0x008 */ unsigned int speed : 5;               // bits 7..11
    /* 0x008 */ unsigned int scroll : 2;              // bits 12..13
    /* 0x008 */ unsigned int freeze : 1;              // bits 14..14
    /* 0x008 */ unsigned int vivid : 2;               // bits 15..16
    /* 0x008 */ unsigned int anime : 2;               // bits 17..18
    /* 0x008 */ unsigned int dark : 1;                // bits 19..19
    /* 0x008 */ unsigned int pad : 12;                // bits 20..31
};

struct oni_course {   // size 0x110
    /* 0x000 */ unsigned int course_allnum;           // 0x4
    /* 0x004 */ unsigned int course_defnum;           // 0x4
    /* 0x008 */ short flag;                           // 0x2
    /* 0x00A */ short order;                          // 0x2
    /* 0x00C */ short start_life;                     // 0x2
    /* 0x00E */ short stage;                          // 0x2
    /* 0x010 */ int single_steps;                     // 0x4
    /* 0x014 */ int double_steps;                     // 0x4
    /* 0x018 */ int hide;                             // 0x4
    /* 0x01C */ int option;                           // 0x4
    /* 0x020 */ oni_mode mode[20];                    // 0xF0
};

struct _tag_cModeData {   // size 0x14
    /* 0x000 */ int (*Init)();                        // 0x4
    /* 0x004 */ int (*Control)();                     // 0x4
    /* 0x008 */ int (*View)();                        // 0x4
    /* 0x00C */ int (*Update)();                      // 0x4
    /* 0x010 */ int level;                            // 0x4
};

struct machine_point_work {   // size 0x14
    /* 0x000 */ unsigned int hide_show[2];            // 0x8
    /* 0x008 */ unsigned int status;                  // 0x4
    /* 0x00C */ unsigned int period_time;             // 0x4
    /* 0x010 */ int cur_point;                        // 0x4
};

struct _DDRCommonHeader {   // size 0x10
    /* 0x000 */ unsigned char Type;                   // 0x1
    /* 0x001 */ unsigned char Platform;               // 0x1
    /* 0x002 */ unsigned char Hardware;               // 0x1
    /* 0x003 */ unsigned char Version;                // 0x1
    /* 0x004 */ unsigned char Area;                   // 0x1
    /* 0x005 */ signed char tmp;                      // 0x1
    /* 0x006 */ unsigned short title;                 // 0x2
    /* 0x008 */ unsigned int t_info[2];               // 0x8
};

struct _tag_cDDR7Option {   // size 0x40
    /* 0x000 */ unsigned char Sound;                  // 0x1
    /* 0x001 */ unsigned char Voice;                  // 0x1
    /* 0x002 */ signed char Timing;                   // 0x1
    /* 0x003 */ char pad_sound[1];                    // 0x1
    /* 0x004 */ unsigned char KeyConfig[4];           // 0x4
    /* 0x008 */ unsigned char Vibration;              // 0x1
    /* 0x009 */ unsigned char DPlay;                  // 0x1
    /* 0x00A */ char pad_cont[2];                     // 0x2
    /* 0x00C */ unsigned char AutoSave;               // 0x1
    /* 0x00D */ unsigned char FolderLoad;             // 0x1
    /* 0x00E */ char pad_mc[2];                       // 0x2
    /* 0x010 */ unsigned char Level;                  // 0x1
    /* 0x011 */ unsigned char MaxStage[3];            // 0x3
    /* 0x014 */ unsigned char GameOver;               // 0x1
    /* 0x015 */ unsigned char TimeLimit;              // 0x1
    /* 0x016 */ unsigned char EventMode;              // 0x1
    /* 0x017 */ unsigned char DefaultDifficulty;      // 0x1
    /* 0x018 */ char pad_game[8];                     // 0x8
    /* 0x020 */ unsigned char BgEffect;               // 0x1
    /* 0x021 */ unsigned char BgBright;               // 0x1
    /* 0x022 */ unsigned char DangerDisplay;          // 0x1
    /* 0x023 */ unsigned char StepMarkColor;          // 0x1
    /* 0x024 */ signed char screen_x;                 // 0x1
    /* 0x025 */ signed char screen_y;                 // 0x1
    /* 0x026 */ unsigned char FlickerFree;            // 0x1
    /* 0x027 */ unsigned char SongDisplay;            // 0x1
    /* 0x028 */ unsigned char DietMeasure;            // 0x1
    /* 0x029 */ unsigned char DietDisplay;            // 0x1
    /* 0x02A */ unsigned char DietTime;               // 0x1
    /* 0x02B */ unsigned char DietPlayDefault;        // 0x1
    /* 0x02C */ unsigned char DietWeightUnit;         // 0x1
    /* 0x02D */ char pad_diet[3];                     // 0x3
    /* 0x030 */ unsigned char Language;               // 0x1
    /* 0x031 */ char pad_lang[7];                     // 0x7
    /* 0x038 */ unsigned char DollDisp;               // 0x1
    /* 0x039 */ unsigned char DollGuestNum;           // 0x1
    /* 0x03A */ unsigned char DollChara[3];           // 0x3
    /* 0x03D */ char pad[3];                          // 0x3
};

struct _tag_cDDR7Record1 {   // size 0x90
    /* 0x000 */ unsigned int Score[10];               // 0x28
    /* 0x028 */ unsigned int Bonus[10];               // 0x28
    /* 0x050 */ unsigned int nPlayed;                 // 0x4
    /* 0x054 */ unsigned short LinkNum;               // 0x2
    /* 0x056 */ unsigned short Combo[10];             // 0x14
    /* 0x06A */ unsigned short ComboMax[10];          // 0x14
    /* 0x07E */ unsigned char Level[10];              // 0xA
    /* 0x088 */ unsigned char little_flag[2];         // 0x2
    /* 0x08A */ char pad[6];                          // 0x6
};

struct popular {   // size 0x4B4
    /* 0x000 */ short cur_c;                          // 0x2
    /* 0x002 */ short last_c;                         // 0x2
    /* 0x004 */ unsigned short count[150][4];         // 0x4B0
};

struct G_RANKING_W_ {   // size 0x10
    /* 0x000 */ char name[4];                         // 0x4
    /* 0x004 */ // 0x4 bytes padding
    /* 0x008 */ unsigned long score;                  // 0x8
};

struct _tag_cDDR7SaveData {   // size 0x5E30
    /* 0x000 */ _DDRCommonHeader CommonHeader;        // 0x10
    /* 0x010 */ _tag_cDDR7Option Option;              // 0x40
    /* 0x050 */ _tag_cDDR7Record1 MRecord[80];        // 0x2D00
    /* 0x2D50 */ unsigned char Information[144];      // 0x90
    /* 0x2DE0 */ unsigned int nMusic;                 // 0x4
    /* 0x2DE4 */ unsigned int nBoot;                  // 0x4
    /* 0x2DE8 */ unsigned int nPlayerType[3];         // 0xC
    /* 0x2DF4 */ unsigned int nDifficulty[5];         // 0x14
    /* 0x2E08 */ int nwork[2];                        // 0x8
    /* 0x2E10 */ unsigned char LessonWork[32];        // 0x20
    /* 0x2E30 */ _tag_cDDR7OniRecord1 OniRecord[32];  // 0x700
    /* 0x3530 */ popular popular;                     // 0x4B4
    /* 0x39E4 */ // 0x4 bytes padding
    /* 0x39E8 */ G_RANKING_W_ high_score[30];         // 0x1E0
    /* 0x3BC8 */ machine_point_work machine_p;        // 0x14
    /* 0x3BDC */ unsigned int HideMusic[4];           // 0x10
    /* 0x3BEC */ unsigned int HideFlag[4];            // 0x10
    /* 0x3BFC */ unsigned int HideDoll[2];            // 0x8
    /* 0x3C04 */ _EDSSAVE_W EdsRecords;               // 0x238
    /* 0x3E3C */ oni_course oni_order[3];             // 0x330
    /* 0x416C */ oni_course dietprogram_order[3];     // 0x330
    /* 0x449C */ struct {   // size 0xCC8
        /* 0x000 */ unsigned int program_calorie[9];      // 0x24
        /* 0x024 */ unsigned int program_play_count[9];   // 0x24
        /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
        /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
    } diet_calorie_record[2];
    /* 0x5E2C */ // 0x4 bytes padding
};

struct _tag_cRecOni {   // size 0x12C
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int fade_count;                       // 0x4
    /* 0x00C */ int fade_mode;                        // 0x4
    /* 0x010 */ int course_num;                       // 0x4
    /* 0x014 */ int cur_seg;                          // 0x4
    /* 0x018 */ int cur_off;                          // 0x4
    /* 0x01C */ int cur_col;                          // 0x4
    /* 0x020 */ int move_mode;                        // 0x4
    /* 0x024 */ int accelerate_flag;                  // 0x4
    /* 0x028 */ int cursor_count;                     // 0x4
    /* 0x02C */ int base_y;                           // 0x4
    /* 0x030 */ int level_count;                      // 0x4
    /* 0x034 */ int focus_bright_flag;                // 0x4
    /* 0x038 */ int focus_trg;                        // 0x4
    /* 0x03C */ _tag_cRecOniData table_data[8];       // 0xC0
    /* 0x0FC */ int dir_arrow_count[2];               // 0x8
    /* 0x104 */ int dir_arrow_step[2];                // 0x8
    /* 0x10C */ int dir_arrow_bright[2];              // 0x8
    /* 0x114 */ _tag_cRecOniRecord1 *del_data;        // 0x4
    /* 0x118 */ int del_entry_mode;                   // 0x4
    /* 0x11C */ int ope_step[2];                      // 0x8
    /* 0x124 */ int ope_bright[2];                    // 0x8
};

struct _tag_cRecRecord1 {   // size 0x94
    /* 0x000 */ _tag_cDDR7Record1 data;               // 0x90
    /* 0x090 */ _tag_cDDR7Record1 *original;          // 0x4
};

/* variables (5) */
static _tag_cRecOni *pRecOni;                                    /* @0x002A2140 size 0x4 */
_tag_cRec *pRec;                                                 /* @0x002A06B8 size 0x4 */
_tag_cRecm *pRecm;                                               /* @0x002A06BC size 0x4 */
_tag_cDDR7SaveData SaveData;                                     /* @0x002B0470 size 0x5E30 */
static _tag_cRecOni _pRecOni;                                    /* @0x006B26A0 size 0x12C */

/* functions defined (19) */
int Update_Reconi(void);                                         /* 0x00224E20-0x00225068 lines 2148-2188 */
int View_Reconi(void);                                           /* 0x00225070-0x002251A0 lines 2097-2144 */
int Control_Reconi(void);                                        /* 0x002251A0-0x00225270 lines 2084-2093 */
int Init_Reconi(void);                                           /* 0x00225270-0x00225370 lines 2064-2080 */
static void draw_ope(void);                                      /* 0x00225370-0x00225658 lines 1951-2042 */
static void draw_dir_arrow(void);                                /* 0x00225660-0x00225860 lines 1878-1921 */
static void draw_cursor(void);                                   /* 0x00225860-0x00225AB4 lines 1767-1862 */
static void draw_table(void);                                    /* 0x00225AC0-0x002265B0 lines 1390-1761 */
static void draw_detail_data(void);                              /* 0x002265B0-0x00226968 lines 1197-1367 */
static void puts_combo(short _x, short _y, int _val, int _bright, int _pri, int _alpha); /* 0x00226970-0x00226B48 lines 1114-1151 */
static void puts_re2424(short _x, short _y, int _val, int _bright, int _pri, int _alpha, int tex_num); /* 0x00226B50-0x00226D34 lines 1071-1108 */
static int control_loop(void);                                   /* 0x00226D40-0x00227364 lines 722-892 */
static int control_delete(void);                                 /* 0x00227370-0x002274B8 lines 641-687 */
static void SetDelStep(int _step);                               /* 0x002274C0-0x002275E4 lines 589-618 */
static int check_move_cursor(int dir, int *segment, int *offset); /* 0x002275F0-0x00227688 lines 454-485 */
static void set_data_scroll(int dir);                            /* 0x00227690-0x00227830 lines 388-445 */
static void update_data(void);                                   /* 0x00227830-0x00227908 lines 344-383 */
static void init_data(void);                                     /* 0x00227910-0x002279A4 lines 295-322 */
static void init_oni_record(void);                               /* 0x002279B0-0x00227B00 lines 224-290 */
