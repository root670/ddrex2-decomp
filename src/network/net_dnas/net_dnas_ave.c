#include "src/network/net_dnas/net_dnas_ave.h"

extern unsigned char D_00808BF0[];

short SelectDevice(int device_uid);
short GetDeviceInfo(struct dginfo *buf, int bufnum);
short GetDeviceInfoNum(int *num);
short DnsDisp(void);
short DnsInit(unsigned char *def_domain, unsigned int prim_svr, unsigned int sec_svr);
short DhcpReleaseNb(unsigned int ipaddr, int retrans_cnt);
short DhcpTimer(void);
short DhcpGetIfInfo(unsigned int *ip_addr, unsigned int *netmask, unsigned int *bcaddr);
short DhcpRequestNb(unsigned int lease_time, int max_retry_cnt);
short DhcpGetGateway(unsigned int *gateway);
short DhcpGetDns(unsigned char *domain, unsigned int *pr_server, unsigned int *se_server);
short DhcpDisp(void);
short DhcpInit(void);
short NdgFinish(void);
short NdgStartPollStatus(void);
short NdgStart(int mode);
short NdgDisp(void);
short NdgInit(void);
short PppStatus(struct pp_status *pp_status);
short PppFinish(void);
short PppStart(short use_ipcp, short dialtype, char *telephone_number, char *login, char *password, char *outside_number, char *at_command, short use_pppoe, int eth_nego);
short PppDisp(void);
short PppInit(void);
short RouteDel(unsigned int dstaddr, unsigned int gtwayaddr);
short RouteAdd(unsigned int dstaddr, unsigned int gtwayaddr);
short Ifdown(void);
short Ifconfig(unsigned int ipaddr, unsigned int netmask, unsigned int broadcast);
short TcpTerminate(void);
short TcpInitialize(void);

void func_0010E748(char *fmt, ...);
void func_001BCFA8(char *fmt, ...);
void func_001BEE58(void *dst, void *src);
void func_001B7C30(void *p, int size);
int func_001B7B08(unsigned char *p);

static struct _tag_cNetDnasAve _pNetDnasAve = { 0 };
extern struct _tag_cNetDnasAve *pNetDnasAve;

int setup_ave_for_dnas_init(struct sceNetcnfifData *net_cnf_data)
{
    func_001B7C30(pNetDnasAve, 0xD6C);
    pNetDnasAve->phase = 0;
    pNetDnasAve->disp_phase = -1;
    pNetDnasAve->err_code = 0;
    pNetDnasAve->net_cnf = net_cnf_data;
    pNetDnasAve->config_type = 0;
    pNetDnasAve->iftype = 0;
    pNetDnasAve->ether_init_timeout = 0;
    pNetDnasAve->wait = 0;
    return 1;
}

