/*
 * C:\work2\usaex2\src\AM\s573\doll\dinit.c
 * MW MIPS C Compiler, overlay main; 16 functions, code 0x001CF380-0x001D03BC
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
#ifndef DDR_UNIT_src_AM_s573_doll_dinit_c_H
#define DDR_UNIT_src_AM_s573_doll_dinit_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"
#include "types/oni_course.h"

/* anonymous types (4) */

/* anon_4_27 -- @anon4, 0x80 bytes, dinit.c (DIE 0x3EE26) */
typedef struct {   // size 0x80
    /* 0x000 */ struct _tag_cFilepackData tblFilepack[2];  // 0x10
    /* 0x010 */ short loadstep;                       // 0x2
    /* 0x012 */ char loadpid;                         // 0x1
    /* 0x013 */ char loadmid;                         // 0x1
    /* 0x014 */ unsigned int topaddr;                 // 0x4
    /* 0x018 */ unsigned int readaddr;                // 0x4
    /* 0x01C */ unsigned int pdataaddr;               // 0x4
    /* 0x020 */ short ploadstep;                      // 0x2
    /* 0x022 */ short chgstep[3];                     // 0x6
    /* 0x028 */ unsigned int *tex_buff[3];            // 0xC
    /* 0x034 */ unsigned int *nmd_buff[3];            // 0xC
    /* 0x040 */ char nmd_loaded_id[3];                // 0x3
    /* 0x043 */ char mot_loaded_id[3][2];             // 0x6
    /* 0x049 */ char data_buf_broken;                 // 0x1
    /* 0x04A */ char playmode;                        // 0x1
    /* 0x04B */ char toon;                            // 0x1
    /* 0x04C */ char shadow;                          // 0x1
    /* 0x04D */ char effect;                          // 0x1
    /* 0x04E */ char floor;                           // 0x1
    /* 0x04F */ char unison;                          // 0x1
    /* 0x050 */ char chr_num;                         // 0x1
    /* 0x051 */ char chr_id[3];                       // 0x3
    /* 0x054 */ char mot_id[3];                       // 0x3
    /* 0x057 */ // 0x1 bytes padding
    /* 0x058 */ unsigned int *mot_adr[3];             // 0xC
    /* 0x064 */ int base_bri;                         // 0x4
    /* 0x068 */ int bright;                           // 0x4
    /* 0x06C */ int pid_bri[3];                       // 0xC
    /* 0x078 */ unsigned int vcnt;                    // 0x4
    /* 0x07C */ int common_rand;                      // 0x4
} anon_4_27;

/* anon_13_27 -- @anon13, 0x8 bytes, dinit.c (DIE 0x40072) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
} anon_13_27;

/* anon_16_27 -- @anon16, 0x246380 bytes, dinit.c (DIE 0x41CAF) */
typedef struct {   // size 0x246380
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding
    /* 0x11F0 */ struct dancer_model_w model_w[3] __attribute__((aligned(16)));  // 0x1590
    /* 0x2780 */ unsigned int mdl_data[3][45568];     // 0x85800
    /* 0x87F80 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x186380 */ unsigned int packet_w[3][65536];   // 0xC0000
} anon_16_27;

/* anon_19_27 -- @anon19, 0x31 bytes, dinit.c (DIE 0x42CCF) */
typedef struct {   // size 0x31
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[48];                          // 0x30
} anon_19_27;


/* variables (6) */
static char male_mot[4];                                         /* @0x002D16B8 size 0x4 */
anon_4_27 *dancer_ctrl_w;                                        /* @0x002DD94C size 0x4 */
anon_13_27 dollpack_bin[];                                       /* @0x002DA768 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
unsigned int tex_floor[];                                        /* @0x002B3480 */
anon_16_27 *dancer_data_w;                                       /* @0x002DE4A8 size 0x4 */

/* functions referenced (1) */
void DecodeFilepackData_Th(void *);                              /* @0x0016DC50 */

/* functions defined (16) */
int ps2dancerPdataLoadStep(void);                                /* 0x001CF380-0x001CF408 lines 571-588 */
void ps2dancerPdataLoadInit(void *pdataaddr);                    /* 0x001CF410-0x001CF42C lines 558-568 */
int ps2dancerGetEntryNum(void);                                  /* 0x001CF430-0x001CF470 lines 538-545 */
static void shape_mot_id(void);                                  /* 0x001CF470-0x001CF684 lines 446-496 */
void ps2dancerSetup(void);                                       /* 0x001CF690-0x001CF758 lines 416-435 */
int ps2dancerChangeStep(int pid);                                /* 0x001CF760-0x001CF8C8 lines 380-409 */
void ps2dancerChange(int pid, int chara);                        /* 0x001CF8D0-0x001CF938 lines 366-377 */
int ps2dancerLoadStep(void);                                     /* 0x001CF940-0x001CFDB4 lines 258-358 */
static int get_free_motbuf(int mot_id);                          /* 0x001CFDC0-0x001CFE58 lines 236-251 */
void ps2dancerLoadInit(void *readtmpaddr);                       /* 0x001CFE60-0x001D00AC lines 161-220 */
void ps2dancerEntry2(int pid, int chara, int motion);            /* 0x001D00B0-0x001D0140 lines 132-154 */
void ps2dancerEntry(int pid, int chara);                         /* 0x001D0140-0x001D01E0 lines 113-129 */
static int auto_chara_select(int chara);                         /* 0x001D01E0-0x001D02BC lines 84-110 */
void ps2dancerResetEntry(void);                                  /* 0x001D02C0-0x001D02D8 lines 71-77 */
void ps2dancerBreakDataArea(void);                               /* 0x001D02E0-0x001D02F0 lines 62-63 */
void *ps2dancerInit(void *workaddr, int playmode);               /* 0x001D02F0-0x001D03BC lines 25-54 */

#endif /* DDR_UNIT_src_AM_s573_doll_dinit_c_H */
