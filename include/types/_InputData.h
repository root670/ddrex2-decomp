/* struct _InputData -- 7 members, size 0x20, layout 24d0a0d472ef.
 *
 * One definition, agreed by the 4 units that declare it: les_play.c (DIE 0x11D0C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _InputData *`.
 *
 * declared by: les_play.c (DIE 0x11D0C), onimode.c (DIE 0x2C9E2), sp_ending_d.c (DIE 0x32F0B), eds_select.c (DIE 0x3D2B2)
 */
#ifndef DDR_types__InputData_H
#define DDR_types__InputData_H

struct _InputData {   // size 0x20
    /* 0x000 */ unsigned short player_input[4];       // 0x8
    /* 0x008 */ unsigned short player_input_trigger[4];  // 0x8
    /* 0x010 */ unsigned short player_input_released[4];  // 0x8
    /* 0x018 */ unsigned short etc;                   // 0x2
    /* 0x01A */ unsigned short etc_trigger;           // 0x2
    /* 0x01C */ unsigned short etc_released;          // 0x2
    /* 0x01E */ unsigned short padding;               // 0x2
};

#endif /* DDR_types__InputData_H */
