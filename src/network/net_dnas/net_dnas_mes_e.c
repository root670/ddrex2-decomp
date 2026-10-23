typedef struct {
    short lo;
    short hi;
    unsigned char *header;
    unsigned char *body;
    unsigned char *footer;
} anon_0_97;
typedef struct {
    short lo;
    short hi;
    unsigned char *message[8];
} anon_1_97;
struct sceDNAS2Status {
    int code;
    int sub_code;
    int progress;
    void *optional;
};
int func_001BE6F0(unsigned char *, int, unsigned char *, int);

static unsigned char *BASE_TITLE[2] = {
    (unsigned char *)"DNAS",
    0,
};

static unsigned char *NOTICE[3] = {
    (unsigned char *)"DNAS logotype is a trademark of",
    (unsigned char *)"Sony Computer Entertainment Inc.",
    0,
};

static unsigned char *AUTH_RUN[2] = {
    (unsigned char *)"Authenticating DNAS data...",
    0,
};

static unsigned char *AUTH_OK[2] = {
    (unsigned char *)"Authenticated.",
    0,
};

static unsigned char *AUTH_ERR[2] = {
    (unsigned char *)"Authentication failed.",
    0,
};

static unsigned char *SETUP[2] = {
    (unsigned char *)"Setting up...",
    0,
};

static unsigned char *SETUP_ERR[2] = {
    (unsigned char *)"Setup failed.",
    0,
};

unsigned char **ndMessageTbl_ENGLISH[7] = {
    BASE_TITLE,
    NOTICE,
    AUTH_RUN,
    AUTH_OK,
    AUTH_ERR,
    SETUP,
    SETUP_ERR,
};

anon_1_97 dnasErrorMsgs[8] = {
    {-101, -101, {(unsigned char *)"DNAS Error", (unsigned char *)"The network authentication server is busy.", (unsigned char *)"Please try again later."}},
    {-103, -102, {(unsigned char *)"DNAS Error", (unsigned char *)"This software title is not in service.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com."}},
    {-104, -104, {(unsigned char *)"DNAS Error", (unsigned char *)"The network authentication server", (unsigned char *)"is not in service.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com."}},
    {-105, -105, {(unsigned char *)"DNAS Error", (unsigned char *)"Connection to the network authentication server", (unsigned char *)"has timed out.", (unsigned char *)"Please try again later."}},
    {-108, -106, {(unsigned char *)"DNAS Error", (unsigned char *)"A network authentication system error", (unsigned char *)"has occurred.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com."}},
    {-403, -402, {(unsigned char *)"DNAS Error", (unsigned char *)"A PlayStation\2562 disc information error", (unsigned char *)"has occurred.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com."}},
    {-404, -401, {(unsigned char *)"DNAS Error", (unsigned char *)"A PlayStation\2562 hardware information error", (unsigned char *)"has occurred.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com."}},
    {-9999, 0, {(unsigned char *)"DNAS Error", (unsigned char *)"An authentication error has occured.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com."}},
};

anon_1_97 networkErrorMsgs[13] = {
    {-601, -601, {(unsigned char *)"Network Error", (unsigned char *)"Network connection has been aborted."}},
    {-602, -602, {(unsigned char *)"Network Error", (unsigned char *)"Error in proxy setting."}},
    {-603, -603, {(unsigned char *)"Network Error", (unsigned char *)"Connection timed out.", (unsigned char *)"Please try connecting again at a later time."}},
    {-610, -610, {(unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed."}},
    {-611, -611, {(unsigned char *)"Network Error", (unsigned char *)"There was an error in the response from", (unsigned char *)"the DNS server.", (unsigned char *)"Please check your network configuration."}},
    {-612, -612, {(unsigned char *)"Network Error", (unsigned char *)"There was no response from the DNS server.", (unsigned char *)"Please check your network configuration."}},
    {-614, -613, {(unsigned char *)"Network Error", (unsigned char *)"There was an error in the response from", (unsigned char *)"the DNS server.", (unsigned char *)"Please check your network configuration."}},
    {-615, -615, {(unsigned char *)"Network Error", (unsigned char *)"There was a DNS error.", (unsigned char *)"Please check your network configuration."}},
    {-616, -616, {(unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed."}},
    {-617, -617, {(unsigned char *)"Network Error", (unsigned char *)"Connection timed out.", (unsigned char *)"Please try connecting again at a later time."}},
    {-620, -618, {(unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed."}},
    {-626, -626, {(unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed."}},
    {-699, -600, {(unsigned char *)"Network Error", (unsigned char *)"There was a connection error."}},
};

static inline anon_1_97 *find(int code, anon_1_97 *tbl, unsigned int n) {
    anon_1_97 *p;
    unsigned int k;

    for (k = 0; k < n; k++) {
        p = &tbl[k];
        if (!(code < p->lo || p->hi < code)) {
            break;
        }
    }
    return p;
}

void ndmesMakeDNASErrorMessage(struct sceDNAS2Status *status, unsigned char *msgBuf) {
    anon_1_97 *e;
    unsigned char err_string[256];
    int i;
    int j;
    unsigned char *src;
    unsigned char *dst;

    func_001BE6F0(err_string, 256, (unsigned char *)" (%+d)", status->sub_code);
    if (status->code == 7) {
        e = find(status->sub_code, networkErrorMsgs, 13);
    } else {
        e = find(status->sub_code, dnasErrorMsgs, 8);
    }
    dst = msgBuf;
    for (i = 0; i < 8; i++) {
        src = e->message[i];
        if (src == 0) {
            break;
        }
        while (*src != 0) {
            *dst = *src;
            dst++;
            src++;
        }
        if (i == 0) {
            for (j = 0, src = err_string; j < 256; j++) {
                *dst = *src;
                if (*src == 0) {
                    break;
                }
                dst++;
                src++;
            }
        }
        *dst++ = 10;
    }
    dst[-1] = 0;
}

unsigned char **ndmesGetMessageTable(int id) {
    unsigned char **ret;

    ret = 0;
    if (0 <= id && id < 7) {
        ret = ndMessageTbl_ENGLISH[id];
    }
    return ret;
}

static void anon0_probe(anon_0_97 *p) { p->lo = 1; }
