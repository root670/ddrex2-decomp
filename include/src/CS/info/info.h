/*
 * C:\work2\usaex2\src\CS\info\info.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 45 functions, code 0x007F1BB0-0x007F4D84
 * functions come from: myroom_main.c (31), info.c (14)
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
#ifndef DDR_UNIT_src_CS_info_info_c_H
#define DDR_UNIT_src_CS_info_info_c_H

#include "types/CO_OBJ_W.h"
#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_CWS_WIN_W.h"
#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cIdm5DataHeader.h"
#include "types/_tag_cIdm5FileHeader.h"
#include "types/_tag_cInfo.h"
#include "types/_tag_cInfoText.h"
#include "types/_tag_cInfoshow.h"
#include "types/_tag_cModeData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"
#include "types/tex_bind.h"

/* anonymous types (10) */

/* anon_0_183 -- @anon0, 0x10 bytes, info.c (DIE 0x331BA1) */
typedef struct {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
} anon_0_183;

/* anon_2_183 -- @anon2, 0x18 bytes, info.c (DIE 0x331FC9) */
typedef struct {   // size 0x18
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ float btn_cx;                         // 0x4
    /* 0x008 */ float btn_cy;                         // 0x4
    /* 0x00C */ int ex;                               // 0x4
    /* 0x010 */ float ex_x;                           // 0x4
    /* 0x014 */ float ex_cy;                          // 0x4
} anon_2_183;

/* anon_1_183 -- @anon1, 0x18 bytes, info.c (DIE 0x331D24) */
typedef struct {   // size 0x18
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ float dx;                             // 0x4
    /* 0x008 */ float dy;                             // 0x4
    /* 0x00C */ float t;                              // 0x4
    /* 0x010 */ anon_2_183 *info[2];                  // 0x8
} anon_1_183;

/* anon_3_183 -- @anon3, 0x1C bytes, info.c (DIE 0x3326DB) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_3_183;

/* anon_4_183 -- @anon4, 0x10 bytes, info.c (DIE 0x3329D1) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float sx;                             // 0x4
} anon_4_183;

/* anon_6_183 -- @anon6, 0x24 bytes, info.c (DIE 0x33348A) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01C */ unsigned char r0;                     // 0x1
    /* 0x01D */ unsigned char g0;                     // 0x1
    /* 0x01E */ unsigned char b0;                     // 0x1
    /* 0x01F */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
} anon_6_183;

/* anon_12_183 -- @anon12, 0x4 bytes, info.c (DIE 0x33506B) */
typedef struct {   // size 0x4
    /* 0x000 */ struct _CWS_WIN_W *win;               // 0x4
} anon_12_183;

/* anon_14_183 -- @anon14, 0x2F0 bytes, info.c (DIE 0x335C2E) */
typedef struct {   // size 0x2F0
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char step_s;                 // 0x1
    /* 0x002 */ unsigned char mode;                   // 0x1
    /* 0x003 */ unsigned char flag;                   // 0x1
    /* 0x004 */ unsigned char top_cur;                // 0x1
    /* 0x005 */ unsigned char top_old_cur;            // 0x1
    /* 0x006 */ unsigned char cur_x;                  // 0x1
    /* 0x007 */ unsigned char cur_y;                  // 0x1
    /* 0x008 */ float timer;                          // 0x4
    /* 0x00C */ float timer2;                         // 0x4
    /* 0x010 */ unsigned int str_addr;                // 0x4
    /* 0x014 */ float win_y;                          // 0x4
    /* 0x018 */ int idx;                              // 0x4
    /* 0x01C */ int repcnt;                           // 0x4
    /* 0x020 */ void *record_ad;                      // 0x4
    /* 0x024 */ int m_num;                            // 0x4
    /* 0x028 */ float star_t;                         // 0x4
    /* 0x02C */ float scr_y;                          // 0x4
    /* 0x030 */ anon_4_183 xmove[40];                 // 0x280
    /* 0x2B0 */ float scr_t;                          // 0x4
    /* 0x2B4 */ unsigned char er_step;                // 0x1
    /* 0x2B5 */ unsigned char yn_cur;                 // 0x1
    /* 0x2B6 */ unsigned char del_alpha;              // 0x1
    /* 0x2B7 */ // 0x1 bytes padding
    /* 0x2B8 */ short tex_start;                      // 0x2
    /* 0x2BA */ // 0x2 bytes padding
    /* 0x2BC */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x2C8 */ void *obj_p[10];                      // 0x28
} anon_14_183;

