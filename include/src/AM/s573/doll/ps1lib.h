/*
 * C:\work\usam2\src\AM\s573\doll\ps1lib.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0024E2C0-0x0024E9A8
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _GsCOORDINATE2;

/* types (1) */
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

/* functions defined (8) */
void LoadAverageShort12(struct @anon1 *v0, struct @anon1 *v1, int p0, int p1, struct @anon1 *v2); /* 0x0024E2C0-0x0024E33C lines 179-182 */
int VectorNormalSS(struct @anon1 *v0, struct @anon1 *v1);        /* 0x0024E340-0x0024E3F8 lines 161-172 */
void OuterProduct12(struct @anon2 *v0, struct @anon2 *v1, struct @anon2 *v2); /* 0x0024E400-0x0024E494 lines 153-156 */
struct @anon0 *TransposeMatrix(struct @anon0 *m0, struct @anon0 *m1); /* 0x0024E4A0-0x0024E500 lines 139-146 */
int ps1rcos(int a);                                              /* 0x0024E500-0x0024E554 lines 128-130 */
int ps1rsin(int a);                                              /* 0x0024E560-0x0024E5B4 lines 123-125 */
struct @anon0 *PsRotMatrix(struct @anon1 *r, struct @anon0 *m);  /* 0x0024E5C0-0x0024E908 lines 47-81 */
void GsInitCoordinate2(_GsCOORDINATE2 *super, _GsCOORDINATE2 *base); /* 0x0024E910-0x0024E9A8 lines 34-42 */
