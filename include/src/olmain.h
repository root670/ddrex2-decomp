/*
 * C:\work2\usaex2\src\olmain.c
 * MW MIPS C Compiler, overlay main; 27 functions, code 0x001E06B0-0x001E110C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_olmain_c_H
#define DDR_UNIT_src_olmain_c_H

#include "types/_tag_cOlData.h"
#include "types/_tag_cOlModule.h"
#include "types/_tag_cOlWork.h"

/* variables (5) */
static struct _tag_cOlWork *olwork;                              /* @0x002DDA70 size 0x4 */
static struct _tag_cOlData tblOlData[10];                        /* @0x002B6EB0 size 0x410 */
int sop_step;                                                    /* @0x002DE4D4 size 0x4 */
int sop_num;                                                     /* @0x002DE4D0 size 0x4 */
static struct _tag_cOlWork _olwork;                              /* @0x00712B60 size 0x40 */

/* functions referenced (1) */
void rom_load_th(void *);                                        /* @0x001E0BE0 */

/* functions defined (27) */
int Main_Dmm_ol(void);                                           /* 0x001E06B0-0x001E06B8 lines 886-886 */
void Init_Dmm_ol(void);                                          /* 0x001E06C0-0x001E0744 lines 881-883 */
void Term_Opt_ol(void);                                          /* 0x001E0750-0x001E0758 lines 867-867 */
int Step_Opt_ol(void);                                           /* 0x001E0760-0x001E0768 lines 866-866 */
void Init_Opt_ol(void);                                          /* 0x001E0770-0x001E07F4 lines 865-865 */
void SetPreRead_Opt(void);                                       /* 0x001E0800-0x001E083C lines 855-864 */
void SetPreRead_Rec(void);                                       /* 0x001E0840-0x001E087C lines 832-841 */
void Term_Rec_ol(void);                                          /* 0x001E0880-0x001E0888 lines 829-829 */
int Step_Rec_ol(void);                                           /* 0x001E0890-0x001E0898 lines 828-828 */
void Init_Rec_ol(void);                                          /* 0x001E08A0-0x001E0924 lines 827-827 */
void SetPreRead_Workout(void);                                   /* 0x001E0930-0x001E096C lines 811-820 */
void Term_Workout_ol(void);                                      /* 0x001E0970-0x001E0978 lines 808-808 */
int Step_Workout_ol(void);                                       /* 0x001E0980-0x001E0988 lines 807-807 */
void Init_Workout_ol(void);                                      /* 0x001E0990-0x001E0A14 lines 806-806 */
void Term_Les_ol(void);                                          /* 0x001E0A20-0x001E0A28 lines 800-800 */
int Step_Les_ol(void);                                           /* 0x001E0A30-0x001E0A38 lines 799-799 */
void Init_Les_ol(void);                                          /* 0x001E0A40-0x001E0AC0 lines 798-798 */
void SetPreRead_Les(void);                                       /* 0x001E0AC0-0x001E0AFC lines 788-797 */
void Term_Info_ol(void);                                         /* 0x001E0B00-0x001E0B08 lines 783-783 */
int Step_Info_ol(void);                                          /* 0x001E0B10-0x001E0B18 lines 782-782 */
void Init_Info_ol(void);                                         /* 0x001E0B20-0x001E0BA0 lines 781-781 */
void SetPreRead_Info(void);                                      /* 0x001E0BA0-0x001E0BDC lines 771-780 */
static void rom_load_th(void);                                   /* 0x001E0BE0-0x001E0C0C lines 755-763 */
int SetOverlayPos_main(void);                                    /* 0x001E0C10-0x001E0DA8 lines 691-736 */
void SetOverlayPos_init(void);                                   /* 0x001E0DB0-0x001E0DB8 lines 690-690 */
int Main_Overlay(int _ol_class);                                 /* 0x001E0DC0-0x001E1064 lines 513-672 */
void Init_Overlay(int _ol_class, int _ol_id);                    /* 0x001E1070-0x001E110C lines 492-508 */

#endif /* DDR_UNIT_src_olmain_c_H */
