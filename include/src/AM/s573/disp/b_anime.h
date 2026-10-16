/*
 * C:\work\usam2\src\AM\s573\disp\b_anime.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x002442e0-0x0024510c
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_disp_b_anime_c_H
#define DDR_UNIT_src_AM_s573_disp_b_anime_c_H

#include "types/anime_db.h"
#include "types/anime_obj_work.h"
#include "types/g_game_w.h"
#include "types/marker_anime_db.h"
#include "types/tex_bind.h"

/* anonymous types (6) */

/* anon_2_35 -- @anon2, 0x4 bytes, b_anime.c (DIE 0x6ff62) */
union anon_2_35 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_35 -- @anon0, 0x1c bytes, b_anime.c (DIE 0x6e71d) */
struct anon_0_35 {   // size 0x1c
    /* 0x000 */ union anon_2_35 x0;                   // 0x4
    /* 0x004 */ union anon_2_35 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00c */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_1_35 -- @anon1, 0x4 bytes, b_anime.c (DIE 0x6e875) */
struct anon_1_35 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_3_35 -- @anon3, 0x8 bytes, b_anime.c (DIE 0x6ffe3) */
struct anon_3_35 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_4_35 -- @anon4, 0x68 bytes, b_anime.c (DIE 0x7009e) */
struct anon_4_35 {   // size 0x68
    /* 0x000 */ union anon_2_35 x0;                   // 0x4
    /* 0x004 */ union anon_2_35 y0;                   // 0x4
    /* 0x008 */ union anon_2_35 x1;                   // 0x4
    /* 0x00c */ union anon_2_35 y1;                   // 0x4
    /* 0x010 */ union anon_2_35 x2;                   // 0x4
    /* 0x014 */ union anon_2_35 y2;                   // 0x4
    /* 0x018 */ union anon_2_35 x3;                   // 0x4
    /* 0x01c */ union anon_2_35 y3;                   // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02c */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03c */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04c */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05c */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
};

/* anon_5_35 -- @anon5, 0x48 bytes, b_anime.c (DIE 0x70f00) */
struct anon_5_35 {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00c */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02c */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03a */ unsigned short tw;                    // 0x2
    /* 0x03c */ unsigned short th;                    // 0x2
    /* 0x03e */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
};


/* variables (9) */
char *back_anime_tanfile[19];                                    /* @0x00288260 size 0x4c */
static struct anime_obj_work *bap;                               /* @0x002a2598 size 0x4 */
static int marker_anime_tex_tab[7];                              /* @0x0029f320 size 0x1c */
static int marker_anime_posx_tab[8];                             /* @0x0029f340 size 0x20 */
static int marker_anime_posy_tab[8];                             /* @0x0029f360 size 0x20 */
struct marker_anime_db *map;                                     /* @0x002a2aa8 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xab544 */
struct marker_anime_db marker_anime_w;                           /* @0x006b4170 size 0x20 */
struct anime_obj_work back_anime_w;                              /* @0x006b4190 size 0x120 */

/* functions defined (14) */
static int marker_anime_disp(int cl, int cn, int bright);        /* 0x002442e0-0x002445b8 lines 690-801 */
void marker_anime_set_ct(int pid, int ct);                       /* 0x002445c0-0x00244604 lines 672-673 */
void marker_anime_reset(int pid);                                /* 0x00244610-0x00244630 lines 665-668 */
void marker_anime_set(int pid, int id);                          /* 0x00244630-0x0024464c lines 661-662 */
void back_anime_disp(int bright);                                /* 0x00244650-0x00244ccc lines 371-555 */
void back_anime_finish(void);                                    /* 0x00244cd0-0x00244cd8 lines 333-333 */
void back_anime_step(void);                                      /* 0x00244ce0-0x00244db4 lines 305-328 */
void back_anime_init(void);                                      /* 0x00244dc0-0x00244ee4 lines 259-302 */
void back_anime_set_flash_id(void);                              /* 0x00244ef0-0x00244f00 lines 251-252 */
void back_anime_set_inst_mode(void);                             /* 0x00244f00-0x00244f10 lines 246-247 */
void back_anime_set_normal_anime(int id);                        /* 0x00244f10-0x00244f40 lines 240-242 */
void back_anime_set_anime(int id, int anime_id, int anime_ct);   /* 0x00244f40-0x00244fc4 lines 210-230 */
static void back_anime_init_can(int id);                         /* 0x00244fd0-0x00245040 lines 173-207 */
static int down_load_anime(int id, void *address);               /* 0x00245040-0x0024510c lines 122-169 */

#endif /* DDR_UNIT_src_AM_s573_disp_b_anime_c_H */
