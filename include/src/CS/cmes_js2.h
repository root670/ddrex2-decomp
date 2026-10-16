/*
 * C:\work2\usaex2\src\CS\cmes_js2.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_cmes_js2_c_H
#define DDR_UNIT_src_CS_cmes_js2_c_H

/* variables (72) */
static unsigned char warning0[39];                               /* @0x002B69A0 size 0x27 */
static unsigned char warning1[53];                               /* @0x002B69D0 size 0x35 */
static unsigned char *CHECKING[4];                               /* @0x002B6A10 size 0x10 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002DD9C0 size 0x8 */
static unsigned char *NO_DATA_WORKOUT1P[2];                      /* @0x002DD9C8 size 0x8 */
static unsigned char *NO_DATA_WORKOUT2P[2];                      /* @0x002DD9D0 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x002B6A20 size 0xC */
static unsigned char *UNFORMAT[3];                               /* @0x002B6A30 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x002B6A40 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x002B6A50 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x002B6A60 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x002B6A70 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x002B6A80 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x002B6A90 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x002B6AA0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_SAVE[6];        /* @0x002B6AC0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_SAVE[6];        /* @0x002B6AE0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x002B6B00 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_LOAD[6];        /* @0x002B6B20 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_LOAD[6];        /* @0x002B6B40 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x002B6B60 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_START[6];       /* @0x002B6B80 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_START[6];       /* @0x002B6BA0 size 0x18 */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x002B6BB8 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x002B6BC8 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_SAVE[3];        /* @0x002B6BD8 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_LOAD[3];        /* @0x002B6BE8 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_SAVE[3];        /* @0x002B6BF8 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_LOAD[3];        /* @0x002B6C08 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x002B6C18 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x002B6C28 size 0xC */
static unsigned char *FORAMT_YN[4];                              /* @0x002B6C40 size 0x10 */
static unsigned char *FORMATTING[4];                             /* @0x002B6C50 size 0x10 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x002B6C60 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x002B6C70 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[4];            /* @0x002B6C80 size 0x10 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002DD9D8 size 0x8 */
static unsigned char *LOAD_YN_WORKOUT1P[2];                      /* @0x002DD9E0 size 0x8 */
static unsigned char *LOAD_YN_WORKOUT2P[2];                      /* @0x002DD9E8 size 0x8 */
static unsigned char *LOADING[4];                                /* @0x002B6C90 size 0x10 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002DD9F0 size 0x8 */
static unsigned char *LOAD_OK_WORKOUT1P[2];                      /* @0x002DD9F8 size 0x8 */
static unsigned char *LOAD_OK_WORKOUT2P[2];                      /* @0x002DDA00 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x002B6CA0 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002B6CB0 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002B6CC0 size 0xC */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002DDA08 size 0x8 */
static unsigned char *LOAD_STOPPED_WORKOUT1P[2];                 /* @0x002DDA10 size 0x8 */
static unsigned char *LOAD_STOPPED_WORKOUT2P[2];                 /* @0x002DDA18 size 0x8 */
static unsigned char *SAVE_YN_SYSTEM[3];                         /* @0x002B6CD0 size 0xC */
static unsigned char *SAVE_YN_WORKOUT1P[2];                      /* @0x002DDA20 size 0x8 */
static unsigned char *SAVE_YN_WORKOUT2P[2];                      /* @0x002DDA28 size 0x8 */
static unsigned char *SAVING[4];                                 /* @0x002B6CE0 size 0x10 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002DDA30 size 0x8 */
static unsigned char *SAVE_OK_WORKOUT1P[2];                      /* @0x002DDA38 size 0x8 */
static unsigned char *SAVE_OK_WORKOUT2P[2];                      /* @0x002DDA40 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x002B6CF0 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002B6D00 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002B6D10 size 0xC */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002DDA48 size 0x8 */
static unsigned char *SAVE_STOPPED_WORKOUT1P[2];                 /* @0x002DDA50 size 0x8 */
static unsigned char *SAVE_STOPPED_WORKOUT2P[2];                 /* @0x002DDA58 size 0x8 */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002DDA60 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x002B6D20 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT1P[3];               /* @0x002B6D30 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT2P[3];               /* @0x002B6D40 size 0xC */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002DDA68 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[3];                       /* @0x002B6D50 size 0xC */
static unsigned char *WORKOUT_CONFIRM_NOT_SAVED[3];              /* @0x002B6D60 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT1P[3]; /* @0x002B6D70 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT2P[3]; /* @0x002B6D80 size 0xC */
unsigned char **mcMessageTbl_JAPANESE_S2[69];                    /* @0x002B6D90 size 0x114 */

#endif /* DDR_UNIT_src_CS_cmes_js2_c_H */
