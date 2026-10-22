/* eaclib/psx/sndpsxz/sstgetv.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sstgetv.obj @0x800E83EC */
#include "sdata.h"
#include "sndserverpriv.h"
#include "sgetvol.h"
#include "sst.h"
#include "sstpriv.h"
#include "sstgetv.h"

/* SNDSTRM_getvol : query a stream's current volume. */
int SNDSTRM_getvol(int tag)
{
    SndStream *sp;
    int vol;
    if (((struct SndGlobalServerStateView *)sndgs)->initialized == 0)
        return -10;
    sp = (SndStream *)iSNDstreamgetstreamptr(tag);
    if (sp == 0)
        return -8;
    vol = SNDgetvol(sp->start_result);
    if (vol < 0)
        vol = (signed char)sp->start_params.vol; /* signed view preserves the retail lb at +0x54 */
    return vol;
}
