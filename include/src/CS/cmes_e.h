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
unsigned char *cmes_yesno_str_english[2];                        /* @0x002A2148 size 0x8 */
static unsigned char warning0[52];                               /* @0x0027F290 size 0x34 */
static unsigned char warning1[55];                               /* @0x0027F2D0 size 0x37 */
static unsigned char *CHECKING[4];                               /* @0x0027F310 size 0x10 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002A2150 size 0x8 */
static unsigned char *NO_DATA_DIET1P[2];                         /* @0x002A2158 size 0x8 */
static unsigned char *NO_DATA_DIET2P[2];                         /* @0x002A2160 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x0027F320 size 0xC */
static unsigned char *UNFORMAT[3];                               /* @0x0027F330 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x0027F340 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x0027F350 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x0027F360 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x0027F370 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x0027F380 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x0027F390 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x0027F3A0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x0027F3C0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x0027F3E0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x0027F400 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x0027F420 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x0027F440 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x0027F460 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x0027F480 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x0027F4A0 size 0x1C */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x0027F4C0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x0027F4D0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[3];           /* @0x0027F4E0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[3];           /* @0x0027F4F0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[3];           /* @0x0027F500 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[3];           /* @0x0027F510 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x0027F520 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x0027F530 size 0xC */
static unsigned char *FORAMT_YN[4];                              /* @0x0027F540 size 0x10 */
static unsigned char *FORMATTING[4];                             /* @0x0027F550 size 0x10 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x0027F560 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x0027F570 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[5];            /* @0x0027F580 size 0x14 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002A2168 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[2];                         /* @0x002A2170 size 0x8 */
static unsigned char *LOAD_YN_DIET2P[2];                         /* @0x002A2178 size 0x8 */
static unsigned char *LOADING[4];                                /* @0x0027F5A0 size 0x10 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002A2180 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[2];                         /* @0x002A2188 size 0x8 */
static unsigned char *LOAD_OK_DIET2P[2];                         /* @0x002A2190 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x0027F5B0 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[3];               /* @0x0027F5C0 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[3];               /* @0x0027F5D0 size 0xC */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002A2198 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[2];                    /* @0x002A21A0 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET2P[2];                    /* @0x002A21A8 size 0x8 */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002A21B0 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[2];                         /* @0x002A21B8 size 0x8 */
static unsigned char *SAVE_YN_DIET2P[2];                         /* @0x002A21C0 size 0x8 */
static unsigned char *SAVING[4];                                 /* @0x0027F5E0 size 0x10 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002A21C8 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[2];                         /* @0x002A21D0 size 0x8 */
static unsigned char *SAVE_OK_DIET2P[2];                         /* @0x002A21D8 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x0027F5F0 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[3];               /* @0x0027F600 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[3];               /* @0x0027F610 size 0xC */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002A21E0 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[2];                    /* @0x002A21E8 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET2P[2];                    /* @0x002A21F0 size 0x8 */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002A21F8 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x0027F620 size 0xC */
static unsigned char *SAVE_CREATE_YN_DIET1P[3];                  /* @0x0027F630 size 0xC */
static unsigned char *SAVE_CREATE_YN_DIET2P[3];                  /* @0x0027F640 size 0xC */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002A2200 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[3];                       /* @0x0027F650 size 0xC */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x0027F660 size 0xC */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[3];  /* @0x0027F670 size 0xC */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[3];  /* @0x0027F680 size 0xC */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[6];          /* not allocated size 0x18 */
unsigned char **mcMessageTbl_ENGLISH[69];                        /* @0x0027F690 size 0x114 */
static unsigned char *mesElib_CHECKING[2];                       /* @0x002A2208 size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002A2210 size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* @0x002A2218 size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002A2220 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002A2228 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002A2230 size 0x8 */
static unsigned char *mesElib_NO_CARD[4];                        /* @0x0027F7B0 size 0x10 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002A2238 size 0x8 */
unsigned char **elibMessageTbl_ENGLISH[8];                       /* @0x0027F7C0 size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_e_c_H */
