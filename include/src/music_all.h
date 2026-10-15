/*
 * C:\work\usam2\src\music_all.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0022AD30-0x0022AE60
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _tag_cMusicData;

/* types (1) */
struct _tag_cMusicData {   // size 0x14
    /* 0x000 */ int link_num;                         // 0x4
    /* 0x004 */ unsigned char *base_name;             // 0x4
    /* 0x008 */ unsigned char *music_name;            // 0x4
    /* 0x00C */ unsigned char *music_name_mc;         // 0x4
    /* 0x010 */ unsigned char *artist_name;           // 0x4
};

/* variables (1) */
static _tag_cMusicData tblMusicData[546];                        /* @0x0027F800 size 0x2AA8 */

/* functions defined (3) */
_tag_cMusicData *GetMusicData_by_link_num(unsigned short link_num); /* 0x0022AD30-0x0022AD90 lines 803-815 */
_tag_cMusicData *GetMusicData_by_base_name(unsigned char *base_name); /* 0x0022AD90-0x0022AE28 lines 786-799 */
_tag_cMusicData *GetMusicData_by_index(int id);                  /* 0x0022AE30-0x0022AE60 lines 779-783 */
