/*
 * C:\work\usam2\src\CS\cmes_e.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_cmes_e_c_H
#define DDR_UNIT_src_CS_cmes_e_c_H

/* variables (83) */
unsigned char *cmes_yesno_str_english[2];                        /* @0x002a2148 size 0x8 */
static unsigned char warning0[52];                               /* @0x0027f290 size 0x34 */
static unsigned char warning1[55];                               /* @0x0027f2d0 size 0x37 */
static unsigned char *CHECKING[4];                               /* @0x0027f310 size 0x10 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002a2150 size 0x8 */
static unsigned char *NO_DATA_DIET1P[2];                         /* @0x002a2158 size 0x8 */
static unsigned char *NO_DATA_DIET2P[2];                         /* @0x002a2160 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x0027f320 size 0xc */
static unsigned char *UNFORMAT[3];                               /* @0x0027f330 size 0xc */
static unsigned char *CHECK_ERR[3];                              /* @0x0027f340 size 0xc */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x0027f350 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x0027f360 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x0027f370 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x0027f380 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x0027f390 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x0027f3a0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x0027f3c0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x0027f3e0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x0027f400 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x0027f420 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x0027f440 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x0027f460 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x0027f480 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x0027f4a0 size 0x1c */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x0027f4c0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x0027f4d0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[3];           /* @0x0027f4e0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[3];           /* @0x0027f4f0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[3];           /* @0x0027f500 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[3];           /* @0x0027f510 size 0xc */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x0027f520 size 0xc */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x0027f530 size 0xc */
static unsigned char *FORAMT_YN[4];                              /* @0x0027f540 size 0x10 */
static unsigned char *FORMATTING[4];                             /* @0x0027f550 size 0x10 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x0027f560 size 0xc */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x0027f570 size 0xc */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[5];            /* @0x0027f580 size 0x14 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002a2168 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[2];                         /* @0x002a2170 size 0x8 */
static unsigned char *LOAD_YN_DIET2P[2];                         /* @0x002a2178 size 0x8 */
static unsigned char *LOADING[4];                                /* @0x0027f5a0 size 0x10 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002a2180 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[2];                         /* @0x002a2188 size 0x8 */
static unsigned char *LOAD_OK_DIET2P[2];                         /* @0x002a2190 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x0027f5b0 size 0xc */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[3];               /* @0x0027f5c0 size 0xc */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[3];               /* @0x0027f5d0 size 0xc */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002a2198 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[2];                    /* @0x002a21a0 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET2P[2];                    /* @0x002a21a8 size 0x8 */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002a21b0 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[2];                         /* @0x002a21b8 size 0x8 */
static unsigned char *SAVE_YN_DIET2P[2];                         /* @0x002a21c0 size 0x8 */
static unsigned char *SAVING[4];                                 /* @0x0027f5e0 size 0x10 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002a21c8 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[2];                         /* @0x002a21d0 size 0x8 */
static unsigned char *SAVE_OK_DIET2P[2];                         /* @0x002a21d8 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x0027f5f0 size 0xc */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[3];               /* @0x0027f600 size 0xc */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[3];               /* @0x0027f610 size 0xc */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002a21e0 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[2];                    /* @0x002a21e8 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET2P[2];                    /* @0x002a21f0 size 0x8 */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002a21f8 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x0027f620 size 0xc */
static unsigned char *SAVE_CREATE_YN_DIET1P[3];                  /* @0x0027f630 size 0xc */
static unsigned char *SAVE_CREATE_YN_DIET2P[3];                  /* @0x0027f640 size 0xc */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002a2200 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[3];                       /* @0x0027f650 size 0xc */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x0027f660 size 0xc */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[3];  /* @0x0027f670 size 0xc */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[3];  /* @0x0027f680 size 0xc */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[6];          /* not allocated size 0x18 */
unsigned char **mcMessageTbl_ENGLISH[69];                        /* @0x0027f690 size 0x114 */
static unsigned char *mesElib_CHECKING[2];                       /* @0x002a2208 size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002a2210 size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* @0x002a2218 size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002a2220 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002a2228 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002a2230 size 0x8 */
static unsigned char *mesElib_NO_CARD[4];                        /* @0x0027f7b0 size 0x10 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002a2238 size 0x8 */
unsigned char **elibMessageTbl_ENGLISH[8];                       /* @0x0027f7c0 size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_e_c_H */
