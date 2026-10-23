/* eaclib/psx/sndpsxz/sbremove.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 3/3 ***
 *   Source obj : nfs4\eaclib\psx\sbremove.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   3 fns @[0x800E65F8 .. 0x800E6694].  Unload sound banks: stop their voices, release SPU data, clear the
 *   bank table.  Ghidra nfs4-f.exe.c (sbremove) + IDA sigs (`this` is the bank id).
 */
#include "sbremove.h"
#include "sbvalid.h"
#include "sstop.h"
#include "sbirmpat.h"
#include "sdasync.h"
#include "snd_globals.h"
#include "sndchpriv.h"
#include "sndbankpriv.h"
#include "sndbankhdrpriv.h"

/* iSNDremovepatches @0x800E65F8 : release each of a bank's `count` resolved patches (de-dup via a local
 *   scratch table seeded to -1). */
int iSNDremovepatches(int bank, int count)
{
    int scratch[512];
    int *p;
    int i;
    int neg1 = -1;
    i = 0xFF;
    p = &scratch[510];
    do {                                 /* seed the {id} slots to -1, back to front */
        *p = neg1;
        i--;
        p -= 2;
    } while (i >= 0);
    for (i = 0; i < count; i++)
        iSNDbankremovepat(bank, i, scratch);
    return 0;
}

/* SNDbankremove @0x800E6674 : the exit-time hook (sndgs[0x1f]); unloads bank `bankId`. */
void SNDbankremove(int bankId)
{
    cSNDbankremove(bankId, 0);
}

/* cSNDbankremove @0x800E6694 : unload bank `bankId` (or all banks when bankId == -1) -- stop its playing
 *   voices, free its patches/SPU data, and clear its bank-table entry. */
int cSNDbankremove(int bankId, int recurse)
{
    struct SNDGlobals *base = &sndgs;
    int i;

    if (!base->initialized)
        return -10;
    if (bankId == -1) {                  /* unload every bank */
        for (i = 0; i < base->bank_count; i++)
            cSNDbankremove(i, 0);
        return 0;
    }
    if (iSNDvalidbank(bankId))
        return -8;
    {
        int data = (int)(unsigned int)((struct SndBankTableEntry *)(bankId * sizeof(struct SndBankTableEntry) + base->bank_table))->data_block;
        int off;
        unsigned char *entry;
        struct SNDGlobals *base2;
        i = 0;
        if (base->channel_count) {     /* stop voices owned by this bank */
            struct SNDGlobals *loopbase = base;
            off = 0;
            do {
                SndChannel *slot = (SndChannel *)(unsigned int)(loopbase->play_records + off);
                if (slot->start_marker == bankId)
                    SNDstop((int)slot->owner_tag);
                off += sizeof(SndChannel);
            } while (loopbase->channel_count > ++i);
        }
        base2 = &sndgs;
        entry = (unsigned char *)(bankId * sizeof(struct SndBankTableEntry) +
            *(volatile int *)&base2->bank_table);
        if (((struct SndBankTableEntry *)entry)->platform_allocated.s) {
            iSNDplatformfree((int)(unsigned int)((struct SndBankTableEntry *)entry)->platform_block);
            ((struct SndBankTableEntry *)(bankId * sizeof(struct SndBankTableEntry) + sndgs.bank_table))->platform_allocated.u = 0;
        } else
            iSNDremovepatches(bankId, ((struct SndBankDataHeaderPrefix *)(unsigned int)data)->patch_count);
        ((struct SndBankTableEntry *)(bankId * sizeof(struct SndBankTableEntry) + sndgs.bank_table))->data_block = 0;
        ((struct SndBankTableEntry *)(bankId * sizeof(struct SndBankTableEntry) + sndgs.bank_table))->load_state.u = 0;
    }
    return 0;
}

