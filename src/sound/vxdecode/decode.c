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

#line 13
void setL(void)
{
#line 15
    pWork = work;
#line 16
    pWorkf = workf;
}

#line 20
void setR(void)
{
#line 24
    pWork = &work[1];
#line 25
    pWorkf = &workf[1];
}

#line 68
long decodeVAG(unsigned char *s, short *d, long p_len)
{
    long d1;
    long d7;
    long d2, d2L, d5, d6;
    long *a3;
    short d3; short *a2; unsigned char d4; unsigned char *a0;
#line 75
    if (*(long *)s == 0x56414770) {
#line 76
        p_len -= 4;
#line 77
        s += 0x40;
    }
#line 86
    d4 = 0;
#line 88
    a0 = s;
#line 89
    a2 = d;
#line 90
    d5 = pWork->dL;
#line 92
    d2 = pWork->dH;
#line 94
    while (p_len-- > 0) {
#line 95
        d6 = *a0;
#line 104
        d1 = nLow[s[0]]; a3 = &multbl[nL[d1]];
#line 109
        d4 = s[1];
#line 110
        a0 = s + 2;
#line 121
        d3 = 13;
#line 123
        switch (nHigh[(unsigned char)d6]) {
#line 124
        case 0:
                do {
#line 126
                d7 = nLow[*a0];
#line 127
                d2 = a3[d7];
#line 128
                a2[0] = d2;
#line 131
                d1 = nHigh[*a0++];
#line 132
                d2L = a3[d1];
#line 133
                a2[1] = d2L;
#line 134
                d5 = d2L;
#line 135
                a2 += 2; } while (--d3 != -1);
#line 136
            break;
#line 138
        case 1:
                do { d5 = d5 * 60;
#line 140
                d2 = d5 >> 6;
#line 141
                d1 = nLow[*a0];
#line 142
                d2 += a3[d1];
#line 143
                a2[0] = d2;
#line 147
                d2L = (d2 * 60) >> 6;
#line 148
                d7 = nHigh[*a0++];
#line 149
                d2L += a3[d7];
#line 150
                a2[1] = d2L;
#line 151
                d5 = d2L;
#line 152
                a2 += 2; } while (--d3 != -1);
#line 153
            break;
#line 155
        case 2:
                do { d2 = d5 * 115 - d2 * 52;
#line 157
                d2 = d2 >> 6;
#line 158
                d1 = nLow[*a0];
#line 159
                d2 += a3[d1];
#line 160
                a2[0] = d2;
#line 164
                d2L = (d2 * 115 - d5 * 52) >> 6;
#line 165
                d7 = nHigh[*a0++];
#line 166
                d2L += a3[d7];
#line 167
                a2[1] = d2L;
#line 168
                d5 = d2L;
#line 169
                a2 += 2; } while (--d3 != -1);
#line 170
            break;
#line 172
        case 3:
                do { d2 = d5 * 98 - d2 * 55;
#line 174
                d2 = d2 >> 6;
#line 175
                d1 = nLow[*a0];
#line 176
                d2 += a3[d1];
#line 177
                a2[0] = d2;
#line 181
                d2L = (d2 * 98 - d5 * 55) >> 6;
#line 182
                d7 = nHigh[*a0++];
#line 183
                d2L += a3[d7];
#line 184
                a2[1] = d2L;
#line 185
                d5 = d2L;
#line 186
                a2 += 2; } while (--d3 != -1);
#line 187
            break;
#line 189
        case 4:
                do { d2 = d5 * 122 - d2 * 60;
#line 191
                d2 = d2 >> 6;
#line 192
                d1 = nLow[*a0];
#line 193
                d2 += a3[d1];
#line 194
                a2[0] = d2;
#line 198
                d2L = (d2 * 122 - d5 * 60) >> 6;
#line 199
                d7 = nHigh[*a0++];
#line 200
                d2L += a3[d7];
#line 201
                a2[1] = d2L;
#line 202
                d5 = d2L;
#line 203
                a2 += 2; } while (--d3 != -1);
#line 204
            break;
        }
#line 207
        s = a0;
#line 208
    }
#line 210
    if (d4 & 1) {
#line 211
        pWork->dL = 0;
#line 213
        pWork->dH = 0; } else {
#line 215
        pWork->dL = d5;
#line 216
        pWork->dH = d2;
    }
#line 219
    return (long)(unsigned int)a2 -
#line 220
        (long)(unsigned int)d; }
