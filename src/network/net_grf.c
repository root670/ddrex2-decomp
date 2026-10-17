/* src/network/net_grf.c -- the net graph's dancer-id lookup and its printf shim.
 *
 * Reconstructed from orig/SLUS_211.74: the DWARF 1 records for this file (rendered into
 * include/src/network/net_grf.h) and the two functions' disassembly.  The statement lines are
 * evidence, not style: retail's .line table puts the lookup's one statement on line 64, the
 * shim's varargs start and its call on 73 and 74, and the shim's last statement on line 80,
 * so nothing here may be re-wrapped away from those lines.  The file needs no `#line`
 * directive: the declarations the DWARF records sit before the first statement.
 *
 * Two spellings here are reconstructed rather than given, because the DWARF records no
 * typedefs at all: the two file-scope aggregates (@anon0 and @anon1) keep their member order
 * and sizes, and the shim's varargs start is written the way the retail compiler's own
 * stdarg.h spelled it -- the header is not in this tree, so the expression that produces
 * retail's 26 instructions is written out at its one statement line.
 *
 * `dancer_num` is a file-scope static whose bytes live in a *data* split
 * (asm/nonmatchings/main/func_002B6A68.s at 0x002B8C20), not in this unit's .text: the
 * initialiser below is retail's own bytes there, and the ld script already assigns the name.
 */

typedef union {
    int id;
    float fd;
} grf_coord;                        /* DWARF @anon1, size 0x4 */

typedef struct {
    grf_coord x0;
    grf_coord y0;
    grf_coord x1;
    grf_coord y1;
    grf_coord x2;
    grf_coord y2;
    unsigned int z0;
    unsigned int z1;
    unsigned int z2;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char a0;
    unsigned char r1;
    unsigned char g1;
    unsigned char b1;
    unsigned char a1;
    unsigned char r2;
    unsigned char g2;
    unsigned char b2;
    unsigned char a2;
    int flg;
} grf_element;                      /* DWARF @anon0, size 0x34 */

static char dancer_num[22] = {
    5, 4, 7, 6, 3, 2, 1, 0, 14, 15, 13, 12,
    10, 11, 8, 9, 23, 22, 21, 20, 19, 18,
};

static void unused_grf_types(grf_element *p) { p->flg = 1; }
/* No function in this unit uses either aggregate, but retail's CU carries both and in this
 * order: MWCC registers a type's DIEs only from a body that uses it, so the unused helper
 * above carries them.  The table is indexed by half the dancer's id and corrected for the odd
 * half -- retail divides with a sign fixup (`bgez`/`sra`) because `/` truncates toward zero. */

int NetGrfGetDancerIDToNumberPoint(int dancer_id)
{
    return dancer_num[dancer_id / 2] + (dancer_id % 2) * 24;
}

/* The shim hands its buffer, the format and the first vararg slot to the anonymous
 * formatting helper its split calls: no DWARF name, no ledger record, so the call is implicit */
int peerPrintf(char *format, ...) {
    char *ap;
    char tmp[1024];
    int r;
    ap = (char *)__builtin_next_arg(format) - ((__builtin_args_info(2) >= 8) ? 0 : (8 - __builtin_args_info(2)) * 8);
    r = func_001C43E8(tmp, format, ap);

    /* `__builtin_next_arg` is the stack frame's register-save area end and
     * `__builtin_args_info(2)` is this function's count of named arguments, so the
     * subtraction lands `ap` on the first slot the caller's varargs were saved in. */
    return r;
}
