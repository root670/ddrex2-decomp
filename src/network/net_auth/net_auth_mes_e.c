static unsigned char *ITEM_DDR_ID[2] = { 0 };
static unsigned char *ITEM_PASSWORD[2] = { 0 };
static unsigned char *ITEM_AUTHENTICATION[2] = { 0 };
static unsigned char *ITEM_LOGOUT[2] = { 0 };
static unsigned char *EXP_DDR_ID[2] = { 0 };
static unsigned char *EXP_PASSWORD[2] = { 0 };
static unsigned char *EXP_AUTHENTICATION[2] = { 0 };
static unsigned char *EXP_LOGOUT[2] = { 0 };
static unsigned char *AUTH_RUN[2] = { 0 };
static unsigned char *AUTH_OK[2] = { 0 };
static unsigned char *AUTH_ABORT[2] = { 0 };
static unsigned char *AUTH_ABORT_YN[2] = { 0 };
static unsigned char *IDGET_GET_YN[3] = { 0 };
static unsigned char *IDGET_SAVE_YN[4] = { 0 };
static unsigned char *IDGET_FINAL_YN[3] = { 0 };
static unsigned char *HOWTO_GET_DDR_ID[4] = { 0 };
static unsigned char *LOGOUT_YN[2] = { 0 };
static unsigned char *IDMENU_MENU[4] = { 0 };
static unsigned char *IDMENU_EXP_ENTRY[3] = { 0 };
static unsigned char *IDMENU_EXP_CHPASS[2] = { 0 };
static unsigned char *IDMENU_EXP_CANCEL[2] = { 0 };
static unsigned char *ENTRY_CANCELED[2] = { 0 };
static unsigned char *ENTRY_INPUT_ID[3] = { 0 };
static unsigned char *ENTRY_INPUT_PASS1[2] = { 0 };
static unsigned char *ENTRY_INPUT_PASS2[2] = { 0 };
static unsigned char *ENTRY_INPUT_ERR_PASS_NOT_MATCH[2] = { 0 };
static unsigned char *ENTRY_RUN[2] = { 0 };
static unsigned char *ENTRY_OK[2] = { 0 };
static unsigned char *CHANGE_CANCELED[2] = { 0 };
static unsigned char *CHANGE_INPUT_ID[2] = { 0 };
static unsigned char *CHANGE_INPUT_PASS1[2] = { 0 };
static unsigned char *CHANGE_INPUT_PASS2[2] = { 0 };
static unsigned char *CHANGE_INPUT_PASS3[2] = { 0 };
static unsigned char *CHANGE_INPUT_ERR_PASS_NOT_MATCH[2] = { 0 };
static unsigned char *CHANGE_INPUT_ERR_PASS_SAME[3] = { 0 };
static unsigned char *CHANGE_RUN[2] = { 0 };
static unsigned char *CHANGE_OK[2] = { 0 };
unsigned char **naMessageTbl_ENGLISH[37];
unsigned char *cmes_yesno_str_english[];

unsigned char *namesGetNo(void)
{
    return cmes_yesno_str_english[0];
}

unsigned char *namesGetYes(void)
{
    return cmes_yesno_str_english[1];
}

unsigned char **namesGetMessageTable(int id)
{
    unsigned char **ret;

    ret = 0;
    if (0 <= id && id < 0x25) {
        ret = naMessageTbl_ENGLISH[id];
    }
    return ret;
}
