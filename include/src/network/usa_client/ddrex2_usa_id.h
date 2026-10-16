/*
 * C:\work2\usaex2\src\network\usa_client\ddrex2_usa_id.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 1 functions, code 0x007F5E10-0x007F69C0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_usa_client_ddrex2_usa_id_c_H
#define DDR_UNIT_src_network_usa_client_ddrex2_usa_id_c_H

#include "types/sceHTTPClient.h"
#include "types/sceHTTPHeaderList.h"
#include "types/sceHTTPParsedURI.h"
#include "types/sceHTTPResponse.h"

/* anonymous types (2) */

/* anon_x397052_205 -- @enum, 0x2 bytes, ddrex2_usa_id.c (DIE 0x397052) */
enum anon_x397052_205 {   // size 0x2
    sceHTTPC_Continue = 100,
    sceHTTPC_SwitchProtocols = 101,
    sceHTTPC_Processing = 102,
    sceHTTPC_OK = 200,
    sceHTTPC_Created = 201,
    sceHTTPC_Accepted = 202,
    sceHTTPC_NonAuthoritativeInfo = 203,
    sceHTTPC_NoContent = 204,
    sceHTTPC_ResetContent = 205,
    sceHTTPC_PartialContent = 206,
    sceHTTPC_MultiStatus = 207,
    sceHTTPC_MultipleChoices = 300,
    sceHTTPC_MovedPermanentry = 301,
    sceHTTPC_Found = 302,
    sceHTTPC_SeeOther = 303,
    sceHTTPC_NotModified = 304,
    sceHTTPC_UseProxy = 305,
    sceHTTPC_TemporaryRedirect = 307,
    sceHTTPC_BadRequest = 400,
    sceHTTPC_Unauthorized = 401,
    sceHTTPC_PaymentRequired = 402,
    sceHTTPC_Forbidden = 403,
    sceHTTPC_NotFound = 404,
    sceHTTPC_MethodNotAllowed = 405,
    sceHTTPC_NotAcceptable = 406,
    sceHTTPC_ProxyAuthenticationRequired = 407,
    sceHTTPC_RequestTimeout = 408,
    sceHTTPC_Conflict = 409,
    sceHTTPC_Gone = 410,
    sceHTTPC_LengthRequired = 411,
    sceHTTPC_PreconditionFailed = 412,
    sceHTTPC_RequestEntityTooLarge = 413,
    sceHTTPC_RequestURITooLarge = 414,
    sceHTTPC_UnsupportedMediaType = 415,
    sceHTTPC_RequestedRangeNotSatisfiable = 416,
    sceHTTPC_ExceptionFailed = 417,
    sceHTTPC_UnprocessableEntity = 422,
    sceHTTPC_Locked = 423,
    sceHTTPC_FailedDependency = 424,
    sceHTTPC_InternalServerError = 500,
    sceHTTPC_NotImplemented = 501,
    sceHTTPC_BadGateway = 502,
    sceHTTPC_ServiceUnavailable = 503,
    sceHTTPC_GatewayTimeout = 504,
    sceHTTPC_HTTPVersionNotSupported = 505,
    sceHTTPC_InsufficientStorage = 507,
};

/* anon_x397556_205 -- @enum, 0x1 bytes, ddrex2_usa_id.c (DIE 0x397556) */
enum anon_x397556_205 {   // size 0x1
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
};


/* functions defined (1) */
int ddrnet_id_regist_request(int flag, char *uri, char *name, char *passwd, char *newpasswd); /* 0x007F5E10-0x007F69C0 lines 70-315 */

#endif /* DDR_UNIT_src_network_usa_client_ddrex2_usa_id_c_H */
