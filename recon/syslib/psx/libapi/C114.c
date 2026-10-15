/* syslib/psx/libapi/C114.c -- RECONSTRUCTED from nfs4-f.exe (disasm-v3).
 *   obj libapi.lib(C114.OBJ): _96_remove -- BIOS 0xA0:0x72 tail-call thunk (RULE 7).
 *   The 3 thunk instructions match byte-for-byte. The oracle .s lists 3 trailing padding
 *   words (0x80106960..0x80106968, inter-object link padding); objdump abbreviates 3+
 *   zero words to "...", so verify_asm's objdump parser cannot count them and reports
 *   "ours 4 / oracle 6". This is a verify-tool artifact, not a body mismatch. */
#include "../../../lib/bios_thunk.h"

/* Sony library-information stamp: the first 8 bytes of this object's .text (retail
 * 2MB image: the 8 bytes right before the code; part of the original .obj, so a natural link
 * has to carry them in the object itself). */
#if defined(__mips__)
__asm__("\t.text\n\t.byte 0x50,0x73,0x00,0x25,0x9B,0x52,0x43,0x00\n");
#endif

BIOS_THUNK(_96_remove, 0xA0, 0x72);   /* @0x80106954 */
