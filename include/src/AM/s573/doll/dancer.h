/*
 * C:\work\usam2\src\AM\s573\doll\dancer.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x0024E9B0-0x0024F590
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _GsCOORDINATE2; struct one_motion_w; struct dancer_model_w; struct dancer_motion_w;
struct _tag_cFilepackData;

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

struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
};

/* variables (6) */
struct @anon3 *dancer_ctrl_w;                                    /* @0x002A2608 size 0x4 */
static float rad[8][2];                                          /* @0x0028B300 size 0x40 */
static short ofs[8];                                             /* @0x0028B340 size 0x10 */
struct @anon15 *dancer_data_w;                                   /* @0x002A2AC4 size 0x4 */
struct @anon1 *gs3d;                                             /* @0x002A25C8 size 0x4 */
static struct @anon3 _dancer_ctrl_w;                             /* @0x006B6A60 size 0x70 */

/* functions defined (9) */
void ps2dancerSetFloor(int sw);                                  /* 0x0024E9B0-0x0024E9BC lines 421-422 */
void ps2dancerSetToon(int sw);                                   /* 0x0024E9C0-0x0024E9CC lines 416-417 */
void ps2dancerSetPlayCounter(int pid, int cur_p_counter);        /* 0x0024E9D0-0x0024E9FC lines 386-400 */
void ps2dancerSetAllPlayCounter(int cur_p_counter);              /* 0x0024EA00-0x0024EA34 lines 375-382 */
void ps2dancerAdjPos(int pid);                                   /* 0x0024EA40-0x0024EBA4 lines 331-353 */
static void draw_floor(int pid, int bri);                        /* 0x0024EBB0-0x0024EF4C lines 234-291 */
static int get_floor_cull(float y);                              /* 0x0024EF50-0x0024F014 lines 194-219 */
static void clear_zbuf(void);                                    /* 0x0024F020-0x0024F0E0 lines 146-180 */
void ps2dancerDispStep(void);                                    /* 0x0024F0E0-0x0024F590 lines 37-134 */
