struct _tag_SYS_SCF_WORK {
    int date_notation;
    int language;
};

int sceScfGetDateNotation(struct _tag_SYS_SCF_WORK *p);

struct _tag_SYS_SCF_WORK *pscf;

void sysInitScf(struct _tag_SYS_SCF_WORK *p) {
    pscf = p; pscf->date_notation = sceScfGetDateNotation(p);

    pscf->language = 1;
}

int sysGetDateNotation(void) {
    return pscf->date_notation;
}
