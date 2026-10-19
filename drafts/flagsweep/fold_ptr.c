/* Discriminator 3b: the pointer form that reproduces retail's code but costs a
 * 19th local DIE (gw).  A match needs pointer_iv true *and* the index probe's
 * local count. */
struct E { int a; char pad[0x54288]; };
struct G { struct E player[2]; int x; };
struct G g_game_w;

int probe(int n) {
    int pid;
    struct G *gw;
    int total = 0;
    for (pid = 0, gw = &g_game_w; pid < n;
         pid++, gw = (struct G *)((char *)gw + sizeof(struct E))) {
        gw->player[0].a = pid;
        total += gw->player[0].a;
    }
    return total;
}
