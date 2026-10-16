/* struct _DDRCommonHeader -- 8 members, size 0x10, layout 49f633cb3eda.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x5316).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _DDRCommonHeader *`.
 *
 * declared by: onimode.c (DIE 0x5316), dexport.c (DIE 0x3826C), dinit.c (DIE 0x426A3), eye_system.c (DIE 0x4C5C9), info_data.c (DIE 0x57834), fft_disp.c (DIE 0x620B3), bk_disp_sub.c (DIE 0xDDC1A), bk_disp.c (DIE 0xEBF82), fp_msel.c (DIE 0x102AD7), fp_chara.c (DIE 0x11000C), fp_style.c (DIE 0x1259F2), fp_res.c (DIE 0x1302E6), fp_opt.c (DIE 0x144851), dmm_data.c (DIE 0x17DC2C), dmm_disp.c (DIE 0x185B7F), dmm_init.c (DIE 0x18FF6B), fp_doll.c (DIE 0x1B070C), fp_msel_obj.c (DIE 0x1D341B), shop_init.c (DIE 0x211D67), shop_list.c (DIE 0x216F88), shop_obj.c (DIE 0x2223C2), shop_disp.c (DIE 0x2323FF), shop_func.c (DIE 0x239D5C), dmm_mc.c (DIE 0x24B5DB), rec_nor.c (DIE 0x25A4A9), adv_endless_obj.c (DIE 0x28100A), adv_main.c (DIE 0x28DA85), tra_main.c (DIE 0x2AD170), dmm_func.c (DIE 0x2C8E60), tra_func.c (DIE 0x2D92C6), fp_qmenu.c (DIE 0x2FC615), info.c (DIE 0x335208), infoshow.c (DIE 0x343B9C), les.c (DIE 0x36C358), les_play.c (DIE 0x37377F), net_auth_main.c (DIE 0x3A38A8), net_cnf_main.c (DIE 0x3B8170), dmm_event.c (DIE 0x3C9304), dmm_event_cond.c (DIE 0x3D22FD), dmm_event_exe.c (DIE 0x3DE153), dmm_play_course.c (DIE 0x3F9C57), dmm_qmenu.c (DIE 0x402BFF), dmm_result.c (DIE 0x40F30C), dmm_select.c (DIE 0x41C149), dmm_style.c (DIE 0x429858), opt_adjust.c (DIE 0x42FFFA), opt_doll.c (DIE 0x43493B), opt_kconfig.c (DIE 0x4394EF), opt_mc.c (DIE 0x44723F), opt_menu.c (DIE 0x44C4A7), workout_usermanage.c (DIE 0x458F14), rec_hi.c (DIE 0x480F70), rec_end.c (DIE 0x488DA1), rec_hand.c (DIE 0x48E0EB)
 */
#ifndef DDR_types__DDRCommonHeader_H
#define DDR_types__DDRCommonHeader_H

struct _DDRCommonHeader {   // size 0x10
    /* 0x000 */ unsigned char Type;                   // 0x1
    /* 0x001 */ unsigned char Platform;               // 0x1
    /* 0x002 */ unsigned char Hardware;               // 0x1
    /* 0x003 */ unsigned char Version;                // 0x1
    /* 0x004 */ unsigned char Area;                   // 0x1
    /* 0x005 */ signed char tmp;                      // 0x1
    /* 0x006 */ unsigned short title;                 // 0x2
    /* 0x008 */ unsigned int t_info[2];               // 0x8
};

#endif /* DDR_types__DDRCommonHeader_H */
