/* src/CS/dancemaster/dmm_chara.c -- WIP, does not promote (see below and
 * .superpowers/sdd/2026-10-15-m3-promotion-loop/reports/unit-j-report.md).
 *
 * Reconstructed from orig/SLUS_211.74's DWARF 1 records (rendered into
 * include/src/CS/dancemaster/dmm_chara.h) and the function's split under
 * asm/nonmatchings/main/.  Measured under the settled pair (`3.0b38-030307 -c -lang c
 * -O3 -opt full -g`): .text and .line are byte-equal; one finding stops the unit, and
 * it is not the logic of the C.
 *
 * 1. .text and .line are byte-equal (0x1D0 / 0x152).  The four `nop`s retail carries at
 *    0x0023F3FC, 0x0023F40C, 0x0023F41C and 0x0023F484 are reproduced by this shape --
 *    they were never an alignment rule; they follow from the statement layout below.
 *    The `lui`/`%lo` pair for `g_game_w.last_data_addr` is reached through the named
 *    address below, which resolves and matches retail's folded store.
 * 2. The unit's types .debug block fits retail's pinned 0x6389.  The function's own
 *    .debug block does not: it is 0x16A bytes against retail's 0x151, 0x19 bytes too
 *    large, because the case-2 dispatch needs a value that crosses the line 65/66
 *    statement boundary.  Retail's rows put `dmm_freeplay_step()`'s call on line 65 and
 *    the dispatch on line 66, and the dispatch compares the call's result in $2
 *    directly, with constants in $3.  The only C that measures both the text and the
 *    two lines is a block-scoped temporary:
 *
 *        { int t = dmm_freeplay_step(); switch (t) { ... } }
 *
 *    The three forms measured, and what each gets right:
 *
 *    - `switch (dmm_freeplay_step())` (with case 1's `break;`): .text is byte-equal,
 *      but the call and the dispatch share line 65 (32 rows; retail's line 66 row is
 *      absent).  A macro-wrapped or inline-helper call does the same, at 66.
 *    - `step_type = dmm_freeplay_step(); switch (step_type)` (function scope, or the
 *      same two statements inside a block, with or without `register` on `step_type`):
 *      the 65/66 lines are right, but .text's first differing word is 0xF0 --
 *      `daddu $s0,$v0,$zero` here, `addiu $v1,$zero,2` in retail: the result is
 *      materialised into $s0 and compared against $v0 constants.  No extra DIE.
 *    - the block-scoped temporary above: .text and .line are byte-equal, but retail's
 *      function DIE records exactly one local, `step_type` ($s0), and the temp adds a
 *      local DIE (0x19 bytes) with location $2 (`register`, `const`, and shadowing
 *      `step_type` all keep the DIE; shadowing also breaks the allocation, -0x8).
 *
 *    So the residue is a true three-way trade-off: the value must cross a statement
 *    boundary (to get the 65/66 rows) without a declaration (to keep the DIE count),
 *    and no C spelling of this function does both.  The recorded .debug boundary
 *    requires retail's DIE count and so cannot absorb the extra local.
 * 3. All five installed builds were measured on this shape: only `3.0b38-030307` keeps
 *    the outer switch's 118 instructions (3.0-011126 is 0x10 short, 3.0.1/3.0.3 are
 *    0x8 short, 2.4-001213 is 0x8 large), so the settled pair is confirmed for this
 *    unit, not merely assumed.
 * 4. Case 1 has a `break;` on line 68 (retail's `b` at 0x114 with the store in its delay
 *    slot); the case-2 break and the switch's closing brace both sit on line 72, which
 *    is the line retail gives the surviving branch at 0x124.
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
void func_00128600(void);
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
    func_00128600();
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
    case 2: {
#line 65
        int dmm_t = dmm_freeplay_step();
#line 66
        switch (dmm_t) {
#line 67
        case 1:
#line 68
            work->step = step_type;
#line 68
            break;
#line 69
        case 2:
#line 70
            work->step = 20;
#line 72
            break;
#line 72
        }
#line 72
        break;
    }
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
        work->before_state = 2;
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
        work->before_state = 2;
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
