static unsigned char *xxxx_bk_tm2_tbl[75] = { (unsigned char *)0x002DA620, (unsigned char *)0x002DA680, (unsigned char *)0x002DA668, (unsigned char *)0x002DA640, (unsigned char *)0x002DA658, (unsigned char *)0x002DA648, (unsigned char *)0x002DA628, (unsigned char *)0x002DA6C0, (unsigned char *)0x002DA660, (unsigned char *)0x002DA688, (unsigned char *)0x002DA678, (unsigned char *)0x002DA610, (unsigned char *)0x002DA630, (unsigned char *)0x002DA650, (unsigned char *)0x002DA618, (unsigned char *)0x002DA708, (unsigned char *)0x002DA6B0, (unsigned char *)0x002DA670, (unsigned char *)0x002DA6B8, (unsigned char *)0x002DA698, (unsigned char *)0x002DA6A0, (unsigned char *)0x002DA638, (unsigned char *)0x002DA690, (unsigned char *)0x002DA6A8, (unsigned char *)0x002DA4C8, (unsigned char *)0x002DA548, (unsigned char *)0x002DA550, (unsigned char *)0x002DA4D0, (unsigned char *)0x002DA4D8, (unsigned char *)0x002DA558, (unsigned char *)0x002DA560, (unsigned char *)0x002DA4E0, (unsigned char *)0x002DA4E8, (unsigned char *)0x002DA568, (unsigned char *)0x002DA4F0, (unsigned char *)0x002DA570, (unsigned char *)0x002DA6D0, (unsigned char *)0x002DA578, (unsigned char *)0x002DA6C8, (unsigned char *)0x002DA580, (unsigned char *)0x002DA4F8, (unsigned char *)0x002DA500, (unsigned char *)0x002DA6F8, (unsigned char *)0x002DA6F0, (unsigned char *)0x002DA700, (unsigned char *)0x002DA508, (unsigned char *)0x002DA710, (unsigned char *)0x002DA6D8, (unsigned char *)0x002DA588, (unsigned char *)0x002DA520, (unsigned char *)0x002DA590, (unsigned char *)0x002DA540, (unsigned char *)0x002DA6E8, (unsigned char *)0x002DA598, (unsigned char *)0x002DA5A0, (unsigned char *)0x002DA528, (unsigned char *)0x002DA6E0, (unsigned char *)0x002DA530, (unsigned char *)0x002DA538, (unsigned char *)0x002DA718, (unsigned char *)0x002DA5A8, (unsigned char *)0x002DA5B0, (unsigned char *)0x002DA5B8, (unsigned char *)0x002DA5C0, (unsigned char *)0x002DA5C8, (unsigned char *)0x002DA5D0, (unsigned char *)0x002DA5D8, (unsigned char *)0x002DA5E0, (unsigned char *)0x002DA5E8, (unsigned char *)0x002DA5F0, (unsigned char *)0x002DA5F8, (unsigned char *)0x002DA600, (unsigned char *)0x002DA608, (unsigned char *)0x002DA510, (unsigned char *)0x002DA518 };

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
