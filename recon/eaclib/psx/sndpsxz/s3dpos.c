/* eaclib/psx/sndpsxz/s3dpos.c -- RECONSTRUCTED. NOT original.  *** 1/1 PASS ***  obj s3dpos.obj @0x800FEE30 */
/*   iSNDplatform3dpos -- set a voice's pan angle and re-derive its SPU L/R (the low-level half of SND3dpos).
 *   Callers pass a third `y` value, but the callee never reads $a2. The original C formal count is not recoverable
 *   from this binary alone; keep the unused parameter here to match the three-argument caller interface. */
#include "s3dpos.h"
#include "saetodv.h"
#include "saetolrv.h"
#include "sdata.h"
#include "slib.h"
#include "snd_state.h"

extern unsigned char DAT_80147a08, DAT_80147a0c, DAT_80147a0e, DAT_80147a14, DAT_80147a15;

/* iSNDplatform3dpos @0x800FEE30 : store pan angle `x` (+0x18) and, if the voice is playing, recompute its
 *   SPU L/R from the routing mode and push it. MATCH: the voice fields are one volatile sndpd+0xd8 record;
 *   the explicit non-playing return supplies the oracle's zero-valued branch delay slot. */
int iSNDplatform3dpos(int chan, int x, int y)
{
    int vt = chan * 0x2c;
    volatile unsigned char *slot = sndpd + 0xd8 + vt;
    int outL, outR;

    *(volatile short *)(slot + 0x18) = (short)x;
    if (slot[0x1c] != 2)
        return 0;
    if (slot[0x1e] == 1)
        iSNDatodlrv((unsigned int)x, (int)*(signed char *)(chan * 100 + sndgs[0x25] + 0x2d),
                    &outL, &outR, (int)(signed char)slot[0x24], (int)(signed char)slot[0x25]);
    else if (slot[0x1e] == 0)
        iSNDatolrv((unsigned int)x, (int)*(signed char *)(chan * 100 + sndgs[0x25] + 0x2d),
                   &outL, &outR);
    slot[0x24] = (unsigned char)outL;
    slot[0x25] = (unsigned char)outR;
    iSNDsetvol(chan, outL, outR);
    return 0;
}
