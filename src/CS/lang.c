static unsigned char *mesLanguageJAPANESE[6] = { (unsigned char *)"NIHON-GO", (unsigned char *)"JAPANESE", (unsigned char *)"JAPANESE", (unsigned char *)"JAPANESE", (unsigned char *)"JAPANESE", (unsigned char *)"JAPANESE" };
static unsigned char *mesLanguageENGLISH[6] = { (unsigned char *)"EI-GO", (unsigned char *)"ENGLISH", (unsigned char *)"ANGLAIS", (unsigned char *)"ENGLISCH", (unsigned char *)"INGLESE", (unsigned char *)"INGL\311S" };
static unsigned char *mesLanguageFRENCH[6] = { (unsigned char *)"FURANSU-GO", (unsigned char *)"FRENCH", (unsigned char *)"FRANCAIS", (unsigned char *)"FRANZ\326SISCH", (unsigned char *)"FRANCESE", (unsigned char *)"FRANC\311S" };
static unsigned char *mesLanguageGERMAN[6] = { (unsigned char *)"DOITSU-GO", (unsigned char *)"GERMAN", (unsigned char *)"ALLEMAND", (unsigned char *)"DEUTSCH", (unsigned char *)"TEDESCO", (unsigned char *)"ALEM\301N" };
static unsigned char *mesLanguageITALIAN[6] = { (unsigned char *)"ITARIA-GO", (unsigned char *)"ITALIAN", (unsigned char *)"ITALIEN", (unsigned char *)"ITALIENISCH", (unsigned char *)"ITALIANO", (unsigned char *)"ITALIANO" };
static unsigned char *mesLanguageSPANISH[6] = { (unsigned char *)"SUPEIN-GO", (unsigned char *)"SPANISH", (unsigned char *)"ESPAGNOL", (unsigned char *)"SPANISCH", (unsigned char *)"SPAGNOLO", (unsigned char *)"ESPA\321OL" };
static unsigned char **mesLanguage[6] = { mesLanguageJAPANESE, mesLanguageENGLISH, mesLanguageFRENCH, mesLanguageGERMAN, mesLanguageITALIAN, mesLanguageSPANISH };
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