int setup_ave_for_dnas_main(void)
{
    int result;
    short ret;
    int select_index;
    int i;
    int val;
    int ret_val;
    struct dginfo *dginfo;
    struct pp_status stat;

    ret_val = 0;
    switch (pNetDnasAve->phase) {
    case 0:
        pNetDnasAve->phase = 1;
        pNetDnasAve->device_num = GetDeviceInfo(pNetDnasAve->device_info, 4);
        func_0010E748("GetDeviceInfo=%d\n", pNetDnasAve->device_num);
        break;
    case 1:
        ret = GetDeviceInfoNum(&pNetDnasAve->device_num);
        func_0010E748("GetDeviceInfoNum=%d\n", ret);
        if (ret != 0) {
            func_0010E748("GetDeviceInfo=%d\n", GetDeviceInfo(pNetDnasAve->device_info, 4));
        }
        select_index = -1;
        for (i = 0; i < 4; i++) {
            dginfo = &pNetDnasAve->device_info[i];
            if (dginfo->bustype == 1 && dginfo->iftype == 1) {
                select_index = i;
                break;
            }
        }
        func_0010E748("select_index=%d\n", select_index);
        if (select_index == -1) {
            pNetDnasAve->err_code = -1;
            pNetDnasAve->phase = 0x17;
        } else {
            SelectDevice(pNetDnasAve->device_info[select_index].uid);
            pNetDnasAve->phase = 2;
        }
        break;
    case 2:
        if (pNetDnasAve->net_cnf->dhcp == 1) {
            func_0010E748("DHCP\n");
            pNetDnasAve->config_type = 1;
            pNetDnasAve->iftype = 0;
        } else if (pNetDnasAve->net_cnf->pppoe == 1) {
            func_0010E748("PPPoE\n");
            pNetDnasAve->config_type = 2;
            pNetDnasAve->iftype = 1;
        } else {
            func_0010E748("fixed IP\n");
            pNetDnasAve->config_type = 0;
            pNetDnasAve->iftype = 0;
        }
        pNetDnasAve->phase = 3;
        break;
    case 3:
        if (TcpInitialize() != 0) {
            pNetDnasAve->disp_phase = -1;
            pNetDnasAve->err_code = -2;
            pNetDnasAve->phase = 0x17;
        } else {
            pNetDnasAve->phase = 4;
        }
        break;
    case 4:
        if (pNetDnasAve->iftype == 1) {
            ret = PppInit();
        } else {
            ret = NdgInit();
        }
        func_001BCFA8("network driver init ret %d\n", ret);
        if (ret != 0) {
            pNetDnasAve->err_code = -3;
            pNetDnasAve->phase = 0x17;
            pNetDnasAve->disp_phase = 0x13;
        } else {
            pNetDnasAve->phase = 5;
        }
        break;
    case 5:
        switch ((unsigned int)pNetDnasAve->net_cnf->phy_config + 1) {
        default:
        case 0:
        case 1:
        case 2:
        case 5:
            val = 0;
            break;
        case 3:
            val = 1;
            break;
        case 4:
            val = 2;
            break;
        case 6:
            val = 3;
            break;
        case 7:
            val = 4;
            break;
        }
        if (pNetDnasAve->iftype == 1) {
            ret = PppStart(1, 0, (char *)D_00808BF0, pNetDnasAve->net_cnf->auth_name,
                           pNetDnasAve->net_cnf->auth_key, (char *)D_00808BF0,
                           (char *)D_00808BF0,
                           pNetDnasAve->config_type == 2, val);
        } else {
            ret = NdgStart(val);
            pNetDnasAve->ether_init_timeout = 0xA;
        }
        func_001BCFA8("network driver start ret %d\n", ret);
        if (ret != 0) {
            pNetDnasAve->err_code = -4;
            pNetDnasAve->phase = 0x17;
            pNetDnasAve->disp_phase = 0x12;
        } else {
            pNetDnasAve->phase = 6;
        }
        break;
    case 6:
        if (pNetDnasAve->iftype == 1) {
            if (pNetDnasAve->wait == 0) {
                PppStatus(&stat);
                if (stat.phase == 8) {
                    func_0010E748("ERROR: PPP Phase ==> Fail (error %d)\n",
                                stat.last_error);
                    pNetDnasAve->err_code = -5;
                    pNetDnasAve->phase = 0x17;
                    pNetDnasAve->disp_phase = 0x10;
                } else if (stat.phase == 4) {
                    pNetDnasAve->domain[0] = 0;
                    pNetDnasAve->prsvr = stat.ipcpOpts.my_dns1;
                    pNetDnasAve->sesvr = stat.ipcpOpts.my_dns2;
                    pNetDnasAve->phase = 9;
                } else {
                    pNetDnasAve->wait = 0xA;
                }
            } else {
                pNetDnasAve->wait = pNetDnasAve->wait - 1;
            }
        } else {
            if (pNetDnasAve->wait == 0) {
                if (NdgStartPollStatus() == 1) {
                    if (pNetDnasAve->config_type == 1) {
                        pNetDnasAve->phase = 7;
                    } else {
                        pNetDnasAve->my_ipaddr =
                            aton((unsigned char *)pNetDnasAve->net_cnf->address);
                        pNetDnasAve->my_ipaddr =
                            ((pNetDnasAve->my_ipaddr >> 24) & 0xFF) |
                            ((pNetDnasAve->my_ipaddr >> 8) & 0xFF00) |
                            ((pNetDnasAve->my_ipaddr << 8) & 0xFF0000) |
                            ((pNetDnasAve->my_ipaddr << 24) & 0xFF000000);
                        func_0010E748("my_ipaddr =%08x(%s)\n",
                                    pNetDnasAve->my_ipaddr,
                                    pNetDnasAve->net_cnf->address);
                        pNetDnasAve->my_netmask =
                            aton((unsigned char *)pNetDnasAve->net_cnf->netmask);
                        pNetDnasAve->my_netmask =
                            ((pNetDnasAve->my_netmask >> 24) & 0xFF) |
                            ((pNetDnasAve->my_netmask >> 8) & 0xFF00) |
                            ((pNetDnasAve->my_netmask << 8) & 0xFF0000) |
                            ((pNetDnasAve->my_netmask << 24) & 0xFF000000);
                        func_0010E748("my_netmask=%08x(%s)\n",
                                    pNetDnasAve->my_netmask,
                                    pNetDnasAve->net_cnf->netmask);
                        pNetDnasAve->my_bcast = (~pNetDnasAve->my_netmask) |
                            (pNetDnasAve->my_ipaddr & pNetDnasAve->my_netmask);
                        pNetDnasAve->my_bcast =
                            ((pNetDnasAve->my_bcast >> 24) & 0xFF) |
                            ((pNetDnasAve->my_bcast >> 8) & 0xFF00) |
                            ((pNetDnasAve->my_bcast << 8) & 0xFF0000) |
                            ((pNetDnasAve->my_bcast << 24) & 0xFF000000);
                        func_0010E748("my_bcast  =%08x\n",
                                    pNetDnasAve->my_bcast);
                        pNetDnasAve->gateway =
                            aton((unsigned char *)pNetDnasAve->net_cnf->gateway);
                        pNetDnasAve->gateway =
                            ((pNetDnasAve->gateway >> 24) & 0xFF) |
                            ((pNetDnasAve->gateway >> 8) & 0xFF00) |
                            ((pNetDnasAve->gateway << 8) & 0xFF0000) |
                            ((pNetDnasAve->gateway << 24) & 0xFF000000);
                        func_0010E748("gateway   =%08x(%s)\n",
                                    pNetDnasAve->gateway,
                                    pNetDnasAve->net_cnf->gateway);
                        func_001BEE58(pNetDnasAve->domain, D_00808BF0);
                        pNetDnasAve->prsvr =
                            aton((unsigned char *)pNetDnasAve->net_cnf->dns1_address);
                        pNetDnasAve->prsvr =
                            ((pNetDnasAve->prsvr >> 24) & 0xFF) |
                            ((pNetDnasAve->prsvr >> 8) & 0xFF00) |
                            ((pNetDnasAve->prsvr << 8) & 0xFF0000) |
                            ((pNetDnasAve->prsvr << 24) & 0xFF000000);
                        func_0010E748("prsvr     =%08x(%s)\n",
                                    pNetDnasAve->prsvr,
                                    pNetDnasAve->net_cnf->dns1_address);
                        pNetDnasAve->sesvr =
                            aton((unsigned char *)pNetDnasAve->net_cnf->dns2_address);
                        pNetDnasAve->sesvr =
                            ((pNetDnasAve->sesvr >> 24) & 0xFF) |
                            ((pNetDnasAve->sesvr >> 8) & 0xFF00) |
                            ((pNetDnasAve->sesvr << 8) & 0xFF0000) |
                            ((pNetDnasAve->sesvr << 24) & 0xFF000000);
                        func_0010E748("sesvr     =%08x(%s)\n",
                                    pNetDnasAve->sesvr,
                                    pNetDnasAve->net_cnf->dns2_address);
                        pNetDnasAve->phase = 9;
                    }
                } else {
                    pNetDnasAve->ether_init_timeout =
                        pNetDnasAve->ether_init_timeout - 1;
                    if (pNetDnasAve->ether_init_timeout <= 0) {
                        func_0010E748(
                            "ERROR: Ethernet device initialize timeout\n");
                        pNetDnasAve->err_code = -5;
                        pNetDnasAve->phase = 0x17;
                        pNetDnasAve->disp_phase = 0x10;
                    } else {
                        pNetDnasAve->wait = 0x3C;
                    }
                }
            } else {
                pNetDnasAve->wait = pNetDnasAve->wait - 1;
            }
        }
        break;
    case 7:
        ret = DhcpInit();
        if (ret != 0) {
            func_0010E748("DhcpInit error %d\n", ret);
            pNetDnasAve->err_code = -6;
            pNetDnasAve->phase = 0x17;
            pNetDnasAve->disp_phase = 0x10;
        } else {
            ret = DhcpRequestNb(0, 5);
            if (ret != 0) {
                func_0010E748("DhcpRequestNb error %d\n", ret);
                pNetDnasAve->err_code = -7;
                pNetDnasAve->phase = 0x17;
                pNetDnasAve->disp_phase = 0x10;
            } else {
                pNetDnasAve->phase = 8;
            }
        }
        break;
    case 8:
        if (pNetDnasAve->wait == 0) {
            result = DhcpTimer();
            func_0010E748("DhcpTimer ret %d\n", result);
            if (result == 3) {
                if (DhcpGetIfInfo(&pNetDnasAve->my_ipaddr,
                                  &pNetDnasAve->my_netmask,
                                  &pNetDnasAve->my_bcast) < 0) {
                    pNetDnasAve->err_code = -8;
                    pNetDnasAve->phase = 0x17;
                    pNetDnasAve->disp_phase = 0x10;
                } else {
                    func_0010E748("dhcp ip 0x%08x mask 0x%08x bcast 0x%08x\n",
                                pNetDnasAve->my_ipaddr,
                                pNetDnasAve->my_netmask,
                                pNetDnasAve->my_bcast);
                    if (DhcpGetGateway(&pNetDnasAve->gateway) < 0) {
                        pNetDnasAve->err_code = -9;
                        pNetDnasAve->phase = 0x17;
                        pNetDnasAve->disp_phase = 0x10;
                    } else {
                        func_0010E748("dhcp gw 0x%08x\n", pNetDnasAve->gateway);
                        if (DhcpGetDns(pNetDnasAve->domain,
                                       &pNetDnasAve->prsvr,
                                       &pNetDnasAve->sesvr) < 0) {
                            pNetDnasAve->err_code = -9;
                            pNetDnasAve->phase = 0x17;
                            pNetDnasAve->disp_phase = 0x10;
                        } else {
                            func_0010E748(
                                "dhcp domain %s svr1 %08x svr2 %08x\n",
                                pNetDnasAve->domain, pNetDnasAve->prsvr,
                                pNetDnasAve->sesvr);
                            pNetDnasAve->phase = 9;
                        }
                    }
                }
            } else if (result == -1 || result == -2) {
                func_0010E748("DhcpTimer error %d\n", result);
                pNetDnasAve->err_code = -0xB;
                pNetDnasAve->phase = 0x17;
                pNetDnasAve->disp_phase = 0x10;
            } else {
                pNetDnasAve->wait = 6;
            }
        } else {
            pNetDnasAve->wait = pNetDnasAve->wait - 1;
        }
        break;
    case 9:
        if (pNetDnasAve->iftype != 1) {
            if (Ifconfig(pNetDnasAve->my_ipaddr, pNetDnasAve->my_netmask,
                         pNetDnasAve->my_bcast) < 0) {
                pNetDnasAve->err_code = -0xC;
                pNetDnasAve->phase = 0x17;
                if (pNetDnasAve->config_type == 1) {
                    pNetDnasAve->disp_phase = 0xE;
                } else {
                    pNetDnasAve->disp_phase = 0x10;
                }
                break;
            }
            if (pNetDnasAve->gateway != 0 &&
                RouteAdd(0, pNetDnasAve->gateway) < 0) {
                pNetDnasAve->err_code = -0xD;
                pNetDnasAve->phase = 0x17;
                pNetDnasAve->disp_phase = 0xD;
                break;
            }
        }
        pNetDnasAve->err_code = 1;
        pNetDnasAve->phase = 0x17;
        pNetDnasAve->disp_phase = 0xD;
        result = DnsInit(pNetDnasAve->domain, pNetDnasAve->prsvr,
                         pNetDnasAve->sesvr);
        func_0010E748("DnsInit ret %d\n", result);
        if (result < 0) {
            pNetDnasAve->err_code = -0xE;
            pNetDnasAve->phase = 0x17;
            pNetDnasAve->disp_phase = 0xD;
        }
        break;
    case 23:
        func_0010E748("disp_phase=%d\n", pNetDnasAve->disp_phase);
        ret_val = pNetDnasAve->err_code;
        break;
    }
    return ret_val;
}

