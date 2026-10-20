/* eaclib/psx/sndpsxz/sstautov.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   Source obj : nfs4\eaclib\psx\sstautov.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col12 / SYM v3)
 *   1 fn @0x800E9DE8.  SNDSTRM_autovol -- set a stream's auto-volume ramp.  Ghidra nfs4-f.exe.c + IDA sig
 *   (`this` is the stream tag).
 */
#include "sdata.h"
#include "sst.h"
#include "sstautov.h"
#include "sautovol.h"

/* SNDSTRM_autovol @0x800E9DE8 : store the target vol (+0x54) and start an auto-volume ramp over steps/10. */
int SNDSTRM_autovol(int tag, int steps, int vol)
{
    int s;
    if ((signed char)sndgs[0xf] == '\0')
        return -10;
    s = iSNDstreamgetstreamptr(tag);
    if (s == 0)
        return -8;
    *(char *)(s + 0x54) = (char)vol;
    SNDautovol(*(int *)(s + 8), steps / 10, vol);
    return 0;
}
