#include "src/CS/shop/shop_list.h"

struct music_info *func_00160DB0(int id);
struct oni_course *onimode_get_course_list(int id);

void shop_make_contents_list(anon_1_123 *work) {
    work->secret_list_num = 0;

    switch (work->tab_cursor) {
    case 0:
        shop_make_contents_list_music(work);
        break;

    case 1:
        shop_make_contents_list_course(work);
        break;

    case 2:
        shop_make_contents_list_outfit(work);
        break;

    case 3:
        shop_make_contents_list_info(work);
        break;

    case 4:
        shop_make_contents_list_custom(work);
        break;

    case 5:
        shop_make_contents_list_other(work);
        break;
    }
}

static void shop_make_contents_list_music(anon_1_123 *work) {
    struct music_info *minfo;
    anon_4_123 *secw;
    int i;
    int j;

    for (i = 1; i < 0x33; i++) {
        for (j = 0; j < 0x4C; j++) {
            minfo = func_00160DB0(j);

            if (minfo->hide == i
                && (SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
                secw = &work->secret_list[work->secret_list_num];
                secw->secret_no = i;
                secw->value = minfo->dance_num - 1;
                work->secret_list_num++;
            }
        }
    }

    for (i = 1; i < 0x33; i++) {
        for (j = 0; j < 0x4C; j++) {
            minfo = func_00160DB0(j);

            if (minfo->hide == i
                && (SaveData.HideAppFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
                && !(SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
                && !(SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
                secw = &work->secret_list[work->secret_list_num];
                secw->secret_no = i;
                secw->value = minfo->dance_num - 1;
                work->secret_list_num++;
            }
        }
    }

    for (i = 1; i < 0x33; i++) {
        for (j = 0; j < 0x4C; j++) {
            minfo = func_00160DB0(j);

            if (minfo->hide == i
                && (SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
                secw = &work->secret_list[work->secret_list_num];
                secw->secret_no = i;
                secw->value = minfo->dance_num - 1;
                work->secret_list_num++;
            }
        }
    }
}

static void shop_make_contents_list_course(anon_1_123 *work) {
    struct oni_course *cow;
    anon_4_123 *secw;
    int i;
    int j;

    for (i = 0x33; i < 0x47; i++) {
        for (j = 0; j <= 0x1C; j++) {
            cow = onimode_get_course_list(j + 1);

            if (cow->avairable_level == i
                && (SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
                secw = &work->secret_list[work->secret_list_num];
                secw->secret_no = i;
                secw->value = j;
                work->secret_list_num++;
            }
        }
    }

    for (i = 0x33; i < 0x47; i++) {
        for (j = 0; j <= 0x1C; j++) {
            cow = onimode_get_course_list(j + 1);

            if (cow->avairable_level == i
                && (SaveData.HideAppFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
                && !(SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
                && !(SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
                secw = &work->secret_list[work->secret_list_num];
                secw->secret_no = i;
                secw->value = j;
                work->secret_list_num++;
            }
        }
    }

    for (i = 0x33; i < 0x47; i++) {
        for (j = 0; j <= 0x1C; j++) {
            cow = onimode_get_course_list(j + 1);

            if (cow->avairable_level == i
                && (SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
                secw = &work->secret_list[work->secret_list_num];
                secw->secret_no = i;
                secw->value = j;
                work->secret_list_num++;
            }
        }
    }
}

static void shop_make_contents_list_outfit(anon_1_123 *work) {
    anon_4_123 *secw;
    int i;
    int chara_no;

    for (i = 0x48, chara_no = 1; i < 0x73; i += 2, chara_no += 2) {
        if (SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            secw->value = chara_no;
            work->secret_list_num++;
        }
    }

    for (i = 0x48, chara_no = 1; i < 0x73; i += 2, chara_no += 2) {
        if ((SaveData.HideAppFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            secw->value = chara_no;
            work->secret_list_num++;
        }
    }

    for (i = 0x48, chara_no = 1; i < 0x73; i += 2, chara_no += 2) {
        if (SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            secw->value = chara_no;
            work->secret_list_num++;
        }
    }
}

static void shop_make_contents_list_info(anon_1_123 *work) {
    anon_4_123 *secw;
    int i;

    for (i = 0x73; i < 0x96; i++) {
        if (SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            if (i < 0x78)
                secw->value = i - 0x73;
            else
                secw->value = i - 0x78;
            work->secret_list_num++;
        }
    }

    for (i = 0x73; i < 0x96; i++) {
        if ((SaveData.HideAppFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            if (i < 0x78)
                secw->value = i - 0x73;
            else
                secw->value = i - 0x78;
            work->secret_list_num++;
        }
    }

    for (i = 0x73; i < 0x96; i++) {
        if (SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            if (i < 0x78)
                secw->value = i - 0x73;
            else
                secw->value = i - 0x78;
            work->secret_list_num++;
        }
    }
}

static void shop_make_contents_list_custom(anon_1_123 *work) {
    anon_4_123 *secw;
    int i;

    for (i = 0xBA; i < 0xBE; i++) {
        if (SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))
            && i != SaveData.ArrowType + 0xBA) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            secw->value = i - 0xBA;
            work->secret_list_num++;
        }
    }

    for (i = 0xBA; i < 0xBE; i++) {
        if ((SaveData.HideAppFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && i != SaveData.ArrowType + 0xBA) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            secw->value = i - 0xBA;
            work->secret_list_num++;
        }
    }

    for (i = 0xBA; i < 0xBE; i++) {
        if (SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))
            && i != SaveData.ArrowType + 0xBA) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            secw->value = i - 0xBA;
            work->secret_list_num++;
        }
    }
}

static void shop_make_contents_list_other(anon_1_123 *work) {
    anon_4_123 *secw;
    int i;

    for (i = 0xB4; i < 0xBA; i++) {
        if (SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            if (i < 0xB7)
                secw->value = i - 0xB4;
            else
                secw->value = i - 0xB7;
            work->secret_list_num++;
        }
    }

    for (i = 0xB4; i < 0xBA; i++) {
        if ((SaveData.HideAppFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideAppNewFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))
            && !(SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31)))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            if (i < 0xB7)
                secw->value = i - 0xB4;
            else
                secw->value = i - 0xB7;
            work->secret_list_num++;
        }
    }

    for (i = 0xB4; i < 0xBA; i++) {
        if (SaveData.HideFlag[(i - 1) >> 5] & (1 << ((i - 1) & 31))) {
            secw = &work->secret_list[work->secret_list_num];
            secw->secret_no = i;
            if (i < 0xB7)
                secw->value = i - 0xB4;
            else
                secw->value = i - 0xB7;
            work->secret_list_num++;
        }
    }
}
