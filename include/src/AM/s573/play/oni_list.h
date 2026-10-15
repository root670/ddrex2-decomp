/*
 * C:\work\usam2\src\AM\s573\play\oni_list.c
 * MW MIPS C Compiler, overlay main; 0 functions
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct oni_mode; struct oni_course; struct oni_steps;

/* types (3) */
struct oni_mode {   // size 0xC
    /* 0x000 */ unsigned int link_num;                // 0x4
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ unsigned char seq_transfer;           // 0x1
    /* 0x006 */ unsigned char sp_music;               // 0x1
    /* 0x007 */ unsigned char add_life;               // 0x1
    /* 0x008 */ unsigned int hidden : 2;              // bits 0..1
    /* 0x008 */ unsigned int thinout : 1;             // bits 2..2
    /* 0x008 */ unsigned int free : 1;                // bits 3..3
    /* 0x008 */ unsigned int soft : 1;                // bits 4..4
    /* 0x008 */ unsigned int boost : 2;               // bits 5..6
    /* 0x008 */ unsigned int speed : 5;               // bits 7..11
    /* 0x008 */ unsigned int scroll : 2;              // bits 12..13
    /* 0x008 */ unsigned int freeze : 1;              // bits 14..14
    /* 0x008 */ unsigned int vivid : 2;               // bits 15..16
    /* 0x008 */ unsigned int anime : 2;               // bits 17..18
    /* 0x008 */ unsigned int dark : 1;                // bits 19..19
    /* 0x008 */ unsigned int pad : 12;                // bits 20..31
};

struct oni_course {   // size 0x110
    /* 0x000 */ unsigned int course_allnum;           // 0x4
    /* 0x004 */ unsigned int course_defnum;           // 0x4
    /* 0x008 */ short flag;                           // 0x2
    /* 0x00A */ short order;                          // 0x2
    /* 0x00C */ short start_life;                     // 0x2
    /* 0x00E */ short stage;                          // 0x2
    /* 0x010 */ int single_steps;                     // 0x4
    /* 0x014 */ int double_steps;                     // 0x4
    /* 0x018 */ int hide;                             // 0x4
    /* 0x01C */ int option;                           // 0x4
    /* 0x020 */ oni_mode mode[20];                    // 0xF0
};

struct oni_steps {   // size 0x14
    /* 0x000 */ unsigned int link_num;                // 0x4
    /* 0x004 */ unsigned short steps[2][4];           // 0x10
};

/* variables (3) */
oni_course course_list[23];                                      /* @0x00283000 size 0x1870 */
oni_course diet_course_list[9];                                  /* @0x00284870 size 0x990 */
oni_steps oni_steps_table[1];                                    /* not allocated size 0x14 */
