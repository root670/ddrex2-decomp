/* struct _tag_cNetSaveWork -- 5 members, size 0x40, layout 4582460362bb.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x5642).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetSaveWork *`.
 *
 * declared by: onimode.c (DIE 0x5642), dexport.c (DIE 0x3A35F), dinit.c (DIE 0x42BCC), eye_system.c (DIE 0x4DD0B), info_data.c (DIE 0x56F9D), fft_disp.c (DIE 0x62BAD), bk_disp_sub.c (DIE 0xDF909), bk_disp.c (DIE 0xE63C2), fp_msel.c (DIE 0x100545), fp_chara.c (DIE 0x112209), fp_style.c (DIE 0x127B54), fp_res.c (DIE 0x132920), fp_opt.c (DIE 0x1467E3), dmm_data.c (DIE 0x17E038), dmm_disp.c (DIE 0x1860AC), dmm_init.c (DIE 0x191D16), fp_doll.c (DIE 0x1B27FE), fp_msel_obj.c (DIE 0x1D44FE), shop_init.c (DIE 0x213A82), shop_list.c (DIE 0x217410), shop_obj.c (DIE 0x2245C8), shop_disp.c (DIE 0x234605), shop_func.c (DIE 0x23A040), dmm_mc.c (DIE 0x24D6DC), rec_nor.c (DIE 0x256E11), adv_endless_obj.c (DIE 0x282C98), adv_main.c (DIE 0x28FF28), tra_main.c (DIE 0x2B063F), dmm_func.c (DIE 0x2CB0F6), tra_func.c (DIE 0x2D3287), fp_qmenu.c (DIE 0x2FC91D), info.c (DIE 0x334B0F), infoshow.c (DIE 0x346D27), les.c (DIE 0x36EC2F), les_play.c (DIE 0x37832A), net_auth_main.c (DIE 0x3A2F5D), net_cnf_main.c (DIE 0x3B7F1F), dmm_event.c (DIE 0x3C9678), dmm_event_cond.c (DIE 0x3D3CF7), dmm_event_exe.c (DIE 0x3DFAE3), dmm_play_course.c (DIE 0x3FB60D), dmm_qmenu.c (DIE 0x404D00), dmm_result.c (DIE 0x411175), dmm_select.c (DIE 0x41D96C), dmm_style.c (DIE 0x42B774), opt_adjust.c (DIE 0x4305B1), opt_doll.c (DIE 0x43158C), opt_kconfig.c (DIE 0x439DF0), opt_mc.c (DIE 0x4476AA), opt_menu.c (DIE 0x44C9A7), workout_usermanage.c (DIE 0x45913B), rec_hi.c (DIE 0x47D09E), rec_end.c (DIE 0x48527E), rec_hand.c (DIE 0x48A16F)
 */
#ifndef DDR_types__tag_cNetSaveWork_H
#define DDR_types__tag_cNetSaveWork_H

struct _tag_cNetSaveWork {   // size 0x40
    /* 0x000 */ unsigned char last_konami_id[32];     // 0x20
    /* 0x020 */ unsigned char auto_router_support;    // 0x1
    /* 0x021 */ unsigned char auto_router_support_flag;  // 0x1
    /* 0x022 */ unsigned short udp_port;              // 0x2
    /* 0x024 */ char pad[28];                         // 0x1C
};

#endif /* DDR_types__tag_cNetSaveWork_H */
