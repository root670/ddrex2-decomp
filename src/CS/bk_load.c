static unsigned char *xxxx_bk_tm2_tbl[75] = { 0 };

int func_0011DE80(void);
int func_0011E090(unsigned char *a, unsigned int *b);

int sysSetMusicBk(unsigned int *load_addr, int id)
{
    int ret;

    if (func_0011E090(xxxx_bk_tm2_tbl[id], load_addr))
        ret = 1;
    else
        ret = -1;

    return ret;
}

int sysWaitMusicBk(void)
{
    int ret;

    ret = 0;
    if (func_0011DE80())
        ret = 1;

    return ret;
}
