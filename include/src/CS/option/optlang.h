/*
 * C:\work\usam2\src\CS\option\optlang.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00239680-0x0023A128
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _tag_cModeData; struct _tag_cFilepackData; struct _tag_cOptLang; struct _tag_cItemData;
struct _tag_cOpt;

/* types (5) */
struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
};

struct _tag_cOptLang {   // size 0x44
    /* 0x000 */ int ope_step[8];                      // 0x20
    /* 0x020 */ int ope_bright[8];                    // 0x20
    /* 0x040 */ int cursor;                           // 0x4
};

struct _tag_cModeData {   // size 0x14
    /* 0x000 */ int (*Init)();                        // 0x4
    /* 0x004 */ int (*Control)();                     // 0x4
    /* 0x008 */ int (*View)();                        // 0x4
    /* 0x00C */ int (*Update)();                      // 0x4
    /* 0x010 */ int level;                            // 0x4
};

struct _tag_cItemData {   // size 0xC
    /* 0x000 */ int (*GetBoolExist)();                // 0x4
    /* 0x004 */ int (*GetNew)();                      // 0x4
    /* 0x008 */ char *name;                           // 0x4
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

/* variables (6) */
_tag_cOptLang *pOptLang;                                         /* @0x002A2274 size 0x4 */
static _tag_cItemData ItemData[5];                               /* @0x00285D80 size 0x3C */
static unsigned int button_bit_table[6];                         /* @0x00285DC0 size 0x18 */
static struct @anon3 button_tex[6];                              /* @0x00285DE0 size 0x60 */
_tag_cOpt *pOpt;                                                 /* @0x002A05C0 size 0x4 */
static _tag_cOptLang _pOptLang;                                  /* @0x006B3830 size 0x44 */

/* functions defined (9) */
int Update_Optlang(void);                                        /* 0x00239680-0x00239788 lines 400-432 */
int View_Optlang(void);                                          /* 0x00239790-0x00239C98 lines 236-396 */
int Control_Optlang(void);                                       /* 0x00239CA0-0x0023A004 lines 144-230 */
int Init_Optlang(void);                                          /* 0x0023A010-0x0023A0D4 lines 102-139 */
static int GetBoolExist_spanish(void);                           /* 0x0023A0E0-0x0023A0E8 lines 52-52 */
static int GetBoolExist_italian(void);                           /* 0x0023A0F0-0x0023A0F8 lines 51-51 */
static int GetBoolExist_german(void);                            /* 0x0023A100-0x0023A108 lines 50-50 */
static int GetBoolExist_french(void);                            /* 0x0023A110-0x0023A118 lines 49-49 */
static int GetBoolExist_english(void);                           /* 0x0023A120-0x0023A128 lines 48-48 */
