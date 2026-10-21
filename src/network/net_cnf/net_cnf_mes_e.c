static unsigned char warning0[51] = { 0 };
static unsigned char warning1[56] = { 0 };
static unsigned char *NETDEV_CHECKING[3] = { 0 };
static unsigned char *NETDEV_OK[3] = { 0 };
static unsigned char *NETDEV_ERR[6] = { 0 };
static unsigned char *MC_CHECKING[4] = { 0 };
static unsigned char *MC_UNFORMAT_YN_CHECK[5] = { 0 };
static unsigned char *MC_NO_CARD_YN_CHECK[5] = { 0 };
static unsigned char *MC_CHECK_ERR_YN_CHECK[5] = { 0 };
static unsigned char *MC_NO_YNCF_YN_CHECK[4] = { 0 };
static unsigned char *NETCNF_CHECKING[4] = { 0 };
static unsigned char *NETCNF_NO_NET_YN_CHECK[4] = { 0 };
static unsigned char *NETCNF_NO_IFC_YN_CHECK[4] = { 0 };
static unsigned char *NETCNF_ERR_YN_CHECK[5] = { 0 };
static unsigned char *NETCNF_LETHAL_ERR_YN_CHECK[5] = { 0 };
static unsigned char *NETCNF_MAGIC_ERR_YN_CHECK[5] = { 0 };
static unsigned char *WARNING_HOWTO_EDIT[4] = { 0 };
static unsigned char *WARNING_NOT_AVAILABLE[3] = { 0 };
static unsigned char *SELECT_IFC[2] = { 0 };
static unsigned char *BASE_TITLE[2] = { 0 };
static unsigned char *UPNP_YN[4] = { 0 };
static unsigned char *UPNP_EXP[3] = { 0 };
static unsigned char *IRX_LOADING[2] = { 0 };
static unsigned char *IRX_LOAD_ERR[2] = { 0 };
unsigned char **ncMessageTbl_ENGLISH[22];
unsigned char *cmes_yesno_str_english[];

unsigned char **ncmesGetMessageTable(int id)
{
    unsigned char **ret;

    ret = 0;
    if (0 <= id && id < 22) {
        ret = ncMessageTbl_ENGLISH[id];
    }
    return ret;
}

unsigned char *ncmesGetYes(void)
{
    return cmes_yesno_str_english[1];
}

unsigned char *ncmesGetNo(void)
{
    return cmes_yesno_str_english[0];
}
