/*
 * C:\work\usam2\src\CS\cmes_f.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* variables (81) */
unsigned char *cmes_yesno_str_french[2];                         /* @0x002A2288 size 0x8 */
static unsigned char *CHECKING[6];                               /* @0x002865C0 size 0x18 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002A2290 size 0x8 */
static unsigned char *NO_DATA_DIET1P[2];                         /* @0x002A2298 size 0x8 */
static unsigned char *NO_DATA_DIET2P[2];                         /* @0x002A22A0 size 0x8 */
static unsigned char *NO_CARD[4];                                /* @0x002865E0 size 0x10 */
static unsigned char *UNFORMAT[3];                               /* @0x002865F0 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x00286600 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x00286610 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[5];                   /* @0x00286620 size 0x14 */
static unsigned char *NO_CARD_STOP_YN_LOAD[5];                   /* @0x00286640 size 0x14 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x00286660 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x00286670 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x00286680 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x002866A0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x002866C0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x002866E0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x00286700 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x00286720 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x00286740 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x00286760 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x00286780 size 0x1C */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x002867A0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x002867B0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[3];           /* @0x002867C0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[3];           /* @0x002867D0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[3];           /* @0x002867E0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[3];           /* @0x002867F0 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x00286800 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x00286810 size 0xC */
static unsigned char *FORMAT_YN[5];                              /* @0x00286820 size 0x14 */
static unsigned char *FORMATTING[6];                             /* @0x00286840 size 0x18 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x00286858 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x00286868 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[5];            /* @0x00286880 size 0x14 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002A22A8 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[2];                         /* @0x002A22B0 size 0x8 */
static unsigned char *LOAD_YN_DIET2P[2];                         /* @0x002A22B8 size 0x8 */
static unsigned char *LOADING[6];                                /* @0x002868A0 size 0x18 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002A22C0 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[2];                         /* @0x002A22C8 size 0x8 */
static unsigned char *LOAD_OK_DIET2P[2];                         /* @0x002A22D0 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x002868B8 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[4];               /* @0x002868D0 size 0x10 */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[4];               /* @0x002868E0 size 0x10 */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002A22D8 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[3];                    /* @0x002868F0 size 0xC */
static unsigned char *LOAD_STOPPED_DIET2P[3];                    /* @0x00286900 size 0xC */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002A22E0 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[2];                         /* @0x002A22E8 size 0x8 */
static unsigned char *SAVE_YN_DIET2P[2];                         /* @0x002A22F0 size 0x8 */
static unsigned char *SAVING[6];                                 /* @0x00286910 size 0x18 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002A22F8 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[2];                         /* @0x002A2300 size 0x8 */
static unsigned char *SAVE_OK_DIET2P[2];                         /* @0x002A2308 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x00286928 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[4];               /* @0x00286940 size 0x10 */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[4];               /* @0x00286950 size 0x10 */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002A2310 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[3];                    /* @0x00286960 size 0xC */
static unsigned char *SAVE_STOPPED_DIET2P[3];                    /* @0x00286970 size 0xC */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002A2318 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x00286980 size 0xC */
static unsigned char *SAVE_CREATE_YN_DIET1P[3];                  /* @0x00286990 size 0xC */
static unsigned char *SAVE_CREATE_YN_DIET2P[3];                  /* @0x002869A0 size 0xC */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002A2320 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[4];                       /* @0x002869B0 size 0x10 */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x002869C0 size 0xC */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[4];  /* @0x002869D0 size 0x10 */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[4];  /* @0x002869E0 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[7];          /* not allocated size 0x1C */
unsigned char **mcMessageTbl_FRENCH[69];                         /* @0x002869F0 size 0x114 */
static unsigned char *mesElib_CHECKING[3];                       /* @0x00286B08 size 0xC */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002A2328 size 0x8 */
static unsigned char *mesElib_LOADING[3];                        /* @0x00286B18 size 0xC */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002A2330 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002A2338 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002A2340 size 0x8 */
static unsigned char *mesElib_NO_CARD[6];                        /* @0x00286B30 size 0x18 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002A2348 size 0x8 */
unsigned char **elibMessageTbl_FRENCH[8];                        /* @0x00286B50 size 0x20 */
