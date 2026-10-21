extern unsigned char bk_tm2_records[];
static unsigned char *xxxx_bk_tm2_tbl[75] = {
    (unsigned char *)&bk_tm2_records[960], (unsigned char *)&bk_tm2_records[1056], (unsigned char *)&bk_tm2_records[1032], (unsigned char *)&bk_tm2_records[992],
    (unsigned char *)&bk_tm2_records[1016], (unsigned char *)&bk_tm2_records[1000], (unsigned char *)&bk_tm2_records[968], (unsigned char *)&bk_tm2_records[1120],
    (unsigned char *)&bk_tm2_records[1024], (unsigned char *)&bk_tm2_records[1064], (unsigned char *)&bk_tm2_records[1048], (unsigned char *)&bk_tm2_records[944],
    (unsigned char *)&bk_tm2_records[976], (unsigned char *)&bk_tm2_records[1008], (unsigned char *)&bk_tm2_records[952], (unsigned char *)&bk_tm2_records[1192],
    (unsigned char *)&bk_tm2_records[1104], (unsigned char *)&bk_tm2_records[1040], (unsigned char *)&bk_tm2_records[1112], (unsigned char *)&bk_tm2_records[1080],
    (unsigned char *)&bk_tm2_records[1088], (unsigned char *)&bk_tm2_records[984], (unsigned char *)&bk_tm2_records[1072], (unsigned char *)&bk_tm2_records[1096],
    (unsigned char *)&bk_tm2_records[616], (unsigned char *)&bk_tm2_records[744], (unsigned char *)&bk_tm2_records[752], (unsigned char *)&bk_tm2_records[624],
    (unsigned char *)&bk_tm2_records[632], (unsigned char *)&bk_tm2_records[760], (unsigned char *)&bk_tm2_records[768], (unsigned char *)&bk_tm2_records[640],
    (unsigned char *)&bk_tm2_records[648], (unsigned char *)&bk_tm2_records[776], (unsigned char *)&bk_tm2_records[656], (unsigned char *)&bk_tm2_records[784],
    (unsigned char *)&bk_tm2_records[1136], (unsigned char *)&bk_tm2_records[792], (unsigned char *)&bk_tm2_records[1128], (unsigned char *)&bk_tm2_records[800],
    (unsigned char *)&bk_tm2_records[664], (unsigned char *)&bk_tm2_records[672], (unsigned char *)&bk_tm2_records[1176], (unsigned char *)&bk_tm2_records[1168],
    (unsigned char *)&bk_tm2_records[1184], (unsigned char *)&bk_tm2_records[680], (unsigned char *)&bk_tm2_records[1200], (unsigned char *)&bk_tm2_records[1144],
    (unsigned char *)&bk_tm2_records[808], (unsigned char *)&bk_tm2_records[704], (unsigned char *)&bk_tm2_records[816], (unsigned char *)&bk_tm2_records[736],
    (unsigned char *)&bk_tm2_records[1160], (unsigned char *)&bk_tm2_records[824], (unsigned char *)&bk_tm2_records[832], (unsigned char *)&bk_tm2_records[712],
    (unsigned char *)&bk_tm2_records[1152], (unsigned char *)&bk_tm2_records[720], (unsigned char *)&bk_tm2_records[728], (unsigned char *)&bk_tm2_records[1208],
    (unsigned char *)&bk_tm2_records[840], (unsigned char *)&bk_tm2_records[848], (unsigned char *)&bk_tm2_records[856], (unsigned char *)&bk_tm2_records[864],
    (unsigned char *)&bk_tm2_records[872], (unsigned char *)&bk_tm2_records[880], (unsigned char *)&bk_tm2_records[888], (unsigned char *)&bk_tm2_records[896],
    (unsigned char *)&bk_tm2_records[904], (unsigned char *)&bk_tm2_records[912], (unsigned char *)&bk_tm2_records[920], (unsigned char *)&bk_tm2_records[928],
    (unsigned char *)&bk_tm2_records[936], (unsigned char *)&bk_tm2_records[688], (unsigned char *)&bk_tm2_records[696],
};

int func_0011DE80(void);
int func_0011E090(unsigned char *a, unsigned int *b);

int sysSetMusicBk(unsigned int *load_addr, int id) {
    int ret;

    if (func_0011E090(xxxx_bk_tm2_tbl[id], load_addr))
        ret = 1;
    else
        ret = -1;

    return ret;
}

int sysWaitMusicBk(void) {
    int ret;

    ret = 0;
    if (func_0011DE80())
        ret = 1;

    return ret;
}
