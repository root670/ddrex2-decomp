typedef struct { char pad[12]; char *course_data_addr; } W;
extern W *shop_get_work(void);
extern void func_0012CF10(void *, int);
void shop_bind_nm(void) {
    unsigned int *p;
    unsigned int *music_addr;
    int ofs;
    int i;
    unsigned int *base_addr;
    W *work = shop_get_work();
    p = (unsigned int *)0xA7D350;
    for (i = 0; i < 0x4C; i++) {
        base_addr = (unsigned int *)0xA7D350;
        ofs = *p++;
        music_addr = (unsigned int *)((int)base_addr + ofs);
        func_0012CF10((char *)music_addr + *music_addr, i + 0xD8);
    }
    for (i = 0; i < 0x1D; i++) {
        ofs = i * 8;
        base_addr = (unsigned int *)work->course_data_addr;
        func_0012CF10((char *)base_addr + *(unsigned int *)((char *)base_addr + ofs), i + 0x124);
    }
}
