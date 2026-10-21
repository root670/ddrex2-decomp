#include "src/CS/dancemaster/dmm_mess.h"

#define DMM_WIN0 (*(struct _CWS_WIN_W **)0x824450)
#define DMM_WIN1 (*(struct _CWS_WIN_W **)0x824454)

unsigned char *dmm_str_newgame = (unsigned char *)"NEW GAME";
unsigned char *dmm_str_continue = (unsigned char *)"CONTINUE";
unsigned char *dmm_str_yes;
unsigned char *dmm_str_no;
unsigned char *dmm_str_warning = (unsigned char *)"Dance Master Mode data already exists. Saving will overwrite old data.";

anon_8_131 *dmm_get_work(void);
int dmm_is_savedata(void);
int func_00121050(int, unsigned char *);
void func_00125570(int, int, int, int);
void func_00125520(int);
void func_00121320(unsigned char *, long, float, float);
struct tex_bind *func_0012D070(int);
void func_001B7B48(unsigned char *, unsigned char *, int);
char CwsStrSetAll(struct _CWS_WIN_W *, int, int, int, int, unsigned char, unsigned char, unsigned int, int, unsigned char, unsigned char *);
char CwsStrSetBri(struct _CWS_WIN_W *, int, unsigned char);
int GetCsFontLen(unsigned char *);
void CsFontPuts(short, short, unsigned char *, int, int, int, int, int, int);

void dmm_disp_text(unsigned char *str, int x, int y, int z, int br, int alpha, int width, int flg, int font, struct _CWS_WIN_W *winp) {
    anon_8_131 *work;
    unsigned char line_string[256];
    int string_len;
    int line_len;
    int word_len;
    unsigned char *word_str;
    int line_num;
    int size;
    int i;
    struct tex_bind *bp;

    work = dmm_get_work();
    string_len = 0;
    line_len = 0;
    line_num = 1;
    for (;;) {
        word_str = str;
        word_len = 0;
        while (*str != ' ' && *str != 0) {
            str++;
            word_len++;
        }
        if (word_len != 0) {
            func_001B7B48(word_str, &line_string[line_len], word_len);
            line_string[line_len + word_len] = 0;
            switch (font) { case 1: size = func_00121050(0, line_string); break; case 2: size = GetCsFontLen(line_string); break; default: size = 0; } if (width < size) {
                line_string[line_len] = '\n';
                func_001B7B48(line_string, &work->string[string_len], line_len + 1);
                string_len += line_len + 1;
                line_len = 0;
                str = word_str;
                line_num++;
                continue;
            }
            line_len += word_len;
        }
        if (*str == 0) {
            func_001B7B48(line_string, &work->string[string_len], line_len);
            work->string[string_len + line_len] = 0;
            break;
        }
        line_string[line_len] = ' ';
        str++;
        line_len++;
    }
    if (flg & 0x400) {
        size = font == 1 ? 0x14 : 0x18;
        if (line_num % 2 == 0) {
            y -= size * (line_num / 2);
        } else {
            y -= size / 2 + size * (line_num / 2);
        }
    }
    if (winp != 0) {
        CwsStrSetAll(winp, 0, x, y, z, br, alpha, flg, font, 0, work->string);
    }
    else if (font == 1) {
        func_00125570(br, br, br, alpha);
        func_00125520(z);
        word_len = 0;
        for (i = 0; i < line_num; i++) {
            size = 0;
            while (work->string[word_len] != '\n' && work->string[word_len] != 0) {
                line_string[size] = work->string[word_len];
                word_len++;
                size++;
            }
            line_string[size] = 0;
            word_len++;
            func_00121320(line_string, flg | 0x1350, (float)x, (float)y);
            y += 20;
        }
    }
    else if (font == 2) { bp = func_0012D070(0x10);
        CsFontPuts((short)x, (short)y, work->string, br, z, 0, alpha, bp->id, flg);
    }
}

void set_data_warning_mess(void) {
    dmm_get_work();
    dmm_disp_text(dmm_str_warning, 0, -0x56, 0x7100, 0x80, 0x80, 0x178, 0x400, 1, DMM_WIN1);
}

void set_data_select_mess(void) {
    struct _CWS_WIN_W *winp;

    winp = DMM_WIN0;
    CwsStrSetAll(winp, 0, 0, -0x1e, 0x6100, 0x80, 0x80, 0x400, 2, 0, dmm_str_newgame);
    CwsStrSetAll(winp, 1, 0, 4, 0x6100, 0x80, 0x80, 0x400, 2, 0, dmm_str_continue);
    if (dmm_is_savedata()) {
        CwsStrSetBri(winp, 1, 0x80);
    } else {
        CwsStrSetBri(winp, 1, 0x40);
    }
}
