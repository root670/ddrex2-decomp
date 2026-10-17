/*
 * C:\work2\usaex2\src\AM\s573\doll\motion1.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001CA060-0x001CAE30
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_motion1_c_H
#define DDR_UNIT_src_AM_s573_doll_motion1_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cFilepackData.h"
#include "types/dance_set.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"

/* anonymous types (12) */

/* anon_10_19 -- @anon10, 0x2 bytes, motion1.c (DIE 0x2D670) */
typedef struct {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
} anon_10_19;

/* anon_11_19 -- @anon11, 0x4 bytes, motion1.c (DIE 0x2D6D9) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ anon_10_19 tbl[1];                    // 0x2
} anon_11_19;

/* anon_2_19 -- @anon2, 0x8 bytes, motion1.c (DIE 0x2CB64) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ anon_11_19 data;                      // 0x4
} anon_2_19;

/* anon_0_19 -- @anon0, 0xC bytes, motion1.c (DIE 0x2C8BA) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ anon_2_19 **offset;                   // 0x4
} anon_0_19;

/* anon_5_19 -- @anon5, 0xC bytes, motion1.c (DIE 0x2D332) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ anon_0_19 **offset;                   // 0x4
} anon_5_19;

/* anon_7_19 -- @anon7, 0x8 bytes, motion1.c (DIE 0x2D454) */
typedef struct {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ anon_5_19 *offset;                    // 0x4
} anon_7_19;

/* anon_1_19 -- @anon1, 0x10 bytes, motion1.c (DIE 0x2C9FC) */
typedef struct {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ anon_7_19 motion[1];                  // 0x8
} anon_1_19;

/* anon_3_19 -- @anon3, 0x80 bytes, motion1.c (DIE 0x2CC31) */
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
} anon_3_19;

/* anon_6_19 -- @anon6, 0x14 bytes, motion1.c (DIE 0x2D3E3) */
typedef struct {   // size 0x14
    /* 0x000 */ char *dance_name;                     // 0x4
    /* 0x004 */ char *tail_name[4];                   // 0x10
} anon_6_19;

/* anon_9_19 -- @anon9, 0x10 bytes, motion1.c (DIE 0x2D5D4) */
typedef struct {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
} anon_9_19;

/* anon_12_19 -- @anon12, 0x8 bytes, motion1.c (DIE 0x2D741) */
typedef struct {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
} anon_12_19;

/* anon_15_19 -- @anon15, 0x246380 bytes, motion1.c (DIE 0x2DF55) */
typedef struct {   // size 0x246380
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1590
    /* 0x2780 */ unsigned int mdl_data[3][45568];     // 0x85800
    /* 0x87F80 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x186380 */ unsigned int packet_w[3][65536];   // 0xC0000
} anon_15_19;


/* variables (12) */
static char *dset[8][5];                                         /* @0x002B5CC0 size 0xA0 */
static struct dance_set normal_dance_set[9];                     /* @0x002D12C0 size 0x144 */
static anon_6_19 dance_con[20];                                  /* @0x002D14E0 size 0x190 */
static char *dance_name[20];                                     /* @0x002B5D60 size 0x50 */
static int parent_parts[18];                                     /* @0x002B5DB0 size 0x48 */
static unsigned int chara_pos[28];                               /* @0x002B5E00 size 0x70 */
void *dance_motion_pack_tab[3][20];                              /* @0x0070FF50 size 0xF0 */
anon_3_19 *dancer_ctrl_w;                                        /* @0x002DD94C size 0x4 */
anon_15_19 *dancer_data_w;                                       /* @0x002DE4A8 size 0x4 */
int player_dance_top[3][17];                                     /* @0x00712200 size 0xCC */
struct dance_set player_dance_set[3][80];                        /* @0x00710040 size 0x21C0 */
int motiontype[3];                                               /* @0x007122D0 size 0xC */

/* functions defined (5) */
void set_dance_motion_pack_tab(int pid);                         /* 0x001CA060-0x001CA240 lines 499-525 */
static anon_1_19 *get_dance_mpack(int pid, char *dname);         /* 0x001CA240-0x001CA2F8 lines 455-472 */
void set_dance_motion(int pid);                                  /* 0x001CA300-0x001CA88C lines 274-392 */
void init_dance_motion(int pid);                                 /* 0x001CA890-0x001CABFC lines 217-265 */
int dancer_motion_setup(int pid, int motion_id);                 /* 0x001CAC00-0x001CAE30 lines 161-209 */

#endif /* DDR_UNIT_src_AM_s573_doll_motion1_c_H */
