/*
 * C:\work\usam2\src\CS\lesson\kn_ldisp.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x00223610-0x00224E14
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _LESTEX_INIT_SET; struct _LESTEX_W; struct _tag_cModeData; struct _tag_cFilepackData;
struct _LESWIN_W; struct _tag_cLes; struct _tag_cLesPlay;

/* types (7) */
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

struct _tag_cLesPlay {   // size 0x54
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int start_beat_count;                 // 0x4
    /* 0x00C */ int start_music_count;                // 0x4
    /* 0x010 */ int end_beat_count;                   // 0x4
    /* 0x014 */ int repeat_max;                       // 0x4
    /* 0x018 */ int repeat_num;                       // 0x4
    /* 0x01C */ int demonstration_flag;               // 0x4
    /* 0x020 */ int demonstration_alpha;              // 0x4
    /* 0x024 */ int obi_wipe_mode;                    // 0x4
    /* 0x028 */ int obi_wipe_speed;                   // 0x4
    /* 0x02C */ int pass_flag;                        // 0x4
    /* 0x030 */ int force_exit_flag;                  // 0x4
    /* 0x034 */ int closing_count;                    // 0x4
    /* 0x038 */ int end_count;                        // 0x4
    /* 0x03C */ int s_counter;                        // 0x4
    /* 0x040 */ int p_counter;                        // 0x4
    /* 0x044 */ int p_flag;                           // 0x4
    /* 0x048 */ int status_disp_flag;                 // 0x4
    /* 0x04C */ int hbota_step;                       // 0x4
    /* 0x050 */ int hbota_bright;                     // 0x4
};

/* variables (16) */
static struct @anon5 sect_win;                                   /* not allocated size 0x8 */
static struct @anon5 msg_win;                                    /* not allocated size 0x8 */
static struct @anon5 msg_rect;                                   /* @0x002A2138 size 0x8 */
static short foot_panel_pos_tbl[4][6];                           /* @0x0027ED60 size 0x30 */
_tag_cLesPlay *pLesPlay;                                         /* @0x002A2134 size 0x4 */
_tag_cLes *pLes;                                                 /* @0x002A2128 size 0x4 */
struct @anon12 kn_foot_w[2];                                     /* @0x006B2530 size 0x80 */
struct @anon12 kn_touch_w[2];                                    /* @0x006B0230 size 0x80 */
struct @anon0 kn_fin_w;                                          /* @0x006B0210 size 0x20 */
short font_anime_pos_y;                                          /* @0x002A2A98 size 0x2 */
short font_anime_pos_x;                                          /* @0x002A2A9C size 0x2 */
short kn_msg_num;                                                /* @0x002A2A90 size 0x2 */
unsigned int cur_font_pos;                                       /* @0x002A2A94 size 0x4 */
unsigned char *LesStrDataTbl[];                                  /* @0x0027F260 */
struct @anon4 kn_msg_w;                                          /* @0x002A2A88 size 0x8 */
struct @anon2 kn_lesson_main_work;                               /* @0x006B25B0 size 0x88 */

/* functions defined (14) */
void kn_ldisp_start_exit(void);                                  /* 0x00223610-0x002236B0 lines 971-1023 */
void kn_ldisp_back(unsigned int col, int flg);                   /* 0x002236B0-0x00223770 lines 950-966 */
void kn_ldisp_foot_stage(void);                                  /* 0x00223770-0x002239BC lines 897-945 */
void kn_ldisp_foot_touch(void);                                  /* 0x002239C0-0x00223BEC lines 835-888 */
static void kn_set_ft4_gte(struct @anon1 *disp);                 /* 0x00223BF0-0x00224020 lines 621-752 */
void kn_ldisp_face_obj(void);                                    /* 0x00224020-0x002241B8 lines 580-613 */
void kn_ldisp_foot_obj(void);                                    /* 0x002241C0-0x002245B0 lines 509-572 */
void kn_ldisp_now_teach(void);                                   /* 0x002245B0-0x00224784 lines 454-498 */
void kn_ldisp_play_msg_win(int _bright, int _alpha, int _ot);    /* 0x00224790-0x00224838 lines 362-445 */
void kn_ldisp_kanji_font_init(void);                             /* 0x00224840-0x00224854 lines 350-351 */
void kn_ldisp_reset_font_emi(void);                              /* 0x00224860-0x00224868 lines 343-343 */
void kn_ldisp_message(int flg, int _bright, int _ot);            /* 0x00224870-0x00224A0C lines 280-335 */
static int kn_kanji_font_emi(struct @anon8 *font);               /* 0x00224A10-0x00224BD0 lines 164-240 */
void kn_ldisp_lesson_play(void);                                 /* 0x00224BD0-0x00224E14 lines 116-149 */
