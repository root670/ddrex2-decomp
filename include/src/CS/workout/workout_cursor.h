/*
 * C:\work2\usaex2\src\CS\workout\workout_cursor.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 7 functions, code 0x007FFE20-0x00800140
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_cursor_c_H
#define DDR_UNIT_src_CS_workout_workout_cursor_c_H

/* anonymous types (4) */

/* anon_0_239 -- @anon0, 0x28 bytes, workout_cursor.c (DIE 0x46BA3A) */
typedef struct {   // size 0x28
    /* 0x000 */ int pos_x;                            // 0x4
    /* 0x004 */ int pos_y;                            // 0x4
    /* 0x008 */ int depth_z;                          // 0x4
    /* 0x00C */ int cur_x;                            // 0x4
    /* 0x010 */ int cur_y;                            // 0x4
    /* 0x014 */ int item_x;                           // 0x4
    /* 0x018 */ int item_y;                           // 0x4
    /* 0x01C */ int dist_x;                           // 0x4
    /* 0x020 */ int dist_y;                           // 0x4
    /* 0x024 */ int counter;                          // 0x4
} anon_0_239;

/* anon_1_239 -- @anon1, 0x48 bytes, workout_cursor.c (DIE 0x46BBB5) */
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
} anon_1_239;

/* anon_3_239 -- @anon3, 0x4 bytes, workout_cursor.c (DIE 0x46BFCB) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_239;

/* anon_2_239 -- @anon2, 0x24 bytes, workout_cursor.c (DIE 0x46BE37) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_3_239 x0;                        // 0x4
    /* 0x004 */ anon_3_239 y0;                        // 0x4
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
} anon_2_239;


/* variables (1) */
anon_0_239 wo_cursor[2];                                         /* @0x008024F0 size 0x50 */

/* functions defined (7) */
void woCursorSet(int cno, unsigned int flag, int val);           /* 0x007FFE20-0x007FFE88 lines 154-162 */
int woCursorGet(int cno, unsigned int flag);                     /* 0x007FFE90-0x007FFED8 lines 137-145 */
void woCursorDec(int cno, unsigned int flag);                    /* 0x007FFEE0-0x007FFF50 lines 116-128 */
void woCursorInc(int cno, unsigned int flag);                    /* 0x007FFF50-0x007FFFC8 lines 94-106 */
void woCursorDraw(int cno);                                      /* 0x007FFFD0-0x008000E4 lines 57-75 */
void woCursorAct(int cno);                                       /* 0x008000F0-0x00800118 lines 44-46 */
void woCursorInit(int cno);                                      /* 0x00800120-0x00800140 lines 31-31 */

#endif /* DDR_UNIT_src_CS_workout_workout_cursor_c_H */
