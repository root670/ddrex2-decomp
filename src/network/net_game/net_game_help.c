struct _net_help_work {
    int num_old;
    int num;
    int num2_old;
    int num2;
    int timer;
    int pos;
};

extern unsigned char *D_01029FE4;
extern unsigned char *D_0102FACC;
#define D_0102FE00 ((struct _net_help_work *)0x0102FE00)

char CwsWinSetCode(unsigned char *, char);
void CwsStrAllDelete(unsigned char *);
unsigned char *NetReadDataGetStr(int);
int NetReadDataGetStrLFNum(unsigned char *);
char CwsStrSetAll(unsigned char *, int, int, int, int, unsigned char, unsigned char,
                  unsigned int, int, unsigned char, unsigned char *, ...);
char CwsStrSetDispStatus(unsigned char *, int, char);

void NetGameHelpSetMes(int, int _num, int _num2, int pos)
{
    D_0102FE00->num = _num;
    D_0102FE00->num2 = _num2;
    D_0102FE00->pos = pos;
}

void NetGameHelpDisp(void)
{
    unsigned char *str00;
    int lf;
    if ((!!(*(int *)(D_01029FE4 + 0xEC0) & 0x20)) != 0) {
        if (D_0102FE00->num == -1) {
            *(char *)(D_0102FACC + 0x51) = 6;
            CwsWinSetCode(D_0102FACC, 2);
            D_0102FE00->timer = 0;
            return;
        } else if (D_0102FE00->num_old != D_0102FE00->num ||
                   D_0102FE00->num2_old != D_0102FE00->num2) {
            str00 = NetReadDataGetStr(D_0102FE00->num);
            CwsStrAllDelete(D_0102FACC);
            CwsStrSetAll(D_0102FACC, 0, 0, -0x24, 0x100, 0x80, 0x80, 0x400, 2, 0, str00);
            if (D_0102FE00->num2 >= 0) {
                lf = NetReadDataGetStrLFNum(str00) + 1;
                CwsStrSetAll(D_0102FACC, 1, 0, lf * 24 - 0x24, 0x100, 0x80, 0x80, 0x400, 2, 0,
                             NetReadDataGetStr(D_0102FE00->num2));
            }
            if (D_0102FE00->pos == 1) {
                *(int *)(D_0102FACC + 0x34) = -0x4C;
                *(int *)(D_0102FACC + 0x18) = -0x4C;
            } else {
                *(int *)(D_0102FACC + 0x34) = 0x8B;
                *(int *)(D_0102FACC + 0x18) = 0x8B;
            }
            if (D_0102FE00->timer <= 0) {
                *(char *)(D_0102FACC + 0x51) = 6;
                CwsWinSetCode(D_0102FACC, 1);
            } else {
                CwsStrSetDispStatus(D_0102FACC, 0, 1);
                CwsStrSetDispStatus(D_0102FACC, 1, 1);
            }
            D_0102FE00->timer = 0xB4;
            D_0102FE00->num_old = D_0102FE00->num;
            D_0102FE00->num2_old = D_0102FE00->num2;
            return;
        } else if (D_0102FE00->timer <= 0) {
            *(char *)(D_0102FACC + 0x51) = 6;
            CwsWinSetCode(D_0102FACC, 2);
        } else {
            D_0102FE00->timer -= 1;
        }
    } else {
        *(char *)(D_0102FACC + 0x51) = 6;
        CwsWinSetCode(D_0102FACC, 2);
        D_0102FE00->timer = 0;
    }
}
