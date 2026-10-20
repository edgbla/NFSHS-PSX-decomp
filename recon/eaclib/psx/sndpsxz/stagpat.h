#ifndef _SNDPSXZ_STAGPAT_H_
#define _SNDPSXZ_STAGPAT_H_

extern void iSNDresetpatch(int patch); /* @0x80101ABC */
extern unsigned char *iSNDresettimbre(int *t, int buf); /* @0x80101AC4 */
extern void iSNDresolveheader(int *hdr, int *out); /* @0x80101B7C */
extern int iSNDfindfreekey(void); /* @0x80101BFC */
extern int iSNDplaytaggedtimbre(int timbre, int tag, int vol, int header, int baseNote, int velScale, int pitchOff); /* @0x80101C8C */
extern int iSNDplaytaggedpatch(int bank, int tag); /* stagpat */ /* @0x8010218C */
extern int iSNDresolvetaggedpatch(int bank, int patch_idx, int scratch); /* stagpat */ /* @0x801024EC */
extern int iSNDremovetaggedpatch(int bank, int *patch_idx); /* stagpat */ /* @0x801025C0 */

extern signed char snddefaultenvelope[8];
extern unsigned char DAT_801371cc;

#endif /* _SNDPSXZ_STAGPAT_H_ */
