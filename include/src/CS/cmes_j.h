/*
 * C:\work2\usaex2\src\CS\cmes_j.c
 * MW MIPS C Compiler, overlay main; 0 functions
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
#ifndef DDR_UNIT_src_CS_cmes_j_c_H
#define DDR_UNIT_src_CS_cmes_j_c_H

/* variables (83) */
unsigned char *cmes_yesno_str_japanese[2];                       /* @0x002DD800 size 0x8 */
static unsigned char warning0[39];                               /* @0x002AF820 size 0x27 */
static unsigned char warning1[53];                               /* @0x002AF850 size 0x35 */
static unsigned char *CHECKING[4];                               /* @0x002AF890 size 0x10 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002DD808 size 0x8 */
static unsigned char *NO_DATA_WORKOUT1P[2];                      /* @0x002DD810 size 0x8 */
static unsigned char *NO_DATA_WORKOUT2P[2];                      /* @0x002DD818 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x002AF8A0 size 0xC */
static unsigned char *UNFORMAT[3];                               /* @0x002AF8B0 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x002AF8C0 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x002AF8D0 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x002AF8E0 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x002AF8F0 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x002AF900 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x002AF910 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[5];           /* @0x002AF920 size 0x14 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_SAVE[6];        /* @0x002AF940 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_SAVE[6];        /* @0x002AF960 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[5];           /* @0x002AF980 size 0x14 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_LOAD[6];        /* @0x002AF9A0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_LOAD[6];        /* @0x002AF9C0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x002AF9E0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT1P_START[6];       /* @0x002AFA00 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_WORKOUT2P_START[6];       /* @0x002AFA20 size 0x18 */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x002AFA38 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x002AFA48 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_SAVE[3];        /* @0x002AFA58 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT1P_LOAD[3];        /* @0x002AFA68 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_SAVE[3];        /* @0x002AFA78 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_WORKOUT2P_LOAD[3];        /* @0x002AFA88 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x002AFA98 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x002AFAA8 size 0xC */
static unsigned char *FORAMT_YN[4];                              /* @0x002AFAC0 size 0x10 */
static unsigned char *FORMATTING[4];                             /* @0x002AFAD0 size 0x10 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x002AFAE0 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x002AFAF0 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[4];            /* @0x002AFB00 size 0x10 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002DD820 size 0x8 */
static unsigned char *LOAD_YN_WORKOUT1P[2];                      /* @0x002DD828 size 0x8 */
static unsigned char *LOAD_YN_WORKOUT2P[2];                      /* @0x002DD830 size 0x8 */
static unsigned char *LOADING[4];                                /* @0x002AFB10 size 0x10 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002DD838 size 0x8 */
static unsigned char *LOAD_OK_WORKOUT1P[2];                      /* @0x002DD840 size 0x8 */
static unsigned char *LOAD_OK_WORKOUT2P[2];                      /* @0x002DD848 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x002AFB20 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002AFB30 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002AFB40 size 0xC */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002DD850 size 0x8 */
static unsigned char *LOAD_STOPPED_WORKOUT1P[2];                 /* @0x002DD858 size 0x8 */
static unsigned char *LOAD_STOPPED_WORKOUT2P[2];                 /* @0x002DD860 size 0x8 */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002DD868 size 0x8 */
static unsigned char *SAVE_YN_WORKOUT1P[2];                      /* @0x002DD870 size 0x8 */
static unsigned char *SAVE_YN_WORKOUT2P[2];                      /* @0x002DD878 size 0x8 */
static unsigned char *SAVING[4];                                 /* @0x002AFB50 size 0x10 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002DD880 size 0x8 */
static unsigned char *SAVE_OK_WORKOUT1P[2];                      /* @0x002DD888 size 0x8 */
static unsigned char *SAVE_OK_WORKOUT2P[2];                      /* @0x002DD890 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x002AFB60 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT1P[3];            /* @0x002AFB70 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_WORKOUT2P[3];            /* @0x002AFB80 size 0xC */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002DD898 size 0x8 */
static unsigned char *SAVE_STOPPED_WORKOUT1P[2];                 /* @0x002DD8A0 size 0x8 */
static unsigned char *SAVE_STOPPED_WORKOUT2P[2];                 /* @0x002DD8A8 size 0x8 */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002DD8B0 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x002AFB90 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT1P[3];               /* @0x002AFBA0 size 0xC */
static unsigned char *SAVE_CREATE_YN_WORKOUT2P[3];               /* @0x002AFBB0 size 0xC */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002DD8B8 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[3];                       /* @0x002AFBC0 size 0xC */
static unsigned char *WORKOUT_CONFIRM_NOT_SAVED[3];              /* @0x002AFBD0 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT1P[3]; /* @0x002AFBE0 size 0xC */
static unsigned char *WORKOUT_CONFIRM_SAVE_CLEARED_DATA_WORKOUT2P[3]; /* @0x002AFBF0 size 0xC */
static unsigned char *NO_CARD_STOP_YN_LOAD_AT_BOOT[7];           /* @0x002AFC00 size 0x1C */
unsigned char **mcMessageTbl_JAPANESE[70];                       /* @0x002AFC20 size 0x118 */
static unsigned char *mesElib_CHECKING[2];                       /* not allocated size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* not allocated size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* not allocated size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* not allocated size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* not allocated size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* not allocated size 0x8 */
static unsigned char *mesElib_NO_CARD[3];                        /* not allocated size 0xC */
static unsigned char *mesElib_UNFORMATTED[3];                    /* not allocated size 0xC */
unsigned char **elibMessageTbl_JAPANESE[8];                      /* not allocated size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_j_c_H */
