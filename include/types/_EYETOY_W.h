/* struct _EYETOY_W -- 42 members, size 0x2DC, layout 3bb50dfe6e0d.
 *
 * One definition, agreed by the 5 units that declare it: eye_system.c (DIE 0x497AF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EYETOY_W *`.
 *
 * declared by: eye_system.c (DIE 0x497AF), eye_ref.c (DIE 0x50860), bk_disp.c (DIE 0xE7CC5), freeplay.c (DIE 0x11BCC6), fp_hand.c (DIE 0x20173F)
 */
#ifndef DDR_types__EYETOY_W_H
#define DDR_types__EYETOY_W_H

struct _DOUBLE_DISP_W;
struct _eRECT;
struct sceImage;

#include "types/_DOUBLE_DISP_W.h"
#include "types/_eRECT.h"
#include "types/sceImage.h"

struct _EYETOY_W {   // size 0x2DC
    /* 0x000 */ unsigned char step[4];                // 0x4
    /* 0x004 */ unsigned int status;                  // 0x4
    /* 0x008 */ int gStatus;                          // 0x4
    /* 0x00C */ int gSteadyCount;                     // 0x4
    /* 0x010 */ int code;                             // 0x4
    /* 0x014 */ int counter;                          // 0x4
    /* 0x018 */ unsigned int di_flg;                  // 0x4
    /* 0x01C */ int split_num;                        // 0x4
    /* 0x020 */ struct _eRECT window;                 // 0x10
    /* 0x030 */ struct _eRECT move_window;            // 0x10
    /* 0x040 */ int move_timer;                       // 0x4
    /* 0x044 */ int position_z;                       // 0x4
    /* 0x048 */ unsigned char r;                      // 0x1
    /* 0x049 */ unsigned char g;                      // 0x1
    /* 0x04A */ unsigned char b;                      // 0x1
    /* 0x04B */ unsigned char alpha;                  // 0x1
    /* 0x04C */ unsigned char salpha;                 // 0x1
    /* 0x04D */ // 0x3 bytes padding
    /* 0x050 */ int colani_range;                     // 0x4
    /* 0x054 */ int colani_speed;                     // 0x4
    /* 0x058 */ char colani_type;                     // 0x1
    /* 0x059 */ unsigned char colani_r;               // 0x1
    /* 0x05A */ unsigned char colani_g;               // 0x1
    /* 0x05B */ unsigned char colani_b;               // 0x1
    /* 0x05C */ unsigned char old_colani_r;           // 0x1
    /* 0x05D */ unsigned char old_colani_g;           // 0x1
    /* 0x05E */ unsigned char old_colani_b;           // 0x1
    /* 0x05F */ // 0x1 bytes padding
    /* 0x060 */ unsigned int def_flag;                // 0x4
    /* 0x064 */ unsigned int mem_set_addr;            // 0x4
    /* 0x068 */ unsigned int mem_last_addr;           // 0x4
    /* 0x06C */ int check_frame;                      // 0x4
    /* 0x070 */ int check_depth;                      // 0x4
    /* 0x074 */ int check_pdf;                        // 0x4
    /* 0x078 */ int imagenum;                         // 0x4
    /* 0x07C */ int old_pict_num;                     // 0x4
    /* 0x080 */ struct sceImage tmprgba;              // 0x18
    /* 0x098 */ struct sceImage check_tex;            // 0x18
    /* 0x0B0 */ struct sceImage check_tex2;           // 0x18
    /* 0x0C8 */ struct sceImage lum_hit[3];           // 0x48
    /* 0x110 */ struct _DOUBLE_DISP_W screen[2];      // 0x1C0
    /* 0x2D0 */ void *buff;                           // 0x4
    /* 0x2D4 */ void *cam_buf;                        // 0x4
    /* 0x2D8 */ void *s_capt;                         // 0x4
};

#endif /* DDR_types__EYETOY_W_H */
