/*
 * C:\work2\usaex2\src\CS\train\tra_str.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0027C010-0x0027C1F0
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
#ifndef DDR_UNIT_src_CS_train_tra_str_c_H
#define DDR_UNIT_src_CS_train_tra_str_c_H

/* anonymous types (1) */

/* anon_0_158 -- @anon0, 0x8 bytes, tra_str.c (DIE 0x2D0AF6) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char **array;                // 0x4
    /* 0x004 */ int num;                              // 0x4
} anon_0_158;


/* variables (14) */
static unsigned char *tr_str_play[3];                            /* @0x002C0CC8 size 0xC */
static unsigned char *tr_str_step[6];                            /* @0x002C0CE0 size 0x18 */
static unsigned char *tr_str_offon[2];                           /* @0x002DDDE8 size 0x8 */
static unsigned char *tr_str_mspeed[5];                          /* @0x002C0D00 size 0x14 */
static unsigned char *tr_str_op_speed[6];                        /* @0x002C0D20 size 0x18 */
static unsigned char *tr_str_op_appear[4];                       /* @0x002C0D40 size 0x10 */
static unsigned char *tr_str_op_turn[5];                         /* @0x002C0D50 size 0x14 */
static unsigned char *tr_str_op_simu[3];                         /* @0x002C0D68 size 0xC */
static unsigned char *tr_str_op_scroll[2];                       /* @0x002DDDF0 size 0x8 */
static unsigned char *tr_str_op_freeze[2];                       /* @0x002DDDF8 size 0x8 */
static unsigned char *tr_str_rs_menu[4];                         /* @0x002C0D80 size 0x10 */
static unsigned char *tr_str_ck_menu[3];                         /* @0x002C0D90 size 0xC */
static unsigned char *tr_str_ck_mode[2];                         /* @0x002DDE00 size 0x8 */
static anon_0_158 tr_str_tbl[15];                                /* @0x002C0DA0 size 0x78 */

/* functions defined (3) */
void Tr_bar_digit_disp(float cx, float y0, unsigned char num, int pri); /* 0x0027C010-0x0027C154 lines 143-163 */
unsigned char Tr_get_lr_item_max(int kind);                      /* 0x0027C160-0x0027C18C lines 135-138 */
unsigned char *Tr_get_str(int kind, int index);                  /* 0x0027C190-0x0027C1F0 lines 120-127 */

#endif /* DDR_UNIT_src_CS_train_tra_str_c_H */
