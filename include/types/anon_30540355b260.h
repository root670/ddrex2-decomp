/* anonymous enum -- 0 members, size 0x2, layout 30540355b260.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_30540355b260` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: ddrex2_usa_id.c (DIE 0x397052)
 */
#ifndef DDR_types_anon_30540355b260_H
#define DDR_types_anon_30540355b260_H

typedef enum {   // size 0x2
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
} anon_30540355b260;

#endif /* DDR_types_anon_30540355b260_H */
