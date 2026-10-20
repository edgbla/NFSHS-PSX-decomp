/* eaclib/psx/sndpsxz/sstgetv.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sstgetv.obj @0x800E83EC */
#include "sdata.h"
#include "sgetvol.h"
#include "sst.h"
#include "sstgetv.h"

/* SNDSTRM_getvol : query a stream's current volume. */
int SNDSTRM_getvol(int tag)
{
    int sp, vol;
    if ((signed char)sndgs[0xf] == 0)
        return -10;
    sp = iSNDstreamgetstreamptr(tag);
    if (sp == 0)
        return -8;
    vol = SNDgetvol(*(unsigned int *)(sp + 8));
    if (vol < 0)
        vol = *(signed char *)(sp + 0x54);
    return vol;
}