static unsigned int aton(unsigned char *addr)
{
    unsigned char *p;
    int i;
    int j;
    unsigned char buf[512];
    int n;
    unsigned int addr32;
    unsigned int uval;

    j = 0;
    i = 0;
    n = 3;
    addr32 = 0;
    for (i = 0; i < 0x100; i++) {
        p = &addr[i];
        if (*p >= '0' && *p < ':') {
            buf[j] = *p;
            j++;
        } else {
            if (*p == '.' || *p == 0) {
                buf[j] = 0;
                uval = func_001B7B08(buf);
                addr32 |= (uval & 0xFF) << (n * 8);
                n--;
                j = 0;
                if (n < 0) {
                    break;
                }
            }
            if (*p == 0) {
                break;
            }
        }
    }
    return addr32;
}

int reset_ave_for_dnas_init(void)
{
    pNetDnasAve->phase = 0;
    pNetDnasAve->wait = 0;
    return 1;
}

int reset_ave_for_dnas_main(void)
{
    short ret;
    int ret_val;
    struct pp_status stat;

    ret_val = 0;
    switch (pNetDnasAve->phase) {
    case 0:
        if (pNetDnasAve->disp_phase == -1) {
            pNetDnasAve->phase = 0x17;
        } else {
            pNetDnasAve->phase = pNetDnasAve->disp_phase;
        }
        break;
    case 13:
        ret = DnsDisp();
        func_0010E748("DnsDisp ret %d\n", ret);
        if (pNetDnasAve->iftype == 1) {
            pNetDnasAve->phase = 0x10;
        } else {
            func_0010E748("RouteDel (%08x) ret %d\n", pNetDnasAve->gateway,
                        RouteDel(0, pNetDnasAve->gateway));
            func_0010E748("Ifdown ret %d\n", Ifdown());
            if (pNetDnasAve->config_type == 1) {
                pNetDnasAve->phase = 0xE;
            } else {
                pNetDnasAve->phase = 0x10;
            }
        }
        break;
    case 14:
        ret = DhcpReleaseNb(pNetDnasAve->my_ipaddr, 5);
        if (ret != 0) {
            func_0010E748("DhcpRlease error %d\n", ret);
            DhcpDisp();
            func_0010E748("DhcpDisp\n");
            pNetDnasAve->phase = 0x10;
        } else {
            pNetDnasAve->phase = 0xF;
        }
        break;
    case 15:
        if (pNetDnasAve->wait == 0) {
            ret = DhcpTimer();
            func_0010E748("DhcpTimer ret %d\n", ret);
            if (ret == 0 || ret == -2 || ret == -1) {
                DhcpDisp();
                func_0010E748("DhcpDisp\n");
                pNetDnasAve->phase = 0x10;
            } else {
                pNetDnasAve->wait = 6;
            }
        } else {
            pNetDnasAve->wait = pNetDnasAve->wait - 1;
        }
        break;
    case 16:
        if (pNetDnasAve->iftype == 1) {
            func_0010E748("PppFinish ret %d\n", PppFinish());
            pNetDnasAve->phase = 0x11;
        } else {
            func_0010E748("NdgFinish ret %d\n", NdgFinish());
            pNetDnasAve->phase = 0x12;
        }
        break;
    case 17:
        if (pNetDnasAve->iftype == 1) {
            if (pNetDnasAve->wait == 0) {
                PppStatus(&stat);
                if (stat.phase == 0) {
                    pNetDnasAve->phase = 0x12;
                }
                pNetDnasAve->wait = 0xA;
            } else {
                pNetDnasAve->wait = pNetDnasAve->wait - 1;
            }
        }
        break;
    case 18:
        if (pNetDnasAve->iftype == 1) {
            func_0010E748("PppDisp ret %d\n", PppDisp());
        } else {
            func_0010E748("NdgDisp ret %d\n", NdgDisp());
        }
        pNetDnasAve->phase = 0x13;
        break;
    case 19:
        func_0010E748("TcpTerminate ret %d\n", TcpTerminate());
        pNetDnasAve->phase = 0x17;
        break;
    case 23:
        ret_val = 1;
        break;
    }
    return ret_val;
}
