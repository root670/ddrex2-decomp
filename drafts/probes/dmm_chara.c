/* src/CS/dancemaster/dmm_chara.c -- WIP, does not promote (see below and
 * .superpowers/sdd/2026-10-15-m3-promotion-loop/reports/unit-j-report.md).
 *
 * Reconstructed from orig/SLUS_211.74's DWARF 1 records (rendered into
 * include/src/CS/dancemaster/dmm_chara.h) and the function's split under
 * asm/nonmatchings/main/.  Three findings are what stop this unit, and none of them is
 * the logic of the C:
 *
 * 1. The types .debug block is 0x67A0 bytes where retail's pin is 0x6389, and the DIE
 *    sequences do not correspond: retail's declaration CU records named aggregates the
 *    generated header renders as this unit's own anonymous structs (retail: `play_w`
 *    with its ~400 members, `sequence`, `note_status`, ...; here: `anon_23_109`,
 *    `anon_14_109`, ...).  MWCC emits a type DIE for a type the source mentions, so the
 *    block is a function of the *spellings* the C uses, not of the C's statements.
 * 2. `g_game_w` is 0xACDC4 bytes and its field `last_data_addr` sits at 0xAB4E8, so the
 *    C that reaches it the way retail's bytes do (`lui $1,%hi(0x006B2F58)` + `sw
 *    %lo(...)($1)`) makes MWCC emit a `lui` whose high half carries that offset, which
 *    `compile.py`'s `_pairs` refuses by design ("the address at 0x... has 0xB in its high
 *    half ... cannot be recomputed from g_game_w").  The spelling used below names the
 *    address directly, which resolves -- but costs one more instruction than retail's
 *    folded pair (`lui`+`ori` instead of `lui`+`sw`), so .text is 0x1C4 against retail's
 *    0x1D0.
 * 3. Retail's .text carries four `nop`s (0x0023F3FC, 0x0023F40C, 0x0023F41C, 0x0023F484)
 *    at case-label lines 67, 69, 76 and 90, each where the preceding block ends 4 mod 8.
 *    No probe reproduced them: case-label alignment is not a rule this build applies
 *    (measured on four shapes whose labels land 4 mod 8 with no pad), and empty
 *    statements, empty blocks, empty `if`/`else`, dead expressions, `goto`, unused
 *    labels, `do{}while(0)`, `while(0);` and the 2.4-001213 build all produce no `nop`.
 * 4. The inner switch: retail's rows put `dmm_freeplay_step()`'s call on line 65 and its
 *    dispatch on line 66, and the dispatch compares the call's result in $2 directly --
 *    so the value crosses a statement boundary, and the function's DWARF nevertheless
 *    records exactly one local (`step_type`, $s0, which the call never writes: s0 is only
 *    ever set to 10 and 8).  Every C shape that gets the two lines measured here
 *    (`r = f9(); switch (r)`) adds a local DIE with location $2, and every shape that
 *    keeps the DWARF clean puts the call and the dispatch on one line.
 */

/* * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file (rendered into
 * include/src/CS/dancemaster/dmm_chara.h) and the function's split under
 * asm/nonmatchings/main/.  The statement lines are evidence, so the file uses `#line` to
 * put every statement on retail's own line.
 */
#include "src/CS/dancemaster/dmm_chara.h"

/* g_game_w.last_data_addr: 0x00607A70 + 0xAB4E8.  Retail reaches it with the plain
 * %hi/%lo pair, and a field offset that large is one the promotion path cannot read
 * back out of an object, so the address is named directly instead. */
#define DMM_LAST_DATA (*(unsigned char **)0x6B2F58)

anon_7_109 *dmm_get_work(void);
void func_00128600(anon_7_109 *work);
void gsInit3d(void);
void dmm_freeplay_chara_init(unsigned char *addr);
void func_0012CD70(unsigned char *addr);
int dmm_freeplay_chara_load(void);
int dmm_freeplay_step(void);
void dmm_freeplay_chara_finish(int *id_1, int *id_2);
void dmm_set_step(int step);

/* The case-0 body: retail's statement list gives it one line, and its pointer is live
 * across two calls, so it is an inlined function -- an inlined body's statements all take
 * the call's line, and its locals carry no DIE in the caller. */
static inline void dmm_chara_work_init(anon_7_109 *work) {
    anon_7_109 *w = dmm_get_work();
    DMM_LAST_DATA = (unsigned char *)0xFC29D0;
    func_00128600(work);
    gsInit3d();
    w->chara_work_addr = DMM_LAST_DATA;
    dmm_freeplay_chara_init(w->chara_work_addr);
    func_0012CD70(DMM_LAST_DATA);
}

/* The case-10 body: same shape, one line, pointer live across a call. */
static inline void dmm_chara_finish(void) {
    anon_7_109 *w = dmm_get_work();
    dmm_freeplay_chara_finish(&w->dancer[0], &w->dancer[1]);
    if (w->dancer[0] == 0x2D && w->dancer[1] == 0x2D) w->is_disp_dancer = 0;
}

#line 33
void dmm_chara(anon_7_109 *work) {
#line 34
    int step_type = 10;
#line 37
    switch (work->step) {
#line 40
    case 0:
#line 41
        dmm_chara_work_init(work);
#line 42
        work->step++;
#line 43
        break;
#line 44
    case 1:
#line 47
        if (dmm_freeplay_chara_load()) {
#line 56
            work->free_mem_addr = DMM_LAST_DATA;
#line 59
            work->step++;
#line 60
        }
#line 61
        break;
#line 62
    case 2:
#line 65
        step_type = dmm_freeplay_step();
#line 66
        switch (step_type) {
#line 67
        case 1:
#line 68
            work->step = step_type;
#line 69
        case 2:
#line 70
            work->step = 20;
#line 72
            break;
#line 73
        }
#line 74
        break;
#line 76
    case 10:
#line 77
        dmm_chara_finish();
#line 78
        work->step++;
#line 79
        break;
#line 82
    case 11:
#line 82
        work->next_cursor = 2;
#line 83
        step_type = 8;
#line 84
        break;
#line 87
    case 20:
#line 88
        work->step++;
#line 89
        break;
#line 90
    case 21:
#line 91
        work->next_cursor = 2;
#line 92
        dmm_set_step(9);
#line 93
        return;
#line 95
    }
#line 99
    dmm_set_step(step_type);
#line 101
}
