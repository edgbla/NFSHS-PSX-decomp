/* syslib/psx/libc/A63.c -- RECONSTRUCTED from nfs4-f.exe (disasm-v3).
 *   obj A63.obj ; libc.lib.  puts @0x800E80CC -- BIOS trampoline (B0:0x3F -> std_out_puts).  In the EXE
 *   this is a 3-insn tail-call (addiu $t2,$zero,0xB0; jr $t2; addiu $t1,$zero,0x3F) to the PSX BIOS, so
 *   per RULE 7 it stays a BIOS thunk (the real code is the console BIOS TTY).
 */
#include "../../../lib/bios_thunk.h"

/* Sony library-information stamp: the first 8 bytes of this object's .text (retail
 * 2MB image: the 8 bytes right before the code; part of the original .obj, so a natural link
 * has to carry them in the object itself). */
#if defined(__mips__)
__asm__("\t.text\n\t.byte 0x50,0x73,0x01,0x25,0x9B,0x52,0x43,0x00\n");
#endif

BIOS_THUNK(puts, 0xB0, 0x3F);   /* @0x800E80CC */
