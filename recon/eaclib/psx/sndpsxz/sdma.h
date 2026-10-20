#ifndef _SNDPSXZ_SDMA_H_
#define _SNDPSXZ_SDMA_H_

extern void iSNDdmtransfer(void); /* @0x8010A880 */
extern void iSNDdmcallback(void); /* @0x8010AA64 */ /* sdma -- installed as the DMA4 callback */
extern void iSNDdmservice(void); /* @0x8010AC20 */
extern int iSNDdmqueue(int dst_spu, unsigned int src_ram, int len, int prio, int flag); /* sdma */ /* @0x8010ACA0 */ /* sdma
                                                             * -- real 5-arg sig (see sdma.c): the fillspu
                                                             * DMA-kick call was a DROPPED-ARGS bug (1-arg
                                                             * called as if void(spuBuf)); oracle sets up
                                                             * all 5: a0=chBuf, a1=pp->0+chunk<<pp->0x43+
                                                             * pp->8*i, a2=pp->0x44(blockBytes), a3=2,
                                                             * stack=flag(chunk==0&&i==0). */
extern int iSNDdmqueuesplit(int dst_spu, unsigned int src_ram, int len, int prio);
extern int iSNDdmcomplete(int handle);

#endif /* _SNDPSXZ_SDMA_H_ */
