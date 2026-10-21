typedef struct {
    unsigned char **array;
    int num;
} anon_0_158;

static unsigned char *tr_str_play[3] = { (unsigned char *)"SINGLE", (unsigned char *)"VERSUS", (unsigned char *)"DOUBLE" };
static unsigned char *tr_str_step[6] = { (unsigned char *)"BEGINNER", (unsigned char *)"LIGHT", (unsigned char *)"STANDARD", (unsigned char *)"HEAVY", (unsigned char *)"CHALLENGE", (unsigned char *)"EDIT" };
static unsigned char *tr_str_offon[2] = { (unsigned char *)"OFF", (unsigned char *)"ON" };
static unsigned char *tr_str_mspeed[5] = { (unsigned char *)"1", (unsigned char *)"2", (unsigned char *)"3", (unsigned char *)"4", (unsigned char *)"5" };
static unsigned char *tr_str_op_speed[6] = { (unsigned char *)"x1", (unsigned char *)"x1.5", (unsigned char *)"x2", (unsigned char *)"x3", (unsigned char *)"x5", (unsigned char *)"x8" };
static unsigned char *tr_str_op_appear[4] = { (unsigned char *)"VISIBLE", (unsigned char *)"HIDDEN", (unsigned char *)"SUDDEN", (unsigned char *)"STEALTH" };
static unsigned char *tr_str_op_turn[5] = { (unsigned char *)"OFF", (unsigned char *)"MIRROR", (unsigned char *)"LEFT", (unsigned char *)"RIGHT", (unsigned char *)"SHUFFLE" };
static unsigned char *tr_str_op_simu[3] = { (unsigned char *)"ON", (unsigned char *)"OFF1", (unsigned char *)"OFF2" };
static unsigned char *tr_str_op_scroll[2] = { (unsigned char *)"STANDARD", (unsigned char *)"REVERSE" };
static unsigned char *tr_str_op_freeze[2] = { (unsigned char *)"ON", (unsigned char *)"OFF" };
static unsigned char *tr_str_rs_menu[4] = { (unsigned char *)"AGAIN", (unsigned char *)"CHECK", (unsigned char *)"MENU", (unsigned char *)"CANCEL" };
static unsigned char *tr_str_ck_menu[3] = { (unsigned char *)"MENU", (unsigned char *)"BACK", (unsigned char *)"CANCEL" };
static unsigned char *tr_str_ck_mode[2] = { (unsigned char *)"Judgement Color", (unsigned char *)"Timing Color" };
static anon_0_158 tr_str_tbl[15] = { { .array = tr_str_play, .num = 3 }, { .array = tr_str_step, .num = 6 }, { .array = tr_str_mspeed, .num = 5 }, { .array = tr_str_op_speed, .num = 6 }, { .array = tr_str_offon, .num = 2 }, { .array = tr_str_op_appear, .num = 4 }, { .array = tr_str_op_turn, .num = 5 }, { .array = tr_str_offon, .num = 2 }, { .array = tr_str_offon, .num = 2 }, { .array = tr_str_op_simu, .num = 3 }, { .array = tr_str_op_scroll, .num = 2 }, { .array = tr_str_op_freeze, .num = 2 }, { .array = tr_str_rs_menu, .num = 4 }, { .array = tr_str_ck_menu, .num = 3 }, { .array = tr_str_ck_mode, .num = 2 } };

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
