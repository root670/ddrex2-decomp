/*
 * Emotion Engine DMA controller registers, channel 2.
 *
 * A register is an lvalue, so a unit writes `D2_TADR = x;` instead of a cast at the call
 * site.  The macro deliberately keeps the `*(volatile unsigned int *)ADDR` shape: spelling
 * the channel as a struct and reaching `->tadr` makes the compiler emit `lui`/`addiu` for
 * the channel base plus an offset, which is a different instruction than the matched unit's
 * `lui`/`addiu` for the register address.  These units are matched byte for byte, so the
 * spelling is part of the evidence.
 *
 * EE DMAC channel bases: D0 0x10008000, D1 0x10009000, D2 0x1000A000, D3 0x1000B000; within
 * a channel CHCR +0x00, MADR +0x10, QWC +0x20, TADR +0x30, ASR0 +0x40, ASR1 +0x50, SADR
 * +0x80.  Only the registers a matched unit actually touches are named here; add another the
 * same way when a unit needs it rather than defining the whole map speculatively.
 */
#ifndef DDR_HW_EE_DMA_H
#define DDR_HW_EE_DMA_H

#define D2_CHCR (*(volatile unsigned int *)0x1000A000u)
#define D2_QWC (*(volatile unsigned int *)0x1000A020u)
#define D2_TADR (*(volatile unsigned int *)0x1000A030u)

#endif /* DDR_HW_EE_DMA_H */