/* anon_25_183 -- @anon25, 0x34 bytes, info.c (DIE 0x33AE9A) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
    /* 0x010 */ anon_d075beaabcd0 x2;                 // 0x4
    /* 0x014 */ anon_d075beaabcd0 y2;                 // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
} anon_25_183;

/* anon_26_183 -- @anon26, 0x48 bytes, info.c (DIE 0x33B492) */
typedef struct {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02C */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03A */ unsigned short tw;                    // 0x2
    /* 0x03C */ unsigned short th;                    // 0x2
    /* 0x03E */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
} anon_26_183;


/* variables (19) */
struct _tag_cInfo *pInfo;                                        /* @0x002DDE54 size 0x4 */
static struct _tag_cModeData ModeData[4];                        /* @0x00800080 size 0x50 */
anon_14_183 *roomw;                                              /* @0x002DDE58 size 0x4 */
static int (*myroom_exec_func[5])(anon_14_183 *);                /* @0x008000D0 size 0x14 */
static anon_1fa6d74458f3 myroom_obj_f[10];                       /* @0x008000F0 size 0xA0 */
unsigned char myroom_obj_pri[10];                                /* @0x00800190 size 0xA */
unsigned char *myroom_title_str[7];                              /* @0x008001A0 size 0x1C */
unsigned char *myroom_menu_str[7];                               /* @0x008001C0 size 0x1C */
static anon_2_183 myroom_btn_info[4];                            /* @0x008001E0 size 0x60 */
struct tex_bind tex_bind[375];                                   /* @0x0058C390 size 0x2904 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cInfoshow *pInfoshow;                                /* @0x002DDE6C size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
int tblInfoOrder[];                                              /* @0x002B72C0 */
int tblInfoOrder_for_course[];                                   /* @0x002B7470 */
int tblInfoOrder_for_music[];                                    /* @0x002B7340 */
struct CO_OBJ_W co_obj_addr[32];                                 /* @0x00802530 size 0x5000 */
static anon_14_183 myroom_w;                                     /* @0x00802240 size 0x2F0 */
static struct _tag_cInfo _pInfo;                                 /* @0x00807530 size 0x370 */

/* functions referenced (1) */
void DecodeFilepackDataEx_Th(void *);                            /* @0x0016DB60 */

/* functions defined (45) */

