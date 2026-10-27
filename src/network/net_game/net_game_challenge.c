#include "src/network/net_game/net_game_challenge.h"
#include "types/_CWS_WIN_W.h"

struct oni_course *onimode_get_course_list(int id);
struct music_info *func_00161E00(int id);
struct _tag_cMusicData *GetMusicData_by_link_num(unsigned short link_num);
char CwsWinSetCode(struct _CWS_WIN_W *work, char _code);
int CwsWinsAllGetStatus(int flag);
void CwsWinsDelete(void);
int co_movie_stop(void);
void co_caption_disap(void);
void NetWin_AnySetTexture(struct _CWS_WIN_W *win, int _tex_id, int _tu, int _tv,
                          int _tw, int _th);
int NetPrgGetRCEntry(int err_mode, unsigned char type);
int NetPrgGetRCRegist(int err_mode, int score, int time, short combo, short gauge);
int InitNetRankPlay(struct _NETWORK_W *netw);
int npGetBeforeSyncFlag(void);
int npGetAfterSyncFlag(void);
int npGetAfterSyncState(void);
int MainNetRankPlay(void);
int TermNetRankPlay(void);
void *ps2dancerInit(void *workaddr, int playmode);
void func_0011EEC0(void *addr, int size);
int func_00120250(int mode);
void func_00128600(void);
void func_00125290(int flag);

void NetGameChallengeInit(struct _NETWORK_W *netw) {
    int i;
    int rec;

    switch (netw->step) {
    case 0:
        rec = NetPrgGetRCEntry(0, *(unsigned char *)0x102FE44);
        if (rec == 1)
            netw->step++;
        else if (rec < 0)
            netw->NewFunc = NetGameRCInit2;
        break;
    case 1:
        NetWin_AnySetTexture(*(struct _CWS_WIN_W **)0x102FC08, 0x23, 0, 0, 0x280, 0x1A8);
        for (i = 2; i < 0x51; i++) {
            ((struct _CWS_WIN_W **)0x102FAC4)[i]->mode = 0;
            CwsWinSetCode(((struct _CWS_WIN_W **)0x102FAC4)[i], 2);
        }
        co_caption_disap();
        (*(struct _CWS_WIN_W **)0x102FC08)->mode = 0;
        CwsWinSetCode(*(struct _CWS_WIN_W **)0x102FC08, 1);
        netw->NewFunc = NetGameChallengeMain;
        break;
    }
}

static void NetGameChallengeMain(struct _NETWORK_W *netw) {
    int no_clear_flag;
    int rec;
    struct eval_w *src_eva;

    no_clear_flag = 0;
    switch (netw->step) {
    case 0:
        if (CwsWinsAllGetStatus(0) != 0) {
            co_movie_stop();
            no_clear_flag = 1;
            netw->step++;
        }
        break;
    case 1:
        netw->SubFunc = 0;
        CwsWinsDelete();
        func_00128600();
        *(int *)0x102FFCC = 0;
        func_0011EEC0((void *)0x102FFD0, 0x18);
        no_clear_flag = 1;
        netw->step++;
        break;
    case 2:
        netw->step = netw->step + 1;
        no_clear_flag = 1;
        break;
    case 3:
        if (func_00120250(2) == 1)
            netw->step++;
        no_clear_flag = 1;
        break;
    case 4:
        NetGameChallengeCourseConvert(netw->dur_rc_data);
        netw->step++;
        no_clear_flag = 1;
        break;
    case 5:
        ps2dancerInit((void *)0x18FB800, 0);
        if (InitNetRankPlay(netw) == 1)
            netw->step++;
        no_clear_flag = 1;
        break;
    case 6:
        if (npGetBeforeSyncFlag() != 1) {
            if (npGetAfterSyncFlag() == 0)
                g_game_w.network_flag &= ~8;
            else
                npGetAfterSyncState();
        }
        if (MainNetRankPlay() == 1)
            netw->step++;
        break;
    case 7:
        src_eva = &g_game_w.player[0].stage_evaluation;
        rec = NetPrgGetRCRegist(0, src_eva->score, g_game_w.player[0].game_time,
                                src_eva->max_combo_ct, g_game_w.player[0].cur_life);
        if (rec == 1)
            netw->step++;
        else if (rec < 0)
            netw->NewFunc = NetGameRCInit2;
        break;
    case 8:
        if (TermNetRankPlay() == 1)
            netw->step++;
        break;
    case 9:
        netw->step = netw->step + 1;
        break;
    case 10:
        netw->NewFunc = NetToGameInit;
        break;
    }
    if (no_clear_flag == 1)
        func_00125290(1);
}

static int NetGameChallengeCourseConvert(struct _nsv_rc_table_param_work *net_course_data) {
    struct oni_course *local_course_data;
    struct music_info *mip;
    struct _tag_cMusicData *mdata;
    struct _nsv_music_data_work *mdata_w;
    struct oni_mode *song_list;
    int i;
    int stage_num;

    stage_num = 0;
    local_course_data = onimode_get_course_list(6);
    for (i = 0; i < 10; i++) {
        mdata_w = &net_course_data->music_data[i];
        song_list = &local_course_data->mode[i];
        if (mdata_w->music_id == -1)
            break;
        mip = func_00161E00(mdata_w->music_id + 1);
        if (mip == 0)
            break;
        mdata = GetMusicData_by_link_num(mip->verm_num);
        if (mdata == 0)
            break;
        song_list->link_num = mip->verm_num;
        song_list->speed = mdata_w->speed;
        song_list->boost = mdata_w->boost;
        song_list->hidden = mdata_w->appearance;
        song_list->turn = mdata_w->turn;
        song_list->seq_transfer = mdata_w->turn;
        song_list->thinout = mdata_w->little;
        song_list->dark = mdata_w->dark;
        song_list->simultaneous = mdata_w->simultaneous;
        song_list->scroll = mdata_w->scroll;
        song_list->freeze = mdata_w->freeze_arrow;
        switch (mdata_w->difficult) {
        case 0:
            song_list->seq_kind = 1;
            break;
        case 1:
            song_list->seq_kind = 2;
            break;
        case 2:
            song_list->seq_kind = 3;
            break;
        case 4:
            song_list->seq_kind = 6;
            break;
        default:
            song_list->seq_kind = 1;
            break;
        }
        stage_num++;
    }
    local_course_data->course_allnum = stage_num;
    local_course_data->course_defnum = stage_num;
    local_course_data->stage = stage_num;
    if (stage_num <= 0)
        return -1;
    return stage_num;
}
