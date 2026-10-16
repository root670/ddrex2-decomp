/*
 * C:\work2\usaex2\src\CS\cmes_e.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_cmes_e_c_H
#define DDR_UNIT_src_CS_cmes_e_c_H

/* variables (84) */
unsigned char *cmes_yesno_str_english[2];                        /* @0x002DD738 size 0x8 */
static unsigned char warning0[51];                               /* @0x002ABCC0 size 0x33 */
static unsigned char warning1[56];                               /* @0x002ABD00 size 0x38 */
static unsigned char *CHECKING[4];                               /* @0x002ABD40 size 0x10 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002DD740 size 0x8 */
static unsigned char *NO_DATA_WORKOUT1P[2];                      /* @0x002DD748 size 0x8 */
static unsigned char *NO_DATA_WORKOUT2P[2];                      /* @0x002DD750 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x002ABD50 size 0xC */
static unsigned char *UNFORMAT[3];                               /* @0x002ABD60 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x002ABD70 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x002ABD80 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x002ABD90 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x002ABDA0 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x002ABDB0 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x002ABDC0 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x002ABDD0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_SAVE[7];        /* @0x002ABDF0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_SAVE[7];        /* @0x002ABE10 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x002ABE30 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_LOAD[7];        /* @0x002ABE50 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_LOAD[7];        /* @0x002ABE70 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x002ABE90 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_START[7];       /* @0x002ABEB0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_START[7];       /* @0x002ABED0 size 0x1C */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x002ABEF0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x002ABF00 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_SAVE[3];        /* @0x002ABF10 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_LOAD[3];        /* @0x002ABF20 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_SAVE[3];        /* @0x002ABF30 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_LOAD[3];        /* @0x002ABF40 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x002ABF50 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x002ABF60 size 0xC */
static unsigned char *FORAMT_YN[4];                              /* @0x002ABF70 size 0x10 */
static unsigned char *FORMATTING[4];                             /* @0x002ABF80 size 0x10 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x002ABF90 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x002ABFA0 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[5];            /* @0x002ABFB0 size 0x14 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002DD758 size 0x8 */
static unsigned char *LOAD_YN_WORKOUT1P[2];                      /* @0x002DD760 size 0x8 */
static unsigned char *LOAD_YN_WORKOUT2P[2];                      /* @0x002DD768 size 0x8 */
static unsigned char *LOADING[4];                                /* @0x002ABFD0 size 0x10 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002DD770 size 0x8 */
static unsigned char *LOAD_OK_WORKOUT1P[2];                      /* @0x002DD778 size 0x8 */
static unsigned char *LOAD_OK_WORKOUT2P[2];                      /* @0x002DD780 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x002ABFE0 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002ABFF0 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002AC000 size 0xC */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002DD788 size 0x8 */
static unsigned char *LOAD_STOPPED_WORKOUT1P[2];                 /* @0x002DD790 size 0x8 */
static unsigned char *LOAD_STOPPED_WORKOUT2P[2];                 /* @0x002DD798 size 0x8 */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002DD7A0 size 0x8 */
static unsigned char *SAVE_YN_WORKOUT1P[2];                      /* @0x002DD7A8 size 0x8 */
static unsigned char *SAVE_YN_WORKOUT2P[2];                      /* @0x002DD7B0 size 0x8 */
static unsigned char *SAVING[4];                                 /* @0x002AC010 size 0x10 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002DD7B8 size 0x8 */
static unsigned char *SAVE_OK_WORKOUT1P[2];                      /* @0x002DD7C0 size 0x8 */
static unsigned char *SAVE_OK_WORKOUT2P[2];                      /* @0x002DD7C8 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x002AC020 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002AC030 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002AC040 size 0xC */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002DD7D0 size 0x8 */
static unsigned char *SAVE_STOPPED_WORKOUT1P[2];                 /* @0x002DD7D8 size 0x8 */
static unsigned char *SAVE_STOPPED_WORKOUT2P[2];                 /* @0x002DD7E0 size 0x8 */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002DD7E8 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x002AC050 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT1P[3];               /* @0x002AC060 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT2P[3];               /* @0x002AC070 size 0xC */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002DD7F0 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[3];                       /* @0x002AC080 size 0xC */
static unsigned char *WORKOUT_CONFIRM_NOT_SAVED[3];              /* @0x002AC090 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT1P[3]; /* @0x002AC0A0 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT2P[3]; /* @0x002AC0B0 size 0xC */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[6];          /* not allocated size 0x18 */
static unsigned char *NO_CARD_STOPY_YN_LOAD_AT_BOOT[6];          /* @0x002AC0C0 size 0x18 */
unsigned char **mcMessageTbl_ENGLISH[70];                        /* @0x002AC0E0 size 0x118 */
static unsigned char *mesElib_CHECKING[2];                       /* not allocated size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* not allocated size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* not allocated size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* not allocated size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* not allocated size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* not allocated size 0x8 */
static unsigned char *mesElib_NO_CARD[4];                        /* not allocated size 0x10 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* not allocated size 0x8 */
unsigned char **elibMessageTbl_ENGLISH[8];                       /* not allocated size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_e_c_H */
