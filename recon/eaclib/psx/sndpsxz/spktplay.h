#ifndef _SNDPSXZ_SPKTPLAY_H_
#define _SNDPSXZ_SPKTPLAY_H_

extern int iSNDpacketplayoverhead(int n); /* @0x801028BC */
extern int SNDPKTPLAY_overhead(int n); /* @0x801028D0 */ /* spktplay */
extern int SNDPKTPLAY_create(int mem, int memsize, int relcb, int notifycb); /* @0x801028FC */
extern int SNDPKTPLAY_start(int p, int rate, int hdr, int params); /* @0x80102A10 */
extern int SNDPKTPLAY_submit(int p, int frame); /* @0x80102CFC */
extern int SNDPKTPLAY_submitspace(int p); /* @0x80102E70 */
extern int SNDPKTPLAY_unsafeframesoutstanding(int p); /* @0x80102EC4 */ /* spktplay */
extern int SNDPKTPLAY_framesoutstanding(int p); /* @0x80102EEC */
extern int SNDPKTPLAY_purge(int p, int lo, int hi); /* @0x80102F3C */
extern int SNDPKTPLAY_stop(int p); /* @0x80103118 */
extern int SNDPKTPLAY_destroy(int p); /* @0x801031F4 */
extern int iSNDpacketget(int p, int idx, int *out); /* spktplay */ /* @0x80103248 */
extern unsigned int iSNDpacketfreeframes(int p, int idx, int bytes); /* spktplay @0x801033C4, real 3-arg sig
                                                                          * (see spktplay.cpp) -- the oracle call
                                                                          * site sets up a0=p/a1=i/a2=taken. */ /* @0x801033C4 */

extern int sndpps[];

#endif /* _SNDPSXZ_SPKTPLAY_H_ */
