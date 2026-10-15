/*
 * C:\work\usam2\src\AM\s573\doll\motion2.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0024D0E0-0x0024E2B4
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _GsCOORDINATE2; struct one_motion_w; struct dancer_motion_w;

/* types (3) */
struct _GsCOORDINATE2 {   // size 0x50
    /* 0x000 */ unsigned int flg;                     // 0x4
    /* 0x004 */ struct {   // size 0x20
        /* 0x000 */ short m[3][3];                        // 0x12
        /* 0x012 */ // 0x2 bytes padding
        /* 0x014 */ int t[3];                             // 0xC
    } coord;
    /* 0x024 */ struct {   // size 0x20
        /* 0x000 */ short m[3][3];                        // 0x12
        /* 0x012 */ // 0x2 bytes padding
        /* 0x014 */ int t[3];                             // 0xC
    } workm;
    /* 0x044 */ struct {   // size 0x28
        /* 0x000 */ struct {   // size 0x10
            /* 0x000 */ int vx;                               // 0x4
            /* 0x004 */ int vy;                               // 0x4
            /* 0x008 */ int vz;                               // 0x4
            /* 0x00C */ int pad;                              // 0x4
        } scale;
        /* 0x010 */ struct {   // size 0x8
            /* 0x000 */ short vx;                             // 0x2
            /* 0x002 */ short vy;                             // 0x2
            /* 0x004 */ short vz;                             // 0x2
            /* 0x006 */ short pad;                            // 0x2
        } rotate;
        /* 0x018 */ struct {   // size 0x10
            /* 0x000 */ int vx;                               // 0x4
            /* 0x004 */ int vy;                               // 0x4
            /* 0x008 */ int vz;                               // 0x4
            /* 0x00C */ int pad;                              // 0x4
        } trans;
    } *param;
    /* 0x048 */ _GsCOORDINATE2 *super;                // 0x4
    /* 0x04C */ _GsCOORDINATE2 *sub;                  // 0x4
};

struct one_motion_w {   // size 0x14
    /* 0x000 */ int m_id;                             // 0x4
    /* 0x004 */ int frame;                            // 0x4
    /* 0x008 */ unsigned int state;                   // 0x4
    /* 0x00C */ struct {   // size 0xC
        /* 0x000 */ unsigned int size;                    // 0x4
        /* 0x004 */ unsigned short nbparts;               // 0x2
        /* 0x006 */ unsigned short nbframe;               // 0x2
        /* 0x008 */ struct {   // size 0xC
            /* 0x000 */ unsigned char id;                     // 0x1
            /* 0x001 */ unsigned char format;                 // 0x1
            /* 0x002 */ unsigned char hastrans;               // 0x1
            /* 0x003 */ unsigned char parent_id;              // 0x1
            /* 0x004 */ unsigned int nbwave;                  // 0x4
            /* 0x008 */ struct {   // size 0x8
                /* 0x000 */ unsigned char kind;                   // 0x1
                /* 0x001 */ unsigned char pad[3];                 // 0x3
                /* 0x004 */ struct {   // size 0x4
                    /* 0x000 */ unsigned short shift_bit;             // 0x2
                    /* 0x002 */ struct {   // size 0x2
                        /* 0x000 */ unsigned short offset;                // 0x2
                    } tbl[1];
                } data;
            } **offset;
        } **offset;
    } *mdata;
    /* 0x010 */ int weight;                           // 0x4
};

struct dancer_motion_w {   // size 0x5F8
    /* 0x000 */ _GsCOORDINATE2 coord2[18];            // 0x5A0
    /* 0x5A0 */ unsigned char model_change[16];       // 0x10
    /* 0x5B0 */ int cur_dance_id;                     // 0x4
    /* 0x5B4 */ int last_dance_id;                    // 0x4
    /* 0x5B8 */ one_motion_w motion[2];               // 0x28
    /* 0x5E0 */ struct {   // size 0x10
        /* 0x000 */ char magic[2];                        // 0x2
        /* 0x002 */ short nbmdt;                          // 0x2
        /* 0x004 */ int reserve;                          // 0x4
        /* 0x008 */ struct {   // size 0x8
            /* 0x000 */ char *name;                           // 0x4
            /* 0x004 */ struct {   // size 0xC
                /* 0x000 */ unsigned int size;                    // 0x4
                /* 0x004 */ unsigned short nbparts;               // 0x2
                /* 0x006 */ unsigned short nbframe;               // 0x2
                /* 0x008 */ struct {   // size 0xC
                    /* 0x000 */ unsigned char id;                     // 0x1
                    /* 0x001 */ unsigned char format;                 // 0x1
                    /* 0x002 */ unsigned char hastrans;               // 0x1
                    /* 0x003 */ unsigned char parent_id;              // 0x1
                    /* 0x004 */ unsigned int nbwave;                  // 0x4
                    /* 0x008 */ struct {   // size 0x8
                        /* 0x000 */ unsigned char kind;                   // 0x1
                        /* 0x001 */ unsigned char pad[3];                 // 0x3
                        /* 0x004 */ struct {   // size 0x4
                            /* 0x000 */ unsigned short shift_bit;             // 0x2
                            /* 0x002 */ struct {   // size 0x2
                                /* 0x000 */ unsigned short offset;                // 0x2
                            } tbl[1];
                        } data;
                    } **offset;
                } **offset;
            } *offset;
        } motion[1];
    } *mpack;
    /* 0x5E4 */ int cur_p_counter;                    // 0x4
    /* 0x5E8 */ int last_p_counter;                   // 0x4
    /* 0x5EC */ int dance_class;                      // 0x4
    /* 0x5F0 */ float adj_x;                          // 0x4
    /* 0x5F4 */ float adj_z;                          // 0x4
};

/* variables (1) */
int state;                                                       /* @0x002A2AC0 size 0x4 */

/* functions defined (8) */
static int decodeMimeParam(struct @anon1 *md, _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x0024D0E0-0x0024D50C lines 566-629 */
static int mimeAnimation_local(_GsCOORDINATE2 *dst, _GsCOORDINATE2 *src1, _GsCOORDINATE2 *src2, int hastrans, short rot1, short rot2, short w1, short w2); /* 0x0024D510-0x0024D724 lines 496-561 */
static int mimeAnimation(_GsCOORDINATE2 *coord2, struct @anon1 *md1, int frame1, struct @anon1 *md2, int frame2, int pidx, int weight); /* 0x0024D730-0x0024D9D8 lines 418-493 */
static void decodeRotateFormat(struct @anon7 *m, struct @anon9 *trans, struct @anon10 *rotate); /* 0x0024D9E0-0x0024DB20 lines 379-409 */
static void decodeVectorFormat(struct @anon7 *mm, struct @anon9 *trans, struct @anon10 *dir, short rotate); /* 0x0024DB20-0x0024DD0C lines 273-357 */
static short decodeBody(struct @anon8 *ptr, int frame);          /* 0x0024DD10-0x0024DE20 lines 199-235 */
static int decodeAnimation(struct @anon1 *md, _GsCOORDINATE2 *coord2, int idx, int frame); /* 0x0024DE20-0x0024E144 lines 81-165 */
void dancer_motion_decode(dancer_motion_w *dancer_motion_w);     /* 0x0024E150-0x0024E2B4 lines 33-70 */
