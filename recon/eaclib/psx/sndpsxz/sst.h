#ifndef _SNDPSXZ_SST_H_
#define _SNDPSXZ_SST_H_

struct SNDPLAYOPTS;

extern int iSNDstreamdestroyall(void); /* @0x800E8C14 */
extern int iSNDstreamgetstreamptr(int idx); /* @0x800E8C48 */ /* sst */
extern void iSNDstreamremoverequest(unsigned int reqid); /* @0x800E8C64 */
extern void iSNDstreamreleasecallback(int sample); /* @0x800E8D90 */
extern void iSNDstreamnotifycallback(int handle, unsigned int bytes); /* @0x800E8DD4 */
extern int iSNDstreamparseheader(int S, int data); /* @0x800E8E9C */
extern int iSNDstreamparsenumchunks(int S, int data); /* @0x800E9044 */
extern int iSNDstreamparsedata(int S, int chunk); /* @0x800E90AC (oracle: always returns 1) */
extern int iSNDstreamparseend(int S, int chunk); /* @0x800E9230 */
extern int iSNDstreamparsechunk(int S, int chunk); /* @0x800E9270 */
extern int iSNDstreamisheld(int S); /* @0x800E9318 */
extern void iSNDstreamhotroddatachunks(void); /* sst */ /* @0x800E9438 */
extern void iSNDstreamservice(void); /* @0x800E9590 (serve hook) */ /* @0x800E9590 */
extern int iSNDstreamnumcreated(void); /* @0x800E96F8 */
extern int iSNDstreamcreate(struct SNDPLAYOPTS *priority, int numReq, int pktArg, int objbuf, int memsize, int extHandle, int extFlag); /* @0x800E9730 */
extern int iSNDstreamqueue(unsigned int s, int name, char *filename, int off, int mode); /* @0x800E9970 */

extern int sndss[];
extern unsigned char sndStreamMap[];

#endif /* _SNDPSXZ_SST_H_ */
