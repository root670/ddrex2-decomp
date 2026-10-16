/*
 * C:\work\usam2\src\AM\s573\doll\ddata.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x00249830-0x00249A08
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_ddata_c_H
#define DDR_UNIT_src_AM_s573_doll_ddata_c_H

/* anonymous types (2) */

/* anon_0_46 -- @anon0, 0x10 bytes, ddata.c (DIE 0x81CE9) */
struct anon_0_46 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_1_46 -- @anon1, 0x1C bytes, ddata.c (DIE 0x81EB5) */
struct anon_1_46 {   // size 0x1C
    /* 0x000 */ float scale;                          // 0x4
    /* 0x004 */ float shadow_bri;                     // 0x4
    /* 0x008 */ unsigned int chara_lst : 2;           // bits 0..1
    /* 0x008 */ unsigned int hide : 1;                // bits 2..2
    /* 0x00C */ unsigned int *prim_tbl;               // 0x4
    /* 0x010 */ unsigned char *mot_tbl;               // 0x4
    /* 0x014 */ struct anon_0_46 *edge_info;          // 0x4
    /* 0x018 */ char *name;                           // 0x4
};


/* variables (26) */
unsigned int tex_floor[2088];                                    /* @0x00288660 size 0x20A0 */
static void **chara_data_name[58];                               /* @0x0028A700 size 0xE8 */
static void **mot_data_name[8];                                  /* @0x0028A7F0 size 0x20 */
static unsigned int prm_aa1off[16];                              /* @0x006B4690 size 0x40 */
static unsigned int prm_comon[16];                               /* @0x0028A810 size 0x40 */
static unsigned int prm_4yuni[16];                               /* @0x0028A850 size 0x40 */
static unsigned int prm_4maid[16];                               /* @0x0028A890 size 0x40 */
static unsigned int prm_3usagi[16];                              /* not allocated size 0x40 */
static unsigned int prm_5zukin[16];                              /* @0x0028A8D0 size 0x40 */
static unsigned int prm_5naoki[16];                              /* @0x0028A910 size 0x40 */
static unsigned int prm_2kaeru[16];                              /* @0x0028A950 size 0x40 */
static unsigned char mot_f_norm[4];                              /* @0x002A25CC size 0x4 */
static unsigned char mot_f_capo[4];                              /* @0x002A25D0 size 0x4 */
static unsigned char mot_f_zkin[4];                              /* @0x002A25D4 size 0x4 */
static unsigned char mot_m_norm[4];                              /* @0x002A25D8 size 0x4 */
static unsigned char mot_m_afro[4];                              /* @0x002A25DC size 0x4 */
static unsigned char mot_m_capo[4];                              /* @0x002A25E0 size 0x4 */
static unsigned char mot_m_gagg[4];                              /* @0x002A25E4 size 0x4 */
static struct anon_0_46 es_comon[16];                            /* @0x0028A990 size 0x100 */
static struct anon_0_46 es_4yuni[16];                            /* @0x0028AA90 size 0x100 */
static struct anon_0_46 es_4emi[16];                             /* @0x0028AB90 size 0x100 */
static struct anon_0_46 es_5zukin[16];                           /* @0x0028AC90 size 0x100 */
static struct anon_0_46 es_5naoki[16];                           /* @0x0028AD90 size 0x100 */
static struct anon_0_46 es_2kaeru[16];                           /* @0x0028AE90 size 0x100 */
static struct anon_0_46 es_4maid[16];                            /* @0x0028AF90 size 0x100 */
static struct anon_1_46 dancer_info[58];                         /* @0x0029F920 size 0x658 */

/* functions defined (11) */
int get_chara_hide(int chara);                                   /* 0x00249830-0x00249858 lines 510-511 */
int get_chara_lst_id(int chara);                                 /* 0x00249860-0x00249884 lines 504-505 */
float get_shadow_bri(int chara);                                 /* 0x00249890-0x002498B0 lines 498-499 */
struct anon_0_46 *get_edge_info(int chara, int parts);           /* 0x002498B0-0x002498D8 lines 492-493 */
char *ps2dancerGetName(int chara);                               /* 0x002498E0-0x00249900 lines 485-486 */
int get_dancer_default_mot(int chara);                           /* 0x00249900-0x00249924 lines 479-480 */
int rnd_get_dancer_mot(int chara);                               /* 0x00249930-0x0024998C lines 471-474 */
unsigned int *get_primdt_tbl(int chara);                         /* 0x00249990-0x002499B0 lines 467-468 */
float get_dancer_scale(int chara);                               /* 0x002499B0-0x002499D0 lines 461-462 */
void **get_mdt_name(int motion);                                 /* 0x002499D0-0x002499E8 lines 169-170 */
void **get_cdt_name(int chara);                                  /* 0x002499F0-0x00249A08 lines 163-164 */

#endif /* DDR_UNIT_src_AM_s573_doll_ddata_c_H */
