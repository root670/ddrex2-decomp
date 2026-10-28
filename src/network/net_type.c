#include "src/network/net_type.h"

#define D_00F4D380 ((unsigned int *)0x00F4D380)
#define D_00F4D384 ((unsigned short *)0x00F4D384)
#define D_00F4D386 ((unsigned char *)0x00F4D386)
#define D_00F4D387 ((unsigned char *)0x00F4D387)
#define D_00F4D388 ((unsigned int *)0x00F4D388)
#define D_00F4D38C ((unsigned char *)0x00F4D38C)
#define D_00F4DB80 ((struct _NetPacketHeader *)0x00F4DB80)

extern struct _NS_NET_INFO_W *netiw;
void *func_001BBBF8(void *dst, void *src, unsigned int n);
void func_0011EEC0(void *ptr, int size);
int ddrnet_lobby_send_p2p(struct _ddrnet_con *con, void *data, int length);
unsigned int *EyeRefGetMyBitstreamAddr(void);
int EyeRefChangeMyBitstream(void);
int sendto(int s, void *msg, unsigned int len, int flags, void *to, int tolen);

static unsigned int net_type_work_size[9] = {
    0, 76, 24, 4, 24, 4, 36, 4, 12,
};

void *NsNetP2PRecv(anon_x82a28_44 type)
{
    void *rtn;
    rtn = 0;
    if (netiw->p2precv.get_type == type) {
        netiw->p2precv.get_type = 0;
        rtn = &netiw->p2precv.buff[4];
    }
    return rtn;
}

int NetP2PSendProgram(anon_x82a28_44 type, void *memory)
{
    int ret;
    int rtn;
    int data_size;
    struct _ddrnet_con *con;
    int *send_dt;
    data_size = net_type_work_size[type] + 4;
    if (netiw->send.sec_size_now + data_size > netiw->send.sec_size_max)
        return -1;
    con = &netiw->d2uc->conmgr.con[2];
    send_dt = (int *)&netiw->p2psend;
    if (con->sd > 0) {
        *send_dt = type;
        func_001BBBF8(send_dt + 1, memory, net_type_work_size[type]);
        ret = ddrnet_lobby_send_p2p(con, send_dt, data_size);
        if (ret == 0) {
            netiw->send.sec_size_now += data_size;
            rtn = 0;
        }
        else
            rtn = -1;
    }
    else
        rtn = -1;
    return rtn;
}

void *NetRecvProgramData(anon_x82a28_44 type, int counter, unsigned int flag)
{
    void *rtn;
    struct _NetPacketHeader *recv_h;
    unsigned char *recv_dt;
    int i;
    rtn = 0;
    recv_h = D_00F4DB80;
    for (i = 0; i < 10; i++) {
        if (netiw->recv.prog[i].type == type) {
            recv_dt = (unsigned char *)recv_h + 0xC;
            if (flag & 1) {
                netiw->recv.prog[i].type = 0;
                rtn = recv_dt;
                recv_h->status |= 1;
            }
            else if (recv_h->counter == counter) {
                netiw->recv.prog[i].type = 0;
                rtn = recv_dt;
                recv_h->status |= 1;
            }
        }
        recv_h = (struct _NetPacketHeader *)((unsigned char *)recv_h + 0x100);
    }
    return rtn;
}

int NetSendPicture(void)
{
    int rtn;
    if (netiw->send.pict.status & 1)
        rtn = -1;
    else {
        func_0011EEC0(&netiw->send.pict, 0x18);
        netiw->send.pict.status |= 1;
        netiw->send.pict.id = netiw->send.counter;
        netiw->send.pict.total_size = 0x5040;
        netiw->send.status |= 4;
        netiw->send.type = 2;
        netiw->send.pict.eye_buf = EyeRefGetMyBitstreamAddr();
        EyeRefChangeMyBitstream();
        netiw->send.counter = (netiw->send.counter + 1) & 0xFFFFFFF;
        rtn = netiw->send.pict.id;
    }
    return rtn;
}

int NetSendProgram(anon_x82a28_44 type, void *memory)
{
    int ret;
    int rtn;
    int data_size;
    data_size = net_type_work_size[type] + 0xC;
    if (netiw->send.sec_size_now + data_size > netiw->send.sec_size_max)
        return -1;
    *D_00F4D380 = netiw->send.counter;
    *D_00F4D384 = 0x4D2;
    *D_00F4D386 = type;
    *D_00F4D387 = 0;
    *D_00F4D388 = data_size;
    func_001BBBF8(D_00F4D38C, memory, net_type_work_size[type]);
    ret = sendto(netiw->sock[0].DC, D_00F4D380, data_size, 0, &netiw->sock[0].peer_addr, 0x10);
    if (ret == data_size) {
        netiw->send.type = 1;
        rtn = netiw->send.counter;
        netiw->send.sec_size_now += data_size;
        netiw->send.counter = (netiw->send.counter + 1) & 0xFFFFFFF;
    }
    else
        rtn = -1;
    return rtn;
}
