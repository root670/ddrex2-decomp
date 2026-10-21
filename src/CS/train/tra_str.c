typedef struct {
    unsigned char **array;
    int num;
} anon_0_158;

static unsigned char *tr_str_play[3] = { 0 };
static unsigned char *tr_str_step[6] = { 0 };
static unsigned char *tr_str_offon[2] = { 0 };
static unsigned char *tr_str_mspeed[5] = { 0 };
static unsigned char *tr_str_op_speed[6] = { 0 };
static unsigned char *tr_str_op_appear[4] = { 0 };
static unsigned char *tr_str_op_turn[5] = { 0 };
static unsigned char *tr_str_op_simu[3] = { 0 };
static unsigned char *tr_str_op_scroll[2] = { 0 };
static unsigned char *tr_str_op_freeze[2] = { 0 };
static unsigned char *tr_str_rs_menu[4] = { 0 };
static unsigned char *tr_str_ck_menu[3] = { 0 };
static unsigned char *tr_str_ck_mode[2] = { 0 };
static anon_0_158 tr_str_tbl[15] = { 0 };

unsigned char *Tr_get_str(int kind, int index)
{
    if ((unsigned)kind >= 0xF) {
        return 0;
    }

    if (index >= tr_str_tbl[kind].num)
        return 0;

    return tr_str_tbl[kind].array[index];
}

unsigned char Tr_get_lr_item_max(int kind)
{
    if ((unsigned)kind >= 0xF) return 0;

    return tr_str_tbl[kind].num;
}

void Tr_bar_digit_disp(float cx, float y0, unsigned char num, int pri)
{
    unsigned char num_str[4];

    if (num < 10) {
        num_str[0] = num % 10 + 0x30;
        num_str[1] = 0;
    } else if (num < 100) {
        num_str[0] = num / 10 + 0x30;
        num_str[1] = num % 10 + 0x30;
        num_str[2] = 0;
    } else {
        num_str[0] = num / 100 + 0x30;
        num_str[1] = num % 100 / 10 + 0x30;
        num_str[2] = num % 10 + 0x30;
        num_str[3] = 0;
    }

    CSXX20Puts((int)cx, (int)y0, num_str, 0x80, pri, 0, 0x80, 0xFB, 0x1750);
}
