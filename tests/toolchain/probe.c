/* tests/toolchain/probe.c */
typedef struct { int date_notation; int language; } _tag_SYS_SCF_WORK;
_tag_SYS_SCF_WORK *pscf;
int sysGetDateNotation(void) { return pscf->date_notation; }
void sysInitScf(_tag_SYS_SCF_WORK *p) { pscf = p; p->date_notation = 0; }
