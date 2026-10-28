#include "src/network/usa_client/ddrex2_usa_gate.h"

int ddrnet_only_request(struct _ddrnet_con *con, int msgid);
int ddrnet_only_get_result(struct _mio_message *msg, int msgid, int *result);
void mio_unpack_start(struct _mio_message *msg);
void mio_unpack_end(struct _mio_message *msg);
int mio_get_u32(struct _mio_message *msg, unsigned int *value);
int mio_get_32(struct _mio_message *msg, int *value);
int mio_get_16(struct _mio_message *msg, short *value);
int mio_get_u16(struct _mio_message *msg, unsigned short *value);
int mio_get_8(struct _mio_message *msg, char *value);
int mio_get_strn(struct _mio_message *msg, char *value, int size);
int mio_get_vstr(struct _mio_message *msg, char *value, char delim);
int mio_check_bp(struct _mio_message *msg);
void func_001BBDB0(void *addr, int value, int size);

int ddrnet_gate_req_svrlist(struct _ddrnet_con *con)
{
    int ret;

    ret = ddrnet_only_request(con, 0x2005);
    return ret;
}

int ddrnet_gate_req_svrtime(struct _ddrnet_con *con)
{
    int ret;

    ret = ddrnet_only_request(con, 0x2006);
    return ret;
}

int ddrnet_gate_req_infolist(struct _ddrnet_con *con)
{
    int ret;

    ret = ddrnet_only_request(con, 0x2008);
    return ret;
}

int ddrnet_gate_res_infoliststart(struct _mio_message *msg, int *result)
{
    int ret;

    ret = ddrnet_only_get_result(msg, 0x2009, result);
    return ret;
}

int ddrnet_gate_res_svrtime(struct _mio_message *msg, unsigned int *time)
{
    if (msg == 0 || time == 0) {
        return -0x18;
    }
    if (msg->msgid != 0x2007) {
        return -0x46;
    }
    mio_unpack_start(msg);
    mio_get_u32(msg, time);
    mio_unpack_end(msg);
    return 0;
}

int ddrnet_gate_res_svrliststart(struct _mio_message *msg, struct _ddrnet_svrlist *list, int *result)
{
    int ret;
    int i;
    struct _ddrnet_svr *svr;

    if (msg == 0 || list == 0 || result == 0) {
        return -0x18;
    }
    mio_unpack_start(msg);
    ret = mio_get_32(msg, result);
    mio_unpack_end(msg);
    if (ret != 0) {
        return ret;
    }
    list->count = 0;
    i = 0;
    do {
        svr = &list->entry[i];
        svr->svid = 0;
        svr->svtype = 0;
        func_001BBDB0(svr->svname, 0, 0x11);
        func_001BBDB0(svr->svaddr, 0, 0x10);
        svr->svport = 0;
        svr->ucount = 0;
        svr->svrgid = 0;
        i++;
    } while (i < 0xC8);
    return 0;
}

int ddrnet_gate_res_infolist(struct _mio_message *msg, struct _ddrnet_infolist *list)
{
    struct _ddrnet_info *info;

    if (msg == 0 || list == 0) {
        return -0x18;
    }
    mio_unpack_start(msg);
    info = &list->entry[list->count];
    mio_get_u32(msg, &info->id);
    mio_get_8(msg, &info->important);
    mio_get_8(msg, &info->present);
    func_001BBDB0(info->reldate, 0, 0x14);
    mio_get_strn(msg, info->reldate, 0x13);
    func_001BBDB0(info->title, 0, 0x41);
    mio_get_strn(msg, info->title, 0x40);
    func_001BBDB0(info->text, 0, 0x201);
    mio_get_vstr(msg, info->text, 0);
    mio_unpack_end(msg);
    list->count++;
    return 0;
}

int ddrnet_gate_res_svrlist(struct _mio_message *msg, struct _ddrnet_svrlist *list)
{
    int i;
    struct _ddrnet_svr *svr;

    if (msg == 0 || list == 0) {
        return -0x18;
    }
    mio_unpack_start(msg);
    i = list->count;
    while (i < 0xC8) {
        if (mio_check_bp(msg) == -1) {
            break;
        }
        svr = &list->entry[i];
        mio_get_32(msg, &svr->svid);
        mio_get_32(msg, &svr->svtype);
        mio_get_strn(msg, svr->svname, 0x10);
        mio_get_strn(msg, svr->svaddr, 0xF);
        mio_get_u16(msg, &svr->svport);
        mio_get_16(msg, &svr->ucount);
        mio_get_u16(msg, &svr->svrgid);
        i++;
    }
    mio_unpack_end(msg);
    list->count = i;
    return 0;
}
