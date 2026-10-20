#ifndef _SNDPSXZ_SLIB_H_
#define _SNDPSXZ_SLIB_H_

extern void iSNDcalcvol(int chan); /* spatkey */
extern int iSNDpsxkeyon(int mask);
extern int iSNDpsxkeyoff(int mask); /* spatkey */
extern unsigned int iSNDpsxeffecton(int mask);
extern unsigned int iSNDpsxeffectoff(int mask); /* spatkey */
extern int iSNDpsxeffectvol(int left, int right); /* spatkey */
extern void iSNDsetvol(int chan, int left, int right); /* spatkey */
extern int iSNDsetslot(int chan, int addr, int pitch); /* @0x800FF394 */
extern unsigned int iSNDstartvoice(unsigned int chan); /* spatkey */
extern int iSNDplatformoutputcaps(void); /* @0x800FF5A8 -- oracle explicitly zeroes $v0 before return */
extern int iSNDplatformoutputset(void); /* @0x800FF600 */
extern int iSNDinit(void); /* @0x800FF700 */
extern int iSNDrestore(void); /* @0x800FF9A0 */
extern void iSNDserve(void); /* @0x800FFAF4 */ /* slib */

#endif /* _SNDPSXZ_SLIB_H_ */
