#ifndef _SNDPSXZ_SDPACKET_H_
#define _SNDPSXZ_SDPACKET_H_

extern void iSNDpacketgetirq(void);
extern void iSNDpacketsetirq(void);
extern void iSNDpacketirqcallback(void);
extern void iSNDpsxzerospu(int *addr, int len);
extern unsigned int iSNDpacketpurgeframes(int p, unsigned int byteoff, int count);
extern int iSNDfillspuwithpackets(int p, int chunk);
extern void iSNDpacketserve(void);
extern int iSNDplatformpacketoverhead(void);
extern int iSNDplatformcalcdatarate(unsigned short *sample_rate);
extern int iSNDplatformpacketplaycreate(int p, int *mem);
extern void iSNDplatformpacketplaydestroy(int p);
extern int iSNDplatformpacketplay(int p, int note, unsigned short volAngle, unsigned char level, int pitch, int a6, unsigned char fxlevel, unsigned short *hdr);
extern void iSNDpsxpacketstop(void *parg);

extern int sndpp[];

#endif /* _SNDPSXZ_SDPACKET_H_ */
