/*
 * C:\work2\usaex2\src\network\net_auth\net_auth_mes_e.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x00246DC0-0x00246E18
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_auth_net_auth_mes_e_c_H
#define DDR_UNIT_src_network_net_auth_net_auth_mes_e_c_H

/* variables (39) */
static unsigned char *ITEM_DDR_ID[2];                            /* @0x002DDC40 size 0x8 */
static unsigned char *ITEM_PASSWORD[2];                          /* @0x002DDC48 size 0x8 */
static unsigned char *ITEM_AUTHENTICATION[2];                    /* @0x002DDC50 size 0x8 */
static unsigned char *ITEM_LOGOUT[2];                            /* @0x002DDC58 size 0x8 */
static unsigned char *EXP_DDR_ID[2];                             /* @0x002DDC60 size 0x8 */
static unsigned char *EXP_PASSWORD[2];                           /* @0x002DDC68 size 0x8 */
static unsigned char *EXP_AUTHENTICATION[2];                     /* @0x002DDC70 size 0x8 */
static unsigned char *EXP_LOGOUT[2];                             /* @0x002DDC78 size 0x8 */
static unsigned char *AUTH_RUN[2];                               /* @0x002DDC80 size 0x8 */
static unsigned char *AUTH_OK[2];                                /* @0x002DDC88 size 0x8 */
static unsigned char *AUTH_ABORT[2];                             /* @0x002DDC90 size 0x8 */
static unsigned char *AUTH_ABORT_YN[2];                          /* @0x002DDC98 size 0x8 */
static unsigned char *IDGET_GET_YN[3];                           /* @0x002BF0E0 size 0xC */
static unsigned char *IDGET_SAVE_YN[4];                          /* @0x002BF0F0 size 0x10 */
static unsigned char *IDGET_FINAL_YN[3];                         /* @0x002BF100 size 0xC */
static unsigned char *HOWTO_GET_DDR_ID[4];                       /* @0x002BF110 size 0x10 */
static unsigned char *LOGOUT_YN[2];                              /* @0x002DDCA0 size 0x8 */
static unsigned char *IDMENU_MENU[4];                            /* @0x002BF120 size 0x10 */
static unsigned char *IDMENU_EXP_ENTRY[3];                       /* @0x002BF130 size 0xC */
static unsigned char *IDMENU_EXP_CHPASS[2];                      /* @0x002DDCA8 size 0x8 */
static unsigned char *IDMENU_EXP_CANCEL[2];                      /* @0x002DDCB0 size 0x8 */
static unsigned char *ENTRY_CANCELED[2];                         /* @0x002DDCB8 size 0x8 */
static unsigned char *ENTRY_INPUT_ID[3];                         /* @0x002BF140 size 0xC */
static unsigned char *ENTRY_INPUT_PASS1[2];                      /* @0x002DDCC0 size 0x8 */
static unsigned char *ENTRY_INPUT_PASS2[2];                      /* @0x002DDCC8 size 0x8 */
static unsigned char *ENTRY_INPUT_ERR_PASS_NOT_MATCH[2];         /* @0x002DDCD0 size 0x8 */
static unsigned char *ENTRY_RUN[2];                              /* @0x002DDCD8 size 0x8 */
static unsigned char *ENTRY_OK[2];                               /* @0x002DDCE0 size 0x8 */
static unsigned char *CHANGE_CANCELED[2];                        /* @0x002DDCE8 size 0x8 */
static unsigned char *CHANGE_INPUT_ID[2];                        /* @0x002DDCF0 size 0x8 */
static unsigned char *CHANGE_INPUT_PASS1[2];                     /* @0x002DDCF8 size 0x8 */
static unsigned char *CHANGE_INPUT_PASS2[2];                     /* @0x002DDD00 size 0x8 */
static unsigned char *CHANGE_INPUT_PASS3[2];                     /* @0x002DDD08 size 0x8 */
static unsigned char *CHANGE_INPUT_ERR_PASS_NOT_MATCH[2];        /* @0x002DDD10 size 0x8 */
static unsigned char *CHANGE_INPUT_ERR_PASS_SAME[3];             /* @0x002BF150 size 0xC */
static unsigned char *CHANGE_RUN[2];                             /* @0x002DDD18 size 0x8 */
static unsigned char *CHANGE_OK[2];                              /* @0x002DDD20 size 0x8 */
unsigned char **naMessageTbl_ENGLISH[37];                        /* @0x002BF160 size 0x94 */
unsigned char *cmes_yesno_str_english[];                         /* @0x002DD738 */

/* functions defined (3) */
unsigned char *namesGetNo(void);                                 /* 0x00246DC0-0x00246DCC lines 319-320 */
unsigned char *namesGetYes(void);                                /* 0x00246DD0-0x00246DDC lines 316-317 */
unsigned char **namesGetMessageTable(int id);                    /* 0x00246DE0-0x00246E18 lines 307-312 */

#endif /* DDR_UNIT_src_network_net_auth_net_auth_mes_e_c_H */
