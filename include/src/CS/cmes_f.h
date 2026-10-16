/*
 * C:\work\usam2\src\CS\cmes_f.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_cmes_f_c_H
#define DDR_UNIT_src_CS_cmes_f_c_H

/* variables (81) */
unsigned char *cmes_yesno_str_french[2];                         /* @0x002a2288 size 0x8 */
static unsigned char *CHECKING[6];                               /* @0x002865c0 size 0x18 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002a2290 size 0x8 */
static unsigned char *NO_DATA_DIET1P[2];                         /* @0x002a2298 size 0x8 */
static unsigned char *NO_DATA_DIET2P[2];                         /* @0x002a22a0 size 0x8 */
static unsigned char *NO_CARD[4];                                /* @0x002865e0 size 0x10 */
static unsigned char *UNFORMAT[3];                               /* @0x002865f0 size 0xc */
static unsigned char *CHECK_ERR[3];                              /* @0x00286600 size 0xc */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x00286610 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[5];                   /* @0x00286620 size 0x14 */
static unsigned char *NO_CARD_STOP_YN_LOAD[5];                   /* @0x00286640 size 0x14 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x00286660 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x00286670 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x00286680 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x002866a0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x002866c0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x002866e0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x00286700 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x00286720 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x00286740 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x00286760 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x00286780 size 0x1c */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x002867a0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x002867b0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[3];           /* @0x002867c0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[3];           /* @0x002867d0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[3];           /* @0x002867e0 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[3];           /* @0x002867f0 size 0xc */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x00286800 size 0xc */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x00286810 size 0xc */
static unsigned char *FORMAT_YN[5];                              /* @0x00286820 size 0x14 */
static unsigned char *FORMATTING[6];                             /* @0x00286840 size 0x18 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x00286858 size 0xc */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x00286868 size 0xc */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[5];            /* @0x00286880 size 0x14 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002a22a8 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[2];                         /* @0x002a22b0 size 0x8 */
static unsigned char *LOAD_YN_DIET2P[2];                         /* @0x002a22b8 size 0x8 */
static unsigned char *LOADING[6];                                /* @0x002868a0 size 0x18 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002a22c0 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[2];                         /* @0x002a22c8 size 0x8 */
static unsigned char *LOAD_OK_DIET2P[2];                         /* @0x002a22d0 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x002868b8 size 0xc */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[4];               /* @0x002868d0 size 0x10 */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[4];               /* @0x002868e0 size 0x10 */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002a22d8 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[3];                    /* @0x002868f0 size 0xc */
static unsigned char *LOAD_STOPPED_DIET2P[3];                    /* @0x00286900 size 0xc */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002a22e0 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[2];                         /* @0x002a22e8 size 0x8 */
static unsigned char *SAVE_YN_DIET2P[2];                         /* @0x002a22f0 size 0x8 */
static unsigned char *SAVING[6];                                 /* @0x00286910 size 0x18 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002a22f8 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[2];                         /* @0x002a2300 size 0x8 */
static unsigned char *SAVE_OK_DIET2P[2];                         /* @0x002a2308 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x00286928 size 0xc */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[4];               /* @0x00286940 size 0x10 */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[4];               /* @0x00286950 size 0x10 */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002a2310 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[3];                    /* @0x00286960 size 0xc */
static unsigned char *SAVE_STOPPED_DIET2P[3];                    /* @0x00286970 size 0xc */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002a2318 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x00286980 size 0xc */
static unsigned char *SAVE_CREATE_YN_DIET1P[3];                  /* @0x00286990 size 0xc */
static unsigned char *SAVE_CREATE_YN_DIET2P[3];                  /* @0x002869a0 size 0xc */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002a2320 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[4];                       /* @0x002869b0 size 0x10 */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x002869c0 size 0xc */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[4];  /* @0x002869d0 size 0x10 */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[4];  /* @0x002869e0 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[7];          /* not allocated size 0x1c */
unsigned char **mcMessageTbl_FRENCH[69];                         /* @0x002869f0 size 0x114 */
static unsigned char *mesElib_CHECKING[3];                       /* @0x00286b08 size 0xc */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002a2328 size 0x8 */
static unsigned char *mesElib_LOADING[3];                        /* @0x00286b18 size 0xc */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002a2330 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002a2338 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002a2340 size 0x8 */
static unsigned char *mesElib_NO_CARD[6];                        /* @0x00286b30 size 0x18 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002a2348 size 0x8 */
unsigned char **elibMessageTbl_FRENCH[8];                        /* @0x00286b50 size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_f_c_H */
