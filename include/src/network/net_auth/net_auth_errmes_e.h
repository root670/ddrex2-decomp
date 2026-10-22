/*
 * C:\work2\usaex2\src\network\net_auth\net_auth_errmes_e.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x002547E0-0x00254A88
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_network_net_auth_net_auth_errmes_e_c_H
#define DDR_UNIT_src_network_net_auth_net_auth_errmes_e_c_H

/* variables (9) */
static unsigned char *ERR_SERVERNOTREADY[3];                     /* @0x002BF2C8 size 0xC */
static unsigned char *ERR_LOGIN_FAILED[3];                       /* @0x002BF2D8 size 0xC */
static unsigned char *ERR_ALREADYLOGGEDIN[3];                    /* @0x002BF2E8 size 0xC */
static unsigned char *ERR_ETC[2];                                /* @0x002DDD50 size 0x8 */
static unsigned char *REG_ERR_ETC[2];                            /* @0x002DDD58 size 0x8 */
static unsigned char *REG_ERR_NGWORDS[3];                        /* @0x002BF2F8 size 0xC */
static unsigned char *REG_ERR_USED[4];                           /* @0x002BF310 size 0x10 */
static unsigned char *CHG_ERR_ETC[2];                            /* @0x002DDD60 size 0x8 */
static unsigned char *CHG_ERR_OLDPASS[3];                        /* @0x002BF320 size 0xC */

/* functions defined (3) */
void namesMakeChangeMessage(int code, unsigned char *msg);       /* 0x002547E0-0x002548A8 lines 203-247 */
void namesMakeRegisterMessage(int code, unsigned char *msg);     /* 0x002548B0-0x00254990 lines 134-180 */
void namesMakeAuthMessage(int code, unsigned char *msg);         /* 0x00254990-0x00254A88 lines 55-103 */

#endif /* DDR_UNIT_src_network_net_auth_net_auth_errmes_e_c_H */
