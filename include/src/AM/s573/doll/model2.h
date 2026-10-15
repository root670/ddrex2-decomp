/*
 * C:\work\usam2\src\AM\s573\doll\model2.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x0024A1B0-0x0024C308
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _GsCOORDINATE2; struct one_motion_w; struct dancer_model_w; struct _tag_cFilepackData;
struct dancer_motion_w;

/* types (5) */
struct dancer_model_w {   // size 0x720
    /* 0x000 */ struct {   // size 0x14
        /* 0x000 */ unsigned int attribute;               // 0x4
        /* 0x004 */ _GsCOORDINATE2 *coord2;               // 0x4
        /* 0x008 */ unsigned int *tmd;                    // 0x4
        /* 0x00C */ unsigned int *packet;                 // 0x4
        /* 0x010 */ unsigned int id;                      // 0x4
    } obj[30];
    /* 0x258 */ int entry[17];                        // 0x44
    /* 0x29C */ unsigned int model;                   // 0x4
    /* 0x2A0 */ unsigned int *packet;                 // 0x4
    /* 0x2A4 */ unsigned int *header;                 // 0x4
    /* 0x2A8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x2B0 */ float m[17][4][4];                    // 0x440
    /* 0x6F0 */ unsigned int *prim_tbl;               // 0x4
    /* 0x6F4 */ float dist;                           // 0x4
    /* 0x6F8 */ float scale;                          // 0x4
    /* 0x6FC */ float sscale;                         // 0x4
    /* 0x700 */ float x;                              // 0x4
    /* 0x704 */ float y;                              // 0x4
    /* 0x708 */ float z;                              // 0x4
    /* 0x70C */ short winkcnt;                        // 0x2
    /* 0x70E */ unsigned short chara;                 // 0x2
    /* 0x710 */ char hide;                            // 0x1
    /* 0x711 */ unsigned char id;                     // 0x1
    /* 0x712 */ unsigned char pad[2];                 // 0x2
    /* 0x714 */ struct {   // size 0x10
        /* 0x000 */ float x;                              // 0x4
        /* 0x004 */ float y;                              // 0x4
        /* 0x008 */ float z;                              // 0x4
        /* 0x00C */ unsigned int disp : 1;                // bits 0..0
    } *einf;
    /* 0x718 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

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

struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
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

/* variables (14) */
static union @anon10 *wk;                                        /* @0x002A25E8 size 0x4 */
static union @anon10 *lw;                                        /* @0x002A25EC size 0x4 */
static float (*tmp)[4];                                          /* @0x002A25F0 size 0x4 */
static float (*rmat)[4][4];                                      /* @0x002A2600 size 0x4 */
static _GsCOORDINATE2 **DSTACK;                                  /* @0x002A2604 size 0x4 */
static float lc[2][4];                                           /* @0x0028B110 size 0x20 */
static float lct[2][4];                                          /* @0x0028B130 size 0x20 */
struct @anon4 *dancer_ctrl_w;                                    /* @0x002A2608 size 0x4 */
union @anon10 *sharenk;                                          /* @0x002A2ABC size 0x4 */
struct @anon20 *gs3d;                                            /* @0x002A25C8 size 0x4 */
float shadow_bri;                                                /* @0x002A2AB0 size 0x4 */
union @anon10 *sharewk;                                          /* @0x002A2AB8 size 0x4 */
unsigned int *prim_tbl;                                          /* @0x002A2AB4 size 0x4 */
struct @anon7 *dancer_data_w;                                    /* @0x002A2AC4 size 0x4 */

/* functions defined (12) */
static void NormCulcG3US(struct @anon13 *hp, struct @anon6 *rp); /* 0x0024A1B0-0x0024A550 lines 709-751 */
static void NormCulcG3U(struct @anon13 *hp, struct @anon6 *rp);  /* 0x0024A550-0x0024A8DC lines 651-704 */
static void VertCulcU(struct @anon13 *hp, struct @anon6 *rp, float scalex, float scaley, float scalez); /* 0x0024A8E0-0x0024AD38 lines 593-646 */
static void drawGT3(struct @anon6 *rp, struct @anon8 *prp, int cull, unsigned int prmask); /* 0x0024AD40-0x0024B078 lines 527-588 */
static void drawGT3L(struct @anon6 *rp, struct @anon8 *prp, int cull, unsigned int prmask); /* 0x0024B080-0x0024B394 lines 460-522 */
static void drawG3core(struct @anon6 *rp, int cull, int r, int g, int b, unsigned int prmask); /* 0x0024B3A0-0x0024B57C lines 403-441 */
static void drawG3L(struct @anon6 *rp, int cull, unsigned int prmask); /* 0x0024B580-0x0024B764 lines 358-398 */
static void NMDSortObject5(dancer_model_w *mdl, struct @anon21 *objp, int id, int render); /* 0x0024B770-0x0024BAFC lines 283-353 */
static void nmd_model_disp(dancer_model_w *mdl, struct @anon21 *obj_p, int id, int render); /* 0x0024BB00-0x0024BD28 lines 235-278 */
void draw_dancer_model(int pid, int toon);                       /* 0x0024BD30-0x0024BFAC lines 187-230 */
static void PsGsGetLs(_GsCOORDINATE2 *coord, float (*mat)[4]);   /* 0x0024BFB0-0x0024C0FC lines 146-179 */
void pre_draw_dancer_model(int pid);                             /* 0x0024C100-0x0024C308 lines 100-126 */
