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
unsigned char *cmes_yesno_str_spanish[2];                        /* @0x002A2350 size 0x8 */
static unsigned char *CHECKING[6];                               /* @0x00286B70 size 0x18 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002A2358 size 0x8 */
static unsigned char *NO_DATA_DIET1P[3];                         /* @0x00286B88 size 0xC */
static unsigned char *NO_DATA_DIET2P[3];                         /* @0x00286B98 size 0xC */
static unsigned char *NO_CARD[4];                                /* @0x00286BB0 size 0x10 */
static unsigned char *UNFORMAT[3];                               /* @0x00286BC0 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x00286BD0 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x00286BE0 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[5];                   /* @0x00286BF0 size 0x14 */
static unsigned char *NO_CARD_STOP_YN_LOAD[5];                   /* @0x00286C10 size 0x14 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x00286C30 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x00286C40 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x00286C50 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x00286C70 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x00286C90 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x00286CB0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x00286CD0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x00286CF0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x00286D10 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x00286D30 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x00286D50 size 0x1C */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x00286D70 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x00286D80 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[4];           /* @0x00286D90 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[4];           /* @0x00286DA0 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[4];           /* @0x00286DB0 size 0x10 */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[4];           /* @0x00286DC0 size 0x10 */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x00286DD0 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x00286DE0 size 0xC */
static unsigned char *FORMAT_YN[5];                              /* @0x00286DF0 size 0x14 */
static unsigned char *FORMATTING[6];                             /* @0x00286E10 size 0x18 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x00286E28 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x00286E38 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[6];            /* @0x00286E50 size 0x18 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002A2360 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[3];                         /* @0x00286E68 size 0xC */
static unsigned char *LOAD_YN_DIET2P[3];                         /* @0x00286E78 size 0xC */
static unsigned char *LOADING[6];                                /* @0x00286E90 size 0x18 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002A2368 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[3];                         /* @0x00286EA8 size 0xC */
static unsigned char *LOAD_OK_DIET2P[3];                         /* @0x00286EB8 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x00286EC8 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[4];               /* @0x00286EE0 size 0x10 */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[4];               /* @0x00286EF0 size 0x10 */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002A2370 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[3];                    /* @0x00286F00 size 0xC */
static unsigned char *LOAD_STOPPED_DIET2P[3];                    /* @0x00286F10 size 0xC */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002A2378 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[3];                         /* @0x00286F20 size 0xC */
static unsigned char *SAVE_YN_DIET2P[3];                         /* @0x00286F30 size 0xC */
static unsigned char *SAVING[6];                                 /* @0x00286F40 size 0x18 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002A2380 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[3];                         /* @0x00286F58 size 0xC */
static unsigned char *SAVE_OK_DIET2P[3];                         /* @0x00286F68 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x00286F78 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[4];               /* @0x00286F90 size 0x10 */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[4];               /* @0x00286FA0 size 0x10 */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002A2388 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[3];                    /* @0x00286FB0 size 0xC */
static unsigned char *SAVE_STOPPED_DIET2P[3];                    /* @0x00286FC0 size 0xC */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002A2390 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x00286FD0 size 0xC */
static unsigned char *SAVE_CREATE_YN_DIET1P[4];                  /* @0x00286FE0 size 0x10 */
static unsigned char *SAVE_CREATE_YN_DIET2P[4];                  /* @0x00286FF0 size 0x10 */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002A2398 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[4];                       /* @0x00287000 size 0x10 */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x00287010 size 0xC */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[4];  /* @0x00287020 size 0x10 */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[4];  /* @0x00287030 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[8];          /* not allocated size 0x20 */
unsigned char **mcMessageTbl_SPANISH[69];                        /* @0x00287040 size 0x114 */
static unsigned char *mesElib_CHECKING[2];                       /* @0x002A23A0 size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002A23A8 size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* @0x002A23B0 size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002A23B8 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002A23C0 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002A23C8 size 0x8 */
static unsigned char *mesElib_NO_CARD[6];                        /* @0x00287160 size 0x18 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002A23D0 size 0x8 */
unsigned char **elibMessageTbl_SPANISH[8];                       /* @0x00287180 size 0x20 */

#endif /* DDR_UNIT_src_CS_cmes_s_c_H */
