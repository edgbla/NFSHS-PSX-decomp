/* eaclib/psx/sndpsxz/seffect.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   Source obj : nfs4\eaclib\psx\seffect.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   2 fns @[0x800E6D58 .. 0x800E6DD0].  SNDfxinitbus/SNDfxmasterlevel -- configure an effect (reverb) bus
 *   and broadcast its master level to every channel.  Ghidra nfs4-f.exe.c (seffect) + IDA sigs (this=bus).
 *
 *   The PSX bus-0 record begins at byte offset +0x9C (word index 0x27); indexed paths retain a 0x10
 *   stride. Each SndFxBus record has int fields type/master/depth/delay at offsets +0/+4/+8/+0xC.
 *   Known game callsites use bus 0; the apparent bus-1 range overlaps server-state fields.
 */
#include "sdata.h"
#include "sndserverpriv.h"
#include "sndchpriv.h"
#include "sndfxpriv.h"
#include "sdfx.h"
#include "seffect.h"
#include "sfxlevel.h"

/* SNDfxinitbus @0x800E6D58 : initialise effect bus `bus` (mode + depth params), then set its master level. */
int SNDfxinitbus(int bus, int mode, int arg2, int arg3, int arg4)
{
    SndFxBus *e = (SndFxBus *)((unsigned char *)sndgs + 0x9C) + bus;
    e->type = arg2;
    e->depth = arg3;
    e->delay = arg4;
    iSNDplatformfxinit(bus, arg2, arg3, arg4);
    if (arg2 == 0)
        mode = 0;
    return SNDfxmasterlevel(bus, mode);
}

/* SNDfxmasterlevel @0x800E6DD0 : record bus `bus`'s master level and re-push each channel's send level.
 * MATCH: the short-lived `base` keeps the bus-store address rooted at sndgs, while the indexed record
 * loop naturally creates the oracle's separate base, count and 100-byte induction registers. */
int SNDfxmasterlevel(int bus, int level)
{
    int r, i;
    struct SndGlobalServerStateView *loopBase;
    struct SndGlobalServerStateView *base = (struct SndGlobalServerStateView *)sndgs;
    SndFxBus *fx = (SndFxBus *)((unsigned char *)base + bus * (int)sizeof(SndFxBus) + 0x9c);
    fx->master = level;
    r = iSNDplatformfxmasterlevel(bus, level);
    if (r < 0)
        return r;
    if (base->initialized == 0)
        return 0;
    for (i = 0; i < ((struct SndGlobalServerStateView *)sndgs)->channel_count; i++) {
        unsigned char *rec;
        loopBase = (struct SndGlobalServerStateView *)sndgs;
        rec = (unsigned char *)(i * sizeof(SndChannel) + loopBase->play_records);
        SNDfxlevel((int)((SndChannel *)(unsigned int)rec)->owner_tag,
                   bus, (int)((SndChannelFxLevelStepView *)(unsigned int)(rec + bus + 0x34))->next_level);
    }
    return 0;
}
