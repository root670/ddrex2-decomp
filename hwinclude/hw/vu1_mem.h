/*
 * VU1 data memory, as the EE core addresses it: 0x70000000-0x70003FFF (16 KiB).
 *
 * VU1's data memory is mapped into the EE's address space as an uncached window, so a unit
 * that hands VU1 microcode a buffer names it by this base, and the microcode's input areas
 * are byte offsets into the same window: `gs_3d` keeps its vertex/colour/texture pointers at
 * 0x00, 0x10, 0x20 and 0x30 (four floats each), and `title_demo` stages an MPEG picture in
 * the whole window between two DMA calls.
 *
 * Every accessor keeps the `*(volatile TYPE *)ADDR` shape (or, for the pointer form, an
 * address the compiler folds to the same constant).  Spelling the window as a struct and
 * reaching a field would emit `lui`/`addiu` for the window base plus an offset -- a different
 * instruction than the matched unit's own constant -- so the spelling is part of the evidence
 * and a unit must not replace these macros with a hand-written cast at the use site.
 * `VU1_MEM_PTR` is the pointer form (a typed pointer at a byte offset, for a unit that keeps
 * the address in a variable), and the typed lvalues are the load/store form; the 128-bit one
 * requires a 16-byte-aligned offset, the window's quad alignment.
 */
#ifndef DDR_HW_VU1_MEM_H
#define DDR_HW_VU1_MEM_H

#define VU1_MEM_BASE 0x70000000u
#define VU1_MEM_SIZE 0x4000u

#define VU1_MEM_PTR(type, offset) ((type *)(VU1_MEM_BASE + (offset)))

#define VU1_MEM_U128(offset) (*(volatile unsigned __int128 *)(VU1_MEM_BASE + (offset)))
#define VU1_MEM_U32(offset) (*(volatile unsigned int *)(VU1_MEM_BASE + (offset)))
#define VU1_MEM_S32(offset) (*(volatile int *)(VU1_MEM_BASE + (offset)))
#define VU1_MEM_F32(offset) (*(volatile float *)(VU1_MEM_BASE + (offset)))
#define VU1_MEM_U16(offset) (*(volatile unsigned short *)(VU1_MEM_BASE + (offset)))
#define VU1_MEM_S16(offset) (*(volatile short *)(VU1_MEM_BASE + (offset)))

#endif /* DDR_HW_VU1_MEM_H */
