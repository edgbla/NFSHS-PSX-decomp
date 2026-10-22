/* eaclib/psx/sndpsxz/sststat.c -- RECONSTRUCTED. NOT original.  *** 1/1 PASS ***  obj sststat.obj @0x800E86D8 */
#include "sdata.h"
#include "../../../shared/SNDSTREAMSTATUS.h"
#include "sndserverpriv.h"
#include "spktplay.h"
#include "sserver.h"
#include "sst.h"
#include "sstpriv.h"
#include "sststat.h"

/* SNDSTRM_status : fill the 3-int status block `s` (active, bytes, permille) for stream `tag`. */
int SNDSTRM_status(int tag, int s)
{
    SndStream *sp;
    unsigned int frames, outstanding;
    ((struct SNDSTREAMSTATUS *)(unsigned int)s)->timebuffered = 0;
    ((struct SNDSTREAMSTATUS *)(unsigned int)s)->currentrequest = 0;
    ((struct SNDSTREAMSTATUS *)(unsigned int)s)->outstandingrequests = 0;
    if (((struct SndGlobalServerStateView *)sndgs)->initialized == 0) return -10;
    sp = (SndStream *)iSNDstreamgetstreamptr(tag);
    if (sp == 0) return -8;
    iSNDenteraudio();
    ((struct SNDSTREAMSTATUS *)(unsigned int)s)->outstandingrequests = ((int)((unsigned)((volatile SndStream *)sp)->current_count << 24)) >> 24;
    if (sp->current_count != 0) {
        ((struct SNDSTREAMSTATUS *)(unsigned int)s)->currentrequest = sp->requests->request_id;
        frames = sp->locked_rate.samplerate;
        if (frames != 0) {
            outstanding = (unsigned int)SNDPKTPLAY_unsafeframesoutstanding(sp->packet_player);
            ((struct SNDSTREAMSTATUS *)(unsigned int)s)->timebuffered =
                (outstanding * 1000) / sp->locked_rate.samplerate;
        }
    }
    iSNDleaveaudio();
    return 0;
}
