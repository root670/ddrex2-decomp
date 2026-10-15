/* src/sys/sys_scf.c -- the SCF work object and its two accessors.
 *
 * Reconstructed from orig/SLUS_207.11: the DWARF 1 records for this file (rendered into
 * include/src/sys/sys_scf.h) plus the two functions' disassembly.  The statement line
 * numbers are evidence too -- the promotion rule compares this file's .line bytes with
 * retail -- so nothing is re-wrapped away from the retail lines 24, 29, 32 and 34
 * (sysInitScf) and 41-42 (sysGetDateNotation).  The generated header spells the tag
 * `_tag_SYS_SCF_WORK` bare, which is C++ syntax, so this C unit writes `struct` in front. */
struct _tag_SYS_SCF_WORK {
    int date_notation;
    int language;
};

/* The two calls sysInitScf makes have no compile unit of their own in retail DWARF, so
 * the only names the evidence offers are the oracle's address-derived ones in
 * config/usam2/symbol_addrs.txt; both return the value stored into a pscf field.
 */
int func_0021BF20(struct _tag_SYS_SCF_WORK *p);
int func_0021BDD0(void);

/* The work object every caller of this unit shares. */
struct _tag_SYS_SCF_WORK *pscf;

void sysInitScf(struct _tag_SYS_SCF_WORK *p) {
    /* A fresh work object, then both of its fields from the calls that own them: the
     * store of p and the call to the first of them are one statement pair on one retail
     * line, because mwcc schedules the store into the call's delay slot. */

    pscf = p; pscf->date_notation = func_0021BF20(p);

    /* The second field, from the function that owns it. */
    pscf->language = func_0021BDD0();

}

/* The date notation callers should render dates in: the unit's read-only accessor, which
 * needs no frame because the object's address comes straight out of $gp.  Its retail line
 * table holds two records -- the return line, then the closing brace that owns the jump.
 */
int sysGetDateNotation(void) {
    return pscf->date_notation;
}
