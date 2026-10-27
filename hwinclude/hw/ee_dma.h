/*
 * Emotion Engine DMA controller registers.
 *
 * A register is an lvalue, so a unit writes `D2_TADR = x;` instead of a cast at the call
 * site.  The macro deliberately keeps the `*(volatile unsigned int *)ADDR` shape: spelling
 * the channel as a struct and reaching `->tadr` makes the compiler emit `lui`/`addiu` for
 * the channel base plus an offset, which is a different instruction than the matched unit's
 * `lui`/`addiu` for the register address.  These units are matched byte for byte, so the
 * spelling is part of the evidence.
 *
 * EE DMAC channel bases: D0 0x10008000 (VIF0), D1 0x10009000 (VIF1), D2 0x1000A000 (GIF),
 * D3 0x1000B000 (IPU); within a channel CHCR +0x00, MADR +0x10, QWC +0x20, TADR +0x30,
 * ASR0 +0x40, ASR1 +0x50, SADR +0x80.  The controller's own registers sit at 0x1000E000,
 * one per 0x10: D_CTRL, D_STAT, D_PCR, D_SQWC, D_RBSR, D_RBOR, D_STADR.
 *
 * These are documented hardware facts, not game symbols: a name here comes from the
 * register map, so it does not need DWARF or ghidra_functions.json evidence (AGENTS.md
 * rule 3 is about game names).  A register the tree needs and this header lacks is added
 * here, as an lvalue macro in the same shape, rather than cast at the use site.
 *
 * What this header deliberately does not name: an absolute address in the EE's *main RAM*
 * is game state, not hardware, and is only named when a DWARF member or a splat `D_XXXXXXXX`
 * covers it.  The freeplay singletons at 0x006D2E30 (`struct _tag_cCmes`) and 0x006D33A0
 * (`struct _tag_cOpening`) are outside `g_sys_w` -- which is 0x98 bytes at 0x006B4840, so it
 * ends at 0x006B48D8 -- and no symbol covers either address; the overlay scratch base
 * 0x01874000 that `fp_doll.c` hands `ps2dancerPdataLoadInit` has none either.  Those three
 * stay raw casts in their units until a named member or const genuinely covers them, and
 * the hardware-address check (tools/units/hw_names.py) does not ask for a macro they cannot
 * have.
 */
#ifndef DDR_HW_EE_DMA_H
#define DDR_HW_EE_DMA_H

#define D0_CHCR (*(volatile unsigned int *)0x10008000u)
#define D0_MADR (*(volatile unsigned int *)0x10008010u)
#define D0_QWC (*(volatile unsigned int *)0x10008020u)
#define D0_TADR (*(volatile unsigned int *)0x10008030u)
#define D0_ASR0 (*(volatile unsigned int *)0x10008040u)
#define D0_ASR1 (*(volatile unsigned int *)0x10008050u)
#define D0_SADR (*(volatile unsigned int *)0x10008080u)

#define D1_CHCR (*(volatile unsigned int *)0x10009000u)
#define D1_MADR (*(volatile unsigned int *)0x10009010u)
#define D1_QWC (*(volatile unsigned int *)0x10009020u)
#define D1_TADR (*(volatile unsigned int *)0x10009030u)
#define D1_ASR0 (*(volatile unsigned int *)0x10009040u)
#define D1_ASR1 (*(volatile unsigned int *)0x10009050u)
#define D1_SADR (*(volatile unsigned int *)0x10009080u)

#define D2_CHCR (*(volatile unsigned int *)0x1000A000u)
#define D2_MADR (*(volatile unsigned int *)0x1000A010u)
#define D2_QWC (*(volatile unsigned int *)0x1000A020u)
#define D2_TADR (*(volatile unsigned int *)0x1000A030u)
#define D2_ASR0 (*(volatile unsigned int *)0x1000A040u)
#define D2_ASR1 (*(volatile unsigned int *)0x1000A050u)
#define D2_SADR (*(volatile unsigned int *)0x1000A080u)

#define D3_CHCR (*(volatile unsigned int *)0x1000B000u)
#define D3_MADR (*(volatile unsigned int *)0x1000B010u)
#define D3_QWC (*(volatile unsigned int *)0x1000B020u)
#define D3_TADR (*(volatile unsigned int *)0x1000B030u)
#define D3_ASR0 (*(volatile unsigned int *)0x1000B040u)
#define D3_ASR1 (*(volatile unsigned int *)0x1000B050u)
#define D3_SADR (*(volatile unsigned int *)0x1000B080u)

#define D_CTRL (*(volatile unsigned int *)0x1000E000u)
#define D_STAT (*(volatile unsigned int *)0x1000E010u)
#define D_PCR (*(volatile unsigned int *)0x1000E020u)
#define D_SQWC (*(volatile unsigned int *)0x1000E030u)
#define D_RBSR (*(volatile unsigned int *)0x1000E040u)
#define D_RBOR (*(volatile unsigned int *)0x1000E050u)
#define D_STADR (*(volatile unsigned int *)0x1000E060u)

#endif /* DDR_HW_EE_DMA_H */
