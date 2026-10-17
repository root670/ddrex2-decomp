/* src/CS/lang.c -- the message-language tables and the accessor the rest of the game calls.
 *
 * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file (rendered into
 * include/src/CS/lang.h) plus mesGetLanguage01's disassembly.  The statement line numbers
 * are evidence too -- the promotion rule compares this file's .line bytes with retail -- so
 * nothing is re-wrapped away from the retail lines 118-119, 121-122, 127 and 128.
 *
 * The file does not promote yet.  Two mismatches remain, both measured against retail's own
 * pinned chunks with `tools/toolchain/compile.py`'s placement -- the same bytes the gate
 * compares -- and each is a fact about the source shape or the compiler, not the game:
 *
 *  - `.line` and `.text` pull apart.  Retail's statement list has a record for each clamp
 *    store (lines 119 and 122), which only the `if` shape below produces: as a conditional
 *    expression one statement owns all four clamp instructions and `.line` is 0x30 where
 *    retail pins 0x4E.  With the `if` shape, `2.4-001213` reproduces `.line` byte for byte
 *    and the function's `.debug` block too, but schedules the second test into the first
 *    branch's delay slot (0x1C4724, 0x1C4728) and then orders the return's address and
 *    loads differently (0x1C4744, 0x1C4748, 0x1C4750, 0x1C4754); every other installed
 *    build collapses the function to 0x34 or 0x3C bytes.  The conditional-expression shape
 *    has retail's `.text` and three line records fewer.
 *
 *  - The `.debug` types block is the right length and the wrong bytes: the nine table DIEs
 *    come out in an order this unit's retail DWARF does not have.  The declarations below
 *    are in retail's variable DIE order (an initialized static is emitted where it is
 *    declared) and that part matches; the *array* DIEs do not follow the declaration order
 *    at all -- four one-line probes of distinct array types came out in neither declaration
 *    nor reverse-declaration order -- so this is the file-scope-table part of the `mes_*`
 *    debug-order class and needs a source or compiler answer, not another declaration
 *    order.  Measurements:
 *    .superpowers/sdd/2026-10-15-m3-promotion-loop/reports/draft-finish-report.md.
 *
 * The nine tables are file-scope statics: CodeWarrior writes their DIEs as locals with a
 * location, and two of them (`mesLanguageOK`, `mesLanguageCANCEL`) carry address 0 in retail
 * -- declared but never allocated, which is why they are in config/ddrex2p/unplaced_symbols.txt
 * and not in this target's split.  The `= { 0 }` initializers are not retail's values: what
 * the tables contain lives in retail's `.data`, which this build does not reconstruct yet
 * (rule 9), and a promoted unit links only its `.text`. */

static unsigned char *mesLanguageJAPANESE[6] = { 0 };
static unsigned char *mesLanguageENGLISH[6] = { 0 };
static unsigned char *mesLanguageFRENCH[6] = { 0 };
static unsigned char *mesLanguageGERMAN[6] = { 0 };
static unsigned char *mesLanguageITALIAN[6] = { 0 };
static unsigned char *mesLanguageSPANISH[6] = { 0 };
static unsigned char **mesLanguage[6] = { 0 };
static unsigned char *mesLanguageOK[6] = { 0 };
static unsigned char *mesLanguageCANCEL[6] = { 0 };

