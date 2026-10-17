/*
 * C:\work2\usaex2\src\network\net_cnf\net_cnf_main.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 15 functions, code 0x007FF570-0x00802E14
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_cnf_net_cnf_main_c_H
#define DDR_UNIT_src_network_net_cnf_net_cnf_main_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cNetCnf.h"
#include "types/oni_course.h"
#include "types/sceNetcnfifArg.h"
#include "types/sceNetcnfifData.h"
#include "types/sceNetcnfifList.h"

/* anonymous types (9) */

/* anon_0_209 -- @anon0, 0x8 bytes, net_cnf_main.c (DIE 0x3B162C) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_0_209;

/* anon_1_209 -- @anon1, 0x14 bytes, net_cnf_main.c (DIE 0x3B17A1) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_1_209;

/* anon_4_209 -- @anon4, 0x4 bytes, net_cnf_main.c (DIE 0x3B3043) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_4_209;

/* anon_3_209 -- @anon3, 0x4 bytes, net_cnf_main.c (DIE 0x3B2FC1) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_4_209 s;                         // 0x4
} anon_3_209;

/* anon_8_209 -- @anon8, 0xC bytes, net_cnf_main.c (DIE 0x3B7774) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_8_209;

/* anon_10_209 -- @anon10, 0x12E0 bytes, net_cnf_main.c (DIE 0x3B82B0) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_8_209 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_10_209;

/* anon_11_209 -- @anon11, 0xD40 bytes, net_cnf_main.c (DIE 0x3B849B) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_11_209;

/* anon_9_209 -- @anon9, 0x4 bytes, net_cnf_main.c (DIE 0x3B7896) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_9_209;

/* anon_7_209 -- @anon7, 0x34 bytes, net_cnf_main.c (DIE 0x3B5D76) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_9_209 x0;                        // 0x4
    /* 0x004 */ anon_9_209 y0;                        // 0x4
    /* 0x008 */ anon_9_209 x1;                        // 0x4
    /* 0x00C */ anon_9_209 y1;                        // 0x4
    /* 0x010 */ anon_9_209 x2;                        // 0x4
    /* 0x014 */ anon_9_209 y2;                        // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
} anon_7_209;


/* variables (13) */
int netcnf_mid;                                                  /* @0x002DE660 size 0x4 */
int netcnfif_mid;                                                /* @0x002DE658 size 0x4 */
int lib_reset_step;                                              /* @0x002DE648 size 0x4 */
int lib_set_flag;                                                /* @0x002DE664 size 0x4 */
int load_module_abort_flag;                                      /* @0x002DE64C size 0x4 */
int netcnfif_load_result;                                        /* @0x002DE654 size 0x4 */
int netcnf_load_result;                                          /* @0x002DE65C size 0x4 */
struct _tag_cNetCnf *pNetCnf;                                    /* @0x002DE66C size 0x4 */
int lib_set_step;                                                /* @0x002DE668 size 0x4 */
int load_module_counter;                                         /* @0x002DE650 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
int SmapResult;                                                  /* @0x002DE194 size 0x4 */
int Dev9Result;                                                  /* @0x002DE19C size 0x4 */

/* functions referenced (6) */
void unload_module_th(void *);                                   /* @0x007FF570 */
void load_module_th(void *);                                     /* @0x007FF7E0 */
void load_entry_th(void *);                                      /* @0x00800E30 */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */
void NetDnasMain(struct _NETWORK_W *);                           /* @0x00805860 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */

/* functions defined (15) */
static void unload_module_th(void);                              /* 0x007FF570-0x007FF6C4 lines 2032-2078 */
int ncLibResetMain(void);                                        /* 0x007FF6D0-0x007FF7DC lines 1986-2029 */
static void load_module_th(void);                                /* 0x007FF7E0-0x007FF864 lines 1955-1975 */
int ncLibSetMain(void);                                          /* 0x007FF870-0x007FFC1C lines 1813-1953 */
static void set_warning_msg(int id, int yesno);                  /* 0x007FFC20-0x007FFEBC lines 1674-1769 */
static void set_msg(int id, int yesno);                          /* 0x007FFEC0-0x008000F4 lines 1564-1643 */
static int display(void);                                        /* 0x00800100-0x0080079C lines 1376-1558 */
static int term(void);                                           /* 0x008007A0-0x0080091C lines 1317-1370 */
static int menu(void);                                           /* 0x00800920-0x00800E30 lines 1188-1311 */
static void load_entry_th(void);                                 /* 0x00800E30-0x008011F0 lines 1064-1182 */
static int load_entry(void);                                     /* 0x008011F0-0x008016D8 lines 918-1063 */
static int get_list(void);                                       /* 0x008016E0-0x00801D68 lines 659-885 */
static int mc_check(void);                                       /* 0x00801D70-0x008022C8 lines 448-626 */
static int dev_check(void);                                      /* 0x008022D0-0x00802454 lines 345-417 */
void NetCnfMain(struct _NETWORK_W *netw);                        /* 0x00802460-0x00802E14 lines 126-339 */

#endif /* DDR_UNIT_src_network_net_cnf_net_cnf_main_c_H */
