/* Private control prefix for the SPU-DMA / packet IRQ shared state at sndpd+0.
 * Access unions preserve the observed volatile and signed/unsigned byte views. */
#ifndef _SNDPSXZ_SNDDMAPRIV_H_
#define _SNDPSXZ_SNDDMAPRIV_H_

union SndDmaCallbackGuardView {
    unsigned char plain;
    volatile unsigned char v;
};
typedef char SndDmaCallbackGuardView_size_check[(sizeof(union SndDmaCallbackGuardView) == 1) ? 1 : -1];

union SndDmaControlByteView {
    unsigned char plain;
    volatile unsigned char v;
    signed char s;
    volatile signed char vs;
};
typedef char SndDmaControlByteView_size_check[(sizeof(union SndDmaControlByteView) == 1) ? 1 : -1];

struct SndDmaQueueStateView {
    unsigned char opaque_00;
    union SndDmaCallbackGuardView callback_guard; /* +0x01; shared by DMA preload and packet IRQ */
    unsigned char opaque_02_07[6];
    volatile int next_handle;                      /* +0x08 */
    union SndDmaControlByteView in_flight_count;   /* +0x0C */
    union SndDmaControlByteView active_slot;      /* +0x0D */
    union SndDmaControlByteView transfer_busy;    /* +0x0E */
    unsigned char opaque_0F;
};
typedef char SndDmaQueueStateView_size_check[(sizeof(struct SndDmaQueueStateView) == 0x10) ? 1 : -1];

#endif /* _SNDPSXZ_SNDDMAPRIV_H_ */
