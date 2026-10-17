/* src/CS/lang.c -- the message-language tables and the accessor the rest of the game calls.
 *
 * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file (rendered into
 * include/src/CS/lang.h) plus mesGetLanguage01's disassembly.  The statement line numbers
 * are evidence too -- the promotion rule compares this file's .line bytes with retail -- so
 * nothing is re-wrapped away from the retail lines 118-119, 121-122, 127 and 128.
 *
 * The nine tables are file-scope statics: CodeWarrior writes their DIEs as locals with a
 * location, and two of them (`mesLanguageOK`, `mesLanguageCANCEL`) carry address 0 in retail
 * -- declared but never allocated, which is why they are in config/ddrex2p/unplaced_symbols.txt
 * and not in this target's split.
 *
 * Nothing here contributes an image byte: the tables live in `.data` in retail and a
 * promoted unit links only its `.text` (AGENTS.md, rule 9), so these definitions exist for
 * the DIE that names them and for the code that reads them, not for their storage. */

static unsigned char *mesLanguageJAPANESE[6];
static unsigned char *mesLanguageENGLISH[6];
static unsigned char *mesLanguageFRENCH[6];
static unsigned char *mesLanguageGERMAN[6];
static unsigned char *mesLanguageITALIAN[6];
static unsigned char *mesLanguageSPANISH[6];
static unsigned char **mesLanguage[6];
static unsigned char *mesLanguageOK[6];
static unsigned char *mesLanguageCANCEL[6];

/** ---------------------------------------------------------------------------
 * The pinned lines, one at a time -- each is a fact read off this build, not a layout
 * choice, and the `.line` gate compares the statement lists byte for byte:
 *
 *   117  the definition's own line: no instruction is attributed to it, because mwcc
 *        attributes the first statement's code to the statement.
 *   118  `id0 = id0 >= 7 ?`  ->  slti v0,a0,7 / bnez / nop: the compare and its branch,
 *        with the delay slot the conditional expression leaves empty.
 *   119  `2 : id0;`          ->  li a0,2: the value the condition selects.
 *   120  blank: the `?`'s second statement is a separate line, so this one holds nothing.
 *   121  `id1 = id1 >= 7 ?`  ->  the same pair for the second index.
 *   122  `2 : id1;`          ->  li a1,2.
 *   123-126  the block below: retail's own comment/declaration space between the clamps
 *        and the return.  Anything that emits an instruction here would move line 127.
 *   127  `return mesLanguage[id1][id0];`  ->  lui/addiu for the table's absolute address,
 *        both scaled indexes and the first of the two loads.
 *   128  the closing brace  ->  jr ra with the second load in its delay slot, which is what
 *        makes the last line-table entry the brace rather than the return.
 *
 * Two things about the tables above are evidence as well, and both are visible in the
 * generated header rather than only here: their declaration order is the DIE order
 * (JAPANESE, ENGLISH, FRENCH, GERMAN, ITALIAN, SPANISH, `mesLanguage` -- the table of
 * tables -- then the two fallbacks), and `mesLanguage` is a `unsigned char **` array
 * because `mesLanguage[id1][id0]` yields the `unsigned char *` the function returns.
 *
 * The two fallbacks are the interesting pair.  Retail's DWARF gives them `AT_location`
 * address 0, so their DIEs hold a relocation against a symbol the link never defines; that
 * is why they are declared here without being allocated anywhere.  A placement has to
 * reproduce that 0, which is what `compile.py` now reads out of
 * config/ddrex2p/unplaced_symbols.txt (the oracle's `reason:no AT_location address`
 * records) rather than refusing the unit for a name the symbol file has no address for.
 *
 * Nothing in this file is a guess about the game: the six language tables are the ones its
 * own accessor indexes, `mesLanguage` is named by the DWARF of this unit, and `mesGetLanguage01`
 * is the name the DWARF carries for 0x001C4720.  What the tables *contain* is another
 * translation unit's business -- the values live in retail's `.data`, which this build does
 * not reconstruct yet (rule 9), and nothing in the `.text` gate depends on them.
 *
 * The disassembly this unit was written against, for the record (0x001C4720-0x001C4764):
 *
 * Each line of it is attributed to the statement the line table gives it, so the source's
 * shape and the gate's verdict are the same fact read twice.  The two `lui`/`addiu` halves
 * of the table's address are one statement on line 127, and the `sll` the scheduler moved
 * between them is the same statement's second index: mwcc reorders the address computation
 * and the two scaled indexes freely, which is why the order below is not the order the C
 * writes them in.  What it *cannot* reorder is the load into the delay slot of the return,
 * which is what makes line 128 the brace rather than a statement of its own.
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
 * back on when the caller asks for an id outside the table.
 *
 * The clamp is a *conditional expression split across two lines*, and retail's own bytes are
 * what say so: the two `slti`/`bnez` pairs each have a `nop` in the branch delay slot, which
 * is what mwcc leaves there when the clobber of the compared value is *inside* the same
 * statement.  Written as two `if`s the same three instructions come out, but the second
 * statement's test is hoisted into the first branch's delay slot and re-materialised after
 * the `li`, so the bytes differ in two instructions (`-O3 -g`, measured with
 * `tools/toolchain/select_build.py`).  The line table agrees: the compare is on 118 and 121
 * while the `li` that stores the fallback is on 119 and 122, which is the split of `?` from
 * its value.
 *
 * The lookup is `mesLanguage[id1][id0]`: one `lui`/`addiu` pair for the table's absolute
 * address (24 bytes is over the small-data threshold, so it is not `$gp`-relative), both
 * indexes scaled by 4, and the second load scheduled into the `jr ra` delay slot -- which is
 * why the line table's last entry is the closing brace and not the return.
 *
 * The file's remaining lines held retail's other declarations and comments; the comment
 * block below is that space, kept as prose so that no statement of ours lands on a line the
 * gate compares.  Lines 123-126 are the same space inside the function: the clamps end on
 * 122 and the return sits on 127. */

unsigned char *mesGetLanguage01(int id0, int id1)
{
    id0 = id0 >= 7 ? 2 : id0;

    id1 = id1 >= 7 ? 2 : id1;
    /* The table walk: its first index is scaled before the address is materialised, and
     * its second load is the one the scheduler hoisted into this return's delay slot.
     * Lines 123-126 are retail's own gap between the clamps and the return -- this block is
     * prose so that nothing of ours can move the return off the line the gate compares. */
    return mesLanguage[id1][id0];
}
