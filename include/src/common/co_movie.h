/*
 * C:\work2\usaex2\src\common\co_movie.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x002470F0-0x0024804C
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
#ifndef DDR_UNIT_src_common_co_movie_c_H
#define DDR_UNIT_src_common_co_movie_c_H

/* anonymous types (7) */

/* anon_0_119 -- @anon0, 0x10 bytes, co_movie.c (DIE 0x2094BA) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_0_119;

/* anon_1_119 -- @anon1, 0x1C bytes, co_movie.c (DIE 0x20960F) */
typedef struct {   // size 0x1C
    /* 0x000 */ int tbp;                              // 0x4
    /* 0x004 */ int psm;                              // 0x4
    /* 0x008 */ int cbp;                              // 0x4
    /* 0x00C */ int cpsm;                             // 0x4
    /* 0x010 */ int width;                            // 0x4
    /* 0x014 */ int height;                           // 0x4
    /* 0x018 */ int colors;                           // 0x4
} anon_1_119;

/* anon_2_119 -- @anon2, 0x4 bytes, co_movie.c (DIE 0x20975F) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_2_119;

/* anon_6_119 -- @anon6, 0x400 bytes, co_movie.c (DIE 0x209F64) */
typedef struct {   // size 0x400
    /* 0x000 */ unsigned int pix[256];                // 0x400
} anon_6_119;

/* anon_3_119 -- @anon3, 0x30 bytes, co_movie.c (DIE 0x20980A) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_0_119 *decTags[2];               // 0x8
    /* 0x008 */ anon_6_119 *cscBuff[2];               // 0x8
    /* 0x010 */ unsigned char *buf[2];                // 0x8
    /* 0x018 */ unsigned char *addr;                  // 0x4
    /* 0x01C */ float ct;                             // 0x4
    /* 0x020 */ float alpha;                          // 0x4
    /* 0x024 */ int kind;                             // 0x4
    /* 0x028 */ unsigned char step;                   // 0x1
    /* 0x029 */ unsigned char stat;                   // 0x1
    /* 0x02A */ unsigned char req;                    // 0x1
    /* 0x02B */ unsigned char disp_flg;               // 0x1
    /* 0x02C */ unsigned char play_flg;               // 0x1
    /* 0x02D */ unsigned char loop_flg;               // 0x1
    /* 0x02E */ // 0x2 bytes padding
} anon_3_119;

/* anon_4_119 -- @anon4, 0x68 bytes, co_movie.c (DIE 0x2099EE) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_2_119 x0;                        // 0x4
    /* 0x004 */ anon_2_119 y0;                        // 0x4
    /* 0x008 */ anon_2_119 x1;                        // 0x4
    /* 0x00C */ anon_2_119 y1;                        // 0x4
    /* 0x010 */ anon_2_119 x2;                        // 0x4
    /* 0x014 */ anon_2_119 y2;                        // 0x4
    /* 0x018 */ anon_2_119 x3;                        // 0x4
    /* 0x01C */ anon_2_119 y3;                        // 0x4
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
} anon_4_119;

/* anon_5_119 -- @anon5, 0x48 bytes, co_movie.c (DIE 0x209DA1) */
typedef struct {   // size 0x48
    /* 0x000 */ int width;                            // 0x4
    /* 0x004 */ int height;                           // 0x4
    /* 0x008 */ int frameCount;                       // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ long pts;                             // 0x8
    /* 0x018 */ long dts;                             // 0x8
    /* 0x020 */ unsigned long flags;                  // 0x8
    /* 0x028 */ long pts2nd;                          // 0x8
    /* 0x030 */ long dts2nd;                          // 0x8
    /* 0x038 */ unsigned long flags2nd;               // 0x8
    /* 0x040 */ void *sys;                            // 0x4
    /* 0x044 */ // 0x4 bytes padding
} anon_5_119;


/* variables (5) */
static unsigned char *co_mv_list[14];                            /* @0x002BF200 size 0x38 */
static int co_movie_is_avtive;                                   /* not allocated size 0x4 */
static anon_3_119 *mvw;                                          /* @0x002DDD28 size 0x4 */
anon_5_119 mpeg;                                                 /* @0x0032A5C0 size 0x48 */
static anon_3_119 co_movie_w;                                    /* @0x00722020 size 0x30 */

/* functions referenced (1) */
void co_movie_change_init_th(void *);                            /* @0x00247A70 */

/* functions defined (11) */
static void co_movie_SetDecTag(int id);                          /* 0x002470F0-0x002472A8 lines 646-738 */
static void co_movie_disp(unsigned int pri);                     /* 0x002472B0-0x002477E0 lines 447-630 */
static void co_movie_play(void);                                 /* 0x002477E0-0x00247944 lines 393-438 */
unsigned char co_movie_get_stat(void);                           /* 0x00247950-0x0024795C lines 376-377 */
void co_movie_change_start(void);                                /* 0x00247960-0x00247980 lines 366-370 */
int co_movie_restart(void);                                      /* 0x00247980-0x00247A04 lines 330-347 */
int co_movie_stop(void);                                         /* 0x00247A10-0x00247A68 lines 312-325 */
static void co_movie_change_init_th(void);                       /* 0x00247A70-0x00247AF0 lines 292-305 */
void co_movie_manage(void);                                      /* 0x00247AF0-0x00247D24 lines 214-287 */
int co_movie_set(int kind, unsigned char *addr);                 /* 0x00247D30-0x00247F90 lines 158-208 */
unsigned int co_movie_init(unsigned char *addr);                 /* 0x00247F90-0x0024804C lines 113-142 */

#endif /* DDR_UNIT_src_common_co_movie_c_H */
