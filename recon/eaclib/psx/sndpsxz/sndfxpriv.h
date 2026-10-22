/* Private PSX SND effect-bus record. The shared SND state places two buses at +0x9C;
 * recon/lib/snd.h independently records the same 0x10-byte type/master/depth/delay layout. */
#ifndef _SNDPSXZ_SNDFXPRIV_H_
#define _SNDPSXZ_SNDFXPRIV_H_

typedef struct SndFxBus {
    int type;       /* +0x00 */
    int master;     /* +0x04 */
    int depth;      /* +0x08 */
    int delay;      /* +0x0C */
} SndFxBus;
typedef char SndFxBus_size_check[(sizeof(SndFxBus) == 0x10) ? 1 : -1];

#endif /* _SNDPSXZ_SNDFXPRIV_H_ */
