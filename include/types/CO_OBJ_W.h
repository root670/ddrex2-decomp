/* struct CO_OBJ_W -- 8 members, size 0x280, layout 0dd90dd6653b.
 *
 * One definition, agreed by the 4 units that declare it: workout.c (DIE 0xAD179).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct CO_OBJ_W *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: workout.c (DIE 0xAD179), co_obj.c (DIE 0x1B9493), info.c (DIE 0x334039), opt_main.c (DIE 0x44216F)
 */
#ifndef DDR_types_CO_OBJ_W_H
#define DDR_types_CO_OBJ_W_H

struct CO_OBJ_W {   // size 0x280
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char disp_flag;              // 0x1
    /* 0x002 */ unsigned char pri;                    // 0x1
    /* 0x003 */ unsigned char ini_flag;               // 0x1
    /* 0x004 */ unsigned char work[624];              // 0x270
    /* 0x274 */ struct CO_OBJ_W *next;                // 0x4
    /* 0x278 */ struct {   // size 0x10
        /* 0x000 */ int (*appr)(void *);                  // 0x4
        /* 0x004 */ int (*exec)(void *);                  // 0x4
        /* 0x008 */ int (*disap)(void *);                 // 0x4
        /* 0x00C */ int (*disp)(void *);                  // 0x4
    } *f;
    /* 0x27C */ unsigned int id;                      // 0x4
};

#endif /* DDR_types_CO_OBJ_W_H */
