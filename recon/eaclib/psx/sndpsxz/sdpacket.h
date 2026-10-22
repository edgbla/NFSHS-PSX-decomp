#ifndef _SNDPSXZ_SDPACKET_H_
#define _SNDPSXZ_SDPACKET_H_

extern void iSNDpacketgetirq(void);
extern void iSNDpacketsetirq(void);
extern void iSNDpacketirqcallback(void);
extern void iSNDpsxzerospu(int *addr, int len);
extern unsigned int iSNDpacketpurgeframes(int p, unsigned int byteoff, int count);
extern int iSNDfillspuwithpackets(int p, int chunk);
extern void iSNDpacketserve(void);
extern int iSNDplatformpacketoverhead(void); /* @0x801041B8; sdpacket */
struct SNDSAMPLEFORMAT;
extern int iSNDplatformcalcdatarate(struct SNDSAMPLEFORMAT *sample_format);
extern int iSNDplatformpacketplaycreate(int p, int *mem); /* @0x8010421C; sdpacket */
extern void iSNDplatformpacketplaydestroy(int p); /* @0x801042C0; sdpacket */
extern int iSNDplatformpacketplay(int p, int note, int volAngle, int level, int pitch, int a6, int fxlevel, unsigned short *hdr, int a9); /* @0x80104304; caller ABI has 9 words, final a9 is unused */
extern void iSNDpsxpacketstop(void *parg);

extern int sndpp[];

#endif /* _SNDPSXZ_SDPACKET_H_ */
