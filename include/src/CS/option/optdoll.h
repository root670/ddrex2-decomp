/*
 * C:\work\usam2\src\CS\option\optdoll.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x0024F590-0x00250368
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _EDSS_DATA_W; struct _EDSS_PLAY_W; struct oni_mode; struct _tag_cModeData;
struct _tag_cFilepackData; struct _DDRCommonHeader; struct _tag_cDDR7Option;
struct _tag_cDDR7Record1; struct _tag_cDDR7OniRecord1; struct popular; struct G_RANKING_W_;
struct machine_point_work; struct _EDSSAVE_W; struct oni_course; struct _tag_OptDoll;
struct _tag_cOpt; struct _tag_cDDR7SaveData; struct _tag_cItemData;

/* types (18) */
struct _EDSS_DATA_W {   // size 0x10
    /* 0x000 */ unsigned int score[2];                // 0x8
    /* 0x008 */ int combo;                            // 0x4
    /* 0x00C */ int stage;                            // 0x4
};

struct _EDSS_PLAY_W {   // size 0x60
    /* 0x000 */ _EDSS_DATA_W p_single[3];             // 0x30
    /* 0x030 */ _EDSS_DATA_W p_double[3];             // 0x30
};

struct _EDSSAVE_W {   // size 0x238
    /* 0x000 */ _EDSS_PLAY_W reg[2];                  // 0xC0
    /* 0x0C0 */ _EDSS_DATA_W max_point;               // 0x10
    /* 0x0D0 */ unsigned int PlayFlag[90];            // 0x168
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

struct _tag_OptDoll {   // size 0x2C
    /* 0x000 */ void *loadaddr;                       // 0x4
    /* 0x004 */ int p_counter;                        // 0x4
    /* 0x008 */ int timer;                            // 0x4
    /* 0x00C */ short dstep;                          // 0x2
    /* 0x00E */ short new_chr;                        // 0x2
    /* 0x010 */ short cur_chr;                        // 0x2
    /* 0x012 */ short sel_id[3];                      // 0x6
    /* 0x018 */ int uratimer;                         // 0x4
    /* 0x01C */ int upcounter;                        // 0x4
    /* 0x020 */ short uchrid;                         // 0x2
    /* 0x022 */ char loading;                         // 0x1
    /* 0x023 */ char uramode;                         // 0x1
    /* 0x024 */ char ustep;                           // 0x1
    /* 0x025 */ char umotid;                          // 0x1
    /* 0x026 */ char uautoplay;                       // 0x1
    /* 0x027 */ char utoon;                           // 0x1
    /* 0x028 */ char ufloor;                          // 0x1
    /* 0x029 */ // 0x3 bytes padding
};

struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
};

