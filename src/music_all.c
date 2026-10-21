#include "types/_tag_cMusicData.h"

static struct _tag_cMusicData tblMusicData[674] = { 0 };

int func_001BED10(unsigned char *a, unsigned char *b);

struct _tag_cMusicData *GetMusicData_by_link_num(unsigned short link_num)
{
    struct _tag_cMusicData *ret = 0;
    int i;

    for (i = 0; i < sizeof(tblMusicData) / sizeof(tblMusicData[0]); i++) {
        if (tblMusicData[i].base_name != 0)
            if (tblMusicData[i].link_num == link_num) {
                ret = &tblMusicData[i];
                break;
            }
    }
    return ret;
}

struct _tag_cMusicData *GetMusicData_by_index(int id)
{
    struct _tag_cMusicData *ret;
    ret = 0;
    if ((unsigned int)id < 674) {
        ret = &tblMusicData[id];
    }
    return ret;
}

struct _tag_cMusicData *GetMusicData_by_base_name(unsigned char *base_name)
{
    struct _tag_cMusicData *ret = 0;
    int i;

    for (i = 0; i < sizeof(tblMusicData) / sizeof(tblMusicData[0]); i++) {
        if (tblMusicData[i].base_name != 0)
            if (func_001BED10(tblMusicData[i].base_name, base_name) == 0) {
                ret = &tblMusicData[i];
                break;
            }
    }
    return ret;
}
