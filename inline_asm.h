#pragma once
/* The calling convention is splat's: the folder argument already carries its path
   (`INCLUDE_ASM("asm/nonmatchings/main", func_00100000)`), so the macro only joins it to
   the symbol name.  The split's own header supplies `.set noat` / `.set noreorder` and
   the macros from `asm/include/macro.inc`. */
#ifdef SKIP_ASM
#define INCLUDE_ASM(folder, name)
#define INCLUDE_DATA(folder, name)
#else
#define INCLUDE_ASM(folder, name) __asm__( \
    ".section .text\n.set noat\n.set noreorder\n" \
    ".include \"" folder "/" #name ".s\"\n")
#define INCLUDE_DATA(folder, name) __asm__( \
    ".include \"" folder "/" #name ".s\"\n")
#endif
