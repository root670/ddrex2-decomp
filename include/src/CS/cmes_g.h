/*
 * C:\work\usam2\src\CS\cmes_g.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_cmes_g_c_H
#define DDR_UNIT_src_CS_cmes_g_c_H

/* variables (81) */
unsigned char *cmes_yesno_str_german[2];                         /* @0x002a24b0 size 0x8 */
static unsigned char *CHECKING[5];                               /* @0x00287700 size 0x14 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002a24b8 size 0x8 */
static unsigned char *NO_DATA_DIET1P[2];                         /* @0x002a24c0 size 0x8 */
static unsigned char *NO_DATA_DIET2P[2];                         /* @0x002a24c8 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x00287718 size 0xc */
static unsigned char *UNFORMAT[3];                               /* @0x00287728 size 0xc */
static unsigned char *CHECK_ERR[3];                              /* @0x00287738 size 0xc */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x00287750 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x00287760 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x00287770 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x00287780 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x00287790 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x002877a0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x002877c0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x002877e0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x00287800 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x00287820 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x00287840 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x00287860 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x00287880 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x002878a0 size 0x1c */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x002878c0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x002878d0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[3];           /* @0x002878e0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[3];           /* @0x002878f0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[3];           /* @0x00287900 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[3];           /* @0x00287910 size 0xc */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x00287920 size 0xc */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x00287930 size 0xc */
static unsigned char *FORMAT_YN[5];                              /* @0x00287940 size 0x14 */
static unsigned char *FORMATTING[5];                             /* @0x00287960 size 0x14 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x00287978 size 0xc */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x00287988 size 0xc */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[5];            /* @0x002879a0 size 0x14 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002a24d0 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[2];                         /* @0x002a24d8 size 0x8 */
static unsigned char *LOAD_YN_DIET2P[2];                         /* @0x002a24e0 size 0x8 */
static unsigned char *LOADING[5];                                /* @0x002879c0 size 0x14 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002a24e8 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[2];                         /* @0x002a24f0 size 0x8 */
static unsigned char *LOAD_OK_DIET2P[2];                         /* @0x002a24f8 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x002879d8 size 0xc */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[4];               /* @0x002879f0 size 0x10 */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[4];               /* @0x00287a00 size 0x10 */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002a2500 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[2];                    /* @0x002a2508 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET2P[2];                    /* @0x002a2510 size 0x8 */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002a2518 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[2];                         /* @0x002a2520 size 0x8 */
static unsigned char *SAVE_YN_DIET2P[2];                         /* @0x002a2528 size 0x8 */
static unsigned char *SAVING[5];                                 /* @0x00287a10 size 0x14 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002a2530 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[2];                         /* @0x002a2538 size 0x8 */
static unsigned char *SAVE_OK_DIET2P[2];                         /* @0x002a2540 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x00287a28 size 0xc */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[3];               /* @0x00287a38 size 0xc */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[3];               /* @0x00287a48 size 0xc */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002a2548 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[3];                    /* @0x00287a58 size 0xc */
static unsigned char *SAVE_STOPPED_DIET2P[3];                    /* @0x00287a68 size 0xc */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002a2550 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x00287a78 size 0xc */
static unsigned char *SAVE_CREATE_YN_DIET1P[3];                  /* @0x00287a88 size 0xc */
static unsigned char *SAVE_CREATE_YN_DIET2P[3];                  /* @0x00287a98 size 0xc */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002a2558 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[4];                       /* @0x00287ab0 size 0x10 */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x00287ac0 size 0xc */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[3];  /* @0x00287ad0 size 0xc */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[3];  /* @0x00287ae0 size 0xc */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[7];          /* not allocated size 0x1c */
unsigned char **mcMessageTbl_GERMAN[69];                         /* @0x00287af0 size 0x114 */
static unsigned char *mesElib_CHECKING[2];                       /* @0x002a2560 size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002a2568 size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* @0x002a2570 size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002a2578 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002a2580 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002a2588 size 0x8 */
static unsigned char *mesElib_NO_CARD[4];                        /* @0x00287c10 size 0x10 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002a2590 size 0x8 */
unsigned char **elibMessageTbl_GERMAN[8];                        /* @0x00287c20 size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_g_c_H */
