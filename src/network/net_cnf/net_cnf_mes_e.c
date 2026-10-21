static unsigned char warning0[51] = { 'D', 'o', ' ', 'n', 'o', 't', ' ', 'r', 'e', 'm', 'o', 'v', 'e', ' ', 'm', 'e', 'm', 'o', 'r', 'y', ' ', 'c', 'a', 'r', 'd', ' ', '(', '8', 'M', 'B', ')', '(', 'f', 'o', 'r', ' ', 'P', 'l', 'a', 'y', 'S', 't', 'a', 't', 'i', 'o', 'n', '\256', '2', ')', 0 };
static unsigned char warning1[56] = { 'i', 'n', ' ', 'M', 'E', 'M', 'O', 'R', 'Y', ' ', 'C', 'A', 'R', 'D', ' ', 's', 'l', 'o', 't', ' ', '1', ',', ' ', 'r', 'e', 's', 'e', 't', ' ', 'o', 'r', ' ', 's', 'w', 'i', 't', 'c', 'h', ' ', 'o', 'f', 'f', ' ', 't', 'h', 'e', ' ', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 0 };
static unsigned char *NETDEV_CHECKING[3] = { (unsigned char *)"Checking Network Adaptor (Ethernet/modem)", (unsigned char *)"(for PlayStation\2562) ...", 0 };
static unsigned char *NETDEV_OK[3] = { (unsigned char *)"Network Adaptor (Ethernet/modem)", (unsigned char *)"(for PlayStation\2562) was found.", 0 };
static unsigned char *NETDEV_ERR[6] = { (unsigned char *)"Network Adaptor (Ethernet/modem)", (unsigned char *)"(for PlayStation\2562) could not be found.", (unsigned char *)"Make sure Network Adaptor (Ethernet/modem)", (unsigned char *)"(for PlayStation\2562) is connected,", (unsigned char *)"and then reboot.", 0 };
static unsigned char *MC_CHECKING[4] = { (unsigned char *)"Checking...", (unsigned char *)"Do not remove memory card (8MB)(for PlayStation\2562)", (unsigned char *)"in MEMORY CARD slot 1, reset or switch off the console.", 0 };
static unsigned char *MC_UNFORMAT_YN_CHECK[5] = { (unsigned char *)"The memory card (8MB)(for PlayStation\2562)", (unsigned char *)"is not formatted.", (unsigned char *)"Cannot access Your Network Configuration file.", (unsigned char *)"Continue check?", 0 };
static unsigned char *MC_NO_CARD_YN_CHECK[5] = { (unsigned char *)"The memory card (8MB)(for PlayStation\2562)", (unsigned char *)"is not inserted in MEMORY CARD slot 1.", (unsigned char *)"Cannot access Your Network Configuration file.", (unsigned char *)"Continue check?", 0 };
static unsigned char *MC_CHECK_ERR_YN_CHECK[5] = { (unsigned char *)"The memory card (8MB)(for PlayStation\2562)", (unsigned char *)"could not be found.", (unsigned char *)"Cannot access Your Network Configuration file.", (unsigned char *)"Continue check?", 0 };
static unsigned char *MC_NO_YNCF_YN_CHECK[4] = { (unsigned char *)"No Your Network Configuratio file", (unsigned char *)"found on memory card (8MB)(for PlayStation\2562).", (unsigned char *)"Continue check?", 0 };
static unsigned char *NETCNF_CHECKING[4] = { (unsigned char *)"Checking Your Network Configuratio file...", (unsigned char *)"Do not remove memory card (8MB)(for PlayStation\2562)", (unsigned char *)"in MEMORY CARD slot 1, reset or switch off the console.", 0 };
static unsigned char *NETCNF_NO_NET_YN_CHECK[4] = { (unsigned char *)"No network configuration", (unsigned char *)"in Your Network Configuratio file", (unsigned char *)"Continue check?", 0 };
static unsigned char *NETCNF_NO_IFC_YN_CHECK[4] = { (unsigned char *)"No Internet service provider setting", (unsigned char *)"in Your Network Configuratio file", (unsigned char *)"Continue check?", 0 };
static unsigned char *NETCNF_ERR_YN_CHECK[5] = { (unsigned char *)"Your Network Configuration file was", (unsigned char *)"not found.", (unsigned char *)"Cannot access Your Network Configuration file.", (unsigned char *)"Continue check?", 0 };
static unsigned char *NETCNF_LETHAL_ERR_YN_CHECK[5] = { (unsigned char *)"Your Network Configuration file is", (unsigned char *)"corrupted.", (unsigned char *)"Cannot access Your Network Configuration file.", (unsigned char *)"Continue check?", 0 };
static unsigned char *NETCNF_MAGIC_ERR_YN_CHECK[5] = { (unsigned char *)"Your Network Configuration file was", (unsigned char *)"created by another PlayStation\2562,", (unsigned char *)"and cannot be used.", (unsigned char *)"Continue check?", 0 };
static unsigned char *WARNING_HOWTO_EDIT[4] = { (unsigned char *)"Your Network Configuration file", (unsigned char *)"can be edited using a", (unsigned char *)"NETWORK ADAPTOR START-UP DISC.", 0 };
static unsigned char *WARNING_NOT_AVAILABLE[3] = { (unsigned char *)"This Internet service provider setting", (unsigned char *)"is not available.", 0 };
static unsigned char *SELECT_IFC[2] = { (unsigned char *)"Select Internet service provider setting.", 0 };
static unsigned char *BASE_TITLE[2] = { (unsigned char *)"Configuration", 0 };
static unsigned char *UPNP_YN[4] = { (unsigned char *)"Attempting to determine network settings", (unsigned char *)"automatically during initialization.", (unsigned char *)"OK to proceed?", 0 };
static unsigned char *UPNP_EXP[3] = { (unsigned char *)"These settings can be changed at any time", (unsigned char *)"from the Options menu.", 0 };
static unsigned char *IRX_LOADING[2] = { (unsigned char *)"Setting up...", 0 };
static unsigned char *IRX_LOAD_ERR[2] = { (unsigned char *)"Setup failed.", 0 };
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
