/*
 * C:\work2\usaex2\src\common\co_diap.c
 * MW MIPS C Compiler, overlay main; 17 functions, code 0x00230A50-0x00231624
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_common_co_diap_c_H
#define DDR_UNIT_src_common_co_diap_c_H

#include "types/tex_bind.h"

/* anonymous types (8) */

/* anon_0_100 -- @anon0, 0x48 bytes, co_diap.c (DIE 0x1BA92B) */
struct anon_0_100 {   // size 0x48
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

/* anon_1_100 -- @anon1, 0x20 bytes, co_diap.c (DIE 0x1BABAD) */
struct anon_1_100 {   // size 0x20
    /* 0x000 */ unsigned char flag;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned short w;                     // 0x2
    /* 0x004 */ unsigned short tex_id;                // 0x2
    /* 0x006 */ // 0x2 bytes padding
    /* 0x008 */ int waku_tex_id;                      // 0x4
    /* 0x00C */ unsigned short z;                     // 0x2
    /* 0x00E */ // 0x2 bytes padding
    /* 0x010 */ int obj_id;                           // 0x4
    /* 0x014 */ int id;                               // 0x4
    /* 0x018 */ float t;                              // 0x4
    /* 0x01C */ void *obj_p;                          // 0x4
};

/* anon_2_100 -- @anon2, 0x10 bytes, co_diap.c (DIE 0x1BAD1A) */
union anon_2_100 {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
};

/* anon_3_100 -- @anon3, 0x18 bytes, co_diap.c (DIE 0x1BAE6F) */
struct anon_3_100 {   // size 0x18
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned short z;                     // 0x2
    /* 0x004 */ int tex_id;                           // 0x4
    /* 0x008 */ float t;                              // 0x4
    /* 0x00C */ float dx;                             // 0x4
    /* 0x010 */ void *obj_p;                          // 0x4
    /* 0x014 */ int obj_id;                           // 0x4
};

/* anon_5_100 -- @anon5, 0x4 bytes, co_diap.c (DIE 0x1BB172) */
union anon_5_100 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_4_100 -- @anon4, 0x24 bytes, co_diap.c (DIE 0x1BAFDE) */
struct anon_4_100 {   // size 0x24
    /* 0x000 */ union anon_5_100 x0;                  // 0x4
    /* 0x004 */ union anon_5_100 y0;                  // 0x4
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

/* anon_6_100 -- @anon6, 0x30 bytes, co_diap.c (DIE 0x1BB1CF) */
struct anon_6_100 {   // size 0x30
    /* 0x000 */ union anon_5_100 x0;                  // 0x4
    /* 0x004 */ union anon_5_100 y0;                  // 0x4
    /* 0x008 */ union anon_5_100 x1;                  // 0x4
    /* 0x00C */ union anon_5_100 y1;                  // 0x4
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

/* anon_7_100 -- @anon7, 0x10 bytes, co_diap.c (DIE 0x1BB40C) */
struct anon_7_100 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};


/* variables (4) */
static struct anon_7_100 co_caption_objf;                        /* @0x002BE810 size 0x10 */
static struct anon_7_100 co_sel00_objf;                          /* @0x002BE820 size 0x10 */
struct anon_3_100 co_sel00_w;                                    /* @0x0071EFE0 size 0x18 */
struct anon_1_100 co_caption_w;                                  /* @0x0071F000 size 0x20 */

/* functions defined (17) */
void co_disp_all_init(void);                                     /* 0x00230A50-0x00230A84 lines 734-737 */
static int co_sel00_disp(void);                                  /* 0x00230A90-0x00230CB0 lines 572-648 */
static int co_sel00_move(void);                                  /* 0x00230CB0-0x00230E1C lines 523-567 */
float co_sel00_x(void);                                          /* 0x00230E20-0x00230E84 lines 509-516 */
int co_sel00_is_exist(void);                                     /* 0x00230E90-0x00230ECC lines 498-503 */
int co_sel00_is_apper_end(void);                                 /* 0x00230ED0-0x00230EFC lines 490-493 */
void co_sel00_disap_set(void);                                   /* 0x00230F00-0x00230F78 lines 462-470 */
void co_base00_set(unsigned short pri, unsigned char obj_pri, int tex_id); /* 0x00230F80-0x00231000 lines 416-428 */
void co_sel00_set(unsigned char mode, unsigned short pri, unsigned char obj_pri); /* 0x00231000-0x00231074 lines 386-398 */
static int co_caption_disp(void);                                /* 0x00231080-0x002313B8 lines 231-286 */
static int co_caption_move(void);                                /* 0x002313C0-0x00231450 lines 210-228 */
int co_caption_is_exist(void);                                   /* 0x00231450-0x0023148C lines 196-201 */
int co_caption_is_apper_end(void);                               /* 0x00231490-0x002314BC lines 188-191 */
void co_caption_del(void);                                       /* 0x002314C0-0x00231520 lines 173-181 */
void co_caption_disap(void);                                     /* 0x00231520-0x00231588 lines 158-167 */
void co_caption_tex_id_set(int tex_id);                          /* 0x00231590-0x0023159C lines 150-151 */
void co_caption_set(unsigned short w, unsigned short tex_id, unsigned char mode, unsigned short pri, unsigned char obj_pri); /* 0x002315A0-0x00231624 lines 127-142 */

#endif /* DDR_UNIT_src_common_co_diap_c_H */
