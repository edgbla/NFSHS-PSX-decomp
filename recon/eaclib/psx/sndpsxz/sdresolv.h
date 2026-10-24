#ifndef _SNDPSXZ_SDRESOLV_H_
#define _SNDPSXZ_SDRESOLV_H_

struct SNDResolveEntry {
    int offset;
    int spu;
};
typedef char SNDResolveEntry_size_check[(sizeof(struct SNDResolveEntry) == 8) ? 1 : -1];

struct SNDRemoveEntry {
    int spu_address;
    int reserved;
};
typedef char SNDRemoveEntry_size_check[(sizeof(struct SNDRemoveEntry) == 8) ? 1 : -1];

extern int iSNDplatformresolve(unsigned char *cursor, const unsigned char *bankData, struct SNDResolveEntry *patch); /* @0x8010B75C */ /* sdresolv */
extern int iSNDplatformremove(unsigned char *cursor, struct SNDRemoveEntry *patch); /* @0x8010B958 */ /* sdresolv */

#endif /* _SNDPSXZ_SDRESOLV_H_ */
