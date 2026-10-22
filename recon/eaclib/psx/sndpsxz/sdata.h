#ifndef _SNDPSXZ_SDATA_H_
#define _SNDPSXZ_SDATA_H_

#include "sndgsbase.h"
extern unsigned char gSndState[];
extern unsigned char D_80147871;
extern int D_80147898[]; /* linker alias for sndgs +0x38 (SNDSYSOPTS::vec) */
extern int DAT_801478f4[];
extern int sndgs_fx_bus0_master[]; /* interior linker alias: sndgs +0xA0, SndFxBus[0].master */

#endif /* _SNDPSXZ_SDATA_H_ */
