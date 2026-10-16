/*
 * C:\work2\usaex2\src\CS\train\tra_chk.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x00283820-0x002853D4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_train_tra_chk_c_H
#define DDR_UNIT_src_CS_train_tra_chk_c_H

/* anonymous types (9) */

/* anon_0_164 -- @anon0, 0x10 bytes, tra_chk.c (DIE 0x2F2301) */
struct anon_0_164 {   // size 0x10
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ float btn_cx;                         // 0x4
    /* 0x008 */ int ex;                               // 0x4
    /* 0x00C */ float ex_x;                           // 0x4
};

/* anon_1_164 -- @anon1, 0x48 bytes, tra_chk.c (DIE 0x2F23A3) */
struct anon_1_164 {   // size 0x48
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
};

/* anon_3_164 -- @anon3, 0xC bytes, tra_chk.c (DIE 0x2F2779) */
struct anon_3_164 {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float dx;                             // 0x4
};

/* anon_2_164 -- @anon2, 0x94 bytes, tra_chk.c (DIE 0x2F2625) */
struct anon_2_164 {   // size 0x94
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ float alpha;                          // 0x4
    /* 0x008 */ float t;                              // 0x4
    /* 0x00C */ float dx;                             // 0x4
    /* 0x010 */ float fra_h;                          // 0x4
    /* 0x014 */ float center_len;                     // 0x4
    /* 0x018 */ float bri_t;                          // 0x4
    /* 0x01C */ struct anon_3_164 one_jd[6];          // 0x48
    /* 0x064 */ struct anon_3_164 one_tm[4];          // 0x30
};

/* anon_6_164 -- @anon6, 0x4 bytes, tra_chk.c (DIE 0x2F2B74) */
union anon_6_164 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_4_164 -- @anon4, 0x1C bytes, tra_chk.c (DIE 0x2F27F6) */
struct anon_4_164 {   // size 0x1C
    /* 0x000 */ union anon_6_164 x0;                  // 0x4
    /* 0x004 */ union anon_6_164 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_5_164 -- @anon5, 0x24 bytes, tra_chk.c (DIE 0x2F29BC) */
struct anon_5_164 {   // size 0x24
    /* 0x000 */ union anon_6_164 x0;                  // 0x4
    /* 0x004 */ union anon_6_164 y0;                  // 0x4
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
};

/* anon_7_164 -- @anon7, 0x30 bytes, tra_chk.c (DIE 0x2F2BD1) */
struct anon_7_164 {   // size 0x30
    /* 0x000 */ union anon_6_164 x0;                  // 0x4
    /* 0x004 */ union anon_6_164 y0;                  // 0x4
    /* 0x008 */ union anon_6_164 x1;                  // 0x4
    /* 0x00C */ union anon_6_164 y1;                  // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
};

/* anon_8_164 -- @anon8, 0xB8 bytes, tra_chk.c (DIE 0x2F2E11) */
struct anon_8_164 {   // size 0xB8
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
};


/* variables (6) */
static float ck_jd_pos[6][2];                                    /* @0x002C0F20 size 0x30 */
static float ck_tm_pos[4][2];                                    /* @0x002C0F50 size 0x20 */
static struct anon_0_164 tr_btn_ck[2];                           /* @0x002C0F70 size 0x20 */
struct anon_8_164 *trw;                                          /* @0x002DDDDC size 0x4 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (8) */
static int tr_ck_item_one_move(struct anon_3_164 *one, unsigned char mode); /* 0x00283820-0x002839D8 lines 701-739 */
static void tr_ck_pad(void);                                     /* 0x002839E0-0x00283C1C lines 640-694 */
static int tr_ck_apper(void);                                    /* 0x00283C20-0x00283D30 lines 585-617 */
int TRObj_ck_item_disp(void *wp);                                /* 0x00283D30-0x00284688 lines 404-566 */
int TRObj_ck_item_disap(void *wp);                               /* 0x00284690-0x002849C8 lines 355-401 */
int TRObj_ck_item_exec(void *wp);                                /* 0x002849D0-0x00284E64 lines 222-352 */
int TRObj_ck_item_apper(void *wp);                               /* 0x00284E70-0x00285080 lines 165-219 */
unsigned char Train_Chk(void);                                   /* 0x00285080-0x002853D4 lines 64-151 */

#endif /* DDR_UNIT_src_CS_train_tra_chk_c_H */
