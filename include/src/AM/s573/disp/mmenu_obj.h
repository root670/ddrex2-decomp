/*
 * C:\work2\usaex2\src\AM\s573\disp\mmenu_obj.c
 * MW MIPS C Compiler, overlay main; 20 functions, code 0x00254F80-0x00256B90
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_disp_mmenu_obj_c_H
#define DDR_UNIT_src_AM_s573_disp_mmenu_obj_c_H

/* anonymous types (12) */

/* anon_7_132 -- @anon7, 0xC bytes, mmenu_obj.c (DIE 0x24413A) */
struct anon_7_132 {   // size 0xC
    /* 0x000 */ float dx;                             // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ unsigned char step;                   // 0x1
    /* 0x009 */ // 0x3 bytes padding
};

/* anon_0_132 -- @anon0, 0xB4 bytes, mmenu_obj.c (DIE 0x2438E4) */
struct anon_0_132 {   // size 0xB4
    /* 0x000 */ struct anon_7_132 one[13];            // 0x9C
    /* 0x09C */ float dx;                             // 0x4
    /* 0x0A0 */ float t;                              // 0x4
    /* 0x0A4 */ unsigned char cur;                    // 0x1
    /* 0x0A5 */ unsigned char step;                   // 0x1
    /* 0x0A6 */ // 0x2 bytes padding
    /* 0x0A8 */ float ln_p[2];                        // 0x8
    /* 0x0B0 */ float ln_t;                           // 0x4
};

/* anon_1_132 -- @anon1, 0xC bytes, mmenu_obj.c (DIE 0x2439E7) */
struct anon_1_132 {   // size 0xC
    /* 0x000 */ float t;                              // 0x4
    /* 0x004 */ unsigned char up;                     // 0x1
    /* 0x005 */ unsigned char dw;                     // 0x1
    /* 0x006 */ // 0x2 bytes padding
    /* 0x008 */ float timer;                          // 0x4
};

