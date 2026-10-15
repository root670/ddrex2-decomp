/*
 * C:\work\usam2\src\AM\s573\doll\dcamera.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x00247E00-0x0024982C
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

/* variables (4) */
struct @anon1 camera_w;                                          /* @0x006B4620 size 0x70 */
struct @anon15 *gs3d;                                            /* @0x002A25C8 size 0x4 */
struct @anon8 *dancer_data_w;                                    /* @0x002A2AC4 size 0x4 */
struct @anon6 *dancer_ctrl_w;                                    /* @0x002A2608 size 0x4 */

/* functions defined (11) */
static void camera_tst(struct @anon1 *cw);                       /* 0x00247E00-0x002483BC lines 410-425 */
struct @anon1 *GetDancerCameraW(void);                           /* 0x002483C0-0x002483CC lines 394-395 */
static void camera_ero(struct @anon1 *cw, dancer_model_w *mdl);  /* 0x002483D0-0x00248644 lines 319-339 */
static void camera_roll(struct @anon1 *cw);                      /* 0x00248650-0x00248A18 lines 280-314 */
static void camera_s03(struct @anon1 *cw, dancer_model_w *mdl);  /* 0x00248A20-0x00248DF0 lines 249-275 */
static void camera_s02(struct @anon1 *cw, dancer_model_w *mdl);  /* 0x00248DF0-0x00248F50 lines 215-244 */
static void camera_s01(struct @anon1 *cw, dancer_model_w *mdl);  /* 0x00248F50-0x00249194 lines 199-210 */
static int change_camera_type(struct @anon1 *cw, int nmea);      /* 0x002491A0-0x0024936C lines 128-156 */
void ps2dancerCameraStep(void);                                  /* 0x00249370-0x0024966C lines 96-123 */
int ps2dancerCameraPreStep(void);                                /* 0x00249670-0x00249720 lines 69-92 */
void ps2dancerCameraInit(float cx, float cy, float scale);       /* 0x00249720-0x0024982C lines 38-65 */
