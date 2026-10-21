static unsigned char *ITEM_DDR_ID[2] = { (unsigned char *)"DDREX2 ID", 0 };
static unsigned char *ITEM_PASSWORD[2] = { (unsigned char *)"PASSWORD", 0 };
static unsigned char *ITEM_AUTHENTICATION[2] = { (unsigned char *)"AUTHENTICATION", 0 };
static unsigned char *ITEM_LOGOUT[2] = { (unsigned char *)"LOGOUT", 0 };
static unsigned char *EXP_DDR_ID[2] = { (unsigned char *)"Please enter your DDREX2 ID.", 0 };
static unsigned char *EXP_PASSWORD[2] = { (unsigned char *)"Please enter your Password.", 0 };
static unsigned char *EXP_AUTHENTICATION[2] = { (unsigned char *)"Proceeding to authenticate.", 0 };
static unsigned char *EXP_LOGOUT[2] = { (unsigned char *)"Logout.", 0 };
static unsigned char *AUTH_RUN[2] = { (unsigned char *)"Authenticating...", 0 };
static unsigned char *AUTH_OK[2] = { (unsigned char *)"Authenticated.", 0 };
static unsigned char *AUTH_ABORT[2] = { (unsigned char *)"Authentication aborted.", 0 };
static unsigned char *AUTH_ABORT_YN[2] = { (unsigned char *)"Abort authentication?", 0 };
static unsigned char *IDGET_GET_YN[3] = { (unsigned char *)"You need a DDREX2 ID for Online Play.", (unsigned char *)"Get a DDREX2 ID?", 0 };
static unsigned char *IDGET_SAVE_YN[4] = { (unsigned char *)"You need to reboot for getting", (unsigned char *)"a DDREX2 ID.", (unsigned char *)"Save system data before reboot?", 0 };
static unsigned char *IDGET_FINAL_YN[3] = { (unsigned char *)"Then it will be rebooted.", (unsigned char *)"Ok?", 0 };
static unsigned char *HOWTO_GET_DDR_ID[4] = { (unsigned char *)"If you don't have a DDREX2 ID,", (unsigned char *)"press the START button to go to", (unsigned char *)"the DDREX2 ID registration screen.", 0 };
static unsigned char *LOGOUT_YN[2] = { (unsigned char *)"Logout?", 0 };
static unsigned char *IDMENU_MENU[4] = { (unsigned char *)"NEW ENTRY", (unsigned char *)"CHANGE PASSWORD", (unsigned char *)"CANCEL", 0 };
static unsigned char *IDMENU_EXP_ENTRY[3] = { (unsigned char *)"Register a new DDREX2 ID.", (unsigned char *)"Your DDREX2 ID must be between 8 and 32 characters.", 0 };
static unsigned char *IDMENU_EXP_CHPASS[2] = { (unsigned char *)"Change Password.", 0 };
static unsigned char *IDMENU_EXP_CANCEL[2] = { (unsigned char *)"Cancel.", 0 };
static unsigned char *ENTRY_CANCELED[2] = { (unsigned char *)"Canceled.", 0 };
static unsigned char *ENTRY_INPUT_ID[3] = { (unsigned char *)"Enter new DDREX2 ID to create", (unsigned char *)"a new account.", 0 };
static unsigned char *ENTRY_INPUT_PASS1[2] = { (unsigned char *)"Enter Password.", 0 };
static unsigned char *ENTRY_INPUT_PASS2[2] = { (unsigned char *)"Enter Password again.", 0 };
static unsigned char *ENTRY_INPUT_ERR_PASS_NOT_MATCH[2] = { (unsigned char *)"Password does not match.", 0 };
static unsigned char *ENTRY_RUN[2] = { (unsigned char *)"Registering a new DDREX2 ID...", 0 };
static unsigned char *ENTRY_OK[2] = { (unsigned char *)"Registration successful.", 0 };
static unsigned char *CHANGE_CANCELED[2] = { (unsigned char *)"Canceled.", 0 };
static unsigned char *CHANGE_INPUT_ID[2] = { (unsigned char *)"Enter DDREX2 ID to change Password.", 0 };
static unsigned char *CHANGE_INPUT_PASS1[2] = { (unsigned char *)"Enter old Password.", 0 };
static unsigned char *CHANGE_INPUT_PASS2[2] = { (unsigned char *)"Enter new Password.", 0 };
static unsigned char *CHANGE_INPUT_PASS3[2] = { (unsigned char *)"Enter new Password again.", 0 };
static unsigned char *CHANGE_INPUT_ERR_PASS_NOT_MATCH[2] = { (unsigned char *)"Password does not match.", 0 };
static unsigned char *CHANGE_INPUT_ERR_PASS_SAME[3] = { (unsigned char *)"This password has been used before.", (unsigned char *)"Please create a new password.", 0 };
static unsigned char *CHANGE_RUN[2] = { (unsigned char *)"Updating...", 0 };
static unsigned char *CHANGE_OK[2] = { (unsigned char *)"Password has been changed.", 0 };
unsigned char **naMessageTbl_ENGLISH[37];
unsigned char *cmes_yesno_str_english[];

unsigned char *namesGetNo(void) {
    return cmes_yesno_str_english[0];
}

unsigned char *namesGetYes(void) {
    return cmes_yesno_str_english[1];
}

unsigned char **namesGetMessageTable(int id) {
    unsigned char **ret;

    ret = 0;
    if (0 <= id && id < 0x25) {
        ret = naMessageTbl_ENGLISH[id];
    }
    return ret;
}
