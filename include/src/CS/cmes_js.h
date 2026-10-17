/*
 * C:\work2\usaex2\src\CS\cmes_js.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_cmes_js_c_H
#define DDR_UNIT_src_CS_cmes_js_c_H

/* variables (73) */
unsigned char *cmes_yesno_str_japanese_s[2];                     /* @0x002DD8C0 size 0x8 */
static unsigned char warning0[39];                               /* @0x002B2620 size 0x27 */
static unsigned char warning1[53];                               /* @0x002B2650 size 0x35 */
static unsigned char *CHECKING[4];                               /* @0x002B2690 size 0x10 */
static unsigned char *NO_DATA_SYSTEM[3];                         /* @0x002B26A0 size 0xC */
static unsigned char *NO_DATA_WORKOUT1P[2];                      /* @0x002DD8C8 size 0x8 */
static unsigned char *NO_DATA_WORKOUT2P[2];                      /* @0x002DD8D0 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x002B26B0 size 0xC */
static unsigned char *UNFORMAT[3];                               /* @0x002B26C0 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x002B26D0 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x002B26E0 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x002B26F0 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x002B2700 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x002B2710 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x002B2720 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x002B2730 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_SAVE[6];        /* @0x002B2750 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_SAVE[6];        /* @0x002B2770 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x002B2790 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_LOAD[6];        /* @0x002B27B0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_LOAD[6];        /* @0x002B27D0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x002B27F0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_START[6];       /* @0x002B2810 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_START[6];       /* @0x002B2830 size 0x18 */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[4];           /* @0x002B2850 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[4];           /* @0x002B2860 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_SAVE[3];        /* @0x002B2870 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_LOAD[3];        /* @0x002B2880 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_SAVE[3];        /* @0x002B2890 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_LOAD[3];        /* @0x002B28A0 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x002B28B0 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x002B28C0 size 0xC */
static unsigned char *FORAMT_YN[4];                              /* @0x002B28D0 size 0x10 */
static unsigned char *FORMATTING[4];                             /* @0x002B28E0 size 0x10 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x002B28F0 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x002B2900 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[4];            /* @0x002B2910 size 0x10 */
static unsigned char *LOAD_YN_SYSTEM[3];                         /* @0x002B2920 size 0xC */
static unsigned char *LOAD_YN_WORKOUT1P[2];                      /* @0x002DD8D8 size 0x8 */
static unsigned char *LOAD_YN_WORKOUT2P[2];                      /* @0x002DD8E0 size 0x8 */
static unsigned char *LOADING[4];                                /* @0x002B2930 size 0x10 */
static unsigned char *LOAD_OK_SYSTEM[3];                         /* @0x002B2940 size 0xC */
static unsigned char *LOAD_OK_WORKOUT1P[2];                      /* @0x002DD8E8 size 0x8 */
static unsigned char *LOAD_OK_WORKOUT2P[2];                      /* @0x002DD8F0 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[4];               /* @0x002B2950 size 0x10 */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002B2960 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002B2970 size 0xC */
static unsigned char *LOAD_STOPPED_SYSTEM[3];                    /* @0x002B2980 size 0xC */
static unsigned char *LOAD_STOPPED_WORKOUT1P[2];                 /* @0x002DD8F8 size 0x8 */
static unsigned char *LOAD_STOPPED_WORKOUT2P[2];                 /* @0x002DD900 size 0x8 */
static unsigned char *SAVE_YN_SYSTEM[3];                         /* @0x002B2990 size 0xC */
static unsigned char *SAVE_YN_WORKOUT1P[2];                      /* @0x002DD908 size 0x8 */
static unsigned char *SAVE_YN_WORKOUT2P[2];                      /* @0x002DD910 size 0x8 */
static unsigned char *SAVING[4];                                 /* @0x002B29A0 size 0x10 */
static unsigned char *SAVE_OK_SYSTEM[3];                         /* @0x002B29B0 size 0xC */
static unsigned char *SAVE_OK_WORKOUT1P[2];                      /* @0x002DD918 size 0x8 */
static unsigned char *SAVE_OK_WORKOUT2P[2];                      /* @0x002DD920 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[4];               /* @0x002B29C0 size 0x10 */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002B29D0 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002B29E0 size 0xC */
static unsigned char *SAVE_STOPPED_SYSTEM[3];                    /* @0x002B29F0 size 0xC */
static unsigned char *SAVE_STOPPED_WORKOUT1P[2];                 /* @0x002DD928 size 0x8 */
static unsigned char *SAVE_STOPPED_WORKOUT2P[2];                 /* @0x002DD930 size 0x8 */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002DD938 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x002B2A00 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT1P[3];               /* @0x002B2A10 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT2P[3];               /* @0x002B2A20 size 0xC */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002DD940 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[3];                       /* @0x002B2A30 size 0xC */
static unsigned char *WORKOUT_CONFIRM_NOT_SAVED[3];              /* @0x002B2A40 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT1P[3]; /* @0x002B2A50 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT2P[3]; /* @0x002B2A60 size 0xC */
unsigned char **mcMessageTbl_JAPANESE_S[69];                     /* @0x002B2A70 size 0x114 */

#endif /* DDR_UNIT_src_CS_cmes_js_c_H */
