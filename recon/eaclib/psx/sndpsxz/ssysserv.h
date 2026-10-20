#ifndef _SNDPSXZ_SSYSSERV_H_
#define _SNDPSXZ_SSYSSERV_H_

extern short *iSNDserveraddclient(int cb); /* @0x8010479C */
extern void iSNDserverremoveclient(int cb); /* @0x801047CC */
extern void SNDSYS_service(void); /* ssysserv */ /* @0x80104878 */

#endif /* _SNDPSXZ_SSYSSERV_H_ */
