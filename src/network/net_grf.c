typedef union {
    int id;
    float fd;
} grf_coord;

typedef struct {
    grf_coord x0;
    grf_coord y0;
    grf_coord x1;
    grf_coord y1;
    grf_coord x2;
    grf_coord y2;
    unsigned int z0;
    unsigned int z1;
    unsigned int z2;
    unsigned char r0;
    unsigned char g0;
    unsigned char b0;
    unsigned char a0;
    unsigned char r1;
    unsigned char g1;
    unsigned char b1;
    unsigned char a1;
    unsigned char r2;
    unsigned char g2;
    unsigned char b2;
    unsigned char a2;
    int flg;
} grf_element;

static char dancer_num[22] = {
    5, 4, 7, 6, 3, 2, 1, 0, 14, 15, 13, 12,
    10, 11, 8, 9, 23, 22, 21, 20, 19, 18,
};
static void unused_grf_types(grf_element *p) { p->flg = 1; }

int NetGrfGetDancerIDToNumberPoint(int dancer_id) {
    return dancer_num[dancer_id / 2] + (dancer_id % 2) * 24;
}

int peerPrintf(char *format, ...) {
    char *ap;
    char tmp[1024];
    int r;
    ap = (char *)__builtin_next_arg(format) - ((__builtin_args_info(2) >= 8) ? 0 : (8 - __builtin_args_info(2)) * 8);
    r = func_001C43E8(tmp, format, ap);

    return r;
}
