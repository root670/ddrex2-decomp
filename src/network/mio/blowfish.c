typedef struct {
    unsigned int P[18];
    unsigned int S[4][256];
} anon_0_114;
static unsigned int ORIG_P[18] = {0}; static unsigned int ORIG_S[4][256] = {0};

void Blowfish_Encrypt(anon_0_114 *ctx, unsigned int *xl, unsigned int *xr) { unsigned int Xl; unsigned int Xr; unsigned int temp; short i; Xl = *xl;
    Xr = *xr;

    i = 0;
    do
    { Xl = Xl ^ ctx->P[i];
        temp = (ctx)->S[0][((Xl) >> 24) & 0xFF] + (ctx)->S[1][((Xl) >> 16) & 0xFF]; temp = temp ^ (ctx)->S[2][((Xl) >> 8) & 0xFF]; Xr = (temp + (ctx)->S[3][(Xl) & 0xFF]) ^ Xr;
        temp = Xl;
        Xl = Xr;
        Xr = temp;
        i++; } while (i < 16);

    temp = Xl;
    Xl = Xr;
    Xr = temp;

    Xr = Xr ^ ctx->P[16];
    Xl = Xl ^ ctx->P[17];

    *xl = Xl;

    *xr = Xr; }

void Blowfish_Decrypt(anon_0_114 *ctx, unsigned int *xl, unsigned int *xr) { unsigned int Xl; unsigned int Xr; unsigned int temp; short i; Xl = *xl;
    Xr = *xr;

    i = 17;
    do
    { Xl = Xl ^ ctx->P[i];
        temp = (ctx)->S[0][((Xl) >> 24) & 0xFF] + (ctx)->S[1][((Xl) >> 16) & 0xFF]; temp = temp ^ (ctx)->S[2][((Xl) >> 8) & 0xFF]; Xr = (temp + (ctx)->S[3][(Xl) & 0xFF]) ^ Xr;
        temp = Xl;
        Xl = Xr;
        Xr = temp;
        i--; } while (i > 1);

    temp = Xl;
    Xl = Xr;
    Xr = temp;

    Xr = Xr ^ ctx->P[1];
    Xl = Xl ^ ctx->P[0];

    *xl = Xl;

    *xr = Xr; }

void Blowfish_Init(anon_0_114 *ctx, unsigned char *key, int keyLen) {
    int i; int j; int k; unsigned int data; unsigned int datal; unsigned int datar;

    for (i = 0; i < 4; i++)
    { for (j = 0; j < 256; j++)
        { ctx->S[i][j] = ORIG_S[i][j];
        } }

    j = 0;
    for (i = 0; i < 18; i++)
    { data = 0x00000000;
        for (k = 0; k < 4; k++)
        { data = (data << 8) | key[j];
            j = j + 1;
            if (j >= keyLen)
                j = 0;
        }
        ctx->P[i] = ORIG_P[i] ^ data;
    }

    datal = 0x00000000;
    datar = 0x00000000;

    for (i = 0; i < 18; i += 2)
    { Blowfish_Encrypt(ctx, &datal, &datar);
        ctx->P[i] = datal;
        ctx->P[i + 1] = datar;
    }

    for (i = 0; i < 4; i++)
    { for (j = 0; j < 256; j += 2)
        { Blowfish_Encrypt(ctx, &datal, &datar);
            ctx->S[i][j] = datal;
            ctx->S[i][j + 1] = datar;
        }
    }
}
