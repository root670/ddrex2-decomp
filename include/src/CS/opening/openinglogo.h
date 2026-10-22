/*
 * C:\work2\usaex2\src\CS\opening\openinglogo.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x001CEF00-0x001CF1A4
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
#ifndef DDR_UNIT_src_CS_opening_openinglogo_c_H
#define DDR_UNIT_src_CS_opening_openinglogo_c_H

#include "types/_tag_cOpening.h"
#include "types/_tag_cOpeninglogo.h"

/* anonymous types (3) */

/* anon_0_25 -- @anon0, 0x48 bytes, openinglogo.c (DIE 0x36CFB) */
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
} anon_0_25;

/* anon_2_25 -- @anon2, 0x4 bytes, openinglogo.c (DIE 0x371A5) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_2_25;

/* anon_1_25 -- @anon1, 0x24 bytes, openinglogo.c (DIE 0x37011) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_2_25 x0;                         // 0x4
    /* 0x004 */ anon_2_25 y0;                         // 0x4
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
} anon_1_25;


/* variables (4) */
struct _tag_cOpeninglogo *pOpeninglogo;                          /* @0x002DD9A0 size 0x4 */
static int logo_tex_num[1];                                      /* @0x002DE4C0 size 0x4 */
struct _tag_cOpening *pOpening;                                  /* @0x002DA1E8 size 0x4 */
static struct _tag_cOpeninglogo _pOpeninglogo;                   /* @0x00712670 size 0x1C */

/* functions defined (4) */
int Update_Openinglogo(void);                                    /* 0x001CEF00-0x001CEF18 lines 182-190 */
int View_Openinglogo(void);                                      /* 0x001CEF20-0x001CF048 lines 150-176 */
int Control_Openinglogo(void);                                   /* 0x001CF050-0x001CF140 lines 83-146 */
int Init_Openinglogo(void);                                      /* 0x001CF140-0x001CF1A4 lines 60-79 */

#endif /* DDR_UNIT_src_CS_opening_openinglogo_c_H */
