/*
 * C:\work2\usaex2\src\common\cws\cws_str.c
 * MW MIPS C Compiler, overlay main; 20 functions, code 0x00205510-0x00206E48
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_common_cws_cws_str_c_H
#define DDR_UNIT_src_common_cws_cws_str_c_H

#include "types/_CWS_STR.h"
#include "types/_CWS_STR_DIGI.h"
#include "types/_CWS_WINS_W.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (3) */

/* anon_1_62 -- @anon1, 0x48 bytes, cws_str.c (DIE 0xF0FF9) */
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
} anon_1_62;

/* anon_3_62 -- @anon3, 0x4 bytes, cws_str.c (DIE 0xF1B5F) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_62;

/* anon_2_62 -- @anon2, 0x24 bytes, cws_str.c (DIE 0xF1950) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_3_62 x0;                         // 0x4
    /* 0x004 */ anon_3_62 y0;                         // 0x4
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
} anon_2_62;


/* variables (4) */
static struct _CWS_STR_DIGI digi_tbl[3][15];                     /* @0x002BB350 size 0xB4 */
static unsigned char digi_work[15];                              /* @0x002BB408 size 0xF */
unsigned char cws_str_buf[128];                                  /* @0x0071DA00 size 0x80 */
unsigned char cws_str_font_buf[130];                             /* @0x0071D970 size 0x82 */

/* functions defined (20) */
static void CwsStrDigi(short _x, short _y, unsigned char *_str, int _bri, int _pri, int _col, int alpha, int tex_id, int mode, int type); /* 0x00205510-0x002058D0 lines 606-676 */
void CwsStrDisp(struct _CWS_WIN_W *win, struct _CWS_STR *strw);  /* 0x002058D0-0x002060C0 lines 391-578 */
char CwsStrSetDispStatus(struct _CWS_WIN_W *win, int str_num, char on_off); /* 0x002060C0-0x00206138 lines 376-386 */
void CwsStrAllDelete(struct _CWS_WIN_W *win);                    /* 0x00206140-0x002061A4 lines 366-371 */
char CwsStrDelete(struct _CWS_WIN_W *win, int str_num);          /* 0x002061B0-0x00206218 lines 355-363 */
char CwsStrSetTex(struct _CWS_WIN_W *win, int str_num, int tex_id); /* 0x00206220-0x002062AC lines 341-351 */
char CwsStrSetFlag(struct _CWS_WIN_W *win, int str_num, unsigned int flag); /* 0x002062B0-0x0020633C lines 327-337 */
char CwsStrSetA(struct _CWS_WIN_W *win, int str_num, unsigned char a); /* 0x00206340-0x002063CC lines 312-322 */
char CwsStrSetBri(struct _CWS_WIN_W *win, int str_num, unsigned char bri); /* 0x002063D0-0x0020645C lines 298-308 */
char CwsStrSetCol(struct _CWS_WIN_W *win, int str_num, unsigned char col); /* 0x00206460-0x002064EC lines 285-295 */
char CwsStrSetFontType(struct _CWS_WIN_W *win, int str_num, int font_type); /* 0x002064F0-0x0020657C lines 272-282 */
char CwsStrSetPri(struct _CWS_WIN_W *win, int str_num, int z);   /* 0x00206580-0x0020660C lines 259-269 */
char CwsStrSetY(struct _CWS_WIN_W *win, int str_num, int y);     /* 0x00206610-0x0020669C lines 246-256 */
char CwsStrSetX(struct _CWS_WIN_W *win, int str_num, int x);     /* 0x002066A0-0x0020672C lines 233-243 */
char CwsStrSetStrightString(struct _CWS_WIN_W *win, unsigned char *string, int top_line, int cp_line_size); /* 0x00206730-0x00206884 lines 178-229 */
char CwsStrSetString(struct _CWS_WIN_W *win, int str_num, unsigned char *string); /* 0x00206890-0x00206978 lines 158-173 */
char CwsStrClear(struct _CWS_WIN_W *win, int str_num);           /* 0x00206980-0x00206A30 lines 139-154 */
char CwsStrSetStrightAll(struct _CWS_WIN_W *win, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string, int top_line, int cp_line_size); /* 0x00206A30-0x00206C18 lines 71-136 */
char CwsStrSetAll(struct _CWS_WIN_W *win, int str_num, int x, int y, int pri, unsigned char bri, unsigned char alpha, unsigned int flag, int type, unsigned char col, unsigned char *string); /* 0x00206C20-0x00206D80 lines 35-68 */
static struct _CWS_STR *GetStrFreeWork(void);                    /* 0x00206D80-0x00206E48 lines 12-31 */

#endif /* DDR_UNIT_src_common_cws_cws_str_c_H */
