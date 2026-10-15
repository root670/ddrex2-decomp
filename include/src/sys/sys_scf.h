/*
 * C:\work\usam2\src\sys\sys_scf.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x0021C410-0x0021C450
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _tag_SYS_SCF_WORK;

/* types (1) */
struct _tag_SYS_SCF_WORK {   // size 0x8
    /* 0x000 */ int date_notation;                    // 0x4
    /* 0x004 */ int language;                         // 0x4
};

/* variables (1) */
_tag_SYS_SCF_WORK *pscf;                                         /* @0x002A2A78 size 0x4 */

/* functions defined (2) */
int sysGetDateNotation(void);                                    /* 0x0021C410-0x0021C41C lines 41-42 */
void sysInitScf(_tag_SYS_SCF_WORK *p);                           /* 0x0021C420-0x0021C450 lines 24-34 */
