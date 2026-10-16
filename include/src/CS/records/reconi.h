/*
 * C:\work\usam2\src\CS\records\reconi.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x00224E20-0x00227B00
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_reconi_c_H
#define DDR_UNIT_src_CS_records_reconi_c_H

#include "types/_tag_cDDR7OniRecord1.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cRec.h"
#include "types/_tag_cRecOni.h"
#include "types/_tag_cRecOniData.h"
#include "types/_tag_cRecOniRecord1.h"
#include "types/_tag_cRecOniTitleInfo.h"
#include "types/_tag_cRecm.h"
#include "types/_tag_cRecmDelWnd.h"

/* anonymous types (7) */

/* anon_0_9 -- @anon0, 0xCC8 bytes, reconi.c (DIE 0x22721) */
struct anon_0_9 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_2_9 -- @anon2, 0x4 bytes, reconi.c (DIE 0x230A9) */
union anon_2_9 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_9 -- @anon1, 0x24 bytes, reconi.c (DIE 0x22B58) */
struct anon_1_9 {   // size 0x24
    /* 0x000 */ union anon_2_9 x0;                    // 0x4
    /* 0x004 */ union anon_2_9 y0;                    // 0x4
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

/* anon_3_9 -- @anon3, 0x68 bytes, reconi.c (DIE 0x2367A) */
struct anon_3_9 {   // size 0x68
    /* 0x000 */ union anon_2_9 x0;                    // 0x4
    /* 0x004 */ union anon_2_9 y0;                    // 0x4
    /* 0x008 */ union anon_2_9 x1;                    // 0x4
    /* 0x00C */ union anon_2_9 y1;                    // 0x4
    /* 0x010 */ union anon_2_9 x2;                    // 0x4
    /* 0x014 */ union anon_2_9 y2;                    // 0x4
    /* 0x018 */ union anon_2_9 x3;                    // 0x4
    /* 0x01C */ union anon_2_9 y3;                    // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
};

/* anon_4_9 -- @anon4, 0x48 bytes, reconi.c (DIE 0x2432C) */
struct anon_4_9 {   // size 0x48
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

/* anon_5_9 -- @anon5, 0x8 bytes, reconi.c (DIE 0x245D2) */
struct anon_5_9 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_6_9 -- @anon6, 0xC bytes, reconi.c (DIE 0x252D0) */
struct anon_6_9 {   // size 0xC
    /* 0x000 */ int year;                             // 0x4
    /* 0x004 */ int month;                            // 0x4
    /* 0x008 */ int day;                              // 0x4
};


/* variables (5) */
static struct _tag_cRecOni *pRecOni;                             /* @0x002A2140 size 0x4 */
struct _tag_cRec *pRec;                                          /* @0x002A06B8 size 0x4 */
struct _tag_cRecm *pRecm;                                        /* @0x002A06BC size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
static struct _tag_cRecOni _pRecOni;                             /* @0x006B26A0 size 0x12C */

/* functions defined (19) */
int Update_Reconi(void);                                         /* 0x00224E20-0x00225068 lines 2148-2188 */
int View_Reconi(void);                                           /* 0x00225070-0x002251A0 lines 2097-2144 */
int Control_Reconi(void);                                        /* 0x002251A0-0x00225270 lines 2084-2093 */
int Init_Reconi(void);                                           /* 0x00225270-0x00225370 lines 2064-2080 */
static void draw_ope(void);                                      /* 0x00225370-0x00225658 lines 1951-2042 */
static void draw_dir_arrow(void);                                /* 0x00225660-0x00225860 lines 1878-1921 */
static void draw_cursor(void);                                   /* 0x00225860-0x00225AB4 lines 1767-1862 */
static void draw_table(void);                                    /* 0x00225AC0-0x002265B0 lines 1390-1761 */
static void draw_detail_data(void);                              /* 0x002265B0-0x00226968 lines 1197-1367 */
static void puts_combo(short _x, short _y, int _val, int _bright, int _pri, int _alpha); /* 0x00226970-0x00226B48 lines 1114-1151 */
static void puts_re2424(short _x, short _y, int _val, int _bright, int _pri, int _alpha, int tex_num); /* 0x00226B50-0x00226D34 lines 1071-1108 */
static int control_loop(void);                                   /* 0x00226D40-0x00227364 lines 722-892 */
static int control_delete(void);                                 /* 0x00227370-0x002274B8 lines 641-687 */
static void SetDelStep(int _step);                               /* 0x002274C0-0x002275E4 lines 589-618 */
static int check_move_cursor(int dir, int *segment, int *offset); /* 0x002275F0-0x00227688 lines 454-485 */
static void set_data_scroll(int dir);                            /* 0x00227690-0x00227830 lines 388-445 */
static void update_data(void);                                   /* 0x00227830-0x00227908 lines 344-383 */
static void init_data(void);                                     /* 0x00227910-0x002279A4 lines 295-322 */
static void init_oni_record(void);                               /* 0x002279B0-0x00227B00 lines 224-290 */

#endif /* DDR_UNIT_src_CS_records_reconi_c_H */
