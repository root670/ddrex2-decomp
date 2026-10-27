static unsigned char *CHECKING[2] = {
    (unsigned char *)"Checking...",
    0,
};
static unsigned char *UPNP_YN[4] = {
    (unsigned char *)"Attempting to determine network settings",
    (unsigned char *)"automatically during initialization.",
    (unsigned char *)"OK to proceed?",
    0,
};
static unsigned char *UPNP_EXP[3] = {
    (unsigned char *)"These settings can be changed at any time",
    (unsigned char *)"from the Options menu.",
    0,
};
static unsigned char *BAD_ROUTER[3] = {
    (unsigned char *)"Please change your router settings",
    (unsigned char *)"in order to play Head-to-Head.",
    0,
};
unsigned char **nrMessageTbl_ENGLISH[4];
unsigned char *cmes_yesno_str_english[];

unsigned char *nrmesGetNo(void) {
    return cmes_yesno_str_english[0];
}

unsigned char *nrmesGetYes(void) {
    return cmes_yesno_str_english[1];
}

unsigned char **nrmesGetMessageTable(int id) {
    unsigned char **ret;

    ret = 0;
    if (0 <= id && id < 4) {
        ret = nrMessageTbl_ENGLISH[id];
    }
    return ret;
}
