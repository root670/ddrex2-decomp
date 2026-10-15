/*
 * C:\work\usam2\src\CS\opening\openinglogo.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x002468E0-0x00246F6C
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* forward declarations */
struct _tag_cModeData; struct _tag_cFilepackData; struct _tag_cOpeninglogo;
struct _tag_cOpening;

/* types (4) */
struct _tag_cModeData {   // size 0x14
    /* 0x000 */ int (*Init)();                        // 0x4
    /* 0x004 */ int (*Control)();                     // 0x4
    /* 0x008 */ int (*View)();                        // 0x4
    /* 0x00C */ int (*Update)();                      // 0x4
    /* 0x010 */ int level;                            // 0x4
};

struct _tag_cOpeninglogo {   // size 0x1C
    /* 0x000 */ int logo_num;                         // 0x4
    /* 0x004 */ int bright;                           // 0x4
    /* 0x008 */ int disp_count;                       // 0x4
    /* 0x00C */ int fi_count;                         // 0x4
    /* 0x010 */ int fo_count;                         // 0x4
    /* 0x014 */ int cancel_count;                     // 0x4
    /* 0x018 */ int cancel_counter;                   // 0x4
};

struct _tag_cFilepackData {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
};

struct _tag_cOpening {   // size 0xA4
    /* 0x000 */ int StepOpening;                      // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int Cursor[4];                        // 0x10
    /* 0x020 */ int Step;                             // 0x4
    /* 0x024 */ int Mode;                             // 0x4
    /* 0x028 */ int NextMode;                         // 0x4
    /* 0x02C */ int bDraw;                            // 0x4
    /* 0x030 */ int bTopDown;                         // 0x4
    /* 0x034 */ int Step2;                            // 0x4
    /* 0x038 */ int init_ok;                          // 0x4
    /* 0x03C */ _tag_cModeData *mode_data_table;      // 0x4
    /* 0x040 */ _tag_cModeData *mode_data;            // 0x4
    /* 0x044 */ _tag_cFilepackData tblFilepack[5];    // 0x28
    /* 0x06C */ int draw_mcwnd;                       // 0x4
    /* 0x070 */ int msg_id;                           // 0x4
    /* 0x074 */ int mc_counter;                       // 0x4
    /* 0x078 */ int is_edit_folder_load_disp;         // 0x4
    /* 0x07C */ int mc_ret_init;                      // 0x4
    /* 0x080 */ int mc_ret;                           // 0x4
    /* 0x084 */ int mc_type;                          // 0x4
    /* 0x088 */ int mc_free;                          // 0x4
    /* 0x08C */ int mc_format;                        // 0x4
    /* 0x090 */ int mc_cmd;                           // 0x4
    /* 0x094 */ int mc_result;                        // 0x4
    /* 0x098 */ int bg_read_step;                     // 0x4
    /* 0x09C */ int edit_folder_load_read_flag;       // 0x4
    /* 0x0A0 */ int ddrobjs_read_flag;                // 0x4
};

/* variables (5) */
_tag_cOpeninglogo *pOpeninglogo;                                 /* @0x002A259C size 0x4 */
static int logo_tex_num[2];                                      /* @0x002A25A0 size 0x8 */
static int warn_tex_num[1];                                      /* @0x002A25A8 size 0x4 */
_tag_cOpening *pOpening;                                         /* @0x002A06C4 size 0x4 */
static _tag_cOpeninglogo _pOpeninglogo;                          /* @0x006B42E0 size 0x1C */

/* functions defined (8) */
int Update_Openingwarn(void);                                    /* 0x002468E0-0x00246908 lines 300-304 */
int View_Openingwarn(void);                                      /* 0x00246910-0x00246A38 lines 271-297 */
int Control_Openingwarn(void);                                   /* 0x00246A40-0x00246B9C lines 223-270 */
int Init_Openingwarn(void);                                      /* 0x00246BA0-0x00246C1C lines 206-222 */
int Update_Openinglogo(void);                                    /* 0x00246C20-0x00246C48 lines 184-192 */
int View_Openinglogo(void);                                      /* 0x00246C50-0x00246D78 lines 152-178 */
int Control_Openinglogo(void);                                   /* 0x00246D80-0x00246EE4 lines 78-148 */
int Init_Openinglogo(void);                                      /* 0x00246EF0-0x00246F6C lines 55-74 */
