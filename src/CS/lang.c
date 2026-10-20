static unsigned char *mesLanguageJAPANESE[6] = { 0 };
static unsigned char *mesLanguageENGLISH[6] = { 0 };
static unsigned char *mesLanguageFRENCH[6] = { 0 };
static unsigned char *mesLanguageGERMAN[6] = { 0 };
static unsigned char *mesLanguageITALIAN[6] = { 0 };
static unsigned char *mesLanguageSPANISH[6] = { 0 };
static unsigned char **mesLanguage[6] = { 0 };
static unsigned char *mesLanguageOK[6] = { 0 };
static unsigned char *mesLanguageCANCEL[6] = { 0 };

unsigned char *mesGetLanguage01(int id0, int id1)
{
    if (id0 >= 7)
        id0 = 2;

    if (id1 >= 7)
        id1 = 2;

    return mesLanguage[id1][id0];
}
