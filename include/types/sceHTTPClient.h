/* struct sceHTTPClient -- 81 members, size 0x210, layout 3cfaa2cc5646.
 *
 * One definition, agreed by the 1 unit that declares it: ddrex2_usa_id.c (DIE 0x3960F8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceHTTPClient *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: ddrex2_usa_id.c (DIE 0x3960F8)
 */
#ifndef DDR_types_sceHTTPClient_H
#define DDR_types_sceHTTPClient_H

struct sceHTTPHeaderList;
struct sceHTTPParsedURI;
struct sceHTTPResponse;

#include "types/sceHTTPHeaderList.h"
#include "types/sceHTTPParsedURI.h"
#include "types/sceHTTPResponse.h"

struct sceHTTPClient {   // size 0x210
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ int http_ver;                         // 0x4
    /* 0x008 */ int http_rev;                         // 0x4
    /* 0x00C */ int rtimeout;                         // 0x4
    /* 0x010 */ int ttimeout;                         // 0x4
    /* 0x014 */ int laptime;                          // 0x4
    /* 0x018 */ int prot;                             // 0x4
    /* 0x01C */ int state;                            // 0x4
    /* 0x020 */ int errnum;                           // 0x4
    /* 0x024 */ int net_errno;                        // 0x4
    /* 0x028 */ int net_herrno;                       // 0x4
    /* 0x02C */ int reloading;                        // 0x4
    /* 0x030 */ int keep_alive;                       // 0x4
    /* 0x034 */ int keep_count;                       // 0x4
    /* 0x038 */ int non_blocking;                     // 0x4
    /* 0x03C */ int abort_req;                        // 0x4
    /* 0x040 */ int otimeout;                         // 0x4
    /* 0x044 */ int c_wait0;                          // 0x4
    /* 0x048 */ int c_wait1;                          // 0x4
    /* 0x04C */ int c_tcount;                         // 0x4
    /* 0x050 */ int c_timer;                          // 0x4
    /* 0x054 */ int t_stacksize;                      // 0x4
    /* 0x058 */ int t_priority;                       // 0x4
    /* 0x05C */ int t_thread;                         // 0x4
    /* 0x060 */ void *t_stack;                        // 0x4
    /* 0x064 */ int t_rtn;                            // 0x4
    /* 0x068 */ void (*t_notify)(struct sceHTTPClient *, int, void *);  // 0x4
    /* 0x06C */ void *t_notify_opt;                   // 0x4
    /* 0x070 */ void *t_notify_gp;                    // 0x4
    /* 0x074 */ int t_busy;                           // 0x4
    /* 0x078 */ void (*t_hash)(struct sceHTTPClient *, long long, void *);  // 0x4
    /* 0x07C */ void *t_hash_opt;                     // 0x4
    /* 0x080 */ void *t_hash_gp;                      // 0x4
    /* 0x084 */ int hashbytes;                        // 0x4
    /* 0x088 */ unsigned int t_sent;                  // 0x4
    /* 0x08C */ unsigned int max_olength;             // 0x4
    /* 0x090 */ struct sceHTTPParsedURI *proxy;       // 0x4
    /* 0x094 */ int c_stacksize;                      // 0x4
    /* 0x098 */ int c_priority;                       // 0x4
    /* 0x09C */ int c_thread;                         // 0x4
    /* 0x0A0 */ void *c_stack;                        // 0x4
    /* 0x0A4 */ void (*c_notify)(struct sceHTTPClient *, int, void *);  // 0x4
    /* 0x0A8 */ void *c_notify_opt;                   // 0x4
    /* 0x0AC */ void *c_notify_gp;                    // 0x4
    /* 0x0B0 */ int nb_open;                          // 0x4
    /* 0x0B4 */ enum @enum {   // size 0x1
        sceHTTPM_OPTIONS = 0,
        sceHTTPM_GET = 1,
        sceHTTPM_HEAD = 2,
        sceHTTPM_POST = 3,
        sceHTTPM_PUT = 4,
        sceHTTPM_DELETE = 5,
        sceHTTPM_TRACE = 6,
        sceHTTPM_CONNECT = 7,
        sceHTTPM_PROPFIND = 8,
        sceHTTPM_PROPPATCH = 9,
        sceHTTPM_MKCOL = 10,
        sceHTTPM_COPY = 11,
        sceHTTPM_MOVE = 12,
        sceHTTPM_LOCK = 13,
        sceHTTPM_UNLOCK = 14,
    } method;
    /* 0x0B5 */ // 0x3 bytes padding
    /* 0x0B8 */ struct sceHTTPParsedURI *puri;        // 0x4
    /* 0x0BC */ struct sceHTTPHeaderList *iheaders;   // 0x4
    /* 0x0C0 */ char *idata;                          // 0x4
    /* 0x0C4 */ int ilength;                          // 0x4
    /* 0x0C8 */ int iflags;                           // 0x4
    /* 0x0CC */ int fd;                               // 0x4
    /* 0x0D0 */ int (*writef)(int, unsigned char *, unsigned int);  // 0x4
    /* 0x0D4 */ void *writef_gp;                      // 0x4
    /* 0x0D8 */ int hflags;                           // 0x4
    /* 0x0DC */ // 0x4 bytes padding
    /* 0x0E0 */ struct sceHTTPResponse response;      // 0x40
    /* 0x120 */ void (*chunkf)(struct sceHTTPClient *, unsigned char *, unsigned int, void *);  // 0x4
    /* 0x124 */ void *chunkf_opt;                     // 0x4
    /* 0x128 */ void *chunkf_gp;                      // 0x4
    /* 0x12C */ int recv_thread;                      // 0x4
    /* 0x130 */ int send_thread;                      // 0x4
    /* 0x134 */ void *io_rstack;                      // 0x4
    /* 0x138 */ void *io_sstack;                      // 0x4
    /* 0x13C */ int io_desc;                          // 0x4
    /* 0x140 */ char *io_buf;                         // 0x4
    /* 0x144 */ int io_len;                           // 0x4
    /* 0x148 */ int io_rtn;                           // 0x4
    /* 0x14C */ int io_timer;                         // 0x4
    /* 0x150 */ int io_rwait;                         // 0x4
    /* 0x154 */ int io_rdone;                         // 0x4
    /* 0x158 */ int io_swait;                         // 0x4
    /* 0x15C */ int io_sdone;                         // 0x4
    /* 0x160 */ int io_flags;                         // 0x4
    /* 0x164 */ int io_tcount;                        // 0x4
    /* 0x168 */ int reserved00;                       // 0x4
    /* 0x16C */ void *reserved0;                      // 0x4
    /* 0x170 */ void *reserved1;                      // 0x4
    /* 0x174 */ int reserved2;                        // 0x4
    /* 0x178 */ int hflags2;                          // 0x4
    /* 0x17C */ void *write4_opt;                     // 0x4
    /* 0x180 */ int pad[35];                          // 0x8C
    /* 0x20C */ // 0x4 bytes padding
};

#endif /* DDR_types_sceHTTPClient_H */
