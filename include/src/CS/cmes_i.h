/*
 * C:\work\usam2\src\CS\cmes_i.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* variables (81) */
unsigned char *cmes_yesno_str_italian[2];                        /* @0x002A23D8 size 0x8 */
static unsigned char *CHECKING[6];                               /* @0x002871A0 size 0x18 */
static unsigned char *NO_DATA_SYSTEM[2];                         /* @0x002A23E0 size 0x8 */
static unsigned char *NO_DATA_DIET1P[2];                         /* @0x002A23E8 size 0x8 */
static unsigned char *NO_DATA_DIET2P[2];                         /* @0x002A23F0 size 0x8 */
static unsigned char *NO_CARD[3];                                /* @0x002871B8 size 0xC */
static unsigned char *UNFORMAT[3];                               /* @0x002871C8 size 0xC */
static unsigned char *CHECK_ERR[3];                              /* @0x002871D8 size 0xC */
static unsigned char *CHECK_ERR_RETRY_YN[4];                     /* @0x002871F0 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_SAVE[4];                   /* @0x00287200 size 0x10 */
static unsigned char *NO_CARD_STOP_YN_LOAD[4];                   /* @0x00287210 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_SAVE[4];                  /* @0x00287220 size 0x10 */
static unsigned char *UNFORMAT_STOP_YN_LOAD[4];                  /* @0x00287230 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_SAVE[6];           /* @0x00287240 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_SAVE[7];           /* @0x00287260 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_SAVE[7];           /* @0x00287280 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_LOAD[6];           /* @0x002872A0 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_LOAD[7];           /* @0x002872C0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_LOAD[7];           /* @0x002872E0 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_SYSTEM_START[6];          /* @0x00287300 size 0x18 */
static unsigned char *NO_SPACE_STOP_YN_DIET1P_START[7];          /* @0x00287320 size 0x1C */
static unsigned char *NO_SPACE_STOP_YN_DIET2P_START[7];          /* @0x00287340 size 0x1C */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_SAVE[3];           /* @0x00287360 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_SYSTEM_LOAD[3];           /* @0x00287370 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_SAVE[3];           /* @0x00287380 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET1P_LOAD[3];           /* @0x00287390 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_SAVE[3];           /* @0x002873A0 size 0xC */
static unsigned char *ERR_DATA_STOP_YN_DIET2P_LOAD[3];           /* @0x002873B0 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_SAVE[3];             /* @0x002873C0 size 0xC */
static unsigned char *CHECK_STOPPED_STOP_YN_LOAD[3];             /* @0x002873D0 size 0xC */
static unsigned char *FORMAT_YN[5];                              /* @0x002873E0 size 0x14 */
static unsigned char *FORMATTING[6];                             /* @0x00287400 size 0x18 */
static unsigned char *FORMAT_ERR_RETRY_YN[3];                    /* @0x00287418 size 0xC */
static unsigned char *FORMAT_ERR_STOP_SAVE_YN[3];                /* @0x00287428 size 0xC */
static unsigned char *FORMAT_ERR_OUT_STOP_SAVE_YN[4];            /* @0x00287440 size 0x10 */
static unsigned char *LOAD_YN_SYSTEM[2];                         /* @0x002A23F8 size 0x8 */
static unsigned char *LOAD_YN_DIET1P[2];                         /* @0x002A2400 size 0x8 */
static unsigned char *LOAD_YN_DIET2P[2];                         /* @0x002A2408 size 0x8 */
static unsigned char *LOADING[6];                                /* @0x00287450 size 0x18 */
static unsigned char *LOAD_OK_SYSTEM[2];                         /* @0x002A2410 size 0x8 */
static unsigned char *LOAD_OK_DIET1P[2];                         /* @0x002A2418 size 0x8 */
static unsigned char *LOAD_OK_DIET2P[2];                         /* @0x002A2420 size 0x8 */
static unsigned char *LOAD_ERR_RETRY_YN_SYSTEM[3];               /* @0x00287468 size 0xC */
static unsigned char *LOAD_ERR_RETRY_YN_DIET1P[4];               /* @0x00287480 size 0x10 */
static unsigned char *LOAD_ERR_RETRY_YN_DIET2P[4];               /* @0x00287490 size 0x10 */
static unsigned char *LOAD_STOPPED_SYSTEM[2];                    /* @0x002A2428 size 0x8 */
static unsigned char *LOAD_STOPPED_DIET1P[3];                    /* @0x002874A0 size 0xC */
static unsigned char *LOAD_STOPPED_DIET2P[3];                    /* @0x002874B0 size 0xC */
static unsigned char *SAVE_YN_SYSTEM[2];                         /* @0x002A2430 size 0x8 */
static unsigned char *SAVE_YN_DIET1P[2];                         /* @0x002A2438 size 0x8 */
static unsigned char *SAVE_YN_DIET2P[2];                         /* @0x002A2440 size 0x8 */
static unsigned char *SAVING[6];                                 /* @0x002874C0 size 0x18 */
static unsigned char *SAVE_OK_SYSTEM[2];                         /* @0x002A2448 size 0x8 */
static unsigned char *SAVE_OK_DIET1P[2];                         /* @0x002A2450 size 0x8 */
static unsigned char *SAVE_OK_DIET2P[2];                         /* @0x002A2458 size 0x8 */
static unsigned char *SAVE_ERR_RETRY_YN_SYSTEM[3];               /* @0x002874D8 size 0xC */
static unsigned char *SAVE_ERR_RETRY_YN_DIET1P[4];               /* @0x002874F0 size 0x10 */
static unsigned char *SAVE_ERR_RETRY_YN_DIET2P[4];               /* @0x00287500 size 0x10 */
static unsigned char *SAVE_STOPPED_SYSTEM[2];                    /* @0x002A2460 size 0x8 */
static unsigned char *SAVE_STOPPED_DIET1P[3];                    /* @0x00287510 size 0xC */
static unsigned char *SAVE_STOPPED_DIET2P[3];                    /* @0x00287520 size 0xC */
static unsigned char *SAVE_OVERWRITE_YN[2];                      /* @0x002A2468 size 0x8 */
static unsigned char *SAVE_CREATE_YN_SYSTEM[3];                  /* @0x00287530 size 0xC */
static unsigned char *SAVE_CREATE_YN_DIET1P[3];                  /* @0x00287540 size 0xC */
static unsigned char *SAVE_CREATE_YN_DIET2P[3];                  /* @0x00287550 size 0xC */
static unsigned char *START_LIKE_THIS_YN[2];                     /* @0x002A2470 size 0x8 */
static unsigned char *AUTO_SAVE_USE_YN[3];                       /* @0x00287560 size 0xC */
static unsigned char *DIET_CONFIRM_NOT_SAVED[3];                 /* @0x00287570 size 0xC */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET1P[4];  /* @0x00287580 size 0x10 */
static unsigned char *DIET_CONFIRM_SAVE_CLEARED_DATA_DIET2P[4];  /* @0x00287590 size 0x10 */
static unsigned char *NO_SPACE_STOP_YN_START_SYSTEM[6];          /* not allocated size 0x18 */
unsigned char **mcMessageTbl_ITALIAN[69];                        /* @0x002875A0 size 0x114 */
static unsigned char *mesElib_CHECKING[2];                       /* @0x002A2478 size 0x8 */
static unsigned char *mesElib_LOAD_YN[2];                        /* @0x002A2480 size 0x8 */
static unsigned char *mesElib_LOADING[2];                        /* @0x002A2488 size 0x8 */
static unsigned char *mesElib_CHECK_FAILED[2];                   /* @0x002A2490 size 0x8 */
static unsigned char *mesElib_LOAD_FAILED[2];                    /* @0x002A2498 size 0x8 */
static unsigned char *mesElib_NO_DATA[2];                        /* @0x002A24A0 size 0x8 */
static unsigned char *mesElib_NO_CARD[5];                        /* @0x002876C0 size 0x14 */
static unsigned char *mesElib_UNFORMATTED[2];                    /* @0x002A24A8 size 0x8 */
unsigned char **elibMessageTbl_ITALIAN[8];                       /* @0x002876E0 size 0x20 */
