/*
 * C:\work\usam2\src\CS\cmes_s.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_cmes_s_c_H
#define DDR_UNIT_src_CS_cmes_s_c_H

/* variables (81) */
unsigned char *cmes_yesno_str_spanish[2];                        /* @0x002a2350 size 0x8 */
static unsigned char *CHECKING[6];                               /* @0x00286b70 size 0x18 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002a2358 size 0x8 */
static unsigned char *NO_DATA_DIET1P[3];                         /* @0x00286b88 size 0xc */
static unsigned char *NO_DATA_DIET2P[3];                         /* @0x00286b98 size 0xc */
static unsigned char *NO_CARD[4];                                /* @0x00286bb0 size 0x10 */
static unsigned char *UNFORMAT[3];                               /* @0x00286bc0 size 0xc */
static unsigned char *CHECK_ERR[3];                              /* @0x00286bd0 size 0xc */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x00286be0 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[5];                   /* @0x00286bf0 size 0x14 */
static unsigned char *NO_CARD_STOP_YN_LOAD[5];                   /* @0x00286c10 size 0x14 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x00286c30 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x00286c40 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x00286c50 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x00286c70 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x00286c90 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x00286cb0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x00286cd0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x00286cf0 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x00286d10 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x00286d30 size 0x1c */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x00286d50 size 0x1c */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x00286d70 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x00286d80 size 0xc */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[4];           /* @0x00286d90 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[4];           /* @0x00286da0 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[4];           /* @0x00286db0 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[4];           /* @0x00286dc0 size 0x10 */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x00286dd0 size 0xc */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x00286de0 size 0xc */
static unsigned char *FORMAT_YN[5];                              /* @0x00286df0 size 0x14 */
static unsigned char *FORMATTING[6];                             /* @0x00286e10 size 0x18 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x00286e28 size 0xc */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x00286e38 size 0xc */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[6];            /* @0x00286e50 size 0x18 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002a2360 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[3];                         /* @0x00286e68 size 0xc */
static unsigned char *LOAD_YN_DIET2P[3];                         /* @0x00286e78 size 0xc */
static unsigned char *LOADING[6];                                /* @0x00286e90 size 0x18 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002a2368 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[3];                         /* @0x00286ea8 size 0xc */
static unsigned char *LOAD_OK_DIET2P[3];                         /* @0x00286eb8 size 0xc */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x00286ec8 size 0xc */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[4];               /* @0x00286ee0 size 0x10 */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[4];               /* @0x00286ef0 size 0x10 */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002a2370 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[3];                    /* @0x00286f00 size 0xc */
static unsigned char *LOAD_STOPPED_DIET2P[3];                    /* @0x00286f10 size 0xc */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002a2378 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[3];                         /* @0x00286f20 size 0xc */
static unsigned char *SAVE_YN_DIET2P[3];                         /* @0x00286f30 size 0xc */
static unsigned char *SAVING[6];                                 /* @0x00286f40 size 0x18 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002a2380 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[3];                         /* @0x00286f58 size 0xc */
static unsigned char *SAVE_OK_DIET2P[3];                         /* @0x00286f68 size 0xc */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x00286f78 size 0xc */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[4];               /* @0x00286f90 size 0x10 */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[4];               /* @0x00286fa0 size 0x10 */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002a2388 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[3];                    /* @0x00286fb0 size 0xc */
static unsigned char *SAVE_STOPPED_DIET2P[3];                    /* @0x00286fc0 size 0xc */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002a2390 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x00286fd0 size 0xc */
static unsigned char *SAVE_CREATE_YN_DIET1P[4];                  /* @0x00286fe0 size 0x10 */
static unsigned char *SAVE_CREATE_YN_DIET2P[4];                  /* @0x00286ff0 size 0x10 */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002a2398 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[4];                       /* @0x00287000 size 0x10 */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x00287010 size 0xc */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[4];  /* @0x00287020 size 0x10 */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[4];  /* @0x00287030 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[8];          /* not allocated size 0x20 */
unsigned char **mcMessageTbl_SPANISH[69];                        /* @0x00287040 size 0x114 */
static unsigned char *mesElib_CHECKING[2];                       /* @0x002a23a0 size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002a23a8 size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* @0x002a23b0 size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002a23b8 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002a23c0 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002a23c8 size 0x8 */
static unsigned char *mesElib_NO_CARD[6];                        /* @0x00287160 size 0x18 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002a23d0 size 0x8 */
unsigned char **elibMessageTbl_SPANISH[8];                       /* @0x00287180 size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_s_c_H */
