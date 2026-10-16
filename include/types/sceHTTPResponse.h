/* struct sceHTTPResponse -- 11 members, size 0x40, layout f6f7b2de2dee.
 *
 * One definition, agreed by the 1 unit that declares it: ddrex2_usa_id.c (DIE 0x395ED0).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceHTTPResponse *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: ddrex2_usa_id.c (DIE 0x395ED0)
 */
#ifndef DDR_types_sceHTTPResponse_H
#define DDR_types_sceHTTPResponse_H

struct sceHTTPHeaderList;

#include "types/sceHTTPHeaderList.h"

struct sceHTTPResponse {   // size 0x40
    /* 0x000 */ int http_ver;                         // 0x4
    /* 0x004 */ int http_rev;                         // 0x4
    /* 0x008 */ enum @enum {   // size 0x2
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
    } code;
    /* 0x00A */ // 0x2 bytes padding
    /* 0x00C */ char *reason;                         // 0x4
    /* 0x010 */ int server_prot;                      // 0x4
    /* 0x014 */ struct sceHTTPHeaderList *headers;    // 0x4
    /* 0x018 */ unsigned char *entity;                // 0x4
    /* 0x01C */ // 0x4 bytes padding
    /* 0x020 */ long long length;                     // 0x8
    /* 0x028 */ int interrupted;                      // 0x4
    /* 0x02C */ // 0x4 bytes padding
    /* 0x030 */ long long date;                       // 0x8
    /* 0x038 */ long long content_length;             // 0x8
};

#endif /* DDR_types_sceHTTPResponse_H */
