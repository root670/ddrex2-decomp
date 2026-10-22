#include "types/_tag_cDDR8SaveData.h"
#include "types/music_info.h"
#include "types/oni_course.h"

int tblInfoOrder[29] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28,
};
int tblInfoOrder_for_music[76] = {
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
    75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
    98, 99, 100, 101, 102, 103, 104,
};
int tblInfoOrder_for_course[26] = {
    105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,
    123, 124, 125, 126, 127, 128, 129, 130,
};
static unsigned short link_num_dt[75] = {
    472, 33024, 267, 372, 266, 482, 33553, 445, 33554, 117, 11, 374, 184, 384, 112, 32768, 365,
    120, 434, 452, 33567, 459, 265, 126, 377, 33551, 33555, 463, 477, 32769, 33562, 175, 33035,
    33671, 33037, 33670, 433, 33038, 479, 431, 438, 368, 24579, 416, 33569, 33665, 33666, 33667,
    446, 33557, 392, 27, 430, 464, 33672, 33565, 33664, 33564, 33048, 475, 33049, 24582, 33669,
    222, 380, 33558, 435, 33563, 346, 469, 33668, 473, 28717, 33552, 33673,
};
int tblDancerByInfotext[45] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
};
struct _tag_cDDR8SaveData SaveData;

struct music_info *func_00160D50(unsigned short num);
int func_00160DE0(short num);
int func_00162780(void);
void func_00172330(int num);

int GetInfoOrderNum(void) {
    return 29;
}

int GetInfoOrderNum_for_music(void) {
    return 76;
}

int GetInfoOrderNum_for_course(void) {
    return 26;
}

struct music_info *get_minfo_by_infotxt_num(int infotxt_num) {
    int index;

    if (infotxt_num >= 29 && infotxt_num < 104) {
        index = infotxt_num - 29;
        if (index < 0 || index >= sizeof(link_num_dt) / sizeof(link_num_dt[0]))
            return 0;
        return func_00160D50(link_num_dt[index]);
    }
    return 0;
}

int get_infotxt_num_by_mip(struct music_info *mip) {
    int i;

    if (mip == 0)
        return -1;
    for (i = 0; i < sizeof(link_num_dt) / sizeof(link_num_dt[0]); i++)
        if (link_num_dt[i] == mip->verm_num)
            return i + 29;
    return -1;
}

int get_table_no_by_infotxt_num(int infotxt_num) {
    struct music_info *mip;
    int index;

    if (infotxt_num >= 29 && infotxt_num < 104) {
        index = infotxt_num - 29;
        if (index < 0 || (unsigned)index >= sizeof(link_num_dt) / sizeof(link_num_dt[0]))
            mip = 0;
        else
            mip = func_00160D50(link_num_dt[index]);
    } else {
        mip = 0;
    }
    if (mip == 0)
        return -1;
    return func_00160DE0(mip->dance_num);
}

int get_course_id_by_infotxt_num(int num) {
    int ret;

    ret = -1;
    if (num >= 105 && num < 130)
        ret = num - 105;
    return ret;
}

int get_dancer_id_by_infotext_num(int num) {
    if (num >= 202 && num < 220)
        return tblDancerByInfotext[(int)(num - 202)];
    return -1;
}

void ReleaseInformation_AllSongsUnlocked(void) {
    int val;

    val = func_00162780();
    if (val == 1)
        func_00172330(0xDD);
}