/** ---------------------------------------------------------------------------
 * The pinned lines, one at a time -- each is a fact read off this build, not a layout
 * choice, and the `.line` gate compares the statement lists byte for byte:
 *
 *   117  the definition's own line: no instruction is attributed to it, because mwcc
 *        attributes the first statement's code to the statement.
 *   118  `if (id0 >= 7)`     ->  slti v0,a0,7 / bnez / nop: the compare and its branch,
 *        with the delay slot the clobber-inside-the-statement shape leaves empty.
 *   119  `id0 = 2;`          ->  li a0,2: the value the condition selects.
 *   120  blank: retail's own space between the two clamps.
 *   121  `if (id1 >= 7)`     ->  the same pair for the second index.
 *   122  `id1 = 2;`          ->  li a1,2.
 *   123-126  the block inside the function below: retail's own comment/declaration space
 *        between the clamps and the return.  Anything that emits an instruction there
 *        would move line 127.
 *   127  `return mesLanguage[id1][id0];`  ->  lui/addiu for the table's absolute address,
 *        both scaled indexes and the first of the two loads.
 *   128  the closing brace  ->  jr ra with the second load in its delay slot, which is what
 *        makes the last line-table entry the brace rather than the return.
 *
 * Two things about the tables above are evidence as well: `mesLanguage` is a
 * `unsigned char **` array because `mesLanguage[id1][id0]` yields the `unsigned char *` the
 * function returns, and the two fallbacks' `AT_location` is address 0 in retail -- a
 * relocation against a symbol the link never defines, which is what `compile.py` reads out
 * of config/ddrex2p/unplaced_symbols.txt rather than refusing the unit for a name the
 * symbol file has no address for.
 *
 * The disassembly this unit was written against (0x001C4720-0x001C4764), each line
 * attributed to the statement the line table gives it -- the source's shape and the gate's
 * verdict read twice.  The two `lui`/`addiu` halves of the table's address are one statement
 * on line 127, and the `sll` the scheduler moved between them is the same statement's second
 * index: mwcc reorders the address computation and the two scaled indexes freely, which is
 * why the order below is not the order the C writes them in.  What it *cannot* reorder is
 * the load into the delay slot of the return, which is what makes line 128 the brace.
 *
 *   1c4720  28820007  slti  v0,a0,7        118
 *   1c4724  14400002  bnez  v0,0x1c4730    118
 *   1c4728  00000000  nop                  118
 *   1c472c  24040002  li    a0,2           119
 *   1c4730  28a20007  slti  v0,a1,7        121
 *   1c4734  14400002  bnez  v0,0x1c4740    121
 *   1c4738  00000000  nop                  121
 *   1c473c  24050002  li    a1,2           122
 *   1c4740  3c02002b  lui   v0,0x2b        127
 *   1c4744  00052880  sll   a1,a1,0x2      127
 *   1c4748  244233c0  addiu v0,v0,13248   127
 *   1c474c  00451021  addu  v0,v0,a1       127
 *   1c4750  00041880  sll   v1,a0,0x2      127
 *   1c4754  8c420000  lw    v0,0(v0)       127
 *   1c4758  00431021  addu  v0,v0,v1       127
 *   1c475c  03e00008  jr    ra             128
 *   1c4760  8c420000  lw    v0,0(v0)       128
 *
 * mesGetLanguage01 -- the table entry for one message, clamped to the entry the game falls
 * back on when the caller asks for an id outside the table.  The clamp is two one-line
 * `if`s, one per index, and retail's line records say so: the stores have lines of their own
 * (119, 122) and the compares theirs (118, 121), which a conditional expression cannot give
 * -- all of its instructions sit on the line its statement starts on, measured.  The lookup
 * `mesLanguage[id1][id0]` is one `lui`/`addiu` pair for the table's absolute address (24
 * bytes is over the small-data threshold, so it is not `$gp`-relative), both indexes scaled
 * by 4, and the second load scheduled into the `jr ra` delay slot -- why the last line-table
 * entry is the closing brace and not the return.
 *
 * The space between this block and the definition is retail's own declaration/comment
 * space, kept as prose so that no statement of ours lands on a line the gate compares. */


unsigned char *mesGetLanguage01(int id0, int id1)
{
    if (id0 >= 7)
        id0 = 2;

    if (id1 >= 7)
        id1 = 2;
    /* The table walk: its first index is scaled before the address is materialised, and
     * its second load is the one the scheduler hoisted into this return's delay slot.
     * Lines 123-126 are retail's own gap between the clamps and the return -- this block is
     * prose so that nothing of ours can move the return off the line the gate compares. */
    return mesLanguage[id1][id0];
}
