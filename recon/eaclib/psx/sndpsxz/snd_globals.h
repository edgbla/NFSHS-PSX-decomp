/* snd_globals.h -- typed overlay of the sound-bank fields in the shared sndgs state block.
 * bank_table is a SndBankTableEntry array base. Do not combine with sdata.h's generic `int sndgs[]`
 * view in the same translation unit. */
#ifndef _SNDPSXZ_SND_GLOBALS_H_
#define _SNDPSXZ_SND_GLOBALS_H_

struct SndBankTableEntry;

struct SNDGlobals {
    char pad0[0x0c];
    unsigned short bank_count;
    char pad0e[3];
    unsigned char channel_count;
    char pad12[0x2a];
    signed char initialized;
    char pad3d[0x57];
    int play_records;
    struct SndBankTableEntry *bank_table; /* +0x98 */
};

extern struct SNDGlobals sndgs;

#endif /* _SNDPSXZ_SND_GLOBALS_H_ */
