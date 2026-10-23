static unsigned char *ERR_SERVERNOTREADY[3] = {
    (unsigned char *)"Authentication failed.",
    (unsigned char *)"Network server is unavailable.",
    0,
};
static unsigned char *ERR_LOGIN_FAILED[3] = {
    (unsigned char *)"Authenticate failed.",
    (unsigned char *)"DDREX2 ID or password is incorrect.",
    0,
};
static unsigned char *ERR_ALREADYLOGGEDIN[3] = {
    (unsigned char *)"Authenticate failed.",
    (unsigned char *)"This DDREX2 ID is currently in use.",
    0,
};
static unsigned char *ERR_ETC[2] = {
    (unsigned char *)"Authentication failed.",
    0,
};
static unsigned char *REG_ERR_ETC[2] = {
    (unsigned char *)"Failed.",
    0,
};
static unsigned char *REG_ERR_NGWORDS[3] = {
    (unsigned char *)"Failed.",
    (unsigned char *)"It includes taboo word(s).",
    0,
};
static unsigned char *REG_ERR_USED[4] = {
    (unsigned char *)"Registration failed.",
    (unsigned char *)"This DDREX2 ID is already registered",
    (unsigned char *)"by another user.",
    0,
};
static unsigned char *CHG_ERR_ETC[2] = {
    (unsigned char *)"Password changed failed.",
    0,
};
static unsigned char *CHG_ERR_OLDPASS[3] = {
    (unsigned char *)"Password changed failed.",
    (unsigned char *)"DDREX2ID or password is incorrect.",
    0,
};
int func_001BE6F0(unsigned char *buf, int size, char *fmt, int v);

void namesMakeChangeMessage(int code, unsigned char *msg) {
    unsigned char **table;
    unsigned char *line;
    unsigned char err_string[256];
    int i;

    if (code == 10) {
        table = CHG_ERR_OLDPASS;
    } else {
        table = CHG_ERR_ETC;
    }
    for (line = *table; line != 0; line = *table) {
        while (*line != 0) {
            *msg++ = *line++;
        }
        *msg++ = 10;
        table++;
    }
    func_001BE6F0(err_string, 256, "(%+d)\0\0\0", code);
    for (i = 0; i < 256; i++) {
        *msg++ = err_string[i];
        if (err_string[i] == 0) {
            break;
        }
    }
}

void namesMakeRegisterMessage(int code, unsigned char *msg) {
    unsigned char **table;
    unsigned char *line;
    unsigned char err_string[256];
    int i;

    if (code == 7) {
        table = REG_ERR_NGWORDS;
    } else if (code == 8) {
        table = REG_ERR_USED;
    } else {
        table = REG_ERR_ETC;
    }
    for (line = *table; line != 0; line = *table) {
        while (*line != 0) {
            *msg++ = *line++;
        }
        *msg++ = 10;
        table++;
    }
    func_001BE6F0(err_string, 256, "(%+d)\0\0\0", code);
    for (i = 0; i < 256; i++) {
        *msg++ = err_string[i];
        if (err_string[i] == 0) {
            break;
        }
    }
}

void namesMakeAuthMessage(int code, unsigned char *msg) {
    unsigned char **table;
    unsigned char *line;
    unsigned char err_string[256];
    int i;

    if (code == -200) {
        table = ERR_SERVERNOTREADY;
    } else if (code == -240) {
        table = ERR_LOGIN_FAILED;
    } else if (code == -242) {
        table = ERR_ALREADYLOGGEDIN;
    } else {
        table = ERR_ETC;
    }
    for (line = *table; line != 0; line = *table) {
        while (*line != 0) {
            *msg++ = *line++;
        }
        *msg++ = 10;
        table++;
    }
    func_001BE6F0(err_string, 256, "(%+d)\0\0\0", code);
    for (i = 0; i < 256; i++) {
        *msg++ = err_string[i];
        if (err_string[i] == 0) {
            break;
        }
    }
}
