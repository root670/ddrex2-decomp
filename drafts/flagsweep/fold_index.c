/* Discriminator 3a: the index form used by our p_anime.c reconstruction.  mwcc
 * keeps an index IV and recomputes base+index each iteration; retail's bytes show
 * one register holding &g_game_w, advanced at the loop bottom. */
struct E { int a; char pad[0x54288]; };
struct G { struct E player[2]; int x; };
struct G g_game_w;

int probe(int n) {
    int pid;
    int total = 0;
    for (pid = 0; pid < n; pid++) {
        g_game_w.player[pid].a = pid;
        total += g_game_w.player[pid].a;
    }
    return total;
}
