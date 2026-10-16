/*
 * C:\work2\usaex2\src\network\net_game\net_game_challenge.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0025EDB0-0x0025F3E0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_challenge_c_H
#define DDR_UNIT_src_network_net_game_net_game_challenge_c_H

#include "types/_NETWORK_W.h"
#include "types/_nsv_music_data_work.h"
#include "types/_nsv_rc_table_param_work.h"
#include "types/_tag_cMusicData.h"
#include "types/eval_w.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"
#include "types/oni_mode.h"

/* anonymous types (6) */

/* anon_0_146 -- @anon0, 0x14 bytes, net_game_challenge.c (DIE 0x26A867) */
struct anon_0_146 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_1_146 -- @anon1, 0x8 bytes, net_game_challenge.c (DIE 0x26AFE4) */
struct anon_1_146 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_2_146 -- @anon2, 0x4 bytes, net_game_challenge.c (DIE 0x26DDD3) */
struct anon_2_146 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_4_146 -- @anon4, 0x4 bytes, net_game_challenge.c (DIE 0x26F35B) */
union anon_4_146 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_5_146 -- @anon5, 0x10 bytes, net_game_challenge.c (DIE 0x2706C8) */
struct anon_5_146 {   // size 0x10
    /* 0x000 */ union anon_4_146 x0;                  // 0x4
    /* 0x004 */ union anon_4_146 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_3_146 -- @anon3, 0x184 bytes, net_game_challenge.c (DIE 0x26F067) */
struct anon_3_146 {   // size 0x184
    /* 0x000 */ struct anon_5_146 line_a[8];          // 0x80
    /* 0x080 */ struct anon_5_146 line_b[8];          // 0x80
    /* 0x100 */ struct anon_5_146 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};


/* variables (1) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (3) */
void NetToGameInit(struct _NETWORK_W *);                         /* @0x001EB260 */
void NetGameRCInit2(struct _NETWORK_W *);                        /* @0x0025DE50 */
void NetGameChallengeMain(struct _NETWORK_W *);                  /* @0x0025F030 */

/* functions defined (3) */
static int NetGameChallengeCourseConvert(struct _nsv_rc_table_param_work *net_course_data); /* 0x0025EDB0-0x0025F024 lines 326-427 */
static void NetGameChallengeMain(struct _NETWORK_W *netw);       /* 0x0025F030-0x0025F2B4 lines 55-245 */
void NetGameChallengeInit(struct _NETWORK_W *netw);              /* 0x0025F2C0-0x0025F3E0 lines 18-49 */

#endif /* DDR_UNIT_src_network_net_game_net_game_challenge_c_H */
