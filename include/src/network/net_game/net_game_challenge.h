/*
 * C:\work2\usaex2\src\network\net_game\net_game_challenge.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0025EDB0-0x0025F3E0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
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

/* anonymous types (2) */

/* anon_4_146 -- @anon4, 0x4 bytes, net_game_challenge.c (DIE 0x26F35B) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_4_146;

/* anon_5_146 -- @anon5, 0x10 bytes, net_game_challenge.c (DIE 0x2706C8) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_4_146 x0;                        // 0x4
    /* 0x004 */ anon_4_146 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_5_146;


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