/* anon_2_132 -- @anon2, 0x48 bytes, mmenu_obj.c (DIE 0x243A84) */
struct anon_2_132 {   // size 0x48
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

/* anon_3_132 -- @anon3, 0x4 bytes, mmenu_obj.c (DIE 0x243D06) */
struct anon_3_132 {   // size 0x4
    /* 0x000 */ float timer;                          // 0x4
};

/* anon_4_132 -- @anon4, 0x18 bytes, mmenu_obj.c (DIE 0x243D6B) */
struct anon_4_132 {   // size 0x18
    /* 0x000 */ float dx[2];                          // 0x8
    /* 0x008 */ float t[2];                           // 0x8
    /* 0x010 */ unsigned char step[2];                // 0x2
    /* 0x012 */ unsigned char up;                     // 0x1
    /* 0x013 */ unsigned char dw;                     // 0x1
    /* 0x014 */ float timer;                          // 0x4
};

/* anon_8_132 -- @anon8, 0x4 bytes, mmenu_obj.c (DIE 0x2441B7) */
union anon_8_132 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_5_132 -- @anon5, 0x1C bytes, mmenu_obj.c (DIE 0x243E4E) */
struct anon_5_132 {   // size 0x1C
    /* 0x000 */ union anon_8_132 x0;                  // 0x4
    /* 0x004 */ union anon_8_132 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_6_132 -- @anon6, 0x24 bytes, mmenu_obj.c (DIE 0x243FA6) */
struct anon_6_132 {   // size 0x24
    /* 0x000 */ union anon_8_132 x0;                  // 0x4
    /* 0x004 */ union anon_8_132 y0;                  // 0x4
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

/* anon_9_132 -- @anon9, 0x10 bytes, mmenu_obj.c (DIE 0x24425E) */
struct anon_9_132 {   // size 0x10
    /* 0x000 */ float dx;                             // 0x4
    /* 0x004 */ float dy;                             // 0x4
    /* 0x008 */ float t;                              // 0x4
    /* 0x00C */ float pad;                            // 0x4
};

/* anon_10_132 -- @anon10, 0x10 bytes, mmenu_obj.c (DIE 0x24431D) */
struct anon_10_132 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};

/* anon_11_132 -- @anon11, 0x2C bytes, mmenu_obj.c (DIE 0x244502) */
struct anon_11_132 {   // size 0x2C
    /* 0x000 */ int next_step;                        // 0x4
    /* 0x004 */ int wait_ct;                          // 0x4
    /* 0x008 */ float timer;                          // 0x4
    /* 0x00C */ float fade_timer;                     // 0x4
    /* 0x010 */ void *obj_p[4];                       // 0x10
    /* 0x020 */ void *logo_obj;                       // 0x4
    /* 0x024 */ unsigned char obj_end_suu;            // 0x1
    /* 0x025 */ unsigned char how_to_read_wait;       // 0x1
    /* 0x026 */ unsigned char logo;                   // 0x1
    /* 0x027 */ unsigned char step;                   // 0x1
    /* 0x028 */ unsigned char cur;                    // 0x1
    /* 0x029 */ unsigned char step_s;                 // 0x1
    /* 0x02A */ unsigned char black_or_white;         // 0x1
    /* 0x02B */ // 0x1 bytes padding
};


/* variables (6) */
static struct anon_10_132 mmenu_objf[4];                         /* @0x002BF330 size 0x40 */
struct anon_10_132 mmenu_logo_objf;                              /* @0x002BF370 size 0x10 */
static float mmenu_ap_time[4];                                   /* @0x002BF380 size 0x10 */
static float mmenu_disap_time[4];                                /* @0x002BF390 size 0x10 */
static float mmenu_obj_pri[4];                                   /* @0x002BF3A0 size 0x10 */
struct anon_11_132 *mmw;                                         /* @0x002DA1A4 size 0x4 */

/* functions defined (20) */
static int mmenu_logo_disp(void *w);                             /* 0x00254F80-0x0025509C lines 864-885 */
static int mmenu_logo_disap(void *w);                            /* 0x002550A0-0x00255108 lines 848-861 */
static int mmenu_logo_exec(void *w);                             /* 0x00255110-0x00255130 lines 838-845 */
static int mmenu_exp_disp(void *w);                              /* 0x00255130-0x0025542C lines 776-821 */
static int mmenu_exp_disap(void *w);                             /* 0x00255430-0x00255594 lines 733-773 */
static int mmenu_exp_exec(void *w);                              /* 0x002555A0-0x00255634 lines 714-730 */
static int mmenu_exp_apper(void *w);                             /* 0x00255640-0x00255794 lines 671-711 */
static int mmenu_pic_disp(void *w);                              /* 0x002557A0-0x00255BB4 lines 605-651 */
static int mmenu_pic_disap(void *w);                             /* 0x00255BC0-0x00255C40 lines 584-601 */
static int mmenu_pic_exec(void *w);                              /* 0x00255C40-0x00255CD4 lines 565-581 */
static int mmenu_pic_apper(void *w);                             /* 0x00255CE0-0x00255D60 lines 546-563 */
static int mmenu_base_disp(void *w);                             /* 0x00255D60-0x00255E20 lines 505-525 */
static int mmenu_base_move(void *w);                             /* 0x00255E20-0x00255F50 lines 468-502 */
static int mmenu_item_disp(void *w);                             /* 0x00255F50-0x00256210 lines 400-458 */
static int mmenu_item_disap(void *w);                            /* 0x00256210-0x00256478 lines 350-397 */
static int mmenu_item_exec(void *w);                             /* 0x00256480-0x002565BC lines 317-347 */
static int mmenu_item_apper(void *w);                            /* 0x002565C0-0x00256878 lines 255-314 */
int mmenu_disap(void);                                           /* 0x00256880-0x0025693C lines 193-212 */
int mmenu_apper(void);                                           /* 0x00256940-0x00256A90 lines 166-187 */
int mmenu_logo(int push);                                        /* 0x00256A90-0x00256B90 lines 136-161 */

#endif /* DDR_UNIT_src_AM_s573_disp_mmenu_obj_c_H */
