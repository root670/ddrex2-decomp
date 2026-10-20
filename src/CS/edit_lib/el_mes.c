#include "src/CS/edit_lib/el_mes.h"

int func_00192F30(int a, int b);

unsigned char *el_get_message_str(int kind, int sub_id)
{
    int id = func_00192F30(sub_id, kind);
    return el_message_str_e[id];
}
