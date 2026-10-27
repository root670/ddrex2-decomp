#include "types/_NETWORK_W.h"

int NsNetLogin(void);
void NetToLogout(struct _NETWORK_W *);
void NetRouterMain(struct _NETWORK_W *);

static void NetSysConnectMain(struct _NETWORK_W *netw);







void NetSysConnectInit(struct _NETWORK_W *netw) {
    netw->NewFunc = NetSysConnectMain;
}

static void NetSysConnectMain(struct _NETWORK_W *netw) {
    int answer;







    switch (netw->step) {

    case 0:
        netw->step = 1;
        break;
    case 1:


        answer = NsNetLogin();
        if (answer == 1) {
            netw->step = 2;
        } else if (answer < 0) {
            netw->step = 4;
        }
        break;
    case 2:











        netw->step = 3;
        break;
    case 3:


        netw->NewFunc = NetRouterMain;
        break;
    case 4:

        netw->NewFunc = NetToLogout;
        break;
    }
}
