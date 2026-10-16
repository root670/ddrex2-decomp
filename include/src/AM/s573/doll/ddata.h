/*
 * C:\work2\usaex2\src\AM\s573\doll\ddata.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x001C7250-0x001C7428
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_ddata_c_H
#define DDR_UNIT_src_AM_s573_doll_ddata_c_H

/* anonymous types (2) */

/* anon_0_15 -- @anon0, 0x10 bytes, ddata.c (DIE 0x22F59) */
struct anon_0_15 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_1_15 -- @anon1, 0x1C bytes, ddata.c (DIE 0x23023) */
struct anon_1_15 {   // size 0x1C
    /* 0x000 */ float scale;                          // 0x4
    /* 0x004 */ float shadow_bri;                     // 0x4
    /* 0x008 */ unsigned int chara_lst : 2;           // bits 0..1
    /* 0x008 */ unsigned int hide : 1;                // bits 2..2
    /* 0x00C */ unsigned int *prim_tbl;               // 0x4
    /* 0x010 */ unsigned char *mot_tbl;               // 0x4
    /* 0x014 */ struct anon_0_15 *edge_info;          // 0x4
    /* 0x018 */ char *name;                           // 0x4
};


/* variables (26) */
unsigned int tex_floor[2088];                                    /* @0x002B3480 size 0x20A0 */
static void **chara_data_name[45];                               /* @0x002B5520 size 0xB4 */
static void **mot_data_name[8];                                  /* @0x002B55E0 size 0x20 */
static unsigned int prm_aa1off[16];                              /* not allocated size 0x40 */
static unsigned int prm_comon[16];                               /* @0x002B5600 size 0x40 */
static unsigned int prm_4yuni[16];                               /* @0x002B5640 size 0x40 */
static unsigned int prm_4maid[16];                               /* not allocated size 0x40 */
static unsigned int prm_3usagi[16];                              /* not allocated size 0x40 */
static unsigned int prm_5zukin[16];                              /* @0x002B5680 size 0x40 */
static unsigned int prm_5naoki[16];                              /* @0x002B56C0 size 0x40 */
static unsigned int prm_2kaeru[16];                              /* not allocated size 0x40 */
static unsigned char mot_f_norm[4];                              /* @0x002DD950 size 0x4 */
static unsigned char mot_f_capo[4];                              /* @0x002DD954 size 0x4 */
static unsigned char mot_f_zkin[4];                              /* @0x002DD958 size 0x4 */
static unsigned char mot_m_norm[4];                              /* @0x002DD95C size 0x4 */
static unsigned char mot_m_afro[4];                              /* @0x002DD960 size 0x4 */
static unsigned char mot_m_capo[4];                              /* @0x002DD964 size 0x4 */
static unsigned char mot_m_gagg[4];                              /* @0x002DD968 size 0x4 */
static struct anon_0_15 es_comon[16];                            /* @0x002B5700 size 0x100 */
static struct anon_0_15 es_4yuni[16];                            /* @0x002B5800 size 0x100 */
static struct anon_0_15 es_4emi[16];                             /* @0x002B5900 size 0x100 */
static struct anon_0_15 es_5zukin[16];                           /* @0x002B5A00 size 0x100 */
static struct anon_0_15 es_5naoki[16];                           /* @0x002B5B00 size 0x100 */
static struct anon_0_15 es_2kaeru[16];                           /* not allocated size 0x100 */
static struct anon_0_15 es_4maid[16];                            /* not allocated size 0x100 */
static struct anon_1_15 dancer_info[45];                         /* @0x002D0D30 size 0x4EC */

/* functions defined (11) */
int get_chara_hide(int chara);                                   /* 0x001C7250-0x001C7278 lines 617-618 */
int get_chara_lst_id(int chara);                                 /* 0x001C7280-0x001C72A4 lines 611-612 */
float get_shadow_bri(int chara);                                 /* 0x001C72B0-0x001C72D0 lines 605-606 */
struct anon_0_15 *get_edge_info(int chara, int parts);           /* 0x001C72D0-0x001C72F8 lines 599-600 */
char *ps2dancerGetName(int chara);                               /* 0x001C7300-0x001C7320 lines 592-593 */
int get_dancer_default_mot(int chara);                           /* 0x001C7320-0x001C7344 lines 586-587 */
int rnd_get_dancer_mot(int chara);                               /* 0x001C7350-0x001C73AC lines 578-581 */
unsigned int *get_primdt_tbl(int chara);                         /* 0x001C73B0-0x001C73D0 lines 574-575 */
float get_dancer_scale(int chara);                               /* 0x001C73D0-0x001C73F0 lines 568-569 */
void **get_mdt_name(int motion);                                 /* 0x001C73F0-0x001C7408 lines 164-165 */
void **get_cdt_name(int chara);                                  /* 0x001C7410-0x001C7428 lines 158-159 */

#endif /* DDR_UNIT_src_AM_s573_doll_ddata_c_H */
