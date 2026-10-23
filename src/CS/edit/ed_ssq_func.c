#include "types/sq_header.h"
#include "types/sq_indicator.h"
#include "types/sq_standard.h"

typedef struct {
    int beat_count;
    int music_count;
} anon_3_173;

typedef struct {
    int num;
    anon_3_173 val[80];
    float bpm[80];
} anon_2_173;

typedef struct {
    int beat_count;
    int music_count;
    int note_kind;
} anon_4_173;

typedef struct {
    int num;
    anon_4_173 val[8];
} anon_1_173;

typedef struct {
    int *ssq_addr;
    unsigned char *edit_seq_addr;
    unsigned char *edit_freeze_addr;
    anon_2_173 timing;
    anon_1_173 sp_note;
} anon_0_173;

static anon_0_173 ssq_info_work;
static anon_0_173 *p_ssq_info_work = &ssq_info_work;

void func_001B7C30(void *p, int size);

static int calc_ssq_music_count_from_beat_count(int bc);

static void set_ssq_timing_info(void) {
    struct sq_header *header;
    anon_2_173 *timing;
    struct sq_standard *ssq_timing_addr;
    int size;
    int i;
    int num;
    int *bc;
    int *mc;

    header = (struct sq_header *)p_ssq_info_work->ssq_addr;
    timing = &p_ssq_info_work->timing;
    func_001B7C30(timing, sizeof(anon_2_173));
    for (;;) {
        size = header->size;
        if (size == 0) return;
        if (header->kind == 1) { ssq_timing_addr = (struct sq_standard *)header; break; }
        header = (struct sq_header *)((char *)header + size);
    }
    header = (struct sq_header *)ssq_timing_addr;
    num = ssq_timing_addr->num;
    bc = ssq_timing_addr->body;
    mc = bc + num;
    timing->num = num;
    for (i = 0; i < num; i++) {
        timing->val[i].beat_count = bc[i];
        timing->val[i].music_count = mc[i];
    }
    for (i = 0; i < num - 1; i++) {
        timing->bpm[i] = 60.0f * (bc[i + 1] - bc[i]) / (1024.0f * ((mc[i + 1] - mc[i]) / 150.0f));
    }
}

static int calc_ssq_music_count_from_beat_count(int bc) {
    anon_2_173 *timing;
    int note_mc;
    int t_idx0;
    int t_idx1;
    int found;
    int ti;
    int ti_bc;
    int dbc_sp;
    int dbc_t;
    int dmc_t;

    timing = &p_ssq_info_work->timing;
    note_mc = 0;
    t_idx0 = -1;
    t_idx1 = -1;
    found = 0;
    for (ti = 0; ti < timing->num; ti++) {
        ti_bc = timing->val[ti].beat_count;
        if (bc == ti_bc) {
            note_mc = timing->val[ti].music_count;
            found = 1;
            break;
        }
        if (ti_bc < bc) {
            if (t_idx0 == -1 || timing->val[t_idx0].beat_count < ti_bc) t_idx0 = ti;
        } else if (t_idx1 == -1 || ti_bc < timing->val[t_idx1].beat_count) {
            t_idx1 = ti;
        }
    }
    if (found) goto out;
    if (t_idx0 == -1) t_idx0 = 0;
    if (t_idx1 == -1) t_idx1 = 0;
    dbc_sp = (bc - timing->val[t_idx0].beat_count) >> 3;
    dbc_t = (timing->val[t_idx1].beat_count - timing->val[t_idx0].beat_count) >> 3;
    dmc_t = timing->val[t_idx1].music_count - timing->val[t_idx0].music_count;
    if (dbc_t == 0) {
        note_mc = timing->val[t_idx1].music_count;
        goto out;
    }
    note_mc = timing->val[t_idx0].music_count + dbc_sp * dmc_t / dbc_t;
out:
    return note_mc;
}

static void set_ssq_special_note_info(void) {
    struct sq_header *header;
    anon_1_173 *sp_note;
    struct sq_standard *ssq_indicator_addr;
    int size;
    int i;
    int *bc;
    struct sq_indicator *code;
    int num;
    int icode;

    header = (struct sq_header *)p_ssq_info_work->ssq_addr;
    sp_note = &p_ssq_info_work->sp_note;
    func_001B7C30(sp_note, sizeof(anon_1_173));
    for (;;) {
        size = header->size;
        if (size == 0) return;
        if (header->kind == 2) { ssq_indicator_addr = (struct sq_standard *)header; break; }
        header = (struct sq_header *)((char *)header + size);
    }
    header = (struct sq_header *)ssq_indicator_addr;
    bc = ssq_indicator_addr->body;
    code = (struct sq_indicator *)(bc + ssq_indicator_addr->num);
    num = 0;
    {
    int kind_table[6] = {0, -5, -6, -7, -2, -8};
    for (i = 0; i < ssq_indicator_addr->num; i++) {
        icode = code[i].icode;
        if (code[i].class == 2) {
            if (0 < icode && icode < 6) {
                sp_note->val[num].beat_count = bc[i];
                sp_note->val[num].note_kind = kind_table[icode];
                sp_note->val[num].music_count = calc_ssq_music_count_from_beat_count(bc[i]);
                num++;
            }
        }
    }
    sp_note->num = num;
    }
}

void init_ssq_info(void *ssq_addr, unsigned char *edit_seq_addr, unsigned char *edit_freeze_addr) {
    anon_0_173 *work;

    work = p_ssq_info_work;
    work->ssq_addr = ssq_addr;
    work->edit_seq_addr = edit_seq_addr;
    work->edit_freeze_addr = edit_freeze_addr;
    set_ssq_timing_info();
    set_ssq_special_note_info();
}

int get_ssq_special_note_beat_count(int note_kind) {
    anon_1_173 *sp_note;
    int i;

    sp_note = &p_ssq_info_work->sp_note;
    for (i = 0; i < sp_note->num; i++) {
        if (sp_note->val[i].note_kind == note_kind) return sp_note->val[i].beat_count;
    }
    return -1;
}

int get_ssq_special_note_music_count(int note_kind) {
    anon_1_173 *sp_note;
    int i;

    sp_note = &p_ssq_info_work->sp_note;
    for (i = 0; i < sp_note->num; i++) {
        if (sp_note->val[i].note_kind == note_kind) return sp_note->val[i].music_count;
    }
    return -1;
}

unsigned char *get_ssq_edit_seq_addr(void) {
    return p_ssq_info_work->edit_seq_addr;
}

unsigned char *get_ssq_edit_freeze_addr(void) {
    return p_ssq_info_work->edit_freeze_addr;
}

int get_ssq_timing_num(void) {
    return p_ssq_info_work->timing.num;
}

int get_ssq_timing_beat_count(int index) {
    return p_ssq_info_work->timing.val[index].beat_count;
}

int get_ssq_timing_music_count(int index) {
    return p_ssq_info_work->timing.val[index].music_count;
}
