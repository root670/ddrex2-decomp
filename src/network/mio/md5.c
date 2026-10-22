typedef struct {
    unsigned int state[4];
    unsigned int count[2];
    unsigned char buffer[64];
} anon_0_115;
void *func_001BBBF8(void *dst, void *src, unsigned int n);
static unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define FF(a, b, c, d, x, s, ac) { (a) += F ((b), (c), (d)) + (x) + (unsigned int)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define GG(a, b, c, d, x, s, ac) { (a) += G ((b), (c), (d)) + (x) + (unsigned int)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define HH(a, b, c, d, x, s, ac) { (a) += H ((b), (c), (d)) + (x) + (unsigned int)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define II(a, b, c, d, x, s, ac) { (a) += I ((b), (c), (d)) + (x) + (unsigned int)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
static inline void Decode(unsigned int *output, unsigned char *input, unsigned int len) {
    unsigned int i, j;
    for (i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j+1]) << 8) | (((unsigned int)input[j+2]) << 16) | (((unsigned int)input[j+3]) << 24);
}
static inline void MD5_memset(char *output, int value, unsigned int len) {
    unsigned int i;
    for (i = 0; i < len; i++)
        ((char *)output)[i] = (char)value;
}
static void MD5Transform(unsigned int *state, unsigned char *block) {
    unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    Decode(x, block, 64);
    FF(a, b, c, d, x[0], 7, 0xd76aa478u);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756u);
    FF(c, d, a, b, x[2], 17, 0x242070dbu);
    FF(b, c, d, a, x[3], 22, 0xc1bdceeeu);
    FF(a, b, c, d, x[4], 7, 0xf57c0fafu);
    FF(d, a, b, c, x[5], 12, 0x4787c62au);
    FF(c, d, a, b, x[6], 17, 0xa8304613u);
    FF(b, c, d, a, x[7], 22, 0xfd469501u);
    FF(a, b, c, d, x[8], 7, 0x698098d8u);
    FF(d, a, b, c, x[9], 12, 0x8b44f7afu);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1u);
    FF(b, c, d, a, x[11], 22, 0x895cd7beu);
    FF(a, b, c, d, x[12], 7, 0x6b901122u);
    FF(d, a, b, c, x[13], 12, 0xfd987193u);
    FF(c, d, a, b, x[14], 17, 0xa679438eu);
    FF(b, c, d, a, x[15], 22, 0x49b40821u);
    GG(a, b, c, d, x[1], 5, 0xf61e2562u);
    GG(d, a, b, c, x[6], 9, 0xc040b340u);
    GG(c, d, a, b, x[11], 14, 0x265e5a51u);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aau);
    GG(a, b, c, d, x[5], 5, 0xd62f105du);
    GG(d, a, b, c, x[10], 9, 0x02441453u);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681u);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8u);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6u);
    GG(d, a, b, c, x[14], 9, 0xc33707d6u);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87u);
    GG(b, c, d, a, x[8], 20, 0x455a14edu);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905u);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8u);
    GG(c, d, a, b, x[7], 14, 0x676f02d9u);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8au);
    HH(a, b, c, d, x[5], 4, 0xfffa3942u);
    HH(d, a, b, c, x[8], 11, 0x8771f681u);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122u);
    HH(b, c, d, a, x[14], 23, 0xfde5380cu);
    HH(a, b, c, d, x[1], 4, 0xa4beea44u);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9u);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60u);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70u);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6u);
    HH(d, a, b, c, x[0], 11, 0xeaa127fau);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085u);
    HH(b, c, d, a, x[6], 23, 0x04881d05u);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039u);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5u);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8u);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665u);
    II(a, b, c, d, x[0], 6, 0xf4292244u);
    II(d, a, b, c, x[7], 10, 0x432aff97u);
    II(c, d, a, b, x[14], 15, 0xab9423a7u);
    II(b, c, d, a, x[5], 21, 0xfc93a039u);
    II(a, b, c, d, x[12], 6, 0x655b59c3u);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92u);
    II(c, d, a, b, x[10], 15, 0xffeff47du);
    II(b, c, d, a, x[1], 21, 0x85845dd1u);
    II(a, b, c, d, x[8], 6, 0x6fa87e4fu);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0u);
    II(c, d, a, b, x[6], 15, 0xa3014314u);
    II(b, c, d, a, x[13], 21, 0x4e0811a1u);
    II(a, b, c, d, x[4], 6, 0xf7537e82u);
    II(d, a, b, c, x[11], 10, 0xbd3af235u);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bbu);
    II(b, c, d, a, x[9], 21, 0xeb86d391u);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    MD5_memset((char *)x, 0, sizeof(x));
}
static inline void Encode(unsigned char *output, unsigned int *input, unsigned int len) {
    unsigned int i, j;
    for (i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}
void MD5Update(anon_0_115 *context, unsigned char *input, unsigned int inputLen);
void MD5Final(unsigned char *digest, anon_0_115 *context) {
    unsigned char bits[8];
    unsigned int indx;
    Encode(bits, context->count, 8);
    indx = (unsigned int)((context->count[0] >> 3) & 0x3f);
    MD5Update(context, PADDING, (indx < 56) ? (56 - indx) : (120 - indx));
    MD5Update(context, bits, 8);
    Encode(digest, context->state, 16);
    MD5_memset((char *)context, 0, sizeof(*context));
}
void MD5Update(anon_0_115 *context, unsigned char *input, unsigned int inputLen) {
    unsigned int i, indx, partLen;
    indx = (unsigned int)((context->count[0] >> 3) & 0x3F);
    if ((context->count[0] += ((unsigned int)inputLen << 3)) < ((unsigned int)inputLen << 3))
        context->count[1]++;
    context->count[1] += ((unsigned int)inputLen >> 29);
    partLen = 64 - indx;
    if (inputLen >= partLen) {
        func_001BBBF8(&context->buffer[indx], input, partLen);
        MD5Transform(context->state, context->buffer);
        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform(context->state, &input[i]);
        indx = 0;
    } else
        i = 0;
    func_001BBBF8(&context->buffer[indx], &input[i], inputLen - i);
}
void MD5Init(anon_0_115 *context) {
    context->count[0] = context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}
