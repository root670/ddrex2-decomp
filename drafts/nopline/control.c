/* nopline control -- the shape of retail's ps2dancerInitHide with no candidate statement.
 * Compiled with 3.0-011126 -c -lang c -O3 -g; see drafts/nopline/README.md.  */

struct nopline_savedata {
    unsigned char pad[0x40];
    unsigned char HideFlag[0x100];
};
extern struct nopline_savedata SaveData;
int get_chara_hide(int chara);

#line 98
void ps2dancerInitHide(void) { int i;
#line 99

#line 100
    i = 0;
    do {
#line 101
        if (get_chara_hide(i)) {
#line 102
            SaveData.HideFlag[(i + 0x46) >> 5] |= 1 << ((i + 0x46) & 0x1F);
#line 103
        }
#line 104
        i++;
    } while (i < 0x2D);
#line 105
}
