/*
 * C:\work\usam2\src\sys\sys_demo.c
 * MW MIPS C Compiler, overlay main; 1 functions, code 0x00227B00-0x00227B08
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _tag_SYS_DEMO_WORK;

/* types (1) */
struct _tag_SYS_DEMO_WORK {   // size 0x54
    /* 0x000 */ int mode;                             // 0x4
    /* 0x004 */ int inactive_flag;                    // 0x4
    /* 0x008 */ int inactive_counter;                 // 0x4
    /* 0x00C */ int gameplay_flag;                    // 0x4
    /* 0x010 */ int gameplay_counter;                 // 0x4
    /* 0x014 */ int end_screen_request;               // 0x4
    /* 0x018 */ int main_loop_break_request;          // 0x4
    /* 0x01C */ struct {   // size 0x24
        /* 0x000 */ unsigned int lsn;                     // 0x4
        /* 0x004 */ unsigned int size;                    // 0x4
        /* 0x008 */ char name[16];                        // 0x10
        /* 0x018 */ unsigned char date[8];                // 0x8
        /* 0x020 */ unsigned int flag;                    // 0x4
    } cdl_file;
    /* 0x040 */ unsigned short language;              // 0x2
    /* 0x042 */ unsigned short aspect;                // 0x2
    /* 0x044 */ unsigned short playmode;              // 0x2
    /* 0x046 */ unsigned short to_inactive;           // 0x2
    /* 0x048 */ unsigned short to_gameplay;           // 0x2
    /* 0x04A */ unsigned short mediatype;             // 0x2
    /* 0x04C */ unsigned short masterVolScale;        // 0x2
    /* 0x04E */ unsigned short dirSector;             // 0x2
    /* 0x050 */ int why;                              // 0x4
};

/* variables (1) */
_tag_SYS_DEMO_WORK *pdemo;                                       /* @0x002A2AA0 size 0x4 */

/* functions defined (1) */
void sysDemoSet(_tag_SYS_DEMO_WORK *p);                          /* 0x00227B00-0x00227B08 lines 54-54 */
