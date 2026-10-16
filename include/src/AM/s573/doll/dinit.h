/*
 * C:\work2\usaex2\src\AM\s573\doll\dinit.c
 * MW MIPS C Compiler, overlay main; 16 functions, code 0x001CF380-0x001D03BC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_dinit_c_H
#define DDR_UNIT_src_AM_s573_doll_dinit_c_H

#include "types/_GsCOORDINATE2.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cFilepackData.h"
#include "types/dancer_model_w.h"
#include "types/dancer_motion_w.h"
#include "types/oni_course.h"

/* anonymous types (26) */

/* anon_22_27 -- @anon22, 0x14 bytes, dinit.c (DIE 0x433CA) */
struct anon_22_27 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_0_27 -- @anon0, 0x1300 bytes, dinit.c (DIE 0x3EAD2) */
struct anon_0_27 {   // size 0x1300
    /* 0x000 */ unsigned char evboot[24];             // 0x18
    /* 0x018 */ unsigned char is_savedata;            // 0x1
    /* 0x019 */ signed char max_area;                 // 0x1
    /* 0x01A */ signed char disp_type;                // 0x1
    /* 0x01B */ char pading;                          // 0x1
    /* 0x01C */ unsigned char dancer_use_cnt[24];     // 0x18
    /* 0x034 */ int cur_cursor;                       // 0x4
    /* 0x038 */ unsigned int all_clear_count;         // 0x4
    /* 0x03C */ unsigned int all_play_time;           // 0x4
    /* 0x040 */ int route[200];                       // 0x320
    /* 0x360 */ struct anon_22_27 subject[200];       // 0xFA0
};

/* anon_1_27 -- @anon1, 0x10 bytes, dinit.c (DIE 0x3ECC4) */
struct anon_1_27 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
};

/* anon_2_27 -- @anon2, 0x2 bytes, dinit.c (DIE 0x3ED60) */
struct anon_2_27 {   // size 0x2
    /* 0x000 */ unsigned short offset;                // 0x2
};

/* anon_5_27 -- @anon5, 0x4 bytes, dinit.c (DIE 0x3F285) */
struct anon_5_27 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_3_27 -- @anon3, 0x4 bytes, dinit.c (DIE 0x3EDC8) */
union anon_3_27 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_5_27 s;                   // 0x4
};

/* anon_4_27 -- @anon4, 0x80 bytes, dinit.c (DIE 0x3EE26) */
struct anon_4_27 {   // size 0x80
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
};

/* anon_6_27 -- @anon6, 0x4 bytes, dinit.c (DIE 0x3F4B6) */
struct anon_6_27 {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ struct anon_2_27 tbl[1];              // 0x2
};

/* anon_24_27 -- @anon24, 0xC bytes, dinit.c (DIE 0x4364D) */
struct anon_24_27 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_7_27 -- @anon7, 0x12E0 bytes, dinit.c (DIE 0x3F51D) */
struct anon_7_27 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_24_27 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_8_27 -- @anon8, 0x8 bytes, dinit.c (DIE 0x3F801) */
struct anon_8_27 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_21_27 -- @anon21, 0xD40 bytes, dinit.c (DIE 0x42F73) */
struct anon_21_27 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_9_27 -- @anon9, 0x2134 bytes, dinit.c (DIE 0x3F90B) */
struct anon_9_27 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_3_27 userpass;             // 0x4
    /* 0x008 */ struct anon_7_27 pwork;               // 0x12E0
    /* 0x12E8 */ struct anon_21_27 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_10_27 -- @anon10, 0xC bytes, dinit.c (DIE 0x3FB11) */
struct anon_10_27 {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ struct anon_20_27 **offset;           // 0x4
};

/* anon_11_27 -- @anon11, 0x28 bytes, dinit.c (DIE 0x3FEC3) */
struct anon_11_27 {   // size 0x28
    /* 0x000 */ struct anon_1_27 scale;               // 0x10
    /* 0x010 */ struct anon_8_27 rotate;              // 0x8
    /* 0x018 */ struct anon_1_27 trans;               // 0x10
};

/* anon_12_27 -- @anon12, 0x4 bytes, dinit.c (DIE 0x3FF98) */
struct anon_12_27 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_13_27 -- @anon13, 0x8 bytes, dinit.c (DIE 0x40072) */
struct anon_13_27 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};

/* anon_23_27 -- @anon23, 0x8 bytes, dinit.c (DIE 0x435E1) */
struct anon_23_27 {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ struct anon_10_27 *offset;            // 0x4
};

/* anon_14_27 -- @anon14, 0x10 bytes, dinit.c (DIE 0x40890) */
struct anon_14_27 {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ struct anon_23_27 motion[1];          // 0x8
};

/* anon_15_27 -- @anon15, 0x14 bytes, dinit.c (DIE 0x40E7A) */
struct anon_15_27 {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00C */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
};

/* anon_16_27 -- @anon16, 0x246380 bytes, dinit.c (DIE 0x41CAF) */
struct anon_16_27 {   // size 0x246380
    /* 0x000 */ struct dancer_motion_w motion_w[3];   // 0x11E8
    /* 0x11E8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x11F0 */ struct dancer_model_w model_w[3];    // 0x1590
    /* 0x2780 */ unsigned int mdl_data[3][45568];     // 0x85800
    /* 0x87F80 */ unsigned int mot_data[3][86784];    // 0xFE400
    /* 0x186380 */ unsigned int packet_w[3][65536];   // 0xC0000
};

/* anon_17_27 -- @anon17, 0x10 bytes, dinit.c (DIE 0x420B6) */
struct anon_17_27 {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
};

/* anon_18_27 -- @anon18, 0x8 bytes, dinit.c (DIE 0x42A20) */
struct anon_18_27 {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ struct anon_6_27 data;                // 0x4
};

/* anon_19_27 -- @anon19, 0x31 bytes, dinit.c (DIE 0x42CCF) */
struct anon_19_27 {   // size 0x31
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[48];                          // 0x30
};

/* anon_20_27 -- @anon20, 0xC bytes, dinit.c (DIE 0x42D78) */
struct anon_20_27 {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ struct anon_18_27 **offset;           // 0x4
};

/* anon_25_27 -- @anon25, 0x20 bytes, dinit.c (DIE 0x43794) */
struct anon_25_27 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
};


/* variables (6) */
static char male_mot[4];                                         /* @0x002D16B8 size 0x4 */
struct anon_4_27 *dancer_ctrl_w;                                 /* @0x002DD94C size 0x4 */
struct anon_13_27 dollpack_bin[];                                /* @0x002DA768 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
unsigned int tex_floor[];                                        /* @0x002B3480 */
struct anon_16_27 *dancer_data_w;                                /* @0x002DE4A8 size 0x4 */

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
