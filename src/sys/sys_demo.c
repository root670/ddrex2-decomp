#include "types/_tag_SYS_DEMO_WORK.h"

static void unused_types(unsigned char *(*a)[6], unsigned char (*b)[256]) { (*a)[0] = 0; (*b)[0] = 0; }

struct _tag_SYS_DEMO_WORK *pdemo;

void sysDemoSet(struct _tag_SYS_DEMO_WORK *p) { pdemo = p; }

void sysDemoSetMainLoopBreakRequest(int val) {
    pdemo->main_loop_break_request = val;
}
