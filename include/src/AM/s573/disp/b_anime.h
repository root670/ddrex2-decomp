/*
 * C:\work2\usaex2\src\AM\s573\disp\b_anime.c
 * MW MIPS C Compiler, overlay main; 17 functions, code 0x001C4770-0x001C5B3C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_disp_b_anime_c_H
#define DDR_UNIT_src_AM_s573_disp_b_anime_c_H

#include "types/G_SYS_W_.h"
#include "types/anime_db.h"
#include "types/anime_obj_work.h"
#include "types/g_game_w.h"
#include "types/marker_anime_db.h"
#include "types/tex_bind.h"

/* anonymous types (11) */

/* anon_0_10 -- @anon0, 0x14 bytes, b_anime.c (DIE 0x1350F) */
struct anon_0_10 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_1_10 -- @anon1, 0x8 bytes, b_anime.c (DIE 0x13671) */
struct anon_1_10 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_2_10 -- @anon2, 0x48 bytes, b_anime.c (DIE 0x1372C) */
struct anon_2_10 {   // size 0x48
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

/* anon_5_10 -- @anon5, 0x4 bytes, b_anime.c (DIE 0x14A97) */
union anon_5_10 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_10 -- @anon3, 0x24 bytes, b_anime.c (DIE 0x14651) */
struct anon_3_10 {   // size 0x24
    /* 0x000 */ union anon_5_10 x0;                   // 0x4
    /* 0x004 */ union anon_5_10 y0;                   // 0x4
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

/* anon_4_10 -- @anon4, 0x18 bytes, b_anime.c (DIE 0x14877) */
struct anon_4_10 {   // size 0x18
    /* 0x000 */ unsigned long freeze_bit[2];          // 0x10
    /* 0x010 */ unsigned long onoff;                  // 0x8
};

/* anon_6_10 -- @anon6, 0x10 bytes, b_anime.c (DIE 0x14BF2) */
struct anon_6_10 {   // size 0x10
    /* 0x000 */ union anon_5_10 x0;                   // 0x4
    /* 0x004 */ union anon_5_10 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_7_10 -- @anon7, 0x10 bytes, b_anime.c (DIE 0x14DCF) */
struct anon_7_10 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float scale;                          // 0x4
    /* 0x00C */ float pad;                            // 0x4
};

/* anon_8_10 -- @anon8, 0x68 bytes, b_anime.c (DIE 0x14FDE) */
struct anon_8_10 {   // size 0x68
    /* 0x000 */ union anon_5_10 x0;                   // 0x4
    /* 0x004 */ union anon_5_10 y0;                   // 0x4
    /* 0x008 */ union anon_5_10 x1;                   // 0x4
    /* 0x00C */ union anon_5_10 y1;                   // 0x4
    /* 0x010 */ union anon_5_10 x2;                   // 0x4
    /* 0x014 */ union anon_5_10 y2;                   // 0x4
    /* 0x018 */ union anon_5_10 x3;                   // 0x4
    /* 0x01C */ union anon_5_10 y3;                   // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
};

/* anon_9_10 -- @anon9, 0x4 bytes, b_anime.c (DIE 0x1571C) */
struct anon_9_10 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_10_10 -- @anon10, 0x184 bytes, b_anime.c (DIE 0x15C04) */
struct anon_10_10 {   // size 0x184
    /* 0x000 */ struct anon_6_10 line_a[8];           // 0x80
    /* 0x080 */ struct anon_6_10 line_b[8];           // 0x80
    /* 0x100 */ struct anon_6_10 line_c[8];           // 0x80
    /* 0x180 */ int num;                              // 0x4
};


/* variables (13) */
char *back_anime_tanfile[19];                                    /* @0x002B33E0 size 0x4C */
static struct anime_obj_work *bap;                               /* @0x002DD948 size 0x4 */
static int marker_anime_tex_tab[7];                              /* @0x002D0A60 size 0x1C */
static int marker_anime_posx_tab[8];                             /* @0x002D0A80 size 0x20 */
static int marker_anime_posy_tab[8];                             /* @0x002D0AA0 size 0x20 */
static struct anon_7_10 frz_eff_info[8];                         /* @0x002D0AC0 size 0x80 */
struct anon_4_10 *few;                                           /* @0x002DE494 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct anon_4_10 frz_eff_w;                                      /* @0x0070FD30 size 0x18 */
struct marker_anime_db *map;                                     /* @0x002DE498 size 0x4 */
struct marker_anime_db marker_anime_w;                           /* @0x0070FD50 size 0x20 */
struct anime_obj_work back_anime_w;                              /* @0x0070FD70 size 0x120 */

/* functions defined (17) */
static void freeze_eff_disp(int bright);                         /* 0x001C4770-0x001C4D30 lines 835-926 */
void freeze_eff_off(void);                                       /* 0x001C4D30-0x001C4D3C lines 817-818 */
void freeze_eff_on(void);                                        /* 0x001C4D40-0x001C4D50 lines 813-814 */
void freeze_eff_set(int pid, int id);                            /* 0x001C4D50-0x001C4D70 lines 807-810 */
static int marker_anime_disp(int cl, int cn, int bright);        /* 0x001C4D70-0x001C5048 lines 715-770 */
void marker_anime_set_ct(int pid, int ct);                       /* 0x001C5050-0x001C5094 lines 697-698 */
void marker_anime_reset(int pid);                                /* 0x001C50A0-0x001C50C0 lines 690-693 */
void marker_anime_set(int pid, int id);                          /* 0x001C50C0-0x001C50DC lines 686-687 */
void back_anime_disp(int bright);                                /* 0x001C50E0-0x001C56D0 lines 374-580 */
void back_anime_finish(void);                                    /* 0x001C56D0-0x001C56D8 lines 336-336 */
void back_anime_step(void);                                      /* 0x001C56E0-0x001C57B4 lines 308-331 */
void back_anime_init(void);                                      /* 0x001C57C0-0x001C5924 lines 261-305 */
void back_anime_set_inst_mode(void);                             /* 0x001C5930-0x001C5940 lines 248-249 */
void back_anime_set_normal_anime(int id);                        /* 0x001C5940-0x001C5970 lines 242-244 */
void back_anime_set_anime(int id, int anime_id, int anime_ct);   /* 0x001C5970-0x001C59F4 lines 212-232 */
static void back_anime_init_can(int id);                         /* 0x001C5A00-0x001C5A70 lines 175-209 */
static int down_load_anime(int id, void *address);               /* 0x001C5A70-0x001C5B3C lines 130-171 */

#endif /* DDR_UNIT_src_AM_s573_disp_b_anime_c_H */
