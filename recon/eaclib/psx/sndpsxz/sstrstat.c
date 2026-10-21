/* eaclib/psx/sndpsxz/sstrstat.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sstrstat.obj @0x800E87D0 */
#include "sdata.h"
#include "sserver.h"
#include "sst.h"
#include "sstgetrp.h"
#include "sstrstat.h"
#include "smath64.h"

/* SNDSTRM_requeststatus : fill the 4-int request-status block `s` (state, played, remaining, permille). */
int SNDSTRM_requeststatus(unsigned int reqTag, int s)
{
    int *sp, *rp;
    unsigned int div;
    struct SNDu64Value q;
    *(int *)s = 0;
    *(int *)(s + 4) = 0;
    *(int *)(s + 8) = 0;
    *(int *)(s + 0xc) = 0;
    if ((signed char)sndgs[0xf] == 0) return -10;
    if (-1 >= (int)reqTag) return -8;
    sp = (int *)iSNDstreamgetstreamptr((int)(reqTag & 0xff));
    if (sp == 0) return -8;
    iSNDenteraudio();
    rp = (int *)iSNDstreamgetrequestptr(reqTag);
    if (rp == 0)
        goto no_request;
    if (rp[2] < 0) {
        *(int *)s = 0;
    } else {
        if (*sp == (int)rp) { *(int *)s = 2; div = *(unsigned short *)(sp + 7); }
        else                { *(int *)s = 1; div = *(unsigned short *)(sp + 8); }
        (void)iSNDmulu64(&q, (unsigned int)rp[5], 1000);
        *(int *)(s + 4) = iSNDdivu64(q, div);
        (void)iSNDmulu64(&q, (unsigned int)(rp[6] - rp[5]), 1000);
        *(int *)(s + 8) = iSNDdivu64(q, div);
        *(unsigned int *)(s + 0xc) = (unsigned int)(rp[7] * 1000) / div;
    }
    goto status_done;
no_request:
    *(int *)s = 3;
status_done:
    iSNDleaveaudio();
    return 0;
}
