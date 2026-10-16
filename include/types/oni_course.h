/* struct oni_course -- 11 members, size 0x110, layout 38f31f8f8916.
 *
 * One definition, agreed by the 15 units that declare it: les.c (DIE 0x5465).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct oni_course *`.
 *
 * declared by: les.c (DIE 0x5465), les_play.c (DIE 0x12360), reconi.c (DIE 0x22565), onimode.c (DIE 0x2AC52), recend.c (DIE 0x375BB), eds_select.c (DIE 0x3DAD3), eds_main.c (DIE 0x43D84), optscr.c (DIE 0x4A510), oni_list.c (DIE 0x4DECC), eds_aid.c (DIE 0x527A7), eds_break.c (DIE 0x598A0), eds_record.c (DIE 0x5D66C), optdoll.c (DIE 0x93492), dexport.c (DIE 0x98707), dinit.c (DIE 0x9CFF4)
 */
#ifndef DDR_types_oni_course_H
#define DDR_types_oni_course_H

struct oni_mode;

#include "types/oni_mode.h"

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
    /* 0x020 */ struct oni_mode mode[20];             // 0xF0
};

#endif /* DDR_types_oni_course_H */
