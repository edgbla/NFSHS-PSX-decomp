#ifndef _SNDPSXZ_SALLOC_H_
#define _SNDPSXZ_SALLOC_H_

extern int iSNDischanreserved(int chan, int count); /* @0x800FE724 */
extern int iSNDallocchan(unsigned int priority, int numChannels, int a2, unsigned int *out); /* salloc */
extern void iSNDfreechan(int chan); /* salloc */
extern int iSNDgetchan(unsigned int tag); /* salloc */

extern int DAT_80136dec[1];
extern signed char sndchanreserved[];

#endif /* _SNDPSXZ_SALLOC_H_ */
