typedef struct {
    long dH;
    long dL;
} anon_0_28;

typedef struct {
    double dH;
    double dL;
} anon_1_28;

anon_1_28 *pWorkf;
unsigned char nHigh[];
unsigned char nLow[];
double dfltB[];
double dfltA[];
double multblF[];
unsigned char nL[];
anon_0_28 *pWork;
long multbl[];
anon_1_28 workf[2];
anon_0_28 work[2];

static void unused_dectbl(void) {
    dfltA[0] = 1;
    dfltB[0] = 2;
    multblF[0] = 3;
}

void setL(void);
void setR(void);
long decodeVAG(unsigned char *s, short *d, long p_len);

void setL(void)
{
    pWork = work;
    pWorkf = workf;
}

void setR(void)
{
    pWork = &work[1];
    pWorkf = &workf[1];
}

long decodeVAG(unsigned char *s, short *d, long p_len)
{
    long d1;
    long d7;
    long d2, d2L, d5, d6;
    long *a3;
    short d3; short *a2; unsigned char d4; unsigned char *a0;
    if (*(long *)s == 0x56414770) {
        p_len -= 4;
        s += 0x40;
    }
    d4 = 0;
    a0 = s;
    a2 = d;
    d5 = pWork->dL;
    d2 = pWork->dH;
    while (p_len-- > 0) {
        d6 = *a0;
        d1 = nLow[s[0]]; a3 = &multbl[nL[d1]];
        d4 = s[1];
        a0 = s + 2;
        d3 = 13;
        switch (nHigh[(unsigned char)d6]) {
        case 0:
                do {
                d7 = nLow[*a0];
                d2 = a3[d7];
                a2[0] = d2;
                d1 = nHigh[*a0++];
                d2L = a3[d1];
                a2[1] = d2L;
                d5 = d2L;
                a2 += 2; } while (--d3 != -1);
            break;
        case 1:
                do { d5 = d5 * 60;
                d2 = d5 >> 6;
                d1 = nLow[*a0];
                d2 += a3[d1];
                a2[0] = d2;
                d2L = (d2 * 60) >> 6;
                d7 = nHigh[*a0++];
                d2L += a3[d7];
                a2[1] = d2L;
                d5 = d2L;
                a2 += 2; } while (--d3 != -1);
            break;
        case 2:
                do { d2 = d5 * 115 - d2 * 52;
                d2 = d2 >> 6;
                d1 = nLow[*a0];
                d2 += a3[d1];
                a2[0] = d2;
                d2L = (d2 * 115 - d5 * 52) >> 6;
                d7 = nHigh[*a0++];
                d2L += a3[d7];
                a2[1] = d2L;
                d5 = d2L;
                a2 += 2; } while (--d3 != -1);
            break;
        case 3:
                do { d2 = d5 * 98 - d2 * 55;
                d2 = d2 >> 6;
                d1 = nLow[*a0];
                d2 += a3[d1];
                a2[0] = d2;
                d2L = (d2 * 98 - d5 * 55) >> 6;
                d7 = nHigh[*a0++];
                d2L += a3[d7];
                a2[1] = d2L;
                d5 = d2L;
                a2 += 2; } while (--d3 != -1);
            break;
        case 4:
                do { d2 = d5 * 122 - d2 * 60;
                d2 = d2 >> 6;
                d1 = nLow[*a0];
                d2 += a3[d1];
                a2[0] = d2;
                d2L = (d2 * 122 - d5 * 60) >> 6;
                d7 = nHigh[*a0++];
                d2L += a3[d7];
                a2[1] = d2L;
                d5 = d2L;
                a2 += 2; } while (--d3 != -1);
            break;
        }
        s = a0;
    }
    if (d4 & 1) {
        pWork->dL = 0;
        pWork->dH = 0; } else {
        pWork->dL = d5;
        pWork->dH = d2;
    }
    return (long)(unsigned int)a2 -
        (long)(unsigned int)d; }
