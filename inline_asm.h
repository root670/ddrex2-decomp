#pragma once
#ifdef SKIP_ASM
#define INCLUDE_ASM(folder, name)
#define INCLUDE_DATA(folder, name)
#else
#define INCLUDE_ASM(folder, name) __asm__( \
    ".section .text\n.set noat\n.set noreorder\n" \
    ".include \"asm/nonmatchings/" folder "/" #name ".s\"\n")
#define INCLUDE_DATA(folder, name) __asm__( \
    ".include \"asm/nonmatchings/" folder "/" #name ".s\"\n")
#endif
