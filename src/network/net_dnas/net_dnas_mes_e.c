#include "src/network/net_dnas/net_dnas_mes_e.h"

void func_001BE6F0(unsigned char *buf, int size, unsigned char *fmt, ...);

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
    { .lo = -101, .hi = -101, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"The network authentication server is busy.", (unsigned char *)"Please try again later.", 0, 0, 0, 0, 0 } },
    { .lo = -103, .hi = -102, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"This software title is not in service.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com.", 0, 0, 0 } },
    { .lo = -104, .hi = -104, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"The network authentication server", (unsigned char *)"is not in service.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com.", 0, 0 } },
    { .lo = -105, .hi = -105, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"Connection to the network authentication server", (unsigned char *)"has timed out.", (unsigned char *)"Please try again later.", 0, 0, 0, 0 } },
    { .lo = -108, .hi = -106, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"A network authentication system error", (unsigned char *)"has occurred.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com.", 0, 0 } },
    { .lo = -403, .hi = -402, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"A PlayStation\2562 disc information error", (unsigned char *)"has occurred.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com.", 0, 0 } },
    { .lo = -404, .hi = -401, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"A PlayStation\2562 hardware information error", (unsigned char *)"has occurred.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com.", 0, 0 } },
    { .lo = -9999, .hi = 0, .message = { (unsigned char *)"DNAS Error", (unsigned char *)"An authentication error has occured.", (unsigned char *)"Please write down the error code number,", (unsigned char *)"and contact SCEA at 1-866-466-5333 or via", (unsigned char *)"SCEA's website, www.us.playstation.com.", 0, 0, 0 } },
};
anon_1_97 networkErrorMsgs[13] = {
    { .lo = -601, .hi = -601, .message = { (unsigned char *)"Network Error", (unsigned char *)"Network connection has been aborted.", 0, 0, 0, 0, 0, 0 } },
    { .lo = -602, .hi = -602, .message = { (unsigned char *)"Network Error", (unsigned char *)"Error in proxy setting.", 0, 0, 0, 0, 0, 0 } },
    { .lo = -603, .hi = -603, .message = { (unsigned char *)"Network Error", (unsigned char *)"Connection timed out.", (unsigned char *)"Please try connecting again at a later time.", 0, 0, 0, 0, 0 } },
    { .lo = -610, .hi = -610, .message = { (unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed.", 0, 0, 0, 0, 0, 0 } },
    { .lo = -611, .hi = -611, .message = { (unsigned char *)"Network Error", (unsigned char *)"There was an error in the response from", (unsigned char *)"the DNS server.", (unsigned char *)"Please check your network configuration.", 0, 0, 0, 0 } },
    { .lo = -612, .hi = -612, .message = { (unsigned char *)"Network Error", (unsigned char *)"There was no response from the DNS server.", (unsigned char *)"Please check your network configuration.", 0, 0, 0, 0, 0 } },
    { .lo = -614, .hi = -613, .message = { (unsigned char *)"Network Error", (unsigned char *)"There was an error in the response from", (unsigned char *)"the DNS server.", (unsigned char *)"Please check your network configuration.", 0, 0, 0, 0 } },
    { .lo = -615, .hi = -615, .message = { (unsigned char *)"Network Error", (unsigned char *)"There was a DNS error.", (unsigned char *)"Please check your network configuration.", 0, 0, 0, 0, 0 } },
    { .lo = -616, .hi = -616, .message = { (unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed.", 0, 0, 0, 0, 0, 0 } },
    { .lo = -617, .hi = -617, .message = { (unsigned char *)"Network Error", (unsigned char *)"Connection timed out.", (unsigned char *)"Please try connecting again at a later time.", 0, 0, 0, 0, 0 } },
    { .lo = -620, .hi = -618, .message = { (unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed.", 0, 0, 0, 0, 0, 0 } },
    { .lo = -626, .hi = -626, .message = { (unsigned char *)"Network Error", (unsigned char *)"Connection to the DNAS server failed.", 0, 0, 0, 0, 0, 0 } },
    { .lo = -699, .hi = -600, .message = { (unsigned char *)"Network Error", (unsigned char *)"There was a connection error.", 0, 0, 0, 0, 0, 0 } },
};

void ndmesMakeDNASErrorMessage(struct sceDNAS2Status *status, unsigned char *msgBuf)
{
    anon_1_97 *e;
    unsigned char err_string[0x100];
    int i;
    int j;
    unsigned char *src;
    unsigned char *dst;

    func_001BE6F0(err_string, 0x100, (unsigned char *)" (%+d)", status->sub_code);
    if (status->code == 7) {
        e = networkErrorMsgs;
        for (i = 0; i < sizeof(networkErrorMsgs) / sizeof(networkErrorMsgs[0]); i++, e++) {
            if (e->lo <= status->sub_code && status->sub_code <= e->hi) break;
        }
        goto out;
    }
    e = dnasErrorMsgs;
    for (i = 0; i < sizeof(dnasErrorMsgs) / sizeof(dnasErrorMsgs[0]); i++, e++) {
        if (e->lo <= status->sub_code && status->sub_code <= e->hi) break;
    }
out:
    dst = msgBuf;
    for (j = 0; j < 8; j++) {
        src = e->message[j];
        if (src == 0) break;
        while (*src) {
            *dst = *src;
            dst++;
            src++;
        }
        if (j == 0) {
            for (i = 0; i < 0x100; i++) {
                *dst = err_string[i];
                if (err_string[i] == 0) break;
                dst++;
            }
        }
        *dst++ = '\n';
    }
    dst[-1] = 0;
}

unsigned char **ndmesGetMessageTable(int id)
{
    unsigned char **ret;

    ret = 0;
    if (0 <= id && id < 7) ret = ndMessageTbl_ENGLISH[id];
    return ret;
}
