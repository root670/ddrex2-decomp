/*
 * C:\work2\usaex2\src\CS\info\infosel.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 13 functions, code 0x007F0080-0x007F1BAC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_info_infosel_c_H
#define DDR_UNIT_src_CS_info_infosel_c_H

#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_tag_cInfo.h"
#include "types/_tag_cInfoScrBar.h"
#include "types/_tag_cInfoText.h"
#include "types/_tag_cInfoTitle.h"
#include "types/_tag_cInfosel.h"

/* anonymous types (4) */

/* anon_1_182 -- @anon1, 0x4 bytes, infosel.c (DIE 0x32F631) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_1_182;

/* anon_0_182 -- @anon0, 0x24 bytes, infosel.c (DIE 0x32EBD3) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_1_182 x0;                        // 0x4
    /* 0x004 */ anon_1_182 y0;                        // 0x4
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
} anon_0_182;

/* anon_3_182 -- @anon3, 0x8 bytes, infosel.c (DIE 0x32F97A) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_3_182;

/* anon_4_182 -- @anon4, 0x48 bytes, infosel.c (DIE 0x32FEDD) */
typedef struct {   // size 0x48
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
} anon_4_182;


/* variables (4) */
static unsigned char csxx24_color_table[16];                     /* not allocated size 0x10 */
struct _tag_cInfosel *pInfosel;                                  /* @0x002DDE50 size 0x4 */
struct _tag_cInfo *pInfo;                                        /* @0x002DDE54 size 0x4 */
static struct _tag_cInfosel _pInfosel;                           /* @0x00802200 size 0x3C */

/* functions defined (13) */
static void init_title_list(void);                               /* 0x007F0080-0x007F0150 lines 1354-1381 */
static void init_bar(void);                                      /* 0x007F0150-0x007F023C lines 1018-1055 */
static void view_title(void);                                    /* 0x007F0240-0x007F05F8 lines 740-994 */
static void control_title(void);                                 /* 0x007F0600-0x007F0860 lines 657-738 */
static void set_title(int mode0, int mode1);                     /* 0x007F0860-0x007F0A40 lines 574-650 */
int Update_Infosel(void);                                        /* 0x007F0A40-0x007F0B50 lines 540-567 */
int View_Infosel(void);                                          /* 0x007F0B50-0x007F0BA0 lines 506-535 */
static int Page_Change(int dir);                                 /* 0x007F0BA0-0x007F0D20 lines 425-474 */
int MoveCursor_Infosel(int dir, int *segment, int *offset, int mode); /* 0x007F0D20-0x007F0DAC lines 402-420 */
int CheckMoveCursor_Infosel(int dir, int *segment, int *offset); /* 0x007F0DB0-0x007F0E48 lines 366-397 */
static void control_sel(void);                                   /* 0x007F0E50-0x007F14D4 lines 236-357 */
int Control_Infosel(void);                                       /* 0x007F14E0-0x007F1AE8 lines 163-234 */
int Init_Infosel(void);                                          /* 0x007F1AF0-0x007F1BAC lines 128-158 */

#endif /* DDR_UNIT_src_CS_info_infosel_c_H */
