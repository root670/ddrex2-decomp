/* anonymous enum -- 0 members, size 0x1, layout 315a882ef873.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_315a882ef873` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: ddrex2_usa_id.c (DIE 0x397556)
 */
#ifndef DDR_types_anon_315a882ef873_H
#define DDR_types_anon_315a882ef873_H

typedef enum {   // size 0x1
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
} anon_315a882ef873;

#endif /* DDR_types_anon_315a882ef873_H */
