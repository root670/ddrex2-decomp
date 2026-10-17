/* src/sys/sys_demo.c -- the demo work object and the setters that fill it in.
 *
 * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file (rendered into
 * include/src/sys/sys_demo.h) plus the two functions' disassembly.  The statement line
 * numbers are evidence too -- the promotion rule compares this file's .line bytes with
 * retail -- so nothing is re-wrapped away from the retail lines 54 (sysDemoSet) and 80-81
 * (sysDemoSetMainLoopBreakRequest).  That gap is retail's own: its file carried 25 lines
 * between the two definitions that this reconstruction has no statement to fill (the unit
 * declares exactly these two functions and one global), so the space below is comment.
 *
 * The generated header spells the tag `_tag_SYS_DEMO_WORK` bare, which is C++ syntax, so
 * this C unit writes `struct` in front; the anonymous inner struct has no name in DWARF,
 * so it is spelled out here, member for member, in the order the offsets give.
 *
 * Neither function makes a call: each is one store, so neither needs a name that the DWARF
 * does not carry (see config/ddrex2p/borrowed_symbols.txt for the ones that do). */

struct _tag_SYS_DEMO_WORK {
    int mode;
    int inactive_flag;
    int inactive_counter;
    int gameplay_flag;
    int gameplay_counter;
    int end_screen_request;
    int main_loop_break_request;
    struct {
        unsigned int lsn;
        unsigned int size;
        char name[16];
        unsigned char date[8];
        unsigned int flag;
    } cdl_file;
    unsigned short language;
    unsigned short aspect;
    unsigned short playmode;
    unsigned short to_inactive;
    unsigned short to_gameplay;
    unsigned short mediatype;
    unsigned short masterVolScale;
    unsigned short dirSector;
    int why;
};

/* The work object every other unit of the demo reads: this unit is where it is set, and the
 * demo loop's own file is where it is read back.  It lives in `.bss` in retail, so nothing
 * here contributes an image byte -- only the DIE that names it. */
struct _tag_SYS_DEMO_WORK *pdemo;

/* The setter callers use to hand this unit the work object.  Its one store needs no load of
 * the global, so `pdemo = p` is a single `sw` -- which the scheduler puts in the `jr ra`
 * delay slot, leaving the whole body on one retail line.  Retail's statement list holds one
 * entry for this function, at 54, so the statement and the closing brace share that line:
 * written on two lines, the closing brace's line would own the `jr` and move the entry. */
void sysDemoSet(struct _tag_SYS_DEMO_WORK *p) { pdemo = p; }

/* ---------------------------------------------------------------------------
 * sysDemoSetMainLoopBreakRequest -- the one field of the work object that the demo's own
 * loop polls to leave its frame.  It is a store to a field of the object, so unlike the
 * setter above it needs the object's address first: one `lw` of the global out of `$gp`,
 * then the field store -- and the store again lands in the `jr ra` delay slot.
 *
 * That is why this function's line table has two entries and not one: the load is the
 * statement's own instruction and keeps line 80, while the branch and everything in its
 * delay slot belong to the closing brace on 81.  The lines below are spaced so that the
 * statement sits on 80 and the brace on 81; the comment block is retail's own gap between
 * this function and the one above (see the note at the top of the file).
 *
 * Nothing else belongs to this unit.  What the demo's loop does with
 * `main_loop_break_request` -- clear it, count frames, hand control back -- is other
 * translation units' code: the DWARF for this file carries two functions and the one
 * global, and no statement of ours could be added here without moving a retail line and
 * failing the `.line` gate that pins them.
 *
 * The field's offset is 0x18, which is what makes the store `sw a0,24(v1)` rather than a
 * store to a shorter-reached member: the seven fields above it are four bytes each, and
 * the setter above is what fills the object in the first place.
 * --------------------------------------------------------------------------- */

void sysDemoSetMainLoopBreakRequest(int val) {
    pdemo->main_loop_break_request = val;
}
