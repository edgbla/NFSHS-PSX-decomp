#ifndef _SNDPSXZ_SDMEMMAN_H_
#define _SNDPSXZ_SDMEMMAN_H_

extern void iSNDpsxmemconstrain(unsigned int *size, int *avail); /* @0x8010A550 */
extern int iSNDpsxmalloc(int size); /* @0x8010A5CC */
extern int iSNDpsxfree(int ptr); /* sdmemman */

#endif /* _SNDPSXZ_SDMEMMAN_H_ */
