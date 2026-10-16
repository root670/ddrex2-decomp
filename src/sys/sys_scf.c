/* src/sys/sys_scf.c -- the SCF work object and its two accessors.
 *
 * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file (rendered into
 * include/src/sys/sys_scf.h) plus the two functions' disassembly.  The statement line
 * numbers are evidence too -- the promotion rule compares this file's .line bytes with
 * retail -- so nothing is re-wrapped away from the retail lines 24, 29, 35 and 43
 * (sysInitScf) and 50-51 (sysGetDateNotation).  The generated header spells the tag
 * `_tag_SYS_SCF_WORK` bare, which is C++ syntax, so this C unit writes `struct` in front.
 *
 * The preview's sysInitScf is not DDRMAX2 (US)'s: it makes one call, not two, and stores
 * the constant 1 into `language` where that build called a second function, so the old
 * source cannot be reused.  The one callee has no compile unit of its own in retail DWARF,
 * so its name is the one config/ddrex2p/borrowed_symbols.txt borrowed from libscf.a. */
struct _tag_SYS_SCF_WORK {
    int date_notation;
    int language;
};

int sceScfGetDateNotation(struct _tag_SYS_SCF_WORK *p);

/* The work object every caller of this unit shares. */
struct _tag_SYS_SCF_WORK *pscf;

void sysInitScf(struct _tag_SYS_SCF_WORK *p) {
    /* A fresh work object, then its first field from the call that owns it: the store of p
     * and the call are one statement pair on one retail line, because mwcc schedules the
     * store into the call's delay slot -- and the callee is handed the object itself. */

    pscf = p; pscf->date_notation = sceScfGetDateNotation(p);

    /* The second field is this game's, not the SDK's: the preview writes a constant where
     * the previous target's build called sceScfGetLanguage, and mwcc's scheduler records
     * the statement it reordered by leaving the earlier line on the load alone. */

    pscf->language = 1;

    /* The epilogue of a void function belongs to the closing brace: retail's statement
     * list gives that line every instruction from the restore of `ra` to the frame
     * teardown, and there is no statement here that would own it instead.  Nothing else
     * is left to write here -- the object is complete once the two fields are set, and p
     * is only ever stored, never read again, so no later statement's code could be
     * scheduled into the epilogue's range. */
}

/* The date notation callers should render dates in: the unit's read-only accessor, which
 * needs no frame because the object's address comes straight out of $gp.  Its retail line
 * table holds two records -- the return line, then the closing brace that owns the jump.
 */
int sysGetDateNotation(void) {
    return pscf->date_notation;
}
