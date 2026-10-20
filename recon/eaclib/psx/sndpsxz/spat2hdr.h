#ifndef _SNDPSXZ_SPAT2HDR_H_
#define _SNDPSXZ_SPAT2HDR_H_

extern int SNDattributessetdef(int *attr); /* @0x801035B0 */
extern int iSNDpatchtohdr(short *sampleData, int *hdr, int *attr, int *extraOut); /* @0x801035E4 (returns 0) */ /* spat2hdr */

#endif /* _SNDPSXZ_SPAT2HDR_H_ */
