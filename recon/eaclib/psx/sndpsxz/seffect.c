/* eaclib/psx/sndpsxz/seffect.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   Source obj : nfs4\eaclib\psx\seffect.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   2 fns @[0x800E6D58 .. 0x800E6DD0].  SNDfxinitbus/SNDfxmasterlevel -- configure an effect (reverb) bus
 *   and broadcast its master level to every channel.  Ghidra nfs4-f.exe.c (seffect) + IDA sigs (this=bus).
 *
 *   Effect buses begin at byte offset +0x9C (word index 0x27), stride 0x10; each SndFxBus has
 *   int fields type/master/depth/delay at byte offsets +0/+4/+8/+0xC.
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
    SndFxBus *e = (SndFxBus *)&sndgs[0x27] + bus;
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
    unsigned char *loopBase;
    unsigned char *base = (unsigned char *)sndgs;
    SndFxBus *fx = (SndFxBus *)(base + bus * 16 + 0x9c);
    fx->master = level;
    r = iSNDplatformfxmasterlevel(bus, level);
    if (r < 0)
        return r;
    if (((struct SndGlobalServerStateView *)sndgs)->initialized == 0)
        return 0;
    for (i = 0; i < (int)(unsigned)((unsigned char *)sndgs)[0x11]; i++) {
        unsigned char *rec;
        loopBase = (unsigned char *)sndgs;
        rec = (unsigned char *)(i * (int)sizeof(SndChannel) + ((struct SndGlobalServerStateView *)loopBase)->play_records);
        SNDfxlevel((int)((SndChannel *)(unsigned int)rec)->owner_tag,
                   bus, (int)((SndChannelFxLevelStepView *)(unsigned int)(rec + bus + 0x34))->next_level);
    }
    return 0;
}