/* myroom_main.c */
void MyRoom_Board_Disp(anon_b14b78a0b5d3 r, int pri_add, unsigned char flag); /* 0x007F1BB0-0x007F1DF8 lines 1703-1738 */
static int MyRoom_btn_disp(void *w);                             /* 0x007F1E00-0x007F1F60 lines 1661-1693 */
static int MyRoom_btn_move(void *w);                             /* 0x007F1F60-0x007F2058 lines 1628-1659 */
int MyRoom_scr_bar_disp(void *wp);                               /* 0x007F2060-0x007F2100 lines 1515-1576 */
int MyRoom_scr_bar_disap(void *wp);                              /* 0x007F2100-0x007F2154 lines 1504-1512 */
int MyRoom_scr_bar_apper(void *wp);                              /* 0x007F2160-0x007F21BC lines 1493-1501 */
int MyRoom_caption_disap(void *wp);                              /* 0x007F21C0-0x007F2268 lines 1468-1487 */
int MyRoom_caption_apper(void *wp);                              /* 0x007F2270-0x007F2308 lines 1451-1465 */
int MyRoom_back_disp(void);                                      /* 0x007F2310-0x007F2390 lines 1432-1445 */
int MyRoom_back_disap(void *wp);                                 /* 0x007F2390-0x007F240C lines 1417-1430 */
int MyRoom_back_apper(void *wp);                                 /* 0x007F2410-0x007F2480 lines 1404-1414 */
int MyRoom_base_disp(void);                                      /* 0x007F2480-0x007F250C lines 1381-1397 */
int MyRoom_base_disap(void *wp);                                 /* 0x007F2510-0x007F2604 lines 1356-1379 */
int MyRoom_base_apper(void *wp);                                 /* 0x007F2610-0x007F2690 lines 1341-1353 */
int MyRoom_top_item_disp(void);                                  /* 0x007F2690-0x007F2770 lines 1313-1334 */
int MyRoom_top_item_disap(void *wp);                             /* 0x007F2770-0x007F28A4 lines 1276-1310 */
int MyRoom_top_item_exec(void *wp);                              /* 0x007F28B0-0x007F28F8 lines 1269-1273 */
int MyRoom_top_item_apper(void *wp);                             /* 0x007F2900-0x007F2A94 lines 1225-1263 */
int MyRoom_cur_disp(void);                                       /* 0x007F2AA0-0x007F2AA8 lines 1222-1222 */
int MyRoom_cur_exec(void *wp);                                   /* 0x007F2AB0-0x007F2AFC lines 1119-1142 */
int MyRoom_win_disp(void);                                       /* 0x007F2B00-0x007F2B20 lines 1108-1113 */
int MyRoom_win_func(void *w);                                    /* 0x007F2B20-0x007F2CF8 lines 1062-1106 */
int MyRoom_fade(anon_0_183 *w, float time, int kind);            /* 0x007F2D00-0x007F2E08 lines 1015-1033 */
void myroom_xmove_update(void);                                  /* 0x007F2E10-0x007F304C lines 521-571 */
int Update_MyRoom(void);                                         /* 0x007F3050-0x007F3058 lines 516-516 */
int View_MyRoom(void);                                           /* 0x007F3060-0x007F3068 lines 513-513 */
int Control_MyRoom(void);                                        /* 0x007F3070-0x007F30FC lines 498-510 */
int Init_MyRoom(void);                                           /* 0x007F3100-0x007F3258 lines 487-496 */
int MyRoom_Extra_Arrow_OR_Ending_List(void);                     /* 0x007F3260-0x007F34E4 lines 239-311 */
int MyRoom_Credits(void);                                        /* 0x007F34F0-0x007F388C lines 160-231 */
int MyRoom_Top(void);                                            /* 0x007F3890-0x007F3E28 lines 42-152 */

/* info.c */
void CheckInfo_Info(int serial, int *exist, int *anew);          /* 0x007F3E30-0x007F3F20 lines 1134-1162 */
void DrawScrollBar_Info(void);                                   /* 0x007F3F20-0x007F3F54 lines 1043-1120 */
static void decode_text_idm5_th(void);                           /* 0x007F3F60-0x007F4020 lines 1001-1037 */
void set_select_track_no_by_infotxt_num(int infotxt_num);        /* 0x007F4020-0x007F4094 lines 956-969 */
static void sound_poll(void);                                    /* 0x007F40A0-0x007F4174 lines 892-949 */
void DivideInfoDataIdm5_Info(struct _tag_cIdm5DataHeader *src, int nl, unsigned char *str, unsigned char *col); /* 0x007F4180-0x007F421C lines 857-885 */
static void information_check(void);                             /* 0x007F4220-0x007F43D4 lines 745-847 */
static int init_tex(void);                                       /* 0x007F43E0-0x007F4524 lines 569-629 */
static void open_func(void);                                     /* 0x007F4530-0x007F4674 lines 344-385 */
static void init_func(void);                                     /* 0x007F4680-0x007F49E0 lines 249-340 */
void Term_Info(void);                                            /* 0x007F49E0-0x007F49E8 lines 239-239 */
int Step_Info(void);                                             /* 0x007F49F0-0x007F4CB0 lines 188-233 */
void Init_Info(void);                                            /* 0x007F4CB0-0x007F4D5C lines 143-183 */
void SetStep_Info(int _step, int _next_mode);                    /* 0x007F4D60-0x007F4D84 lines 118-123 */

#endif /* DDR_UNIT_src_CS_info_info_c_H */
