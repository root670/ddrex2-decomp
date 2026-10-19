/* Discriminator 2: com_scrollbar.c's else path.  Retail keeps bar_h and
 * dw_h = h - bar_h distinct:
 *
 *   bgez v0, .next
 *   nop
 *   move v0, zero
 *   subu v1, a3, a1      <- the surviving second subtraction
 *   slt  at, v1, v0
 *   ...
 *
 * Under mwcc's default -O3 scheduling the subtraction is folded into the
 * bgez delay slot and one subtraction disappears:
 *
 *   bgez v1, .next
 *   subu a0, a2, v0      <- coalesced, in the delay slot
 *   move v1, zero
 *   slt  at, a0, v1
 */
struct S {
    int x, y, h, z;
    int c_max, c_num, c_now;
    unsigned flag;
};

int probe(struct S *s) {
    int bar_y, bar_h;
    bar_y = s->c_now * (s->h - 4) / s->c_max;
    bar_h = s->c_num * (s->h - 4) / s->c_max;
    if (bar_y < 0) bar_y = 0;
    if (s->h - bar_h < bar_y) bar_y = s->h - bar_h;
    return bar_y + bar_h;
}
