/* eaclib/psx/sndpsxz/sbend.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   Source obj : nfs4\eaclib\psx\sbend.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   2 fns @[0x800E78F8 .. 0x800E79D0].  SNDpitchbend -- retune the voices of a playing sound.
 *   Ghidra nfs4-f.exe.c (sbend) + IDA sigs.
 */
#include "salloc.h"
#include "sbend.h"
#include "sclcptch.h"
#include "sdata.h"
#include "sdriver.h"
#include "spatkey.h"
#include "sserver.h"

/* iSNDunsafebend @0x800E78F8 : set the detune (+0x2f) on every voice of `tag`, recomputing SPU pitch. */
int iSNDunsafebend(unsigned int tag, unsigned int chan)
{
    int chanIdx = iSNDgetchan(tag);
    int cur[2];
    if (-1 < chanIdx) {
        cur[0] = -1;
        while (iSNDpatchkey(chanIdx, (int)cur) != 0) {
            int v = sndgs[0x25] + cur[0] * 100;
            if ((int)*(signed char *)(v + 0x2f) == (int)chan)   /* +0x2f detune read signed (lb); this build's char is unsigned */
                return 0;
            if (*(short *)(v + 0x5a) == 0)
                return 0;
            *(char *)(v + 0x2f) = (char)chan;
            {
                /* MATCH: naming the already-loaded channel before the store lets gcc sink the store
                 * into iSNDcalcpitch's jal delay slot; either statement alone leaves a nop there. */
                int c = cur[0];
                *(short *)(v + 0x5e) = 0;
                iSNDcalcpitch(c);
            }
            iSNDplatformpitch(cur[0], (int)(unsigned)*(unsigned short *)(v + 0x62));
        }
    }
    return chanIdx;
}

/* SNDpitchbend @0x800E79D0 : audio-locked wrapper around iSNDunsafebend. */
int SNDpitchbend(unsigned int tag, int bend)
{
    int r;
    if ((signed char)sndgs[0xf] == 0)
        return -10;
    iSNDenteraudio();
    r = iSNDunsafebend(tag, (unsigned int)bend);
    iSNDleaveaudio();
    return r;
}
