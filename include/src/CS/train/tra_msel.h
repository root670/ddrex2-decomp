/*
 * C:\work2\usaex2\src\CS\train\tra_msel.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00277E40-0x00278C1C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_CS_train_tra_msel_c_H
#define DDR_UNIT_src_CS_train_tra_msel_c_H

#include "types/g_game_w.h"

/* anonymous types (12) */

/* anon_1_155 -- @anon1, 0x8 bytes, tra_msel.c (DIE 0x2BA40C) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_1_155;

/* anon_4_155 -- @anon4, 0x90 bytes, tra_msel.c (DIE 0x2BAD34) */
typedef struct {   // size 0x90
    /* 0x000 */ void *loadaddr;                       // 0x4
    /* 0x004 */ int doll_p_counter;                   // 0x4
    /* 0x008 */ unsigned char max;                    // 0x1
    /* 0x009 */ unsigned char fpanel_max;             // 0x1
    /* 0x00A */ unsigned char step;                   // 0x1
    /* 0x00B */ unsigned char dancing;                // 0x1
    /* 0x00C */ unsigned char cur[2];                 // 0x2
    /* 0x00E */ // 0x2 bytes padding
    /* 0x010 */ float fpanel_x[2];                    // 0x8
    /* 0x018 */ float fpanel_y[2];                    // 0x8
    /* 0x020 */ float cx[3];                          // 0xC
    /* 0x02C */ float cy[3];                          // 0xC
    /* 0x038 */ float cz[3];                          // 0xC
    /* 0x044 */ float adj_y[3];                       // 0xC
    /* 0x050 */ float timer;                          // 0x4
    /* 0x054 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x060 */ float cam_p[4];                       // 0x10
    /* 0x070 */ float eye_p[4];                       // 0x10
    /* 0x080 */ void *fpanel;                         // 0x4
    /* 0x084 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
} anon_4_155;

/* anon_15_155 -- @anon15, 0xC bytes, tra_msel.c (DIE 0x2BDB0E) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_15_155;

/* anon_9_155 -- @anon9, 0xC bytes, tra_msel.c (DIE 0x2BCD61) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_9_155;

/* anon_14_155 -- @anon14, 0x1C bytes, tra_msel.c (DIE 0x2BD840) */
typedef struct {   // size 0x1C
    /* 0x000 */ unsigned char end_num;                // 0x1
    /* 0x001 */ unsigned char decide;                 // 0x1
    /* 0x002 */ unsigned char cancel;                 // 0x1
    /* 0x003 */ unsigned char cur[2];                 // 0x2
    /* 0x005 */ unsigned char rand_id[2];             // 0x2
    /* 0x007 */ // 0x1 bytes padding
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ int timer;                            // 0x4
    /* 0x014 */ void *item;                           // 0x4
    /* 0x018 */ void *entry;                          // 0x4
} anon_14_155;

/* anon_6_155 -- @anon6, 0x494 bytes, tra_msel.c (DIE 0x2BB870) */
typedef struct {   // size 0x494
    /* 0x000 */ float ftimer;                         // 0x4
    /* 0x004 */ float repcnt;                         // 0x4
    /* 0x008 */ float scr_sp;                         // 0x4
    /* 0x00C */ float scr_ct;                         // 0x4
    /* 0x010 */ unsigned int lr_obj_id;               // 0x4
    /* 0x014 */ void *lr;                             // 0x4
    /* 0x018 */ void *ud;                             // 0x4
    /* 0x01C */ void *radar;                          // 0x4
    /* 0x020 */ void *entry;                          // 0x4
    /* 0x024 */ void *base;                           // 0x4
    /* 0x028 */ void *sort_obj;                       // 0x4
    /* 0x02C */ void *scr;                            // 0x4
    /* 0x030 */ void *opt;                            // 0x4
    /* 0x034 */ void *edmc;                           // 0x4
    /* 0x038 */ unsigned char *th_up_addr;            // 0x4
    /* 0x03C */ unsigned char *th_dw_addr;            // 0x4
    /* 0x040 */ unsigned char ud_start;               // 0x1
    /* 0x041 */ unsigned char ud_end;                 // 0x1
    /* 0x042 */ unsigned char cur_ud[2];              // 0x2
    /* 0x044 */ unsigned char cur_ud_old[2];          // 0x2
    /* 0x046 */ unsigned char cur_ud_edi_old[2];      // 0x2
    /* 0x048 */ short cur_lr;                         // 0x2
    /* 0x04A */ short old_d_num;                      // 0x2
    /* 0x04C */ short old_lr;                         // 0x2
    /* 0x04E */ short ena_num;                        // 0x2
    /* 0x050 */ short sel_tab[128];                   // 0x100
    /* 0x150 */ short base_num;                       // 0x2
    /* 0x152 */ short base_tab[250];                  // 0x1F4
    /* 0x346 */ short kind_key[50];                   // 0x64
    /* 0x3AA */ short kind_ofs[50];                   // 0x64
    /* 0x40E */ short kind_len[50];                   // 0x64
    /* 0x472 */ short abc_open;                       // 0x2
    /* 0x474 */ unsigned char edit_sel;               // 0x1
    /* 0x475 */ unsigned char sort;                   // 0x1
    /* 0x476 */ unsigned char step;                   // 0x1
    /* 0x477 */ unsigned char rlt_stop_mode;          // 0x1
    /* 0x478 */ unsigned char rlt_turn_num;           // 0x1
    /* 0x479 */ unsigned char rlt_remain;             // 0x1
    /* 0x47A */ // 0x2 bytes padding
    /* 0x47C */ float rlt_t;                          // 0x4
    /* 0x480 */ float rlt_wait;                       // 0x4
    /* 0x484 */ char mcard_type;                      // 0x1
    /* 0x485 */ char msg_id;                          // 0x1
    /* 0x486 */ char yesno;                           // 0x1
    /* 0x487 */ char lib_num;                         // 0x1
    /* 0x488 */ char lib_sel_num;                     // 0x1
    /* 0x489 */ unsigned char lib_loaded;             // 0x1
    /* 0x48A */ short edi_start;                      // 0x2
    /* 0x48C */ unsigned char sn_f;                   // 0x1
    /* 0x48D */ // 0x3 bytes padding
    /* 0x490 */ float sn_t;                           // 0x4
} anon_6_155;

/* anon_3_155 -- @anon3, 0x70 bytes, tra_msel.c (DIE 0x2BAAFE) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_1_155 one[11];                   // 0x58
} anon_3_155;

/* anon_10_155 -- @anon10, 0x34 bytes, tra_msel.c (DIE 0x2BCE50) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_10_155;

/* anon_12_155 -- @anon12, 0xA0 bytes, tra_msel.c (DIE 0x2BD152) */
typedef struct {   // size 0xA0
    /* 0x000 */ float ftimer;                         // 0x4
    /* 0x004 */ void *base;                           // 0x4
    /* 0x008 */ void *value;                          // 0x4
    /* 0x00C */ void *point;                          // 0x4
    /* 0x010 */ void *score;                          // 0x4
    /* 0x014 */ void *btn;                            // 0x4
    /* 0x018 */ unsigned char *th_addr;               // 0x4
    /* 0x01C */ int total_pnt;                        // 0x4
    /* 0x020 */ int vo_code;                          // 0x4
    /* 0x024 */ short d_num;                          // 0x2
    /* 0x026 */ unsigned char push[2];                // 0x2
    /* 0x028 */ unsigned char edi_str[11];            // 0xB
    /* 0x033 */ unsigned char cheer;                  // 0x1
    /* 0x034 */ unsigned char vo_pid;                 // 0x1
    /* 0x035 */ // 0x3 bytes padding
    /* 0x038 */ anon_10_155 eva[2];                   // 0x68
} anon_12_155;

/* anon_2_155 -- @anon2, 0x7E0 bytes, tra_msel.c (DIE 0x2BA6BB) */
typedef struct {   // size 0x7E0
    /* 0x000 */ float wsm[4][4];                      // 0x40
    /* 0x040 */ unsigned char step;                   // 0x1
    /* 0x041 */ unsigned char step_s;                 // 0x1
    /* 0x042 */ unsigned char next_step;              // 0x1
    /* 0x043 */ unsigned char qm_step;                // 0x1
    /* 0x044 */ unsigned char pad_type;               // 0x1
    /* 0x045 */ // 0x3 bytes padding
    /* 0x048 */ float fade_ct;                        // 0x4
    /* 0x04C */ int fade_kind;                        // 0x4
    /* 0x050 */ int tex_start;                        // 0x4
    /* 0x054 */ float quit_ct;                        // 0x4
    /* 0x058 */ unsigned char eye_step;               // 0x1
    /* 0x059 */ unsigned char fade_step;              // 0x1
    /* 0x05A */ unsigned char dp_alpha;               // 0x1
    /* 0x05B */ unsigned char start_pid;              // 0x1
    /* 0x05C */ unsigned char prev_step;              // 0x1
    /* 0x05D */ // 0x3 bytes padding
    /* 0x060 */ unsigned int flag;                    // 0x4
    /* 0x064 */ void *btn;                            // 0x4
    /* 0x068 */ unsigned int btn_obj_id;              // 0x4
    /* 0x06C */ unsigned char *str_addr;              // 0x4
    /* 0x070 */ unsigned char str_buf[256];           // 0x100
    /* 0x170 */ anon_4_155 doll;                      // 0x90
    /* 0x200 */ anon_15_155 eyetoy;                   // 0xC
    /* 0x20C */ anon_9_155 style;                     // 0xC
    /* 0x218 */ anon_14_155 chara;                    // 0x1C
    /* 0x234 */ anon_6_155 music;                     // 0x494
    /* 0x6C8 */ anon_3_155 option;                    // 0x70
    /* 0x738 */ anon_12_155 result;                   // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_2_155;

/* anon_8_155 -- @anon8, 0xB8 bytes, tra_msel.c (DIE 0x2BC349) */
typedef struct {   // size 0xB8
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char step_s;                 // 0x1
    /* 0x002 */ unsigned char mode;                   // 0x1
    /* 0x003 */ unsigned char next_mode;              // 0x1
    /* 0x004 */ unsigned char sub_win_alpha;          // 0x1
    /* 0x005 */ unsigned char cur;                    // 0x1
    /* 0x006 */ unsigned char old_cur;                // 0x1
    /* 0x007 */ unsigned char opt_cur;                // 0x1
    /* 0x008 */ unsigned char asi_cur;                // 0x1
    /* 0x009 */ unsigned char co_win_suu;             // 0x1
    /* 0x00A */ // 0x6 bytes padding
    /* 0x010 */ unsigned long arrow_clut_ct;          // 0x8
    /* 0x018 */ unsigned int flag;                    // 0x4
    /* 0x01C */ int repcnt;                           // 0x4
    /* 0x020 */ float ftimer;                         // 0x4
    /* 0x024 */ short music_num;                      // 0x2
    /* 0x026 */ short old_music_num;                  // 0x2
    /* 0x028 */ unsigned char player;                 // 0x1
    /* 0x029 */ unsigned char level;                  // 0x1
    /* 0x02A */ unsigned char mspeed;                 // 0x1
    /* 0x02B */ unsigned char edit_data_on;           // 0x1
    /* 0x02C */ unsigned char clap;                   // 0x1
    /* 0x02D */ unsigned char metro;                  // 0x1
    /* 0x02E */ unsigned char track;                  // 0x1
    /* 0x02F */ unsigned char arrow_speed;            // 0x1
    /* 0x030 */ unsigned char boost;                  // 0x1
    /* 0x031 */ unsigned char appear;                 // 0x1
    /* 0x032 */ unsigned char turn;                   // 0x1
    /* 0x033 */ unsigned char little;                 // 0x1
    /* 0x034 */ unsigned char dark;                   // 0x1
    /* 0x035 */ unsigned char simu;                   // 0x1
    /* 0x036 */ unsigned char scroll;                 // 0x1
    /* 0x037 */ unsigned char freeze;                 // 0x1
    /* 0x038 */ unsigned char real_turn;              // 0x1
    /* 0x039 */ unsigned char c_bar_max;              // 0x1
    /* 0x03A */ unsigned char c_bar_adjust;           // 0x1
    /* 0x03B */ unsigned char bar_start;              // 0x1
    /* 0x03C */ unsigned char bar_end;                // 0x1
    /* 0x03D */ unsigned char bar_max;                // 0x1
    /* 0x03E */ unsigned char adjust_bar;             // 0x1
    /* 0x03F */ unsigned char cur_bar_w;              // 0x1
    /* 0x040 */ unsigned char special_bar;            // 0x1
    /* 0x041 */ // 0x1 bytes padding
    /* 0x042 */ short scroll_ct;                      // 0x2
    /* 0x044 */ unsigned char scroll_spd;             // 0x1
    /* 0x045 */ unsigned char start_side;             // 0x1
    /* 0x046 */ unsigned char finish_flg;             // 0x1
    /* 0x047 */ unsigned char music_step;             // 0x1
    /* 0x048 */ unsigned char finish_step;            // 0x1
    /* 0x049 */ unsigned char now_play_bar;           // 0x1
    /* 0x04A */ unsigned char old_play_bar;           // 0x1
    /* 0x04B */ unsigned char cur_point_pos[2];       // 0x2
    /* 0x04D */ unsigned char play_bright;            // 0x1
    /* 0x04E */ short obi_deg;                        // 0x2
    /* 0x050 */ short cur_clap_pos[2];                // 0x4
    /* 0x054 */ short cur_metro_pos;                  // 0x2
    /* 0x056 */ // 0x2 bytes padding
    /* 0x058 */ int now_music_data;                   // 0x4
    /* 0x05C */ int check_music_ct;                   // 0x4
    /* 0x060 */ unsigned long push_cont_timer;        // 0x8
    /* 0x068 */ unsigned char rs_cur;                 // 0x1
    /* 0x069 */ unsigned char ck_cur;                 // 0x1
    /* 0x06A */ unsigned char cur_chk_bar;            // 0x1
    /* 0x06B */ unsigned char check_mode_flg;         // 0x1
    /* 0x06C */ void *obj_p[10];                      // 0x28
    /* 0x094 */ void *ms_display;                     // 0x4
    /* 0x098 */ unsigned short tex_no[15];            // 0x1E
    /* 0x0B6 */ // 0x2 bytes padding
} anon_8_155;

/* anon_11_155 -- @anon11, 0x10 bytes, tra_msel.c (DIE 0x2BD001) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_11_155;


/* variables (6) */
anon_8_155 *trw;                                                 /* @0x002DDDDC size 0x4 */
anon_11_155 fp_objf[];                                           /* @0x002BBD80 */
anon_2_155 *fpw;                                                 /* @0x002DE540 size 0x4 */
anon_6_155 *msw;                                                 /* @0x002DE52C size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_11_155 fp_ms_objf[];                                        /* @0x002BEA80 */

/* functions defined (4) */
static void tr_msel_init(void);                                  /* 0x00277E40-0x0027808C lines 369-434 */
static int Tr_ms_disap(void);                                    /* 0x00278090-0x00278364 lines 285-364 */
static int Tr_ms_apper(void);                                    /* 0x00278370-0x00278670 lines 187-281 */
unsigned char Train_Msel(void);                                  /* 0x00278670-0x00278C1C lines 37-178 */

#endif /* DDR_UNIT_src_CS_train_tra_msel_c_H */