struct _tag_cOpt {   // size 0x17C
    /* 0x000 */ int StepOpt;                          // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int cRepeat2[2];                      // 0x8
    /* 0x018 */ int Cursor[4];                        // 0x10
    /* 0x028 */ int Step;                             // 0x4
    /* 0x02C */ int Mode;                             // 0x4
    /* 0x030 */ int NextMode;                         // 0x4
    /* 0x034 */ int bDraw;                            // 0x4
    /* 0x038 */ int bTopDown;                         // 0x4
    /* 0x03C */ int Step2;                            // 0x4
    /* 0x040 */ int init_ok;                          // 0x4
    /* 0x044 */ int sd_dir;                           // 0x4
    /* 0x048 */ int title_step;                       // 0x4
    /* 0x04C */ int title_count;                      // 0x4
    /* 0x050 */ int nItemLetter;                      // 0x4
    /* 0x054 */ unsigned int str_base_address;        // 0x4
    /* 0x058 */ int out_str_exp_id;                   // 0x4
    /* 0x05C */ int is_draw_nest_button;              // 0x4
    /* 0x060 */ _tag_cModeData *mode_data_table;      // 0x4
    /* 0x064 */ _tag_cModeData *mode_data;            // 0x4
    /* 0x068 */ int item_bright[9];                   // 0x24
    /* 0x08C */ int item_select_num;                  // 0x4
    /* 0x090 */ int item_bright_delay[9];             // 0x24
    /* 0x0B4 */ int item_bright_count;                // 0x4
    /* 0x0B8 */ int item_bright_mode;                 // 0x4
    /* 0x0BC */ int subtitle_flag;                    // 0x4
    /* 0x0C0 */ int black_tile_rate;                  // 0x4
    /* 0x0C4 */ int black_tile_mode;                  // 0x4
    /* 0x0C8 */ int black_tile_flag;                  // 0x4
    /* 0x0CC */ int black_tile_count;                 // 0x4
    /* 0x0D0 */ int black_tile_open;                  // 0x4
    /* 0x0D4 */ float orange_arrow_x;                 // 0x4
    /* 0x0D8 */ float orange_arrow_y;                 // 0x4
    /* 0x0DC */ float orange_arrow_xn;                // 0x4
    /* 0x0E0 */ float orange_arrow_yn;                // 0x4
    /* 0x0E4 */ int orange_arrow_step;                // 0x4
    /* 0x0E8 */ int orange_arrow_count;               // 0x4
    /* 0x0EC */ int orange_arrow_angle;               // 0x4
    /* 0x0F0 */ int orange_arrow_zangle;              // 0x4
    /* 0x0F4 */ int orange_arrow_zanglen;             // 0x4
    /* 0x0F8 */ int ddrmax_count;                     // 0x4
    /* 0x0FC */ int ddrmax_type;                      // 0x4
    /* 0x100 */ _tag_cFilepackData tblFilepack[12];   // 0x60
    /* 0x160 */ int frame_cursor_counter;             // 0x4
    /* 0x164 */ int lang_butt_tex_id;                 // 0x4
    /* 0x168 */ int lang_font_tex_id;                 // 0x4
    /* 0x16C */ int lang_enable_cancel;               // 0x4
    /* 0x170 */ int optlang_exit_flag;                // 0x4
    /* 0x174 */ int putscore2_mode;                   // 0x4
    /* 0x178 */ int doll_new_mode;                    // 0x4
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

struct _tag_cItemData {   // size 0xC
    /* 0x000 */ int (*GetBoolExist)();                // 0x4
    /* 0x004 */ int (*GetNew)();                      // 0x4
    /* 0x008 */ char *name;                           // 0x4
};

/* variables (10) */
static struct @anon2 crect;                                      /* @0x002A2610 size 0x8 */
static _tag_OptDoll *wk;                                         /* @0x002A2618 size 0x4 */
static _tag_cItemData ItemData[6];                               /* @0x0028B350 size 0x48 */
static int outstr_exp[6];                                        /* @0x0028B3A0 size 0x18 */
static int outstr_title[6];                                      /* @0x0028B3C0 size 0x18 */
_tag_cOpt *pOpt;                                                 /* @0x002A05C0 size 0x4 */
_tag_cDDR7SaveData SaveData;                                     /* @0x002B0470 size 0x5E30 */
_tag_cDDR7Option OptionDefault;                                  /* @0x00274000 size 0x40 */
struct @anon1 lst;                                               /* @0x006B6AD0 size 0x3E */
static _tag_OptDoll _pOptDoll;                                   /* @0x006B6B10 size 0x2C */

/* functions defined (11) */
int Update_OptDoll(void);                                        /* 0x0024F590-0x0024F630 lines 425-440 */
int View_OptDoll(void);                                          /* 0x0024F630-0x0024FB4C lines 294-421 */
static int control_lr(int *pcursor, int _lr);                    /* 0x0024FB50-0x0024FC80 lines 265-290 */
int Control_OptDoll(void);                                       /* 0x0024FC80-0x0025015C lines 139-260 */
int Init_OptDoll(void);                                          /* 0x00250160-0x002502CC lines 98-133 */
static int GetBoolExist_exit(void);                              /* 0x002502D0-0x002502D8 lines 65-65 */
static int GetBoolExist_3p(void);                                /* 0x002502E0-0x002502F4 lines 64-64 */
static int GetBoolExist_2p(void);                                /* 0x00250300-0x00250314 lines 63-63 */
static int GetBoolExist_1p(void);                                /* 0x00250320-0x00250334 lines 62-62 */
static int GetBoolExist_guest(void);                             /* 0x00250340-0x00250354 lines 61-61 */
static int GetBoolExist_disp(void);                              /* 0x00250360-0x00250368 lines 60-60 */
