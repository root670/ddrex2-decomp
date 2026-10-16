/*
 * C:\work2\usaex2\src\sound\fft\sd_fft.c
 * MW MIPS C Compiler, overlay main; 17 functions, code 0x001D08B0-0x001D2180
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_sound_fft_sd_fft_c_H
#define DDR_UNIT_src_sound_fft_sd_fft_c_H

/* anonymous types (2) */

/* anon_0_31 -- @anon0, 0x4C60 bytes, sd_fft.c (DIE 0x45D50) */
struct anon_0_31 {   // size 0x4C60
    /* 0x000 */ int sdwork[256];                      // 0x400
    /* 0x400 */ float window_table[512];              // 0x800
    /* 0xC00 */ float sdtable[1024];                  // 0x1000
    /* 0x1C00 */ float buff_right[1026];              // 0x1008
    /* 0x2C08 */ float buff_left[1026];               // 0x1008
    /* 0x3C10 */ short pcmdata_right[532];            // 0x428
    /* 0x4038 */ short pcmdata_left[532];             // 0x428
    /* 0x4460 */ float fftdata_right[256];            // 0x400
    /* 0x4860 */ float fftdata_left[256];             // 0x400
};

/* anon_1_31 -- @anon1, 0xC bytes, sd_fft.c (DIE 0x45F2C) */
struct anon_1_31 {   // size 0xC
    /* 0x000 */ struct anon_0_31 *fft_ope_work;       // 0x4
    /* 0x004 */ int set_flg;                          // 0x4
    /* 0x008 */ int use_flg;                          // 0x4
};


/* variables (2) */
struct anon_1_31 *p_fft_work;                                    /* @0x002DD9A4 size 0x4 */
static struct anon_1_31 fft_work;                                /* @0x007126D0 size 0xC */

/* functions defined (17) */
static void SdMakewt(int nw, int *p_work, float *p_table);       /* 0x001D08B0-0x001D09EC lines 798-823 */
static void SdBitrv2conj(int n, int *p_work, float *data);       /* 0x001D09F0-0x001D0EBC lines 684-795 */
static void SdBitrv2(int n, int *p_work, float *data);           /* 0x001D0EC0-0x001D12E8 lines 584-680 */
static void SdCftmdl(int n, int l, float *data, float *w);       /* 0x001D12F0-0x001D1758 lines 458-581 */
static void SdCft1st(int n, float *data, float *p_table);        /* 0x001D1760-0x001D1A78 lines 353-454 */
static void SdCftbsub(int n, float *data, float *p_table);       /* 0x001D1A80-0x001D1C34 lines 305-351 */
void SdFFTCore(void);                                            /* 0x001D1C40-0x001D2024 lines 159-227 */
int SdFFTInit(struct anon_0_31 *addr);                           /* 0x001D2030-0x001D20EC lines 130-150 */
int SdGetFFTStart(void);                                         /* 0x001D20F0-0x001D20FC lines 122-123 */
void SdSetFFTEnd(void);                                          /* 0x001D2100-0x001D210C lines 115-116 */
void SdSetFFTStart(void);                                        /* 0x001D2110-0x001D2120 lines 109-110 */
void SdSetFFTSet(int flg);                                       /* 0x001D2120-0x001D212C lines 102-103 */
int SdGetFFTSet(void);                                           /* 0x001D2130-0x001D213C lines 94-95 */
float *SdGetFFTWorkL(void);                                      /* 0x001D2140-0x001D2150 lines 86-87 */
float *SdGetFFTWorkR(void);                                      /* 0x001D2150-0x001D2160 lines 79-80 */
short *SdGetDecodeWorkL(void);                                   /* 0x001D2160-0x001D2170 lines 72-73 */
short *SdGetDecodeWorkR(void);                                   /* 0x001D2170-0x001D2180 lines 65-66 */

#endif /* DDR_UNIT_src_sound_fft_sd_fft_c_H */
