/*
 * C:\work2\usaex2\src\CS\records\rec_main.c
 * MW MIPS C Compiler, overlay rec_rel4cd.prg; 14 functions, code 0x007F0080-0x007F0F60
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_rec_main_c_H
#define DDR_UNIT_src_CS_records_rec_main_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cFilepackData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"

/* anonymous types (9) */

/* anon_6_242 -- @anon6, 0x8 bytes, rec_main.c (DIE 0x470FA4) */
struct anon_6_242 {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

/* anon_2_242 -- @anon2, 0xC bytes, rec_main.c (DIE 0x470082) */
struct anon_2_242 {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
};

/* anon_0_242 -- @anon0, 0x504 bytes, rec_main.c (DIE 0x46F472) */
struct anon_0_242 {   // size 0x504
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
    /* 0x010 */ float disap_timer;                    // 0x4
    /* 0x014 */ unsigned int str_addr;                // 0x4
    /* 0x018 */ float win_y;                          // 0x4
    /* 0x01C */ int idx;                              // 0x4
    /* 0x020 */ int repcnt;                           // 0x4
    /* 0x024 */ void *record_ad;                      // 0x4
    /* 0x028 */ int m_num;                            // 0x4
    /* 0x02C */ float star_t;                         // 0x4
    /* 0x030 */ float scr_y;                          // 0x4
    /* 0x034 */ struct anon_6_242 title_info[80];     // 0x280
    /* 0x2B4 */ struct anon_2_242 xmove[40];          // 0x1E0
    /* 0x494 */ float scr_t;                          // 0x4
    /* 0x498 */ unsigned char er_step;                // 0x1
    /* 0x499 */ unsigned char yn_cur;                 // 0x1
    /* 0x49A */ unsigned char del_alpha;              // 0x1
    /* 0x49B */ // 0x1 bytes padding
    /* 0x49C */ short tex_start;                      // 0x2
    /* 0x49E */ // 0x2 bytes padding
    /* 0x4A0 */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x4AC */ void *obj_p[22];                      // 0x58
};

/* anon_1_242 -- @anon1, 0x14 bytes, rec_main.c (DIE 0x46F8C0) */
struct anon_1_242 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_3_242 -- @anon3, 0x4 bytes, rec_main.c (DIE 0x470B43) */
union anon_3_242 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_4_242 -- @anon4, 0x10 bytes, rec_main.c (DIE 0x470C7F) */
struct anon_4_242 {   // size 0x10
    /* 0x000 */ union anon_3_242 x0;                  // 0x4
    /* 0x004 */ union anon_3_242 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_5_242 -- @anon5, 0x10 bytes, rec_main.c (DIE 0x470D9F) */
struct anon_5_242 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};

/* anon_7_242 -- @anon7, 0x4 bytes, rec_main.c (DIE 0x471451) */
struct anon_7_242 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_8_242 -- @anon8, 0x184 bytes, rec_main.c (DIE 0x471631) */
struct anon_8_242 {   // size 0x184
    /* 0x000 */ struct anon_4_242 line_a[8];          // 0x80
    /* 0x080 */ struct anon_4_242 line_b[8];          // 0x80
    /* 0x100 */ struct anon_4_242 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};


/* variables (6) */
struct anon_0_242 *rw;                                           /* @0x002DDFB4 size 0x4 */
static unsigned char (*rec_exec_func[9])(struct anon_0_242 *);   /* @0x007FBC80 size 0x24 */
static struct anon_5_242 rec_obj_f[22];                          /* @0x007FBCB0 size 0x160 */
unsigned char rec_obj_pri[22];                                   /* @0x007FBE10 size 0x16 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct anon_0_242 rec_w;                                         /* @0x007FC400 size 0x504 */

/* functions referenced (2) */
void trans_title_th(void *);                                     /* @0x007F0080 */
void DecodeFilepackData_Th(void *);                              /* @0x0016DC50 */

/* functions defined (14) */
static void trans_title_th(void);                                /* 0x007F0080-0x007F0190 lines 747-793 */
static int rec_tex_init(struct anon_0_242 *rw);                  /* 0x007F0190-0x007F0348 lines 672-739 */
static void rec_xmove_update(struct anon_0_242 *rw);             /* 0x007F0350-0x007F05D4 lines 615-667 */
void Rec_XMoveSet(struct anon_2_242 *mw, float wait, unsigned char mode); /* 0x007F05E0-0x007F0610 lines 601-610 */
void rec_obj_disap(int obj_no);                                  /* 0x007F0610-0x007F0658 lines 572-577 */
void rec_obj_set(int obj_no);                                    /* 0x007F0660-0x007F06E0 lines 562-569 */
void Rec_FontPuts20(short x, short lim_x, short y, unsigned char *str, unsigned char alpha); /* 0x007F06E0-0x007F0828 lines 493-527 */
unsigned char *Rec_OutStrGet(int id);                            /* 0x007F0830-0x007F084C lines 445-452 */
unsigned int Rec_PadScroll(unsigned int key);                    /* 0x007F0850-0x007F08FC lines 421-439 */
unsigned int Rec_PadRepeat(unsigned int key);                    /* 0x007F0900-0x007F094C lines 415-417 */
unsigned int Rec_PadTrg(unsigned int key);                       /* 0x007F0950-0x007F099C lines 408-410 */
void Term_Reco(void);                                            /* 0x007F09A0-0x007F09A8 lines 391-391 */
int Step_Reco(void);                                             /* 0x007F09B0-0x007F0EE0 lines 285-387 */
void Init_Reco(void);                                            /* 0x007F0EE0-0x007F0F60 lines 252-283 */

#endif /* DDR_UNIT_src_CS_records_rec_main_c_H */
