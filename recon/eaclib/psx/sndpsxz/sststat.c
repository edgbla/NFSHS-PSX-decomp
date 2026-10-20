/* eaclib/psx/sndpsxz/sststat.c -- RECONSTRUCTED. NOT original.  *** 1/1 PASS ***  obj sststat.obj @0x800E86D8 */
#include "sdata.h"
#include "spktplay.h"
#include "sserver.h"
#include "sst.h"
#include "sststat.h"

/* SNDSTRM_status : fill the 3-int status block `s` (active, bytes, permille) for stream `tag`. */
int SNDSTRM_status(int tag, int s)
{
    int *sp;
    unsigned int frames, outstanding;
    *(int *)(s + 8) = 0;
    *(int *)(s + 4) = 0;
    *(int *)s = 0;
    if ((signed char)sndgs[0xf] == 0) return -10;
    sp = (int *)iSNDstreamgetstreamptr(tag);
    if (sp == 0) return -8;
    iSNDenteraudio();
    *(int *)s = ((int)(*(volatile unsigned char *)((int)sp + 0x16) << 24)) >> 24;
    if (*(unsigned char *)((int)sp + 0x16) != 0) {
        *(int *)(s + 4) = *(int *)(*sp + 4);
        frames = (unsigned int)*(unsigned short *)(sp + 7);
        if (frames != 0) {
            outstanding = (unsigned int)SNDPKTPLAY_unsafeframesoutstanding(sp[3]);
            *(unsigned int *)(s + 8) =
                (outstanding * 1000) / (unsigned int)*(unsigned short *)(sp + 7);
        }
    }
    iSNDleaveaudio();
    return 0;
}
