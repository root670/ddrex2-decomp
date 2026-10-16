/* struct _EDSSYS_W -- 36 members, size 0xB00, layout 7c2ee8d63dcf.
 *
 * One definition, agreed by the 6 units that declare it: eds_select.c (DIE 0x3BB93).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSSYS_W *`.
 *
 * declared by: eds_select.c (DIE 0x3BB93), eds_main.c (DIE 0x446A1), eds_win.c (DIE 0x4EDAA), eds_aid.c (DIE 0x53106), eds_break.c (DIE 0x59CF7), eds_record.c (DIE 0x5D0EC)
 */
#ifndef DDR_types__EDSSYS_W_H
#define DDR_types__EDSSYS_W_H

struct _EDSBREAK_W;
struct _EDSRECORD_W;
struct _EDSWIN_W;
struct _GAME_MODE_W;

#include "types/_EDSBREAK_W.h"
#include "types/_EDSRECORD_W.h"
#include "types/_EDSWIN_W.h"
#include "types/_GAME_MODE_W.h"

struct _EDSSYS_W {   // size 0xB00
    /* 0x000 */ void (*MainFunc)();                   // 0x4
    /* 0x004 */ struct _GAME_MODE_W *game_w;          // 0x4
    /* 0x008 */ struct _EDSWIN_W *work[34];           // 0x88
    /* 0x090 */ float sys_timer;                      // 0x4
    /* 0x094 */ int all_music_max;                    // 0x4
    /* 0x098 */ int music_max;                        // 0x4
    /* 0x09C */ int SystemFlag;                       // 0x4
    /* 0x0A0 */ int GameFlag;                         // 0x4
    /* 0x0A4 */ char Sorting;                         // 0x1
    /* 0x0A5 */ char MainStep;                        // 0x1
    /* 0x0A6 */ char TexInitStep;                     // 0x1
    /* 0x0A7 */ char WarningStep;                     // 0x1
    /* 0x0A8 */ char MenuStep;                        // 0x1
    /* 0x0A9 */ char ReturnGStep;                     // 0x1
    /* 0x0AA */ char OrderStep;                       // 0x1
    /* 0x0AB */ char RecordStep;                      // 0x1
    /* 0x0AC */ char MenuCursor;                      // 0x1
    /* 0x0AD */ char MenuStCursor[12];                // 0xC
    /* 0x0B9 */ char OrderCursorX;                    // 0x1
    /* 0x0BA */ unsigned char OrderCursorY;           // 0x1
    /* 0x0BB */ unsigned char OldOrderMusic;          // 0x1
    /* 0x0BC */ char OrderTopID;                      // 0x1
    /* 0x0BD */ unsigned char PlayTbl[69];            // 0x45
    /* 0x102 */ // 0x2 bytes padding
    /* 0x104 */ int Level;                            // 0x4
    /* 0x108 */ int Combo;                            // 0x4
    /* 0x10C */ int ComboMax;                         // 0x4
    /* 0x110 */ int StageMax;                         // 0x4
    /* 0x114 */ unsigned int ScoreMax[2];             // 0x8
    /* 0x11C */ short Gauge;                          // 0x2
    /* 0x11E */ char BreakStage;                      // 0x1
    /* 0x11F */ unsigned char HelpAlpha;              // 0x1
    /* 0x120 */ unsigned char CurAlpha;               // 0x1
    /* 0x121 */ unsigned char MusicNo[69];            // 0x45
    /* 0x166 */ // 0x2 bytes padding
    /* 0x168 */ struct _EDSWIN_W Obj[34];             // 0x990
    /* 0xAF8 */ struct _EDSRECORD_W rwork;            // 0x4
    /* 0xAFC */ struct _EDSBREAK_W bwork;             // 0x4
};

#endif /* DDR_types__EDSSYS_W_H */
