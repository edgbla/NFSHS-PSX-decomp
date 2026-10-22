/* Evidence-backed libetc interrupt entry points used by sndpsxz. */
#ifndef _SNDPSXZ_SNDLIBETCPRIV_H_
#define _SNDPSXZ_SNDLIBETCPRIV_H_

extern void InterruptCallback(int idx, void (*handler)(void)); /* syslib INTR (real 2-arg sig -- see
                                                                 * INTR_DMA.cpp/INTR_VB.c/drv.cpp);
                                                                 * INTR.obj @0x800F287C. */
extern int DMACallback(int ch, int func); /* libetc INTR.obj @0x800F28AC; real args are channel and
                                           * new-callback-fn; Ghidra/older declarations dropped both
                                           * args, see cdcont.cpp/SYS.cpp; installed as DMA4 callback. */

#endif /* _SNDPSXZ_SNDLIBETCPRIV_H_ */
