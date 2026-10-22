/* eaclib/psx/sndpsxz/s3dpos.c -- RECONSTRUCTED. NOT original.  *** 1/1 PASS ***  obj s3dpos.obj @0x800FEE30 */
/*   iSNDplatform3dpos -- set a voice's pan angle and re-derive its SPU L/R (the low-level half of SND3dpos).
 *   Callers pass a third `y` value, but the callee never reads $a2. The original C formal count is not recoverable
 *   from this binary alone; keep the unused parameter here to match the three-argument caller interface. */
#include "s3dpos.h"
#include "saetodv.h"
#include "saetolrv.h"
#include "sdata.h"
#include "sndserverpriv.h"
#include "sndchpriv.h"
#include "sndpacketpriv.h"
#include "slib.h"
#include "snd_state.h"

/* iSNDplatform3dpos @0x800FEE30 : store pan angle `x` (+0x18) and, if the voice is playing, recompute its
 *   SPU L/R from the routing mode and push it. MATCH: the voice fields are one volatile sndpd+0xd8 record;
 *   the explicit non-playing return supplies the oracle's zero-valued branch delay slot. */
int iSNDplatform3dpos(int chan, int x, int y)
{
    int vt = chan * 0x2c;
    volatile unsigned char *slot = sndpd + 0xd8 + vt;
    int outL, outR;

    ((volatile SndPacketVoiceState *)slot)->volume_angle = (short)x;
    if (((volatile SndPacketVoiceState *)slot)->play_state != 2)
        return 0;
    if (((volatile SndPacketVoiceState *)slot)->route == 1)
        iSNDatodlrv(x, ((SndChannel *)(unsigned int)((struct SndGlobalServerStateView *)sndgs)->play_records)[chan].volume,
                    &outL, &outR, (signed char)((volatile SndPacketVoiceState *)slot)->pad24_25[0], (signed char)((volatile SndPacketVoiceState *)slot)->pad24_25[1]);
    else if (((volatile SndPacketVoiceState *)slot)->route == 0)
        iSNDatolrv(x, ((SndChannel *)(unsigned int)((struct SndGlobalServerStateView *)sndgs)->play_records)[chan].volume,
                   &outL, &outR);
    ((volatile SndPacketVoiceState *)slot)->pad24_25[0] = (unsigned char)outL;
    ((volatile SndPacketVoiceState *)slot)->pad24_25[1] = (unsigned char)outR;
    iSNDsetvol(chan, outL, outR);
    return 0;
}
